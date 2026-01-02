#ifndef PXCSTBAS_DOTH
#define PXCSTBAS_DOTH

#include "pxbase/pxrecord.hpp"
#include "types/pricetypeenum.inc"
#include "types/origintypeenum.inc"
#include <date.hpp>
#include <money.hpp>
#include <libbasarcmnutil_date.h>

#include "pxartcls.hpp"
#include "icustomerflaggetter.h"

struct tKUNDE;
class pxCustomerFlags;
class pxCustBaseInformation;
class pxCustBusinessTimes;
class pxCustBusinessTimesList;
class pxCustDelDelivery;
class pxCustDiscCondition;
class pxCustomerGrpFlagsList;
class pxCustOrderTypeList;
class pxCstPaymentTermsList;
class pxCustPharmGroupList;
class pxCstPrintList;
class pxCustRouteList;
class pxCustRoutingList;
class pxCustRouteWeekList;
class pxCstSepOrderArtGroupList;
class pxCustTerms;
class pxDebitLimit;
class pxDonePromoQuotasList;
class pxEncloserScaleList;
class pxGoodsDelivery;
class pxOrder;
class pxOrderItem;
class pxRangeList;
class pxRangeMemberList;
class pxSession;
class pxSubOrderType;
class pxTimeTypeList;
class TourManager;

class pxCustBase : public pxDBRecord, public csc::pricing::ICustomerFlagGetter
{
public:
    virtual           ~pxCustBase();
// constructors:
                      pxCustBase(pxCustBase& src);
                      pxCustBase(pxSession *session);
                      pxCustBase(pxSession *session, short Vertriebszentrum, long KundenNr, DBAccessMode mode = cDBGET_READONLY);

    pxCustBase&       operator=(const pxCustBase& src);
//  Assigns the values of 'src' to self and returns a reference to it.

    virtual int             Get(DBAccessMode mode = cDBGET_READONLY);
    virtual bool            isHospitalMarket() const;

//  set members
             void           SetNoSeparate(bool bSeparate = true)
                            {NoSeparate_ = bSeparate;}
//  Queries:
    pxCustomerFlags&        Flags();
    pxCustomerGrpFlagsList* CustomerGroupFlagsList();
    pxCustTerms&            Terms();
//    pxCustTermGroupList*    TermGroupList();
    pxCustOrderTypeList*    OrderTypeList();
    pxCustRouteList*        RouteList();
    pxCustRouteList*        RouteListOrderType(const nString& KdAuftragArt = "");
    pxCustRouteList*  OrdTypeRouteList();
    pxCustRouteWeekList*     RouteWeekList();
    pxCustRouteWeekList*     RouteWeekListOrderType(const nString& KdAuftragArt = "");
    pxCustRouteWeekList*     OrdTypeRouteWeekList();
    void                     DeleteRouteList();
    pxCustBusinessTimesList* BusyList();
    pxCustBusinessTimes&     BusyTime();
    pxTimeTypeList*          CustTimeList();
    pxCustPharmGroupList*    PharmGroupList();
    long                     GetDeferredOrderNr();
    pxCustDelDelivery*       getDelayedDelivery(const nDate& date, const bool withTransportExclusion);
    int                      ConsolidationTime( nString& TourId, const nTime& orderDayTimeCreation);
    int                      ParkDeliveryOrder(pxGoodsDelivery*  GDentry, pxOrder** order, pxOrderItem** item);
    pxOrder*                 FindBatchOrder(const long BatchAuftragNr);
    const nString&           FirstTourId()       { return FirstTourId_;           }
    const nString&           LastTourId()        { return LastTourId_;            }

    // some queries and methodes for short business
    pxCustDiscCondition*       CustDiscCondition() { return CustDiscCondition_;  }
    pxSubOrderType*            SubOrderType()      { return SubOrderType_;       }
    pxCustBaseInformation*     CustBaseInformation();
    pxCstSepOrderArtGroupList* CstSepOrderArtGroupList(); // Customer separate article group list
    pxDebitLimit*              DebitLimitK2();            // Customers Debtlimit entry(type K2)
    pxDebitLimit*              DebitLimitK1();            // Customers Debtlimit entry(type K1)
    pxCstPaymentTermsList*     CstPaymentTermsList();     // Customers Payment Termlist
    pxRangeList*               DiscountGrpListFive();     // Customers DiscountGrp entry for a list of article(list 5 )
    pxRangeMemberList*         DiscountGrpMemListFive();  // Customers DiscountGrpMem list of article(list 5 )
    pxCstPrintList*            CstPrintList();            // Customers Print info. list
    pxEncloserScaleList*       EncloserScaleList();       // Customers encloserscale info. list
    pxDonePromoQuotasList*     DonePromoQuotaList();      // Customers DonePromoQuotas  info. List (BG just for raising Performance)
    pxCustRoutingList*         CustomerRoutingList();       // Customer Routing List


    int               DiscountConditions(const nString& OrderType, const nString& SubOrderType);

    bool              IsQuantityRaising();
    bool              IsCashPayer();
    bool              IsCashPayer( PriceTypeEnum pricetype, pxOrder* order );
    bool              IsCreditLimitRelevant( PriceTypeEnum pricetype );
    bool              IsDelayedDelivery(nString& TourId, bool withTransportExclusion);
    nMoney            RestCreditLimit();
    int               ConvertLanguage(const nString& langcode);
    bool              IsNoRoutesToday();
    nDate             NextDeliveryDay();
    bool              IsHealthFundAuthorized();

    bool              IsNotAuxDeliveryUser() const				{ return (VerbundKunde_ == '0'); }  // = N
    bool              IsAuxDeliveryUser() const					{ return (VerbundKunde_ == '1'); }  // = J
    bool              IsNeverAuxDeliveryUser() const			{ return (VerbundKunde_ == '2'); }  // = G
    bool              IsSpecialAuxDeliveryUser() const			{ return (VerbundKunde_ == '3'); }  // = S
    bool              IsAuxDeliveryAllowed() const				{ return (IsAuxDeliveryUser() || IsSpecialAuxDeliveryUser()); }
    bool              IsUnusualAuxDeliveryUser() const			{ return (VerbundKunde_ == '4'); }
    bool              IsAuxDeliveryInfoUser() const				{ return (VerbundKunde_ == '5'); }  // = M // AuxDeliveryInfoUser just becomes information about possible auxdelivery, he is not able to book article within the auxdelivery service.
    bool              IsNoCooler() const						{ return (KuehlBox_ == '0'); }
    bool              IsCoolerBeneath4Degrees() const			{ return (KuehlBox_ == '1'); }
    bool              IsCoolerBeneath8Degrees() const			{ return (KuehlBox_ == '2'); }
    bool              IsCoolerBeneath20Degrees() const			{ return (KuehlBox_ == '3'); }
    bool              IsNotRestDeliveryUser() const				{ return (NachLieferTyp_ == '0' || NachLieferTyp_ == '1'); }
    bool              IsAskCustomerForRestDelivery() const		{ return (NachLieferTyp_ == '2'); }
    bool              IsGeneralRestDeliveryUser() const			{ return (NachLieferTyp_ == '3'); }
    bool              IsImmediateRestDeliveryUser() const		{ return (NachLieferTyp_ == '4'); }
    bool              IsAskRestDeliveryUser() const				{ return (NachLieferTyp_ == '5'); }
    bool              IsReservOrderedQuantity() const			{ return (NachLieferTyp_ == '6'); }
    bool              IsParkRestDeliveryOrder() const			{ return (NachLieferTyp_ == '7'); } //  The order generatet from the Restdelivery Positions, has to be parked for the next Day. For the normal orderlogik, the customer is treated as an ImmediateRestDeliveryUser( type 4)
    bool              IsIgnoreRestDeliveryService() const		{ return (NachLieferTyp_ == '9'); }
    bool              IsCreditLimited() const					{ return (PartnerNr_ > 0); }
    bool              IsPsychoAllowed() const					{ return (KzPsychoStoffe_ == '1'); }
    bool              IsVZKk1() const							{ return (VZKk1_ == '1'); }
    bool              IsNoSeparate() const						{ return NoSeparate_; }
    bool              IsNoInfoLevel() const						{ return ((XMLInfoLevel_ == '0') || (XMLInfoLevel_ == ' ')); }
    bool              IsInfoLevelLow() const					{ return (XMLInfoLevel_ == '1'); }
    bool              IsInfoLevelMiddle() const					{ return (XMLInfoLevel_ == '2'); }
    bool              IsInfoLevelHigh() const					{ return (XMLInfoLevel_ == '3'); }
    bool              IsInfoLevelNoLimit() const				{ return (XMLInfoLevel_ == '4'); }
    bool              IsCommercialRounding() const				{ return (CalculationType_ == '0'); }
    bool              IsMathematicalRounding() const			{ return (CalculationType_ == '1'); }
    bool              IsRebateMethFreeSale() const				{ return (RebateMethFreeSale_ == 1); }
    bool              IsRebateMethHealthf() const				{ return (RebateMethHealthf_ == 1); }
    bool              HasDebitLimitK1();
    bool              HasDebitLimitK2();

    void              SetHasDebitLimitK1()                      { HasDebitLimitK1_ = true; }
    void              ClearHasDebitLimitK1()                    { HasDebitLimitK1_ = false; }
    void              SetHasDebitLimitK2()                      { HasDebitLimitK2_ = true; }
    void              ClearHasDebitLimitK2()                    { HasDebitLimitK2_ = false; }

    short            GetPrint(const PriceTypeEnum pricetype);
    short            GetDeductionAep(const PriceTypeEnum pricetype);
    short            GetDeductionAvp(const PriceTypeEnum pricetype);
    short            GetWithColumnNr(const PriceTypeEnum pricetype);
    short            GetInvoiceEmail(const PriceTypeEnum pricetype);

    int              SetPrint(const short print, const PriceTypeEnum pricetype);
    int              SetDeductionAep(const short deductionaep, const PriceTypeEnum pricetype);
    int              SetDeductionAvp(const short deductionavp, const PriceTypeEnum pricetype);
    int              SetWithColumnNr(const short withcolumnnr, const PriceTypeEnum pricetype);
    int              SetInvoiceEmail(const short invoiceemail, const PriceTypeEnum pricetype);
    int              CstPrintInitMembers();
    int              CopyCstPrintList( pxCstPrintList* CstPrintList );
    int              DeconstructSubOrderType();
    int              DeconstructCustDiscCondition();
    short            GetDayNightDestBranchNo();
    bool             IsRoutedFromOriginalBranchNo();
    int              ReloadSessionCustomerBranch();
    int              getCustomersNextTourId( nString& TourId, nDate& DatumAuslieferung);


    char             VerbundKunde() const				{ return VerbundKunde_; }
    long             IDFNr() const						{ return IDFNr_; }
    short            FilialNr() const					{ return FilialNr_; }
    short            AnredeKz() const					{ return AnredeKz_; }
    short            AnzPosLS_RG() const				{ return AnzPosLS_RG_; }
    short            AnzPosSortBehaelt() const			{ return AnzPosSortBehaelt_; }
    char             KuehlBox() const					{ return KuehlBox_; }
    long             TourenKippZeit() const				{ return TourenKippZeit_; }
    long             IMSBezirkNr() const				{ return IMSBezirkNr_; }
    long             PersonalNrVertr() const			{ return PersonalNrVertr_; }
    short            Vertriebszentrum() const			{ return VertriebszentrumNr_; }
    long             KundenNr() const					{ return KundenNr_; }
    short            OriginalFilialNr() const			{ return OriginalFilialNr_; }
    short            NotFilialNr() const				{ return NotFilialNr_; }
    char             NachLieferTyp() const				{ return NachLieferTyp_; }
    long             PartnerNr() const					{ return PartnerNr_; }
    char             PsychoStoffe() const				{ return KzPsychoStoffe_; }
    char             VZKk1() const						{ return VZKk1_; }
    char             XMLPreisLevel() const				{ return XMLPreisLevel_; }
    char             PreWholeTyp() const				{ return PreWholeTyp_; }
    char             XMLInfoLevel() const				{ return XMLInfoLevel_; }
    short            AnzAufClose() const				{ return AnzAufClose_; }
    char             CalculationType() const			{ return CalculationType_; }
    short            SurchargeBasic() const				{ return SurchargeBasic_; }
    short            DeductionBasic() const				{ return DeductionBasic_; }
    double           SurchargePct() const				{ return SurchargePct_; }
    double           DeductionPct() const				{ return DeductionPct_; }
    short            VatRegistered() const				{ return VatRegistered_; }
    short            RebateMethFreeSale() const			{ return RebateMethFreeSale_; }
    short            RebateMethHealthf() const			{ return RebateMethHealthf_; }
    long             MainCstNo() const					{ return MainCstNo_; }
    short            SurchargeBasicKK() const			{ return SurchargeBasicKK_; }
    short            DeductionBasicKK() const			{ return DeductionBasicKK_; }
    double           SurchargePctKK() const				{ return SurchargePctKK_; }
    double           DeductionPctKK() const				{ return DeductionPctKK_; }
    short            LieferMeldung() const				{ return LieferMeldung_; }
    long             ManufacturerNo() const				{ return ManufacturerNo_; }

    const basar::Date& MSV3CfgChangeDate() const		{ return MSV3CfgChangeDate_; }

    const nString&   MatchCode()					{ return MatchCode_; }
    const nString&   NameApo()						{ return NameApo_; }
    const nString&   NameInhaber()					{ return NameInhaber_; }
    const nString&   Strasse()						{ return Strasse_; }
    const nString&   Ort()							{ return Ort_; }
    const nString&   Postleitzahl()					{ return Postleitzahl_; }
    const nString&   Land()							{ return Land_; }
    const nString&   TelNr()						{ return TelNr_; }
    const nString&   TelNrDafue()					{ return TelNrDafue_; }
    const nString&   FaxNr()						{ return FaxNr_; }
    const basar::VarString                          getFaxNrCountry();
    const nString&   TelKurzwahl()					{ return TelKurzwahl_; }
    const nString&   Bemerkungen()					{ return Bemerkungen_; }
    const nString&   KdGruppe()                     { return KdGruppe_; }
    const nString&   KdGruppe()	const				{ return KdGruppe_; }
    const nString&   DafueSystem()					{ return DafueSystem_; }
    const nString&   LagerFachNrRgBei()				{ return LagerFachNrRgBei_; }
    const nString&   KzKdKlasse()					{ return KzKdKlasse_; }
    const nString&   KundeText()					{ return KundeText_; }
    const nString&   StdAufKoBuart()				{ return StdAufKoBuart_; }
    const nString&   PassWord()						{ return PassWord_; }
    const nString&   Sprache()						{ return KzSprache_; }
    const nString&   NationalCustomerNo()			{ return NationalCustomerNo_; }
    const nString&   RatioCustomerNo()				{ return RatioCustomerNo_; }
    const nString&   KrankenKassenNr()				{ return KrankenKassenNr_; }
    const nString&   EmailAdresse()					{ return EmailAdresse_; }

    pxArtClass&       ArtClass()						{ return ETArtKlasse_; }


protected:
    pxCustBase(pxSession *session, tKUNDE& src);
    pxCustBase&       operator=(const tKUNDE& src);
    friend   pxCustBase& Assign(pxCustBase& dest, const tKUNDE& src);
    friend   tKUNDE&  Assign(tKUNDE& dest, const pxCustBase& src);
    virtual  int      CompareTo(const nCollectable *that, void *p,
                                const long lparm) const;
    virtual  int     Read(const void *record);
    void              Init();

    TourManager* m_TourManager;
    TourManager* getTourManager();

    pxCustomerFlags*        flags_;
    pxCustomerGrpFlagsList* CustomerGroupFlagsList_;
    pxCustTerms*            terms_;
    pxCustOrderTypeList*    OrderTypeList_;
    pxCustRouteList*        RouteList_;
    pxCustRouteList*        RouteListOrderType_;
    pxCustRouteList*        OrdTypeRouteList_;
    pxCustRouteWeekList*    RouteWeekList_;
    pxCustRouteWeekList*    RouteWeekListOrderType_;
    pxCustRouteWeekList*    OrdTypeRouteWeekList_;
    pxCustBusinessTimesList*   BusyList_;
    pxCustBusinessTimes* BusyTime_;
    pxTimeTypeList*   CustTimeList_;                      // link to customer ADS timelist
    pxCustPharmGroupList* PharmGroupList_;                // link to customer pharmgroup list
    pxCustDelDelivery* DelayedDelivery_;                  // link to DelayedDelivery entry
    bool               DelayedDeliveryRead_;
    nString           FirstTourId_;                       // customers first tour
    nString           LastTourId_;                        // customers last  tour
    pxCustDiscCondition* CustDiscCondition_;              // customer discount condition (Short, Ge)
    pxSubOrderType*      SubOrderType_;                   // Subordertype entry (table discountlist)
    pxCustBaseInformation*  CustBaseInformation_;         // Tableentry KNDAUSKU
    pxCstSepOrderArtGroupList*  CstSepOrderArtGroupList_; // Customer separate article group list
    pxDebitLimit*      DebitLimitK2_;                     // Customer Debtlimit type k2
    pxDebitLimit*      DebitLimitK1_;                     // Customer Debtlimit type k1
    pxCstPaymentTermsList*    CstPaymentTermsList_;       // Customer Paymenttermslist
    pxRangeList*              DiscountGrpListFive_;       // Customers DiscountGrp entry for a list of article(list 5 )
    pxRangeMemberList*        DiscountGrpMemListFive_;    // Customers DiscountGrpMem list of article(list 5 )
    pxCstPrintList*           CstPrintList_;              // Customers Print info.
    pxEncloserScaleList*      EncloserScaleList_;         // Customers encloserscale  info. List
    pxDonePromoQuotasList*    DonePromoQuotaList_;        // Customers DonePromoQuotas  info. List (BG just for raising Performance)
    pxCustRoutingList*        CustomerRoutingList_;       // Customer Routing List

    long             IDFNr_;           // Kundennummer IDF
    nString           MatchCode_;       // MatchCode
    short            FilialNr_;        // Filialnummer
    nString           NameApo_;         // Name Apotheke
    nString           NameInhaber_;     // Name Inhaber
    nString           Strasse_;         // Strasse
    nString           Ort_;             // Ort
    nString           Postleitzahl_;    // Postleitzahl
    nString           TelNr_;           // Telefonnummer
    nString           TelNrDafue_;      // Telefonnummer Dafue
    nString           FaxNr_;           // Faxnummer
    nString           TelKurzwahl_;     // Telefon Kurzwahl
    nString           Bemerkungen_;     // Bemerkungen
    pxArtClass        ETArtKlasse_;     // Bit Map Artikelbezugsberechtigungen
    short            AnredeKz_;        // Kennzeichen Anrede
    nString           KdGruppe_;        // Kundengruppe
    nString           DafueSystem_;     // Dafue System
    nString           LagerFachNrRgBei_;// Lager Fachnummer Rechn. Beilage
    short            AnzPosLS_RG_;     // Anzahl Positionen LS/RG
    short            AnzPosSortBehaelt_;// Anzahl Positionen Sort Behaelter
    nString           KzKdKlasse_;      // KzKd Klassifizierung
    nString           KundeText_;       // Kunde Text
    char             VerbundKunde_;    // VerbundKunde Info( J/N/G/S )
    nString           StdAufKoBuart_;   // Standard Auftrag-Buart
    nString           PassWord_;        // Password für Kontostandanzeige
    char             KuehlBox_;        // Schalter für Kühlbox Position
    long             TourenKippZeit_;  // Customer rout control time
    long             IMSBezirkNr_;     // IMS Bezirksnummer
    long             PersonalNrVertr_; // Personalnummer Vertreter
    short            VertriebszentrumNr_; // Nr. des Vertriebszentrum
    long             KundenNr_;          // Phoenix-eigene Kunden-Nr.
    short            OriginalFilialNr_; //Nr. der Originalfiliale
    short            NotFilialNr_     ; //Nr. der Ausweichfilialnr
    nString          EmailAdresse_;
    char             NachLieferTyp_;    //Schalter für Wafosystem
    long             PartnerNr_;        //Partner Nummer Kriditlimit
    nString           KzSprache_;        //Sprachkennzeichen
    char             KzPsychoStoffe_;   //Kennzeichen psychotropische Stoffe
    char             VZKk1_;            //Kunde will Rechnung übertragen haben
    bool             NoSeparate_;       //trennen delayeddelivery
    char             XMLPreisLevel_;    //XML Preislevel
    char             PreWholeTyp_;      //Prewholetyp
    char             XMLInfoLevel_;     //XML Infolevel
    nString           NationalCustomerNo_; //National Customerno
    nString           RatioCustomerNo_;  //Ratiopharm Customerno
    short            AnzAufClose_;      // Anzahl Aufträge ab wann close
    nString           KrankenKassenNr_;  // Krankenkassennummer
    char             CalculationType_;  // Calculation Type (Verrechnungstype Math/Kaufm)
    short            SurchargeBasic_;   // Basis Zuschlag 0 = AEP 1 = GEP
    short            DeductionBasic_;   // Basis Abschlag 0 = AEP 1 = GEP
    double          SurchargePct_;     // Basis Zuschlag %
    double          DeductionPct_;     // Basis Abschlag %
    short            VatRegistered_;    // Mehrwertsteuer registriert
    short            RebateMethFreeSale_; // Rebatemethode Freesale
    short            RebateMethHealthf_;  // Rebatemethode Healthfund
    long             MainCstNo_;        // Chain number
    short            SurchargeBasicKK_;   // Basis Zuschlag 0 = AEP 1 = GEP
    short            DeductionBasicKK_;   // Basis Abschlag 0 = AEP 1 = GEP
    double          SurchargePctKK_;     // Basis Zuschlag %
    double          DeductionPctKK_;     // Basis Abschlag %
    short           LieferMeldung_;      // LieferMeldung
    long            ManufacturerNo_;     // manufacturerno
    nString         Land_;              // Land
    basar::Date     MSV3CfgChangeDate_; // MSV3CfgChangeDate

    bool            HasDebitLimitK1_;   // Customer has K1 debtlimit entry(performance)
    bool            DebitLimitK1InitCallDone_;
    bool            HasDebitLimitK2_;   // Customer has K2 debtlimit entry(performance)
    bool            DebitLimitK2InitCallDone_;


private:
    friend class pxCustBaseList;
};

class pxCustBaseList : public nDListCollect, public nDBRecordSet
{
public:
                      pxCustBaseList(pxSession *session);
                      virtual  ~pxCustBaseList() {Clear();}

    void              Clear()        {nDBRecordSet::Clear();}
    size_t            Select ( const char *MatchCode,
                               const int count = 500 );
    pxSession*        Session()       { return (pxSession*) DataBase();}

protected:
    size_t            Select ( tKUNDE *a,  const int count = 500 );
    virtual  int     EndBrowse(const int cursorid);
    virtual  nCollectable* AddToList(const void *record, const int row);
    virtual  int     GetNext(const void* record, const int cursorid);
    virtual  int     StartBrowse(const void *keys, const int cursorid);

private:
    friend class pxCustBaseListIter;
};

class pxCustBaseListIter : public nDListCollectIter
{
public:
    pxCustBaseListIter(pxCustBaseList& list) : nDListCollectIter(list) {}
    virtual  ~pxCustBaseListIter() {}
};

#endif
