#ifndef GUARD_LIBCSC_UTIL_LOGGINGUTILS_H
#define GUARD_LIBCSC_UTIL_LOGGINGUTILS_H

#include <logger/loggerpool.h>
#include <boost/shared_ptr.hpp>

namespace log4cplus {

typedef boost::shared_ptr<log4cplus::TraceLogger> TraceLoggerPtr;

} // log4cplus

namespace libcsc {
namespace util {

class LoggingUtilsHelper
{
public:
    virtual ~LoggingUtilsHelper() {}

    static log4cplus::TraceLoggerPtr makeSharedTraceLoggerPtr(
        const log4cplus::Logger& logger,
        log4cplus::tstring logEvent,
        const char* _file = NULL,
        int _line = -1
    );

private:
    LoggingUtilsHelper() {}
};


} // end namespace util
} // end namespace libcsc


//----------------------------------------------------------------------------------
// Macros:
//----------------------------------------------------------------------------------

// 'meta' class macro
#define METHODNAME_DEF( CLASS, FUNNAME )       static basar::ConstString fun = #CLASS"::"#FUNNAME"() ";


// Extended the BLOG_TRACE_METHOD == LOG4CPLUS_TRACE_METHOD to be able to use a stream string building.
// The creationf of the tracing stack object "_log4cplus_trace_logger" is also optimized only for TRACE_LOG_LEVEL cases using boost::shared_ptr
#define BLOG_TRACE_METHODEX(logger, logEvent)                               \
    log4cplus::TraceLoggerPtr _log4cplus_trace_loggerPtr;                   \
    LOG4CPLUS_SUPPRESS_DOWHILE_WARNING()                                    \
    do {                                                                    \
        log4cplus::Logger const & _l                                        \
            = log4cplus::detail::macros_get_logger (logger);                \
        if (LOG4CPLUS_MACRO_LOGLEVEL_PRED (                                 \
                _l.isEnabledFor (log4cplus::TRACE_LOG_LEVEL),               \
                TRACE_LOG_LEVEL                                             \
                )                                                           \
           )                                                                \
        {                                                                   \
            LOG4CPLUS_MACRO_INSTANTIATE_OSTRINGSTREAM (_log4cplus_buf);     \
            _log4cplus_buf << logEvent;                                     \
            _log4cplus_trace_loggerPtr =                                    \
                libcsc::util::LoggingUtilsHelper::makeSharedTraceLoggerPtr( \
                logger, _log4cplus_buf.str(), __FILE__, __LINE__            \
                );                                                          \
        }                                                                   \
    } while (0);                                                            \
    LOG4CPLUS_RESTORE_DOWHILE_WARNING()


#endif // GUARD_LIBCSC_UTIL_LOGGINGUTILS_H
