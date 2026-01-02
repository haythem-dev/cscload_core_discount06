//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  
 *  \author		Steffen Heinlein
 *  \date		18.09.2012
 */
//----------------------------------------------------------------------------//
#ifndef GUARD_DOMMOD_CORPHA_PXVERBUND_PXVBORDERENTRYPARAMCHECKER_H
#define GUARD_DOMMOD_CORPHA_PXVERBUND_PXVBORDERENTRYPARAMCHECKER_H

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
//#include <libbasarcmnutil.h>
#include "ipxvborderentryparamchecker.h"
#include "pxorderentryparamptr.h"
#include <icsc_loggerptr.h>
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

class PXVBOrderEntryParamChecker : public  IPXVBOrderEntryParamChecker
{				
    public:		
	PXVBOrderEntryParamChecker( pxOrderEntryParamPtr oeparam, libcsc_utils::ICSC_LoggerPtr csc_logger );
        ~PXVBOrderEntryParamChecker();             			
			
	bool							checkNarcoticsTransfer() const;

    private:
	libcsc_utils::ICSC_LoggerPtr				m_CSC_Logger;
	pxOrderEntryParamPtr						m_pxOrderEntryParam;
};

} // end namespace pxVerbund
} // end namespace corpha
} // end namespace domMod

#endif 

