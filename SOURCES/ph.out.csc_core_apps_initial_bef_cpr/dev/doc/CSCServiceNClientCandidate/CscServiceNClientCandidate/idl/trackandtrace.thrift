include "cscbase.thrift"

namespace cpp documents
namespace csharp Documents


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TNT Delivery Information
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct TNTDeliveryInformationDataFilter
{
    1: optional cscbase.Date                           RequestDate,
    2: optional bool                                   DetailsDesired,
    3: optional string                                 SpecificTourID
}

struct TNTLineDetail
{
    1: optional i32                                     OrderPosNo,                     // <- dktsv.tsv_pos
    2: optional i32                                     Quantity,                       // <- dktsv.tsv_kop_meng
    3: optional string                                  ArticleCode,                    // <- dktsv.tsv_kop_pzn (ArticleCode dazu lesen)
    4: optional string                                  ArticleName,                    // <- dktsv.tsv_kop_abez
    5: optional bool                                    IsNarcotic,                     // <- dktsv.tsv_vsw_btm
}
typedef list<TNTLineDetail>	                            TNTLineDetailList

struct TNTPackageInformation
{
    1: optional string                                  PackageIdentifier,              // <- dktsv.tsv_wannennr
    2: optional i32                                     PickingOrderNo,                 // <- dktsv.tsv_vsw_la
    3: optional i16                                     PickingOrderPageNo,             // <- dktsv.tsv_vsw_seite
    4: optional i32                                     OrderNo,                        // <- dktsv.tsv_kauf
    5: optional TNTLineDetailList                       LineDetails,
}
typedef list<TNTPackageInformation>	                    TNTPackageInformationList

struct TNTTourInformation
{
    1: optional string                                  TourID,                         // <- dktsv.tsv_tour
    2: optional cscbase.DateTime                        PlannedTimeOfArrival,           // <- ???
    3: optional cscbase.DateTime                        EstimatedTimeOfArrival,         // <- etatransmed.eta_tseta
    4: optional string                                  DelayInfo,
    5: optional TNTPackageInformationList               PackageInformationList,
}
typedef list<TNTTourInformation>	                    TNTTourInformationList


///////////////////////////////////////////////////////////////////////////////////////////////////
/// REQUEST
///////////////////////////////////////////////////////////////////////////////////////////////////
struct TNTDeliveryInformationRequest
{
	1:	optional i16									BranchNo,
	2:	optional i32									CustomerNo,
    10: optional TNTDeliveryInformationDataFilter       DataFilter,
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/// RESPONSE
///////////////////////////////////////////////////////////////////////////////////////////////////
struct TNTDeliveryInformationResponse
{
	1:	optional cscbase.ReturnStruct				    RetValue,
    2:  optional TNTTourInformationList                 TourInformation,
}


