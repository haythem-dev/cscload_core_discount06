//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file
 *  \brief
 *  \author Bischof Bjoern
 *  \date   12.06.2015 */
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef GUARD_CSC_PHADEX_INFRASTRUCTURE_SETUP_ICSC_PHADEXLOGINGETTERCONSTPTR_H
#define GUARD_CSC_PHADEX_INFRASTRUCTURE_SETUP_ICSC_PHADEXLOGINGETTERCONSTPTR_H

#include <boost/shared_ptr.hpp>

namespace csc_phadex
{
    namespace infrastructure
    {
        namespace setup
        {
            class ICscPhadexLoginGetter;
            typedef boost::shared_ptr< ICscPhadexLoginGetter const> ICscPhadexLoginGetterConstPtr;
        }
    }
}

#endif
