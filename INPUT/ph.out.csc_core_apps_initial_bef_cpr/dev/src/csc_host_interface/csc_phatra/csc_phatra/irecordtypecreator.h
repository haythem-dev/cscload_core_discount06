//-------------------------------------------------------------------------------------------------//
/*! \file 
 *  \brief 
 *  \author Steffen Heinlein
 *  \date 06.07.2012
 */
//-------------------------------------------------------------------------------------------------//
#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_UTIL_IRECORDTYPECREATOR_H
#define GUARD_DOMMOD_PHARMOSTRANSACTION_UTIL_IRECORDTYPECREATOR_H
//----------------------------------------------------------------------------//
// includes section
//----------------------------------------------------------------------------//
#include "transactionrecordbaseptr.h"
#include "irecordtypeprocessorptr.h"

//----------------------------------------------------------------------------//
// forward declaration section
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
// class declaration setcion
//----------------------------------------------------------------------------//
namespace domMod
{
namespace pharmosTransaction
{
namespace util
{
    class IRecordTypeCreator
    {
        public:	
            virtual ~IRecordTypeCreator(){};
			virtual util::IRecordTypeProcessorPtr					createRecordType( const core::TransactionRecordBasePtr ) const = 0;
    };

}
}
}

#endif 

