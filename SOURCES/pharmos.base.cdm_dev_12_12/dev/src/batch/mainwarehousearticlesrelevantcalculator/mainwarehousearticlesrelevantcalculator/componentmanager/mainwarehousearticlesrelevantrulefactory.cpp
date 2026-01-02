#include "mainwarehousearticlesrelevantrulefactory.h"

#include "componentmanager/istoragelocationslotcheckergetter.h"

#include "domainmodule/assignmentparameter/iassignmentparametercollection.h"
#include "domainmodule/mainwarehouse/imainwarehousefinder.h"
#include "domainmodule/storagelocation/istoragelocationslotchecker.h"

#include "domainmodule/relevantrule/irelevantrule.h"
#include "domainmodule/relevantrule/rulecomposite.h"
#include "domainmodule/relevantrule/rulecompositeptr.h"
#include "domainmodule/relevantrule/mainwarehousepropertyremapperinterceptor.h"
#include "domainmodule/relevantrule/mainwarehousepropertyremapperinterceptorptr.h"

#include "domainmodule/relevantrule/admissionpurchaseprognosis.h"
#include "domainmodule/relevantrule/batch.h"
#include "domainmodule/relevantrule/binlocationrange.h"
#include "domainmodule/relevantrule/blockedarticle.h"
#include "domainmodule/relevantrule/centralpurchaseblockedarticle.h"
#include "domainmodule/relevantrule/consignment.h"
#include "domainmodule/relevantrule/cool.h"
#include "domainmodule/relevantrule/creationdate.h"
#include "domainmodule/relevantrule/dangerous.h"
#include "domainmodule/relevantrule/exclusionpurchaseprognosis.h"
#include "domainmodule/relevantrule/expensive.h"
#include "domainmodule/relevantrule/fixmainwarehouselisting.h"
#include "domainmodule/relevantrule/hazardoussubstance.h"
#include "domainmodule/relevantrule/narcotic.h"
#include "domainmodule/relevantrule/nationalarticle.h"
#include "domainmodule/relevantrule/outoftradearticle.h"
#include "domainmodule/relevantrule/registrable.h"
#include "domainmodule/relevantrule/seasoncategory.h"
#include "domainmodule/relevantrule/specialarticletype.h"
#include "domainmodule/relevantrule/withoutactivebinlocation.h"
#include "domainmodule/relevantrule/underdeliveryquota.h"
#include "domainmodule/relevantrule/regionalarticle.h"
#include "domainmodule/relevantrule/admissionoptionartrwe.h"
#include "domainmodule/relevantrule/admissionconsidergroups.h"

#include "domainmodule/mainwarehousearticlesrelevantcalculator_properties_definitions.h"

#include "exceptions/norulefoundexception.h"
#include "exceptions/missingdataexception.h"

#include "loggerpool/mainwarehousearticlesrelevantcalculator_loggerpool.h"
#include <libutil/util.h>
#include <libbasardbaspect_accessorpropertytable.h>
#include <libbasardbaspect_accessorpropertytable_yiterator.h>

#include <boost/make_shared.hpp>

namespace mainwarehousearticlesrelevantcalculator
{
namespace componentManager
{
    MainwarehouseArticlesRelevantRuleFactory::MainwarehouseArticlesRelevantRuleFactory()
    {
    }

    MainwarehouseArticlesRelevantRuleFactory::~MainwarehouseArticlesRelevantRuleFactory()
    {
    }

    void MainwarehouseArticlesRelevantRuleFactory::injectAssignmentParameterCollection( domMod::assignmentParameter::IAssignmentParameterCollectionPtr param )
    {
        m_AssignmentParameterCollection = param;
    }

    domMod::assignmentParameter::IAssignmentParameterCollectionPtr MainwarehouseArticlesRelevantRuleFactory::getAssignmentParameterCollection() const
    {
        CHECK_INSTANCE_EXCEPTION( m_AssignmentParameterCollection.get() );
        return m_AssignmentParameterCollection;
    }

    void MainwarehouseArticlesRelevantRuleFactory::injectMainwarehouseFinder( domMod::mainwarehouse::IMainwarehouseFinderPtr finder )
    {
        m_MainwarehouseFinder = finder;
    }

    basar::Int16 MainwarehouseArticlesRelevantRuleFactory::getMainwarehouseBranchNo( basar::Int16 branchNo ) const
    {
        CHECK_INSTANCE_EXCEPTION( m_MainwarehouseFinder.get() );
        m_MainwarehouseFinder->findByBranchNo( branchNo );
        return m_MainwarehouseFinder->getMainwarehouseBranch();
    }

    void MainwarehouseArticlesRelevantRuleFactory::injectStorageLocationSlotCheckerGetter( componentManager::IStorageLocationSlotCheckerGetterPtr storLocCheckerGetter )
    {
        m_StorageLocationSlotCheckerGetter = storLocCheckerGetter;
    }

    domMod::storageLocation::IStorageLocationSlotCheckerPtr MainwarehouseArticlesRelevantRuleFactory::getStorageLocationSlotCheckerByBranch( basar::Int16 branchNo ) const
    {
        CHECK_INSTANCE_EXCEPTION( m_StorageLocationSlotCheckerGetter.get() );
        
        domMod::storageLocation::IStorageLocationSlotCheckerPtr storageLocationSlotChecker = m_StorageLocationSlotCheckerGetter->getStorageLocationSlotChecker();
        storageLocationSlotChecker->findByBranchNo( branchNo );
        return storageLocationSlotChecker;
    }

    void MainwarehouseArticlesRelevantRuleFactory::loadAssignmentParameters( basar::Int16 branchNo )
    {
        METHODNAME_DEF( MainwarehouseArticlesRelevantRuleFactory, loadAssignmentParameters );

		getAssignmentParameterCollection()->findByBranchNo( branchNo );

        if( getAssignmentParameterCollection()->isEmpty() )
        {
            basar::VarString msg = "No rules found for either satellite or mainwarehouse!";
            throw libutil::exceptions::MissingDataException( basar::ExceptInfo( fun, msg, __FILE__, __LINE__ ) );
        }
    }
    
    MainwarehouseArticlesRelevantRuleFactory::RuleDescriptionCollection MainwarehouseArticlesRelevantRuleFactory::getPrecedenceOrderedRuleDesc() const
    {
        using domMod::relevantRule::RuleDescription;
        RuleDescriptionCollection ruleDescColl;
        ruleDescColl.reserve( RuleDescription::END_OF_ENUM );

        // add rules in order of precedence
        ruleDescColl.push_back( RuleDescription::FIX_MAINWAREHOUSE_LISTING     ); // must be first rule as it states relevant=true, independent if any other exclusion criteria would match!
        ruleDescColl.push_back( RuleDescription::NATIONALARTICLE               );
        ruleDescColl.push_back( RuleDescription::WITHOUT_ACTIVE_BINLOCATION    );
        ruleDescColl.push_back( RuleDescription::BINLOCATIONRANGE              );
        ruleDescColl.push_back( RuleDescription::CREATION_DATE                 );
        ruleDescColl.push_back( RuleDescription::OUTOFTRADEARTICLE             );
        ruleDescColl.push_back( RuleDescription::BATCH                         );
        ruleDescColl.push_back( RuleDescription::BLOCKEDARTICLE                );
        ruleDescColl.push_back( RuleDescription::CENTRALPURCHASEBLOCKEDARTICLE );
        ruleDescColl.push_back( RuleDescription::CONSIGNMENT                   );
        ruleDescColl.push_back( RuleDescription::COOL                          );
        ruleDescColl.push_back( RuleDescription::DANGEROUS                     );
        ruleDescColl.push_back( RuleDescription::EXPENSIVE                     );
        ruleDescColl.push_back( RuleDescription::HAZARDOUSSUBSTANCE            );
        ruleDescColl.push_back( RuleDescription::NARCOTIC                      );
        ruleDescColl.push_back( RuleDescription::REGISTRABLE                   );
        ruleDescColl.push_back( RuleDescription::SEASONCATEGORY                );
        ruleDescColl.push_back( RuleDescription::SPECIALARTICLETYPE            );
		ruleDescColl.push_back( RuleDescription::UNDERDELIVERYQUOTA			   );
		ruleDescColl.push_back( RuleDescription::REGIONALARTICLE			   );
        ruleDescColl.push_back( RuleDescription::EXCLUSION_PURCHASE_PROGNOSIS  );
        ruleDescColl.push_back( RuleDescription::ADMISSION_OPTION_ARTRWE	   );
        ruleDescColl.push_back( RuleDescription::ADMISSION_PURCHASE_PROGNOSIS  );
		ruleDescColl.push_back( RuleDescription::ADMISSION_CONSIDER_GROUPS     ); // admission rules must be last rules as it states relevant=true, if all other exclusion criteria are false AND saleability prognosis matches

        return ruleDescColl;
    }

    domMod::relevantRule::IRelevantRulePtr MainwarehouseArticlesRelevantRuleFactory::createRule( const basar::db::aspect::AccessorPropertyTable_YIterator yit ) const
    {
        METHODNAME_DEF( MainwarehouseArticlesRelevantRuleFactory, createRule );
        using namespace domMod::relevantRule;

        const RuleDescription ruleDesc = RuleDescription::fromString( yit.getString( properties::CONTEXT_NAME ) );
        switch( ruleDesc )
        {
        case RuleDescription::ADMISSION_PURCHASE_PROGNOSIS:
            return boost::make_shared< AdmissionPurchasePrognosis >( yit.getInt32( properties::INT_INTERVAL_START ),
                                                                     yit.getInt32( properties::INT_INTERVAL_END ) );
        case RuleDescription::EXCLUSION_PURCHASE_PROGNOSIS:
            return boost::make_shared< ExclusionPurchasePrognosis >( yit.getInt32( properties::INT_INTERVAL_START ),
                                                                     yit.getInt32( properties::INT_INTERVAL_END ) );
        case RuleDescription::CREATION_DATE:
            return boost::make_shared< CreationDate >( yit.getInt32( properties::COMPARE_VALUE_INT ) );
        case RuleDescription::WITHOUT_ACTIVE_BINLOCATION:
            return boost::make_shared< WithoutActiveBinLocation >( getStorageLocationSlotCheckerByBranch( yit.getInt16( properties::BRANCH_NO ) ) );
        case RuleDescription::NARCOTIC:
            return boost::make_shared< Narcotic >();
        case RuleDescription::FIX_MAINWAREHOUSE_LISTING:
            return boost::make_shared< FixMainWarehouseListing >();
        case RuleDescription::CONSIGNMENT:
            return boost::make_shared< Consignment >();
        case RuleDescription::DANGEROUS:
            return boost::make_shared< Dangerous >();
        case RuleDescription::EXPENSIVE:
            return boost::make_shared< Expensive >( yit.getDecimal( properties::COMPARE_VALUE_DEC ) );
        case RuleDescription::BATCH:
            return boost::make_shared< Batch >();
        case RuleDescription::COOL:
            return boost::make_shared< Cool >( yit.getInt32( properties::COMPARE_VALUE_INT ) );
        case RuleDescription::REGISTRABLE:
            return boost::make_shared< Registrable >();
        case RuleDescription::BINLOCATIONRANGE:
            return boost::make_shared< BinLocationRange >( BinLocationRange::StringInterval( yit.getString( properties::STRING_INTERVAL_START ), 
                                                                                             yit.getString( properties::STRING_INTERVAL_END ) ) );
        case RuleDescription::SEASONCATEGORY:
            return boost::make_shared< SeasonCategory >( yit.getString( properties::COMPARE_VALUE_STR ) );
        case RuleDescription::SPECIALARTICLETYPE:
            return boost::make_shared< SpecialArticleType >();
        case RuleDescription::HAZARDOUSSUBSTANCE:
            return boost::make_shared< HazardousSubstance >();
        case RuleDescription::BLOCKEDARTICLE:
            return boost::make_shared< BlockedArticle >();
        case RuleDescription::OUTOFTRADEARTICLE:
            return boost::make_shared< OutOfTradeArticle >( yit.getInt32( properties::COMPARE_VALUE_INT ) );
        case RuleDescription::NATIONALARTICLE:
            return boost::make_shared< NationalArticle >( yit.getInt32( properties::COMPARE_VALUE_INT ) );
        case RuleDescription::CENTRALPURCHASEBLOCKEDARTICLE:
            return boost::make_shared< CentralPurchaseBlockedArticle >();
		case RuleDescription::REGIONALARTICLE:
			return boost::make_shared< RegionalArticle >();
		case RuleDescription::UNDERDELIVERYQUOTA:
			return boost::make_shared< UnderDeliveryQuota >(yit.getInt32(properties::COMPARE_VALUE_INT));
		case RuleDescription::ADMISSION_OPTION_ARTRWE:
			return boost::make_shared< AdmissionOptionArtrwe >();
        case RuleDescription::ADMISSION_CONSIDER_GROUPS:
            return boost::make_shared< AdmissionConsiderGroups >();

        default:
            throw exceptions::NoRuleFoundException( basar::ExceptInfo( fun, ">" + ruleDesc.toString() + "< rule is unknown!", __FILE__, __LINE__ ) );
        }
    }

    domMod::relevantRule::IRelevantRulePtr MainwarehouseArticlesRelevantRuleFactory::create( basar::Int16 branchNo )
    {
        METHODNAME_DEF( MainwarehouseArticlesRelevantRuleFactory, create );
        using domMod::relevantRule::RuleDescription;
        const basar::Int16 mainwarehouseBranchNo = getMainwarehouseBranchNo( branchNo );

        loadAssignmentParameters( branchNo );

        domMod::relevantRule::RuleCompositePtr ruleComposite = boost::make_shared< domMod::relevantRule::RuleComposite >();
        RuleDescriptionCollection              ruleDescColl  = getPrecedenceOrderedRuleDesc();
        for( RuleDescriptionCollection::const_iterator it = ruleDescColl.begin(); it != ruleDescColl.end(); ++it )
        {
            try
            {
                basar::db::aspect::AccessorPropertyTable_YIterator yit = getAssignmentParameterCollection()->getFirstParameterByName( it->toString() );
                if( ! yit.isEnd() )
                {
                    basar::Int32 ruleID = yit.getInt32( properties::RULEID );
                    for( ; ! yit.isEnd() && yit.getInt32( properties::RULEID ) == ruleID; ++yit ) // process this rule and further rules of same kind (same id) if any
                    {
                        domMod::relevantRule::IRelevantRulePtr rule = createRule( yit );
						switch( rule->getDescription() )
                        {
                            // these are the rules, which are based on branch article master data, so isRelevant- check has to take the correct comparsion branch values from artikelf!
							case RuleDescription::WITHOUT_ACTIVE_BINLOCATION:
                            case RuleDescription::BINLOCATIONRANGE:
                            {
                                if( yit.getInt16( properties::BRANCH_NO ) == mainwarehouseBranchNo ) // is mainwarehouse rule?
                                {
                                    // add interceptor in between
                                    rule = boost::make_shared< domMod::relevantRule::MainwarehousePropertyRemapperInterceptor >( rule );
                                }
                            } // fall through
                            default:
                            {
                                ruleComposite->addRule( rule );
                            }
                        }
                    }
                }
            }
            catch( exceptions::NoRuleFoundException& e )
            {
                BLOG_WARN( LoggerPool::getLoggerMainwarehouseArticlesRelevantCalculator(), e.reason() );
            }
        }
        
        return ruleComposite;
    }
}// end namespace componentManager
}// end namespace mainwarehousearticlesrelevantcalculator
