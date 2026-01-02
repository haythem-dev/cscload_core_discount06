#ifndef GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_COMPONENTMANAGER_MAINWAREHOUSEARTICLESRELEVANTCALCULATORAPPLCOMPMGR_H
#define GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_COMPONENTMANAGER_MAINWAREHOUSEARTICLESRELEVANTCALCULATORAPPLCOMPMGR_H

//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include <libutil/irunnableptr.h>

// uc
#include "iusecasegetter.h"

// getter
#include "istoragelocationslotcheckergetter.h"

// factories
#include "componentmanager/irelevantrulefactoryptr.h"
#include "componentmanager/iarticlefactoryptr.h"

// dm
#include "domainmodule/article/iarticlecollectionfinderptr.h"
#include "domainmodule/article/iarticleptr.h"
#include "domainmodule/article/iarticleconfigwriterptr.h"
#include "domainmodule/assignmentparameter/iassignmentparametercollectionptr.h"
#include "domainmodule/mainwarehouse/imainwarehousefinderptr.h"
#include "domainmodule/relevantcalculator/irelevantcalculatorptr.h"
#include "domainmodule/storagelocation/istoragelocationslotcheckerptr.h"

// libutil
#include <libutil/applcomponent.h>
#include <libutil/accessor/iaccessorptr.h>

#include <boost/enable_shared_from_this.hpp>

//-------------------------------------------------------------------------------------------------//
// forward declaration section
//-------------------------------------------------------------------------------------------------//
namespace basar
{
    namespace db
    {
        namespace aspect
        {
            class ConnectionRef;
        }
    }
}

namespace log4cplus
{
    class Logger;
}

//-------------------------------------------------------------------------------------------------//
// class declaration setcion
//-------------------------------------------------------------------------------------------------//
namespace mainwarehousearticlesrelevantcalculator
{
    namespace componentManager
    {
        class ApplCompMgr : public libutil::componentManager::ApplCompMgrBase,
                            public IUseCaseGetter,
                            public IStorageLocationSlotCheckerGetter,
                            public boost::enable_shared_from_this< ApplCompMgr >
        {
            public:
                ApplCompMgr();
                virtual ~ApplCompMgr();

                /////////////////////////////////////////////////////////////////////
                // use case
                /////////////////////////////////////////////////////////////////////
                libutil::useCase::IRunnablePtr                                              getMainUC();
                libutil::useCase::IRunnablePtr                                              getRelevantCalculatorUC();
                libutil::useCase::IRunnablePtr                                              getAdmissionConsiderGroupUC();

            protected:
                virtual void                                                                doClear();

            private:
                ApplCompMgr( const ApplCompMgr& );
                ApplCompMgr& operator=( const ApplCompMgr& );

                /////////////////////////////////////////////////////////////////////
                // Factories
                /////////////////////////////////////////////////////////////////////
                IArticleFactoryPtr                                                          getMainwarehouseArticleFactory();
                IRelevantRuleFactoryPtr                                                     getMainwarehouseArticlesRelevantRuleFactory();

                /////////////////////////////////////////////////////////////////////
                // DM
                /////////////////////////////////////////////////////////////////////
                domMod::article::IArticleCollectionFinderPtr                                getMainwarehouseArticleCollectionFinder();
                domMod::article::IArticleConfigWriterPtr                                    getMainwarehouseArticleConfigWriter();

                domMod::assignmentParameter::IAssignmentParameterCollectionPtr              getMainwarehouseAssignmentParameterCollection();
                domMod::mainwarehouse::IMainwarehouseFinderPtr                              getMainwarehouseFinder();

                domMod::relevantCalculator::IRelevantCalculatorPtr                          getMainwarehouseRelevantCalculator();
                domMod::storageLocation::IStorageLocationSlotCheckerPtr                     getStorageLocationSlotChecker();
                
                /////////////////////////////////////////////////////////////////////
                // Accessor
                /////////////////////////////////////////////////////////////////////
                libutil::infrastructure::accessor::IAccessorPtr                             getMainwarehouseArticleCollectionACC();
                libutil::infrastructure::accessor::IAccessorPtr                             getMainwarehouseAssignmentParameterACC();
                libutil::infrastructure::accessor::IAccessorPtr                             getMainwarehouseBranchArticleConfigACC();
                libutil::infrastructure::accessor::IAccessorPtr                             getMainwarehouseACC();
                libutil::infrastructure::accessor::IAccessorPtr                             getStorageLocationSlotACC();

            private:
                ///////////////////////////////////////////////////////////////////
                // member variables
                ///////////////////////////////////////////////////////////////////
                const log4cplus::Logger&                                                    m_Logger;
        };

    } // end namnespace componentManager
} // end namnespace mainwarehousearticlesrelevantcalculator

#endif
