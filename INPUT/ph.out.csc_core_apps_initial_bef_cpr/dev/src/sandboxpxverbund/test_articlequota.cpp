#include <UnitTest++/UnitTest++.h>
#include "SessionUtil.h"
#include "pxarticlequota.hpp"

// -----------------------------------------------------------------------------
// Fixture for pxArticleQuota
// -----------------------------------------------------------------------------
class ArticleQuotaFixture
{
public:
    short branchno;
    long customerNo;
    long articleNo;
    pxArticleQuota* quota;
    SessionUtil* session;

    ArticleQuotaFixture()
        : branchno(31), customerNo(2001), articleNo(106), quota(NULL), session(NULL)
    {
        session = new SessionUtil(branchno);
        session->doSQL("DELETE FROM ARTICLEQUOTA WHERE BRANCHNO = 31 AND CUSTOMERNO = 2001 AND ARTICLENO = 106");
        session->doSQL("DELETE FROM ARTICLEQUOTA WHERE BRANCHNO = 31 AND CUSTOMERNO = 0 AND ARTICLENO = 106");
        session->doSQL("INSERT INTO ARTICLEQUOTA (BRANCHNO,CUSTOMERNO,ARTICLENO,QUOTA,KUMQTY,VALIDITY,DATEUPDATE,UID_ANLAGE,SDAFUEQUOTA,DATEFROM,DATETO,PHARMACYGROUPID,SNOBATCHCHANGE) "
                       "VALUES (31,2001,106,7,0,'W',20250831,1271,' ',20250101,20991231,'   ',' ')");
        session->doSQL("INSERT INTO ARTICLEQUOTA (BRANCHNO,CUSTOMERNO,ARTICLENO,QUOTA,KUMQTY,VALIDITY,DATEUPDATE,UID_ANLAGE,SDAFUEQUOTA,DATEFROM,DATETO,PHARMACYGROUPID,SNOBATCHCHANGE) "
                       "VALUES (31,0,106,7,0,'W',20250831,1271,' ',20250101,20991231,'   ',' ')");
        quota = new pxArticleQuota(session->get(), branchno, customerNo, articleNo);
    }

    ~ArticleQuotaFixture()
    {
        // Cleanup: delete record if it still exists
        session->doSQL("DELETE FROM ARTICLEQUOTA WHERE BRANCHNO = 31 AND CUSTOMERNO = 2001 AND ARTICLENO = 106");
        session->doSQL("DELETE FROM ARTICLEQUOTA WHERE BRANCHNO = 31 AND CUSTOMERNO = 0 AND ARTICLENO = 106");
        delete quota;
        delete session;
    }
};

SUITE(ArticleQuotaTests)
{
    TEST_FIXTURE(ArticleQuotaFixture, CreateArticleQuota)
    {
        // Ensure it does not yet exist
        //CHECK(quota->Get() != 0);
        // Create (Put writes new record with default initialized fields)
        //CHECK_EQUAL(0, quota->Put());
        // Verify
        CHECK_EQUAL(0, quota->Get());
        CHECK_EQUAL(branchno, quota->BranchNo());
        CHECK_EQUAL(customerNo, quota->CustomerNo());
        CHECK_EQUAL(articleNo, quota->ArticleNo());
        CHECK_EQUAL(0L, quota->KumQty());
    }

    TEST_FIXTURE(ArticleQuotaFixture, ReadArticleQuota)
    {
        // Precondition: create if needed
        if (quota->Get() != 0)
            CHECK_EQUAL(0, quota->Put());
        CHECK_EQUAL(0, quota->Get());
        CHECK_EQUAL(branchno, quota->BranchNo());
        CHECK_EQUAL(customerNo, quota->CustomerNo());
        CHECK_EQUAL(articleNo, quota->ArticleNo());
    }

    TEST_FIXTURE(ArticleQuotaFixture, UpdateArticleQuota)
    {
        if (quota->Get() != 0)
            CHECK_EQUAL(0, quota->Put());
        long before = quota->KumQty();
        quota->Session()->nDBBeginTransaction();
        quota->Get(cDBGET_FORUPDATE);
        quota->AddQuantity(5); // modifies KumQty and sets dirty
        CHECK_EQUAL(0, quota->Put());
        quota->Session()->nDBCommit();
        quota->Get();
        CHECK_EQUAL(before + 5, quota->KumQty());
    }

    TEST_FIXTURE(ArticleQuotaFixture, DeleteArticleQuota)
    {
        if (quota->Get() != 0)
            CHECK_EQUAL(0, quota->Put());
        CHECK_EQUAL(0, quota->Delete());
        CHECK(quota->Get() != 0); // should not be found anymore
    }

    TEST_FIXTURE(ArticleQuotaFixture, SelectBasicList)
    {
        // Ensure record exists (though SelectBasic ignores customer)
        if (quota->Get() != 0)
            CHECK_EQUAL(0, quota->Put());
        pxArticleQuotaList list(session->get());
        CHECK(list.SelectBasic(branchno, articleNo) > 0UL);
        // We cannot guarantee positive entries if database filtering differs, so just ensure call succeeded
    }

    TEST_FIXTURE(ArticleQuotaFixture, SelectOriginalList)
    {
        if (quota->Get() != 0)
            CHECK_EQUAL(0, quota->Put());
        pxArticleQuotaList list(session->get());
        CHECK(list.SelectOriginal(branchno, customerNo, articleNo) > 0UL);
    }
}
