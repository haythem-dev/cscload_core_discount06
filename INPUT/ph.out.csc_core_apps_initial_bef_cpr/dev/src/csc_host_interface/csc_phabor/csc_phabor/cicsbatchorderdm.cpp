//-------------------------------------------------------------------------------------------------------------------//
/*! \file		
 *  \brief		domain module for handling batchorders
 *  \author		Julian Machata
 *  \date		17.10.2012
 */
//-------------------------------------------------------------------------------------------------------------------//

#include "cmndm.h"
#include <icsc_logger.h>
#include <csc_logger.h>

#include "cicsbatchorderdm.h"
#include "cicsbatchorderdmptr.h"
#include "property_definitions.h"

namespace domMod 
{		
namespace batchOrder
{
namespace preparation
{
//-------------------------------------------------------------------------------------------------------------------//
CICSBatchOrderDM::CICSBatchOrderDM( libcsc_utils::ICSC_LoggerPtr csc_logger )
: BatchOrderDMBase(csc_logger),
  m_CSC_Logger(csc_logger),
  m_PreviousOffSetNo(0)

{
	METHODNAME_DEF( CICSBatchOrderDM, CICSBatchOrderDM );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
}

//-------------------------------------------------------------------------------------------------------------------//
CICSBatchOrderDM::~CICSBatchOrderDM()
{		
	METHODNAME_DEF( CICSBatchOrderDM, ~CICSBatchOrderDM );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
}

//-------------------------------------------------------------------------------------------------------------------//
basar::Int32 CICSBatchOrderDM::getLastKey()
{
	METHODNAME_DEF( CICSBatchOrderDM, getLastKey );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

	return 0;
}

//-------------------------------------------------------------------------------------------------------------------//
basar::db::aspect::AccessorPropertyTable_YIterator CICSBatchOrderDM::getFirstOrderHead()
{
	METHODNAME_DEF( CICSBatchOrderDM, getFirstOrderHead );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

	basar::db::aspect::AccessorPropertyTable_YIterator yitHead;

	yitHead = BatchOrderDMBase::getFirstOrderHead();

	// is already at end, cannot get next one
	if (yitHead.isEnd())
	{
		return yitHead;
	}

	// if it is the last head (one before .isEnd()) then check if it is complete
	++yitHead;
	if (yitHead == getBatchOrderHeads().end())
	{
		getBatchOrderPositions(getCurrentHead());
		basar::Int32 headPosCount = getPositionCountFromHead();
		basar::Int32 posPosCount = getPositionCountFromPositions();

		std::stringstream s;
		s << "Checking poscount on "<< getCurrentHead().getInt32(properties::dkbazk::KBAZKANR)
			<< " headpos " << headPosCount << ", pos " << posPosCount;
		BLOG_INFO(m_CSC_Logger->getLogger(), s.str());

		if (posPosCount != headPosCount)
		{
			s.str("");
			s << "Order " << getCurrentHead().getInt32(properties::dkbazk::KBAZKANR) << " not yet complete!";
			BLOG_WARN(m_CSC_Logger->getLogger(), s.str());

			getCurrentPositions().clear();
			return getBatchOrderHeads().end();
		}
	}
	return getCurrentHead();
}

//-------------------------------------------------------------------------------------------------------------------//
basar::db::aspect::AccessorPropertyTable_YIterator CICSBatchOrderDM::getNextOrderHead()
{
	METHODNAME_DEF( CICSBatchOrderDM, getNextOrderHead );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

	basar::db::aspect::AccessorPropertyTable_YIterator current = getCurrentHead();
	basar::db::aspect::AccessorPropertyTable_YIterator next = current; ++next;	
	basar::db::aspect::AccessorPropertyTable_YIterator last = next; 

	// is already at end, cannot get next one
	if (current.isEnd()){
		return current;
	}
	
	setCurrentHead( next );

	// check if now changed to last head
	if (getCurrentHead().isEnd()){
		return getCurrentHead();
	}

	++last; 

	// if it is the last head (one before .isEnd()) then check if it is complete
	if ( last == getBatchOrderHeads().end() ){

		getBatchOrderPositions( getCurrentHead() );
		basar::Int32 headPosCount = getPositionCountFromHead();
		basar::Int32 posPosCount = getPositionCountFromPositions();

		std::stringstream s;
		s << "Checking poscount on "<< getCurrentHead().getInt32(properties::dkbazk::KBAZKANR)
			<< " headpos " << headPosCount << ", pos " << posPosCount;
		BLOG_INFO(m_CSC_Logger->getLogger(), s.str());

		if (posPosCount != headPosCount ){
			getCurrentPositions().clear();
			return getBatchOrderHeads().end();
		}
	}	

	return getCurrentHead();
}

//-------------------------------------------------------------------------------------------------------------------//
basar::Int32 CICSBatchOrderDM::getPositionCountFromPositions()
{
	METHODNAME_DEF( CICSBatchOrderDM, getPositionCountFromPosition );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

	basar::db::aspect::AccessorPropertyTable_YIterator yitPos = getCurrentPositions().begin();
	basar::Int32 count = 0;

	for ( ; !yitPos.isEnd(); yitPos++){
		++count;
	}

	return count;
}

//-------------------------------------------------------------------------------------------------------------------//
basar::Int32 CICSBatchOrderDM::getPositionCountFromHead()
{
	METHODNAME_DEF( CICSBatchOrderDM, getPositionCountFromPosition );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

	return getCurrentHead().getInt32( properties::dkbazk::KBAZKPOSLINES );
}

//-------------------------------------------------------------------------------------------------------------------//
basar::db::aspect::AccessorPropertyTable_YIterator	CICSBatchOrderDM::getBatchOrderHeadSearchCriteria( const domMod::batchOrder::core::OffSetNo offSetNo, basar::Int16 /*branchno*/ )
{
	METHODNAME_DEF( CICSBatchOrderDM, getBatchOrderHeadSearchCriteria );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

	m_PreviousOffSetNo = offSetNo;
	basar::db::aspect::AccessorPropertyTable_YIterator  yitSearch = getOrderHeadSearchYit();

	yitSearch.setInt32(properties::dkbazk::RECORDOFFSET, m_PreviousOffSetNo);

	return yitSearch;
}

//-------------------------------------------------------------------------------------------------------------------//
basar::db::aspect::AccessorPropertyTable_YIterator CICSBatchOrderDM::getBatchOrderPosSearchCriteria ( const basar::db::aspect::AccessorPropertyTable_YIterator yitBatchOrderHead )
{
	METHODNAME_DEF( CICSBatchOrderDM, getBatchOrderPosSearchCriteria );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

	basar::db::aspect::AccessorPropertyTable_YIterator yitSearch = getOrderPosSearchYit();

	yitSearch.setInt32( properties::dkbazp::RECORDOFFSET, m_PreviousOffSetNo );
	yitSearch.setInt32( properties::dkbazp::KBAZPLFDANR, yitBatchOrderHead.getInt32( properties::dkbazk::KBAZKLFDANR ) );

	return yitSearch;
}

//-------------------------------------------------------------------------------------------------------------------//
void CICSBatchOrderDM::clearTables()
{
	METHODNAME_DEF( CICSBatchOrderDM, clearTables );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

	m_CICSBatchOrderPosDM->clearTable();
	m_CICSBatchOrderHeadDM->clearTable();
}

void CICSBatchOrderDM::setStatusTransfered( basar::db::aspect::AccessorPropertyTable_YIterator yitCicsHead )
{
	METHODNAME_DEF( CICSBatchOrderDM, setStatusTransfered );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

	m_CICSBatchOrderHeadDM->setTransfered( yitCicsHead );
	m_CICSBatchOrderHeadDM->save( yitCicsHead );
}

} // namespace preparation
} // namespace batchOrder
} // namespace domMod
