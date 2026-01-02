#ifndef GUARD_LIBCSC_RETURNS_ORDERTYPEFLAGTYPEENUM_H
#define GUARD_LIBCSC_RETURNS_ORDERTYPEFLAGTYPEENUM_H

namespace libcsc {
namespace cscordertype {

	enum OrderTypeFlagTypeEnum
	{
		CONSULTATION_FOR_MSV3_RETURNS_NECESSARY = 1,	// Rücksprache für MSV3 Retourenavis nötig
		NO_LINEFEE_CALCULATION = 2,					    // Keine Berechnung von Zeilenkosten (Ursprung CH PKS1 CPR-190072)
		NO_PACKAGEFEE_CALCULATION = 3,				    // Keine Berechnung von Packungskosten (Ursprung CH PKS1 CPR-190072)
		MUST_HEADLINE = 4							    // Kopfzeile muss eingegeben werden
	};

} //returns
} //libcsc

#endif // GUARD_LIBCSC_RETURNS_ORDERTYPEFLAGTYPEENUM_H
