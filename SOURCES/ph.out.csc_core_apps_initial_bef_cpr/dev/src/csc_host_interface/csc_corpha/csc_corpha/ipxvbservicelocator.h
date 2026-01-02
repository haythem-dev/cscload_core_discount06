//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  
 *  \author		Steffen Heinlein
 *  \date		18.09.2012
 */
//----------------------------------------------------------------------------//

#ifndef GUARD_DOMMOD_CORPHA_PXVERBUND_IPXVBSERVICELOCATOR_H
#define GUARD_DOMMOD_CORPHA_PXVERBUND_IPXVBSERVICELOCATOR_H

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include "ipxvbsessionptr.h"
#include "ipxvbdbconnectionptr.h"
#include "ipxvbinitializationptr.h"
#include "ipxvborderentryparamcheckerptr.h"

//----------------------------------------------------------------------------//
// class declaration setcion
//----------------------------------------------------------------------------//
namespace domMod
{
namespace corpha
{
namespace pxVerbund
{	

class IPXVBServiceLocator
{			
    public:		
        virtual ~IPXVBServiceLocator(){};
		
		virtual IPXVBInitializationPtr					getPXVBInitialization() = 0;
		virtual IPXVBOrderEntryParamCheckerPtr			getPXVBOrderEntryParamChecker() = 0;
		virtual IPXVBSessionPtr							getPXVBSession() = 0;
		virtual IPXVBDBConnectionPtr					getPXVBDBConnection() = 0;
};

}
}
}

#endif 
