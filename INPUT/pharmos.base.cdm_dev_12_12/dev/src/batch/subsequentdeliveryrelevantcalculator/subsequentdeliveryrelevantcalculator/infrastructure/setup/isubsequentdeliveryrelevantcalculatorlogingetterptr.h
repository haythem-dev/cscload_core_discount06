//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file
 *  \brief
 *  \author Michael Helmich
 *  \date   14.10.2022 */
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef GUARD_SUBSEQUENTDELIVERYRELEVANTCALCULATOR_INFRASTRUCTURE_SETUP_ILOGINGETTERCONSTPTR_H
#define GUARD_SUBSEQUENTDELIVERYRELEVANTCALCULATOR_INFRASTRUCTURE_SETUP_ILOGINGETTERCONSTPTR_H

#include <boost/shared_ptr.hpp>

namespace subsequentdeliveryrelevantcalculator
{
    namespace infrastructure
    {
        namespace setup
        {
            class ISUBSEQUENTDELIVERYRELEVANTCALCULATORLoginGetter;
            typedef boost::shared_ptr< ISUBSEQUENTDELIVERYRELEVANTCALCULATORLoginGetter const> ISUBSEQUENTDELIVERYRELEVANTCALCULATORLoginGetterConstPtr;
        }
    }
}

#endif
