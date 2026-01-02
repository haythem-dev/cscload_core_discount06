#ifndef GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_STORAGELOCATION_ISTORAGELOCATIONSLOTCHECKERPTR_H
#define GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_STORAGELOCATION_ISTORAGELOCATIONSLOTCHECKERPTR_H

#include <boost/shared_ptr.hpp>

namespace mainwarehousearticlesrelevantcalculator
{
    namespace domMod
    {
        namespace storageLocation
        {
            class IStorageLocationSlotChecker;
            typedef boost::shared_ptr< IStorageLocationSlotChecker > IStorageLocationSlotCheckerPtr;
        }
    }
}

#endif // GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_STORAGELOCATION_ISTORAGELOCATIONSLOTCHECKERPTR_H
