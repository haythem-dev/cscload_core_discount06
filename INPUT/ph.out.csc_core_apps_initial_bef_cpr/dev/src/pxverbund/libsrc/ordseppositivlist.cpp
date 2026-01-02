#include "pxsess.hpp"
#include "pxdevice.hpp"
#include "pxbranch.hpp"
#include "pxcstbas.hpp"
#include "pxcustomerflags.hpp"
#include "pxartbas.hpp"
#include "pxitem.hpp"
#include "pxorder.hpp"
#include "pxcomtyp.hpp"
#include "pxseporderartgrp.hpp"
#include "pxtxtdoc.hpp"
#include "pxoeparm.hpp"
#include "pxbase/pxconstants.hpp"
#include "types/messagecodeenum.inc"

/*----------------------------------------------------------------------------*/
/* SeparatePositivListPositions;                                              */
/* The current Order(*this) will be scanned for Positivlist items             */
/* This is a special business process in Serbia, so that I decided to activate*/
/* this function only for that country.                                       */
/* The positivlist article are marked within the table ARTIKELZENTRAL column  */
/* PositivListe = "1"                                                         */
/* Take care for a well constructed pxOrder object to prevent unpredictable   */
/* results                                                                    */
/*----------------------------------------------------------------------------*/
Order::States
pxOrder :: SeparatePositivListPositions
(
    int     &positivlistq
)
{
    Order::States State = Order::LeaveAsIs;
/*----------------------------------------------------------------------------*/
/*  Do some checks to prevent problems                                        */
/*----------------------------------------------------------------------------*/

    if (!Session()->isSerbia())     // only for Serbia
    {
       return State;
    }

    // if this order only contains positivlist article, do not splitt the order
    if ( positivlistq == AnzPos_ )      // just positivlist article
    {
       return State;
    }

    if ( KdAuftragNrOrg_ > 0 )                 // nothing to do
    {
       return State;
    }
    if ( CommType_->IsNoShipment() )
    {
       return State;
    }

    if ( IsDoNotSplittOrder() )
    {
       return State;
    }
    if ( positivlistq == 0 )
    {
       return State;
    }

    pxOrderItemListIter it(*ItemList_);        // iterator itemlist
    pxOrderItem*                     item;     // item object
    pxOrderItem*                  newitem;     // item object
    pxOrder* seporder                = NULL;   // separated  order
    pxSepOrderArtGroup*    SepGroup  = NULL;   // entry pointer
    pxCustBase* customer             = Customer();
    short BranchNo                  = customer->Vertriebszentrum();
    nString KdAuftragArt;                      // ordertype
    char   KoArt   = ' ';                     // commi
    char   BuchArt = ' ';                     // book
    nDate now;

/*----------------------------------------------------------------------------*/
/* Do not seperate for Versandapo with BA order                               */
/*----------------------------------------------------------------------------*/
    if ( customer->Flags().IsVersandApo() && customer->Flags().IsBaAuftrag() )
    {
       return State;
    }

    pxSepOrderArtGroupList* SepOList = SepOrderArtGroupList();

    // Look for SEP_GROUP_POSITIVLIST entry within SepOList
    SepGroup = SepOList->Find(BranchNo,(short)pxSepOrderArtGroup::SEP_GROUP_POSITIVLIST);

    if ( SepGroup == NULL )
       return State;

/*----------------------------------------------------------------------------*/
/*  Separate PositivList article into a new order                             */
/*----------------------------------------------------------------------------*/
    KdAuftragArt = SepGroup->KdAuftragArt();
    if (CommType_->IsShipNormal() )
    {
       KoArt     = SepGroup->KoArt();
    }
    BuchArt      = SepGroup->BuchArt();
    KdAuftragArt.Strip();
    KdAuftragArt = ( KdAuftragArt.IsEmpty() ) ? KdAuftragArt_ : KdAuftragArt;
    BuchArt      = ( BuchArt == ' ') ? BuchArt_ : BuchArt;
    KoArt        = ( KoArt == ' ' ) ? KoArt_ : KoArt;

    it.Reset();                             // top of list
    while ( (item = (pxOrderItem*) ++it) != NULL )
    {
       if ( item->IsCancelled() )
          continue;
       if ( item->ArtikelNr() == 0 )
          continue;
       if ( !item->IsKnownProduct() )
          continue;
       if ( item->MengeGeliefert() == 0 )
          continue;
       if ( item->ArtBase()->IsPositivListe() )
       {
          if ( !item->IsAuxPosted() && !item->IsNachliefern() )
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
             newitem = seporder->CopyOrderItem(item, pxOrderItem::SeparateArticle, SplittType_Unknown);
             newitem->UndoRedoItemDiscount(item);
             newitem->UndoRedoOrderPosPromo(item);
             // now delete item members
             item->MengeBestaetigt( 0L);
             item->MengeGeliefert( 0L);
             item->MengeAbgebucht( 0L);
             item->MengeNatra( 0L);
             item->SetSeparatePosition();
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
       if ( SepGroup->IsDeferOrder() )
       {
          seporder->SetProblemClearance();
          seporder->SetSeparateArtGroup();
          seporder->CloseState(Order::EntryDeferred); // set order state flags
          seporder->CloseOrder();
       }
       else
       {
          if ( seporder->DatumAuslieferung() != pxConstants::NullDate && seporder->DatumAuslieferung() != now )
          {
             seporder->CloseState(Order::EntryDeferred); // set order state flags
          }
          else
          {
             seporder->CloseState(Order::EntryClosed);   // set order state flags
          }
          seporder->CloseOrder();              // set order state flags
       }
       Error() = seporder->Error();            // copy Error
       delete seporder;
       seporder = NULL;
    }
    return State;
}
