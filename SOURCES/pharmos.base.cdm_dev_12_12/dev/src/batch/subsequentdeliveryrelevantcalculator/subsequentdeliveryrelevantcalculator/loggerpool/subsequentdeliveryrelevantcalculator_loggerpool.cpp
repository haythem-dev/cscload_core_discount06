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
#include "loggerpool/subsequentdeliveryrelevantcalculator_loggerpool.h"
#include <libbasarcmnutil.h>

//--------------------------------------------------------------------------------------------------//
// using declaration section
//--------------------------------------------------------------------------------------------------//
//using log4cplus::Logger;
using basar::cmnutil::Logging;

//--------------------------------------------------------------------------------------------------//
// class definition section
//--------------------------------------------------------------------------------------------------//
namespace subsequentdeliveryrelevantcalculator
{
    using log4cplus::Logger;
    using basar::cmnutil::Logging;

    const log4cplus::Logger& subsequentdeliveryrelevantcalculator::LoggerPool::getLoggerSubsequentdeliveryrelevantcalculator()
    {
        static Logger log = Logging::getInstance( "subsequentdeliveryrelevantcalculator" );
        return log;
    }

    const log4cplus::Logger& subsequentdeliveryrelevantcalculator::LoggerPool::getLoggerUseCases()
    {
        static Logger log = Logging::getInstance( "subsequentdeliveryrelevantcalculator.useCase" );
        return log;
    }

    const log4cplus::Logger& subsequentdeliveryrelevantcalculator::LoggerPool::getLoggerDomModules()
    {
        static Logger log = Logging::getInstance( "subsequentdeliveryrelevantcalculator.domMod" );
        return log;
    }

	const log4cplus::Logger& subsequentdeliveryrelevantcalculator::LoggerPool::getLoggerAccessors()
	{
		static Logger log = Logging::getInstance("subsequentdeliveryrelevantcalculator.accessors");
		return log;
	}
	
	const log4cplus::Logger& subsequentdeliveryrelevantcalculator::LoggerPool::getLoggerDebugOutput()
    {
        static Logger log = Logging::getInstance( "subsequentdeliveryrelevantcalculator.debugOutput" );
        return log;
    }
}
