include "cscbase.thrift"
include "cscorder.thrift"
include "types/returntypeenum.inc"
include "types/returnreasonenum.inc"
include "types/returnacceptancecheckresultenum.inc"

namespace cpp csc.returns
namespace csharp Csc.Returns

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ReturnsRequest
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct ReturnsRequestPosition
{
	1:	optional i32																PositionReferenceNo,
	2:	optional string																DeliveryNoteNo,
	3:	optional cscbase.Date														DeliveryNoteDate,
	4:	optional string																ArticleCode,
	5:	optional i32																ReturnQty,
	6:	optional returnreasonenum.ReturnReasonEnum									ReturnReason,
	7:	optional string																Batch,
	8:	optional cscbase.Date														ExpiryDate,
}
typedef list<ReturnsRequestPosition>												ReturnsRequestPositionList


struct ReturnsRequestHead
{
	1:	optional returntypeenum.ReturnTypeEnum										ReturnType,						// ReturnRequest (Anfrage), ReturnAnnouncement (Ankündigung)
	10:	optional i16																BranchNo,
	11:	optional i32																CustomerNo,
	20:	optional cscbase.Date														ReturnDate,
	21:	optional string																ReturnID,
	22:	optional i32																SupportID,
	30:	optional string																LocalCourt,						// Amtsgericht
	31:	optional string																CompanyRegistrationNo,			// Handelsregisternummer
	32:	optional string																VATIdentificationNo,			// UmsatzsteuerID
	33: optional string																TaxIdentificationNo,			// Steuernummer
	34:	optional cscbase.BankAccount												CustomerBankAccount,
}

struct ReturnsRequest
{
	1:	optional ReturnsRequestHead													ReturnsHeadInformation,
	2:	optional ReturnsRequestPositionList											ReturnsPositions,
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ReturnsResponse
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct ReturnsResponsePosition
{
	1:	optional i32																PosNo,
	2:	optional i32																PositionReferenceNo,
	3:	optional string																DeliveryNoteNo,
	4:	optional cscbase.Date														DeliveryNoteDate,
	5:	optional string																ArticleCode,
	6:	optional i32																ReturnQty,
	7:	optional returnreasonenum.ReturnReasonEnum									ReturnReason,
	8:	optional string																Batch,
	9:	optional cscbase.Date														ExpiryDate,
	10:	optional cscorder.ArticleInformation										ArticleDetails,
	11: optional i16																FailedCheckId,
	12: optional string																FailedCheckString,
}
typedef list<ReturnsResponsePosition>												ReturnsResponsePositionList

struct ReturnsResponseGroup
{
	1:  optional i32                                                                CSCAnnouncementID,
	2:	optional i32																CSCAnnouncementHeadID,
	10:	optional string																WholesalerReferenceID,
	11:	optional string																DocumentID,
	12:	optional string																ReturnsTourID,
	13:	optional cscbase.DateTime													ReturnsTourDeparture,
	14:	optional cscbase.DateTime													ReturnsTourArrival,
	15:	optional ReturnsResponsePositionList										ReturnsPositions,
}
typedef map<returnacceptancecheckresultenum.ReturnAcceptanceCheckResultEnum, ReturnsResponseGroup>	ReturnsResponseGroupMap

struct ReturnsResponse
{
	1:	optional cscbase.ReturnStruct												RetValue,
	10:	optional ReturnsResponseGroupMap											ReturnsResponses,
    20: optional cscbase.BranchDetails                                              BranchInformation,
    30: optional cscbase.CustomerDetails                                            CustomerInformation,
}

