//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file
 *  \brief
 *  \author Bischof Bjoern
 *  \date   12.06.2015 */
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef GUARD_LONGTERMLACKLOADER_INFRASTRUCTURE_SETUP_ILONGTERMLACKLOADERLOGINGETTERPTR_H
#define GUARD_LONGTERMLACKLOADER_INFRASTRUCTURE_SETUP_ILONGTERMLACKLOADERLOGINGETTERPTR_H

#include <boost/shared_ptr.hpp>

namespace longtermlackloader
{
    namespace infrastructure
    {
        namespace setup
        {
            class ILongTermLackLoaderLoginGetter;
            typedef boost::shared_ptr< const ILongTermLackLoaderLoginGetter > IILongTermLackLoaderLoginGetterPtr;
        }
    }
}

#endif
