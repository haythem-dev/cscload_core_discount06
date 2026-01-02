//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  
 *  \author		Steffen Heinlein
 *  \date		26.11.2012
 */
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include <icsc_logger.h>
#include <classinfo_macros.h>
#include <iapplconfiguration.h>

#include "pxvbtaskcontrol.h"
#include "ipxvbservicelocator.h"

#include "ipxvbsessionptr.h"
#include "ipxvbsession.h"
#include "ipxvbdbconnectionptr.h"
#include "ipxvbdbconnection.h"

#include "csc_corphacmdlineoption_definitions.h"

//----------------------------------------------------------------------------//
// forward declaration section
//----------------------------------------------------------------------------//

namespace domMod
{
namespace corpha
{
namespace pxVerbund
{	
	//----------------------------------------------------------------------------//
	PXVBTaskControl::PXVBTaskControl( domMod::corpha::pxVerbund::IPXVBServiceLocatorPtr svcloc, libcsc_utils::IApplConfigurationPtr appcfg, libcsc_utils::ICSC_LoggerPtr logger )		
		: m_ApplConfiguration( appcfg ), m_PXVBServiceLocator( svcloc ), m_Logger( logger )
	{
		METHODNAME_DEF( PXVBTaskControl, PXVBTaskControl );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );		

		m_ApplicationName.format( "corpha %s", m_ApplConfiguration->getOrderFilter().c_str() );
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	PXVBTaskControl::~PXVBTaskControl()
	{
		METHODNAME_DEF( PXVBTaskControl, ~PXVBTaskControl );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );
	}
	//----------------------------------------------------------------------------//		

	//----------------------------------------------------------------------------//
	pxTaskControlPtr PXVBTaskControl::getPXTaskControl()
	{
		METHODNAME_DEF( PXVBTaskControl, getPXTaskControl );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		if( 0 == m_pxTaskControl.get() )
		{
			m_pxTaskControl = pxTaskControlPtr( 
								new pxTaskControl(	m_PXVBServiceLocator->getPXVBSession()->get(), 
													m_ApplConfiguration->getBranchNo(), 
													m_ApplicationName.c_str() ) );			
		}

		return m_pxTaskControl;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void PXVBTaskControl::setHeartBeat()
	{
		METHODNAME_DEF( PXVBTaskControl, setHeartBeat );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		try
		{
			m_PXVBServiceLocator->getPXVBDBConnection()->beginTransaction( MULTI_RECORD );
			nTime now;
			getPXTaskControl()->TaskControl( now );
			if( !getPXTaskControl()->IsGoodState() )
			{								
				m_Logger->log( log4cplus::WARN_LOG_LEVEL, "-> setHeartBeat failed: TaskControl is not in good state" );							
				m_PXVBServiceLocator->getPXVBDBConnection()->rollbackTransaction();
			}
			else
			{
				m_PXVBServiceLocator->getPXVBDBConnection()->commitTransaction( MULTI_RECORD );
			}			
		}
		catch( ... )
		{				
			m_Logger->log( log4cplus::ERROR_LOG_LEVEL, "-> setHeartBeat unexpected exception" );							
			m_PXVBServiceLocator->getPXVBDBConnection()->rollbackTransaction();	
		}

	}
	//----------------------------------------------------------------------------//

} // namespace pxVerbund
} // namespace corpha
} // namespace domMod
