//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file
 *  \brief
 *  \author Bischof Bjoern
 *  \date   12.06.2015 */
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef GUARD_EXPORTARTICLECALCULATOR_INFRASTRUCTURE_SETUP_IEXPORTARTICLECALCULATORLOGINGETTERCONSTPTR_H
#define GUARD_EXPORTARTICLECALCULATOR_INFRASTRUCTURE_SETUP_IEXPORTARTICLECALCULATORLOGINGETTERCONSTPTR_H

#include <boost/shared_ptr.hpp>

namespace exportarticlecalculator
{
    namespace infrastructure
    {
        namespace setup
        {
            class IEXPORTARTICLECALCULATORLoginGetter;
            typedef boost::shared_ptr< IEXPORTARTICLECALCULATORLoginGetter const> IEXPORTARTICLECALCULATORLoginGetterConstPtr;
        }
    }
}

#endif
