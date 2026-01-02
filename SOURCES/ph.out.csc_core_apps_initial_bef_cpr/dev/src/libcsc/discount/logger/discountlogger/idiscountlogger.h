#ifndef GUARD_LIBCSC_I_DISCOUNT_LOGGER_H
#define GUARD_LIBCSC_I_DISCOUNT_LOGGER_H

#include <discount/calculator/discountcalculatortypeenum.h>
#include <discount/calculator/discountcalculatorresult.h>

namespace libcsc
{
namespace discount
{
// real logging during calculation
class IDiscountLogger
{
public:
	virtual ~IDiscountLogger() {}

	virtual void log( const DiscountCalculatorTypeEnum calcType, const DiscountCalculatorResult & calcResult ) = 0;
	virtual void save() = 0;
};

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_I_DISCOUNT_LOGGER_H
