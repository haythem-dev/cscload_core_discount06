include "cscbase.thrift"
include "types/languageenum.inc"
include "types/xmlinfolevelenum.inc"
include "types/paymentsfilterenum.inc"

namespace cpp csc.customer
namespace csharp Csc.Customer

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CustomerDetailsRequest
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct CustomerDetailsRequest
{
    1:	optional i16		BranchNo,
    2:	optional i32		CustomerNo,
    
    3:  optional bool		GetTenderInformation,
    4:  optional bool		GetCreditLimitInformation,
    5:  optional bool		GetLogisticSurcharge,
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CustomerDetailsResponse
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct CreditLimitInformation
{
    1:	optional i32		PartnerNo,
    2:	optional double		Limit,
    3:	optional double		SumDebitSide,
    4:  optional double		SumCreditSide,
    5:  optional double		SumMonthTurnover,
    6:  optional double		SumDayTurnover,
    7:	optional double		SumReturns,
    8:  optional double		SumGoodsReceipt,
}

struct CustomerDetails
{
    1:	optional i16									BranchNo,
    2:	optional i32									CustomerNo,
    3:	optional string									PharmacyName,
    4:  optional string									Salutation,
    5:	optional string									OwnerName,
    6:	optional cscbase.Address						CustomerAddress,
    7:	optional string									MailAddress,
    8:	optional string									FaxNo,
    9:  optional languageenum.LanguageEnum				Language,
    10: optional i16                                    SalutationId,
    11: optional string                                 SalutationExtension,
    12: optional string                                 CustomerGroup,
    13: optional i32									ChainCustomerNo,
    14: optional string                                 TelephoneNo,
    15:	optional xmlinfolevelenum.XMLInfoLevelEnum		XmlInfoLevel,
    16: optional bool									IsActive,
    17: optional bool									HasTender,

    // optional: withLogisticSurcharge == CustomerDetailsRequest.GetLogisticSurcharge
    18: optional double									LogisticSurchargePct,			// kndausku.logistikaufschlag    as Logistikzuschlag_Prozentsatz
    19: optional double									LogisticSurchargeMinValue,		// kndausku.logistikaufschlagmin as Logistikzuschlag_Mindestwert

    20: optional CreditLimitInformation					CreditLimit,
}

typedef list<CustomerDetails> CustomerDetailsList

struct CustomerDetailsResponse
{
    1:	optional cscbase.ReturnStruct					RetValue,

    10: optional CustomerDetailsList					Customers,
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ChangeCreditLimitRequest
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct ChangeCreditLimitRequest
{
    1:	optional i16		BranchNo,
    2:	optional i32		CustomerNo,
    3:  optional double		NewLimit,
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ChangeCreditLimitResponse
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct ChangeCreditLimitResponse
{
    1:	optional cscbase.ReturnStruct	RetValue,
    2:	optional i16					BranchNo,
    3:	optional i32					CustomerNo,
    4:  optional double					OldLimit,
    5:  optional CreditLimitInformation	CreditLimit,
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CustomerConditionsRequest
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct CustomerConditionsRequest
{
    1:	optional i16	BranchNo,
    2:	optional i32	FromCustomerNo,
    3:  optional i32	FromArticleNo,
    4:  optional i32	MaxPriceElements,
    5:  optional i32	CustomerNoFilter,
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CustomerConditionsResponse
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct PaymentTarget
{
    1:	optional i32	TargetDays,
    2:	optional double	DiscountPercent,
    3:	optional double DiscountPrice,
}
typedef list<PaymentTarget>	PaymentTargetList


struct ArticleCondition
{
    1:	optional i32				ArticleNo,
    2:	optional double				BasePrice,
    3:	optional i32				BaseQuantity,
    4:	optional double				DiscountPercent,
    5:	optional double				DiscountPrice,
    10:	optional PaymentTargetList	PaymentTargets,
}
typedef list<ArticleCondition>	ArticleConditionList


struct CustomerCondition
{
    1:	optional i32					CustomerNo,
    10:	optional ArticleConditionList	ArticleConditions,
}
typedef list<CustomerCondition>	CustomerConditionList


struct CustomerConditionsResponse
{
    1:	optional cscbase.ReturnStruct		RetValue,
    2:	optional i32						NextCustomerNo,
    3:  optional i32						NextArticleNo,

    10:	optional CustomerConditionList		CustomerConditions,
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TenderInfoRequest
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct TenderInfoRequest
{
    1:	optional i16	BranchNo,
    2:	optional i32	CustomerNo,
    3:  optional string	ContractNo,
    4:  optional i32	ArticleNo,
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TenderInfoResponse
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct TenderItem
{
    1:  optional i32	ArticleNo,
    2:  optional i32	TenderQty,
    3:  optional i32	FreeTenderQty,
    4:  optional i32	DeliveredQty,
    5:  optional i32	ReturnedQty,
}
typedef list<TenderItem>	TenderItemList


struct Tender
{
    1:  optional i32			CustomerNo,
    2:  optional i32			TenderNo,
    3:  optional string			ContractNo,
    4:  optional cscbase.Date	ValidFrom,
    5:  optional cscbase.Date	ValidTo,
    6:  optional i32			ChainNo,
    10: optional TenderItemList	TenderItems,
}
typedef list<Tender>	TenderList

struct TenderInfoResponse
{
    1:	optional cscbase.ReturnStruct	RetValue,
    2:  optional TenderList				Tenders,
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ArticleInfoRequest
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct ArticleInfoRequest
{
    1:	optional i16	BranchNo,
    2:  optional i32	ArticleNo,
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ArticleInfoResponse
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct ArticleInfo
{
    1:	optional i16			BranchNo,
    2:  optional i32			ArticleNo,
    3:  optional string			EAN,
    4:  optional string			Name,
    5:  optional string			AlternateName,
    6:  optional string			ManufacturerName,
    7:  optional double			BasePrice,
    8:  optional double			VatPercentage,
    9:  optional bool			PositiveList,
    10: optional bool			ActiveFlag,
    11: optional bool			BlockedFlag,
    12: optional cscbase.Date	CreationDate,
    13: optional bool           ColdChainFlag,
    14: optional bool           NarcoticFlag,
}


typedef list<ArticleInfo> ArticleInfoList

struct ArticleInfoResponse
{
    1:	optional cscbase.ReturnStruct	RetValue,
    2:  optional ArticleInfoList		Articles,
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// OrderInfoRequest
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct OrderInfoRequest
{
    1:	optional i16			BranchNo,
    2:	optional cscbase.Date	OrderDate,
    3:  optional i32			CustomerNo,
    4:  optional i32			ArticleNo,
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// OrderInfoResponse
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct OrderLineInfo
{
    1:  optional i32			ArticleNo,
    2:  optional i32			QuantityConfirmed,
    3:  optional i32			QuantityOrdered,
    4:  optional string			ReferenceNo,
}
typedef list<OrderLineInfo> OrderLineInfoList

struct OrderInfo
{
    1:	optional i16				BranchNo,
    2:  optional i32				CustomerNo,
    3:  optional i32				OrderNo,
    4:  optional cscbase.Date		OrderDate,
    5:  optional string				OrderType,
    10: optional OrderLineInfoList	OrderLines,
}
typedef list<OrderInfo> OrderInfoList

struct OrderInfoResponse
{
    1:	optional cscbase.ReturnStruct	RetValue,
    2:  optional OrderInfoList			Orders,
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// OrderStatusRequest
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct OrderStatusRequest
{
    1:  optional i16                    BranchNo,
    2:  optional i32                    CustomerNo,
    3:  optional i32                    OrderNo,
    4:  optional cscbase.Date           OrderDate,
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// OrderStatusResponse
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct OrderStatusResponse
{
    1:  optional cscbase.ReturnStruct   RetValue,
    2:  optional string                 Inprocess,
    3:  optional string                 Onhold,
    4:  optional string                 Ordercreated,
    5:  optional string                 Readyforinvoicing,
    6:  optional string                 Invoicecreated,
    7:  optional string                 Ordercanceled,
    8:  optional string                 Onhold2,
    9:  optional i32                    DriverId,
    10: optional i32                    InvoiceNo,
    11: optional i32                    PharmosOrderNo,
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PricesAndDiscountsRequest
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct PricesAndDiscountsRequest
{
    1:  optional i16                    BranchNo,
    2:  optional i32                    CustomerNo,
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PricesAndDiscountsResponse
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct PricesAndDiscountsResponse
{
    1:  optional cscbase.ReturnStruct   RetValue,
    2:  optional PricesAndDiscountsList PricesAndDiscounts_List,
}

struct PricesAndDiscounts
{
    1:  optional i32                    ArticleNo,
    2:  optional i16                    SellingMode,
    3:  optional double                 DiscountPercentage,
    4:  optional double                 GrossProfitPercentage,
    5:  optional double                 SalesPrice,
    6:  optional double                 PharmacySellPrice,
    7:  optional string                 NZOKCode,
}

typedef list<PricesAndDiscounts> PricesAndDiscountsList

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PaymentsRequest
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct PaymentsRequest
{
    1:  optional i16                    BranchNo,
    2:  optional i32                    CustomerNo,
    3:  optional cscbase.Date           DateFrom,
    4:  optional cscbase.Date           DateTo,
    5:  optional paymentsfilterenum.PaymentsFilterEnum Filter,
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PaymentsResponse
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct PaymentsResponse
{
    1:  optional cscbase.ReturnStruct   RetValue,
    2:  optional PaymentsList           Payments_List,
}

struct Payments
{
    1:  optional string                 InvoiceNo,
    2:  optional i32                    InvoiceDate,
    3:  optional string                 DocType,
    4:  optional i16                    KindOfInvoice,
    5:  optional string                 KindOfOrder,
    6:  optional i16                    DueDays,
    7:  optional i32                    DueDate,
    8:  optional double                 InvoiceValue,
    9:  optional double                 PaidValue,
    10: optional string                 PaymentSpec,
}

typedef list<Payments> PaymentsList

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PaymentConditionsRequest
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct PaymentConditionsRequest
{
    1:  optional i16                    BranchNo,
    2:  optional i32                    CustomerNo,
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PaymentConditionsResponse
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct PaymentConditionsResponse
{
    1:  optional cscbase.ReturnStruct   RetValue,
    2:  optional i16                    NZOKDiscountMethod,
    3:  optional i16                    DiscountMethod,
    4:  optional i16                    NZOKDaysOfPayment,
    5:  optional i16                    DaysOfPayment,
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TurnoverRequest
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct TurnoverRequest
{
    1:  optional i16                    BranchNo,
    2:  optional i32                    CustomerNo,
    3:  optional cscbase.Date           DateFrom,
    4:  optional cscbase.Date           DateTo,
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TurnoverResponse
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct TurnoverResponse
{
    1:  optional cscbase.ReturnStruct   RetValue,
    2:  optional double                 Total,
    3:  optional double                 XmlValue,
    4:  optional double                 Value,
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ChangedQuantitiesRequest
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct ChangedQuantitiesRequest
{
    1:  optional i16                    BranchNo,
    2:  optional i32                    CustomerNo,
    3:  optional i32                    OrderNo,
    4:  optional cscbase.Date           DateFrom,
    5:  optional cscbase.Date           DateTo,
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ChangedQuantitiesResponse
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct ChangedQuantitiesResponse
{
    1:  optional cscbase.ReturnStruct   RetValue,
    2:  optional ChangedQuantitiesList  ChangedQuantities_List,
}

struct ChangedQuantities
{
    1:  optional i16                    BranchNo,
    2:  optional i32                    CustomerNo,
    3:  optional i32                    OrderDate,
    4:  optional i32                    OrderNo,
    5:  optional string                 InvoiceNo,
    6:  optional i32                    ArticleNo,
    7:  optional string                 ArticleName,
    8:  optional i32                    QuantityOriginal,
    9:  optional i32                    QuantityNew,
    10: optional i32                    QuantityOrdered,
}

typedef list<ChangedQuantities> ChangedQuantitiesList

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DiscountAccountRequest
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct DiscountAccountRequest
{
    1:  optional i16                    BranchNo,
    2:  optional i32                    CustomerNo,
    3:  optional cscbase.Date           DateFrom,
    4:  optional cscbase.Date           DateTo,
    5:  optional bool                   AccNatRebateGroup,
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DiscountAccountResponse
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct DiscountAccountResponse
{
    1:  optional cscbase.ReturnStruct   RetValue,
    2:  optional double                 Value,
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PromotionsRequest
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct PromotionsRequest
{
    1:  optional i16                    BranchNo,
    2:  optional i32                    CustomerNo,
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PromotionsResponse
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct PromotionsResponse
{
    1:  optional cscbase.ReturnStruct   RetValue,
    2:  optional PromotionsList         Promotions_List,
}

struct Promotions
{
    1:  optional i32                    MaxQuantity1,
    2:  optional i32                    MaxQuantity,
    3:  optional i32                    SoldQuantity,
    4:  optional i32                    MinQuantity,
    5:  optional i32                    DateFrom,
    6:  optional i32                    DateTo,
    7:  optional i32                    ArticleNo,
    8:  optional i32                    BaseQuantity,
    9:  optional double                 BaseValue,
    10: optional double                 DiscountValuePercentage,
    11: optional i16                    DiscountQuantity,
    12: optional i32                    DiscountArticle,
    13: optional i16                    DiscountSpecification,
    14: optional string                 NotViaSalesWeb,
    15: optional i16                    PromotionNo,
    16: optional string                 Name,
}

typedef list<Promotions> PromotionsList

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RoutesRequest
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct RoutesRequest
{
    1:  optional i16                    BranchNo,
    2:  optional i32                    CustomerNo,
    3:  optional i16                    Weekday,
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RoutesResponse
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct RoutesResponse
{
    1:  optional cscbase.ReturnStruct   RetValue,
    2:  optional RoutesList             Routes_List,
}

struct Routes
{
    1:  optional i16                    Weekday,
    2:  optional string                 TourId,
    3:  optional i32                    Duration,
}

typedef list<Routes> RoutesList

//#############################################################################################################################################################//
// <S U B S E Q U E N T    D E L I V E R Y>
//#############################################################################################################################################################//
//---------------------------------------------------------------------------------------------------------------//
// SubsequentDelivery Query / Search / Select
//---------------------------------------------------------------------------------------------------------------//
// REQUEST
struct SubsequentDeliveryRequest
{
    1:  optional i16                    BranchNo,
    2:  optional i32                    CustomerNo,
    3:  optional i32                    ArticleNo,
}

// RESPONSE (subsequent delivery aggregation)
struct SubsequentDeliveryArticleQtyAggregation
{
    1:  optional i32                    FrequencyOfArticle,
    2:  optional i32                    AccumulationOfQty,
}

struct SubsequentDeliveryArticleQtyAggregationResponse
{
    1:  optional cscbase.ReturnStruct                       RetValue,
    2:  optional SubsequentDeliveryArticleQtyAggregation    subsequent_DeliveryArticleQtyAggregation,
}

// RESPONSE
struct SubsequentDeliveryResponse
{
    1:  optional cscbase.ReturnStruct   RetValue,
    2:  optional SubsequentDeliveryList Subsequent_DeliveryList,
}

struct SubsequentDelivery
{
    1:  optional i32                    CustomerNo,
    2:  optional i32                    CSCOrderNo,
    3:  optional i32                    PosNo,
    4:  optional i32                    Date,
    5:  optional i16                    PosType,
    6:  optional i32                    ArticleNo,
    7:  optional string                 ArticleCode,
    8:  optional i32                    Qty,
    9:  optional string                 ArticleName,
    10:  optional string                ArticleUnit,
}

typedef list<SubsequentDelivery> SubsequentDeliveryList

//---------------------------------------------------------------------------------------------------------------//
// SubsequentDelivery Adjustment / Update
//---------------------------------------------------------------------------------------------------------------//
// REQUEST
struct SubsequentDeliveryKey
{
	1:	optional i32								CustomerOrderNo,		    // Table nachlieferpos::kdauftragnr
    2:	optional i32								PositionNo,				    // Table nachlieferpos::posnr
    3:	optional i32								Date,                       // Table nachlieferpos::datum
    4:	optional i16								PositionType,	            // Table nachlieferpos::postyp
}

struct SubsequentDeliveryAdjustment
{
	1:	optional SubsequentDeliveryKey				Key,
	2:	optional i32								Qty,	                    // Table nachlieferpos::menge
}
typedef list<SubsequentDeliveryAdjustment>	        SubsequentDeliveryAdjustmentList

struct SubsequentDeliveryAdjustmentRequest
{
	1:  optional i16                                BranchNo,
    2:  optional i32                                CustomerNo,
    3:	optional SubsequentDeliveryAdjustmentList	SubsequentDeliveries,
}

// RESPONSE
struct SubsequentDeliveryAcknowledgement
{
    1:	optional SubsequentDeliveryKey	            Key,
    3:  optional i32                                ArticleNo,
    4:  optional string                             ArticleCode,
    5:	optional i32						        PreviousQty,    // Table nachlieferpos::menge
    6:	optional i32						        AdjustedQty,	// Table nachlieferpos::menge
    7:	optional cscbase.ReturnStruct		        RetValue,
}
typedef list<SubsequentDeliveryAcknowledgement>	SubsequentDeliveryAcknowledgementList

struct SubsequentDeliveryAdjustmentResponse
{
	1:  optional i16                                    BranchNo,
    2:  optional i32                                    CustomerNo,
    3:	optional cscbase.ReturnStruct		            RetValue,
    4:	optional SubsequentDeliveryAcknowledgementList	SubsequentDeliveryAcknowledgements,
}
//#############################################################################################################################################################//
// </S U B S E Q U E N T    D E L I V E R Y>
//#############################################################################################################################################################//

//#############################################################################################################################################################//
// <CUSTOMER SPECIFIC PRICE FOR ARTICLE(S) >
//#############################################################################################################################################################//
///////////////
// REQUEST
///////////////
typedef list<string> ArticleCodeCollection

struct CustomerArticlePricesRequest
{
    1:  optional i16                                BranchNo,
    2:  optional i32                                CustomerNo,
    3:	optional ArticleCodeCollection              CollectionArticleCode,
}
///////////////
// RESPONSE
///////////////
struct PricingTier
{
    1:  optional i32                                ArticleQty,
    2:  optional double                             ArticlePrice,
}
typedef list<PricingTier> PricingTierCollection

struct PriceList
{
    1:  optional string                             PricingListNo,
    2:  optional PricingTierCollection              CollectionPricingTier,
}
typedef list<PriceList> PriceListCollection

struct CustomerArticlePrices
{
    1:  optional cscbase.ReturnStruct               RetValue,
    2:  optional string                             ArticleCode,
    3:  optional double                             PharmacyPurchasePrice,
    4:  optional PriceListCollection                CollectionPriceList,
}
typedef list<CustomerArticlePrices> CustomerArticlePricesCollection

struct CustomerArticlePricesResponse
{
    1:	optional cscbase.ReturnStruct               RetValue,
    2:	optional CustomerArticlePricesCollection    CollectionCustomerArticlePrices,
}


//#############################################################################################################################################################//
// </CUSTOMER SPECIFIC PRICE FOR ARTICLE(S)>
//#############################################################################################################################################################//


//#############################################################################################################################################################//
// <CUSTOMER TOURIDS BASED ON BRANCH AND DATE>
//#############################################################################################################################################################//

typedef list<string> TourIDsList;

struct CustomerTourInfo
{
    1: optional string                                  Tourid,
    2: optional i32                                     Idfnr,
    3: optional i32                                     DatumVersand,
    4: optional i32                                     ZeitVersand,
    5: optional i32                                     FahrtZeit,
    6: optional bool                                    Delivered
}

typedef list<CustomerTourInfo>                          CustomerTourInfoList

//#############################################################################################################################################################//
// <CUSTOMER WEEK TOURS BASED ON BRANCH AND CUSTOMER>
//#############################################################################################################################################################//

struct WeekTourInfo
{
    1: optional string                                  Tourid,
    2: optional i32                                     FahrtZeit,
    3: optional i16                                     Weekday,
    4: optional string                                  OrderType,
    5: optional bool                                    IsIbtTour,
    6: optional bool                                    IsBtmTour,
    7: optional bool                                    IsKKTour,
    8: optional bool                                    IsK08Tour,
    9: optional bool                                    IsK20Tour,
    10: optional bool                                   IsReturnsTour,
    11: optional i32                                    OrderPeriodFromTime,
    12: optional i32                                    OrderPeriodToTime,
    13: optional i32                                    OrderPeriodMainTime
}

typedef list<WeekTourInfo>                              WeekTourInfoList

///////////////////////////////////////////////////////////////////////////////////////////////////
/// REQUEST
///////////////////////////////////////////////////////////////////////////////////////////////////

struct CustomerTourIDsRequest
{
    1: optional i16                                     BranchNo,
    2: optional i32                                     TourDate
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/// RESPONSE
///////////////////////////////////////////////////////////////////////////////////////////////////

struct CustomerTourIDsResponse
{
    1: optional cscbase.ReturnStruct                    RetValue,
    2: optional i16                                     BranchNo,
    3: optional i32                                     TourDate,
    4: optional TourIDsList                             TourIDs,
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/// REQUEST
///////////////////////////////////////////////////////////////////////////////////////////////////

struct CustomerIDFsByTourIdRequest
{
    1: optional i16                                     BranchNo,
    2: optional i32                                     TourDate,
    3: optional TourIDsList                             TourIDs,
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/// RESPONSE
///////////////////////////////////////////////////////////////////////////////////////////////////

struct CustomerIDFsByTourIdResponse
{
    1: optional cscbase.ReturnStruct                    RetValue,
    2: optional i16                                     BranchNo,
    3: optional i32                                     TourDate,
    4: optional CustomerTourInfoList                    CustomerTourInfos,
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/// REQUEST
///////////////////////////////////////////////////////////////////////////////////////////////////

struct CustomerToursForWeekRequest
{
    1: optional i16                                     BranchNo,
    2: optional i32                                     CustomerNo,
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/// RESPONSE
///////////////////////////////////////////////////////////////////////////////////////////////////

struct CustomerToursForWeekResponse
{
    1: optional cscbase.ReturnStruct                    RetValue,
    2: optional i16                                     BranchNo,
    3: optional i32                                     CustomerNo,
    4: optional WeekTourInfoList                        WeekTourInfos,
}

//#############################################################################################################################################################//
// </CUSTOMER TOURIDS BASED ON BRANCH AND DATE>
//#############################################################################################################################################################//
