#include <UnitTest++/UnitTest++.h>
#include "SessionUtil.h"

class CSCCustomerFixture
{
public:
    short branchno1;
    long customerno1;
    short branchno2;
    long customerno2;
    SessionUtil* session;
    pxOrderTransmit* xmit;

    CSCCustomerFixture()
        : branchno1(33), customerno1(19063), branchno2(5), customerno2(3325317), session(NULL), xmit(NULL)
    {
        // Setup: Initialisiere gemeinsam genutzte Ressourcen
        session = new SessionUtil(branchno1);
        xmit = session->get();
    }

    ~CSCCustomerFixture()
    {
        // Teardown: Bereinige Ressourcen
        delete session;
    }
};

SUITE(CSCCustomer)
{
    TEST_FIXTURE(CSCCustomerFixture, TestCSCCustomer1)
    {
        CSCCustomer* csccustomer = new CSCCustomer(xmit->Session(), branchno1, customerno1);
        CHECK(csccustomer != NULL);
        CHECK_EQUAL(0, csccustomer->Read());
        CHECK(csccustomer->IsGoodState());
        delete csccustomer;
    }

    TEST_FIXTURE(CSCCustomerFixture, TestCSCCustomer2)
    {
        CSCCustomer* csccustomer2 = new CSCCustomer(xmit->Session(), branchno2, customerno2);
        CHECK(csccustomer2 != NULL);
        CHECK_EQUAL(0, csccustomer2->Read());
        CHECK(csccustomer2->IsGoodState());
        delete csccustomer2;
    }
}

