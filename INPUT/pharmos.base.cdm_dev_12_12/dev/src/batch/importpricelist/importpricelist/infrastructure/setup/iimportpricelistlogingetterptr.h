//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file
 *  \brief
 *  \author Michael Helmich
 *  \date   25.08.2021 */
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef GUARD_IMPORTPRICELIST_INFRASTRUCTURE_SETUP_IIMPORTPRICELISTLOGINGETTERCONSTPTR_H
#define GUARD_IMPORTPRICELIST_INFRASTRUCTURE_SETUP_IIMPORTPRICELISTLOGINGETTERCONSTPTR_H

#include <boost/shared_ptr.hpp>

namespace importpricelist
{
    namespace infrastructure
    {
        namespace setup
        {
            class IIMPORTPRICELISTLoginGetter;
            typedef boost::shared_ptr< IIMPORTPRICELISTLoginGetter const> IIMPORTPRICELISTLoginGetterConstPtr;
        }
    }
}

#endif
