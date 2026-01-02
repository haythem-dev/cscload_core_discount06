#include <UnitTest++/UnitTest++.h>
#include "SessionUtil.h"

class OrderRelationNoFixture
{
public:
    short branchno;
    SessionUtil* session;
    pxOrderRelationNoList* relationList;
    long orderno;
    long puorderno;

    OrderRelationNoFixture()
        : branchno(33), session(NULL), relationList(NULL), orderno(999999), puorderno(12345)
    {
        // Setup: Initialisiere gemeinsam genutzte Ressourcen
        session = new SessionUtil(branchno);
        relationList = new pxOrderRelationNoList(session->get());
    }

    ~OrderRelationNoFixture()
    {
        // Teardown: Bereinige Ressourcen
        delete relationList;
        delete session;
    }
};

SUITE(OrderRelationNoTests)
{
    TEST_FIXTURE(OrderRelationNoFixture, TestCreateOrderRelationNo)
    {
        // Füge eine OrderRelation hinzu
        CHECK(relationList->SetOrderRelationNo(orderno, puorderno, ePurchaseOrderNo));
        CHECK(relationList->IsGoodState());
    }

    TEST_FIXTURE(OrderRelationNoFixture, TestSelectOrderRelationNo)
    {
        // Sicherstellen, dass Relation existiert (idempotent genug für Testumgebung)
        relationList->SetOrderRelationNo(orderno, puorderno, ePurchaseOrderNo);

        // Überprüfe, ob die Relation hinzugefügt wurde
        relationList->SelectOrderRelationNoByOrderNoAndType(orderno, ePurchaseOrderNo);
		CHECK(relationList->IsGoodState());
        CHECK(relationList->Entries() > 0);

        pxOrderRelationNoListIter iter(*relationList);
        pxOrderRelationNo* it = NULL;
        it = (pxOrderRelationNo*)++iter;
        CHECK(it->IsGoodState());
        CHECK_EQUAL(orderno, it->CSCOrderNo());
        CHECK_EQUAL(puorderno, it->RelationNo());
        CHECK_EQUAL(ePurchaseOrderNo, it->RelationNoType());
        CHECK_EQUAL(1UL, relationList->Entries());
    }

    TEST_FIXTURE(OrderRelationNoFixture, TestDeleteOrderRelationNo)
    {
        // Sicherstellen, dass Relation existiert
        relationList->SetOrderRelationNo(orderno, puorderno, ePurchaseOrderNo);

        // Entferne die OrderRelation
        CHECK(relationList->RemoveOrderRelationNo(orderno, ePurchaseOrderNo));
        CHECK(relationList->IsGoodState());
        CHECK_EQUAL(false, relationList->SelectOrderRelationNoByOrderNoAndType(orderno, ePurchaseOrderNo));
        CHECK_EQUAL(0UL, relationList->Entries());
        CHECK(relationList->IsGoodState());
    }
}
