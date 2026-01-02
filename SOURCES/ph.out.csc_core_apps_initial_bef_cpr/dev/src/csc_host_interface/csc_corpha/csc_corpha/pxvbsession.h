//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  
 *  \author		Steffen Heinlein
 *  \date		18.09.2012
 */
//----------------------------------------------------------------------------//
#ifndef GUARD_DOMMOD_CORPHA_PXVERBUND_PXVBSESSION_H
#define GUARD_DOMMOD_CORPHA_PXVERBUND_PXVBSESSION_H

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include <icsc_loggerptr.h>
#include "ipxvbsession.h"
#include "pxordertransmitptr.h"

//----------------------------------------------------------------------------//
// forward declaration section
//----------------------------------------------------------------------------//
class pxSession;

//----------------------------------------------------------------------------//
// class declaration setcion
//----------------------------------------------------------------------------//
namespace domMod
{
namespace corpha
{
namespace pxVerbund
{	

class PXVBSession : public IPXVBSession
{			
    public:		
        PXVBSession( pxOrderTransmitPtr, libcsc_utils::ICSC_LoggerPtr );
        ~PXVBSession();             			

		virtual pxSession*					get();

    private:        
		::pxOrderTransmitPtr				m_pxOrderTransmit;
		libcsc_utils::ICSC_LoggerPtr		m_Logger;
};

} // end namespace pxVerbund
} // end namespace corpha
} // end namespace domMod

#endif 
