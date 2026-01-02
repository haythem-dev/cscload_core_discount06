//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  NullPXVBOrderTransmit
 *  \author Steffen Heinlein
 *  \date   09.07.2012
 */
//----------------------------------------------------------------------------//
#ifndef GUARD_DOMMOD_BATCHORDER_PXVERBUND_NULLPXVBORDERTRANSMIT_H
#define GUARD_DOMMOD_BATCHORDER_PXVERBUND_NULLPXVBORDERTRANSMIT_H

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include "ipxvbordertransmit.h"

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

class NullPXVBOrderTransmit : public IPXVBOrderTransmit
{			
    public:		
        NullPXVBOrderTransmit();
        ~NullPXVBOrderTransmit();             		

		virtual pxOrderTransmitPtr get();

    private:
        NullPXVBOrderTransmit( const NullPXVBOrderTransmit& );
		NullPXVBOrderTransmit& operator= ( const NullPXVBOrderTransmit& );        		
};

} // end namespace pxVerbund
} // end namespace batchOrder
} // end namespace domMod

#endif 

