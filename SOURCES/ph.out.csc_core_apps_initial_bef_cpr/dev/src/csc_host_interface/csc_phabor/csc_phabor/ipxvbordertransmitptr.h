//--------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief		shared ptr
 *  \author		Steffen Heinlein
 *  \date		20.06.2012
 */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_PXVERBUND_IPXVBORDERTRANSMITPTR_H
#define GUARD_DOMMOD_PHARMOSTRANSACTION_PXVERBUND_IPXVBORDERTRANSMITPTR_H

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

class IPXVBOrderTransmit;
typedef boost::shared_ptr< IPXVBOrderTransmit > IPXVBOrderTransmitPtr;    

}
}
}

#endif

