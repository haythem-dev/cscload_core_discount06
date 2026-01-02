#include "pxsess.hpp"
#include "pxdevice.hpp"
#include "pxbranch.hpp"
#include "pxcstbas.hpp"
#include "pxartbas.hpp"
#include "pxitem.hpp"
#include "pxorder.hpp"
#include "pxoeparm.hpp"
#include "pxordtyp.hpp"
#include "pxtxtdoc.hpp"
#include <logger/loggerpool.h>
#include "pxbase/pxconstants.hpp"
#include "types/messagecodeenum.inc"

/*----------------------------------------------------------------------------*/
/*SeparateBigOrder; This is a special bulgarian methode                       */
/* The current Order(*this) will be splitted depend on the parameter          */
/* MaxPosAuftrag within the table paraauftragbearb                            */
/* All position above this parameter are placed in a separte order.           */
/* Take care of a well constructed pxOrder object                             */
/*----------------------------------------------------------------------------*/
Order::States
pxOrder :: SeparateBigOrder
(
)
{
    Order::States State = Order::LeaveAsIs;
    long MaxPosAuftrag = Param()->MaxPosAuftrag();
    long CountRealPos = 1;
    nString m_str;
    m_str = "pxOrder ::  SeparateBigOrder";

    if ( IsDoNotSplittOrder() )
    {
       return State;
    }
    if (!Session()->isBulgaria())
    {
       return State;
    }

    if ( IsPseudoLock() )                     // Do not Splitt if PreudoLock
    {
       return State;                          // INC-031782 INC-032063
    }

    if ( MaxPosAuftrag >=  AnzPos_ -  CountNoTransferPositions() )
    {
       return State;
    }

    pxOrderItemListIter it(*ItemList_);        // iterator itemlist
    pxOrderItem*                     item;     // item object
    pxOrderItem*                  newitem;     // item object
    pxOrder* seporder                = NULL;   // separated  order
    pxCustBase* customer             = Customer();
    // unused variable
    /* short BranchNo                  = */ customer->Vertriebszentrum();
    nDate now;

/*----------------------------------------------------------------------------*/
/*  Now separate order                                                        */
/*----------------------------------------------------------------------------*/
    it.Reset();                             // top of list
    //it += MaxPosAuftrag;
    while ( (item = (pxOrderItem*) ++it) != NULL )
    {
       if ( item->IsNichtNachPharmos() )
           continue;
       if ( CountRealPos  <= MaxPosAuftrag )
       {
           CountRealPos ++;
           continue;
       }
       if ( seporder == NULL )
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
          seporder->SetRouteForOrderSeparation( TourId(), DatumAuslieferung() );
          seporder->SetPaymentTerm(PaymentTerm());

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
       else
       if (seporder->AnzPos() >= MaxPosAuftrag )
       {
          if ( seporder->DatumAuslieferung() != pxConstants::NullDate && seporder->DatumAuslieferung() != now )
          {
             seporder->Close(Order::EntryDeferred); // set order state flags
          }
          else
          {
             seporder->Close(Order::EntryClosed);   // set order state flags
          }
         // seporder->CloseOrder();              // set order state flags
          Error() = seporder->Error();            // copy Error
          delete seporder;
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
          seporder->SetRouteForOrderSeparation( TourId(), DatumAuslieferung() );
          seporder->SetKdAuftragNrOrgRO(KdAuftragNrOrgRO());
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

       newitem = seporder->CopyOrderItem(item, pxOrderItem::SeparateArticle, SplittType_Unknown);
       BLOG_DEBUG( libcsc::LoggerPool::getLoggerDiscountCalc(), m_str() );
       newitem->UndoRedoItemDiscount(item);
       newitem->UndoRedoOrderPosPromo(item);
       newitem->InvoiceValue();             // recalc PreisFaktur
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
       item->Bemerkungen(posbem);
    }

    // Now close seporder
    if ( seporder )
    {
       if ( seporder->DatumAuslieferung() != pxConstants::NullDate && seporder->DatumAuslieferung() != now )
       {
          seporder->Close(Order::EntryDeferred); // set order state flags
       }
       else
       {
          seporder->Close(Order::EntryClosed);   // set order state flags
       }
      // seporder->CloseOrder();              // set order state flags
       Error() = seporder->Error();            // copy Error
       delete seporder;
       seporder = NULL;
    }
    return State;
}
/*----------------------------------------------------------------------------*/
/* CountNoTransferPositions                                                   */
/* Returns count of positions which should not transfer to Pharmos            */
/* Such positions are marked within etposschalter3 least significant bit      */
/* (value 1 )                                                                 */
/*----------------------------------------------------------------------------*/
long
pxOrder :: CountNoTransferPositions
(
)
{
    long  count = 0;
    pxOrderItem*                     item;     // item object
    pxOrderItemListIter it(*ItemList_);        // iterator itemlist
    while ( (item = (pxOrderItem*) ++it) != NULL )
    {
        if ( item->IsNichtNachPharmos() )
        {
           count ++;
        }
    }
    return count;
}
