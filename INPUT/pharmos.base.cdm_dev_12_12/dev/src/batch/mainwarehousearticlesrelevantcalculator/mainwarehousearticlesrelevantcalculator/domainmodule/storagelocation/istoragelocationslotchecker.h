#ifndef GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_STORAGELOCATION_ISTORAGELOCATIONSLOTCHECKER_H
#define GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_STORAGELOCATION_ISTORAGELOCATIONSLOTCHECKER_H

#include <libbasar_definitions.h>

//-------------------------------------------------------------------------------------------------//
// interface definition section
//-------------------------------------------------------------------------------------------------//
namespace mainwarehousearticlesrelevantcalculator
{
namespace domMod
{
namespace storageLocation
{
    class IStorageLocationSlotChecker
    {
    public:
        virtual ~IStorageLocationSlotChecker() {}

        virtual void                                  findByBranchNo    ( basar::Int16 )                                      = 0;
        virtual bool                                  hasStorageLocation( const basar::VarString& storageLocationSlot ) const = 0;
        virtual basar::VarString                      getPseudoStorageLocation()                                        const = 0;
    };

} // end namespace storageLocation
} // end namespace domMod
} // end namespace mainwarehousearticlesrelevantcalculator

#endif // GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_STORAGELOCATION_ISTORAGELOCATIONSLOTCHECKER_H
