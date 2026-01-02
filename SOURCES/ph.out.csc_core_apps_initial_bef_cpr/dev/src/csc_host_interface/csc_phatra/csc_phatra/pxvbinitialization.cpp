//--------------------------------------------------------------------------------------------------//
/*! \brief 
 *  \author     Steffen Heinlein
 *  \date       10.07.2012
 *  \version    00.00.00.01
 */ //--------------------------------------------------------------------------------------------------//

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include "pxvbinitialization.h"

#include "pvhx01_includes.h"

//--------------------------------------------------------------------------------------------------//
// class definition section
//--------------------------------------------------------------------------------------------------//
namespace domMod
{
namespace pharmosTransaction
{
namespace pxVerbund
{	

//--------------------------------------------------------------------------------------------------//
	PXVBInitialization::PXVBInitialization( pxOrderTransmitPtr xmit, pxOrderEntryParamPtr oeparam )
	: m_pxOrderTransmit( xmit ), m_pxOrderEntryParam( oeparam )
	{
        //METHODNAME_DEF( PXVBInitialization, PXVBInitialization )
        //BLOG_TRACE_METHOD( m_Logger, fun );
	}

//--------------------------------------------------------------------------------------------------//
	PXVBInitialization::~PXVBInitialization()
	{
        //METHODNAME_DEF( PXVBInitialization, ~PXVBInitialization )
        //BLOG_TRACE_METHOD( m_Logger, fun );
	}

//--------------------------------------------------------------------------------------------------//
	bool PXVBInitialization::isInitialized() const
	{
        //METHODNAME_DEF( PXVBOrderEntryParamChecker, isInitialized )
        //BLOG_TRACE_METHOD( m_Logger, fun );
		
		return (m_pxOrderTransmit->IsGoodState() && m_pxOrderEntryParam->IsGoodState());
	}

//--------------------------------------------------------------------------------------------------//

} // end namespace pxVerbund
} // end namespace pharmosTransaction
} // end namespace domMod
