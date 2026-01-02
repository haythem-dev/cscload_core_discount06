#ifndef GUARD_LIBCSC_I_HIERARCHY_LOGGER_H
#define GUARD_LIBCSC_I_HIERARCHY_LOGGER_H

#include "discount/calculator/discountcalculatortypeenum.h"
#include "discount/calculator/discountcalculatorresult.h"

namespace libcsc
{
namespace discount
{
// logging of result and hierarchy info
class IHierarchyLogger
{
public:
	virtual ~IHierarchyLogger() {}

	virtual void log(
		const DiscountCalculatorTypeEnum parentCalcType, 
		const DiscountCalculatorTypeEnum calcType, 
		const DiscountCalculatorResult & calcResult 
			) = 0;
};

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_I_HIERARCHY_LOGGER_H
