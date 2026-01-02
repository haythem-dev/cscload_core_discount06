//--------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief		shared ptr 
 *  \author		Steffen Heinlein
 *  \date		06.07.2012
 */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_CORE_PHARMOSTRANSACTIONDMPTR_H
#define GUARD_DOMMOD_PHARMOSTRANSACTION_CORE_PHARMOSTRANSACTIONDMPTR_H

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
namespace core
{

	class PharmosTransactionDM;
    typedef boost::shared_ptr< PharmosTransactionDM > PharmosTransactionDMPtr;    

}
}
}

#endif // GUARD_DOMMOD_PHARMOSTRANSACTION_CORE_PHARMOSTRANSACTIONDMPTR_H

