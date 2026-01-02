//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file
 *  \brief
 *  \author Bischof Bjoern
 *  \date   12.06.2015 */
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef GUARD_IBTRELEVANTCALCULATOR_INFRASTRUCTURE_SETUP_IIBTRELEVANTCALCULATORLOGINGETTERCONSTPTR_H
#define GUARD_IBTRELEVANTCALCULATOR_INFRASTRUCTURE_SETUP_IIBTRELEVANTCALCULATORLOGINGETTERCONSTPTR_H

#include <boost/shared_ptr.hpp>

namespace ibtrelevantcalculator
{
    namespace infrastructure
    {
        namespace setup
        {
            class IIBTRELEVANTCALCULATORLoginGetter;
            typedef boost::shared_ptr< IIBTRELEVANTCALCULATORLoginGetter const> IIBTRELEVANTCALCULATORLoginGetterConstPtr;
        }
    }
}

#endif
