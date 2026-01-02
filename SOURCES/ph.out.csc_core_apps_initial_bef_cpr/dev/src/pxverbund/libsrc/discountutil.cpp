#include "pxrecord.h"
#include "pxdbxx.h"
#include "pxsess.hpp"
#include "pxitem.hpp"
#include "pxorder.hpp"
#include "pxcustomerflags.hpp"
#include "pxcstot.hpp"
#include "pxdiscount.hpp"
#include "pxdiscountdef.h"
#include "pxcstbas.hpp"
#include "pxbase/pxconstants.hpp"

//----------------------------------------------------------------------------
//  Get refundvalue, if there is any
//  Return 0, otherwise
//----------------------------------------------------------------------------
nMoney
pxDiscountList :: GetRefundValue()
{
    pxDiscountListIter cursor(*this); // define an iterator to read first list element
    pxDiscount *dikp;                 // ptr to a discount list entry
    dikp = (pxDiscount*) ++cursor;
    if(!dikp)
    {
        return (nMoney)0; //Error
    }
    return dikp->RefundValue_;
}

//----------------------------------------------------------------------------
//  Get promotion_no , if there is any
//  Return 0, otherwise
//----------------------------------------------------------------------------
short
pxDiscountList :: GetPromotionNo()
{
    pxDiscountListIter cursor(*this); // define an iterator to read first list element
    pxDiscount *dikp;                 // ptr to a discount list entry
    dikp = (pxDiscount*) ++cursor;
    if(!dikp)
    {
        return (short)0; //Error
    }
    return dikp->PromotionNo_;
}

/*----------------------------------------------------------------------------*/
/*  CheckList: for easier work, we look at every entry of the list to         */
/*  determine what kind of entry it is.                                       */
/*----------------------------------------------------------------------------*/
int
pxDiscountList :: CheckList
(
    pxOrderItem* item
)
{
    pxDiscountListIter  iter(*this);
    pxDiscount*         dikp;
    const pxCustOrderType& ot = item->Order().OrderType();

    pxCustBase&            customer = *(item->Order().Customer());
//    pxCustTermGroup       *tgp      = NULL;
    LogAddSpecials( item);        // special for france
    SpecialPrice( item);          // special for croatia
    ArtComPackMembers(item);      // special for ArtComPackMembers

    while ( (dikp = (pxDiscount*) ++iter) != NULL )
    {
        if ( dikp->IsMonthlyDiscount() )
        {
            delete iter.Remove();
            continue;
        }
        // FixedPricePaymentterms fixed price for serbian paymentterms
        if ( item->Order().Serbia() )
        {
            if(dikp->DiscountType_ == DiscType_Default && dikp->BaseQty_ > 0 && dikp->PaymentTargetNo_ > 0 &&
               dikp->FixedPrice_ != pxConstants::mZero && dikp->DiscountValuePct_ != pxConstants::dZero)
            {
                item->SetFixedPricePaymentterms(dikp->FixedPrice_);
            }
        }
        // Natra Default
        if (   dikp->DiscountType_ == DiscType_Default
            && (dikp->BaseQty_  > 0 || dikp->BaseValue_ > 0)
            && dikp->DiscountQty_ > 0 )
        {
            // maybe just for special Customer
            if ( dikp->CustomerNo_ > 0 )
            {
                if ( dikp->CustomerNo_ == customer.KundenNr() )
                {
                    dikp->BestBuy_ = BestBuy_NatraDefault;
                    SetKindOffRebate( NatraDefault);                      // Mark List
                }
                else
                {
                    delete iter.Remove();
                    continue;
                }
            }
            else
            {
                dikp->BestBuy_ = BestBuy_NatraDefault;
                SetKindOffRebate( NatraDefault);                      // Mark List
            }
        }

        // Natra Team = Aktionsservice  (SchwerPunkt3)
        if ( dikp->DiscountType_ == DiscType_Team &&
             dikp->BaseQty_  > 0 && dikp->DiscountQty_ > 0 )
        {
            //tgp = customer.FindTermGroup(dikp->DiscountType_);
            //if (tgp)
            //{
                dikp->BestBuy_  = BestBuy_NatraTeam;
                SetKindOffRebate(NatraTeam);
            //}                                        // Mark List
            //else
            //{
            //    delete iter.Remove();
            //    continue;
            //}
        }

        // Natra Diabetes  (SchwerPunkt5)
        if ( dikp->DiscountType_ == DiscType_Diabetes &&
             dikp->BaseQty_ > 0 && dikp->DiscountQty_ > 0 )
        {
            //tgp = customer.FindTermGroup(dikp->DiscountType_);
            //if (tgp)
            //{
                dikp->BestBuy_  = BestBuy_NatraDiabetes;
                SetKindOffRebate(NatraDiabetes);                   // Mark List
            //}
            //else
            //{
            //    delete iter.Remove();
            //    continue;
            //}
        }

        // Netto Default and special Customer Service
        if ( dikp->DiscountType_ == DiscType_Default &&
             dikp->FixedPrice_ != pxConstants::mZero && dikp->BaseQty_  > 0 &&
             ot.IsCalcNetPrice() )
        {
            // maybe just for special Customer
            if ( dikp->CustomerNo_ > 0 )
            {
                if ( dikp->CustomerNo_ == customer.KundenNr() )
                {
                    dikp->BestBuy_   = BestBuy_FixedPriceDefault;
                    SetKindOffRebate(FixedPriceDefault);       // Mark List
                }
                else
                {
                    delete iter.Remove();
                    continue;
                }
            }
            else
            {
                dikp->BestBuy_   = BestBuy_FixedPriceDefault;
                SetKindOffRebate(FixedPriceDefault);       // Mark List
            }
        }

        // Netto Team = Aktionsservice  (SchwerPunkt3)
        if ( dikp->DiscountType_ == DiscType_Team &&
             dikp->FixedPrice_ != pxConstants::mZero && dikp->BaseQty_ > 0 &&
             ot.IsCalcNetPrice())
        {
            //tgp = customer.FindTermGroup(dikp->DiscountType_);
            //if (tgp)
            //{
                dikp->BestBuy_   = BestBuy_FixedPriceTeam;
                SetKindOffRebate(FixedPriceTeam);                  // Mark List
            //}
            //else
            //{
            //    delete iter.Remove();
            //    continue;
            //}
        }

        // Netto Diabetes  (SchwerPunkt5)
        if ( dikp->DiscountType_ == DiscType_Diabetes &&
             dikp->FixedPrice_ != pxConstants::mZero && dikp->BaseQty_ > 0 &&
             ot.IsCalcNetPrice() )
        {
            //tgp = customer.FindTermGroup(dikp->DiscountType_);
            //if (tgp)
            //{
                dikp->BestBuy_   = BestBuy_FixedPriceDiabetes;
                SetKindOffRebate(FixedPriceDiabetes);              // Mark List
            //}
            //else
            //{
            //    delete iter.Remove();
            //    continue;
            //}
        }

        // Netto Default and special Customer Service
        if ( dikp->DiscountType_ == DiscType_Default &&
             dikp->FixedPrice_ != pxConstants::mZero && dikp->BaseQty_ > 0 &&
             item->Order().Serbia() )
        {
            dikp->BestBuy_ = BestBuy_FixedPriceDefault;
            SetKindOffRebate(FixedPriceDefault);       // Mark List
        }

        // Barrabatt Default
        if ( dikp->DiscountType_  == DiscType_Default &&
             dikp->DiscountValuePct_ > 0 && dikp->BaseQty_  > 0 &&
             (dikp->DiscountSpec() == 0 || dikp->DiscountSpec() == DiscSpec_Occasions || dikp->DiscountSpec() == DiscSpec_VoluntarySale || dikp->DiscountSpec() == DiscSpec_HealthFund) &&
             dikp->CustomerNo_ == 0)
        {
            // Special just for Swiss application
            if ( item->Order().Swiss() )
            {
                // No Barrabatt for Ordertype ZT,DI,ID,DT,SO
                if ( ot.IsTimeOrdered() || ot.IsScheduleOrder() || ot.IsIndustrieDispo() || ot.IsDispoTransfer() || ot.IsSpecial() )
                {
                    delete iter.Remove();
                    continue;
                }
            }
            if ((item->Order().Swiss()) && (dikp->DiscountGrpNo_ > 0))
            {
                dikp->BestBuy_ = BestBuy_ValuePctCashAssorted;
                SetKindOffRebate(ValuePctCashAssorted);
            }
            else
            {
            dikp->BestBuy_ = BestBuy_ValuePctCash;
            SetKindOffRebate(ValuePctCash);                      // Mark List
        }
        }

        // Rabatt Short Business
        if ( dikp->DiscountType_ == DiscType_Shortrabatt )
        {
            if (ot.IsShortBusiness() && dikp->DiscountValuePct_ > 0 && dikp->BaseQty_ > 0 )
            {
                dikp->BestBuy_ = BestBuy_ValuePctShort;
                SetKindOffRebate(ValuePctShort);                   // MarkList
            }
            else
            if ( ot.IsShortBusiness() && dikp->FixedPrice_ != pxConstants::mZero && dikp->BaseQty_ > 0 && ot.IsCalcNetPrice())
            {
                dikp->BestBuy_ = BestBuy_FixedPriceDefault;
                SetKindOffRebate(FixedPriceDefault);       // Mark List
            }
            else
            if ( ot.IsShortBusiness() && dikp->BaseQty_ > 0 && dikp->DiscountQty_ > 0 )
            {
                dikp->BestBuy_ = BestBuy_NatraDefault;
                SetKindOffRebate(NatraDefault);                      // Mark List
            }
            else
            {
                delete iter.Remove();
                continue;
            }
        }
        // Rabatt Short Line Business
        if ( dikp->DiscountType_ == DiscType_ShortLine )
        {
            if (ot.IsShortLineBusiness() && dikp->DiscountValuePct_ > 0 && dikp->BaseQty_ > 0 )
            {
                dikp->BestBuy_ = BestBuy_ValuePctShortLine;
                SetKindOffRebate(ValuePctShortLine);                   // MarkList
            }
            else
            if ( ot.IsShortLineBusiness() && dikp->FixedPrice_ != pxConstants::mZero && dikp->BaseQty_ > 0 && ot.IsCalcNetPrice())
            {
                dikp->BestBuy_ = BestBuy_FixedPriceDefault;
                SetKindOffRebate(FixedPriceDefault);       // Mark List
            }
            else
            if ( ot.IsShortLineBusiness() && dikp->BaseQty_ > 0 && dikp->DiscountQty_ > 0 )
            {
                dikp->BestBuy_ = BestBuy_NatraDefault;
                SetKindOffRebate(NatraDefault);                      // Mark List
            }
            else
            if ( ot.IsShortLineBusiness() && dikp->BaseQty_ > 0 && dikp->FixedDiscountValue_ > 0 )
            {
                dikp->BestBuy_ = BestBuy_FixedDiscountValue;
                SetKindOffRebate(FixedDiscountValue);                      // Mark List
            }
            else
            {
                delete iter.Remove();
                continue;
            }
        }

        // Rabatt GE
        if ( dikp->DiscountType_ == DiscType_Generika && ot.IsGenerika())
        {
            if (dikp->DiscountValuePct_ > 0 && dikp->BaseQty_ > 0 )
            {
                dikp->BestBuy_ = BestBuy_ValuePctGenerika;
                SetKindOffRebate(ValuePctGenerika);                // Mark List
            }
            else
            if ( dikp->FixedPrice_ != pxConstants::mZero && dikp->BaseQty_  > 0 && ot.IsCalcNetPrice())
            {
                dikp->BestBuy_ = BestBuy_FixedPriceDefault;
                SetKindOffRebate(FixedPriceDefault);       // Mark List
            }
            else
            if (dikp->BaseQty_ > 0 && dikp->DiscountQty_ > 0 )
            {
                dikp->BestBuy_ = BestBuy_NatraDefault;
                SetKindOffRebate(NatraDefault);                      // Mark List
            }
            else
            {
                delete iter.Remove();
                continue;
            }
        }

        // Rabatt PM
        if (dikp->DiscountType_ == DiscType_PhoenixMagic)
        {
            if ( ot.IsPhoenixMagic() && dikp->DiscountValuePct_ > 0 && dikp->BaseQty_ > 0 )
            {
                dikp->BestBuy_ = BestBuy_ValuePctPhoenixMagic;
                SetKindOffRebate(ValuePctPhoenixMagic);      // Mark List
            }
            else
            if ( ot.IsPhoenixMagic() && dikp->FixedPrice_ != pxConstants::mZero && dikp->BaseQty_ > 0 )
            {
                dikp->BestBuy_ = BestBuy_FixedPriceDefault;
                SetKindOffRebate(FixedPriceDefault);       // Mark List
            }
            else
            if ( ot.IsPhoenixMagic() && dikp->BaseQty_ > 0 && dikp->DiscountQty_ > 0 )
            {
                dikp->BestBuy_ = BestBuy_NatraDefault;
                SetKindOffRebate(NatraDefault);                      // Mark List
            }
            else
            {
                delete iter.Remove();
                continue;
            }
        }

        // Rabatt OV
        if ( dikp->DiscountType_ == DiscType_Overdrive )
        {
            if ( ot.IsOverDrive() && dikp->DiscountValuePct_ > 0 && dikp->BaseQty_ > 0 )
            {
                dikp->BestBuy_ = BestBuy_ValuePctOverdrive;
                SetKindOffRebate(ValuePctOverdrive);      // Mark List
            }
            else
            if ( ot.IsOverDrive() && dikp->FixedPrice_ != pxConstants::mZero && dikp->BaseQty_ > 0 && ot.IsCalcNetPrice() )
            {
                dikp->BestBuy_ = BestBuy_FixedPriceDefault;
                SetKindOffRebate(FixedPriceDefault);       // Mark List
            }
            else
            if ( ot.IsOverDrive() && dikp->DiscountSpec_ == DiscSpec_LogisticAddition && dikp->BaseQty_ > 0 )
            {
                dikp->BestBuy_ = BestBuy_LogisticAddition;
                SetKindOffRebate(LogisticAddition);                  // Mark List
            }
            else
            if ( ot.IsOverDrive() && dikp->BaseQty_ > 0 && dikp->DiscountQty_ > 0 )
            {
                dikp->BestBuy_ = BestBuy_NatraDefault;
                SetKindOffRebate(NatraDefault);                      // Mark List
            }
            else
            {
                delete iter.Remove();
                continue;
            }
        }

        // Rabatt Partenariat
        if ( dikp->DiscountType_ == DiscType_Partenariat && customer.Flags().IsParternariat() )
        {
            if ( (dikp->BaseQty_ > 0 || dikp->BaseValue_ > 0) && dikp->DiscountValuePct_ > 0 && dikp->DiscountQty_ > 0 )
            {
                dikp->BestBuy_ = BestBuy_ValuePctPartenariat;
                SetKindOffRebate(ValuePctPartenariat);               // Mark List
                SetKindOffRebate( NatraDefault);                     // Mark List
            }
            else
            if ( (dikp->BaseQty_ > 0 || dikp->BaseValue_ > 0) && dikp->DiscountValuePct_ > 0 && dikp->DiscountQty_ == 0 )
            {
                dikp->BestBuy_ = BestBuy_ValuePctPartenariat;
                SetKindOffRebate(ValuePctPartenariat);               // Mark List
            }
            else
            if ( dikp->FixedPrice_ != pxConstants::mZero && dikp->BaseQty_ > 0 && ot.IsCalcNetPrice() )
            {
                dikp->BestBuy_ = BestBuy_FixedPriceDefault;
                SetKindOffRebate(FixedPriceDefault);       // Mark List
            }
            else
            if ( (dikp->BaseQty_ > 0 || dikp->BaseValue_ > 0) && dikp->DiscountQty_ > 0 )
            {
                dikp->BestBuy_ = BestBuy_NatraDefault;
                SetKindOffRebate( NatraDefault);                      // Mark List
            }
            else
            {
                delete iter.Remove();
                continue;
            }
        }

        // WholeSale
        if ( dikp->DiscountType_ == DiscType_Default &&
             dikp->DiscountSpec_ == DiscSpec_WholeSale &&
             dikp->DiscountValuePct_ > 0 && dikp->BaseQty_ > 0 )
        {
            dikp->BestBuy_ = BestBuy_ValuePctWholeSale;
            SetKindOffRebate(ValuePctWholeSale);                 // Mark List
        }

        // Retail
        if ( dikp->DiscountType_ == DiscType_Default &&
             dikp->DiscountSpec_ == DiscSpec_Retail &&
             dikp->DiscountValuePct_ > 0 && dikp->BaseQty_ > 0 )
        {
            dikp->BestBuy_ = BestBuy_ValuePctRetail;
            SetKindOffRebate(ValuePctRetail);                    // Mark List
        }

        // WholeSaleIndustrie
        if ( dikp->DiscountType_ == DiscType_Default &&
             dikp->DiscountSpec_ == DiscSpec_WholeSale_Ind &&
             dikp->DiscountValuePct_ > 0 && dikp->BaseQty_ > 0 )
        {
            dikp->BestBuy_ = BestBuy_ValuePctWholeSaleInd;
            SetKindOffRebate(ValuePctWholeSaleInd);         // Mark List
        }

        // Tena + Barrabatt auf Kundenebene
        if ( dikp->DiscountType_ == DiscType_Default &&
             (dikp->DiscountSpec() == 0 || dikp->DiscountSpec() == DiscSpec_VoluntarySale || dikp->DiscountSpec() == DiscSpec_HealthFund) &&
             dikp->BaseQty_ > 0 &&
             dikp->CustomerNo_ > 0 &&
             dikp->PromotionNo_ == 0)
        {
            if ( dikp->CustomerNo_ == customer.KundenNr() )
            {
                // Special just for Serbian application
                if ( item->Order().Serbia() || item->Order().Bulgaria() )
                {
                    dikp->BestBuy_   = BestBuy_ValuePctCash;
                    SetKindOffRebate(ValuePctCash);                    // Mark List
                }
                else
                {
                    dikp->BestBuy_   = BestBuy_ValuePctTena;
                    SetKindOffRebate(ValuePctTena);                    // Mark List
                }
            }
            else
            {
                delete iter.Remove();
                continue;
            }
        }

        // LogisticAddition
        if ( dikp->DiscountType_ == DiscType_Default &&
             dikp->DiscountSpec_ == DiscSpec_LogisticAddition )
        {
            dikp->BestBuy_ = BestBuy_LogisticAddition;
            SetKindOffRebate(LogisticAddition);                  // Mark List
        }

        if ( dikp->DiscountType_ == DiscType_Default &&
             dikp->DiscountSpec_ == DiscSpec_Default &&
             dikp->PharmacyGroupId_ > "000" &&
             dikp->FixedPrice_ != pxConstants::mZero )
        {
            dikp->BestBuy_ = BestBuy_FixedPricePharmGroup;
            SetKindOffRebate(FixedPricePharmGroup);              // Mark List
        }

        if ( dikp->DiscountType_ == DiscType_Default &&
             dikp->DiscountSpec_ == DiscSpec_SpecialPrice &&
             dikp->FixedPrice_ != pxConstants::mZero )
        {
            dikp->BestBuy_ = BestBuy_SpecialPrice;
            SetKindOffRebate(SpecialPriceHR);                      // Mark List
        }

        // GrossProfitPct
        if ( dikp->DiscountType_ == DiscType_Default &&
             dikp->BaseQty_ > 0 && dikp->GrossProfitPct_ > 0 )
        {
            dikp->BestBuy_ = BestBuy_GrossProfitPct;
            SetKindOffRebate(ValueGrossProfitPct);                // Mark List
        }

        // 0er Rabatt Serbien
        if(item->Order().Serbia())
        {
            if ( dikp->DiscountType_ == DiscType_Default &&
                 dikp->BaseQty_ > 0 &&
                 dikp->PaymentTargetNo_ > 0 &&
                 0 == dikp->DiscountQty_ &&
                 0 == dikp->DiscountQtyPct_ &&
                 0 == dikp->SurchargePct_ &&
                 0 == dikp->RefundPct_  &&
                 pxConstants::mZero == dikp->FixedPrice_ &&
                 0 == dikp->DiscountValuePct_ )
            {
                dikp->BestBuy_ = BestBuy_ValuePctCash;
                SetKindOffRebate(ValuePctCash);                      // Mark List
            }
        }

        // Natra Promotion  DiscountType = 0 and Discountgrpno = 0
        if ( dikp->DiscountType_ == DiscType_Default &&
             dikp->BaseQty_ > 0  &&
             dikp->DiscountQty_ > 0 && dikp->DiscountGrpNo() == 0 )
        {
            dikp->BestBuy_ = BestBuy_NatraDefault;
            SetKindOffRebate( NatraDefault);                      // Mark List
        }

        // Barrabatt Promotion DiscountType = 0 and Discountgrpno = 0
        if ( dikp->DiscountType_  == DiscType_Default &&
             dikp->DiscountValuePct_ > 0 &&
             dikp->BaseQty_ > 0 &&
             dikp->DiscountGrpNo() == 0 &&
             dikp->PromotionNo_ > 0 )
        {
            dikp->BestBuy_ = BestBuy_ValuePctCash;
            SetKindOffRebate(ValuePctCash);                      // Mark List
        }

        // Netto Promotion DiscountType = 0 and Discountgrpno = 0
        if ( dikp->DiscountType_ == DiscType_Default &&
             dikp->FixedPrice_ != pxConstants::mZero &&
             dikp->BaseQty_ > 0 &&
             dikp->DiscountGrpNo() == 0 &&
             dikp->PromotionNo_ > 0 )
        {
            dikp->BestBuy_ = BestBuy_FixedPriceDefault;
            SetKindOffRebate(FixedPriceDefault);                 // Mark List
        }

        // 0er Rabatt als GrossProfitPct:
        if(item->Order().Bulgaria())
        {
            if ( dikp->DiscountType_ == DiscType_Default && dikp->BaseQty_ > 0 &&
                 0 == dikp->DiscountQty_ &&
                 0 == dikp->DiscountQtyPct_ &&
                 0 == dikp->SurchargePct_ &&
                 0 == dikp->RefundPct_ &&
                 pxConstants::mZero == dikp->FixedPrice_ &&
                 0 == dikp->DiscountValuePct_ )
            {
                dikp->BestBuy_ = BestBuy_GrossProfitPct;
                SetKindOffRebate(ValueGrossProfitPct);                // Mark List
            }
        }

        if (item->Order().Swiss())
        {
            // logistic addition with data transfer
            if (dikp->DiscountType_ == DiscType_Default && dikp->DiscountSpec_ == DiscSpec_DataTransfer)
            {
                dikp->BestBuy_ = BestBuy_LogisticDataTransfer;
                SetKindOffRebate(LogisticDataTransfer);
            }
            // value percentage with assorted cash discount
            if ((dikp->DiscountType_ == DiscType_Default || dikp->DiscountType_ == DiscType_CashDiscount) && dikp->DiscountValuePct_ > 0 && dikp->BaseQty_ > 0 && dikp->DiscountGrpNo_ > 0)
            {
                dikp->BestBuy_ = BestBuy_ValuePctCashAssorted;
                SetKindOffRebate(ValuePctCashAssorted);                 // Mark List
            }
        }
    }

    return static_cast<int>(Entries());
}

/*----------------------------------------------------------------------------*/
/*  LogAddSpecials: until now, this is a special function for the french      */
/*  application.                                                              */
/*  This function inspects the entries with discountspec = 1(Logisticadd.)    */
/*----------------------------------------------------------------------------*/
int
pxDiscountList :: LogAddSpecials
(
    pxOrderItem* item
)
{
    pxDiscountListIter  iter(*this);
    pxDiscount*         dikp;
    pxDiscount*         newdikp;
    pxCustBase& customer = *(item->Order().Customer());

    customer.Flags(); // Init Flags

    /*if (!Session()->isFrance())
        return ErrorState();*/

    if ( !item->Session()->isFrance() )
    {
        return ErrorState();
    }

    while ( (dikp = (pxDiscount*) ++iter) != NULL )
    {
        if ( dikp->DiscountType_ == DiscType_Default &&
             dikp->DiscountSpec_ == DiscSpec_LogisticAddition )
        {
            if ( dikp->FixedPrice() > pxConstants::mZero )
            {
                newdikp = new pxDiscount(*dikp);
                newdikp->DiscountSpec((short)0);
                newdikp->SurchargePct(0.0);
                newdikp->DiscountValuePct(0.0);
                dikp->FixedPrice(0.0);
                Append(newdikp);
            }
            if ( dikp->DiscountValuePct() > pxConstants::dZero )
            {
                newdikp = new pxDiscount(*dikp);
                newdikp->DiscountSpec((short)0);
                newdikp->SurchargePct(0.0);
                newdikp->FixedPrice(pxConstants::mZero);
                dikp->DiscountValuePct(0.0);
                Append(newdikp);
            }
        }
    }
    return ErrorState();
}

/*----------------------------------------------------------------------------*/
/*  SpecialPrice: until now, this is a special function for the croatia       */
/*  application.                                                              */
/*  This function inspects the entries with fixedpric > 0, if found mark it as*/
/*  a special price entry for further use                                     */
/*----------------------------------------------------------------------------*/
int
pxDiscountList :: SpecialPrice
(
    pxOrderItem* item
)
{
    pxDiscountListIter  iter(*this);
    pxDiscount*         dikp;

    /*if ( !item->Order().Croatia())
        return ErrorState();*/
    if ( !item->Session()->isCroatia() )
    {
        return ErrorState();
    }

    while ( (dikp = (pxDiscount*) ++iter) != NULL )
    {
        if ( dikp->DiscountType_ == DiscType_Default &&
             dikp->DiscountSpec_ == DiscSpec_Default )
        {
            if ( dikp->FixedPrice() > pxConstants::mZero )
            {
                dikp->DiscountSpec((short)DiscSpec_SpecialPrice);
            }
        }
    }
    return ErrorState();
}

/*----------------------------------------------------------------------------*/
/*  ArtComPackMembers: if ArticleNoPack > 0, check for existance of this      */
/*  article within the current order.                                         */
/*  If not, the pxdiscount entry will be removed from this list.              */
/*----------------------------------------------------------------------------*/
int
pxDiscountList :: ArtComPackMembers
(
    pxOrderItem* item
)
{
    pxDiscountListIter  iter(*this);
    pxDiscount*         dikp;

    while ( (dikp = (pxDiscount*) ++iter) != NULL )
    {
        if ( dikp->ArticleNoPack_ > 0 )
        {
            if ( !item->Order().ItemList()->Find(dikp->ArticleNoPack_ ) )
            {
                delete iter.Remove();
                continue;
            }
        }
    }
    return ErrorState();
}

/*----------------------------------------------------------------------------*/
/*  checkHigherConditions                                                     */
/*----------------------------------------------------------------------------*/
bool
pxDiscountList :: checkHigherConditions
(
    pxOrderItem* item,
    const long QOrdered
)
{
    bool retval = false;
    pxDiscountListIter  iter(*this);
    pxDiscount*         dikp;
    const pxCustOrderType& ot = item->Order().OrderType();

    if ( Session()->isBulgaria() )
    {
        return false;
    }

    while ( (dikp = (pxDiscount*) ++iter) != NULL )
    {
        if (   !dikp->IsMonthlyDiscount() && (dikp->BaseQty() > 0)
            && (   (ot.IsCalcDisInKind() && dikp->DiscountQty() > 0)
                || dikp->DiscountValuePct() > 0.0 || (ot.IsCalcNetPrice() && dikp->FixedPrice() > pxConstants::mZero) )
            && (QOrdered < dikp->BaseQty()) )
        {
            retval = true;
        }
    }
    return retval;
}
