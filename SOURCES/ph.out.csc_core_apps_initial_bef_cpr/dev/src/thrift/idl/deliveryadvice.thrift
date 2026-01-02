include "cscbase.thrift"
include "types/orderremarktypeenum.inc"
include "types/kindofdiscountenum.inc"

namespace cpp documents
namespace csharp Documents

// Delivery Advice

// ------------------------------------------------------------------------------------------------------------------------------------
struct DeliveryAdviceLineDetail
{
	1:	optional i32								DeliveryLineNo,					// deliveryadvicelinedetails.deliveryposno
	2:	optional i32								QtyDelivery,					// deliveryadvicelinedetails.qty_delivery
	3:	optional i32								QtyLack,						// deliveryadvicelinedetails.qty_lack
	10:	optional string								Batch,							// deliveryadvicelinedetails.batch
	11: optional cscbase.Date						ExpiryDate,						// deliveryadvicelinedetails.expirydate
	20: optional i32								PackageId,						// deliveryadvicelinedetails.packageid
	21: optional string								TrackingId,						// deliveryadvicelinedetails.trackingid
    22: optional bool                               PreCalculatedBatchChanged,      // deliveryadvicelinedetails.precalcbatchchanged
}
typedef list<DeliveryAdviceLineDetail>				DeliveryAdviceLineDetailList
// ------------------------------------------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------------------------------------------
struct DeliveryAdviceLineDiscount
{
	1:	optional i16									DiscountMode,					// deliveryadvicelinediscounts.discountmode
	2:	optional double									Discount,						// deliveryadvicelinediscounts.discount
	3:	optional string									Origin,							// deliveryadvicelinediscounts.origin
	4:	optional i16									DeleteReason,					// deliveryadvicelinediscounts.deletereason
	5:	optional double									DiscountValue,					// deliveryadvicelinediscounts.discountvalue
	6:	optional i16									DiscountType,					// deliveryadvicelinediscounts.discounttype
	7:	optional i16									Hierarchy,						// deliveryadvicelinediscounts.trackingid
	8:	optional i16									CalculationBasis,				// deliveryadvicelinediscounts.calculationbasis
	9:	optional kindofdiscountenum.KindOfDiscountEnum	KindOfDiscount,					// cdiscform.kindofdiscount from a LEFT JOIN cdiscform on (cdiscform.discountformno == deliveryadvicelinediscounts.discountmode)
}
typedef list<DeliveryAdviceLineDiscount>			DeliveryAdviceLineDiscountList
// ------------------------------------------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------------------------------------------
struct DeliveryAdviceLineReturn
{
	1:	optional i32								DeliveryAdvicePosNo,			// deliveryadvicelinereturn.deliveryadviceposno
	2:	optional i16								BlockedforReturns,				// deliveryadvicelinereturn.blockedforreturns
	3:	optional i32								Qty_Returned,					// deliveryadvicelinereturn.qty_returned
	10:	optional i32								Qty_Returned_RebateInKind,		// deliveryadvicelinereturn.qty_returned_rebateinkind
	11: optional i32								Qty_Return_Rejected,			// deliveryadvicelinereturn.qty_return_rejected
}
typedef list<DeliveryAdviceLineReturn>				DeliveryAdviceLineReturnList

// ------------------------------------------------------------------------------------------------------------------------------------
struct DeliveryAdviceRemarks
{
	1:	optional orderremarktypeenum.OrderRemarkTypeEnum	RemarkType,						// deliveryadviceremarks.remarktype
	2:	optional i16										SerialNo,						// deliveryadviceremarks.serialno
	3:	optional string										RemarkText,						// deliveryadviceremarks.remarktext
}
typedef list<DeliveryAdviceRemarks>							DeliveryAdviceRemarksList
// ------------------------------------------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------------------------------------------
struct DeliveryAdviceLineExtrasAT
{
	1:	optional bool								IsNarcotic,						// artikelzentral.bitand(etartklasse1, 512 )
	2:	optional bool								IsRX,							// artikelzentral.bitand(etartklasse1, 2048 )
	3:	optional bool								IsPsychotropic,					// artikelzentral.kzpsychostoffe
	4:	optional bool								IsVeterinary,					// artikelzentral.bitand(etartklasse1, 256 )
	5:  optional bool								IsHazardous,					// artikelzentral.bitand(etartschalter4, 1 )
	6:  optional bool								IsReportable,					// artikelzentral.bitand(etartschalter2, 32768 )
	7:  optional bool								IsShortExpiry,					// artikelzentral.bitand(etartschalter2, 8192 )
}

// ------------------------------------------------------------------------------------------------------------------------------------
struct DeliveryAdviceLine
{
	1:	optional i32								PharmosOrderLineNo,				// deliveryadviceline.pharmosorderposno
	2:	optional i32								DeliveryAdviceLineNo,			// deliveryadviceline.invoiceposno
	3:	optional i32								CSCOrderLineNo,					// deliveryadviceline.cscorderposno
	10:	optional i32								ArticleNo,						// deliveryadviceline.articleno
	11:	optional string								ArticleCode,					// deliveryadviceline.articlecode
	12:	optional i16								CodeType,						// deliveryadviceline.code_type
	13:	optional string								LineReference,					// deliveryadviceline.linereference
	20:	optional i32								QtyOrdered,						// deliveryadviceline.qty_ordered
	21: optional i32								QtyConfirmed,					// deliveryadviceline.qty_confirmed
	22: optional i32								QtyRebateInKind,				// deliveryadviceline.qty_rebateinkind
	23: optional i32								QtyInvoiced,					// deliveryadviceline.qty_invoiced
	30: optional double								InvoicedPrice,					// deliveryadviceline.invoicedprice
	31: optional double								VatPercentage,					// deliveryadviceline.vatpercentage
	32: optional double								LogisticServiceCost,			// deliveryadviceline.logisticservicecost
	33: optional double								MinLogisticServiceCostValue,	// deliveryadviceline.minlogisticservicecostvalue
	34:	optional string								ArticleName,					// deliveryadviceline.articlename
	35:	optional string								ArticleUnit,					// deliveryadviceline.articleunit
	36:	optional string								PharmaceuticalForm,				// deliveryadviceline.pharmaceuticalform
	37:	optional string								Vat,							// deliveryadviceline.vat

	40: optional DeliveryAdviceLineDetailList		LineDeliveryDetails,			// deliveryadvicelinedetails

	50: optional DeliveryAdviceLineDiscountList		LineDiscounts,					// deliveryadvicelinediscounts

	60:	optional DeliveryAdviceRemarksList			LineRemarks,					// deliveryadviceremarks
    70: optional string                             EANCode,                        // article´s EAN code
    75: optional double								BasePrice,					    // deliveryadviceline.baseprice
    76: optional double								PharmacySellPrice,			    // deliveryadviceline.pharmacysellprice
	77: optional i32								QtyFeeCalculation,				// deliveryadviceline.qty_feecalculation
    78: optional double								LineFee,						// deliveryadvicehead.linefee if deliveryadviceline.qty_feecalculation > 0
    79: optional double								PackageFee,						// deliveryadvicehead.packagefee * deliveryadviceline.qty_feecalculation

    80: optional DeliveryAdviceLineReturnList		LineReturn,                     //deliveryadvicelinereturn

    90: optional double								PrintedPricePerPiece,			// deliveryadviceline.printedpriceperpiece
    91: optional double								LineValue,						// deliveryadviceline.linevalue
	92: optional DeliveryAdviceLineExtrasAT			ExtrasAT,						// extras for Austria
}
typedef list<DeliveryAdviceLine>					DeliveryAdviceLineList
// ------------------------------------------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------------------------------------------
struct DeliveryAdviceVatTotal
{
	1:	optional string								Vat,							// deliveryadvicevattotals.vat
	2:	optional double								VatPercentage,					// deliveryadvicevattotals.vatpercentage
	3:	optional double								NetValue,						// deliveryadvicevattotals.netvalue
	4:	optional double								VatValue,						// deliveryadvicevattotals.vatvalue
	5:	optional double								SumLineFee,						// deliveryadvicevattotals.sumlinefee
	6:	optional double								SumPackageFee,					// deliveryadvicevattotals.sumpackagefee
}
typedef list<DeliveryAdviceVatTotal>				DeliveryAdviceVatList
// ------------------------------------------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------------------------------------------
struct DeliveryAdviceTotals
{
	1:  optional DeliveryAdviceVatList				VatValues,
	2:	optional double								DepositValue,					// deliveryadvicetotals.depositvalue
	3:	optional double								NetTurnover,					// deliveryadvicetotals.depositvalue
	4:	optional double								DiscountRetail,					// deliveryadvicetotals.depositvalue
	5:	optional double								DiscountWholesale,				// deliveryadvicetotals.depositvalue
	6:	optional double								VatAmount,						// deliveryadvicetotals.depositvalue
	7:	optional double								LogisticServiceCost,			// deliveryadvicetotals.logisticservicecost
}
// ------------------------------------------------------------------------------------------------------------------------------------

struct DeliveryAdviceKey
{
	1:	optional i16								BranchNo,						// deliveryadvicehead.branchno
	2:	optional i32								CustomerNo,						// deliveryadvicehead.customerno
	3:	optional string								DeliveryAdviceNo,				// deliveryadvicehead.invoiceno
	4:	optional cscbase.Date						DeliveryAdviceDate,				// deliveryadvicehead.deliveryadvicedate
}

typedef list<DeliveryAdviceKey>						DeliveryAdviceKeyList

// ------------------------------------------------------------------------------------------------------------------------------------
struct DeliveryAdvice
{
	1:	optional i16								BranchNo,						// deliveryadvicehead.branchno
	2:	optional i32								CustomerNo,						// deliveryadvicehead.customerno
	3:	optional string								DeliveryAdviceNo,				// deliveryadvicehead.invoiceno
	4:	optional cscbase.Date						DeliveryAdviceDate,				// deliveryadvicehead.deliveryadvicedate
    5:  optional cscbase.CustomerDetails            CustomerInformation,

	10:	optional i32								PharmosOrderNo,					// deliveryadvicehead.pharmosorderno
	11:	optional i32								CSCOrderNo,						// deliveryadvicehead.cscorderno
	12:	optional string								Completed,						// deliveryadvicehead.completed
	13:	optional string								SpecialDocumentType,			// deliveryadvicehead.specialdocumenttype
	14:	optional string								TourId,							// deliveryadvicehead.tourid
	15:	optional cscbase.Date						DueDate,						// deliveryadvicehead.duedate
	16:	optional string								DocumentGuid,					// deliveryadvicehead.msv3documentid
	17:	optional string								OrderType,						// deliveryadvicehead.ordertype
	18:	optional string								PickingType,					// deliveryadvicehead.pickingtype
	19:	optional string								BookingType,					// deliveryadvicehead.bookingtype
	20:	optional i16								Requested,						// deliveryadvicehead.requested
	21:	optional bool								Confirmed,						// deliveryadvicehead.confirmed
	22:	optional string								OrderLabel,						// deliveryadvicehead.orderlabel
	23:	optional i16								Cancelled,						// deliveryadvicehead.cancelled
    24: optional i16                                BatchCorrectionAdviceStatus,    // deliveryadvicehead.batchcorrectionadvice
    25: optional double								LineFee,						// deliveryadvicehead.linefee
    26: optional double								PackageFee,						// deliveryadvicehead.packagefee

	30:	optional DeliveryAdviceTotals				Totals,
	40:	optional DeliveryAdviceLineList				LinesInformation,
	50:	optional DeliveryAdviceRemarksList			HeadRemarks,					// deliveryadviceremarks (posnr=0)
}
typedef list<DeliveryAdvice>						DeliveryAdviceList
// ------------------------------------------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------------------------------------------
struct DeliveryAdviceIdentifier
{
	1:	optional string								DeliveryAdviceNo,				// optional! just used for document specific requests
	2:	optional cscbase.Date						DeliveryAdviceDate,				// optional! just used for historical requests
	3:	optional i32								CSCOrderNo,						// optional! just used for search by CSCOrderNo
}
typedef list<DeliveryAdviceIdentifier>				DeliveryAdviceIdentifierList
// ------------------------------------------------------------------------------------------------------------------------------------


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// delivery advice information request (request all delivery advices that have not been confirmed yet)
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct DeliveryAdviceInformationFilter
{
	1:	optional bool								SendTotals,						// optional! true => send information from deliveryadvicetotals and devliveryadvicevattotals
	2:	optional bool								SendLineInformation,			// optional! true => send information from deliveryadviceline
	3:	optional bool								SendLinePickingInformation,		// optional! true => add information from deliveryadvicelinedetails
	4:	optional bool								SendLineDiscountInformation,	// optional! true => add information from delvieryadvicelinediscounts
	5:	optional bool								SendLineReturn,					// optional! true => add information from delvieryadvicelinereturn
	6:	optional bool								SendCustomerInformation,		// optional! true => add information from cscbase.CustomerDetails
	7:	optional bool								SendOnlyInvoicedLines,			// optional! true => add only lines with qty_invoiced > 0
	8:  optional bool								SendLineExtrasAT,				// optional! true => add information for Austria
}

enum ConfirmationRequestStatusEnum
{
	ALL_UNCONFIRMED_DELIVERY_ADVICES	= 0,
	ALL_DELIVERY_ADVICES				= 1,
}

struct DeliveryAdvicesRequest
{
	1:	optional i16								BranchNo,
	2:	optional i32								CustomerNo,
	3:	optional ConfirmationRequestStatusEnum		ConfirmationStatus,				// 0 = all unconfirmed delivery advices, 1 = all delivery advices
	10:	optional cscbase.Date						SearchPeriodStart,				// start date for the search of delivery advices
	11:	optional cscbase.Date						SearchPeriodEnd,				// end date for the search of delivery advices
	20:	optional DeliveryAdviceInformationFilter	InformationFilter,
}

struct DeliveryAdviceSpecificRequest
{
	1:	optional i16								BranchNo,
	2:	optional i32								CustomerNo,
	10:	optional DeliveryAdviceIdentifierList		RequestedDeliveryAdvices,
	20:	optional DeliveryAdviceInformationFilter	InformationFilter,
}

struct DeliveryAdvicesResponse
{
	1:	optional cscbase.ReturnStruct				RetValue,
	2:	optional DeliveryAdviceList					DeliveryAdvices,
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// delivery advice receive confirmation request (mark these delivery advices as received by the customer)
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct DeliveryAdviceReceiveConfirmationRequest
{
	1:	optional i16								BranchNo,
	2:	optional i32								CustomerNo,
	10:	optional DeliveryAdviceIdentifierList		RequestedDeliveryAdvices,
}

struct DeliveryAdviceReceiveConfirmationResponse
{
	1:	optional cscbase.ReturnStruct				RetValue,
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// delivery advice batch correction request (get delivery advices for which a batch (correction) advice should be created)
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct BatchAdviceRequest
{
	1:	optional i16								BranchNo,
	2:	optional bool								BatchCorrectionOnly,			// get only delivery advices with precalcbatchchanged = 1 in the details
}

struct BatchAdviceResponse
{
	1:	optional cscbase.ReturnStruct				RetValue,
	2:	optional DeliveryAdviceKeyList				DeliveryAdvices,
    3:  optional cscbase.BranchDetails              BranchInformation
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// delivery advice update request
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct DeliveryAdviceUpdate
{
	1:	optional DeliveryAdviceKey					Key,
	2:	optional bool								Confirmed,						// deliveryadvicehead.confirmed
	3:	optional i16								BatchCorrectionAdvice,			// deliveryadvicehead.batchcorrectionadvice
}

typedef list<DeliveryAdviceUpdate>	DeliveryAdviceUpdateList

struct UpdateDeliveryAdvicesRequest
{
	1:	optional DeliveryAdviceUpdateList	DeliveryAdvices,
}

struct UpdateDeliveryAdvicesResponse
{
	1:	optional cscbase.ReturnStruct		RetValue,
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DeliveryAdvicesHRRequest
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum DeliveryAdvicesHRRequestTypeEnum
{
    ByPeriod                            = 0,
    ByInvoiceNumber                     = 1,
    ByReference                         = 2,
}

struct DeliveryAdvicesHRRequest
{
    1:  optional i16                    BranchNo,
    2:  optional i32                    CustomerNo,
    4:  optional DeliveryAdvicesHRRequestTypeEnum RequestType,
    5:  optional cscbase.Date           PeriodFrom,
    6:  optional cscbase.Date           PeriodTo,
    7:  optional list<string>           DeliveryAdviceNos,
    8:  optional list<string>           References,
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DeliveryAdvicesHRResponse
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct DeliveryAdvicesHRResponse
{
    1:  optional DeliveryAdvicesResponse DeliveryAdvicesResp,
	2:  optional map<i16, double>       Taxrates,
}
