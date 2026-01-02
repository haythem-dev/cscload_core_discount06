//----------------------------------------------------------------------------
/*! \file
 *  \brief  pool for logger objects in CSC_PHADEX
 *  \author
 *  \date
 */
//----------------------------------------------------------------------------

#ifndef GUARD_LIBCSC_PHADEX_LOGGERPOOL_H
#define GUARD_LIBCSC_PHADEX_LOGGERPOOL_H

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
namespace csc_phadex
{
    class LoggerPool
    {
        public:
            static const log4cplus::Logger&    getLoggerCsc_phadex();
            static const log4cplus::Logger&    getLoggerUseCases();
            static const log4cplus::Logger&    getLoggerDomModules();
    };
}

#endif
