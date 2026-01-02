#include <UnitTest++/UnitTest++.h>
#include "FixtureBase.h"
#include <base/irunnable.h>
#include <base/iint32result.h>
#include <callback/domainmodule/callbackdivisiondm.h>
#include <callback/domainmodule/callbackreasondm.h>
#include <callback/domainmodule/callbackstatusdm.h>
#include <callback/domainmodule/newcallbackdm.h>
#include <callback/domainmodule/newcallbackcritposdm.h>
#include <callback/domainmodule/callbackoverviewitemdm.h>
#include <callback/repository/findcallbacksrequest.h>

using namespace libcsc::callback::domMod;

class Helper
{
public:

    static void getFirstDivisionNoAndReasonNo(ICallbackComponentManagerPtr callbackMgr, short branchno, int& divisionno, int& reasonno)
    {
        CallbackDivisionCollectionPtr divisions = callbackMgr->getCallbackDivisions(branchno);
        CallbackDivisionCollection::Iterator iterDivisions = divisions->begin();
        CallbackReasonCollectionPtr reasons = callbackMgr->getCallbackReasons(branchno, (*iterDivisions)->getDivisionNo());
        CallbackReasonCollection::Iterator iterReasons = reasons->begin();
        divisionno = (*iterDivisions)->getDivisionNo();
        reasonno = (*iterReasons)->getReasonNo();
    }

    static INewCallbackPtr createSimpleNewCallback(ICallbackComponentManagerPtr callbackMgr, const short branchno, const int customerno)
    {
        int divisionno;
        int reasonno;
        getFirstDivisionNoAndReasonNo(callbackMgr, branchno, divisionno, reasonno);

        INewCallbackPtr newCallback = NewCallbackDM::create();
        newCallback->setBranchNo(branchno);
        newCallback->setCustomerNo(customerno);
        newCallback->setCstBranchNo(branchno);
        newCallback->setDivisionNo(divisionno);
        newCallback->setReasonNo(reasonno);
        newCallback->setCritText("TestCritText");
        newCallback->setCritLevel(0);
        newCallback->setContactPerson("TestContactPerson");
        newCallback->setCallbackWantedText("TestCallbackWantedText");
        newCallback->setCallbackDateWished(basar::Date::getCurrent().getDate());
        newCallback->setCallbackTimeWished(235900);
        newCallback->setState("0");
        newCallback->setUserName("TestUserName");
        newCallback->setWebSiteBaseUrl("TestWebSiteBaseUrl");
        newCallback->setReference("TestReference");
        newCallback->setCallbackStatus(0);
        newCallback->setWindowsUser("TestWindowsUser");
        newCallback->setSourceApplication(1); // SourceApplicationCallbackEditor
        newCallback->setUId(0);
        newCallback->setSendEmail(false);

        return newCallback;
    }

    static int writeCallback(ICallbackComponentManagerPtr callbackMgr, INewCallbackPtr newCallback)
    {
        libcsc::base::IRunnablePtr uc = callbackMgr->getWriteNewCallbackUC(newCallback);
        uc->run();
        const libcsc::base::IInt32Result* result = dynamic_cast<libcsc::base::IInt32Result*>(uc.get());
        if (result == NULL)
        {
            return -1;
        }
        return result->getInt32Result();
    }
};

class CallbackFixtureBase : public FixtureBase
{
public:
    short branchno;
    int customerno;

    CallbackFixtureBase(const short branchno, const int customerno)
        : FixtureBase(branchno), branchno(branchno), customerno(customerno)
    {
        // Setup: Initialize shared resources
    }

    ICallbackComponentManagerPtr getCallbackComponentManager()
    {
        pxOrderTransmit* xmit = _session.get();
        if (xmit == NULL)
        {
            std::cout << "Exception: Session is not initialized." << std::endl;
            throw;
        }
        return xmit->getCallbackComponentManager();
    }
};

class CallbackFixture : public CallbackFixtureBase
{
public:
    CallbackFixture() : CallbackFixtureBase(5, 1436) {}
};

SUITE(Callback)
{
    TEST_FIXTURE(CallbackFixture, Init)
    {
        // Ensure there is at least one callback in the system for testing
        INewCallbackPtr newCallback = Helper::createSimpleNewCallback(getCallbackComponentManager(), branchno, customerno);
        Helper::writeCallback(getCallbackComponentManager(), newCallback);
    }

    TEST_FIXTURE(CallbackFixture, TestGetCallbackDivisions)
    {
        CallbackDivisionCollectionPtr divisions = getCallbackComponentManager()->getCallbackDivisions(branchno);

        CHECK(!divisions->isEmpty());
    }

    TEST_FIXTURE(CallbackFixture, TestGetCallbackReasons)
    {
        CallbackDivisionCollectionPtr divisions = getCallbackComponentManager()->getCallbackDivisions(branchno);
        CallbackDivisionCollection::Iterator iter = divisions->begin();
        CallbackReasonCollectionPtr reasons = getCallbackComponentManager()->getCallbackReasons(branchno, (*iter)->getDivisionNo());

        CHECK(!reasons->isEmpty());
    }

    TEST_FIXTURE(CallbackFixture, TestGetCallbackDivisionAndReasonName)
    {
        int divisionno;
        int reasonno;
        Helper::getFirstDivisionNoAndReasonNo(getCallbackComponentManager(), branchno, divisionno, reasonno);

        basar::VarString divisionName;
        basar::VarString reasonName;
        getCallbackComponentManager()->getGetCallbackDivisionAndReasonName(branchno, divisionno, reasonno, divisionName, reasonName);

        CHECK(!divisionName.empty());
        CHECK(!reasonName.empty());
    }

    TEST_FIXTURE(CallbackFixture, TestGetCallbackStatus)
    {
        CallbackStatusCollectionPtr statuses = getCallbackComponentManager()->getCallbackStatuses(branchno);

        CHECK(!statuses->isEmpty());
    }

    TEST_FIXTURE(CallbackFixture, TestFindCallbacks)
    {
        libcsc::callback::repo::FindCallbacksRequestPtr request = libcsc::callback::repo::FindCallbacksRequest::create(branchno, true, customerno, "", 0, 99999999, 0, 0, 25, -1);
        CallbackOverviewCollectionPtr overview = getCallbackComponentManager()->findCallbacks(request);

        CHECK(!overview->isEmpty());
    }

    TEST_FIXTURE(CallbackFixture, TestFindCustomers)
    {
        libcsc::callback::repo::FindCustomersRequestPtr request = libcsc::callback::repo::FindCustomersRequest::create(branchno, true, false, customerno, "", "", "", "", 25);
        CallbackCustomerCollectionPtr customers = getCallbackComponentManager()->findCustomers(request);

        CHECK(!customers->isEmpty());
    }

    TEST_FIXTURE(CallbackFixture, TestFindCallbacksCount)
    {
        libcsc::callback::repo::FindCallbacksRequestPtr request = libcsc::callback::repo::FindCallbacksRequest::create(branchno, true, customerno, "", 0, 99999999, 0, 0, 25, -1);

        int count = getCallbackComponentManager()->getFindCallbacksCount(request);

        CHECK(count > 0);
    }

    TEST_FIXTURE(CallbackFixture, TestFindCustomersCount)
    {
        libcsc::callback::repo::FindCustomersRequestPtr request = libcsc::callback::repo::FindCustomersRequest::create(branchno, true, false, customerno, "", "", "", "", 25);

        int count = getCallbackComponentManager()->getFindCustomersCount(request);

        CHECK(count > 0);
    }

    TEST_FIXTURE(CallbackFixture, TestHasCallback)
    {
        INewCallbackPtr newCallback = Helper::createSimpleNewCallback(getCallbackComponentManager(), branchno, customerno);
        const int callbackNo = Helper::writeCallback(getCallbackComponentManager(), newCallback);

        bool result = getCallbackComponentManager()->hasCallback(callbackNo , branchno);

        CHECK(result);
    }

    TEST_FIXTURE(CallbackFixture, TestIsCallbackStatusVisibile)
    {
        const bool isCallbackStatusVisibile = getCallbackComponentManager()->isCallbackStatusVisibile(branchno);

        CHECK(!isCallbackStatusVisibile);
    }

    TEST_FIXTURE(CallbackFixture, TestGetCallback)
    {
        INewCallbackPtr newCallback = Helper::createSimpleNewCallback(getCallbackComponentManager(), branchno, customerno);
        const int callbackNo = Helper::writeCallback(getCallbackComponentManager(), newCallback);

        ICallbackPtr callback;
        CallbackPosCollectionPtr callbackPos;
        const bool result = getCallbackComponentManager()->tryGetCallback(callbackNo, branchno, callback, callbackPos);

        CHECK(result);
    }

    TEST_FIXTURE(CallbackFixture, TestWriteNewCallbackUC)
    {
        INewCallbackPtr newCallback = Helper::createSimpleNewCallback(getCallbackComponentManager(), branchno, customerno);
        const int callbackNo = Helper::writeCallback(getCallbackComponentManager(), newCallback);

        CHECK(callbackNo > 0);
    }

    TEST_FIXTURE(CallbackFixture, TestWriteNewCallbackCritPosUC)
    {
        INewCallbackPtr newCallback = Helper::createSimpleNewCallback(getCallbackComponentManager(), branchno, customerno);
        const int callbackNo = Helper::writeCallback(getCallbackComponentManager(), newCallback);

        INewCallbackCritPosPtr newCallbackCritPos = NewCallbackCritPosDM::create();
        newCallbackCritPos->setBranchNo(branchno);
        newCallbackCritPos->setCallbackNo(callbackNo);
        newCallbackCritPos->setCallbackStatus(0);
        newCallbackCritPos->setText("TestText");
        newCallbackCritPos->setWindowsUser("TestWindowsUser");
        newCallbackCritPos->setSourceApplication(1); // SourceApplicationCallbackEditor
        newCallbackCritPos->setUId(0);
        libcsc::base::IRunnablePtr ucNewCritPos = getCallbackComponentManager()->getWriteNewCallbackCritPosUC(newCallbackCritPos);
        ucNewCritPos->run();

        //CHECK(!statuses->isEmpty());
    }
}
