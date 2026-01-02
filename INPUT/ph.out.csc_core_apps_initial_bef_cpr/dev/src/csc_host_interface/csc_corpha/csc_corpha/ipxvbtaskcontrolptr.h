//--------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief		
 *  \author		Steffen Heinlein
 *  \date		18.09.2012
 */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_DOMMOD_CORPHA_PXVERBUND_IPXVBTASKCONTROLPTR_H
#define GUARD_DOMMOD_CORPHA_PXVERBUND_IPXVBTASKCONTROLPTR_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <boost/shared_ptr.hpp>

//--------------------------------------------------------------------------------------------------//
// forward declaration section
//--------------------------------------------------------------------------------------------------//

namespace domMod
{
namespace corpha
{
namespace pxVerbund
{	

	class IPXVBTaskControl;
	typedef boost::shared_ptr< IPXVBTaskControl > IPXVBTaskControlPtr;    

}
}
}

#endif // GUARD_DOMMOD_CORPHA_PXVERBUND_IPXVBTASKCONTROLPTR_H
