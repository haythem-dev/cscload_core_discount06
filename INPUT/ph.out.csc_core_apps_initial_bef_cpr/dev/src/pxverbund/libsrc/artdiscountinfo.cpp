/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

Class pxArtDiscountInfo:

REVISION HISTORY

01 February 2010 V1.00 REV 00 written by Ysbrand.Bouma
*/

#include "pxartdiscountinfo.hpp"
#include "pxdbxx.h"
#include "pxsess.hpp"
#include "pxcstbas.hpp"
#include "pxdiscount.hpp"
#include "pxorder.hpp"
#include "pxitem.hpp"
#include "pxoeparm.hpp"
#include "pxcustomergrpflags.hpp"
#include "pxbase/pxconstants.hpp"

extern bool pxGlobalNoDatabaseWrite;
/*----------------------------------------------------------------------------*/
/*  Constructor for pxArtDiscountInfo                                         */
/*                                                                            */
/*----------------------------------------------------------------------------*/
pxArtDiscountInfo :: pxArtDiscountInfo
(
    pxSession* session
)
{
    Init();
    Session_ = session;
}

/*----------------------------------------------------------------------------*/
/*  Destructor  forpxArtDiscountInfo                                          */
/*----------------------------------------------------------------------------*/
pxArtDiscountInfo :: ~pxArtDiscountInfo
()
{
    if (Item_)    delete Item_;
    if (Order_)   delete Order_;
    pxGlobalNoDatabaseWrite = false;
}

/*----------------------------------------------------------------------------*/
/*  GetDiscountList                                                           */
/*----------------------------------------------------------------------------*/
pxDiscountList*
pxArtDiscountInfo :: GetDiscountList
(
    const short BranchNo,
    const long  CustomerNo,
    const long  ArticleNo,
    const PriceTypeEnum  pricetype,
    const long  Quantity
)
{
    if (!setCustomer(BranchNo, CustomerNo))
    {
        return NULL;
    }

    if (!setPseudoOrder() || !setOrderItem(ArticleNo, pricetype, Quantity))
    {
        return NULL;
    }
    return Item_->ArtDiscountList();
}

//----------------------------------------------------------------------------
//  Construct a discount-in-kind list containing all promotions (position and
//  range promotions) for displaying
//----------------------------------------------------------------------------
pxDiscountList* pxArtDiscountInfo :: GetPromotionList
(
    const short BranchNo,
    const long  CustomerNo,
    const long  ArticleNo,
    const PriceTypeEnum pricetype
)
{
    if (!setCustomer(BranchNo, CustomerNo))
    {
        return NULL;
    }

    if (!Customer_->CustomerGroupFlagsList()->IsKscDiscountEnabled())
        return NULL;

    tDiscountSpec discountspec = (HEALTHFUND_PRICE == pricetype) ? DiscSpec_HealthFund : DiscSpec_VoluntarySale;

    pxDiscountList *dlist = new pxDiscountList(Session_);
    dlist->Select(CASCADE_ALL_PROMOTIONS, BranchNo, ArticleNo, CustomerNo, 0L, static_cast<short>(discountspec));  // -> discount.cpp

    pxDiscountListIter cursor(*dlist); // cast away constness
    pxDiscount* curp;
    if (dlist->Entries() == 0)      // no entries found, go back to caller
    {
        delete dlist;
        return NULL;
    }

    curp = (pxDiscount*) ++cursor;
    while (curp)
    {
        if ((curp->GrossProfitPct() > pxConstants::dZero) && (curp->DiscountGrpNo() > 0))
        {
            // create a pro forma order to have an order item,
            // which is needed to calculate the discount pct out of the gross profit pct
            //pxDiscountList* dlist2 = NULL;   // prt discountlist

            if (!setPseudoOrder())
            {
                return NULL;
            }
            if (setOrderItem(ArticleNo, pricetype, curp->BaseQty()))
            {
                curp->DiscountValuePct(
                    Item_->CalcDiscountPercentage(curp->GrossProfitPct(), static_cast<short>(pxOrderItem::CascadeLevelRangePromotion), curp->BaseQty()));
            }
        }
        curp = (pxDiscount*) ++cursor;
    }

    return dlist;
}

/*----------------------------------------------------------------------------*/
/*  Init                                                                      */
/*----------------------------------------------------------------------------*/
void
pxArtDiscountInfo :: Init()
{
    Item_     = NULL;
    Order_    = NULL;
    Customer_ = NULL;
}

bool pxArtDiscountInfo::setCustomer(const short branchNo, const long customerNo)
{
    // BG Performance test code
    pxOrder* CurrentOrder = Session_->CurrentOrder();

    if  ( CurrentOrder )
    {
        Customer_ = CurrentOrder->Customer();
    }
    else
    {
        Customer_ = new pxCustBase(Session_, branchNo, customerNo);
    }
    return Customer_->IsGoodState();
}

bool pxArtDiscountInfo::setPseudoOrder()
{
	Order_ = new pxOrder(Session_, Customer_, pxOrder::INFO_ORDER_TYPE_DEFAULT);  // Pseudo-Auftragsnr., keine Buchung!
    return Order_->IsGoodState();
}

bool pxArtDiscountInfo::setOrderItem(const long articleNo, const PriceTypeEnum pricetype, const long quantity)
{
    Item_ = Order_->ItemDiscountInfo(articleNo, pricetype);
    Item_->MengeBestellt(quantity); // DEPricing
    if(Item_)
    {
        if (Order_->Param()->IsNewDiscount())
        {
            Item_->CalcDiscount(quantity);
//          dlist2 = Item_->ArtDiscountList();
        }
        return true;
    }
    return false;
}
