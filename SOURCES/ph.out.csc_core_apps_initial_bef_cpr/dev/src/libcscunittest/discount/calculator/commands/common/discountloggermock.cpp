#include "cmnut.h"
#include "discountloggermock.h"

namespace libcscUnitTest
{
namespace SuiteTestDiscountCalculatorCommands
{
DiscountLoggerMock::DiscountLoggerMock()
{
}

DiscountLoggerMock::~DiscountLoggerMock()
{
}

void DiscountLoggerMock::log( const libcsc::discount::DiscountCalculatorTypeEnum calcType, const libcsc::discount::DiscountCalculatorResult & calcResult )
{
	m_LogCollection[ calcType ] = calcResult;
}

void DiscountLoggerMock::save()
{
}

const libcsc::discount::DiscountCalculatorResult DiscountLoggerMock::getCalcResult( const libcsc::discount::DiscountCalculatorTypeEnum calcType ) const
{
	DiscountLogCollection::const_iterator iter = m_LogCollection.find( calcType );
	if( iter == m_LogCollection.end() )
	{
		return libcsc::discount::DiscountCalculatorResult();
	}

	return ( iter->second );
}

} // end namespace SuiteTestDiscountCalculatorCommands
} // end namespace libcscUnitTest

