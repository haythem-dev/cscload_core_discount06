#ifndef GUARD_LIBCSC_I_ORDER_BASE_VALUE_GETTER_PTR_H
#define GUARD_LIBCSC_I_ORDER_BASE_VALUE_GETTER_PTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc
{
namespace discount
{
class IOrderBaseValueGetter;
typedef boost::shared_ptr<libcsc::discount::IOrderBaseValueGetter> IOrderBaseValueGetterPtr;

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_I_ORDER_BASE_VALUE_GETTER_PTR_H
