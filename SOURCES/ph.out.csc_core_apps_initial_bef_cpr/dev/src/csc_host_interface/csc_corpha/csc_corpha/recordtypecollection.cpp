//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  RecordTypeCollection
 *  \author Steffen Heinlein
 *  \date   04.09.2012
 */
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include <icsc_logger.h>
#include <classinfo_macros.h>
#include <libbasarcmnutil.h>
#include "recordtypecollection.h"


//----------------------------------------------------------------------------//
// forward declaration section
//----------------------------------------------------------------------------//

namespace domMod
{
namespace corpha
{
namespace recordtypes
{	
	//----------------------------------------------------------------------------//
	RecordTypeCollection::RecordTypeQueuePtr RecordTypeCollection::getRecords() const
	{
		METHODNAME_DEF( RecordTypeCollection, getRecords );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		if( 0 == m_Records.get() )
		{
			m_Records = RecordTypeQueuePtr( new std::queue< RecordTypeBasePtr >() );
		}
		return m_Records;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeCollection::clear()
	{
		METHODNAME_DEF( RecordTypeCollection, clear );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		getRecords().reset();
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	RecordTypeCollection::RecordTypeCollection( libcsc_utils::ICSC_LoggerPtr logger )				
		: m_Logger( logger )
	{
		METHODNAME_DEF( RecordTypeCollection, RecordTypeCollection );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	RecordTypeCollection::~RecordTypeCollection()
	{
		METHODNAME_DEF( RecordTypeCollection, ~RecordTypeCollection );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );
	}
	//----------------------------------------------------------------------------//		

	//----------------------------------------------------------------------------//		
	void RecordTypeCollection::setTransferTimeID( const basar::Long64& time )
	{
		METHODNAME_DEF( RecordTypeCollection, setTransferTimeID );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_TransferTimeID = time;
	}

	//----------------------------------------------------------------------------//		
	void RecordTypeCollection::setCSCOrderNo( const basar::Long64& orderno )
	{
		METHODNAME_DEF( RecordTypeCollection, setCSCOrderNo );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_CSCOrderNo = orderno;
	}
	//----------------------------------------------------------------------------//		

	//----------------------------------------------------------------------------//		
	basar::Long64 RecordTypeCollection::getTransferTimeID() const
	{
		METHODNAME_DEF( RecordTypeCollection, getTransferTimeID );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		return m_TransferTimeID;
	}
	//----------------------------------------------------------------------------//		

	//----------------------------------------------------------------------------//		
	basar::Long64 RecordTypeCollection::getCSCOrderNo() const
	{
		METHODNAME_DEF( RecordTypeCollection, getCSCOrderNo );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		return m_CSCOrderNo;
	}
	//----------------------------------------------------------------------------//		

	//----------------------------------------------------------------------------//		
	bool RecordTypeCollection::isEmpty() const
	{
		METHODNAME_DEF( RecordTypeCollection, isEmpty );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		return getRecords()->empty();
	}
	//----------------------------------------------------------------------------//	

	//----------------------------------------------------------------------------//	
	size_t RecordTypeCollection::getSize() const
	{
		METHODNAME_DEF( RecordTypeCollection, getSize );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		return getRecords()->size();
	}
	//----------------------------------------------------------------------------//	

	//----------------------------------------------------------------------------//	
	void RecordTypeCollection::addRecord( const RecordTypeBasePtr record )
	{
		METHODNAME_DEF( RecordTypeCollection, addRecord );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		record->setSequentialNo( getRecords()->size() );
		getRecords()->push( record );
	}
	//----------------------------------------------------------------------------//	

	//----------------------------------------------------------------------------//	
	const RecordTypeBasePtr RecordTypeCollection::getRecord()
	{
		METHODNAME_DEF( RecordTypeCollection, getRecord );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		if( isEmpty() )
		{
			throw basar::cmnutil::BasarOutOfRangeIndexException( 
				basar::ExceptInfo( fun, "tried to get element from empty collection", __FILE__, __LINE__ ) );			
		}
		RecordTypeBasePtr retval = getRecords()->front();
		getRecords()->pop();
		return retval;				
	}
	 //----------------------------------------------------------------------------//	


} // namespace recordtypes
} // namespace corpha
} // namespace domMod
