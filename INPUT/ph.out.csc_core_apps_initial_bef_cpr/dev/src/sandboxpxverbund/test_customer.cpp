#include <UnitTest++/UnitTest++.h>
#include "SessionUtil.h"
#include "pxcstbas.hpp"
#include "pxcustpharmgroup.hpp"
#include "pxcustrouteweek.hpp"

class CustBaseFixture
{
public:
    short branchno;
    long customerno;
    SessionUtil* session;
    pxCustBase* custBase;

    CustBaseFixture()
        : branchno(5), customerno(9674467), session(NULL), custBase(NULL)
    {
        // Setup: Initialize shared resources
        session = new SessionUtil(branchno);
        custBase = new pxCustBase(session->get(), branchno, customerno);
    }

    ~CustBaseFixture()
    {
        // Teardown: Clean up resources
        delete custBase;
        delete session;
    }
};

SUITE(CustBaseTests)
{
    TEST_FIXTURE(CustBaseFixture, TestCustBaseInitialization)
    {
        // Verify that the pxCustBase object is in a good state after initialization
        CHECK(custBase->IsGoodState());
    }

    TEST_FIXTURE(CustBaseFixture, TestCustBaseProperties)
    {
        // Verify that the customer number is correctly set
        CHECK_EQUAL(customerno, custBase->IDFNr());

        // Verify that the branch number is correctly set
        CHECK_EQUAL(branchno, custBase->FilialNr());
        CHECK_EQUAL("07", custBase->KdGruppe());
        CHECK_EQUAL("FUERTH", custBase->Ort());
        CHECK_EQUAL("PERSONALKONTO", custBase->NameInhaber());
    }

    TEST_FIXTURE(CustBaseFixture, TestCustBasePharmGroupList)
    {
        // Verify that the PharmGroupList() method returns a valid object
        pxCustPharmGroupList* pharmGroupList = custBase->PharmGroupList();
        CHECK(pharmGroupList != NULL);
        CHECK(pharmGroupList->IsGoodState());

        // Example: Verify the number of pharmacy groups (if applicable)
        const size_t groupCount = pharmGroupList->Entries();
        CHECK(groupCount > 0);

		pxCustPharmGroup* cpg = pharmGroupList->Find("250");
		CHECK(cpg != NULL);
		CHECK(cpg->IsGoodState());  
		CHECK_EQUAL(customerno, cpg->CustomerNo());
		CHECK_EQUAL(branchno, cpg->BranchNo());
		CHECK_EQUAL("250", cpg->PharmacyGroupId());
   }

    TEST_FIXTURE(CustBaseFixture, TestCustBaseRouteWeekList)
    {
        // Verify that the RouteWeekList() method returns a valid object
        pxCustRouteWeekList* routeWeekList = custBase->RouteWeekList();
        CHECK(routeWeekList != NULL);
        CHECK(routeWeekList->IsGoodState());

        // Example: Verify the number of weekly routes (if applicable)
        const size_t routeCount = routeWeekList->Entries();
        CHECK(routeCount > 0);
        CHECK(routeWeekList->Find("174601", 1));
        CHECK(routeWeekList->Find("174601", 2));
        CHECK(routeWeekList->Find("174601", 3));
        CHECK(routeWeekList->Find("174601", 4));
        CHECK(routeWeekList->Find("174601", 5));
    }
}
