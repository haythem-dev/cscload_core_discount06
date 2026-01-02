//--------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief
 *  \author     Bischof Bjoern
 *  \date       28.07.2013
 *  \version    00.00.00.01 first version
 */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_EXPORTARTICLECALCULATOR_COMPONENTMANAGER_EXPORTARTICLECALCULATORINFRASTRUCTURECOMPMGRPTR_H
#define GUARD_EXPORTARTICLECALCULATOR_COMPONENTMANAGER_EXPORTARTICLECALCULATORINFRASTRUCTURECOMPMGRPTR_H

#include <boost/shared_ptr.hpp>

namespace exportarticlecalculator
{
    namespace componentManager
    {
        class InfrastructureCompMgr;
        typedef boost::shared_ptr< InfrastructureCompMgr > InfrastructureCompMgrPtr;
    }
}

#endif //GUARD_EXPORTARTICLECALCULATOR_COMPONENTMANAGER_EXPORTARTICLECALCULATORINFRASTRUCTURECOMPMGRPTR_H
