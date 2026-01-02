#ifndef GUARD_LIBCSC_I_DISCOUNT_CALCULATOR_COMMAND_PTR_H
#define GUARD_LIBCSC_I_DISCOUNT_CALCULATOR_COMMAND_PTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc
{
namespace discount
{
class IDiscountCalculatorCommand;
typedef boost::shared_ptr<libcsc::discount::IDiscountCalculatorCommand> IDiscountCalculatorCommandPtr;

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_I_DISCOUNT_CALCULATOR_COMMAND_PTR_H
