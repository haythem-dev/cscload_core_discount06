//--------------------------------------------------------------------------------------------------//
/*! \brief 
 *  \author     Bjoern Bischof
 *  \date       23.12.2010
 *  \version    00.00.00.01
 */ 
//--------------------------------------------------------------------------------------------------//

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include "cmdlineoption.h"
#include "cmdlineoption_definitions.h"
#include "loggerpool.h"
#include "classinfo_macros.h"

//--------------------------------------------------------------------------------------------------//
// namespace section
//--------------------------------------------------------------------------------------------------//
namespace libBatch 
{
namespace cmdLine
{

CmdLineOption::CmdLineOption( const basar::VarString& option )
: m_Logger( LoggerPool::LoggerCmdLine ), m_Option( option )
{
    METHODNAME_DEF( CmdLineOption, CmdLineOption )
	BLOG_TRACE_METHOD( m_Logger, fun );
}

CmdLineOption::~CmdLineOption()
{
    METHODNAME_DEF( CmdLineOption, ~CmdLineOption )
	BLOG_TRACE_METHOD( m_Logger, fun );
}

bool CmdLineOption::isOptionUsage() const
{
    METHODNAME_DEF( CmdLineOption, isOptionUsage )
	BLOG_TRACE_METHOD( m_Logger, fun );

    return m_Option == USAGE;
}

bool CmdLineOption::isOptionVersion() const
{
    METHODNAME_DEF( CmdLineOption, isOptionVersion )
	BLOG_TRACE_METHOD( m_Logger, fun );

    return m_Option == VERSION;
}

bool CmdLineOption::isOptionHelp() const
{
    METHODNAME_DEF( CmdLineOption, isOptionHelp )
	BLOG_TRACE_METHOD( m_Logger, fun );

    return m_Option == HELP;
}

bool CmdLineOption::isOptionVersionHistory() const
{
    METHODNAME_DEF( CmdLineOption, isOptionVersionHistory() )
	BLOG_TRACE_METHOD( m_Logger, fun );

    return m_Option == VH;
}

bool CmdLineOption::isOptionReturnValues() const
{
    METHODNAME_DEF( CmdLineOption, isOptionReturnValues )
	BLOG_TRACE_METHOD( m_Logger, fun );

    return m_Option == RETURN_VALUES;
}

} // end namespace cmdLine
} // end namespace libBatch
