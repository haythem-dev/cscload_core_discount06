#ifndef GUARD_LIBCSC_ORDER_BASE_VALUE_GETTER_PTR_H
#define GUARD_LIBCSC_ORDER_BASE_VALUE_GETTER_PTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc
{
namespace discount
{
class OrderBaseValueGetter;
typedef boost::shared_ptr<libcsc::discount::OrderBaseValueGetter> OrderBaseValueGetterPtr;

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_ORDER_BASE_VALUE_GETTER_PTR_H
