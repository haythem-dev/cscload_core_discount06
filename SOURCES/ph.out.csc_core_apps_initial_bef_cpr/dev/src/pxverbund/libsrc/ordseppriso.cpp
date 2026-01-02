#include "pxsess.hpp"
#include "pxdevice.hpp"
#include "pxbranch.hpp"
#include "pxcstbas.hpp"
#include "pxcustomerflags.hpp"
#include "pxartbas.hpp"
#include "pxitem.hpp"
#include "pxorder.hpp"
#include "pxtxtdoc.hpp"
#include "pxoeparm.hpp"
#include "pxbase/pxconstants.hpp"
#include "types/origintypeenum.inc"
#include "types/messagecodeenum.inc"

/*----------------------------------------------------------------------------*/
/* SeparatePrivatProductRangePositions;                                       */
/* The current Order(*this) will be scanned for PrivatProductRange items      */
/* This is a special business process in Serbia, so that I decided to activate*/
/* this function only for that country.                                       */
/* The positivlist article are marked within the Position.                    */
/* Take care for a well constructed pxOrder object to prevent unpredictable   */
/* results                                                                    */
/*----------------------------------------------------------------------------*/
Order::States
pxOrder :: SeparatePrisoPositions
(
    int     &prisoq
)
{
    Order::States State = Order::LeaveAsIs;
/*----------------------------------------------------------------------------*/
/*  Do some checks to prevent problems                                        */
/*----------------------------------------------------------------------------*/

    if (!Session()->isGermany())     // only for Germany
    {
       return State;
    }

    if ( BatchSchreiben_ ==  cORTYPE_AUXILIARY )    // Verbundauftrag
    {
        return State;
    }

    if ( IsPseudoLock() )                     // Do not Splitt if PreudoLock
    {
       return State;                          // INC-031782 INC-032063
    }


    if ( prisoq == 0 )
    {
        return State;
    }

    if ( KdAuftragNrOrg_ > 0 )                 // nothing to do
    {
       return State;
    }

    // if this order only contains priso article, do not splitt the order but change the ordertype
    if ( prisoq == AnzPos_ )      // just priso articles
    {
        nString KdAuftragArt;                      // ordertype
        char   KoArt   = KoArt_;                   // commi
        char   BuchArt = BuchArt_;                 // book
        KdAuftragArt = "PR";
        KdAuftragArt.Strip();
        OrderType(KdAuftragArt,KoArt,BuchArt);
        {
            if ( IsGoodState() )
            {
                State = Order::EntryClosed;
                return State;
            }
            else
            {
                ClearError();
            }
        }
    }

    pxOrderItemListIter it(*ItemList_);        // iterator itemlist
    pxOrderItem*                     item;     // item object
    pxOrder* seporder                = NULL;   // separated  order
    pxCustBase* customer             = Customer();
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

/*----------------------------------------------------------------------------*/
/*  Separate Priso article into a new order                                   */
/*----------------------------------------------------------------------------*/
    KdAuftragArt = "PR";
    KdAuftragArt.Strip();
    KoArt        = KoArt_;
    BuchArt      = BuchArt_;

    it.Reset();                             // top of list
    while ( (item = (pxOrderItem*) ++it) != NULL )
    {
        if ( item->IsCancelled() )
            continue;
        if ( item->IsSeparatePosition() ) // already splitted to another order... (ANNA IBT Split)
            continue;
        if ( item->IsPriso() )
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
            if ( item->IsAuxPosted() )
            {
                /* newitem = */ seporder->CopyOrderItem(item, pxOrderItem::AuxDeliveryComplete, SplittType_Priso);
            }
            else if( item->IsNachliefern() )
            {
                /* newitem = */ seporder->CopyOrderItem(item, pxOrderItem::RestDeliveryItem, SplittType_Priso);
            }
            else if ( item->IsDisponieren() )
            {
                /* newitem = */ seporder->CopyOrderItem(item, pxOrderItem::PurchaseItem, SplittType_Priso);

            }
            else if ( item->IsDispoItem() )
            {
                /* newitem = */ seporder->CopyOrderItem(item, pxOrderItem::DispoItem, SplittType_Priso);
            }
            else
            {
                /* newitem = */ seporder->CopyOrderItem(item, pxOrderItem::SeparateArticle, SplittType_Priso);
            }
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

    // Now close seporder
    if ( seporder )
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
        Error() = seporder->Error();            // copy Error
        delete seporder;
        seporder = NULL;
    }

    return State;
}
