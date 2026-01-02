//----------------------------------------------------------------------------
/*! \file
 *  \brief  pool for logger objects in IBTRELEVANTCALCULATOR
 *  \author
 *  \date
 */
//----------------------------------------------------------------------------

#ifndef GUARD_IBTRELEVANTCALCULATOR_LOGGERPOOL_H
#define GUARD_IBTRELEVANTCALCULATOR_LOGGERPOOL_H

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
namespace ibtrelevantcalculator
{
    class LoggerPool
    {
        public:
            static const log4cplus::Logger&    getLoggerIbtrelevantcalculator();
            static const log4cplus::Logger&    getLoggerUseCases();
            static const log4cplus::Logger&    getLoggerDomModules();
            static const log4cplus::Logger&    getLoggerDebugOutput();
    };
}

#endif
