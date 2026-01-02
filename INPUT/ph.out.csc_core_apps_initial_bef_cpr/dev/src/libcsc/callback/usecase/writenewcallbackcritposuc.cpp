/*
 * writenewcallbackcritposuc.cpp
 *
 *  Created on: 26.04.2016
 *  Author: sebastian.barth
 */

#include "writenewcallbackcritposuc.h"
#include "callback/domainmodule/critposdmptr.h"
#include "callback/domainmodule/critposdm.h"
#include "callback/domainmodule/newcallbackcritposdm.h"
#include "callback/repository/irepository.h"
#include "logger/loggerpool.h"
#include <libbasarcmnutil_datetime.h>

namespace libcsc {
namespace callback {
namespace uc {

WriteNewCallbackCritPosUC::WriteNewCallbackCritPosUC()
    : m_CritPos(domMod::CritPosDM::create())
{
}

WriteNewCallbackCritPosUC::~WriteNewCallbackCritPosUC()
{
}

void WriteNewCallbackCritPosUC::injectRepository(repo::IRepositoryPtr repository)
{
    m_Repository = repository;
}

void WriteNewCallbackCritPosUC::setNewCritPos(domMod::INewCallbackCritPosPtr newCallbackCritPos)
{
    m_CallbackNo = newCallbackCritPos->getCallbackNo();
    m_StatusNo = newCallbackCritPos->getCallbackStatus();
    m_CritPos->setBranchNo(newCallbackCritPos->getBranchNo());
    m_CritPos->setUId(newCallbackCritPos->getUId());
    m_CritPos->setText(newCallbackCritPos->getText());
    m_CritPos->setWindowsUserId(newCallbackCritPos->getWindowsUser());
    m_CritPos->setSourceApplication(newCallbackCritPos->getSourceApplication());
}

void WriteNewCallbackCritPosUC::run()
{
    BLOG_TRACE_METHOD(LoggerPool::getLoggerCallback(), "WriteNewCallbackCritPosUC::run()");

    basar::DateTime now = basar::DateTime::getCurrent();
    m_CritPos->setDate(now.getDate());
    m_CritPos->setTime(now.getTime() / 1000);

    m_Repository->writeNewCritPos(m_CallbackNo, m_StatusNo, m_CritPos);
}

} // end namespace uc
} // end namespace callback
} // end namespace libcsc
