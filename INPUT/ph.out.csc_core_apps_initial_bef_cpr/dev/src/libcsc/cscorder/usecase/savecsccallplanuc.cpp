/*
 * savecsccallplanuc.cpp
 *
 *  Created on: 25.09.2021
 *  Author: sebastian.barth
 */

#include "savecsccallplanuc.h"
#include "cscorder/csccallplan/icsccallplanrepository.h"
#include "cscorder/csccallplan/csccallplanptr.h"
#include "cscorder/csccallplan/csccallplan.h"
#include "logger/loggerpool.h"
#include <libbasarcmnutil_datetime.h>

namespace libcsc {
namespace cscorder {
namespace uc {

SaveCSCCallplanUC::SaveCSCCallplanUC()
    : m_Callplan(domMod::CSCCallplan::create())
{
}

SaveCSCCallplanUC::~SaveCSCCallplanUC()
{
}

void SaveCSCCallplanUC::injectRepository(repo::ICSCCallplanRepositoryPtr repository)
{
    m_Repository = repository;
}

void SaveCSCCallplanUC::setCallplan(short branchno, int customerno, int timeto)
{
    m_Callplan->setBranchNo(branchno);
    m_Callplan->setCustomerNo(customerno);
    m_Callplan->setTimeTo(timeto);
}

void SaveCSCCallplanUC::run()
{
    BLOG_TRACE_METHOD(LoggerPool::getLoggerCallback(), "SaveCSCCallplanUC::run()");

    if (!saveCallplan())
    {
        BLOG_WARN(LoggerPool::getLoggerCallback(), "SaveCSCCallplanUC::run() failed!");
    }
}

bool SaveCSCCallplanUC::saveCallplan()
{
    BLOG_TRACE_METHOD(LoggerPool::getLoggerCallback(), "SaveCSCCallplanUC::saveCallplan()");

    basar::DateTime now = basar::DateTime::getCurrent();

    m_Callplan->setDate(now.getDate());
    m_Callplan->setTimeNow(now.getTime() / 1000);
    m_Callplan->setTimeFrom(m_Callplan->getTimeNow() / 100);

    return m_Repository->saveCSCCallplan(m_Callplan);
}

} // end namespace uc
} // end namespace cscorder
} // end namespace libcsc
