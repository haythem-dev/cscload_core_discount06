/*(c)
********************* PHARMX Customer Order Entry Server *********************

(c) Copyright 1994-1995 by NORDAT Network GmbH
All rights reserved

Class pxOrderTransmit:
Transmission control methods.

REVISION HISTORY

19 Jan 1995 V1.00 REV 00 written by Wolfgang Hoppe.
*/
#include "pxxmit.hpp"
#include <time.hpp>
#include <date.hpp>
#include "types/origintypeenum.inc"
#include "types/messagecodeenum.inc"
#include "pxparameter.hpp"
#include "pxttype.hpp"
#include "pxeventreason.hpp"
#include "pxtxtdoc.hpp"
#include "pxoeparm.hpp"
#include "pxcstrou.hpp"
#include "pxcstot.hpp"
#include "pxcstbas.hpp"
#include "pxcustomerflags.hpp"
#include "pxbranch.hpp"
#include "pxorder.hpp"
#include "pxbase/pxconstants.hpp"
#include "tourinfo.hpp"
#include "tourutil.hpp"

/*----------------------------------------------------------------------------*/
/*  EndProforma: Scans order list and does a proforma close order to get the  */
/*  final prices for all position within the order. This function does affect */
/*  the bulgarian XML application.                                            */
/*----------------------------------------------------------------------------*/
int
pxOrderTransmit::EndProforma
(
)
{
    ClearError();
    if (ActiveOrders_)                   // ensure orders are there
    {
        pxOrder          *order;
        pxOrderListIter   ocursor(*ActiveOrders_);

        while ((order = (pxOrder*) ++ocursor) != NULL)
        {
            if (Session()->isBulgaria())
            {
                order->ProformaInvoice();         // do the bulgarian proforma invoice calculation
            }
            else
            {
                order->CommonProformaInvoice();  // do proforma invoice calculation for all other countries
            }
        }
    }
    return ErrorState();
}

/*----------------------------------------------------------------------------*/
/*  End of Transmission. Close all orders.                                    */
/*----------------------------------------------------------------------------*/
int
pxOrderTransmit::End
(
)
{
    ClearError();
    Order::States state = Order::EntryDeferred;
    int    splittState = 0;
    pxParameter*  suppressparm = NULL;
    TotalTransPos_ = CountOrderPos();      // total count positions of all orders
    nString key;
    key = Customer_->IDFNr();
    pxTimeTypeList *timelist = NULL;
    timelist = new pxTimeTypeList(Session());
    timelist->Select(Type_ADS_DEFER_ORDER, key, Branch()->FilialNr());
    bool cTIMEDEFERORDER = false;
    if (!timelist->Entries())
    {
        delete timelist;
        timelist = NULL;
    }
    else
    {
        cTIMEDEFERORDER = timelist->TimeInWindow();
    }

    if (ActiveOrders_)                   // ensure orders are there
    {
        pxOrderListIter   ocursor(*ActiveOrders_);

        while ((Order_ = (pxOrder*) ++ocursor) != NULL)
        {
            if (CallBack_)
            {
                Order_->SetCallBack();
                Order_->SetProblemClearance();
                Order_->SetEventCode(pxEventReason::CallBack);
            }
            if (Order_->IsCallBack())
            {
                Order_->SetProblemClearance();
                Order_->SetEventCode(pxEventReason::CallBack);
            }

            if (IsSerial() && Order_->AnzPos() == 0)
            {
                pxTextDoc* headtext = Order_->HeadText();
                pxTextDoc* tailtext = Order_->TailText();
                if (!Order_->IsProblemClearance() && !Order_->IsCallBack() &&
                    headtext->Entries() == 0 && tailtext->Entries() == 0)
                {
                    Order_->SetOrderCompleted();
                    continue;
                }
            }

            // do check just orders with no textpositions
            if (Order_->AnzAlphaText() == 0)
            {
                // close order if Dafuart 7 is set
                if (Order_->Customer()->Flags().IsTrennAlphaText() ||
                    Order_->Customer()->Flags().IsTrennAlphaURR())
                {
                    Order_->ClearProblemClearance();
                    state = Order::EntryClosed;
                }
            }
            // close order although Callback is set
            if (Order_->Customer()->Flags().IsAbSchlussRR())
            {
                Order_->ClearProblemClearance();
                state = Order::EntryClosed;
            }

            // close order although Callback is set, even ShipUrgent if possible
            if (Order_->Customer()->Flags().IsAbSchlussRREil())
            {
                if (Order_->ShipUrgentVerification())
                {
                    Order_->ClearProblemClearance();
                    state = Order::EntryClosed;
                }
            }

            if (Order_->IsHoldOrder())
            {
                Order_->SetProblemClearance();
            }
            // if Order_ was send double(swiss spec)
            if (Order_->IsSendOrderDouble())
            {
                // get canned message.
                nMessage text(CMsgStream(), CMSG_ORD_DOUBLE_ORDER, 0);
                nString bem = text.String();
                bem.Compress('\n');
                Order_->Bemerkungen(bem);
                // Prevent writing a KdauftragBem in Branch Ris Orangis(PWS)
                // because sychronization between Shpcon/Shpfac
                if (Order_->FilialNr() != (short)48)
                {
                    Order_ = FreeTextDoc(text.String());
                }
                Order_->SetProblemClearance();
                Order_->SetEventCode(pxEventReason::DoubleOrder);
                Order_->SetDoNotAppend();
            }

            if (Order_->Customer()->Flags().IsAuftragZurueck() || cTIMEDEFERORDER)
            {
                suppressparm = new pxParameter(Session(), Branch()->FilialNr(), (nString)cPAR_HMK_GROUP,
                    (nString)cPAR_HMK_PURPOSE, (nString)cPAR_HMK_PARAMNAME);
                if (!suppressparm->Get(cDBGET_READONLY))
                {
                    if (suppressparm->Wert() != CMSG_ORD_TRANSFER_POSTING)
                    {
                        nMessage text(CMsgStream(), CMSG_ORD_TRANSFER_POSTING);
                        Order_ = FreeTextDoc(text.String());
                        Order_->SetProblemClearance();
                        Order_->SetEventCode(pxEventReason::DeferOrderByParam);
                    }
                    else
                    {
                        Order_->SetProblemClearance();
                        Order_->SetEventCode(pxEventReason::DeferOrderByParam);
                    }
                }
                else
                {
                    nMessage text(CMsgStream(), CMSG_ORD_TRANSFER_POSTING);
                    Order_ = FreeTextDoc(text.String());
                    Order_->SetProblemClearance();
                    Order_->SetEventCode(pxEventReason::DeferOrderByParam);
                }
                delete suppressparm;
                suppressparm = NULL;
            }

            if (!WrongIDFNr_.IsEmpty())
            {
                nMessage text(CMsgStream(), CMSG_XMIT_INVALID_CUSTOMER, (char*)WrongIDFNr_, 0);

                Order_ = FreeTextDoc(text.String());
                Order_->SetProblemClearance();
                Order_->SetEventCode(pxEventReason::WrongCustomerNumber);
            }

            if (Order_->IsProblemClearance())
            {
                Order_->SetProblemClearance();
                state = Order::EntryDeferred;
            }
            else
                state = Order::EntryClosed;

            if (IsOrderConsolidation() && Order_->CloseOptions() == Order::CLOSE_DEFAULT)
            {
                Order_->SetConsolidation();
                state = Order::EntryDeferred;
            }
            if (!Session()->isBulgaria() && !Order_->Param()->IsSCrema())
            {
                if (Order_->CheckForCreditSumOnTop())
                {
                    Order_->SetKreditLimitErreicht();
                    Order_->SetProblemClearance();
                    Order_->SetEventCode(pxEventReason::CreditLimitExceeded);
                    state = Order::EntryDeferred;
                }
            }

            if (Order_->IsDDNotClose())
            {
                Order_->SetProblemClearance();
                Order_->SetEventCode(pxEventReason::NotCloseDelayedDeliveryOrder);
                state = Order::EntryDeferred;
            }

            if ((AnzPosZu() > 0) && (TotalTransPos_ >  AnzPosZu()))
            {
                Order_->SetProblemClearance();
                Order_->SetEventCode(pxEventReason::TotalTransPosExceeded);
                state = Order::EntryDeferred;
            }

            // For batchserver
            if (IsFileTransfer() || (Order_->BatchSchreiben()) > 0)
            {
                if (Order_->BatchSchreiben() == cORTYPE_TRANSFER && (Session()->IsSubDeviceTypeOf(ABBA) || Session()->IsSubDeviceTypeOf(CSCBATCH)))
                {
                    if (Order_->IsHoldOrder())
                    {
                        Order_->ClearProblemClearance();
                        state = Order::EntryDeferred;
                    }
                    else
                    {
                        Order_->ClearProblemClearance();
                        state = Order::EntryClosed;
                    }
                }
                else
                {
                    state = Order::EntryDeferred;
                    if (Order_->BatchSchreiben() == cORTYPE_AUXILIARY)
                    {
                        if (Order_->Param()->MaxPosVerbund() > 0)
                        {
                            if (Order_->AnzPos() > Order_->Param()->MaxPosVerbund())
                                state = Order::EntryClosed;
                        }
                    }
                }
            }
            /*----------------------------------------------------------------------------*/
            /*        XML Dispatching Chemist with OrderConsolidation                     */
            /*----------------------------------------------------------------------------*/
            if (Order_->Customer()->Flags().IsVersandApo() || Order_->isMSV3Order())
            {
                /*----------------------------------------------------------------------------*/
                /*           Order_->Customer()->AnzAufClose() has the main priority          */
                /*----------------------------------------------------------------------------*/
                if (IsOrderConsolidation() && Order_->Customer()->AnzAufClose() > 0)
                {
                    if (Order_->AnzAuf() >= Order_->Customer()->AnzAufClose())
                    {
                        Order_->ClearConsolidation();
                        Order_->SetDoNotAppend();
                        Order_->ClearProblemClearance();
                        state = Order::EntryClosed;
                    }
                }
                else if (IsOrderConsolidation())
                {
                    if (Order_->Param()->AnzAufClose() > 0)
                    {
                        if (Order_->AnzAuf() >= Order_->Param()->AnzAufClose())
                        {
                            Order_->ClearConsolidation();
                            Order_->SetDoNotAppend();
                            Order_->ClearProblemClearance();
                            state = Order::EntryClosed;
                        }
                    }

                    if (Order_->Param()->AnzPosClose() > 0)
                    {
                        if (Order_->AnzPos() >= Order_->Param()->AnzPosClose())
                        {
                            Order_->ClearConsolidation();
                            Order_->SetDoNotAppend();
                            Order_->ClearProblemClearance();
                            state = Order::EntryClosed;
                        }
                    }
                }

                if (Order_->Customer()->Flags().IsNoCloseDefVB() &&
                    state == Order::EntryClosed)
                {
                    if (Order_->CountDefects()  > 0 || Order_->CountAuxDeliveryPos() > 0)
                    {
                        Order_->SetProblemClearance();
                        Order_->SetEventCode(pxEventReason::NoCloseDefectAndIBTPositions);
                        state = Order::EntryDeferred;
                    }
                }
            }

            //special  applications  for orderconsolidation Germany
            if (Session()->isGermany())
            {
                if (Order_->Param()->AnzPosClose() > 0 && IsOrderConsolidation() &&
                    !Order_->Customer()->Flags().IsVersandApo() &&
                    !Order_->IsSendOrderDouble() && (Order_->Customer()->KdGruppe() == "01" ||
                        Order_->Customer()->KdGruppe() == "06") && !Order_->OrderType().IsTransfer() &&
                    !Order_->IsProblemClearance())
                {
                    if (Order_->AnzPos() >= Order_->Param()->AnzPosClose())
                    {
                        Order_->ClearConsolidation();
                        Order_->ClearProblemClearance();
                        state = Order::EntryClosed;
                    }
                }
            }
            else
                //special  applications  for orderconsolidation all other countries
                if (Order_->Param()->AnzPosClose() > 0 && IsOrderConsolidation() &&
                    !Order_->Customer()->Flags().IsVersandApo() &&
                    !Order_->IsSendOrderDouble() && !Order_->IsProblemClearance())
                {
                    if (Order_->AnzPos() >= Order_->Param()->AnzPosClose())
                    {
                        Order_->ClearConsolidation();
                        Order_->ClearProblemClearance();
                        state = Order::EntryClosed;
                    }
                }

            //special for Swiss application Overdrive
            if (isSwitzerland() && CheckOrderOverdrive())
            {
                Order_->SetProblemClearance();
                Order_->SetEventCode(pxEventReason::CheckOrderOverdrive);
                state = Order::EntryDeferred;
            }

            /*----------------------------------------------------------------------------*/
            /*        Defer order depend on odertype flag                                 */
            /*----------------------------------------------------------------------------*/
            if (Order_->OrderType().IsDeferOrder())
            {
                Order_->SetProblemClearance();
                Order_->SetEventCode(pxEventReason::OrderTypeIsDeferOrder);
                state = Order::EntryDeferred;
            }

            // INC-045681
            if (WrongIDFNr_.IsEmpty())
            {
                if (Session()->isGermany())
                {
                    splittState = SeparateDefects_DE();
                }
                else
                {
                    splittState = SeparateDefects();
                }
                if (splittState != 0)
                {
                    Order_->ClearConsolidation();
                    Order_->ClearProblemClearance();
                    Order_->Close((Order::States)splittState);
                }
                else
                {
                    Order_->Close(state);
                }
            }
            else
            {
                Order_->Close(state);
            }
            // For batchserver
            if (!IsFileTransfer())
                Customer_ = Order_->Customer();
        }
    }
    Reset();
    return ErrorState();
}

/*----------------------------------------------------------------------------*/
/*  Cancel entire transmission.                                               */
/*----------------------------------------------------------------------------*/
int
pxOrderTransmit::CancelTransmission
(
)
{
    ClearError();
    if (ActiveOrders_)
    {
        pxOrder* order;
        pxOrderListIter   ocursor(*ActiveOrders_);
        while ((order = (pxOrder*) ++ocursor) != NULL)
        {
            order->CancelOrder(pxDVC_UNDEFINED);
        }
    }
    Reset();
    return ErrorState();
}

/*----------------------------------------------------------------------------*/
/*  Customer call back request. This is a transmission oriented function,     */
/*  thus a flag within self is set.  Since we do not have a corresponding     */
/*  data base entity for a transmission, each order flagged at the end of     */
/*  the transmission.                                                         */
/*----------------------------------------------------------------------------*/
void pxOrderTransmit::CallBack()
{
    CallBack_ = true;
}

/*----------------------------------------------------------------------------*/
/* CountOrderPos: this function counts on the end of a transmission, the      */
/* positions of all generated activ orders during this transmission.          */
/*----------------------------------------------------------------------------*/
long pxOrderTransmit::CountOrderPos()
{
    long count = 0;
    if (ActiveOrders_)                   // ensure orders are there
    {
        pxOrder        *order;
        pxOrderListIter cursor(*ActiveOrders_);

        while ((order = (pxOrder*) ++cursor) != NULL)
        {
            count += order->AnzPos();
        }
    }
    return  count;
}
