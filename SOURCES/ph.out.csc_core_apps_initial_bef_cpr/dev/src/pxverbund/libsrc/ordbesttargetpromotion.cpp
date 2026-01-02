#include "pxrecord.h"
#include "pxdevice.hpp"
#include "pxsess.hpp"
#include "pxcstbas.hpp"
#include "pxcustomergrpflags.hpp"
#include "pxartbas.hpp"
#include "pxitem.hpp"
#include "pxcomtyp.hpp"
#include "pxstktra.hpp"
#include "pxorder.hpp"
#include "pxoeparm.hpp"
#include "pxcstot.hpp"
#include "pxcstrou.hpp"
#include "pxoclpar.hpp"
#include "pxrangecollect.hpp"
#include "pxrangemember.hpp"
#include "pxdiscountordtyp.hpp"
#include "pxrangecontrol.hpp"
#include "pxitemdiscount.hpp"
#include "types/messagecodeenum.inc"

/*----------------------------------------------------------------------------*/
/*  BestTargetPromotion : This is a special methode devoloped for the         */
/*  bulgarian order entry system (BG-ID232).                                  */
/*  This methode calculates the best targetpromotion within the               */
/*  ItemListTemporary                                                         */
/*  The calculation is based on the promotion number within each item         */
/*  of this list                                                              */
/*  This fuction is called by the manual order entry system during shift P    */
/*  (booking of target promotion) to find out the best promotion scale.       */
/*  The best TargetpromotionNo will be return in param PromotionNo(callers    */
/*  variable)                                                                 */
/*----------------------------------------------------------------------------*/
int
pxOrder :: BestTargetPromotion
(
    long  *PromotionNo
)
{
    pxCustBase*       customer    = Customer();       // customer
    pxRangeControlList*    rangcl = NULL;
    pxRangeControl*      rentriep = NULL;             // RangeControlEntry Pointer

/*----------------------------------------------------------------------------*/
/*  Basic sanity checks.                                                      */
/*----------------------------------------------------------------------------*/
     ClearError();
    if (!ItemList_ )                    // then order item processing not open
       return ExternalError(CMsgStream(), CMSG_ORD_NOTOPEN, KdAuftragNr_);
/*----------------------------------------------------------------------------*/
/*  Additional sanity checks.                                                 */
/*----------------------------------------------------------------------------*/
    if ( !IsPseudoLock() )
    {
       if ( !IsLocked() )                  // order still locked ??
       {
          ExternalError(CMsgStream(),CMSG_ORD_LOCK_DISAPPEARED, KdAuftragNr_);
          return NULL;
       }
    }

    if (!Session()->isBulgaria())
       return NULL;

    // OrderType is not discountable
    if ( !OrderType().IsDiscountable() )
          return ErrorState();

    // Customer Group is not discountable(Group 8,9,13)
    //if ( customer->Group().IsDiscountDisabled()  )
    if ( !(customer->CustomerGroupFlagsList()->IsKscDiscountEnabled())  )
          return ErrorState();

    if ( ItemListTemporary()->Entries() == 0 )
    {
       return ErrorState();
    }
/*----------------------------------------------------------------------------*/
/*  Now look for discount groups within each item of the ItemListTemporary    */
/*----------------------------------------------------------------------------*/
    RangeCollectList();                     // init RangeCollectList
    PromotionScaleCollectList();            // collection of promotion scale members
    if ( !RangeCollectList()->Entries() )
    {
       delete RangeCollectList_;
       RangeCollectList_ = NULL;
       return ErrorState();
    }

    rangcl = PromotionScaleControleList();  // collection of discountgroup numbers
/*----------------------------------------------------------------------------*/
/*  First check validity of Rangecontrol Entries                              */
/*  every non valid entry will be removed from the list                       */
/*----------------------------------------------------------------------------*/
    pxRangeControlListIter    cursor(*rangcl);
    if ( rangcl->Entries() )
    {
       while ( (rentriep = (pxRangeControl*) ++cursor) != NULL )
       {
          if ( !rentriep->IsValidTargetPromotion(Session(),this))
          {
              RangeCollectList()->DeleteInvalidEntries (rentriep->DiscountGrpNo(), rentriep->PreisTyp());
              delete cursor.Remove();
          }
       }
    }
    if ( rangcl->Entries() == 0)
    {
       delete rangcl;
       delete RangeCollectList_;
       RangeCollectList_ = NULL;
       return ErrorState();
    }

    // take the last entry from  rangcl, it should be the best one
    cursor.Reset();
    cursor.ToLast();
    rentriep = (pxRangeControl*)cursor.Current();
    if ( rentriep )
    {
       *PromotionNo = rentriep->DiscountGrpNo();
    }


    if ( rangcl )
       delete rangcl;
    if (RangeCollectList_ )
    {
       delete RangeCollectList_;
       RangeCollectList_ = NULL;
    }
    return ErrorState();
}

/*----------------------------------------------------------------------------*/
/* First we build up the Rangecollectionlist, containing discountgroupmember  */
/* information for each position within this orderobject.                     */
/*----------------------------------------------------------------------------*/
int
pxOrder :: PromotionScaleCollectList
(
)
{
    pxOrderItemListIter it(*ItemListTemporary_);     // define an iterator
    pxOrderItem *item;

    while ( (item = (pxOrderItem*) ++it) != NULL )
    {
       if ( !item->IsCancelled() )
       {
          item->CollectPromotionScaleMembers();
       }
    }
    return ErrorState();
}
/*----------------------------------------------------------------------------*/
/* Second: Build up the Rangecontrolelist, containing information for each    */
/* discountgroupnumber within the Rangecollectionlist.                        */
/*----------------------------------------------------------------------------*/
pxRangeControlList*
pxOrder :: PromotionScaleControleList
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
