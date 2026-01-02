#ifndef GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_RELEVANTRULE_ADMISSIONCONSIDERGROUPS_H
#define GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_RELEVANTRULE_ADMISSIONCONSIDERGROUPS_H

#include "irelevantrule.h"

#include <libbasar_definitions.h>
#include <libbasarcmnutil_decimal.h>

//-------------------------------------------------------------------------------------------------//
// class definition section
//-------------------------------------------------------------------------------------------------//
namespace mainwarehousearticlesrelevantcalculator
{
namespace domMod
{
namespace relevantRule
{
    class AdmissionConsiderGroups : public IRelevantRule
    {
    public:
        AdmissionConsiderGroups(basar::Int16 flags);
        ~AdmissionConsiderGroups();

        // from IRelevantRule interface
        RuleDescription                                 getDescription() const;
        infrastructure::dataType::Trilean               isRelevant( infrastructure::dataProvider::IDataProviderPtr ) const;
    private:
        // forbidden
        AdmissionConsiderGroups();

    private:
        basar::Int16                                    m_Flags;

    };

} // end namespace relevantRule
} // end namespace domMod
} // end namespace mainwarehousearticlesrelevantcalculator

#endif // GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_RELEVANTRULE_ADMISSIONCONSIDERGROUPS_H
