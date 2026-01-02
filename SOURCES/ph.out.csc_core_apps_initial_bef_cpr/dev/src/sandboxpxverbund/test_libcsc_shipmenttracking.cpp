#include <UnitTest++/UnitTest++.h>
#include "FixtureBase.h"
#include <shipmenttracking/componentmanager/shipmenttrackingcomponentmanager.h>
#include <shipmenttracking/shipmenttrackingrepository.h>

using namespace libcsc::shipmenttracking;

class ShipmenttrackingFixture : public FixtureBase
{
public:
    ShipmenttrackingFixture() : FixtureBase(5) // any random german branch to get a german session
    {
        // Do NOT RELY ON THIS BRANCH NO of the session as we use random branches in the tests!
    }

    ShipmentTrackingComponentManagerPtr getShipmentTrackingComponentManager()
    {
        pxOrderTransmit* xmit = _session.get();
        if (xmit == NULL)
        {
            std::cout << "Exception: Session is not initialized." << std::endl;
            throw;
        }
        return xmit->getShipmentTrackingComponentManager();
    }
};

SUITE(Shipmenttracking)
{
    TEST_FIXTURE(ShipmenttrackingFixture, FindTourIDs)
    {
        // Find any existing query data for the test
        std::stringstream ss;
        ss << "SELECT FIRST 1 vertriebszentrumnr, datumkommi "
           << "FROM tourplantag "
           << "WHERE tourinaktiv = '0' AND tourinaktiv <> '1';";

        basar::db::sql::ResultsetRef result = _session.doSelect(ss.str());
        if (!result.next())
        {
            std::cout << "No tour for shipmenttracking found in database." << std::endl;
            throw;
        }

        ShipmentTrackingDataFilter filter;

        // TEST
        const std::vector<std::string> tourIDs =
            getShipmentTrackingComponentManager()->getShipmentTrackingRepository()->findTourIDs(result.getInt16("vertriebszentrumnr"), result.getInt32("datumkommi"), filter);

        CHECK(tourIDs.size() > 0);
    }

    TEST_FIXTURE(ShipmenttrackingFixture, FindShipmentTracking)
    {
        // Find any existing query data for the test
        std::stringstream ss;
        ss << "SELECT FIRST 1 a.vertriebszentrumnr, a.kundennr "
           << "FROM kdauftrag a "
           << "JOIN kdauftragereignis e110 ON e110.kdauftragnr = a.kdauftragnr AND e110.ereignisart = 110 "
           << "JOIN kdauftragpos p ON p.kdauftragnr = a.kdauftragnr "
           << "JOIN kdauftragpostour ta ON ta.kdauftragnr = a.kdauftragnr AND ta.posnr = 0 AND ta.deliverybranchno = 0 "
           << "JOIN artikelzentral az ON az.artikel_nr = p.artikel_nr "
           << "LEFT JOIN ibtrequest i ON i.branchno = a.vertriebszentrumnr AND i.cscorderno = a.kdauftragnr AND i.cscorderposno = p.posnr "
           << "      AND to_char(i.creationdatetime, '%Y%m%d') >= e110.datum AND i.customerno = a.kundennr "
           << "LEFT JOIN ibtresponse ir ON ir.ibtrequestid = i.ibtrequestid "
           << "WHERE a.kdauftragart <> 'PR' AND NVL(ir.ibtconfirmedqty, p.mengegeliefert) > 0;";

        basar::db::sql::ResultsetRef result = _session.doSelect(ss.str());
        if (!result.next())
        {
            std::cout << "No order for shipmenttracking found in database." << std::endl;
            throw;
        }

        ShipmentTrackingDataFilter filter;

        // TEST
        const ShipmentTrackingTourInformationCollectionPtr shipmentTrackingTourInformations =
            getShipmentTrackingComponentManager()->getShipmentTrackingRepository()->findShipmentTracking(result.getInt16("vertriebszentrumnr"), result.getInt32("kundennr"), filter);

        CHECK(shipmentTrackingTourInformations->size() > 0);
    }

    TEST_FIXTURE(ShipmenttrackingFixture, FindIDFsforTourIDs)
    {
        // Find any existing query data for the test
        std::stringstream ss;
        ss << "SELECT FIRST 10 tpt.tourid, tpt.vertriebszentrumnr, tpt.datumkommi "
           << "FROM tourplantag tpt "
           << "WHERE tpt.idfnr IN (SELECT DISTINCT(IDFNR) from kdauftrag kd WHERE kd.filialnr = tpt.vertriebszentrumnr) "
           << "ORDER BY tpt.vertriebszentrumnr, tpt.idfnr, tpt.datumkommi;";

        basar::db::sql::ResultsetRef result = _session.doSelect(ss.str());

        short branchno = 0;
        int tourdate;
        std::vector<std::string> tourIDList;
        while (result.next())
        {
            short nextBranchno = result.getInt16("vertriebszentrumnr");
            int nextTourdate = result.getInt32("datumkommi");

            if (branchno == 0)
            {
                branchno = nextBranchno;
                tourdate = nextTourdate;
            }
            if ((branchno != nextBranchno) && (tourdate != nextTourdate))
            {
                break; // we only need tourids of one distinct entry
            }
            tourIDList.push_back(result.getString("tourid"));
        }
        if (branchno == 0)
        {
            std::cout << "No tour IDs for shipmenttracking found in database." << std::endl;
            throw;
        }

        ShipmentTrackingDataFilter filter;

        // TEST
        const std::map<std::string, std::vector<int> > idfsforTourIDs =
            getShipmentTrackingComponentManager()->getShipmentTrackingRepository()->findIDFsforTourIDs(branchno, tourdate, filter, tourIDList);

        CHECK(idfsforTourIDs.size() > 0);
    }
}
