#ifndef GUARD_LIBCSC_DISCOUNT_CALCULATOR_COMMAND_BASE_PTR_H
#define GUARD_LIBCSC_DISCOUNT_CALCULATOR_COMMAND_BASE_PTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc
{
namespace discount
{
class DiscountCalculatorCommandBase;
typedef boost::shared_ptr<libcsc::discount::DiscountCalculatorCommandBase> DiscountCalculatorCommandBasePtr;

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_DISCOUNT_CALCULATOR_COMMAND_BASE_PTR_H
