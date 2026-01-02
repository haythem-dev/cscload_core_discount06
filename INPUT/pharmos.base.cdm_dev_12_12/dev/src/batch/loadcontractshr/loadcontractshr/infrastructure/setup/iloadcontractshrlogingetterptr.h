//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file
 *  \brief
 *  \author Bischof Bjoern
 *  \date   12.06.2015 */
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef GUARD_LOADCONTRACTSHR_INFRASTRUCTURE_SETUP_ILOADCONTRACTSHRLOGINGETTERCONSTPTR_H
#define GUARD_LOADCONTRACTSHR_INFRASTRUCTURE_SETUP_ILOADCONTRACTSHRLOGINGETTERCONSTPTR_H

#include <boost/shared_ptr.hpp>

namespace loadcontractshr
{
    namespace infrastructure
    {
        namespace setup
        {
            class ILoadContractsHrLoginGetter;
            typedef boost::shared_ptr< ILoadContractsHrLoginGetter const> ILoadContractsHrLoginGetterConstPtr;
        }
    }
}

#endif
