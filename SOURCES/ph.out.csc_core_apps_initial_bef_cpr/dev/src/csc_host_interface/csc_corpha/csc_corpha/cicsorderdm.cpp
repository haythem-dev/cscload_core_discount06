//-------------------------------------------------------------------------------------------------------------------//
/*! \file	
 *  \brief		implementation of cics module DKOTE/DKOTO
 *  \author		Steffen Heinlein
 *  \date		10.09.2012
 */
//-------------------------------------------------------------------------------------------------------------------//

#include <icsc_logger.h>
#include <classinfo_macros.h>
#include <libbasardbaspect.h>
#include <transactionguard.h>
#include <accessorexecutionexception.h>

#include "cicsorderdm.h"
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
	CICSOrderDM::CICSOrderDM( const basar::db::aspect::ConnectionRef tca, libcsc_utils::ICSC_LoggerPtr logger, libcsc_utils::IApplConfigurationPtr applConfiguration )
		: m_Logger( logger ), m_CSCOrderNo( CICSOrderDM::NOTINITIALIZED ), m_CICSOrderAccessorManager( tca, logger, applConfiguration )
	{
		METHODNAME_DEF( CICSOrderDM, CICSOrderDM );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );
	}
	//-------------------------------------------------------------------------------------------------------------------//

	//-------------------------------------------------------------------------------------------------------------------//
	CICSOrderDM::~CICSOrderDM()
	{		
		METHODNAME_DEF( CICSOrderDM, ~CICSOrderDM );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );
	}
	//-------------------------------------------------------------------------------------------------------------------//

	//-------------------------------------------------------------------------------------------------------------------//
	void CICSOrderDM::doInit()
	{
		METHODNAME_DEF( CICSOrderDM, doInit );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );
	}
	//-------------------------------------------------------------------------------------------------------------------//

	//-------------------------------------------------------------------------------------------------------------------//
	void CICSOrderDM::doShutdown()
	{
		METHODNAME_DEF( CICSOrderDM, doShutdown );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );
	}
	//-------------------------------------------------------------------------------------------------------------------//

	//-------------------------------------------------------------------------------------------------------------------//
	libcsc_utils::ICSC_LoggerPtr CICSOrderDM::getLogger() const
	{
		METHODNAME_DEF( CICSOrderDM, getLogger );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );
		return m_Logger;
	}
	//-------------------------------------------------------------------------------------------------------------------//	

	//-------------------------------------------------------------------------------------------------------------------//
	CICSRecord CICSOrderDM::getCICSRecord( basar::db::aspect::AccessorPropertyTable_YIterator yit )
	{
		METHODNAME_DEF( CICSOrderDM, getCICSRecord );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		return m_AccessorResponsePtr->getCICSRecord( yit );		
	}
	//-------------------------------------------------------------------------------------------------------------------//	

	//-------------------------------------------------------------------------------------------------------------------//
	void CICSOrderDM::retrieve()
	{
		METHODNAME_DEF( CICSOrderDM, retrieve );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		if( !isInitialized() )
		{
			throw basar::cmnutil::BasarInvalidStateException( basar::ExceptInfo( fun, "not initialized", __FILE__, __LINE__ ) );
		}
		
		m_AccessorResponsePtr->prepareRetrieveCriteria( m_CSCOrderNo );
		m_AccessorResponsePtr->findByPattern();
	}
	//-------------------------------------------------------------------------------------------------------------------//

	//-------------------------------------------------------------------------------------------------------------------//
	void CICSOrderDM::send( recordtypes::RecordTypeCollectionPtr collection )
	{
		METHODNAME_DEF( CICSOrderDM, send );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		basar::VarString logmessage("");
		logmessage.format( "   -> started inserting order records to DKOTO/DKOTE for OrderNo:%d", m_CSCOrderNo );
		m_Logger->log( log4cplus::INFO_LOG_LEVEL, logmessage );								
		
		prepareForTransfer( collection );

		if( !isInitialized() )
		{
			basar::cmnutil::BasarInvalidStateException( basar::ExceptInfo( fun, "not initialized", __FILE__, __LINE__ ) );
		}
		m_AccessorPtr->send();

		logmessage.format( "   -> finished inserting order records to DKOTO/DKOTE for OrderNo:%d", m_CSCOrderNo );
		m_Logger->log( log4cplus::INFO_LOG_LEVEL, logmessage );								
	}
	//-------------------------------------------------------------------------------------------------------------------//

	//-------------------------------------------------------------------------------------------------------------------//
	void CICSOrderDM::prepareForTransfer( recordtypes::RecordTypeCollectionPtr collection )
	{
		METHODNAME_DEF( CICSOrderDM, prepareForTransfer );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		if( !isInitialized() )
		{
			throw basar::cmnutil::BasarInvalidStateException( basar::ExceptInfo( fun, "not initialized", __FILE__, __LINE__ ) );			
		}

		m_AccessorPtr->getPropTab().clear();		
		while( !collection->isEmpty() )
		{						
			m_AccessorPtr->addOrderItemYit( collection->getRecord(), collection->getCSCOrderNo(), collection->getTransferTimeID() );			
		}		
	}
	//-------------------------------------------------------------------------------------------------------------------//

	//-------------------------------------------------------------------------------------------------------------------//
	void CICSOrderDM::init( const basar::Long64 cscorderno )
	{
		METHODNAME_DEF( CICSOrderDM, init );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_CSCOrderNo = cscorderno;
		m_AccessorPtr = m_CICSOrderAccessorManager.getAccessor(cscorderno);
		m_AccessorResponsePtr = m_CICSOrderAccessorManager.getAccessor(cscorderno, false);
	}
	//-------------------------------------------------------------------------------------------------------------------//

	//-------------------------------------------------------------------------------------------------------------------//
	void CICSOrderDM::shutdown()
	{
		METHODNAME_DEF( CICSOrderDM, shutdown );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );
		m_CSCOrderNo = CICSOrderDM::NOTINITIALIZED;		
		getPropTab().clear();
		getResponsePropTab().clear();
	}
	//-------------------------------------------------------------------------------------------------------------------//

	//-------------------------------------------------------------------------------------------------------------------//
	bool CICSOrderDM::isInitialized() const
	{
		METHODNAME_DEF( CICSOrderDM, isInitialized );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );
		if( CICSOrderDM::NOTINITIALIZED == m_CSCOrderNo )
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	//-------------------------------------------------------------------------------------------------------------------//

	//-------------------------------------------------------------------------------------------------------------------//
	basar::db::aspect::AccessorPropertyTableRef CICSOrderDM::getPropTab()
	{
		METHODNAME_DEF( CICSOrderAccessorOdd, getPropTab );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		return m_AccessorPtr->getPropTab();
	}
	//-------------------------------------------------------------------------------------------------------------------//

	//-------------------------------------------------------------------------------------------------------------------//
	basar::db::aspect::AccessorPropertyTableRef CICSOrderDM::getResponsePropTab()
	{
		METHODNAME_DEF( CICSOrderAccessorOdd, getResponsePropTab );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		return m_AccessorResponsePtr->getPropTab();
	}
	//-------------------------------------------------------------------------------------------------------------------//

} // namespace processOrder
} // namespace corpha
} // namespace domMod
