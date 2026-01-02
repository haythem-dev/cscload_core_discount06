#include "pxsess.hpp"
#include "pxdevice.hpp"
#include "pxbranch.hpp"
#include "pxcstbas.hpp"
#include "pxartbas.hpp"
#include "pxitem.hpp"
#include "pxorder.hpp"
#include "pxordtyp.hpp"
#include "pxcomtyp.hpp"
#include "pxseporderartgrp.hpp"
#include "pxtxtdoc.hpp"
#include "pxoeparm.hpp"
#include <logger/loggerpool.h>
#include "pxbase/pxconstants.hpp"
#include "types/messagecodeenum.inc"

/*----------------------------------------------------------------------------*/
/* SeparateListFivePositions ; a bulgarian speciality                         */
/* The current Order(*this) will be scanned for items defined in the parameter*/
/* SEPORDERARTGRP. In this case ListFive Positions are placed into a separate */
/* order                                                                      */
/* Take care for a well constructed pxOrder object to prevent unpredictable   */
/* results                                                                    */
/*----------------------------------------------------------------------------*/
Order::States
pxOrder :: SeparateListFivePositions
(
)
{
    Order::States State = Order::LeaveAsIs;
    nString m_str;
    m_str = "pxOrder ::  SeparateListFivePositions";

    if ( IsPseudoLock() )                     // Do not Splitt if PreudoLock
    {
       return State;                          // INC-031782 INC-032063
    }

    pxOrderItemListIter it(*ItemList_);        // iterator itemlist
    pxOrder* seporder                = NULL;   // separated  order
    pxOrderItem*                     item;     // item object
    pxOrderItem*                  delitem;     // item object
    pxSepOrderArtGroup*   entryp     = NULL;
    pxCustBase* customer             = Customer();
    short BranchNo                  = customer->Vertriebszentrum();
    nString KdAuftragArt;                      // ordertype
    char   KoArt   = ' ';                     // commi
    char   BuchArt = ' ';                     // book
    nDate now;
    int    countListFivePos = 0;

    pxSepOrderArtGroupList* SepOList = SepOrderArtGroupList();
    if ( SepOList->Entries() == 0 )            // nothing to do
    {
       return State;
    }
    entryp = SepOList->Find(BranchNo,(short)pxSepOrderArtGroup::SEP_GROUP_LISTFIVE);
    if (entryp == NULL)
    {
       return State;
    }

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

    while ( (item = (pxOrderItem*) ++it) != NULL )
    {
       countListFivePos += item->IsArticleListFiveMember();
    }

    if ( countListFivePos == 0)      // no position found
    {
       return State;
    }

    // Just ListFive positions
    if ( countListFivePos == AnzPos_ )
    {
       OrderType(KdAuftragArt,KoArt,BuchArt);
       SetBulgariaListFive();
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
    it.Reset();
    while ( (item = (pxOrderItem*) ++it) != NULL )
    {
       if ( item->IsCancelled() )
           continue;
       if ( item->ArtikelNr() == 0 )
          continue;
       if ( !item->IsKnownProduct() )
          continue;
       if (item->IsArticleListFiveMember() )
       {
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
                seporder->SetBulgariaListFive();
                seporder->Bemerkungen(Bemerkungen());
                seporder->SetOrderLabel(OrderLabel());
                seporder->SetKdAuftragNrOrgRO(KdAuftragNrOrgRO());

                if ( DatumValuta_ != pxConstants::NullDate )
                {
                   seporder->SetDatumValuta(DatumValuta_);
                   seporder->SetValutaMonManuell(ValutaMonManuell_);
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
             item->Bemerkungen(posbem);
          }
       }
    }

    // Now close seporder
    if ( seporder )
    {
       if ( seporder->DatumAuslieferung() != pxConstants::NullDate && seporder->DatumAuslieferung() != now )
       {
          seporder->CloseState(Order::EntryDeferred); // set order state flags
          seporder->CloseOrder();              // set order state flags
       }
       else
       {
          if (entryp->IsDeferOrder() )
          {
             seporder->SetProblemClearance();
             seporder->SetSeparateArtGroup();
             seporder->CloseState(Order::EntryDeferred);
             seporder->CloseOrder();              // set order state flags
          }
          else
          {
             seporder->Close(Order::EntryClosed, Order::cClose_SeparatedOrder);   // set order state flags
          }
       }
       Error() = seporder->Error();            // copy Error
       delete seporder;
       seporder = NULL;
    }
    return State;
}
