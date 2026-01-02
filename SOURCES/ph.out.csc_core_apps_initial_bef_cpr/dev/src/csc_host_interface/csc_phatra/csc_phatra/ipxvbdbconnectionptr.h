//--------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief		shared ptr for PXVBDBConnectionPtr
 *  \author		Steffen Heinlein
 *  \date		20.06.2012
 */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_PXVERBUND_IPXVBDBCONNECTIONPTR_H
#define GUARD_DOMMOD_PHARMOSTRANSACTION_PXVERBUND_IPXVBDBCONNECTIONPTR_H

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

class IPXVBDBConnection;
typedef boost::shared_ptr< IPXVBDBConnection > IPXVBDBConnectionPtr;    

}
}
}

#endif

