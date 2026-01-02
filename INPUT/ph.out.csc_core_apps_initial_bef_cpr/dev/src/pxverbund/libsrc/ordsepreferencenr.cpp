#include "pxrecord.h"
#include "pxdevice.hpp"
#include "pxsess.hpp"
#include "pxcstbas.hpp"
#include "pxcustomerflags.hpp"
#include "pxartbas.hpp"
#include "pxitem.hpp"
#include "pxcomtyp.hpp"
#include "pxorder.hpp"
#include "pxholiday.hpp"
#include "pxrefnrcollect.hpp"
#include "pxcstrou.hpp"
#include "pxtxtdoc.hpp"
#include "pxoeparm.hpp"
#include "types/messagecodeenum.inc"

/*----------------------------------------------------------------------------*/
/* SeperateReferenceNr:This methode is just for customer with the following   */
/* settings:  customer->Flags().IsVersandApo() and                            */
/*           customer->Flags().IsBaAuftrag()                                  */
/* VerSandApo is Versandapotheke and BaAuftrag is Beschaffungsauftrag         */
/* If there is an AuxPosition within this order,so all positions with the same*/
/* referencenumber(KdAuftragBestellNr) are splitted into a new order.         */
/* Please take care for a well contructed pxOrder object.                     */
/*----------------------------------------------------------------------------*/
Order::States
pxOrder ::  SeparateReferenceNr
(
         int     &auxposq
)
{
    Order::States State = Order::LeaveAsIs;
    nDate today;
    pxOrderItemListIter it(*ItemList_);        // iterator itemlist
    pxCustBase* customer = Customer();
    pxRefnrCollectList*   RefnrList   = NULL;
    pxRefnrCollect*       RefnrEntry  = NULL;
    pxOrder*                reforder  = NULL;  // new order
    pxOrderList      *ActivRefOrders  = NULL;  // ptr to list of reforder
    pxOrderItem*                item  = NULL;
    bool            cDoNotSplitOrder  = false; // no split marker
    nString       kdauftragbestellnr;

/*----------------------------------------------------------------------------*/
/*  some prechecks before further action has taking place                     */
/*----------------------------------------------------------------------------*/
    if ( auxposq == 0)
    {
       return State;                         // nothing to do
    }

    if ( !customer->Flags().IsVersandApo() )
    {
       return State;                         // nothing to do
    }

    if ( !customer->Flags().IsBaAuftrag() )
    {
       return State;                         // nothing to do
    }

    if ( IsPseudoLock() )                     // Do not Splitt if PreudoLock
    {
       return State;                         // INC-031782 INC-032063
    }

/*----------------------------------------------------------------------------*/
/*  collect auxpositions within reference number collect list                 */
/*  There is only one entry per different referenc number for fuhter workup   */
/*----------------------------------------------------------------------------*/
    while ( (item = (pxOrderItem*) ++it) != NULL )
    {
       if ( item->IsAuxPosted() )
       {
          if ( RefnrList == NULL )
          {
             RefnrList = new pxRefnrCollectList();
          }
          if ( RefnrList->Find(item->KdAuftragBestellNr() ) )
          {
             continue;
          }
          kdauftragbestellnr = item->KdAuftragBestellNr();
          kdauftragbestellnr.Strip();
          if ( !kdauftragbestellnr.IsEmpty() )
          {
             RefnrEntry = new pxRefnrCollect(item->KdAuftragBestellNr());
             RefnrEntry->SetRefNrCount(CountRefnr(item->KdAuftragBestellNr()));
             RefnrList->InsertAscending(RefnrEntry);
          }
       }
    }

/*----------------------------------------------------------------------------*/
/*  leave this methode if no aux positions found, because there is nothing to */
/*  do.                                                                       */
/*----------------------------------------------------------------------------*/
    if ( RefnrList == NULL )
    {
       return State;
    }

/*----------------------------------------------------------------------------*/
/*  Now look within  RefnrList and check count of position with same Refnr.   */
/*  If count of positions is the same as AnPos within this order, so there    */
/*  is no need to split this order.                                           */
/*----------------------------------------------------------------------------*/
    pxRefnrCollectListIter  cursor(*RefnrList);
    while ( (RefnrEntry = (pxRefnrCollect*) ++cursor) != NULL )
    {
       if ( AnzPos() == RefnrEntry->RefNrCount() )
       {
          cDoNotSplitOrder = true;
          SetDoNotAppend();
          break;
       }
    }
    if ( cDoNotSplitOrder )                  // Do not split this order
    {
       delete RefnrList;
       return State;                  // nothing to do
    }

/*----------------------------------------------------------------------------*/
/*  Now split this order depend on reference number within the reference      */
/*  number collect list                                                       */
/*----------------------------------------------------------------------------*/
    cursor.Reset();
    while ( (RefnrEntry = (pxRefnrCollect*) ++cursor) != NULL )
    {
       reforder = this->NewOrderReference( RefnrEntry->KdAuftragBestellNr());
       if ( !reforder->IsGoodState())
       {
          Error() = reforder->Error();
          break;
       }
       if ( ActivRefOrders == NULL )        // then must construct new order list
       {
          ActivRefOrders = new pxOrderList(Session());
       }
       ActivRefOrders->Append(reforder);
    }
/*----------------------------------------------------------------------------*/
/*  Now check result                                                          */
/*----------------------------------------------------------------------------*/
    if ( IsGoodState() )
    {
       auxposq  = 0;
       if ( ActivRefOrders != NULL )
       {
          pxOrderListIter iter(*ActivRefOrders);
          while ( (reforder = (pxOrder*) ++iter) != NULL )
          {
             reforder->Close(Order::EntryClosed, Order::cClose_SeparatedOrder);
             Error() = reforder->Error();
          }
       }
    }

/*----------------------------------------------------------------------------*/
/*  Go back to caller                                                         */
/*----------------------------------------------------------------------------*/
    if ( reforder )
    {
       delete reforder;
    }
    if ( RefnrList )
    {
       delete RefnrList;
    }
    if ( ActivRefOrders )
    {
       delete ActivRefOrders;
    }

    return State;
}

/*----------------------------------------------------------------------------*/
/* NewOrderReference: All position with KdAuftragBestellNr are collected      */
/* in a new order.                                                            */
/* All information for the original postion are rolled back(ArtikelKonto....) */
/*----------------------------------------------------------------------------*/
pxOrder*
pxOrder ::  NewOrderReference
(
    const nString& KdAuftragBestellNr
)
{
    nDate today;

    pxOrder* seporder        = NULL;         // order with same referencenr
    pxOrderItemListIter it(*ItemList());
    pxOrderItem *item;
    pxOrderItem *refitem = NULL;
    pxCustBase* customer = Customer();
    pxCustRouteList    *rl = NULL;
    pxCustRoute   *varoute = NULL;

    rl = RouteList();
    if (rl)
    {
       varoute = rl->FindVaTour(); // TourManagerIssue -> Prüfen was hier passiert
    }
    while ( (item = (pxOrderItem*) ++it) != NULL )
    {
       if ( item->KdAuftragBestellNr() != KdAuftragBestellNr )
          continue;
       if ( item->IsCancelled() )
           continue;
       if ( item->ArtikelNr() == 0 )
          continue;
       if ( !item->IsKnownProduct() )
          continue;
       if (seporder == NULL )
       {
           seporder = new pxOrder(Session(),*customer);
          if ( !seporder->IsGoodState() )
          {
             delete seporder;
             seporder = NULL;
             break;
          }

          seporder->OrderType(KdAuftragArt_,KoArt_,BuchArt_);
          seporder->KdAuftragNrOrg(KdAuftragNr_);
          seporder->DafueAuftragNr((long) cDCTSequenceNumDDELMax);
          seporder->DatumAuslieferung( DatumAuslieferung_);
          seporder->setPurchaseOrderNo(getPurchaseOrderNo());
          seporder->HerkunftFiliale(HerkunftFiliale());
          seporder->BatchSchreiben(BatchSchreiben());
          seporder->SetPaymentTerm(PaymentTerm());
          seporder->SetPaymentType( PaymentType() );

            if (varoute)
            {
                seporder->SetRouteForOrderSeparation( varoute->TourId(), DatumAuslieferung() );
            }
            else
            {
                seporder->SetRouteForOrderSeparation( TourId(), DatumAuslieferung() );
            }

            seporder->SetReferenceNr(KdAuftragBestellNr);
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
       if (item->IsAuxPosted() )
       {
          refitem = seporder->CopyOrderItem(item, pxOrderItem::AuxDelivery, SplittType_Unknown);
          nString KdAuftragNr;
          KdAuftragNr = seporder->KdAuftragNr();
          nMessage msg(CMsgStream(), CMSG_ITM_SEPARATE_ARTGROUP_S, (char*)&KdAuftragNr);
          nString posbem = msg.String();
          posbem.Compress('\n');
          item->Bemerkungen(posbem);
       }
       else
       if (item->IsNachliefern() )
       {
          refitem = seporder->CopyOrderItem(item, pxOrderItem::RestDeliveryItem, SplittType_Unknown);
          nString KdAuftragNr;
          KdAuftragNr = seporder->KdAuftragNr();
          nMessage msg(CMsgStream(), CMSG_ITM_SEPARATE_ARTGROUP_S, (char*)&KdAuftragNr);
          nString posbem = msg.String();
          posbem.Compress('\n');
          item->Bemerkungen(posbem);
       }
       else
       {
          refitem = seporder->CopyOrderItem(item, pxOrderItem::ReferenceItem, SplittType_Unknown);
          nString KdAuftragNr;
          KdAuftragNr = seporder->KdAuftragNr();
          nMessage msg(CMsgStream(), CMSG_ITM_SEPARATE_ARTGROUP_S, (char*)&KdAuftragNr);
          nString posbem = msg.String();
          posbem.Compress('\n');
          item->Bemerkungen(posbem);
       }

       Error() = refitem->Error();
    }
    return seporder;
}
/*----------------------------------------------------------------------------*/
/* CountRefnr: This methode counts the position within the same refefencenr   */
/* given by KdAuftragBestellNr. retval is returnd                             */
/*----------------------------------------------------------------------------*/
long
pxOrder ::  CountRefnr
(
    const nString& KdAuftragBestellNr
)
{
    pxOrderItemListIter it(*ItemList());
    pxOrderItem *item;
    long retval = 0;

    while ( (item = (pxOrderItem*) ++it) != NULL )
    {
       if ( item->KdAuftragBestellNr() == KdAuftragBestellNr )
       {
          ++retval;
       }
    }
    return retval;
}

