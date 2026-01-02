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
#include "pxvbsession.h"
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
	PXVBSession::PXVBSession( pxOrderTransmitPtr xmit, libcsc_utils::ICSC_LoggerPtr logger )
	: m_pxOrderTransmit( xmit ), m_Logger( logger )
	{
        METHODNAME_DEF( PXVBSession, PXVBSession );
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );
	}

//--------------------------------------------------------------------------------------------------//
	PXVBSession::~PXVBSession()
	{
        METHODNAME_DEF( PXVBSession, ~PXVBSession );
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );
	}

//--------------------------------------------------------------------------------------------------//
	pxSession* PXVBSession::get()
	{
        METHODNAME_DEF( PXVBOrderEntryParamChecker, get );
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );
		
		return m_pxOrderTransmit->Session();
	}

//--------------------------------------------------------------------------------------------------//

} // end namespace pxVerbund
} // end namespace corpha
} // end namespace domMod
