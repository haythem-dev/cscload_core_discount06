//--------------------------------------------------------------------------------------------------//
/*! \brief 
 *  \author     Bjoern Bischof
 *  \date       22.12.2010
 *  \version    00.00.00.01
 */ //--------------------------------------------------------------------------------------------------//

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include "cmdlineevaluator.h"
#include "cmdlineoption.h"
#include "classinfo_macros.h"
#include "cmdlineexception.h"
#include <assert.h>
#include "cmdlineoption_definitions.h"
#include "loggerpool.h"

//--------------------------------------------------------------------------------------------------//
// class definition section
//--------------------------------------------------------------------------------------------------//
namespace libBatch 
{
namespace cmdLine
{

CmdLineEvaluator::CmdLineEvaluator( const CmdLineConfiguration& cmdLineConfiguration )
: m_CmdLineParser( cmdLineConfiguration.m_Argc, cmdLineConfiguration.m_Argv ), m_Logger( LoggerPool::LoggerCmdLine ), m_OptionPassed( "" )
{
    METHODNAME_DEF( CmdLineEvaluator, CmdLineEvaluator )
    BLOG_TRACE_METHOD( m_Logger, fun );

    if( !checkNumberParameters() ){
        basar::VarString msg( "ERROR: No parameter / options set!" );
        throw libBatch::cmdLine::CmdLineException( basar::ExceptInfo(fun, msg, __FILE__, __LINE__) );
    }

    m_OptionPassed = checkCmdLineOptions();
}

CmdLineEvaluator::~CmdLineEvaluator()
{
    METHODNAME_DEF( CmdLineEvaluator, CmdLineEvaluator )
    BLOG_TRACE_METHOD( m_Logger, fun );
}

void CmdLineEvaluator::loadOptions( OptionsCollector& options ) const
{
    METHODNAME_DEF( CmdLineEvaluator, loadOptions )
    BLOG_TRACE_METHOD( m_Logger, fun );

    assert( options.empty() );

    options.push_back( cmdLine::USAGE         );
    options.push_back( cmdLine::VERSION       );
    options.push_back( cmdLine::HELP          );
    options.push_back( cmdLine::RETURN_VALUES );
    options.push_back( cmdLine::VH            );
}

basar::VarString CmdLineEvaluator::checkCmdLineOptions() const
{   
    METHODNAME_DEF( CmdLineEvaluator, checkCmdLineOptions )
    BLOG_TRACE_METHOD( m_Logger, fun );

    OptionsCollector cmdLineOptions;
    loadOptions( cmdLineOptions );

    OptionsCollector::const_iterator it = cmdLineOptions.begin();
    for( ; it != cmdLineOptions.end(); ++it ){
        if( m_CmdLineParser.isParam(it->c_str()) ){
            return (*it);
        }
    }

    return "";
}

bool CmdLineEvaluator::checkNumberParameters() const
{
    METHODNAME_DEF( CmdLineEvaluator, checkNumberParameters )
    BLOG_TRACE_METHOD( m_Logger, fun );

    return m_CmdLineParser.existArguments();
}

bool CmdLineEvaluator::isOptionSet() const
{
    METHODNAME_DEF( CmdLineEvaluator, isOptionSet )
    BLOG_TRACE_METHOD( m_Logger, fun );

    return !m_OptionPassed.empty();
}

const basar::VarString& CmdLineEvaluator::getOption() const
{
    METHODNAME_DEF( CmdLineEvaluator, getOption )
    BLOG_TRACE_METHOD( m_Logger, fun );

    return m_OptionPassed;
}

void CmdLineEvaluator::evaluate()
{
    METHODNAME_DEF( CmdLineEvaluator, evaluate )
    BLOG_TRACE_METHOD( m_Logger, fun );

    if( !evaluateAppArgs() ){
        basar::VarString msg( "ERROR: No valid application specific parameter / options set!" );
        throw libBatch::cmdLine::CmdLineException( basar::ExceptInfo(fun, msg, __FILE__, __LINE__) );
    }
}

} // end namespace cmdLine
} // end namespace libBatch
