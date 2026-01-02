//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  
 *  \author		Steffen Heinlein
 *  \date		08.10.2012
 */
//----------------------------------------------------------------------------//

#ifndef GUARD_DOMMOD_CORPHA_PXVERBUND_IPXVBORDERCOLLECTION_H
#define GUARD_DOMMOD_CORPHA_PXVERBUND_IPXVBORDERCOLLECTION_H

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//

#include "pxvborderdmptr.h"
#include "pxvbordercollectiondm_definitions.h"

//----------------------------------------------------------------------------//
// class declaration setcion
//----------------------------------------------------------------------------//
namespace domMod
{
namespace corpha
{
namespace pxVerbund
{	

class IPXVBOrderCollection
{			
    public:		
        virtual ~IPXVBOrderCollection(){};

		virtual void				findOrders2BeTransferred( OrderSelectionMode ) = 0;
		virtual PXVBOrderDMPtr		getFirst() = 0;
		virtual PXVBOrderDMPtr		getNext() = 0;
		virtual bool				isEnd() = 0;
				
};

}
}
}

#endif // GUARD_DOMMOD_CORPHA_PXVERBUND_IPXVBORDERCOLLECTION_H
