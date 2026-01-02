//--------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief		shared ptr for ITransferKeyGetterPtr 
 *  \author		Steffen Heinlein
 *  \date		05.07.2012
 */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_UTIL_ITRANSFERKEYGETTERPTR_H
#define GUARD_UTIL_ITRANSFERKEYGETTERPTR_H

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
namespace util
{

	class ITransferKeyGetter;
    typedef boost::shared_ptr<ITransferKeyGetter> ITransferKeyGetterPtr;    

}
}
} // namespace util

#endif // GUARD_UTIL_ITRANSFERKEYGETTERPTR_H

