#ifndef GUARD_LIBCSC_I_DISCOUNT_BASE_VALUE_REPOSITORY_H
#define GUARD_LIBCSC_I_DISCOUNT_BASE_VALUE_REPOSITORY_H

#include <discount/basevalues/discountbasevalue/discountbasevaluecollectionptr.h>
#include <discount/basevalues/orderbasevalue/iorderbasevaluegetterptr.h>

namespace libcsc
{
namespace discount
{
class IDiscountBaseValueRepository
{
public:
	virtual ~IDiscountBaseValueRepository() {}

	virtual DiscountBaseValueCollectionPtr get() = 0;
	virtual DiscountBaseValueCollectionPtr findByArticle( const IOrderBaseValueGetterPtr orderBaseValue ) const = 0;
	virtual DiscountBaseValueCollectionPtr findByOrder( const IOrderBaseValueGetterPtr orderBaseValue ) const = 0;
};

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_I_DISCOUNT_BASE_VALUE_REPOSITORY_H
