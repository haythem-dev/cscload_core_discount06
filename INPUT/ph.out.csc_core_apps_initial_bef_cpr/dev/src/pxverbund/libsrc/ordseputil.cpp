#include "pxrecord.h"
#include "pxdevice.hpp"
#include "pxsess.hpp"
#include "pxcstbas.hpp"
#include "pxcustomerflags.hpp"
#include "pxartbas.hpp"
#include "pxitem.hpp"
#include "pxcomtyp.hpp"
#include "pxorder.hpp"
#include "pxoeparm.hpp"
#include "pxcustdeldelivery.hpp"
#include "pxseporderartgrp.hpp"
#include "pxcstseporderartgrp.hpp"
#include "pxholiday.hpp"
#include "pxeventreason.hpp"
#include "pxtxtdoc.hpp"
#include "pxbase/pxconstants.hpp"
#include "types/messagecodeenum.inc"

/*----------------------------------------------------------------------------*/
/* SeparateSpecials                                                           */
/* The current Order(*this) will be scanned for article to be placed in a     */
/* separate order by different methodes, depend on the definition within      */
/* the following table:  SEPORDERARTGRP                                       */
/* Take care for a well constructed pxOrder object to prevent unpredictable   */
/* results                                                                    */
/*----------------------------------------------------------------------------*/
Order::States
pxOrder ::  SeparateSpecials
(
         int     &coolerq,
         int     &opiateq,
         int     &reshospital,
         int     &zytosq,
         int     &auxposq,
         int     &psychoq
)
{
    nDate today;
    int  saveopiateq = opiateq;             // save opiateq
    int  savecoolerq = coolerq;             // save coolerq
    int  zerocoolerq = 0;
    int  zeroopiateq = 0;
    Order::States State = Order::LeaveAsIs;
    pxOrder* seporder                 = NULL;         // separates order
    pxSepOrderArtGroup*      SepGroup = NULL;
    pxSepOrderArtGroupList*  SepOList = NULL;
    short BranchNo     = Customer()->Vertriebszentrum();

/*----------------------------------------------------------------------------*/
/*  some prechecks before further action has taking place                     */
/*----------------------------------------------------------------------------*/
    if ( opiateq == 0 && reshospital == 0 &&  coolerq == 0 && zytosq == 0  && auxposq == 0  && psychoq == 0)
    {
       return State;                  // nothing to do
    }

    if ( IsPseudoLock() )                     // Do not Splitt if PreudoLock
    {
       return State;                   // INC-031782 INC-032063
    }


    if ( CommType_->IsNoShipment() )
    {
       return State;
    }

    if ( IsDoNotSplittOrder() )
    {
       return State;
    }
    if ( IsSeparatedOrder() )      // if oder already separated
    {
       return State;               // do not try to split it again(anchor)
    }
/*----------------------------------------------------------------------------*/
/*  Do not seperate  for Versandapo with BA order                             */
/*----------------------------------------------------------------------------*/
    if ( Customer()->Flags().IsVersandApo() && Customer()->Flags().IsBaAuftrag() )
    {
       return State;
    }

/*----------------------------------------------------------------------------*/
/*  Build Parameterlist for splittoptions.                                    */
/*----------------------------------------------------------------------------*/
    SepOList = SepOrderArtGroupList();
    if ( SepOList->Entries() == 0 )
    {
       return State;                  // nothing to do
    }

/*----------------------------------------------------------------------------*/
/*  Separate Narcotics                                                        */
/*----------------------------------------------------------------------------*/
    if ( opiateq > 0 && !Param()->IsUseTourManagerWithTransportExclusion() ) // do not separate narcotics for tourmanager with transport exclusion
    {
       SepGroup = SepOList->Find(BranchNo, (short)pxSepOrderArtGroup::SEP_GROUP_NARCOTIC);
       if (SepGroup != NULL)
       {
          // Just narcoticpositions within this order, so do not separate
          if ( opiateq == AnzPos_ )
          {
             return SeparateSpecialsSwitchOrder(SepGroup);
          }

          seporder = SeparateNarcotics(&opiateq, SepGroup);
          if (seporder)
          {
/*-------------------------------------------------------------------------------*/
/*              seporder has been changed to its homebase, so seporder has been  */
/*              changed to a delayeddelivery order                               */
/*-------------------------------------------------------------------------------*/
             if (SepGroup->IsDeferOrder() || seporder->IsProblemClearance())
             {
                seporder->SetProblemClearance();
                seporder->SetSeparateArtGroup();
                seporder->CloseState(Order::EntryDeferred); // set order state flags
                seporder->CloseOrder();
             }
             else
             {
                seporder->SeparateDelayedDelivery(0L, zerocoolerq, saveopiateq, zytosq);
                seporder->SetSeparatedOrder();   // marke order
                seporder->Close(Order::EntryClosed, Order::cClose_SeparatedOrder);   // set order state flags
             }
             if ( seporder->IsGoodState() )
             {
                AnzBTM_ = 0; // 2013-08-12 if narcotics are splitted into new order, reset narcotics quantity in original order head
                delete seporder;
                seporder = NULL;
             }
          }
       }
    }
/*----------------------------------------------------------------------------*/
/*  Separate reserve hospital                                                 */
/*----------------------------------------------------------------------------*/
    if ( reshospital > 0 )
    {
       if ( reshospital == AnzPos_ )
          return State;                // nothing to do
       SepGroup = SepOList->Find(BranchNo, (short)pxSepOrderArtGroup::SEP_GROUP_RES_HOSPITAL);
       if (SepGroup != NULL)
       {
           seporder = SeparateResHospital(&reshospital, SepGroup);
          if (seporder)
          {
             if (SepGroup->IsDeferOrder() )
             {
                seporder->SetProblemClearance();
                seporder->SetSeparateArtGroup();
                seporder->CloseState(Order::EntryDeferred);      // set order state flags
                seporder->CloseOrder();
             }
             else
             {
                seporder->Close(Order::EntryClosed, Order::cClose_SeparatedOrder);   // set order state flags
             }
             if ( seporder->IsGoodState() )
             {
                delete seporder;
             }
          }
       }
    }
/*----------------------------------------------------------------------------*/
/*  Separate KK, K04, K08 Article                                             */
/*----------------------------------------------------------------------------*/
    if ( coolerq > 0 && !Param()->IsUseTourManagerWithTransportExclusion() ) // do not separate narcotics for tourmanager with transport exclusion
    {
       if ( coolerq == AnzPos_ )
          return State;                // nothing to do
       seporder = SeparateCooler(&coolerq, SepOList);
       if (seporder)
       {
          if (SepGroup->IsDeferOrder() || seporder->IsProblemClearance())
          {
             seporder->SetSeparateArtGroup();
             seporder->CloseState(Order::EntryDeferred);      // set order state flags
             seporder->CloseOrder();
          }
          else
          {
             seporder->SeparateDelayedDelivery(0L, savecoolerq, zeroopiateq, zytosq);
             seporder->Close(Order::EntryClosed, Order::cClose_SeparatedOrder);  // set order state flags
          }
          if ( seporder->IsGoodState() )
          {
              delete seporder;
          }
       }
    }
/*----------------------------------------------------------------------------*/
/*  Separate Zytostatics                                                      */
/*----------------------------------------------------------------------------*/
    if ( zytosq > 0 )
    {
       SepGroup = SepOList->Find(BranchNo, (short)pxSepOrderArtGroup::SEP_GROUP_ZYTOSTATIC);
       if (SepGroup != NULL)
       {
          // Just Zytostatics within this order, so do not separate
          if (zytosq == AnzPos_)
          {
             return SeparateSpecialsSwitchOrder(SepGroup);
          }
          seporder = SeparateZytostatic(&zytosq, SepGroup);
          if (seporder)
          {
             if (SepGroup->IsDeferOrder() )
             {
                seporder->SetProblemClearance();
                seporder->SetSeparateArtGroup();
                seporder->CloseState(Order::EntryDeferred);      // set order state flags
                seporder->CloseOrder();
             }
             else
             {
                seporder->Close(Order::EntryClosed, Order::cClose_SeparatedOrder);    // set order state flags
             }
             if ( seporder->IsGoodState() )
             {
                delete seporder;
             }
          }
       }
    }
/*----------------------------------------------------------------------------*/
/*  Separate Psychotrop                                                       */
/*----------------------------------------------------------------------------*/
    if ( psychoq > 0 )
    {
       SepGroup = SepOList->Find(BranchNo, (short)pxSepOrderArtGroup::SEP_GROUP_PSYCHO);
       if (SepGroup != NULL)
       {
          // Just Psychotrop within this order, so do not separate
          if (psychoq == AnzPos_)
          {
             return SeparateSpecialsSwitchOrder(SepGroup);
          }
          seporder = SeparatePsycho(&psychoq, SepGroup);
          if (seporder)
          {
             if (SepGroup->IsDeferOrder() )
             {
                seporder->SetProblemClearance();
                seporder->SetSeparateArtGroup();
                seporder->CloseState(Order::EntryDeferred);      // set order state flags
                seporder->CloseOrder();
             }
             else
             {
                seporder->Close(Order::EntryClosed, Order::cClose_SeparatedOrder);    // set order state flags
             }
             if ( seporder->IsGoodState() )
             {
                delete seporder;
             }
          }
       }
    }
/*----------------------------------------------------------------------------*/
/*  Separate Auxpositions                                                     */
/*----------------------------------------------------------------------------*/
    if ( auxposq > 0 )
    {
       if (Param()->IsSIbtCstOrg() && (Session()->isFrance() || Session()->isFrancePrewhole()) )
       {
          RangeCalculation();                 // do just RangeCalculation
          return State;
       }

       SepGroup = SepOList->Find(BranchNo, (short)pxSepOrderArtGroup::SEP_GROUP_AUXDELIVERY);
       if (SepGroup == NULL)
          return State;                // nothing to do

       if (Session()->isFrance())
       {
          RangeCalculation();
       }
       // Just narcoticpositions within this order, so do not separate
       if ( auxposq == AnzPos_ )
       {
          return SeparateSpecialsSwitchOrder(SepGroup);
       }

       seporder = SeparateAuxPositions(&auxposq, SepGroup);
       if (seporder)
       {
          ClearAuxPositions();
          if (SepGroup->IsDeferOrder() )
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
    return State;
}
/*----------------------------------------------------------------------------*/
/* SeparateNarcotics;                                                         */
/* The current Order(*this) will be scanned for narcotic article, to be       */
/* placed in an extra order.                                                  */
/* Prerequisites for this process is a corresponding BTM entry within the     */
/* within the following table;   SEPORDERARTGRP                               */
/* Take care for a well constructed pxOrder object to prevent unpredictable   */
/* results                                                                    */
/*----------------------------------------------------------------------------*/
pxOrder*
pxOrder ::  SeparateNarcotics
(
         int          *opiateq,
   pxSepOrderArtGroup*  sepgroup
)
{
    nDate today;
    pxOrder* seporder        = NULL;         // delayed deliver order
    pxOrderItemListIter it(*ItemList());
    pxOrderItem *item;
    pxOrderItem *delitem;
    pxCustBase* customer = Customer();
    nString KdAuftragArt;                   // ordertype
    char   KoArt   = ' ';                  // commi
    char   BuchArt = ' ';                  // book

    if ( sepgroup == NULL )                  // if no entry within SEPORDERARTGRP
       return seporder;

    if ( !sepgroup->IsNarCotic() )           // this entry has to be a narcotic one
       return seporder;

    if (CommType_->IsNoShipment() || CommType_->IsShipDisposal() || CommType_->IsShipDeliveryNote() )
       return seporder;

    KdAuftragArt = sepgroup->KdAuftragArt();
    BuchArt      = sepgroup->BuchArt();
    if (CommType_->IsShipNormal() )          // just if KommiArt = 0
    {
       KoArt     = sepgroup->KoArt();
    }
    KdAuftragArt.Strip();
    KdAuftragArt = ( KdAuftragArt.IsEmpty() ) ? KdAuftragArt_ : KdAuftragArt;
    BuchArt      = ( BuchArt == ' ') ? BuchArt_ : BuchArt;
    KoArt        = ( KoArt == ' ' ) ? KoArt_ : KoArt;

    // Now scan this order for Narcotic Article
    while ( (item = (pxOrderItem*) ++it) != NULL )
    {
       if ( item->IsCancelled() )
           continue;
       if ( item->ArtikelNr() == 0 )
          continue;
       if ( !item->IsKnownProduct() )
          continue;
       if (item->ArtBase()->ArtClass().IsOpiat() )
       {
          if (item->MengeGeliefert() > 0 && !item->IsAuxPosted() && !item->IsNachliefern() )
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
                seporder->SetBTMFormularNr((DatumBTM().GetYYYYMMDD()), BTMFormularNr());
                seporder->Bemerkungen(Bemerkungen());
                seporder->SetOrderLabel(OrderLabel());
                seporder->SetTenderNo(TenderNo());
                if ( IsVerbundhausNewSuivra() )
                {
                   seporder->SetVerbundhausNewSuivra();
                }
                if ( IsStammhausNewSuivra() )
                {
                   seporder->SetStammhausNewSuivra();
                }
                seporder->SetRouteForOrderSeparation( TourId(), DatumAuslieferung() );

                if ( DatumValuta_ != pxConstants::NullDate )
                {
                   seporder->SetDatumValuta(DatumValuta_);
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
             }
             delitem = seporder->CopyOrderItem(item, pxOrderItem::SeparateArticle, SplittType_Unknown);
             *opiateq = 0;
             delitem->UndoRedoItemDiscount(item);
             delitem->WriteOrderPosSplittInfo(item, SplittType_Narcotics);
             delitem->UndoRedoOrderPosPromo(item);
             delitem->UndoRedoOrderPosRefund(item);
             delitem->InvoiceValue();
             // now delete item members
             item->MengeBestaetigt( 0L);
             item->MengeGeliefert( 0L);
             item->MengeAbgebucht( 0L);
             item->MengeNatra( 0L);
             item->SetSeparatePosition();
             if (Session()->isBulgaria())
             {
                item->SetNichtNachPharmos();
             }
             nString KdAuftragNr;
             KdAuftragNr = seporder->KdAuftragNr();

             nMessage msg(CMsgStream(), CMSG_ITM_SEPARATE_ARTGROUP_S, (char*)&KdAuftragNr);
             nString posbem = msg.String();
             posbem.Compress('\n');
             item->Bemerkungen(posbem);
          }
       }
    }
    return seporder;
}
/*----------------------------------------------------------------------------*/
/* SeparateResHospital:                                                       */
/* The current Order(*this) will be scanned for reserve Hospital article      */
/* to be placed in an extra order                                             */
/* Prerequisites for this process is a corresponding reserve Hospital entry   */
/* within the following table;   SEPORDERARTGRP                               */
/* Take care for a well constructed pxOrder object to prevent unpredictable   */
/* results                                                                    */
/*----------------------------------------------------------------------------*/
pxOrder*
pxOrder ::  SeparateResHospital
(
   int* /* reshospital */,
   pxSepOrderArtGroup*  sepgroup
)
{
    nDate today;
    pxOrder* seporder        = NULL;         // delayed deliver order
    pxOrderItemListIter it(*ItemList());
    pxOrderItem *item;
    pxOrderItem *delitem;
    pxCustBase* customer = Customer();
    nString KdAuftragArt;                   // ordertype
    char   KoArt   = ' ';                  // commi
    char   BuchArt = ' ';                  // book

    if ( sepgroup == NULL )                  // if no entry within SEPORDERARTGRP
       return seporder;
    if ( !sepgroup->IsResHospital() )        // this entry has to be a reserve Hospital one
       return seporder;
    if (CommType_->IsNoShipment() || CommType_->IsShipDisposal() || CommType_->IsShipDeliveryNote() )
       return seporder;

    KdAuftragArt = sepgroup->KdAuftragArt();
    if (CommType_->IsShipNormal() )
    {
       KoArt     = sepgroup->KoArt();        // just if KommArt = 0
    }
    BuchArt      = sepgroup->BuchArt();
    KdAuftragArt.Strip();
    KdAuftragArt = ( KdAuftragArt.IsEmpty() ) ? KdAuftragArt_ : KdAuftragArt;
    BuchArt      = ( BuchArt == ' ') ? BuchArt_ : BuchArt;
    KoArt        = ( KoArt == ' ' ) ? KoArt_ : KoArt;

    // Now scan this order for reserve Hospital article
    while ( (item = (pxOrderItem*) ++it) != NULL )
    {
       if ( item->IsCancelled() )
           continue;
       if ( item->ArtikelNr() == 0 )
          continue;
       if ( !item->IsKnownProduct() )
          continue;
       if (item->ArtBase()->IsReserveHospital() )
       {
          if (item->MengeGeliefert() > 0 && !item->IsAuxPosted() && !item->IsNachliefern() )
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
                seporder->Bemerkungen(Bemerkungen());
                seporder->SetOrderLabel(OrderLabel());
                seporder->SetTenderNo(TenderNo());
                if ( IsVerbundhausNewSuivra() )
                {
                   seporder->SetVerbundhausNewSuivra();
                }
                if ( IsStammhausNewSuivra() )
                {
                   seporder->SetStammhausNewSuivra();
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
             delitem->WriteOrderPosSplittInfo(item, SplittType_ResHospital);
             delitem->UndoRedoOrderPosPromo(item);
             delitem->UndoRedoOrderPosRefund(item);
             delitem->InvoiceValue();
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
    return seporder;
}
/*----------------------------------------------------------------------------*/
/* SeparateCooler:                                                            */
/* The current Order(*this) will be scanned for cooler article KK, K08, K20   */
/* to be placed in an extra order                                             */
/* Prerequisites for this process is a corresponding KK, K08 or K20 entry     */
/* within the following table;   SEPORDERARTGRP                               */
/* Take care for a well constructed pxOrder object to prevent unpredictable   */
/* results                                                                    */
/*----------------------------------------------------------------------------*/
pxOrder*
pxOrder ::  SeparateCooler
(
   int                    *coolerq,
   pxSepOrderArtGroupList*  sepgrouplist
)
{
    // unused variable
    // int  retval = 0;
    nDate today;
    pxOrder* seporder        = NULL;         // delayed deliver order
    pxOrderItemListIter it(*ItemList());
    pxOrderItem *item;
    pxOrderItem *delitem;
    pxCustBase* customer = Customer();
    // unused variable
    /* pxOrderEntryParam &param   = */ Param();
    nString KdAuftragArt;                   // ordertype
    char   KoArt   = ' ';                  // commi
    char   BuchArt = ' ' ;                 // book
    short BranchNo = customer->Vertriebszentrum();
    pxSepOrderArtGroup*      SepGroupKK  = NULL;
    pxSepOrderArtGroup*      SepGroupK08 = NULL;
    pxSepOrderArtGroup*      SepGroupK20 = NULL;


    if ( sepgrouplist == NULL )             // if no SEPORDERARTGRP list
       return seporder;

    SepGroupKK  = sepgrouplist->Find(BranchNo,(short)pxSepOrderArtGroup::SEP_GROUP_COLDCHAIN);
    SepGroupK08 = sepgrouplist->Find(BranchNo,(short)pxSepOrderArtGroup::SEP_GROUP_COOL08);
    SepGroupK20 = sepgrouplist->Find(BranchNo,(short)pxSepOrderArtGroup::SEP_GROUP_COOL20);
    // something to do ??
    if ( SepGroupKK == NULL && SepGroupK08 == NULL && SepGroupK20 == NULL )
    {
       return seporder;
    }

    if (CommType_->IsNoShipment() || CommType_->IsShipDisposal() || CommType_->IsShipDeliveryNote() )
       return seporder;

    // Set Ordertype, Shipcode and Stocktransaction code: we just take one of them
    if ( SepGroupKK )
    {
       KdAuftragArt = SepGroupKK->KdAuftragArt();
       if (CommType_->IsShipNormal() )      // just if KommiArt = 0
       {
          KoArt     = SepGroupKK->KoArt();
       }
       BuchArt      = SepGroupKK->BuchArt();
       KdAuftragArt.Strip();
       KdAuftragArt = ( KdAuftragArt.IsEmpty() ) ? KdAuftragArt_ : KdAuftragArt;
       BuchArt      = ( BuchArt == ' ') ? BuchArt_ : BuchArt;
       KoArt        = ( KoArt == ' ' ) ? KoArt_ : KoArt;
    }
    else if ( SepGroupK08)
    {
       KdAuftragArt = SepGroupK08->KdAuftragArt();
       if (CommType_->IsShipNormal() )      // just if KommiArt = 0
       {
          KoArt     = SepGroupK08->KoArt();
       }
       BuchArt      = SepGroupK08->BuchArt();
       KdAuftragArt.Strip();
       KdAuftragArt = ( KdAuftragArt.IsEmpty() ) ? KdAuftragArt_ : KdAuftragArt;
       BuchArt      = ( BuchArt == ' ') ? BuchArt_ : BuchArt;
       KoArt        = ( KoArt == ' ' ) ? KoArt_ : KoArt;
    }
    else if ( SepGroupK20)
    {
       KdAuftragArt = SepGroupK20->KdAuftragArt();
       if (CommType_->IsShipNormal() )
       {
          KoArt     = SepGroupK20->KoArt();
       }
       BuchArt      = SepGroupK20->BuchArt();
       KdAuftragArt.Strip();
       KdAuftragArt = ( KdAuftragArt.IsEmpty() ) ? KdAuftragArt_ : KdAuftragArt;
       BuchArt      = ( BuchArt == ' ') ? BuchArt_ : BuchArt;
       KoArt        = ( KoArt == ' ' ) ? KoArt_ : KoArt;
    }

    // Now scan this order for KK, K08 and K20 article
    while ( (item = (pxOrderItem*) ++it) != NULL )
    {
       if ( item->IsCancelled() )
           continue;
       if ( item->ArtikelNr() == 0 )
          continue;
       if ( !item->IsKnownProduct() )
          continue;
       if ( (item->ArtBase()->ArtFlags().IsKuehlKette() && SepGroupKK  != NULL  ) ||
            (item->ArtBase()->ArtFlags().IsGekuehlt08() && SepGroupK08 != NULL  ) ||
            (item->ArtBase()->ArtFlags().IsGekuehlt20() && SepGroupK20 != NULL  ) )
       {
          if (item->MengeGeliefert() > 0 && !item->IsAuxPosted() && !item->IsNachliefern() )
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
                seporder->Bemerkungen(Bemerkungen());
                seporder->SetOrderLabel(OrderLabel());
                seporder->SetTenderNo(TenderNo());
                if ( IsVerbundhausNewSuivra() )
                {
                   seporder->SetVerbundhausNewSuivra();
                }
                if ( IsStammhausNewSuivra() )
                {
                   seporder->SetStammhausNewSuivra();
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
             delitem->WriteOrderPosSplittInfo(item, SplittType_Cooler);
             delitem->UndoRedoOrderPosPromo(item);
             delitem->UndoRedoOrderPosRefund(item);
             delitem->InvoiceValue();
             // now delete item members
             item->MengeBestaetigt( 0L);
             item->MengeGeliefert( 0L);
             item->MengeAbgebucht( 0L);
             item->MengeNatra( 0L);
             item->SetSeparatePosition();
             if (Session()->isBulgaria())
             {
                item->SetNichtNachPharmos();
             }

             nString KdAuftragNr;
             KdAuftragNr = seporder->KdAuftragNr();

             nMessage msg(CMsgStream(), CMSG_ITM_SEPARATE_ARTGROUP_S, (char*)&KdAuftragNr);
             nString posbem = msg.String();
             posbem.Compress('\n');
             item->Bemerkungen(posbem);
             if (item->ArtBase()->ArtFlags().IsKuehlKette() || item->ArtBase()->ArtFlags().IsGekuehlt08() ||
                 item->ArtBase()->ArtFlags().IsGekuehlt20() )
             {
                *coolerq = 0;
             }
          }
       }
    }
    if ( seporder )
    {
        if ( (SepGroupKK  != NULL && SepGroupKK ->IsDeferOrder()) ||
             (SepGroupK08 != NULL && SepGroupK08->IsDeferOrder()) ||
             (SepGroupK20 != NULL && SepGroupK20->IsDeferOrder()) )
        {
           seporder->SetProblemClearance();
        }
    }
    return seporder;
}
/*----------------------------------------------------------------------------*/
/* SeparateZytostatic:                                                        */
/* The current Order(*this) will be scanned for zytostatic article            */
/* to be placed in an extra order                                             */
/* Prerequisites for this process is a corresponding zytodtatic entry         */
/* within the following table;   SEPORDERARTGRP                               */
/* Take care for a well constructed pxOrder object to prevent unpredictable   */
/* results                                                                    */
/*----------------------------------------------------------------------------*/
pxOrder*
pxOrder ::  SeparateZytostatic
(
         int          *zytosq,
   pxSepOrderArtGroup*  sepgroup
)
{
    nDate today;
    pxOrder* seporder        = NULL;         // delayed deliver order
    pxOrderItemListIter it(*ItemList());
    pxOrderItem *item;
    pxOrderItem *delitem;
    pxCustBase* customer = Customer();
    nString KdAuftragArt;                   // ordertype
    char   KoArt   =  ' ';                 // commi
    char   BuchArt =  ' ';                 // book

    if ( sepgroup == NULL )                 // if no entry within SEPORDERARTGRP
       return seporder;
    if ( !sepgroup->IsZytoStatics() )       // this entry has to be a reserve Hospital one
       return seporder;

    if (CommType_->IsNoShipment() || CommType_->IsShipDisposal() || CommType_->IsShipDeliveryNote() )
       return seporder;

    KdAuftragArt = sepgroup->KdAuftragArt();
    if (CommType_->IsShipNormal() )
    {
       KoArt     = sepgroup->KoArt();
    }
    BuchArt      = sepgroup->BuchArt();
    KdAuftragArt.Strip();
    KdAuftragArt = ( KdAuftragArt.IsEmpty() ) ? KdAuftragArt_ : KdAuftragArt;
    BuchArt      = ( BuchArt == ' ') ? BuchArt_ : BuchArt;
    KoArt        = ( KoArt == ' ' ) ? KoArt_ : KoArt;

    // Now scan this order for zytostatic article
    while ( (item = (pxOrderItem*) ++it) != NULL )
    {
       if ( item->IsCancelled() )
           continue;
       if ( item->ArtikelNr() == 0 )
          continue;
       if ( !item->IsKnownProduct() )
          continue;
       if (item->ArtBase()->ArtFlags().IsZytoStatikaArtikel() )
       {
          if (item->MengeGeliefert() > 0 && !item->IsAuxPosted() && !item->IsNachliefern() )
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
                seporder->Bemerkungen(Bemerkungen());
                seporder->SetOrderLabel(OrderLabel());
                seporder->SetTenderNo(TenderNo());
                if ( IsVerbundhausNewSuivra() )
                {
                   seporder->SetVerbundhausNewSuivra();
                }
                if ( IsStammhausNewSuivra() )
                {
                   seporder->SetStammhausNewSuivra();
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
             delitem->WriteOrderPosSplittInfo(item, SplittType_Zytostatic);
             delitem->UndoRedoOrderPosPromo(item);
             delitem->UndoRedoOrderPosRefund(item);
             delitem->InvoiceValue();
             *zytosq = 0;
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
    return seporder;
}
/*----------------------------------------------------------------------------*/
/* SeparateAuxpositions:                                                      */
/* The current Order(*this) will be scanned for auxdelivery article           */
/* to be placed in an extra order                                             */
/* Prerequisites for this process is a corresponding auxposdelivery entry     */
/* within the following table;   SEPORDERARTGRP                               */
/* Take care for a well constructed pxOrder object to prevent unpredictable   */
/* results                                                                    */
/*----------------------------------------------------------------------------*/
pxOrder*
pxOrder ::  SeparateAuxPositions
(
         int          *auxposq,
   pxSepOrderArtGroup*  sepgroup
)
{
    nDate today;
    pxOrder* seporder        = NULL;         // delayed deliver order
    pxOrderItemListIter it(*ItemList());
    pxOrderItem *item;
    pxOrderItem *delitem;
    pxCustBase* customer = Customer();
    nString KdAuftragArt;                   // ordertype
    char   KoArt   =  ' ';                 // commi
    char   BuchArt =  ' ';                 // book

    if ( sepgroup == NULL )                 // if no entry within SEPORDERARTGRP
       return seporder;
    if ( !sepgroup->IsAuxDelivery() )       // this entry has to be a auxdelivery one
       return seporder;

    if (CommType_->IsNoShipment() || CommType_->IsShipDisposal() || CommType_->IsShipDeliveryNote() )
       return seporder;

    KdAuftragArt = sepgroup->KdAuftragArt();
    if (CommType_->IsShipNormal() )
    {
       KoArt     = sepgroup->KoArt();
    }
    BuchArt      = sepgroup->BuchArt();
    KdAuftragArt.Strip();
    KdAuftragArt = ( KdAuftragArt.IsEmpty() ) ? KdAuftragArt_ : KdAuftragArt;
    BuchArt      = ( BuchArt == ' ') ? BuchArt_ : BuchArt;
    KoArt        = ( KoArt == ' ' ) ? KoArt_ : KoArt;

    // Now scan this order for zytostatic article
    while ( (item = (pxOrderItem*) ++it) != NULL )
    {
       if ( item->IsCancelled() )
           continue;
       if ( item->ArtikelNr() == 0 )
          continue;
       if ( !item->IsKnownProduct() )
          continue;
       if (item->IsAuxPosted() )
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
             seporder->DatumAuslieferung( DatumAuslieferung_ );
             seporder->setPurchaseOrderNo(getPurchaseOrderNo());
             seporder->HerkunftFiliale(HerkunftFiliale());
             seporder->BatchSchreiben(BatchSchreiben());
             seporder->SetPaymentTerm(PaymentTerm());
             seporder->SetPaymentType( PaymentType() );
             seporder->SetRouteForOrderSeparation( TourId(), DatumAuslieferung() );

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
          }
          delitem = seporder->CopyOrderItem(item, pxOrderItem::AuxDelivery, SplittType_Unknown);
          delitem->UndoRedoItemDiscount(item);
          delitem->WriteOrderPosSplittInfo(item, SplittType_Auxpositions);
          *auxposq = 0;


          // now delete item members
          item->SetSeparatePosition();
          item->SetVerbundAuftragsPosition();
          nString KdAuftragNr;
          KdAuftragNr = seporder->KdAuftragNr();

          nMessage msg(CMsgStream(), CMSG_ITM_SEPARATE_AUXDELIVERY_S,(char*)&KdAuftragNr);
          nString posbem = msg.String();
          posbem.Compress('\n');
          item->Bemerkungen(posbem);
       }
    }
    return seporder;
}
/*----------------------------------------------------------------------------*/
/* SeparatePsycho:                                                        */
/* The current Order(*this) will be scanned for psychotrop article            */
/* to be placed in an extra order                                             */
/* Prerequisites for this process is a corresponding psychotrop entry         */
/* within the following table;   SEPORDERARTGRP                               */
/* Take care for a well constructed pxOrder object to prevent unpredictable   */
/* results                                                                    */
/*----------------------------------------------------------------------------*/
pxOrder*
pxOrder ::  SeparatePsycho
(
         int          *psychoq,
   pxSepOrderArtGroup*  sepgroup
)
{
    nDate today;
    pxOrder* seporder        = NULL;         // delayed deliver order
    pxOrderItemListIter it(*ItemList());
    pxOrderItem *item;
    pxOrderItem *delitem;
    pxCustBase* customer = Customer();
    nString KdAuftragArt;                   // ordertype
    char   KoArt   =  ' ';                 // commi
    char   BuchArt =  ' ';                 // book

    if ( sepgroup == NULL )                 // if no entry within SEPORDERARTGRP
       return seporder;
    if ( !sepgroup->IsPsycho() )       // this entry has to be a reserve Hospital one
       return seporder;

    if (CommType_->IsNoShipment() || CommType_->IsShipDisposal() || CommType_->IsShipDeliveryNote() )
       return seporder;

    KdAuftragArt = sepgroup->KdAuftragArt();
    if (CommType_->IsShipNormal() )
    {
       KoArt     = sepgroup->KoArt();
    }
    BuchArt      = sepgroup->BuchArt();
    KdAuftragArt.Strip();
    KdAuftragArt = ( KdAuftragArt.IsEmpty() ) ? KdAuftragArt_ : KdAuftragArt;
    BuchArt      = ( BuchArt == ' ') ? BuchArt_ : BuchArt;
    KoArt        = ( KoArt == ' ' ) ? KoArt_ : KoArt;

    // Now scan this order for zytostatic article
    while ( (item = (pxOrderItem*) ++it) != NULL )
    {
       if ( item->IsCancelled() )
           continue;
       if ( item->ArtikelNr() == 0 )
          continue;
       if ( !item->IsKnownProduct() )
          continue;
       if (item->ArtBase()->IsKzPsychoStoffe() )
       {
          if (item->MengeGeliefert() > 0 && !item->IsAuxPosted() && !item->IsNachliefern() )
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
                seporder->Bemerkungen(Bemerkungen());
                seporder->SetOrderLabel(OrderLabel());
                seporder->SetTenderNo(TenderNo());
                if ( IsVerbundhausNewSuivra() )
                {
                   seporder->SetVerbundhausNewSuivra();
                }
                if ( IsStammhausNewSuivra() )
                {
                   seporder->SetStammhausNewSuivra();
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
             delitem->WriteOrderPosSplittInfo(item, SplittType_Psychotrop);
             delitem->UndoRedoOrderPosPromo(item);
             delitem->UndoRedoOrderPosRefund(item);
             delitem->InvoiceValue();
             *psychoq = 0;
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
    return seporder;
}

/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
Order::States pxOrder::SeparateSpecialsSwitchOrder(pxSepOrderArtGroup* sepgroup)
{
    Order::States State = Order::LeaveAsIs;
    nString KdAuftragArt;                   // ordertype
    char   KoArt = ' ';                  // commi
    char   BuchArt = ' ';                  // book

    KdAuftragArt = sepgroup->KdAuftragArt();
    BuchArt = sepgroup->BuchArt();
    KdAuftragArt.Strip();
    KdAuftragArt = (KdAuftragArt.IsEmpty()) ? KdAuftragArt_ : KdAuftragArt;
    if (CommType_->IsShipNormal())
    {
        KoArt = sepgroup->KoArt();
    }
    KoArt = (KoArt == ' ') ? KoArt_ : KoArt;
    BuchArt = (BuchArt == ' ') ? BuchArt_ : BuchArt;
    OrderType(KdAuftragArt, KoArt, BuchArt);
    // maybe combination or ordertype is not available
    if (!IsGoodState())
    {
        SetProblemClearance();  // manual clearance required
        SetSeparateArtGroup();
        State = Order::EntryDeferred;
        SetEventCode(pxEventReason::ErrorOnMethodeOrderType);
        ClearError();
        return State;
    }

    if (sepgroup->IsDeferOrder())
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
