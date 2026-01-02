//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include "loggerpool/mainwarehousearticlesrelevantcalculator_loggerpool.h"
#include <libbasarcmnutil.h>

//--------------------------------------------------------------------------------------------------//
// using declaration section
//--------------------------------------------------------------------------------------------------//
using basar::cmnutil::Logging;

//--------------------------------------------------------------------------------------------------//
// class definition section
//--------------------------------------------------------------------------------------------------//
namespace mainwarehousearticlesrelevantcalculator
{
    using log4cplus::Logger;
    using basar::cmnutil::Logging;

    const log4cplus::Logger& mainwarehousearticlesrelevantcalculator::LoggerPool::getLoggerMainwarehouseArticlesRelevantCalculator()
    {
        static Logger log = Logging::getInstance( "mwhousearticlesrelcalc" );
        return log;
    }

    const log4cplus::Logger& mainwarehousearticlesrelevantcalculator::LoggerPool::getLoggerAccessors()
    {
        static Logger log = Logging::getInstance( "mwhousearticlesrelcalc.accessors" );
        return log;
    }

    const log4cplus::Logger& mainwarehousearticlesrelevantcalculator::LoggerPool::getLoggerViewConn()
    {
        static Logger log = Logging::getInstance( "mwhousearticlesrelcalc.viewConn" );
        return log;
    }

    const log4cplus::Logger& mainwarehousearticlesrelevantcalculator::LoggerPool::getLoggerUseCases()
    {
        static Logger log = Logging::getInstance( "mwhousearticlesrelcalc.useCase" );
        return log;
    }

    const log4cplus::Logger& mainwarehousearticlesrelevantcalculator::LoggerPool::getLoggerDomModules()
    {
        static Logger log = Logging::getInstance( "mwhousearticlesrelcalc.domMod" );
        return log;
    }

    const log4cplus::Logger& mainwarehousearticlesrelevantcalculator::LoggerPool::getLoggerDebugOutput()
    {
        static Logger log = Logging::getInstance( "mwhousearticlesrelcalc.debugOutput" );
        return log;
    }
}
