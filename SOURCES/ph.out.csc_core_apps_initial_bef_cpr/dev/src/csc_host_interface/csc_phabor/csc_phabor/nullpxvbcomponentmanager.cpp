//--------------------------------------------------------------------------------------------------//
/*! \brief 
 *  \author     Steffen Heinlein
 *  \date       10.07.2012
 *  \version    00.00.00.01
 */ //--------------------------------------------------------------------------------------------------//

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include "cmndm.h"

#include "nullpxvbcomponentmanager.h"

#include "nullpxvbinitialization.h"
#include "nullpxvborderentryparamchecker.h"
#include "nullpxvbsession.h"

//#include "nullpxvbdbconnectionptr.h"
//#include "nullpxvbdbconnection.h"
#include "nullpxvbordertransmit.h"

//--------------------------------------------------------------------------------------------------//
// class definition section
//--------------------------------------------------------------------------------------------------//
namespace domMod
{
namespace batchOrder
{
namespace pxVerbund
{	

//--------------------------------------------------------------------------------------------------//
	NullPXVBComponentManager::NullPXVBComponentManager()
	{
	}

//--------------------------------------------------------------------------------------------------//
	NullPXVBComponentManager::~NullPXVBComponentManager()
	{
    }
	
//--------------------------------------------------------------------------------------------------//
	IPXVBOrderEntryParamCheckerPtr NullPXVBComponentManager::getPXVBOrderEntryParamChecker()
	{
		return IPXVBOrderEntryParamCheckerPtr( new NullPXVBOrderEntryParamChecker() );
	}
	
	IPXVBInitializationPtr NullPXVBComponentManager::getPXVBInitialization()
	{
	    return IPXVBInitializationPtr( new NullPXVBInitialization() );
	}

	IPXVBSessionPtr NullPXVBComponentManager::getPXVBSession()
	{
		return IPXVBSessionPtr( new NullPXVBSession() );
	}

	IPXVBOrderTransmitPtr NullPXVBComponentManager::getPXVBOrderTransmit()
	{
        return IPXVBOrderTransmitPtr( new NullPXVBOrderTransmit() );
	}


} // end namespace pxVerbund
} // end namespace batchOrder
} // end namespace domMod
