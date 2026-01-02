#include "shipmenttracking/shipmenttrackingutils.h"
#include "shipmenttrackingetaanddeliverydatasqlmapper.h"
#include "shipmenttrackingetaanddeliverydata.h"

#include <libbasarcmnutil_timespan.h>
#include <util/loggingutils.h>

#include <string>       // std::string
#include <sstream>      // std::stringstream
#include <iterator>     // std:ostream_iterator
#include <boost/make_shared.hpp>

namespace libcsc {
namespace shipmenttracking {


ShipmentTrackingEtaAndDeliveryDataSQLMapper::ShipmentTrackingEtaAndDeliveryDataSQLMapper(ShipmentTrackingEtaAndDeliveryDataPtr shipmentTrackingEtaAndDeliveryData) :
    ShipmentTrackingEtaAndDeliveryDataMapperBase(shipmentTrackingEtaAndDeliveryData)
{
}


ShipmentTrackingEtaAndDeliveryDataSQLMapper::~ShipmentTrackingEtaAndDeliveryDataSQLMapper()
{
}

//----------------------------------------------------------------------------------
// Get SQL Statement to query Shipment Tracking ETA and "Delivered at" Information from Warehouse database
//----------------------------------------------------------------------------------
const basar::VarString ShipmentTrackingEtaAndDeliveryDataSQLMapper::getSelectSQL(
    const basar::VarString& dbNameWarehouse,
    const std::list<basar::Int32>& pickingDateList,
    const std::list<basar::VarString>& trackingBarcodeList,
    const basar::VarString& transmedStatusDeliveredToCustomerIds
)
{
    if (pickingDateList.size() < 1)
    {
        throw basar::Exception(basar::ExceptInfo("ShipmentTrackingEtaAndDeliveryDataSQLMapper::getSelectSQL()", "pickingDateList is empty. Nothing to look for!", __FILE__, __LINE__), "");
    }
    if (trackingBarcodeList.size() < 1)
    {
        throw basar::Exception(basar::ExceptInfo("ShipmentTrackingEtaAndDeliveryDataSQLMapper::getSelectSQL()", "trackingBarcodeList is empty. Nothing to look for!", __FILE__, __LINE__), "");
    }

    std::string pickingDatesStr = stringJoin(pickingDateList, ", ");
    std::string trackingBarcodesStr = stringJoin(trackingBarcodeList, "', '"); //NOTE: the "'" + ... + "'" left and right decoration is done rather down in the SQL statement


    // ----------------------
    // -- THE RIGHT STATEMENT to get ETA and DeliveredAt DateTime!
    // -- NOTE: Max 2 different PickingDates found for a tour of a single customer and branchno; and there were only 12 such cases in a range of: a.datum between 20201008 and 202010012
    //
    // SELECT 
    // (SELECT eta_tseta FROM 
    //  (SELECT FIRST 1 ei.eta_tseta FROM etatransmed ei 
    //   WHERE ei.pickingdate in (20200926, 20200928 , 99991231)                -- looking for 99991231 is a workaround for PINT and sometimes Transmed problems with LF-CSV files
    //   AND ei.eta_barcode in ('44089375126006359017', '44089375128000750029') -- looking for several barcodes is due to fact, that the data is sometimes missing for a specific barcode
    //   ORDER BY ei.eta_tsexport DESC
    //  )
    // )::DATETIME YEAR TO FRACTION AS tseta --  <- NOTE: this can be NULL!
    // , 
    // (SELECT ScanTransferDateTime FROM 
    //  (SELECT FIRST 1 tts.ScanTransferDateTime FROM transmedtotestatus tts 
    //   WHERE tts.pickingdate in (20200926, 20200928 , 99991231)                    -- looking for 99991231 is a workaround for PINT and sometimes Transmed problems with LF-CSV files
    //   AND tts.trackingbarcode in ('44089375126006359017', '44089375128000750029') -- looking for several barcodes is due to fact, that the data is sometimes missing for a specific barcode
    //   AND tts.stateid IN (SELECT ts.id FROM transmedstatus ts 
    //                      JOIN transmedstatuscategory tc ON tc.id=ts.categoryid 
    //                      WHERE tc.description='DeliveredToCustomer' ) 
    //   ORDER BY tts.ScanTransferDateTime ASC 
    //  )
    // )::DATETIME YEAR TO FRACTION AS DeliveredAt --  <- NOTE: this can be NULL!
    // FROM systables s
    // WHERE s.tabid=1

    std::stringstream sSql;

    sSql <<
        "SELECT "
        "(SELECT eta_tseta FROM "
        " (SELECT FIRST 1 ei.eta_tseta FROM " << dbNameWarehouse << ":etatransmed ei "
        "  WHERE ei.pickingdate in (" << pickingDatesStr << ", 99991231) "  // looking for 99991231 is a workaround for PINT and sometimes Transmed problems with LF - CSV files
        "  AND ei.eta_barcode in ('" << trackingBarcodesStr << "') "          // looking for several barcodes is due to fact, that the data is sometimes missing for a specific barcode
        "  ORDER BY ei.eta_tsexport DESC "
        " ) "
        ")::DATETIME YEAR TO FRACTION AS tseta "        //  <-NOTE: this can be NULL!
        ", "
        "(SELECT ScanTransferDateTime FROM "
        " (SELECT FIRST 1 tts.ScanTransferDateTime FROM " << dbNameWarehouse << ":transmedtotestatus tts "
        "  WHERE tts.pickingdate in (" << pickingDatesStr << ", 99991231) " // looking for 99991231 is a workaround for PINT and sometimes Transmed problems with LF - CSV files
        "  AND tts.trackingbarcode in ('" << trackingBarcodesStr << "') "     // looking for several barcodes is due to fact, that the data is sometimes missing for a specific barcode
        "  AND tts.stateid IN ("
        //NOTE: due to an INFORMIX DB internall bug: "Wrong Result of Nested SQL select when using cross DB call from Ode21 to Wde21" I had to replace this nested query with the cached list of states:
        //"                      SELECT ts.id FROM " << dbNameWarehouse << ":transmedstatus ts "
        //"                      JOIN " << dbNameWarehouse << ":transmedstatuscategory tc ON tc.id=ts.categoryid "
        //"                      WHERE tc.description='DeliveredToCustomer' "
        "                      " << transmedStatusDeliveredToCustomerIds << " "
        "                     ) "
        "  ORDER BY tts.ScanTransferDateTime ASC "
        " )"
        ")::DATETIME YEAR TO FRACTION AS DeliveredAt "  //   <-NOTE: this can be NULL!
        "FROM systables s "
        "WHERE s.tabid=1 "
        ;
        
    return sSql.str();
}

//----------------------------------------------------------------------------------
// Mapping Shipment Tracking ETA and Delivery Data from Warehouse database
//----------------------------------------------------------------------------------
void ShipmentTrackingEtaAndDeliveryDataSQLMapper::doMapTimesAndComputeDelay(const basar::DateTime& plannedTimeOfArrival, EtaDelayPresentationPtr etaDelayPresentation, EtaDelayEvaluationCollection etaDelayEvaluationCollection)
{
    METHODNAME_DEF(ShipmentTrackingEtaAndDeliveryDataSQLMapper, doMapTimesAndComputeDelay);
    BLOG_TRACE_METHODEX(libcsc::LoggerPool::getLoggerShipmentTracking(), fun << plannedTimeOfArrival);

    if (m_ResultSet.isNull())
    {
        throw basar::Exception(basar::ExceptInfo("ShipmentTrackingEtaAndDeliveryDataSQLMapper::doMapShipmentTrackingEtaAndDeliveryData()", "m_ResultSet is Null!", __FILE__, __LINE__), "");
    }

    setEstimatedTimeOfArrival   (m_ResultSet.getDateTime("tseta"));                   // <- etatransmed.eta_tseta
    setDeliveredAt              (m_ResultSet.getDateTime("deliveredat"));             // <- TransmedToteStatus.ScanTransferDateTime WHERE StateId IN (6, 7, 20, 21, 44, 45, 49, 55)

                                                                        // Compute the estimated Delay:
    computeDelay(plannedTimeOfArrival, etaDelayPresentation, etaDelayEvaluationCollection);
}

void ShipmentTrackingEtaAndDeliveryDataSQLMapper::doSetTimesAndDelayFallback(EtaDelayEvaluationCollection etaDelayEvaluationCollection)
{
    METHODNAME_DEF(ShipmentTrackingEtaAndDeliveryDataSQLMapper, doSetTimesAndDelayFallback);
    BLOG_TRACE_METHODEX(libcsc::LoggerPool::getLoggerShipmentTracking(), fun);

    // Old fallback was: no data means = NO DELAY knonw => report no Delay: ... so set:
    //basar::DateTime myCurrent(basar::Date::getCurrent());
    //myCurrent.setTime(0, 0, 0, 0);  //NOTE: <- this is a must! Else the time part is invalid... See Basar....
    //setEstimatedTimeOfArrival   (myCurrent);    // <- TODAY

	basar::VarString delayText = etaDelayEvaluationCollection.front()->getDelayText();
    basar::DateTime invalidDateTime;
    invalidDateTime.setInvalid();

    setEstimatedTimeOfArrival   (invalidDateTime);    // <- invalid
    setDeliveredAt              (invalidDateTime);    // <- invalid

    setEstimatedTimeOfArrivalMin(invalidDateTime);    // <- invalid
    setEstimatedTimeOfArrivalMax(invalidDateTime);    // <- invalid

    setDelayInMinutes           (0);                  // <- not set
   // setDelayInfo                (basar::VarString()); // <- not set
	setDelayInfo(delayText);
}

void ShipmentTrackingEtaAndDeliveryDataSQLMapper::computeDelay(const basar::DateTime& plannedTimeOfArrival, EtaDelayPresentationPtr etaDelayPresentation, EtaDelayEvaluationCollection etaDelayEvaluationCollection)
{
    METHODNAME_DEF(ShipmentTrackingEtaAndDeliveryDataSQLMapper, computeDelay);
    BLOG_TRACE_METHODEX(libcsc::LoggerPool::getLoggerShipmentTracking(), fun << plannedTimeOfArrival);

    // Compute the estimated Delay:

    basar::DateTime minEtaOrDeliveredAtDateTime;

    // --------
    // 1st check if the EstimatedTimeOfArrival is valid and set defaults and quit if no:
    bool etaIsValid = m_EtaAndDeliveryData->getEstimatedTimeOfArrival().isValid();
    if (!etaIsValid)
    {
        // in this case, no delay can be estimated, so quit now.
        basar::DateTime invalidDateTime;
        invalidDateTime.setInvalid();

        setEstimatedTimeOfArrivalMin(invalidDateTime);      // <- invalid
        setEstimatedTimeOfArrivalMax(invalidDateTime);      // <- invalid
    }
    else
    {
        // --------
        // Min ETA:
        basar::DateTime minEta = m_EtaAndDeliveryData->getEstimatedTimeOfArrival();

        // rm seconds and milliseconds:
        basar::TimeSpan::Numeric secsAndMsecsNumeric;
        secsAndMsecsNumeric.seconds = minEta.getSec();
        secsAndMsecsNumeric.fraction = minEta.getMSec();
        //secsAndMsecsNumeric.isNegative = true;

        basar::TimeSpan secsAndMsecs;
        secsAndMsecs.fromNumeric(secsAndMsecsNumeric);

        minEta -= secsAndMsecs;

        // round up to the next RoundingTo minutes:
        int oriMinutes = minEta.getMinute();
        int roundingMinutes = oriMinutes + etaDelayPresentation->getRoundingTo();
        roundingMinutes /= etaDelayPresentation->getRoundingTo();
        roundingMinutes *= etaDelayPresentation->getRoundingTo();
        int deltaMins2add = roundingMinutes - oriMinutes;

        // update minEta to the required rounding:
        minEta += basar::TimeSpan(deltaMins2add, basar::TimeSpan::TSUNIT_MIN);

        setEstimatedTimeOfArrivalMin(minEta);               // <- rounded to the next etaDelayPresentation->getRoundingTo() minutes

                                                            // --------
                                                            // Max ETA:
        basar::DateTime maxEta = minEta + basar::TimeSpan(etaDelayPresentation->getArrivalTimeFrameInMinutes(), basar::TimeSpan::TSUNIT_MIN);

        setEstimatedTimeOfArrivalMax(maxEta);                   // <- added arrival time frame to the minEta

                                                                // take minEta for delay computation:
        minEtaOrDeliveredAtDateTime = minEta;
    }

    bool deliveredAtIsValid = m_EtaAndDeliveryData->getDeliveredAt().isValid();
	basar::VarString delayText = etaDelayEvaluationCollection.front()->getDelayText();

    if (deliveredAtIsValid)
    {
        // take minEta for delay computation:
        minEtaOrDeliveredAtDateTime = m_EtaAndDeliveryData->getDeliveredAt();

        // rm seconds and milliseconds:
        basar::TimeSpan::Numeric secsAndMsecsNumeric;
        secsAndMsecsNumeric.seconds = minEtaOrDeliveredAtDateTime.getSec();
        secsAndMsecsNumeric.fraction = minEtaOrDeliveredAtDateTime.getMSec();
        //secsAndMsecsNumeric.isNegative = true;

        basar::TimeSpan secsAndMsecs;
        secsAndMsecs.fromNumeric(secsAndMsecsNumeric);

        minEtaOrDeliveredAtDateTime -= secsAndMsecs;
    }
    else if (!etaIsValid) // if there is no ETA and no DeliveredAt, then set defaults and quit:
    {
        setDelayInMinutes       (0);                    // <- not set
        //setDelayInfo            (basar::VarString());   // <- not set
		setDelayInfo(delayText);
        return;
    }


    // --------
    // check if the PlannedTimeOfArrival is valid and set defaults and quit if no:
    if (!plannedTimeOfArrival.isValid())
    {
        // in this case, no delay can be estimated, so quit now.
        setDelayInMinutes(0);                   // <- not set
        //setDelayInfo(basar::VarString());       // <- not set
		setDelayInfo(delayText);
        return;
    }


    // --------
    // Delivery Delay Delta:
    basar::TimeSpan deliveryDelay = minEtaOrDeliveredAtDateTime - plannedTimeOfArrival;

    basar::TimeSpan::Numeric deliveryDelayNumeric = deliveryDelay.toNumeric();
    int delayInMinutes =
        deliveryDelayNumeric.days * basar::TimeSpan::MINUTES_PER_DAY +
        deliveryDelayNumeric.hours * basar::TimeSpan::MINUTES_PER_HOUR +
        deliveryDelayNumeric.minutes
        ;

    if (deliveryDelayNumeric.isNegative)
    {
        delayInMinutes *= -1;
    }

    setDelayInMinutes(delayInMinutes);           // <- computed DelayInMinutes = EstimatedTimeOfArrivalMin (the rounded ETA time!) - PlannedTimeOfArrival. DelayInMinutes is the base for estimating the DelayText.

                                                 // set delayText to fallback -> to the worst case, if not hit during lookup:
    delayText = etaDelayEvaluationCollection.back()->getDelayText();

    // lookup:
    for (EtaDelayEvaluationCollection::const_iterator iter = etaDelayEvaluationCollection.begin();
        iter != etaDelayEvaluationCollection.end();
        iter++
        )
    {

		if ((*iter)->getUpToDelayedMinutes() <= -999)
		{
			continue;
		}

        if ((*iter)->getUpToDelayedMinutes() >= delayInMinutes)
        {
            delayText = (*iter)->getDelayText();
            break;
        }
    }

    setDelayInfo(delayText);
}


} // end namespace shipmenttracking
} // end namespace libcsc
