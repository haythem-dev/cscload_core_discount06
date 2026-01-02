//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  IRecordTypeTransformer
 *  \author Steffen Heinlein
 *  \date   04.07.2012
 */
//----------------------------------------------------------------------------//
#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_UTIL_IRECORDTYPETRANSFORMHER_H
#define GUARD_DOMMOD_PHARMOSTRANSACTION_UTIL_IRECORDTYPETRANSFORMHER_H


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
    class IRecordTypeTransformer
    {
        public:	
            virtual ~IRecordTypeTransformer(){};       

			virtual void							transform( const domMod::pharmosTransaction::core::TransactionRecordBasePtr source,
															   domMod::pharmosTransaction::core::TransactionRecordBasePtr target ) const = 0;

    };

}
}
}

#endif 

