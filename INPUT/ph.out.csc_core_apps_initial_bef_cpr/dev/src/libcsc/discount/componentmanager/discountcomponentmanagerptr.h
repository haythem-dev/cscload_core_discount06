#ifndef GUARD_LIBCSC_DISCOUNT_COMPONENT_MANAGER_PTR_H
#define GUARD_LIBCSC_DISCOUNT_COMPONENT_MANAGER_PTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc
{
namespace discount
{
class DiscountComponentManager;
typedef boost::shared_ptr<libcsc::discount::DiscountComponentManager> DiscountComponentManagerPtr;

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_DISCOUNT_COMPONENT_MANAGER_PTR_H
