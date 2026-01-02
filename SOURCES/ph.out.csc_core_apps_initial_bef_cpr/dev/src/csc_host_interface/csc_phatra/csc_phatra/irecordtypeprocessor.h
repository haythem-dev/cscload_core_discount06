//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  IRecordTypeProcessor
 *  \author Steffen Heinlein
 *  \date   04.07.2012
 */
//----------------------------------------------------------------------------//
#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_UTIL_IRECORDTYPEPROCESSOR_H
#define GUARD_DOMMOD_PHARMOSTRANSACTION_UTIL_IRECORDTYPEPROCESSOR_H


//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include "transactionrecordbaseptr.h"

//----------------------------------------------------------------------------//
// class declaration setcion
//----------------------------------------------------------------------------//

namespace domMod
{
namespace pharmosTransaction
{
namespace util
{
    class IRecordTypeProcessor
    {
        public:	
            virtual ~IRecordTypeProcessor(){};       
			
			virtual void						process( const core::TransactionRecordBasePtr record ) const = 0;			

    };

}
}
}

#endif 

