//-------------------------------------------------------------------------------------------------------------------//
/*! \file	
 *  \brief		implementation of CICSOrderAccessorManager
 *  \author		Steffen Heinlein
 *  \date		27.05.2013
 */
//-------------------------------------------------------------------------------------------------------------------//

#include <icsc_logger.h>
#include <classinfo_macros.h>
#include <csc_logger.h>
#include <transactionguard.h>
#include <accessorexecutionexception.h>
#include <iapplconfiguration.h>

#include "cicsorderaccessormanager.h"
#include "property_definitions.h"
#include "accessorinstancerefwrapper.h"
#include "recordtypecollection.h"

namespace domMod 
{		
namespace corpha
{
namespace processOrder
{
	//-------------------------------------------------------------------------------------------------------------------//
	CICSOrderAccessorManager::CICSOrderAccessorManager( const basar::db::aspect::ConnectionRef tca, libcsc_utils::ICSC_LoggerPtr logger, libcsc_utils::IApplConfigurationPtr applConfiguration)
		: m_Logger( logger ), m_TCAConn( tca ), m_ApplConfiguration( applConfiguration )
	{
		METHODNAME_DEF( CICSOrderAccessorManager, CICSOrderAccessorManager );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );							
	}
	//-------------------------------------------------------------------------------------------------------------------//

	//-------------------------------------------------------------------------------------------------------------------//
	CICSOrderAccessorBasePtr CICSOrderAccessorManager::getAccessorResponse()
	{
		METHODNAME_DEF( CICSOrderAccessorManager, getAccessorResponse ) 
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );	

		if( 0 == m_AccessorResponse.get() )
		{
			m_AccessorResponse = CICSOrderAccessorBasePtr( new CICSOrderAccessorResponse(m_TCAConn, m_Logger) );
		}
		return m_AccessorResponse;		
	}
	//-------------------------------------------------------------------------------------------------------------------//

	//-------------------------------------------------------------------------------------------------------------------//
	CICSOrderAccessorBasePtr CICSOrderAccessorManager::getAccessorEven()
	{
		METHODNAME_DEF( CICSOrderAccessorManager, getAccessorEven ) 
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );	

		if( 0 == m_AccessorEven.get() )
		{
			m_AccessorEven = CICSOrderAccessorBasePtr( new CICSOrderAccessorEven(m_TCAConn, m_Logger) );
			m_AccessorEven->setBulkInsert(m_ApplConfiguration->getBulkInsert());
		}
		return m_AccessorEven;		
	}
	//-------------------------------------------------------------------------------------------------------------------//

	//-------------------------------------------------------------------------------------------------------------------//
	CICSOrderAccessorBasePtr CICSOrderAccessorManager::getAccessorOdd()
	{
		METHODNAME_DEF( CICSOrderAccessorManager, getAccessorOdd ) 
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );	

		if( 0 == m_AccessorOdd.get() )
		{
			m_AccessorOdd = CICSOrderAccessorBasePtr( new CICSOrderAccessorOdd(m_TCAConn, m_Logger) );
			m_AccessorOdd->setBulkInsert(m_ApplConfiguration->getBulkInsert());
		}
		return m_AccessorOdd;		
	}
	//-------------------------------------------------------------------------------------------------------------------//

	//-------------------------------------------------------------------------------------------------------------------//
	CICSOrderAccessorManager::~CICSOrderAccessorManager()
	{		
		METHODNAME_DEF( CICSOrderAccessorManager, ~CICSOrderAccessorManager );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );
	}
	//-------------------------------------------------------------------------------------------------------------------//	


	//-------------------------------------------------------------------------------------------------------------------//
	bool CICSOrderAccessorManager::isEven( const basar::Long64 orderno )
	{
		METHODNAME_DEF( CICSOrderAccessorManager, isEven );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );
		
		if( 0 == (orderno % 2) )
		{
			return true;
		}
		return false;
	}
	//-------------------------------------------------------------------------------------------------------------------//

	//-------------------------------------------------------------------------------------------------------------------//
	CICSOrderAccessorBasePtr CICSOrderAccessorManager::getAccessor( const basar::Long64 orderno, bool DirectionSend /* = true */ )
	{
		METHODNAME_DEF( CICSOrderAccessorManager, getAccessor );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		if( DirectionSend )
		{
			if( isEven(orderno) )
			{
				return getAccessorEven();
			}
			else
			{
				return getAccessorOdd();
			}
		}
		else
		{
			return getAccessorResponse();
		}
	}
	//-------------------------------------------------------------------------------------------------------------------//


} // namespace processOrder
} // namespace corpha
} // namespace domMod
