//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file
 *  \brief  Typedefs for shared pointer to interace class IRecordTypeFactory
 *  \author Bischof Bjoern 
 *  \date   20.03.2012 */
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_CORE_RECORD_TYPE_FACTORY_PTR_H
#define GUARD_DOMMOD_PHARMOSTRANSACTION_CORE_RECORD_TYPE_FACTORY_PTR_H

#include <boost/shared_ptr.hpp>

namespace domMod
{
    namespace pharmosTransaction
    {
        namespace core
        {
            class RecordTypeFactory;
            typedef boost::shared_ptr< RecordTypeFactory > RecordTypeFactoryPtr;
        }
    }
}

#endif

