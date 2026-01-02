#ifndef _CALLKSC_H
#define _CALLKSC_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define YES 1
#define NO 0

#ifdef _WINDLL
#define PROTOTYPE __declspec(dllexport)
#else
#define PROTOTYPE 
#endif

PROTOTYPE int ConnectServer(const char *IniFile /* name of inifile */, orderinfoS *Info );
PROTOTYPE int ConnectServerNoIni(const char *DeviceName /* name of Device (XML) */, const long UID, const int PortNo, const char *Server, orderinfoS *Info );
PROTOTYPE int DisconnectServer(orderinfoS *Info);

PROTOTYPE int SetTourAndDeliveryDate(const long DeliveryDate, const char *TourId, orderinfoS *Info);
PROTOTYPE int OpenOrder(const long CustomerNo, const char *OrderTyp, const char *SubOrderTyp, orderinfoS *Info);
PROTOTYPE int OpenOrderVz(const short VzNr, const long CustomerNo, const char *OrderTyp, const char *SubOrderTyp, orderinfoS *Info);
PROTOTYPE int SetOrderType  (const char *OrderTyp, const char *KoArt, const char *BuchArt, orderinfoS *Info);
PROTOTYPE int SetOrderTypeSub  (const char *OrderTyp, const char *KoArt, const char *BuchArt, const char *SubOrderTyp, orderinfoS *Info);
PROTOTYPE int SetOrderText(const char *text, orderinfoS *Info);
PROTOTYPE int SetTenderNo(const int TenderNo, orderinfoS *Info);
PROTOTYPE int SetBatchOrderTyp(const int BatchTyp,const short OriginBranch,const int ValutaDatum,const char *EdiLieferSchein,const char *JobNo,orderinfoS *Info);
PROTOTYPE int SetValueDate(const int ValutaDatum,orderinfoS *Info);
PROTOTYPE int SetBatchValueDate(const int Batchschreiben,const short BranchNoOrigin,const int ValutaDatum,orderinfoS *Info);
PROTOTYPE int SetROParam  (const long DatumVon, const long DatumBis, const char *KzKette, orderinfoS *Info);
PROTOTYPE int CloseOrder (const char *strText, orderinfoS *Info);
PROTOTYPE int CancelOrder(orderinfoS *Info);
PROTOTYPE int PostponeOrder(orderinfoS *Info);
PROTOTYPE int SetTourId(const char *TourId, orderinfoS *Info);
PROTOTYPE int SetBTMLicense(const long datum, const char *btmlicence, orderinfoS *Info);
PROTOTYPE int SetOrderReference(const char *text, orderinfoS *Info);
PROTOTYPE int SetOrderRelationNo(const long RelationNo, const short RelationNoType, orderinfoS *Info);
PROTOTYPE int SetProLink  (const long KdauftragnrPro, const long DatumPro, const char *RechnrPro, orderinfoS *Info);
PROTOTYPE int SetOrderInfoDetails(const long pharmacyorderno, const long pharmacycustomerno, const char* customertour, const char* typeofdispatch, const long processid, orderinfoS *Info);
PROTOTYPE int SetTurnOverOrigin(orderinfoS *Info);
PROTOTYPE int GetManufacturerForArticle(const char *Code, orderinfoS *Info);

/************************************************************************/
/* Artikelanfragen   */
/************************************************************************/
PROTOTYPE int OpenInfoOrder(const short VzNr, const long CustomerNo, const short Infolevel, orderinfoS *Info);
PROTOTYPE int OpenProformaOrder(const short VzNr, const long CustomerNo, orderinfoS *Info);
PROTOTYPE int GetPositions(orderinfoS *Info);
PROTOTYPE int GetArticleInfo(stArticleInfo *Info);
PROTOTYPE int GetArticleInfoCode(stArticleInfoCode *Info);
PROTOTYPE int GetArticleInquiry(const long Qty, const long number, const char *EAN, const short Infolevel, orderinfoS *Info);
PROTOTYPE int GetArticleInquiryCode(const long Qty, const char *Code, const short Infolevel, orderinfoS *Info);
PROTOTYPE int GetArticleStock(const long Qty, const char *Code, const short Infolevel, orderinfoS *Info);
PROTOTYPE int GetArticleAvailabilityBulk(const short branchno, const long customerno, char* articleList);
PROTOTYPE int GetArticleStockBulk(const short branchno, const long customerno, char* articleList);
PROTOTYPE int IsExportPermitted(const short branchNo, const long customerNo, const long articleNo, orderinfoS* info);

/************************************************************************/
/* OpenClOrderSaleCenterAufnr, return value:ordernr or if error less then zero   */
/************************************************************************/
PROTOTYPE int OpenOrderReference(const long CustomerNo, const char *Reference, orderinfoS *Info);
PROTOTYPE int OpenOrderReferenceVz(const short VzNr, const long CustomerNo, const char *Reference, orderinfoS *Info);
PROTOTYPE int OpenOrderReferenceVzType(const short VzNr,
												   const long CustomerNo,
												   const char *Reference,
												   const char *OrderTyp,
												   const char *KoArt,
												   const char *BuchArt,
												   const char *SubOrderTyp,
												   orderinfoS *Info);
PROTOTYPE int OpenOrderReferenceVzTypeDate(const short VzNr,
												   const long CustomerNo,
												   const char *Reference,
												   const char *OrderTyp,
												   const char *KoArt,
												   const char *BuchArt,
												   const char *SubOrderTyp,
												   const long DeliveryDate,
												   orderinfoS *Info);

/************************************************************************/
/* Internet-Auftrags-Methoden   */
/************************************************************************/
PROTOTYPE int CloseOrderInternet (const char *strText, orderinfoS *Info);
PROTOTYPE int PostponeOrderInternet(orderinfoS *Info);
PROTOTYPE int OpenOrderInternetOrderno( const long lOrderNo, orderinfoS *Info);
PROTOTYPE int SetReferenceNo(const long CustomerNo, const char *Reference, orderinfoS *Info);
PROTOTYPE void SetCheckDouble();
PROTOTYPE void SetNoRouting();

/************************************************************************/
/* Crema-Auftrags-Methoden   */
/************************************************************************/
PROTOTYPE int OpenOrderOrderno( const long lOrderNo, orderinfoS *Info);
PROTOTYPE int CloseOrderDebtlimit (const char *strReason,const char *strComment,const char *strUser,const char *strGuid,const char *strUrl, orderinfoS *Info);
PROTOTYPE int CancelOrderDebtlimit (const char *strReason,const char *strComment,const char *strUser,const char *strGuid,const char *strUrl, orderinfoS *Info);
PROTOTYPE int GetApprovalData (const long orderNo, const short branchNo, orderinfoS *Info);

/************************************************************************/
/* MSV3-Auftrags-Methoden   */
/************************************************************************/
PROTOTYPE int OpenOrderMSV3(const short VzNr,
										const long CustomerNo,
										const char *OrderTyp,
										const char *KoArt,
										const char *BuchArt,
										const char *OrderLabel,
										orderinfoS *Info);

/************************************************************************/
/* Neue-Auftrags-Methoden   */
/************************************************************************/
PROTOTYPE int CheckDoubleOrder(orderinfoS *Info);
PROTOTYPE int SetCallback(orderinfoS *Info);
PROTOTYPE int SetDeliveryDate(const long Date, orderinfoS *Info);
PROTOTYPE int ChangePaymentToCashOrder(orderinfoS* info);

/************************************************************************/
/* AddItem, return value:item quantity or if error less then zero   */
/************************************************************************/
PROTOTYPE int AddOrderItem(const long Qty, const long number, const char *EAN,
				 const int iAux,			/* auxiliary */
				 const int iRestDel,		/* restdelivery */
				 const int iDispo,		/* dispose */
				 const int iPartDel,		/* part delivery */
				 const short sSeqNo,		/* internal OrderNo */
				 const int iIdfOrigin,	/* interne IDF-Nummer */
				 const int iOrderNoOrigin,	/* Ursprungs Auftragsnummer */
				 const int iPosNoOrigin,	/* Ursprungs Positionsnummer */
				 const char *strText, orderinfoS *Info);

/************************************************************************/
/* AddItemPT, return value:item quantity or if error less then zero   */
/************************************************************************/
PROTOTYPE int AddOrderItemPT(const long Qty, const long number, const char *EAN,
				 const int iAux,			/* auxiliary */
				 const int iRestDel,		/* restdelivery */
				 const int iDispo,		/* dispose */
				 const int iPartDel,		/* part delivery */
				 const short sSeqNo,		/* internal OrderNo */
				 const int iIdfOrigin,	/* interne IDF-Nummer */
				 const int iOrderNoOrigin,	/* Ursprungs Auftragsnummer */
				 const int iPosNoOrigin,	/* Ursprungs Positionsnummer */
				 const int iPriceType,	/* Preistyp */
				 const char *strText, orderinfoS *Info);

/************************************************************************/
/* AddItemPT, return value:item quantity or if error less then zero   */
/************************************************************************/
PROTOTYPE int AddOrderItemCode(const long Qty, const char *Code,
				 const int iAux,			/* auxiliary */
				 const int iRestDel,		/* restdelivery */
				 const int iDispo,		/* dispose */
				 const int iPartDel,		/* part delivery */
				 const short sSeqNo,		/* internal OrderNo */
				 const int iIdfOrigin,	/* interne IDF-Nummer */
				 const int iOrderNoOrigin,	/* Ursprungs Auftragsnummer */
				 const int iPosNoOrigin,	/* Ursprungs Positionsnummer */
				 const int iPriceType,	/* Preistyp */
				 const char *strText, orderinfoS *Info);

/************************************************************************/
/* AddItemCodeRef, return value:item quantity or if error less then zero   */
/************************************************************************/
PROTOTYPE int AddOrderItemCodeRef(const long Qty, const char *Code,
				 const int iAux,			/* auxiliary */
				 const int iRestDel,		/* restdelivery */
				 const int iDispo,		/* dispose */
				 const int iPartDel,		/* part delivery */
				 const short sSeqNo,		/* internal OrderNo */
				 const int iIdfOrigin,	/* interne IDF-Nummer */
				 const int iOrderNoOrigin,	/* Ursprungs Auftragsnummer */
				 const int iPosNoOrigin,	/* Ursprungs Positionsnummer */
				 const int iPriceType,	/* Preistyp */
				 const char *strText,		/* Bermerkungstext */
				 const char *strRef,		/* Line Reference */
				 orderinfoS *Info);

/************************************************************************/
/* AddItemCodeRefFree, return value:item quantity or if error less then zero   */
/************************************************************************/
PROTOTYPE int AddOrderItemCodeRefFree(const long Qty, const char *Code,
				 const int iAux,			/* auxiliary */
				 const int iRestDel,		/* restdelivery */
				 const int iDispo,		/* dispose */
				 const int iPartDel,		/* part delivery */
				 const short sSeqNo,		/* internal OrderNo */
				 const int iIdfOrigin,	/* interne IDF-Nummer */
				 const int iOrderNoOrigin,	/* Ursprungs Auftragsnummer */
				 const int iPosNoOrigin,	/* Ursprungs Positionsnummer */
				 const int iPriceType,	/* Preistyp */
				 const char *strText,		/* Bermerkungstext */
				 const char *strRef,		/* Line Reference */
				 const double dPriceAep,	/* neuer AEPreis */
				 const double dPrice,		/* freier Preis */
				 const double dPCT,		/* freier Rabatt */
				 orderinfoS *Info);

PROTOTYPE int AddOrderItemCodeRefFreeLineRef(const long Qty, const char *Code,
				 const int iAux,			/* auxiliary */
				 const int iRestDel,		/* restdelivery */
				 const int iDispo,		/* dispose */
				 const int iPartDel,		/* part delivery */
				 const short sSeqNo,		/* internal OrderNo */
				 const int iIdfOrigin,	/* interne IDF-Nummer */
				 const int iOrderNoOrigin,	/* Ursprungs Auftragsnummer */
				 const int iPosNoOrigin,	/* Ursprungs Positionsnummer */
				 const int iPriceType,	/* Preistyp */
				 const char *strText,		/* Bermerkungstext */
				 const char *strRef,		/* Line Reference */
				 const double dPriceAep,	/* neuer AEPreis */
				 const double dPrice,		/* freier Preis */
				 const double dPCT,		/* freier Rabatt */
				 const char *strLineRef,	/* LineReference */
				 orderinfoS *Info);

/************************************************************************/
/* AddItemCodeRefFree, return value:item quantity or if error less then zero   */
/************************************************************************/
PROTOTYPE int AddOrderItemRebateInKind(
				 const long Qty,			/* order quantity */
				 const long RebateInKind,	/* rebate in kind quantity */
				 const char *Code,
				 const int iAux,			/* auxiliary */
				 const int iRestDel,		/* restdelivery */
				 const int iDispo,		/* dispose */
				 const int iPartDel,		/* part delivery */
				 const short sSeqNo,		/* internal OrderNo */
				 const int iIdfOrigin,	/* interne IDF-Nummer */
				 const int iOrderNoOrigin,	/* Ursprungs Auftragsnummer */
				 const int iPosNoOrigin,	/* Ursprungs Positionsnummer */
				 const int iPriceType,	/* Preistyp */
				 const char *strText,		/* Bermerkungstext */
				 const char *strRef,		/* Line Reference */
				 const double dPriceAep,	/* neuer AEPreis */
				 const double dPrice,		/* freier Preis */
				 const double dPCT,		/* freier Rabatt */
				 orderinfoS *Info);

/************************************************************************/
/* AddOrderItemCodeRab, return value:item quantity or if error less then zero   */
/************************************************************************/
PROTOTYPE int AddOrderItemCodeRab(const long Qty, const char *Code,
				 const int iAux,				/* auxiliary */
				 const int iRestDel,			/* restdelivery */
				 const int iDispo,			/* dispose */
				 const int iPartDel,			/* part delivery */
				 const short sSeqNo,			/* internal OrderNo */
				 const int iIdfOrigin,		/* interne IDF-Nummer */
				 const int iOrderNoOrigin,	/* Ursprungs Auftragsnummer */
				 const int iPosNoOrigin,		/* Ursprungs Positionsnummer */
				 const int iPriceType,		/* Preistyp */
				 const long lDiscQty,			/* Naturalrabatt */
				 const double dPCT,			/* freier Rabatt */
				 const short sKindOfDiscount,	/* Rabatttyp */
				 const char *strText, orderinfoS *Info);

/************************************************************************/
/* AddTextItem, return value:item quantity or if error less then zero   */
/************************************************************************/
PROTOTYPE int AddTextItem(const long Qty, const char *strText, orderinfoS *Info);

PROTOTYPE int AddDispoItem(const long Qty,
                 const char *strRemarks,
                 const char *strDarreichform,
                 const char *strEinheit,
                 const char *strArtBez,
                 const double dPreiskgrosso,
                 const double dPreiskapo,
                 const double dMwstSchluessel,
                 const long lKdAuftragNr,
                 const long lPosNr,
                 const double dPorto,
                 orderinfoS *Info);

PROTOTYPE int AddOrderHeadItem(const char *strText, orderinfoS *Info); /* AddOrderHeadItem, return value:item quantity or if error less then zero   */
PROTOTYPE int AddOrderItemCodeBatch(const long Qty, const char *Code, const char *BatchNo /* Chargen Nummer */, const int iPriceType /* Preistyp */, const char *strText, orderinfoS *Info); /* AddItemPT, return value:item quantity or if error less then zero   */

#ifdef __cplusplus
}
#endif /* __cplusplus */    

#endif
