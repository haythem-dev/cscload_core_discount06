#ifndef GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_COMPONENTMANAGER_ISTORAGELOCATIONSLOTCHECKERGETTER_H
#define GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_COMPONENTMANAGER_ISTORAGELOCATIONSLOTCHECKERGETTER_H

#include "domainmodule/storagelocation/istoragelocationslotcheckerptr.h"

//-------------------------------------------------------------------------------------------------//
// interface definition section
//-------------------------------------------------------------------------------------------------//
namespace mainwarehousearticlesrelevantcalculator
{
namespace componentManager
{
    class IStorageLocationSlotCheckerGetter
    {
        public:
            virtual ~IStorageLocationSlotCheckerGetter() {};

            virtual domMod::storageLocation::IStorageLocationSlotCheckerPtr   getStorageLocationSlotChecker() = 0;
    };
} // end namespace componentManager
} // end namespace mainwarehousearticlesrelevantcalculator

#endif // GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_COMPONENTMANAGER_ISTORAGELOCATIONSLOTCHECKERGETTER_H
