//-------------------------------------------------------------------------------------------------//
/*! \file   cicscustomerdm.cpp
 *  \brief  implementation of cics customer module DKKUL
 *  \author	Frank Naumann
 *  \date   25.03.2010
 */
//-------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------------//
// includes
//-------------------------------------------------------------------------------------------------//

#include "commonheader.h"
#include "cicscustomerdm.h"
#include "zpldcust_definitions.h"
#include "loggerpool.h"

//-------------------------------------------------------------------------------------------------//
// namespaces
//-------------------------------------------------------------------------------------------------//

namespace domMod {

//-------------------------------------------------------------------------------------------------//

CicsCustomerDM::CicsCustomerDM() : m_Initialized(0)
{
  BLOG_TRACE_METHOD(zpldcust::LoggerPool::zpldcust, "CicsCustomerDM::CicsCustomerDM().");
}

//-------------------------------------------------------------------------------------------------//

CicsCustomerDM::~CicsCustomerDM()
{
  BLOG_TRACE_METHOD(zpldcust::LoggerPool::zpldcust, "CicsCustomerDM::~CicsCustomerDM().");
}

//-------------------------------------------------------------------------------------------------//

void CicsCustomerDM::init( const ConnectionRef activeConn, const Int16 branchNo)
{
  BLOG_TRACE_METHOD(zpldcust::LoggerPool::zpldcust, "CicsCustomerDM::init().");

  if (zpldcust::LoggerPool::zpldcust.isEnabledFor(log4cplus::DEBUG_LOG_LEVEL))
  {
    VarString msg;
    msg.format("CicsCustomerDM::init(). Branch:<%d>", branchNo);
    zpldcust::LoggerPool::zpldcust.forcedLog(log4cplus::DEBUG_LOG_LEVEL, msg.c_str(), __FILE__, __LINE__);
  }

  if( 0 == m_Initialized )
  {
    m_DKKULACC = basar::db::aspect::Manager::getInstance().createAccessorInstance( 
      "AccInstDKKUL", "AccDefinitionDKKUL", activeConn , basar::db::aspect::FULL_CACHING);
  }

  ++m_Initialized;

  VarString defParam;
  defParam.format("%s=%d;%s=%d;%s=%d;",
    lit::zpldcust::KUL_FIL1.getName().c_str(), branchNo,
    lit::zpldcust::KUL_FIL2.getName().c_str(), branchNo,
    lit::zpldcust::KUL_FIL3.getName().c_str(), branchNo);
  m_DKKULACC.setDefaultParameter(defParam);
}

//-------------------------------------------------------------------------------------------------//

void CicsCustomerDM::shutdown()
{
  BLOG_TRACE_METHOD(zpldcust::LoggerPool::zpldcust, "CicsCustomerDM::shutdown().");

  if (0 == m_Initialized)
    return;

  --m_Initialized;

  if( 0 == m_Initialized )
  {
    FREE_ACCESSOR(m_DKKULACC)
  }
}

//----------------------------------------------------------------------------

AccessorPropertyTableRef CicsCustomerDM::findDKKULByPattern(AccessorPropertyTable_YIterator yitSearch)
{
  BLOG_TRACE_METHOD(zpldcust::LoggerPool::zpldcust, "CicsCustomerDM::findDKKULByPattern().");
	
  AccessorPropertyTableRef propTab;
  ExecuteResultInfo        result;

  result = m_DKKULACC.execute("amSelectDKKULByPattern", yitSearch, true, false, basar::db::aspect::HOLD_RECORDSET);
  if (result.hasError() == false)
    propTab = m_DKKULACC.getPropertyTable();
  return propTab;
}

//----------------------------------------------------------------------------

AccessorPropertyTable_YIterator CicsCustomerDM::addEmptyDKKUL()
{
  BLOG_TRACE_METHOD(zpldcust::LoggerPool::zpldcust, "CicsCustomerDM::addEmptyDKKUL().");

  m_DKKULACC.getPropertyTable().clear();
  return m_DKKULACC.getPropertyTable().insert(basar::FOR_CLEAN);
}

//----------------------------------------------------------------------------

} // namespace domMod

//----------------------------------------------------------------------------
