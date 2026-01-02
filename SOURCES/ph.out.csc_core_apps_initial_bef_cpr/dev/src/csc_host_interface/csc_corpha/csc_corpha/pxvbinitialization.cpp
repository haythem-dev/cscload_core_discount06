//--------------------------------------------------------------------------------------------------//
/*! \brief 
 *  \author     Steffen Heinlein
 *  \date       18.09.2012
 *  \version    00.00.00.01
 */ //--------------------------------------------------------------------------------------------------//

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <icsc_logger.h>
#include <classinfo_macros.h>
#include "pxvbinitialization.h"
#include "pvhx04_includes.h"

//--------------------------------------------------------------------------------------------------//
// class definition section
//--------------------------------------------------------------------------------------------------//
namespace domMod
{
namespace corpha
{
namespace pxVerbund
{	

//--------------------------------------------------------------------------------------------------//
	PXVBInitialization::PXVBInitialization( pxOrderTransmitPtr xmit, pxOrderEntryParamPtr oeparam, libcsc_utils::ICSC_LoggerPtr logger )
	: m_pxOrderTransmit( xmit ), m_pxOrderEntryParam( oeparam ), m_Logger( logger )
	{
        METHODNAME_DEF( PXVBInitialization, PXVBInitialization );
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );
	}

//--------------------------------------------------------------------------------------------------//
	PXVBInitialization::~PXVBInitialization()
	{
        METHODNAME_DEF( PXVBInitialization, ~PXVBInitialization );
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );
	}

//--------------------------------------------------------------------------------------------------//
	bool PXVBInitialization::isInitialized() const
	{
        METHODNAME_DEF( PXVBOrderEntryParamChecker, isInitialized );
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );
		
		return (m_pxOrderTransmit->IsGoodState() && m_pxOrderEntryParam->IsGoodState());
	}

//--------------------------------------------------------------------------------------------------//

} // end namespace pxVerbund
} // end namespace corpha
} // end namespace domMod
