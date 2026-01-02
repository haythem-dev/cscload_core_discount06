#ifndef GUARD_LIBCSC_ORDER_ITEM_BASE_VALUE_PTR_H
#define GUARD_LIBCSC_ORDER_ITEM_BASE_VALUE_PTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc
{
namespace discount
{
class OrderItemBaseValue;
typedef boost::shared_ptr<libcsc::discount::OrderItemBaseValue> OrderItemBaseValuePtr;

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_ORDER_ITEM_BASE_VALUE_PTR_H
