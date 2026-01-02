//--------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief		shared ptr for PXVBComponentManagerPtr
 *  \author		Steffen Heinlein
 *  \date		11.07.2012
 */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_PXVERBUND_PXVBCOMPONENTMANAGERPTR_H
#define GUARD_DOMMOD_PHARMOSTRANSACTION_PXVERBUND_PXVBCOMPONENTMANAGERPTR_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <boost/shared_ptr.hpp>

//--------------------------------------------------------------------------------------------------//
// forward declaration section
//--------------------------------------------------------------------------------------------------//

namespace domMod
{
namespace batchOrder
{
namespace pxVerbund
{	

class PXVBComponentManager;
typedef boost::shared_ptr<PXVBComponentManager> PXVBComponentManagerPtr;    

}
}
}

#endif

