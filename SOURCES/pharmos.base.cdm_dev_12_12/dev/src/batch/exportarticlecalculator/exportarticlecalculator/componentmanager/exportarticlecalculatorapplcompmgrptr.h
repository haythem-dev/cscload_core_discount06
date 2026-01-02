//--------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief
 *  \author     Bischof Bjoern
 *  \date       09.07.2013
 *  \version    00.00.00.01 first version
 */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_EXPORTARTICLECALCULATOR_COMPONENTMANAGER_EXPORTARTICLECALCULATORAPPLCOMPMGRPTR_H
#define GUARD_EXPORTARTICLECALCULATOR_COMPONENTMANAGER_EXPORTARTICLECALCULATORAPPLCOMPMGRPTR_H

#include <boost/shared_ptr.hpp>

namespace exportarticlecalculator
{
    namespace componentManager
    {
        class ApplCompMgr;
        typedef boost::shared_ptr< ApplCompMgr > ApplCompMgrPtr;
    }
}

#endif //GUARD_EXPORTARTICLECALCULATOR_COMPONENTMANAGER_EXPORTARTICLECALCULATORAPPLCOMPMGRPTR_H
