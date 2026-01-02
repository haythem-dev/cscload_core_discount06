//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include "mainwarehousearticlecollectiondm.h"

#include "componentmanager/iarticlefactory.h"
#include "domainmodule/mainwarehouse/imainwarehousefinder.h"

#include "domainmodule/mainwarehousearticlesrelevantcalculator_properties_definitions.h"
#include "infrastructure/accessor/article/articlecollectionacc_definitions.h"
#include "loggerpool/mainwarehousearticlesrelevantcalculator_loggerpool.h"

#include <libutil/domainmodule.h>
#include <libutil/version.h>
#include <libutil/exception.h>

#include <boost/make_shared.hpp>

//--------------------------------------------------------------------------------------------------//
// class definition section
//--------------------------------------------------------------------------------------------------//
namespace mainwarehousearticlesrelevantcalculator
{
namespace domMod
{
namespace article
{

    const libutil::misc::ClassInfo& MainwarehouseArticleCollectionDM::getClassInfo()
    {
        static const libutil::misc::ClassInfo info( "MainwarehouseArticleCollectionDM", libutil::misc::Version( 1, 0, 0, 0 ) );
        return info;
    }

    MainwarehouseArticleCollectionDM::MainwarehouseArticleCollectionDM()
        : m_Logger( LoggerPool::getLoggerDomModules() )
    {
        METHODNAME_DEF( MainwarehouseArticleCollectionDM, MainwarehouseArticleCollectionDM )
        BLOG_TRACE_METHOD( getLogger(), fun );
    }

    MainwarehouseArticleCollectionDM::~MainwarehouseArticleCollectionDM()
    {
        METHODNAME_DEF( MainwarehouseArticleCollectionDM, ~MainwarehouseArticleCollectionDM )
        BLOG_TRACE_METHOD( getLogger(), fun );
    }

    void MainwarehouseArticleCollectionDM::injectArticleCollectionAccessor( libutil::infrastructure::accessor::IAccessorPtr accessor )
    {
        m_Accessor = accessor;
    }

    libutil::infrastructure::accessor::IAccessorPtr MainwarehouseArticleCollectionDM::getAccessor() const
    {
        CHECK_INSTANCE_EXCEPTION( m_Accessor.get() );
        return m_Accessor;
    }

    void MainwarehouseArticleCollectionDM::injectArticleFactory( componentManager::IArticleFactoryPtr articleFactory )
    {
        m_ArticleFactory = articleFactory;
    }

    void MainwarehouseArticleCollectionDM::injectMainwarehouseFinder( domMod::mainwarehouse::IMainwarehouseFinderPtr warehouseFinder )
    {
        m_MainwarehouseFinder = warehouseFinder;
    }

    basar::db::aspect::AccessorPropertyTableRef MainwarehouseArticleCollectionDM::get() const
    {
        return getAccessor()->getPropertyTable();
    }

    bool MainwarehouseArticleCollectionDM::isEmpty() const
    {
        return 0 == getAccessor().get() || m_Accessor->getPropertyTable().isNull() ||
               m_Accessor->getPropertyTable().isEmpty();
    }

    libutil::domMod::SearchYIteratorPtr MainwarehouseArticleCollectionDM::getSearchYIterator()
    {
        if( NULL == m_SearchYIterator.get() )
        {
            m_SearchYIterator = boost::make_shared< libutil::domMod::SearchYIterator >( properties::BRANCH_NO.toDescriptionString()               + 
                                                                                        properties::BRANCH_NO_MAINWAREHOUSE.toDescriptionString() +
                                                                                        properties::LAST_PROGNOSIS_DATE.toDescriptionString()
                                                                                      );
        }

        return m_SearchYIterator;
    }

    const log4cplus::Logger& MainwarehouseArticleCollectionDM::getLogger() const
    {
        return m_Logger;
    }
    basar::Int32 MainwarehouseArticleCollectionDM::countByBranchNo( basar::Int16 branchNo )
    {
        METHODNAME_DEF(MainwarehouseArticleCollectionDM, countByBranchNo);
        BLOG_TRACE_METHOD(getLogger(), fun);

        using infrastructure::accessor::article::lit::SELECT_COUNT_ARTICLE_COLLECTION;

        basar::Int32 count = 0;
        try
        {
            getSearchYIterator()->get().setInt16(properties::BRANCH_NO, branchNo);
            getSearchYIterator()->get().setInt16(properties::BRANCH_NO_MAINWAREHOUSE, getMainwarehouseByBranchNo(branchNo));
            getSearchYIterator()->get().setInt32(properties::LAST_PROGNOSIS_DATE, findLastPrognosisDate());

            const std::pair<bool, basar::Decimal > result = getAccessor()->executeAggregate(SELECT_COUNT_ARTICLE_COLLECTION, getSearchYIterator()->get());
            if (result.first)
            {
                count = result.second.toInt32();
            }
        }
        catch (basar::Exception& e)
        {
            // count = 0 is already the answer in error case, so prevent exception
            e;
        }

        return count;
    }

    void MainwarehouseArticleCollectionDM::findByBranchNo( basar::Int16 branchNo )
    {
        METHODNAME_DEF( MainwarehouseArticleCollectionDM, findByBranchNo );
        BLOG_TRACE_METHOD( getLogger(), fun );

        using infrastructure::accessor::article::lit::SELECT_ARTICLE_COLLECTION;

        basar::db::aspect::ExecuteResultInfo executeResultInfo;
        try
        {
			getSearchYIterator()->get().setInt16( properties::BRANCH_NO, branchNo );
            getSearchYIterator()->get().setInt16( properties::BRANCH_NO_MAINWAREHOUSE, getMainwarehouseByBranchNo( branchNo ) );
            getSearchYIterator()->get().setInt32( properties::LAST_PROGNOSIS_DATE, findLastPrognosisDate() );


			std::ostringstream oss;
			oss << "fetching all articles for branch=" << branchNo << 
											", mwh=" << getSearchYIterator()->get().getInt16( properties::BRANCH_NO_MAINWAREHOUSE ) << 
											", date=" << getSearchYIterator()->get().getInt32( properties::LAST_PROGNOSIS_DATE ) << " ...";
			BLOG_INFO( getLogger(), oss.str() );

            executeResultInfo = getAccessor()->execute( SELECT_ARTICLE_COLLECTION, getSearchYIterator()->get() );
        }
        catch( basar::Exception& e )
        {
            libutil::exceptions::ExceptionHandler::processAccessorException( e, getLogger(), fun, SELECT_ARTICLE_COLLECTION, __FILE__, __LINE__ );
            throw;
        }

        if( executeResultInfo.hasError() )
        {
            THROW_ACCESSOR_EXECUTION_EXCEPTION( fun, SELECT_ARTICLE_COLLECTION, executeResultInfo )
        }
    }

    basar::Int32 MainwarehouseArticleCollectionDM::findLastPrognosisDate()
    {
        METHODNAME_DEF( MainwarehouseArticleCollectionDM, findLastPrognosisDate );
        BLOG_TRACE_METHOD( getLogger(), fun );

        using infrastructure::accessor::article::lit::SELECT_LAST_PROGNOSIS_DATE;

        basar::Int32 lastDate = 0;

        const std::pair<bool, basar::Decimal > result = getAccessor()->executeAggregate( SELECT_LAST_PROGNOSIS_DATE, 
                                                                                         getSearchYIterator()->get() );
        if( result.first )
        {
            lastDate = result.second.toInt32();
        }

        return lastDate;
    }

    basar::Int16 MainwarehouseArticleCollectionDM::getMainwarehouseByBranchNo( basar::Int16 branchNo )
    {
        METHODNAME_DEF( MainwarehouseArticleCollectionDM, getMainwarehouseByBranchNo );
        BLOG_TRACE_METHOD( getLogger(), fun );

        CHECK_INSTANCE_EXCEPTION( m_MainwarehouseFinder.get() );
        m_MainwarehouseFinder->findByBranchNo( branchNo );
        return m_MainwarehouseFinder->getMainwarehouseBranch();
    }

    IArticlePtr MainwarehouseArticleCollectionDM::getArticle( basar::db::aspect::AccessorPropertyTable_YIterator yit ) const
    {
        CHECK_INSTANCE_EXCEPTION( m_ArticleFactory.get() );
        return m_ArticleFactory->create( yit );
    }

} // end namespace article
} // end namespace domMod
} // end namespace mainwarehousearticlesrelevantcalculator
