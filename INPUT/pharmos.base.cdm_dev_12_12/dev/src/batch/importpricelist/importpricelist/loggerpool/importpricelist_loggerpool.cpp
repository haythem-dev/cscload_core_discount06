//--------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief  pool for logger objects
 *  \author
 *  \date
 */
//--------------------------------------------------------------------------------------------------//

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include "loggerpool/importpricelist_loggerpool.h"
#include <libbasarcmnutil.h>

//--------------------------------------------------------------------------------------------------//
// using declaration section
//--------------------------------------------------------------------------------------------------//
//using log4cplus::Logger;
using basar::cmnutil::Logging;

//--------------------------------------------------------------------------------------------------//
// class definition section
//--------------------------------------------------------------------------------------------------//
namespace importpricelist
{
    using log4cplus::Logger;
    using basar::cmnutil::Logging;

    const log4cplus::Logger& importpricelist::LoggerPool::getLoggerImportpricelist()
    {
        static Logger log = Logging::getInstance( "importpricelist" );
        return log;
    }

    const log4cplus::Logger& importpricelist::LoggerPool::getLoggerUseCases()
    {
        static Logger log = Logging::getInstance( "importpricelist.useCase" );
        return log;
    }

    const log4cplus::Logger& importpricelist::LoggerPool::getLoggerDomModules()
    {
        static Logger log = Logging::getInstance( "importpricelist.domMod" );
        return log;
    }

	const log4cplus::Logger& importpricelist::LoggerPool::getLoggerAccessors()
	{
		static Logger log = Logging::getInstance("importpricelist.accessors");
		return log;
	}
	
	const log4cplus::Logger& importpricelist::LoggerPool::getLoggerDebugOutput()
    {
        static Logger log = Logging::getInstance( "importpricelist.debugOutput" );
        return log;
    }
}
