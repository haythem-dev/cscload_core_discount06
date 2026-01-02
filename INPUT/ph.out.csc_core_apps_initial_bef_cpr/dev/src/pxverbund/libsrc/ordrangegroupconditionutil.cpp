#include "pxrecord.h"
#include "pxsess.hpp"
#include "pxdevice.hpp"
#include "pxcstbas.hpp"
#include "pxartbas.hpp"

#include "pxitem.hpp"
#include "pxorder.hpp"
#include "pxordtyp.hpp"
#include "pxcstot.hpp"
#include "pxrangecollect.hpp"
#include "pxrangemember.hpp"
#include "pxdiscountordtyp.hpp"
#include "pxrangecontrol.hpp"
#include "pxpromotions.hpp"
#include "pxartcompack.hpp"
#include "pxcpvalidityperiod.hpp"
#include "pxstockbooking.hpp"

/*----------------------------------------------------------------------------*/
/*  Book FreeArticle Position or a Package of Positions                       */
/*----------------------------------------------------------------------------*/
int
pxOrder :: calculateGroupQuantityArticleNo
(
    pxRangeControl* rclentryp
)
{
    pxOrderItem *newitem  = NULL;
    pxOrderItemListIter it(*ItemList_);
    pxArtComPackList        *acpl   = NULL;
    pxArtComPack        *acpentry   = NULL;
    pxCPValidityPeriodList *cpvpl   = NULL;
    pxCPValidityPeriod  *cpventry   = NULL;
    PriceTypeEnum PriceType = FREESALE_PRICE;
    bool StellerOk     = false;
    pxArtBase* discountArtBase    = NULL;
    bool       bProblemState      = false;

/*----------------------------------------------------------------------------*/
/*  Do some validity checks                                                   */
/*----------------------------------------------------------------------------*/
    if ( rclentryp->RangeCondition() == NULL ) // condition not reached
        return ErrorState();

    if ( rclentryp->RangeCondition()->DiscountArticle() ==  0 || rclentryp->RangeCondition()->DiscountQty() == 0 )
        return ErrorState();

    // check DiscountArticle_, maybe it is a Steller Article. In that case
    // we must check the type be select the cpvalidityperiod entry
    cpvpl = new pxCPValidityPeriodList(Session());
    cpvpl->Select(rclentryp->RangeCondition()->DiscountArticle());
    cpvpl->ReduceToValidEntries();
    if (cpvpl->Entries() == 0 )
    {
        delete cpvpl;
    }
    else
    {
        cpventry = (pxCPValidityPeriod*)( cpvpl->At(0)); // entry to be checked
    }

    if ( cpventry )
    {
        if ( cpventry->IsReplaceDiscArticle() || cpventry->IsReplaceByMembers()  )       // = 3/4 Rebate from the artcompack list
        {
            // now get the members belonging to this Pseudo article
            acpl = new pxArtComPackList(Session());
            acpl->Select( rclentryp->RangeCondition()->DiscountArticle());
            if (acpl->Entries() == 0 )                   // nothing found
            {
                delete acpl;
                acpl = NULL;
                return ErrorState();
            }
        }
    }
    // now book the members belonging to  item->DiscountArticleNo()
    if ( acpl )
    {
        pxArtComPackListIter iter(*acpl);

        iter.Reset();
        while ( (acpentry = (pxArtComPack*) ++iter) != NULL )
        {
            if ( cpventry->IsReplaceDiscArticle()  )
            {
                if ( !StellerOk )
                {
                    newitem = NewOrderItemProforma_NatraWithRangeArticle(acpentry->ArticleNoElement(), 0L, PriceType);
                }
            }
            else
            {
                // first check quantity in Stock. If QInStock of the discount article does not fit the  item->MengeNatraDiscountArticle,
                // we mark this item and  also  this order. This order will be deferred, so it can be manupulated by the KSC employers
                long DiscountQty = rclentryp->RangeCondition()->CalcDiscountQty(rclentryp->QtyInRange());
                discountArtBase = pxArtBase :: CreateArticle(Session(), acpentry->ArticleNoElement(), FilialNr());
                if (  discountArtBase->IsGoodState() )
                {
                    if ( Session()->getStockBooking()->GetAvailableQtyInStock(*discountArtBase) < DiscountQty )   // does not fit
//                    if ( discountArtBase->Bestand() < DiscountQty )   // does not fit
                    {
                        bProblemState = true;
                    }
                }
                else
                {
                    bProblemState = true;
                }
                delete discountArtBase;
                // now decide about what to do, write position or not
                if ( !bProblemState )
                {
                    newitem = NewOrderItemProforma_NatraWithRangeArticle(acpentry->ArticleNoElement(), acpentry->Quantity(), PriceType);
                }
            }
            bProblemState = false;
            if ( newitem == NULL )
            {
                ClearError();                           // to prevent Error during booking
            }
            else
            if ( newitem->IsGoodState() )
            {
                Error() = newitem->Error();
            }
        }
        delete acpl;
        delete cpvpl;
        return ErrorState();
    }

    // first check quantity in Stock. If QInStock of the discount article does not fit the  item->MengeNatraDiscountArticle,
    // we mark this item and  also  this order. This order will be deferred, so it can be manupulated by the KSC employers
    long DiscountQty = rclentryp->RangeCondition()->CalcDiscountQty(rclentryp->QtyInRange());
    discountArtBase = pxArtBase :: CreateArticle(Session(), rclentryp->RangeCondition()->DiscountArticle(), FilialNr());
    if (  discountArtBase->IsGoodState() )
    {
        if ( Session()->getStockBooking()->GetAvailableQtyInStock(*discountArtBase) < DiscountQty )   // does not fit
//        if ( discountArtBase->Bestand() < DiscountQty )   // does not fit
        {
            bProblemState = true;
        }
    }
    else
    {
        bProblemState = true;
    }
    delete discountArtBase;

    // now decide about what to do, write position or not
    if ( !bProblemState )
    {
        newitem = NewOrderItemProforma_NatraWithRangeArticle(rclentryp->RangeCondition()->DiscountArticle(), DiscountQty, PriceType);
    }

    bProblemState = false;
    if ( newitem == NULL )
    {
        ClearError();                           // to prevent Error during booking
    }
    else
    if ( newitem->IsGoodState() )
    {
        rclentryp->AddGroupNaturalRebateValue(newitem->calculateNaturalRebateValue());
        Error() = newitem->Error();
    }
    return ErrorState();
}

/*----------------------------------------------------------------------------*/
/*  Book FreeArticle Position depebr discount->discountqtypct                 */
/*  discount->articleno must be set                                           */
/*----------------------------------------------------------------------------*/
int
pxOrder :: calculateGroupPercentageArticleNo
(
    pxRangeControl* rclentryp
)
{
    pxOrderItem *newitem  = NULL;
    pxArtBase* discountArtBase    = NULL;
    PriceTypeEnum PriceType = FREESALE_PRICE;
    bool bProblemState      = false;

/*----------------------------------------------------------------------------*/
/*  Do some validity checks                                                   */
/*----------------------------------------------------------------------------*/
    if ( rclentryp->RangeCondition() == NULL ) // condition not reached
        return ErrorState();

    if ( rclentryp->RangeCondition()->DiscountArticle() ==  0 || rclentryp->RangeCondition()->DiscountQtyPct() == 0.0 )
        return ErrorState();

    double res = (rclentryp->QtyInRange()*rclentryp->RangeCondition()->DiscountQtyPct()) / 100 + 0.5;
    // first check quantity in Stock. If QInStock of the discount article does not fit the  item->MengeNatraDiscountArticle,
    // we mark this item and  also  this order. This order will be deferred, so it can be manupulated by the KSC employers
    discountArtBase = pxArtBase :: CreateArticle(Session(), rclentryp->RangeCondition()->DiscountArticle(), FilialNr());
    if (  discountArtBase->IsGoodState() )
    {
        if ( Session()->getStockBooking()->GetAvailableQtyInStock(*discountArtBase) < (long)res )   // does not fit
//        if ( discountArtBase->Bestand() < (long)res )   // does not fit
        {
            bProblemState = true;
        }
    }
    else
    {
        bProblemState = true;
    }
    delete discountArtBase;

    // now decide about what to do, write position or not
    if ( !bProblemState )
    {
        newitem = NewOrderItemProforma_NatraWithRangeArticle(rclentryp->RangeCondition()->DiscountArticle(), (long)res, PriceType);
    }

    bProblemState = false;
    if ( newitem == NULL )
    {
        ClearError();                           // to prevent Error during booking
    }
    else
    if ( newitem->IsGoodState() )
    {
        rclentryp->AddGroupNaturalRebateValue(newitem->calculateNaturalRebateValue());
        Error() = newitem->Error();
    }
    return ErrorState();
}

/*----------------------------------------------------------------------------*/
/* calculateGroupDiscountQty. The same funtionality as                        */
/* calulateGroupDiscountPct                                                   */
/* but in this methode every rangemember position becomes an additional       */
/* quantity free for the RangeMember Article depend on the discount condition */
/* Please take care for a well constructed RangeControl List and a well       */
/* constructed RangeCollect List, otherwise you become unpredictable results  */
/*----------------------------------------------------------------------------*/
int
pxOrder :: calculateGroupDiscountQty
(
    pxRangeControl* rclentryp
)
{
    pxRangeCollectListIter  cursor(*RangeCollectList());
    pxRangeCollect*    rc         = NULL;

    if ( rclentryp->RangeCondition() == NULL ) // condition not reached
        return ErrorState();
    // Loop throug the RangeCollect List
    cursor.Reset();
    while ( (rc = (pxRangeCollect*) ++ cursor) != NULL )
    {
        if ( rc->DiscountGrpNo() == rclentryp->DiscountGrpNo() ) // groupno equals
        {
            pxOrderItem* item = (pxOrderItem*)ItemListProforma_->At(rc->PosNr() - 1); // get item
            if (item)
            {
                item->OrderQuantityRange_RangeArticle(item->MengeBestellt(), rclentryp->RangeCondition()->CalcDiscountQty(item->MengeBestellt()), item->MengeBestellt());
            }
        }
    }
    return ErrorState();
}
