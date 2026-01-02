#include "loggingutils.h"
#include <boost/make_shared.hpp>

namespace libcsc {
namespace util {

log4cplus::TraceLoggerPtr LoggingUtilsHelper::makeSharedTraceLoggerPtr(
    const log4cplus::Logger& logger,
    log4cplus::tstring logEvent,
    const char* _file,
    int _line
)
{
    log4cplus::TraceLoggerPtr retPtr = boost::make_shared<log4cplus::TraceLogger>(logger, logEvent, _file, _line);

    return retPtr;
}

} // end namespace util
} // end namespace libcsc
