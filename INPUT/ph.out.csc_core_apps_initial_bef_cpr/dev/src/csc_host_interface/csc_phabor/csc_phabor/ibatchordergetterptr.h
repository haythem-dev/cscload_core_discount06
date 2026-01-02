//--------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief		shared ptr for IBatchOrderGetterPtr 
 *  \author		Steffen Heinlein
 *  \date		05.07.2012
 */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_UTIL_IBATCHORDER_GETTER_PTR_H
#define GUARD_UTIL_IBATCHORDER_GETTER_PTR_H

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

	class IBatchOrderGetter;
    typedef boost::shared_ptr<IBatchOrderGetter> IBatchOrderGetterPtr;    

}
}
} // namespace util

#endif // GUARD_UTIL_IBATCHORDER_GETTER_PTR_H
