#include <UnitTest++/UnitTest++.h>
#include "SessionUtil.h"
#include "pxcuststockreserved.hpp"
#include <pxtaskcl.hpp>


class ClearReservationFixture
{
public:
    short branchno;
    long customerno; // Example customer number
    long articleno; // Example article number
    long articleno2; // Example article number
    SessionUtil* session;

    ClearReservationFixture()
        : branchno(31), customerno(19063), articleno(106), articleno2(3764531), session(NULL)
    {
        // Setup: Initialize shared resources
        session = new SessionUtil(branchno);
    }

    ~ClearReservationFixture()
    {
        // Teardown: Clean up resources
        delete session;
    }
};

SUITE(ClearReservationTests)
{
    TEST_FIXTURE(ClearReservationFixture, TestInitialization)
    {
        // Test initialization of the fixture
        CHECK(session != NULL);
        CHECK(session->get() != NULL);
        CHECK(session->get()->IsGoodState());

        basar::DateTime fromDateTime = basar::DateTime::getCurrent();
        fromDateTime.addTime(-1000); // 10 minutes in the past
        basar::DateTime toDateTime = basar::DateTime::getCurrent();
        toDateTime.addTime(-100); // 1 minute in the past

        pxCustStockReserved reservation(session->get(), branchno, customerno, articleno, fromDateTime, RESTYPE_INFOORDER_FREE);
        reservation.SetDateTimeTo(basar::DateTime::getCurrent());
        reservation.SetReservedQty(5);
        CHECK_EQUAL(0, reservation.Put());
        CHECK(reservation.IsGoodState());

        pxCustStockReserved reservation2(session->get(), branchno, customerno, articleno2, fromDateTime, RESTYPE_INFOORDER_FREE);
        reservation2.SetDateTimeTo(basar::DateTime::getCurrent());
        reservation2.SetReservedQty(10);
        CHECK_EQUAL(0, reservation2.Put());
        CHECK(reservation2.IsGoodState());
    }

    TEST_FIXTURE(ClearReservationFixture, TestSelectOldReservations)
    {
        // Test select old reservations
        pxCustStockReservedList reservationList(session->get());
        reservationList.SelectOldReservations(branchno, basar::DateTime().getCurrent());
        CHECK_EQUAL(2UL, reservationList.Entries());
        // Placeholder for actual logic
        CHECK(true);
    }

    TEST_FIXTURE(ClearReservationFixture, TestClearAllReservations)
    {
        // Test clearing all reservations
        pxCustStockReservedList reservationList(session->get());
        reservationList.SelectOldReservations(branchno, basar::DateTime().getCurrent());
        CHECK_EQUAL(2UL, reservationList.Entries());

        pxCustStockReservedListIter iter(reservationList);    // define iterator
        pxCustStockReserved* custStockReserved;
        while (NULL != (custStockReserved = (pxCustStockReserved*)++iter)) // browse list
        {
            session->get()->nDBBeginTransaction();
            pxCustBase customer(session->get(), branchno, custStockReserved->CustomerNo());
            CHECK(customer.IsGoodState());

            pxArtBase* article = pxArtBase::CreateArticle(session->get(), custStockReserved->ArticleNo(), branchno);
            CHECK(article->IsGoodState());
            session->get()->getStockBooking()->CancelReservationForInfoOrder(*article, customer, custStockReserved->ReservedQty());
            CHECK(session->get()->getStockBooking()->IsGoodState());
            session->get()->nDBCommit();
            delete article;
        }
    }

    TEST_FIXTURE(ClearReservationFixture, TestVerifyReservationsCleared)
    {
        // Test verifying that reservations have been cleared
        pxCustStockReservedList reservationList(session->get());
        reservationList.SelectOldReservations(branchno, basar::DateTime().getCurrent());
        CHECK_EQUAL(0UL, reservationList.Entries());
    }

    TEST_FIXTURE(ClearReservationFixture, TestTaskControl)
    {
        const char* PROGRAM="clearreserve"; // max 15 characters because of task control!!!

        session->get()->nDBBeginTransaction();
        nString prog(PROGRAM);				  // Programname
        nTime now;
        pxTaskControl tc(session->get(), branchno, prog);
        CHECK_EQUAL(0, tc.TaskControl(now));
        CHECK(tc.IsGoodState());
        session->get()->nDBCommit();
    }
}
