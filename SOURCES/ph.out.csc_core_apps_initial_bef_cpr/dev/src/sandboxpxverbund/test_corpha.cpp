#include <UnitTest++/UnitTest++.h>
#include "SessionUtil.h"
#include <boost/lexical_cast.hpp>

extern bool pxGlobalDataBaseSort;

class CorphaFixture
{
public:
    short branchno;
	long customerno;
	long orderno;
    SessionUtil* session;

    CorphaFixture()
		: branchno(5), customerno(9674467), orderno(9999999), session(NULL)
    {
        // Setup: Initialize shared resources
        session = new SessionUtil(branchno);
        session->doSQL("DELETE FROM KDAUFTRAG WHERE KDAUFTRAGNR = " + boost::lexical_cast<std::string>(orderno));

        session->doSQL("INSERT INTO KDAUFTRAG (KDAUFTRAGNR, KDAUFTRAGSTAT, IDFNR, GERAETNAME, FILIALNR, VERTRIEBSZENTRUMNR, KDAUFTRAGART, KOART, BUCHART, SENDESTATUS) "
                       "VALUES (" + boost::lexical_cast<std::string>(orderno) + ", '0000100000000000', " + boost::lexical_cast<std::string>(customerno) + ", 'SANDBOX', " +
                                boost::lexical_cast<std::string>(branchno) + ", " + boost::lexical_cast<std::string>(branchno) + ", 'NO', '0', '0', 0);");
    }

    ~CorphaFixture()
    {
        // Teardown: Clean up resources
        session->doSQL("DELETE FROM KDAUFTRAG WHERE KDAUFTRAGNR = " + boost::lexical_cast<std::string>(orderno));
        delete session;
    }
};

SUITE(CorphaTests)
{
    TEST_FIXTURE(CorphaFixture, TestFindOrders2BeTransferred)
    {
        // Test finding orders to be transferred
        CHECK(session != NULL);
        CHECK(session->get() != NULL);
        CHECK(session->get()->IsGoodState());
        CHECK(session->get()->isGermany());

        pxOrderList orders(session->get());
        CHECK(orders.IsGoodState());
        CHECK_EQUAL(0UL, orders.Entries());

        pxGlobalDataBaseSort = true; // switch of CompareTo handling in ordbase.cpp in pxverbund, use sort by tourid from kauftrag.h in pxdb // pxGlobalDataBaseSort = global flag in pxverbund
        orders.SelectVSE(::pxOrder::cVSEnoTransmit, 50, // m_ApplConfiguration->getMaxSelectOrders()
            branchno, -1, // mode ALLORDERNUMBERS
            ::Order::EntryClosed, ::Order::cStateLast);
        pxGlobalDataBaseSort = false; // switch off pxGlobalDataBaseSort again
        CHECK(orders.IsGoodState());
        CHECK(orders.Entries() > 0UL);
    }

    TEST_FIXTURE(CorphaFixture, TestFinishWithoutTransfer)
    {
        // Test finishing an order without transfer
        session->get()->nDBBeginTransaction();
        pxOrder order(session->get(), orderno, cDBGET_FORUPDATE);
        CHECK(order.IsGoodState());
        order.OrderStatus(Order::Invoiceable);
        order.OrderStatus(Order::Invoiced);
        order.SendeStatus(pxOrder::cVSEok);
        order.VSEPut();
        CHECK(order.IsGoodState());
        session->get()->nDBCommit();

        // validate changes in database
        pxOrder order2(session->get(), orderno, cDBOPEN_READONLY);
        CHECK(order2.IsGoodState());
        CHECK_EQUAL(customerno, order2.IDFNr());
        CHECK_EQUAL(orderno, order2.KdAuftragNr());
        CHECK_EQUAL("NO",    order2.KdAuftragArt());
        CHECK_EQUAL(false,   order2.IsEntryInProgress());
        CHECK_EQUAL(false,   order2.IsUpdateInProgress());
        CHECK_EQUAL(false,   order2.IsEntryDeferred());
        CHECK_EQUAL(true,    order2.IsEntryClosed());
        CHECK_EQUAL(false,   order2.IsShipmentInProgress());
        CHECK_EQUAL(false,   order2.IsShipmentClosed());
        CHECK_EQUAL(true,    order2.IsInvoiceable());
        CHECK_EQUAL(true,    order2.IsInvoiced());
        CHECK_EQUAL(false,   order2.IsProtected());
        CHECK_EQUAL(false,   order2.IsCustomerService());
        CHECK_EQUAL(false,   order2.IsProblemClearance());
        CHECK_EQUAL(false,   order2.IsCallBack());
        CHECK_EQUAL(false,   order2.IsDCParallel());
        CHECK_EQUAL(false,   order2.IsConsolidation());
        CHECK_EQUAL(false,   order2.IsCancelled());
        CHECK_EQUAL(pxOrder::cVSEok, order2.SendeStatus());
    }

    TEST_FIXTURE(CorphaFixture, TestFinishTransfer)
    {
        // Test finishing an order transfer
        session->get()->nDBBeginTransaction();
        pxOrder order(session->get(), orderno, cDBGET_FORUPDATE);
        CHECK(order.IsGoodState());
        order.VSEAuftragNr(1234);
        order.OrderStatus(Order::ShipmentInProgress);
        order.OrderStatus(Order::ShipmentClosed);
        order.OrderStatus(Order::Invoiceable);
        order.OrderStatus(Order::Invoiced);
        order.SendeStatus(pxOrder::cVSEok);
        order.VSEPut();
        CHECK(order.IsGoodState());
        session->get()->nDBCommit();

        // validate changes in database
        pxOrder order2(session->get(), orderno, cDBOPEN_READONLY);
        CHECK(order2.IsGoodState());
        CHECK_EQUAL(customerno, order2.IDFNr());
        CHECK_EQUAL(orderno, order2.KdAuftragNr());
        CHECK_EQUAL("NO",    order2.KdAuftragArt());
        CHECK_EQUAL(false,   order2.IsEntryInProgress());
        CHECK_EQUAL(false,   order2.IsUpdateInProgress());
        CHECK_EQUAL(false,   order2.IsEntryDeferred());
        CHECK_EQUAL(true,    order2.IsEntryClosed());
        CHECK_EQUAL(true,    order2.IsShipmentInProgress());
        CHECK_EQUAL(true,    order2.IsShipmentClosed());
        CHECK_EQUAL(true,    order2.IsInvoiceable());
        CHECK_EQUAL(true,    order2.IsInvoiced());
        CHECK_EQUAL(false,   order2.IsProtected());
        CHECK_EQUAL(false,   order2.IsCustomerService());
        CHECK_EQUAL(false,   order2.IsProblemClearance());
        CHECK_EQUAL(false,   order2.IsCallBack());
        CHECK_EQUAL(false,   order2.IsDCParallel());
        CHECK_EQUAL(false,   order2.IsConsolidation());
        CHECK_EQUAL(false,   order2.IsCancelled());
        CHECK_EQUAL(pxOrder::cVSEok, order2.SendeStatus());
    }
}
