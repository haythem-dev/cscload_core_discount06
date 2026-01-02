//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  PXVBOrderEntryParamChecker
 *  \author Steffen Heinlein
 *  \date   10.07.2012
 */
//----------------------------------------------------------------------------//
#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_PXVERBUND_PXVBORDERENTRYPARAMCHECKER_H
#define GUARD_DOMMOD_PHARMOSTRANSACTION_PXVERBUND_PXVBORDERENTRYPARAMCHECKER_H

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
namespace batchOrder
{
namespace pxVerbund
{	

class PXVBOrderEntryParamChecker : public  IPXVBOrderEntryParamChecker
{				
    public:		
		PXVBOrderEntryParamChecker( pxOrderEntryParamPtr oeparam, libcsc_utils::ICSC_LoggerPtr csc_logger );
        ~PXVBOrderEntryParamChecker();             			
			
		virtual bool							checkNarcoticsTransfer() const;

    private:
		libcsc_utils::ICSC_LoggerPtr						m_CSC_Logger;
		pxOrderEntryParamPtr						m_pxOrderEntryParam;
};

} // end namespace pxVerbund
} // end namespace batchOrder
} // end namespace domMod

#endif 

