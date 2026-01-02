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
#include "loggerpool/ibtorderimport_loggerpool.h"
#include <libbasarcmnutil.h>

//--------------------------------------------------------------------------------------------------//
// using declaration section
//--------------------------------------------------------------------------------------------------//
//using log4cplus::Logger;
using basar::cmnutil::Logging;

//--------------------------------------------------------------------------------------------------//
// class definition section
//--------------------------------------------------------------------------------------------------//
namespace ibtorderimport
{
    using log4cplus::Logger;
    using basar::cmnutil::Logging;

    const log4cplus::Logger& ibtorderimport::LoggerPool::getLoggerIbtorderimport()
    {
        static Logger log = Logging::getInstance( "ibtorderimport" );
        return log;
    }

    const log4cplus::Logger& ibtorderimport::LoggerPool::getLoggerUseCases()
    {
        static Logger log = Logging::getInstance( "ibtorderimport.useCase" );
        return log;
    }

    const log4cplus::Logger& ibtorderimport::LoggerPool::getLoggerDomModules()
    {
        static Logger log = Logging::getInstance( "ibtorderimport.domMod" );
        return log;
    }

    const log4cplus::Logger& ibtorderimport::LoggerPool::getLoggerDebugOutput()
    {
        static Logger log = Logging::getInstance( "ibtorderimport.debugOutput" );
        return log;
    }

}
