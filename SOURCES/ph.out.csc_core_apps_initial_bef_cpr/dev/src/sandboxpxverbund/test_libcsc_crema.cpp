#include <UnitTest++/UnitTest++.h>
#include "FixtureBase.h"
#include <crema/componentmanager/cremacomponentmanager.h>
#include <crema/repository/repository.h>
#include <crema/usersuggestion/usersuggestion.h>
#include <crema/guidata/guidata.h>
#include <crema/maildata/maildata.h>
#include "MocCrema.h"

using namespace libcsc::crema;

class CremaFixtureBase : public FixtureBase
{
public:
    short _branchno;
    int _customerno;

    CremaFixtureBase(const short branchno, const int customerno) : FixtureBase(branchno), _branchno(branchno), _customerno(customerno)
    {
    }
};

class CremaFixture : public CremaFixtureBase
{
public:
    CremaFixture() : CremaFixtureBase(5, 1436)
    {
    }

    CremaComponentManagerPtr getCremaComponentManager()
    {
        pxOrderTransmit* xmit = _session.get();
        if (xmit == NULL)
        {
            std::cout << "Exception: Session is not initialized." << std::endl;
            throw;
        }
        return xmit->getCremaComponentManager();
    }

    CremaDataSearchValues getRandomGuiData()
    {
        std::stringstream ss;
        ss << "SELECT FIRST 1 a.kdauftragnr, a.vertriebszentrumnr FROM kdauftrag a "
           << "INNER JOIN kunde k ON k.idfnr = a.idfnr "
           << "INNER JOIN debtlimit d ON d.partnerno = k.partnernr;";

        basar::db::sql::ResultsetRef result = _session.doSelect(ss.str());
        if (!result.next())
        {
            std::cout << "No orders found in database." << std::endl;
            throw;
        }

        CremaDataSearchValues guiData;
        guiData.orderno = result.getInt32("kdauftragnr");
        guiData.branchno = result.getInt16("vertriebszentrumnr");
        return guiData;
    }

    basar::VarString getRandomMailData()
    {
        std::string ss = "SELECT FIRST 1 guid FROM debtmailsend;";

        basar::db::sql::ResultsetRef result = _session.doSelect(ss);
        if (!result.next())
        {
            std::cout << "No mail data found in database." << std::endl;
            throw;
        }
        return basar::VarString(result.getString(0));
    }

    basar::VarString getRandomOrderData()
    {
        std::string ss = "SELECT FIRST 1 guid FROM debtmailsend;";

        basar::db::sql::ResultsetRef result = _session.doSelect(ss);
        if (!result.next())
        {
            std::cout << "No order data found in database." << std::endl;
            throw;
        }
        return basar::VarString(result.getString("guid"));
    }

    CremaDataSearchValues getRandomCreditLimitData()
    {
        std::stringstream ss;
        ss << "SELECT FIRST 1 a.kdauftragnr, a.vertriebszentrumnr "
           << "FROM kdauftrag a "
           << "INNER JOIN kunde k ON k.idfnr = a.idfnr "
           << "INNER JOIN debtlimit d ON d.partnerno = k.partnernr OR d.partnerno = k.maincstno "
           << "WHERE d.limittype = 2 OR d.partnerno = k.maincstno OR k.maincstno = 0;";

        basar::db::sql::ResultsetRef result = _session.doSelect(ss.str());
        if (!result.next())
        {
            std::cout << "No orders found in database." << std::endl;
            throw;
        }

        CremaDataSearchValues creditLimitData;
        creditLimitData.orderno = result.getInt32("kdauftragnr");
        creditLimitData.branchno = result.getInt16("vertriebszentrumnr");
        return creditLimitData;
    }
};

SUITE(Crema)
{
    TEST_FIXTURE(CremaFixture, UserSuggestion)
    {
        const int customerno = 112233;
        const int orderno = 123456;

        MocUserSuggestion moc(_session);
        moc.createOrder(customerno, orderno);

        const std::string comment1 = "TestComment";
        getCremaComponentManager()->getRepository()->saveLastDecision(1, 1, comment1, moc.getTestUser(), moc.getBranchNo(), orderno);

        UserSuggestionPtr userSuggestion1 = getCremaComponentManager()->getRepository()->findUserSuggestion(moc.getBranchNo(), customerno, "", true);

        CHECK(userSuggestion1->getChoiceComment() == comment1);

        const std::string comment2 = "ChangedTestComment";
        getCremaComponentManager()->getRepository()->saveLastDecision(1, 1, comment2, moc.getTestUser(), moc.getBranchNo(), orderno);

        UserSuggestionPtr userSuggestion2 = getCremaComponentManager()->getRepository()->findUserSuggestion(moc.getBranchNo(), customerno, moc.getTestUser(), false);

        CHECK(userSuggestion2->getChoiceComment() == comment2);
    }

    TEST_FIXTURE(CremaFixture, FindReasons)
    {
        ReasonCollectionPtr result = getCremaComponentManager()->getRepository()->findReasons(5, 5, true);

        CHECK(!result->empty());
    }

    TEST_FIXTURE(CremaFixture, FindGuiData)
    {
        const CremaDataSearchValues values = getRandomGuiData();

        GuiDataPtr guiData = getCremaComponentManager()->getRepository()->findGuiData(values.branchno, values.orderno);

        CHECK(guiData.get() != NULL);
    }

    TEST_FIXTURE(CremaFixture, FindMailData)
    {
        const basar::VarString uuid = getRandomMailData();

        MailDataPtr mailData = getCremaComponentManager()->getRepository()->findMailData(uuid);

        CHECK(mailData.get() != NULL);
    }

    TEST_FIXTURE(CremaFixture, FindOrderData)
    {
        const basar::VarString uuid = getRandomOrderData();

        OrderDataPtr orderData = getCremaComponentManager()->getRepository()->findOrderData(uuid);

        CHECK(orderData.get() != NULL);
    }

    TEST_FIXTURE(CremaFixture, FindOpenCremaOrders)
    {
        MocOpenCremaOrder moc(_session);
        const short branchno = moc.createOpenCremaOrder();

        std::vector<basar::Int16> relevantBranchNos;
        relevantBranchNos.push_back(branchno);
        CremaOrderCollectionPtr cremaOrders = getCremaComponentManager()->getRepository()->findOpenCremaOrders(1, relevantBranchNos);

        CHECK(!cremaOrders->empty());
    }

    TEST_FIXTURE(CremaFixture, FindFinishedTodayCremaOrders)
    {
        MocFinishedTodayCremaOrder moc(_session);
        const short branchno = moc.createFinishedTodayCremaOrder();

        std::vector<basar::Int16> relevantBranchNos;
        relevantBranchNos.push_back(branchno);
        CremaOrderCollectionPtr cremaOrders = getCremaComponentManager()->getRepository()->findFinishedTodayCremaOrders(relevantBranchNos);

        CHECK(!cremaOrders->empty());
    }

    TEST_FIXTURE(CremaFixture, FindCreditLimitData)
    {
        const CremaDataSearchValues values = getRandomCreditLimitData();

        CreditLimitDataCollectionPtr creditLimitData = getCremaComponentManager()->getRepository()->findCreditLimitData(values.branchno, values.orderno);

        CHECK(!creditLimitData->empty());
    }
}
