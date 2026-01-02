//--------------------------------------------------------------------------------------------------//
/*! \brief 
 *  \author     Steffen Heinlein
 *  \date       10.07.2012
 *  \version    00.00.00.01
 */ //--------------------------------------------------------------------------------------------------//

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include "cmndm.h"

#include "pxvbcomponentmanager.h"
#include <iapplconfiguration.h>
#include "pxvbinitialization.h"
#include "pxvborderentryparamchecker.h"
#include "pxvbordertransmit.h"
#include "pxvbsession.h"
#include "pxvbordertransmit.h"
#include <icsc_logger.h>

#include "pvhx04_includes.h"

#include <pxvbcomponentbadstateexception.h>
#include <putenvfailedexception.h>
#include <libbasardbsql_databaseinfo.h>
//--------------------------------------------------------------------------------------------------//
// class definition section
//--------------------------------------------------------------------------------------------------//
namespace domMod
{
namespace batchOrder
{
namespace pxVerbund
{

//--------------------------------------------------------------------------------------------------//
	PXVBComponentManager::PXVBComponentManager( libcsc_utils::IApplConfigurationPtr config, libcsc_utils::ICSC_LoggerPtr csc_logger )
	: m_IApplConfiguration( config ), m_CSC_Logger( csc_logger )
	{
        METHODNAME_DEF( PXVBComponentManager, PXVBComponentManager )
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
	}

//--------------------------------------------------------------------------------------------------//
	PXVBComponentManager::~PXVBComponentManager()
	{
        METHODNAME_DEF( PXVBComponentManager, ~PXVBComponentManager )
        BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );
	}

//--------------------------------------------------------------------------------------------------//
	void PXVBComponentManager::injectCscDbConnection(libcsc::persistence::ConnectionPtr cscDbConnection)
	{
		METHODNAME_DEF( PXVBComponentManager, injectCscDbConnection )
		BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
	
		m_CscDbConnection = cscDbConnection;
	}

//--------------------------------------------------------------------------------------------------//
	libcsc::persistence::ConnectionPtr PXVBComponentManager::getCscDbConnection() const
	{
		return m_CscDbConnection;
	}

//--------------------------------------------------------------------------------------------------//
	pxOrderTransmitPtr PXVBComponentManager::getPXOrderTransmit()
	{
        METHODNAME_DEF( PXVBComponentManager, getPXOrderTransmit )
        BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

		if( 0 == m_pxOrderTransmit.get() )
		{
			pxSessionInitialization pxSessInit;
			basar::I18nString paraVal1;
			basar::I18nString paraVal2;

			pxSessInit.setBranchInformation(m_IApplConfiguration->getBranchNo(), m_IApplConfiguration->getCountryCode() );
			pxSessInit.setDBInformation(m_IApplConfiguration->getIFXConfiguration().dbServer, m_IApplConfiguration->getIFXConfiguration().database);
			pxSessInit.setDevice((::pxDeviceType)m_IApplConfiguration->getDeviceType(), m_IApplConfiguration->getDeviceName());
			pxSessInit.setMessageFileName(m_IApplConfiguration->getMessageFile());

			m_pxOrderTransmit = pxOrderTransmitPtr(new pxOrderTransmit(pxSessInit));
			m_pxOrderTransmit->injectDBConnection(getCscDbConnection());
			m_pxOrderTransmit->prepareSession();
		}

		if( !m_pxOrderTransmit->IsGoodState() )
		{
			throw libcsc_utils::PXVBComponentBadStateException( basar::ExceptInfo(fun, "m_pxOrderTransmit is not in good state", __FILE__, __LINE__) );
		}

		return m_pxOrderTransmit;
	}
//--------------------------------------------------------------------------------------------------//
	pxOrderEntryParamPtr PXVBComponentManager::getPXOrderEntryParam()
	{
        METHODNAME_DEF( PXVBComponentManager, getPXOrderEntryParam )
        BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

		if( 0 == m_pxOrderEntryParam.get() )
		{
			m_pxOrderEntryParam = pxOrderEntryParamPtr( getPXVBSession()->get()->getOrderEntryParam(
															m_IApplConfiguration->getBranchNo()
															) );	
		}

		if( !m_pxOrderEntryParam->IsGoodState() )
		{
			throw libcsc_utils::PXVBComponentBadStateException( basar::ExceptInfo(fun, "m_pxOrderEntryParam is not in good state", __FILE__, __LINE__) );
		}

		return m_pxOrderEntryParam;

	}
//--------------------------------------------------------------------------------------------------//

	IPXVBOrderEntryParamCheckerPtr PXVBComponentManager::getPXVBOrderEntryParamChecker()
	{
        METHODNAME_DEF( PXVBComponentManager, getPXVBOrderEntryParamChecker )
        BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );
	
        if( 0 == m_PXVBOrderEntryParamChecker.get() )
		{
			m_PXVBOrderEntryParamChecker = IPXVBOrderEntryParamCheckerPtr( new PXVBOrderEntryParamChecker(getPXOrderEntryParam(), m_CSC_Logger) );
		}

		return m_PXVBOrderEntryParamChecker;
	}
//--------------------------------------------------------------------------------------------------//
	IPXVBOrderTransmitPtr PXVBComponentManager::getPXVBOrderTransmit()
	{
        METHODNAME_DEF( PXVBComponentManager, getPXVBOrderTransmit )
        BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );
	
        if( 0 == m_PXVBOrderTransmit.get() )
		{
			m_PXVBOrderTransmit = IPXVBOrderTransmitPtr( new PXVBOrderTransmit( getPXOrderTransmit() ) );
		}

		return m_PXVBOrderTransmit;
	}
//--------------------------------------------------------------------------------------------------//
	IPXVBInitializationPtr PXVBComponentManager::getPXVBInitialization()
	{
	    METHODNAME_DEF( PXVBComponentManager, getPXVBInitialization )
        BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );
	
        if( 0 == m_PXVBInitialization.get() )
		{
			m_PXVBInitialization = IPXVBInitializationPtr( new PXVBInitialization(getPXOrderTransmit(), getPXOrderEntryParam()) );
		}

		return m_PXVBInitialization;
	}

	IPXVBSessionPtr PXVBComponentManager::getPXVBSession()
	{
		METHODNAME_DEF( PXVBComponentManager, getPXVBSession )
        BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );		

		if( 0 == m_PXVBSession.get() )
		{
			m_PXVBSession  = IPXVBSessionPtr( new PXVBSession( getPXOrderTransmit() ) );
			m_PXVBSession->get()->SetSubDeviceType( m_IApplConfiguration->getDeviceName().c_str() );
		}

		return m_PXVBSession;
	}
} // end namespace pxVerbund
} // end namespace batchOrder
} // end namespace domMod
