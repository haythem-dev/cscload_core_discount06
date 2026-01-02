#ifndef CALC_AVP_H
#define CALC_AVP_H

#include <libbasarcmnutil_decimal.h>

namespace calcavp
{
const basar::Decimal CalcAvp(
	const basar::Decimal & customerArticleSurchargePct, // aus cstcalcavp
    const basar::Decimal & customerArticleDeductionPct, // aus cstcalcavp
    const short customerArticlePriceBasis, // aus cstcalcavp

	const basar::Decimal & customerSurchargePctKK, // aus kunde
    const basar::Decimal & customerDeductionPctKK, // aus kunde
    const short customerSurchargeBasicKK, // aus kunde

	const basar::Decimal & customerSurchargePct, // aus kunde
    const basar::Decimal & customerDeductionPct, // aus kunde
    const short customerSurchargeBasic, // aus kunde

	const basar::Decimal & generalPercentPreScript,	// aus generalcalcavp
	const basar::Decimal & generalPercentNoPreScript,	// aus generalcalcavp

	const basar::Decimal & gep,
	const basar::Decimal & aep,
	const basar::Decimal & vat,
	const basar::Decimal & PreisFaktur,
	const basar::Decimal & maxSurcharge, 
	const basar::Decimal & maxAvp,

	const bool isMedicine,
	const bool isPrescriptionNeeded,
	const bool isVatRegistered,
	const bool isHealthFund,
	const bool isDeduction,

	basar::Decimal & avp,
	basar::Decimal & avpDiscounted,
	basar::Decimal & surchargePct,
	basar::Decimal & deductionPct,
	basar::Decimal & surcharge,
	basar::Decimal & surchargeDiscounted
		);

const basar::Decimal getSurchargePercentage(
	const basar::Decimal & customerArticleSurchargePct, // aus cstcalcavp
    const basar::Decimal & customerArticleDeductionPct, // aus cstcalcavp
    const short customerArticlePriceBasis, // aus cstcalcavp

	const basar::Decimal & customerSurchargePctKK, // aus kunde
    const basar::Decimal & customerDeductionPctKK, // aus kunde
    const short customerSurchargeBasicKK, // aus kunde

	const basar::Decimal & customerSurchargePct, // aus kunde
    const basar::Decimal & customerDeductionPct, // aus kunde
    const short customerSurchargeBasic, // aus kunde

	const basar::Decimal & generalPercentPreScript,	// aus generalcalcavp
	const basar::Decimal & generalPercentNoPreScript,	// aus generalcalcavp

	const bool isPrescriptionNeeded,
	const bool isHealthFund,

	short & PriceBasis, 
	basar::Decimal & SurchargePct, 
	basar::Decimal & DeductionPct 
		);

const basar::Decimal CalcSurcharge(
	const basar::Decimal & basePrice, 
	const basar::Decimal & surchargePct, 
	const basar::Decimal & maxSurcharge, 
	const basar::Decimal & vat, 
	const bool isMedicine, 
	const bool isVatRegistered
		);

bool isMedicine(
	const short pricegroup
		);

} // end namespace calcavp

#endif // CALC_AVP_H