//--------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief		shared ptr
 *  \author		Steffen Heinlein
 *  \date		20.06.2012
 */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_PXVERBUND_PXVBSESSIONPTR_H
#define GUARD_DOMMOD_PHARMOSTRANSACTION_PXVERBUND_PXVBSESSIONPTR_H

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

class PXVBSession;
typedef boost::shared_ptr<PXVBSession> PXVBSessionPtr;    

}
}
}

#endif

