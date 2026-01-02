include "cscbase.thrift"
include "types/xmlinfolevelenum.inc"
include "types/weekdayenum.inc"

namespace cpp csc.msv3
namespace csharp Csc.Msv3


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// M S V 3
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// common stuff
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum Msv3OrderTypeEnum
{
	NORMAL = 0,
	SONDER = 1,
	STAPEL = 2,
	VERSAND = 3,
	RUECKNAHME = 4,
}

typedef string CscOrderTypeString

const CscOrderTypeString CscOrderType_NORMAL		= "NO";
const CscOrderTypeString CscOrderType_SONDER		= "SO";
const CscOrderTypeString CscOrderType_STAPEL		= "ST";
const CscOrderTypeString CscOrderType_VERSAND		= "VH";
const CscOrderTypeString CscOrderType_RUECKNAHME	= "RK";

const map<Msv3OrderTypeEnum, CscOrderTypeString> Msv3ToCSCOrderTypeMap =
{
	Msv3OrderType.NORMAL		:	CscOrderType_NORMAL,
	Msv3OrderType.SONDER		:	CscOrderType_SONDER,
	Msv3OrderType.STAPEL		:	CscOrderType_STAPEL,
	Msv3OrderType.VERSAND		:	CscOrderType_VERSAND,
	Msv3OrderType.RUECKNAHME	:	CscOrderType_RUECKNAHME,
}

const map<CscOrderTypeString, Msv3OrderTypeEnum> CSCToMsv3OrderTypeMap =
{
	CscOrderType_NORMAL		:	Msv3OrderType.NORMAL,
	CscOrderType_SONDER		:	Msv3OrderType.SONDER,
	CscOrderType_STAPEL		:	Msv3OrderType.STAPEL,
	CscOrderType_VERSAND	:	Msv3OrderType.VERSAND,
	CscOrderType_RUECKNAHME	:	Msv3OrderType.RUECKNAHME,
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MSV3 order transmission preparation
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Msv3OrderPreparationRequest
{
//	1:	optional Msv3OrderTypeEnum			OrderType,				// MSV3: Bestellung/Auftraege[]/@Auftragsart (NORMAL, SONDER, STAPEL, VERSAND)
	2:	optional string						OrderLabel,				// MSV3: Bestellung/Auftraege[]/@Auftragskennung (xs:string, length 1-20)
	3:	optional string						GebindeId,				// MSV3: Bestellung/Auftraege[]/@GebindeId (xs:string, length 1-20)
	4:	optional i32						OrderSupportId,			// MSV3: Bestellung/Auftraege[]/@AuftragsSupportID (xs:int, minInclusive 1, maxInclusive 999999)
	5:	optional string						OrderGuid,				// MSV3: Bestellung/Auftraege[]/@Id (xs:string, length 36, GUID)	
}

typedef list<Msv3OrderPreparationRequest>	Msv3OrderPreparationRequestList

typedef map<Msv3OrderTypeEnum, Msv3OrderPreparationRequestList>	Msv3OrderPreparationRequestMap


struct Msv3TransmissionPreparationRequest
{
	1:	optional i16						BranchNo,
	2:	optional i32						CustomerNo,
	3:	optional i32						TransmissionSupportId,		// MSV3: Bestellung/@BestellSupportID (xs:int, minInclusive 1, maxInclusive 999999)
	4:	optional string						TransmissionGuid,			// MSV3: Bestellung/@Id (xs:string, length 36, GUID)

	10:	Msv3OrderPreparationRequestMap		MSV3Orders,
}


struct Msv3OrderPreparationResponse
{
	1:	optional cscbase.ReturnStruct		RetValue,
//	1:	optional Msv3OrderTypeEnum			OrderType,					// MSV3: Bestellung/Auftraege[]/@Auftragsart (NORMAL, SONDER, STAPEL, VERSAND)
	2:	optional string						OrderLabel,					// MSV3: Bestellung/Auftraege[]/@Auftragskennung (xs:string, length 1-20)
	3:	optional string						GebindeId,					// MSV3: Bestellung/Auftraege[]/@GebindeId (xs:string, length 1-20)
	4:	optional i32						OrderSupportId,				// MSV3: Bestellung/Auftraege[]/@AuftragsSupportID (xs:int, minInclusive 1, maxInclusive 999999)
	5:	optional string						OrderGuid,					// MSV3: Bestellung/Auftraege[]/@Id (xs:string, length 36, GUID)	

	11:	optional string						OriginalOrderLabel,			// original order label if it has been changed due to exceeded number of allowed custom orderlabels
//	12:	optional bool						OrderTypeNotAllowed,		// true if the order type is not allowed to be used for MSV3 for this customer
}

typedef list<Msv3OrderPreparationResponse>	Msv3OrderPreparationResponseList
typedef map<Msv3OrderTypeEnum, Msv3OrderPreparationResponseList>	Msv3OrderPreparationResponseMap

struct Msv3TransmissionPreparationResponse
{
	1:	optional cscbase.ReturnStruct		RetValue,
	2:	optional i16						BranchNo,
	3:	optional i32						CustomerNo,

	10:	optional i32						OrderPeriodId,				// BestellfensterID	
	11:	Msv3OrderPreparationResponseMap 	MSV3Orders,
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MSV3 order transmission postprocessing
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Msv3OrderPostProcessingRequest
{
	1:	optional string						OrderGuid,					// MSV3: Bestellung/Auftraege[]/@Id (xs:string, length 36, GUID)
	2:	optional i32						OrderNo,					// CSC orderno
}
typedef list<Msv3OrderPostProcessingRequest>	Msv3OrderPostProcessingRequestList

struct Msv3TransmissionPostProcessingRequest
{
	1:	optional string						TransmissionGuid,			// MSV3: Bestellung/@Id (xs:string, length 36, GUID)
	2:	optional string 					XmlResponse,

	10:	Msv3OrderPostProcessingRequestList	MSV3Orders,
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MSV3 order status
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Msv3OrderStatusRequest
{
	1:	optional string 					TransmissionGuid,			// MSV3: Bestellung/@Id (xs:string, length 36, GUID)
}

struct Msv3OrderStatusResponse
{
	1:	optional string 					TransmissionGuid,			// MSV3: Bestellung/@Id (xs:string, length 36, GUID)
	2:	optional string 					XmlResponse,
	3:	optional bool						IsOffer,
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MSV3 contract data
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Msv3OrderTypeInformation
{
	1:	optional Msv3OrderTypeEnum			OrderType,							// auftragartkd.kdauftragart ('NO', 'ST', 'SO' oder 'VH')
	2:	optional bool						Msv3Permission,						// auftragartkd.swmsv3 == 1 ? Vereinbart="true" : Vereinbart="false"
	3:	optional i32						AllowedOrderLabels,					// auftragartkd.orderlabelcount => MaxAnzahlFreieAuftragskennungen
	4:	optional bool						OnlyCompleteDeliveryForBundle,		// auftragartkd.swpartdel == 1 ? NurKompletteGebinde="true" : NurKompletteGebinde="false"
}

typedef list<Msv3OrderTypeInformation>		Msv3OrderTypeInformationList


struct Msv3OrderPeriod
{
	1:	optional weekdayenum.WeekDayEnum	Weekday,					// 0 = Sunday, ....
	2:	optional cscbase.Time				OrderPeriodEndTime,			// HHMM
	3:	optional cscbase.Time				MainOrderTime,
}

typedef list<Msv3OrderPeriod>				Msv3OrderPeriodList

struct Msv3OrderPeriodSpecialDay
{
	1:	optional Msv3OrderPeriod			OrderPeriod,
	2:	optional cscbase.Date				SpecialDayDate
}

typedef list<Msv3OrderPeriodSpecialDay>		Msv3OrderPeriodSpecialDayList

struct Msv3ContractDataRequest
{
	1:	optional i16								BranchNo,
	2:	optional i32								CustomerNo,
	3:	optional string								Msv3UserAccount,
	4:	optional bool								AutomatedRequest,	
}

struct Msv3ContractDataResponse
{
	1:	optional cscbase.ReturnStruct				RetValue,
	2:	optional i16								BranchNo,
	3:	optional i32								CustomerNo,
	4:	optional Msv3OrderTypeInformationList		OrderTypeList,
	5:	optional Msv3OrderPeriodList				OrderPeriodList,
	6:	optional Msv3OrderPeriodSpecialDayList		OrderPeriodSpecialDayList,				
	7:	optional bool								ReturnsOfferAgreement,							// true, wenn Kunde Auftragsart RK darf						
	8:	optional bool								SpecificProductAvailabilityAgreement,			// kunde.xmlinfolevel > 1
	9:	optional bool								BulkProductAvailabilityAgreement,				// true
	10:	optional bool								ArticleSubstitutionAgreement,					// Select skdnosub from kundeschalter where skdnosub = 0 and idfnr = {0} and vertriebszentrumnr = {1} 
	11: optional cscbase.Date						ValidFromDate,
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MSV3 customer info level
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct XmlInfoLevelRequest
{
	1:	optional i16						BranchNo,
	2:	optional i32						CustomerNo,
}

struct XmlInfoLevelResponse
{
	1:	optional cscbase.ReturnStruct				RetValue,
	2:	optional i16								BranchNo,
	3:	optional i32								CustomerNo,		
	4:	optional xmlinfolevelenum.XMLInfoLevelEnum	XmlInfoLevel,
	5:	optional bool								WithArticleReservation,
}

