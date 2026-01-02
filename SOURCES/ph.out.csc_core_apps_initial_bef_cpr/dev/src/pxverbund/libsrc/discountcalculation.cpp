#include "pxrecord.h"
#include "pxdbxx.h"
#include "pxsess.hpp"
#include "pxdiscount.hpp"
#include "pxdiscountdef.h"
#include "pxbase/pxconstants.hpp"
#include <logger/loggerpool.h>

/*----------------------------------------------------------------------------*/
/*  Calculate and return the discount-in-kind quantity based upon the order   */
/*  quantity passed.                                                          */
/*----------------------------------------------------------------------------*/
long
pxDiscountList :: CalcDiscountNatra
(
    long          *orderq,       // quantity to be ordered
    short          Discounttype,
    double        *Discountkey,
    short         *DiscountBestBuy,
    long          *DiscountArticle,
    nMoney        *pRefundValue,
    short         *pPromotionNo,
    char          *pTurnOverCalcImpact,
    char          *pInternalDiscount,
    long          *pPromoBaseQty,
    double        *pRefundPct,
    long          *pCustomerNo,
    short         *pDiscountCalcFrom,
    short         *pDiscountApplyTo
)
{
    long          qdiscount = 0;       // calculated discount quantity
    pxDiscountListIter   cursor(*this); // define an iterator to scan the list

    switch (Discounttype)
    {
    case DiscType_Default:      // BaseQty > 0; DiscountQty > 0
        {
            *DiscountBestBuy =  BestBuy_NatraDefault;
            qdiscount = ComputeNatra(orderq, Discountkey, DiscountBestBuy, DiscountArticle, pRefundValue, pPromotionNo,
                                     pTurnOverCalcImpact, pInternalDiscount, pPromoBaseQty, pRefundPct, pCustomerNo,
                                     pDiscountCalcFrom, pDiscountApplyTo);
            break;
        }

    case DiscType_Team:
        {
            *DiscountBestBuy = BestBuy_NatraTeam;
            qdiscount = ComputeNatra(orderq, Discountkey, DiscountBestBuy, DiscountArticle, pRefundValue, pPromotionNo,
                                     pTurnOverCalcImpact, pInternalDiscount, pPromoBaseQty, pRefundPct, pCustomerNo,
                                     pDiscountCalcFrom, pDiscountApplyTo);
            break;
        }

    case DiscType_Diabetes:
        {
            *DiscountBestBuy = BestBuy_NatraDiabetes;
            qdiscount = ComputeNatra(orderq, Discountkey, DiscountBestBuy, DiscountArticle, pRefundValue, pPromotionNo,
                                     pTurnOverCalcImpact, pInternalDiscount, pPromoBaseQty, pRefundPct, pCustomerNo,
                                     pDiscountCalcFrom, pDiscountApplyTo);
            break;
        }
    }

    return qdiscount;
}

/*----------------------------------------------------------------------------*/
/*  Discount price list lookup. The list is scanned for all entries           */
/*  matching the discount term group passed. Within the matching entries,     */
/*  the discount price for a quantity being less than or equal to the order   */
/*  quantity is picked up and returned.                                       */
/*  If the order quantity is less than the lowest discount quantity within    */
/*  the discount term group, the order quantity is raised automatically to    */
/*  meet at least this condition. This is the reason for using a pointer to   */
/*  the order quantity rather than passing it by value. However, the caller   */
/*  might deny this feature by simply resetting the order quantity to its     */
/*  original value and then ignore the discount price returned.               */
/*----------------------------------------------------------------------------*/
nMoney
pxDiscountList :: CalcDiscountNetto
(
    long          *orderq,             // quantity to be ordered
    short          Discounttype,
    double        *Discountkey,
    short         *DiscountBestBuy,
    nMoney        *pRefundValue,
    short         *pPromotionNo,
    char          *pTurnOverCalcImpact,
    char          *pInternalDiscount,
    long          *pPromoBaseQty,
    double        *pRefundPct,
    long          *pCustomerNo
)
{
    nMoney         dprice(0.0);  // calculated discount price

    pxDiscountListIter   cursor(*this); // define an iterator to scan the list

    switch (Discounttype)
    {
    case DiscType_Default:      // BaseQty > 0; DiscountQty > 0
        {
            *DiscountBestBuy = BestBuy_FixedPriceDefault;
            dprice = ComputeNetto(orderq, Discountkey, DiscountBestBuy, pRefundValue, pPromotionNo, pTurnOverCalcImpact, pInternalDiscount, pPromoBaseQty, pRefundPct, pCustomerNo);
            break;
        }

    case DiscType_Team:
        {
            *DiscountBestBuy = BestBuy_FixedPriceTeam;
            dprice = ComputeNetto(orderq, Discountkey, DiscountBestBuy, pRefundValue, pPromotionNo, pTurnOverCalcImpact, pInternalDiscount, pPromoBaseQty, pRefundPct, pCustomerNo);
            break;
        }

    case DiscType_Diabetes:
        {
            *DiscountBestBuy = BestBuy_FixedPriceDiabetes;
            dprice = ComputeNetto(orderq, Discountkey, DiscountBestBuy, pRefundValue, pPromotionNo, pTurnOverCalcImpact, pInternalDiscount, pPromoBaseQty, pRefundPct, pCustomerNo);
            break;
        }
    case BestBuy_FixedPricePharmGroup:
        {
            *DiscountBestBuy = BestBuy_FixedPricePharmGroup;
            dprice = ComputeNetto(orderq, Discountkey, DiscountBestBuy, pRefundValue, pPromotionNo, pTurnOverCalcImpact, pInternalDiscount, pPromoBaseQty, pRefundPct, pCustomerNo);
            break;
        }
    case BestBuy_SpecialPrice:
        {
            *DiscountBestBuy = BestBuy_SpecialPrice;
            dprice = ComputeNetto(orderq, Discountkey, DiscountBestBuy, pRefundValue, pPromotionNo, pTurnOverCalcImpact, pInternalDiscount, pPromoBaseQty, pRefundPct, pCustomerNo);
            break;
        }

    default:
        {
            break;
        }
    }

    return dprice;
}

/*----------------------------------------------------------------------------*/
/*  CalcDiscountCash                                                          */
/*----------------------------------------------------------------------------*/
double
pxDiscountList :: CalcDiscountCash
(
    long          *orderq,             // quantity to be ordered
    short          Discounttype,
    double        *Discountkey,
    short         *DiscountBestBuy,
    nMoney        *pRefundValue,
    short         *pPromotionNo,
    char          *pTurnOverCalcImpact,
    char          *pInternalDiscount,
    long          *pPromoBaseQty,
    double        *pRefundPct,
    long          *pCustomerNo,
    short         *pDiscountCalcFrom,
    short         *pDiscountApplyTo
)
{
    double       DiscountValuePct = 0.0;  // Discountvalue percentage

    pxDiscountListIter   cursor(*this); // define an iterator to scan the list

    switch (Discounttype)
    {
    case DiscType_Default:              // Barrabatt;
        {
            *DiscountBestBuy = BestBuy_ValuePctCash;
            DiscountValuePct = ComputeCash( orderq, Discountkey, DiscountBestBuy, pRefundValue, pPromotionNo, pTurnOverCalcImpact, pInternalDiscount, pPromoBaseQty, pRefundPct, pCustomerNo, pDiscountCalcFrom, pDiscountApplyTo);
            break;
        }
    case DiscType_Shortrabatt:          // Shortrabatt
        {
            *DiscountBestBuy = BestBuy_ValuePctShort;
            DiscountValuePct = ComputeCash( orderq, Discountkey, DiscountBestBuy, pRefundValue, pPromotionNo, pTurnOverCalcImpact, pInternalDiscount, pPromoBaseQty, pRefundPct, pCustomerNo, pDiscountCalcFrom, pDiscountApplyTo);
            break;
        }
    case BestBuy_ValuePctShortLine:     // ShortLinerabatt
        {
            *DiscountBestBuy = BestBuy_ValuePctShortLine;
            DiscountValuePct = ComputeCash( orderq, Discountkey, DiscountBestBuy, pRefundValue, pPromotionNo, pTurnOverCalcImpact, pInternalDiscount, pPromoBaseQty, pRefundPct, pCustomerNo, pDiscountCalcFrom, pDiscountApplyTo);
            break;
        }
    case DiscType_Generika:             // Generika
        {
            *DiscountBestBuy = BestBuy_ValuePctGenerika;
            DiscountValuePct = ComputeCash( orderq, Discountkey, DiscountBestBuy, pRefundValue, pPromotionNo, pTurnOverCalcImpact, pInternalDiscount, pPromoBaseQty, pRefundPct, pCustomerNo, pDiscountCalcFrom, pDiscountApplyTo);
            break;
        }
    case DiscType_Partenariat:          // Partenariat
        {
            *DiscountBestBuy = BestBuy_ValuePctPartenariat;
            DiscountValuePct = ComputeCash( orderq, Discountkey, DiscountBestBuy, pRefundValue, pPromotionNo, pTurnOverCalcImpact, pInternalDiscount, pPromoBaseQty, pRefundPct, pCustomerNo, pDiscountCalcFrom, pDiscountApplyTo);
            break;
        }
    case BestBuy_ValuePctWholeSale:     // Whole
        {
            *DiscountBestBuy = BestBuy_ValuePctWholeSale;
            DiscountValuePct = ComputeCash( orderq, Discountkey, DiscountBestBuy, pRefundValue, pPromotionNo, pTurnOverCalcImpact, pInternalDiscount, pPromoBaseQty, pRefundPct, pCustomerNo, pDiscountCalcFrom, pDiscountApplyTo);
            break;
        }
    case BestBuy_ValuePctWholeSaleInd:  // Whole Industrie
        {
            *DiscountBestBuy = BestBuy_ValuePctWholeSaleInd;
            DiscountValuePct = ComputeCash( orderq, Discountkey, DiscountBestBuy, pRefundValue, pPromotionNo, pTurnOverCalcImpact, pInternalDiscount, pPromoBaseQty, pRefundPct, pCustomerNo, pDiscountCalcFrom, pDiscountApplyTo);
            break;
        }
    case BestBuy_ValuePctRetail:        // Retail
        {
            *DiscountBestBuy = BestBuy_ValuePctRetail;
            DiscountValuePct = ComputeCash( orderq, Discountkey, DiscountBestBuy, pRefundValue, pPromotionNo, pTurnOverCalcImpact, pInternalDiscount, pPromoBaseQty, pRefundPct, pCustomerNo, pDiscountCalcFrom, pDiscountApplyTo);
            break;
        }
    case BestBuy_ValuePctTena:          // Retail
        {
            *DiscountBestBuy = BestBuy_ValuePctTena;
            DiscountValuePct = ComputeCash( orderq, Discountkey, DiscountBestBuy, pRefundValue, pPromotionNo, pTurnOverCalcImpact, pInternalDiscount, pPromoBaseQty, pRefundPct, pCustomerNo, pDiscountCalcFrom, pDiscountApplyTo);
            break;
        }
    case BestBuy_LogisticAddition:      // Logistic Addition
        {
            *DiscountBestBuy = BestBuy_LogisticAddition;
            DiscountValuePct = ComputeLogAdd( orderq, Discountkey, DiscountBestBuy, pRefundValue, pPromotionNo, pTurnOverCalcImpact, pInternalDiscount, pPromoBaseQty, pRefundPct, pCustomerNo, pDiscountCalcFrom, pDiscountApplyTo);
            break;
        }
    case BestBuy_ValuePctPhoenixMagic:  // Phoenix Magic
        {
            *DiscountBestBuy = BestBuy_ValuePctPhoenixMagic;
            DiscountValuePct = ComputeCash( orderq, Discountkey, DiscountBestBuy, pRefundValue, pPromotionNo, pTurnOverCalcImpact, pInternalDiscount, pPromoBaseQty, pRefundPct, pCustomerNo, pDiscountCalcFrom, pDiscountApplyTo);
            break;
        }
    case BestBuy_ValuePctOverdrive:     // Overdrive
        {
            *DiscountBestBuy = BestBuy_ValuePctOverdrive;
            DiscountValuePct = ComputeCash( orderq, Discountkey, DiscountBestBuy, pRefundValue, pPromotionNo, pTurnOverCalcImpact, pInternalDiscount, pPromoBaseQty, pRefundPct, pCustomerNo, pDiscountCalcFrom, pDiscountApplyTo);
            break;
        }
    case BestBuy_ValuePctCashAssorted:   // assorted cash discount
        {
            *DiscountBestBuy = BestBuy_ValuePctCashAssorted;
            DiscountValuePct = ComputeCash(orderq, Discountkey, DiscountBestBuy, pRefundValue, pPromotionNo, pTurnOverCalcImpact, pInternalDiscount, pPromoBaseQty, pRefundPct, pCustomerNo, pDiscountCalcFrom, pDiscountApplyTo);
            break;
        }
    case BestBuy_LogisticDataTransfer:  // logistic addtion with data transfer
        {
            *DiscountBestBuy = BestBuy_LogisticDataTransfer;
            DiscountValuePct = ComputeLogAdd(orderq, Discountkey, DiscountBestBuy, pRefundValue, pPromotionNo, pTurnOverCalcImpact, pInternalDiscount, pPromoBaseQty, pRefundPct, pCustomerNo, pDiscountCalcFrom, pDiscountApplyTo);
            break;
        }

    default:
        {
            break;
        }
    }

    return DiscountValuePct;
}

/*----------------------------------------------------------------------------*/
/*  CalcGrossProfitPct                                                        */
/*----------------------------------------------------------------------------*/
double
pxDiscountList :: CalcGrossProfitPct
(
    long          *orderq,             // quantity to be ordered
    short          Discounttype,
    double        *Discountkey,
    short         *DiscountBestBuy,
    nMoney        *pRefundValue,
    short         *pPromotionNo,
    char          *pTurnOverCalcImpact,
    char          *pInternalDiscount,
    long          *pPromoBaseQty,
    double        *pRefundPct,
    long          *pCustomerNo
)
{
    double       GrossProfitPct = 0.0;  // Rohertrag percentage

    pxDiscountListIter   cursor(*this); // define an iterator to scan the list

    switch (Discounttype)
    {
    case BestBuy_GrossProfitPct:        // Rohertrag
        {
            *DiscountBestBuy = BestBuy_GrossProfitPct;
            GrossProfitPct = ComputeGrossProfitPct( orderq, Discountkey, DiscountBestBuy, pRefundValue, pPromotionNo, pTurnOverCalcImpact, pInternalDiscount, pPromoBaseQty, pRefundPct, pCustomerNo);
            break;
        }
    default:
        {
            break;
        }
    }

    return GrossProfitPct;
}

/*----------------------------------------------------------------------------*/
/*  CalcFixedDiscountValue                                                        */
/*----------------------------------------------------------------------------*/
double
pxDiscountList :: CalcFixedDiscountValue
(
    long          *orderq,             // quantity to be ordered
    short          Discounttype,
    double        *Discountkey,
    short         *DiscountBestBuy,
    nMoney        *pRefundValue,
    short         *pPromotionNo,
    char          *pTurnOverCalcImpact,
    char          *pInternalDiscount,
    long          *pPromoBaseQty,
    double        *pRefundPct,
    long          *pCustomerNo
)
{
    double       FixedDiscVal = 0.0;

    pxDiscountListIter   cursor(*this); // define an iterator to scan the list

    switch (Discounttype)
    {
    case BestBuy_FixedDiscountValue:        // Rohertrag
        {
            *DiscountBestBuy = BestBuy_FixedDiscountValue;
            FixedDiscVal = ComputeFixedDiscountValue( orderq, Discountkey, DiscountBestBuy, pRefundValue, pPromotionNo, pTurnOverCalcImpact, pInternalDiscount, pPromoBaseQty, pRefundPct, pCustomerNo);
            break;
        }
    default:
        {
            break;
        }
    }

    return FixedDiscVal;
}

/*----------------------------------------------------------------------------*/
/*  Calculate and return the discount-in-kind quantity based upon the order   */
/*  quantity passed.                                                          */
/*----------------------------------------------------------------------------*/
long
pxDiscountList :: ComputeNatra
(
    long          *orderq,       // quantity to be ordered
    double        *Discountkey,
    short         *DiscountBestBuy,
    long          *DiscountArticle,
    nMoney        *pRefundValue,
    short         *pPromotionNo,
    char          *pTurnOverCalcImpact,
    char          *pInternalDiscount,
    long          *pPromoBaseQty,
    double        *pRefundPct,
    long          *pCustomerNo,
    short         *pDiscountCalcFrom,
    short         *pDiscountApplyTo
)
{
    // avoid "unused" compiler warning
    { DiscountBestBuy = DiscountBestBuy; }

    pxDiscount    *dikp;               // ptr to a discount list entry
    long          q = *orderq;         // actual quantity to be calc'ed upon
    long          qdiscount = 0;       // calculated discount quantity
    pxDiscountListIter  cursor(*this); // define an iterator to scan the list

/*----------------------------------------------------------------------------*/
/*  Look at the first matching entry in the discount list. If the order       */
/*  quantity is less than the base quantity in that entry, the order quantity */
/*  is raised automatically to meet at least this condition. This is the      */
/*  reason for using a pointer to the order quantity rather than passing it   */
/*  by value. However, the caller might deny this feature by simply resetting */
/*  the order quantity to its old value and then ignore the discount-in-kind  */
/*  quantity returned.                                                        */
/*----------------------------------------------------------------------------*/
    while ( (dikp = (pxDiscount*) ++cursor) != NULL )
    {
        //if ( *DiscountBestBuy == dikp->BestBuy_ )
        if ( dikp->DiscountQty_ > 0)
        {                                // this is the first matching entry
            if ( q < dikp->BaseQty_ )
            {                             // then raise order quantity
                *orderq = q = dikp->BaseQty_;
            }
            break;
        }
    }
/*----------------------------------------------------------------------------*/
/*  Now scan the list in a backward direction and calculate the discount-in-  */
/*  kind quantity.                                                            */
/*----------------------------------------------------------------------------*/
    for (cursor.ToLast(); ( (dikp = (pxDiscount*) cursor.Current()) != NULL ) && (q > 0); --cursor )
    {
        if ( dikp->DiscountQty_ > 0)
        {
            while ( q >= dikp->BaseQty_ )
            {                                // as long as this entry fits:
                qdiscount        += dikp->DiscountQty_;
                if ( dikp->IsNonProportional() )
                {
                    *Discountkey     = dikp->RefundPct_;
                    *DiscountArticle = dikp->DiscountArticle_;
                    PharmacyGroupId_ = dikp->PharmacyGroupId_;
                    *pPromoBaseQty   = dikp->BaseQty_;
                    q                = 0;
                    break;
                }
                q                   -= dikp->BaseQty_;
                *Discountkey         = dikp->RefundPct_;
                *DiscountArticle     = dikp->DiscountArticle_;
                 PharmacyGroupId_    = dikp->PharmacyGroupId_;
                *pRefundValue        = dikp->RefundValue_;
                *pPromotionNo        = dikp->PromotionNo_;
                *pTurnOverCalcImpact = dikp->TurnOverCalcImpact_;
                *pInternalDiscount   = dikp->InternalDiscount_;
                *pPromoBaseQty       = dikp->BaseQty_;
                *pRefundPct          = dikp->RefundPct_;
                *pCustomerNo         = dikp->CustomerNo_;
                *pDiscountCalcFrom   = dikp->DiscountCalcFrom_;
                *pDiscountApplyTo    = dikp->DiscountApplyTo_;

            }
        }
    }

#ifdef CHDISCLOG
    std::stringstream v;
    v << "pxDiscountList::ComputeNatra - Value Natra qdiscount = " << qdiscount;
    BLOG_DEBUG(libcsc::LoggerPool::getLoggerDiscountCalc(), v.str());
#endif  

    return qdiscount;
}

/*----------------------------------------------------------------------------*/
/*  Compute and return the fixedprice based upon the order quantity passed    */
/*----------------------------------------------------------------------------*/
nMoney
pxDiscountList :: ComputeNetto
(
    long          *orderq,             // quantity to be ordered
    double        *Discountkey,
    short         *DiscountBestBuy,
    nMoney        *pRefundValue,
    short         *pPromotionNo,
    char          *pTurnOverCalcImpact,
    char          *pInternalDiscount,
    long          *pPromoBaseQty,
    double        *pRefundPct,
    long          *pCustomerNo
)
{
    // avoid "unused" compiler warning
    { DiscountBestBuy = DiscountBestBuy; }

    pxDiscount  *disp;                 // ptr to a discount list entry
    long        q = *orderq;           // actual quantity to be calc'ed upon
    nMoney      dprice(0.0);           // calculated discount price

    pxDiscountListIter   cursor(*this);   // define an iterator to scan the list
    while ( (disp = (pxDiscount*) ++cursor) != NULL )
    {
        //if ( *DiscountBestBuy == disp->BestBuy_)
        if ( disp->FixedPrice_ > pxConstants::mZero )
        {                                   // this is a matching entry
            if ( q < disp->BaseQty_ )       // q does not fit
            {
                if ( !dprice )               // then no discount price found until now,
                {                            // so it must be the 1. matching entry
                    *orderq = q = disp->BaseQty_;    // raise order quantity
                    //+++Bea: Frage an Ysi: Ist der Rest dieser if-Schleife nicht überflüssig, wenn break weggelassen wird?
                    dprice  = disp->FixedPrice_;    // to meet this condition
                    *Discountkey  = disp->RefundPct_;
                    PharmacyGroupId_ = disp->PharmacyGroupId_;
                    *pRefundValue    = disp->RefundValue_;
                    *pPromotionNo    = disp->PromotionNo_;
                    *pTurnOverCalcImpact = disp->TurnOverCalcImpact_;
                    *pInternalDiscount = disp->InternalDiscount_;
                    *pPromoBaseQty   = disp->BaseQty_;
                    *pRefundPct      = disp->RefundPct_;
                    *pCustomerNo     = disp->CustomerNo_;
                }
                break;
            }
            if ( q >= disp->BaseQty_ )      // then q fits, store price
            {
                if ( dprice )
                {
                    if ( dprice < disp->FixedPrice_ )   // Attention: the less the FixedPrice_, the more the discount for the customer
                    {
                        continue;
                    }
                }
                dprice = disp->FixedPrice_;
                *Discountkey  = disp->RefundPct_;
                PharmacyGroupId_ = disp->PharmacyGroupId_;
                *pRefundValue    = disp->RefundValue_;
                *pPromotionNo    = disp->PromotionNo_;
                *pTurnOverCalcImpact = disp->TurnOverCalcImpact_;
                *pInternalDiscount = disp->InternalDiscount_;
                *pPromoBaseQty   = disp->BaseQty_;
                *pRefundPct      = disp->RefundPct_;
                *pCustomerNo     = disp->CustomerNo_;
            }
        }
    }
    return dprice;
}

/*----------------------------------------------------------------------------*/
/*  ComputeCash                                                               */
/*----------------------------------------------------------------------------*/
double
pxDiscountList :: ComputeCash
(
    long          *orderq,             // quantity to be ordered
    double        *Discountkey,
    short         *DiscountBestBuy,
    nMoney        *pRefundValue,
    short         *pPromotionNo,
    char          *pTurnOverCalcImpact,
    char          *pInternalDiscount,
    long          *pPromoBaseQty,
    double        *pRefundPct,
    long          *pCustomerNo,
    short         *pDiscountCalcFrom,
    short         *pDiscountApplyTo
)
{
    pxDiscount  *disp;                   // ptr to a discount list entry
    long        q = *orderq;             // actual quantity to be calc'ed upon
    double      DiscountValuePct = 0.0;  // Discountvalue percentage

    pxDiscountListIter cursor(*this);     // define an iterator to scan the list

#ifdef CHDISCLOG
    std::stringstream u;
    u << "pxDiscountList::ComputeCash - Start with quantity = " << q;
    BLOG_DEBUG(libcsc::LoggerPool::getLoggerDiscountCalc(), u.str());
#endif

    while ( (disp = (pxDiscount*) ++cursor) != NULL )
    {
#ifdef CHDISCLOG
        std::stringstream v;
        v << "pxDiscountList::ComputeCash - Verify Discount disp->BaseQty_ = " << disp->BaseQty_ << " with disp->DiscountValuePct_ = " << disp->DiscountValuePct_;
        BLOG_DEBUG(libcsc::LoggerPool::getLoggerDiscountCalc(), v.str());
#endif
//      if ( *DiscountBestBuy == disp->BestBuy_ )
//      {                                     // this is a matching entry

        if ( q < disp->BaseQty_ )          // q does not fit
        {
#ifdef CHDISCLOG
            std::stringstream w;
            w << "pxDiscountList::ComputeCash - Remove Discount because of q = " << q << "< disp->BaseQty_ = " << disp->BaseQty_;
            BLOG_DEBUG(libcsc::LoggerPool::getLoggerDiscountCalc(), w.str());
#endif
            if ( !DiscountValuePct )        // then no discount percentage found until now,
            {                               // so it must be the 1. matching entry
                *orderq = q       = disp->BaseQty_;           // raise order quantity
                DiscountValuePct  = disp->DiscountValuePct_; // to meet this condition
                *Discountkey  = disp->RefundPct_;
                PharmacyGroupId_ = disp->PharmacyGroupId_;
                PaymentTargetNo_ = disp->PaymentTargetNo_;
                *pRefundValue = disp->RefundValue_;
                *pPromotionNo = disp->PromotionNo_;
                *pTurnOverCalcImpact = disp->TurnOverCalcImpact_;
                *pInternalDiscount = disp->InternalDiscount_;
                *pPromoBaseQty   = disp->BaseQty_;
                *DiscountBestBuy = disp->ConvertDiscountSpecToBestBuy(*DiscountBestBuy);
                *pRefundPct = disp->RefundPct_;
                *pCustomerNo = disp->CustomerNo_;
                *pDiscountCalcFrom = disp->DiscountCalcFrom_;
                *pDiscountApplyTo = disp->DiscountApplyTo_;
            }
            break;
        }

        if ( q >= disp->BaseQty_ )         // then q fits, store price
        {
#ifdef CHDISCLOG
            std::stringstream w;
            w << "pxDiscountList::ComputeCash - Verify Discount " << disp->DiscountValuePct_ << "% because q = " << q << " >= disp->BaseQty_ = " << disp->BaseQty_;
#endif
            if ( DiscountValuePct <= disp->DiscountValuePct_)  // should be executed, if DiscountValuePct=0.0!
            {
                DiscountValuePct = disp->DiscountValuePct_;
                *Discountkey  = disp->RefundPct_;
                PharmacyGroupId_ = disp->PharmacyGroupId_;
                PaymentTargetNo_ = disp->PaymentTargetNo_;
                *pRefundValue = disp->RefundValue_;
                *pPromotionNo = disp->PromotionNo_;
                *pTurnOverCalcImpact = disp->TurnOverCalcImpact_;
                *pInternalDiscount = disp->InternalDiscount_;
                *pPromoBaseQty   = disp->BaseQty_;
                *DiscountBestBuy = disp->ConvertDiscountSpecToBestBuy(*DiscountBestBuy);
                *pRefundPct = disp->RefundPct_;
                *pCustomerNo = disp->CustomerNo_;
                *pDiscountCalcFrom = disp->DiscountCalcFrom_;
                *pDiscountApplyTo = disp->DiscountApplyTo_;
#ifdef CHDISCLOG
                w << "pxDiscountList::ComputeCash - Condition fulfilled!" << " New value for DiscountValuePct = " << DiscountValuePct << "%" <<std::endl;
#endif
            }
#ifdef CHDISCLOG
            else
            {
                w << "pxDiscountList::ComputeCash - Condition not fulfilled!" << " Keep value for DiscountValuePct = " << DiscountValuePct << "%" <<std::endl;
            }

            BLOG_DEBUG(libcsc::LoggerPool::getLoggerDiscountCalc(), w.str());
#endif
        }
    }

#ifdef CHDISCLOG
    std::stringstream v;
    v << "pxDiscountList::ComputeCash - Biggest value for DiscountValuePct = " << DiscountValuePct << "%";
    BLOG_DEBUG(libcsc::LoggerPool::getLoggerDiscountCalc(), v.str());
#endif

    return DiscountValuePct;
}

//----------------------------------------------------------------------------
//  ComputeGrossProfitPct
//  Returns: the most appropriate entry from discount list
//
//----------------------------------------------------------------------------
double
pxDiscountList :: ComputeGrossProfitPct
(
    long          *orderq,             // quantity to be ordered
    double        *Discountkey,
    short         *DiscountBestBuy,
    nMoney        *pRefundValue,
    short         *pPromotionNo,
    char          *pTurnOverCalcImpact,
    char          *pInternalDiscount,
    long          *pPromoBaseQty,
    double        *pRefundPct,
    long          *pCustomerNo
)
{
    // avoid "unused" compiler warning
    { DiscountBestBuy = DiscountBestBuy; }

    pxDiscount   *disp;           // ptr to a discount list entry
    long         q = *orderq;     // actual quantity to be calc'ed upon
    double       GrossProfitPct;  // Discountvalue percentage

    GrossProfitPct = pxConstants::dZero;
    pxDiscountListIter cursor(*this);      // define an iterator to scan the list

    while ( (disp = (pxDiscount*) ++cursor) != NULL )
    {
        // if ( *DiscountBestBuy == disp->BestBuy_ ) //nochmal Abfrage auf GrossProfitPct
        if ( disp->GrossProfitPct_ > 0.0  )          //nochmal Abfrage auf GrossProfitPct
        {                                     // this is a matching entry
            if ( q < disp->BaseQty_ )          // q does not fit
            {
                if ( !GrossProfitPct )        // then no discount percentage found until now,
                {                               // so it must be the 1. matching entry
                    *orderq = q       = disp->BaseQty_;           // raise order quantity
                    GrossProfitPct  = disp->GrossProfitPct_; // to meet this condition
                    *Discountkey  = disp->RefundPct_;
                    PharmacyGroupId_ = disp->PharmacyGroupId_;
                    *pRefundValue = disp->RefundValue_;
                    *pPromotionNo = disp->PromotionNo_;
                    *pTurnOverCalcImpact = disp->TurnOverCalcImpact_;
                    *pInternalDiscount = disp->InternalDiscount_;
                    *pPromoBaseQty   = disp->BaseQty_;
                    *pRefundPct = disp->RefundPct_;
                    *pCustomerNo = disp->CustomerNo_;
                }
                break;
            }
            if ( q >= disp->BaseQty_ )         // then q fits, store price
            {
                if ( GrossProfitPct <= pxConstants::dZero || disp->GrossProfitPct_ < GrossProfitPct)  // Attention: the less the GrossProfit, the more the discount for the customer
                {
                    GrossProfitPct = disp->GrossProfitPct_;
                    *Discountkey  = disp->RefundPct_;
                    PharmacyGroupId_ = disp->PharmacyGroupId_;
                    *pRefundValue = disp->RefundValue_;
                    *pPromotionNo = disp->PromotionNo_;
                    *pTurnOverCalcImpact = disp->TurnOverCalcImpact_;
                    *pInternalDiscount = disp->InternalDiscount_;
                    *pPromoBaseQty   = disp->BaseQty_;
                    *pRefundPct = disp->RefundPct_;
                    *pCustomerNo = disp->CustomerNo_;
                }
            }
        }
    }
    return GrossProfitPct;
}

//----------------------------------------------------------------------------
//  ComputeFixedDiscountValue
//  Returns: the most appropriate entry from discount list
//
//----------------------------------------------------------------------------
double
pxDiscountList :: ComputeFixedDiscountValue
(
    long          *orderq,             // quantity to be ordered
    double        *Discountkey,
    short         *DiscountBestBuy,
    nMoney        *pRefundValue,
    short         *pPromotionNo,
    char          *pTurnOverCalcImpact,
    char          *pInternalDiscount,
    long          *pPromoBaseQty,
    double        *pRefundPct,
    long          *pCustomerNo
)
{
    // avoid "unused" compiler warning
    { DiscountBestBuy = DiscountBestBuy; }

    pxDiscount   *disp;           // ptr to a discount list entry
    long         q = *orderq;     // actual quantity to be calc'ed upon
    double       FixedDiscVal;      // Discountvalue

    FixedDiscVal = pxConstants::dZero;

    pxDiscountListIter cursor(*this);      // define an iterator to scan the list

    while ( (disp = (pxDiscount*) ++cursor) != NULL )
    {
        if ( disp->FixedDiscountValue_ > 0.0  )          //nochmal Abfrage auf GrossProfitPct
        {                                     // this is a matching entry
            if ( q < disp->BaseQty_ )          // q does not fit
            {
                if ( !FixedDiscVal )        // then no discount percentage found until now,
                {                               // so it must be the 1. matching entry
                    *orderq = q       = disp->BaseQty_;           // raise order quantity
                    FixedDiscVal  = disp->FixedDiscountValue_; // to meet this condition
                    *Discountkey  = disp->RefundPct_;
                    PharmacyGroupId_ = disp->PharmacyGroupId_;
                    *pRefundValue = disp->RefundValue_;
                    *pPromotionNo = disp->PromotionNo_;
                    *pTurnOverCalcImpact = disp->TurnOverCalcImpact_;
                    *pInternalDiscount = disp->InternalDiscount_;
                    *pPromoBaseQty   = disp->BaseQty_;
                    *pRefundPct = disp->RefundPct_;
                    *pCustomerNo = disp->CustomerNo_;
                }
                break;
            }
            if ( q >= disp->BaseQty_ )         // then q fits, store price
            {
                if ( FixedDiscVal <= pxConstants::dZero || disp->FixedDiscountValue_ > FixedDiscVal)
                {
                    FixedDiscVal = disp->FixedDiscountValue_;
                    *Discountkey  = disp->RefundPct_;
                    PharmacyGroupId_ = disp->PharmacyGroupId_;
                    *pRefundValue = disp->RefundValue_;
                    *pPromotionNo = disp->PromotionNo_;
                    *pTurnOverCalcImpact = disp->TurnOverCalcImpact_;
                    *pInternalDiscount = disp->InternalDiscount_;
                    *pPromoBaseQty   = disp->BaseQty_;
                    *pRefundPct = disp->RefundPct_;
                    *pCustomerNo = disp->CustomerNo_;
                }
            }
        }
    }

    return FixedDiscVal;
}

/*----------------------------------------------------------------------------*/
/*  ComputeLogAdd = LogisticAddition                                          */
/*----------------------------------------------------------------------------*/
double
pxDiscountList :: ComputeLogAdd
(
    long         *orderq,             // quantity to be ordered
    double       *Discountkey,
    short        *DiscountBestBuy,
    nMoney       *pRefundValue,
    short        *pPromotionNo,
    char         *pTurnOverCalcImpact,
    char         *pInternalDiscount,
    long         *pPromoBaseQty,
    double       *pRefundPct,
    long         *pCustomerNo,
    short         *pDiscountCalcFrom,
    short         *pDiscountApplyTo
)
{
    pxDiscount  *disp;          // ptr to a discount list entry
    long        q = *orderq;    // actual quantity to be calc'ed upon
    double SurchargePct = 0.0;  // Discountvalue percentage (Zuschlag)
    bool entryFound = false;

    pxDiscountListIter cursor(*this);      // define an iterator to scan the list

#ifdef CHDISCLOG
    std::stringstream u;
    u << "pxDiscountList::ComputeLogAdd - Start with quantity = " << q;
    BLOG_DEBUG(libcsc::LoggerPool::getLoggerDiscountCalc(), u.str());
#endif

    while ( (disp = (pxDiscount*) ++cursor) != NULL )
    {
        if ( *DiscountBestBuy == disp->BestBuy_ )
        {                                      // this is a matching entry
            if ( q < disp->BaseQty_ )          // q does not fit
            {
                if ( !SurchargePct )            // then no discount percentage found until now,
                {                               // so it must be the 1. matching entry
                    if (entryFound)
                    {
                        break;
                    }
                    *orderq = q  = disp->BaseQty_;                 // raise order quantity
                    SurchargePct = disp->SurchargePct_;            // to meet this condition
                    *Discountkey = disp->RefundPct_;               // Vergütung(Bonus)
                    PharmacyGroupId_ = disp->PharmacyGroupId_;
                    *pRefundValue = disp->RefundValue_;
                    *pPromotionNo = disp->PromotionNo_;
                    *pTurnOverCalcImpact = disp->TurnOverCalcImpact_;
                    *pInternalDiscount = disp->InternalDiscount_;
                    *pPromoBaseQty   = disp->BaseQty_;
                    *pRefundPct = disp->RefundPct_;
                    *pCustomerNo = disp->CustomerNo_;
                    *pDiscountCalcFrom = disp->DiscountCalcFrom_;
                    *pDiscountApplyTo = disp->DiscountApplyTo_;
                }
                break;
            }
            if ( q >= disp->BaseQty_ )         // then q fits, store price
            {
                SurchargePct = disp->SurchargePct_;  //Zuschlag
                *Discountkey  = disp->RefundPct_;
                PharmacyGroupId_ = disp->PharmacyGroupId_;
                *pRefundValue = disp->RefundValue_;
                *pPromotionNo = disp->PromotionNo_;
                *pTurnOverCalcImpact = disp->TurnOverCalcImpact_;
                *pInternalDiscount = disp->InternalDiscount_;
                *pPromoBaseQty   = disp->BaseQty_;
                *pRefundPct = disp->RefundPct_;
                *pCustomerNo = disp->CustomerNo_;
                *pDiscountCalcFrom = disp->DiscountCalcFrom_;
                *pDiscountApplyTo = disp->DiscountApplyTo_;

                entryFound = true;
            }
        }
    }

#ifdef CHDISCLOG
    std::stringstream v;
    v << "pxDiscountList::ComputeLogAdd - Smallest value for SurchargePct = " << SurchargePct << "%";
    BLOG_DEBUG(libcsc::LoggerPool::getLoggerDiscountCalc(), v.str());
#endif
    return SurchargePct;
}
