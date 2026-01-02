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
#include "cicsorderaccessorodd.h"
#include "property_definitions.h"
#include "dkotoacc_definitions.h"
#include "accessorinstancerefwrapper.h"
#include "recordtypecollection.h"
#include "csc_corpha_table_definitions.h"
#include <classinfo_macros.h>
#include <libbasardbaspect.h>
#include <searchyiterator.h>


namespace domMod 
{		
namespace corpha
{
namespace processOrder
{
	//-------------------------------------------------------------------------------------------------------------------//
	CICSOrderAccessorOdd::~CICSOrderAccessorOdd()
	{		
		METHODNAME_DEF( CICSOrderAccessorOdd, ~CICSOrderAccessorOdd );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );
	}
	//-------------------------------------------------------------------------------------------------------------------//

	////-------------------------------------------------------------------------------------------------------------------//
	CICSOrderAccessorOdd::CICSOrderAccessorOdd( const basar::db::aspect::ConnectionRef tca, libcsc_utils::ICSC_LoggerPtr logger )		
		: CICSOrderAccessorBase( logger, lit::acc_dkoto::ACC_DKOTO, tca )
	{
		METHODNAME_DEF( CICSOrderAccessorOdd, CICSOrderAccessorOdd );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );
	}
	//-------------------------------------------------------------------------------------------------------------------//

	//-------------------------------------------------------------------------------------------------------------------//
	AccessorInstanceRefWrapper& CICSOrderAccessorOdd::getAccessor()
	{
		METHODNAME_DEF( CICSOrderAccessorOdd, getAccessor );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );
		return m_Accessor;
	}
	//-------------------------------------------------------------------------------------------------------------------//

	//-------------------------------------------------------------------------------------------------------------------//
	domMod::searchyiterator::SearchYIteratorPtr CICSOrderAccessorOdd::getSearchYit()
	{
		METHODNAME_DEF( CICSOrderAccessorOdd, getSearchYit );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );		

		m_SearchYit = domMod::searchyiterator::SearchYIteratorPtr(
						new domMod::searchyiterator::SearchYIterator(						
							properties::dkoto::TIME.toDescriptionString() +
							properties::dkoto::KSCANR.toDescriptionString() +
							properties::dkoto::DIRECTION.toDescriptionString() + 
							properties::dkoto::STATUS.toDescriptionString(),
							m_Logger->getLogger() ) );		

		return m_SearchYit;
	}
	//-------------------------------------------------------------------------------------------------------------------//

	//-------------------------------------------------------------------------------------------------------------------//
	void CICSOrderAccessorOdd::findByPattern()
	{
		METHODNAME_DEF( CICSOrderAccessorOdd, findByPattern );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		doFindByPattern( lit::acc_dkoto::SELECT_DKOTO_BY_PATTERN );		
	}
	//-------------------------------------------------------------------------------------------------------------------//

	//-------------------------------------------------------------------------------------------------------------------//
	basar::Int32 CICSOrderAccessorOdd::getCountByPattern()
	{
		METHODNAME_DEF( CICSOrderAccessorOdd, getCountByPattern );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		return doGetCountByPattern( lit::acc_dkoto::SELECT_DKOTO_COUNT_BY_PATTERN );
	}
	//-------------------------------------------------------------------------------------------------------------------//

	//-------------------------------------------------------------------------------------------------------------------//
	void CICSOrderAccessorOdd::addOrderItemYit( const recordtypes::RecordTypeBasePtr record, const basar::Int32 orderno, const basar::Int32 transfertimeid )
	{
		METHODNAME_DEF( CICSOrderAccessorOdd, addOrderItemYit );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );		

		basar::db::aspect::AccessorPropertyTable_YIterator yit = addEmptyYit();

		yit.setInt32( properties::dkoto::TIME, transfertimeid );
		yit.setInt32( properties::dkoto::KSCANR, orderno );
		yit.setInt32( properties::dkoto::LFDNR, static_cast<basar::Int32>(record->getSequentialNo()) );
		yit.setString( properties::dkoto::SA, record->getRecordTypeName() );
		yit.setString( properties::dkoto::DIRECTION, record->getDirection() );
		yit.setString( properties::dkoto::STATUS, record->getStatus() );		
		yit.setString( properties::dkoto::BUFFER, record->serialize() );		

		basar::DateTime dtnow = basar::DateTime::getCurrent();	
		basar::Int32 now = (dtnow.getHour() * 10000) + (dtnow.getMinute() * 100) + (dtnow.getSec());		
		yit.setInt32( properties::dkoto::ZEIT, now );		
	}
	//-------------------------------------------------------------------------------------------------------------------//

	//-------------------------------------------------------------------------------------------------------------------//
	void CICSOrderAccessorOdd::prepareRetrieveCriteria(const basar::Int32 orderno)
	{
		METHODNAME_DEF( CICSOrderAccessorOdd, prepareRetrieveCriteria );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		basar::db::aspect::AccessorPropertyTable_YIterator searchyit = getSearchYit()->get();
		searchyit.setInt32( properties::dkoto::KSCANR, orderno );
		searchyit.setString( properties::dkoto::DIRECTION, domMod::corpha::recordtypes::DIRECTION_RECEIVE );		
		searchyit.setString( properties::dkoto::STATUS, domMod::STATUS_TRANSFER_COMPLETED );
	}
	//-------------------------------------------------------------------------------------------------------------------//

	//-------------------------------------------------------------------------------------------------------------------//
	void CICSOrderAccessorOdd::send()
	{
		METHODNAME_DEF( CICSOrderAccessorOdd, send );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		doSend( lit::acc_dkoto::SAVE_DKOTO );
		//doSetTransferCompleted( lit::acc_dkoto::SAVE_DKOTO_STATUS );
	}
	//-------------------------------------------------------------------------------------------------------------------//

	//-------------------------------------------------------------------------------------------------------------------//
	CICSRecord CICSOrderAccessorOdd::getCICSRecord( basar::db::aspect::AccessorPropertyTable_YIterator yit )
	{
		METHODNAME_DEF( CICSOrderAccessorOdd, getCICSRecord );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		CICSRecord retval;

		retval.CSCOrderNo = yit.getInt32( properties::dkoto::KSCANR );
		retval.SeqeuentialNo = yit.getInt32( properties::dkoto::LFDNR );
		retval.RecordType = yit.getString( properties::dkoto::SA );
		retval.Direction = yit.getString( properties::dkoto::DIRECTION );
		retval.Status = yit.getString( properties::dkoto::STATUS );
		retval.Time = yit.getInt32( properties::dkoto::ZEIT );
		retval.Buffer = yit.getString( properties::dkoto::BUFFER );

		return retval;
	}
	//-------------------------------------------------------------------------------------------------------------------//


} // namespace processOrder
} // namespace corpha
} // namespace domMod
