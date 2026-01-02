//--------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief
 *  \author     Michael Helmich
 *  \date       25.08.2021
 *  \version    00.00.00.01 first version
 */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_IMPORTPRICELIST_COMPONENTMANAGER_IMPORTPRICELISTAPPLCOMPMGRPTR_H
#define GUARD_IMPORTPRICELIST_COMPONENTMANAGER_IMPORTPRICELISTAPPLCOMPMGRPTR_H

#include <boost/shared_ptr.hpp>

namespace importpricelist
{
    namespace componentManager
    {
        class ApplCompMgr;
        typedef boost::shared_ptr< ApplCompMgr > ApplCompMgrPtr;
    }
}

#endif //GUARD_IMPORTPRICELIST_COMPONENTMANAGER_IMPORTPRICELISTAPPLCOMPMGRPTR_H
