#include "articlefactory.h"

#include "irelevantrulefactory.h"

#include "domainmodule/article/articledm.h"
#include "domainmodule/article/articledmptr.h"

#include "loggerpool/mainwarehousearticlesrelevantcalculator_loggerpool.h"

// other
#include "infrastructure/dataprovider/basardbaspect_dataprovider.h"

#include <libutil/util.h>
#include <libbasardbaspect_accessorpropertytable_yiterator.h>
#include <libbasardbaspect_accessorpropertytable.h>

#include <boost/make_shared.hpp>

namespace mainwarehousearticlesrelevantcalculator
{
namespace componentManager
{
    ArticleFactory::ArticleFactory()
        : m_Logger( LoggerPool::getLoggerMainwarehouseArticlesRelevantCalculator() )
    {
        METHODNAME_DEF( ArticleFactory, ArticleFactory );
        BLOG_TRACE_METHOD( getLogger(), fun );
    }

    ArticleFactory::~ArticleFactory()
    {
        METHODNAME_DEF( ArticleFactory, ~ArticleFactory );
        BLOG_TRACE_METHOD( getLogger(), fun );
    }

    const log4cplus::Logger& ArticleFactory::getLogger() const
    {
        return m_Logger;
    }

    void ArticleFactory::injectRelevantRule( domMod::relevantRule::IRelevantRulePtr rule )
    {
        m_RelevantRule = rule;
    }

    domMod::relevantRule::IRelevantRulePtr ArticleFactory::getRelevantRule() const
    {
        CHECK_INSTANCE_EXCEPTION( m_RelevantRule.get() );
        return m_RelevantRule;
    }

    infrastructure::dataProvider::IDataProviderPtr ArticleFactory::getDataProvider( basar::db::aspect::AccessorPropertyTable_YIterator yit )
    {
        return boost::make_shared< infrastructure::dataProvider::BasarDBAspectDataProvider >( yit );
    }

    domMod::article::IArticlePtr ArticleFactory::create( basar::db::aspect::AccessorPropertyTable_YIterator yit )
    {
        METHODNAME_DEF( ApplCompMgr, getArticle );
        BLOG_TRACE_METHOD( m_Logger, fun );

        domMod::article::ArticleDMPtr article = boost::make_shared< domMod::article::ArticleDM >();
        article->injectRelevantRule    ( getRelevantRule()      );
        article->setArticleDataProvider( getDataProvider( yit ) );

        return article;
    }

}// end namespace componentManager
}// end namespace mainwarehousearticlesrelevantcalculator
