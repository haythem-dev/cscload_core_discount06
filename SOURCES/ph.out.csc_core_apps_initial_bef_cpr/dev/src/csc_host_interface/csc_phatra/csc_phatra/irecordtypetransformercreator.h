//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  IRecordTypeTransformer
 *  \author Steffen Heinlein
 *  \date   04.07.2012
 */
//----------------------------------------------------------------------------//
#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_UTIL_IRECORDTYPETRANSFORMERCREATOR_H
#define GUARD_DOMMOD_PHARMOSTRANSACTION_UTIL_IRECORDTYPETRANSFORMERCREATOR_H


//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include "irecordtypeofptr.h"

//----------------------------------------------------------------------------//
// class declaration setcion
//----------------------------------------------------------------------------//
namespace domMod
{
namespace pharmosTransaction
{
namespace util
{

    class IRecordTypeTransformerCreator
    {
        public:	
			//IRecordTypeTransformerCreator();
            virtual ~IRecordTypeTransformerCreator(){};

			virtual IRecordTypeTransformerPtr createTransformer( const domMod::pharmosTransaction::core::IRecordTypeOfPtr ) const = 0;
    };

}
}
}

#endif 

