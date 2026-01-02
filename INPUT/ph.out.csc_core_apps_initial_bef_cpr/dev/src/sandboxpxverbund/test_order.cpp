#include <UnitTest++/UnitTest++.h>
#include "SessionUtil.h"
#include "pxorder.hpp"
#include "pxcstbas.hpp"

class OrderFixture
{
public:
    short branchno;
    long customerno;
    SessionUtil* session;
    pxOrder* order;

    OrderFixture()
        : branchno(33), customerno(19063), session(NULL), order(NULL)
    {
        // Setup: Initialize shared resources
        session = new SessionUtil(branchno);
    }

    ~OrderFixture()
    {
        // Teardown: Clean up resources
        delete session;
    }
};

static long orderno = 0;

SUITE(OrderTests)
{
    TEST_FIXTURE(OrderFixture, CreateOrder)
    {
        // Test creating a new order
        pxCustBase* customer = session->get()->CustomerId(customerno, branchno);
        CHECK(customer != NULL);
        CHECK(customer->IsGoodState());
        order = session->get()->SubOrderType("NO", "", 0);
        order->Bemerkungen("Test Order"); // Set remarks as an example
        CHECK(order->IsGoodState());
        orderno = order->KdAuftragNr();
        session->get()->SetNotCloseOrder();
        session->get()->End();
        CHECK(orderno > 0);
    }

    TEST_FIXTURE(OrderFixture, AddPositionsToOrder)
    {
        // Test reading an existing order
        order = new pxOrder(session->get(), orderno, cDBOPEN_READONLY);
        CHECK(order != NULL);
        CHECK(order->IsGoodState());

        CHECK_EQUAL(0, order->OpenOrder(cDBOPEN_INSERT));
        CHECK(order->IsGoodState());
		pxOrderItem* item1 = order->NewOrderItem_02(106, 5, 0, 0); // Example article number: 106
        CHECK(item1 != NULL);
        CHECK(item1->IsGoodState());

        pxOrderItem* item2 = order->NewOrderItem_02(3764531, 5, 0, 0); // Example article number: 3764531
        CHECK(item2 != NULL);
        CHECK(item2->IsGoodState());

        CHECK_EQUAL(0, order->Close(Order::LeaveAsIs, Order::cClose_Nohandle));
		CHECK(order->IsGoodState());
    }

    TEST_FIXTURE(OrderFixture, ReadOrder)
    {
        // Test reading an existing order
        order = new pxOrder(session->get(), orderno, cDBOPEN_READONLY);
        CHECK(order != NULL);
        CHECK(order->IsGoodState());

        CHECK_EQUAL(customerno, order->IDFNr());
        CHECK_EQUAL(orderno, order->KdAuftragNr());
        CHECK_EQUAL("NO", order->KdAuftragArt());

        nString bem = order->Bemerkungen();
        bem.Strip();
        CHECK_EQUAL("Test Order", bem);

        pxCustBase* customer = order->Customer();
        CHECK(customer != NULL);
        CHECK(customer->IsGoodState());
        CHECK_EQUAL(customerno, customer->IDFNr());
    }

    TEST_FIXTURE(OrderFixture, ReadOrderPositions)
    {
        // Test reading existing order positions
        order = new pxOrder(session->get(), orderno, cDBOPEN_READONLY);
        CHECK(order != NULL);
        CHECK(order->IsGoodState());

        pxOrderItemList* positions = order->ItemList();
        CHECK(positions != NULL);
        CHECK_EQUAL(2UL, positions->Entries());

        pxOrderItem* pos1 = (pxOrderItem*)positions->At(0);
        CHECK(pos1 != NULL);
        CHECK(pos1->IsGoodState());
        CHECK_EQUAL(1, pos1->PosNr());
        CHECK_EQUAL(106, pos1->ArtikelNr());
        CHECK_EQUAL(5, pos1->MengeBestellt());

        pxOrderItem* pos2 = (pxOrderItem*)positions->At(1);
        CHECK(pos2 != NULL);
        CHECK(pos2->IsGoodState());
        CHECK_EQUAL(2, pos2->PosNr());
        CHECK_EQUAL(3764531, pos2->ArtikelNr());
        CHECK_EQUAL(5, pos2->MengeBestellt());
    }

    TEST_FIXTURE(OrderFixture, CancelOrder)
    {
        // Test canceling an existing order
        session->setVideo();
        order = new pxOrder(session->get(), orderno, cDBOPEN_READONLY);
        CHECK(order != NULL);
        CHECK(order->IsGoodState());

        CHECK_EQUAL(0, order->OpenOrder(cDBOPEN_INSERT));
        CHECK_EQUAL(0, order->CancelOrder(pxDVC_UNDEFINED));
        CHECK(order->IsGoodState());
        CHECK(order->IsCancelled());
    }
}
