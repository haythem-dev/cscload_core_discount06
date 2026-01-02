#ifndef GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_RELEVANTRULE_ADMISSIONPURCHASEPROGNOSIS_H
#define GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_RELEVANTRULE_ADMISSIONPURCHASEPROGNOSIS_H

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
    class AdmissionPurchasePrognosis : public IRelevantRule
    {
    public:
        AdmissionPurchasePrognosis( basar::Int32 days, basar::Int32 prognosisLimit );
        ~AdmissionPurchasePrognosis();

        // from IRelevantRule interface
        RuleDescription                                 getDescription() const;
        infrastructure::dataType::Trilean               isRelevant( infrastructure::dataProvider::IDataProviderPtr ) const;

    private:
        // forbidden
        AdmissionPurchasePrognosis();

    private:
        basar::Int32                                    m_Days;
        basar::Decimal                                  m_PrognosisLimit;
    };

} // end namespace relevantRule
} // end namespace domMod
} // end namespace mainwarehousearticlesrelevantcalculator

#endif // GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_RELEVANTRULE_ADMISSIONPURCHASEPROGNOSIS_H
