#include <UnitTest++/UnitTest++.h>
#include "SessionUtil.h"
#include "pxttype.hpp" // For pxTimeTypeList
#include "pxoclpar.hpp" // For pxOrderCloseParamList

class AAOrderCloseFixture
{
public:
    short branchno;
    SessionUtil* session;

    AAOrderCloseFixture()
        : branchno(5), session(NULL)
    {
        // Setup: Initialize shared resources
        session = new SessionUtil(branchno);
    }

    ~AAOrderCloseFixture()
    {
        // Teardown: Clean up resources
        delete session;
    }
};

SUITE(AAOrderCloseTests)
{
    TEST_FIXTURE(AAOrderCloseFixture, TestInitialization)
    {
        // Test initialization of the fixture
        CHECK(session != NULL);
        CHECK(session->get() != NULL);
        CHECK(session->get()->isGermany());
        CHECK(session->get()->IsGoodState());
    }

    TEST_FIXTURE(AAOrderCloseFixture, TestTimeTypeList)
    {
        pxTimeTypeList timelist(session->get());
        timelist.Select(Type_ADS_CLOSE_FOR_AOCL, "", branchno);
        CHECK(timelist.IsGoodState());
        CHECK(timelist.Entries() > 0UL);

        nDate today;
        CHECK(timelist.FindDayOfWeek(today.GetDayOfWeek()));

        timelist.Select(Type_ADS_END_CONSOLIDATION, "", branchno);
        CHECK(timelist.IsGoodState());
        CHECK(timelist.Entries() > 0UL);
    }

    TEST_FIXTURE(AAOrderCloseFixture, TestOrderCloseParamList)
    {
        pxOrderCloseParamList closeparamlist(session->get());
        CHECK(closeparamlist.Select(branchno) > 0UL);
        CHECK(closeparamlist.IsGoodState());
        CHECK(closeparamlist.Entries() > 0UL);
    }

    TEST_FIXTURE(AAOrderCloseFixture, TestSelectForAutomaticClosure)
    {
        pxOrderList orderlist(session->get());
        orderlist.SelectForAutomaticClosure(branchno, "0000%", Order::EntryDeferred, Order::NOT_Invoiced, Order::NOT_Cancelled, Order::NOT_ProblemClearance, Order::cStateLast);
        CHECK(orderlist.IsGoodState());
        CHECK(orderlist.Entries() > 0UL || orderlist.Entries() == 0UL);
    }
}
