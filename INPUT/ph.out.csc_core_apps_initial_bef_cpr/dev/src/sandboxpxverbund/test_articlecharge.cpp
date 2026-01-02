#include <UnitTest++/UnitTest++.h>
#include "SessionUtil.h"
#include "pxarticlecharge.hpp"

class ArticleChargeFixture
{
public:
    short branchno;
    long articleno;
    pxArticleCharge* articleCharge;
    SessionUtil* session;

    ArticleChargeFixture()
        : branchno(31), articleno(1001), articleCharge(NULL), session(NULL)
    {
        // Setup: Initialize shared resources
        session = new SessionUtil(branchno);
        articleCharge = new pxArticleCharge(session->get(), branchno, articleno, "CHARGE_A");
    }

    ~ArticleChargeFixture()
    {
        // Teardown: Clean up resources
        delete articleCharge;
        delete session;
    }
};

SUITE(ArticleChargeTests)
{
    TEST_FIXTURE(ArticleChargeFixture, TestCreateArticleCharge)
    {
        // Test creating a new article charge
        articleCharge->SetExpiryDate(basar::Date::getCurrent());
		articleCharge->SetStateCharge(BATCHSTATUS_SALEABLE);
        articleCharge->SetQuantity(10);
        CHECK_EQUAL(0, articleCharge->Put());
    }

    TEST_FIXTURE(ArticleChargeFixture, TestReadArticleCharge)
    {
        // Test reading an existing article charge
        CHECK_EQUAL(0, articleCharge->Get());
        CHECK_EQUAL(branchno, articleCharge->BranchNo());
        CHECK_EQUAL(articleno, articleCharge->ArticleNo());
        basar::VarString charge = articleCharge->ChargenNr();
        charge.trim();
        CHECK_EQUAL("CHARGE_A", charge);
        CHECK_EQUAL(basar::Date::getCurrent(), articleCharge->ExpiryDate());
        CHECK_EQUAL(10, articleCharge->Stock());
    }

    TEST_FIXTURE(ArticleChargeFixture, TestUpdateArticleCharge)
    {
        // Test updating an existing article charge
        session->get()->nDBBeginTransaction();
        articleCharge->Get(cDBGET_FORUPDATE);
        articleCharge->AddQuantity(10);
        CHECK_EQUAL(0, articleCharge->Put());
        session->get()->nDBCommit();

        // Verify the update
        articleCharge->Get();
        CHECK_EQUAL(20, articleCharge->Stock());
    }

    TEST_FIXTURE(ArticleChargeFixture, TestSelectArticleChargeList)
    {
        // Test selecting article charges using pxArticleChargeList
        pxArticleChargeList chargeList(session->get());
        CHECK(chargeList.Select(branchno, articleno) > 0UL);
        CHECK(chargeList.Entries() > 0UL);
    }

    TEST_FIXTURE(ArticleChargeFixture, TestDeleteArticleCharge)
    {
        // Test deleting an existing article charge
        CHECK_EQUAL(0, articleCharge->Delete());

        // Verify the deletion
        CHECK(articleCharge->Get() != 0);
    }

}