#include "shipmenttrackingcurrentwhslinecontext.h"
#include "shipmenttrackingpackageinformationsqlmapper.h"
#include "shipmenttracking/shipmenttrackingrequestprocessingcontext.h"
#include "shipmenttracking/packageinformation/shipmenttrackingtotepositiontolinebuildermapper.h"

#include <util/loggingutils.h>
#include <boost/make_shared.hpp>


namespace libcsc {
namespace shipmenttracking {

/////////////////////////////////////////////////////////////////////////////////////
// Factory method
/////////////////////////////////////////////////////////////////////////////////////
ShipmentTrackingCurrentWhsLineContextPtr ShipmentTrackingCurrentWhsLineContext::create(
    ShipmentTrackingRequestProcessingContextPtr context,
    const basar::db::sql::ResultsetRef resultSet,
    int resultSetRowPosition
)
{
    METHODNAME_DEF(ShipmentTrackingCurrentWhsLineContext, create);
    BLOG_TRACE_METHODEX(libcsc::LoggerPool::getLoggerShipmentTracking(), fun);

    if (context.get() == NULL)
    {
        throw basar::Exception(basar::ExceptInfo(fun, "context is Null!", __FILE__, __LINE__), "");
    }

    if (resultSet.isNull())
    {
        throw basar::Exception(basar::ExceptInfo(fun, "resultSet is Null!", __FILE__, __LINE__), "");
    }


    ShipmentTrackingCurrentWhsLineContext *currentWhsLineContextRawCppPointer = 
        new ShipmentTrackingCurrentWhsLineContext(
            context,
            resultSet,
            resultSetRowPosition
            );

    ShipmentTrackingCurrentWhsLineContextPtr currentWhsLineContext(currentWhsLineContextRawCppPointer);

    currentWhsLineContext->initialize();

    return currentWhsLineContext;
}

ShipmentTrackingCurrentWhsLineContext::ShipmentTrackingCurrentWhsLineContext(
    ShipmentTrackingRequestProcessingContextPtr context,
    const basar::db::sql::ResultsetRef resultSet,
    int resultSetRowPosition
) :
    m_Context(context),
    m_ResultSet(resultSet),
    m_ResultSetRowPosition(resultSetRowPosition),
    m_PackageId(0),
    m_CscOrderNo(0),
    m_PickingOrderNo(0),
    m_PickingOrderPageNo(0),
    m_DeliveryDurationInMin(0),
    m_IsIbtLocal(false),
    m_IsContentChanged(false),
    m_IsTourRedirected(false),
    m_IsDeleted(false),
    m_TotePosNr(0),
    m_ArticleNr(0),
    m_WhsOriginalQuantity(0),
    m_IsContainer(false),
    m_IsNarcotic(false),
    m_IsFirstTotePositionLine(false),
    m_IbtOrderPosNr(0)
{
}

void ShipmentTrackingCurrentWhsLineContext::initialize()
{
    METHODNAME_DEF(ShipmentTrackingCurrentWhsLineContext, initialize);
    BLOG_TRACE_METHODEX(libcsc::LoggerPool::getLoggerShipmentTracking(), fun);

    // read PackageInfo
    m_TrackingBarcode = m_ResultSet.getString("tsv_vsw_tm_barcode");    // <- dktsv.tsv_vsw_tm_barcode
    m_PackageId = m_ResultSet.getInt32("tsv_wannennr");                 // <- dktsv.tsv_wannennr == ToteNo
    m_CscOrderNo = m_ResultSet.getInt32("tsv_cscorderno");              // <- it could be the Customer-CscOrderNo, or the IBT-CscOrderNo

    if (m_Context->Filter.SendPickingOrderNumbers)
    {
        m_PickingOrderNo = m_ResultSet.getInt32("tsv_vsw_la");              // <- dktsv.tsv_vsw_la    == WarehouseOrderNo
        m_PickingOrderPageNo = m_ResultSet.getInt16("tsv_vsw_seite");       // <- dktsv.tsv_vsw_seite == WarehouseOrderPageNo
    }

    m_Kzlk = m_ResultSet.getString("tsv_vsw_kzlk");
    
    m_ToteState = m_ResultSet.getString("tsv_status");                  // <- dktsv.tsv_status == 1 -> means "Gutschrift", i.e. some tote articles have less quantity, than confirmed in CSC Oder! One value for Normal local, IBT Remote or Local case. Picking is done just once!
    
    m_TourId = m_ResultSet.getString("tsv_tour");                       // <- dktsv.tsv_tour
    m_RedirectedFromTourId = m_ResultSet.getString("tsv_vsw_rtour");    // <- dktsv.tsv_vsw_rtour
    m_DeliveryDurationInMin = m_ResultSet.getInt32("tsv_fahrzeit");     // <- dktsv.tsv_fahrzeit
    m_InsertDateTime = m_ResultSet.getDateTime("insertdatetime");       // <- dktsv.insertdatetime

    m_IsContainer = m_ResultSet.getInt32("isContainer") == 1;           // <- d.tsv_vsw_beipack='J'
    m_IsNarcotic = m_ResultSet.getInt32("isNarcotic") == 1;             // <- d.tsv_vsw_btm='J'

    // read LineDetail info:
    if (m_Context->Filter.DetailsDesired)
    {
        m_TotePosNr = m_ResultSet.getInt16("tsv_pos");    // <- dktsv.tsv_pos
        m_ArticleNr = m_ResultSet.getInt32("tsv_kop_pzn");              // <- dktsv.tsv_kop_pzn (== (a)kdauftragpos.artikel_nr) -> used for JOINing DKTSV lines
        m_WhsOriginalQuantity = m_ResultSet.getInt32("tsv_kop_omenge"); // <- the DKTSV.tsv_kop_omenge is the "original quantity to pick" == [Outbound:] NVL(ibtresponse.ibtconfirmedqty, (a)kdauftragpos.mengegeliefert) [the equation shall be given!]
    }
    else
    {
        m_ArticleNr = m_IsNarcotic ? 1 : 0;
    }


    // -------------------
    // derived properties:
    m_IsIbtLocal = m_Kzlk == "V";

    if (m_IsIbtLocal)
    {
        m_TotePosNr = 0;  // manual correction. TotePosNo has not meaning for DKTSV.Kzlk == "V" records
    }

    std::stringstream whsPackageInfoKeyStrm;
    whsPackageInfoKeyStrm << m_TrackingBarcode << "-" << m_PackageId;
    m_WhsPackageInfoKey = whsPackageInfoKeyStrm.str();

    // get the ToteState -> it is important for reading the line details correctly!
    m_IsContentChanged = m_ToteState == "1";
    m_IsTourRedirected = m_RedirectedFromTourId.find_first_not_of(' ') != std::string::npos; //NOTE: tour redirected can be also a line with toteState == "1" !!
    if (m_ToteState == "0" && m_IsTourRedirected)
    {
        m_ToteState = "8"; // implying from data. Why: the state "8" is only set in one command DKTSV row with no line data, but not in the content rows, i.e. lines....
    }

    m_IsDeleted = m_ToteState == "9";
}


} // end namespace shipmenttracking
} // end namespace libcsc


std::ostream& operator<<(std::ostream& os, const libcsc::shipmenttracking::ShipmentTrackingCurrentWhsLineContext& currentWhsLineContext)
{
    os << "ST-CurrentWhsLineContext: {"
        << "ResultSetRowPosition: " << currentWhsLineContext.getResultSetRowPosition()
        << ", TrackingBarcode: " << currentWhsLineContext.getTrackingBarcode()
        << ", PackageId: " << currentWhsLineContext.getPackageId()
        << ", CscOrderNo: " << currentWhsLineContext.getCscOrderNo()
        << ", PickingOrderNo: " << currentWhsLineContext.getPickingOrderNo()
        << ", PickingOrderPageNo: " << currentWhsLineContext.getPickingOrderPageNo()
        << ", Kzlk: " << currentWhsLineContext.getKzlk()
        << ", ToteState: " << currentWhsLineContext.getToteState()
        << ", TourId: " << currentWhsLineContext.getTourId()
        << ", RedirectedFromTourId: " << currentWhsLineContext.getRedirectedFromTourId()
        << ", DeliveryDurationInMin: " << currentWhsLineContext.getDeliveryDurationInMin()
        << ", InsertDateTime: " << currentWhsLineContext.getInsertDateTime()
        << ", isIbtLocal: " << currentWhsLineContext.isIbtLocal()
        << ", isContentChanged: " << currentWhsLineContext.isContentChanged()
        << ", isTourRedirected: " << currentWhsLineContext.isTourRedirected()
        << ", isDeleted: " << currentWhsLineContext.isDeleted()
        << ", TotePosNr: " << currentWhsLineContext.getTotePosNr()
        << ", ArticleNr: " << currentWhsLineContext.getArticleNr()
        << ", WhsOriginalQuantity: " << currentWhsLineContext.getWhsOriginalQuantity()
        << ", isContainer: " << currentWhsLineContext.isContainer()
        << ", isNarcotic: " << currentWhsLineContext.isNarcotic()
        << ", isFirstTotePositionLine: " << currentWhsLineContext.isFirstTotePositionLine()
        << ", IbtOrderPosNr: " << currentWhsLineContext.getIbtOrderPosNr()
        << "}";
    ;
    return os;
}

std::ostream& operator<<(std::ostream& os, const libcsc::shipmenttracking::ShipmentTrackingCurrentWhsLineContext* currentWhsLineContext)
{
    if (currentWhsLineContext != NULL)
    {
        os << *currentWhsLineContext;
    }
    else
    {
        os << "ST-CurrentWhsLineContext: <null>";
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const libcsc::shipmenttracking::ShipmentTrackingCurrentWhsLineContextPtr currentWhsLineContext)
{
    os << currentWhsLineContext.get();
    return os;
}

