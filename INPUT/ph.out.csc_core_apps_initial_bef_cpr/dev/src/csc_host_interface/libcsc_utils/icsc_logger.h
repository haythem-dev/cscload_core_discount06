//--------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief  
 *  \author  
 *  \date    */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_UTIL_ICSC_LOGGER_H
#define GUARD_UTIL_ICSC_LOGGER_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//

#include "iloggableptr.h"
#include <libbasarcmnutil_logging.h>
#include <libbasar_definitions.h>


//--------------------------------------------------------------------------------------------------//
// forward declaration section
//--------------------------------------------------------------------------------------------------//
//namespace basar
//{
//	class Exception;
//	class BString;
//}


namespace libcsc_utils
{    

	
	class ICSC_Logger
	{
		public: 
			virtual ~ICSC_Logger(){};

			virtual void log(log4cplus::LogLevel logLevel, const basar::VarString& logMessage, ILoggablePtr auxLogInfo) = 0;
			
			virtual void log(log4cplus::LogLevel logLevel, const basar::VarString& logMessage, const basar::VarString& auxLogInfo) = 0;
			
			virtual void log(log4cplus::LogLevel logLevel, const basar::VarString& logMessage) = 0;
			
			virtual void logGenericException(const basar::VarString& logMessage, ILoggablePtr auxLogInfo) = 0;
			

			virtual void logBasarException(const basar::VarString& logMessage, const basar::Exception& ex, ILoggablePtr auxLogInfo) = 0;
			virtual void logBasarException(const basar::VarString& logMessage, const basar::Exception& ex) = 0;
			

			virtual const log4cplus::Logger& getLogger() const = 0;
	};
    
}

#endif // GUARD_UTIL_ICSC_LOGGER_H	
