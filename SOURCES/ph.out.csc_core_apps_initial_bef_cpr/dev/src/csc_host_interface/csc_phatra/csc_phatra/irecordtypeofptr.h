//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file
 *  \brief  
 *  \author Bischof Bjoern 
 *  \date   20.03.2012 */
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_CORE_IRECORDTYPEOFPTR_H
#define GUARD_DOMMOD_PHARMOSTRANSACTION_CORE_IRECORDTYPEOFPTR_H

#include <boost/shared_ptr.hpp>

namespace domMod
{
    namespace pharmosTransaction
    {
        namespace core
        {
            class IRecordTypeOf;
            typedef boost::shared_ptr< IRecordTypeOf > IRecordTypeOfPtr;
        }
    }
}

#endif

