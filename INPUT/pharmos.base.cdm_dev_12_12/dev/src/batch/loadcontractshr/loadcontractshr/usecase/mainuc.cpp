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

#include "componentmanager/loadcontractshrapplcompmgr.h"
#include "loggerpool/loadcontractshr_loggerpool.h"
#include "domainmodule/iloadcontractshrdm.h"
#include "domainmodule/loadcontractshr_property_definitions.h"

#include <libutil/util.h>

#include <libutil/irunnable.h>
#include <libutil/exception.h>

#include <infrastructure/mail/imailalert.h>

#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp> 
#include <boost/date_time.hpp>
#include <boost/filesystem.hpp>

#include <fstream>
#include <iostream>

//-------------------------------------------------------------------------------------------------//
// namespace sections
//-------------------------------------------------------------------------------------------------//
namespace loadcontractshr
{
    namespace useCase
    {
        //-------------------------------------------------------------------------------------------------//
        // macro for registrating and deregistrating EventHandlers!
        //-------------------------------------------------------------------------------------------------//

        MainUC::MainUC()
		: m_Logger( loadcontractshr::LoggerPool::getLoggerUseCases() ), m_isRezeptpflActive(false)
        {
            METHODNAME_DEF( MainUC, MainUC )
            BLOG_TRACE_METHOD( m_Logger, fun );
        }

        MainUC::~MainUC()
        {
            METHODNAME_DEF( MainUC, ~MainUC )
            BLOG_TRACE_METHOD( m_Logger, fun );
        }

        void MainUC::injectUseCaseGetter( loadcontractshr::componentManager::IUseCaseGetterPtr useCaseGetter )
        {
            METHODNAME_DEF( MainUC, injectUseCaseGetter )
            BLOG_TRACE_METHOD( m_Logger, fun );

            m_UseCaseGetter = useCaseGetter;
        }

		void MainUC::injectMailAlert( infrastructure::mail::IMailAlertPtr mailAlert )
		{
			METHODNAME_DEF( MainUC, injectMailAlert )
			BLOG_TRACE_METHOD( m_Logger, fun );

			m_MailAlert = mailAlert;
		}

		loadcontractshr::componentManager::IUseCaseGetterPtr MainUC::getUseCaseGetter()
        {
            METHODNAME_DEF( MainUC, getUseCaseGetter )
            BLOG_TRACE_METHOD( m_Logger, fun );

            CHECK_INSTANCE_EXCEPTION( m_UseCaseGetter.get() );
            return m_UseCaseGetter;
        }

		infrastructure::mail::IMailAlertPtr MainUC::getMailAlert()
		{
			CHECK_INSTANCE_EXCEPTION( m_MailAlert.get() );
			return m_MailAlert;
		}

		void MainUC::injectLoadContractsHrDM( domMod::loadcontractshrdm::ILoadContractsHrDMPtr LoadContractsHrDM )
		{
			METHODNAME_DEF( MainUC, injectLoadContractsHrDM )
			BLOG_TRACE_METHOD( m_Logger, fun );

			m_LoadContractsHrDM = LoadContractsHrDM;
		}

		domMod::loadcontractshrdm::ILoadContractsHrDMPtr	 MainUC::getContractsLoaderDM()
		{
			CHECK_INSTANCE_EXCEPTION( m_LoadContractsHrDM.get() );
			return m_LoadContractsHrDM;
		}

		void MainUC::run()
		{
			METHODNAME_DEF(MainUC, run)
			BLOG_TRACE_METHOD(m_Logger, fun);
			basar::cmnutil::CollBString	msgList;

			try
			{
				BLOG_INFO(m_Logger, "-------- Loading data with contract numbers ------------");
				getContractsLoaderDM()->run();
				std::stringstream ss;
				BLOG_INFO(m_Logger, "-------- Finished loading data with contract numbers ------------");
				msgList.push_back(ss.str());
				sendMail(msgList, false);
				boost::posix_time::ptime timeLocal = boost::posix_time::second_clock::local_time();
				std::string dt = boost::posix_time::to_iso_extended_string(timeLocal);
				std::replace(dt.begin(), dt.end(), 'T', '_');
				std::replace(dt.begin(), dt.end(), ':', '-');
#ifndef _WIN32
				std::string path = "../log/loadcontractshr_" + dt + "/";
#else
				std::string path = "C:\\loadcontractshr\\log\\loadcontractshr_" + dt + "\\";
#endif 
				boost::filesystem::path dir(path.c_str());
				if (boost::filesystem::create_directory(dir))
				{
					// do nothing
				}

				if (getContractsLoaderDM()->getMode().compare("update") != 0)
				{
					writeResults(getContractsLoaderDM()->getResult(loadcontractshr::domMod::loadcontractshrdm::ILoadContractsHrDM::BADFORMAT), path + "BADFORMAT-" + dt);
					writeResults(getContractsLoaderDM()->getResult(loadcontractshr::domMod::loadcontractshrdm::ILoadContractsHrDM::OUTOFDATE), path + "OUTDATED_DATETO-" + dt);
					writeResults(getContractsLoaderDM()->getResult(loadcontractshr::domMod::loadcontractshrdm::ILoadContractsHrDM::MATCHING_EXISTS), path + "MATCHING_EXISTS-" + dt);
					writeResults(getContractsLoaderDM()->getResult(loadcontractshr::domMod::loadcontractshrdm::ILoadContractsHrDM::SIMILAR_EXISTS), path + "SIMILAR_WITH_ACTIVE_DATETO_EXISTS-" + dt);
					writeResults(getContractsLoaderDM()->getResult(loadcontractshr::domMod::loadcontractshrdm::ILoadContractsHrDM::INSERTED), path + "INSERTED-" + dt);
				}
				else
				{
					writeResults(getContractsLoaderDM()->getResult(loadcontractshr::domMod::loadcontractshrdm::ILoadContractsHrDM::BADFORMAT), path + "u_BADFORMAT-" + dt);
					writeResults(getContractsLoaderDM()->getResult(loadcontractshr::domMod::loadcontractshrdm::ILoadContractsHrDM::UPDATED), path + "u_UPDATED-" + dt);
					writeResults(getContractsLoaderDM()->getResult(loadcontractshr::domMod::loadcontractshrdm::ILoadContractsHrDM::NO_MATCHING_FOUND), path + "u_NO_MATCHING_FOUND-" + dt);
				}
			}
			catch (basar::Exception& e)
			{
				BLOG_ERROR(m_Logger, e.what());
				msgList.push_back(e.what());
				sendMail(msgList);
			}
		}

		void MainUC::writeResults(std::stringstream* ss, const std::string& loc)
		{
			std::ofstream myfile;
			myfile.open((loc + ".txt").c_str(), std::ios_base::trunc);
			myfile << (*ss).str();
			myfile.close();
		}

        void MainUC::sendMail(basar::cmnutil::CollBString& msgList, const bool isError)
		{
			std::stringstream body;

			if (isError)
				body << "ERROR while loading rebates with contract numbers" << std::endl;
			else
			{
				bool isInsertionMode = getContractsLoaderDM()->getMode().compare("update") != 0;
				if (isInsertionMode)
					body << "Rebates with contract numbers loaded" << std::endl;
				else
					body << "[MODE:UPDATE] Rebates with contract numbers updated" << std::endl;
				std::stringstream ss;
				ss << "< " << getContractsLoaderDM()->getCounter() << " > rebate records detected in the file." << std::endl;
				
				if (isInsertionMode)
					ss << "< " << getContractsLoaderDM()->getCounterRebatesAdded() << " > new rebate records with contract numbers were added (INSERTED)." << std::endl;		
				else
				    ss << "< " << getContractsLoaderDM()->getCounterRebatesUpdated() << " > new rebate records with contract numbers were updated (UPDATED)." << std::endl;
				
				ss << "< " << getContractsLoaderDM()->getCounterContractsAdded() << " > new contract numbers were found/added; previously not known to the system." << std::endl;
				ss << "< " << getContractsLoaderDM()->getCounterRebatesUnchanged() << (isInsertionMode ? " > ignored records with conditions that already exist (MATCHING_EXISTS)." : " > with no matching entries found for update (NO_MATCHING_FOUND).") << std::endl;

				if (isInsertionMode)
				{
					ss << "< " << getContractsLoaderDM()->getCounterRebatesUnchangedOutOfDate() << " > rejected records due to having an out of date 'dateto'-value (OUTOFDATE)." << std::endl;
					ss << "< " << getContractsLoaderDM()->getCounterRebatesUnchangedSimilar() << " > ignored records due to having an active 'dateto' in an existing similar record (SIMILAR_EXISTS)." << std::endl;
				}
				ss << "< " << getContractsLoaderDM()->getCounterBadFormat() << " > rejected records due to bad format (BADFORMAT)." << std::endl;
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
				subject << "Error - loading HR rebates with contracts from <" << getContractsLoaderDM()->getPath() << ">" << std::endl;
			else if (getContractsLoaderDM()->getMode().compare("update") != 0)
				subject << "load HR rebates with contracts from <" << getContractsLoaderDM()->getPath() << ">" << std::endl;
			else
				subject << "[[MODE:UPDATE]] update HR rebates with contracts from <" << getContractsLoaderDM()->getPath() << ">" << std::endl;
			
			getMailAlert()->send(subject.str(), body.str());
		}
    } // namespace usecase
} // namespace loadcontractshr
