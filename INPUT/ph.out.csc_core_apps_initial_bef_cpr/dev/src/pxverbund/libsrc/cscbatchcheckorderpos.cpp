#include "pxitem.hpp"
#include "pxorder.hpp"
#include "pxsess.hpp"
#include "pxartbas.hpp"
#include "pxoclpar.hpp"
#include "pxdelpos.hpp"
#include "pxdellog.hpp"
#include "pxcstot.hpp"
#include "pxstockbooking.hpp"
#include <logger/loggerpool.h>
#include "pxrecord.h"
#include "pxbase/pxconstants.hpp"
#include "types/origintypeenum.inc"
#include "types/messagecodeenum.inc"

/*----------------------------------------------------------------------------*/
/*  CscBatchCheckOrderPos                                                     */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: CscBatchCheckOrderPos
(
    const long    QtyNatra,
    const nString& Remarks
)
{
    const pxCustOrderType&  ot = Order().OrderType();
    bool ArtNotOnStore = false;
    char buffer [128];
    char temp[30];

    // Do some pre checks
    if( Order().BatchSchreiben() == 0 )
    {
       return ErrorState();
    }

    if ( !(IsQStateNotOnHand()) )
    {
       if ( ArtBase() )
       {
          if (!ArtBase_->IsGoodState())
          {
             MengeBestellt(0);
             sprintf(buffer,"Artikel %ld hat kein ArtikelLokalEntry, HerkunftFiliale %d",ArtikelNr(), Order().HerkunftFiliale());
             BLOG_ERROR(libcsc::LoggerPool::getLoggerSession(), buffer);
          }
       }
       // BAP-PTEXT into pxorderitem::Bemerkungen
       nString itemtxt = Remarks;
       Bemerkungen(itemtxt);

       // Construct NachLieferPos
       //if ( Order().BatchSchreiben() == cORTYPE_AUXILIARY    ||
        //    Order().BatchSchreiben() == cORTYPE_GLOBUS_ORDER ||
         //   Order().BatchSchreiben() == cORTYPE_EDIFAC_ORDER ||
          //  Order().BatchSchreiben() == cORTYPE_PARENT_COMPANY)
       //{
         // CscBatchCreateDeliveryPos(IDFNrOrg, OrderNoOrg,PosNrOrg);
       //}
       return ErrorState();
    }

    // partial rest delivery allowed ?
    if (MengeGeliefert() > 0 && ot.IsNoPartQty() )
    {
       nDBBeginTransaction(cDBTransRecord);
       Session()->getStockBooking()->CancelReservationForOpenOrder(*this, this->MengeGeliefert());

       ArtBase(cDBGET_FORUPDATE);
       if ( ArtBase()->IsGoodState() )
       {
           if (ArtBase_->IsAktivAndNotOnStore() )
           {
              ArtNotOnStore = true;
           }
       }
       CalcConditions();
       MengeGeliefert(0L);
       MengeAbgebucht(0L);
       MengeBestaetigt(0L);
       MengeNatra(0L);
       MengeNatraGrossH(0L);
       MengeNatraHerst(0L);
       ClearToCommission();
       CancelAuxPosting();
       //if (Order().BatchSchreiben() == cORTYPE_GLOBUS_ORDER ||
        //   Order().BatchSchreiben() == cORTYPE_EDIFAC_ORDER ||
         //  Order().BatchSchreiben() == cORTYPE_PARENT_COMPANY)
       //{
          // Construct NachLieferPos/Type_Batch
        //  CscBatchCreateDeliveryPos(IDFNrOrg, OrderNoOrg,PosNrOrg);
       //}

       // BAP-PTEXT into pxorderitem::Bemerkungen
       nString itemtxt = Remarks;
       itemtxt.Strip();
       if ( ot.IsRestDel() )
       {
          CscBatchUpdateDeliveryPos(QtyNatra, Remarks ); // Restdelivery
       }
       //put the text in Benerkungen
       if ( (ot.IsTransfer() || ot.IsScheduleQuantity()) && !ArtNotOnStore )
       {
          itemtxt.Strip();
          nMessage msg(CMsgStream(), CMSG_ITM_RESTDELIVERY_COMES);
          nString posbem = msg.String();
          posbem.Compress('\n');
          int templen = sprintf(temp,"%ld+%ld %s", MengeBestellt(),QtyNatra, (char*)posbem);
          temp[templen] = '\0';
          if ( itemtxt.IsEmpty() )
          {
             itemtxt+=temp;
          }
          else if (!this->Order().OrderType().IsTransfer())
          {
             itemtxt = itemtxt+" "+temp;
          }
       }
       Bemerkungen(itemtxt);
       nDBCommit();
    }
    else
    {
       //if (Order().BatchSchreiben() == cORTYPE_GLOBUS_ORDER ||
        //   Order().BatchSchreiben() == cORTYPE_EDIFAC_ORDER ||
         //  Order().BatchSchreiben() == cORTYPE_PARENT_COMPANY)
       //{
          // Construct NachLieferPos/Type_Batch
        //  CscBatchCreateDeliveryPos(IDFNrOrg, OrderNoOrg,PosNrOrg);
       //}
       CalcConditions();
       nString itemtxt = Remarks;
       itemtxt.Strip();
       if ( ot.IsRestDel() )
       {
          CscBatchUpdateDeliveryPos(QtyNatra, Remarks ); // Restdelivery
       }
       if (ArtBase_->IsAktivAndNotOnStore() )
       {
          ArtNotOnStore = true;
       }
       //put the text in Benerkungen
       if ( (ot.IsTransfer() || ot.IsScheduleQuantity() ) && !ArtNotOnStore )

       {
          itemtxt.Strip();
          nMessage msg(CMsgStream(), CMSG_ITM_RESTDELIVERY_COMES);
          nString posbem = msg.String();
          posbem.Compress('\n');
          long Qty = 0;
          long pNatra = 0;
          Qty = ( MengeBestellt() + MengeNatra() ) - MengeGeliefert();
          pNatra = (MengeNatra_ == 0) ? QtyNatra : 0;
          int templen = sprintf(temp,"%ld+%ld %s", Qty,pNatra, (char*)posbem);
          temp[templen] = '\0';
          if ( itemtxt.IsEmpty() )
          {
             itemtxt+=temp;
          }
          else if (!this->Order().OrderType().IsTransfer())
          {
             itemtxt = itemtxt+" "+temp;
          }
       }
       Bemerkungen(itemtxt);
       nDBCommit();
    }

    return ErrorState();
}

/*----------------------------------------------------------------------------*/
/*  Create new DeliveryPos Entry typ = pxVerbund::subsequentDelivery::pxDeliveryPos::pxDPT_BATCH_ITEM        */
/*----------------------------------------------------------------------------*/
//int
//pxOrderItem::CscBatchCreateDeliveryPos
//(
//    const long  IDFNrOrg,
//    const long  OrderNoOrg,
//    const long  PosNrOrg
//)
//{
//    int retval = 0;
    // Construct NachLieferPos
    //pxVerbund::subsequentDelivery::pxDeliveryPos delivery_(*this, pxVerbund::subsequentDelivery::pxDPT_BATCH_ITEM);
    //tNACHLIEFERPOS position_;

    // We must change some values.
    //Assign(position_, delivery_);

    //position_.IDFNr = IDFNrOrg;
    //position_.FilialNr1 = Order().HerkunftFiliale();
    //position_.UrsprungAuftragNr = OrderNoOrg;
    //position_.UrsprungPosNr = PosNrOrg;

    //Assign(delivery_, position_);

    // Finally write it.
    //delivery_.Put();

    //return retval;
//}
/*----------------------------------------------------------------------------*/
/*  Create new DeliveryPos Entry typ = pxVerbund::subsequentDelivery::pxDeliveryPos::pxDPT_RESTDELIVERY_ITEM */
/*----------------------------------------------------------------------------*/
int
pxOrderItem::CscBatchUpdateDeliveryPos
(
    const long       QtyNatra,
    const nString&    Remarks
)
{
    int retval = 0;
    pxVerbund::subsequentDelivery::pxDeliveryPos* dp_ = NULL;

    nDate today;

    // Construct NachLieferPos
    if ( NULL != (dp_ = AuxDelList()->Find(KdAuftragNr(), PosNr(), pxVerbund::subsequentDelivery::pxDPT_RESTDELIVERY_ITEM)) )
    {

       nDBBeginTransaction(cDBTransRecord);
       if ( dp_->Get(cDBGET_FORUPDATE) == 0 ) // read and lock deliverypos
       {
          tNACHLIEFERPOS position_;
          memset(&position_, 0, sizeof(tNACHLIEFERPOS));
          // We must change some values.
          nString itemtxt = Remarks;
          itemtxt.Strip();
          Assign(position_, *dp_);
          position_.Menge          = (MengeBestellt()+ MengeNatra()) - MengeGeliefert();
          if ( MengeNatra_ == 0 )
          {
             position_.MengeNatra     = QtyNatra;
          }
          position_.Bemerkungen[0] = ' ';
          itemtxt.GetData(position_.Bemerkungen);
          if ( PreisEKApoNetto() > pxConstants::mZero )
          {
             position_.PreisEKApoNetto = PreisEKApoNetto();
          }
          Assign(*dp_, position_);
          // Finally write it.
          dp_->Put();
          nDBCommit(cDBTransRecord);
       }
    }

    return retval;
}
