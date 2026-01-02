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
#include "loggerpool/ibtrelevantcalculator_loggerpool.h"
#include <libbasarcmnutil.h>

//--------------------------------------------------------------------------------------------------//
// using declaration section
//--------------------------------------------------------------------------------------------------//
//using log4cplus::Logger;
using basar::cmnutil::Logging;

//--------------------------------------------------------------------------------------------------//
// class definition section
//--------------------------------------------------------------------------------------------------//
namespace ibtrelevantcalculator
{
    using log4cplus::Logger;
    using basar::cmnutil::Logging;

    const log4cplus::Logger& ibtrelevantcalculator::LoggerPool::getLoggerIbtrelevantcalculator()
    {
        static Logger log = Logging::getInstance( "ibtrelevantcalculator" );
        return log;
    }

    const log4cplus::Logger& ibtrelevantcalculator::LoggerPool::getLoggerUseCases()
    {
        static Logger log = Logging::getInstance( "ibtrelevantcalculator.useCase" );
        return log;
    }

    const log4cplus::Logger& ibtrelevantcalculator::LoggerPool::getLoggerDomModules()
    {
        static Logger log = Logging::getInstance( "ibtrelevantcalculator.domMod" );
        return log;
    }

    const log4cplus::Logger& ibtrelevantcalculator::LoggerPool::getLoggerDebugOutput()
    {
        static Logger log = Logging::getInstance( "ibtrelevantcalculator.debugOutput" );
        return log;
    }

}
