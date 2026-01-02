	//--------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief		shared ptr for IBatchOrderGetterPtr 
 *  \date		05.07.2012
 */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_UTIL_IBATCHORDERSTATUSUPDATER_PTR_H
#define GUARD_UTIL_IBATCHORDERSTATUSUPDATER_PTR_H

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
namespace util
{
	class IBatchOrderStatusUpdater;
    typedef boost::shared_ptr<IBatchOrderStatusUpdater> IBatchOrderStatusUpdaterPtr;    
}
}
} // namespace util

#endif // GUARD_UTIL_IBATCHORDERSTATUSUPDATER_PTR_H
