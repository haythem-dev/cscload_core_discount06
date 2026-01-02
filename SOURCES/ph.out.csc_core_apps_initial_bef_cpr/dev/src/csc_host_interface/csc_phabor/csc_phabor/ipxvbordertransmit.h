//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  
 *  \author Steffen Heinlein
 *  \date   10.07.2012
 */
//----------------------------------------------------------------------------//
#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_PXVERBUND_IPXVBORDERTRANSMIT_H
#define GUARD_DOMMOD_PHARMOSTRANSACTION_PXVERBUND_IPXVBORDERTRANSMIT_H

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
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
	
class IPXVBOrderTransmit
{			
    public:		
        virtual ~IPXVBOrderTransmit(){};     
		virtual pxOrderTransmitPtr get() = 0;
};

} // end namespace pxVerbund
} // end namespace batchOrder
} // end namespace domMod

#endif 

