//--------------------------------------------------------------------------------------------------//
/*! \file 
 *  \brief      
 *  \author     Bischof Bjoern
 *  \date       24.06.2011
 *  \version    00.00.00.01 first version
 */ 
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_CORE_RECORDTYPEBASEPTR_H
#define GUARD_DOMMOD_PHARMOSTRANSACTION_CORE_RECORDTYPEBASEPTR_H

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
            class RecordTypeBase;
            typedef boost::shared_ptr< RecordTypeBase > RecordTypeBasePtr;
        }
    }
}

#endif

