#include <UnitTest++/UnitTest++.h>
#include "SessionUtil.h"

class CustomerOrderTypeFixture
{
public:
    short branchno;
    long Idf;
    SessionUtil* session;
    pxOrderTransmit* xmit;
    pxCustOrderType* cot;

    CustomerOrderTypeFixture()
        : branchno(31), Idf(655), session(NULL), xmit(NULL), cot(NULL)
    {
        // Setup: Initialisiere gemeinsam genutzte Ressourcen
        session = new SessionUtil(branchno);
        xmit = session->get();
        cot = new pxCustOrderType(xmit->Session());
    }

    ~CustomerOrderTypeFixture()
    {
        // Teardown: Bereinige Ressourcen
        delete cot;
        delete session;
    }
};

SUITE(CustomerOrderType)
{
    TEST_FIXTURE(CustomerOrderTypeFixture, TestGetCustomerOrderType)
    {
        CHECK_EQUAL(true, cot->IsGoodState());

        nString AuftragsArt("NO");
        int rc = cot->getCustomerOrderType(branchno, Idf, AuftragsArt);
        CHECK_EQUAL(0, rc);

        nString DefaultOrderLabel("NORMAL");
        nString FreeOrderLabel("XXX");
        CHECK_EQUAL(true, cot->isDefaultOrderLabel(DefaultOrderLabel));
        CHECK_EQUAL(false, cot->isDefaultOrderLabel(FreeOrderLabel));
    }
}
