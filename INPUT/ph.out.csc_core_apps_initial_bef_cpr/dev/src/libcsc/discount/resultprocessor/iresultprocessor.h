#ifndef GUARD_LIBCSC_I_RESULT_PROCESSOR_H
#define GUARD_LIBCSC_I_RESULT_PROCESSOR_H

#include <discount/calculator/discountcalculatortypeenum.h>
#include <discount/calculator/discountcalculatorresult.h>
#include <discount/basevalues/orderbasevalue/iorderbasevaluegetterptr.h>

namespace libcsc
{
namespace discount
{
// saving results to store in orderpositiondiscount
class IResultProcessor
{
public:
	virtual ~IResultProcessor() {}

	virtual void process( 
		const DiscountCalculatorTypeEnum calcType, 
		const IOrderBaseValueGetterPtr baseValueGetter, 
		const DiscountCalculatorResult & calcResult 
			) = 0;
};

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_I_RESULT_PROCESSOR_H
