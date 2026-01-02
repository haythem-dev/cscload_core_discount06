#include "pxerrorloggable.hpp"
#include <logger/loggerpool.h>
#include <libbasarcmnutil_bstring.h>

pxErrorLoggable::pxErrorLoggable() : nError()
{
}

pxErrorLoggable::~pxErrorLoggable()
{
}
	
void pxErrorLoggable::WriteLog(const nString& message, nErrorState state, int msgid)
{
	//! \note workaround for messages from message.txt: cut trailing newline from message
	basar::VarString logMessage(message());
	if( '\n' == logMessage.at(logMessage.length()-1) )
	{
		logMessage = logMessage.substr(0, logMessage.length() - 1);
	}

	std::stringstream s;
	s << "MESSAGE_ID : " << msgid << " " << logMessage;
	switch (state)
	{
		case nSTATE_GOOD :
			BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), s.str());
			break;
		case nSTATE_CONDITION :
			BLOG_WARN(libcsc::LoggerPool::getLoggerSession(), s.str());
			break;
		case nSTATE_ERROR :
		default :
			BLOG_ERROR(libcsc::LoggerPool::getLoggerSession(), s.str());
			break;
	}
}

// pxErrorLoggable& pxErrorLoggable::operator=(const pxErrorLoggable& other)
// {
// 	nError::operator = (other);
// 	return *this;
// }

// pxErrorLoggable& pxErrorLoggable::operator=(const nError& other)
// {
// 	nError::operator = (other);
// 	return *this;
// }
