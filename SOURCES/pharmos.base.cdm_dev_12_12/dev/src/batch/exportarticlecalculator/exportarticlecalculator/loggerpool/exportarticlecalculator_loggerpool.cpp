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
#include "loggerpool/exportarticlecalculator_loggerpool.h"
#include <libbasarcmnutil.h>

//--------------------------------------------------------------------------------------------------//
// using declaration section
//--------------------------------------------------------------------------------------------------//
//using log4cplus::Logger;
using basar::cmnutil::Logging;

//--------------------------------------------------------------------------------------------------//
// class definition section
//--------------------------------------------------------------------------------------------------//
namespace exportarticlecalculator
{
    using log4cplus::Logger;
    using basar::cmnutil::Logging;

    const log4cplus::Logger& exportarticlecalculator::LoggerPool::getLoggerExportarticlecalculator()
    {
        static Logger log = Logging::getInstance( "exportarticlecalculator" );
        return log;
    }

    const log4cplus::Logger& exportarticlecalculator::LoggerPool::getLoggerUseCases()
    {
        static Logger log = Logging::getInstance( "exportarticlecalculator.useCase" );
        return log;
    }

    const log4cplus::Logger& exportarticlecalculator::LoggerPool::getLoggerDomModules()
    {
        static Logger log = Logging::getInstance( "exportarticlecalculator.domMod" );
        return log;
    }

    const log4cplus::Logger& exportarticlecalculator::LoggerPool::getLoggerDebugOutput()
    {
        static Logger log = Logging::getInstance( "exportarticlecalculator.debugOutput" );
        return log;
    }

}
