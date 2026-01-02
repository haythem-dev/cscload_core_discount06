#ifndef GUARD_DOMMOD_PHARMOSBATCHORDER_PROCESSING_BATCHORDERDMINITSTRUCT_H
#define GUARD_DOMMOD_PHARMOSBATCHORDER_PROCESSING_BATCHORDERDMINITSTRUCT_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <libbasar_definitions.h>
#include "batchorderheaddmptr.h"
#include "batchorderposdmptr.h"
#include "ibatchordergetterptr.h"

//--------------------------------------------------------------------------------------------------//
// class decl./ def. section
//--------------------------------------------------------------------------------------------------//
namespace domMod
{
namespace batchOrder
{
namespace processing
{
    struct BatchOrderDMInitStruct
    {
	public:
		domMod::batchOrder::processing::BatchOrderHeadDMPtr	getOrderHeadDMPtr()		 const	{return m_OrderHeadDMPtr;}
		domMod::batchOrder::processing::BatchOrderPosDMPtr	getOrderPosDMPtr()		 const 	{return m_OrderPosDMPtr;}
	    
        BatchOrderDMInitStruct( 
			domMod::batchOrder::processing::BatchOrderHeadDMPtr	orderHeadDMPtr,
			domMod::batchOrder::processing::BatchOrderPosDMPtr	orderPosDMPtr
			) 
		: m_OrderHeadDMPtr( orderHeadDMPtr ), 
		  m_OrderPosDMPtr( orderPosDMPtr )
	    {
	    }

	private:
		domMod::batchOrder::processing::BatchOrderHeadDMPtr	m_OrderHeadDMPtr;
		domMod::batchOrder::processing::BatchOrderPosDMPtr	m_OrderPosDMPtr;
    };

} // end namespace processing
} // end namespace batchOrder
} // end namespace domMod

#endif
