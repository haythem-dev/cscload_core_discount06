#include <UnitTest++/UnitTest++.h>
#include "SessionUtil.h"

class OrderRemarkTypesFixture
{
public:
    short branchno;
    SessionUtil* session;
    pxOrderRemarkTypeList* list;

    OrderRemarkTypesFixture()
        : branchno(33), session(NULL), list(NULL)
    {
        // Setup: Initialisiere gemeinsam genutzte Ressourcen
        session = new SessionUtil(branchno);
        list = new pxOrderRemarkTypeList(session->get());
    }

    ~OrderRemarkTypesFixture()
    {
        // Teardown: Bereinige Ressourcen
        delete list;
        delete session;
    }
};

SUITE(OrderRemarkTypes)
{
    TEST_FIXTURE(OrderRemarkTypesFixture, TestOrderRemarkTypeBoth)
    {
        list->SelectOrderRemarkTypes(pxOrderRemarkType::eOrderRemarkTypeBoth);
        CHECK(list->IsGoodState());
        CHECK(list->Entries() > 0);
    }

    TEST_FIXTURE(OrderRemarkTypesFixture, TestOrderRemarkTypeHeaderLevel)
    {
        list->SelectOrderRemarkTypes(pxOrderRemarkType::eOrderRemarkTypeHeaderLevel);
        CHECK(list->IsGoodState());
        CHECK(list->Entries() > 0);
    }

    TEST_FIXTURE(OrderRemarkTypesFixture, TestOrderRemarkTypeLineLevel)
    {
        list->SelectOrderRemarkTypes(pxOrderRemarkType::eOrderRemarkTypeLineLevel);
        CHECK(list->IsGoodState());
        CHECK(list->Entries() > 0);
    }
}
