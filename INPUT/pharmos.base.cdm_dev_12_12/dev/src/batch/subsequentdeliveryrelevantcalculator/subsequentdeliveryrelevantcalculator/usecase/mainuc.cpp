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

#include <list>
#include <sstream>
#include <string>

// basar
#include <libbasarcmnutil.h>

#include "componentmanager/subsequentdeliveryrelevantcalculatorapplcompmgr.h"
#include "loggerpool/subsequentdeliveryrelevantcalculator_loggerpool.h"

#include "CalculationRules.h"

//-------------------------------------------------------------------------------------------------//
// namespace sections
//-------------------------------------------------------------------------------------------------//
namespace subsequentdeliveryrelevantcalculator
{
	namespace useCase
	{
		//-------------------------------------------------------------------------------------------------//
		// macro for registrating and deregistrating EventHandlers!
		//-------------------------------------------------------------------------------------------------//

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		MainUC::MainUC()
			: m_Logger(subsequentdeliveryrelevantcalculator::LoggerPool::getLoggerUseCases())
		{
			METHODNAME_DEF(MainUC, MainUC)
			BLOG_TRACE_METHOD(m_Logger, fun);
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		MainUC::~MainUC()
		{
			METHODNAME_DEF(MainUC, ~MainUC)
			BLOG_TRACE_METHOD(m_Logger, fun);
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void MainUC::injectUseCaseGetter(subsequentdeliveryrelevantcalculator::componentManager::IUseCaseGetterPtr useCaseGetter)
		{
			METHODNAME_DEF(MainUC, injectUseCaseGetter)
			BLOG_TRACE_METHOD(m_Logger, fun);

			m_UseCaseGetter = useCaseGetter;
		}

		//-------------------------------------------------------------------------------------------------//
		subsequentdeliveryrelevantcalculator::componentManager::IUseCaseGetterPtr MainUC::getUseCaseGetter()
		{
			METHODNAME_DEF(MainUC, getUseCaseGetter)
			BLOG_TRACE_METHOD(m_Logger, fun);

			CHECK_INSTANCE_EXCEPTION(m_UseCaseGetter.get());
			return m_UseCaseGetter;
		}

		//-------------------------------------------------------------------------------------------------//
		void MainUC::injectArticleDM(domMod::article::ArticleDMPtr articleDM)
		{
			METHODNAME_DEF(MainUC, injectArticleDM)
			BLOG_TRACE_METHOD(m_Logger, fun);

			m_ArticleDM = articleDM;
		}

		void MainUC::injectDeliveryParamDM(domMod::deliveryparam::DeliveryParamDMPtr deliveryParamDM)
		{
			METHODNAME_DEF(MainUC, injectDeliveryParamDM)
				BLOG_TRACE_METHOD(m_Logger, fun);

			m_DeliveryParamDM = deliveryParamDM;
		}

		//-------------------------------------------------------------------------------------------------//
		void MainUC::injectSubsequentDeliveryConfigDM(domMod::subsequentdeliveryconfig::SubsequentDeliveryConfigDMPtr subsequentDeliveryConfigDM)
		{
			METHODNAME_DEF(MainUC, injectSubsequentDeliveryConfigDM)
			BLOG_TRACE_METHOD(m_Logger, fun);

			m_SubsequentDeliveryConfigDM = subsequentDeliveryConfigDM;
		}

		//-------------------------------------------------------------------------------------------------//
		domMod::article::ArticleDMPtr MainUC::getArticleDM()
		{
			CHECK_INSTANCE_EXCEPTION(m_ArticleDM.get());
			return m_ArticleDM;
		}

		//-------------------------------------------------------------------------------------------------//
		domMod::subsequentdeliveryconfig::SubsequentDeliveryConfigDMPtr MainUC::getSubsequentDeliveryConfigDM()
		{
			CHECK_INSTANCE_EXCEPTION(m_SubsequentDeliveryConfigDM.get());
			return m_SubsequentDeliveryConfigDM;
		}

		//-------------------------------------------------------------------------------------------------//
		domMod::deliveryparam::DeliveryParamDMPtr MainUC::getDeliveryParamDM()
		{
			CHECK_INSTANCE_EXCEPTION(m_DeliveryParamDM.get());
			return m_DeliveryParamDM;
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void MainUC::run()
		{
			try
			{
			METHODNAME_DEF(MainUC, run)
			BLOG_TRACE_METHOD(m_Logger, fun);

			// business logic starts here:
			// ---------------------------------------------------------

			BLOG_INFO(m_Logger, "-------- STARTING subsequentdeliveryrelevantcalculator processing ------------");
			{
				std::stringstream ss;
				ss << "processing branch " << getBranchNo();
				BLOG_INFO(m_Logger, ss.str());
			}
			std::cout << "subsequentdeliveryrelevantcalculator started - " << basar::DateTime() << std::endl;

			int ctrArticle = 0;
			int ctrUpdate = 0;
			int ctrInsert = 0;

			// read list of rules from DB (tables csubsequentdeliveryrule / csubsequentdeliveryparam)
				BLOG_DEBUG(m_Logger, "select csubsequentdeliveryparams for branch");
			basar::db::aspect::ExecuteResultInfo selectDPResult = getDeliveryParamDM()->selectDeliveryParams(getBranchNo());

				BLOG_DEBUG(m_Logger, "fill property table for csubsequentdeliveryparams");
			basar::db::aspect::AccessorPropertyTableRef selectedDPData = getDeliveryParamDM()->getDeliveryParamData();

			// initalize CalculationRules from subsequent delivery params
				BLOG_DEBUG(m_Logger, "initialize calculator rules");
			CalculationRules::initialize(selectedDPData);

				BLOG_DEBUG(m_Logger, "select all articles by branch");
				basar::db::aspect::ExecuteResultInfo selectResult = getArticleDM()->selectArticles(getBranchNo());

				BLOG_DEBUG(m_Logger, "fill property table from article selection");
				basar::db::aspect::AccessorPropertyTableRef selectedData = getArticleDM()->getArticleData();

				BLOG_DEBUG(m_Logger, "init property table to first entry");
				basar::db::aspect::AccessorPropertyTable_YIterator articleIterator = selectedData.begin();

			// initialize Subsequentdelivery State for all articles currently disables to 0
				BLOG_DEBUG(m_Logger, "initialize all existing current articles to subsequentdelivery state 0 / disabled (default)");
			basar::db::aspect::ExecuteResultInfo initResult =
				getSubsequentDeliveryConfigDM()->initSubsequentDeliveryConfig(getBranchNo());
			if (initResult.hasError())
			{
				std::stringstream ss;
					ss << "ERROR initializing all subsequentdelivery entries for branch: " << getBranchNo() <<
					  "| Error:" << initResult.getError();
				BLOG_ERROR(m_Logger, ss.str());
			}
			else
			{
				BLOG_DEBUG(m_Logger, "subsequentdelivery entries initialized");
			}

				BLOG_INFO(m_Logger, "start transaction for calculated update");
			getArticleDM()->beginTransaction();
			while (!articleIterator.isEnd())
			{
				int processingStatus = 0;
				basar::Int32 artNr = articleIterator.getInt32(domMod::article::ARTICLE_ARTICLENO);

				// check if any of our rules applies
					RuleResult rr = CalculationRules::ApplyRules(articleIterator, getCalcDate(), getCalcTime());
				basar::Int16 newSubsequentDelivery = rr.getSubsequentDelivery();
				basar::VarString newRuleName = rr.getRuleName();

				basar::Int16 currentSubsequentDelivery = articleIterator.getInt16(domMod::article::ARTICLE_SUBSEQUENTDELIVERY);
				// csubsequentdeliverybrancharticleconfig.lastchangeuser contains the name of the rule the caused
				// ther current subsequent delivery status
				basar::VarString currentRuleName = articleIterator.getString(domMod::article::ARTICLE_LASTCHANGEUSER);
				// if the subsequent delivery status changed or it stayed the same but a different rule matched
				if (newSubsequentDelivery != currentSubsequentDelivery || newRuleName != currentRuleName)
				{
					basar::Int16 branchNr = getBranchNo();
					if (currentSubsequentDelivery == -1)
					{
							basar::db::sql::ExecuteReturnInfo updateResult =
								getSubsequentDeliveryConfigDM()->updateSubsequentDeliveryConfig(branchNr, artNr, newSubsequentDelivery, newRuleName);
							if (updateResult.getAffectedRows() == 0)
							{
						basar::db::sql::ExecuteReturnInfo insertResult = 
							getSubsequentDeliveryConfigDM()->insertSubsequentDeliveryConfig(branchNr, artNr, newSubsequentDelivery, newRuleName);
						if (insertResult.hasError())
						{
							std::stringstream ss;
							ss << "ERROR record inserted: artNo: " << artNr <<
								", artBranch: " << articleIterator.getInt32(branchNr) << "| Error:" << insertResult.getError();
							BLOG_ERROR(m_Logger, ss.str());
						}
						else
						{
							BLOG_DEBUG(m_Logger, "record inserted");
							processingStatus = 1; // config entry inserted
							ctrInsert++;
						}
					}
					else
					{
								BLOG_DEBUG(m_Logger, "record updated");
								processingStatus = 2; // config entry updated
								ctrUpdate++;
							}
						}
						else
						{
						basar::db::sql::ExecuteReturnInfo updateResult = 
							getSubsequentDeliveryConfigDM()->updateSubsequentDeliveryConfig(branchNr, artNr, newSubsequentDelivery, newRuleName);
						
						if (updateResult.hasError())
						{
							std::stringstream ss;
							ss << "ERROR record updated: artNo: " << artNr <<
								", artBranch: " << branchNr << "| Error:" << updateResult.getError();
							BLOG_ERROR(m_Logger, ss.str());
						}
						else
						{
							BLOG_DEBUG(m_Logger, "record updated");
							processingStatus = 2; // config entry updated
							ctrUpdate++;
						}
					}
					if ((ctrInsert + ctrUpdate) % CalculationRules::RECCNT_BETWEEN_TRANSACT == 0)
					{
						getArticleDM()->commitTransaction();
						getArticleDM()->beginTransaction();
					}
				}
				else
				{
					// subsequent delivery status not changed --> nothing to to
				}

				// write log entry for each processed article
				std::stringstream ss;
				ss << artNr << "|" << newSubsequentDelivery << "|" << newRuleName << "|";
				if (processingStatus == 1)
				{
					ss << "insert";
				}
				else if (processingStatus == 2)
				{
					ss << "update";
				}
				else
				{
					ss << "no change";
				}
				BLOG_INFO(m_Logger, ss.str());

				ctrArticle++;
				articleIterator++;
			}
				BLOG_INFO(m_Logger, "commit calculated changes");
			getArticleDM()->commitTransaction();

			{
				std::stringstream ss;
				ss << "articles read: " << ctrArticle;
				BLOG_INFO(m_Logger, ss.str());
				std::cout << ss.str() << std::endl;
			}
			{
				std::stringstream ss;
				ss << "subsequent delivery config entries updated/inserted: " << ctrUpdate << "/" << ctrInsert;
				BLOG_INFO(m_Logger, ss.str());
				std::cout << ss.str() << std::endl;
			}

			std::cout << "subsequentdeliveryrelevantcalculator successfully ended - " << basar::DateTime() << std::endl;
			BLOG_INFO(m_Logger, "-------- FINISHED subsequentdeliveryrelevantcalculator processing ------------");
			}
			catch (std::exception &e)
			{
				std::stringstream ss;
				ss << "Exception caught: " << e.what();
				BLOG_ERROR(m_Logger, ss.str());
				throw e;
			}
		}
	} // namespace usecase
} // namespace subsequentdeliveryrelevantcalculator
