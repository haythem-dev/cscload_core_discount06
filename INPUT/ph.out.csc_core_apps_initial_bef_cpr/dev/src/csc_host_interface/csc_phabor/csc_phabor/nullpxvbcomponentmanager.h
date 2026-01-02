//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  NullPXVBComponentManager
 *  \author Steffen Heinlein
 *  \date   09.07.2012
 */
//----------------------------------------------------------------------------//
#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_PXVERBUND_NULLPXVBCOMPONENTMANAGER_H
#define GUARD_DOMMOD_PHARMOSTRANSACTION_PXVERBUND_NULLPXVBCOMPONENTMANAGER_H

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include "ipxvbordertransmit.h"
#include "ipxvbordertransmitptr.h"

#include "ipxvbinitializationptr.h"
#include "ipxvborderentryparamcheckerptr.h"
#include "ipxvbsessionptr.h"
#include "nullpxvbordertransmitptr.h"

//----------------------------------------------------------------------------//
// class declaration setcion
//----------------------------------------------------------------------------//
namespace domMod
{
namespace batchOrder
{
namespace pxVerbund
{	

class NullPXVBComponentManager : public IPXVBOrderTransmit
{			
    public:		
        NullPXVBComponentManager();
        ~NullPXVBComponentManager();             		

		virtual IPXVBInitializationPtr				getPXVBInitialization();
		virtual IPXVBOrderEntryParamCheckerPtr		getPXVBOrderEntryParamChecker();
		virtual IPXVBSessionPtr					    getPXVBSession();
		virtual IPXVBOrderTransmitPtr				getPXVBOrderTransmit();

    private:
        NullPXVBComponentManager( const NullPXVBComponentManager& );
		NullPXVBComponentManager& operator= ( const NullPXVBComponentManager& );        		
};

} // end namespace pxVerbund
} // end namespace batchOrder
} // end namespace domMod

#endif 

