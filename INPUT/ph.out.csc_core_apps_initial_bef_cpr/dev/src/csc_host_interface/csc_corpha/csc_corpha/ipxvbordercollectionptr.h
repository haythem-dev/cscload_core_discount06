//--------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief		
 *  \author		Steffen Heinlein
 *  \date		08.10.2012
 */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_DOMMOD_CORPHA_PXVERBUND_IPXVBORDERCOLLECTIONPTR_H
#define GUARD_DOMMOD_CORPHA_PXVERBUND_IPXVBORDERCOLLECTIONPTR_H

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

	class IPXVBOrderCollection;
	typedef boost::shared_ptr< IPXVBOrderCollection > IPXVBOrderCollectionPtr;    

}
}
}

#endif // GUARD_DOMMOD_CORPHA_PXVERBUND_IPXVBORDERCOLLECTIONPTR_H
