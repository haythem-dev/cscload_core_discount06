//----------------------------------------------------------------------------
/*! \file
 *  \brief  pool for logger objects in EXPORTARTICLECALCULATOR
 *  \author
 *  \date
 */
//----------------------------------------------------------------------------

#ifndef GUARD_EXPORTARTICLECALCULATOR_LOGGERPOOL_H
#define GUARD_EXPORTARTICLECALCULATOR_LOGGERPOOL_H

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
namespace exportarticlecalculator
{
    class LoggerPool
    {
        public:
            static const log4cplus::Logger&    getLoggerExportarticlecalculator();
            static const log4cplus::Logger&    getLoggerUseCases();
            static const log4cplus::Logger&    getLoggerDomModules();
            static const log4cplus::Logger&    getLoggerDebugOutput();
    };
}

#endif
