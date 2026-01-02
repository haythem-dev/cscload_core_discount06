#include <UnitTest++/UnitTest++.h>
#include "FixtureBase.h"
#include "MocTour.h"

class RouteListFixture : public FixtureBase
{
public:
    int customerno;
    nString tourid;
    MocTour moc;

    RouteListFixture()
        : FixtureBase(666), customerno(19063), tourid("103526"), moc(_session)  // any random german branch to get a german session
    {
        // Do NOT RELY ON THIS BRANCH NO of the session as we use random branches in the tests!
        moc.setup(customerno);
    }

    ~RouteListFixture()
    {
    }

    void showCustomerTour(CustomerTour* ct)
    {
        CHECK(ct != NULL);
        //std::cout << "\t TourId:[" << ct->getTourId() << "]" << std::endl;
        //std::cout << "\t\t WeekDay:[" << ct->getWeekDay() << "] IsAssignable:[" << ct->isAssignable() << "] AutoAssignable:[" << ct->isAutoAssignable() << "]" << std::endl;
        //std::cout << "\t\t Permissions: KK:[" << ct->hasCoolPermission() << "] K08:[" << ct->hasCoolBelow8Permission() << "] K20:[" << ct->hasCoolBelow20Permission() << "] BTM:[" << ct->hasNarcoticsPermission() << "] Psycho:[" << ct->hasPsychotropicPermission() << "]" << std::endl;
        //std::cout << "\t\t PseudoTour:[" << ct->isPseudoTour() << "] PickingType:[" << ct->getPickingType() << "]" << std::endl;
        //std::cout << "\t\t PickingDate:[" << ct->getPickingDate().GetYYYYMMDD() << "]" << std::endl;
        //std::cout << "\t\t DrivingDur:[" << ct->getDrivingDuration() << "] DeliveryTimeBuffer:[" << ct->getDeliveryTimeBuffer() << "]" << std::endl;
        //std::cout << "\t\t Min. DeliveryDate:[" << ct->getTourDeliveryDateTimeMin().GetYYYYMMDD() << "] DeliveryTime:[" << ct->getTourDeliveryDateTimeMin().GetHours() * 100 + ct->getTourDeliveryDateTimeMin().GetMinutes() << "]" << std::endl;
        //std::cout << "\t\t Max. DeliveryDate:[" << ct->getTourDeliveryDateTimeMax().GetYYYYMMDD() << "] DeliveryTime:[" << ct->getTourDeliveryDateTimeMax().GetHours() * 100 + ct->getTourDeliveryDateTimeMax().GetMinutes() << "]" << std::endl;
    }
};

SUITE(RouteList)
{
    TEST_FIXTURE(RouteListFixture, TestGetCurrentTours)
    {
        //std::cout << "\n\tCustomerTourList::getCurrentTours():" << std::endl;
        CustomerTourList* ctl = new CustomerTourList(_session.get(), moc.getBranchNo(), customerno);
        CHECK_EQUAL(true, ctl->getCurrentTours());
        CustomerTourListIter iter(*ctl);
        CustomerTour* ct = NULL;
        while ((ct = (CustomerTour*)++iter) != NULL)
        {
            showCustomerTour(ct);
        }
        delete ctl;
    }

    TEST_FIXTURE(RouteListFixture, TestGetTour)
    {
        //std::cout << "\n\tCustomerTourList::getTour():" << std::endl;
        CustomerTourList* ctl = new CustomerTourList(_session.get(), moc.getBranchNo(), customerno);
        CHECK_EQUAL(true, ctl->getTour(tourid));

        CustomerTourListIter iter(*ctl);
        CustomerTour* ct = NULL;
        while ((ct = (CustomerTour*)++iter) != NULL)
        {
            showCustomerTour(ct);
        }
        delete ctl;
    }

    TEST_FIXTURE(RouteListFixture, TestGetCurrentToursWithOrderType)
    {
        //std::cout << "\n\tCustomerTourList::getCurrentTours('SO'):" << std::endl;
        CustomerTourList* ctl = new CustomerTourList(_session.get(), moc.getBranchNo(), customerno);
        nString ordertype = "SO";
        ordertype.Strip();

        CHECK_EQUAL(true, ctl->getCurrentTours(ordertype));

        CustomerTourListIter iter(*ctl);
        CustomerTour* ct = NULL;
        while ((ct = (CustomerTour*)++iter) != NULL)
        {
            showCustomerTour(ct);
        }
        delete ctl;
    }
}

