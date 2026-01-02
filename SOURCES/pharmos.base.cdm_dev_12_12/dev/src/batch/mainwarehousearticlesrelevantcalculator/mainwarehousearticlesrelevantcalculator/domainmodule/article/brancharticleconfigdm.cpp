#include "brancharticleconfigdm.h"

#include "iarticle.h"

#include "infrastructure/accessor/article/brancharticleconfigacc_definitions.h"


#include "domainmodule/mainwarehousearticlesrelevantcalculator_properties_definitions.h"
#include "infrastructure/accessor/article/articlecollectionacc_definitions.h"
#include "loggerpool/mainwarehousearticlesrelevantcalculator_loggerpool.h"

#include <libutil/exception.h>

//--------------------------------------------------------------------------------------------------//
// class definition section
//--------------------------------------------------------------------------------------------------//
namespace mainwarehousearticlesrelevantcalculator
{
namespace domMod
{
namespace article
{
    const libutil::misc::ClassInfo& BranchArticleConfigDM::getClassInfo()
    {
        static const libutil::misc::ClassInfo info( "BranchArticleConfigDM", libutil::misc::Version( 1, 0, 0, 0 ) );
        return info;
    }

    BranchArticleConfigDM::BranchArticleConfigDM()
        : m_Logger( LoggerPool::getLoggerDomModules() )
    {
        METHODNAME_DEF( BranchArticleConfigDM, BranchArticleConfigDM )
        BLOG_TRACE_METHOD( getLogger(), fun );
    }

    BranchArticleConfigDM::~BranchArticleConfigDM()
    {
        METHODNAME_DEF( BranchArticleConfigDM, ~BranchArticleConfigDM )
        BLOG_TRACE_METHOD( getLogger(), fun );
    }

    void BranchArticleConfigDM::injectBranchArticleConfigAccessor( libutil::infrastructure::accessor::IAccessorPtr accessor )
    {
        m_Accessor = accessor;
    }

    void BranchArticleConfigDM::injectAdmissionConsiderGroupsUC(useCase::AdmissionConsiderGroup::AdmissionConsiderGroupsUCPtr uc)
    {
        m_AdmissionGroupUC = uc;
    }

    libutil::infrastructure::accessor::IAccessorPtr BranchArticleConfigDM::getAccessor() const
    {
        CHECK_INSTANCE_EXCEPTION( m_Accessor.get() );
        return m_Accessor;
    }

    const log4cplus::Logger& BranchArticleConfigDM::getLogger() const
    {
        return m_Logger;
    }

    basar::db::aspect::AccessorPropertyTable_YIterator BranchArticleConfigDM::get() const
    {
        basar::db::aspect::AccessorPropertyTableRef propTab = getAccessor()->getPropertyTable();
        if( isEmpty() )
        {
            propTab.insert( basar::FOR_CLEAN );
        }

        return propTab.begin();
    }

    bool BranchArticleConfigDM::isEmpty() const
    {
        return 0 == getAccessor().get() || m_Accessor->getPropertyTable().isNull() ||
               m_Accessor->getPropertyTable().isEmpty();
    }

    void BranchArticleConfigDM::writeConfig( IArticlePtr article )
    {
        METHODNAME_DEF( BranchArticleConfigDM, writeConfig );
        BLOG_TRACE_METHOD( getLogger(), fun );

        using infrastructure::accessor::article::lit::INSERT_FLAG;
        using infrastructure::accessor::article::lit::UPDATE_FLAG;

        basar::VarString accMethod;
        basar::db::aspect::ExecuteResultInfo executeResultInfo;

        try
        {
            //const bool relevanceFlag = article->calculateRelevance();
            bool relevanceFlag = article->calculateRelevance();
            basar::Int16 paramgroupid = 0;
            // if its addmission group relevance
            if (article->isAdmissionParamGroupRelevant() == true)
            {
                article->setAdmissionParamGroupRelevant(false);
                m_AdmissionGroupUC->setArticleno(article->getArticleNo());
                paramgroupid = m_AdmissionGroupUC->assignAdmissionGroups();
                if (paramgroupid > 0) 
                {
                    relevanceFlag = true;
                    std::ostringstream oss;
                    oss << "ACG Paramgroupid relevance flag TRUE for Article..." << article->getArticleNo();
                    BLOG_INFO(getLogger(), oss.str());
                }
                else
                {
                    relevanceFlag = false;
                    std::ostringstream oss1;
                    oss1 << "ACG Paramgroupid relevance flag FALSE for Article..." << article->getArticleNo();
                    BLOG_INFO(getLogger(), oss1.str());
                }
            }
            bool prf = article->getPreviousRelevanceFlag();
            bool hc = article->hasConfiguration();
            if (prf)
            {
                BLOG_INFO(getLogger(), "getPreviousRelevanceFlag is TRUE...");
            }
            if (hc)
            {
                BLOG_INFO(getLogger(), "hasConfiguration is TRUE...");
            }
            if( relevanceFlag == article->getPreviousRelevanceFlag() && article->hasConfiguration() )
            {
                BLOG_INFO( getLogger(), "article relevance unchanged - nothing to persist ..." );
				return; // nothing to do
            }
            // flag has changed - store it
            basar::db::aspect::AccessorPropertyTable_YIterator yit = get();
            yit.setInt32(properties::ARTICLE_NO,     article->getArticleNo() );
            yit.setInt16(properties::RELEVANCE_FLAG, relevanceFlag           );
            yit.setInt16(properties::ADMISSION_PARAM_GROUPID, paramgroupid);

            if( article->hasConfiguration() )
            {
                std::ostringstream osu;
                osu << "Article relevance changed - updating article=" << article->getArticleNo() << " relevance flag=" << relevanceFlag << " admgroupid=" << paramgroupid;
                BLOG_INFO( getLogger(), osu.str());
				accMethod = UPDATE_FLAG;
            }
            else
            {
                std::ostringstream osi;
                osi << "New article relevance - inserting article=" << article->getArticleNo() << " relevance flag=" << relevanceFlag << " admgroupid=" << paramgroupid;
                BLOG_INFO(getLogger(), osi.str());
                accMethod = INSERT_FLAG;
            }
            executeResultInfo = getAccessor()->execute( accMethod, yit );
        }
        catch( basar::Exception& e )
        {
            libutil::exceptions::ExceptionHandler::processAccessorException( e, getLogger(), fun, accMethod, __FILE__, __LINE__ );
            throw;
        }

        if( executeResultInfo.hasError() )
        {
            THROW_ACCESSOR_EXECUTION_EXCEPTION( fun, accMethod, executeResultInfo )
        }
    }

    void BranchArticleConfigDM::eraseDeprecatedConfig()
    {
        METHODNAME_DEF( BranchArticleConfigDM, eraseDeprecatedConfig );
        BLOG_TRACE_METHOD( getLogger(), fun );

        using infrastructure::accessor::article::lit::ERASE_DEPRECATED_CONFIG;

        basar::db::aspect::ExecuteResultInfo executeResultInfo;
        try
        {
            executeResultInfo = getAccessor()->execute( ERASE_DEPRECATED_CONFIG );
        }
        catch( basar::Exception& e )
        {
            libutil::exceptions::ExceptionHandler::processAccessorException( e, getLogger(), fun, ERASE_DEPRECATED_CONFIG, __FILE__, __LINE__ );
            throw;
        }

        if( executeResultInfo.hasError() )
        {
            THROW_ACCESSOR_EXECUTION_EXCEPTION( fun, ERASE_DEPRECATED_CONFIG, executeResultInfo )
        }
    }

} // end namespace article
} // end namespace domMod
} // end namespace mainwarehousearticlesrelevantcalculator
