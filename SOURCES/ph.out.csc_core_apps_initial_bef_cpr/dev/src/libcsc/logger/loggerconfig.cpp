#include "loggerconfig.h"
#include <libbasarcmnutil.h>
#include <log4cplus/logger.h> 
#include <log4cplus/configurator.h>
#include "loggerpool.h"
#include <sys/stat.h>
#include <stdlib.h>
#include <sstream>
#include <iomanip>

namespace libcsc
{
LoggerConfig::LoggerConfig( const basar::VarString & moduleName )
: m_ModuleName( moduleName )
{
}

void LoggerConfig::doConfigure( const basar::Int16 branchno, const basar::Int32 orderno, const basar::Int32 customerno )
{
	BLOG_TRACE( LoggerPool::getLoggerInfrastructure(), "LoggerConfig::doConfigure()" );

	if( LoggerPool::getLoggerInfrastructure().isEnabledFor( log4cplus::TRACE_LOG_LEVEL ) )
	{
		std::stringstream ss;
		ss << "branchno=<" << branchno << ">";
		ss << ", orderno=<" << orderno << ">";
		ss << ", customerno=<" << customerno << ">";
		LoggerPool::getLoggerInfrastructure().forcedLog( log4cplus::TRACE_LOG_LEVEL, ss.str().c_str(), __FILE__, __LINE__ );
	}

	basar::VarString configFilename( getConfigFilename( branchno ) );

	if( LoggerPool::getLoggerInfrastructure().isEnabledFor( log4cplus::TRACE_LOG_LEVEL ) )
	{
		std::stringstream ss;
		ss << "configFilename=<" << configFilename.c_str() << ">";
		LoggerPool::getLoggerInfrastructure().forcedLog( log4cplus::TRACE_LOG_LEVEL, ss.str().c_str(), __FILE__, __LINE__ );
	}

	StringCollection envStrings;

	std::stringstream ss;
	ss << "BRANCHNO=" << branchno;
	envStrings.push_back( ss.str().c_str() );

	ss.str( "" );
	ss << "ORDERNO=" << orderno;
	envStrings.push_back( ss.str().c_str() );

	ss.str( "" );
	ss << "CUSTOMERNO=" << customerno;
	envStrings.push_back( ss.str().c_str() );

	setEnvironment( envStrings );
	log4cplus::PropertyConfigurator::doConfigure( configFilename.c_str() );
}

void LoggerConfig::setEnvironment( const StringCollection & envStrings ) const
{
	StringCollection::const_iterator iter = envStrings.begin();
	for( ; iter != envStrings.end(); ++iter )
	{
#ifdef WIN32 
		int dummy = _putenv( ( *iter ).c_str() ); dummy;
#else
		putenv( const_cast<char *>( ( *iter ).c_str() ) ); 
#endif
	}
}

const basar::VarString LoggerConfig::getConfigFilename( const basar::Int16 branchno ) const
{
	BLOG_TRACE( LoggerPool::getLoggerInfrastructure(), "LoggerConfig::getConfigFilename()" );

	basar::VarString baseConfigFilename( getenv( "MARATHON_LOG_CONFIGDIR" ) );
	baseConfigFilename.append( "/" );
	baseConfigFilename.append( m_ModuleName );

	using namespace std;
	stringstream ss;
	ss << baseConfigFilename.c_str() << ".";
	ss << setw( 2 ) << setfill( '0' ) << branchno << ".cfg";
	basar::VarString configFile( ss.str().c_str() );

	if( fileExists( configFile ) )
	{
		return configFile;
	}

	baseConfigFilename.append( ".cfg" );
	return baseConfigFilename;
}

bool LoggerConfig::fileExists( const basar::VarString & fileName ) const
{
	struct stat buf;
	return ( stat( fileName.c_str(), &buf ) != -1 );
}

} // end namespace libcsc
