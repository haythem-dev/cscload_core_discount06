#ifndef GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_MAINWAREHOUSE_IMAINWAREHOUSEFINDERPTR_H
#define GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_MAINWAREHOUSE_IMAINWAREHOUSEFINDERPTR_H

#include <boost/shared_ptr.hpp>

namespace mainwarehousearticlesrelevantcalculator
{
    namespace domMod
    {
        namespace mainwarehouse
        {
            class IMainwarehouseFinder;
            typedef boost::shared_ptr< IMainwarehouseFinder > IMainwarehouseFinderPtr;
        }
    }
}

#endif // GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_MAINWAREHOUSE_IMAINWAREHOUSEFINDERPTR_H
