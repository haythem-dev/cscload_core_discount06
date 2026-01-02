//-------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief
 *  \author
 *  \date
 */
//-------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include "mainuc.h"
#include "articlebasevalues.h"
#include "excludeparametervalues.h"
#include "branchrelevancevalues.h"

#include "componentmanager/ibtrelevantcalculatorapplcompmgr.h"
#include "loggerpool/ibtrelevantcalculator_loggerpool.h"
#include "domainmodule/iibtarticledm.h"
#include "domainmodule/iibtrelevantparameterdm.h"
#include "domainmodule/iibtrelevantbranchparameterdm.h"

#include <libutil/util.h>

#include <infrastructure/mail/imailalert.h>

//-------------------------------------------------------------------------------------------------//
// namespace sections
//-------------------------------------------------------------------------------------------------//
namespace ibtrelevantcalculator
{
    namespace useCase
    {
        //-------------------------------------------------------------------------------------------------//
        // macro for registrating and deregistrating EventHandlers!
        //-------------------------------------------------------------------------------------------------//

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        MainUC::MainUC()
		: m_Logger( ibtrelevantcalculator::LoggerPool::getLoggerUseCases() )
        {
            METHODNAME_DEF( MainUC, MainUC )
            BLOG_TRACE_METHOD( m_Logger, fun );
        }
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        MainUC::~MainUC()
        {
            METHODNAME_DEF( MainUC, ~MainUC )
            BLOG_TRACE_METHOD( m_Logger, fun );
        }

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void MainUC::injectUseCaseGetter( ibtrelevantcalculator::componentManager::IUseCaseGetterPtr useCaseGetter )
        {
            METHODNAME_DEF( MainUC, injectUseCaseGetter )
            BLOG_TRACE_METHOD( m_Logger, fun );

            m_UseCaseGetter = useCaseGetter;
        }

		//-------------------------------------------------------------------------------------------------//
		void MainUC::injectMailAlert( infrastructure::mail::IMailAlertPtr mailAlert )
		{
			METHODNAME_DEF( MainUC, injectMailAlert )
			BLOG_TRACE_METHOD( m_Logger, fun );

			m_MailAlert = mailAlert;
		}

        //-------------------------------------------------------------------------------------------------//
		ibtrelevantcalculator::componentManager::IUseCaseGetterPtr MainUC::getUseCaseGetter()
        {
            METHODNAME_DEF( MainUC, getUseCaseGetter )
            BLOG_TRACE_METHOD( m_Logger, fun );

            CHECK_INSTANCE_EXCEPTION( m_UseCaseGetter.get() );
            return m_UseCaseGetter;
        }

		//-------------------------------------------------------------------------------------------------//
		infrastructure::mail::IMailAlertPtr MainUC::getMailAlert()
		{
			CHECK_INSTANCE_EXCEPTION( m_MailAlert.get() );
			return m_MailAlert;
		}

		//-------------------------------------------------------------------------------------------------//
		void MainUC::injectIbtRelevantParameterDM( domMod::ibtRelevantParameter::IIbtRelevantParameterDMPtr ibtRelevantParameterDM )
		{
			METHODNAME_DEF( MainUC, injectIbtRelevantParameterDM )
			BLOG_TRACE_METHOD( m_Logger, fun );

			m_IbtRelevantParameterDM = ibtRelevantParameterDM;
		}

		//-------------------------------------------------------------------------------------------------//
		void MainUC::injectIbtArticleDM( domMod::ibtArticle::IIbtArticleDMPtr ibtArticleDM )
		{
			METHODNAME_DEF( MainUC, injectIbtArticleDM )
			BLOG_TRACE_METHOD( m_Logger, fun );

			m_IbtArticleDM = ibtArticleDM;
		}
		//-------------------------------------------------------------------------------------------------//
		void MainUC::injectIbtRelevantBranchParameterDM( domMod::ibtRelevantBranchParameter::IIbtRelevantBranchParameterDMPtr ibtRelevantBranchParameterDM )
		{
			METHODNAME_DEF( MainUC, injectIbtRelevantBranchParameterDM )
			BLOG_TRACE_METHOD( m_Logger, fun );

			m_IbtRelevantBranchParameterDM = ibtRelevantBranchParameterDM;
		}
		//-------------------------------------------------------------------------------------------------//
		domMod::ibtRelevantParameter::IIbtRelevantParameterDMPtr MainUC::getIbtRelevantParameterDM()
		{
			CHECK_INSTANCE_EXCEPTION( m_IbtRelevantParameterDM.get() );
			return m_IbtRelevantParameterDM;
		}
		//-------------------------------------------------------------------------------------------------//
		domMod::ibtRelevantBranchParameter::IIbtRelevantBranchParameterDMPtr MainUC::getIbtRelevantBranchParameterDM()
		{
			CHECK_INSTANCE_EXCEPTION( m_IbtRelevantBranchParameterDM.get() );
			return m_IbtRelevantBranchParameterDM;
		}

		//-------------------------------------------------------------------------------------------------//
		domMod::ibtArticle::IIbtArticleDMPtr MainUC::getIbtArticleDM()
		{
			CHECK_INSTANCE_EXCEPTION( m_IbtArticleDM.get() );
			return m_IbtArticleDM;
		}

		//-------------------------------------------------------------------------------------------------//
		basar::Int32	MainUC::calcAssortmentType(ArticleBaseValuesPtr articleData)
		{
			if (articleData->isPrivateGood()) 
				return 1;
			/*else if (Tierarznei) 
				return 2;*/
			else
				return 0;
		}
		/*
		//-------------------------------------------------------------------------------------------------//
		int	MainUC::checkisRegionalIbt(ArticleBaseValuesPtr articleData)
		{
            std::stringstream ss;
			ss << " checkisRegionalIbt ";
			if( articleData->getisFixedRegional() )
			{
				ss << " Article <" << articleData->getArticleNo() << "> is FixedRegional TRUE";
				BLOG_DEBUG(m_Logger, ss.str());
				return true;
			}
			else
			{
				ss << " Article <" << articleData->getArticleNo() << "> is FixedRegional FALSE";
				BLOG_DEBUG(m_Logger, ss.str());
				return false;
			}

		}
		*/
		//-------------------------------------------------------------------------------------------------//
		int	MainUC::checkisRegionalIbt(ArticleBaseValuesPtr articleData)
		{
            std::stringstream ss;
			ss << "checkisRegionalIbt for Article ";
            int fixReg = articleData->getisFixedRegional();
			if( fixReg == 1 )
			{
				ss << " <" << articleData->getArticleNo() << "> In table CIBT it is set to 1 from zdp so set relevanceflag to 1";
				BLOG_DEBUG(m_Logger, ss.str());
				return fixReg;
			}
            else if(fixReg == 0)
            {
				ss << " <" << articleData->getArticleNo() << "> In table CIBT it is set to 0 from zdp so set relevanceflag to 0";
				BLOG_DEBUG(m_Logger, ss.str());
				return fixReg;
            }
			else
			{
				ss << " <" << articleData->getArticleNo() << "> In table CIBT it is 2 means article does not have entry in cibt table so call the old Save";
				BLOG_DEBUG(m_Logger, ss.str());
				return 2;
			}

		}
		//-------------------------------------------------------------------------------------------------//
		bool	MainUC::calcIbtRelevance(ArticleBaseValuesPtr articleData, ExcludeParameterValuesPtr paramData)
		{
			// Errechnung Verbundfähigkeit (Parameter <-> Artikel- Eigenschaften)

			if (articleData->isPrivateGood()) 
			{
				BLOG_DEBUG(m_Logger, "article is IBT relevant due to PRIVATE GOOD = no exclusion !");
				return true; // wenn Privat-Sortiment, dann sind keine weiteren Checks mehr notwendig, da Artikel dann für KSC immer verbundfähig sein muss !
			}

			std::stringstream ss;
			ss << "article excluded from IBT (not relevant) due to ";

			if (paramData->isPseudoStorLocExcluded() && articleData->isPseudoStorLoc(paramData->getPseudoStorLoc()))
			{
				ss << "PSEUDO STORAGE LOCATION.";
				BLOG_DEBUG(m_Logger, ss.str());
				return false;
			}

			if (paramData->isNarcoticExcluded() && articleData->isNarcotic())
			{
				ss << "NARCOTIC.";
				BLOG_DEBUG(m_Logger, ss.str());
				return false;
			}

			if (paramData->isConsignmentExcluded() && articleData->isConsignment())
			{
				ss << "CONSIGNMENT.";
				BLOG_DEBUG(m_Logger, ss.str());
				return false;
			}

			if (paramData->isDangerousExcluded() && articleData->isDangerous())
			{
				ss << "DANGEROUS.";
				BLOG_DEBUG(m_Logger, ss.str());
				return false;
			}
			
			if (paramData->isExpensiveExcluded() && articleData->isExpensive(paramData->getExpensivePriceBorder()))
			{
				ss << "EXPENSIVE price <" << articleData->getPrice().toString(2).c_str() << ">";
				BLOG_DEBUG(m_Logger, ss.str());
				return false;
			}

			if (paramData->isCoolExcluded() && articleData->isCoolExcl(paramData->getCoolBorder()))
			{
				BLOG_DEBUG(m_Logger, "article not IBT relevant due to COOL.");
				return false;
			}

			if (paramData->isCentralLockExcluded() && articleData->isCentralExcl())
			{
				ss << "CENTRAL IBT LOCK.";
				BLOG_DEBUG(m_Logger, ss.str());
				return false;
			}
			
			if (paramData->isBatchExcluded() && articleData->isBatch())
			{
				ss << "BATCH.";
				BLOG_DEBUG(m_Logger, ss.str());
				return false;
			}

			if (paramData->isSpecialArticleExcluded() && articleData->isSpecialArticle())
			{
				ss << "SPECIAL ARTICLE TYPE.";
				BLOG_DEBUG(m_Logger, ss.str());
				return false;
			}

			if (paramData->isHazardGoodExcluded() && articleData->isHazardArticle())
			{
				ss << "HAZARDOUS SUBSTANCE.";
				BLOG_DEBUG(m_Logger, ss.str());
				return false;
			}

			if (paramData->isLockedArticleExcluded() && articleData->isLockedArticle())
			{
				ss << "CENTRAL ARTICLE LOCK.";
				BLOG_DEBUG(m_Logger, ss.str());
				return false;
			}

			if (paramData->isCentralPurchaseLockedArticleExcluded() && articleData->isCentralPurchaseLockedArticle())
			{
				ss << "CENTRAL PURCHASE ARTICLE LOCK.";
				BLOG_DEBUG(m_Logger, ss.str());
				return false;
			}
			

			if (paramData->isOutsaleExcluded() && articleData->isOutsaleExcl(paramData->getOutsaleBorder()))
			{
				ss << "OUTSALE date <" << articleData->getOutsaleDate() << ">";
				BLOG_DEBUG(m_Logger, ss.str());
				return false;
			}

			if (paramData->isStorLocAreaExcluded())
			{
				ExcludedStorLocAreaCollection exclStorLocs = paramData->getExclStorLocAreas();
				ExcludedStorLocAreaCollection::const_iterator it = exclStorLocs.begin();

				while (it != exclStorLocs.end())
				{
					if (articleData->isStorLocExcl(it->first, it->second))
					{
						ss << "STORAGE LOCATION <" << articleData->getStorLoc().c_str() << ">";
						BLOG_DEBUG(m_Logger, ss.str());
						return false;
					}

					++it;
				}
			}
			
			if (paramData->isSeasonGroupExcluded())
			{
				ExcludedSeasonGroupCollection exclSeasonGrps = paramData->getExclSeasonGroups();
				ExcludedSeasonGroupCollection::const_iterator it = exclSeasonGrps.begin();

				while (it != exclSeasonGrps.end())
				{
					if (articleData->isSeasonGroup(*it))
					{
						ss << "SEASON GROUP <" << it->c_str() << ">";
						BLOG_DEBUG(m_Logger, ss.str());
						return false;
					}

					++it;
				}
			}

			if (paramData->isAbcCategoryExcluded())
			{
				ExcludedAbcCategoryCollection exclAbcCats = paramData->getExclAbcCategories();
				ExcludedAbcCategoryCollection::const_iterator it = exclAbcCats.begin();

				while (it != exclAbcCats.end())
				{
					if (articleData->isAbcExcl(*it))
					{
						ss << "ABC CATEGORY <" << it->c_str() << ">";
						BLOG_DEBUG(m_Logger, ss.str());
						return false;
					}

					++it;
				}
			}

			if (paramData->isDemandNullExcluded() && articleData->isNoDemand( getIbtArticleDM()->findDemand(articleData->getArticleNo(), paramData->getWeeksForDemandNull()) ))
			{
				ss << "NO DEMAND.";
				BLOG_DEBUG(m_Logger, ss.str());
				return false;
			}

			//TH add checks for new exclusion parameters

			BLOG_DEBUG(m_Logger, "article is IBT relevant = no exclusion !");

			return true;
		}

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void MainUC::run()
        {
            METHODNAME_DEF( MainUC, run )
            BLOG_TRACE_METHOD( m_Logger, fun );

			basar::cmnutil::CollBString	msgList;
			basar::Int32 counter = 0;

            try
            {
                // business logic starts here:
				// ---------------------------------------------------------

				// Lesen der relevanten Parameter
				BLOG_INFO( m_Logger, "-------- DETECTING exclusion parameter ------------" );
				ibtrelevantcalculator::useCase::ExcludeParameterValuesPtr paramData = ibtrelevantcalculator::useCase::ExcludeParameterValuesPtr( new ibtrelevantcalculator::useCase::ExcludeParameterValues );

				ibtrelevantcalculator::useCase::BranchRelevanceValuePtr paramBrData = ibtrelevantcalculator::useCase::BranchRelevanceValuePtr( new ibtrelevantcalculator::useCase::BranchRelevanceValues );
				getIbtRelevantBranchParameterDM()->find();
				basar::db::aspect::AccessorPropertyTable_YIterator  yitBranchParam = getIbtRelevantBranchParameterDM()->get().begin();
				
				if (yitBranchParam.isEnd())
					BLOG_WARN( m_Logger, " !!! --- no Branch parameter set at all --- !!! " );
				basar::Int16 brYesNo = 0;
				while (false == yitBranchParam.isEnd())
				{
					BLOG_INFO( m_Logger, "-------- GetBranchParameterValue from puibtbrancharticlerelevanceparam ------------" );
					paramBrData->GetBranchParameterValue(yitBranchParam, getIbtRelevantBranchParameterDM()->getBranchNo() );
					brYesNo = paramBrData->getBranchValueYesNo();
					++yitBranchParam;
				}
				
				getIbtRelevantParameterDM()->find();
				basar::db::aspect::AccessorPropertyTable_YIterator  yitParam = getIbtRelevantParameterDM()->get().begin();

				if (yitParam.isEnd())
					BLOG_WARN( m_Logger, " !!! --- no exclusion parameter set at all --- !!! " );
								
				while (false == yitParam.isEnd())
				{
					// Schleife über alle Parameter-Rows + zuweisen zu einem Parameter- Objekt, das man später alles fragen kann
					paramData->addParameterRow(yitParam);
					++yitParam;
				}
				
				// Schleife über alle Artikel eines VZ´s aus artikelf
				BLOG_INFO( m_Logger, "-------- LOOPING all branch articles ------------" );
				ibtrelevantcalculator::useCase::ArticleBaseValuesPtr articleData = ibtrelevantcalculator::useCase::ArticleBaseValuesPtr( new ibtrelevantcalculator::useCase::ArticleBaseValues );
            
				getIbtArticleDM()->find(); // Lesen aller notwendigen Artikel- Eigenschaften
				
				while (getIbtArticleDM()->next())
				{
					// Zuweisen aller ResultSet- Spalten zu einem Artikel- Objekt ?
					articleData->fillFromDbResult(getIbtArticleDM()->getArticleData());
					if( brYesNo )
					{
						int ibt = checkisRegionalIbt(articleData);
						if ( ibt == 1)
						{
							BLOG_INFO( m_Logger, "**** brarticlerelevance is TRUE and cibt is 1 so set in puibtbrancharticleconfig RelevanceFlag to 1****" );
							getIbtArticleDM()->saveRelevanceFlag(articleData->getArticleNo(), calcAssortmentType(articleData), 1);
						}
						else if( ibt == 0)
						{
							BLOG_INFO( m_Logger, "**** brarticlerelevance is TRUE and cibt is 0 so set in puibtbrancharticleconfig RelevanceFlag to 0 ****" );
							getIbtArticleDM()->saveRelevanceFlag(articleData->getArticleNo(), calcAssortmentType(articleData), 0);
							BLOG_INFO( m_Logger, "$$$ brarticlerelevance is TRUE and call the Old Save $$$" );
							getIbtArticleDM()->save(articleData->getArticleNo(), calcIbtRelevance(articleData, paramData), calcAssortmentType(articleData));							
						}
						else //ibt == 2
						{
						// Schreiben ibtrelevantflag (bei Änderung) + Log (prepStmt)
							BLOG_INFO( m_Logger, "$$$ brarticlerelevance is True and no entry in CIBT so call old Save method $$$" );
							getIbtArticleDM()->save(articleData->getArticleNo(), calcIbtRelevance(articleData, paramData), calcAssortmentType(articleData));
						}
					}
					else
					{
					// Schreiben ibtrelevantflag (bei Änderung) + Log (prepStmt)
						BLOG_INFO( m_Logger, "$$$ brarticlerelevance is FALSE and calling old Save method $$$" );
						getIbtArticleDM()->save(articleData->getArticleNo(), calcIbtRelevance(articleData, paramData), calcAssortmentType(articleData));
					}
					/*
					if ( checkisRegionalIbt(articleData))
					{
						BLOG_INFO( m_Logger, "-------- Save RelevanceFlag ------------" );
						getIbtArticleDM()->saveRelevanceFlag(articleData->getArticleNo(), calcAssortmentType(articleData));
					}
					else
					{
					// Schreiben ibtrelevantflag (bei Änderung) + Log (prepStmt)
						BLOG_INFO( m_Logger, "--------General Save ------------" );
						getIbtArticleDM()->save(articleData->getArticleNo(), calcIbtRelevance(articleData, paramData), calcAssortmentType(articleData));
					}
					*/
					++counter;

#ifndef NDEBUG
					if (counter >= 1000) // only thousand articles for testing
						break;
#endif
				}

				std::stringstream ss;
				ss << "< " << counter << " > articles checked for IBT relevance.";
				BLOG_INFO( m_Logger, ss.str() );

				// löschen aller puibtbrancharticleconfig- Sätze, zu denen es keine artikelf.artikel_nr gibt ...
				BLOG_INFO( m_Logger, "-------- DELETING unknown branch articles ------------" );
				getIbtArticleDM()->deleteUnknownConfig();

				// Senden Info Mail
				msgList.push_back(ss.str());
				sendMail(msgList, false);
			}
            catch( basar::Exception& e )
            {
                BLOG_ERROR( m_Logger, e.what() );
				
				// Senden Error Mail
				msgList.push_back(e.what());
				sendMail(msgList);
            }
        }

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void MainUC::sendMail(basar::cmnutil::CollBString& msgList, const bool isError)
		{
			std::stringstream body;

			if (isError)
				body << "ERROR while calculating IBT relevance" << std::endl;
			else
			{
				body << "IBT relevances calculated SUCCESSFULLY" << std::endl;

				std::stringstream ss;
				ss << "< " << getIbtArticleDM()->getCounterUpdate() << " > relevance flags updated / changed." << std::endl;
				ss << "< " << getIbtArticleDM()->getCounterInsert() << " > new relevance flags inserted." << std::endl;
				ss << "< " << getIbtArticleDM()->getCounterUnchanged() << " > relevance flags remained unchanged." << std::endl;
				msgList.push_back(ss.str());
				BLOG_INFO( m_Logger, ss.str() );
			}

			body << std::endl;
			basar::cmnutil::CollBString::const_iterator it = msgList.begin();
			while (it != msgList.end())
			{
				body << (*it) << std::endl;
				++it;
			}

			std::stringstream subject;
			
			if (isError)
				subject << "Error - IBT RELEVANT CALCULATOR in BRANCH <" << getIbtRelevantParameterDM()->getBranchNo() << ">" << std::endl;
			else
				subject << "IBT RELEVANT CALCULATOR succeeded in BRANCH <" << getIbtRelevantParameterDM()->getBranchNo() << ">" << std::endl;
			
			getMailAlert()->send(subject.str(), body.str());
		}
    } // namespace usecase
} // namespace ibtrelevantcalculator
