#include "pxsess.hpp"
#include "pxdevice.hpp"
#include "pxbranch.hpp"
#include "pxcstbas.hpp"
#include "pxartbas.hpp"
#include "pxitem.hpp"
#include "pxorder.hpp"
#include "pxoeparm.hpp"
#include "pxcomtyp.hpp"
#include "pxseporderartgrp.hpp"
#include "pxtxtdoc.hpp"
#include <logger/loggerpool.h>
#include "pxbase/pxconstants.hpp"
#include "types/messagecodeenum.inc"

/*----------------------------------------------------------------------------*/
/* SeparatePriceType ; a bulgarian speciality                                 */
/* The current Order(*this) will be scanned for items with pricetypes         */
/* defined in the parameter table SEPORDERARTGRP                              */
/* The related items are place into a separate order                          */
/* Take care for a well constructed pxOrder object to prevent unpredictable   */
/* results                                                                    */
/*----------------------------------------------------------------------------*/
Order::States
pxOrder :: SeparatePriceType
(
    int     &healthfundq,
    int     &retailq
)
{
    Order::States State = Order::LeaveAsIs;
    pxDebitLimit*       debtlimit = NULL;                // customers debtlimit entry pointer
    if ( KdAuftragNrOrg_ > 0 )                 // nothing to do
    {
       return State;
    }

    if ( IsDoNotSplittOrder() )
    {
       return State;
    }

    if ( IsPseudoLock() )                     // Do not Splitt if PreudoLock
    {
       return State;                          // INC-031782 INC-032063
    }


    pxOrderItemListIter it(*ItemList_);        // iterator itemlist
    pxOrder* seporder                = NULL;   // separated  order
    pxSepOrderArtGroup*   entryp     = NULL;
    pxCustBase* customer             = Customer();
    short BranchNo                  = customer->Vertriebszentrum();
    nString KdAuftragArt;                      // ordertype
    char   KoArt   = ' ';                     // commi
    char   BuchArt = ' ';                     // book
    nDate now;
    int      CountFreeSale         = 0;



    pxSepOrderArtGroupList* SepOList = SepOrderArtGroupList();
    if ( SepOList->Entries() == 0 )            // nothing to do
    {
       return State;
    }

    if ( healthfundq == 0 && retailq == 0 )
       return State;

    CountFreeSale = CountPriceTypeItems(FREESALE_PRICE );

/*----------------------------------------------------------------------------*/
/*  Separate item with pricetype = HealthFund(KK)                             */
/*----------------------------------------------------------------------------*/
    if ( healthfundq )
    {
       entryp = SepOList->Find(BranchNo,(short)pxSepOrderArtGroup::SEP_GROUP_HEALTHFUND);
       if (entryp != NULL)
       {
          // Just pricetype
          if ( AnzPos_ == CountPriceTypeItems(HEALTHFUND_PRICE ) )
          {
             KdAuftragArt = entryp->KdAuftragArt();
             BuchArt      = entryp->BuchArt();
             KdAuftragArt.Strip();
             KdAuftragArt = ( KdAuftragArt.IsEmpty() ) ? KdAuftragArt_ : KdAuftragArt;
             if (CommType_->IsShipNormal() )
             {
                KoArt        = entryp->KoArt();
             }
             KoArt        = ( KoArt   == ' ' ) ? KoArt_   : KoArt;
             BuchArt      = ( BuchArt == ' ' ) ? BuchArt_ : BuchArt;
             OrderType(KdAuftragArt,KoArt,BuchArt);
             if (entryp->IsDeferOrder() )
             {
                SetProblemClearance();
                SetSeparateArtGroup();
                State = Order::EntryDeferred;
             }
             else
             {
                State = Order::EntryClosed;
             }
             return State;
          }

          seporder = SeparateHealthFund(&healthfundq, entryp);
          if (seporder)
          {
             seporder->SeparateBigOrder();
             if (entryp->IsDeferOrder() )
             {
                seporder->SetProblemClearance();
                seporder->SetSeparateArtGroup();
                seporder->CloseState(Order::EntryDeferred); // set order state flags
                seporder->CloseOrder();
             }
             else
             {
                seporder->Close(Order::EntryClosed, Order::cClose_SeparatedOrder);   // set order state flags
             }
             if ( seporder->IsGoodState() )
             {
                delete seporder;
                seporder = NULL;
             }
          }
       }
    }
/*----------------------------------------------------------------------------*/
/*  Separate item with pricetype = Retail(EV)                                 */
/*----------------------------------------------------------------------------*/
    if ( retailq )
    {
       entryp = SepOList->Find(BranchNo,(short)pxSepOrderArtGroup::SEP_GROUP_RETAIL);
       if (entryp != NULL)
       {
          // Just pricetype
          if ( AnzPos_ == CountPriceTypeItems(RETAIL_PRICE) )
          {
             KdAuftragArt = entryp->KdAuftragArt();
             BuchArt      = entryp->BuchArt();
             KdAuftragArt.Strip();
             KdAuftragArt = ( KdAuftragArt.IsEmpty() ) ? KdAuftragArt_ : KdAuftragArt;
             if (CommType_->IsShipNormal() )
             {
                KoArt        = entryp->KoArt();
             }
             KoArt        = ( KoArt   == ' ' ) ? KoArt_   : KoArt;
             BuchArt      = ( BuchArt == ' ' ) ? BuchArt_ : BuchArt;
             OrderType(KdAuftragArt,KoArt,BuchArt);
             if (entryp->IsDeferOrder() )
             {
                SetProblemClearance();
                SetSeparateArtGroup();
                State = Order::EntryDeferred;
             }
             else
             {
                State = Order::EntryClosed;
             }
             return State;
          }

          seporder = SeparateRetail(&retailq, entryp);
          if (seporder)
          {
             seporder->SeparateBigOrder();
             if (entryp->IsDeferOrder() )
             {
                seporder->SetProblemClearance();
                seporder->SetSeparateArtGroup();
                seporder->CloseState(Order::EntryDeferred); // set order state flags
                seporder->CloseOrder();
             }
             else
             {
                seporder->Close(Order::EntryClosed, Order::cClose_SeparatedOrder);   // set order state flags
             }
             if ( seporder->IsGoodState() )
             {
                delete seporder;
                seporder = NULL;
             }
          }
       }
    }

    if ( CountFreeSale > 0 )
    {
       if ( DatumValuta_ != pxConstants::NullDate )
       {
          if ( (Customer()->IsCashPayer( FREESALE_PRICE, this ) ) )
          {
             debtlimit = customer->DebitLimitK2(); // get pointer to customers debtlimit entry
             if ( debtlimit == NULL )
             {
                SetDatumValuta(pxConstants::NullDate);
             }
          }
       }
    }


    return State;
}
/*----------------------------------------------------------------------------*/
/* SeparateHealthFund:                                                        */
/* The current Order(*this) will be scanned for items with pricetype          */
/* HEALTHFUND to be placed in an extra order                                  */
/* Prerequisites for this process is a corresponding reserve HEALTHFUND entry */
/* within the following table;   SEPORDERARTGRP                               */
/* Take care for a well constructed pxOrder object to prevent unpredictable   */
/* results                                                                    */
/*----------------------------------------------------------------------------*/
pxOrder*
pxOrder ::  SeparateHealthFund
(
    int          *healthfundq,
    pxSepOrderArtGroup*  entryp
)
{
    // avoid "unused" compiler warning
    { healthfundq = healthfundq; }

    // unused variable
    // int  retval = 0;
    nDate today;
    pxOrder* seporder        = NULL;         // splitt order
    pxOrderItemListIter it(*ItemList());
    pxOrderItem *item;
    pxOrderItem *delitem;
    pxCustBase* customer = Customer();
    // unused variable
    /* pxOrderEntryParam &param = */ Param();
    nString KdAuftragArt;                   // ordertype
    char   KoArt   = ' ';                  // commi
    char   BuchArt = ' ';                  // book
    nString m_str;
    m_str = "pxOrder ::  SeparateHealthFund";

/*----------------------------------------------------------------------------*/
/*  do some checks before to prevent unpredictable relsults                   */
/*----------------------------------------------------------------------------*/
    if ( entryp == NULL )                    // if no entry within SEPORDERARTGRP
       return seporder;
    if ( !entryp->IsHealthFund())    // this entry has to be a HealthFund entry
       return seporder;

    if (CommType_->IsNoShipment() || CommType_->IsShipDisposal() || CommType_->IsShipDeliveryNote() )
       return seporder;

    KdAuftragArt = entryp->KdAuftragArt();
    if (CommType_->IsShipNormal() )
    {
       KoArt     = entryp->KoArt();          // just if KommArt = 0
    }
    BuchArt      = entryp->BuchArt();
    KdAuftragArt.Strip();
    KdAuftragArt = ( KdAuftragArt.IsEmpty() ) ? KdAuftragArt_ : KdAuftragArt;
    BuchArt      = ( BuchArt == ' ') ? BuchArt_ : BuchArt;
    KoArt        = ( KoArt == ' ' ) ? KoArt_ : KoArt;

    // Now scan this order for reserve Hospital article
    while ( (item = (pxOrderItem*) ++it) != NULL )
    {
       if ( item->IsCancelled() )
       {
          item->SetNichtNachPharmos();
          continue;
       }
       if ( item->ArtikelNr() == 0 )
       {
          item->SetNichtNachPharmos();
          continue;
       }
       if ( !item->IsKnownProduct() )
       {
          item->SetNichtNachPharmos();
          continue;
       }
       if (item->IsPriceTypeHealthFund() )
       {
          if ( item->MengeGeliefert() ==  0 )
          {
             item->SetNichtNachPharmos();
             continue;
          }
          if ( item->MengeGeliefert() > 0 )
          {
             if ( seporder == NULL )
             {
                seporder = new pxOrder(Session(),*customer);
                if ( !seporder->IsGoodState() )
                {
                   delete seporder;
                   seporder = NULL;
                   break;
                }

                seporder->OrderType(KdAuftragArt,KoArt,BuchArt);
                seporder->KdAuftragNrOrg(KdAuftragNr_);
                seporder->DafueAuftragNr((long) cDCTSequenceNumDDELMax);
                seporder->DatumAuslieferung( DatumAuslieferung_);
                seporder->setPurchaseOrderNo(getPurchaseOrderNo());
                seporder->HerkunftFiliale(HerkunftFiliale());
                seporder->BatchSchreiben(BatchSchreiben());
                seporder->SetPaymentTerm(PaymentTerm());
                seporder->SetPaymentType( PaymentType() );
                seporder->SetTenderNo(TenderNo_);
                seporder->BTMFormularNr(BTMFormularNr_);
                seporder->DatumBTM(DatumBTM_);
                seporder->DatumVersand(DatumVersand_);
                seporder->Customer()->CopyCstPrintList(Customer()->CstPrintList());
                seporder->Bemerkungen(Bemerkungen());
                seporder->SetOrderLabel(OrderLabel());
                seporder->SetKdAuftragNrOrgRO(KdAuftragNrOrgRO());
                //seporder->SetSeparatedOrder();
                if ( DatumValuta_ != pxConstants::NullDate )
                {
                      seporder->SetDatumValuta(DatumValuta_);
                      seporder->SetValutaMonManuell(ValutaMonManuell_);
                }
                if ( pxConstants::NullDate != RODateFrom_ && pxConstants::NullDate != RODateTo_ )
                {
                   seporder->SetRODateFrom(RODateFrom_.GetYYYYMMDD());
                   seporder->SetRODateTo(RODateTo_.GetYYYYMMDD());
                }
                seporder->SetRouteForOrderSeparation( TourId(), DatumAuslieferung() );

                // Look for Headtext
                pxTextDoc* headtext = HeadText();
                pxTextDoc* tailtext = TailText();
                pxTextDocIter headiter  = pxTextDocIter(*headtext);
                pxTextDocIter tailiter  = pxTextDocIter(*tailtext);
                if (headtext->Entries() > 0)
                {
                   pxTextDoc *headp = seporder->HeadText();
                   while ( (headtext = (pxTextDoc *) ++headiter) != NULL )
                   {
                      nString headline = ((pxTextLine*) headtext)->Text();
                      headp->NewLine(headline);
                   }
                }
                // Look for Tailtext
                if (tailtext->Entries() > 0)
                {
                   pxTextDoc *tailp = seporder->TailText();
                   while ( (tailtext = (pxTextDoc *) ++tailiter) != NULL )
                   {
                      nString tailline = ((pxTextLine*) tailtext)->Text();
                      tailp->NewLine(tailline);
                   }
                }
             }
             delitem = seporder->CopyOrderItem(item, pxOrderItem::SeparateArticle, SplittType_Unknown);
             BLOG_DEBUG( libcsc::LoggerPool::getLoggerDiscountCalc(), m_str() );
             delitem->UndoRedoItemDiscount(item);
             delitem->UndoRedoOrderPosPromo(item);
             delitem->UndoRedoOrderPosRefund(item);
             delitem->InvoiceValue();             // recalc PreisFaktur
             // now delete item members
             item->MengeBestaetigt( 0L);
             item->MengeGeliefert( 0L);
             item->MengeAbgebucht( 0L);
             item->MengeNatra( 0L);
             item->SetSeparatePosition();
             item->SetNichtNachPharmos();
             nString KdAuftragNr;
             KdAuftragNr = seporder->KdAuftragNr();

             nMessage msg(CMsgStream(), CMSG_ITM_SEPARATE_ARTGROUP_S, (char*)&KdAuftragNr);
             nString posbem = msg.String();
             posbem.Compress('\n');
             item->Bemerkungen(posbem,item->LinkPosNr());
          }
       }
    }
    return seporder;
}
/*----------------------------------------------------------------------------*/
/* SeparateRetail:                                                            */
/* The current Order(*this) will be scanned for items with pricetype Retail   */
/* to be placed in an new order                                               */
/* Prerequisites for this process is a corresponding reserve Retail entry     */
/* within the following table;   SEPORDERARTGRP                               */
/* Take care for a well constructed pxOrder object to prevent unpredictable   */
/* results                                                                    */
/*----------------------------------------------------------------------------*/
pxOrder*
pxOrder ::  SeparateRetail
(
         int          *retailq,
   pxSepOrderArtGroup*  entryp
)
{
    // avoid "unused" compiler warning
    { retailq = retailq; }

    // unused variable
    // int  retval = 0;
    nDate today;
    pxOrder* seporder        = NULL;         // splitt order
    pxOrderItemListIter it(*ItemList());
    pxOrderItem *item;
    pxOrderItem *delitem;
    pxCustBase* customer = Customer();
    // unused variable
    /* pxOrderEntryParam &param = */ Param();
    nString KdAuftragArt;                   // ordertype
    char   KoArt   = ' ';                  // commi
    char   BuchArt = ' ';                  // book
    nString m_str;
    m_str = "pxOrder ::  SeparateRetail";

/*----------------------------------------------------------------------------*/
/*  do some checks before to prevent unpredictable relsults                   */
/*----------------------------------------------------------------------------*/
    if ( entryp == NULL )                    // if no entry within SEPORDERARTGRP
       return seporder;
    if ( !entryp->IsRetail())                // this entry has to be a Retail entry
       return seporder;

    if (CommType_->IsNoShipment() || CommType_->IsShipDisposal() || CommType_->IsShipDeliveryNote() )
       return seporder;

    KdAuftragArt = entryp->KdAuftragArt();
    if (CommType_->IsShipNormal() )
    {
       KoArt     = entryp->KoArt();          // just if KommArt = 0
    }
    BuchArt      = entryp->BuchArt();
    KdAuftragArt.Strip();
    KdAuftragArt = ( KdAuftragArt.IsEmpty() ) ? KdAuftragArt_ : KdAuftragArt;
    BuchArt      = ( BuchArt == ' ') ? BuchArt_ : BuchArt;
    KoArt        = ( KoArt == ' ' ) ? KoArt_ : KoArt;

    // Now scan this order for reserve Hospital article
    while ( (item = (pxOrderItem*) ++it) != NULL )
    {
       if ( item->IsCancelled() )
       {
          item->SetNichtNachPharmos();
          continue;
       }
       if ( item->ArtikelNr() == 0 )
       {
          item->SetNichtNachPharmos();
          continue;
       }
       if ( !item->IsKnownProduct() )
       {
          item->SetNichtNachPharmos();
          continue;
       }
       if (item->IsPriceTypeRetail() )
       {
          if ( item->MengeGeliefert() == 0 )
          {
             item->SetNichtNachPharmos();
             continue;
          }
          if ( item->MengeGeliefert() > 0 )
          {
             if ( seporder == NULL )
             {
                seporder = new pxOrder(Session(),*customer);
                if ( !seporder->IsGoodState() )
                {
                   delete seporder;
                   seporder = NULL;
                   break;
                }

                seporder->OrderType(KdAuftragArt,KoArt,BuchArt);
                seporder->KdAuftragNrOrg(KdAuftragNr_);
                seporder->DafueAuftragNr((long) cDCTSequenceNumDDELMax);
                seporder->DatumAuslieferung( DatumAuslieferung_);
                seporder->setPurchaseOrderNo(getPurchaseOrderNo());
                seporder->HerkunftFiliale(HerkunftFiliale());
                seporder->BatchSchreiben(BatchSchreiben());
                seporder->SetPaymentTerm(PaymentTerm());
                seporder->SetPaymentType( PaymentType() );
                seporder->SetTenderNo(TenderNo_);
                seporder->BTMFormularNr(BTMFormularNr_);
                seporder->DatumBTM(DatumBTM_);
                seporder->DatumVersand(DatumVersand_);
                seporder->Customer()->CopyCstPrintList(Customer()->CstPrintList());
                seporder->Bemerkungen(Bemerkungen());
                seporder->SetOrderLabel(OrderLabel());
                seporder->SetKdAuftragNrOrgRO(KdAuftragNrOrgRO());
                //seporder->SetSeparatedOrder();
               /*if ( DatumValuta_ != pxConstants::NullDate )
                {
                   seporder->SetDatumValuta(pxConstants::NullDate);
                }
               */
                seporder->SetRouteForOrderSeparation( TourId(), DatumAuslieferung() );

                // Look for Headtext
                pxTextDoc* headtext = HeadText();
                pxTextDoc* tailtext = TailText();
                pxTextDocIter headiter  = pxTextDocIter(*headtext);
                pxTextDocIter tailiter  = pxTextDocIter(*tailtext);
                if (headtext->Entries() > 0)
                {
                   pxTextDoc *headp = seporder->HeadText();
                   while ( (headtext = (pxTextDoc *) ++headiter) != NULL )
                   {
                      nString headline = ((pxTextLine*) headtext)->Text();
                      headp->NewLine(headline);
                   }
                }
                // Look for Tailtext
                if (tailtext->Entries() > 0)
                {
                   pxTextDoc *tailp = seporder->TailText();
                   while ( (tailtext = (pxTextDoc *) ++tailiter) != NULL )
                   {
                      nString tailline = ((pxTextLine*) tailtext)->Text();
                      tailp->NewLine(tailline);
                   }
                }
             }
             delitem = seporder->CopyOrderItem(item, pxOrderItem::SeparateArticle, SplittType_Unknown);
             BLOG_DEBUG( libcsc::LoggerPool::getLoggerDiscountCalc(), m_str() );
             delitem->UndoRedoItemDiscount(item);
             delitem->UndoRedoOrderPosPromo(item);
             delitem->UndoRedoOrderPosRefund(item);
             delitem->InvoiceValue();             // recalc PreisFaktur
             // now delete item members
             item->MengeBestaetigt( 0L);
             item->MengeGeliefert( 0L);
             item->MengeAbgebucht( 0L);
             item->MengeNatra( 0L);
             item->SetSeparatePosition();
             item->SetNichtNachPharmos();
             nString KdAuftragNr;
             KdAuftragNr = seporder->KdAuftragNr();

             nMessage msg(CMsgStream(), CMSG_ITM_SEPARATE_ARTGROUP_S, (char*)&KdAuftragNr);
             nString posbem = msg.String();
             posbem.Compress('\n');
             item->Bemerkungen(posbem,item->LinkPosNr());
          }
       }
    }
    return seporder;
}
