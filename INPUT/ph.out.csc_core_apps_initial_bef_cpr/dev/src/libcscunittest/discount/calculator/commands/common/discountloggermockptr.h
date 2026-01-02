#ifndef GUARD_LIBCSC_UNITTEST_DISCOUNT_LOGGER_MOCK_PTR_H
#define GUARD_LIBCSC_UNITTEST_DISCOUNT_LOGGER_MOCK_PTR_H

#include <boost/shared_ptr.hpp>

namespace libcscUnitTest
{
namespace SuiteTestDiscountCalculatorCommands
{
class IDiscountLogger;
typedef boost::shared_ptr<libcscUnitTest::SuiteTestDiscountCalculatorCommands::DiscountLoggerMock> DiscountLoggerMockPtr;

} // end namespace SuiteTestDiscountCalculatorCommands
} // end namespace libcscUnitTest

#endif // GUARD_LIBCSC_UNITTEST_DISCOUNT_LOGGER_MOCK_PTR_H
