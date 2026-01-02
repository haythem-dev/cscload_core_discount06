//-------------------------------------------------------------------------------------------------------------------//
/*! \file		
 *  \brief		container for iterating batchorders
 *  \author		Julian Machata
 *  \date		17.10.2012
 */
//-------------------------------------------------------------------------------------------------------------------//

#include <libbasarproperty.h>
#include <classinfo_macros.h>
#include <icsc_logger.h>

#include "batchordercollection.h"

namespace domMod 
{		
namespace batchOrder
{
namespace core
{
//-------------------------------------------------------------------------------------------------------------------//
BatchOrderCollection::BatchOrderCollection( domMod::batchOrder::util::IBatchOrderGetterPtr batchOrderGetter, libcsc_utils::ICSC_LoggerPtr csc_logger)
: m_CSC_Logger(csc_logger),
  m_BatchOrderGetterPtr(batchOrderGetter) 
{
	METHODNAME_DEF( BatchOrderCollection, BatchOrderCollection );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
}

//-------------------------------------------------------------------------------------------------------------------//
BatchOrderCollection::~BatchOrderCollection()
{		
	METHODNAME_DEF( BatchOrderCollection, ~BatchOrderCollection );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
}

//-------------------------------------------------------------------------------------------------------------------//
domMod::batchOrder::core::BatchOrderPtr BatchOrderCollection::getFirst()
{
	METHODNAME_DEF( BatchOrderCollection, getFirst );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

	m_CurrentBatchOrderHeadYit  = m_BatchOrderGetterPtr->getFirstOrderHead();
	
	return getNewBatchOrder ();
}

//-------------------------------------------------------------------------------------------------------------------//
domMod::batchOrder::core::BatchOrderPtr BatchOrderCollection::getNext()
{
	METHODNAME_DEF( BatchOrderCollection, getNext );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

	m_CurrentBatchOrderHeadYit = m_BatchOrderGetterPtr->getNextOrderHead();

	return getNewBatchOrder();
}

//-------------------------------------------------------------------------------------------------------------------//
domMod::batchOrder::core::BatchOrderPtr	BatchOrderCollection::getNewBatchOrder()
{
	METHODNAME_DEF( BatchOrderCollection, getNewBatchOrder );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

	domMod::batchOrder::core::BatchOrderPtr newOrder = domMod::batchOrder::core::BatchOrderPtr( new domMod::batchOrder::core::BatchOrder ( m_CurrentBatchOrderHeadYit, getPositions(), m_CSC_Logger ));
	m_CurrentBatchOrderPtr = newOrder;

	return m_CurrentBatchOrderPtr; 
}

//-------------------------------------------------------------------------------------------------------------------//
basar::db::aspect::AccessorPropertyTableRef	BatchOrderCollection::getPositions( )
{
	METHODNAME_DEF( BatchOrderCollection, getPositions );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

	return m_BatchOrderGetterPtr->getBatchOrderPositions( m_CurrentBatchOrderHeadYit );
}

} // namespace core
} // namespace batchOrder
} // namespace domMod
