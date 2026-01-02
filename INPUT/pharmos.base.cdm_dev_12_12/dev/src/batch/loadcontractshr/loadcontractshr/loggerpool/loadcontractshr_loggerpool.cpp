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
#include "loggerpool/loadcontractshr_loggerpool.h"
#include <libbasarcmnutil.h>

//--------------------------------------------------------------------------------------------------//
// using declaration section
//--------------------------------------------------------------------------------------------------//
//using log4cplus::Logger;
using basar::cmnutil::Logging;

//--------------------------------------------------------------------------------------------------//
// class definition section
//--------------------------------------------------------------------------------------------------//
namespace loadcontractshr
{
    using log4cplus::Logger;
    using basar::cmnutil::Logging;

    const log4cplus::Logger& loadcontractshr::LoggerPool::getLoggerLoadContractsHr()
    {
        static Logger log = Logging::getInstance( "loadcontractshr" );
        return log;
    }

    const log4cplus::Logger& loadcontractshr::LoggerPool::getLoggerUseCases()
    {
        static Logger log = Logging::getInstance( "loadcontractshr.useCase" );
        return log;
    }

    const log4cplus::Logger& loadcontractshr::LoggerPool::getLoggerDomModules()
    {
        static Logger log = Logging::getInstance( "loadcontractshr.domMod" );
        return log;
    }

    const log4cplus::Logger& loadcontractshr::LoggerPool::getLoggerDebugOutput()
    {
        static Logger log = Logging::getInstance( "loadcontractshr.debugOutput" );
        return log;
    }

}
