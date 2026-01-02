include "cscbase.thrift"

include "types/pricetypeenum.inc"
include "types/positiontypeenum.inc"
include "types/origintypeenum.inc"
include "types/orderrelationnotypeenum.inc"

namespace cpp csc.order
namespace csharp Csc.Order


struct OrderPositionRequest
{
    1: optional positiontypeenum.PositionTypeEnum	PosType,				// on request, only 0, 3 and 4 are allowed.
                                                    // TypeProductStocked:	properties 1-30
                                                    // TypeTextOnly:		properties 1,3,4
                                                    // TypeDispoItem:		properties 1,3,4, 12, 13, 21, 40-50

    2: optional string					ArticleCode, 				// d.ARTICLE_CODE
    3: optional i32 					QuantityOrdered,			// d.ORDERQTY			/* Bestellmenge */
    4: optional string					PositionText,				// d.REMARKS			/* Bemerkungstext */

    5: optional bool					AcceptInterBranchDelivery,	// d.SWAUX
    6: optional bool					AcceptRestDelivery, 		// d.SWRESTDELIVERY
    7: optional bool					AcceptDispoDelivery,		// d.SWDISPO
    8: optional bool					AcceptPartialDelivery,		// d.SWPARTDELIVERY

    10: optional i16					SequenceNo,					// d.ORDERSEQUENZNO 	/* internal OrderNo */
    11: optional i32					OriginCustomerNo, 			// d.IDFORIGIN			/* interne IDF-Nummer */
    12: optional i32					OriginOrderNo, 				// d.ORDERNOORIGIN		/* Ursprungs Auftragsnummer */
    13: optional i32					OriginPositionNo, 			// d.POSNOORIGIN		/* Ursprungs Positionsnummer */
    14: optional i16					InternalPosReference,		// auf Wunsch von Sebastian

    15: optional pricetypeenum.PriceTypeEnum	PriceType,			// d.PREIS_TYP			/* Preistyp */
    16: optional string 				XmlOrderReference,			// d.XMLTEXT			/* OrderReference */
    17: optional string 				XmlLineReference,			// d.XMLLINEREFERENCE	/* LineReference */

    20: optional i32					QuantityRebateInKind,		// d.QTYNATRA			/* Naturalrabatt */
    21: optional double 				PriceAep,					// d.PHARMPURCHPRICE	/* Apothekeneinkaufspreis */
    22: optional double 				PriceFree,					// d.MANUALPRICE		/* freier Preis */
    23: optional double 				DiscountPercentFree,		// d.MANUELDISCPCT		/* freier Rabatt */
//	24: optional i16					DiscountType, 				// d.SKINDOFDISCOUNT	/* Rabatttyp */

    30: optional string 				Batch, 						// d.BATCHNO			/* Chargen Nummer */
    31: optional bool					FixBatch,					//						/* Fixe Charge */

    40: optional string 				ArticleHandout,				// d.HANDOUT			/* Darreichform */
    41: optional string 				ArticleUnit,				// d.ARTICLEUNIT		/* Einheit */
    42: optional string 				ArticleName,				// d.ARTICLENAME		/* Artikelbezeichnung */
    43: optional double 				PriceEKGrosso,				// d.PREISEKGROSSO		/* Grosshandelseinkaufspreis */
    44: optional double 				TaxRate,					// d.TAXRATE			/* MwstSchluessel */
    45: optional double 				Postage,					// d.POSTAGE			/* Porto */

    50: optional string					MSV3RequestID,				// MSV3: Bestellung/@Id (GUID, length 36)
    51: optional string					MSV3RequestSupportID,		// MSV3: Bestellung/@BestellSupportId (Number 1 - 999999)
    52: optional string					MSV3OrderID,				// MSV3: Bestellung/Auftraege[]/@Id (GUID, length 36)
    53: optional string					MSV3OrderSupportID,			// MSV3: Bestellung/Auftraege[]/@AuftragsSupportID (Number 1 - 999999)

    60: optional i32 			        OCPOfferID,	                // OCP: identifier of the offer  (length 10)

}

typedef list<OrderPositionRequest> OrderPositionRequestList


enum OrderCloseMode
{
    CLOSE_MODE_CLOSE = 0,
    CLOSE_MODE_POSTPONE = 1,
    CLOSE_MODE_CANCEL = 2,

    CLOSE_MODE_CLOSE_INTERNET = 3,		// TODO is this really needed???
    CLOSE_MODE_POSTPONE_INTERNET = 4,	// TODO is this really needed???


    CLOSE_MODE_CLOSE_DEBTLIMIT = 5,
    CLOSE_MODE_POSTPONE_DEBTLIMIT = 6
}


struct DebtLimitStruct
{
    1: optional string						Reason,					// d.TEXT
    2: optional string						Comment,				// d.ARTICLETEXT
    3: optional string						User,					// d.REMARKS

    4: optional i16							ApprovalCancel,			// d.APPROVALCANCEL;
    5: optional i16							ApprovalClose,			// d.APPROVALCLOSE;
    6: optional i16							ApprovalPersonsNeeded,	// d.APPROVALPERSONSNEEDED;
}

struct NarcoticsLicenseStruct
{
    1: optional i32							NarcoticsDate,			// d.DATUMBTM			SetBTMLicense (BG)
    2: optional string						NarcoticsLicense,		// d.BTMFORMULARNR
}

struct RebateOrderStruct
{
    40: optional i32						RODateFrom,				// d.DATUMROVON 		SetROParam (RebateOrder BG)
    41: optional i32						RODateTo,				// d.DATUMROBIS
    42: optional i16						ROChain,				// d.KZROKETTE
}

struct OrderRelationNumber
{
    1: optional orderrelationnotypeenum.OrderRelationNoTypeEnum 	RelationType,			// d.RELATIONNOTYPE
    2: optional i32							                        RelationNo,				// d.RELATIONNO
}

typedef list<OrderRelationNumber>			OrderRelationNumberList

struct OpenOrderRequest
{
    1: optional i16 						    BranchNo,				// d.BRANCHNO
    2: optional i32 						    CustomerNo,				// d.CUSTOMERNO
    3: optional bool						    NoCustomerRouting,		//						TODO SH (evtl. nachziehen in Inquiry???)

    10: optional string 					    OrderType,				// d.KINDOFORDER
    11: optional string 					    ShipmentType,			// d.SHIPMENTTYPE
    12: optional string 					    BookingType,			// d.BOOKINGTYPE
    13: optional string 					    SubOrderType,			// d.SUB_ORDER_TYPE
    14: optional origintypeenum.OriginTypeEnum	OriginType,			    // d.BATCHSCHREIBEN
    15: optional i16						    OriginBranchNo,			// d.BRANCHNOORIGIN
    16: optional cscbase.Date				    DeferredPaymentDate,	// d.VALUTADATUM
    17: optional OrderRelationNumberList	    OrderRelationNumbers,	//

    20: optional i32 						    MSV3OrderPeriodId,		//						OpenOrderMSV3
    21: optional string 					    MSV3OrderLabel,			// d.ORDERLABEL			OpenOrderMSV3
    22: optional string 					    MSV3OriginalOrderLabel,	//						OpenOrderMSV3

    25: optional i16					        InternalOrderReference,	// auf Wunsch von Sebastian

    30: optional string 					    OrderText,				// d.REMARKS			SetOrderText
    31: optional list<string>				    HeadTexts,				// d.REMARKS			AddOrderHeadItem
    32: optional bool						    CallBack,				//						SetCallback

    40: optional string 					    Reference,				// d.REMARKS
    41: optional bool						    CheckDouble,			// d.SCHECKDOUBLE		Prüfen Referenznummer vorhanden
    42: optional i32						    DeliveryDate,			// d.DELIVERYDATE		KscsrvSetdelayeddate (BG)
    43: optional i32							TenderNo,				//	                    SetTenderNo (RS)
    44: optional string							DeliveryTour,			//						KscsrvSetTourId (BG)
    45: optional bool							IsCashOrder,			//						KscsrvChangePaymentToCashOrder (BG)

    50: optional i32						    OrderNo,				// d.ORDERNO			OpenOrderOrderno

    60: optional NarcoticsLicenseStruct		    NarcoticsLicenseParam,	// SetBTMLicense (BG)
    70: optional RebateOrderStruct			    RebateOrderParam,		// SetROParam (RebateOrder BG)

    80: optional bool                           TurnoverOrigin,         // Kennzeichnen zur gesonderten Behandlung in der Monatsrabattierung Frankreich (PMR888)
    81: optional string                         PharmacyOrderNo,        // SWIMP-CH-OR specific: XML Request XPath: /customerOrder/orderHeader/orderDetails/@PharmacyOrderNo --> IFX DB: KdAuftragInfo.KdAuftragBestellNr
    82: optional i32                            PharmacyCustomerNo,     // SWIMP-CH-OR specific: XML Request XPath: /customerOrder/orderHeader/orderDetails/@PharmacyCustomerNo --> IFX DB: KdAuftragInfo.IdfNrIntern

    90: optional bool                           ProformaOrder,          // Open proforma order (FR, BG)

    100: optional string				        OCPChannelID,			// OCP: web portal source of request identifier  (length 50)
    101: optional double					    OCPFreightCost,			// OCP: total Freight Cost of the Order
    102: optional double					    OCPCarriageFree,		// OCP: Carriage Free limit or min Order Value

}

struct CloseOrderRequest
{
    1: optional OrderCloseMode					CloseMode,
    2: optional bool							CalculateRangeRebates,	// (GetPositions, FR, BG)

    30: optional DebtLimitStruct				DebtLimitParam,			// for CREMA cancel/close
}

struct PlaceOrderRequest
{
    1: optional OpenOrderRequest			OpenRequest,
    2: optional CloseOrderRequest			CloseRequest,

    10 : OrderPositionRequestList			Positions,
}

struct TourInformation
{
    1: optional string				TourId,					// d.TOURID
    2: optional cscbase.Date		TourDate,				// d.TOURDATE
    3: optional cscbase.DateTime	TourDepartureDate,
    4: optional cscbase.DateTime	DeliveryDate,			// d.DELIVERYDATE
                                                            // d.TIMEDELIVERY
    5: optional i32					DeliveryTimeBuffer,		// d.KARENZZEIT

    10: optional string 			TourIdIbt,				// d.TOURIDIBT
    11: optional cscbase.Date		TourDateIbt,			// d.TOURDATEIBT
    12: optional cscbase.DateTime	TourDepartureDateIbt,
    13: optional cscbase.DateTime	DeliveryDateIbt,		// d.DELIVERYDATEIBT
                                                            // d.DELIVERYTIMEIBT

    14: optional i32				DeliveryTimeBufferIbt,	// d.KARENZZEIT
    15: optional i16				IbtType, 				// d.IBTTYPE


    20: optional cscbase.DateTime	ActTourClosingDate,		// d.ACTTOURCLOSINGDATE
                                                            // d.ACTTOURCLOSINGTIME
    21: optional cscbase.DateTime	NextTourClosingDate,	// d.NEXTTOURCLOSINGDATE
                                                            // d.NEXTTOURCLOSINGTIME
    22: optional cscbase.DateTime	NextTourDeliveryDate,	// d.NEXTTOURDELIVERYDATE
                                                            // d.NEXTTOURDELIVERYTIME
}

struct ArticleInformation
{
    1:  optional string					ArticleCode,		// d.ARTICLE_CODE
    2:  optional i32					ArticleNo,			// d.ARTICLENO
    3:  optional string					Ean,				// d.EAN
    4:  optional string					ArticleText,		// d.ARTICLETEXT		pxArticleText
    5:  optional string					ArticleName,		// d.ARTICLENAME		orderitem->ArtBase()->Bezeichnung()
    6:  optional string					ArticleLongName,	// d.ARTIKEL_LANGNAME	orderitem->ArtBase()->ArtikelLangname()
    7:  optional string					ArticleUnit,		// d.ARTICLEUNIT		orderitem->ArtBase()->Einheit()
    8:  optional string					ArticleHandout, 	// d.HANDOUT			orderitem->ArtBase()->Darreichform()
    9:  optional string					ATCCode,			//						orderitem->ArtBase()-ATC_Code()
    10: optional string					CodeBlocage,		// d->CODEBLOCAGE[0]	orderitem->ArtBase()->CodeBlocage()
    11: optional string					SeraCode,			// d->SERACODE
    12: optional string					XmlCode, 			// d->XMLCODE
    13: optional string					XmlText,			// d->XMLTEXT
    14: optional string					ArticleInfoText,	//						Tabelle "artinfotext" -> SWIMP HR

    15: optional i32					ManufacturerNo,
    16: optional string					ManufacturerName,

    20: optional double 				PricePharmacyPurchase,		// d->PHARMPURCHPRICE = orderitem->PreisEKApo();
    21: optional double 				PriceCustomerPurchase,		// d->CUSTPURCHPRICE = orderitem->PreisEKApoNetto();
    22: optional double 				PricePharmacySell,			// d->PHARMSELLPRICE = orderitem->PreisVKApo();
    23: optional double 				PriceLppr,					// d->LPPR_PRICE = orderitem->ReimbursementPrice(orderitem->ArtikelNr(),'2');
    24: optional double 				PriceTfr, 					// d->TFR_PRICE = orderitem->ReimbursementPrice(orderitem->ArtikelNr(),'1');

    30: optional cscbase.Date			CreationDate,
    31: optional cscbase.Date			ChangeDate,

    35: optional bool                   IsQuotaPPE,                 // KontingentPPE
}

struct OrderPositionResponse
{
    1: optional cscbase.ReturnStruct	RetValue,
    2: optional i32						OrderNo,					// d.ORDERNO
    3: optional i32						PositionNo,
    4: optional ArticleInformation		ArticleDelivered,
    5: optional ArticleInformation		ArticleOrdered,

    6: optional string					CodeBlocage,				// d->CODEBLOCAGE[0] = orderitem->ArtBase()->CodeBlocage()
    7: optional string					SeraCode,					// d->SERACODE
    8: optional string					XmlCode, 					// d->XMLCODE
    9: optional string					XmlText,					// d->XMLTEXT
    10: optional string					LackReasonCountryCode,		// d->LACKREASONCTYCODE
    11: optional string					PositionText,				// d.REMARKS			/* Bemerkungstext */
    12: optional string 				Batch, 						// d.BATCHNO			/* Chargen Nummer */
    13: optional bool					FixBatch,					//						/* Fixe Charge */
    14: optional i16					InternalPosReference,		// auf Wunsch von Sebastian

    15: optional i32					QuantityOrdered,			// d->ORDERQTY
    16: optional i32					QuantityDelivered,			// d->DELIVERYQTY orderitem->MengeGeliefert();
    17: optional i32					QuantityLack,				// d->QTYLACK
    18: optional i32					QuantityInterBranch,		// d->AUXQTY = orderitem->TotalIBTQuantity();
    19: optional i32					QuantityInterBranchPossible,// d->AUXQTYPOSSIBLE = orderitem->MengeMoeglich();
    20: optional i32					QuantityRestDelivery,		// d->RESTDELIVERYQTY = orderitem->MengeNachgeliefert();
    21: optional i32					QuantityDispo,				// d->DISPOQTY = orderitem->MengeDisponiert();
    22: optional i32					QuantityNatra,				// d->QTYNATRA = orderitem->MengeNatra();
    23: optional bool					Available,					// d->AVAILABLE
    24: optional i16					BranchNoIbt,				// d->AUXBRANCHNO = ps->Order()->AuxFil();
    25: optional i32					QuantityReserved,			// d->QTYRESERVATION
    26: optional bool					IbtQuantityAsNormal,		// flag: ibt qty delivered back as normal (QuantityDelivered)
    27: optional bool                   RestDeliveryPossible,       // is rest delivery generally possible for this article

    30: optional double 				PricePharmacyPurchase,		// d->PHARMPURCHPRICE = orderitem->PreisEKApo(); = AEP (APO Einkaufspreis) DB: ArtikelPreis.PreisEKApo
    31: optional double 				PriceInvoice, 				// d->PREISFAKTUR = orderitem->InvoiceValue();     // Rabattierter Preis
    32: optional double 				PriceCustomerPurchase,		// d->CUSTPURCHPRICE = orderitem->PreisEKApoNetto();
    33: optional double 				PricePurchase,				// d->PREISEKGROSSO = orderitem->PreisEKGrosso(); = ExFactory (in CH) = GEP (GrundEinkaufsPreis) DB: ArtikelPreis.PreisEkGrosso
    34: optional double 				Margin,						// d->MARGIN = orderitem->getMarginGepAep();
    35: optional double 				DiscountValuePct, 			// d->DISCOUNTVALUEPCT = orderitem->GetDiscountValuePct();
    36: optional double 				PricePharmacySell,			// d->PHARMSELLPRICE = orderitem->PreisVKApo(); = PublicPrice (in CH) = Patientenpreis = DB: ArtikelPreis.PreisVKApo
    37: optional double 				PriceBase,					// d->BASEPRICE = orderitem->BasePrice(); = AGP - (GEP * DiscountValuePct / 100). If AGP == 0 => use GEP istead!
    38: optional double 				PriceLppr,					// d->LPPR_PRICE = orderitem->ReimbursementPrice(orderitem->ArtikelNr(),'2');
    39: optional double 				PriceTfr, 					// d->TFR_PRICE = orderitem->ReimbursementPrice(orderitem->ArtikelNr(),'1');
    40: optional double 				PriceBaseAmedis,		// CH only: AGP = orderitem->PreisAGP() = DB: ArtikelPreis.PreisAGP = Amedis Grundpreis
    // Amedis Grundpreis (AGP) sollte als Ersatz für AEP in CH stehen. In CH ist AEP für SWIMP: CH-PA/CC/OR/DN nicht relevant. AGP ist der Verkaufspreis an Kunde (APO, usw. = Kunde)

                                                                //d->PHARMPURCHPRICEORG = ArtInfo->PreisEKApo();
                                                                //d->CUSTPURCHPRICEORG = ArtInfo->PreisEKApoNetto();
                                                                //if(d->CUSTPURCHPRICEORG == 0)
                                                                //d->CUSTPURCHPRICEORG = ArtInfo->PreisEKApo();
                                                                //d->PHARMSELLPRICEORG = ArtInfo->PreisVKApo();
                                                                    //d->LPPR_PRICEORG = orderitem->ReimbursementPrice(d->ARTICLENOORG,'2');
                                                                    //d->TFR_PRICEORG = orderitem->ReimbursementPrice(d->ARTICLENOORG,'1');
                                                                    //d->TAXRATEORG = ArtInfo->SalesTaxRate();
                                                                    //d->CODEBLOCAGEORG[0] = ArtInfo->CodeBlocage();


    50: optional i32					ExpiryDate, 				// d->EXPIRYDATE = orderitem->ArticleExpireDate(); // TODO Date
    51: optional double 				TaxRate,					// d->TAXRATE = orderitem->SalesTaxRate();
    52: optional i32					PromotionNo,				// d->PROMONO = orderitem->PromotionNo();
    53: optional string					PromotionName,				// d->PROMONAME = kscSel_Promotion(...)

    60: optional string 				XmlLineReference,			// d.XMLLINEREFERENCE	/* LineReference */

    65: optional i32                    PredictedAvailabilityDate,  // d->PREDICTEDAVAILABILITYDATE (AT)
    66: optional string                 LackReasonList,             // d->LACKREASONLIST (AT)

    70: optional i32                    ArticleOrderDate,
    71: optional i32                    ArticleGoodsReceiptTargetDate,

    100: optional TourInformation		TourInfo,
}

typedef list<OrderPositionResponse> OrderPositionResponseList


struct OrderValuesResponse
{
    1: optional double					OrdValFtaxFS, 			//	= ps->Order()->OrderValues()->OrdValFtaxFS();
    2: optional double					OrdValFtaxFSDisc,		//	= ps->Order()->OrderValues()->OrdValFtaxFSDisc();
    3: optional double					OrdValFtaxHF,			//	= ps->Order()->OrderValues()->OrdValFtaxHF();
    4: optional double					OrdValFtaxHFDisc,		//	= ps->Order()->OrderValues()->OrdValFtaxHFDisc();
    5: optional double					OrdValFtaxRS,			//	= ps->Order()->OrderValues()->OrdValFtaxRS();
    6: optional double					OrdValFtaxRSDisc,		//	= ps->Order()->OrderValues()->OrdValFtaxRSDisc();

    7: optional double					OrdValLtaxFS,			//	= ps->Order()->OrderValues()->OrdValLtaxFS();
    8: optional double					OrdValLtaxFSDisc,		//	= ps->Order()->OrderValues()->OrdValLtaxFSDisc();
    9: optional double					OrdValLtaxHF,			//	= ps->Order()->OrderValues()->OrdValLtaxHF();
    10: optional double 				OrdValLtaxHFDisc,		//	= ps->Order()->OrderValues()->OrdValLtaxHFDisc();
    11: optional double 				OrdValLtaxRS,			//	= ps->Order()->OrderValues()->OrdValLtaxRS();
    12: optional double 				OrdValLtaxRSDisc,		//	= ps->Order()->OrderValues()->OrdValLtaxRSDisc();

    13: optional double					OrdValNtaxFS,			//	= ps->Order()->OrderValues()->OrdValNtaxFS();
    14: optional double					OrdValNtaxFSDisc,		//	= ps->Order()->OrderValues()->OrdValNtaxFSDisc();
    15: optional double					OrdValNtaxHF,			//	= ps->Order()->OrderValues()->OrdValNtaxHF();
    16: optional double 				OrdValNtaxHFDisc,		//	= ps->Order()->OrderValues()->OrdValNtaxHFDisc();
    17: optional double 				OrdValNtaxRS,			//	= ps->Order()->OrderValues()->OrdValNtaxRS();
    18: optional double 				OrdValNtaxRSDisc,		//	= ps->Order()->OrderValues()->OrdValNtaxRSDisc();

    19: optional double 				TaxValFtaxFS,			//	= ps->Order()->OrderValues()->TaxValFtaxFS();
    20: optional double 				TaxValFtaxFSDisc,		//	= ps->Order()->OrderValues()->TaxValFtaxFSDisc();
    21: optional double 				TaxValFtaxHF,			//	= ps->Order()->OrderValues()->TaxValFtaxHF();
    22: optional double 				TaxValFtaxHFDisc,		//	= ps->Order()->OrderValues()->TaxValFtaxHFDisc();
    23: optional double 				TaxValFtaxRS,			//	= ps->Order()->OrderValues()->TaxValFtaxRS();
    24: optional double 				TaxValFtaxRSDisc,		//	= ps->Order()->OrderValues()->TaxValFtaxRSDisc();

    25: optional double 				TaxValLtaxFS,			//	= ps->Order()->OrderValues()->TaxValLtaxFS();
    26: optional double 				TaxValLtaxFSDisc,		//	= ps->Order()->OrderValues()->TaxValLtaxFSDisc();
    27: optional double 				TaxValLtaxHF,			//	= ps->Order()->OrderValues()->TaxValLtaxHF();
    28: optional double 				TaxValLtaxHFDisc,		//	= ps->Order()->OrderValues()->TaxValLtaxHFDisc();
    29: optional double 				TaxValLtaxRS,			//	= ps->Order()->OrderValues()->TaxValLtaxRS();
    30: optional double 				TaxValLtaxRSDisc,		//	= ps->Order()->OrderValues()->TaxValLtaxRSDisc();

    31: optional double 				TaxValNtaxFS,			//	= ps->Order()->OrderValues()->TaxValNtaxFS();
    32: optional double 				TaxValNtaxFSDisc,		//	= ps->Order()->OrderValues()->TaxValNtaxFSDisc();
    33: optional double 				TaxValNtaxHF,			//	= ps->Order()->OrderValues()->TaxValNtaxHF();
    34: optional double 				TaxValNtaxHFDisc,		//	= ps->Order()->OrderValues()->TaxValNtaxHFDisc();
    35: optional double 				TaxValNtaxRS,			//	= ps->Order()->OrderValues()->TaxValNtaxRS();
    36: optional double 				TaxValNtaxRSDisc,		//	= ps->Order()->OrderValues()->TaxValNtaxRSDisc();
}

struct OpenOrderResponse
{
    1: optional cscbase.ReturnStruct	RetValue,

    2: optional i16 					BranchNo,					// d.BRANCHNO (might have changed)
    3: optional i32 					CustomerNo,					// d.CUSTOMERNO (might have changed)
    4: optional i32 					Pid,						// d.PID
    5: optional i32 					OrderNo,					// d.ORDERNO
    6: optional string					OrderType,					// new
    7: optional string					PharmacyName,				// d.PHARMACYNAME
    8: optional string					MSV3OrderLabel,				// d.ORDERLABEL (MSV3)
    9: optional i16					    InternalOrderReference,	    // auf Wunsch von Sebastian
}

struct CloseOrderResponse
{
    1: optional cscbase.ReturnStruct	RetValue,

    2: optional i16 					BranchNo,					// d.BRANCHNO
    3: optional i32 					CustomerNo,					// d.CUSTOMERNO
    4: optional i32 					OrderNo,					// d.ORDERNO
    5: optional string					OrderType,					// new

    10: optional TourInformation		TourInfo,

    20: optional double 				OrderValue, 			// d->VALUEOFORDER		= ps->Order()->WertLieferung();
    21: optional i32					OrderLines,				// d->LINESOFORDER		= ps->Order()->AnzPos();
    22: optional i32					TextLines, 				// d->TEXTLINES 		= ps->Order()->AnzAlphaText();  //nase von ohne bestand auf alpha, bitte prüfen
    23: optional i32					LackLines, 				// d->LACKLINES 		= ps->Order()->AnzPosDafueFehler();
//	24: optional double 				WERTNETTO_FV,			// d->WERTNETTO_FV		= ps->Order()->GetValueNetCash(0);
//	25: optional double 				WERTTAX_FV, 			// d->WERTTAX_FV		= ps->Order()->GetValueSalesTax(0);
//	26: optional double 				WERTNETTO_KK,			// d->WERTNETTO_KK		= ps->Order()->GetValueNetCash(1);
//	27: optional double 				WERTTAX_KK, 			// d->WERTTAX_KK		= ps->Order()->GetValueSalesTax(1);
//	28: optional double 				WERTNETTO_EH,			// d->WERTNETTO_EH		= ps->Order()->GetValueNetCash(2);
    29: optional double 				RemainingCreditLimit,	// d->VALRESTCL			= ps->Order()->Customer()->RestCreditLimit();
//	30: optional i16					DeliveryBranchNo,	 	// d->DELIVERYBRANCHNO	= ps->Order()->FilialNr();
    31: optional bool					IsCashPayer,			// d->SWCASH[0] = '1'
    32: optional string 				PostponeReason,			// d->POSTPONEREASON	= GetOrderZugrund(ps,d->ORDERNO)
    40: optional OrderValuesResponse	OrderValues,			// needed only for BG
    50: optional DebtLimitStruct		DebtLimit,				// for CREMA cancel/close
}

struct PlaceOrderResponse
{
    1: optional cscbase.ReturnStruct		RetValue,

    2: optional OpenOrderResponse			OpenOrder,
    3: optional CloseOrderResponse			CloseOrder,
    4: optional OrderPositionResponseList	Positions,
}

struct ArticleExportPermittedRequest
{
    1: optional i16     BranchNo,           // d.BRANCHNO
    2: optional i32     CustomerNo,         // d.CUSTOMERNO
    3: optional i32     ArticleNo,          // d.ARTICLENO
}

struct ArticleExportPermittedResponse
{
    1: optional cscbase.ReturnStruct    RetValue,
    2: optional bool                    ExportPermitted,    // d.BRANCHNO
}
