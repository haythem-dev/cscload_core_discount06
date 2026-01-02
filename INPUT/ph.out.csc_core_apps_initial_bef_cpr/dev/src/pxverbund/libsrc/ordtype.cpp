#include "pxrecord.h"
#include "pxdevice.hpp"
#include "pxsess.hpp"
#include "pxcstbas.hpp"
#include "pxartbas.hpp"
#include "pxitem.hpp"
#include "pxorder.hpp"
#include "pxoeparm.hpp"
#include "pxstktra.hpp"
#include "pxcomtyp.hpp"
#include "pxordtyp.hpp"
#include "pxordvtr.hpp"
#include "pxcstot.hpp"
#include "pxcustdisccondition.hpp"
#include "pxsubordertype.hpp"
#include "pxholiday.hpp"
#include "pxbase/pxconstants.hpp"
#include "types/messagecodeenum.inc"

extern bool pxGlobalNoDatabaseWrite;
extern bool pxGlobalCollectiveOrderDiscountable;

/*----------------------------------------------------------------------------*/
/*  Set Order Type API.                                                       */
/*  Returns number of order items that have gone into quantity state          */
/*  'NotOnHand' during re-doing quantity posting, otherwise 0 is returned.    */
/*  To catch errors and conditions, the error object must be explicitly       */
/*  tested.                                                                   */
/*----------------------------------------------------------------------------*/
int pxOrder::OrderType(const nString& KdAuftragArt, const char KoArt, const char BuchArt)
{
    int   retval = 0;
    ClearError();

    // return if ordertype, bookingtype and pickingtype do not change (OrderType already processed before!)
    if (NULL != OrderType_ && NULL != CommType_ && NULL != StockTrans_)
    {
        if ((KdAuftragArt == OrderType_->KdAuftragArt()) && KoArt == CommType_->KoArt() && BuchArt == StockTrans_->BuchArt())
        {
            return retval;
        }
    }

    /*----------------------------------------------------------------------------*/
    /*  Locate table entries for order type, commission type and stock transaction*/
    /*----------------------------------------------------------------------------*/
    pxCustOrderType* ot = Customer()->OrderTypeList()->Find(KdAuftragArt, Customer()->Vertriebszentrum(), Customer()->KundenNr());
    pxCommType* ct = Session()->CommTypeList(Customer()->Vertriebszentrum())->Find(KoArt, Customer()->Vertriebszentrum());
    pxStockTrans* st = Session()->StockTransList(Customer()->Vertriebszentrum())->Find(BuchArt, Customer()->Vertriebszentrum());
    if (!ot)
    {
        ExternalError(CMsgStream(), CMSG_ORD_TYPE_CUST, (char*)KdAuftragArt, IDFNr_);
        return retval;
    }
    if (!ct)
    {
        ExternalError(CMsgStream(), CMSG_ORD_INVALID_COMMTYPE, (int)KoArt);
        return retval;
    }
    if (!st)
    {
        ExternalError(CMsgStream(), CMSG_ORD_INVALID_STOCKTRANS, (int)BuchArt);
        return retval;
    }

    // Test for a valid combination:
    if (!(Session()->OrderValidTransList(Customer()->Vertriebszentrum())->Find(KdAuftragArt, (KoArt - '0'), (BuchArt - '0'), Customer()->Vertriebszentrum())))
    {
        ExternalError(CMsgStream(), CMSG_ORD_TYPE_COMB,
            (char*)KdAuftragArt, (int)KoArt, (int)BuchArt);
        return retval;
    }

    /*----------------------------------------------------------------------------*/
    /*  Test if this is an initial load while order is being opened.              */
    /*  We only keep the table pointers within self in that case.                 */
    /*----------------------------------------------------------------------------*/
    if (OrderType_ == NULL)           // yes, we are called during open
    {
        OrderType_ = ot;            // store table pointers
        CommType_ = ct;
        StockTrans_ = st;
        return retval;             // and we are done here
    }

    // CR-15D035 - Alle Aufträge mit Bestellfenster-ID und Auftragskennung ausstatten
    //bool hadDefaultOrderLabelBefore = this->hasDefaultOrderLabel();

/*----------------------------------------------------------------------------*/
/*  Test if anything changed.                                                 */
/*----------------------------------------------------------------------------*/
    if ((ot == OrderType_) && (ct == CommType_) && (st == StockTrans_))
        return retval;             // then nothing has changed
    //if ( (ot == OrderType_) && (st == StockTrans_) )
    //    return retval;             // then nothing has changed

/*----------------------------------------------------------------------------*/
/*  Additional sanity checks.                                                 */
/*----------------------------------------------------------------------------*/
    if (!IsChangeable())
        return retval;             // order not changeable
                                        // count stocked products
    int count = CountItems(bCOUNT_ITEMTYPE,
        (long)pxOrderItem::TypeProductStocked);
    if (ct != CommType_)              // commission type changed
    {
        ;                               // test if valid for customer
    }
    if (st != StockTrans_)              // then stock transaction changed
    {
        ;                               // test for valid changes
    }

    // If order type has changed and stocked product items are already entered,
    // an order type change to or from a type where entering discount-in-kind
    // quantities is allowed will be denied, due to the lack of recovery methods.
    if (ot != OrderType_ && count > 0)
    {
        /*if ( ot->IsCashOrder() )
        {
            UndoCreditDayTurnOver();
            //CancelCurrentCreditDayTurnOver();
        }
        */
        if (OrderType_->IsDisInKindEnterable() || ot->IsDisInKindEnterable())
        {
            if (Param()->IsSNOToAK())
            {
                if (!OrderType_->IsNormal() && !ot->IsActive3000())
                {
                    ExternalError(CMsgStream(), CMSG_ORD_TYPE_DENIED);
                    return retval;
                }
            }
            else
            {
                ExternalError(CMsgStream(), CMSG_ORD_TYPE_DENIED);
                return retval;
            }
        }
    }

    /*----------------------------------------------------------------------------*/
    /*  Update order type values.                                                 */
    /*----------------------------------------------------------------------------*/
    if (IsCollectiveOrderDiscountable())
    {
        pxGlobalCollectiveOrderDiscountable = true;
    }

    // Save old values before loading the new ones
    pxCustOrderType* oldot = OrderType_;
    pxCommType* oldct = CommType_;
    pxStockTrans* oldst = StockTrans_;


    /*----------------------------------------------------------------------------*/
    /*  SR-15004144 Check contents of order. If there are already worked up       */
    /*  IBT positions or daynightmerge positions within this order, so change of  */
    /*  order type is not allowed.                                                */
    /*----------------------------------------------------------------------------*/
        // is this an order type change ??
    if ((count > 0) && (ot != oldot || st != oldst)/* && !(ot->IsCashOrder())*/)
    {
        if (hasAtLeastOneCompletedIbtBooking() || CountDayNightMergePositions() > 0 || CountSeparatedPositions() > 0)
        {
            ExternalError(CMsgStream(), CMSG_ORD_CHANGE_OF_ORDERTYPE_NOT_ALLOWED);
            return retval;
        }
    }


    OrderType_ = ot;               // store table pointers
    CommType_ = ct;
    StockTrans_ = st;
    KdAuftragArt_ = KdAuftragArt;
    KoArt_ = KoArt;
    BuchArt_ = BuchArt;

    if (IsEntryInProgress() && CommType_->IsNoShipment())
    {
        RouteAssignClearTourAssignment();
    }

    SetDirty();

    Customer()->DeleteRouteList();
    RouteList();
    if (RouteList() == NULL)
        ClearError();

    /*----------------------------------------------------------------------------*/
    /*  Test for order type and/or stock transaction changes. Quantity posting    */
    /*  and calculation of terms and conditions for stocked product items must    */
    /*  be re-done in that case.                                                  */
    /*----------------------------------------------------------------------------*/
    nDBBeginTransaction(cDBTransSet);   // embed the following in a transaction
  //  if ( (count > 0) && (ot != oldot || st != oldst || ct != oldct ) )
    pxOrderItemListIter it(*ItemList());
    pxOrderItem* item;
    if ((count > 0) && (ot != oldot || st != oldst) /*&& !(ot->IsCashOrder())*/)
    {
        while (((item = (pxOrderItem*) ++it) != NULL) && IsGoodState())
        {
            if (item->IsProductStocked())
            {
                retval = retval + item->UndoRedo(*oldot, *oldct, *oldst);
                Error() = item->Error();
                CalcPromotionQuota(item);        // redo Promotionquota
            }
        }
        pxGlobalCollectiveOrderDiscountable = false;
    }
    else
        if ((count > 0) && ct != oldct)
        {
            if (ct->IsNoShipment())
            {
                while (((item = (pxOrderItem*) ++it) != NULL) && IsGoodState())
                {
                    if (item->IsProductStocked())
                    {
                        retval = retval + item->UndoCommission();
                        Error() = item->Error();
                    }
                }
            }
            else
                if (oldct->IsNoShipment())
                {
                    while (((item = (pxOrderItem*) ++it) != NULL) && IsGoodState())
                    {
                        if (item->IsProductStocked())
                        {
                            retval = retval + item->DoCommission();
                            Error() = item->Error();
                        }
                    }
                }
        }

    // CR-15D035 - Alle Aufträge mit Bestellfenster-ID und Auftragskennung ausstatten
    /*
    if( this->Session()->Device()->IsVideo() )
    {
        if( hadDefaultOrderLabelBefore || !this->isMSV3Order() )
        {
            this->SetDefaultOrderLabel();
        }
    }
    */

    /*----------------------------------------------------------------------------*/
    /*  Update order, then write it into the data base.                           */
    /*----------------------------------------------------------------------------*/
    if (IsGoodState())
    {
        ReCalcValues();
        Put();                        // update data base
    }

    if (IsGoodState())
        nDBCommit(cDBTransSet);          // commit changes
    else
        nDBRollBack();                   // or roll them back in case of any error
    if (pxGlobalNoDatabaseWrite)
        ClearError();
    return retval;
}
/*----------------------------------------------------------------------------*/
/*  OrderType: Main param in this methode is SubOrderTyp. If SubOrderType     */
/*  IsEmpty, so control is given to OrderType, otherwise SubOrderType is      */
/*  checked against Customers DiscountConditions. That means: KdAuftragArt +  */
/*  SubOrderType must have entries both within table DISCOUNTLIST and         */
/*  CSTDISCOUNTCONT, additionaly DISCOUNTLIST->PharmacyGroupId must be        */
/*  within Customers PharmacyGroupList. If everything is ok, so control is    */
/*  to OrderType, otherwise control is been given to the caller               */
/*----------------------------------------------------------------------------*/
int
pxOrder::OrderType
(
    const nString& KdAuftragArt,
    const char    KoArt,
    const char    BuchArt,
    const nString& SubOrderType
)
{
    int   retval = 0;
    ClearError();
    pxCustBase* customer = Customer();  // customer
    nString  subot = SubOrderType;      // for check
    subot.Strip();                      // may be just blank
    pxCustOrderType* ot = Customer()->OrderTypeList()->Find(KdAuftragArt, Customer()->Vertriebszentrum(), Customer()->KundenNr());
    pxDevice* device = Session()->Device();
    Session()->HoliDayList(Customer()->Vertriebszentrum());
    nDate today;

    if (!device->IsVideo())         // is  dct
    {
        if (ot == NULL)
        {
            ExternalError(CMsgStream(), CMSG_ORD_TYPE_CUST, (char*)KdAuftragArt, IDFNr_);
            return retval;
        }
        if (!ot->IsValidViaDCT())
        {
            ExternalError(CMsgStream(), CMSG_ORD_TYPE_CUST, (char*)KdAuftragArt, IDFNr_);
            return retval;
        }
    }

    if (subot.IsEmpty())              // control to OrderType
    {
        if (AnzPos_ == 0)
        {
            SubOrderType_.Clear();
            customer->DeconstructSubOrderType();
            customer->DeconstructCustDiscCondition();
        }
        OrderType(KdAuftragArt, KoArt, BuchArt);
        // do check for Collecttive Orders CV22
        nString  aufArt;
        aufArt = KdAuftragArt_ + (nString)KoArt_ + (nString)BuchArt_;
        if (aufArt == cCOLLECTIVORDER22)
        {
            DatumAuslieferung_ = today.AddMonth(12);
        }
        return  ErrorState();
    }

    // now ordertype and subordertype are available
    if (customer->DiscountConditions(KdAuftragArt, SubOrderType)) // check customers discountconditions
    {
        Error() = (customer->Error());                     // copy error
        return  ErrorState();
    }
    SetSubOrderType(SubOrderType);
    nString cpaymentterm = customer->CustDiscCondition()->PaymentTerm();
    nString paymentterm = customer->SubOrderType()->PaymentTerm();
    cpaymentterm.Strip();
    paymentterm.Strip();
    SetPaymentTerm(paymentterm);
    if (!cpaymentterm.IsEmpty())
        SetPaymentTerm(cpaymentterm);

    return  (OrderType(KdAuftragArt, KoArt, BuchArt));
}

/*----------------------------------------------------------------------------*/
/*  SetOrderToCash: PaymentType_ is set to  'C'(ash)                          */
/*  Credits are turned back to the database and paymentterms are set to zero  */
/*  This is called after CreMa approval as Cash Order                          */
/*----------------------------------------------------------------------------*/
int pxOrder::SetOrderToCash()
{
    //UndoCreditDayTurnOver();               // return credit back: no longer required due to openorder
    SetPaymentDate(pxConstants::NullDate); // set PaymentDate to zero
    SetPaymentType('C');                   // now cash order
    ClearUpdateDebtlimitK2();              // clear update debtlimt K2
    ClearUpdateDebtlimitK1();              // clear update debtlimt K1
    SetDatumValuta(pxConstants::NullDate); // clear
    return ErrorState();
}

/*----------------------------------------------------------------------------*/
/*  SetOrderToCashAe: PaymentType_ is set to  'C'(ash)                          */
/*  Credits are turned back to the database and paymentterms are set to zero  */
/*  This is called from AE and KSCServer | when order is set to Cash explicitly by customer   */
/*----------------------------------------------------------------------------*/
int pxOrder::SetOrderToCashAe()
{
    if (!(Session()->getOrderEntryParam(Customer()->Vertriebszentrum())->IsSCrema()))
    {
        UndoCreditDayTurnOver();               // return credit back
    }
    SetPaymentDate(pxConstants::NullDate); // set PaymentDate to zero
    SetPaymentType('C');                   // now cash order
    ClearUpdateDebtlimitK2();              // clear update debtlimt K2
    ClearUpdateDebtlimitK1();              // clear update debtlimt K1
    SetDatumValuta(pxConstants::NullDate); // clear
    return ErrorState();
}

/*----------------------------------------------------------------------------*/
/*  SetOrderWithTimeForPayment: PaymentType_ is set to  'Z'(ahlungsziel)      */
/*  Redo Credits to sumdayturnover of the deblimits entries                   */
/*----------------------------------------------------------------------------*/
int pxOrder::SetOrderWithTimeForPayment()
{
    nMoney           diffValue(0.0);          // exceedance of  Creditlimit
    SetPaymentType('Z');                      // now order with payment term
    RedoCreditDayTurnOver(OrderValue_);
    diffValue = checkCreditLimitOverflow();
    if (diffValue > pxConstants::mZero)     // credit limit exhausted
    {
        SetOrderToCash();
        ExternalCondition(CMsgStream(), CMSG_ORD_CREDITLIMIT_EXHAUSTED, (double)diffValue);
        return ErrorState();
    }
    return ErrorState();
}
