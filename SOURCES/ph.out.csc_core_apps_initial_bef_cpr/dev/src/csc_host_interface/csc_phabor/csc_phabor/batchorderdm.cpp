//-------------------------------------------------------------------------------------------------------------------//
/*! \file		
 *  \brief		domain module for handling batchorders on ifx side
 *  \author		Julian Machata
 *  \date		17.10.2012
 */
//-------------------------------------------------------------------------------------------------------------------//

#include "cmndm.h"
#include <icsc_logger.h>
#include <csc_logger.h>

#include "batchorderdm.h"
#include "batchorderdm_definitions.h"
#include "batchorderdmptr.h"
#include "batchorderheaddm.h"
#include "batchorderposdm.h"
#include "property_definitions.h"

namespace domMod 
{		
namespace batchOrder
{
namespace processing
{
//-------------------------------------------------------------------------------------------------------------------//
BatchOrderDM::BatchOrderDM( libcsc_utils::ICSC_LoggerPtr csc_logger
						   , domMod::batchOrder::processing::BatchOrderHeadDMPtr batchOrderHeadDM
						   , domMod::batchOrder::processing::BatchOrderPosDMPtr batchOrderPosDM )
: BatchOrderDMBase(csc_logger),
  m_CSC_Logger(csc_logger), 
  m_BatchOrderHeadDM( batchOrderHeadDM ), 
  m_BatchOrderPosDM( batchOrderPosDM )
{
	METHODNAME_DEF( BatchOrderDM, BatchOrderDM );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
}

//-------------------------------------------------------------------------------------------------------------------//
BatchOrderDM::~BatchOrderDM()
{		
	METHODNAME_DEF( BatchOrderDM, ~BatchOrderDM );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
}

//-------------------------------------------------------------------------------------------------------------------//
basar::db::aspect::AccessorPropertyTable_YIterator BatchOrderDM::getNextOrderHead()
{
	METHODNAME_DEF( BatchOrderDM, getNextOrderHead );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

	basar::db::aspect::AccessorPropertyTable_YIterator current = getCurrentHead();

	setCurrentHead( ++current );

	return getCurrentHead();
}

//-------------------------------------------------------------------------------------------------------------------//
basar::db::aspect::AccessorPropertyTable_YIterator	BatchOrderDM::getBatchOrderHeadSearchCriteria( const domMod::batchOrder::core::OffSetNo offSetNo, const basar::Int16 branchno )
{
	METHODNAME_DEF( BatchOrderDM, getBatchOrderHeadSearchCriteria );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

	basar::db::aspect::AccessorPropertyTable_YIterator  yitSearch = getOrderHeadSearchYit();
	
	yitSearch.setInt32(properties::pharmosbatchorderhead::VSEOFFSET, offSetNo);
	yitSearch.setInt16(properties::pharmosbatchorderhead::BRANCHNO, branchno);

	return yitSearch;
}

//-------------------------------------------------------------------------------------------------------------------//
basar::db::aspect::AccessorPropertyTable_YIterator BatchOrderDM::getBatchOrderPosSearchCriteria ( const basar::db::aspect::AccessorPropertyTable_YIterator yitBatchOrderHead )
{
	METHODNAME_DEF( BatchOrderDM, getBatchOrderPosSearchCriteria );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

	basar::db::aspect::AccessorPropertyTable_YIterator yitSearch = getOrderPosSearchYit();

	yitSearch.setInt32( properties::pharmosbatchorderpos::BATCHORDERNO, yitBatchOrderHead.getInt32( properties::pharmosbatchorderhead::BATCHORDERNO ) );
	yitSearch.setInt32( properties::pharmosbatchorderpos::VSEOFFSET, yitBatchOrderHead.getInt32( properties::pharmosbatchorderhead::VSEOFFSET ) );
	yitSearch.setInt16( properties::pharmosbatchorderpos::BRANCHNO, yitBatchOrderHead.getInt16( properties::pharmosbatchorderhead::BRANCHNO ) );
	yitSearch.setString( properties::pharmosbatchorderpos::PROCESSINGSTATE, domMod::batchOrder::processing::batchOrderDM::STATUS_OPEN );

	return yitSearch;
}

//-------------------------------------------------------------------------------------------------------------------//
void BatchOrderDM::setBatchOrderInProcess ( basar::db::aspect::AccessorPropertyTable_YIterator head )
{
	METHODNAME_DEF( BatchOrderDM, setBatchOrderInProcess );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

	m_BatchOrderHeadDM->setInProcess( head );
	m_BatchOrderHeadDM->save( head );
}

//-------------------------------------------------------------------------------------------------------------------//
void BatchOrderDM::setBatchOrderClosed ( basar::db::aspect::AccessorPropertyTable_YIterator head )
{
	METHODNAME_DEF( BatchOrderDM, setBatchOrderClosed );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

	m_BatchOrderHeadDM->setClosed( head );
	m_BatchOrderHeadDM->save( head );
}

//-------------------------------------------------------------------------------------------------------------------//
void BatchOrderDM::setBatchOrderPosInProcess ( basar::db::aspect::AccessorPropertyTable_YIterator pos  ) 
{
	METHODNAME_DEF( BatchOrderDM, setBatchOrderPosInProcess );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

	m_BatchOrderPosDM->setInProcess( pos );
	m_BatchOrderPosDM->save( pos );
}

//-------------------------------------------------------------------------------------------------------------------//
void BatchOrderDM::setBatchOrderPosClosed ( basar::db::aspect::AccessorPropertyTable_YIterator pos  ) 
{
	METHODNAME_DEF( BatchOrderDM, setBatchOrderPosClosed );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

	m_BatchOrderPosDM->setClosed( pos );
	m_BatchOrderPosDM->save( pos );
}

} // namespace processing
} // namespace batchOrder
} // namespace domMod
