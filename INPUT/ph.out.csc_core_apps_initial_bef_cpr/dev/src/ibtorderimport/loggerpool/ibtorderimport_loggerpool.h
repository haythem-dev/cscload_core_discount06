//----------------------------------------------------------------------------
/*! \file
 *  \brief  pool for logger objects in IBTORDERIMPORT
 *  \author
 *  \date
 */
//----------------------------------------------------------------------------

#ifndef GUARD_IBTORDERIMPORT_LOGGERPOOL_H
#define GUARD_IBTORDERIMPORT_LOGGERPOOL_H

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
namespace ibtorderimport
{
    class LoggerPool
    {
        public:
            static const log4cplus::Logger&    getLoggerIbtorderimport();
            static const log4cplus::Logger&    getLoggerUseCases();
            static const log4cplus::Logger&    getLoggerDomModules();
            static const log4cplus::Logger&    getLoggerDebugOutput();
    };
}

#endif
