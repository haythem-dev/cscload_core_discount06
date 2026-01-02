#ifndef GUARD_LIBCSC_LOGGER_POOL_H
#define GUARD_LIBCSC_LOGGER_POOL_H

#include <libbasarcmnutil_logging.h>

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

namespace libcsc
{
class LoggerPool
{
public:
	static const log4cplus::Logger getLoggerDiscountBaseValue();
	static const log4cplus::Logger getLoggerOrderPositionDiscount();
	static const log4cplus::Logger getLoggerSession();
	static const log4cplus::Logger getLoggerOrder();
	static const log4cplus::Logger getLoggerOrderItem();
	static const log4cplus::Logger getLoggerOrderItemBaseValue();
    static const log4cplus::Logger getLoggerOrderPos();
    static const log4cplus::Logger getLoggerStockBooking();
	static const log4cplus::Logger getLoggerDiscountCalc();
	static const log4cplus::Logger getLoggerDiscountLog();
	static const log4cplus::Logger getLoggerInfrastructure();
	static const log4cplus::Logger getLoggerTcaSession();
	static const log4cplus::Logger getLoggerArticleSubstitution();
	static const log4cplus::Logger getLoggerTourManager();
    static const log4cplus::Logger getLoggerIbtRequest();
    static const log4cplus::Logger getLoggerProcurementPermissionRequest();
    static const log4cplus::Logger getLoggerCallback();
    static const log4cplus::Logger getLoggerCrema();
    static const log4cplus::Logger getLoggerTenderDiscount();
	static const log4cplus::Logger getLoggerDocuments();
	static const log4cplus::Logger getLoggerShipmentTracking();
	static const log4cplus::Logger getLoggerOrderRemarks();
	static const log4cplus::Logger getLoggerParameter();
	static const log4cplus::Logger getLoggerReturns();
	static const log4cplus::Logger getLoggerWorkingdaysCalendar();
};

} // end namespace libcsc

#endif // GUARD_LIBCSC_LOGGER_POOL_H
