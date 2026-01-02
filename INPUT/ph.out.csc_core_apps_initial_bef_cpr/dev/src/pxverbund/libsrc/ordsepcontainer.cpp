#include "pxsess.hpp"
#include "pxdevice.hpp"
#include "pxbranch.hpp"
#include "pxcstbas.hpp"
#include "pxcustomerflags.hpp"
#include "pxartbas.hpp"
#include "pxitem.hpp"
#include "pxorder.hpp"
#include "pxordtyp.hpp"
#include "pxcomtyp.hpp"
#include "pxseporderartgrp.hpp"
#include "pxcustinf.hpp"
#include "pxeventreason.hpp"
#include "pxtxtdoc.hpp"
#include "pxoeparm.hpp"
#include "pxbase/pxconstants.hpp"
#include "types/messagecodeenum.inc"

/*----------------------------------------------------------------------------*/
/* SeparateContainer;                                                         */
/* The current Order(*this) will be scanned for ContainerPack items and       */
/* Container Article  to be placed in an extra order.                         */
/* Prerequisites for this process is a corresponding Container or Big Volume  */
/* entry within the following table;   SEPORDERARTGRP                         */
/* Take care for a well constructed pxOrder object to prevent unpredictable   */
/* results                                                                    */
/*----------------------------------------------------------------------------*/
Order::States
pxOrder :: SeparateContainer
(
)
{
    Order::States State = Order::LeaveAsIs;
    pxCustOrderInfo* custinfo = NULL;
    pxCustOrderInfo* sepordercustinfo = NULL;

    if ( IsPseudoLock() )                     // Do not Splitt if PreudoLock
    {
       return State;                          // INC-031782 INC-032063
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


    pxOrderItemListIter it(*ItemList_);        // iterator itemlist
    pxOrderItem*                     item;     // item object
    pxOrderItem*                  newitem;     // item object
    pxOrder* seporder                = NULL;   // separated  order
    pxSepOrderArtGroup*  Containerp  = NULL;
    pxSepOrderArtGroup*  BigVolumep  = NULL;
    pxCustBase* customer             = Customer();
    short BranchNo                  = customer->Vertriebszentrum();
    nString KdAuftragArt;                      // ordertype
    char   KoArt   = ' ';                     // commi
    char   BuchArt = ' ';                     // book
    int    BigVolumeArtq            = 0;      // Container Article count
    int    ContainerPackq           = 0;      // Container Pack = Raised Quantity
    nDate now;

/*----------------------------------------------------------------------------*/
/* Do not seperate for Versandapo with BA order                               */
/*----------------------------------------------------------------------------*/
    if ( customer->Flags().IsVersandApo() && customer->Flags().IsBaAuftrag() )
    {
       return State;
    }

    pxSepOrderArtGroupList* SepOList = SepOrderArtGroupList();
    // Look for Container entry (item->IsContainerPack())
    Containerp  = SepOList->Find(BranchNo,(short)pxSepOrderArtGroup::SEP_GROUP_CONTAINER);

    // Look for Big Volume entry (ArtBase()->ArtFlags().IsContainerArtikel())
    BigVolumep  = SepOList->Find(BranchNo,(short)pxSepOrderArtGroup::SEP_GROUP_BIG_VOLUME);

    if ( Containerp == NULL && BigVolumep == NULL )
       return State;

/*----------------------------------------------------------------------------*/
/* Calculate count of Containerarticle and Containerpack items                */
/*----------------------------------------------------------------------------*/
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
       BigVolumeArtq    += item->ArtBase()->ArtFlags().IsContainerArtikel();
       ContainerPackq   += ( item->ArtBase()->ContainerGroesse() > 0 &&
                             item->MengeGeliefert_ >= item->ArtBase()->ContainerGroesse() );

    }
    if ( BigVolumeArtq == 0 && ContainerPackq == 0 )
       return State;

/*----------------------------------------------------------------------------*/
/*  Separate Containerarticle                                                 */
/*----------------------------------------------------------------------------*/
    if ( BigVolumeArtq > 0 && BigVolumep )
    {
       KdAuftragArt = BigVolumep->KdAuftragArt();
       if (CommType_->IsShipNormal() )
       {
          KoArt     = BigVolumep->KoArt();
       }
       BuchArt      = BigVolumep->BuchArt();
       KdAuftragArt.Strip();
       KdAuftragArt = ( KdAuftragArt.IsEmpty() ) ? KdAuftragArt_ : KdAuftragArt;
       BuchArt      = ( BuchArt == ' ') ? BuchArt_ : BuchArt;
       KoArt        = ( KoArt == ' ' ) ? KoArt_ : KoArt;
       if ( BigVolumeArtq == AnzPos_ )      // just container
       {
          OrderType(KdAuftragArt,KoArt,BuchArt);
          // maybe combination or ordertype is not available
          if (!IsGoodState() )
          {
             SetProblemClearance();  // manual clearance required
             SetSeparateArtGroup();
             State = Order::EntryDeferred;
             SetEventCode(pxEventReason::ErrorOnMethodeOrderType);
             ClearError();
             return State;
          }
          if (BigVolumep->IsDeferOrder() )
          {
             SetProblemClearance();
             SetSeparateArtGroup();
             State = Order::EntryDeferred;
          }
          else
          {
             RangeCalculation();
             State = Order::EntryClosed;
          }
          return State;
       }

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
          if ( item->ArtBase()->ArtFlags().IsContainerArtikel() && BigVolumep != NULL )
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
                   RangeCalculation();
                   seporder->OrderType(KdAuftragArt,KoArt,BuchArt);
                   // maybe combination or ordertype is not available
                   if (!seporder->IsGoodState() )
                   {
                      seporder->SetProblemClearance();  // manual clearance required
                      seporder->SetSeparateArtGroup();
                      seporder->SetEventCode(pxEventReason::ErrorOnMethodeOrderType);
                      seporder->ClearError();
                   }

                   seporder->KdAuftragNrOrg(KdAuftragNr_);
                   seporder->DafueAuftragNr((long) cDCTSequenceNumDDELMax);
                   seporder->DatumAuslieferung( DatumAuslieferung_);
                   seporder->setPurchaseOrderNo(getPurchaseOrderNo());
                   seporder->HerkunftFiliale(HerkunftFiliale());
                   seporder->BatchSchreiben(BatchSchreiben());
                   seporder->SetPaymentTerm(PaymentTerm());
                   seporder->SetPaymentType( PaymentType() );
                   seporder->SetSubOrderType(SubOrderType());
                   seporder->SetRouteForOrderSeparation( TourId(), DatumAuslieferung() );
                   seporder->Bemerkungen(Bemerkungen());
                   seporder->SetOrderLabel(OrderLabel());
                   if ( IsVerbundhausNewSuivra() )
                   {
                      seporder->SetVerbundhausNewSuivra();
                   }
                   if ( IsStammhausNewSuivra() )
                   {
                      seporder->SetStammhausNewSuivra();
                   }
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
                   // look for pxCustOrderInfo(KdAuftragInfo table
                   custinfo = new pxCustOrderInfo(Session(), KdAuftragNr_);
                   if ( custinfo->IsGoodState() )
                   {
                       sepordercustinfo = new pxCustOrderInfo(*custinfo);
                       sepordercustinfo->SetOrderNr(seporder->KdAuftragNr());
                       sepordercustinfo->Put();
                       delete sepordercustinfo;
                   }
                   delete custinfo;
                }
                newitem = seporder->CopyOrderItem(item, pxOrderItem::SeparateArticle, SplittType_Unknown);
                newitem->UndoRedoItemDiscount(item);
                //newitem->IBTDeliveryItem(item);
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
    }
    // Now close seporder
    if ( seporder )
    {
       if ( BigVolumep->IsDeferOrder() || seporder->IsProblemClearance())
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
/*----------------------------------------------------------------------------*/
/*  Separate Containerpack article                                            */
/*----------------------------------------------------------------------------*/
    if ( ContainerPackq > 0 && Containerp )
    {
       KdAuftragArt = Containerp->KdAuftragArt();
       if (CommType_->IsShipNormal() )
       {
          KoArt     = Containerp->KoArt();
       }
       BuchArt      = Containerp->BuchArt();
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
          if ( item->ArtBase()->ContainerGroesse() == 0)
             continue;
          if ( item->ArtBase()->ArtFlags().IsContainerArtikel() )
             continue;
          if ( item->IsContainerPack() )
          {
             // Vielleicht hat sich die Containergroesse geaendert( Ticket SR-19027468 )
             if (item->ArtBase()->ContainerGroesse() > 0 && item->MengeGeliefert_ < item->ArtBase()->ContainerGroesse())
             {
                 item->ClearContainerPack();
                 item->ClearBeiPackMulti();
                 continue;
             }

             if (((item->MengeGeliefert()%item->ArtBase()->ContainerGroesse()) == 0 ) && AnzPos_ == 1 )
             {
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
                RangeCalculation();
                seporder->OrderType(KdAuftragArt,KoArt,BuchArt);
                // maybe combination or ordertype is not available
                if (!seporder->IsGoodState() )
                {
                   seporder->SetProblemClearance();  // manual clearance required
                   seporder->SetSeparateArtGroup();
                   seporder->SetEventCode(pxEventReason::ErrorOnMethodeOrderType);
                   seporder->ClearError();
                }
                seporder->KdAuftragNrOrg(KdAuftragNr_);
                seporder->DafueAuftragNr((long) cDCTSequenceNumDDELMax);
                seporder->DatumAuslieferung( DatumAuslieferung_);
                seporder->setPurchaseOrderNo(getPurchaseOrderNo());
                seporder->HerkunftFiliale(HerkunftFiliale());
                seporder->BatchSchreiben(BatchSchreiben());
                seporder->SetPaymentTerm(PaymentTerm());
                seporder->SetPaymentType( PaymentType() );
                seporder->SetSubOrderType(SubOrderType());
                seporder->SetRouteForOrderSeparation( TourId(), DatumAuslieferung() );
                seporder->Bemerkungen(Bemerkungen());
                seporder->SetOrderLabel(OrderLabel());
                if ( IsVerbundhausNewSuivra() )
                {
                   seporder->SetVerbundhausNewSuivra();
                }
                if ( IsStammhausNewSuivra() )
                {
                   seporder->SetStammhausNewSuivra();
                }
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
                // look for pxCustOrderInfo(KdAuftragInfo table
                custinfo = new pxCustOrderInfo(Session(), KdAuftragNr_);
                if ( custinfo->IsGoodState() )
                {
                    sepordercustinfo = new pxCustOrderInfo(*custinfo);
                    sepordercustinfo->SetOrderNr(seporder->KdAuftragNr());
                    sepordercustinfo->Put();
                    delete sepordercustinfo;
                }
                delete custinfo;
             }
             newitem = seporder->CopyOrderItem(item, pxOrderItem::SeparateContainer, SplittType_Unknown);
             newitem->UndoRedoItemDiscount(item);
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

    if ( seporder )
    {
       if (  Containerp->IsDeferOrder() || seporder->IsProblemClearance())
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
