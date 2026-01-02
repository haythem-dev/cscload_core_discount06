//--------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief		shared ptr
 *  \author		Bischof Bjoern
 *  \date		06.07.2012
 */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_UTIL_IRECORDTYPETRANSFORMERCREATORPTR_H
#define GUARD_DOMMOD_PHARMOSTRANSACTION_UTIL_IRECORDTYPETRANSFORMERCREATORPTR_H

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

	class IRecordTypeTransformerCreator;
    typedef boost::shared_ptr<IRecordTypeTransformerCreator> IRecordTypeTransformerCreatorPtr;

}
}
}

#endif

