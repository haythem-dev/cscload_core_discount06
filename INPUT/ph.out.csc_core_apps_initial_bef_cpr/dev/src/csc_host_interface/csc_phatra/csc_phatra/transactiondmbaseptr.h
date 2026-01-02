//--------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief		shared ptr 
 *  \author		Steffen Heinlein
 *  \date		27.06.2012
 */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_CORE_TRANSACTIONDMBASEPTR_H
#define GUARD_DOMMOD_PHARMOSTRANSACTION_CORE_TRANSACTIONDMBASEPTR_H

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
	class TransactionDMBase;
    typedef boost::shared_ptr<TransactionDMBase> TransactionDMBasePtr;    

}
}
}

#endif // GUARD_DOMMOD_PHARMOSTRANSACTION_CORE_TRANSACTIONDMBASEPTR_H

