//--------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief		shared ptr
 *  \author		Steffen Heinlein
 *  \date		06.07.2012
 */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_UTIL_ITRANSACTIONRECORDCREATORPTR_H
#define GUARD_DOMMOD_PHARMOSTRANSACTION_UTIL_ITRANSACTIONRECORDCREATORPTR_H

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

	class ITransactionRecordCreator;
    typedef boost::shared_ptr<ITransactionRecordCreator> ITransactionRecordCreatorPtr;    

}
}
}

#endif // GUARD_DOMMOD_PHARMOSTRANSACTION_UTIL_ITRANSACTIONRECORDCREATORPTR_H

