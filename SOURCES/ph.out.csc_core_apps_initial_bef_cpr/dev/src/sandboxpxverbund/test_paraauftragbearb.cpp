#include <UnitTest++/UnitTest++.h>
#include "SessionUtil.h"

class ParaauftragbearbFixture
{
public:
    short branchno;
    SessionUtil* session;
    pxOrderTransmit* xmit;

    ParaauftragbearbFixture()
        : branchno(44), session(NULL), xmit(NULL)
    {
        // Setup: Initialisiere gemeinsam genutzte Ressourcen
        session = new SessionUtil(branchno);
        xmit = session->get();
    }

    ~ParaauftragbearbFixture()
    {
        // Teardown: Bereinige Ressourcen
        delete session;
    }
};

SUITE(Paraauftragbearb)
{
    TEST_FIXTURE(ParaauftragbearbFixture, TestOrderEntryParamBranch44)
    {
        const pxOrderEntryParamPtr orderEntryParamIBTBranch44 = xmit->getOrderEntryParam(44);
        CHECK(orderEntryParamIBTBranch44->IsGoodState());
        CHECK_EQUAL(44, orderEntryParamIBTBranch44->getBranchNo());
        CHECK_EQUAL(2, orderEntryParamIBTBranch44->UseTourManager());
    }

    TEST_FIXTURE(ParaauftragbearbFixture, TestOrderEntryParamBranch09)
    {
        const pxOrderEntryParamPtr orderEntryParamIBTBranch09 = xmit->getOrderEntryParam(9);
        CHECK(orderEntryParamIBTBranch09->IsGoodState());
        CHECK_EQUAL(9, orderEntryParamIBTBranch09->getBranchNo());
        CHECK_EQUAL(2, orderEntryParamIBTBranch09->UseTourManager());
    }
}
