#include "discount/logger/discountlogger/shelldiscountlogger.h"
#include <sstream>
#include <iostream>
#include <discount/calculator/discountcalculatortypemapper.h>

namespace libcsc
{
namespace discount
{
ShellDiscountLogger::ShellDiscountLogger()
{
}

ShellDiscountLogger::~ShellDiscountLogger()
{
}

void ShellDiscountLogger::log( const DiscountCalculatorTypeEnum calcType, const DiscountCalculatorResult & calcResult )
{
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
	m_Messages.push_back( message.str() );
}

void ShellDiscountLogger::save()
{
	std::vector<std::string>::const_iterator iter = m_Messages.begin();
	for( ; iter != m_Messages.end(); ++iter )
	{
		std::cout << ( *iter ) << std::endl;
	}
}

void ShellDiscountLogger::reset()
{
	m_Messages.clear();
}

} // end namespace discount
} // end namespace libcsc
