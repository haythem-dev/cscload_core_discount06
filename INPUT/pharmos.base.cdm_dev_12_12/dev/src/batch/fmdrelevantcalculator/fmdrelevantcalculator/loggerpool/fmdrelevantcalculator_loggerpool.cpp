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
#include "loggerpool/fmdrelevantcalculator_loggerpool.h"
#include <libbasarcmnutil.h>

//--------------------------------------------------------------------------------------------------//
// using declaration section
//--------------------------------------------------------------------------------------------------//
//using log4cplus::Logger;
using basar::cmnutil::Logging;

//--------------------------------------------------------------------------------------------------//
// class definition section
//--------------------------------------------------------------------------------------------------//
namespace fmdrelevantcalculator
{
    using log4cplus::Logger;
    using basar::cmnutil::Logging;

    const log4cplus::Logger& fmdrelevantcalculator::LoggerPool::getLoggerFmdRelevantcalculator()
    {
        static Logger log = Logging::getInstance( "fmdrelevantcalculator" );
        return log;
    }

    const log4cplus::Logger& fmdrelevantcalculator::LoggerPool::getLoggerUseCases()
    {
        static Logger log = Logging::getInstance( "fmdrelevantcalculator.useCase" );
        return log;
    }

    const log4cplus::Logger& fmdrelevantcalculator::LoggerPool::getLoggerDomModules()
    {
        static Logger log = Logging::getInstance( "fmdrelevantcalculator.domMod" );
        return log;
    }

    const log4cplus::Logger& fmdrelevantcalculator::LoggerPool::getLoggerDebugOutput()
    {
        static Logger log = Logging::getInstance( "fmdrelevantcalculator.debugOutput" );
        return log;
    }

}
