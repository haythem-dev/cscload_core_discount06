/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

                 (c) Copyright 1994-1995 by NORDAT Network GmbH
                              All rights reserved

PXORDPR_.HPP
Private/protected customer order class members.
This file is used to hide internal functions and variables not available
at the API level.

REVISION HISTORY

05 Oct 1995 V1.00 REV 00 written by Wolfgang Hoppe.
*/

#ifndef PXORDPR__INC
    #define PXORDPR__INC

protected:
                      pxOrder(pxCustBase* customer,
                              const pxOrderValidTrans* vt= NULL,
                              const long n = 0L,
                              const long deliverydate = 0L,
                              const OriginTypeEnum batchschreiben = cORTYPE_UNKNOWN);

                      pxOrder(pxOrder& src);
                      pxOrder(pxSession *session, tKDAUFTRAG& src);

    pxOrder&          operator=(const pxOrder& src);
//  Assigns the values of 'src' to self and returns a reference to it.
    pxOrder&          operator=(const tKDAUFTRAG& src);
//  Assigns the values of the record structure 'src' to self and returns a
//  reference to self.

    friend
    pxOrder&          Assign(pxOrder& dest, const tKDAUFTRAG& src);
    friend
    tKDAUFTRAG&       Assign(tKDAUFTRAG& dest, const pxOrder& src);
    virtual  int      CompareTo(const nCollectable *that, void *p,
                                const long lparm) const;
    virtual  int     Get(DBAccessMode mode = cDBGET_READONLY);
    virtual  int     Put();

    static void InitOrderMaster(tKDAUFTRAG& rp);

    virtual  int     Read(const void *record);
    virtual  int     ReadLock(const void *record);
    virtual  int     Insert(const void *record);
    virtual  int     Update(const void *record);

    pxOrderItem*      AddNewItem(pxOrderItem *item);
    pxOrderItem*      AddNewCalcItem(pxOrderItem *item);
    pxOrderItem*      AddNewDiscountInfoItem(pxOrderItem *item);
    pxOrderItem*      AddNewProformaItem(pxOrderItem *item);
    pxOrderItem*      AddNewTemporaryItem(pxOrderItem *item);
    long             CountAuxDeliveryPos();
    long             CountDefects();

//  Helpers during order close:
    void              CloseState(const Order::States state);
    int               CloseItems();
    int               CloseTextDocs();
    int               CloseOrder();
    int               AutoItems(const int coolerq, const int opiateq,const int zytosq,const int commiq);
    int               Freightage(const int freightage);
    int               TriggerInvoice(const int commiq,const Order::States state);

    Order::States     SeparateContainer();
    Order::States     SeparateSpecials(int &coolerq, int &opiateq, int &reshospital, int &zytosq, int &auxposq, int &psychoq);
    Order::States     SeparateSpecialsSwitchOrder(pxSepOrderArtGroup* sepgroup);
    pxOrder*          SeparateNarcotics(int *opiateq, pxSepOrderArtGroup* sepgroup);
    pxOrder*          SeparateResHospital(int *reshospital, pxSepOrderArtGroup* sepgroup);
    pxOrder*          SeparateZytostatic(int *zytosq, pxSepOrderArtGroup* sepgroup);
    pxOrder*          SeparateCooler(int *coolerq, pxSepOrderArtGroupList* sepgroup);
    pxOrder*          SeparateAuxPositions(int *auxposq, pxSepOrderArtGroup* sepgroup);
    pxOrder*          SeparateHealthFund(int *healthfundq, pxSepOrderArtGroup* sepgroup);
    pxOrder*          SeparateRetail(int *retailq, pxSepOrderArtGroup* sepgroup);
    pxOrder*          SeparatePsycho(int *psychoq, pxSepOrderArtGroup* sepgroup);

    Order::States     SeparatePositivListPositions(int &positivlist);
    Order::States     SeparatePriceType(int &healthfundq, int &retailq);
    Order::States     SeparateBigOrder();
    Order::States     SeparateListFivePositions();
    Order::States     SeparateCapPositions();
    Order::States     SeparateManufacturerPositions();
    Order::States     SeparateManufacturerPositions(pxSepOrderArtGroup*  sepOrderArtGrp);
    void              XMLEncloserScaleSetEncloserDone();
    Order::States     XMLEncloserScale(Order::States state);
    Order::States     XMLEncloserScaleAssignNextRoute(Order::States state);
    int               SplittEncloseScale( const long FromPos, const char KoArt, Order::States state );
    Order::States     SeparatePrisoPositions(int &prisoq);
    Order::States     SeparateIbtBranchLines();
    Order::States     SeparateIbtBranchLines(const short ibtBranchNo, const nDate& departureDate,
                                            const basar::VarString& tourId, const bool waitForIbtPicking);
    Order::States     SeparateOrderLinesWithDifferentTour(int& coolerq, int& opiateq, int& zytosq);
    Order::States     SeparateOrderLinesForTour(const long departureDate, const basar::VarString& tourId, int& coolerq, int& opiateq, int& zytosq);
    Order::States     SeparateDelayedDelivery(const long date, int &coolerq, int &opiateq, int &zytosq);
    Order::States     SeparateReferenceNr( int &auxposq );
    Order::States     DayNightMergeProcessing(int &IbzPosq);
    Order::States     checkDelayedRebateOrder(Order::States state, int &healthfundq, int &retailq);
    int               CopyOrderHeadAndTailText(pxOrder* seporder);
    int               SetRestDeliveryPositionsToReadyForWorkup();
    int               SetDisposalPositionsToReadyForWorkup();

    pxOrder* GetExistingSplitDelayDeliveryOrder();
    bool IsSplitOrderAvailableForOrderConsolidation();
    pxOrder*          DDProcessing(const long date, int *coolerq, int *opiateq, int *zytosq);
    int               ProcessOrderDelayedDelivery(const long date);
    int               CheckDeliveryDate();
    int               CheckOverdriveState();
    pxOrder*          NewOrderReference(const nString& KdAuftragBestellNr);
    long              CountRefnr( const nString& KdAuftragBestellNr);
    int               ChangeContainerLevel();

//  Some Rangecalculation methodes
    int                 RangeCalculation();
//  Some Rangecalculation methodes just for NG application
    int                 TargetPromotionCalculation();
    int                 CollectItemTargetPromotions( pxRangeControl* rclentry);
    int                AssignDiscountPctToAllMembers( pxRangeControl* rclentry, pxDiscount* diskentry, pxItemDiscountList* dicl = NULL  );
    int                AssignDiscountQtyToAllMembers( pxRangeControl* rclentry, pxDiscount* diskentry );
    int                AssignDiscountToPosition( pxRangeControlList* rcl, pxItemDiscountList* dicl = NULL  );
    int                AssignTargetGrossProfitPct( pxRangeControl* rclentry );
    short              GetTargetBestPromotion(pxRangeControl* rclentry);

    int                AssignRangeDiscountPct( pxRangeControl* rclentry, pxItemDiscountList* dicl = NULL  );
    int                AssignRangeDiscountQty( pxRangeControl* rclentry );
    int                AssignRangeFixedDiscountVal( pxRangeControl* rclentry );
    int                AssignRangeDiscountQtyPct( pxRangeControl* rclentry, pxItemDiscountList* dicl = NULL );
    int                AssignRangeMultyCondArticle( pxRangeControl* rclentry, pxItemDiscountList* dicl = NULL );
    int                AssignRangeMultyCondManuMacturer( pxRangeControl* rclentry, pxItemDiscountList* dicl = NULL );
    int                AssignRangeBaseValue( pxRangeControl* rclentry, pxItemDiscountList* dicl = NULL );
    int                AssignRangeGrossProfitPct( pxRangeControl* rclentry );
    long               CalcTargetDiscountFacktor( pxRangeControl* rclentry);
    long               CalcPosTartgetDiscountFaktor( pxDiscount* diskentry);
    int                CheckPromotionValidity(const Order::States state);
    int                SpecialOmgRebateHandling();

//  French Application methodes
    int                ReduceCustConditions();


//  Application methodes
    pxOrderItem*      NewItem();
    pxOrderItem*      NewCalcItem();
    pxOrderItem*      NewDiscountInfoItem();
    pxOrderItem*      NewProformaItem();
    pxOrderItem*      NewTemporaryItem();
    void              FromPharmos();
    void              ToPharmos();
    void              Init();
    void              InitValues();
    void              ItemValues(pxOrderItem *item, pxItemDiscountList* discl = NULL);
    nMoney            AverageItemValue();
    bool              IsCreditSumOnTop();
    bool              CheckForCreditSumOnTop();
    int               CompleteCreditLimit();
    bool              IsOrderAffectingCreditLimit();

    int               Lock();
    int               UnLock();
    void              UnlockCstDiscAccEntry( pxCstDiscAcc* );
    bool              IsLocked() const;
    void              SetPseudoLock() { PseudoLock_ = true;}
    void              SetBGInfoOrder() { BGInfoOrder_ = true;}
    void              SetDoNotSplittOrder() { DoNotSplittOrder_ = true;}
    bool              IsDoNotSplittOrder()  { return DoNotSplittOrder_;}
    bool              isDayNightMergeNecessary();

    void OpenInfoCommon();

    bool tryGetLowerPromoCondition(pxOrderItem* item, long& promoBaseQty, long const restPromoQuotaCustomerQty, double const discountValuePct);
    long updateItemQuantity(pxOrderItem* item,  long const restPromoQuotaQty);
    void cleanPromotionQuota(pxOrderItem* item, double const discountValuePct);
    void addToDonePromoQuotasOnPromotionQuotaReached(pxPromotionQuotaCst* promoQuotaCustomer);
    void addToDonePromoQuotas(pxPromotionQuotaCst* const promoQuotaCustomer);
    void addSoldQtyCst(pxPromotionQuotaCst* const promoQuotaCustomer, long const q);
    void addSoldQtyBranch(pxPromotionQuota* const PromoQuotaBranch, long const q);
    void bookAsNewOrderItem(pxOrderItem* item, long const newItemQty);

    Order::States setNoValidRoute(std::string reasonDetail);

    pxOrderItem* getNewOrderItemProforma(pxRangeControl* rclentry, long articleNo, long quantity, PriceTypeEnum priceType);
    pxOrderItem* getNewOrderItemProformaOrSetTargetPositionsProblemState(pxRangeControl* rclentry, long articleNo, long quantity, PriceTypeEnum priceType);
    short checkQtyInStockBG(long articleNo, long discountQuantity);
    void verifyNewOrderItemProforma(pxOrderItem* newItem, short bestPromo);

    PriceTypeEnum getPriceType(short discountSpec);
    bool getPseudoArticleMembers(long discountArticle, pxCPValidityPeriodList*& cpvpl, pxCPValidityPeriod*& cpventry, pxArtComPackList*& acpl);

    int updateCustomerDebtlimit(pxDebitLimit* debtlimit);
    int completeCustomerDebtlimit(pxDebitLimit* debtlimit);
    nMoney orderValuesToCustomerDebtlimit(pxDebitLimit* debtlimit);
    bool hasPositionsOrNotIsCashPayer(long anzPos, PriceTypeEnum priceType);
    bool getOrderDiffValue(pxDebitLimit* debtlimit, nMoney orderValue, nMoney& diffValue);
    void increaseDayTurnOverAndPutItem(pxDebitLimit* debtlimit, nMoney orderValue);
    void decreaseDayTurnOverAndPutItem(pxDebitLimit* debtlimit, nMoney orderValue);
    void putItem(pxDebitLimit* debtlimit);
    nMoney undoCustomerDebtlimit(pxDebitLimit* debtlimit);
    bool getRebateMethValueOnCustomerFlags(nMoney& rebateMethValue);
    void setPaymentDateAndType(PriceTypeEnum priceType);
    bool setPaymentDateAndTypeOnArtPrice(PriceTypeEnum priceType);
    void commitOrRollback(pxKdAuftragDebtRel* debtRel);
    int writeChangeEvent(Order::States state);
    bool setErrorOnMissingLock();
    pxOrderItem* addItemAndProcess(pxOrderItem* item);
    void calcSplittBookItem(pxOrderItem* item);
    bool isDiscountOMGorUW(pxOrderItem* item);

private:

    friend class      pxOrderList;
    friend class      pxOrderTransmit;

    nBitMap           pflags_;          // internal processing flags
    pxCustBase        *Customer_;       // link to customer base class
    pxCustBase        *ShuttleCustomer_; // link to shuttle customer base class
    pxOrderItemList   *ItemList_;       // link to item list
    pxOrderItemList   *ItemListProforma_; // link to item list proforma
    pxOrderItemList   *ItemListTemporary_; // link to item list temporary
    pxTextDoc         *HeadText_;       // link order head text document
    pxTextDoc         *TailText_;       // link order tail text document
    pxCustRoute       *Route_;          // link to route currently allocated
    pxCustOrderType   *OrderType_;      // link to order type object
    pxCommType        *CommType_;       // link to commisiion type object
    pxStockTrans      *StockTrans_;     // link to commisiion type object
    long             laststock_;       // last stock amount of a stocked product
    long             auxstock_;        // auxiliarystock amount of a  ,, product
    short            auxfil_;          // alternate deliver company
    long             restquota_;       // rest quotaamount of a stock product
    long             subArticleNo_;    // substitution article possible
    nMoney           DefektWert_;      // Sum of all corrupt positions
    pxOrderItem      *ItemQuery_;      // point at item query object
    libLockManager::ILockGuardPtr m_LockGuard; // Lock object for order
    nTime            DateTimeCreated_; // Order creation date/time stamp
    short            CloseOptions_;    // Order close options
    long             FirstTransPos_    ; // first position of transmission

    pxRangeCollectList* RangeCollectList_; // List of rangemembers
    pxTimeTypeList*   StockReservTimeList_; // List of stockreservation timetype entries
    pxSepOrderArtGroupList* SepOrderArtGroupList_; // Link to separate group list
    pxCstDiscAccList*  CstDiscountAccount_; // Link to Dealers DiscountAccountList
    pxTenderHead*     TenderHead_;        // Link TenderHead entry on Tenderorders
    pxOrdTaxValues*   OrdTaxValues_;      // OrdTaxValues
    pxOrderDiscAccList* OrderDiscAccList_; // Order Discount Account List
    pxBalanceCollectList* BalanceCollectList_; // Balance List(BG cstdiscacc)
    pxValuesCollectList* ValuesCollectList_; // collection of order values
    pxOrderValues*    OrderValues_;       // pointer KDAUFTRAGWERTE(BG)
    pxOrderCalcMode*  OrderCalcMode_;     // pointer KDAUFTRAGRECHART(BG)
    pxDiscountList*   OrderPosDiscountList_; // BG Performance test code

//  Members exported to the data base:
    nBitMap           State_;           // This order's current state
    long              KdAuftragNr_;     // Kunde Auftrag Nummer
    long              IDFNr_;           // Kundennummer IDF
    nString           GeraetName_;      // Geraet Name
    nString           OrderTourId_;          // Tour Identifikation
    nString           TourIdAlt_;       // Tour Identifikation Alt
    long              PersonalNr_;      // Personalnr. Erfasser
    long              RechnungNr_;      // Rechnungsnummer
    short             FilialNr_;        // Filialnummer
    nString           KdAuftragArt_;    // Kunde Auftrag Art
    char              KoArt_;           // Kommissionierungsart
    char              BuchArt_;         // Buchungsart
    nDate             DatumValuta_;     // Datum Valuta
    nMoney            WertAuftrag_;     // Wert Auftrag
    nMoney            WertLieferung_;   // Wert Lieferung
    nMoney            WertZeilen_;      // Wert Zeilendurchschnitt
    long              AnzPos_;          // Anzahl Positionen
    long              AnzPosOB_;        // Anzahl Positionen ohne Berechng
    long              AnzPosDafue_;     // Anzahl Positionen Dafue
    long              AnzPosDafueFehler_;// Anzahl Positionen Dafue Fehler
    long              AnzAlphaText_;    // Anzahl Alphatexte
    long              AnzBTM_;          // Anzahl Betaeubungsmittel
    double            RabattBarProz_;   // Rabatt Bar in Prozent
    nClock            ZeitEndeAM_;      // Zeit Betriebsende morgens
    nClock            ZeitEndePM_;      // Zeit Betriebsende abends
    OriginTypeEnum    BatchSchreiben_;  // BatchSchreiben
    short             HerkunftFiliale_; // Herkunftfilialnummer
    nString           NaechsteTour_;    // naechste Tour
    nString           LetzteTour_;      // letzte   Tour
    long              DafueAuftragNr_;  // Dafue Auftragnummer
    nString           DafueGeraeteName_; // Dafue GeraeteName
    nString           Bemerkungen_;     // Bemerkungen
    nBitMap           ETAuftragSchalter_;// ETab Kundenauftrag
    long              KdAuftragNrFiliale_; // AuftragNr (A1) VSE
    OrderSendStatusEnum SendeStatus_;      // Status VSE-Transfer
    long              KundenNr_;          // KundenNr
    short             VertriebsZentrumNr_; // Vertriebszentrum
    nBitMap           RCEntryDeffered_;   // Reasoncodes for deferred entries
    nDate             DatumAuslieferung_; // Datum der Auslieferung
    long              KdAuftragNrOrg_;   // Auftragnummer aus der der Auftrag enstanden ist
    nDate             DatumOrg_;         // Datum OriginalAuftrag
    char              KzRestored_;       // KzRestored
    long              BatchAuftragNr_;   // Batch Auftragsnummer
    nString           SubOrderType_;     // subordertype
    nString           PaymentTerm_;      // payment terms
    short             AnzAuf_;           // Anzahl Aufträge (Auftragzusammen..)
    nDate             DatumValutaBatch_; // Datum Valuta aus Batch
    short             ValutaMonAuto_;    // Automatisches Valuta aus Kundestamm
    short             ValutaMonManuell_; // Valuta aus der manuellen Eingabeamm
    long              TenderNo_;         // Tender Number(RS/BG)
    nDate             DatumVersand_;     // Datum Versand
    nDate             DatumBTM_;         // Datum BTM
    nString           BTMFormularNr_;    // BTM Formular Nummer
    nMoney            WertNetto_;        // Wert Auftrag  Netto
    nMoney            WertRabatt_;       // Wert Auftrags Rabatt
    nString           InvoiceNumber_;    // Rechnungsnimmer
    nDate             PaymentDate_;      // Payment date YYYYMMDD
    char              PaymentType_;      // PaymentType C = Bar, Z = ZielKauf
    long              DriverID_;         // DriverId(BG)
    nString           XMLReferenceNo_;   // XML Reference Number
    long              LogisticVolume_;   // Logistic Volume collective orders (FR)
    nString           OrderLabel_;       // MSV3 Order Label
    short             DPODays_;          // ???
    long              OrderPeriodID_;    // MSV3 Order period

    nString           ReferenceNr_;      // Order Reference Number

    nMoney            SaveOrderValueDL_; // Save OrderValue for DebtLimitUpdate

    bool              UpdateDebtlimitK2_; // Update Debtlimit type K2
    bool              UpdateDebtlimitK1_; // Update Debtlimit type K1
    bool              PseudoLock_;       // just for InfoOrders

    bool              BGInfoOrder_;      // just for InfoOrders in Bulgaria

    bool              DoNotSplittOrder_; // Do not split this order

    short             ROChain_;          // BG Rebate Order for a String of Customer
                                         // 0 = No Chain
                                         // 1 = for the Chain
    long              ROMainCstNo_;      // BG Rebate Order Main Customer Number
    nDate             RODateFrom_;       // BG Rebate Order Period start
    nDate             RODateTo_;         // BG Rebate Order Period end
    bool              ChangedToCashOrder_;  //  BG Creditlimit exceeded, changed
                                            // ordertype to Chash(CO)
    bool              DeliveryDatePreset_;  // Datum Auslieferung gesetzt vom Kunden(BG Applikation)

    long              CstIBTDeliveryTime_;  // Customers Delivery Time for IBT Position
    long              CstIBTDeliveryDate_;  // Customers Delivery Date for IBT Position
    long              CstIBTTourDate_;      // Customers Tour Date for IBT Position
    long              KdAuftragNrOrgRO_  ;  // Ist Original RO Kdauftragnummer wo die DKRAK Sätze
                                            // gesperrt worden sind

    //EMail Values
    double            DLPercentage_;        // percentage needed for getting data to send debtLevelMail
    double            OrderValue_;          // value amout order
    double            CustomerDebtLimit_;   // customer debt limit value
    nMoney            UsedCustomerCredit_;  // used customer credit
    bool              NoDebtLimitCheck_;    // Don't check debtlimit
    pxEventReason::EventCodes EventCode_;   // event code for kdauftragereignis whene order is placed in status DF
    int               ApprovalsNeeded_;
    bool              IsReleased_;
    bool              DiscussionNeeded_;
    bool              NoCreditLimitCheck_; // Bulgarian application. Used in ordclose.cpp

#define bPFL_NEWORDER                 0 // new order creation in progress
#define bPFL_NOCUST_DESTRUCT          1 // do not destruct customer object
#define bPFL_NOT_CLOSEORDER           2 // do not close this order
//#define bPFL_LASTROUT                 3 // assign last rout
//#define bPFL_NOT_CONFIRMORDER         4 // do not send orderinformations
#define bPFL_MAPWIDTH                 8


#define PFTEST           pflags_.TestBit
#define PFON             pflags_.SetBit
#define PFOFF            pflags_.ClearBit

    bool     IsNewOrder       () {return PFTEST(bPFL_NEWORDER        );}
    void    SetNewOrder       () {       PFON  (bPFL_NEWORDER        );}
    void  ClearNewOrder       () {       PFOFF (bPFL_NEWORDER        );}

    bool     IsNoCustDestruct () {return PFTEST(bPFL_NOCUST_DESTRUCT );}
    void    SetNoCustDestruct () {       PFON  (bPFL_NOCUST_DESTRUCT );}
    void  ClearNoCustDestruct () {       PFOFF (bPFL_NOCUST_DESTRUCT );}

    bool     IsNOTCLOSEORDER  () {return PFTEST(bPFL_NOT_CLOSEORDER );}
    void    SetNOTCLOSEORDER  () {       PFON  (bPFL_NOT_CLOSEORDER );}
    void  ClearNOTCLOSEORDER  () {       PFOFF (bPFL_NOT_CLOSEORDER );}


#undef  PFTEST
#undef  PFON
#undef  PFOFF

    void AddHeadTextLine(double lDif);
    void IncreaseDayTurnOver(pxDebitLimit* lm, nMoney orderValue);
    void DecreaseDayTurnOver(pxDebitLimit* lm, nMoney orderValue);
    bool checkCreditLimitOverflow(pxDebitLimit* lm, nMoney& diffValue);
    void GetPriceTypeValues(nMoney& list5Value, nMoney& freeSaleValue, nMoney& healtHFundValue);
    nMoney CalculatePriceTypeValue(PriceTypeEnum priceType);
    bool CancelCurrentCreditDayTurnOver(pxDebitLimit* lm);
    bool RedoCreditDayTurnOver(pxDebitLimit* lm, nMoney orderValue);
    bool UndoCreditDayTurnOver(pxDebitLimit* lm, nMoney freeSaleValue, nMoney healtHFundValue, nMoney list5Value, bool bHandleListe5);
    bool UndoCreditDayTurnOver(pxDebitLimit* lm, nMoney orderValue);
    nMoney ShowCreditLimit(pxDebitLimit* debtlimit);

#endif
