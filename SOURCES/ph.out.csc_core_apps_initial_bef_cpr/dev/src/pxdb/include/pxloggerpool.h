#ifndef GUARD_LIBCSC_PX_LOGGER_POOL_H
#define GUARD_LIBCSC_PX_LOGGER_POOL_H

enum Log4CplusLoggerEnum
{
	LOGGER_DISCOUNT_BASE_VALUE = 1,
	LOGGER_ORDER_POSITION_DISCOUNT,
	LOGGER_SESSION,
	LOGGER_ORDER,
	LOGGER_ORDER_ITEM,
	LOGGER_ORDER_ITEM_BASE_VALUE,
	LOGGER_STOCK_BOOKING,
	LOGGER_DISCOUNT_CALC,
	LOGGER_DISCOUNT_LOG,
	LOGGER_INFRASTRUCTURE,
	LOGGER_TCASESSION,
	LOGGER_ARTICLESUBSTITUTION,
	LOGGER_DISCOUNT_TENDER,
	LOGGER_PARAMETER,
	LOGGER_RETURNS
};

#ifdef __cplusplus
extern "C" {
#endif

extern void log4cplus_trace( const enum Log4CplusLoggerEnum logger, const char * msg );
extern void log4cplus_debug( const enum Log4CplusLoggerEnum logger, const char * msg );
extern void log4cplus_info( const enum Log4CplusLoggerEnum logger, const char * msg );
extern void log4cplus_error( const enum Log4CplusLoggerEnum logger, const char * msg );
extern void log4cplus_fatal( const enum Log4CplusLoggerEnum logger, const char * msg );

#ifdef __cplusplus
}
#endif


#endif // GUARD_LIBCSC_PX_LOGGER_POOL_H

