//-------------------------------------------------------------------------------------------------//
/*! \file   loadcustomerappl.cpp
 *  \brief  application (main) functions for zpldcust load customer
 *  \author	Frank Naumann
 *  \date   25.03.2010
 */
//-------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------------//
// includes
//-------------------------------------------------------------------------------------------------//
#include "commonheader.h"
#include "loadcustomerappl.h"
#include "zpldcust_definitions.h"
#include "loggerpool.h"

//-------------------------------------------------------------------------------------------------//
/*! \ingroup DIFF_WIN_UNIX */ 
#ifdef __sun	// Solaris
using basar::cmnutil::Singleton;
using zpldcust::LoadCustomerApplBase;
//! \brief explicit template instantiation for singleton 
template <> Singleton<LoadCustomerApplBase>::InstancePtr Singleton<LoadCustomerApplBase>::m_Instance = Singleton<LoadCustomerApplBase>::InstancePtr();
#endif

#ifdef _AIX
namespace basar {
	namespace cmnutil {
		using zpldcust::LoadCustomerApplBase;
		template <> typename Singleton<LoadCustomerApplBase>::InstancePtr& Singleton<LoadCustomerApplBase>::inst()
		{
			static InstancePtr s_inst; 
			return s_inst;
		}
	}
}
#endif

#ifdef WIN32
using basar::cmnutil::Singleton;
using zpldcust::LoadCustomerApplBase;
template <> typename Singleton<LoadCustomerApplBase>::InstancePtr& Singleton<LoadCustomerApplBase>::inst()
{
	static InstancePtr s_inst; 
	return s_inst;
}
#endif


//-------------------------------------------------------------------------------------------------//

namespace zpldcust {

//-------------------------------------------------------------------------------------------------//

LoadCustomerApplBase::LoadCustomerApplBase()
{
  BLOG_TRACE_METHOD(LoggerPool::zpldcust, "LoadCustomerApplBase::LoadCustomerApplBase()");
}

//-------------------------------------------------------------------------------------------------//

LoadCustomerApplBase::~LoadCustomerApplBase()
{
  BLOG_TRACE_METHOD(LoggerPool::zpldcust, "LoadCustomerApplBase::~LoadCustomerApplBase()");

  shutdown();
}

//-------------------------------------------------------------------------------------------------//

bool LoadCustomerApplBase::init(const AccessorPropertyTable_YIterator yitSearch)
{
  BLOG_TRACE_METHOD(LoggerPool::zpldcust, "LoadCustomerApplBase::init()");

  // this string identifies your application in global user administration (read parameters from Appl ZDP)
  I18nString appl = "ZDP";
  I18nString batchUser = "zdp.batch";
  I18nString batchPass = "l8dQuwr8"; // Klartext: ZdpBat10
  Int16      branchno;

  if (!yitSearch.isContainedAndSet(lit::zpldcust::BRANCHNO))
    return false;
  branchno = static_cast<Int16>(yitSearch.getString(lit::zpldcust::BRANCHNO).stoi());

  if (basar::login::Manager::getInstance().nonInteractiveLogin(appl, batchUser, batchPass, branchno) != true )
  {
    LOG4CPLUS_ERROR(LoggerPool::zpldcust, "login failed! username or password wrong!");
    return false;
  }

  m_Connection.connect();
  return true;
}

//-------------------------------------------------------------------------------------------------//

EventReturnType LoadCustomerApplBase::run(IEventSource& rSource, AccessorPropertyTable_YIterator yitSearch)
{
  BLOG_TRACE_METHOD(LoggerPool::zpldcust, "LoadCustomerApplBase::run()");

  if (!init(yitSearch))
    return EventReturnStruct(basar::appl::HANDLER_ERROR, "Error at initializing zpldcust");

  return m_LoadCustomerUC.run(rSource, yitSearch);
}

//-------------------------------------------------------------------------------------------------//

void LoadCustomerApplBase::shutdown()
{
  BLOG_TRACE_METHOD(LoggerPool::zpldcust, "LoadCustomerApplBase::shutdown()");

  m_Connection.disconnect();
}

//-------------------------------------------------------------------------------------------------//

} // namespace zpldcust

//-------------------------------------------------------------------------------------------------//
