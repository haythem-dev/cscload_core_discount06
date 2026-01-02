//--------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief		
 *  \author		Steffen Heinlein
 *  \date		18.09.2012
 */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_DOMMOD_CORPHA_PXVERBUND_PXVBCOMPONENTMANAGERPTR_H
#define GUARD_DOMMOD_CORPHA_PXVERBUND_PXVBCOMPONENTMANAGERPTR_H

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

class PXVBComponentManager;
typedef boost::shared_ptr<PXVBComponentManager> PXVBComponentManagerPtr;    

}
}
}

#endif
