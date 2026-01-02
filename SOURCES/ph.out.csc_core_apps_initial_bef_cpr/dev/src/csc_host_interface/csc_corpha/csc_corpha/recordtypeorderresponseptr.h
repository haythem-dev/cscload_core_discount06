//--------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief		
 *  \author		Steffen Heinlein
 *  \date		15.10.2012
 */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_DOMMOD_CORPHA_RECORDTYPES_RECORDTYPEORDERRESPONSEPTR_H
#define GUARD_DOMMOD_CORPHA_RECORDTYPES_RECORDTYPEORDERRESPONSEPTR_H

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
namespace recordtypes
{		

	class RecordTypeOrderResponse;
	typedef boost::shared_ptr< RecordTypeOrderResponse > RecordTypeOrderResponsePtr;    

} // namespace recordtypes
} // namespace corpha
} // namespace domMod

#endif // GUARD_DOMMOD_CORPHA_RECORDTYPES_RECORDTYPEORDERRESPONSEPTR_H
