#include <UnitTest++/UnitTest++.h>
#include "SessionUtil.h"
#include "pxcuststockreserved.hpp"

class CustStockReservedFixture
{
public:
    short branchno;
    long customerno;
    long articleno;
    basar::DateTime fromDateTime;
    SessionUtil* session;
    pxCustStockReserved* custStockReserved;

    CustStockReservedFixture()
        : branchno(5), customerno(9674467), articleno(106), fromDateTime(basar::DateTime()), session(NULL), custStockReserved(NULL)
    {
        // Setup: Initialize shared resources
        fromDateTime.setTime(fromDateTime.getHour(), fromDateTime.getMinute(), fromDateTime.getSec()); // strip millisec from Datetime
        session = new SessionUtil(branchno);
        custStockReserved = new pxCustStockReserved(session->get(), branchno, customerno, articleno, fromDateTime, RESTYPE_OPENORDER_FREE);
    }

    ~CustStockReservedFixture()
    {
        // Teardown: Clean up resources
        delete custStockReserved;
        delete session;
    }
};

SUITE(CustStockReservedTests)
{
    TEST_FIXTURE(CustStockReservedFixture, TestCreateCustStockReserved)
    {
        // Test the creation (Insert) of a new record
        custStockReserved->SetReservedQty(10);
        CHECK_EQUAL(0, custStockReserved->Put());
    }

    TEST_FIXTURE(CustStockReservedFixture, TestReadCustStockReserved)
    {
        // Test reading (Get) an existing record
        CHECK_EQUAL(0, custStockReserved->Get());
        CHECK(custStockReserved->IsGoodState());
		CHECK_EQUAL(branchno, custStockReserved->BranchNo());
		CHECK_EQUAL(customerno, custStockReserved->CustomerNo());
		CHECK_EQUAL(articleno, custStockReserved->ArticleNo());
		CHECK_EQUAL(fromDateTime, custStockReserved->DateTimeFrom());
        CHECK_EQUAL(10, custStockReserved->ReservedQty());
    }

    TEST_FIXTURE(CustStockReservedFixture, TestUpdateCustStockReserved)
    {
        // Test updating an existing record
        session->get()->nDBBeginTransaction();
        CHECK_EQUAL(0, custStockReserved->Get(cDBGET_FORUPDATE));
        custStockReserved->SetReservedQty(20);
        CHECK_EQUAL(0, custStockReserved->Put());
        CHECK(custStockReserved->IsGoodState());
        session->get()->nDBCommit();

        // Verify the update
        CHECK_EQUAL(0, custStockReserved->Get());
        CHECK_EQUAL(20, custStockReserved->ReservedQty());
    }

    TEST_FIXTURE(CustStockReservedFixture, TestDeleteCustStockReserved)
    {
        // Test deleting an existing record
        CHECK_EQUAL(0, custStockReserved->Delete());

        // Verify the deletion
        CHECK(custStockReserved->Get() != 0);
    }
}
