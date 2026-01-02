//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file
 *  \brief
 *  \author Michael Helmich
 *  \date   25.08.2021 */
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef GUARD_IMPORTPRICELIST_COMPONENTMANAGER_IUSECASEGETTERPTR_H
#define GUARD_IMPORTPRICELIST_COMPONENTMANAGER_IUSECASEGETTERPTR_H

#include <boost/shared_ptr.hpp>

namespace importpricelist
{
    namespace componentManager
    {
        class IUseCaseGetter;
        typedef boost::shared_ptr< IUseCaseGetter > IUseCaseGetterPtr;
    }
}

#endif
