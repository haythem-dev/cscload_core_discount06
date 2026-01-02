#ifndef CALCDISCPCT_H
#define CALCDISCPCT_H

//------------------------------------------------------------------------------

#include <libbasarcmnutil_decimal.h>

typedef basar::Decimal Decimal;

//------------------------------------------------------------------------------

#ifdef USE_BASAR

// used by grp2disc

// pxcstgrp.hpp: keep in sync
class pxCustGroup
{
public:	
	enum CustomerGroupTypeBG
	{
		TypePharmacy           =  1,  // Apotheken
		TypeHospital		   =  6,  // Apothekenbelegschaft (in BG: Krankenhaus)
		TypeExternalWholesaler =  8,  // FREMDGROSSHANDEL + ANDERE AG
		TypeOwnBranch          =  9,  // FILIALE DER EIGENEN AG
		TypeWholesaler         = 12,  // Groﬂh‰ndler
		TypeOwnConsumption     = 13,  // EIGENVERBRAUCH, INT. KONTEN
		TypeWholesalerEG       = 15,  // Groﬂh‰ndler EG
		TypeAssocCompanies	   = 17,  // AssoziierteUnternehmen
		TypeOwnConsumptionAep  = 18   // EIGENVERBRAUCH,INT.KONTEN AEP
	};
};

#endif // USE_BASAR

//------------------------------------------------------------------------------
namespace calcdisc
{

// pxitem.hpp: keep in sync
enum
{
        MAX_RABPCT_EXCLUSIVE = 10
};

//------------------------------------------------------------------------------
//  Const
//------------------------------------------------------------------------------
static const Decimal DECZERO;                                              // default c'tor: 0.0
static const Decimal DECINVAL                             			( -1); // signals NULL value
static const Decimal DECONE_NEG                           			( -1);
static const Decimal DECONE                                       	(  1);
static const Decimal DEC100                                       	(100);
static const Decimal DEC_MAX_RABPCT_EXCLUSIVE (MAX_RABPCT_EXCLUSIVE);

//------------------------------------------------------------------------------
// do not mix up with pxOrderItem::CascadeLevelBG, they keep different values!
enum RebateCascadeLevel
{
	CASCADE_LEVEL_PROMOTION		= 0,
	CASCADE_LEVEL_ARTICLE		= 1,
	CASCADE_LEVEL_MANUFACTURER	= 2,
	CASCADE_LEVEL_RPG			= 3,
	CASCADE_LEVEL_ARTICLEGROUP	= 4,
	CASCADE_LEVEL_CUSTOMER		= 5,
	CASCADE_LEVEL_CUSTOMERGROUP = 6
};

//------------------------------------------------------------------------------
// if margin is SMALLER than this value, special surcharge calculation is necessary
const Decimal MARGINPCT_SURCHARGECALC (0.02);  // = 2%
	
//------------------------------------------------------------------------------
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

	Decimal & discount,					// calculated result
	Decimal & customerSurcharge,		// calculated result (if surcharge was calculated)
	Decimal & calcDiscountPercentage
	
);

//------------------------------------------------------------------------------
bool calcDiscountSurchargePct (
		  Decimal & discount,
	const Decimal & gep,
	const Decimal & gepna,
	const Decimal & surcharge,
	const Decimal & grossProfitPct,
	const short     cascadeLevel,
	const int       customerGroup,
	const int       priceType,
	const Decimal & gepnana_f,
	const Decimal & gepnana_k
);
	
//------------------------------------------------------------------------------
bool isSurchargeCalcNecessary (
	const Decimal & grossProfitPct,
	const Decimal & gep,
	const Decimal & gepnana,
	const short     cascadeLevel,
	const int       customerGroup
);

//------------------------------------------------------------------------------
void getGepnanaByPriceType(
		  Decimal & gepnana,
	const Decimal & gepnana_f,
	const Decimal & gepnana_k,
	const int       priceType
);

//------------------------------------------------------------------------------
void calcGepnana(
	const Decimal & gep,
	const Decimal & invDisc,
	const Decimal & invDiscAnnual,
	const Decimal & rebInKind,
	const Decimal & rebInKindAnnual,
	Decimal       & gepnana);

//------------------------------------------------------------------------------
void getWholesalerMarginPct (
	Decimal & margin,
	const Decimal & gep,
	const Decimal & gepnana
);

//------------------------------------------------------------------------------
void getValueByPriceType (
	const Decimal & gep_f,
	const Decimal & gep_k,
	const int 		priceType,
		  Decimal & gepReturn
);
	
//------------------------------------------------------------------------------
}	// namespace

//------------------------------------------------------------------------------
#endif

