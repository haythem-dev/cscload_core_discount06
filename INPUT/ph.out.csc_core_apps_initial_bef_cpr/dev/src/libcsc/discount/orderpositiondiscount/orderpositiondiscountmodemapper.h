#ifndef GUARD_LIBCSC_ORDER_POSITION_DISCOUNT_MODE_MAPPER_H
#define GUARD_LIBCSC_ORDER_POSITION_DISCOUNT_MODE_MAPPER_H

#include <ostream>
#include <discount/orderpositiondiscount/orderpositiondiscountmodeenum.h>

namespace libcsc
{
namespace discount
{
class OrderPositionDiscountModeMapper
{
public:
	static std::ostream & toStream( std::ostream & str, const OrderPositionDiscountModeEnum type );

private:
	OrderPositionDiscountModeMapper();
	~OrderPositionDiscountModeMapper();
};

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_ORDER_POSITION_DISCOUNT_MODE_MAPPER_H
