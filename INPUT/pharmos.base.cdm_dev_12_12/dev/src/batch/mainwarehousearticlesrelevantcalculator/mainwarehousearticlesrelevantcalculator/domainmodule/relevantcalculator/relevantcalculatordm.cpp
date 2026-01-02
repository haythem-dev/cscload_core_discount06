#include "relevantcalculatordm.h"

#include "domainmodule/article/iarticlecollectionfinder.h"
#include "domainmodule/article/iarticle.h"
#include "domainmodule/article/iarticleconfigwriter.h"

#include "domainmodule/mainwarehousearticlesrelevantcalculator_properties_definitions.h"
#include "loggerpool/mainwarehousearticlesrelevantcalculator_loggerpool.h"

#include <libbasardbaspect_accessorpropertytable.h>
#include <libbasardbaspect_accessorpropertytable_yiterator.h>

#include <libutil/util.h>
#ifdef _DEBUG
#include <chrono>
#endif
namespace mainwarehousearticlesrelevantcalculator
{
namespace domMod
{
namespace relevantCalculator
{
    const libutil::misc::ClassInfo& RelevantCalculatorDM::getClassInfo()
    {
        static const libutil::misc::ClassInfo info( "RelevantCalculatorDM", libutil::misc::Version( 1, 0, 0, 0 ) );
        return info;
    }

    RelevantCalculatorDM::RelevantCalculatorDM()
        : m_Logger( LoggerPool::getLoggerDomModules() )
    {
    }

    RelevantCalculatorDM::~RelevantCalculatorDM()
    {
    }

    const log4cplus::Logger& RelevantCalculatorDM::getLogger() const
    {
        return m_Logger;
    }

    void RelevantCalculatorDM::injectArticleCollectionFinder( domMod::article::IArticleCollectionFinderPtr articleColl )
    {
        m_ArticleCollectionFinder = articleColl;
    }

    domMod::article::IArticleCollectionFinderPtr RelevantCalculatorDM::getArticleCollectionFinder() const
    {
        CHECK_INSTANCE_EXCEPTION( m_ArticleCollectionFinder.get() );
        return m_ArticleCollectionFinder;
    }

    void RelevantCalculatorDM::injectArticleConfigWriter( domMod::article::IArticleConfigWriterPtr articleConfigWriter )
    {
        m_ArticleConfigWriter = articleConfigWriter;
    }

    domMod::article::IArticleConfigWriterPtr RelevantCalculatorDM::getArticleConfigWriter() const
    {
        CHECK_INSTANCE_EXCEPTION( m_ArticleConfigWriter.get() );
        return m_ArticleConfigWriter;
    }

    void RelevantCalculatorDM::setSession( libutil::infrastructure::session::ISessionPtr session )
    {
        m_Session = session;
    }

    libutil::infrastructure::session::ISessionPtr RelevantCalculatorDM::getSession() const
    {
        CHECK_INSTANCE_EXCEPTION( m_Session.get() );
        return m_Session;
    }

    void RelevantCalculatorDM::calculate()
    {
        METHODNAME_DEF( RelevantCalculatorDM, calculate );
        BLOG_TRACE_METHOD( getLogger(), fun );

#ifdef _DEBUG
        // get count of all articles for this branch
        // hint: cannot ask the propTab result for the count, so need to get the before as an own result
        basar::Int32 counter = getArticleCollectionFinder()->countByBranchNo(getSession()->getUser()->getAreaID());
        std::ostringstream scnt;
        scnt << "RelevantCalculatorDM::calculate() found " << counter << " articles for branch " << getSession()->getUser()->getAreaID();
        BLOG_INFO(getLogger(), scnt.str());
#endif

        // get all articles for this branch
		getArticleCollectionFinder()->findByBranchNo( getSession()->getUser()->getAreaID() );
        basar::db::aspect::AccessorPropertyTableRef propTab = getArticleCollectionFinder()->get();
        
        int cnt = 0;
#ifdef _DEBUG
        auto startTime = std::chrono::high_resolution_clock::now();
        auto tempTime = startTime;
        auto endTime = std::chrono::high_resolution_clock::now();
        auto duration = 0;
#endif
        // Schleife über alle Artikel dieses VZ´s
        for( basar::db::aspect::AccessorPropertyTable_YIterator yit = propTab.begin(); ! yit.isEnd(); ++yit )
        {
            domMod::article::IArticlePtr article = getArticleCollectionFinder()->getArticle( yit );         
			getArticleConfigWriter()->writeConfig( article );
            cnt++;
#ifdef _DEBUG
            if ((cnt % 10000) == 0)
            {
                endTime = std::chrono::high_resolution_clock::now();
                duration = (int)std::chrono::duration_cast<std::chrono::milliseconds>(endTime - tempTime).count();
                std::ostringstream scnt1;
                scnt1 << "RelevantCalculatorDM::calculate() Articlecount: " << std::to_string(cnt) << " took " << std::to_string(duration / 1000) << " seconds";
                BLOG_INFO(getLogger(), scnt1.str());
                tempTime = endTime;
            }
#endif
        }
#ifdef _DEBUG
        endTime = std::chrono::high_resolution_clock::now();
        duration = (int)std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
        std::ostringstream scnt2;
        scnt2 << "RelevantCalculatorDM::calculate() All Articles: " << std::to_string(cnt) << " took " << std::to_string(duration / 1000) << " seconds";
        BLOG_INFO(getLogger(), scnt2.str());
#else
        std::ostringstream scnt3;
        scnt3 << "RelevantCalculatorDM::calculate(): " << std::to_string(cnt) << " Articles processed";
        BLOG_INFO(getLogger(), scnt3.str());
#endif

		BLOG_INFO( getLogger(), "deleting all relevance flags for unknown articles ..." );
        getArticleConfigWriter()->eraseDeprecatedConfig();
    }

} // end namespace relevantCalculator
} // end namespace domMod
} // end namespace mainwarehousearticlesrelevantcalculator
