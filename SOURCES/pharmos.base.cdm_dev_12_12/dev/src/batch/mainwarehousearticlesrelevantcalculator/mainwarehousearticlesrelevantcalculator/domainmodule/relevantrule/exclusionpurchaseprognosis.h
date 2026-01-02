#ifndef GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_RELEVANTRULE_EXCLUSIONPURCHASEPROGNOSIS_H
#define GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_RELEVANTRULE_EXCLUSIONPURCHASEPROGNOSIS_H

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
    class ExclusionPurchasePrognosis : public IRelevantRule
    {
    public:
        ExclusionPurchasePrognosis( basar::Int32 days, basar::Int32 prognosisLimit );
        ~ExclusionPurchasePrognosis();

        // from IRelevantRule interface
        RuleDescription                                 getDescription() const;
        infrastructure::dataType::Trilean               isRelevant( infrastructure::dataProvider::IDataProviderPtr ) const;

    private:
        // forbidden
        ExclusionPurchasePrognosis();

    private:
        basar::Int32                                    m_Days;
        basar::Decimal                                  m_PrognosisLimit;
    };

} // end namespace relevantRule
} // end namespace domMod
} // end namespace mainwarehousearticlesrelevantcalculator

#endif // GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_RELEVANTRULE_EXCLUSIONPURCHASEPROGNOSIS_H
