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

#include "batchorderdmbase.h"
#include "batchorderdmbaseptr.h"
#include "property_definitions.h"

namespace domMod 
{		
namespace batchOrder
{
namespace core
{
//-------------------------------------------------------------------------------------------------------------------//
BatchOrderDMBase::BatchOrderDMBase( libcsc_utils::ICSC_LoggerPtr csc_logger )
: m_CSC_Logger(csc_logger)
{
	METHODNAME_DEF( BatchOrderDMBase, BatchOrderDMBase );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
}

//-------------------------------------------------------------------------------------------------------------------//
BatchOrderDMBase::~BatchOrderDMBase()
{		
	METHODNAME_DEF( BatchOrderDMBase, ~BatchOrderDMBase );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
}

//-------------------------------------------------------------------------------------------------------------------//
void BatchOrderDMBase::doInit( const BatchOrderDMBaseInitStruct initStruct )
{
	METHODNAME_DEF( BatchOrderDMBase, doInit );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

	m_BatchOrderGetterPtr = initStruct.getBatchOrderGetterPtr();
	m_OrderHeadDMPtr = initStruct.getOrderHeadDMPtr();
	m_OrderPosDMPtr = initStruct.getOrderPosDMPtr();
}

//-------------------------------------------------------------------------------------------------------------------//
void BatchOrderDMBase::doShutdown()
{
	METHODNAME_DEF( BatchOrderDMBase, doShutdown );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
}

//-------------------------------------------------------------------------------------------------------------------//
basar::db::aspect::AccessorPropertyTable_YIterator	BatchOrderDMBase::getCurrentHead()
{
	METHODNAME_DEF( BatchOrderDMBase, getCurrentHead );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

	return m_CurrentBatchOrderHeadYit;
}

//-------------------------------------------------------------------------------------------------------------------//
void	BatchOrderDMBase::setCurrentHead( basar::db::aspect::AccessorPropertyTable_YIterator next )
{
	METHODNAME_DEF( BatchOrderDMBase, setCurrentHead );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

	m_CurrentBatchOrderHeadYit = next;
}

//-------------------------------------------------------------------------------------------------------------------//
basar::db::aspect::AccessorPropertyTableRef	BatchOrderDMBase::getCurrentPositions()
{
	METHODNAME_DEF( BatchOrderDMBase, getCurrentPositions );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

	return m_OrderPosDMPtr->getPropTab();
}

//-------------------------------------------------------------------------------------------------------------------//
domMod::batchOrder::core::BatchOrderCollectionPtr BatchOrderDMBase::findOpenOrders( const domMod::batchOrder::core::OffSetNo offSetNo, const basar::Int16 branchno )
{
	METHODNAME_DEF( BatchOrderDMBase, findOpenOrders );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

	m_OrderHeadDMPtr->findOpen( getBatchOrderHeadSearchCriteria(offSetNo, branchno) );
	
	return getNewBatchOrderCollection(getBatchOrderGetter());
}

//-------------------------------------------------------------------------------------------------------------------//
basar::db::aspect::AccessorPropertyTableRef	BatchOrderDMBase::getBatchOrderHeads()
{
	METHODNAME_DEF( BatchOrderDMBase, getBatchOrderHeads );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

	return m_OrderHeadDMPtr->getPropTab();
}

//-------------------------------------------------------------------------------------------------------------------//
basar::db::aspect::AccessorPropertyTableRef	BatchOrderDMBase::getBatchOrderPositions( basar::db::aspect::AccessorPropertyTable_YIterator yitBatchOrderHead )
{
	METHODNAME_DEF( BatchOrderDMBase, getBatchOrderPositions );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

	if ( yitBatchOrderHead.isEnd() )
	{
		m_OrderPosDMPtr->getPropTab().clear();
		return m_OrderPosDMPtr->getPropTab();
	}

	m_OrderPosDMPtr->findOpen( getBatchOrderPosSearchCriteria(yitBatchOrderHead) );

	return m_OrderPosDMPtr->getPropTab();
}

//-------------------------------------------------------------------------------------------------------------------//
domMod::batchOrder::core::BatchOrderCollectionPtr	BatchOrderDMBase::getNewBatchOrderCollection( domMod::batchOrder::util::IBatchOrderGetterPtr batchOrderGetter)
{
	METHODNAME_DEF( BatchOrderDMBase, getNewBatchOrderCollection );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

	return domMod::batchOrder::core::BatchOrderCollectionPtr ( new domMod::batchOrder::core::BatchOrderCollection( batchOrderGetter, m_CSC_Logger));
}

//-------------------------------------------------------------------------------------------------------------------//
domMod::batchOrder::util::IBatchOrderGetterPtr	BatchOrderDMBase::getBatchOrderGetter()
{
	METHODNAME_DEF( BatchOrderDMBase, getBatchOrderGetter );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

	return m_BatchOrderGetterPtr;
}

//-------------------------------------------------------------------------------------------------------------------//
basar::db::aspect::AccessorPropertyTable_YIterator BatchOrderDMBase::getFirstOrderHead()
{
	METHODNAME_DEF( BatchOrderDMBase, getFirstOrderHead );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

	m_CurrentBatchOrderHeadYit  = getBatchOrderHeads().begin();
	
	return m_CurrentBatchOrderHeadYit;
}

//-------------------------------------------------------------------------------------------------------------------//
domMod::batchOrder::core::BatchOrderPtr BatchOrderDMBase::getEmptyBatchOrder()
{
	METHODNAME_DEF( BatchOrderDMBase, getEmptyBatchOrder );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

	basar::db::aspect::AccessorPropertyTableRef posPropTab  = m_OrderPosDMPtr->getPropTab();
	basar::db::aspect::AccessorPropertyTableRef headPropTab = m_OrderHeadDMPtr->getPropTab();
	
	posPropTab.clear();
	headPropTab.clear();

	basar::db::aspect::AccessorPropertyTable_YIterator yitNewHead = headPropTab.insert(basar::FOR_INSERT);

	return domMod::batchOrder::core::BatchOrderPtr ( new domMod::batchOrder::core::BatchOrder( yitNewHead, posPropTab, m_CSC_Logger ) );
}

//-------------------------------------------------------------------------------------------------------------------//
void BatchOrderDMBase::saveBatchOrder( domMod::batchOrder::core::BatchOrderPtr batchOrder )
{
	METHODNAME_DEF( BatchOrderDMBase, saveBatchOrder );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

	basar::db::aspect::AccessorPropertyTable_YIterator yitHead = batchOrder->getOrderHead();
	basar::db::aspect::AccessorPropertyTable_YIterator yitPos = batchOrder->getOrderPositions().begin();

	// wrap head and pos save in try /catch block to prevent duplicate key exceptions
	// might happen in case of recovery after crash -> try to write remaining positions.
	// no log output necessary, already done in base DM.
	try
	{
		m_OrderHeadDMPtr->save( yitHead );
	}
	catch (...)
	{
	}

	for ( ; !yitPos.isEnd(); ++yitPos )
	{
		try
		{
			m_OrderPosDMPtr->save (yitPos);
		}
		catch (...)
		{
		}
	}
}

//-------------------------------------------------------------------------------------------------------------------//
basar::Int32 BatchOrderDMBase::getLastKey(const basar::Int16 branchno)
{
	METHODNAME_DEF( BatchOrderDMBase, getLastKey );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

	basar::Int32 lastHeadKey = m_OrderHeadDMPtr->findLastKey( branchno );

	return lastHeadKey;
}

//-------------------------------------------------------------------------------------------------------------------//
basar::db::aspect::AccessorPropertyTable_YIterator	BatchOrderDMBase::getOrderHeadSearchYit()
{
	METHODNAME_DEF( BatchOrderDMBase, getOrderHeadSearchYit );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

	return m_OrderHeadDMPtr->getSearchYit();
}

//-------------------------------------------------------------------------------------------------------------------//
basar::db::aspect::AccessorPropertyTable_YIterator	BatchOrderDMBase::getOrderPosSearchYit()
{
	METHODNAME_DEF( BatchOrderDMBase, getOrderPosSearchYit );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

	return m_OrderPosDMPtr->getSearchYit();
}

} // namespace core
} // namespace batchOrder
} // namespace domMod
