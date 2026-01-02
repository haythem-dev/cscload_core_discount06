#ifndef GUARD_LIBCSC_I_DISCOUNT_LOGGER_PTR_H
#define GUARD_LIBCSC_I_DISCOUNT_LOGGER_PTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc
{
namespace discount
{
class IDiscountLogger;
typedef boost::shared_ptr<libcsc::discount::IDiscountLogger> IDiscountLoggerPtr;

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_I_DISCOUNT_LOGGER_H
