//--------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief		shared ptr for PXVBOrderTransmitPtr
 *  \author		Steffen Heinlein
 *  \date		11.07.2012
 */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_DOMMOD_BATCHORDER_PXVERBUND_NULLPXVBORDERTRANSMITPTR_H
#define GUARD_DOMMOD_BATCHORDER_PXVERBUND_NULLPXVBORDERTRANSMITPTR_H

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

class NullPXVBOrderTransmit;
typedef boost::shared_ptr< NullPXVBOrderTransmit > NullPXVBOrderTransmitPtr;    

}
}
}

#endif

