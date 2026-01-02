#ifndef GUARD_LIBCSC_UNITTEST_DISCOUNT_LOGGER_MOCK_H
#define GUARD_LIBCSC_UNITTEST_DISCOUNT_LOGGER_MOCK_H

#include <discount/logger/discountlogger/idiscountlogger.h>
#include <map>
	
namespace libcscUnitTest
{
namespace SuiteTestDiscountCalculatorCommands
{
class DiscountLoggerMock : public libcsc::discount::IDiscountLogger
{
public:
	DiscountLoggerMock();
	virtual ~DiscountLoggerMock();

	virtual void log( const libcsc::discount::DiscountCalculatorTypeEnum calcType, const libcsc::discount::DiscountCalculatorResult & calcResult );
	virtual void save();

	const libcsc::discount::DiscountCalculatorResult getCalcResult( const libcsc::discount::DiscountCalculatorTypeEnum calcType ) const;

private:
	DiscountLoggerMock( const DiscountLoggerMock & );
	DiscountLoggerMock & operator=( const DiscountLoggerMock & );

	typedef std::map<libcsc::discount::DiscountCalculatorTypeEnum, libcsc::discount::DiscountCalculatorResult> DiscountLogCollection;

	DiscountLogCollection	m_LogCollection;
};

} // end namespace SuiteTestDiscountCalculatorCommands
} // end namespace libcscUnitTest

#endif // GUARD_LIBCSC_UNITTEST_DISCOUNT_LOGGER_MOCK_H
