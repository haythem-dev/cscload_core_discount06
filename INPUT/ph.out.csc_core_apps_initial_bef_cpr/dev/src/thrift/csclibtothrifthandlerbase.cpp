#include "csclibtothrifthandlerbase.h"

#include <logger/loggerpool.h>

namespace csc {
namespace service {

CscLibToThriftHandlerBase::CscLibToThriftHandlerBase()
{
    //LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "CscLibToThriftHandlerBase::CscLibToThriftHandlerBase()");
}


CscLibToThriftHandlerBase::~CscLibToThriftHandlerBase()
{
    //LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "CscLibToThriftHandlerBase::~CscLibToThriftHandlerBase()");
}

void CscLibToThriftHandlerBase::injectSession(pxOrderTransmitPtr session)
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "CscLibToThriftHandlerBase::injectSession()");

    m_Session = session;
}

} // namespace service
} // namespace csc
