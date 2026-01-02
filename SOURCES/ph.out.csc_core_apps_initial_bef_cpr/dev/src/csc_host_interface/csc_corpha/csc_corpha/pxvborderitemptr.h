//--------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief		
 *  \author		Steffen Heinlein
 *  \date		18.09.2012
 */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_DOMMOD_CORPHA_PXVERBUND_PXVBORDERITEMPTR_H
#define GUARD_DOMMOD_CORPHA_PXVERBUND_PXVBORDERITEMPTR_H

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

class PXVBOrderItem;
typedef boost::shared_ptr< PXVBOrderItem > PXVBOrderItemPtr;

}
}
}

#endif // GUARD_DOMMOD_CORPHA_PXVERBUND_PXVBORDERITEMPTR_H
