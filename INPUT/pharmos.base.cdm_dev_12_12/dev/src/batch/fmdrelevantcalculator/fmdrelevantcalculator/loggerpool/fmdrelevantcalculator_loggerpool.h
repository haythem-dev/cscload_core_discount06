//----------------------------------------------------------------------------
/*! \file
 *  \brief  pool for logger objects in FMDRELEVANTCALCULATOR
 *  \author
 *  \date
 */
//----------------------------------------------------------------------------

#ifndef GUARD_FMDRELEVANTCALCULATOR_LOGGERPOOL_H
#define GUARD_FMDRELEVANTCALCULATOR_LOGGERPOOL_H

//--------------------------------------------------------------------------------------------------//
// forward declaration section
//--------------------------------------------------------------------------------------------------//
namespace log4cplus
{
    class Logger;
}

namespace basar
{
    namespace cmnutil
    {
        class Logging;
    }
}

//--------------------------------------------------------------------------------------------------//
// class declaration section
//--------------------------------------------------------------------------------------------------//
namespace fmdrelevantcalculator
{
    class LoggerPool
    {
        public:
            static const log4cplus::Logger&    getLoggerFmdRelevantcalculator();
            static const log4cplus::Logger&    getLoggerUseCases();
            static const log4cplus::Logger&    getLoggerDomModules();
            static const log4cplus::Logger&    getLoggerDebugOutput();
    };
}

#endif
