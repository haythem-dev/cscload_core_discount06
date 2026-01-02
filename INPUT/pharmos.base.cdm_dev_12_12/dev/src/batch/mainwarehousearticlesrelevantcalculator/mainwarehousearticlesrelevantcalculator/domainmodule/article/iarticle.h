#ifndef GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_ARTICLE_IARTICLE_H
#define GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_ARTICLE_IARTICLE_H

#include "infrastructure/dataprovider/idataproviderptr.h"
#include <libbasar_definitions.h>

//-------------------------------------------------------------------------------------------------//
// interface definition section
//-------------------------------------------------------------------------------------------------//
namespace mainwarehousearticlesrelevantcalculator
{
namespace domMod
{
namespace article
{
    class IArticle
    {
    public:
        virtual ~IArticle() {}

        virtual bool                                                        calculateRelevance() = 0;  //const = 0;
        virtual bool                                                        hasConfiguration()         const = 0;

        virtual basar::Int32                                                getArticleNo()             const = 0;
        virtual bool                                                        getPreviousRelevanceFlag() const = 0;
        virtual infrastructure::dataProvider::IDataProviderPtr              getArticleData()           const = 0;
        virtual bool                                                        isAdmissionParamGroupRelevant() = 0;
        virtual void                                                        setAdmissionParamGroupRelevant(bool acg) = 0;
    };

} // end namespace article
} // end namespace domMod
} // end namespace mainwarehousearticlesrelevantcalculator

#endif // GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_ARTICLE_IARTICLE_H
