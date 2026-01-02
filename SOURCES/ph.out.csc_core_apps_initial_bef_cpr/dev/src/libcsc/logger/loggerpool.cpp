#include "loggerpool.h"
#include <libbasarcmnutil.h>
#include <pxloggerpool.h>

namespace libcsc
{
using log4cplus::Logger;
using basar::cmnutil::Logging;

const Logger LoggerPool::getLoggerDiscountBaseValue()
{
	return Logging::getInstance( "libcsc.discountBaseValue" );
}

const Logger LoggerPool::getLoggerOrderPositionDiscount()
{
	return Logging::getInstance( "libcsc.orderPositionDiscount" );
}

const Logger LoggerPool::getLoggerSession()
{
	return Logging::getInstance( "libcsc.session" );
}

const Logger LoggerPool::getLoggerOrder()
{
	return Logging::getInstance( "libcsc.order" );
}

const Logger LoggerPool::getLoggerOrderItem()
{
	return Logging::getInstance( "libcsc.orderItem" );
}

const Logger LoggerPool::getLoggerOrderItemBaseValue()
{
	return Logging::getInstance( "libcsc.orderItemBaseValue" );
}

const Logger LoggerPool::getLoggerOrderPos()
{
    return Logging::getInstance("libcsc.orderPos");
}

const Logger LoggerPool::getLoggerStockBooking()
{
	return Logging::getInstance( "libcsc.stockBooking" );
}

const Logger LoggerPool::getLoggerTourManager()
{
	return Logging::getInstance( "libcsc.TourManager" );
}

const Logger LoggerPool::getLoggerDiscountCalc()
{
	return Logging::getInstance( "libcsc.discountCalc" );
}

const Logger LoggerPool::getLoggerDiscountLog()
{
	return Logging::getInstance( "libcsc.discountLog" );
}

const Logger LoggerPool::getLoggerInfrastructure()
{
	return Logging::getInstance( "libcsc.infrastructure" );
}

const Logger LoggerPool::getLoggerTcaSession()
{
	return Logging::getInstance( "libcsc.tcaSession" );
}

const Logger LoggerPool::getLoggerArticleSubstitution()
{
	return Logging::getInstance( "libcsc.articleSubstitution" );
}

const Logger LoggerPool::getLoggerIbtRequest()
{
    return Logging::getInstance("libcsc.ibtRequest");
}

const Logger LoggerPool::getLoggerProcurementPermissionRequest()
{
    return Logging::getInstance("libcsc.procurementPermissionRequest");
}

const Logger LoggerPool::getLoggerCallback()
{
    return Logging::getInstance("libcsc.callback");
}

const Logger LoggerPool::getLoggerCrema()
{
    return Logging::getInstance("libcsc.crema");
}

const log4cplus::Logger LoggerPool::getLoggerTenderDiscount()
{
	return Logging::getInstance("libcsc.tenderDiscount");
}

const log4cplus::Logger LoggerPool::getLoggerDocuments()
{
    return Logging::getInstance("libcsc.documents");
}

const log4cplus::Logger LoggerPool::getLoggerShipmentTracking()
{
    return Logging::getInstance("libcsc.shipmenttracking");
}

const log4cplus::Logger LoggerPool::getLoggerOrderRemarks()
{
	return Logging::getInstance( "libcsc.orderRemarks" );
}

const Logger LoggerPool::getLoggerParameter()
{
	return Logging::getInstance("libcsc.parameter");
}

const Logger LoggerPool::getLoggerReturns()
{
	return Logging::getInstance("libcsc.returns");
}

const Logger LoggerPool::getLoggerWorkingdaysCalendar()
{
	return Logging::getInstance("libcsc.workingdayscalendar");
}

} // end namespace libcsc

// convenience for usage in plain C (pxDB, server code, batch programs)
// see <pxdb/include/pxloggerpool.h>
log4cplus::Logger getLogger( const Log4CplusLoggerEnum logger )
{
	switch( logger )
	{
		case LOGGER_DISCOUNT_BASE_VALUE: return libcsc::LoggerPool::getLoggerDiscountBaseValue(); break;
		case LOGGER_ORDER_POSITION_DISCOUNT: return libcsc::LoggerPool::getLoggerOrderPositionDiscount(); break;
		case LOGGER_SESSION: return libcsc::LoggerPool::getLoggerSession(); break;
		case LOGGER_ORDER: return libcsc::LoggerPool::getLoggerOrder(); break;
		case LOGGER_ORDER_ITEM: return libcsc::LoggerPool::getLoggerOrderItem(); break;
		case LOGGER_ORDER_ITEM_BASE_VALUE: return libcsc::LoggerPool::getLoggerOrderItemBaseValue(); break;
		case LOGGER_STOCK_BOOKING: return libcsc::LoggerPool::getLoggerStockBooking(); break;
		case LOGGER_DISCOUNT_CALC: return libcsc::LoggerPool::getLoggerDiscountCalc(); break;
		case LOGGER_DISCOUNT_LOG: return libcsc::LoggerPool::getLoggerDiscountLog(); break;
		case LOGGER_INFRASTRUCTURE: return libcsc::LoggerPool::getLoggerInfrastructure(); break;
		case LOGGER_ARTICLESUBSTITUTION: return libcsc::LoggerPool::getLoggerArticleSubstitution(); break;
		case LOGGER_TCASESSION: return libcsc::LoggerPool::getLoggerTcaSession(); break;
		case LOGGER_DISCOUNT_TENDER: return libcsc::LoggerPool::getLoggerTenderDiscount(); break;
		case LOGGER_PARAMETER: return libcsc::LoggerPool::getLoggerParameter(); break;
		case LOGGER_RETURNS: return libcsc::LoggerPool::getLoggerReturns(); break;
		default: break;
	}

	// root logger
	return basar::cmnutil::Logging::getInstance( "" );
}

extern "C"
{
	void log4cplus_trace( const Log4CplusLoggerEnum logger, const char * msg )
	{
		BLOG_TRACE( getLogger( logger ), msg );
	}

	void log4cplus_debug( const Log4CplusLoggerEnum logger, const char * msg )
	{
		BLOG_DEBUG( getLogger( logger ), msg );
	}

	void log4cplus_info( const Log4CplusLoggerEnum logger, const char * msg )
	{
		BLOG_INFO( getLogger( logger ), msg );
	}

	void log4cplus_error( const Log4CplusLoggerEnum logger, const char * msg )
	{
		BLOG_ERROR( getLogger( logger ), msg );
	}

	void log4cplus_fatal( const Log4CplusLoggerEnum logger, const char * msg )
	{
		BLOG_FATAL( getLogger( logger ), msg );
	}
}

