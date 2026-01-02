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

#include "componentmanager/fmdrelevantcalculatorapplcompmgr.h"
#include "loggerpool/fmdrelevantcalculator_loggerpool.h"
#include "domainmodule/ifmdrelevantdm.h"
#include "domainmodule/ifmddeterminationparameterdm.h"
#include "domainmodule/fmdrelevantcalculator_property_definitions.h"
#include "domainmodule/fmdrelevantdm_definitions.h"

#include <libutil/util.h>

#include <libutil/irunnable.h>
#include <libutil/exception.h>

#include <infrastructure/mail/imailalert.h>

#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>

//-------------------------------------------------------------------------------------------------//
// namespace sections
//-------------------------------------------------------------------------------------------------//
namespace fmdrelevantcalculator
{
    namespace useCase
    {
        //-------------------------------------------------------------------------------------------------//
        // macro for registrating and deregistrating EventHandlers!
        //-------------------------------------------------------------------------------------------------//

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        MainUC::MainUC()
		: m_Logger( fmdrelevantcalculator::LoggerPool::getLoggerUseCases() ), m_isRezeptpflActive(false)
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
        void MainUC::injectUseCaseGetter( fmdrelevantcalculator::componentManager::IUseCaseGetterPtr useCaseGetter )
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
		fmdrelevantcalculator::componentManager::IUseCaseGetterPtr MainUC::getUseCaseGetter()
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
		void MainUC::injectFmdDeterminationParameterDM( domMod::fmddeterminationparameter::IFmdDeterminationParameterDMPtr fmdDeterminationParameterDM )
		{
			METHODNAME_DEF( MainUC, injectFmdDeterminationParameterDM )
			BLOG_TRACE_METHOD( m_Logger, fun );

			m_FmdDeterminationParameterDM = fmdDeterminationParameterDM;
		}

		//-------------------------------------------------------------------------------------------------//
		void MainUC::injectFmdRelevantDM( domMod::fmdarticle::IFmdRelevantDMPtr fmdRelevantDM )
		{
			METHODNAME_DEF( MainUC, injectFmdRelevantDM )
			BLOG_TRACE_METHOD( m_Logger, fun );

			m_FmdRelevantDM = fmdRelevantDM;
		}

		//-------------------------------------------------------------------------------------------------//
		domMod::fmddeterminationparameter::IFmdDeterminationParameterDMPtr MainUC::getFmdDeterminationParameterDM()
		{
			CHECK_INSTANCE_EXCEPTION( m_FmdDeterminationParameterDM.get() );
			return m_FmdDeterminationParameterDM;
		}

		//-------------------------------------------------------------------------------------------------//
		domMod::fmdarticle::IFmdRelevantDMPtr	 MainUC::getFmdArticleDM()
		{
			CHECK_INSTANCE_EXCEPTION( m_FmdRelevantDM.get() );
			return m_FmdRelevantDM;
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void MainUC::logDeterminationParameter()
        {
            METHODNAME_DEF( MainUC, run )
            BLOG_TRACE_METHOD( m_Logger, fun );

			basar::db::aspect::AccessorPropertyTable_YIterator  yitParam = getFmdDeterminationParameterDM()->get().begin();
			
			std::stringstream ss;

			while (false == yitParam.isEnd())
			{
				
				if (yitParam.getInt16(properties::ACTIVATION_FLAG) == fmdrelevantcalculator::domMod::fmdarticle::FLAG_ON)
				{
					ss << "\nfmd determination rule <" << yitParam.getInt16(properties::RULE_ID) << ">: compare value <" << yitParam.getString(properties::COMPARE_START).c_str() << ">";

					if (false == yitParam.getString(properties::COMPARE_END).empty())
						ss << " - <" << yitParam.getString(properties::COMPARE_END).c_str() << ">";

					if (yitParam.getInt16(properties::RULE_ID) == domMod::RULE4)
						m_isRezeptpflActive = true;
				}
				
				++yitParam;
			}

			BLOG_INFO(m_Logger, ss.str());
		}

		void MainUC::CheckCompareStartValueIsNotNull(basar::VarString compareStartVal, basar::Int16 ruleId)
		{
			if (compareStartVal.empty())
			{
				std::stringstream ssError;
				ssError << "Rule " << ruleId << " is not correctly configured. comparestartvalue is empty.";
				BLOG_DEBUG(m_Logger, ssError.str());
				throw;
			}
		}

		bool MainUC::CheckCaseIfa( basar::db::aspect::AccessorPropertyTable_YIterator rulesIterator )
		{
			// Rule 1
			if (getFmdArticleDM()->getArticleData().getInt32(properties::IFA_FMD_VAL) < 0)
			{
				m_isIfaOrDcArticle = false;
				return false;
			}
			else
			{
				m_isIfaOrDcArticle = true;
			}
	
			if (getFmdArticleDM()->getArticleData().getInt32(properties::IFA_FMD_VAL) >= rulesIterator.getString(properties::COMPARE_START).stoi() && 
				getFmdArticleDM()->getArticleData().getInt32(properties::IFA_FMD_VAL) <= rulesIterator.getString(properties::COMPARE_END).stoi())
			{
				std::stringstream ss;
				ss << "fmd relevant due to rule <" << rulesIterator.getInt16(properties::RULE_ID) << ">: IFA A11VERIHOC <" << getFmdArticleDM()->getArticleData().getInt32(properties::IFA_FMD_VAL)
				   << "> is between <" << rulesIterator.getString(properties::COMPARE_START).c_str() << "> - <" 
				   << rulesIterator.getString(properties::COMPARE_END).c_str() << ">.";
				BLOG_DEBUG(m_Logger, ss.str());

				return true;
			}
			else
				return false;
		}

		bool MainUC::CheckCaseDc(basar::db::aspect::AccessorPropertyTable_YIterator rulesIterator)
		{
			// Rule 2
			if (getFmdArticleDM()->getArticleData().getInt16(properties::DC_FMD_VAL) < 0)
			{
				m_isIfaOrDcArticle = false;
				return false;
			}
			else
			{
				m_isIfaOrDcArticle = true;
			}

			if (rulesIterator.getString(properties::COMPARE_START).stoi() == getFmdArticleDM()->getArticleData().getInt16(properties::DC_FMD_VAL))
			{
				std::stringstream ss;
				ss << "fmd relevant due to rule <" << rulesIterator.getInt16(properties::RULE_ID) 
				   << ">: dc value <" << getFmdArticleDM()->getArticleData().getInt16(properties::DC_FMD_VAL) << ">.";
				BLOG_DEBUG(m_Logger, ss.str());

				return true;
			}
			else
				return false;
		}
		
		bool MainUC::CheckCaseBlacklist(basar::db::aspect::AccessorPropertyTable_YIterator rulesIterator)
		{
			// Rule 3
			if (getFmdArticleDM()->getArticleData().getInt16(properties::EXCEPTION_TYPE) == rulesIterator.getString(properties::COMPARE_START).stoi())
			{
				std::stringstream ss;
				ss << "fmd relevant due to rule <" << rulesIterator.getInt16(properties::RULE_ID) 
				   << ">: blacklist <" << getFmdArticleDM()->getArticleData().getInt16(properties::EXCEPTION_TYPE) << ">.";
				BLOG_DEBUG(m_Logger, ss.str());
				return true;
			}
			else
				return false;
		}

		bool MainUC::CheckCaseWhitelist(basar::db::aspect::AccessorPropertyTable_YIterator rulesIterator)
		{
			// Rule 6
			if (getFmdArticleDM()->getArticleData().getInt16(properties::EXCEPTION_TYPE) == rulesIterator.getString(properties::COMPARE_START).stoi())
			{
				std::stringstream ss;
				ss << "fmd relevant due to rule <" << rulesIterator.getInt16(properties::RULE_ID) 
				   << ">: whitelist <" << getFmdArticleDM()->getArticleData().getInt16(properties::EXCEPTION_TYPE) << ">.";
				BLOG_DEBUG(m_Logger, ss.str());
				return true;
			}
			else
				return false;
		}

		bool MainUC::CheckCaseRezeptPfl(basar::db::aspect::AccessorPropertyTable_YIterator rulesIterator)
		{
			// Rule 4
			if (getFmdArticleDM()->getArticleData().getString(properties::REZEPTPFL) == rulesIterator.getString(properties::COMPARE_START))
			{
				std::stringstream ss;
				ss << "fmd relevant due to rule <" << rulesIterator.getInt16(properties::RULE_ID) 
				   << ">: RX <" << getFmdArticleDM()->getArticleData().getString(properties::REZEPTPFL) << ">.";
				BLOG_DEBUG(m_Logger, ss.str());
				return true;
			}
			else
				return false;
		}

		bool MainUC::CheckCaseArzneimittel(basar::db::aspect::AccessorPropertyTable_YIterator rulesIterator)
		{
			// Rule 5
			if (getFmdArticleDM()->getArticleData().getString(properties::ARZNEIMITTEL) == rulesIterator.getString(properties::COMPARE_START))
			{
				std::stringstream ss;
				ss << "fmd relevant due to rule <" << rulesIterator.getInt16(properties::RULE_ID) 
				   << ">: medicine <" << getFmdArticleDM()->getArticleData().getString(properties::ARZNEIMITTEL) << ">.";
				BLOG_DEBUG(m_Logger, ss.str());
				return true;
			}
			else
				return false;
		}
		
		bool MainUC::CheckCaseTierarznei(basar::db::aspect::AccessorPropertyTable_YIterator rulesIterator)
		{
			// Rule 7
			if (getFmdArticleDM()->getArticleData().getString(properties::TIERARZNEI) == rulesIterator.getString(properties::COMPARE_START))
			{
				std::stringstream ss;
				ss << "fmd exception due to rule <" << rulesIterator.getInt16(properties::RULE_ID) 
				   << ">: animal medicine <" << getFmdArticleDM()->getArticleData().getString(properties::TIERARZNEI) << ">.";
				BLOG_DEBUG(m_Logger, ss.str());
				return true;
			}
			else
				return false;
		}

		bool MainUC::CheckCaseHomoeopathikum(basar::db::aspect::AccessorPropertyTable_YIterator rulesIterator)
		{
			// Rule 8
			if (getFmdArticleDM()->getArticleData().getString(properties::HOMOEOPATHIKUM) == rulesIterator.getString(properties::COMPARE_START))
			{
				std::stringstream ss;
				ss << "fmd exception due to rule <" << rulesIterator.getInt16(properties::RULE_ID) 
				   << ">: homeopathic <" << getFmdArticleDM()->getArticleData().getString(properties::HOMOEOPATHIKUM) << ">.";
				BLOG_DEBUG(m_Logger, ss.str());
				return true;
			}
			else
				return false;
		}

		bool MainUC::CheckCaseMedizinischeGase(basar::db::aspect::AccessorPropertyTable_YIterator rulesIterator)
		{
			// Rule 9
			if (getFmdArticleDM()->getArticleData().getString(properties::MEDIZINISCHE_GASE) == rulesIterator.getString(properties::COMPARE_START))
			{
				std::stringstream ss;
				ss << "fmd exception due to rule <" << rulesIterator.getInt16(properties::RULE_ID) 
				   << ">: medical gas <" << getFmdArticleDM()->getArticleData().getString(properties::MEDIZINISCHE_GASE) << ">.";
				BLOG_DEBUG(m_Logger, ss.str());
				return true;
			}
			else
				return false;
		}

		bool MainUC::CheckCaseAtcCodeMatching(basar::db::aspect::AccessorPropertyTable_YIterator rulesIterator)
		{
			// Rule 10
			try 
			{
				if (boost::starts_with(getFmdArticleDM()->getArticleData().getString(properties::ATC_CODE), rulesIterator.getString(properties::COMPARE_START)))
				{
					std::stringstream ss;
					ss << "fmd exception due to rule <" << rulesIterator.getInt16(properties::RULE_ID) 
					   << ">: ATC code <" << getFmdArticleDM()->getArticleData().getString(properties::ATC_CODE) << ">.";
					BLOG_DEBUG(m_Logger, ss.str());
					return true;
				}
				else
					return false;
			}
			catch (boost::bad_lexical_cast e) 
			{
				std::stringstream ssError;
				ssError << "Error: Could not check atc code values. " << __FILE__ << " " << __LINE__;
				BLOG_WARN(m_Logger, ssError.str());
				return false;
			}
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		basar::Int16 MainUC::mapAndCheckRuleIdVsArticleVal(	basar::db::aspect::AccessorPropertyTable_YIterator rulesIterator )
		{
			basar::Int16 relDueToRule = -1;
			m_isIfaOrDcArticle = false;
			basar::Int16 fmdRelevantValueToSet = 0;
			
			while (false == rulesIterator.isEnd())
			{
				if (rulesIterator.getInt16(properties::ACTIVATION_FLAG) != domMod::fmdarticle::FLAG_ON)
				{
					++rulesIterator;
					continue;
				}
			
			// ---------------------------
			// FMD relevant
			// ---------------------------
				if (rulesIterator.getInt16(properties::RULE_ID) == domMod::RULE1) 
				{
					if (CheckCaseIfa(rulesIterator))
						relDueToRule = domMod::RULE1;

					++rulesIterator;
					continue;
				}

				if (rulesIterator.getInt16(properties::RULE_ID) == domMod::RULE2) 
				{
					if (CheckCaseDc(rulesIterator))
						relDueToRule = domMod::RULE2;

					++rulesIterator;
					continue;
				}

				if (rulesIterator.getInt16(properties::RULE_ID) == domMod::RULE3)
				{
					if ( CheckCaseBlacklist(rulesIterator))
					{
						relDueToRule = domMod::RULE3;
						break; // if article is on blacklist, nothing else has to be checked.
					}
					else
					{
						++rulesIterator;
						continue;
					}
				}

				if (rulesIterator.getInt16(properties::RULE_ID) == domMod::RULE4)
				{
					if( m_isIfaOrDcArticle == false && // check only, if relevance has not been detected yet
						CheckCaseRezeptPfl(rulesIterator))
						relDueToRule = domMod::RULE4;

					++rulesIterator;
					continue;
				}

				if (rulesIterator.getInt16(properties::RULE_ID) == domMod::RULE5 )
				{
					if ( m_isIfaOrDcArticle == false && // check only, if relevance has not been detected yet
						CheckCaseArzneimittel(rulesIterator) && 
						(m_isRezeptpflActive == false || relDueToRule == domMod::RULE4))
					{
						relDueToRule = domMod::RULE5;
					}
					else if (relDueToRule == domMod::RULE4)
					{
						relDueToRule = -1;
					}

					++rulesIterator;
					continue;
				}

			// ---------------------------
			// exceptions --> NOT FMD relevant
			// ---------------------------
				if (relDueToRule < 0)
					break; // no need to check for exceptions as article is not determined as FMD relevant at all

				if (rulesIterator.getInt16(properties::RULE_ID) == domMod::RULE6 )
				{
					if (CheckCaseWhitelist(rulesIterator))
						relDueToRule = -1;

					++rulesIterator;
					continue;
				}

				if (m_isIfaOrDcArticle == true)
					break; // don´t check for other exceptions if article was stated via IFA / Datacare
						
				if (rulesIterator.getInt16(properties::RULE_ID) == domMod::RULE7 )
				{
					if( CheckCaseTierarznei(rulesIterator))
						relDueToRule = -1;

					++rulesIterator;
					continue;
				}

				if (rulesIterator.getInt16(properties::RULE_ID) == domMod::RULE8 )
				{
					if (CheckCaseHomoeopathikum(rulesIterator))
						relDueToRule = -1;

					++rulesIterator;
					continue;
				}

				if (rulesIterator.getInt16(properties::RULE_ID) == domMod::RULE9 )
				{
					if (CheckCaseMedizinischeGase(rulesIterator))
						relDueToRule = -1;

					++rulesIterator;
					continue;
				}

				if (rulesIterator.getInt16(properties::RULE_ID) == domMod::RULE10 )
				{
					if (CheckCaseAtcCodeMatching(rulesIterator))
						relDueToRule = -1;

					++rulesIterator;
					continue;
				}

				if (rulesIterator.getInt16(properties::RULE_ID) > domMod::RULE10)
				{
					std::stringstream ss;
					ss	<< "rule <" << rulesIterator.getInt16(properties::RULE_ID) << "> NOT mapped to any article value!";
					BLOG_DEBUG(m_Logger, ss.str());
				}

				++rulesIterator;
			}

			if (relDueToRule == domMod::RULE3)
				fmdRelevantValueToSet = getFmdArticleDM()->getArticleData().getInt16(properties::EXCEPTION_TYPE);
			else if (relDueToRule > 0)
				fmdRelevantValueToSet = domMod::fmdarticle::FLAG_ON;
			else 
				fmdRelevantValueToSet = domMod::fmdarticle::FLAG_OFF;

			return fmdRelevantValueToSet;
		}
			
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void MainUC::run()
		{
			METHODNAME_DEF(MainUC, run)
				BLOG_TRACE_METHOD(m_Logger, fun);

			basar::cmnutil::CollBString	msgList;
			basar::Int32 counter = 0;

			try
			{
				// business logic starts here:
				// ---------------------------------------------------------

				// Lesen der relevanten Parameter
				BLOG_INFO(m_Logger, "-------- DETECTING FMD determination parameter ------------");

				getFmdDeterminationParameterDM()->find();
				logDeterminationParameter();

				if (getFmdDeterminationParameterDM()->get().begin().isEnd())
				{
					BLOG_WARN(m_Logger, " !!! --- no relevant parameter found at all --- !!! ");
					return;
				}

				// Schleife über alle Artikel eines VZ´s aus artikelf
				BLOG_INFO(m_Logger, "-------- LOOPING all articles ------------");

				getFmdArticleDM()->find(); // Lesen aller notwendigen Artikel- Eigenschaften

				while (getFmdArticleDM()->next())
				{
					BLOG_DEBUG(m_Logger, "**************"); // delimiter per article for better readability

					// Setze fmd_relevant flag
					getFmdArticleDM()->save(getFmdArticleDM()->getArticleData().getInt32(properties::ARTICLE_NO), mapAndCheckRuleIdVsArticleVal(getFmdDeterminationParameterDM()->get().begin()));

					++counter;
					
#ifndef NDEBUG
					if (counter >= 1000) // only thousand articles for testing
						break;
#endif
				}

				std::stringstream ss;
				ss << "< " << counter << " > articles checked for fmd relevance.";
				BLOG_INFO(m_Logger, ss.str());

				// Senden Info Mail
				msgList.push_back(ss.str());
				sendMail(msgList, false);
			}
			catch (basar::Exception& e)
			{
				BLOG_ERROR(m_Logger, e.what());

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
				body << "ERROR while calculating fmd articles" << std::endl;
			else
			{
				body << "fmd articles calculated SUCCESSFULLY" << std::endl;

				std::stringstream ss;
				ss << "< " << getFmdArticleDM()->getCounterUpdate() << " > fmd relevance flags updated / changed." << std::endl;
				ss << "< " << getFmdArticleDM()->getCounterUnchanged() << " > fmd relevance flags remained unchanged." << std::endl;
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
				subject << "Error - FMD ARTICLE CALCULATOR in COUNTRY <" << getFmdArticleDM()->getBranchNo() << ">" << std::endl;
			else
				subject << "FMD ARTICLE CALCULATOR succeeded in COUNTRY <" << getFmdArticleDM()->getBranchNo() << ">" << std::endl;
			
			getMailAlert()->send(subject.str(), body.str());
		}
    } // namespace usecase
} // namespace fmdrelevantcalculator
