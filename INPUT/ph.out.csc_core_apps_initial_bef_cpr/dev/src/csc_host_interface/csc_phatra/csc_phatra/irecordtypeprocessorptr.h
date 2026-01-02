//--------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief		shared ptr
 *  \author		Bischof Bjoern
 *  \date		06.07.2012
 */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_UTIL_IRECORDTYPEPROCESSORPTR_H
#define GUARD_DOMMOD_PHARMOSTRANSACTION_UTIL_IRECORDTYPEPROCESSORPTR_H

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

	class IRecordTypeProcessor;
    typedef boost::shared_ptr< IRecordTypeProcessor > IRecordTypeProcessorPtr;

}
}
}

#endif

