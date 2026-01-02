//--------------------------------------------------------------------------------------------------//
/*! \brief 
 *  \author     Steffen Heinlein
 *  \date       18.09.2012
 *  \version    00.00.00.01
 */ //--------------------------------------------------------------------------------------------------//

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include "pxvbcomponentmanager.h"
#include <iapplconfiguration.h>
#include <icsc_logger.h>
#include <pxvbcomponentbadstateexception.h>
#include <putenvfailedexception.h>
#include "pxvbinitialization.h"
#include "pxvborderentryparamchecker.h"
#include "pxvbsession.h"
#include "pxvbdbconnection.h"
#include "pvhx04_includes.h"
#include <sstream>
#include <classinfo_macros.h>

//--------------------------------------------------------------------------------------------------//
// class definition section
//--------------------------------------------------------------------------------------------------//
namespace domMod
{
namespace corpha
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

	//--------------------------------------------------------------------------------------------------//
	PXVBComponentManager::~PXVBComponentManager()
	{
        METHODNAME_DEF( PXVBComponentManager, ~PXVBComponentManager )
        BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );
	}
	//--------------------------------------------------------------------------------------------------//

	//--------------------------------------------------------------------------------------------------//
	pxOrderTransmitPtr PXVBComponentManager::getPXOrderTransmit()
	{
        METHODNAME_DEF( PXVBComponentManager, getPXOrderTransmit )
        BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

		if( 0 == m_pxOrderTransmit.get() )
		{
			m_pxOrderTransmit = pxOrderTransmitPtr( 
				new pxOrderTransmit(
				m_IApplConfiguration->getBranchNo(),
				m_IApplConfiguration->getCountryCode(),
				m_IApplConfiguration->getDataSource(),				
				(::pxDeviceType)(m_IApplConfiguration->getDeviceType()),
				m_IApplConfiguration->getDeviceName(),
				m_IApplConfiguration->getMessageFile())
				);
		}

		if( !m_pxOrderTransmit->IsGoodState() )
		{
			std::stringstream ss;
			ss << "m_pxOrderTransmit is not in good state: " << m_pxOrderTransmit->ErrorMsg();
			throw libcsc_utils::PXVBComponentBadStateException( basar::ExceptInfo(fun, ss.str().c_str(), __FILE__, __LINE__) );
		}
		return m_pxOrderTransmit;
	}
	//--------------------------------------------------------------------------------------------------//

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
	
	//--------------------------------------------------------------------------------------------------//
	IPXVBInitializationPtr PXVBComponentManager::getPXVBInitialization()
	{
	    METHODNAME_DEF( PXVBComponentManager, getPXVBInitialization )
        BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );
	
        if( 0 == m_PXVBInitialization.get() )
		{
			m_PXVBInitialization = IPXVBInitializationPtr( new PXVBInitialization(getPXOrderTransmit(), getPXOrderEntryParam(), m_CSC_Logger) );
		}

		return m_PXVBInitialization;
	}
	//--------------------------------------------------------------------------------------------------//

	//--------------------------------------------------------------------------------------------------//
	IPXVBSessionPtr PXVBComponentManager::getPXVBSession()
	{
		METHODNAME_DEF( PXVBComponentManager, getPXVBSession )
        BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );		

		if( 0 == m_PXVBSession.get() )
		{
			m_PXVBSession  = IPXVBSessionPtr( new PXVBSession( getPXOrderTransmit(), m_CSC_Logger ) );
		}

		return m_PXVBSession;
	}
	//--------------------------------------------------------------------------------------------------//

	//--------------------------------------------------------------------------------------------------//
	IPXVBDBConnectionPtr PXVBComponentManager::getPXVBDBConnection()
	{
		METHODNAME_DEF( PXVBComponentManager, getPXVBSession )
        BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

		if( 0 == m_PXVBDBConnection.get() )
		{
			m_PXVBDBConnection  = IPXVBDBConnectionPtr( new PXVBDBConnection( getPXOrderTransmit(), m_CSC_Logger) );
		}

		return m_PXVBDBConnection;
	}
	//--------------------------------------------------------------------------------------------------//

} // end namespace pxVerbund
} // end namespace corpha
} // end namespace domMod
