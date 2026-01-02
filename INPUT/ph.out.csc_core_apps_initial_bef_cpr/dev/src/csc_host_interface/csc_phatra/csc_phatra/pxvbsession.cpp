//--------------------------------------------------------------------------------------------------//
/*! \brief 
 *  \author     Steffen Heinlein
 *  \date       10.07.2012
 *  \version    00.00.00.01
 */ //--------------------------------------------------------------------------------------------------//

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//

#include "pxvbsession.h"

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
	PXVBSession::PXVBSession( pxOrderTransmitPtr xmit )
	: m_pxOrderTransmit( xmit )
	{
        //METHODNAME_DEF( PXVBSession, PXVBSession )
        //BLOG_TRACE_METHOD( m_Logger, fun );
	}

//--------------------------------------------------------------------------------------------------//
	PXVBSession::~PXVBSession()
	{
        //METHODNAME_DEF( PXVBSession, ~PXVBSession )
        //BLOG_TRACE_METHOD( m_Logger, fun );
	}

//--------------------------------------------------------------------------------------------------//
	pxSession* PXVBSession::get()
	{
        //METHODNAME_DEF( PXVBOrderEntryParamChecker, get )
        //BLOG_TRACE_METHOD( m_Logger, fun );
		
		return m_pxOrderTransmit->Session();
	}

//--------------------------------------------------------------------------------------------------//

} // end namespace pxVerbund
} // end namespace pharmosTransaction
} // end namespace domMod
