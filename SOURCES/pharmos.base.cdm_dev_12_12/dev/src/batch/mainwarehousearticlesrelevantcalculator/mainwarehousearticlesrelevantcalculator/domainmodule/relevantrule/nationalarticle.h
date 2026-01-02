#ifndef GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_RELEVANTRULE_NATIONALARTICLE_H
#define GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_RELEVANTRULE_NATIONALARTICLE_H

#include "irelevantrule.h"
#include <libbasar_definitions.h>

//-------------------------------------------------------------------------------------------------//
// class definition section
//-------------------------------------------------------------------------------------------------//
namespace mainwarehousearticlesrelevantcalculator
{
namespace domMod
{
namespace relevantRule
{
    class NationalArticle : public IRelevantRule
    {
    public:
        NationalArticle( basar::Int32 nationalArticleMinimalCount );
        ~NationalArticle();

        // from IRelevantRule interface
        RuleDescription                                 getDescription() const;
        infrastructure::dataType::Trilean               isRelevant( infrastructure::dataProvider::IDataProviderPtr ) const;

    private:
        // forbidden
        NationalArticle();

    private:
        basar::Int32                                    m_NationalArticleMinimalCount;
    };

} // end namespace relevantRule
} // end namespace domMod
} // end namespace mainwarehousearticlesrelevantcalculator

#endif // GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_RELEVANTRULE_NATIONALARTICLE_H
