#ifndef GUARD_DOMMOD_BATCHORDERDMBASEINITSTRUCT_H
#define GUARD_DOMMOD_BATCHORDERDMBASEINITSTRUCT_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <libbasar_definitions.h>
#include "searchdmbaseptr.h"

//--------------------------------------------------------------------------------------------------//
// class decl./ def. section
//--------------------------------------------------------------------------------------------------//
namespace domMod
{
namespace batchOrder
{
namespace core
{
    struct BatchOrderDMBaseInitStruct
    {
	public:
		domMod::batchOrder::core::SearchDMBasePtr	getOrderHeadDMPtr()		 const	{return m_OrderHeadDMPtr;}
		domMod::batchOrder::core::SearchDMBasePtr	getOrderPosDMPtr()		 const 	{return m_OrderPosDMPtr;}
		domMod::batchOrder::util::IBatchOrderGetterPtr	getBatchOrderGetterPtr() const	{return m_BatchOrderGetterPtr;} 
	    
        BatchOrderDMBaseInitStruct( 
			domMod::batchOrder::core::SearchDMBasePtr	orderHeadDMPtr,
			domMod::batchOrder::core::SearchDMBasePtr	orderPosDMPtr,
			domMod::batchOrder::util::IBatchOrderGetterPtr	batchOrderGetterPtr
			) 
		: m_OrderHeadDMPtr( orderHeadDMPtr ), 
		  m_OrderPosDMPtr( orderPosDMPtr ),
		  m_BatchOrderGetterPtr( batchOrderGetterPtr )
	    {
	    }

	private:
		domMod::batchOrder::core::SearchDMBasePtr	m_OrderHeadDMPtr;
		domMod::batchOrder::core::SearchDMBasePtr	m_OrderPosDMPtr;
		domMod::batchOrder::util::IBatchOrderGetterPtr	m_BatchOrderGetterPtr;
    };

} // end namespace core
} // end namespace batchOrder
} // end namespace domMod

#endif
