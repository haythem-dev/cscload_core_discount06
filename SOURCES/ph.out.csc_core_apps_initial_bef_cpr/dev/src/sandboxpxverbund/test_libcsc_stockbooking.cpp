#include <UnitTest++/UnitTest++.h>
#include "FixtureBase.h"
#include <stockbooking/componentmanager/stockbookingcomponentmanager.h>
#include <stockbooking/bulkrangeselector/ibulkrangeselectorptr.h>
#include <stockbooking/bulkrangeselector/bulkrangeselector.h>
#include <stockbooking/longtermlack/longtermlackrepository.h>
#include <stockbooking/reservation/reservationrepository.h>
#include <stockbooking/reservation/articlereservation.h>
#include <stockbooking/reservation/customerstockreserved.h>

using namespace libcsc::stockbooking;

class StockbookingFixtureBase : public FixtureBase
{
public:
    short branchno;
    int customerno;

    StockbookingFixtureBase(const short branchno, const int customerno)
        : FixtureBase(branchno), branchno(branchno), customerno(customerno)
    {
        // Setup: Initialize shared resources
    }

    StockBookingComponentManagerPtr getStockbookingComponentManager()
    {
        pxOrderTransmit* xmit = _session.get();
        if (xmit == NULL)
        {
            std::cout << "Exception: Session is not initialized." << std::endl;
            throw;
        }
        return xmit->getStockBookingComponentManager();
    }
};

class StockbookingFixture : public StockbookingFixtureBase
{
public:
    StockbookingFixture() : StockbookingFixtureBase(5, 1436) {}
};

SUITE(Stockbooking)
{
    TEST_FIXTURE(StockbookingFixture, TestBulkRangeAvailability)
    {
        IBulkRangeSelectorPtr selector = getStockbookingComponentManager()->getBulkRangeSelector();

        std::vector<std::string> availableArticles;
        selector->bulkRangeAvailability(5, "10000", "20000", availableArticles);

        CHECK(!availableArticles.empty());
    }

    TEST_FIXTURE(StockbookingFixture, TestBulkRangeStock)
    {
        IBulkRangeSelectorPtr selector = getStockbookingComponentManager()->getBulkRangeSelector();

        std::vector<ReturnArticles> availableArticles;
        selector->bulkRangeStock(5, "10000", "20000", availableArticles, true);

        CHECK(!availableArticles.empty());
    }

    TEST_FIXTURE(StockbookingFixture, TestLongTermLack)
    {
        // Mock longtermlack entry
        _session.doSQL("DELETE FROM longtermlack WHERE articleno = -1;");
        _session.doSQL("INSERT INTO longtermlack (articleno, messagecode, enabled) VALUES (-1, 0, 1);");

        bool isLongTermLack = getStockbookingComponentManager()->getLongTermLackChecker()->isLongTermLack(-1);

        CHECK(isLongTermLack);

        getStockbookingComponentManager()->getLongTermLackDeleter()->deleteLongTermLack(-1);
        isLongTermLack = getStockbookingComponentManager()->getLongTermLackChecker()->isLongTermLack(-1);

        CHECK(!isLongTermLack);
    }

    TEST_FIXTURE(StockbookingFixture, TestArticleReservation)
    {
        const short branchno = 5;
        const int articleno = -1;

        IReservationRepositoryPtr mgr = getStockbookingComponentManager()->getReservationRepository(_session.get());

        // Prepare test data
        std::stringstream ss;
        ss << "DELETE FROM articlereservation WHERE branchno = " << branchno << " AND articleno = " << articleno << ";";
        _session.doSQL(ss.str());

        // Insert
        int maxQty = 10;
        const IArticleReservationPtr articleReservationIns = ArticleReservationPtr(new ArticleReservation());
        articleReservationIns->setBranchNo(branchno);
        articleReservationIns->setPharmacyGroupId("ooo");
        articleReservationIns->setArticleNo(articleno);
        articleReservationIns->setReservType(1);
        articleReservationIns->setMaxQty(maxQty);
        articleReservationIns->setReservedQty(1);
        articleReservationIns->setReservePct(1);

        mgr->saveArticleReservation(articleReservationIns);

        IArticleReservationCollectionPtr articleReservations = mgr->findArticleReservation(branchno, articleno);
        IArticleReservationCollection::iterator iter = articleReservations->begin();

        CHECK((*iter)->getMaxQty() == maxQty);

        // Update
        maxQty = 8;
        const IArticleReservationPtr articleReservationUpd = ArticleReservationPtr(new ArticleReservation());
        articleReservationUpd->setBranchNo(branchno);
        articleReservationUpd->setArticleNo(articleno);
        articleReservationUpd->setReservType(1);
        articleReservationUpd->setMaxQty(maxQty);
        articleReservationUpd->setReservedQty(2);
        articleReservationUpd->setReservePct(2);

        mgr->saveArticleReservation(articleReservationUpd);

        articleReservations = mgr->findArticleReservation(branchno, articleno);
        iter = articleReservations->begin();

        CHECK((*iter)->getMaxQty() == maxQty);

        // Delete
        mgr->deleteArticleReservation(articleReservationIns);

        articleReservations = mgr->findArticleReservation(branchno, articleno);

        CHECK(articleReservations->empty());
    }

    TEST_FIXTURE(StockbookingFixture, TestCustomerStockReserved)
    {
        const short branchno = 5;
        const int customerno = 1436;
        const int articleno = -1;
        const short reservType = 7;
        const int dateFrom = 20250101;
        const int kdAuftragNr = 112233;

        IReservationRepositoryPtr mgr = getStockbookingComponentManager()->getReservationRepository(_session.get());

        // Prepare test data
        std::stringstream ssDel;
        ssDel << "DELETE FROM cststockreserved WHERE branchno = " << branchno << " AND customerno = " << customerno << " AND articleno = " << articleno << ";";
        _session.doSQL(ssDel.str());

        std::stringstream ssIns;
        ssIns
            << "INSERT INTO cststockreserved (branchno, customerno, articleno, reservedqty, datefrom, timefrom, dateto, timeto, kdauftragnr, reservtype) "
            << "VALUES (" << branchno << ", " << customerno << ", " << articleno << ", 1, " << dateFrom << ", 180030, 0, 0, " << kdAuftragNr << ", " << reservType << ");";
        _session.doSQL(ssIns.str());

        // Update
        const int reservedQty = 2;
        const ICustomerStockReservedPtr customerStockReserved = CustomerStockReservedPtr(new CustomerStockReserved());
        customerStockReserved->setBranchNo(branchno);
        customerStockReserved->setCustomerNo(1436);
        customerStockReserved->setArticleNo(-1);
        customerStockReserved->setDateTo(1);
        customerStockReserved->setTimeTo(1);
        customerStockReserved->setReservedQty(2);
        customerStockReserved->setReservType(reservType);
        customerStockReserved->setDateFrom(dateFrom);
        customerStockReserved->setKdAuftragNr(kdAuftragNr);

        mgr->saveCustomerStockReserved(customerStockReserved);

        ICustomerStockReservedCollectionPtr customerStockReservations = mgr->findCustomerStockReserved(branchno, articleno);
        const ICustomerStockReservedCollection::iterator iter = customerStockReservations->begin();

        CHECK((*iter)->getReservedQty() == reservedQty);

        // Delete
        mgr->deleteCustomerStockReserved(customerStockReserved);

        customerStockReservations = mgr->findCustomerStockReserved(branchno, articleno);

        CHECK(customerStockReservations->empty());
    }
}
