//--------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief		shared ptr
 *  \author		Steffen Heinlein
 *  \date		18.09.2012
 */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_DOMMOD_CORPHA_PXVERBUND_IPXVBSESSIONPTR_H
#define GUARD_DOMMOD_CORPHA_PXVERBUND_IPXVBSESSIONPTR_H

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

class IPXVBSession;
typedef boost::shared_ptr< IPXVBSession > IPXVBSessionPtr;    

}
}
}

#endif
