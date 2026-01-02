//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  
 *  \author		Steffen Heinlein
 *  \date		18.09.2012
 */
//----------------------------------------------------------------------------//
#ifndef GUARD_DOMMOD_CORPHA_PXVERBUND_PXVBINITIALIZATION_H
#define GUARD_DOMMOD_CORPHA_PXVERBUND_PXVBINITIALIZATION_H

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include <icsc_loggerptr.h>
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
namespace corpha
{
namespace pxVerbund
{	

class PXVBInitialization : public IPXVBInitialization
{			
    public:		
		PXVBInitialization(::pxOrderTransmitPtr, ::pxOrderEntryParamPtr, libcsc_utils::ICSC_LoggerPtr);
        ~PXVBInitialization();             			

		virtual bool isInitialized() const;

    private:        
		::pxOrderTransmitPtr						m_pxOrderTransmit;
		::pxOrderEntryParamPtr						m_pxOrderEntryParam;
		libcsc_utils::ICSC_LoggerPtr				m_Logger;
};

} // end namespace pxVerbund
} // end namespace corpha
} // end namespace domMod

#endif 
