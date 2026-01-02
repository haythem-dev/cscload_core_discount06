//-------------------------------------------------------------------------------------------------//
/*! \file   customerdm.cpp
 *  \brief  implementation of domain module customer.
 *  \author Frank Naumann
 *  \date   25.03.2010
 */
//-------------------------------------------------------------------------------------------------//

#include "commonheader.h"
#include "customerdm.h"
#include "zpldcust_definitions.h"
#include "loggerpool.h"

//-------------------------------------------------------------------------------------------------//

namespace domMod {

//-------------------------------------------------------------------------------------------------//

CustomerDM::CustomerDM() : m_Initialized(0)
{
  BLOG_TRACE_METHOD(zpldcust::LoggerPool::zpldcust, "CustomerDM::CustomerDM().");
}

//-------------------------------------------------------------------------------------------------//

CustomerDM::~CustomerDM()
{
  BLOG_TRACE_METHOD(zpldcust::LoggerPool::zpldcust, "CustomerDM::~CustomerDM().");
}

//-------------------------------------------------------------------------------------------------//

void CustomerDM::init(const ConnectionRef activeConn, const Int16 branchno)
{
  BLOG_TRACE_METHOD(zpldcust::LoggerPool::zpldcust, "CustomerDM::init().");

  if (zpldcust::LoggerPool::zpldcust.isEnabledFor(log4cplus::DEBUG_LOG_LEVEL))
  {
    VarString msg;
    msg.format("CustomerDM::init(). Branch:<%d>", branchno);
    zpldcust::LoggerPool::zpldcust.forcedLog(log4cplus::DEBUG_LOG_LEVEL, msg.c_str(), __FILE__, __LINE__);
  }

  if (0 == m_Initialized)
  {
    m_CustomerACC = basar::db::aspect::Manager::getInstance().createAccessorInstance(
                    "AccInstCustomer", "AccDefinitionCustomer", activeConn);
  }
  ++m_Initialized;

  VarString defParam;
  defParam.format("%s=%d;", lit::zpldcust::BRANCHNO.getName().c_str(), branchno);
  m_CustomerACC.setDefaultParameter(defParam);
}

//-------------------------------------------------------------------------------------------------//

void CustomerDM::shutdown()
{
  BLOG_TRACE_METHOD(zpldcust::LoggerPool::zpldcust, "CustomerDM::shutdown().");
	
  if (0 == m_Initialized)
    return;
	
  --m_Initialized;
	
  if (0 == m_Initialized)
  {
    FREE_ACCESSOR(m_CustomerACC)
  }
}

//-------------------------------------------------------------------------------------------------//

AccessorPropertyTable_YIterator CustomerDM::findCustomer(const AccessorPropertyTable_YIterator yitSearch)
{
  BLOG_TRACE_METHOD(zpldcust::LoggerPool::zpldcust, "CustomerDM::findCustomer().");

  m_CustomerACC.execute("amSelectCustomer", yitSearch, true, false, basar::db::aspect::HOLD_RECORDSET);
  return m_CustomerACC.getPropertyTable().begin();
}

//-------------------------------------------------------------------------------------------------//

ExecuteResultInfo CustomerDM::saveCustomer(AccessorPropertyTable_YIterator yitCustomer)
{
  BLOG_TRACE_METHOD(zpldcust::LoggerPool::zpldcust, "CustomerDM::saveCustomer().");

  return m_CustomerACC.execute("amSaveCustomer", yitCustomer, false, false);
}

//-------------------------------------------------------------------------------------------------//

AccessorPropertyTable_YIterator CustomerDM::addEmptyCustomer()
{
  BLOG_TRACE_METHOD(zpldcust::LoggerPool::zpldcust, "CustomerDM::addEmptyCustomer().");

  m_CustomerACC.getPropertyTable().clear();
  return m_CustomerACC.getPropertyTable().insert(basar::FOR_INSERT);
}

//-------------------------------------------------------------------------------------------------//

} // namespace domMod

//-------------------------------------------------------------------------------------------------//

