#ifndef GUARD_LIBCSC_ORDER_POSITION_DISCOUNT_MODE_ENUM_H
#define GUARD_LIBCSC_ORDER_POSITION_DISCOUNT_MODE_ENUM_H

#include <datatypes/property.hpp>

namespace libcsc
{
namespace discount
{
enum OrderPositionDiscountModeEnum
{
	// contains values from cdiscountmodes
	DM_UNSET = 0,
	
	// General
	DM_FIXED_PRICE_MODE = 1,
	
	// Croatia
	DM_RETAIL = 2,
	DM_WHOLESALE_PERCENT_MODE = 3,
	DM_WHOLESALE_INDUSTRY_PERCENT_MODE = 4,
	DM_WHOLESALE_REBATE_IN_KIND_MODE = 5,
	DM_WHOLESALE_INDUSTRY_REBATE_IN_KIND_MODE = 6,
	// 7 = kroatischer Rechnungsrabatt aus DKKUL-KULEP --> direkt in Faktur vergeben

	// France
	DM_PERCENT_MODE = 8,
	DM_FIXED_DISCOUNT_VALUE_MODE = 9,
	DM_REBATE_IN_KIND_MODE = 10,

	// Switzerland
	DM_ABP_BASEPRICE_MODE = 11,					// 11 = AGP ALS BASISPREIS
	DM_OMG_REBATE_MODE = 12,					// 12 = OMG-RABATT
	DM_FIX_LOGISTIC_SURCHARGE_MODE = 13,		// 13 = FIXER LOGISTIGZUSCHLAG AUS CDISCOUNT
	// 14 TATSAECHLICH BERECHNETER LOGISTIKZUSCHLAG --> direkt in Faktur vergeben
	// 15 MINDESTLOGISTIKZUSCHLAG (ZEILENWERT ON-TOP) --> direkt in Faktur vergeben
	// 16 BTM-GEBUEHR SCHWEIZ-VARIANTE (ADDIEREN AUF POSITIONSWERT) --> direkt in Faktur vergeben
	// 17 KUEHLWANNENGEBUEHR AUS KUL-DOKUGEB --> direkt in Faktur vergeben
		DM_CASH_REBATE_MODE = 18,					// 18 = ERFASSTER (Manueller) BARRABATT IN %
	// 19 TATSAECHLICH.LOGISTIKZUSCHLAG --> direkt in Faktur vergeben
	// 20 ZEILENKOSTEN(ZEILENWERT) --> direkt in Faktur vergeben
	// 21 PACKUNGSKOSTEN --> direkt in Faktur vergeben
	// 22 GELDWERTE LEISTUNGEN --> direkt in Faktur vergeben
	// 23 VERSANDKOSTEN --> direkt in Faktur vergeben

	// Germany DEPricing
	DM_FIXED_PRICE_CONCEPT_DEAP_MODE = 24,		// 24 = KONZEPT-/FIXPREIS DEINE APOTHEKE
	DM_FIXED_PRICE_CONCEPT_MVDA_MODE = 25,		// 25 = KONZEPT-/FIXPREIS MVDA
	DM_CASH_REBATE_AS_PRICE_MODE = 26,			// 26 =	PROZENTRABATT DER ALS SONDERPREIS AUSGEWIESEN WIRD
		DM_SURCHARGE_EXF_MODE = 27,					// 27 = AUFSCHLAG AUF GEP (Z.B. PERSONAL)

		// 28 --> % -RAB.AUF BASIS SEP - FERA
		// 29 --> % -RAB.AUF BASIS ART - MIBO
		// 30 --> RECHN. - RAB.AUF BASIS SEK - ZUAB
		// 31 --> RECHN. - ZUS.AUF BASIS SEK - ZUAB
		DM_LOGISTIC_DATATRANSFER_MODE = 32
};

typedef libcsc::Property<OrderPositionDiscountModeEnum> OrderPositionDiscountMode; 

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_ORDER_POSITION_DISCOUNT_MODE_ENUM_H
