

#include <libbasarcmnutil.h>
#include <libbasarcmnutil_logging.h>

#include "csc_logger.h"


#include "imail.h"
#include "mailexception.h"
#include "iapplconfiguration.h"
#include "iloggable.h"

namespace libcsc_utils
{
//! \todo subjects
	CSC_Logger::CSC_Logger(IMailPtr mailPtr, IApplConfigurationPtr appConfig, const log4cplus::Logger& logger) : m_MailPtr(mailPtr), m_AppConfigPtr(appConfig), m_Logger(logger)
	{
		m_NoMail = appConfig->isNoMailSet();

        m_InfoMailRecipients = appConfig->getInformationSmtpRecipients();
		m_WarnMailRecipients = appConfig->getWarningSmtpRecipients();
		m_ErrorMailRecipients = appConfig->getErrorSmtpRecipients();

		m_MailThreshold = mapToLogLevel(appConfig->getMailThreshold());

       
	}

	const log4cplus::Logger& CSC_Logger::getLogger() const
	{
		return m_Logger;
	}

	log4cplus::LogLevel CSC_Logger::mapToLogLevel(basar::VarString mailThreshold)
	{
		mailThreshold.lower();

		if (mailThreshold == "information")
		{
			//generate a warning - info level mailing is not a great idea
			BLOG_WARN(m_Logger, "Mailing threshold has been set to Warning - info would just spam everyone");
			return log4cplus::WARN_LOG_LEVEL;
		}
		else if (mailThreshold == "warnings")
		{
			return log4cplus::WARN_LOG_LEVEL;
		}
		else if (mailThreshold == "errors")
		{
			return log4cplus::ERROR_LOG_LEVEL;
		}
		else
		{
			//default:
			return log4cplus::ERROR_LOG_LEVEL;
		}
	}

	void CSC_Logger::logGenericException(const basar::VarString& logMessage, ILoggablePtr auxLogInfo)
	{
		this->log(log4cplus::ERROR_LOG_LEVEL, logMessage, auxLogInfo);
	}

	void CSC_Logger::logBasarException(const basar::VarString& logMessage, const basar::Exception& ex)
	{
		basar::VarString msg = logMessage;
		
		msg.append("; basar::Exception was: ");

        msg.append(ex.what().c_str());

		this->log(log4cplus::ERROR_LOG_LEVEL, msg, ILoggablePtr());

	}

	void CSC_Logger::logBasarException(const basar::VarString& logMessage, const basar::Exception& ex, ILoggablePtr auxLogInfo)
	{
		basar::VarString msg = logMessage;
		
		msg.append("; basar::Exception was: ");

		msg.append(ex.what());
		msg.append("\n");

		this->log(log4cplus::ERROR_LOG_LEVEL, msg, auxLogInfo);

	}

	void CSC_Logger::log(log4cplus::LogLevel logLevel, const basar::VarString& logMessage)
	{
		this->log(logLevel, logMessage, ILoggablePtr());
	}

	void CSC_Logger::log(log4cplus::LogLevel logLevel, const basar::VarString& logMessage, const basar::VarString& auxLogInfo)
	{
		basar::VarString msg = logMessage;
		msg.append(" ");
		msg.append(auxLogInfo);

		this->log(logLevel, msg, ILoggablePtr());
	}

	void CSC_Logger::appendILoggableLogInfo(basar::VarString& msg, ILoggablePtr iLoggableLogInfo)
	{
			basar::VarString message("");
			try
			{
				msg.append(" ");
				msg.append(iLoggableLogInfo->getLogMessage());
			}
			catch(basar::Exception& ex)
			{				
				message.format("tried getLogMessage, got basar::Exception: %s", ex.what().c_str());
				BLOG_ERROR(m_Logger, message);
			}
			catch(...)
			{
				message = "tried getLogMessage, got generic exception";
				BLOG_ERROR(m_Logger, message);
			}
	}

	void CSC_Logger::log(log4cplus::LogLevel logLevel, const basar::VarString& logMessage, ILoggablePtr auxLogInfo)
	{
		//swtich severity
		basar::VarString msg = logMessage;
		if (auxLogInfo.get() != 0)
		{
			appendILoggableLogInfo(msg, auxLogInfo);
		}

		basar::VarString mailRecipients = "";

		switch(logLevel) //maybe we should emulate the log4cplus behaviour?
		{
			case log4cplus::TRACE_LOG_LEVEL:
				BLOG_TRACE(m_Logger, msg);
			break;
			case log4cplus::DEBUG_LOG_LEVEL:
				BLOG_DEBUG(m_Logger, msg);
			break;
			case log4cplus::INFO_LOG_LEVEL:
				BLOG_INFO(m_Logger, msg);
				mailRecipients = m_InfoMailRecipients;
			break;
			case log4cplus::WARN_LOG_LEVEL:
				BLOG_WARN(m_Logger, msg);
				mailRecipients = m_WarnMailRecipients;
			break;
			case log4cplus::ERROR_LOG_LEVEL:
				BLOG_ERROR(m_Logger, msg);
				mailRecipients = m_ErrorMailRecipients;
			break;
			case log4cplus::FATAL_LOG_LEVEL:
				BLOG_FATAL(m_Logger, msg);
				mailRecipients = m_ErrorMailRecipients;
			break;
			default:
				BLOG_TRACE(m_Logger, msg);
				//no mailing in default case
			break;
		}	
		
		//we mapped, so this should work
        //! \todo remove false and logmessage before live        
        if(m_NoMail)
        {
            BLOG_INFO(m_Logger, "sending of mails suppressed with '-nomail' option");
        }

		if (!m_NoMail && logLevel >= m_MailThreshold && m_MailThreshold < log4cplus::OFF_LOG_LEVEL)
		{
			try
			{
				m_MailPtr->setRecipientSendTo(mailRecipients);
				m_MailPtr->sendMail(getMailSubject(logLevel), msg);
			}
			catch(MailException& ex)
			{
				//only exception after startup that will just be logged
				BLOG_ERROR(m_Logger, ex.what());
			}
		}
		
	}

	basar::VarString CSC_Logger::getMailSubject(log4cplus::LogLevel logLevel)
	{
		basar::VarString subject = "";
		//subject.append(" in ");
		switch(logLevel)
		{
			case log4cplus::INFO_LOG_LEVEL:
				subject = "[Info] ";
			break;
			case log4cplus::WARN_LOG_LEVEL:
				subject = "[Warning] ";
			break;
			case log4cplus::ERROR_LOG_LEVEL:
				subject = "[Error] ";
			break;
			case log4cplus::FATAL_LOG_LEVEL:
				subject = "[Fatal] ";
			break;
		}

		subject.append(m_AppConfigPtr->getApplicationName());

		// append branchno
        subject.append(" Branch ");        
        basar::VarString branchNoStr;
        branchNoStr.format("%d", m_AppConfigPtr->getBranchNo());		
        subject.append(branchNoStr);

		// append datasource
		basar::VarString dataSourceStr;
		dataSourceStr.format("DataSource %s", m_AppConfigPtr->getDataSource().c_str());
		subject.append(dataSourceStr);

		return subject;
	}
}