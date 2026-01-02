//--------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief		
 *  \author		Steffen Heinlein
 *  \date		11.07.2012
 */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_UTIL_IPXVBSERVICELOCATOR_H
#define GUARD_DOMMOD_PHARMOSTRANSACTION_UTIL_IPXVBSERVICELOCATOR_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <boost/shared_ptr.hpp>

//--------------------------------------------------------------------------------------------------//
// forward declaration section
//--------------------------------------------------------------------------------------------------//

namespace domMod
{
namespace pharmosTransaction
{
namespace pxVerbund
{	

	class IPXVBServiceLocator;
	typedef boost::shared_ptr< IPXVBServiceLocator > IPXVBServiceLocatorPtr;    

}
}
}

#endif

