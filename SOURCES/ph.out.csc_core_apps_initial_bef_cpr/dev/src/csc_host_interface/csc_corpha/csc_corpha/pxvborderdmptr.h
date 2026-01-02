//--------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief		
 *  \author		Steffen Heinlein
 *  \date		07.09.2012
 */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_DOMMOD_CORPHA_PXVERBUND_PXVBORDERDMPTR_H
#define GUARD_DOMMOD_CORPHA_PXVERBUND_PXVBORDERDMPTR_H

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

	class PXVBOrderDM;
	typedef boost::shared_ptr< PXVBOrderDM > PXVBOrderDMPtr;    

} // namespace pxVerbund
} // namespace corpha
} // namespace domMod

#endif // GUARD_DOMMOD_CORPHA_PXVERBUND_PXVBORDERDMPTR_H
