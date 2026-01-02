//----------------------------------------------------------------------------//
/*! \file
 *  \brief
 *  \author Bjoern Bischof
 *  \date   08.07.2013
 */
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
// global
#include "ibtorderimportapplcompmgr.h"
#include "loggerpool/ibtorderimport_loggerpool.h"

// uc
#include "usecase/mainucptr.h"
#include "usecase/mainuc.h"
#include "usecase/ibtordermanager.h"
#include "usecase/ibtordermanagerptr.h"

#include <ibt/componentmanager/ibtcomponentmanager.h>
#include <ibt/ibtrequest/ibtrequestrepositoryptr.h>
#include <ibt/ibtrequest/ibtrequestrepository.h>
#include <ibt/ibtresponse/ibtresponserepositoryptr.h>
#include <ibt/ibtresponse/ibtresponserepository.h>

//dommod
#include "domainmodule/pxordertransmit.h"
#include "domainmodule/pxtaskcontrolptr.h"
#include "domainmodule/pxtaskcontrol.h"
#include "domainmodule/pxvbpxtaskcontrolptr.h"

// libutil
#include <libutil/util.h>
#include <libutil/dbconnection.h>
#include <infrastructure/parameter/iparametergateway.h>

// basar
#include <libbasarcmnutil_logging.h>
#include <libbasardbsql_databaseinfo.h>
#include <libbasarlogin.h>
#include <libbasardbsql.h>
#include <libbasarproperty.h>

#include <persistence/connection.h>
#include <persistence/accessor.h>

#include "pxsessioninitialization.h"

#include "infrastructure/parameterkeys.h"

#include <parameter/branchparametergetter.h>
//#include "usecase/nachlieferposwriter.h"

#define TASKCONTROLNAME "vborderimport"

//----------------------------------------------------------------------------//
// class definition setcion
//----------------------------------------------------------------------------//
namespace ibtorderimport
{
namespace componentManager
{
ApplCompMgr::ApplCompMgr()
	: m_Logger( ibtorderimport::LoggerPool::getLoggerIbtorderimport() )
{
    METHODNAME_DEF( ApplCompMgr, ApplCompMgr )
    BLOG_TRACE_METHOD( getLogger(), fun );
}

ApplCompMgr::~ApplCompMgr()
{
    METHODNAME_DEF( ApplCompMgr, ~ApplCompMgr )
    BLOG_TRACE_METHOD( getLogger(), fun );
}

void ApplCompMgr::doClear()
{
    METHODNAME_DEF( ApplCompMgr, doClear )
    BLOG_TRACE_METHOD( getLogger(), fun );
}

void ApplCompMgr::injectMailAlert( infrastructure::mail::IMailAlertPtr mailAlert )
{
	METHODNAME_DEF( ApplCompMgr, injectMailAlert )
	BLOG_TRACE_METHOD( getLogger(), fun );

	m_MailAlert = mailAlert;
}

void ApplCompMgr::injectCscDbConnection(libcsc::persistence::ConnectionPtr cscDbConnection)
{
	METHODNAME_DEF( ApplCompMgr, injectCscDbConnection )
	BLOG_TRACE_METHOD( getLogger(), fun );

	m_CscDbConnection = cscDbConnection;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// <UC getting>
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
libutil::useCase::IRunnablePtr ApplCompMgr::getMainUC()
{
    METHODNAME_DEF( ApplCompMgr, getMainUC )
    BLOG_TRACE_METHOD( getLogger(), fun );

    ibtorderimport::useCase::MainUCPtr mainUC = ibtorderimport::useCase::MainUCPtr( new ibtorderimport::useCase::MainUC );
	mainUC->injectMailAlert( getMailAlert() );
	mainUC->injectIbtOrderGetter( getIbtOrderManager() );
	mainUC->injectIbtRequestRepository( getIbtRequestRepository() );
	mainUC->injectIbtResponseRepository( getIbtResponseRepository() );
	mainUC->injectTaskControl( getTaskControl() );
	mainUC->injectSession( getSession() );
	mainUC->injectPxOrderTransmit( getPxOrderTransmit() );
	mainUC->injectTransactionFactory( shared_from_this() );
   // mainUC->injectNachlieferPosWriter( getNachlieferPosWriter() );

	mainUC->setBranchNo( m_AppArgs.m_BranchNo );

    return mainUC;
}

libcsc::persistence::ConnectionPtr ApplCompMgr::getCscDbConnection() const
{
	CHECK_INSTANCE_EXCEPTION(m_CscDbConnection.get());

	return m_CscDbConnection;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// </UC getting>
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

libcsc::ibt::IIbtRequestRepositoryPtr ApplCompMgr::getIbtRequestRepository()
{
	return getIbtComponentManager()->createIbtRequestRepository();
}

libcsc::ibt::IIbtResponseRepositoryPtr ApplCompMgr::getIbtResponseRepository()
{
	return getIbtComponentManager()->createIbtResponseRepository();
}

libcsc::persistence::TransactionGuard ApplCompMgr::createTransaction() const
{
	return libcsc::persistence::TransactionGuard(m_PxOrderTransmit->Session());
}

useCase::IIbtOrderGetterPtr	ApplCompMgr::getIbtOrderManager()
{
	useCase::IbtOrderManagerPtr orderManager(new useCase::IbtOrderManager(LoggerPool::getLoggerUseCases()));

	orderManager->injectPxOrderTransmit(getPxOrderTransmit());
	//orderManager->injectTourByIbtRequestFinder(getTourByIbtRequestFinder());

	return orderManager;
}

domMod::IPxTaskControlPtr	ApplCompMgr::getTaskControl()
{
	METHODNAME_DEF( ApplCompMgr, getTaskControl )
	BLOG_TRACE_METHOD( m_Logger, fun );

	domMod::PxTaskControlPtr taskControl( new domMod::PxTaskControl(LoggerPool::getLoggerDomModules()) );
	taskControl->injectTransactionFactory(shared_from_this());
	taskControl->injectPxVbPxTaskControl( domMod::pxVbPxTaskControlPtr(new ::pxTaskControl(	getPxOrderTransmit()->Session(),
																							m_AppArgs.m_BranchNo,
																							TASKCONTROLNAME )));

	return taskControl;
}

domMod::IPxOrderTransmitPtr	ApplCompMgr::getPxOrderTransmit()
{
	METHODNAME_DEF( ApplCompMgr, getPxOrderTransmit )
	BLOG_TRACE_METHOD( m_Logger, fun );

	if (0 == m_PxOrderTransmit.get())
	{
		pxSessionInitialization pxSessInit;
		basar::I18nString paraVal1;
		basar::I18nString paraVal2;

		pxSessInit.setBranchInformation(m_AppArgs.m_BranchNo, pxSessionInitialization::getCountryCode(m_AppArgs.m_BranchNo) );

		getParameterGateway()->getParameterValue(m_AppArgs.m_BranchNo, constants::UADM_DBSERVER, paraVal1);
		getParameterGateway()->getParameterValue(m_AppArgs.m_BranchNo, constants::UADM_DATABASE, paraVal2);
		pxSessInit.setDBInformation(paraVal1.c_str(), paraVal2.c_str());

		getParameterGateway()->getParameterValue(constants::UADM_DEVICENAME, paraVal1);
		pxSessInit.setDevice(pxDVC_DCT_SERIAL, paraVal1.c_str());

		getParameterGateway()->getParameterValue(m_AppArgs.m_BranchNo, constants::UADM_MSG_FILE, paraVal1);
		pxSessInit.setMessageFileName( paraVal1.c_str() );

		std::stringstream s;
		s	<< "creating pxOrderTransmit with branch= " << pxSessInit.getBranchNo() << ", countrycode= " << pxSessInit.getCountryCode()
			<< ", dbserver= " << pxSessInit.getDBServerName()
			<< ", db= " << pxSessInit.getDBName() << ", device= " << pxSessInit.getDeviceName()
			<< " (serial), msgfile= " << pxSessInit.getMessageFileName() << " ...";
		BLOG_INFO( m_Logger, s.str() );

		m_PxOrderTransmit = domMod::PxOrderTransmitPtr (new domMod::PxOrderTransmit(pxSessInit, LoggerPool::getLoggerDomModules()));
		m_PxOrderTransmit->injectCscDbConnection(getCscDbConnection());
		m_PxOrderTransmit->prepareSession();
	}

	return m_PxOrderTransmit;
}

void ApplCompMgr::setCmdLineArguments( const infrastructure::cmdLine::AppArgs& appArgs )
{
	METHODNAME_DEF( ApplCompMgr, setCmdLineArgurments )
	BLOG_TRACE_METHOD( getLogger(), fun );

	m_AppArgs = appArgs;
}

infrastructure::mail::IMailAlertPtr	ApplCompMgr::getMailAlert()
{
	return m_MailAlert;
}

const log4cplus::Logger&	ApplCompMgr::getLogger()
{
	return m_Logger;
}

libcsc::ibt::IbtComponentManagerPtr ApplCompMgr::getIbtComponentManager()
{
	METHODNAME_DEF( ApplCompMgr, getIbtComponentManager )
	BLOG_TRACE_METHOD( m_Logger, fun );

	if( NULL == m_IbtComponentManagerPtr.get() )
	{
		m_IbtComponentManagerPtr = libcsc::ibt::IbtComponentManagerPtr( new libcsc::ibt::IbtComponentManager() );
		m_IbtComponentManagerPtr->injectConnection( getCscDbConnection() );
		m_IbtComponentManagerPtr->injectTransactionHandler( m_PxOrderTransmit->Session() );
	}

	return m_IbtComponentManagerPtr;
}

//useCase::INachlieferPosWriterPtr ApplCompMgr::getNachlieferPosWriter()
//{
	//return useCase::INachlieferPosWriterPtr( new useCase::NachlieferPosWriter() );
//}

libcsc::parameter::IBranchParameterGetterPtr ApplCompMgr::getBranchParamGetter()
{
	return libcsc::parameter::IBranchParameterGetterPtr( new libcsc::parameter::BranchParameterGetter( m_PxOrderTransmit->Session() ) );
}

} // end namnespace componentManager
} // end namnespace ibtorderimport
