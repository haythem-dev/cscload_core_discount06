//--------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief		shared ptr for PXVBDBConnectionPtr
 *  \author		Steffen Heinlein
 *  \date		20.06.2012
 */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_PXVERBUND_PXVBDBCONNECTIONPTR_H
#define GUARD_DOMMOD_PHARMOSTRANSACTION_PXVERBUND_PXVBDBCONNECTIONPTR_H

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

class PXVBInitialization;
typedef boost::shared_ptr< PXVBInitialization > PXVBInitializationPtr;    

}
}
}

#endif

