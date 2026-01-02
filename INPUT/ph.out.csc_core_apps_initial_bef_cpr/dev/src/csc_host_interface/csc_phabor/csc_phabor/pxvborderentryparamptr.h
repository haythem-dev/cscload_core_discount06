//--------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief		shared ptr for PXVBDBConnectionPtr
 *  \author		Steffen Heinlein
 *  \date		20.06.2012
 */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_PXVBDBCONNECTIONPTR_H
#define GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_PXVBDBCONNECTIONPTR_H

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
namespace processing
{	

class PXVBDBConnection;
typedef boost::shared_ptr<PXVBDBConnection> PXVBDBConnectionPtr;    

}
}
}

#endif

