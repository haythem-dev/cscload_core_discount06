//--------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief		
 *  \author		Steffen Heinlein
 *  \date		28.05.2014
 */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_DOMMOD_CORPHA_RECORDTYPES_RECORDTYPEREMARKPTR_H
#define GUARD_DOMMOD_CORPHA_RECORDTYPES_RECORDTYPEREMARKPTR_H

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

	class RecordTypeRemark;
	typedef boost::shared_ptr< RecordTypeRemark > RecordTypeRemarkPtr;    

} // namespace recordtypes
} // namespace corpha
} // namespace domMod

#endif // GUARD_DOMMOD_CORPHA_RECORDTYPES_RECORDTYPEREMARKPTR_H
