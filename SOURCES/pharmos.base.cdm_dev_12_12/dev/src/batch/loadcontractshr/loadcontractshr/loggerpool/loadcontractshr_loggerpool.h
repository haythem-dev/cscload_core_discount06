//----------------------------------------------------------------------------
/*! \file
 *  \brief  pool for logger objects in LOADCONTRACTSHR
 *  \author
 *  \date
 */
//----------------------------------------------------------------------------

#ifndef GUARD_LOADCONTRACTSHR_LOGGERPOOL_H
#define GUARD_LOADCONTRACTSHR_LOGGERPOOL_H

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
namespace loadcontractshr
{
    class LoggerPool
    {
        public:
            static const log4cplus::Logger&    getLoggerLoadContractsHr();
            static const log4cplus::Logger&    getLoggerUseCases();
            static const log4cplus::Logger&    getLoggerDomModules();
            static const log4cplus::Logger&    getLoggerDebugOutput();
    };
}

#endif
