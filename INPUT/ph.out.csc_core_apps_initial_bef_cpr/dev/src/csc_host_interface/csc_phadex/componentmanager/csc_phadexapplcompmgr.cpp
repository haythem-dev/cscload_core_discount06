#include "csc_phadexapplcompmgr.h"

#include "loggerpool/csc_phadex_loggerpool.h"
#include "usecase/mainuc/mainucptr.h"
#include "usecase/transferuc/transferuc.h"
#include "usecase/transferuc/transferucptr.h"
#include "usecase/tendercancellationuc/tendercancellationuc.h"
#include "usecase/tendercancellationuc/tendercancellationucptr.h"
#include "usecase/narcprintupdateuc/narcprintupdateuc.h"
#include "usecase/deliverynotecompleteduc/deliverynotecompleteduc.h"
#include "usecase/deliverynotecancellationuc/deliverynotecancellationuc.h"
#include "usecase/blockedarticleuc/blockedarticleuc.h"
#include "usecase/documentprintinfouc/documentprintinfouc.h"
#include "usecase/sapreferencenouc/sapreferencenouc.h"
#include "usecase/mainuc/mainuc.h"
#include <usecase/processuc/processucptr.h>
#include <usecase/processuc/processuc.h>
#include <domainmodule/taskcontrol/taskcontroldm.h>
#include <domainmodule/taskcontrol/taskcontroldmptr.h>
#include "domainmodule/narcotics/narcoticsdm.h"
#include "domainmodule/narcotics/narcoticsdmptr.h"
#include <domainmodule/cicstransaction/cicstransactioncollectiondmptr.h>
#include <domainmodule/cicstransaction/cicstransactioncollectiondm.h>
#include <domainmodule/phadextransaction/phadextransactioncollectiondmptr.h>
#include <domainmodule/phadextransaction/phadextransactioncollectiondm.h>
#include "infrastructure/accessor/narcoticsacc_definitions.h"
#include "infrastructure/accessor/narcoticsacc.h"
#include <infrastructure/accessor/cicsdataacc_definitions.h>
#include <infrastructure/accessor/cicsdataacc.h>
#include <infrastructure/accessor/phadextransactionacc_definitions.h>
#include <infrastructure/accessor/phadextransactionacc.h>
#include <usecase/processuc/transactionrecordmapper/transactionrecordmapperptr.h>
#include <usecase/processuc/transactionrecordmapper/transactionrecordmapper.h>
#include <libutil/session.h>

#include <libutil/util.h>
#include <libutil/dbconnection.h>
#include <libbasarcmnutil_logging.h>
#include <libbasardbsql_databaseinfo.h>
#include <libbasarlogin.h>
#include <libbasardbsql.h>
#include <libbasarproperty.h>

#include <pxxmit.hpp>
#include <persistence/connection.h>

#include <boost/make_shared.hpp>

namespace csc_phadex
{
namespace componentManager
{
ApplCompMgr::ApplCompMgr()
: m_Logger( csc_phadex::LoggerPool::getLoggerCsc_phadex() )
{
	METHODNAME_DEF( ApplCompMgr, ApplCompMgr )
	BLOG_TRACE_METHOD( m_Logger, fun );
}

ApplCompMgr::~ApplCompMgr()
{
	METHODNAME_DEF( ApplCompMgr, ~ApplCompMgr )
	BLOG_TRACE_METHOD( m_Logger, fun );
}

void ApplCompMgr::injectCICSConnection( basar::db::aspect::ConnectionRef connection )
{
	m_CICSConnection = connection;
}

void ApplCompMgr::setConfig( const csc_phadex::infrastructure::PhadexConfigStruct & config )
{
	m_Config = config;
}

void ApplCompMgr::doClear()
{
	METHODNAME_DEF( ApplCompMgr, doClear )
	BLOG_TRACE_METHOD( m_Logger, fun );
}

libutil::useCase::IRunnablePtr ApplCompMgr::getMainUC()
{
	METHODNAME_DEF( ApplCompMgr, getMainUC )
	BLOG_TRACE_METHOD( m_Logger, fun );

	csc_phadex::useCase::MainUCPtr mainUC = csc_phadex::useCase::MainUCPtr( new csc_phadex::useCase::MainUC );
	mainUC->injectUseCaseGetter( shared_from_this() );
	mainUC->injectTaskControl( getTaskControl() );
	mainUC->setSleepDuration( m_Config.pollInterval );
	mainUC->setNoCICS( m_Config.noCICS );
	return mainUC;
}

libutil::infrastructure::session::ISessionPtr ApplCompMgr::getSession()
{
    CHECK_INSTANCE_EXCEPTION( m_Session.get() );
    return m_Session;
}

csc_phadex::useCase::ITransferUCPtr ApplCompMgr::getTransferUC()
{
	METHODNAME_DEF( ApplCompMgr, getTransferUC )
	BLOG_TRACE_METHOD( m_Logger, fun );

	csc_phadex::useCase::TransferUCPtr uc( new csc_phadex::useCase::TransferUC() );
	uc->inject( getPhadexTransactionCollectionDM() );
	uc->inject( getCICSTransactionCollectionDM() );
	uc->setBranchno( m_Config.branchno );
	uc->setTransferLimit( m_Config.maxSelect );
	return uc;
}

csc_phadex::domMod::phadexTransaction::IPhadexTransactionCollectionPtr ApplCompMgr::getPhadexTransactionCollectionDM()
{
	csc_phadex::domMod::phadexTransaction::PhadexTransactionCollectionDMPtr dm( new csc_phadex::domMod::phadexTransaction::PhadexTransactionCollectionDM() );
	dm->injectPhadexTransactionAccessor( getPhadexTransactionAccessor() );
	return dm;
}

csc_phadex::domMod::cicsTransaction::ICICSTransactionCollectionFinderPtr ApplCompMgr::getCICSTransactionCollectionDM()
{
	csc_phadex::domMod::cicsTransaction::CICSTransactionCollectionDMPtr dm( new csc_phadex::domMod::cicsTransaction::CICSTransactionCollectionDM() );
	dm->injectCICSTransactionAccessor(getCICSDataAccessor());
	dm->injectCICSTransactionUpdateAccessor(getCICSDataAccessor());
	return dm;
}

csc_phadex::useCase::ITenderCancellationUCPtr ApplCompMgr::getTenderCancellationUC()
{
    METHODNAME_DEF( ApplCompMgr, getTenderCancellationUC )
    BLOG_TRACE_METHOD( m_Logger, fun );

    csc_phadex::useCase::TenderCancellationUCPtr tenderCancelation ( new csc_phadex::useCase::TenderCancellationUC() );
    tenderCancelation->injectPxOrderTransmit( getPxOrderTransmit() );
    return tenderCancelation;
}

libutil::infrastructure::accessor::IAccessorPtr ApplCompMgr::getNarcoticsAccessor()
{
    METHODNAME_DEF( ApplCompMgr, getNarcoticsAccessor )
    BLOG_TRACE_METHOD( m_Logger, fun );

    ::infrastructure::accessor::narcotics::UpdateNarcTransfer();
    libutil::infrastructure::accessor::IAccessorPtr accessor = libutil::infrastructure::accessor::AccessorProxyPtr(
        new libutil::infrastructure::accessor::AccessorProxy( ::infrastructure::accessor::narcotics::lit::NARCOTICS_TRANSFER_ACC, getDBConnection()->getCurrentConnection() ));
    return accessor;
}

csc_phadex::domMod::narcotics::INarcoticsPtr ApplCompMgr::getNarcoticsDM()
{
    METHODNAME_DEF( ApplCompMgr, getNarcoticsDM )
    BLOG_TRACE_METHOD( m_Logger, fun );

    csc_phadex::domMod::narcotics::NarcoticsDMPtr narcotics(new csc_phadex::domMod::narcotics::NarcoticsDM());
    narcotics->injectNarcoticsAccessor( getNarcoticsAccessor() );
    return narcotics;
}

 csc_phadex::useCase::INarcPrintUpdateUCPtr ApplCompMgr::getNarcPrintUpdateUC()
 {
    METHODNAME_DEF( ApplCompMgr, getNarcPrintUpdateUC )
    BLOG_TRACE_METHOD( m_Logger, fun );

    if( 0 == m_NarcPrintUpdateUC.get() )
    {
        m_NarcPrintUpdateUC = csc_phadex::useCase::NarcPrintUpdateUCPtr ( new csc_phadex::useCase::NarcPrintUpdateUC() );
        m_NarcPrintUpdateUC->injectNarcoticsDM( getNarcoticsDM() );
    }

    return m_NarcPrintUpdateUC;
 }

 csc_phadex::useCase::IDeliveryNoteCompletedUCPtr ApplCompMgr::getDeliveryNoteCompletedUC()
 {
    METHODNAME_DEF( ApplCompMgr, getDeliveryNoteCompletedUC )
    BLOG_TRACE_METHOD( m_Logger, fun );

    if( 0 == m_DeliveryNoteCompletedUC.get() )
    {
		m_DeliveryNoteCompletedUC = csc_phadex::useCase::DeliveryNoteCompletedUCPtr ( new csc_phadex::useCase::DeliveryNoteCompletedUC() );
		m_DeliveryNoteCompletedUC->injectPxOrderTransmit( getPxOrderTransmit() );
    }
    return m_DeliveryNoteCompletedUC;
 }

 csc_phadex::useCase::IDeliveryNoteCancellationUCPtr ApplCompMgr::getDeliveryNoteCancellationUC()
 {
     METHODNAME_DEF(ApplCompMgr, getDeliveryNoteCancellationUC )
     BLOG_TRACE_METHOD(m_Logger, fun);

     if ( 0 == m_DeliveryNoteCancellationUC.get() )
     {
         m_DeliveryNoteCancellationUC = csc_phadex::useCase::DeliveryNoteCancellationUCPtr ( new csc_phadex::useCase::DeliveryNoteCancellationUC() );
         m_DeliveryNoteCancellationUC->injectPxOrderTransmit( getPxOrderTransmit() );
     }
     return m_DeliveryNoteCancellationUC;
 }

 csc_phadex::useCase::IBlockedArticleUCPtr ApplCompMgr::getBlockedArticleUC()
 {
	 METHODNAME_DEF(ApplCompMgr, getBlockedArticleUC)
		 BLOG_TRACE_METHOD(m_Logger, fun);

	 if (0 == m_BlockedArticleUC.get())
	 {
		 m_BlockedArticleUC = csc_phadex::useCase::BlockedArticleUCPtr(new csc_phadex::useCase::BlockedArticleUC());
		 m_BlockedArticleUC->injectPxOrderTransmit(getPxOrderTransmit());
	 }
	 return m_BlockedArticleUC;
 }

 csc_phadex::useCase::IDocumentPrintInfoUCPtr ApplCompMgr::getDocumentPrintInfoUC()
 {
	 METHODNAME_DEF(ApplCompMgr, getDocumentPrintInfoUC)
		 BLOG_TRACE_METHOD(m_Logger, fun);

	 if (0 == m_DocumentPrintInfoUC.get())
	 {
		 m_DocumentPrintInfoUC = csc_phadex::useCase::DocumentPrintInfoUCPtr(new csc_phadex::useCase::DocumentPrintInfoUC());
		 m_DocumentPrintInfoUC->injectPxOrderTransmit(getPxOrderTransmit());
	 }
	 return m_DocumentPrintInfoUC;
 }

 csc_phadex::useCase::ISAPReferenceNoUCPtr ApplCompMgr::getSAPReferenceNoUC()
 {
	 METHODNAME_DEF(ApplCompMgr, getSAPReferenceNoUC)
		 BLOG_TRACE_METHOD(m_Logger, fun);

	 if (0 == m_SAPReferenceNoUC.get())
	 {
		 m_SAPReferenceNoUC = boost::make_shared<csc_phadex::useCase::SAPReferenceNoUC>();
		 m_SAPReferenceNoUC->injectPxOrderTransmit(getPxOrderTransmit());
	 }
	 return m_SAPReferenceNoUC;
 }
 
 libutil::useCase::IRunnablePtr ApplCompMgr::getProcessUC()
{
	METHODNAME_DEF( ApplCompMgr, getProcessUC )
	BLOG_TRACE_METHOD( m_Logger, fun );

	csc_phadex::useCase::ProcessUCPtr uc( new csc_phadex::useCase::ProcessUC() );
	uc->inject( getTaskControl() );
	uc->inject( getPhadexTransactionCollectionDM() );
	uc->inject( getTransactionRecordMapper() );
	uc->setBranchno( m_Config.branchno );
	if (true == m_Config.noCICS)
	{
		uc->setDatabaseName(getPxOrderTransmit()->getDatabaseNameWarehouse(m_Config.branchno));
	}
	return uc;
}

csc_phadex::useCase::ITransactionRecordMapperPtr ApplCompMgr::getTransactionRecordMapper()
{
	csc_phadex::useCase::TransactionRecordMapperPtr mapper( new csc_phadex::useCase::TransactionRecordMapper() );
	mapper->injectUseCaseGetter( shared_from_this() );
	return mapper;
}

csc_phadex::domMod::ITaskControlPtr ApplCompMgr::getTaskControl()
{
	METHODNAME_DEF( ApplCompMgr, getTaskControl )
	BLOG_TRACE_METHOD( m_Logger, fun );

	csc_phadex::domMod::TaskControlDMPtr tc( new csc_phadex::domMod::TaskControlDM() );
	tc->injectConnection( getDBConnection()->getCurrentConnection().getSqlConnection() );
	tc->setConfig( m_Config.branchno, "phadex" );
	return tc;
}

libutil::infrastructure::accessor::IAccessorPtr ApplCompMgr::getCICSDataAccessor()
{
    METHODNAME_DEF( ApplCompMgr, getCICSDataAccessor )
    BLOG_TRACE_METHOD( m_Logger, fun );

	::infrastructure::accessor::drksc::SelectDRKSCByPattern();
    libutil::infrastructure::accessor::IAccessorPtr accessor = libutil::infrastructure::accessor::AccessorProxyPtr(
        new libutil::infrastructure::accessor::AccessorProxy( ::infrastructure::accessor::drksc::lit::DRKSC_ACC, getCICSConnection() ) );
    return accessor;
}

libutil::infrastructure::accessor::IAccessorPtr ApplCompMgr::getPhadexTransactionAccessor()
{
    METHODNAME_DEF( ApplCompMgr, getPhadexTransactionAccessor )
    BLOG_TRACE_METHOD( m_Logger, fun );

	::infrastructure::accessor::phadex_transaction::SelectLastPhadexTransactionByPattern();
    libutil::infrastructure::accessor::IAccessorPtr accessor = libutil::infrastructure::accessor::AccessorProxyPtr(
        new libutil::infrastructure::accessor::AccessorProxy( ::infrastructure::accessor::phadex_transaction::lit::PHADEX_TRANSACTION_ACC, getDBConnection()->getCurrentConnection() ) );
    return accessor;
}

libutil::infrastructure::db::dbConnection::IDBConnectionDataGetterPtr ApplCompMgr::getDBConnection()
{
	METHODNAME_DEF( ApplCompMgr, getDBConnection() )
	BLOG_TRACE_METHOD( m_Logger, fun );

	return getDBConnectionData();
}

pxOrderTransmitPtr ApplCompMgr::getPxOrderTransmit()
{
	METHODNAME_DEF( ApplCompMgr, getPxOrderTransmit )
	BLOG_TRACE_METHOD(  m_Logger, fun );

	if( 0 == m_pxOrderTransmit.get() )
	{
		pxSessionInitialization pxSessInit;

		pxSessInit.setBranchInformation( m_Config.branchno,  m_Config.country );
		pxSessInit.setDBInformation(m_Config.ifxHost, m_Config.ifxDatabase);
		pxSessInit.setDevice((::pxDeviceType)m_Config.deviceType, m_Config.deviceName);
		pxSessInit.setMessageFileName(m_Config.messageFile);

		m_pxOrderTransmit = boost::make_shared< pxOrderTransmit >( pxSessInit );
		m_pxOrderTransmit->injectDBConnection( boost::make_shared< libcsc::persistence::Connection >( getDBConnection()->getCurrentConnection().getSqlConnection() ) );
		m_pxOrderTransmit->prepareSession();
	}

	if( !m_pxOrderTransmit->IsGoodState() )
	{
		BLOG_ERROR(m_Logger, m_pxOrderTransmit->ErrorMsg());
		throw basar::cmnutil::BasarException( basar::ExceptInfo(fun, "m_pxOrderTransmit is not in good state", __FILE__, __LINE__), "pxOrderTransmit" );
	}
	return m_pxOrderTransmit;
}


basar::db::aspect::ConnectionRef ApplCompMgr::getCICSConnection()
{
	METHODNAME_DEF( ApplCompMgr, getCICSConnection() )
	BLOG_TRACE_METHOD( m_Logger, fun );

	return m_CICSConnection;
}

} // end namnespace componentManager
} // end namnespace csc_phadex
