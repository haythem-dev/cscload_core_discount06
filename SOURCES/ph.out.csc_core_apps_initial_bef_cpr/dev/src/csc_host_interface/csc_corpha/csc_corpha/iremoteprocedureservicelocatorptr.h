//--------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief		
 *  \author		Steffen Heinlein
 *  \date		15.10.2012
 */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_DOMMOD_CORPHA_IREMOTEPROCEDURESERVICELOCATORPTR_H
#define GUARD_DOMMOD_CORPHA_IREMOTEPROCEDURESERVICELOCATORPTR_H

#include <boost/shared_ptr.hpp>

namespace domMod
{
namespace corpha
{
	class IRemoteProcedureServiceLocator;
	typedef boost::shared_ptr< IRemoteProcedureServiceLocator > IRemoteProcedureServiceLocatorPtr;    
}
}

#endif // GUARD_DOMMOD_CORPHA_IREMOTEPROCEDURESERVICELOCATORPTR_H
