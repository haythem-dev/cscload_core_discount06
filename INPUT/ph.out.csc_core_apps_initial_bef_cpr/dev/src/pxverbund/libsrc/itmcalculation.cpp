/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

Class pxOrderItem:
Calculate what kind of discount is given on this product, depend
on entries within table discount.

REVISION HISTORY

05 Jan 2006 V1.00 REV 00 written by Ysbrand Bouma.
*/

#include "pxitem.hpp"
#include "pxsess.hpp"
#include "pxartbas.hpp"
#include "pxartprc.hpp"
#include "pxcstbas.hpp"
#include "pxcustomerflags.hpp"
#include "pxcstpaymentterms.hpp"
#include "pxcustomergrpflags.hpp"
#include "pxorder.hpp"
#include "pxorderremarks.hpp"
#include "pxcstot.hpp"
#include "pxcalcdiscount.hpp"
#include "pxcustomersurcharge.hpp"
#include "pxitemdiscount.hpp"
#include "pxtaxtab.hpp"
#include "pxpromotions.hpp"
#include "calcdiscpct.h"
#include "pxoeparm.hpp"
#include "pxkdauftragposrefund.hpp"
//#include "pxvaldiscinfo.hpp"
#include <logger/loggerpool.h>
#include <base/irunnable.h>
#include "pxbase/pxconstants.hpp"
extern bool pxGlobalNoDatabaseWrite;

//*********************************************** getMarginGepAep *******************************************************
// Descr:   Gets margin between GEP and AEP, depending on pricetype (healthfund, freesale or retail)
//          and price group
//
// Param:
//
// Returns: margin
double pxOrderItem :: getMarginGepAep()
{
    double margin = 0.0;
    short preisgruppe = 0;
    int tax_von_dm = -1;
    char tax_art = 'a';
    int tax_proz = 0;

    // get preisgruppe:
    if(!ArtBase() || !ArtBase_->IsGoodState())
        return 0.0;

    if(!ArtBase()->PriceGroup())
        return 0.0;

    preisgruppe = ArtBase()->PriceGroup();

    // get tax_von_dm:
    switch(preisgruppe)
    {
    case 1:
        tax_von_dm = 0;
        break;
    case 2:
        tax_von_dm = 1000;
        break;
    case 3:
        tax_von_dm = 3000;
        break;
    case 4:
        return 10.0;
    default:
        return 0.0;
    }

    // get tax_art:
    // if Healthfund, then take maximum price:
    // else Freesale, Retail, ...
    tax_art = (HEALTHFUND_PRICE == PreisTyp()) ? '2' : '0';

    pxTaxTabList *ttlist = new pxTaxTabList(Session());
    if(!ttlist)
        return 0.0;

    ttlist->Select(tax_art, tax_von_dm);
    if(ttlist->Entries() > 0)
    {
        pxTaxTab* curp;
        pxTaxTabListIter cursor(*ttlist);  // define an iterator
        while ( (curp = (pxTaxTab*) ++cursor) != NULL )
        {
            tax_proz=curp->TaxProz();
        }
        margin = (double)tax_proz / 1000;
    }

    return margin;
}

//*********************************************** CalcDiscountPercentage *******************************************************
// Descr:   Calculates discount percentage for Rohertrag (Rabatt-Prozentsatz, Tab, Spalte 2)
//
// Param:   GrossProfitPct
//
// Returns: discount as percentage, e.g. 3.0 for 3% (percentage is always integer!)
double pxOrderItem :: CalcDiscountPercentage(double GrossProfitPct, short CascadeLevel, long baseQuantity)
{
    Decimal discount(0);
    Decimal grossProfitPct(GrossProfitPct);
    Decimal grossProfitFVPct(GrossProfitPctFV());
    short   cascadeLevel = CascadeLevel;

    pxCustBase& customer = *(Order().Customer());
    int customerGroup = atoi(customer.KdGruppe());
    bool cstIsCommercialRounding = (1 == customer.IsCommercialRounding());
    bool cstIsMathematicalRounding = (1 == customer.IsMathematicalRounding());
    bool cstIsHalfMargin = (1 == customer.Flags().IsHalfMargin());
    bool cstIsDiscountExcept = (1 == customer.Flags().IsDiscountExcept());

    short paymentTarget0 = -1;
    short paymentTarget1 = -1;
    pxCstPaymentTermsList* PaymentTermsList=customer.CstPaymentTermsList();

    if(PaymentTermsList)
    {
        pxCstPaymentTerms* PaymentTerms;
        PaymentTerms = PaymentTermsList->Find(FREESALE_PRICE);
        if(PaymentTerms)
            paymentTarget0 = PaymentTerms->PaymentTarget();

        PaymentTerms = PaymentTermsList->Find(HEALTHFUND_PRICE);
        if(PaymentTerms)
            paymentTarget1 = PaymentTerms->PaymentTarget();
    }

    bool artIsSortiment2 = (1 == ArtBase()->IsSortiment2());
    Decimal invDisc(ArtBase_->InvoiceRebatePct());
            invDisc /= Decimal(100);
    Decimal rebInKind(ArtBase_->RebateInKindPct());
            rebInKind /= Decimal(100);
    Decimal invDiscAnnual(ArtBase_->AnnualInvRebPct());
            invDiscAnnual /= Decimal(100);
    Decimal rebInKindAnnual(ArtBase_->AnnualRebIKPct());
            rebInKindAnnual /= Decimal(100);

    Decimal custRebRedPct(ArtBase_->CustRebRedPct());

    pxOrder& thisOrder = Order();
    bool isTenderOrder = thisOrder.TenderHead() ? true : false;
    double aep_temp = isTenderOrder ? Price() : PreisEKApoFV();

    PriceTypeEnum priceType = PreisTyp();

    Decimal aep_f(aep_temp);
    Decimal gep_f(PreisEKGrossoFV());
    Decimal aep_k(PreisEKApoKK());
    Decimal gep_k(PreisEKGrossoKK());
    Decimal gepna(PreisEKGrossoNaByPriceType(priceType));
    Decimal customerSurchargePct(GetCustomerSurchargePct());
    Decimal customerGrossProfitPct(getCustomerGrossProfitPct(baseQuantity));

    calcdisc::calcDiscountPercentage(grossProfitPct, grossProfitFVPct, cascadeLevel, customerGroup, cstIsCommercialRounding, cstIsMathematicalRounding, cstIsHalfMargin, cstIsDiscountExcept, paymentTarget0, paymentTarget1, artIsSortiment2, invDisc, rebInKind, invDiscAnnual, rebInKindAnnual, custRebRedPct, aep_f, gep_f, aep_k, gep_k, gepna, priceType, isTenderOrder, discount, customerSurchargePct, customerGrossProfitPct);

    AddSurchargeToAEP( customerSurchargePct, priceType );

    return discount.toFloat64();
}

//*********************************************** getCustomerConditions *******************************************************
// Descr:   Searches for customer conditions and returns grossProfitPercentage
//
// Param:   GrossProfitPct from customer as reference
//
// Returns: GrossProfitPct from customer as reference
Decimal pxOrderItem :: getCustomerGrossProfitPct(long baseQuantity)
{
    pxDiscountList* OrderPosDiscountList = new pxDiscountList(Session());
    pxCustBase& customer = *(Order().Customer());
    pxDiscount  *dikp = 0;
    pxDiscountListIter dlistiter(*OrderPosDiscountList);  // define an iterator
    Decimal ret( calcdisc::DECZERO );

    OrderPosDiscountList->Select(CASCADE_CUSTOMER, customer.FilialNr(), 0L, customer.IDFNr(), 0L, 0);
    OrderPosDiscountList->ShrinkPriceType( this, baseQuantity );

    dikp = (pxDiscount*) ++dlistiter;

    if ( dikp )
    {
        ret = Decimal ( dikp->GrossProfitPct() );
    }

    delete OrderPosDiscountList;
    return ret;
}

//*********************************************** PreisEKApoFV *******************************************************
// Descr:   Gets the PreisEKApo for freesaley sale (FV) from table artikelpreis.
//                      If there is no price found, returns 0
//
// Param:       -
//
// Returns: PreisEKApo for voluntary sale
nMoney pxOrderItem :: PreisEKApoFV()
{
    if(!ArtPriceList())
        return pxConstants::mZero;

    pxArtPrice* ArtPriceFV_;
    ArtPriceFV_ = ArtPriceList()->Find(FREESALE_PRICE);
    if(!ArtPriceFV_)
        return pxConstants::mZero;

    pxCustBase& customer = *(Order().Customer());
    if(customer.CustomerGroupFlagsList()->isGroupBasePriceGEPNA())
    {
        return ArtPriceFV_->PreisEKGrossoNA() ? ArtPriceFV_->PreisEKGrossoNA() : ArtPriceFV_->PreisEKGrosso();
    }
    if(customer.CustomerGroupFlagsList()->isGroupBasePriceGEP())
    {
        return ArtPriceFV_->PreisEKGrosso() ? ArtPriceFV_->PreisEKGrosso() : (nMoney)0;
    }

    return ArtPriceFV_->PreisEKApo();
}

//*********************************************** PreisEKApoKK *******************************************************
// Descr:   Gets the PreisEKApo for Health fund (KK) from table artikelpreis.
//                      If there is no price found, returns 0
//
// Param:       -
//
// Returns: PreisEKApo for voluntary sale
nMoney pxOrderItem :: PreisEKApoKK()
{
    if(!ArtPriceList())
        return pxConstants::mZero;

    pxArtPrice* ArtPriceKK_;
    ArtPriceKK_ = ArtPriceList()->Find(HEALTHFUND_PRICE);
    if(!ArtPriceKK_)
        return pxConstants::mZero;

    pxCustBase& customer = *(Order().Customer());
    if(customer.CustomerGroupFlagsList()->isGroupBasePriceGEPNA())
    {
        return ArtPriceKK_->PreisEKGrossoNA() ? ArtPriceKK_->PreisEKGrossoNA() : ArtPriceKK_->PreisEKGrosso();
    }

    if(customer.CustomerGroupFlagsList()->isGroupBasePriceGEP())
    {
        return ArtPriceKK_->PreisEKGrosso() ? ArtPriceKK_->PreisEKGrosso() : (nMoney)0;
    }

    return ArtPriceKK_->PreisEKApo();
}

//*********************************************** PreisEKGrossoFV *******************************************************
// Descr:   Gets the PreisEKGrosso for Freesale (FV) from table artikelpreis.
//                      If there is no price found, returns 0
//
// Param:       -
//
// Returns: PreisEKApo for voluntary sale
nMoney pxOrderItem :: PreisEKGrossoFV()
{
    if(!ArtPriceList())
        return pxConstants::mZero;

    pxArtPrice* ArtPriceFV_;
    ArtPriceFV_ = ArtPriceList()->Find(FREESALE_PRICE);
    if(!ArtPriceFV_)
        return pxConstants::mZero;

    return ArtPriceFV_->PreisEKGrosso();
}

//*********************************************** PreisEKGrossoKK *******************************************************
// Descr:   Gets the PreisEKGrosso for Healthfund (KK) from table artikelpreis.
//                      If there is no price found, returns 0
//
// Param:       -
//
// Returns: PreisEKApo for voluntary sale
nMoney pxOrderItem :: PreisEKGrossoKK()
{
    if(!ArtPriceList())
        return pxConstants::mZero;

    pxArtPrice* ArtPriceKK_;
    ArtPriceKK_ = ArtPriceList()->Find(HEALTHFUND_PRICE);
    if(!ArtPriceKK_)
        return pxConstants::mZero;

    return ArtPriceKK_->PreisEKGrosso();
}

//*********************************************** CalculateRefundValueByRefundPct *******************************************************
// Descr:   Calculates refund value out of refund pct.
//                      Refund value depends of amount and is based on GEPNA.
//                      Example: If refundpct=3%, article has GEPNA 4,03 and customer buys 5 pieces, you will get:
//                      Old: 5 x 4,03 x 0,03 = 0,6045
//                      New: Function is only called with QtyToBeDelivered=1
//
// Param:   refund pct
//
// Returns: refund value
//
double pxOrderItem :: CalculateRefundValueByRefundPct(double RefundPct, long QtyToBeDelivered)
{
    double RefundValue(0.0);
    nMoney Gepna=0;

    if(HEALTHFUND_PRICE == PreisTyp())
        Gepna = ArtPriceList()->GetPreisEKGrossoNA(HEALTHFUND_PRICE);
    else
        Gepna = ArtPriceList()->GetPreisEKGrossoNA(FREESALE_PRICE);

    RefundValue = RefundPct;
    RefundValue = RefundValue * (double)QtyToBeDelivered;
    RefundValue = RefundValue * (double)Gepna;
    RefundValue = RefundValue / 100.0;

    return RefundValue;
}

bool
pxOrderItem :: CheckSkipDiscountCalculations()
{
    pxCustBase& customer = *(Order().Customer());

    return ( !customer.CustomerGroupFlagsList()->IsKscDiscountEnabled() )
        || ( Order().Param()->IsParamArticle(ArtikelNr_)                ); // No disc-in-kind calulation Param Article
}

//*********************************************** CalcDiscount *******************************************************
long
pxOrderItem :: CalcDiscount
(
    long baseq,                      // base quantity to be calc'ed upon = Liefermenge = QOrdered in calcdiscount.cpp
    long QInStock
)
{
    std::stringstream s;
    s << "pxOrderItem::CalcDiscount() - Start of order no: " << Order().KdAuftragNr() << " baseq: " << baseq << " QInStock: " << QInStock;
    BLOG_INFO(libcsc::LoggerPool::getLoggerDiscountCalc(), s.str());

    long    retval = baseq;
    const pxCustOrderType&    ordertype  = Order().OrderType();
    pxCustBase&       customer   = *(Order().Customer());
    PreisEKApoNetto_  = pxConstants::mZero;
    pxItemDiscount*  itemdisc = NULL;
    nMoney   EKApoNetto = pxConstants::mZero;
    bool AddOnPromoDiscount = true;
    bool AddOnStdDiscount = true;

#ifdef CHDISCLOG
    std::stringstream t;
    t << "pxOrderItem::CalcDiscount() - Customer: " << customer.NameApo();
    if (itemdisc != NULL)
    {
        t << " -> Discount set with discount type: " << itemdisc->DiscountType();
    }
    else
    {
        t << " -> no Discount set";
    }
    BLOG_DEBUG(libcsc::LoggerPool::getLoggerDiscountCalc(), t.str());
#endif

    if( Session()->isBulgaria() )
    {
       return CalcDiscountBG(baseq, QInStock);
    }
    
    if (Order().Param()->IsUseNewDiscountCalc())
    {
		UndoItemDiscount();
        if ( !CheckSkipDiscountCalculations() )
        {
             libcsc::base::IRunnablePtr calcUC( Session()->getPositionDiscountCalcUC(this) );
             calcUC->run();

        }
        return baseq;
    }

    if( Session()->isSwitzerland() )
    {
        long qtyToBook = CalcDiscountCH( baseq, QInStock );

#ifdef CHDISCLOG
        std::stringstream v;
        v << "pxOrderItem::CalcDiscount() - CalcDiscountCH results with qtyToBook = " << qtyToBook << " (qtyToBook > 0 leads to exit CalcDiscount)";
        BLOG_DEBUG(libcsc::LoggerPool::getLoggerDiscountCalc(), v.str());
#endif

        if( qtyToBook > 0 )
        {
            return qtyToBook;
        }
		if( 0 != GetTenderNoFromRemark() )
		{
			return 0;
		}
    }

    if ( CheckSkipDiscountCalculations() )
    {
        return baseq;
    }

//------------------------------------------------------------------------------
// wegwerfen einer evt. erfolgten früheren Kalkulation, z.B. nach Mengenänderung
//------------------------------------------------------------------------------
    UndoItemDiscount();
    UndoOrderPosRefund();

/*----------------------------------------------------------------------------*/
/*  Check the product-related discount-in-kind possibility                    */
/*  before calculation of base discount.                                      */
/*----------------------------------------------------------------------------*/
    pxCustPharmGroupList *phglist   = customer.PharmGroupList();

/*----------------------------------------------------------------------------*/
/*  First check for OMG Rabates. If there is an OMG Condition, no             */
/*  further discount calculation and return to caller                         */
/*----------------------------------------------------------------------------*/
    //if( Session()->isSwitzerland() )
    //{
    //    // No check for OMGs here anymore. This is done in CalcDiscountCH().
    //}
    //else if (phglist && hasOmgRebates())
    //{
    //    return std::max(retval, baseq);
    //}

/*----------------------------------------------------------------------------*/
/*  Do just handle special Disinkind on a well contructed                     */
/*  CustomerPharmacyGroupList                                                 */
/*----------------------------------------------------------------------------*/
    int mode = Session()->isSerbia() ? MODE_SERBIA : 0;
    pxCalcDiscountList* calclist = createCalcDiscountList(mode, baseq, phglist, AddOnPromoDiscount, AddOnStdDiscount);
#ifdef CHDISCLOG
    if (!calclist)
    {
        std::stringstream v;
        v << "pxOrderItem::CalcDiscount() - No calclist returned";
        BLOG_DEBUG(libcsc::LoggerPool::getLoggerDiscountCalc(), v.str());
    }
    else
    {
        std::stringstream v;
        v << "pxOrderItem::CalcDiscount() - Calclist returned with " << calclist->Entries() << " entries";
        BLOG_DEBUG(libcsc::LoggerPool::getLoggerDiscountCalc(), v.str());
    }
#endif

    if ( !IsGoodState() )            // Error in CalcList
    {
       return ErrorState();
    }

/*----------------------------------------------------------------------------*/
/*  Calc product-related discount values.                                     */
/*----------------------------------------------------------------------------*/
    
    if (!calclist)
        return std::max(retval, baseq);

    if (MODE_SERBIA == mode)
    {
        // no calclist->DeleteRaises for Serbia, is done in calcdiscount.cpp
        calclist->ShrinkMultipleEntries();
        ProcessCalclistForSerbia(calclist, customer);
        MaxTargetNo_= GetMaxTargetNoForSerbia(calclist);
    }
    else
    {
        if ( !customer.IsQuantityRaising() )
            calclist->DeleteRaises(DiscType_Default);

        // this is for the Swiss application a temporarily workaround
        // if DiscountPct found, do no calculate DisInKind.
        bool DoNotCalculateDisInKind = false;

        //**************** Barrabatt:
        pxCalcDiscount* calcp = calclist->BestBuyCash();

        if (calcp)
        {
            baseq = calcp->QOrdered();

            // special Austrian discount. I hope this is not forever
            if ( PreisEKApo_ > pxConstants::mZero )
            {
                EKApoNetto = PreisEKApo_ - ((PreisEKApo_ * calcp->DiscountValuePct()) / 100.0);
            }

            if (Order().Austria() && EKApoNetto > pxConstants::mZero)
            {
                PreisEKApoNetto_ =  EKApoNetto;
                SetNetPrice();
                delete calclist;
                calclist = NULL;
                return std::max(retval, baseq);
            }
            double discount = calcp->DiscountValuePct();

            // Swiss workaround
            if (Order().Swiss())
            {
                if (discount > pxConstants::dZero )
                {
                    DoNotCalculateDisInKind = true;
                }
                calcp->DiscountBestBuy();
            }

            if (itemdisc)
            {
#ifdef CHDISCLOG
                std::stringstream v;
                v << "pxOrderItem::CalcDiscount() - itemdisc set and saved";
                BLOG_DEBUG(libcsc::LoggerPool::getLoggerDiscountCalc(), v.str());
#endif
                itemdisc->SetDiscountValuePct(discount);
                itemdisc->Put();
            }
            else
            {
#ifdef CHDISCLOG
                std::stringstream v;
                v << "pxOrderItem::CalcDiscount() - no itemdisc set, so item from calclist set and saved";
                BLOG_DEBUG(libcsc::LoggerPool::getLoggerDiscountCalc(), v.str());
#endif
                itemdisc = createItemDiscount(calcp);
                itemdisc->SetDiscountValuePct(discount);
                putItemAndAppendToList(itemdisc);
            }
            SetRefundValue(calcp->RefundValue());
            setMidasAbrechnung(calcp->TurnOverCalcImpact());

            // calcp->DiscountKey() ist der RefundPct!!!
            writeRefundWithDiscountKey(calcp);

            if (calcp->Promotion_No() != 0)
            {
                WriteOrderPosPromo( calcp->PharmacyGroupId(), 0L, 0L, 0.0, 0L, calcp->Promotion_No(), calcp->InternalDiscount(), calcp->DiscountValuePct());
            }

            setNaturalRabattInternOrWriteKdAuftragPosRefund(calclist->IsNrIntern(), calcp, baseq);

            if (Order().Swiss())
            {
                SetPreisEKGrossoNA(calcp->DiscountKey());
            }
            /*if (Order().Swiss() && (ArtBase()->HerstellerNr() != 300L) && (ArtBase()->HerstellerNr() != 444L))
            {
                delete calclist;
                calclist = NULL;
                return std::max(retval, baseq);
            }*/
        }

        //**************** Natra:
        if ( ordertype.IsCalcDisInKind() && DoNotCalculateDisInKind == false )  // Is rebate in kind allowed for this ordertype (Auftragsart)?
                                            // check whether ordertype is allowed for discounts at all (ob Auftragsart überhaupt rabattfähig), is done in itemterms.cpp
        {
            // natra = natural discounts
            calcp = calclist->BestBuyNatra();
            if (calcp)
            {
                baseq = calcp->QOrdered();
                if ( calcp->DiscountKey() > 0 )
                {
                    MengeNatraHerst_  = calcp->DiscountQty();
                }
                else
                {
                    MengeNatraGrossH_ = calcp->DiscountQty();
                }
                DiscountArticleNo_ = calcp->DiscountArticle();
                if ( DiscountArticleNo_ > 0 )
                {
                    MengeNatraDiscountArticle_ = MengeNatraHerst_ + MengeNatraGrossH_;
                    MengeNatraHerst_  = 0;
                    MengeNatraGrossH_ = 0;
                }

                itemdisc = createItemDiscount(calcp);
                putItemAndAppendToList(itemdisc);
                SetRefundValue(calcp->RefundValue());
                writeRefund(calcp, 0);
                setMidasAbrechnung(calcp->TurnOverCalcImpact());
                setNaturalRabattInternOrWriteKdAuftragPosRefund(calclist->IsNrIntern(), calcp, baseq);

                writeOrderPosPromoWithInternalDiscount(calcp);
            }
        }

        //**************** Netto oder Kroatien:
        if ( ordertype.IsCalcNetPrice() || Order().Croatia())
        {
            calcp = calclist->BestBuyNetto();
            if (calcp)
            {
                baseq = calcp->QOrdered();
                PreisEKApoNetto_ = calcp->FixedPrice();
                itemdisc = createItemDiscount(calcp);
				itemdisc->SetFixedPrice(calcp->FixedPrice());
                putItemAndAppendToList(itemdisc);
                SetRefundValue(calcp->RefundValue());
                writeRefund(calcp, 1);
                setMidasAbrechnung(calcp->TurnOverCalcImpact());
                writeOrderPosPromoWithInternalDiscount(calcp);
                setNaturalRabattInternOrWriteKdAuftragPosRefund(calclist->IsNrIntern(), calcp, baseq);

                if ( Order().Croatia() && (PreisEKGrossoNA_ == pxConstants::mZero) )
                {
                    PreisEKGrossoNA_ =  PreisEKApoNetto_;
                    PreisEKApoNetto_ = pxConstants::mZero;
                }
            }
        }

        //**************** Logistikaufschlag:
        calcp = calclist->BestBuyLogAddition();
        if (calcp)
        {
            baseq    = calcp->QOrdered();
            itemdisc = createItemDiscount(calcp);
            itemdisc->SetDiscountValuePct(calcp->DiscountValuePct());
            putItemAndAppendToList(itemdisc);
            SetRefundValue(calcp->RefundValue());
            writeRefund(calcp, 0);
            setMidasAbrechnung(calcp->TurnOverCalcImpact());
            writeOrderPosPromoWithInternalDiscount(calcp);
            setNaturalRabattIntern(calclist->IsNrIntern());
            if (Order().Swiss())
            {
                SetPreisEKGrossoNA(calcp->DiscountKey());
                // SetTeamAbrechnung();
            }
        }

		//**************** fixer Rabattwert:
		if ( ordertype.IsShortLineBusiness() && Order().France())
		{
			calcp = calclist->BestBuyFixedDiscountValue();
			if (calcp)
			{
				baseq    = calcp->QOrdered();
				RabattFest_ = calcp->FixedDiscountValue();
				itemdisc = createItemDiscount(calcp);
				putItemAndAppendToList(itemdisc);
			}
		}

        // logistic addition for datatransfer in CH
        calcp = calclist->BestBuyLogAdditionDataTransfer();
        if (calcp)
        {
            baseq = calcp->QOrdered();
            itemdisc = createItemDiscount(calcp);
            itemdisc->SetDiscountValuePct(calcp->DiscountValuePct());
            putItemAndAppendToList(itemdisc);
            SetRefundValue(calcp->RefundValue());
            writeRefund(calcp, 0);
            setMidasAbrechnung(calcp->TurnOverCalcImpact());
            writeOrderPosPromoWithInternalDiscount(calcp);
            setNaturalRabattIntern(calclist->IsNrIntern());

            if (Order().Swiss())
            {
                SetPreisEKGrossoNA(calcp->DiscountKey());
            }
        }
    }

    setOrClearNetPriceOnPreisEKApoNetto(!Order().Swiss() && !Order().Croatia());

    if  (calclist)
        delete calclist;

#ifdef CHDISCLOG
    std::stringstream v;
    v << "pxOrderItem::CalcDiscount() done";
    BLOG_DEBUG(libcsc::LoggerPool::getLoggerDiscountCalc(), v.str());
#endif

    return std::max(retval, baseq);
}

//*********************************************** CalcDiscountCH *******************************************************
long
pxOrderItem :: CalcDiscountCH
(
    long baseq,
    long QInStock
)
{
#ifdef CHDISCLOG
    std::stringstream s;
    s << "pxOrderItem::CalcDiscountCH" ;
    BLOG_DEBUG( libcsc::LoggerPool::getLoggerDiscountCalc(), s.str().c_str() );
#endif

	if( 0 == baseq )
	{
		return baseq;
	}

	const pxCustOrderType & ot = Order().OrderType();
	if( false == ot.IsNormal() )
	{
		// OMG discounts on NO orders only
		return 0;
	}

    try
    {
        pxCustBase & customer = *( Order().Customer() );

        libcsc::discount::TenderDiscountSearchParams searchParams( customer.KundenNr(), ArtikelNr_ );
        libcsc::discount::TenderDiscountListPtr list = Session()->getTenderDiscountFinder()->findByPattern( searchParams );
        if ( !list->empty() )
        {
            libcsc::discount::TenderDiscountList::const_iterator iter = list->begin();
            //If multiple rows take only the first with lowest pharmacy group id.
            if( iter != list->end() )
            {
                const libcsc::discount::TenderDiscountPtr & tenderDiscount( *iter );
                m_TenderDiscount = tenderDiscount;

				std::stringstream ss;
				ss << "pxOrderItem::CalcDiscountCH(): ArtikelNo<" <<  ArtikelNr_ << ">, CustomerNo<" << customer.KundenNr();
				ss << "> - TenderNo<" << tenderDiscount->getTenderNo().get() << "> found.";
				BLOG_TRACE( libcsc::LoggerPool::getLoggerTenderDiscount(), ss.str().c_str() );

				// think we have to use this:
                UndoItemDiscount();     // should not be necessary
                pxItemDiscount*  itemdisc = NULL;
                itemdisc = createItemDiscount( BestBuy_ValuePctOMG, tenderDiscount->getPharmacyGroupId().c_str());
                basar::Decimal dc( tenderDiscount->getDiscountPercent() );
                itemdisc->SetDiscountValuePct( dc.toFloat64() );
				itemdisc->SetInternalDiscountFlag(tenderDiscount->getRecallFlag() ? 0 : 1);
				itemdisc->SetDiscountCategory(DiscCategory_PharmacyGroup);
                itemdisc->SetDiscountCalcFrom(tenderDiscount->getDiscountCalcFrom());
                itemdisc->SetDiscountApplyTo(tenderDiscount->getDiscountApplyTo());
                nString str = "pxOrderItem :: CalcDiscountCH";
                itemdisc->logKdAuftragPosRab( str );
                putItemAndAppendToList( itemdisc );

				if( tenderDiscount->getRecallFlag() )
				{
					ClearNaturalRabattIntern();
				}
				else
				{
					// no recall of discount from supplier
					SetNaturalRabattIntern();
				}

                ss.str( "" );
                ss << tenderDiscount->getTenderNo().get();
                basar::VarString sTenderNo( ss.str().c_str() );

                pxGenericOrderRemarkList remarklist( Session() );
                remarklist.SelectOrderRemarksByOrderLineAndType( KdAuftragNr(), PosNr(), eTenderNo );
                if( remarklist.Entries() > 0 )
                {
                    remarklist.ChangeOrderRemark( KdAuftragNr(), PosNr(), eTenderNo, sTenderNo );
                }
                else
                {
                    remarklist.AddOrderRemark( KdAuftragNr(), PosNr(), eTenderNo, sTenderNo );
                }

                return ( QInStock < baseq ? QInStock : baseq );
            }
        }
    }
    catch( const std::exception & ex )
    {
        BLOG_ERROR( libcsc::LoggerPool::getLoggerSession(), ex.what() );
        return 0L;
    }
    return 0L;
}

//*********************************************** CalcDiscountBG *******************************************************
long
pxOrderItem :: CalcDiscountBG
(
    long baseq,                      // base quantity to be calc'ed upon = Liefermenge = QOrdered in calcdiscount.cpp
    long QInStock
)
{
    long    retval = baseq;
    const pxCustOrderType&    ordertype  = Order().OrderType();
    pxCustBase&       customer   = *(Order().Customer());
    PreisEKApoNetto_  = pxConstants::mZero;
    pxItemDiscount*  itemdisc = NULL;
    bool AddOnPromoDiscount = true;
    bool AddOnStdDiscount = true;
    bool NotBySalesWeb;
    long  DiscountQty = 0;
    nString  m_str = "pxOrderItem :: CalcDiscountBG";

    // for safety:
    if (!Session()->isBulgaria())
        return 0L;

    if ( !customer.CustomerGroupFlagsList()->IsKscDiscountEnabled() )
        return std::max(retval, baseq);

/*----------------------------------------------------------------------------*/
/*  No discount-in-kind calulation Param Article                              */
/*----------------------------------------------------------------------------*/
    if ( Order().Param()->IsParamArticle(ArtikelNr_) )
        return std::max(retval, baseq);

//------------------------------------------------------------------------------
// wegwerfen einer evt. erfolgten früheren Kalkulation, z.B. nach Mengenänderung
//------------------------------------------------------------------------------
    if ( ItemDiscountList_ != NULL )
    {
        blogDebugOnGlobalNoDatabaseWrite(m_str);
    }
    UndoItemDiscount();
/*
//------------------------------------------------------------------------------
// wegwerfen einer evt. erfolgten früheren Kalkulation, z.B. nach Mengenänderung
//------------------------------------------------------------------------------
    UndoOrderPosPromo();
    if (!IsArticleDiscountPromotion())
        PromotionNo_ = 0;
//------------------------------------------------------------------------------
// wegwerfen einer evt. erfolgten früheren Kalkulation, z.B. nach Mengenänderung
//------------------------------------------------------------------------------
    UndoOrderPosRefund();
*/

/*----------------------------------------------------------------------------*/
/*  Do not calculate rebate condition if PromoTyp > 0 (Bulgarian Apllication) */
/*----------------------------------------------------------------------------*/
    // PromoTyp == 1 Promotion for this article
    // Member DiscountValPctPromo_ contains the percentage
    if ( IsArticleDiscountPromotion() )  // if PromoTyp 1 (also bestellter Artikel; PromoTyp 2 ist Natra)
    {
        if ( DiscountValPctPromo_ > 0.0 )
        {
            UndoItemDiscount();     // should not be necessary
            itemdisc = createItemDiscount(BestBuy_ValuePctCash, PharmacyGroupId());
            itemdisc->SetDiscountValuePct(DiscountValPctPromo_);
            itemdisc->logKdAuftragPosRab(m_str);
            putItemAndAppendToList(itemdisc);
        }
        GetAddOnFlags(PromotionNo(), AddOnPromoDiscount, AddOnStdDiscount, NotBySalesWeb);
        if (!AddOnPromoDiscount && !AddOnStdDiscount)
        {
            return std::max(retval, baseq);
        }
    }

    // Auf Natras wird kein weiterer Rabatt vergeben, also hier raus:
    if (IsFreeArticlePromotion())
        return std::max(retval, baseq);

/*----------------------------------------------------------------------------*/
/*  Check the product-related discount-in-kind possibility                    */
/*  before calculation of base discount.                                      */
/*----------------------------------------------------------------------------*/
    pxCustPharmGroupList *phglist = customer.PharmGroupList();

/*----------------------------------------------------------------------------*/
/*  First check for OMG Rabates. If there is an OMG Condition, no             */
/*  further discount calculation and return to caller                         */
/*----------------------------------------------------------------------------*/
    //if (phglist && hasOmgRebates())
    //{
    //    return std::max(retval, baseq);
    //}

/*----------------------------------------------------------------------------*/
/*  Do just handle special Disinkind on a well contructed                     */
/*  CustomerPharmacyGroupList                                                 */
/*----------------------------------------------------------------------------*/
	pxCalcDiscountList* calclist = createCalcDiscountList(MODE_BULGARIA, baseq, phglist, AddOnPromoDiscount, AddOnStdDiscount);
    //pxCalcDiscountList* calclist = createCalcDiscountList(MODE_BULGARIA, baseq, phglist);
    if ( !IsGoodState() )            // Error in CalcList
    {
        return ErrorState();
    }

/*----------------------------------------------------------------------------*/
/*  Calc product-related discount values.                                     */
/*----------------------------------------------------------------------------*/
    if (!calclist)
        return std::max(retval, baseq);

    pxCalcDiscount *calcp;
    pxCalcDiscountListIter calcit(*calclist);
    while ( (calcp = (pxCalcDiscount*) ++calcit) != NULL )
    {
        //**************** Netto:
        if ( ordertype.IsCalcNetPrice())
        {
            if(BestBuy_FixedPriceDefault == calcp->DiscountBestBuy() || BestBuy_SpecialPrice == calcp->DiscountBestBuy())
            {
                baseq = calcp->QOrdered();
                PreisEKApoNetto_ = calcp->FixedPrice();
                itemdisc = createItemDiscount(calcp);
                itemdisc->logKdAuftragPosRab(m_str);
                putItemAndAppendToList(itemdisc);
                SetRefundValue(calcp->RefundValue());
                writeRefundWithDiscountKey(calcp);
                setMidasAbrechnung(calcp->TurnOverCalcImpact());
                writeOrderPosPromoWithInternalDiscountAndPromoBaseQty(calcp);
                setNaturalRabattIntern(calclist->IsNrIntern());
                if ( (PreisEKApoNetto_ > pxConstants::mZero) )  // discount price got,
                {
                    SetNetPrice();
                    delete calclist;
                    return std::max(retval, baseq);
                }
            }
        }

        //**************** Barrabatt:
        if(BestBuy_ValuePctCash == calcp->DiscountBestBuy())
        {
            baseq = calcp->QOrdered();
            addDiscountAndWriteRefund(calcp, calcp->DiscountValuePct(), m_str);
            setNaturalRabattIntern(calclist->IsNrIntern());
        }

        //**************** Natra:
        if (ordertype.IsCalcDisInKind())  // Is rebate in kind allowed for this ordertype (Auftragsart)?
        // check whether ordertype is allowed for discounts at all (ob Auftragsart überhaupt rabattfähig), is done in itemterms.cpp
        {
            if(BestBuy_NatraDefault == calcp->DiscountBestBuy())
            {
                baseq = calcp->QOrdered();
                DiscountQty = calcp->DiscountQty();
                if ( (calcp->DiscountArticle() == 0) && ((baseq + DiscountQty) > QInStock) )     // promotion does not fit availability in Stock
                {
                    UndoOrderPosPromo();
                    UndoOrderPosRefund();
                    continue;
                }

                AddNatraToExistingOne(calcp->DiscountQty(), calcp->DiscountArticle(), calcp->DiscountKey(), calcp->PharmacyGroupId(),
                    calcp->RefundValue(), calcp->TurnOverCalcImpact(), calcp->Promotion_No(), calcp->DiscountBestBuy());

                writeRefundWithDiscountKey(calcp);
                setMidasAbrechnung(calcp->TurnOverCalcImpact());
                setNaturalRabattIntern(calclist->IsNrIntern());
                writeOrderPosPromoWithInternalDiscountAndPromoBaseQty(calcp);
            }
        }

        //**************** Rohertragsrabatt:
        if (BestBuy_GrossProfitPct == calcp->DiscountBestBuy()) // ptr auf pxCalcDiscount, welches alle Rabatte zu einer Position hält
        {
            double pct = CalcDiscountPercentage(calcp->GrossProfitPct(), calcp->CascadeLevel(), baseq);
            if ( (pct != 0) || CustomerSurchargeAdded() )
            {
                addDiscountAndWriteRefund(calcp, pct, m_str);
            }
            setNaturalRabattIntern(calclist->IsNrIntern());
        }

        //**************** Logistikaufschlag:
        if (BestBuy_LogisticAddition == calcp->DiscountBestBuy())
        {
            baseq    = calcp->QOrdered();
            itemdisc = createItemDiscount(calcp);
            itemdisc->SetDiscountValuePct(calcp->DiscountValuePct());
            blogDebugOnGlobalNoDatabaseWrite(m_str);
            putItemAndAppendToList(itemdisc);
            SetRefundValue(calcp->RefundValue());
            writeRefundWithDiscountKey(calcp);
            setMidasAbrechnung(calcp->TurnOverCalcImpact());
            writeOrderPosPromoWithInternalDiscountAndPromoBaseQty(calcp);
            setNaturalRabattIntern(calclist->IsNrIntern());
        }

        setOrClearNetPriceOnPreisEKApoNetto(true);

        // refunds based on article level:
        if (ArtBase_)
        {
            double refundValue = (HEALTHFUND_PRICE == PreisTyp()) ? ArtBase_->SupplHiReimb() : ArtBase_->SupplFsReimb();
            WriteRefund(refundValue, 0, 1, 2, 0);
        }
    }

    if (calclist)
        delete calclist;

    return std::max(retval, baseq);
}

//**************************************** AddDiscountToExistingOne ******************************************
double
pxOrderItem :: AddDiscountToExistingOne(
    double newDiscount, nString PharmacyGroupId, double RefundValue, char TurnOverCalcImpact, short PromotionNo, const short DiscountType)
{
    double discount = newDiscount;
    pxItemDiscount* itemdisc = NULL;
    nString m_str = "pxOrderItem :: AddDiscountToExistingOne";
    pxItemDiscountList *itemDiscList = ItemDiscountList();
    if(!itemDiscList)
        return 0.0;

    pxItemDiscount* dikp;
    pxItemDiscountListIter cursor(*itemDiscList);
    bool blnUpdated = false;

    while ( (dikp = (pxItemDiscount*) ++cursor) != NULL )
    {
        // grossprofit discount is handled as cash discount, so there is only one entry in kdauftragposrab
        if(BestBuy_ValuePctCash==dikp->DiscountType() || BestBuy_GrossProfitPct==dikp->DiscountType())  // this is an entry for value pct cash in database
        {
            if(dikp->DiscountValuePct())
                discount += dikp->DiscountValuePct();
            if(discount > 100)
                discount = 100.0;
            dikp->SetDiscountValuePct(discount);
            setSurchargePctOnCustomerSurcharge(dikp);
            dikp->logKdAuftragPosRab(m_str);
            dikp->Put();
            blnUpdated = true;
            setPromotionNoOnPromoTypZero(PromotionNo);
        }
    }

    if(!blnUpdated) // there was no "normal" value pct discount found, so the new one is the only one
    {
        itemdisc = createItemDiscount(DiscountType, PharmacyGroupId);
        itemdisc->SetDiscountValuePct(discount);
        setSurchargePctOnCustomerSurcharge(itemdisc);
        itemdisc->logKdAuftragPosRab(m_str);
        putItemAndAppendToList(itemdisc);
        SetRefundValue(RefundValue);
        setPromotionNoOnPromoTypZero(PromotionNo);
        setMidasAbrechnung(TurnOverCalcImpact);
    }

    return discount;
}

//**************************************** AddNatraToExistingOne ******************************************
void
pxOrderItem :: AddNatraToExistingOne(
    long newDiscountQty, long DiscountArticleNo, double DiscountKey, nString PharmacyGroupId, double RefundValue,
    char TurnOverCalcImpact, short PromotionNo, const short DiscountType)
{
    long NatraHerst = 0;
    long NatraGrossH = 0;
    pxItemDiscount* itemdisc = NULL;
    nString m_str = "pxOrderItem :: AddNatraToExistingOne";

    pxItemDiscountList *itemDiscList=ItemDiscountList();
    if(!itemDiscList)
        return;

    if(BestBuy_NatraDefault == DiscountType)  // this is an entry for natra in database
    {
        if(DiscountKey > 0 )
        {
            NatraHerst = newDiscountQty;
            MengeNatraHerst_ += NatraHerst;
        }
        else
        {
            NatraGrossH = newDiscountQty;
            MengeNatraGrossH_ += NatraGrossH;
        }
        DiscountArticleNo_ = DiscountArticleNo;
        if ( DiscountArticleNo_ > 0 )
        {
            MengeNatraDiscountArticle_ += (NatraHerst + NatraGrossH);
            // subtrahiere die gerade addierten Werte wieder:
            MengeNatraHerst_  -= NatraHerst;
            MengeNatraGrossH_ -= NatraGrossH;
        }

        itemdisc = createItemDiscount(DiscountType, PharmacyGroupId);
        itemdisc->logKdAuftragPosRab(m_str);
        putItemAndAppendToList(itemdisc);
        SetRefundValue(RefundValue);
        setPromotionNoOnPromoTypZero(PromotionNo);
        setMidasAbrechnung(TurnOverCalcImpact);
    }
}

//**************************************** ProcessCalclistForSerbia ******************************************
void
pxOrderItem :: ProcessCalclistForSerbia
(
    pxCalcDiscountList *calclist,               // list that holds all discounts
    pxCustBase&        customer
)
{
    pxCalcDiscountListIter calcit(*calclist);
    pxItemDiscount*  itemdisc = NULL;

    pxCalcDiscount* calcp = calclist->BestBuyNetto();
    if (calcp)
    {
        FixedPricePaymentterms_ = calcp->FixedPrice();
    }

    // Write an entry into kdauftragposrab for all given payment targets
    while ( (calcp = (pxCalcDiscount*) ++calcit) != NULL )
    {
        itemdisc = new pxItemDiscount(customer.Session(), KdAuftragNr_, PosNr_, calcp->DiscountBestBuy(), calcp->PharmacyGroupId(), calcp->PaymentTargetNo());
        itemdisc->SetDiscountValuePct(calcp->DiscountValuePct());
        putItemAndAppendToList(itemdisc);
        SetRefundValue(calcp->RefundValue());
        SetPromotionNo(calcp->Promotion_No());
        setMidasAbrechnung(calcp->TurnOverCalcImpact());
    }

    if ( FixedPricePaymentterms_ != pxConstants::mZero && calclist->Entries() == 0 )
    {
        FixedPricePaymentterms_ = pxConstants::mZero;
    }
}

//**************************************** GetMaxTargetNoForSerbia ******************************************
//
// holt die niedrigste Nr = höchstes Zahlungsziel
short
pxOrderItem :: GetMaxTargetNoForSerbia
(
    pxCalcDiscountList *calclist                // list that holds all discounts
)
{
    pxCalcDiscount *calcp;
    pxCalcDiscountListIter calcit(*calclist);

    // get payment target no for 0 discount or if there is none, get lowest payment target no:
    short ptn = 100;
    while ( (calcp = (pxCalcDiscount*) ++calcit) != NULL )
    {
        if(calcp->PaymentTargetNo() < ptn)
        {
            if(BestBuy_ValuePctCash == calcp->DiscountBestBuy())
            {
                ptn = calcp->PaymentTargetNo();
                if(0.0 == calcp->DiscountValuePct())
                    return calcp->PaymentTargetNo();
            }
        }
    }
    if(ptn >= 100)
        ptn = 0;
    return ptn;
}

//**************************************** WriteRefund ******************************************
int
pxOrderItem :: WriteRefund
(
    long OrderNo,
    long PosNo,
    double RefundValue,
    double RefundPct,
    long QtyToBeDelivered,  // shall always be calculated on basis=1
    short RefundSrc,
    short PromotionNo
)
{
    double TotalRefundValue(0);

    if (!Session()->isBulgaria())
        return ErrorState();

    if(this->ProFormaBooking_)
        return ErrorState();

    //      ClearKdAuftragPosRefundList(); analog UndoItemDiscount() vor Rabattauswertung (ABER ACHTUNG: artikelbezogene Kompensationen!)

    if (RefundPct > 0)
    {
        TotalRefundValue = CalculateRefundValueByRefundPct(RefundPct, QtyToBeDelivered);
    }
    else
    {
        TotalRefundValue = QtyToBeDelivered * RefundValue;
    }

    pxCustBase& customer = *(Order().Customer());

    pxKdAuftragPosRefund* refund = NULL;
    if(TotalRefundValue > 0)
    {
        if (KdAuftragPosRefundList())
        {
            short _RefundSrc = RefundSrc;

            if(PromotionNo > 0)
                _RefundSrc = 1;
            refund = new pxKdAuftragPosRefund(customer.Session(), OrderNo, PosNo, TotalRefundValue, _RefundSrc, PromotionNo);
            refund->Put();
            // append to list, if it's needed anywhere else:
            KdAuftragPosRefundList()->Append(refund);
        }
    }
    return ErrorState();
}

//**************************************** WriteRefund ******************************************
int
pxOrderItem :: WriteRefund
(   double RefundValue,
    double RefundPct,
    long QtyToBeDelivered, // shall always be calculated on basis=1
    short RefundSrc,
    short PromotionNo
)
{
    return WriteRefund(KdAuftragNr_, PosNr_, RefundValue, RefundPct, QtyToBeDelivered, RefundSrc, PromotionNo);
}

//**************************************** GetAddOnFlags ******************************************
void
pxOrderItem :: GetAddOnFlags
(
    short PromotionNo,
    bool& AddOnPromoDiscount,
    bool& AddOnStdDiscount,
    bool& NotBySalesWeb
)
{
    pxPromotionsList *plist = NULL;
    bool SalesWebOrder = Order().IsAuftragVomXML();

    // char-Felder immer mit 0/false vorbelegen, weil '' und ' ' die Bedeutung von 0 haben sollen
    AddOnPromoDiscount = false;
    AddOnStdDiscount = false;
    NotBySalesWeb = false;

    plist = new pxPromotionsList(Session());
    pxPromotionsListIter iter(*plist);

    if(!PromotionNo)
        goto errGetAddOnFlags;

    plist->Select(PromotionNo);

    if(!plist->Entries())
        goto errGetAddOnFlags;
    
    pxPromotions* curp;
    while ( (curp = (pxPromotions*) ++iter) != NULL )
    {
        if ( SalesWebOrder )
        {
            if ( curp->IsSNotBySaleseWeb() )
            {
                NotBySalesWeb = true;
                continue;
            }
        }
        if('1' == curp->AddOnPromoDiscOk())
            AddOnPromoDiscount = true;
        if('1' == curp->AddOnStdDiscOk())
            AddOnStdDiscount = true;
    }

errGetAddOnFlags:
    if(plist)
        delete plist;
}

//*********************************************** PreisEKGrossoNaByPriceType *******************************************************
//
// Returns: Gepna, depending on pricetype
nMoney pxOrderItem :: PreisEKGrossoNaByPriceType(const PriceTypeEnum priceType)
{
    if(HEALTHFUND_PRICE == priceType)
    {
        return ArtPriceList()->GetPreisEKGrossoNA(HEALTHFUND_PRICE);
    }
    else
    {
        return ArtPriceList()->GetPreisEKGrossoNA(FREESALE_PRICE);
    }
}

//*********************************************** GetCustomerSurchargePct *******************************************************
//
// Info: 	Handling this surcharge was a request in ID218 of ROLPH-BG
// Returns: customersurcharge, whether by manufacturer surcharge or default surcharge, depending on entries
Decimal pxOrderItem :: GetCustomerSurchargePct()
{
    Decimal retSurcharge(calcdisc::DECINVAL);
    // get search criteria
    long manufacturerNo = ArtBase_->HerstellerNr(); // for search of manufacturer specific surcharge
    long manufacturerNoDefault = 0;                 // for default search if no manufacturer surcharge is specified

    // check if for current manufacturer a surcharge is specified
    if ( GetCustomerSurchargePctByManufacturer(manufacturerNo, retSurcharge) )
    {
        return retSurcharge;
    }

    // if no specific surcharge is specified, search default surcharge of customer
    if ( GetCustomerSurchargePctByManufacturer( manufacturerNoDefault, retSurcharge ) )
    {
        return retSurcharge;
    }

    // if nothing was found, return -1 as surcharge (because 0 can be a valid surcharge)
    return Decimal(calcdisc::DECINVAL);
}

//*********************************************** GetCustomerSurchargePctByManufacturer *******************************************************
//
// Info: 	Handling this surcharge was a request in ID218 of ROLPH-BG
// Returns: true if surcharge was found, false if not // actual surcharge will be returned by reference parameter
bool pxOrderItem :: GetCustomerSurchargePctByManufacturer(long manufacturerNo, Decimal& surcharge)
{
    CustomerSurchargeList_ = new pxCustomerSurchargeList(Session());
    surcharge = Decimal(calcdisc::DECINVAL);

    // get selection criteria
    long  customerNo = Order().Customer()->IDFNr();
    short branchNo   = Order().OrderFilialNr();

    CustomerSurchargeList_->Select( branchNo, customerNo, manufacturerNo );

    if(!CustomerSurchargeList_->Entries())
    {
        return false;
    }

    pxCustomerSurchargeListIter iter(*CustomerSurchargeList_);
    pxCustomerSurcharge* cstSrg;

    cstSrg = (pxCustomerSurcharge*) ++iter;

    surcharge = Decimal(cstSrg->SurchargePct());

    return true;
}

//*********************************************** AddSurchargeToAEP *******************************************************
//
// Returns: will add given surcharge to current AEP
void pxOrderItem :: AddSurchargeToAEP(Decimal& surchargePct, const PriceTypeEnum priceType)
{
    // if invalid, exit
    if ( surchargePct == calcdisc::DECINVAL )
    {
        return;
    }

    Decimal surchargePctCalc = surchargePct;
    Decimal surcharge ( calcdisc::DECZERO );
    // get current AEP
    Decimal originalAEP = Decimal((HEALTHFUND_PRICE == priceType) ? PreisEKGrossoKK() : PreisEKGrossoFV());

    // calculate surcharge and add to AEP
    Decimal newAEP = originalAEP;

    surcharge           = originalAEP;
    surchargePctCalc    /= calcdisc::DEC100;    // divide through 100 to get multiplier
    surcharge           *= surchargePctCalc;    // calc surcharge from gep
    newAEP              += surcharge;           // add surcharge on aep

    newAEP.round(2);
    // if aep has become smaller dont save anything
    if ( newAEP < originalAEP )
    {
        return;
    }
    // set values
    SetCustomerSurchargeAdded(true);
    SetCustomerSurcharge(surchargePct.toFloat64());
    SetPreisEKApo(newAEP.toFloat64());
    SetTHWertAusKsc(); // bit flag so surcharge% is printed on invoice
}

//bool pxOrderItem::hasOmgRebates()
//{
//    /*----------------------------------------------------------------------------*/
//    /*  First check for OMG Rabates. If there is an OMG Condition, no             */
//    /*  further discount calculation and return to caller                         */
//    /*----------------------------------------------------------------------------*/
//    pxValidDiscInfoList* omglist = ValidDiscOmgList();
//    if (omglist != NULL)
//    {
//        if (omglist->Entries() > 0)    // found any entry ??
//        {
//            return true;
//        }
//    }
//    return false;
//}

pxCalcDiscountList* pxOrderItem::createCalcDiscountList(int mode, long baseq, pxCustPharmGroupList* phglist, bool addOnPromoDiscount, bool addOnStdDiscount)
{
    pxCalcDiscountList* calclist;
    pxCustBase& customer = *(Order().Customer());

    /*----------------------------------------------------------------------------*/
    /*  Do just handle special Disinkind on a well contructed                     */
    /*  CustomerPharmacyGroupList                                                 */
    /*----------------------------------------------------------------------------*/
    if (mode == 0)
    {
        calclist = new pxCalcDiscountList(customer, *ArtBase(), this, baseq, phglist);
    }
    else
    {
        calclist = new pxCalcDiscountList(customer, *ArtBase(), this, baseq, mode, addOnPromoDiscount, addOnStdDiscount, phglist);
    }
    Error() = calclist->Error();
    return calclist;
}

pxCalcDiscountList* pxOrderItem::createCalcDiscountList(int mode, long baseq, pxCustPharmGroupList* phglist)
{
    return createCalcDiscountList(mode, baseq, phglist, false, false);
}

void pxOrderItem::writeOrderPosPromoWithInternalDiscount(pxCalcDiscount* calcp)
{
    if (calcp->Promotion_No() != 0)
    {
        WriteOrderPosPromo(calcp->PharmacyGroupId(), 0L, 0L, 0.0, 0L, calcp->Promotion_No(), calcp->InternalDiscount());
    }
}

void pxOrderItem::writeOrderPosPromoWithInternalDiscountAndPromoBaseQty(pxCalcDiscount* calcp)
{
    if (calcp->Promotion_No() != 0)
    {
        WriteOrderPosPromo(calcp->PharmacyGroupId(), 0L, calcp->PromoBaseQty(), 0.0, 0L, calcp->Promotion_No(), calcp->InternalDiscount());
    }
}

void pxOrderItem::writeRefundWithDiscountKey(pxCalcDiscount* calcp)
{
    writeRefund(calcp, calcp->DiscountKey());
}

void pxOrderItem::writeRefund(pxCalcDiscount* calcp, double refundPct)
{
    WriteRefund(calcp->RefundValue(), refundPct, 1, 0, calcp->Promotion_No());
}

void pxOrderItem::addDiscountToExistingOne(pxCalcDiscount* calcp, double newDiscount)
{
    AddDiscountToExistingOne(newDiscount, calcp->PharmacyGroupId(), calcp->RefundValue(), calcp->TurnOverCalcImpact(),
        calcp->Promotion_No(), calcp->DiscountBestBuy());
}

pxItemDiscount* pxOrderItem::createItemDiscount(pxCalcDiscount* calcp)
{
	//return createItemDiscount(calcp->DiscountBestBuy(), calcp->PharmacyGroupId());
	pxItemDiscount* itemdisc = createItemDiscount(calcp->DiscountBestBuy(), calcp->PharmacyGroupId());
	itemdisc->SetInternalDiscountFlag(calcp->InternalDiscount() == '1' ? 1 : 0);
	itemdisc->SetRefundValuePct(calcp->RefundPct());
	itemdisc->SetDiscountCategory(calcp->GetDiscountCategory());
    itemdisc->SetDiscountCalcFrom(calcp->DiscountCalcFrom());
    itemdisc->SetDiscountApplyTo(calcp->DiscountApplyTo());
	return itemdisc;
}

pxItemDiscount* pxOrderItem::createItemDiscount(short const discountType, nString const& pharmacyGroupId)
{
    pxCustBase& customer = *(Order().Customer());
    return new pxItemDiscount(customer.Session(), KdAuftragNr_, PosNr_, discountType, pharmacyGroupId);
}

void pxOrderItem::setSurchargePctOnCustomerSurcharge(pxItemDiscount* itemdisc)
{
    if ( CustomerSurcharge() && CustomerSurchargeAdded() )
    {
        itemdisc->SetSurchargePct(CustomerSurcharge());
    }
}

void pxOrderItem::putItemAndAppendToList(pxItemDiscount* itemdisc)
{
    itemdisc->Put();
    ItemDiscountList()->Append(itemdisc);
}

void pxOrderItem::setMidasAbrechnung(char turnOverCalcImpact)
{
    if (turnOverCalcImpact == '1')
    {
        SetMidasAbrechnung();
    }
}

void pxOrderItem::setNaturalRabattInternOrWriteKdAuftragPosRefund(bool isNrIntern, pxCalcDiscount* calcp, long baseq)
{
    if (isNrIntern)
    {
        SetNaturalRabattIntern();
    }
    else
    {
        WriteKdAuftragPosRefund(KdAuftragNr_, PosNr_, calcp->RefundValue(), calcp->DiscountKey(), baseq, 0, calcp->Promotion_No());
    }
}

void pxOrderItem::setNaturalRabattIntern(bool isNrIntern)
{
    if (isNrIntern)
    {
        SetNaturalRabattIntern();
    }
}

void pxOrderItem::setOrClearNetPriceOnPreisEKApoNetto(bool clearWholesalePrice)
{
    if (PreisEKApoNetto_ <= pxConstants::mZero)  // no discount price got,
    {
        if (clearWholesalePrice)
        {
            PreisEKGrossoNA_ = pxConstants::mZero;        // clear corresponding wholesale price
        }
        ClearNetPrice();
    }
    else
    {
        SetNetPrice();
    }
}

void pxOrderItem::addDiscountAndWriteRefund(pxCalcDiscount* calcp, double pct, nString const& logevent)
{
    blogDebugOnGlobalNoDatabaseWrite(logevent);
    addDiscountToExistingOne(calcp, pct);
    // calcp->DiscountKey() ist der RefundPct!!!
    writeRefundWithDiscountKey(calcp);
    if (calcp->Promotion_No() != 0)
    {
        WriteOrderPosPromo(calcp->PharmacyGroupId(), 0L, calcp->PromoBaseQty(), 0.0, 0L, calcp->Promotion_No(), calcp->InternalDiscount(), pct);
    }
}

void pxOrderItem::blogDebugOnGlobalNoDatabaseWrite(nString const& logevent)
{
    if (!pxGlobalNoDatabaseWrite)
    {
        BLOG_DEBUG( libcsc::LoggerPool::getLoggerDiscountCalc(), logevent() );
    }
}

void pxOrderItem::setPromotionNoOnPromoTypZero(short promotionNo)
{
    if ((promotionNo > 0) && (PromoTyp_ == 0))
    {
        SetPromotionNo(promotionNo);
    }
}

long  pxOrderItem::calculateRebateForOrderedQuantity(const long QOrdered)
{
	long  Retval = 0;
	if ( MengeNatra() == 0)
	{
		Retval = CalcDiscount(QOrdered);
		SetDirty();
	}
	return Retval;
}
