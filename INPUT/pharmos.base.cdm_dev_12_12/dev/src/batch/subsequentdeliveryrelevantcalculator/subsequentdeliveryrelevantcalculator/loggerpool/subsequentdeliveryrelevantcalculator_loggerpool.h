//----------------------------------------------------------------------------
/*! \file
 *  \brief  pool for logger objects in SUBSEQUENTDELIVERYRELEVANTCALCULATOR
 *  \author
 *  \date
 */
//----------------------------------------------------------------------------

#ifndef GUARD_SUBSEQUENTDELIVERYRELEVANTCALCULATOR_LOGGERPOOL_H
#define GUARD_SUBSEQUENTDELIVERYRELEVANTCALCULATOR_LOGGERPOOL_H

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
namespace subsequentdeliveryrelevantcalculator
{
    class LoggerPool
    {
        public:
            static const log4cplus::Logger&    getLoggerSubsequentdeliveryrelevantcalculator();
            static const log4cplus::Logger&    getLoggerUseCases();
            static const log4cplus::Logger&    getLoggerDomModules();
			static const log4cplus::Logger&    getLoggerAccessors();
			static const log4cplus::Logger&    getLoggerDebugOutput();
    };
}

#endif
