//-------------------------------------------------------------------------------------------------------------------//
/*! \file	
 *  \brief		implementation of CICSOrderAccessorResponse
 *  \author		Steffen Heinlein
 *  \date		27.05.2013
 */
//-------------------------------------------------------------------------------------------------------------------//

#include <icsc_logger.h>
#include <classinfo_macros.h>
#include <searchyiterator.h>
#include <libbasardbaspect.h>
#include <transactionguard.h>
#include <accessorexecutionexception.h>

#include "csc_corpha_table_definitions.h"
#include "cicsorderaccessorresponse.h"
#include "property_definitions.h"
#include "cicsresponseacc_definitions.h"
#include "accessorinstancerefwrapper.h"
#include "recordtypecollection.h"

namespace domMod 
{		
namespace corpha
{
namespace processOrder
{
	//-------------------------------------------------------------------------------------------------------------------//
	CICSOrderAccessorResponse::~CICSOrderAccessorResponse()
	{		
		METHODNAME_DEF( CICSOrderAccessorResponse, ~CICSOrderAccessorResponse );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );
	}
	//-------------------------------------------------------------------------------------------------------------------//

	////-------------------------------------------------------------------------------------------------------------------//
	CICSOrderAccessorResponse::CICSOrderAccessorResponse( const basar::db::aspect::ConnectionRef tca, libcsc_utils::ICSC_LoggerPtr logger )				
		: CICSOrderAccessorBase( logger, lit::acc_dkotr::ACC_DKOTR, tca )
	{
		METHODNAME_DEF( CICSOrderAccessorResponse, CICSOrderAccessorResponse );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );
	}
	//-------------------------------------------------------------------------------------------------------------------//

	//-------------------------------------------------------------------------------------------------------------------//
	AccessorInstanceRefWrapper& CICSOrderAccessorResponse::getAccessor()
	{
		METHODNAME_DEF( CICSOrderAccessorResponse, getAccessor );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );
		return m_Accessor;
	}
	//-------------------------------------------------------------------------------------------------------------------//

	//-------------------------------------------------------------------------------------------------------------------//
	domMod::searchyiterator::SearchYIteratorPtr CICSOrderAccessorResponse::getSearchYit()
	{
		METHODNAME_DEF( CICSOrderAccessorResponse, getSearchYit );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );		

		m_SearchYit = domMod::searchyiterator::SearchYIteratorPtr(
						new domMod::searchyiterator::SearchYIterator(						
							properties::dkotr::KSCANR.toDescriptionString() +
							properties::dkotr::DIRECTION.toDescriptionString(),
							m_Logger->getLogger() ) );

		return m_SearchYit;
	}
	//-------------------------------------------------------------------------------------------------------------------//

	//-------------------------------------------------------------------------------------------------------------------//
	void CICSOrderAccessorResponse::findByPattern()
	{
		METHODNAME_DEF( CICSOrderAccessorResponse, findByPattern );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		doFindByPattern( lit::acc_dkotr::SELECT_DKOTR_BY_PATTERN );
	}
	//-------------------------------------------------------------------------------------------------------------------//

	//-------------------------------------------------------------------------------------------------------------------//
	basar::Int32 CICSOrderAccessorResponse::getCountByPattern()
	{
		METHODNAME_DEF( CICSOrderAccessorResponse, getCountByPattern );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		return doGetCountByPattern( lit::acc_dkotr::SELECT_DKOTR_COUNT_BY_PATTERN );
	}
	//-------------------------------------------------------------------------------------------------------------------//

	//-------------------------------------------------------------------------------------------------------------------//
	void CICSOrderAccessorResponse::prepareRetrieveCriteria(const basar::Int32 orderno)
	{
		METHODNAME_DEF( CICSOrderAccessorResponse, prepareRetrieveCriteria );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		basar::db::aspect::AccessorPropertyTable_YIterator searchyit = getSearchYit()->get();
		searchyit.setInt32( properties::dkotr::KSCANR, orderno );
		searchyit.setString( properties::dkotr::DIRECTION, domMod::corpha::recordtypes::DIRECTION_RECEIVE );				
	}
	//-------------------------------------------------------------------------------------------------------------------//

	//-------------------------------------------------------------------------------------------------------------------//
	CICSRecord CICSOrderAccessorResponse::getCICSRecord( basar::db::aspect::AccessorPropertyTable_YIterator yit )
	{
		METHODNAME_DEF( CICSOrderAccessorResponse, getCICSRecord );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		CICSRecord retval;

		retval.CSCOrderNo = yit.getInt32( properties::dkotr::KSCANR );
		retval.SeqeuentialNo = yit.getInt32( properties::dkotr::LFDNR );
		retval.RecordType = yit.getString( properties::dkotr::SA );
		retval.Direction = yit.getString( properties::dkotr::DIRECTION );
		retval.Status = yit.getString( properties::dkotr::STATUS );
		retval.Time = yit.getInt32( properties::dkotr::ZEIT );
		retval.Buffer = yit.getString( properties::dkotr::BUFFER );

		return retval;
	}
	//-------------------------------------------------------------------------------------------------------------------//


} // namespace processOrder
} // namespace corpha
} // namespace domMod
