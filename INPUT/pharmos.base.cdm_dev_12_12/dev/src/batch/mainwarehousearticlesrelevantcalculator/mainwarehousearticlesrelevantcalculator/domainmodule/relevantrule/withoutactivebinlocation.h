#ifndef GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_RELEVANTRULE_WITHOUTACTIVEBINLOCATION_H
#define GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_RELEVANTRULE_WITHOUTACTIVEBINLOCATION_H

#include "irelevantrule.h"

#include "domainmodule/storagelocation/istoragelocationslotcheckerptr.h"

#include <libbasarcmnutil_bstring.h>

//-------------------------------------------------------------------------------------------------//
// class definition section
//-------------------------------------------------------------------------------------------------//
namespace mainwarehousearticlesrelevantcalculator
{
namespace domMod
{
namespace relevantRule
{
    class WithoutActiveBinLocation : public IRelevantRule
    {
    public:
        WithoutActiveBinLocation( storageLocation::IStorageLocationSlotCheckerPtr );
        ~WithoutActiveBinLocation();

        // from IRelevantRule interface
        RuleDescription                                 getDescription() const;
        infrastructure::dataType::Trilean               isRelevant( infrastructure::dataProvider::IDataProviderPtr ) const;

    private:
        // forbidden
        WithoutActiveBinLocation();
        bool                                            hasStorageLocation( const basar::VarString& storageLocationSlot ) const;
        basar::VarString                                getPseudoStorageLocation() const;

    private:
        storageLocation::IStorageLocationSlotCheckerPtr m_StorageLocationSlotChecker;
    };

} // end namespace relevantRule
} // end namespace domMod
} // end namespace mainwarehousearticlesrelevantcalculator

#endif // GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_RELEVANTRULE_WITHOUTACTIVEBINLOCATION_H
