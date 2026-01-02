#include "discount/resultprocessor/shellresultprocessor.h"
#include <discount/basevalues/orderbasevalue/iorderbasevaluegetter.h>
#include <sstream>
#include <iostream>
#include <discount/calculator/discountcalculatortypemapper.h>

namespace libcsc
{
namespace discount
{
ShellResultProcessor::ShellResultProcessor()
{
}

ShellResultProcessor::~ShellResultProcessor()
{
}

void ShellResultProcessor::process(
	const DiscountCalculatorTypeEnum calcType, 
	const IOrderBaseValueGetterPtr baseValueGetter, 
	const DiscountCalculatorResult & calcResult 
		)
{
	std::stringstream message;
	DiscountCalculatorTypeMapper::toStream( message, calcType );
	message << ": orderNo<" << baseValueGetter->getOrderNo() << ">, positionNo<" << baseValueGetter->getPositionNo() << "> - " << calcResult << std::endl;
	m_Messages.push_back( message.str() );
}

void ShellResultProcessor::print() const
{
	std::vector<std::string>::const_iterator iter = m_Messages.begin();
	for( ; iter != m_Messages.end(); ++iter )
	{
		std::cout << ( *iter ) << std::endl;
	}
}

void ShellResultProcessor::reset()
{
	m_Messages.clear();
}

} // end namespace discount
} // end namespace libcsc
