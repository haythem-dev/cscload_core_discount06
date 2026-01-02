//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  PXVBOrderEntryParamChecker
 *  \author Steffen Heinlein
 *  \date   10.07.2012
 */
//----------------------------------------------------------------------------//
#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_PXVERBUND_PXVBINITIALIZATION_H
#define GUARD_DOMMOD_PHARMOSTRANSACTION_PXVERBUND_PXVBINITIALIZATION_H

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include "ipxvbinitialization.h"
#include "pxordertransmitptr.h"
#include "pxorderentryparamptr.h"

//----------------------------------------------------------------------------//
// forward declaration section
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
// class declaration setcion
//----------------------------------------------------------------------------//
namespace domMod
{
namespace batchOrder
{
namespace pxVerbund
{	

class PXVBInitialization : public IPXVBInitialization
{			
    public:		
		PXVBInitialization(::pxOrderTransmitPtr, ::pxOrderEntryParamPtr);
        ~PXVBInitialization();             			

		virtual bool isInitialized() const;

    private:        
		::pxOrderTransmitPtr						m_pxOrderTransmit;
		::pxOrderEntryParamPtr						m_pxOrderEntryParam;
};

} // end namespace pxVerbund
} // end namespace batchOrder
} // end namespace domMod

#endif 

