#include <UnitTest++/UnitTest++.h>
#include "FixtureBase.h"
#include "MocTour.h"
#include "pxverbundincludes.h"

using namespace std;

void showTourInfo(TourInfo& ti)
{
    if( !ti.getTourFound() )
    {
        cout << "\t Keine Tour gefunden!" << endl;
    }
    else
    {
        //cout << "\t Tour gefunden!" << endl;
        //cout << "\t\t TourID:             " << ti.getTourID() << endl;
        //cout << "\t\t TourDate:           " << ti.getTourDate().GetYYYYMMDD() << endl;
        //cout << "\t\t DrivingDuration:    " << ti.getDrivingDuration() << endl;
        //cout << "\t\t DeliveryTimeBuffer: " << ti.getDeliveryTimeBuffer() << endl;
        //cout << "\t\t PickingType:        " << ti.getPickingType() << endl;
        //cout << "\t\t Delivery Min.:      " << ti.getCustomerDeliveryDateTimeMin().GetYYYYMMDD() << " - " << ti.getCustomerDeliveryDateTimeMin().GetHours() * 100 + ti.getCustomerDeliveryDateTimeMin().GetMinutes() << endl;
        //cout << "\t\t Delivery Max.:      " << ti.getCustomerDeliveryDateTimeMax().GetYYYYMMDD() << " - " << ti.getCustomerDeliveryDateTimeMax().GetHours() * 100 + ti.getCustomerDeliveryDateTimeMax().GetMinutes() << endl;
        //cout << "\t\t LagRechTour:        " << ti.getLagRechTour() << endl;

        //if( ti.getIBTBranchNo() > 0 )
        //{
        //    cout << "\t\t Verbund Filiale:    " << ti.getIBTBranchNo() << endl;
        //    cout << "\t\t Verbund IDF:        " << ti.getIBTCustomerNo() << endl;
        //    cout << "\t\t Verbund TourId:     " << ti.getIBTTourID() << endl;
        //    cout << "\t\t Verbund Typ:        " << ti.getIBTType() << endl;
        //    cout << "\t\t Verbund TagVerbund: " << ti.isDayIBT() << endl;
        //}
    }
}

void testReturnsTourDeterminationForCustomer()
{
    SessionUtil session(33);
    pxOrderTransmit* xmit = session.get();

    short branchno = 33;
    long customerno = 4476490;
    //cout << "BranchNo " << branchno << " CustomerNo " << customerno << ": " << endl;
    TourInfo ti = TourManager::determineReturnsTour(xmit->Session(), branchno, customerno);
    showTourInfo(ti);
}

void testTourDeterminationForCustomer()
{
    SessionUtil session(32);
    pxOrderTransmit* xmit = session.get();

    short branchno = 32;
    long customerno = 4014022;
    //cout << "BranchNo " << branchno << " CustomerNo " << customerno << ": " << endl;
    TourInfo ti = TourManager::getCustomerTourForArticle(xmit->Session(), branchno, customerno);
    showTourInfo(ti);

    branchno = 30;
    customerno = 4014022;
    //cout << "BranchNo " << branchno << " CustomerNo " << customerno << ": " << endl;
    ti = TourManager::getCustomerTourForArticle(xmit->Session(), branchno, customerno);
    showTourInfo(ti);
}


// ------------------------------------------------------------------------------------------- //
class TourAssignabilityFixture : public FixtureBase
{
public:
    long customerno;
    MocTour moc;

    TourAssignabilityFixture()
        : FixtureBase(5), customerno(19063), moc(_session)  // any random german branch to get a german session
    {
        // Do NOT RELY ON THIS BRANCH NO of the session as we use random branches in the tests!
        moc.setup(customerno);
    }
};


void testTourAssignability(short branchno, long customerno)
{
    SessionUtil session(56);
    pxOrderTransmit* xmit = session.get();

    CSCCustomer* customer = new CSCCustomer( xmit->Session(), branchno, customerno );
    customer->Read();
    CHECK(customer->IsGoodState());

    CustomerTourList* currenttours = new CustomerTourList(xmit->Session(), branchno, customerno);
    CHECK(currenttours->IsGoodState());
    CHECK(currenttours->getCurrentTours());
    CHECK(currenttours->Entries() > 0);

    CustomerTourListIter iter(*currenttours);
    CustomerTour* ct = NULL;
    while ( (ct = (CustomerTour*)++iter) != NULL )
    {
        if( ct->isAssignable( true ) )
        {
//			cout << " -> Assignable:     " << ct->getTourId() << " Date: " << ct->getTourDepartureDateTime().GetYYYYMMDD() << endl;
        }
        else
        {
//			cout << " -> Not Assignable: "  << ct->getTourId() << " Date: " << ct->getTourDepartureDateTime().GetYYYYMMDD() << endl;
        }
    }
    delete currenttours; currenttours = NULL;
}

// ------------------------------------------------------------------------------------------- //
void testTourManager_determineFollowingTour()
{
    SessionUtil session(33);
    pxOrderTransmit* xmit = session.get();
    short branchno = 33;
    long customerno = 19063;

    CSCCustomer* customer = new CSCCustomer( xmit->Session(), branchno, customerno );
    customer->Read();
    pxCommType* commtype = new pxCommType(xmit->Session(), '0', branchno);

    TourManager* tourman = new TourManager( xmit->Session(), 0, branchno, customerno, commtype, "NO" );

    //cout << "Using BranchNo " << branchno << " and CustomerNo " << customerno << endl;

    TourInfo y = tourman->determineTour();
    //cout << "Current Tour Information: " << endl;
    showTourInfo( y );

    TourInfo x = tourman->determineFollowingTour(&y);
    //cout << "Following Tour Information: " << endl;
    showTourInfo( x );

    delete tourman;
    delete customer;
    delete commtype;

}

// ------------------------------------------------------------------------------------------- //
void testTourManager()
{
    SessionUtil session(33);
    pxOrderTransmit* xmit = session.get();
    short branchno = 33;
    int customerno = 19063;
    long cscorderno = 1000000;
    long posno = 0;

    CSCCustomer* customer = new CSCCustomer( xmit->Session(), branchno, customerno );
    customer->Read();
    pxCommType* commtype = new pxCommType(xmit->Session(), '0', branchno);
    TourManager* tourman = new TourManager( xmit->Session(), 0, branchno, customerno, commtype, "NO" );
    pxOrderItemTourList* oit = new pxOrderItemTourList( xmit->Session() );

    // ibt tour determination
    {
        posno++;
 //       cout << "\nIBT Tour Determination" << endl;
        tourman->resetArgInjections();
        tourman->injectNewOrderFlag( true );
        tourman->injectIBTBranchNo( 31 );
        tourman->injectIBTTypeArticle( 1 );
        TourInfo ti = tourman->determineTour();
        oit->RemoveOrderItemTour( cscorderno, posno );
        CHECK(oit->IsGoodState());
        oit->AddOrderItemTour( cscorderno, posno, ti );
        CHECK(oit->IsGoodState());
    }

    // ibt tour determination private assortment
    {
        posno++;
//        cout << "\nIBT Tour Determination Private Assortment" << endl;
        tourman->resetArgInjections();
        tourman->injectNewOrderFlag( true );
        tourman->injectIBTBranchNo( 27 );
        tourman->injectIBTTypeArticle( 2 );
        TourInfo ti = tourman->determineTour();
        oit->RemoveOrderItemTour( cscorderno, posno );
        CHECK(oit->IsGoodState());
        oit->AddOrderItemTour( cscorderno, posno, ti );
        CHECK(oit->IsGoodState());
    }

    // normal tour determination
    {
        posno++;
//        cout << "\nNormal Tour Determination" << endl;
        tourman->resetArgInjections();
        tourman->injectNewOrderFlag( true );
        TourInfo ti = tourman->determineTour();
        oit->RemoveOrderItemTour( cscorderno, posno );
        CHECK(oit->IsGoodState());
        oit->AddOrderItemTour( cscorderno, posno, ti );
        CHECK(oit->IsGoodState());
    }

    // specific tour determination
    {
        posno++;
        nString desiredtour("200201");
//        cout << "\nDesired Tour (" << desiredtour << ") Tour Determination" << endl;
        tourman->resetArgInjections();
        tourman->injectNewOrderFlag( true );
        tourman->injectDesiredTourId( desiredtour );
        TourInfo ti = tourman->determineTour();
        oit->RemoveOrderItemTour( cscorderno, posno );
        CHECK(oit->IsGoodState());
        oit->AddOrderItemTour( cscorderno, posno, ti );
        CHECK(oit->IsGoodState());
    }

    // future tour determination
    {
        posno++;
        nDate testdate(2015, 3, 12);
//        cout << "\nFuture (" << testdate.GetYYYYMMDD() << ") Tour Determination" << endl;
        tourman->resetArgInjections();
        tourman->injectNewOrderFlag( true );
        tourman->injectDeliveryDate( testdate );
        TourInfo ti = tourman->determineTour();
        oit->RemoveOrderItemTour( cscorderno, posno );
        CHECK(oit->IsGoodState());
        oit->AddOrderItemTour( cscorderno, posno, ti );
        CHECK(oit->IsGoodState());
    }


    // future specific tour determination
    {
        posno++;
        nDate testdate(2015, 3, 12);
        nString desiredtour("200201");
 //       cout << "\nFuture (" << testdate.GetYYYYMMDD() << ") Desired Tour (" << desiredtour << ") Tour Determination" << endl;
        tourman->resetArgInjections();
        tourman->injectNewOrderFlag( true );
        tourman->injectDeliveryDate( testdate );
        tourman->injectDesiredTourId( desiredtour );
        TourInfo ti = tourman->determineTour();
        showTourInfo( ti );
        oit->RemoveOrderItemTour( cscorderno, posno );
        oit->AddOrderItemTour( cscorderno, posno, ti );
    }

    delete oit;
    delete tourman;
    delete commtype;
}



// ------------------------------------------------------------------------------------------- //

SUITE(TourManager)
{
    TEST(ReturnsTourDeterminationForCustomer)
    {
        testReturnsTourDeterminationForCustomer();
    }


    TEST(TourDeterminationForCustomer)
    {
        testTourDeterminationForCustomer();
    }

    TEST_FIXTURE(TourAssignabilityFixture, TourAssignability)
    {
        testTourAssignability(moc.getBranchNo(), customerno);
    }

    TEST(TourManager_determineFollowingTour)
    {
        testTourManager_determineFollowingTour();
    }

    TEST(TourManager)
    {
        testTourManager();
    }
}

