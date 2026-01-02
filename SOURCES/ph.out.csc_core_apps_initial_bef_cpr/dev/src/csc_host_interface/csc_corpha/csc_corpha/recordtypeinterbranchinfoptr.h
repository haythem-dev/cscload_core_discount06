//--------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief		
 *  \author		Steffen Heinlein
 *  \date		07.09.2012
 */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_DOMMOD_CORPHA_RECORDTYPES_RECORDTYPEINTERBRANCHINFOPTR_H
#define GUARD_DOMMOD_CORPHA_RECORDTYPES_RECORDTYPEINTERBRANCHINFOPTR_H

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

	class RecordTypeInterBranchInfo;
	typedef boost::shared_ptr< RecordTypeInterBranchInfo > RecordTypeInterBranchInfoPtr;    

} // namespace recordtypes
} // namespace corpha
} // namespace domMod

#endif // GUARD_DOMMOD_CORPHA_RECORDTYPES_RECORDTYPEINTERBRANCHINFOPTR_H
