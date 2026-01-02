//----------------------------------------------------------------------------
/*! \file
 *  \brief  pool for logger objects in IMPORTPRICELIST
 *  \author
 *  \date
 */
//----------------------------------------------------------------------------

#ifndef GUARD_IMPORTPRICELIST_LOGGERPOOL_H
#define GUARD_IMPORTPRICELIST_LOGGERPOOL_H

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
namespace importpricelist
{
    class LoggerPool
    {
        public:
            static const log4cplus::Logger&    getLoggerImportpricelist();
            static const log4cplus::Logger&    getLoggerUseCases();
            static const log4cplus::Logger&    getLoggerDomModules();
			static const log4cplus::Logger&    getLoggerAccessors();
			static const log4cplus::Logger&    getLoggerDebugOutput();
    };
}

#endif
