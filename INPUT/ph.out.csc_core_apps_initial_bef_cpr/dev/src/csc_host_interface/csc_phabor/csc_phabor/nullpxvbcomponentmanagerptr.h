//--------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief		shared ptr for PXVBComponentManagerPtr
 *  \author		Steffen Heinlein
 *  \date		11.07.2012
 */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_PXVERBUND_NULLPXVBCOMPONENTMANAGERPTR_H
#define GUARD_DOMMOD_PHARMOSTRANSACTION_PXVERBUND_NULLPXVBCOMPONENTMANAGERPTR_H

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

class NullPXVBComponentManager;
typedef boost::shared_ptr< NullPXVBComponentManager > NullPXVBComponentManagerPtr;    

}
}
}

#endif

