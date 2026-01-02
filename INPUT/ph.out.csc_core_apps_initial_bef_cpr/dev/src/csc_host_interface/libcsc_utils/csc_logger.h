//--------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief  
 *  \author  
 *  \date    */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_LIBCSC_UTILS_CSC_LOGGER_H
#define GUARD_LIBCSC_UTILS_CSC_LOGGER_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <libbasarcmnutil.h>

#include "loggerpool.h"

#include "imailptr.h"


#include "iloggableptr.h"

#include "iapplconfigurationptr.h"
#include "icsc_logger.h"


namespace libcsc_utils
{    
	
	class CSC_Logger : public ICSC_Logger//should we implement IMail as well?
	{
		public:
			virtual ~CSC_Logger(){};

			CSC_Logger(IMailPtr mailPtr, IApplConfigurationPtr appConfig, const log4cplus::Logger& logger);

			virtual void log(log4cplus::LogLevel logLevel, const basar::VarString& logMessage, ILoggablePtr auxLogInfo);
			virtual void log(log4cplus::LogLevel logLevel, const basar::VarString& logMessage);
			virtual void log(log4cplus::LogLevel logLevel, const basar::VarString& logMessage, const basar::VarString& auxLogInfo);
			virtual const log4cplus::Logger&  getLogger() const;
			virtual void logGenericException(const basar::VarString& logMessage, ILoggablePtr auxLogInfo);
			virtual void logBasarException(const basar::VarString& logMessage, const basar::Exception& ex, ILoggablePtr auxLogInfo);
			virtual void logBasarException(const basar::VarString& logMessage, const basar::Exception& ex);
		
		private:	
			CSC_Logger(const CSC_Logger&);
			CSC_Logger& operator=(const CSC_Logger&);

			void								appendILoggableLogInfo(basar::VarString& msg, ILoggablePtr iLoggableLogInfo);

			log4cplus::LogLevel					mapToLogLevel(basar::VarString mailThreashold);

			basar::VarString					getMailSubject(log4cplus::LogLevel logLevel);

			
			log4cplus::LogLevel					m_MailThreshold;

			IMailPtr							m_MailPtr;
			IApplConfigurationPtr				m_AppConfigPtr;
			

			basar::VarString					m_InfoMailRecipients;
			basar::VarString					m_WarnMailRecipients;
			basar::VarString					m_ErrorMailRecipients;
			const log4cplus::Logger&            m_Logger;

            bool                                m_NoMail;

	};
    
}

#endif //#ifndef GUARD_LIBCSC_UTILS_CSC_LOGGER_H
