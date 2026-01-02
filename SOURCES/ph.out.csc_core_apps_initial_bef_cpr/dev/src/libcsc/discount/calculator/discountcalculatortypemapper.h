#ifndef GUARD_LIBCSC_DISCOUNT_CALCULATOR_TYPE_MAPPER_H
#define GUARD_LIBCSC_DISCOUNT_CALCULATOR_TYPE_MAPPER_H

#include <ostream>
#include <discount/calculator/discountcalculatortypeenum.h>

namespace libcsc
{
namespace discount
{
class DiscountCalculatorTypeMapper
{
public:
	static std::ostream & toStream( std::ostream & str, const DiscountCalculatorTypeEnum type );

private:
	DiscountCalculatorTypeMapper();
	~DiscountCalculatorTypeMapper();
};

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_DISCOUNT_CALCULATOR_TYPE_MAPPER_H
