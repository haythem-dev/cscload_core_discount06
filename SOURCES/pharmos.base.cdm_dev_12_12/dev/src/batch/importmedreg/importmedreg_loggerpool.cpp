//----------------------------------------------------------------------------
//! \file  importmedreg_loggerpool.cpp
// \brief  pool for logger objects in importmedreg
// \author Thomas Arnold
// \date   09.05.2022
//----------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include "importmedreg_loggerpool.h"

//--------------------------------------------------------------------------------------------------//
// class definition section
//--------------------------------------------------------------------------------------------------//
namespace importmedreg
{
	using log4cplus::Logger;

	void importmedreg::LoggerPool::trace_log(const log4cplus::Logger& logger, std::string logEvent)
	{
		log4cplus::TraceLogger _log4cplus_trace_logger(logger, logEvent, __FILE__, __LINE__);
		//printf("%s\n", logEvent.c_str());
	}

	const log4cplus::Logger& importmedreg::LoggerPool::getLoggerImportMedReg()
	{
		static Logger log = log4cplus::Logger::getInstance("importmedreg");
		return log;
	}

	const log4cplus::Logger& importmedreg::LoggerPool::getLoggerKeymanager()
	{
		static Logger log = log4cplus::Logger::getInstance("importmedreg.keymanager");
		return log;
	}

	const log4cplus::Logger& importmedreg::LoggerPool::getLoggerWebService()
	{
		static Logger log = log4cplus::Logger::getInstance("importmedreg.webservice");
		return log;
	}

	const log4cplus::Logger & LoggerPool::getLoggerExportJsonToCSV()
	{
		static Logger log = log4cplus::Logger::getInstance("importmedreg.exportjsontocsv");
		return log;
	}
}
