//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  
 *  \author Steffen Heinlein
 *  \date   10.07.2012
 */
//----------------------------------------------------------------------------//
#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_PXVERBUND_NULLPXVBORDERENTRYPARAMCHECKER_H
#define GUARD_DOMMOD_PHARMOSTRANSACTION_PXVERBUND_NULLPXVBORDERENTRYPARAMCHECKER_H

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
//#include <libbasarcmnutil.h>
#include "ipxvborderentryparamchecker.h"
//#include "pxorderentryparamptr.h"

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

class NullPXVBOrderEntryParamChecker : public  IPXVBOrderEntryParamChecker
{				
    public:		
        NullPXVBOrderEntryParamChecker();
        ~NullPXVBOrderEntryParamChecker();
			
		virtual bool checkNarcoticsTransfer() const;

    private:
};

} // end namespace pxVerbund
} // end namespace batchOrder
} // end namespace domMod

#endif 

