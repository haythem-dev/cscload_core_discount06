#ifndef GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_COMPONENTMANAGER_MAINWAREHOUSEARTICLESRELEVANTRULEFACTORY_H
#define GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_COMPONENTMANAGER_MAINWAREHOUSEARTICLESRELEVANTRULEFACTORY_H

#include "irelevantrulefactory.h"
#include "domainmodule/relevantrule/ruledescription.h"

#include "domainmodule/mainwarehouse/imainwarehousefinderptr.h"
#include "domainmodule/assignmentparameter/iassignmentparametercollectionptr.h"
#include "domainmodule/storagelocation/istoragelocationslotcheckerptr.h"

#include "componentmanager/istoragelocationslotcheckergetterptr.h"

#include <vector>

//-------------------------------------------------------------------------------------------------//
// forward declaration section
//-------------------------------------------------------------------------------------------------//
namespace basar
{
    namespace db
    {
        namespace aspect
        {
            class AccessorPropertyTable_YIterator;
        }
    }
}

//-------------------------------------------------------------------------------------------------//
// class definition section
//-------------------------------------------------------------------------------------------------//
namespace mainwarehousearticlesrelevantcalculator
{
namespace componentManager
{
    class MainwarehouseArticlesRelevantRuleFactory : public IRelevantRuleFactory
    {
    public:
        MainwarehouseArticlesRelevantRuleFactory();
        ~MainwarehouseArticlesRelevantRuleFactory();

        void                                                           injectAssignmentParameterCollection( domMod::assignmentParameter::IAssignmentParameterCollectionPtr );
        void                                                           injectMainwarehouseFinder( domMod::mainwarehouse::IMainwarehouseFinderPtr );
        void                                                           injectStorageLocationSlotCheckerGetter( componentManager::IStorageLocationSlotCheckerGetterPtr );

        // from IRelevantRuleFactory interface
        domMod::relevantRule::IRelevantRulePtr                         create( basar::Int16 branchNo );

    private:
        typedef std::vector< domMod::relevantRule::RuleDescription >   RuleDescriptionCollection;

        domMod::assignmentParameter::IAssignmentParameterCollectionPtr getAssignmentParameterCollection()                    const;
        basar::Int16                                                   getMainwarehouseBranchNo( basar::Int16)               const;
        domMod::storageLocation::IStorageLocationSlotCheckerPtr        getStorageLocationSlotCheckerByBranch( basar::Int16 ) const;

        void                                                           loadAssignmentParameters( basar::Int16 branchNo );
        RuleDescriptionCollection                                      getPrecedenceOrderedRuleDesc()                        const;

        domMod::relevantRule::IRelevantRulePtr                         createRule( const basar::db::aspect::AccessorPropertyTable_YIterator ) const;

    private:
        domMod::assignmentParameter::IAssignmentParameterCollectionPtr m_AssignmentParameterCollection;
        domMod::mainwarehouse::IMainwarehouseFinderPtr                 m_MainwarehouseFinder;
        componentManager::IStorageLocationSlotCheckerGetterPtr         m_StorageLocationSlotCheckerGetter;
    };

}// end namespace componentManager
}// end namespace mainwarehousearticlesrelevantcalculator

#endif // GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_COMPONENTMANAGER_MAINWAREHOUSEARTICLESRELEVANTRULEFACTORY_H
