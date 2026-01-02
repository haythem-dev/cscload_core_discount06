#include "calcdiscpct.h"

//------------------------------------------------------------------------------

#ifdef USE_BASAR

// used by grp2disc

// pxitem.hpp: keep in sync
class pxOrderItem
{
public:
        enum CascadeLevelBG                    // Cascade levels
        {
                CascadeLevelProductPromotion    =  0,
                CascadeLevelArticle             =  1,
                CascadeLevelManufacturer        =  2,
                CascadeLevelRPG                 =  3,
                CascadeLevelArticleGroup        =  4,
                CascadeLevelCustomer            =  5,
                CascadeLevelPurchaseGroup       =  6,
                CascadeLevelRangePromotion      = 99  //target promotion
        };
};


// types/pricetypeenum.inc: keep in sync
enum PriceTypeEnum
{
	FREESALE_PRICE,                  // 0 = FF(FreiVerkauf) = default
	HEALTHFUND_PRICE,                // 1 = KK(KrankenKasse)
	RETAIL_PRICE,                    // 2 = EV(EinzelHandelsVerkauf)
	LISTFIVE_PRICE       = 5         // 5 = Liste 5 Bulgarian apllication
};

#else

#include <pxsess.hpp>
#include <pxcstgrp.hpp>

#include <pxdevice.hpp>
#include <pxitem.hpp>

#endif

//------------------------------------------------------------------------------
namespace calcdisc
{


//------------------------------------------------------------------------------
// Descr:   Gets half of the margin as the difference between AEP and GEP.
static void aepHalfMargin (
        const Decimal & gep    ,
        const Decimal & aep    ,
        Decimal       & hMargin)
{
        // hMargin = (aep - gep) / 2    :  e.g. (1.09 - 0.96) / 2 = 0.065 EUR
        hMargin  = aep;
        hMargin -= gep;
        hMargin /= 2;

        hMargin.round(2);       // complete cents

        hMargin += gep;         // e.g. 0.96 + 0.07 = 1.03
}

//------------------------------------------------------------------------------
// changed by Y.Bouma Look at Email Mr.Nedelchev from 27.08.2010 (from 0.7 to 0.8)
// Descr:   Returns floor(), if fraction of number is 0.8 or less
//                      Returns ceil (), if fraction of number is higher than 0.8
static void smoothing (
        const Decimal & decNumber,
        Decimal       & decSmooth,
        short         cascadeLevel)
{
        if (decNumber < DECZERO)
        {
                decSmooth = DECZERO;
                return;
        }


        static const Decimal CMP = Decimal(8)/Decimal(10);      // 0.8

        Decimal tmp = decNumber;
        if ( cascadeLevel == pxOrderItem::CascadeLevelArticle)
        {
           tmp.round(3);     // with decimal places
		   // I-17035899
           if ( tmp < (Decimal) 0.005)
		   {
			   tmp = DECZERO;
		   }
		   // I-17035899
		}
        else
        {
           tmp.round(4);
           tmp.trunc(0);       // no decimal places
        }

        decSmooth = tmp;

        // calculate fraction: decNumber - truncated value
      /*tmp *= DECONE_NEG;
        tmp += decNumber;

        if (tmp > CMP)
                decSmooth += DECONE;
       */

}

//------------------------------------------------------------------------------
// Descr:   Gets the Gepnana (Gep minus lots of discounts) from Gep.
// Param:   gep
// Returns: gepnana
//
void calcGepnana (
        const Decimal & gep            ,
        const Decimal & invDisc        ,
        const Decimal & invDiscAnnual  ,
        const Decimal & rebInKind      ,
        const Decimal & rebInKindAnnual,
        Decimal       & gepnana        )
{
        gepnana = gep;

        Decimal tmp;

        // calc mathematically
        tmp      = DECONE;
        tmp     -= invDisc;
        gepnana *= tmp;

        // calc commercially
        tmp      = DECONE;
        tmp     += rebInKind;
        gepnana /= tmp;

        // calc mathematically
        tmp      = DECONE;
        tmp     -= invDiscAnnual;
        gepnana *= tmp;

        // calc commercially
        tmp      = DECONE;
        tmp     += rebInKindAnnual;
        gepnana /= tmp;

        // => gep * (1 - invDisc)
        //        / (1 + rebInKind)
        //        * (1 - invDiscAnnual)
        //        / (1 + rebInKindAnnual)
}

//------------------------------------------------------------------------------
// Descr:   Reduces the discount regarding days of payment period.
// Param:   original discount
// Returns: new discount
static void diminishDiscount (
        const Decimal & discount           ,
        bool            cstIsDiscountExcept,
        short           paymentTarget      ,
        Decimal       & diminished         )
{
        diminished = discount;

        if (paymentTarget < 0)
                return;

        // reduce discount
        if (cstIsDiscountExcept)
        {
                if(paymentTarget > 90)
                        diminished = DECZERO;

                return;
        }

        if (paymentTarget <= 15)
                diminished -= Decimal(2);
        else
        {
                if (paymentTarget <= 30)
                        diminished -= Decimal(3);
                else
                {
                        if (paymentTarget <= 45)
                                diminished -= Decimal(4);
                        else
                        {
                                if (paymentTarget <= 60)
                                        diminished -= Decimal(5);
                                else
                                {
                                        if (paymentTarget <= 90)
                                                diminished -= Decimal(7);
                                        else
                                                diminished = DECZERO;
                                }
                        }
                }
        }
}

//------------------------------------------------------------------------------
// Descr:   Reduces the discount for exclusive article.
// Param:   original discount
// Returns: reduced  discount
static void reduceDiscountForExclusiveArticle(
        const Decimal & discount       ,
        short           cascadeLevel   ,
        bool            artIsSortiment2,
        int             customerGroup  ,
        Decimal       & reduced        )
{
        reduced = discount;

        // discount for ABDA-Code must not be higher than MAX_RABPCT_EXCLUSIVE:
        // artIsSortiment2: this article is an exclusive article

        if ( artIsSortiment2                           &&
                (discount      > DEC_MAX_RABPCT_EXCLUSIVE) &&
                (cascadeLevel != pxOrderItem::CascadeLevelArticle     )   )
        {
                reduced = ( pxCustGroup::TypeWholesaler == customerGroup)
                            ? DECZERO
                                : DEC_MAX_RABPCT_EXCLUSIVE;
        }
}

//------------------------------------------------------------------------------
// Descr:   Calculates discount percentage for Rohertrag (Rabatt-Prozentsatz, Tab, Spalte 2)
// Param:   GrossProfitPct
// Returns: discount as percentage, e.g. 3.0 for 3% (percentage is always integer!)
//
// ATTENTION:
// All identifiers with suffix "pct"  are percentages between 0 and 100
// All identifiers without suffix "pct" can be used for calculation without dividing by 100
// Example: GrossProfitPct=3  ===>  GrossProfit=0.03

void calcDiscountPercentage (
        Decimal & grossProfitPct,
        Decimal & grossProfitFVPct,
        short     cascadeLevel,

        int       customerGroup,
        bool      cstIsCommercialRounding,
        bool      cstIsMathematicalRounding,
        bool      cstIsHalfMargin,
        bool      cstIsDiscountExcept,
        short     paymentTarget0,
        short     paymentTarget1,

        bool      artIsSortiment2,
        Decimal & invDisc,
        Decimal & rebInKind,
        Decimal & invDiscAnnual,
        Decimal & rebInKindAnnual,
        Decimal & custRebRedPct,

        Decimal & aep_f,
        Decimal & gep_f,
        Decimal & aep_k,
        Decimal & gep_k,
		Decimal & gepna,

        int       priceType,
        bool      isTenderOrder,

        Decimal & discount,             // calculated result
		Decimal & customerSurcharge,	// calculated result (if surcharge was calculated)
		Decimal & customerGrossProfitPct
)
{

        grossProfitPct.round(2);
        grossProfitFVPct.round(2);
        invDisc.round(4);
        rebInKind.round(4);
        invDiscAnnual.round(4);
        rebInKindAnnual.round(4);
        custRebRedPct.round(2);

        aep_f.round(2);
        gep_f.round(2);
        aep_k.round(2);
        gep_k.round(2);
        gepna.round(2);

        if (DECINVAL == invDisc)
                invDisc = DECZERO;

        if (DECINVAL == invDiscAnnual)
                invDiscAnnual = DECZERO;

        if (DECINVAL == rebInKind)
                rebInKind = DECZERO;

        if (DECINVAL == rebInKindAnnual)
                rebInKindAnnual = DECZERO;

       /* if (DECINVAL == custRebRedPct)
                custRebRedPct = DECZERO;

        */
        if (DECINVAL == aep_f)
        {
                discount = DECZERO;
                return;         // Error: AEP for freesales must exist
        }

        if (DECINVAL == gep_f)
        {
                discount = DECZERO;
                return;         // Error: GEP for freesales must exist
        }

        if (DECINVAL == aep_k)
                aep_k = DECZERO;

        if (DECINVAL == gep_k)
                gep_k = DECZERO;
				
		if (DECINVAL == gepna)
                gepna = DECZERO;				

        //------------- initialization:

        // prices:
		Decimal gep; // can be gep_f or gep_k, depending on pricetype
        Decimal aep2_k;
        Decimal gepnana_f;
        Decimal gepnana_k;

		getValueByPriceType( gep_f, gep_k, priceType, gep );
        aepHalfMargin(gep_k, aep_k, aep2_k);
        calcGepnana  (gep_f, invDisc, invDiscAnnual, rebInKind, rebInKindAnnual, gepnana_f);
        calcGepnana  (gep_k, invDisc, invDiscAnnual, rebInKind, rebInKindAnnual, gepnana_k);

        // percentages:
        grossProfitFVPct 	 /= DEC100;
        grossProfitPct   	 /= DEC100;
		
		// Special surcharge calculation, if surcharge was calculated, skip normal rebate calculation and exit
		// For further details see ROLPH-BG, ID218
		if ( calcDiscountSurchargePct(discount, gep, gepna, customerSurcharge, customerGrossProfitPct, cascadeLevel, customerGroup, priceType, gepnana_f, gepnana_k) ){ // test values
			return ;
		} else {
			customerSurcharge = DECINVAL; // signalize that surcharge is ignored
		}
		
        // freesale or healthfund (whole or half margin):
        bool freesaleLogic        = false;
        bool healthfundLogic_half = false;
        bool healthfundLogic_full = false;

        if (HEALTHFUND_PRICE == priceType)
        {
                if(cstIsHalfMargin)
                        healthfundLogic_half = true;
                else
                        healthfundLogic_full = true;
        }
        else
        {
                // priceType: 0 or 2
                freesaleLogic = true;
        }

        // tender orders are freesale:
        if (isTenderOrder)
                freesaleLogic = true;

        //------------------ calculation


        Decimal rabPct;         // 0.0

        // There are 2 possibilities: mathematical or commercial calculation
        // This is set in customer master data.

        // commercial / divided way:
        // At the moment calculate commercial way regardless what is set for the customer
        // Later (after Boyan has developed the mathematical way of calculating) take this if clause:
        // if(cstIsCommercialRounding) {

        if(cstIsCommercialRounding || cstIsMathematicalRounding)
        {
                // discounts:
                Decimal rabPct_f;       // 0.0
                Decimal rabPct_k;       // 0.0

                if(freesaleLogic || healthfundLogic_full)
                {
                        // ALT: denominator = grossProfitFVPct * aep_f + gepnana_f;
                        // NEU: denominator = grossProfitPct * aep_f + gepnana_f;
                        Decimal denominator = grossProfitPct;
                        denominator        *= aep_f;
                        denominator        += gepnana_f;

                        if (DECZERO == denominator)
                        {
                                discount = DECZERO;
                                return;
                        }

                        // rabPct_f = 100 * (aep_f/denominator - 1) + custRebRedPct
                        rabPct_f  = aep_f;
                        rabPct_f /= denominator;
                        rabPct_f -= DECONE;
                        rabPct_f *= DEC100;
                       // rabPct_f += custRebRedPct;                   //CPR-170555

                        smoothing(rabPct_f, rabPct, cascadeLevel);
                }

                if (healthfundLogic_half)
                {
                        // denominator = grossProfitPct * aep2_k + gepnana_k
                        Decimal denominator = grossProfitPct;
                        denominator        *= aep2_k;
                        denominator        += gepnana_k;

                        if (DECZERO == denominator)
                        {
                                discount = DECZERO;
                                return;
                        }

                        // rabPct_k = 100 * (aep2_k/denominator - 1) + custRebRedPct
                        rabPct_k  = aep2_k;
                        rabPct_k /= denominator;
                        rabPct_k -= DECONE;
                        rabPct_k *= DEC100;
                       // rabPct_k += custRebRedPct;                  //CPR-170555

                        smoothing(rabPct_k, rabPct, cascadeLevel);
                }

                if (healthfundLogic_full)
                {
                        // denominator1 = 1 + rabPct/100
                        Decimal denominator1 = rabPct;
                        denominator1 /= DEC100;
                        denominator1 += DECONE;

                        if (DECZERO == denominator1)
                        {
                                discount = DECZERO;
                                return;
                        }

                        // denominator2 = aep_f/denominator1 - gepnana_f + gepnana_k
                        Decimal denominator2 = aep_f;
                        denominator2 /= denominator1;
                        denominator2 -= gepnana_f;
                        denominator2 += gepnana_k;


                        if (DECZERO == denominator2)
                        {
                                discount = DECZERO;
                                return;
                        }

                        // rabPct_k = 100 * (aep_k - (aep_f/denominator1 - gepnana_f + gepnana_k))
                        //          / denominator2;

                        rabPct_k  = aep_f;
                        rabPct_k /= denominator1;
                        rabPct_k -= gepnana_f;
                        rabPct_k += gepnana_k;
                        rabPct_k *= DECONE_NEG;
                        rabPct_k += aep_k;
                        rabPct_k *= DEC100;
                        rabPct_k /= denominator2;

                        smoothing(rabPct_k, rabPct, cascadeLevel);
                }
        }       // if(cstIsCommercialRounding || cstIsMathematicalRounding)


        // mathematical / multiplied way:
        // this will follow in far future

        //------------------ adaptation of calculated discount:
        short paymentTarget = (HEALTHFUND_PRICE == priceType)
                                ? paymentTarget1
                                                : paymentTarget0;

		rabPct += custRebRedPct;                              // CPR_170555

        if(!pxCustGroup::TypeHospital == customerGroup)
        {

                diminishDiscount(rabPct, cstIsDiscountExcept, paymentTarget, rabPct);
        }

        reduceDiscountForExclusiveArticle(rabPct,
                                                  cascadeLevel,
                                                                          artIsSortiment2,
                                                                          customerGroup,
                                                                          rabPct);

        // discount must not be higher than 100%:
        if (rabPct > DEC100)
                rabPct = DEC100;

        // discount must not be lower than 0%:
        if (rabPct < DECZERO)
                rabPct = DECZERO;

        discount = rabPct;
}

//------------------------------------------------------------------------------
// Descr:   Special rebate and surcharge calculation, but only if necessary -> see return values (ROLPH-BG ID218)
// Returns: True if special rebate and surcharge calculation was done/necessary, false if no calculations done!
//
bool calcDiscountSurchargePct(
		  Decimal & discount,
	const Decimal & gep,
	const Decimal & /*gepna*/,
	const Decimal & surcharge,
	const Decimal & grossProfitPct,
	const short     cascadeLevel,
	const int       customerGroup,
	const int       priceType,
	const Decimal & gepnana_f,
	const Decimal & gepnana_k
)
{	
	Decimal gepnana;
	getGepnanaByPriceType( gepnana, gepnana_f, gepnana_k, priceType );

	// if no surcharge defined, it is not possible to handle calculation
	if ( DECINVAL == surcharge ){
		return false;
	}
	// check if special calculation necessary, if not, exit with false
	if ( !isSurchargeCalcNecessary( grossProfitPct, gep, gepnana, cascadeLevel, customerGroup ) ){
		return false;
	}
	
	Decimal marginPct;
	Decimal profit;
	Decimal surchargePct = surcharge;
	
	surchargePct /= DEC100;
	
	// get margin
	getWholesalerMarginPct ( marginPct, gep, gepnana );
	
	// get profit (margin + surcharge)
	profit += surchargePct;
	profit += marginPct;
		
	// calculate rebate ( if current profit is greater than defined grossprofit, give the rest as discount )
	if ( grossProfitPct < profit ){
		Decimal rest = profit;
		rest -= grossProfitPct;
		discount = rest;
		discount *= DEC100;
	} else {
		discount = DECZERO;
	}

	return true;
}

//------------------------------------------------------------------------------
// Descr:   Returning gepnana_f or gepnana_k depending on booked pricetype
//
void getGepnanaByPriceType(
	      Decimal & gepnana,
	const Decimal & gepnana_f,
	const Decimal & gepnana_k,
	const int       priceType
)
{
	if(HEALTHFUND_PRICE==priceType){
		gepnana = gepnana_k;
    }else{
		gepnana = gepnana_f;
	}
}

//------------------------------------------------------------------------------
// Descr:   Checks if it is necessary to make special rebate/surcharge calculation for wholesalers (ROLPH-BG ID218)
// Param:   GrossProfitPct, GEP, GEPNA, CascadeLevel, CustomerGroup
// Returns: True if special calculation is necessary instead of the "normal" one, false if needs normal calculation
//
bool isSurchargeCalcNecessary(
	const Decimal & grossProfitPct,
	const Decimal & gep,
	const Decimal & gepnana,
	const short     /*cascadeLevel*/,
	const int       customerGroup
)
{
	// only if customer is wholesaler, if not exit
	if ( pxCustGroup::TypeWholesaler != customerGroup ){
		return false;
	}
	// only if gep is defined, if not exit I-15010677
	if ( gep == DECZERO ) {
		return false;
	}
	// only if grossprofit is defined, if not exit
	if ( grossProfitPct == DECZERO ) {
		return false;
	}
	
	Decimal marginPct = DECZERO;
	getWholesalerMarginPct( marginPct, gep, gepnana );

	// only if margin% is smaller than profit%, if not exit
	if ( marginPct > grossProfitPct ){
		return false;
	}
	// only if margin is smaller than defined fixed value, if not exit	
	if ( marginPct >= MARGINPCT_SURCHARGECALC ){
		return false;
	}

	// passed all conditions, so it is necessary
	return true;
}

//------------------------------------------------------------------------------
// Descr:   Calculating margin for wholesaler customers
// Param:   Margin (as reference, contains return value), GEP, GEPNA
// Returns: Calculated margin via reference parameter
//
void getWholesalerMarginPct(
	Decimal & marginPct,
	const Decimal & gep,
	const Decimal & gepnana
)
{
	// for wholesalers, the margin is gep - gepna
	marginPct = gep;
	marginPct -= gepnana;
	marginPct /= gep;
	//marginPct *= DEC100;
}

//------------------------------------------------------------------------------
// Returns: Returns the value depending on current pricetype (by reference parameter gepReturn)!
//			if PriceType = KK then value_k will be returned, else the other pricetype
//
void getValueByPriceType (
	const Decimal & value_f,
	const Decimal & value_k,
	const int 		priceType,
		  Decimal & gepReturn
)
{
	if(HEALTHFUND_PRICE==priceType){
	    gepReturn = value_k;
    }else{
        gepReturn = value_f;
	}
}

//------------------------------------------------------------------------------
}       // namespace

