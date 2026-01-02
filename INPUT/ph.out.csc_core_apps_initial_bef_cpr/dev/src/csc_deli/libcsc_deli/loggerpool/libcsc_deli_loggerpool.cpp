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
#include "loggerpool/libcsc_deli_loggerpool.h"
#include <libbasarcmnutil.h>

//--------------------------------------------------------------------------------------------------//
// using declaration section
//--------------------------------------------------------------------------------------------------//
//using log4cplus::Logger;
using basar::cmnutil::Logging;

//--------------------------------------------------------------------------------------------------//
// class definition section
//--------------------------------------------------------------------------------------------------//
namespace libcsc_deli
{
    using log4cplus::Logger;
    using basar::cmnutil::Logging;

    const log4cplus::Logger& libcsc_deli::LoggerPool::getLoggerCsc_deli()
    {
        static Logger log = Logging::getInstance( "csc_deli" );
        return log;
    }

    const log4cplus::Logger& libcsc_deli::LoggerPool::getLoggerViewConn()
    {
        static Logger log = Logging::getInstance( "csc_deli.viewConn" );
        return log;
    }

    const log4cplus::Logger& libcsc_deli::LoggerPool::getLoggerUseCases()
    {
        static Logger log = Logging::getInstance( "csc_deli.useCase" );
        return log;
    }

    const log4cplus::Logger& libcsc_deli::LoggerPool::getLoggerDomModules()
    {
        static Logger log = Logging::getInstance( "csc_deli.domMod" );
        return log;
    }

    const log4cplus::Logger& libcsc_deli::LoggerPool::getLoggerAccessors()
    {
        static Logger log = Logging::getInstance( "csc_deli.infrastructure.accessors" );
        return log;
    }

    const log4cplus::Logger& libcsc_deli::LoggerPool::getLoggerDebugOutput()
    {
        static Logger log = Logging::getInstance( "csc_deli.debugOutput" );
        return log;
    }

}
