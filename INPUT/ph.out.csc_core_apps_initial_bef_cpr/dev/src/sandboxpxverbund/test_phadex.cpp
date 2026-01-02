#include <UnitTest++/UnitTest++.h>
#include "SessionUtil.h"
#include "document/componentmanager/documentcomponentmanager.h"
#include "document/documentprintinfo/documentprintinfoptr.h"
#include "document/documentprintinfo/documentprintinfo.h"
#include "document/documentprintinfo/documentprintinforepository.h"

//#include <blockedarticles/componentmanager/blockedarticlescomponentmanagerptr.h>
#include <blockedarticles/componentmanager/blockedarticlescomponentmanager.h>
#include "blockedarticles/blockedarticles.h"
#include "blockedarticles/blockedarticlesrepository.h"
//#include "blockedarticles/blockedarticlesrepositoryptr.h"


class PhadexFixture
{
public:
    short branchno;
	long customerno;
	basar::VarString documentno;
	basar::Int32 documentDate;

    long blockID;
    SessionUtil* session;

    PhadexFixture()
        : branchno(666), customerno(1234567), documentno("999999999"), documentDate(basar::Date::getCurrent().getDate()), blockID(77), session(NULL)
    {
        // Setup: Initialize shared resources
        session = new SessionUtil(branchno);
        std::stringstream sql;
        sql << "INSERT INTO rechner (filialnr, rechner_name, standort, pflege, datenbank_name, szentral, warehouse_datenbankname, inbound_datenbankname) "
            "VALUES(666, 'zdev21', 'TESTBURG', '0', 'ode21@" << session->getDatabaseServer() << "', '1', 'wde21@" << session->getDatabaseServer() <<
            "', 'ide21@" << session->getDatabaseServer() << "')";
        session->doSQL(sql.str());
		sql.str("");
        sql << "INSERT INTO wde21@" << session->getDatabaseServer() << ":blockedarticles (dkaspkey,blockid,articleno,branchno,quantity,bookingtype,creationtime,creationdate) "
            "VALUES ('666ABCDE',77,164,666,1,1,162656,20230510);";
        session->doSQL(sql.str());
    }

    ~PhadexFixture()
    {
		std::stringstream sql;
        session->doSQL("DELETE FROM rechner WHERE filialnr = 666;");
        session->doSQL("DELETE FROM documentprintinfo WHERE branchno = 666 AND customerno = 1234567 AND documentno = '999999999';");
		sql << "DELETE FROM wde21@" << session->getDatabaseServer() << ":blockedarticles WHERE branchno = 666 AND blockid = 77;";
        session->doSQL(sql.str());
        delete session;
    }
};



SUITE(PhadexTests)
{
    TEST_FIXTURE(PhadexFixture, TestDocumentPrintInfo)
    {
		libcsc::document::DocumentPrintInfoRepositoryPtr repo = session->get()->getDocumentComponentManager()->getDocumentPrintInfoRepository();

		libcsc::document::DocumentPrintInfoPtr foundDocPrintInfo =
			repo->findDocumentPrintInfo(branchno, customerno, Invoice, documentno, documentDate);

        CHECK(NULL == foundDocPrintInfo.get()); // not yet saved in database

		libcsc::document::DocumentPrintInfoPtr documentPrintInfo = repo->createEmptyDocumentPrintInfo();

		documentPrintInfo->setDocumentNo(documentno);
		documentPrintInfo->setBranchNo(branchno);
		documentPrintInfo->setCustomerNo(customerno);
		documentPrintInfo->setDocumentType(Invoice);
		documentPrintInfo->setDocumentDate(documentDate);

		repo->saveDocumentPrintInfo(documentPrintInfo);

        foundDocPrintInfo = repo->findDocumentPrintInfo(branchno, customerno, Invoice, documentno, documentDate);
        CHECK(NULL != foundDocPrintInfo.get());
		CHECK_EQUAL(branchno, foundDocPrintInfo->getBranchNo());
		CHECK_EQUAL(customerno, foundDocPrintInfo->getCustomerNo());
		CHECK_EQUAL(Invoice, foundDocPrintInfo->getDocumentType());
		CHECK_EQUAL(documentno, foundDocPrintInfo->getDocumentNo());
    }

    TEST_FIXTURE(PhadexFixture, TestBlockedArticles)
    {
        libcsc::blockedarticles::BlockedArticlesComponentManagerPtr comp = session->get()->getBlockedArticlesComponentManager();
        CHECK(NULL != comp.get());
        libcsc::blockedarticles::IBlockedArticlesRepositoryPtr repo = comp->getBlockedArticlesRepository();
        CHECK(NULL != repo.get());
        libcsc::blockedarticles::BlockedArticlesCollectionPtr coll = repo->findBlockedArticles(branchno, blockID);
        CHECK(NULL != coll.get());
        CHECK_EQUAL(1UL, coll->size());
        libcsc::blockedarticles::BlockedArticlesCollection::iterator it = coll->begin();
        CHECK(it != coll->end());

        while (it != coll->end())
        {
            CHECK_EQUAL(0, (*it)->getProcessedDate());
            CHECK_EQUAL(0, (*it)->getProcessedTime());
            (*it)->setProcessedDate(basar::cmnutil::DateTime::getCurrent().getDate());
            (*it)->setProcessedTime(basar::cmnutil::DateTime::getCurrent().getTime() / 1000);

            repo->saveBlockedArticle((*it));
            ++it;
        }


    }
}
