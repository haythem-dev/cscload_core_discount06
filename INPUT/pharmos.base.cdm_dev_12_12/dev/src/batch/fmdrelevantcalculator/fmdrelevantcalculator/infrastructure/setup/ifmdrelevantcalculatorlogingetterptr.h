//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file
 *  \brief
 *  \author Bischof Bjoern
 *  \date   12.06.2015 */
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef GUARD_FMDRELEVANTCALCULATOR_INFRASTRUCTURE_SETUP_IFMDRELEVANTCALCULATORLOGINGETTERCONSTPTR_H
#define GUARD_FMDRELEVANTCALCULATOR_INFRASTRUCTURE_SETUP_IFMDRELEVANTCALCULATORLOGINGETTERCONSTPTR_H

#include <boost/shared_ptr.hpp>

namespace fmdrelevantcalculator
{
    namespace infrastructure
    {
        namespace setup
        {
            class IFMDRELEVANTCALCULATORLoginGetter;
            typedef boost::shared_ptr< IFMDRELEVANTCALCULATORLoginGetter const> IFMDRELEVANTCALCULATORLoginGetterConstPtr;
        }
    }
}

#endif
