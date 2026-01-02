//--------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief
 *  \author		Steffen Heinlein
 *  \date		12.11.2018
 */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_DOMMOD_CORPHA_RECORDTYPES_RECORDTYPIBTPICKINGDATAPTR_H
#define GUARD_DOMMOD_CORPHA_RECORDTYPES_RECORDTYPIBTPICKINGDATAPTR_H

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

	class RecordTypeIBTPickingData;
	typedef boost::shared_ptr< RecordTypeIBTPickingData > RecordTypeIBTPickingDataPtr;

} // namespace recordtypes
} // namespace corpha
} // namespace domMod

#endif // GUARD_DOMMOD_CORPHA_RECORDTYPES_RECORDTYPIBTPICKINGDATAPTR_H
