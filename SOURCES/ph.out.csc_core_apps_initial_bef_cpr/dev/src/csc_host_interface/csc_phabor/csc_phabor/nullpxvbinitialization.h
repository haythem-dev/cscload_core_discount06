//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  PXVBOrderEntryParamChecker
 *  \author Steffen Heinlein
 *  \date   10.07.2012
 */
//----------------------------------------------------------------------------//
#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_PXVERBUND_NULLPXVBINITIALIZATION_H
#define GUARD_DOMMOD_PHARMOSTRANSACTION_PXVERBUND_NULLPXVBINITIALIZATION_H

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include "ipxvbinitialization.h"


//----------------------------------------------------------------------------//
// class declaration setcion
//----------------------------------------------------------------------------//
namespace domMod
{
namespace batchOrder
{
namespace pxVerbund
{	

class NullPXVBInitialization : public IPXVBInitialization
{			
    public:		
		NullPXVBInitialization();
        ~NullPXVBInitialization();             			

		virtual bool isInitialized() const;
};

} // end namespace pxVerbund
} // end namespace batchOrder
} // end namespace domMod

#endif 

