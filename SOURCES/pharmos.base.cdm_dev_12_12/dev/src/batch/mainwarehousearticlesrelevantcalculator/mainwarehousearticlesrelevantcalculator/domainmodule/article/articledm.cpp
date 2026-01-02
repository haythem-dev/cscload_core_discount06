#include "articledm.h"

#include "domainmodule/relevantrule/irelevantrule.h"
#include "infrastructure/dataprovider/idataprovider.h"

#include "domainmodule/mainwarehousearticlesrelevantcalculator_properties_definitions.h"
#include "infrastructure/accessor/article/articlecollectionacc_definitions.h"
#include "loggerpool/mainwarehousearticlesrelevantcalculator_loggerpool.h"

//--------------------------------------------------------------------------------------------------//
// class definition section
//--------------------------------------------------------------------------------------------------//
namespace mainwarehousearticlesrelevantcalculator
{
namespace domMod
{
namespace article
{
    const libutil::misc::ClassInfo& ArticleDM::getClassInfo()
    {
        static const libutil::misc::ClassInfo info( "ArticleDM", libutil::misc::Version( 1, 0, 0, 0 ) );
        return info;
    }

    ArticleDM::ArticleDM()
        : m_Logger( LoggerPool::getLoggerDomModules() )
    {
        METHODNAME_DEF( ArticleDM, ArticleDM )
        BLOG_TRACE_METHOD( getLogger(), fun );
        m_isAdmissionParamGroupRelevant = false;
    }

    ArticleDM::~ArticleDM()
    {
        METHODNAME_DEF( ArticleDM, ~ArticleDM )
        BLOG_TRACE_METHOD( getLogger(), fun );
    }

    void ArticleDM::setArticleDataProvider( infrastructure::dataProvider::IDataProviderPtr dataProvider )
    {
        m_ArticleData = dataProvider;
    }

    void ArticleDM::injectRelevantRule( domMod::relevantRule::IRelevantRulePtr relevantRule )
    {
        m_RelevantRule = relevantRule;
    }

    const log4cplus::Logger& ArticleDM::getLogger() const
    {
        return m_Logger;
    }

    bool ArticleDM::isAdmissionParamGroupRelevant()
    {
        return m_isAdmissionParamGroupRelevant;
    }

    void ArticleDM::setAdmissionParamGroupRelevant(bool flag)
    {
        m_isAdmissionParamGroupRelevant = flag;
    }

    bool ArticleDM::calculateRelevance() //const
    {
        METHODNAME_DEF( ArticleDM, calculateRelevance )
        BLOG_TRACE_METHOD( getLogger(), fun );

        CHECK_INSTANCE_EXCEPTION( m_RelevantRule.get() );

        basar::VarString articleNo; 
		articleNo.itos( getArticleNo() );

        bool relevance = false;
        switch( m_RelevantRule->isRelevant( getArticleData() ) )
        {
            case infrastructure::dataType::Trilean::T_TRUE:
                BLOG_INFO( getLogger(), "Article '" + articleNo + "' IS relevant due to >" + m_RelevantRule->getDescription().toString() + "<!" );
                relevance = true;
                break;

            case infrastructure::dataType::Trilean::T_FALSE:
                BLOG_INFO( getLogger(), "Article '" + articleNo + "' is NOT relevant due to >" + m_RelevantRule->getDescription().toString() + "<!" );
                relevance = false;
                break;

            case infrastructure::dataType::Trilean::T_UNKNOWN:
                BLOG_INFO( getLogger(), "Article '" + articleNo + "' has UNKNOWN relevance! As no rule is matching, relevance is switched to FALSE!" );
                relevance = false;
                break;

            case infrastructure::dataType::Trilean::T_ACG:
                BLOG_INFO(getLogger(), "Article '" + articleNo + "' IS relevant due to >" + m_RelevantRule->getDescription().toString() + "<!");
                relevance = true;
                setAdmissionParamGroupRelevant(true);
                break;
        }

        return relevance;
    }

    bool ArticleDM::hasConfiguration() const
    {
        return getArticleData()->getInt16( properties::PREVIOUS_RELEVANCE_FLAG ) >= 0;
    }

    basar::Int32 ArticleDM::getArticleNo() const
    {
        return getArticleData()->getInt32( properties::ARTICLE_NO );
    }

    bool ArticleDM::getPreviousRelevanceFlag() const
    {
        return getArticleData()->getInt16( properties::PREVIOUS_RELEVANCE_FLAG ) == 1;
    }

    infrastructure::dataProvider::IDataProviderPtr ArticleDM::getArticleData() const
    {
        CHECK_INSTANCE_EXCEPTION( m_ArticleData.get() );
        return m_ArticleData;
    }

} // end namespace article
} // end namespace domMod
} // end namespace mainwarehousearticlesrelevantcalculator
