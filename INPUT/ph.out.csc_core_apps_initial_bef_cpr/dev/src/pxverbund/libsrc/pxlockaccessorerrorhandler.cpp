#include "pxlockaccessorerrorhandler.h"

#include <pxdbxx.h>
#include <logger/loggerpool.h>

namespace lock {


PxLockAccessorErrorHandler::PxLockAccessorErrorHandler()
{
	BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerSession(), "PxLockAccessorErrorHandler::PxLockAccessorErrorHandler");
}

PxLockAccessorErrorHandler::~PxLockAccessorErrorHandler()
{
	BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerSession(), "PxLockAccessorErrorHandler::~PxLockAccessorErrorHandler");
}

void PxLockAccessorErrorHandler::handleError(const basar::VarString sql, const basar::db::sql::ExecuteReturnInfo /*info*/, const basar::VarString context)
{
	BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerSession(), "PxLockAccessorErrorHandler::handleError");
	
	std::stringstream s;
	s << "Context: " << context << std::endl;
	s << "SQL: " << sql << std::endl;
	s << "SQLCODE: <" << pxSQLCode() << ">: " << pxSQLMessage() << std::endl;
	s << "Isamcode: <" << pxISAMCode() << ">";
	BLOG_ERROR(libcsc::LoggerPool::getLoggerSession(), s.str());
}


} // end namespace lock
