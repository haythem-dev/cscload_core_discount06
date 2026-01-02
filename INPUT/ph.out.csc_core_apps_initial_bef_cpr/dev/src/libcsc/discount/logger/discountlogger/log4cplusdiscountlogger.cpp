#include <discount/logger/discountlogger/log4cplusdiscountlogger.h>
#include <sstream>
#include <logger/loggerpool.h>
#include <discount/calculator/discountcalculatortypemapper.h>

namespace libcsc
{
namespace discount
{
Log4CplusDiscountLogger::Log4CplusDiscountLogger()
{
}

Log4CplusDiscountLogger::~Log4CplusDiscountLogger()
{
}

void Log4CplusDiscountLogger::log( const DiscountCalculatorTypeEnum calcType, const DiscountCalculatorResult & calcResult )
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerDiscountLog(), "Log4CplusDiscountLogger::log()" );

	std::stringstream message;
	DiscountCalculatorTypeMapper::toStream( message, calcType );
	message << ": ";
	if( calcResult.isUnset() )
	{
		message << "<UNSET>";
	}
	else
	{
		message << calcResult;
	}
	BLOG_INFO( LoggerPool::getLoggerDiscountLog(), message.str().c_str() );
}

void Log4CplusDiscountLogger::save()
{
}

void Log4CplusDiscountLogger::reset()
{
}

} // end namespace discount
} // end namespace libcsc
