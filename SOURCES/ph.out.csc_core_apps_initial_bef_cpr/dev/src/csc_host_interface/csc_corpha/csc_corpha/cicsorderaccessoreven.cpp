//-------------------------------------------------------------------------------------------------------------------//
/*! \file	
 *  \brief		implementation of CICSOrderAccessorBase
 *  \author		Steffen Heinlein
 *  \date		27.05.2013
 */
//-------------------------------------------------------------------------------------------------------------------//

#include <icsc_logger.h>
#include <csc_logger.h>
#include <transactionguard.h>
#include <accessorexecutionexception.h>

#include "csc_corpha_table_definitions.h"
#include "cicsorderaccessoreven.h"
#include "property_definitions.h"
#include "dkoteacc_definitions.h"
#include "accessorinstancerefwrapper.h"
#include "recordtypecollection.h"
#include <classinfo_macros.h>
#include <searchyiterator.h>
#include <libbasardbaspect.h>

namespace domMod 
{		
namespace corpha
{
namespace processOrder
{
	//-------------------------------------------------------------------------------------------------------------------//
	CICSOrderAccessorEven::~CICSOrderAccessorEven()
	{		
		METHODNAME_DEF( CICSOrderAccessorEven, ~CICSOrderAccessorEven );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );
	}
	//-------------------------------------------------------------------------------------------------------------------//

	////-------------------------------------------------------------------------------------------------------------------//
	CICSOrderAccessorEven::CICSOrderAccessorEven( const basar::db::aspect::ConnectionRef tca, libcsc_utils::ICSC_LoggerPtr logger )				
		: CICSOrderAccessorBase( logger, lit::acc_dkote::ACC_DKOTE, tca )
	{
		METHODNAME_DEF( CICSOrderAccessorEven, CICSOrderAccessorEven );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );
	}
	//-------------------------------------------------------------------------------------------------------------------//

	//-------------------------------------------------------------------------------------------------------------------//
	AccessorInstanceRefWrapper& CICSOrderAccessorEven::getAccessor()
	{
		METHODNAME_DEF( CICSOrderAccessorEven, getAccessor );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );
		return m_Accessor;
	}
	//-------------------------------------------------------------------------------------------------------------------//

	//-------------------------------------------------------------------------------------------------------------------//
	domMod::searchyiterator::SearchYIteratorPtr CICSOrderAccessorEven::getSearchYit()
	{
		METHODNAME_DEF( CICSOrderAccessorEven, getSearchYit );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );		

		m_SearchYit = domMod::searchyiterator::SearchYIteratorPtr(
						new domMod::searchyiterator::SearchYIterator(						
							properties::dkote::TIME.toDescriptionString() +
							properties::dkote::KSCANR.toDescriptionString() +
							properties::dkote::DIRECTION.toDescriptionString() +
							properties::dkote::STATUS.toDescriptionString(),
							m_Logger->getLogger() ) );

		return m_SearchYit;
	}
	//-------------------------------------------------------------------------------------------------------------------//

	//-------------------------------------------------------------------------------------------------------------------//
	void CICSOrderAccessorEven::findByPattern()
	{
		METHODNAME_DEF( CICSOrderAccessorEven, findByPattern );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		doFindByPattern( lit::acc_dkote::SELECT_DKOTE_BY_PATTERN );
	}
	//-------------------------------------------------------------------------------------------------------------------//

	//-------------------------------------------------------------------------------------------------------------------//
	basar::Int32 CICSOrderAccessorEven::getCountByPattern()
	{
		METHODNAME_DEF( CICSOrderAccessorEven, getCountByPattern );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		return doGetCountByPattern( lit::acc_dkote::SELECT_DKOTE_COUNT_BY_PATTERN );
	}
	//-------------------------------------------------------------------------------------------------------------------//

	//-------------------------------------------------------------------------------------------------------------------//
	void CICSOrderAccessorEven::addOrderItemYit( const domMod::corpha::recordtypes::RecordTypeBasePtr record, const basar::Int32 orderno, const basar::Int32 transfertimeid )
	{
		METHODNAME_DEF( CICSOrderAccessorEven, addOrderItemYit );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );		

		basar::db::aspect::AccessorPropertyTable_YIterator yit = addEmptyYit();

		yit.setInt32( properties::dkote::TIME, transfertimeid );
		yit.setInt32( properties::dkote::KSCANR, orderno );
		yit.setInt32( properties::dkote::LFDNR, static_cast<basar::Int32>(record->getSequentialNo()) );
		yit.setString( properties::dkote::SA, record->getRecordTypeName() );
		yit.setString( properties::dkote::DIRECTION, record->getDirection() );
		yit.setString( properties::dkote::STATUS, record->getStatus() );		
		yit.setString( properties::dkote::BUFFER, record->serialize() );		

		basar::DateTime dtnow = basar::DateTime::getCurrent();	
		basar::Int32 now = (dtnow.getHour() * 10000) + (dtnow.getMinute() * 100) + (dtnow.getSec());		
		yit.setInt32( properties::dkote::ZEIT, now );		
	}
	//-------------------------------------------------------------------------------------------------------------------//

	//-------------------------------------------------------------------------------------------------------------------//
	void CICSOrderAccessorEven::prepareRetrieveCriteria(const basar::Int32 orderno)
	{
		METHODNAME_DEF( CICSOrderAccessorEven, prepareRetrieveCriteria );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		basar::db::aspect::AccessorPropertyTable_YIterator searchyit = getSearchYit()->get();
		searchyit.setInt32( properties::dkote::KSCANR, orderno );
		searchyit.setString( properties::dkote::DIRECTION, domMod::corpha::recordtypes::DIRECTION_RECEIVE );		
		searchyit.setString( properties::dkote::STATUS, domMod::STATUS_TRANSFER_COMPLETED );
	}
	//-------------------------------------------------------------------------------------------------------------------//

	//-------------------------------------------------------------------------------------------------------------------//
	void CICSOrderAccessorEven::send()
	{
		METHODNAME_DEF( CICSOrderAccessorEven, send );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		doSend( lit::acc_dkote::SAVE_DKOTE );
		//doSetTransferCompleted( lit::acc_dkote::SAVE_DKOTE_STATUS );
	}
	//-------------------------------------------------------------------------------------------------------------------//

	//-------------------------------------------------------------------------------------------------------------------//
	CICSRecord CICSOrderAccessorEven::getCICSRecord( basar::db::aspect::AccessorPropertyTable_YIterator yit )
	{
		METHODNAME_DEF( CICSOrderAccessorEven, getCICSRecord );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		CICSRecord retval;

		retval.CSCOrderNo = yit.getInt32( properties::dkote::KSCANR );
		retval.SeqeuentialNo = yit.getInt32( properties::dkote::LFDNR );
		retval.RecordType = yit.getString( properties::dkote::SA );
		retval.Direction = yit.getString( properties::dkote::DIRECTION );
		retval.Status = yit.getString( properties::dkote::STATUS );
		retval.Time = yit.getInt32( properties::dkote::ZEIT );
		retval.Buffer = yit.getString( properties::dkote::BUFFER );

		return retval;
	}
	//-------------------------------------------------------------------------------------------------------------------//


} // namespace processOrder
} // namespace corpha
} // namespace domMod
