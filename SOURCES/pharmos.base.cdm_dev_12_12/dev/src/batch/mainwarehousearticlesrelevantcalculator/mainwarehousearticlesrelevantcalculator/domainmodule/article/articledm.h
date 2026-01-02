#ifndef GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_ARTICLE_ARTICLEDM_H
#define GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_ARTICLE_ARTICLEDM_H

#include "iarticle.h"

#include "domainmodule/relevantrule/irelevantruleptr.h"

#include <libutil/classinfo.h>
#include <libutil/util.h>

//-------------------------------------------------------------------------------------------------//
// class definition section
//-------------------------------------------------------------------------------------------------//
namespace mainwarehousearticlesrelevantcalculator
{
namespace domMod
{
namespace article
{
    class ArticleDM : public IArticle
    {
    public:
        static const libutil::misc::ClassInfo& getClassInfo();

    public:
        ArticleDM();
        ~ArticleDM();

        void                                                        setArticleDataProvider( infrastructure::dataProvider::IDataProviderPtr );
        void                                                        injectRelevantRule    ( domMod::relevantRule::IRelevantRulePtr );

        // from IArticle interface
        bool                                                        calculateRelevance();//const;
        bool                                                        hasConfiguration()         const;

        basar::Int32                                                getArticleNo()             const;
        bool                                                        getPreviousRelevanceFlag() const;
        infrastructure::dataProvider::IDataProviderPtr              getArticleData()           const;
        bool                                                        isAdmissionParamGroupRelevant()                   ;
        void                                                        setAdmissionParamGroupRelevant( bool flag);

    private:
        // forbidden
        ArticleDM( const ArticleDM& );
        ArticleDM& operator = ( const ArticleDM& );

        const log4cplus::Logger&                                    getLogger()                const;

    private:
        const log4cplus::Logger&                                    m_Logger;
        infrastructure::dataProvider::IDataProviderPtr              m_ArticleData;
        domMod::relevantRule::IRelevantRulePtr                      m_RelevantRule;
        bool                                                        m_isAdmissionParamGroupRelevant;
    };

} // end namespace article
} // end namespace domMod
} // end namespace mainwarehousearticlesrelevantcalculator

#endif // GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_ARTICLE_ARTICLEDM_H
