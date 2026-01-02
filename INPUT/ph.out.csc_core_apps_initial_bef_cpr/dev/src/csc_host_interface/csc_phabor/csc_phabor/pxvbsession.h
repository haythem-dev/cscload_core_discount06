//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  
 *  \author Steffen Heinlein
 *  \date   10.07.2012
 */
//----------------------------------------------------------------------------//
#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_PXVERBUND_PXVBSESSION_H
#define GUARD_DOMMOD_PHARMOSTRANSACTION_PXVERBUND_PXVBSESSION_H

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
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
namespace batchOrder
{
namespace pxVerbund
{	

class PXVBSession : public IPXVBSession
{			
    public:		
        PXVBSession( pxOrderTransmitPtr );
        ~PXVBSession();             			

		virtual pxSession* get();

    private:        
		::pxOrderTransmitPtr m_pxOrderTransmit;
};

} // end namespace pxVerbund
} // end namespace batchOrder
} // end namespace domMod

#endif 

