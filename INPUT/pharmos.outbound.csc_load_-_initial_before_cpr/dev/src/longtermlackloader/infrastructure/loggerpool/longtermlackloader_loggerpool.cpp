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
#include "loggerpool/longtermlackloader_loggerpool.h"
#include <libbasarcmnutil.h>

//--------------------------------------------------------------------------------------------------//
// using declaration section
//--------------------------------------------------------------------------------------------------//
//using log4cplus::Logger;
using basar::cmnutil::Logging;

//--------------------------------------------------------------------------------------------------//
// class definition section
//--------------------------------------------------------------------------------------------------//
namespace longtermlackloader
{
    namespace infrastructure
    {
        
        using log4cplus::Logger;
        using basar::cmnutil::Logging;

        const log4cplus::Logger& /*longtermlackloader::*/LoggerPool::getLoggerLongTermLackLoader()
        {
            static Logger log = Logging::getInstance( "longtermlackloader" );
            return log;
        }

        const log4cplus::Logger& /*longtermlackloader::*/LoggerPool::getLoggerViewConn()
        {
            static Logger log = Logging::getInstance( "longtermlackloader.viewConn" );
            return log;
        }

        const log4cplus::Logger& /*longtermlackloader::*/LoggerPool::getLoggerUseCases()
        {
            static Logger log = Logging::getInstance( "longtermlackloader.useCase" );
            return log;
        }

        const log4cplus::Logger& /*longtermlackloader::*/LoggerPool::getLoggerDomModules()
        {
            static Logger log = Logging::getInstance( "longtermlackloader.domMod" );
            return log;
        }

        const log4cplus::Logger& /*longtermlackloader::*/LoggerPool::getLoggerDebugOutput()
        {
            static Logger log = Logging::getInstance( "longtermlackloader.debugOutput" );
            return log;
        }

    }
}
