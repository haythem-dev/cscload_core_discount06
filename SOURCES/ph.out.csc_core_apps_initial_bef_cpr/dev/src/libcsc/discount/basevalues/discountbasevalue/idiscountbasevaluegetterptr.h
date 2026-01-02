#ifndef GUARD_LIBCSC_I_DISCOUNT_BASE_VALUE_GETTER_PTR_H
#define GUARD_LIBCSC_I_DISCOUNT_BASE_VALUE_GETTER_PTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc
{
namespace discount
{
class IDiscountBaseValueGetter;
typedef boost::shared_ptr<libcsc::discount::IDiscountBaseValueGetter> IDiscountBaseValueGetterPtr;

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_I_DISCOUNT_BASE_VALUE_GETTER_PTR_H
