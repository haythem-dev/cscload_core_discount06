//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  
 *  \author Steffen Heinlein
 *  \date   10.07.2012
 */
//----------------------------------------------------------------------------//
#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_PXVERBUND_PXVBORDERTRANSMIT_H
#define GUARD_DOMMOD_PHARMOSTRANSACTION_PXVERBUND_PXVBORDERTRANSMIT_H

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include "ipxvbordertransmit.h"
#include "pxordertransmitptr.h"

//----------------------------------------------------------------------------//
// forward declaration section
//----------------------------------------------------------------------------//
class pxOrderTransmit;

//----------------------------------------------------------------------------//
// class declaration setcion
//----------------------------------------------------------------------------//
namespace domMod
{
namespace batchOrder
{
namespace pxVerbund
{	

class PXVBOrderTransmit : public IPXVBOrderTransmit
{			
    public:		
        PXVBOrderTransmit( pxOrderTransmitPtr );
        ~PXVBOrderTransmit();             			

		virtual pxOrderTransmitPtr get();

    private:        
		pxOrderTransmitPtr m_pxOrderTransmit;
};

} // end namespace pxVerbund
} // end namespace batchOrder
} // end namespace domMod

#endif 

