#ifndef GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_LOGGERPOOL_H
#define GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_LOGGERPOOL_H

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
namespace mainwarehousearticlesrelevantcalculator
{
    class LoggerPool
    {
        public:
            static const log4cplus::Logger&    getLoggerMainwarehouseArticlesRelevantCalculator();
            static const log4cplus::Logger&    getLoggerAccessors();
            static const log4cplus::Logger&    getLoggerViewConn();
            static const log4cplus::Logger&    getLoggerUseCases();
            static const log4cplus::Logger&    getLoggerDomModules();
            static const log4cplus::Logger&    getLoggerDebugOutput();
    };
}

#endif // GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_LOGGERPOOL_H
