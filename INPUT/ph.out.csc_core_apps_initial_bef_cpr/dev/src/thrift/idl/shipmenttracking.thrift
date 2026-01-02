include "cscbase.thrift"

namespace cpp warehouse.shipmenttracking
namespace csharp Warehouse.ShipmentTracking


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Shipment Tracking - Track and Trace
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct ShipmentTrackingDataFilter
{
    /* NOTE: According date props: ToteDeliveryDate and PickingDate:
       Just one and only one of the dates: ToteDeliveryDate or PickingDate must be provided.
       Value interval for both: <Min, Max> i.e. including the Max, i.e. the invalid date: 99991231.
       NOTE: Dates interpretation:
             1) if ToteDeliveryDate is set to a valid date, the PickingDate must be set to an invalid date! PickingDate will (thus) be ignored in this case.
                ToteDeliveryDate can be a past, current or future date. There can be totes, wchich will be shipped tomorrow, or next week etc. And of course one can request an overview of totes in the past.
             2) if ToteDeliveryDate is set to a *INVALID* date (Max), the PickingDate will be taken into accont. Its value will be interpreted as follows:
                - A PickingDate for past, i.e. for yesterday and older dates: the query will look up just the Archive - starting with archive table "akdauftrag".
                - A PickingDate for current day or valid future date: the query will look up just the current, not yet archived orders: i.e. closed and not yet closed orders in starting with curent table "kdauftrag".
                - A PickingDate is an invalid date (Max): same query as if PickingDate was set for current day or valid future date.
    */

    1: optional cscbase.Date                           ToteDeliveryDate,                // <- (a)kdauftragpostour.deliverydate. Date for which the customer delivery information has to be fetched, i.e. the date on which the totes are planned to be delivered to the customer.
    2: optional bool                                   DetailsDesired,                  // <- flag indicating if also the line info (ShipmentTrackingLineDetail) is needed or not
    3: optional string                                 SpecificTourID,                  // <- optional: reducing the query to a single tour reated to the desired date: ToteDeliveryDate or PickingDate
    4: optional cscbase.Date                           PickingDate,                     // <- akdauftrag.datum || (kdauftragereignis.datum where kdauftragereignis.ereignisart == 11). Date on which the Customer Order was closed, the Picking was done and Delivery Advice was generated.
    5: optional bool                                   SendPharmosOrderNumbers,         // <- flag indicating if also the PharmosOrderNo is needed or not
    6: optional bool                                   SendPickingOrderNumbers,         // <- flag indicating if also the PickingOrderNo and PickingOrderPageNo is needed or not
    7: optional bool                                   SendPackagePosNos,               // <- flag indicating if also the PackagePosNo is needed or not
}

struct ShipmentTrackingLineDetail
{
    1: optional i32                                     OrderPosNo,                     // <- (a)kdauftragpos.posnr
    2: optional i32                                     ExpectedDeliveryQuantity,       // <- NVL(ibtresponse.ibtconfirmedqty, (a)kdauftragpos.mengegeliefert) ~= (a)kdauftragpos.mengebestaetigt + (a)kdauftragpos.mengenatra /or/ dktsv.tsv_kop_omenge
    3: optional string                                  ArticleCode,                    // <- articlecodes.article_code for (a)kdauftragpos.artikel_nr or dktsv.tsv_kop_pzn
    4: optional string                                  ArticleName,                    // <- artikelzentral.artikel_name / dktsv.tsv_kop_abez
    5: optional bool                                    IsNarcotic,                     // <- bitand(artikelzentral.etartklasse1, 512) = 512 / dktsv.tsv_vsw_btm 'J'/'N'
    6: optional i32                                     ConfirmedDeliveryQuantity,      // <- dktsv.tsv_kop_meng   = quantity after picking -> provided only if different than ExpectedDeliveryQuantity!
    7: optional string                                  Batch,                          // <- dktsv.tsv_kop_charge  -  Chargen-Nummer
    8: optional i32                                     PackagePosNo,                   // <- dktsv.tsv_pos
    9: optional list<string>                            SiblingsSplitInTotes,           // <- list of TrackingBarcodes of other totes, which contain Order Position split siblings of this line. Look for the same ArticleCode and OrderPosNo / PackagePosNo in the other totes. In most cases, this is null!
}
typedef list<ShipmentTrackingLineDetail>                ShipmentTrackingLineDetailList

struct ShipmentTrackingTourData
{
    1: optional string                                  TourId,                         // <- (a)kdauftragpostour.tourid (== dktsv.tsv_tour)
    2: optional cscbase.DateTime                        PlannedTimeOfArrival,           // <- (a)kdauftragpostour.deliverydate + (a)kdauftragpostour.deliverytime OR:
                                                                                        // <- dktsv.tsv_tran_date + (substring(dktsv.tsv_tour, 4) as HH:mm) + dktsv.tsv_fahrzeit UNITS MINUTE
}

struct ShipmentTrackingEtaAndDeliveryData
{
    1: optional cscbase.DateTime                        EstimatedTimeOfArrival,         // <- etatransmed.eta_tseta
    2: optional cscbase.DateTime                        EstimatedTimeOfArrivalMin,      // <- etatransmed.eta_tseta + Rounding
    3: optional cscbase.DateTime                        EstimatedTimeOfArrivalMax,      // <- etatransmed.eta_tseta + Rounding + TimeFrame

    4: optional cscbase.DateTime                        DeliveredAt,                    // <- transmedtotestatus.scantransferdatetime where transmedtotestatus.stateid IN (6, 7, 20, 21, 44, 45, 49, 55) -> i.e. delivered

    5: optional i32                                     DelayInMinutes,                 // <- EstimatedTimeOfArrivalMin - PlannedTimeOfArrival in [Minutes]
    6: optional string                                  DelayInfo,                      // <- a delay text picked up from "etadelayevaluation" config DB table according to DelayInMinutes
}

struct ShipmentTrackingPackageProperties
{
    1: optional i32                                     PackageId,                      // <- dktsv.tsv_wannennr == ToteNo
    2: optional i32                                     CscOrderNo,                     // <- (a)kdauftrag.kdauftragnr as cscOrderNo      (old: N/A)
    3: optional i32                                     PharmosOrderNo,                 // <- (a)kdauftrag.kdauftragnrfiliale as pharmosOrderNo (old wrong: dktsv.tsv_kauf)
    4: optional i32                                     DeliveryAdviceNo,               // <- (a)kdauftrag.rechnungnr as deliveryAdviceNo (old: N/A)
    5: optional i32                                     PickingOrderNo,                 // <- dktsv.tsv_vsw_la    == WarehouseOrderNo
    6: optional i16                                     PickingOrderPageNo,             // <- dktsv.tsv_vsw_seite == WarehouseOrderPageNo
    7: optional cscbase.Date                            OrderClosedOn,                  // <- (a)kdauftragereignis as e11 where e11.ereignisart=11 -> e11.datum
    8: optional cscbase.DateTime                        OrderClosedAt,                  // <- (a)kdauftragereignis as e11 where e11.ereignisart=11 -> e11.datum + e11.zeit
    9: optional cscbase.DateTime                        PickingDoneAt,                  // <- dktsv.insertdatetime
   10: optional string                                  TrackingBarcode,                // <- dktsv.tsv_vsw_tm_barcode

   // ToteState: dktsv.tsv_status == 1 (in WHS: TSV-W-STATUS = Wannenstatus)
   11: optional bool                                    ToteContentChanged,             // <- dktsv.tsv_status == 1 -> means "Gutschrift", i.e. some tote articles have less quantity, than confirmed in CSC Oder! One value for Normal local, IBT Remote or Local case. Picking is done just once!
   12: optional string                                  RedirectedToTourId,             // <- dktsv.tsv_vsw_rtour WHERE dktsv.tsv_tour == (a)kdauftragpostour.tourid; NOTE: see the dktsv.tsv_status == 8 "command" logic. Differentiation of Local and Remote case (IBT / Normal case)
   13: optional string                                  RedirectedFromTourId,           // <- dktsv.tsv_vsw_rtour WHERE dktsv.tsv_tour != (a)kdauftragpostour.tourid; NOTE: see the dktsv.tsv_status == 8 "command" logic. Differentiation of Local and Remote case (IBT / Normal case)
   14: optional cscbase.DateTime                        ToteDeletedAt,                  // <- dktsv.tsv_status == 9 -> Sometimes a tote gets deleted during picking. E.g. because tote is defect. Mostly, but not always the content of a deleted tote is loaded to an another tote. There is just one value for Normal local, IBT Remote or Local case. Tote can be deleted just once!

   // PackageType:   | dktsv.tsv_vsw_beipack | dktsv.tsv_vsw_btm | dktsv.tsv_vsw_seite | all other cases
   // ---------------+-----------------------+-------------------+---------------------+----------------
   // Container      |  'J'                  |                   |                     | 
   // Narcotics      |                       |   'J'             |                     | 
   // AdditionalTote |                       |                   | between 70 and 900  | 
   // Tote           |                       |                   |                     |  X
   15: optional string                                  PackageType,                    // <- dktsv.tsv_vsw_beipack / dktsv.tsv_vsw_btm / dktsv.tsv_vsw_seite / DKTSV: all other cases => "Tote"
}

struct ShipmentTrackingIbtInformation
{
    1: optional i16                                     BranchNo,                       // <- IBT: (a)kdauftrag.filialnr
    2: optional i32                                     CustomerNo,                     // <- IBT: (a)kdauftrag.idfnr

    3: optional ShipmentTrackingPackageProperties       PackageProperties,              // <- IBT: all relevant IBT info for the package

    4: optional ShipmentTrackingTourData                TourData,

    //NOTE: IBT EtaAndDeliveryData is neither needed, nor provided yet by any system, but possible in future:
    //5: optional ShipmentTrackingEtaAndDeliveryData      EtaAndDeliveryData,
}
typedef list<ShipmentTrackingIbtInformation>            ShipmentTrackingIbtInformationList

struct ShipmentTrackingPackageInformation
{
    1: optional ShipmentTrackingPackageProperties       PackageProperties,

    //NOTE: self recursion here from ShipmentTrackingIbtInformation to ShipmentTrackingTourInformation is not possible at all in Thrift! That's why there is a list of IBTs as a kind of "stack" here, meaning, 
    //      the last IbtInfo in the list is the actual branch where the tote was picked, then it was sent from the last branch (on position N) in stack (list) to the branch on the (N-1) position in stack,
    //      until it was sent from the branch on the 1st position on the list (stack) to the customers branch referenced in ShipmentTrackingRequest.
    //      This is a preparation for future possible multiple IBT delivery cascade.
    2: optional ShipmentTrackingIbtInformationList      IbtInformationList,

    3: optional ShipmentTrackingLineDetailList          LineDetails,
}
typedef list<ShipmentTrackingPackageInformation>        ShipmentTrackingPackageInformationList

struct ShipmentTrackingTourInformation
{
    1: optional ShipmentTrackingTourData                TourData,
    2: optional ShipmentTrackingEtaAndDeliveryData      EtaAndDeliveryData,

    3: optional ShipmentTrackingPackageInformationList  PackageInformationList,
}
typedef list<ShipmentTrackingTourInformation>           ShipmentTrackingTourInformationList


///////////////////////////////////////////////////////////////////////////////////////////////////
/// REQUEST
///////////////////////////////////////////////////////////////////////////////////////////////////
struct ShipmentTrackingRequest
{
    1: optional i16                                     BranchNo,
    2: optional i32                                     CustomerNo,
   10: optional ShipmentTrackingDataFilter              DataFilter,
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/// RESPONSE
///////////////////////////////////////////////////////////////////////////////////////////////////
struct ShipmentTrackingResponse
{
    1:  optional cscbase.ReturnStruct                   RetValue,
    2:  optional ShipmentTrackingTourInformationList    TourInformationList,
}




