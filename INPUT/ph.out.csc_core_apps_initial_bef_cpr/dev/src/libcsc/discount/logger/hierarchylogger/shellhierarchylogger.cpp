#include <discount/logger/hierarchylogger/shellhierarchylogger.h>
#include <discount/calculator/discountcalculatortypemapper.h>

namespace libcsc
{
namespace discount
{
ShellHierarchyLogger::ShellHierarchyLogger()
{
}

ShellHierarchyLogger::~ShellHierarchyLogger()
{
}

void ShellHierarchyLogger::log(
	const DiscountCalculatorTypeEnum parentCalcType, 
	const DiscountCalculatorTypeEnum calcType, 
	const DiscountCalculatorResult &
		)
{
	std::string indent;
	std::map<DiscountCalculatorTypeEnum, std::string>::const_iterator parentIter = m_LineIndents.find( parentCalcType );
	if( parentIter == m_LineIndents.end() )
	{
		m_LineIndents[ parentCalcType ] = indent;
	}
	else
	{
		indent = parentIter->second;
	}

	indent.append( "  " );
	m_LineIndents[ calcType ] = indent;

	std::stringstream message;
	message << indent;
	DiscountCalculatorTypeMapper::toStream( message, calcType );
	m_Messages.push_back( message.str() );
}

void ShellHierarchyLogger::print() const
{
	std::vector<std::string>::const_iterator iter = m_Messages.begin();
	for( ; iter != m_Messages.end(); ++iter )
	{
		std::cout << ( *iter ) << std::endl;
	}
}

std::ostream & ShellHierarchyLogger::toStream( std::ostream & str ) const
{
	std::vector<std::string>::const_iterator iter = m_Messages.begin();
	for( ; iter != m_Messages.end(); ++iter )
	{
		str << ( *iter ) << std::endl;
	}

	return str;
}

void ShellHierarchyLogger::reset()
{
	m_Messages.clear();
	m_LineIndents.clear();
}

} // end namespace discount
} // end namespace libcsc