//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file
 *  \brief
 *  \author Bischof Bjoern
 *  \date   12.06.2015 */
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef GUARD_IBTORDERIMPORT_INFRASTRUCTURE_SETUP_IIBTORDERIMPORTLOGINGETTERCONSTPTR_H
#define GUARD_IBTORDERIMPORT_INFRASTRUCTURE_SETUP_IIBTORDERIMPORTLOGINGETTERCONSTPTR_H

#include <boost/shared_ptr.hpp>

namespace ibtorderimport
{
    namespace infrastructure
    {
        namespace setup
        {
            class IIBTORDERIMPORTLoginGetter;
            typedef boost::shared_ptr< IIBTORDERIMPORTLoginGetter const> IIBTORDERIMPORTLoginGetterConstPtr;
        }
    }
}

#endif
