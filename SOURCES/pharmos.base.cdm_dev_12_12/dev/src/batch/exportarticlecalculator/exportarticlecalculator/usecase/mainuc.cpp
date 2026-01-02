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

#include "componentmanager/exportarticlecalculatorapplcompmgr.h"
#include "loggerpool/exportarticlecalculator_loggerpool.h"
#include "domainmodule/iexportarticledm.h"
#include "domainmodule/iexportexclusionparameterdm.h"
#include "domainmodule/exportarticlecalculator_property_definitions.h"
#include "domainmodule/exportarticledm_definitions.h"

#include <libutil/util.h>

#include <infrastructure/mail/imailalert.h>

//-------------------------------------------------------------------------------------------------//
// namespace sections
//-------------------------------------------------------------------------------------------------//
namespace exportarticlecalculator
{
    namespace useCase
    {
        //-------------------------------------------------------------------------------------------------//
        // macro for registrating and deregistrating EventHandlers!
        //-------------------------------------------------------------------------------------------------//

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        MainUC::MainUC()
		: m_Logger( exportarticlecalculator::LoggerPool::getLoggerUseCases() )
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
        void MainUC::injectUseCaseGetter( exportarticlecalculator::componentManager::IUseCaseGetterPtr useCaseGetter )
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
		exportarticlecalculator::componentManager::IUseCaseGetterPtr MainUC::getUseCaseGetter()
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
		void MainUC::injectExportExclusionParameterDM( domMod::exportexclusionparameter::IExportExclusionParameterDMPtr exportExclsuionParameterDM )
		{
			METHODNAME_DEF( MainUC, injectExportExclusionParameterDM )
			BLOG_TRACE_METHOD( m_Logger, fun );

			m_ExportExclusionParameterDM = exportExclsuionParameterDM;
		}

		//-------------------------------------------------------------------------------------------------//
		void MainUC::injectExportArticleDM( domMod::exportarticle::IExportArticleDMPtr exportArticleDM )
		{
			METHODNAME_DEF( MainUC, injectExportArticleDM )
			BLOG_TRACE_METHOD( m_Logger, fun );

			m_ExportArticleDM = exportArticleDM;
		}

		//-------------------------------------------------------------------------------------------------//
		domMod::exportexclusionparameter::IExportExclusionParameterDMPtr MainUC::getExportExclusionParameterDM()
		{
			CHECK_INSTANCE_EXCEPTION( m_ExportExclusionParameterDM.get() );
			return m_ExportExclusionParameterDM;
		}

		//-------------------------------------------------------------------------------------------------//
		domMod::exportarticle::IExportArticleDMPtr	 MainUC::getExportArticleDM()
		{
			CHECK_INSTANCE_EXCEPTION( m_ExportArticleDM.get() );
			return m_ExportArticleDM;
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void MainUC::logExclusionParameter()
        {
            METHODNAME_DEF( MainUC, run )
            BLOG_TRACE_METHOD( m_Logger, fun );

			basar::db::aspect::AccessorPropertyTable_YIterator  yitParam = getExportExclusionParameterDM()->get().begin();
			
			std::stringstream ss;

			while (false == yitParam.isEnd())
			{
				
				if (yitParam.getInt16(properties::ACTIVATION_FLAG) == exportarticlecalculator::domMod::exportarticle::FLAG_ON)
				{
					ss << "\nexport exclusion rule <" << yitParam.getInt16(properties::RULE_ID) << ">: compare value <" << yitParam.getString(properties::COMPARE_START).c_str() << ">";

					if (false == yitParam.getString(properties::COMPARE_END).empty())
						ss << " - <" << yitParam.getString(properties::COMPARE_END).c_str() << ">";
				}
				
				++yitParam;
			}

			BLOG_INFO(m_Logger, ss.str());
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		bool MainUC::checkForExportExclusion(basar::VarString articleVal, basar::db::aspect::AccessorPropertyTable_YIterator yitParam)
		{
			std::stringstream ss;

			if (false == yitParam.getString(properties::COMPARE_END).empty()) // check range
			{
				if (articleVal >= yitParam.getString(properties::COMPARE_START) && articleVal <= yitParam.getString(properties::COMPARE_END))
				{
					ss	<< "export excluded due to rule <" << yitParam.getInt16(properties::RULE_ID) << ">: article value <" << articleVal.c_str()
						<< "> is between <" << yitParam.getString(properties::COMPARE_START).c_str() << "> - <" << yitParam.getString(properties::COMPARE_END).c_str() << ">.";
					BLOG_DEBUG(m_Logger, ss.str());
					return true;
				}
			}
			else // check single value
			{
				if (articleVal == yitParam.getString(properties::COMPARE_START))
				{
					ss	<< "export excluded due to rule <" << yitParam.getInt16(properties::RULE_ID) << ">: article value <" << articleVal.c_str()
						<< "> is equal <" << yitParam.getString(properties::COMPARE_START).c_str() << ">.";
					BLOG_DEBUG(m_Logger, ss.str());
					return true;
				}
			}
			return false;
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		bool MainUC::mapAndCheckRuleIdVsArticleVal(	basar::db::aspect::AccessorPropertyTable_YIterator yitParam )
		{
			basar::VarString articleVal;
			basar::VarString atcCode;

			switch(yitParam.getInt16(properties::RULE_ID))
			{
			case exportarticlecalculator::domMod::NARCOTICS:
				articleVal = getExportArticleDM()->getArticleData().getString(properties::NARCOTIC_FLAG);
				break;

			case exportarticlecalculator::domMod::UN_NO:
				articleVal = getExportArticleDM()->getArticleData().getString(properties::UN_NO);
				break;

			case exportarticlecalculator::domMod::NOTIFIABLE:
				articleVal = getExportArticleDM()->getArticleData().getString(properties::NOTIFIABLE_FLAG);
				break;

			case exportarticlecalculator::domMod::EXPLOSION:
				articleVal.itos(getExportArticleDM()->getArticleData().getInt16(properties::EXPLOSION_FLAG));
				break;

			case exportarticlecalculator::domMod::PSYCHOTROPIC:
				articleVal = getExportArticleDM()->getArticleData().getString(properties::PSYCHOTROPIC_FLAG);
				break;

			case exportarticlecalculator::domMod::ANIMAL_MEDICINE:
				articleVal = getExportArticleDM()->getArticleData().getString(properties::ANIMAL_MEDICINE_FLAG);
				break;
				
			case exportarticlecalculator::domMod::ATC_CODE:
				articleVal = getExportArticleDM()->getArticleData().getString(properties::ATC_CODE);
				break;
			
			case exportarticlecalculator::domMod::NARCOTIC_SUBSTANCE:
				articleVal.itos(getExportArticleDM()->getArticleData().getInt16(properties::NARCOTIC_SUBSTANCE_FLAG));
				break;
			
			case exportarticlecalculator::domMod::DISTRIBUTION_RESTR:
				articleVal = getExportArticleDM()->getArticleData().getString(properties::DISTRIBUTION_BINDING_MODE);
				break;

			case exportarticlecalculator::domMod::DISTRIBUTION_IFA:
				articleVal = getExportArticleDM()->getArticleData().getString(properties::DISTRIBUTION_BINDING_IFA);
				break;

			case exportarticlecalculator::domMod::INTERNAL_ARTICLE:
				articleVal.itos(getExportArticleDM()->getArticleData().getInt32(properties::PRISMAE_NO));
				break;

			case exportarticlecalculator::domMod::EXPORT_BLOCK:
				articleVal.itos(getExportArticleDM()->getArticleData().getInt16(properties::EXPORT_BLOCK_FLAG));
				break;

			case exportarticlecalculator::domMod::OUTSALE:
				articleVal.itos(getExportArticleDM()->getArticleData().getInt32(properties::OUTSALE_DATE));
				break;

			case exportarticlecalculator::domMod::EXPIRY:
				articleVal.itos(getExportArticleDM()->getArticleData().getInt32(properties::EXPIRY_DATE));
				break;

			case exportarticlecalculator::domMod::BIOZID:
				articleVal = getExportArticleDM()->getArticleData().getString(properties::BIOZID_FLAG);
				break;

			case exportarticlecalculator::domMod::ARTICLE_LOCK:
				articleVal = getExportArticleDM()->getArticleData().getString(properties::ARTICLE_LOCKED_FLAG);
				break;

			case exportarticlecalculator::domMod::STORAGE_LOCATION:
				articleVal = getExportArticleDM()->getArticleData().getString(properties::STORAGE_LOCATION);
				break;

			case exportarticlecalculator::domMod::ACTIVE_ARTICLE:
				articleVal = getExportArticleDM()->getArticleData().getString(properties::ACTIVE_ARTICLE_FLAG);
				break;

			case exportarticlecalculator::domMod::COOL_ARTICLE:
				articleVal = getExportArticleDM()->getArticleData().getString(properties::COOL_ARTICLE_MODE);
				break;

			case exportarticlecalculator::domMod::HAZARDOUS_OLD:
				articleVal.itos(getExportArticleDM()->getArticleData().getInt16(properties::HAZARDOUS_SUBSTANCE_OLD));
				break;

			case exportarticlecalculator::domMod::HAZARDOUS_NEW:
				articleVal.itos(getExportArticleDM()->getArticleData().getInt16(properties::HAZARDOUS_SUBSTANCE_NEW));
				break;

			// special treatment !!!  --> Arzneimittel sind nur ausgeschlossen, wenn sie keinen ATC-Code haben UND kein Homöopathikum UND kein Anthroposophikum sind
			case exportarticlecalculator::domMod::MEDICINE:
				atcCode = getExportArticleDM()->getArticleData().getString(properties::ATC_CODE);
				
				return	atcCode.empty() && 
						(articleVal = getExportArticleDM()->getArticleData().getString(properties::HOMEOPATHY_FLAG))	 != "1" && 
						(articleVal = getExportArticleDM()->getArticleData().getString(properties::ANTHROPOSOPHIC_FLAG)) != "1" && 
						checkForExportExclusion( getExportArticleDM()->getArticleData().getString(properties::MEDICINE_FLAG), yitParam);
				
			default:
				// rule not mapped to any article value = no exclusion!
				std::stringstream ss;
				ss	<< "rule <" << yitParam.getInt16(properties::RULE_ID) << "> NOT mapped to any article value = no exclusion!";
				BLOG_DEBUG(m_Logger, ss.str());
				return false;
			}	

			return checkForExportExclusion(articleVal, yitParam);
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
				
				getExportExclusionParameterDM()->find();
				logExclusionParameter();
				
				if (getExportExclusionParameterDM()->get().begin().isEnd())
				{
					BLOG_WARN( m_Logger, " !!! --- no exclusion parameter found at all --- !!! " );
					return;
				}				
				
				// Schleife über alle Artikel eines VZ´s aus artikelf
				BLOG_INFO( m_Logger, "-------- LOOPING all articles ------------" );
				
				bool isExportExcluded;
				basar::db::aspect::AccessorPropertyTable_YIterator  yitParam;
				getExportArticleDM()->find(); // Lesen aller notwendigen Artikel- Eigenschaften
				
				while (getExportArticleDM()->next())
				{
					isExportExcluded = true;
					yitParam = getExportExclusionParameterDM()->get().begin();

					while (false == yitParam.isEnd())
					{
						if (yitParam.getInt16(properties::ACTIVATION_FLAG) != domMod::exportarticle::FLAG_ON)
						{
							++yitParam;
							continue;
						}

						isExportExcluded = mapAndCheckRuleIdVsArticleVal(yitParam);

						if (isExportExcluded)
							break; // no need to go on for this article			

						++yitParam;
					}

					// Schreiben exportpermissionflag (bei Änderung) + Log (prepStmt)
					getExportArticleDM()->save(getExportArticleDM()->getArticleData().getInt32(properties::ARTICLE_NO), isExportExcluded);

					++counter;

#ifndef NDEBUG
					if (counter >= 1000000) // only thousand articles for testing
						break;
#endif
				}

				// ALLE Artikel kennzeichnen, deren Stammdaten geändert wurden
				BLOG_INFO( m_Logger, "-------- MARKING article master data changes ------------" );
				getExportArticleDM()->markChangedArticles();

				std::stringstream ss;
				ss << "< " << counter << " > articles checked for export permission.";
				BLOG_INFO( m_Logger, ss.str() );

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
				body << "ERROR while calculating export articles" << std::endl;
			else
			{
				body << "export articles calculated SUCCESSFULLY" << std::endl;

				std::stringstream ss;
				ss << "< " << getExportArticleDM()->getCounterUpdate() << " > export permissons updated / changed." << std::endl;
				ss << "< " << getExportArticleDM()->getCounterInsert() << " > new export articles inserted." << std::endl;
				ss << "< " << getExportArticleDM()->getCounterUnchanged() << " > export permissions remained unchanged." << std::endl;
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
				subject << "Error - EXPORT ARTICLE CALCULATOR for COUNTRY <" << getExportExclusionParameterDM()->getCountry().c_str() << ">, in BRANCH <" << getExportExclusionParameterDM()->getBranchNo() << ">" << std::endl;
			else
				subject << "EXPORT ARTICLE CALCULATOR succeeded for COUNTRY <" << getExportExclusionParameterDM()->getCountry().c_str() << ">, in BRANCH <" << getExportExclusionParameterDM()->getBranchNo() << ">" << std::endl;
			
			getMailAlert()->send(subject.str(), body.str());
		}
    } // namespace usecase
} // namespace ibtrelevantcalculator
