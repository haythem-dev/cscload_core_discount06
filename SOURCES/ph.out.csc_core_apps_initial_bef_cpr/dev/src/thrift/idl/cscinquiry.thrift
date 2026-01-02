include "cscbase.thrift"
include "cscorder.thrift"
include "types/batchstatusenum.inc"
include "types/xmlinfolevelenum.inc"
include "types/reservationtypeenum.inc"
include "types/articleinquiryperioddatetypeenum.inc"

namespace cpp csc.inquiry
namespace csharp Csc.Inquiry

//-----------------------------------------------------------------------
// Article inquiry
//-----------------------------------------------------------------------

struct ArticleInquiryPositionRequest
{
	1: optional string	ArticleCode,
	2: optional i32 	QuantityOrdered,
    3: optional i16		InternalPosReference,		// auf Wunsch von Sebastian
}

typedef list<ArticleInquiryPositionRequest> 	ArticleInquiryPositionRequestList

struct ArticleInquiryRequest
{
	1: optional i16									BranchNo,
	2: optional i32									CustomerNo,

	10: optional ArticleInquiryPositionRequestList	Positions,
}


typedef cscorder.OrderPositionResponse  		ArticleInquiryPositionResponse

typedef list<ArticleInquiryPositionResponse> 	ArticleInquiryPositionResponseList

struct ArticleInquiryResponse
{
	1: optional cscbase.ReturnStruct				RetValue,

	2: optional i16 								BranchNo,
	3: optional i32 								CustomerNo,
	4: optional xmlinfolevelenum.XMLInfoLevelEnum	XmlInfoLevel,
	5: optional string								PharmacyName,
	6: optional cscorder.TourInformation			TourInfo,

	10: optional ArticleInquiryPositionResponseList Positions,
}

//-----------------------------------------------------------------------
// Article availability bulk (list)
//-----------------------------------------------------------------------

struct ArticleAvailabilityBulkRequest
{
	1: optional i16									BranchNo,
	2: optional i32									CustomerNo,

	10: optional list<string>						Positions,
}

struct ArticleAvailabilityPositionResponse
{
	1: optional string								ArticleCode,
	2: optional bool								Available,
}

typedef list<ArticleAvailabilityPositionResponse> ArticleAvailabilityPositionResponseList

struct ArticleAvailabilityBulkResponse
{
	1: optional cscbase.ReturnStruct				RetValue,

	2: optional i16									BranchNo,
	3: optional i32									CustomerNo,

	10: optional ArticleAvailabilityPositionResponseList	Positions,
}

//-----------------------------------------------------------------------
// Article availability bulk (range)
//-----------------------------------------------------------------------

struct ArticleAvailabilityBulkRangeRequest
{
	1: optional i16									BranchNo,
	2: optional i32									CustomerNo,

	5: optional string								ArticleCodeRangeBegin,
	6: optional string								ArticleCodeRangeEnd,
}

struct ArticleAvailabilityBulkRangeResponse
{
	1: optional cscbase.ReturnStruct				RetValue,

	2: optional i16									BranchNo,
	3: optional i32									CustomerNo,

	5: optional string								ArticleCodeRangeBegin,
	6: optional string								ArticleCodeRangeEnd,

	10: optional list<string>						AvailableArticles,
}

//-----------------------------------------------------------------------
// Article stock bulk
//-----------------------------------------------------------------------

struct ArticleStockBulkRequest
{
	1: optional i16									BranchNo,
	2: optional i32									CustomerNo,
	3: optional bool								GetBatchAndExpiryDate,

	5: optional string								ArticleCodeRangeBegin,  // either use 5+6, or 10
	6: optional string								ArticleCodeRangeEnd,

	10: optional list<string>						Positions,
}


struct ArticleStockPositionResponse
{
	1: optional string								ArticleCode,
	2: optional i32									Quantity,
	3: optional string								Batch,
	4: optional i32									ExpiryDate,
	5: optional batchstatusenum.BatchStatusEnum		BatchStatus,
}

typedef list<ArticleStockPositionResponse> ArticleStockPositionResponseList

struct ArticleStockBulkResponse
{
	1: optional cscbase.ReturnStruct				RetValue,

	2: optional i16									BranchNo,
	3: optional i32									CustomerNo,

	10: optional ArticleStockPositionResponseList	Positions,
}

//-----------------------------------------------------------------------
// Article stock details
//-----------------------------------------------------------------------

struct ArticleReservationInfo
{
    1: optional reservationtypeenum.ReservationTypeEnum     ReservationType,
    2: optional i32                                         QuantityReserved,
    3: optional string                                      CustomerPharmacyGroup,
}
typedef list<ArticleReservationInfo>                        ArticleReservationInfoList

struct ArticleStockDetailInfo
{
    1:  optional i16								        BranchNo,
    2:  optional string                                     ArticleCode,
    5:  optional i32                                        QuantityAvailableForAll,
    10: optional ArticleReservationInfoList                 ArticleReservations,
}
typedef list<ArticleStockDetailInfo>                        ArticleStockDetailInfoList

struct ArticleStockDetailsRequestData
{
	1: optional i16									        BranchNo,
	10: optional string						                ArticleCode,
}
typedef list<ArticleStockDetailsRequestData>                ArticleStockDetailsRequestDataList,


struct ArticleStockDetailsRequest
{
	1: optional ArticleStockDetailsRequestDataList	        RequestDataList,
}

struct ArticleStockDetailsResponse
{
    1: optional cscbase.ReturnStruct				        RetValue,
	2: optional ArticleStockDetailInfoList			        ArticleStockDetailInfoResponses,
}

//-----------------------------------------------------------------------
// Article inquiry Croatia
//-----------------------------------------------------------------------

struct ArticleInquiryPeriodRequest
{
    1: optional articleinquiryperioddatetypeenum.ArticleInquiryPeriodDateTypeEnum DateType,
    2: optional cscbase.Date                        DateFrom,
    3: optional cscbase.Date                        DateTo,
}

struct ArticleInquiryHRRequest
{
    1: optional ArticleInquiryRequest               ArticleInquiryReq,
    2: optional ArticleInquiryPeriodRequest         Period,
    3: optional i32                                 BeginningArticleNo,
    4: optional i32                                 PositionsPerPage,
}
