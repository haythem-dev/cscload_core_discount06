#include "pxrecord.h"
#include "pxsess.hpp"
#include "pxcstbas.hpp"
#include "pxartbas.hpp"
#include "pxdiscountdef.h"
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
#include "pxitemdiscount.hpp"
#include "pxstockbooking.hpp"
#include "pxbase/pxconstants.hpp"

/*----------------------------------------------------------------------------*/
/* AssignDiscountPctToAllMembers:  Base input for this methode is the         */
/* RangeControl List. This list contains the summary + conditions informations*/
/* for all RangeMember positions gouped by discountgroupnumber                */
/* There exist just one entry per discountgroupnumber                         */
/* The next basic input is the RangeCollect List. This list contains datailed */
/* informations per RangeMember Position and discount group number            */
/* Depend on those two lists, every rangemember postion becomes the           */
/* discountvaluepercentage depend on the RangeCondition located within the    */
/* RangeControl List for every discount group number                          */
/* Please take care for a well constructed RangeControl List and a well       */
/* constructed RangeCollect List, otherwise you become unpredictable results  */
/*----------------------------------------------------------------------------*/
int
pxOrder :: AssignDiscountPctToAllMembers
(
    pxRangeControl*     rclentry,
    pxDiscount*         diskentry,
    pxItemDiscountList* discl
)
{
    pxRangeCollectListIter  cursor(*RangeCollectList());
    pxRangeCollect*    rc         = NULL;

    pxOrderItemListIter iterator(*ItemList_); // define an iterator

    if ( diskentry == NULL )         // error in call
        return ErrorState();

    // Loop throug the RangeCollect List
    cursor.Reset();
    while ( (rc = (pxRangeCollect*) ++ cursor) != NULL )
    {
        if ( rc->DiscountGrpNo() == diskentry->DiscountGrpNo() ) // groupno equals
        {
            pxOrderItem* item = (pxOrderItem*)ItemList_->At(rc->PosNr() - 1); // get item
            if (item)
            {
                if ( discl == NULL )
                {
                    item->AssignDiscountPct(diskentry, rclentry);
                    item->InvoiceValue(discl);
                }
                else
                {
                    item->AssignDiscountPctProforma(diskentry,discl);
                }
                //item->InvoiceValue(discl);
            }
        }
    }

    return ErrorState();
}

/*----------------------------------------------------------------------------*/
/* AssignDiscountQtyToAllMembers. The same funtionality as                    */
/* AssignDiscountPctToAllMembers,                                             */
/* but in this methode every rangemember position becomes an additional       */
/* quantity free for the RangeMember Article depend on the discount condition */
/* Please take care for a well constructed RangeControl List and a well       */
/* constructed RangeCollect List, otherwise you become unpredictable results  */
/*----------------------------------------------------------------------------*/
int
pxOrder :: AssignDiscountQtyToAllMembers
(
    pxRangeControl* rclentryp,
    pxDiscount*     diskentry
)
{
    pxRangeCollectListIter  cursor(*RangeCollectList());
    pxRangeCollect*    rc         = NULL;
    pxOrderItemListIter iterator(*ItemList_); // define an iterator

    if ( diskentry == NULL )         // error in call
        return ErrorState();
    // Loop throug the RangeCollect List
    cursor.Reset();
    while ( (rc = (pxRangeCollect*) ++ cursor) != NULL )
    {
        if ( rc->DiscountGrpNo() == rclentryp->DiscountGrpNo() ) // groupno equals
        {
            pxOrderItem* item = (pxOrderItem*)ItemList_->At(rc->PosNr() - 1); // get item
            if (item)
            {
                item->OrderQuantityRange_RangeArticle(item->MengeBestellt(), diskentry->CalcDiscountQty(item->MengeBestellt()), item->MengeBestellt());
            }
        }
    }
    return ErrorState();
}

/*----------------------------------------------------------------------------*/
/* AssignDiscountToPosition . The funtionality is like functions above        */
/* but in this methode every rangemember position becomes an additional       */
/* rebate depend on values in diskentry                                       */
/* Please take care for a well constructed RangeControl List and a well       */
/* constructed RangeCollect List, otherwise you become unpredictable results  */
/*----------------------------------------------------------------------------*/
int
pxOrder :: AssignDiscountToPosition
(
    pxRangeControlList* rcl,
    pxItemDiscountList* discl
)
{
    pxOrderItem*      item        = NULL;

    pxOrderItemListIter it(*ItemList_);     // define an iterator

    while ( (item = (pxOrderItem*) ++it) != NULL )
    {
        if ( !item->IsCancelled() )
        {
            if ( discl == NULL )
            {
                item->AssignTargetDiscount(rcl);
                item->InvoiceValue(discl);
            }
            else
            {
                item->AssignTargetDiscountProforma(rcl,discl );
            }
            //item->InvoiceValue(discl);
        }
    }
    return ErrorState();
}

/*----------------------------------------------------------------------------*/
/*  Book FreeArticle Position or a Package of Positions                       */
/*----------------------------------------------------------------------------*/
int
pxOrder :: TargetDiscountArticle
(
    pxRangeControl* rclentry,
    pxDiscount* disc
)
{
    Session()->Device();
    pxOrderItem *newitem  = NULL;
    pxOrderItemListIter it(*ItemList_);
    pxArtComPack        *acpentry   = NULL;
    short BestPromo     = 0;
    int   CountDiscountArticle = 0;
    long  PosNr         = 0;
    long  sMengeNatra   = 0;
    bool  StellerOk     = false;
    double     diskentryBaseValue = 0.0;
    long       diskentryBaseQty   = 0;

/*----------------------------------------------------------------------------*/
/*  Do some validity checks                                                   */
/*----------------------------------------------------------------------------*/
    if ( disc->DiscountArticle() ==  0 || disc->DiscountQty() == 0 )
        return ErrorState();

    BestPromo = GetTargetBestPromotion(rclentry);
    if ( BestPromo ==  0 )           // there is no Targetpromotion collected
    {
        return ErrorState();
    }

    diskentryBaseValue = rclentry->GetTargetControlBaseValue();
    diskentryBaseQty   = rclentry->GetTargetControlBaseQty();

    if ((BestPromo > 0) && (BestPromo != rclentry->PromotionNo()))
    {
        return ErrorState();
    }
    // is BestPromo already checked wihin this order
    if ( !ItemList_->FindPromotionNo(BestPromo ) )
    {
        return ErrorState();
    }
    PriceTypeEnum pricetype = getPriceType(disc->DiscountSpec());
    if ( AnzPos_ == CountPriceTypeItems(RETAIL_PRICE ) )
        pricetype = RETAIL_PRICE;

    // check DiscountArticle_, maybe it is a Steller Article. In that case
    // we must check the type be select the cpvalidityperiod entry
    pxArtComPackList* acpl = NULL;
    pxCPValidityPeriodList* cpvpl = NULL;
    pxCPValidityPeriod* cpventry = NULL;
    if (!getPseudoArticleMembers(disc->DiscountArticle(), cpvpl, cpventry, acpl))
    {
        return ErrorState();
    }
    // now book the members belonging to  item->DiscountArticleNo()
    // till now it's a bulgarian speciality
    if ( acpl )
    {
        pxArtComPackListIter iter(*acpl);
        while ( (acpentry = (pxArtComPack*) ++iter) != NULL )
        {
            if ( cpventry->IsReplaceDiscArticle()  )
            {
                PosNr = 0;
                CountDiscountArticle = ItemList_->CountTargetDiscountArticle(acpentry->ArticleNoElement());
                if ( CountDiscountArticle > 0 )
                {
                    while  (CountDiscountArticle > 0 )
                    {
                        newitem = ItemList_->GetTargetDiscountArticle(acpentry->ArticleNoElement(), PosNr );
                        if ( newitem == NULL )
                        {
                            break;
                        }
                        if ( newitem->PromotionNo() ==  disc->PromotionNo() )
                        {
                            sMengeNatra += newitem->MengeNatra();
                            if ( newitem->MengeNatra() > 0 )                      // already booked (AE)
                            {
                                if (sMengeNatra >= disc->DiscountQty() )
                                {
                                    StellerOk = true;
                                }
                            }
                            PosNr = newitem->PosNr();
                            --CountDiscountArticle;
                            newitem = NULL;
                            continue;
                        }
                        newitem->OrderQuantityRange_NatraWithRangeArticle(0L);
                        newitem->SetPromotionNo(disc->PromotionNo());
                        PosNr = newitem->PosNr();
                        --CountDiscountArticle;
                        newitem = NULL;
                    }
                }
            }
        }

        iter.Reset();
        while ( (acpentry = (pxArtComPack*) ++iter) != NULL )
        {
            newitem = NULL;
            if ( cpventry->IsReplaceDiscArticle()  )
            {
                if ( !StellerOk )
                {
                    newitem = NewOrderItem_03_NatraWithRangeArticle(acpentry->ArticleNoElement(), 0L, pricetype);
                    SetRebateArtSelection();
                }
            }
            else
            {
                CountDiscountArticle = ItemList_->CountTargetDiscountArticle(acpentry->ArticleNoElement());
                if ( CountDiscountArticle > 0 )
                {
                    while  (CountDiscountArticle > 0 )
                    {
                        newitem = ItemList_->GetTargetDiscountArticle(acpentry->ArticleNoElement(), PosNr );
                        if ( newitem == NULL )
                        {
                            break;
                        }
                        if ( newitem-> PromotionNo() ==  disc->PromotionNo() )
                        {
                            PosNr = newitem->PosNr();
                            --CountDiscountArticle;
                            continue;
                        }
                        newitem->OrderQuantityRange_NatraWithRangeArticle(acpentry->Quantity());
                        newitem->SetPromotionNo(disc->PromotionNo());
                        PosNr = newitem->PosNr();
                        --CountDiscountArticle;
                    }
                }
                else
                {
                    pxOrderItem* resultItem = getNewOrderItemProformaOrSetTargetPositionsProblemState(rclentry, acpentry->ArticleNoElement(), acpentry->Quantity(), pricetype);
                    if (resultItem != NULL)
                    {
                        newitem = resultItem;
                    }
                }
            }

            if ( newitem == NULL )
            {
                ClearError();                           // to prevent Error during booking
            }
            else
            if ( newitem->IsGoodState() )
            {
                newitem->SetSperreRabattManuell();      // mark position
                newitem->SetPromotionNo(disc->PromotionNo() );  // mark promotion
                if ( cpventry->IsReplaceDiscArticle() || cpventry->IsReplaceByMembers()  )  // = 3/4 Rebate from the artcompack list
                {
                    newitem->SetPromoTyp((short) 2);      // mark promotion
                }
                newitem->UndoOrderPosPromo();
                newitem->WriteOrderPosPromo( disc->PharmacyGroupId(),disc->DiscountGrpNo(),diskentryBaseQty,
                                            diskentryBaseValue,disc->CustomerNo(), disc->PromotionNo());
                Error() = newitem->Error();
            }
        }
        delete acpl;
        delete cpvpl;
        return ErrorState();
    }

    CountDiscountArticle = ItemList_->CountTargetDiscountArticle(disc->DiscountArticle());
    if ( CountDiscountArticle > 0 )
    {
        while  (CountDiscountArticle > 0 )
        {
            newitem = ItemList_->GetTargetDiscountArticle(disc->DiscountArticle(), PosNr );
            if ( newitem == NULL )
            {
                break;
            }
            if ( newitem->PromotionNo() ==  disc->PromotionNo() )
            {
                PosNr = newitem->PosNr();
                --CountDiscountArticle;
                continue;
            }
            short problemState = checkQtyInStockBG(disc->DiscountArticle(), disc->DiscountQty());
            if (problemState == pxOrderItem::PGood)
            {
                newitem->OrderQuantityRange_NatraWithRangeArticle(disc->DiscountQty());
            }
            else
            {
                SetNoRebateQty();
                newitem->SetProblemState(problemState);
            }

            newitem->SetPromotionNo(disc->PromotionNo());
            PosNr = newitem->PosNr();
            --CountDiscountArticle;
        }
    }
    else
    {
        if (Session()->isBulgaria())
        {
            pxOrderItem* resultItem = getNewOrderItemProformaOrSetTargetPositionsProblemState(rclentry, disc->DiscountArticle(), disc->DiscountQty(), pricetype);
            if (resultItem != NULL)
            {
                newitem = resultItem;
            }
        }
        else
        {
            newitem = NewOrderItem_03_NatraWithRangeArticle(disc->DiscountArticle(), disc->DiscountQty(), pricetype);
        }
    }

    if ( newitem == NULL )
    {
        ClearError();                           // to prevent Error during booking
    }
    else
    if ( newitem->IsGoodState() )
    {
        Error() = newitem->Error();
        newitem->SetSperreRabattManuell();         // mark position
        newitem->SetPromotionNo(disc->PromotionNo() );     // mark promotion
        newitem->SetPromoTyp((short) 2);           // mark promotion
        newitem->UndoOrderPosPromo();
        newitem->WriteOrderPosPromo( disc->PharmacyGroupId(),disc->DiscountGrpNo(),diskentryBaseQty,
                                     diskentryBaseValue,disc->CustomerNo(), disc->PromotionNo());
    }
    return ErrorState();
}

/*----------------------------------------------------------------------------*/
/*  Book FreeArticle Position or a Package of Positions                       */
/*----------------------------------------------------------------------------*/
int
pxOrder :: TargetDiscountArticleProforma
(
    pxRangeControl* rclentry,
    pxDiscount* disc
)
{
    Session()->Device();
    pxOrderItem *newitem  = NULL;
    pxOrderItemListIter it(*ItemList_);
    pxArtComPack        *acpentry   = NULL;
    short BestPromo     = 0;
    bool  StellerOk       = false;

/*----------------------------------------------------------------------------*/
/*  Do some validity checks                                                   */
/*----------------------------------------------------------------------------*/
    if ( disc->DiscountArticle() ==  0 || disc->DiscountQty() == 0 )
        return ErrorState();

    BestPromo = GetTargetBestPromotion(rclentry);

    if ( BestPromo ==  0 )           // there is no Targetpromotion collected
    {
        return ErrorState();
    }

    if ((BestPromo > 0) && (BestPromo != rclentry->PromotionNo()))
    {
        return ErrorState();
    }
    // is BestPromo already checked wihin this order check ItemListProforma
   /*f ( !ItemList_->FindPromotionNo(BestPromo ) )
    {
        return ErrorState();
    }
   */
    PriceTypeEnum pricetype = getPriceType(disc->DiscountSpec());

    // check DiscountArticle_, maybe it is a Steller Article. In that case
    // we must check the type be select the cpvalidityperiod entry
    pxArtComPackList* acpl = NULL;
    pxCPValidityPeriodList* cpvpl = NULL;
    pxCPValidityPeriod* cpventry = NULL;
    if (!getPseudoArticleMembers(disc->DiscountArticle(), cpvpl, cpventry, acpl))
    {
        return ErrorState();
    }
    // now book the members belonging to  item->DiscountArticleNo()
    // till now it's a bulgarian speciality
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
                    newitem = NewOrderItemProforma_NatraWithRangeArticle(acpentry->ArticleNoElement(), 0L, pricetype);
                }
            }
            else
            {
                pxOrderItem* resultItem = getNewOrderItemProforma(rclentry, acpentry->ArticleNoElement(), acpentry->Quantity(), pricetype);
                if (resultItem != NULL)
                {
                    newitem = resultItem;
                }
            }

            verifyNewOrderItemProforma(newitem, BestPromo);
        }
        delete acpl;
        delete cpvpl;
        return ErrorState();
    }

    pxOrderItem* resultItem = getNewOrderItemProforma(rclentry, disc->DiscountArticle(), disc->DiscountQty(), pricetype);
    if (resultItem != NULL)
    {
        newitem = resultItem;
    }

    verifyNewOrderItemProforma(newitem, BestPromo);
    return ErrorState();
}

pxOrderItem* pxOrder::getNewOrderItemProforma(pxRangeControl* rclentry, long articleNo, long quantity, PriceTypeEnum priceType)
{
    long DiscountQty = CalcTargetDiscountFacktor(rclentry) * quantity;
    if (checkQtyInStockBG(articleNo, DiscountQty) == pxOrderItem::PGood)
    {
        // Don't use DiscountQty as second parameter, as I don't know if CalcTargetDiscountFacktor result is still the same!
        return NewOrderItemProforma_NatraWithRangeArticle(articleNo, (CalcTargetDiscountFacktor(rclentry) * quantity), priceType);
    }
    return NULL;
}

void pxOrder::verifyNewOrderItemProforma(pxOrderItem* newItem, short bestPromo)
{
    if (newItem == NULL)
    {
        ClearError();                           // to prevent Error during booking
    }
    else if (newItem->IsGoodState())
    {
        newItem->SetPromoTyp(2);                // mark promotion
        newItem->SetPromotionNo(bestPromo);
        Error() = newItem->Error();
    }
}

pxOrderItem* pxOrder::getNewOrderItemProformaOrSetTargetPositionsProblemState(pxRangeControl* rclentry, long articleNo, long quantity, PriceTypeEnum priceType)
{
    long DiscountQty = CalcTargetDiscountFacktor(rclentry) * quantity;
    short problemState = checkQtyInStockBG(articleNo, DiscountQty);
    if (problemState == pxOrderItem::PGood)
    {
        // Don't use DiscountQty as second parameter, as I don't know if CalcTargetDiscountFacktor result is still the same!
        return NewOrderItem_03_NatraWithRangeArticle(articleNo, (CalcTargetDiscountFacktor(rclentry) * quantity), priceType);
    }
    SetNoRebateQty();
    TargetPositionsProblemState(rclentry, problemState);
    return NULL;
}

short pxOrder::checkQtyInStockBG(long articleNo, long discountQuantity)
{
    short problemState = pxOrderItem::PGood;

    // first check quantity in Stock. If QInStock of the discount article does not fit the  item->MengeNatraDiscountArticle,
    // we mark this item and  also  this order. This order will be deferred, so it can be manupulated by the KSC employers
    if (Session()->isBulgaria())
    {
        pxArtBase* discountArtBase = pxArtBase::CreateArticle(Session(), articleNo, FilialNr());
        if (discountArtBase->IsGoodState())
        {
            if (Session()->getStockBooking()->GetAvailableQtyInStock(*discountArtBase) < discountQuantity)   // does not fit
            {
                problemState = pxOrderItem::PDiscountNoQty;
            }
        }
        else
        {
            problemState = pxOrderItem::PDiscountArticleNotAV;
        }
        delete discountArtBase;
    }
    return problemState;
}

/*----------------------------------------------------------------------------*/
/* AssignRangeGrossProfitPct:  Base input for this methode is the             */
/* RangeControl List. This list contains the summary + conditions informations*/
/* for all RangeMember positions gouped by discountgroupnumber                */
/* There exist just one entry per discountgroupnumber                         */
/* The next basic input is the RangeCollect List. This list contains detailed */
/* informations per RangeMember Position and discount group number            */
/* Depend on those two lists, every rangemember postion becomes the           */
/* GrossProfit percentage depend  on the RangeCondition located within        */
/* the RangeControl List for every discount group number                      */
/* Please take care for a well constructed RangeControl List and a well       */
/* constructed RangeCollect List, otherwise you become unpredictable results  */
/*----------------------------------------------------------------------------*/
int
pxOrder :: AssignTargetGrossProfitPct
(
    pxRangeControl* rclentryp
)
{
    pxRangeCollectListIter  cursor(*RangeCollectList());
    pxRangeCollect*    rc         = NULL;
    pxItemDiscount*   itemdisc    = NULL;
    pxOrderItemListIter iterator(*ItemList_); // define an iterator
    double grossprofit          = 0.0;

    if ( rclentryp->RangeCondition() == NULL ) // condition not reached
        return ErrorState();
    // Loop throug the RangeCollect List
    cursor.Reset();
    while ( (rc = (pxRangeCollect*) ++ cursor) != NULL )
    {
        if ( rc->DiscountGrpNo() == rclentryp->DiscountGrpNo() ) // groupno equals
        {
            pxOrderItem* item = (pxOrderItem*)ItemList_->At(rc->PosNr() - 1); // get item
            if (item)
            {
                grossprofit = item->CalcDiscountPercentage(rclentryp->RangeCondition()->GrossProfitPct(), (short)pxOrderItem::CascadeLevelRangePromotion, item->MengeBestellt() );

                //item->UndoItemDiscount();                          // undo discount
                itemdisc = new pxItemDiscount(Session(), KdAuftragNr_, item->PosNr(),
                                        (short)BestBuy_GrossProfitPct,
                                        rclentryp->RangeCondition()->PharmacyGroupId());
                itemdisc->SetDiscountValuePct(grossprofit);
                itemdisc->Put();
                item->ItemDiscountList()->Append(itemdisc);
                SetDoNotSplittOrder();
                item->InvoiceValue();
            }
        }
    }
    return ErrorState();
}

/*----------------------------------------------------------------------------*/
/* TargetPositionsProblemState:  Sets the ProblemState to all Positions       */
/* belonging to the discount group of rclentryp (entry of RangeControl List)  */
/* Please take care for a well constructed RangeControl List and a well       */
/* constructed RangeCollect List, otherwise you become unpredictable results  */
/*----------------------------------------------------------------------------*/
int
pxOrder :: TargetPositionsProblemState
(
    pxRangeControl* rclentryp,
    short          ProblemState
)
{
    pxRangeCollectListIter  cursor(*RangeCollectList());
    pxRangeCollect*    rc         = NULL;
    pxOrderItemListIter iterator(*ItemList_); // define an iterator

    // Loop throug the RangeCollect List
    cursor.Reset();
    while ( (rc = (pxRangeCollect*) ++ cursor) != NULL )
    {
        if ( rc->DiscountGrpNo() == rclentryp->DiscountGrpNo() ) // groupno equals
        {
            pxOrderItem* item = (pxOrderItem*)ItemList_->At(rc->PosNr() - 1); // get item
            if (item)
            {
                item->SetProblemState(ProblemState);
            }
        }
    }
    return ErrorState();
}

/*----------------------------------------------------------------------------*/
/* CalcTargetDiscountFacktor: go thru the targetpromolist.                    */
/*----------------------------------------------------------------------------*/
long
pxOrder :: CalcTargetDiscountFacktor
(
    pxRangeControl* rclentryp
)
{
    pxDiscountListIter it(*(rclentryp->TargetPromoList()));
    pxRangeCollectListIter  cursor(*RangeCollectList());
    pxDiscount*      diskentry    = NULL;

    long DiscountFaktor = 1;
    long LowDiscountFaktor = 0;
    long TargetQty  = 0;
    bool NonProportional = false;
    double TargetShipValue     = 0.0;
    double StdBaseValue        = 1.0;

    while ( (diskentry = (pxDiscount*) ++it) != NULL )
    {
        if ( diskentry->ArticleNo() > 0 )
        {
            DiscountFaktor = CalcPosTartgetDiscountFaktor(diskentry);
            if ( (LowDiscountFaktor == 0) || (DiscountFaktor < LowDiscountFaktor) )
            {
                LowDiscountFaktor =  DiscountFaktor;
            }
        }
        else
        {
            TargetQty        += diskentry->BaseQty();
            TargetShipValue  += diskentry->BaseValue();
            if ( diskentry->IsNonProportional() )
            {
                NonProportional = true;
            }
        }
    }

    // check LowDiscountFaktor
    if (  LowDiscountFaktor > 0 )
    {
        return LowDiscountFaktor;
    }

    if ( NonProportional )
    {
        return DiscountFaktor;
    }

    if ( TargetQty > 0 )
    {
        DiscountFaktor = rclentryp->QtyInRange() / TargetQty;
    }
    else
    if ( TargetShipValue  != pxConstants::dZero )
    {
        if ( TargetShipValue < StdBaseValue )     // may be 0.01
        {
            DiscountFaktor = 1L;
        }
        else
        {
            DiscountFaktor = static_cast<long>(rclentryp->ShipValue() / TargetShipValue);
        }
    }

    DiscountFaktor = ((DiscountFaktor > 0 ) ? DiscountFaktor : 1L );

    return DiscountFaktor;
}

/*----------------------------------------------------------------------------*/
/* CalcTargetDiscountFacktor: go thru the targetpromolist.                    */
/*----------------------------------------------------------------------------*/
long
pxOrder :: CalcPosTartgetDiscountFaktor
(
    pxDiscount* diskentry
)
{
    pxRangeCollect*    rc         = NULL;
    long DiscountFaktor = 1;
    double StdBaseValue        = 1.0;

    if ( diskentry->ArticleNo() > 0 )
    {
        if ( RangeCollectList() )
        {
            rc = RangeCollectList()->Find( diskentry->ArticleNo(), diskentry->DiscountGrpNo() );
            if ( rc )
            {
                if ( diskentry->BaseQty() > 0 )
                {
                    DiscountFaktor = rc->Quantity() / diskentry->BaseQty();
                }
                else
                if ( diskentry->BaseValue() > pxConstants::dZero )
                {
                    if ( diskentry->BaseValue()  ==  StdBaseValue )
                    {
                        DiscountFaktor = 1L;
                    }
                    else
                    {
                        DiscountFaktor = static_cast<long>(rc->ShipValue() / diskentry->BaseValue());
                    }
                }
            }
        }
    }
    return DiscountFaktor;
}

PriceTypeEnum pxOrder::getPriceType(short discountSpec)
{
    if (   (discountSpec == DiscSpec_HealthFund)
        || (AnzPos_ == CountPriceTypeItems(HEALTHFUND_PRICE )) )
    {
        return HEALTHFUND_PRICE;
    }
    else
    {
        return FREESALE_PRICE;
    }
}

bool pxOrder::getPseudoArticleMembers(long discountArticle, pxCPValidityPeriodList*& cpvpl, pxCPValidityPeriod*& cpventry, pxArtComPackList*& acpl)
{
    cpvpl = new pxCPValidityPeriodList(Session());
    cpvpl->Select(discountArticle);
    cpvpl->ReduceToValidEntries();
    if (cpvpl->Entries() == 0)
    {
        delete cpvpl;
        cpvpl = NULL;
        cpventry = NULL;
    }
    else
    {
        cpventry = (pxCPValidityPeriod*)(cpvpl->At(0)); // entry to be checked
    }

    if ((cpventry != NULL) && (cpventry->IsReplaceDiscArticle() || cpventry->IsReplaceByMembers()))       // = 3/4 Rebate from the artcompack list
    {
        // now get the members belonging to this Pseudo article
        acpl = new pxArtComPackList(Session());
        acpl->Select(discountArticle);
        if (acpl->Entries() == 0)                   // nothing found
        {
            delete acpl;
            acpl = NULL;
            delete cpvpl;
            cpvpl = NULL;
            cpventry = NULL;
            return false;
        }
    }
    return true;
}
