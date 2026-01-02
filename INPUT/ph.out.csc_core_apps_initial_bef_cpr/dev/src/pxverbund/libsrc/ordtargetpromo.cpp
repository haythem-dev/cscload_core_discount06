#include "pxrecord.h"
#include "pxsess.hpp"
#include "pxdevice.hpp"
#include "pxcstbas.hpp"
#include "pxcustomergrpflags.hpp"
#include "pxitem.hpp"
#include "pxorder.hpp"
#include "pxoeparm.hpp"
#include "pxordtyp.hpp"
#include "pxcstot.hpp"
#include "pxrangecollect.hpp"
#include "pxrangemember.hpp"
#include "pxdiscountordtyp.hpp"
#include "pxrangecontrol.hpp"
#include "pxpromotions.hpp"
#include "pxpromotioncollect.hpp"
#include "pxkdauftragposrefund.hpp"
#include "pxbase/pxconstants.hpp"
#include "types/messagecodeenum.inc"

/*----------------------------------------------------------------------------*/
/* Do the main Rangecalculation on the pxOrderItemList                        */
/* First we build up the Rangecollectionlist, containing discountgroupmember  */
/* information for each position within this orderobject.                     */
/* Second: Build up the Rangecontrolelist, containing information for each    */
/* discountgroupnumber within the Rangecollectionlist.                        */
/* After that calculation takes place for each entry within the               */
/* Rangecontrolelist.                                                         */
/*----------------------------------------------------------------------------*/
int
pxOrder :: TargetPromotionCalculation
(
)
{
    pxCustBase*       customer    = Customer();       // customer
    pxRangeControlList*    rangcl = NULL;
    pxRangeControl*      rentriep = NULL;             // RangeControlEntry Pointer
    pxDiscount*         diskentry = NULL;             // Discount entry

    // OrderType is not discountable
    if ( !OrderType().IsDiscountable() )
          return ErrorState();

    // OrderType is not discountable
    if ( OrderType().IsSNoPromotions() )
          return ErrorState();

    // Customer Group is not discountable(Group 8,9,13)
    if ( !customer->CustomerGroupFlagsList()->IsKscDiscountEnabled()  )
          return ErrorState();

    if (OrderType().IsNoDD() )
       return ErrorState();

    if ( IsPseudoLock() )
       return ErrorState();

/*----------------------------------------------------------------------------*/
/*  Assign Refundvalue for already manually booked Target Promotions          */
/*  (Shift+P functionality in Order Entry                                     */
/*----------------------------------------------------------------------------*/
    AssignOrderEntryTargetRefundValue();

    RangeCollectList();                     // init RangeCollectList
    TargetPromotionCollectList();           // collection of discountgroupmembers
    if ( !RangeCollectList()->Entries() )
       return ErrorState();

    rangcl = TargetPromotionControleList();  // collection of discountgroup numbers
/*----------------------------------------------------------------------------*/
/*  First check validity of Rangecontrol Entries                              */
/*  every non quilty entry will be removed from the list                      */
/*----------------------------------------------------------------------------*/
    pxRangeControlListIter    it(*rangcl);
    if ( rangcl->Entries() )
    {
       while ( (rentriep = (pxRangeControl*) ++it) != NULL )
       {
          if ( !rentriep->IsValidTargetPromotion(Session(),this))
          {
              RangeCollectList()->DeleteInvalidEntries (rentriep->DiscountGrpNo(), rentriep->PreisTyp());
              delete it.Remove();
          }
       }
    }
    if ( rangcl->Entries() == 0)
    {
       delete rangcl;
       rangcl = NULL;
       return ErrorState();
    }
    it.Reset();

/*----------------------------------------------------------------------------*/
/*  Second: collect promotion information to each entry of TargetPromotion    */
/*  where articleno > 0                                                       */
/*----------------------------------------------------------------------------*/
    while ( (rentriep = (pxRangeControl*) ++it) != NULL )
    {
       if ( rentriep->TargetPromoList() == NULL)
          continue;

       CollectItemTargetPromotions(rentriep);            // per Position
    }

/*----------------------------------------------------------------------------*/
/* Assign best Promotion to each position                                     */
/*----------------------------------------------------------------------------*/
    AssignDiscountToPosition(rangcl);

/*----------------------------------------------------------------------------*/
/*  Assign TargetPromotion depend on condition of the control record          */
/*----------------------------------------------------------------------------*/
    it.Reset();
    while ( (rentriep = (pxRangeControl*) ++it) != NULL )
    {
       if ( rentriep->TargetPromoList() == NULL)
          continue;
       pxDiscountListIter cursor(*(rentriep->TargetPromoList()));
       while ( (diskentry = (pxDiscount*) ++cursor) != NULL )
       {
          rentriep->SetGrpDiscountTyp(diskentry);
          switch (rentriep->GrpDiscountTyp())
          {
             case  pxRangeControl :: Cond_DiscountArticleQty_PctAllMembers   :
             {
                TargetDiscountArticle(rentriep,diskentry );
                if ( !(IsGoodState()) )
                {
                   ExternalError(CMsgStream(), CMSG_ORD_RANGEARTICLE_ERROR, KdAuftragNr_, diskentry->DiscountArticle());
                }
                AssignDiscountPctToAllMembers ( rentriep, diskentry );          // assign DiscountPct for TargetPromotion Members
                break;
             }
             case  pxRangeControl :: Cond_DiscountArticleQty:
             {
                TargetDiscountArticle(rentriep,diskentry );
                if ( !(IsGoodState()) )
                {
                   ExternalError(CMsgStream(), CMSG_ORD_RANGEARTICLE_ERROR, KdAuftragNr_, diskentry->DiscountArticle());
                }
                break;
             }
             case  pxRangeControl ::  Cond_QtyAllMembers :
             {
                AssignDiscountQtyToAllMembers( rentriep, diskentry );
                break;
             }
             case  pxRangeControl ::  Cond_PctAllMembers :
             {
                AssignDiscountPctToAllMembers ( rentriep, diskentry );
                break;
             }
             case  pxRangeControl ::  Cond_QtyPctAllMembers :
             {
                AssignDiscountPctToAllMembers ( rentriep, diskentry );          // assign DiscountPct for TargetPromotion Members
                AssignDiscountQtyToAllMembers( rentriep, diskentry );
                break;
             }
             //case  pxRangeControl ::  Cond_ArticleNo :
             //{
             //   AssignDiscountToPosition ( rentriep, diskentry );               // assign DiscountPct for TargetPromotion Member
             //   break;
             //}
             default:
             {
                break;
             }
          }
       }
    }

/*----------------------------------------------------------------------------*/
/* Assign best Promotion to each position                                     */
/*----------------------------------------------------------------------------*/
  //AssignDiscountToPosition(rangcl);

/*----------------------------------------------------------------------------*/
/*  Assign TargetRefundValue                                                  */
/*----------------------------------------------------------------------------*/
    it.Reset();
    while ( (rentriep = (pxRangeControl*) ++it) != NULL )
    {
       if ( rentriep->TargetPromoList() == NULL)
          continue;
       AssignTargetRefundValue(rentriep);
    }

    if ( rangcl )
       delete rangcl;
    return ErrorState();
}
/*----------------------------------------------------------------------------*/
/* First we build up the Rangecollectionlist, containing discountgroupmember  */
/* information for each position within this orderobject.                     */
/*----------------------------------------------------------------------------*/
int
pxOrder :: TargetPromotionCollectList
(
)
{
    pxOrderItemListIter it(*ItemList_);     // define an iterator
    pxOrderItem *item;

    while ( (item = (pxOrderItem*) ++it) != NULL )
    {
       if ( !item->IsCancelled() )
       {
          item->CollectTargetPromoMembers ();
       }
    }
    return ErrorState();
}
/*----------------------------------------------------------------------------*/
/* Second: Build up the Rangecontrolelist, containing information for each    */
/* discountgroupnumber within the Rangecollectionlist.                        */
/*----------------------------------------------------------------------------*/
pxRangeControlList*
pxOrder :: TargetPromotionControleList
(
)
{
    pxRangeControlList* rangecl  = new pxRangeControlList();
    pxRangeControl*     rangecp  = NULL;
    pxRangeCollectListIter  cursor(*RangeCollectList());
    pxRangeCollect*    rc         = NULL;
    short             VZ         = Customer()->Vertriebszentrum(); // customers Branchno


    // scan the RangeCollectList, sorted by DiscountGrpNo
    while ( (rc = (pxRangeCollect*) ++cursor) != NULL )
    {
       if (rangecp == NULL )
       {
          rangecp = new pxRangeControl(VZ,rc->DiscountGrpNo(),rc->ArticleNo(),0,0,Customer()->IDFNr(),0, rc->PreisTyp());
          rangecl->InsertAscending(rangecp);
       }
       if (  rc->DiscountGrpNo() == rangecp->DiscountGrpNo() && rc->PreisTyp() == rangecp->PreisTyp())
       {
          rangecp->AddQuantity(rc->Quantity());
          rangecp->AddQtyPack(rc->QtyPack());
          rangecp->AddShipValue(rc->ShipValue());
       }
       else
       {
          rangecp = new pxRangeControl(VZ,rc->DiscountGrpNo(),rc->ArticleNo(),0,0,Customer()->IDFNr(),0,rc->PreisTyp());
          rangecl->InsertAscending(rangecp);
          rangecp->AddQuantity(rc->Quantity());
          rangecp->AddQtyPack(rc->QtyPack());
          rangecp->AddShipValue(rc->ShipValue());
       }
    }
    return rangecl;
}
/*----------------------------------------------------------------------------*/
/* Third: Build up per Position the PromoCollectList((article can belong to    */
/* more as one satisfied Targetpromotion.                                     */
/* This is necessary for calculation of the best Targetpromotion for each     */
/* article wihin this order                                                   */
/*----------------------------------------------------------------------------*/
int
pxOrder :: CollectItemTargetPromotions
(
    pxRangeControl* rclentryp
)
{
    pxDiscountListIter it(*(rclentryp->TargetPromoList()));
    pxDiscount*      diskentry = NULL;
    // unused variable
    // pxRangeControl*     rangecp  = NULL;
    pxRangeCollectListIter  cursor(*RangeCollectList());
    pxRangeCollect*    rc         = NULL;
    pxOrderItem*      item         = NULL;
    pxPromoCollect*   promocollect = NULL;
    pxPromotions*     promo        = NULL;
    // unused variable
    /* short             VZ         = */ Customer()->Vertriebszentrum(); // customers Branchno


    while ( (diskentry = (pxDiscount*) ++it) != NULL )
    {
       if ( diskentry->ArticleNo() > 0 )
       {
           rc = RangeCollectList()->Find(diskentry->ArticleNo(), rclentryp->DiscountGrpNo());
          if (rc)
          {
              item = (pxOrderItem*)ItemList_->At(rc->PosNr() - 1); // get item
             if (item)
             {
                if (promo == NULL )
                {
                   promo = new pxPromotions(Session(), diskentry->PromotionNo());
                   if ( promo->Get() )
                   {
                      delete promo;
                      promo = NULL;
                      continue;
                   }
                   if ( IsAuftragVomXML() )
                   {
                      if ( promo->IsSNotBySaleseWeb() )
                      {
                         delete promo;
                         promo = NULL;
                         continue;
                      }
                   }
                }
                promocollect = new pxPromoCollect(diskentry->PromotionNo(),diskentry->DiscountGrpNo(),rc->PosNr(), diskentry->ArticleNo());
                promocollect->SetDiscountValuePct(diskentry->DiscountValuePct());
                promocollect->SetDiscountQty(diskentry->DiscountQty());
                promocollect->SetPromotionType(promo->PromotionType());
                promocollect->SetAddOnPromoDiscOk(promo->AddOnPromoDiscOk());
                promocollect->SetAddOnStdDiscOk(promo->AddOnStdDiscOk());
                promocollect->SetPriority(promo->Priority());
                promocollect->SetGrossProfitPct(diskentry->GrossProfitPct());
                promocollect->SetRefundPct(diskentry->RefundPct());
                promocollect->SetRefundValue(diskentry->RefundValue());
                promocollect->SetRefundType(diskentry->RefundType());
                item->PromoCollectList()->InsertAscending(promocollect);
                delete promo;
                promo = NULL;
             }
          }
       }
       else
       {
          if (   diskentry->BaseQty() > 0 || diskentry->DiscountQty() > 0 || diskentry->DiscountValuePct() > 0 || diskentry->DiscountArticle() > 0 )
          {
             cursor.Reset();
             while ( (rc = (pxRangeCollect*) ++ cursor) != NULL )
             {
                if ( rc->DiscountGrpNo() == diskentry->DiscountGrpNo() ) // groupno equals
                {
                    item = (pxOrderItem*)ItemList_->At(rc->PosNr() - 1); // get item
                   if (item)
                   {
                      if (promo == NULL )
                      {
                         promo = new pxPromotions(Session(), diskentry->PromotionNo());
                         if ( promo->Get() )
                         {
                            delete promo;
                            promo = NULL;
                            continue;
                         }
                      }
                      if ( IsAuftragVomXML() )
                      {
                         if ( promo->IsSNotBySaleseWeb() )
                         {
                            delete promo;
                            promo = NULL;
                            continue;
                         }
                      }
                      promocollect = new pxPromoCollect(diskentry->PromotionNo(),diskentry->DiscountGrpNo(),rc->PosNr(), diskentry->ArticleNo());
                      promocollect->SetDiscountValuePct(diskentry->DiscountValuePct());
                      promocollect->SetDiscountQty(diskentry->DiscountQty());
                      promocollect->SetPromotionType(promo->PromotionType());
                      promocollect->SetAddOnPromoDiscOk(promo->AddOnPromoDiscOk());
                      promocollect->SetAddOnStdDiscOk(promo->AddOnStdDiscOk());
                      promocollect->SetPriority(promo->Priority());
                      promocollect->SetGrossProfitPct(diskentry->GrossProfitPct());
                      promocollect->SetRefundPct(diskentry->RefundPct());
                      promocollect->SetRefundValue(diskentry->RefundValue());
                      promocollect->SetRefundType(diskentry->RefundType());
                      item->PromoCollectList()->InsertAscending(promocollect);
                      delete promo;
                      promo = NULL;
                   }
                }
             }
          }
       }
    }
    if (promo)
    {
       delete promo;
       promo = NULL;
    }
    return ErrorState();
}
/*----------------------------------------------------------------------------*/
/* GetTargetBestPromotion                                                     */
/*----------------------------------------------------------------------------*/
short
pxOrder :: GetTargetBestPromotion
(
    pxRangeControl* rclentryp
)
{
    short  BestPromo = 0;
    pxDiscountListIter it(*(rclentryp->TargetPromoList()));
    // unused variable
    // pxDiscount*      diskentry = NULL;
    // pxRangeControl*     rangecp  = NULL;
    pxRangeCollectListIter  cursor(*RangeCollectList());
    pxRangeCollect*    rc         = NULL;
    // pxPromotions*     promo        = NULL;

    while ( (rc = (pxRangeCollect*) ++ cursor) != NULL )
    {
       if ( rc->DiscountGrpNo() == rclentryp->DiscountGrpNo() ) // groupno equals
       {
           pxOrderItem* item = (pxOrderItem*)ItemList_->At(rc->PosNr() - 1); // get item
          if (item)
          {
              pxPromoCollect* promocollect = item->PromoCollectList()->BestTargetPromotion();
             if (promocollect)
             {
                 BestPromo = promocollect->PromotionNo();
                 break;
             }
          }
       }
    }
    return BestPromo;
}
/*----------------------------------------------------------------------------*/
/* TargetRefundValue                                                          */
/*----------------------------------------------------------------------------*/
int
pxOrder :: AssignTargetRefundValue
(
    pxRangeControl* rclentryp
)
{
    short  BestPromo = 0;
    pxDiscountListIter it(*(rclentryp->TargetPromoList()));
    pxDiscount*      diskentry = NULL;
    pxRangeCollectListIter  cursor(*RangeCollectList());

    bool headerRefund = false;
    pxKdAuftragPosRefund* refund=NULL;

    double  RefundValue = 0.0;

    BestPromo = GetTargetBestPromotion(rclentryp);
    if ( BestPromo != rclentryp->PromotionNo() )
       return ErrorState();

    while ( (diskentry = (pxDiscount*) ++it) != NULL )
    {
       if ( diskentry->ArticleNo() == 0 )
       {
          if ( diskentry->RefundValue() != pxConstants::mZero && diskentry->RefundPct() > 0)
          {
             headerRefund = false;
          }
          else
          if ( diskentry->RefundValue() != pxConstants::mZero && diskentry->RefundPct() == 0.0 )
          {
             RefundValue = (double) diskentry->RefundValue();
             headerRefund = true;
          }
       }
       else
       if (diskentry->RefundPct() > 0 )
       {
          headerRefund = false;
       }
    }
    if ( headerRefund )
    {

       refund= new pxKdAuftragPosRefund(Session(),KdAuftragNr_,0, RefundValue, 1, rclentryp->PromotionNo());
       refund->Put();
       Error() = refund->Error();
    }

    return ErrorState();
}
/*----------------------------------------------------------------------------*/
/* TargetRefundValue for manually booked Target Promoions                     */
/*----------------------------------------------------------------------------*/
int
pxOrder :: AssignOrderEntryTargetRefundValue
(
)
{
    short  PromotionNo = 0;
    pxOrderItemListIter it(*ItemList());
    pxOrderItem *item;
    pxDiscountList* TargetPromoList = new pxDiscountList(Session());
    pxDiscountListIter cursor(*TargetPromoList);
    // unused variable
    // pxDiscount*           diskentry       = NULL;

    // unused variable
    // double  RefundValue = 0.0;

    while ( (item = (pxOrderItem*) ++it) != NULL )
    {
       if ( item->PromoTyp() == 1 )        // belongs to an allready booked Target Promotion
       {
          if ( PromotionNo == 0 )
          {
             PromotionNo = item->PromotionNo();
             continue;
          }
          if ( PromotionNo == item->PromotionNo())
          {
             continue;
          }
          AssignTargetRefundValue( PromotionNo);
          PromotionNo = 0;
       }
    }

    if ( PromotionNo > 0 )
    {
       AssignTargetRefundValue( PromotionNo);
    }


    return ErrorState();
}
/*----------------------------------------------------------------------------*/
/* TargetRefundValue                                                          */
/*----------------------------------------------------------------------------*/
int
pxOrder :: AssignTargetRefundValue
(
    short PromotionNo
)
{
    pxDiscountList* TargetPromoList = new pxDiscountList(Session());
    pxDiscountListIter cursor(*TargetPromoList);
    pxKdAuftragPosRefund* refund=NULL;
    pxDiscountListIter it(*TargetPromoList);
    pxDiscount*      diskentry = NULL;
    short BranchNo    = Customer()->Vertriebszentrum();

    bool headerRefund = false;

    double  RefundValue = 0.0;

    TargetPromoList->SelectRange(BranchNo, PromotionNo ,IDFNr_ );

    while ( (diskentry = (pxDiscount*) ++it) != NULL )
    {
       if ( diskentry->ArticleNo() == 0 )
       {
          if ( diskentry->RefundValue() != pxConstants::mZero && diskentry->RefundPct() > 0)
          {
             headerRefund = false;
          }
          else
          if ( diskentry->RefundValue() != pxConstants::mZero && diskentry->RefundPct() == 0.0 )
          {
             RefundValue = (double) diskentry->RefundValue();
             headerRefund = true;
          }
       }
       else
       if (diskentry->RefundPct() > 0 )
       {
          headerRefund = false;
       }
    }
    if ( headerRefund )
    {

       refund= new pxKdAuftragPosRefund(Session(),KdAuftragNr_,0, RefundValue, 1, PromotionNo);
       refund->Put();
       Error() = refund->Error();
    }
    delete  TargetPromoList;
    return ErrorState();
}
