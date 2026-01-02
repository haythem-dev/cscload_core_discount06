//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
// global
#include "mainwarehousearticlesrelevantcalculatorapplcompmgr.h"
#include "loggerpool/mainwarehousearticlesrelevantcalculator_loggerpool.h"
#include "mainwarehousearticlesrelevantcalculatorinfo/mainwarehousearticlesrelevantcalculator_info.h"

// uc
#include "usecase/mainucptr.h"
#include "usecase/mainuc.h"
#include "usecase/relevantcalculatorucptr.h"
#include "usecase/relevantcalculatoruc.h"
#include "usecase/admissionconsidergroupsuc.h"
#include "usecase/admissionconsidergroupsucptr.h"

// Factory
#include "articlefactory.h"
#include "articlefactoryptr.h"
#include "mainwarehousearticlesrelevantrulefactory.h"
#include "mainwarehousearticlesrelevantrulefactoryptr.h"

// dm
#include "domainmodule/article/brancharticleconfigdm.h"
#include "domainmodule/article/brancharticleconfigdmptr.h"
#include "domainmodule/article/mainwarehousearticlecollectiondm.h"
#include "domainmodule/article/mainwarehousearticlecollectiondmptr.h"

#include "domainmodule/assignmentparameter/assignmentparametercollectiondm.h"
#include "domainmodule/assignmentparameter/assignmentparametercollectiondmptr.h"

#include "domainmodule/mainwarehouse/mainwarehousedm.h"
#include "domainmodule/mainwarehouse/mainwarehousedmptr.h"

#include "domainmodule/relevantcalculator/relevantcalculatordm.h"
#include "domainmodule/relevantcalculator/relevantcalculatordmptr.h"

#include "domainmodule/storagelocation/storagelocationdm.h"
#include "domainmodule/storagelocation/storagelocationdmptr.h"

#include "domainmodule/mainwarehousearticlesrelevantcalculator_properties_definitions.h"

// accessor
#include "infrastructure/accessor/article/articlecollectionacc.h"
#include "infrastructure/accessor/article/articlecollectionacc_definitions.h"
#include "infrastructure/accessor/assignmentparameter/mainwarehouseassignmentparameteracc.h"
#include "infrastructure/accessor/assignmentparameter/mainwarehouseassignmentparameteracc_definitions.h"
#include "infrastructure/accessor/brancharticleconfig/mainwarehousebrancharticleconfigacc.h"
#include "infrastructure/accessor/brancharticleconfig/mainwarehousebrancharticleconfigacc_definitions.h"
#include "infrastructure/accessor/mainwarehouse/mainwarehouseacc_definitions.h"
#include "infrastructure/accessor/mainwarehouse/mainwarehouseacc.h"
#include "infrastructure/accessor/storagelocationslot/storagelocationslotacc.h"
#include "infrastructure/accessor/storagelocationslot/storagelocationslotacc_definitions.h"

// libutil
#include <libutil/accessor.h>
#include <libutil/util.h>
#include <libutil/dbconnection.h>

// basar
#include <libbasarcmnutil_logging.h>
#include <libbasardbsql_databaseinfo.h>
#include <libbasarlogin.h>
#include <libbasardbsql.h>
#include <libbasarproperty.h>

#include <boost/make_shared.hpp>

//----------------------------------------------------------------------------//
// class definition setcion
//----------------------------------------------------------------------------//
namespace mainwarehousearticlesrelevantcalculator
{
    namespace componentManager
    {
        ApplCompMgr::ApplCompMgr()
        : m_Logger( mainwarehousearticlesrelevantcalculator::LoggerPool::getLoggerMainwarehouseArticlesRelevantCalculator() )
        {
            METHODNAME_DEF( ApplCompMgr, ApplCompMgr )
            BLOG_TRACE_METHOD( m_Logger, fun );
        }

        ApplCompMgr::~ApplCompMgr()
        {
            METHODNAME_DEF( ApplCompMgr, ~ApplCompMgr )
            BLOG_TRACE_METHOD( m_Logger, fun );
        }

        void ApplCompMgr::doClear()
        {
            METHODNAME_DEF( ApplCompMgr, doClear )
            BLOG_TRACE_METHOD( m_Logger, fun );
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // <UC getting>
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        libutil::useCase::IRunnablePtr ApplCompMgr::getMainUC()
        {
            METHODNAME_DEF( ApplCompMgr, getMainUC )
            BLOG_TRACE_METHOD( m_Logger, fun );

            useCase::MainUCPtr mainUC = boost::make_shared< useCase::MainUC > ();
            mainUC->injectUseCaseGetter( shared_from_this() );

            return mainUC;
        }
        
        libutil::useCase::IRunnablePtr ApplCompMgr::getRelevantCalculatorUC()
        {
            METHODNAME_DEF( ApplCompMgr, getRelevantCalculatorUC )
            BLOG_TRACE_METHOD( m_Logger, fun );

            useCase::RelevantCalculatorUCPtr uc = boost::make_shared< useCase::RelevantCalculatorUC >();
            uc->injectRelevantCalculator( getMainwarehouseRelevantCalculator() );

            return uc;
        }

        libutil::useCase::IRunnablePtr ApplCompMgr::getAdmissionConsiderGroupUC()
        {
            METHODNAME_DEF(ApplCompMgr, getAdmissionConsiderGroupUC)
            BLOG_TRACE_METHOD(m_Logger, fun);

            useCase::AdmissionConsiderGroup::AdmissionConsiderGroupsUCPtr uc = boost::make_shared< useCase::AdmissionConsiderGroup::AdmissionConsiderGroupsUC >();
            uc->injectDBConnection(getDBConnectionData()->getCurrentConnection());
            uc->setBranchNo(getSession()->getUser()->getAreaID());
            uc->initAdmissionGroups();
            return uc;
        }

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // </UC getting>
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // <Factory getting>
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        IArticleFactoryPtr ApplCompMgr::getMainwarehouseArticleFactory()
        {
            METHODNAME_DEF( ApplCompMgr, getMainwarehouseArticleFactory )
            BLOG_TRACE_METHOD( m_Logger, fun );

            ArticleFactoryPtr factory = boost::make_shared< ArticleFactory >();
            factory->injectRelevantRule( getMainwarehouseArticlesRelevantRuleFactory()->create( getSession()->getUser()->getAreaID() ) ); 
            
            return factory;
        }

        IRelevantRuleFactoryPtr ApplCompMgr::getMainwarehouseArticlesRelevantRuleFactory()
        {
            METHODNAME_DEF( ApplCompMgr, getMainwarehouseArticlesRelevantRuleFactory )
            BLOG_TRACE_METHOD( m_Logger, fun );

            MainwarehouseArticlesRelevantRuleFactoryPtr factory = boost::make_shared< MainwarehouseArticlesRelevantRuleFactory >();
            factory->injectAssignmentParameterCollection             ( getMainwarehouseAssignmentParameterCollection() );
            factory->injectMainwarehouseFinder                       ( getMainwarehouseFinder()                        );
            factory->injectStorageLocationSlotCheckerGetter          ( shared_from_this()                              );

            return factory;
        }
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // </Factory getting>
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // <DM getting>
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        domMod::article::IArticleCollectionFinderPtr ApplCompMgr::getMainwarehouseArticleCollectionFinder()
        {
            METHODNAME_DEF( ApplCompMgr, getMainwarehouseArticleCollectionFinder )
            BLOG_TRACE_METHOD( m_Logger, fun );

            domMod::article::MainwarehouseArticleCollectionDMPtr dm = boost::make_shared< domMod::article::MainwarehouseArticleCollectionDM >();
            dm->injectArticleCollectionAccessor( getMainwarehouseArticleCollectionACC() );
            dm->injectArticleFactory           ( getMainwarehouseArticleFactory()       );
            dm->injectMainwarehouseFinder      ( getMainwarehouseFinder()               );

            return dm;
        }

        domMod::article::IArticleConfigWriterPtr ApplCompMgr::getMainwarehouseArticleConfigWriter()
        {
            METHODNAME_DEF( ApplCompMgr, getMainwarehouseArticleConfigWriter )
            BLOG_TRACE_METHOD( m_Logger, fun );

            domMod::article::BranchArticleConfigDMPtr dm = boost::make_shared< domMod::article::BranchArticleConfigDM >();
            dm->injectBranchArticleConfigAccessor( getMainwarehouseBranchArticleConfigACC() );

            // add admissionparamgroupUC for checking dynamic group conditions
            useCase::AdmissionConsiderGroup::AdmissionConsiderGroupsUCPtr uc = boost::make_shared< useCase::AdmissionConsiderGroup::AdmissionConsiderGroupsUC >();
            uc->injectDBConnection(getDBConnectionData()->getCurrentConnection());
            uc->setBranchNo(getSession()->getUser()->getAreaID());
            uc->initAdmissionGroups();
            dm->injectAdmissionConsiderGroupsUC(uc);

            return dm;
        }

        domMod::assignmentParameter::IAssignmentParameterCollectionPtr ApplCompMgr::getMainwarehouseAssignmentParameterCollection()
        {
            METHODNAME_DEF( ApplCompMgr, getMainwarehouseAssignmentParameterCollection )
            BLOG_TRACE_METHOD( m_Logger, fun );

            domMod::assignmentParameter::AssignmentParameterCollectionDMPtr dm = boost::make_shared< domMod::assignmentParameter::AssignmentParameterCollectionDM >();
            dm->injectAssignmentParameterCollectionAccessor( getMainwarehouseAssignmentParameterACC() );

            return dm;
        }

        domMod::mainwarehouse::IMainwarehouseFinderPtr ApplCompMgr::getMainwarehouseFinder()
        {
            METHODNAME_DEF( ApplCompMgr, getMainwarehouseFinder )
            BLOG_TRACE_METHOD( m_Logger, fun );

            domMod::mainwarehouse::MainwarehouseDMPtr dm = boost::make_shared< domMod::mainwarehouse::MainwarehouseDM >();
            dm->injectMainwarehouseAccessor( getMainwarehouseACC() );

            return dm;
        }

        domMod::relevantCalculator::IRelevantCalculatorPtr ApplCompMgr::getMainwarehouseRelevantCalculator()
        {
            METHODNAME_DEF( ApplCompMgr, getMainwarehouseRelevantCalculator )
            BLOG_TRACE_METHOD( m_Logger, fun );

            domMod::relevantCalculator::RelevantCalculatorDMPtr dm = boost::make_shared< domMod::relevantCalculator::RelevantCalculatorDM >();
            dm->injectArticleCollectionFinder( getMainwarehouseArticleCollectionFinder() );
            dm->injectArticleConfigWriter    ( getMainwarehouseArticleConfigWriter()     );
            dm->setSession                   ( getSession()                              );

            return dm;
        }

        domMod::storageLocation::IStorageLocationSlotCheckerPtr ApplCompMgr::getStorageLocationSlotChecker()
        {
            METHODNAME_DEF( ApplCompMgr, getStorageLocationSlotChecker )
            BLOG_TRACE_METHOD( m_Logger, fun );

            domMod::storageLocation::StorageLocationDMPtr dm = boost::make_shared< domMod::storageLocation::StorageLocationDM >();
            dm->injectStorageLocationSlotAccessor( getStorageLocationSlotACC() );

            return dm;
        }
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // </DM getting>
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // <ACC getting>
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        libutil::infrastructure::accessor::IAccessorPtr ApplCompMgr::getMainwarehouseArticleCollectionACC()
        {
            METHODNAME_DEF( ApplCompMgr, getMainwarehouseArticleCollectionACC )
            BLOG_TRACE_METHOD( m_Logger, fun );

            infrastructure::accessor::article::SelectArticleCollection();

            using namespace libutil::infrastructure::accessor;
            using infrastructure::accessor::article::lit::ARTICLE_COLLECTION_ACC;
            IAccessorPtr accessor = boost::make_shared< AccessorProxy >( ARTICLE_COLLECTION_ACC, getDBConnectionData()->getCurrentConnection(), 
                                                                         basar::db::aspect::SINGLE_ROW_CACHING );

            return accessor;
        }

        libutil::infrastructure::accessor::IAccessorPtr ApplCompMgr::getMainwarehouseAssignmentParameterACC()
        {
            METHODNAME_DEF( ApplCompMgr, getMainwarehouseAssignmentParameterACC )
            BLOG_TRACE_METHOD( m_Logger, fun );

            infrastructure::accessor::assignmentParameter::SelectMainwarehouseAssignmentParameterByBranch();

            using namespace libutil::infrastructure::accessor;
            using infrastructure::accessor::assignmentParameter::lit::MAINWAREHOUSE_ASSIGNMENTPARAMETER_ACC;
            IAccessorPtr accessor = boost::make_shared< AccessorProxy >( MAINWAREHOUSE_ASSIGNMENTPARAMETER_ACC, 
                                                                         getDBConnectionData()->getCurrentConnection() );

            return accessor;
        }

        libutil::infrastructure::accessor::IAccessorPtr ApplCompMgr::getMainwarehouseBranchArticleConfigACC()
        {
            METHODNAME_DEF( ApplCompMgr, getMainwarehouseBranchArticleConfigACC )
            BLOG_TRACE_METHOD( m_Logger, fun );

            using infrastructure::accessor::branchArticleConfig::MainwarehouseBranchArticleConfigACC;

            typedef boost::shared_ptr< MainwarehouseBranchArticleConfigACC > MainwarehouseBranchArticleConfigACCPtr; 
            MainwarehouseBranchArticleConfigACCPtr accessor = boost::make_shared< MainwarehouseBranchArticleConfigACC >();
            accessor->injectConnection( getDBConnectionData() );
            accessor->setSession( getSession() );

            return accessor;
        }

        libutil::infrastructure::accessor::IAccessorPtr ApplCompMgr::getMainwarehouseACC()
        {
            METHODNAME_DEF( ApplCompMgr, getMainwarehouseACC )
            BLOG_TRACE_METHOD( m_Logger, fun );

            infrastructure::accessor::mainwarehouse::SelectMainwarehouseByBranch();

            using namespace libutil::infrastructure::accessor;
            using infrastructure::accessor::mainwarehouse::lit::MAINWAREHOUSE_ACC;
            IAccessorPtr accessor = boost::make_shared< AccessorProxy >( MAINWAREHOUSE_ACC, getDBConnectionData()->getCurrentConnection() );

            return accessor;
        }

        libutil::infrastructure::accessor::IAccessorPtr ApplCompMgr::getStorageLocationSlotACC()
        {
            METHODNAME_DEF( ApplCompMgr, getStorageLocationSlotACC )
            BLOG_TRACE_METHOD( m_Logger, fun );

            infrastructure::accessor::storageSlot::SelectPseudoStorageSlotByBranch();

            using namespace libutil::infrastructure::accessor;
            using infrastructure::accessor::storageSlot::lit::STORAGESLOT_ACC;
            IAccessorPtr accessor = boost::make_shared< AccessorProxy >( STORAGESLOT_ACC, getDBConnectionData()->getCurrentConnection() );

            return accessor;
        }
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // </ACC getting>
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    } // end namespace componentManager
} // end namespace mainwarehousearticlesrelevantcalculator
