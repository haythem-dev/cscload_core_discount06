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
#include "loggerpool/csc_phadex_loggerpool.h"
#include <libbasarcmnutil.h>

//--------------------------------------------------------------------------------------------------//
// using declaration section
//--------------------------------------------------------------------------------------------------//
//using log4cplus::Logger;
using basar::cmnutil::Logging;

//--------------------------------------------------------------------------------------------------//
// class definition section
//--------------------------------------------------------------------------------------------------//
namespace csc_phadex
{
    using log4cplus::Logger;
    using basar::cmnutil::Logging;

    const log4cplus::Logger& LoggerPool::getLoggerCsc_phadex()
    {
        static Logger log = Logging::getInstance( "csc_phadex" );
        return log;
    }

    const log4cplus::Logger& LoggerPool::getLoggerUseCases()
    {
        static Logger log = Logging::getInstance( "csc_phadex.useCase" );
        return log;
    }

    const log4cplus::Logger& LoggerPool::getLoggerDomModules()
    {
        static Logger log = Logging::getInstance( "csc_phadex.domMod" );
        return log;
    }

}
