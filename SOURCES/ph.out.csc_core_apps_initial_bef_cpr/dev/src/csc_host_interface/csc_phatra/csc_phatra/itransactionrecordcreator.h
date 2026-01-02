//-------------------------------------------------------------------------------------------------//
/*! \file itransactionrecordcreator.h
 *  \brief 
 *  \author Steffen Heinlein
 *  \date 06.07.2012
 */
//-------------------------------------------------------------------------------------------------//
#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_UTIL_ITRANSACTIONRECORDCREATOR_H
#define GUARD_DOMMOD_PHARMOSTRANSACTION_UTIL_ITRANSACTIONRECORDCREATOR_H
//----------------------------------------------------------------------------//
// includes section
//----------------------------------------------------------------------------//
#include "transactionrecordbaseptr.h"

//----------------------------------------------------------------------------//
// forward declaration section
//----------------------------------------------------------------------------//
namespace basar
{
    namespace db
    {
        namespace aspect
        {
            class AccessorPropertyTable_YIterator;
			
        }
    }
}
namespace domMod
{
	class AccessorInstanceRefWrapper;
}

//----------------------------------------------------------------------------//
// class declaration setcion
//----------------------------------------------------------------------------//
namespace domMod
{
namespace pharmosTransaction
{
namespace util
{
    class ITransactionRecordCreator
    {
        public:	
            virtual ~ITransactionRecordCreator(){};
			virtual domMod::pharmosTransaction::core::TransactionRecordBasePtr createTransactionRecord(basar::db::aspect::AccessorPropertyTable_YIterator yit, domMod::AccessorInstanceRefWrapper& acc) = 0;
    };

}
}
}

//----------------------------------------------------------------------------
#endif //GUARD_DOMMOD_PHARMOSTRANSACTION_UTIL_ITRANSACTIONRECORDCREATOR_H

