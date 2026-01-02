//--------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief
 *  \author     Bischof Bjoern
 *  \date       09.07.2013
 *  \version    00.00.00.01 first version
 */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_LONGTERMLACKLOADER_COMPONENTMANAGER_LONGTERMLACKLOADERAPPLCOMPMGRPTR_H
#define GUARD_LONGTERMLACKLOADER_COMPONENTMANAGER_LONGTERMLACKLOADERAPPLCOMPMGRPTR_H

#include <boost/shared_ptr.hpp>

namespace longtermlackloader
{
    namespace componentManager
    {
        class ApplCompMgr;
        typedef boost::shared_ptr< ApplCompMgr > ApplCompMgrPtr;
    }
}

#endif //GUARD_LONGTERMLACKLOADER_COMPONENTMANAGER_LONGTERMLACKLOADERAPPLCOMPMGRPTR_H
