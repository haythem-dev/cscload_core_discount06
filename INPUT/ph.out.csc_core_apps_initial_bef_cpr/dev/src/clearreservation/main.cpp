/***************************************************************************************************************************/
#ifdef WIN32
#include <windows.h>
#endif
#include <csignal>
#include <pxsess.hpp>
#include <pxtaskcl.hpp>
#include <pxbranch.hpp>
#include <pxartbas.hpp>
#include <pxcstbas.hpp>
#include <pxcuststockreserved.hpp>
#include <pxstockbooking.hpp>
#include <logger/loggerpool.h>
#include <libbasarcmnutil_cmdline.h>
#ifndef WIN32
#include "gitversioninfo.h"
#endif

/***************************************************************************************************************************/

bool STOP_PROGRAM = false;

const char* PROGRAM="clearreserve"; // max 15 characters because of task control!!!

/***************************************************************************************************************************/

extern "C"
{
	extern const char versioninfo[];
}

void OnTermination(int /*signum*/)
{
	STOP_PROGRAM = true;
}

/***************************************************************************************************************************/

void writeTaskControl(pxSession* session, short branchno)
{
	session->nDBBeginTransaction();
	nString	prog(PROGRAM);				  // Programname
	nTime now;
	pxTaskControl tc(session, branchno, prog);
	tc.TaskControl(now);
	if (!tc.IsGoodState())
	{
		session->nDBRollBack();
		BLOG_ERROR(libcsc::LoggerPool::getLoggerSession(), tc.ErrorMsg());
	}
	else
	{
		session->nDBCommit();
	}
}

/***************************************************************************************************************************/

int	main(int argc, char	**argv)
{
	basar::cmnutil::CmdLineTokenizer args;
	args.setCmdLine(argc, argv);

#ifndef WIN32
	if (args.isParam("-version"))
	{
		std::cout << versioninfo << std::endl;
		std::cout << GitVersionInfo::instance() << std::endl;
		exit( 0 );
	}		
#endif

	if (argc != 3)
	{
		BLOG_ERROR(libcsc::LoggerPool::getLoggerSession(), "wrong arguments!");
		return -1;
	}
	short branchno = static_cast<short>(atoi(argv[2]));
	
	std::signal(SIGTERM, OnTermination);

	std::string iniFileName;
	iniFileName = getenv("INI_PATH");
	iniFileName += "/clearreservation.ini";
	
	std::stringstream s;
	s << "opening session with " << iniFileName << ", branchno " << branchno;
	BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), s.str());

	pxSession session(iniFileName, branchno);
	if (!session.IsGoodState())
	{
		BLOG_ERROR(libcsc::LoggerPool::getLoggerSession(), session.ErrorMsg());
		return -1;
	}
	session.OpenDBConnection();
	if (!session.IsGoodState())
	{
		BLOG_ERROR(libcsc::LoggerPool::getLoggerSession(), session.ErrorMsg());
		return -1;
	}

	while (!STOP_PROGRAM)
	{
		writeTaskControl(&session, branchno);

		basar::DateTime now = basar::DateTime::getCurrent();
		pxCustStockReservedList reservationList(&session);
		reservationList.SelectOldReservations(branchno, now);

		pxCustStockReservedListIter iter(reservationList);    // define iterator
		pxCustStockReserved* custStockReserved;
		while (NULL != (custStockReserved = (pxCustStockReserved*)++iter)) // browse list
		{
			session.nDBBeginTransaction();
			pxCustBase customer(&session, branchno, custStockReserved->CustomerNo());
			if (!customer.IsGoodState())
			{
				BLOG_ERROR(libcsc::LoggerPool::getLoggerSession(), customer.ErrorMsg());
				continue;
			}
			
			pxArtBase* article = pxArtBase::CreateArticle(&session, custStockReserved->ArticleNo(), branchno);
			if (!article->IsGoodState())
			{
				BLOG_ERROR(libcsc::LoggerPool::getLoggerSession(), article->Error().ErrorMsg());
				delete article;
				continue;
			}
			session.getStockBooking()->CancelReservationForInfoOrder(*article, customer, custStockReserved->ReservedQty());
			if (session.getStockBooking()->IsGoodState())
			{
				session.nDBCommit();
			}
			else
			{
				session.nDBRollBack();
				BLOG_ERROR(libcsc::LoggerPool::getLoggerSession(), session.getStockBooking()->ErrorMsg());
			}
			delete article;
			
			if (STOP_PROGRAM)
			{
				break;
			}
		}

		if (!STOP_PROGRAM)
		{
#ifdef WIN32
			Sleep(30*1000L);
#else
			sleep(30);
#endif
		}
	}
	return 0;
}
