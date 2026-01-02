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
#include "pxbase/pxconstants.hpp"
#include "types/messagecodeenum.inc"

/*----------------------------------------------------------------------------*/
/* SeparateManufacturerPositions ; a french speciality for Ivrylab            */
/* The current Order(*this) will be scanned for items defined in the parameter*/
/* SEPORDERARTGRP. In this case Cap Positions, marked in                      */
/* kdauftragpos.BusinessTypeNo = 4 are splittet into a separate order         */
/* Take care for a well constructed pxOrder object to prevent unpredictable   */
/* results                                                                    */
/*----------------------------------------------------------------------------*/
Order::States
pxOrder :: SeparateManufacturerPositions
(
)
{
    Order::States State = Order::LeaveAsIs;
    if ( IsPseudoLock() ) // Do not Splitt if PreudoLock
    {
       return Order::LeaveAsIs;
    }

    short BranchNo = Customer()->Vertriebszentrum();

    pxSepOrderArtGroupList* SepOList = SepOrderArtGroupList();
    if ( SepOList->Entries() == 0 )            // nothing to do
    {
       return Order::LeaveAsIs;
    }

    pxSepOrderArtGroupListIter iter(*SepOList);
    pxSepOrderArtGroup*        entryp = NULL;
    while (NULL !=  (entryp = ( pxSepOrderArtGroup*) ++iter))
    {
       if (entryp->BranchNo() == BranchNo && (entryp->IsManufacturer() || entryp->IsKonsigPartner()))
       {
          State = SeparateManufacturerPositions(entryp);
       }
    }
    return State;
}

/*----------------------------------------------------------------------------*/

Order::States
pxOrder :: SeparateManufacturerPositions
(
    pxSepOrderArtGroup* sepOrderArtGrp
)
{
    Order::States State = Order::LeaveAsIs;
    pxOrderItemListIter it(*ItemList_);        // iterator itemlist
    pxOrder* seporder                = NULL;   // separated  order
    pxOrderItem*                     item;     // item object
    pxOrderItem*                  delitem;     // item object
    nDate now;

    nString KdAuftragArt;                      // ordertype
    int    countManufacturerPos = 0;



    KdAuftragArt = sepOrderArtGrp->KdAuftragArt();
    char BuchArt = sepOrderArtGrp->BuchArt();
    char KoArt   = ' ';
    KdAuftragArt.Strip();
    KdAuftragArt = ( KdAuftragArt.IsEmpty() ) ? KdAuftragArt_ : KdAuftragArt;
    if (CommType_->IsShipNormal() )
    {
       KoArt        = sepOrderArtGrp->KoArt();
    }
    KoArt        = ( KoArt   == ' ' ) ? KoArt_   : KoArt;
    BuchArt      = ( BuchArt == ' ' ) ? BuchArt_ : BuchArt;

    while (NULL != (item = (pxOrderItem*) ++it))
    {
       if ( item->IsCancelled() )
           continue;
       if ( item->ArtikelNr() == 0 )
          continue;
       if ( item->MengeGeliefert() == 0 )
          continue;
       if ( !item->IsKnownProduct() )
          continue;
       if ( item->ArtBase() == NULL || !item->ArtBase()->IsGoodState())
          continue;
       if ((sepOrderArtGrp->IsManufacturer()  && (item->ArtBase()->HerstellerNr() == sepOrderArtGrp->ManufacturerNo())) ||
           (sepOrderArtGrp->IsKonsigPartner() && (item->ArtBase()->KonsigPartnerNr() == sepOrderArtGrp->ManufacturerNo())))
          countManufacturerPos++;
    }

    if (countManufacturerPos == 0)      // no position found
    {
       return  State;
    }

    // Only positions from manufacturer
    if (countManufacturerPos  == AnzPos_)
    {
       OrderType(KdAuftragArt,KoArt,BuchArt);
       if (sepOrderArtGrp->IsDeferOrder() )
       {
          SetProblemClearance();
          if (sepOrderArtGrp->IsManufacturer())
             SetManufacturerInventory(); // set specific defered flag because manufacturer inventory
          if (sepOrderArtGrp->IsKonsigPartner())
             SetKonsigPartnerInventory(); // set specific defered flag because konsig partner inventory
          State = Order::EntryDeferred;
       }
       else
       {
          State = Order::EntryClosed;
       }
       return State;
    }
    it.Reset();
    while (NULL != (item = (pxOrderItem*)++it))
    {
       if ( item->IsCancelled() )
           continue;
       if ( item->ArtikelNr() == 0 )
          continue;
       if ( item->MengeGeliefert() == 0 )
          continue;
       if ( !item->IsKnownProduct() )
          continue;
       if ( item->ArtBase() == NULL || !item->ArtBase()->IsGoodState() )
          continue;
       if ((sepOrderArtGrp->IsManufacturer()  && (item->ArtBase()->HerstellerNr()    == sepOrderArtGrp->ManufacturerNo())) ||
           (sepOrderArtGrp->IsKonsigPartner() && (item->ArtBase()->KonsigPartnerNr() == sepOrderArtGrp->ManufacturerNo())))
       {
          if ( !item->IsAuxPosted() && !item->IsNachliefern() )
          {
             if ( seporder == NULL )
             {
                seporder = new pxOrder(Session(),*Customer());
                if ( !seporder->IsGoodState() )
                {
                   delete seporder;
                   seporder = NULL;
                   break;
                }
                seporder->OrderType(KdAuftragArt,KoArt,BuchArt);
                seporder->KdAuftragNrOrg(KdAuftragNr());
                seporder->DafueAuftragNr((long) cDCTSequenceNumDDELMax);
                seporder->DatumAuslieferung(DatumAuslieferung());
                seporder->setPurchaseOrderNo(getPurchaseOrderNo());
                seporder->HerkunftFiliale(HerkunftFiliale());
                seporder->BatchSchreiben(BatchSchreiben());
                seporder->SetPaymentTerm(PaymentTerm());
                seporder->SetPaymentType( PaymentType() );
                seporder->SetTenderNo(TenderNo());
                seporder->BTMFormularNr(BTMFormularNr());
                seporder->DatumBTM(DatumBTM());
                seporder->DatumVersand(DatumVersand());
                if (sepOrderArtGrp->IsManufacturer())
                   seporder->SetManufacturerInventory(); // set specific defered flag because manufacturer inventory
                if (sepOrderArtGrp->IsKonsigPartner())
                   seporder->SetKonsigPartnerInventory(); // set specific defered flag because konsig partner inventory
                seporder->Bemerkungen(Bemerkungen());
                seporder->SetOrderLabel(OrderLabel());
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
             delitem->UndoRedoItemDiscount(item);
             delitem->InvoiceValue();             // recalc PreisFaktur
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
       if ( seporder->DatumAuslieferung() != pxConstants::NullDate && seporder->DatumAuslieferung() != now )
       {
          seporder->CloseState(Order::EntryDeferred); // set order state flags
       }
       else
       if (sepOrderArtGrp->IsDeferOrder() )
       {
          seporder->SetProblemClearance();
          seporder->CloseState(Order::EntryDeferred);
       }
       else
       {
          seporder->CloseState(Order::EntryClosed);
       }
       seporder->CloseOrder();
       Error() = seporder->Error();            // copy Error
       delete seporder;
       seporder = NULL;
    }
    return State;
}
