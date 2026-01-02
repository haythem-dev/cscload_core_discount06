//----------------------------------------------------------------------------
//! \file  importmedreg_loggerpool.h
// \brief  pool for logger objects in importmedreg
// \author Thomas Arnold
// \date   09.05.2022
//----------------------------------------------------------------------------

#ifndef GUARD_IMPORTMEDREG_LOGGERPOOL_H
#define GUARD_IMPORTMEDREG_LOGGERPOOL_H

#include <string>
#include <log4cplus/logger.h>
#include <log4cplus/tracelogger.h>
#include <log4cplus/configurator.h>
#include <log4cplus/loggingmacros.h>
//--------------------------------------------------------------------------------------------------//
// forward declaration section
//--------------------------------------------------------------------------------------------------//
namespace log4cplus
{
	class Logger;
}

#define METHODNAME_DEF( CLASS, FUNNAME )		static std::string fun = #CLASS"::"#FUNNAME"()";
#define BLOG_TRACE_METHOD(logger, logEvent)		importmedreg::LoggerPool::trace_log(logger, logEvent);
//--------------------------------------------------------------------------------------------------//
// class declaration section
//--------------------------------------------------------------------------------------------------//
namespace importmedreg
{
	class LoggerPool
	{
	public:

		static void trace_log(const log4cplus::Logger& logger, std::string logEvent);

		static const log4cplus::Logger& getLoggerImportMedReg();
		static const log4cplus::Logger& getLoggerKeymanager();
		static const log4cplus::Logger& getLoggerWebService();
		static const log4cplus::Logger& getLoggerExportJsonToCSV();
	};
}

#endif // GUARD_IMPORTMEDREG_LOGGERPOOL_H
