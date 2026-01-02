#ifndef PXOEPARM_INC
#define PXOEPARM_INC

#include "pxbase/pxrecord.hpp"
#include <clock.hpp>
#include "pxartcls.hpp"

struct tPARAAUFTRAGBEARB;

class pxOrderEntryParam : public pxDBRecord
{
private:
    pxOrderEntryParam(pxSession *session,const short Vertriebszentrumnr);
    friend class pxSession;
public:
    pxOrderEntryParam(pxOrderEntryParam& src);
    virtual  ~pxOrderEntryParam();

    pxOrderEntryParam& operator=( const pxOrderEntryParam& src );
    pxOrderEntryParam& operator=( const tPARAAUFTRAGBEARB& src );

private:
    friend pxOrderEntryParam& Assign( pxOrderEntryParam& dest, const tPARAAUFTRAGBEARB& src );
    friend tPARAAUFTRAGBEARB& Assign( tPARAAUFTRAGBEARB& dest, const pxOrderEntryParam& src );
public:
    virtual int Get( DBAccessMode mode = cDBGET_READONLY );

    // setter needed in aaorderclose TODO verify!
    void            SetDurchlaufNormal(const long d)                            { DurchlaufNormal_ = d; }
    void            SetDurchlaufEilbote(const long d)                           { DurchlaufEilbote_ = d; }
    void            SetTourenKippZeit(const long d)                             { TourenKippZeit_ = d; }
    void            SetAuftragZusammenHHH(const long d)                         { AuftragZusammenHHH_ = d; }

    bool            IsParamArticle(const long ArticleNo) const;

    const pxArtClass& ETArtNoNatra() const                                      { return ETArtNoNatra_; }

    bool            IsPreInvoicing() const                                      { return (SVorfaktura_ == '1'); }
    bool            IsOpiateDeliveryNote() const                                { return (SBTMSchein_ == '1'); }
    bool            IsAdvertising() const                                       { return (SWerbung_ == '1'); }
    bool            IsCustomerOrderSplit() const                                { return (SKdAuftragSplit_ == '1'); }
    bool            IsAutoRestDelivery() const                                  { return (AutomNachLief_ == '1'); }
    bool            IsOrderConsolidation() const                                { return (SAuftragZusammen_ == '1'); }
    bool            IsCoolerUnder8Degrees() const                               { return (SKuehlU8Grad_ == '1'); }
    bool            IsSplitOrderOnTens() const                                  { return (STrennBei10ner_ == '1'); }
    bool            IsBTMExtra() const                                          { return (BTM_Extra_ == '1'); }
    bool            IsVerbundDirect() const                                     { return (SVerbundDirect_ == '1'); }
    bool            IsDefektDispo()    const                                    { return (DefektDispo_ == '1'); }
    bool            IsVorausBezg() const                                        { return (SVorausBezg_ == '1'); }
    bool            IsBTMKommi() const                                          { return (SBTMKommi_ == '1'); }
    bool            IsSNOToAK() const                                           { return (SNOToAK_ == '1'); }
    bool            IsNewDiscount() const                                       { return (SNewDiscount_ == '1'); }
    bool            IsBatchTeilMenge() const                                    { return (SBatchTeilMenge_ == '1'); }
    bool            IsRoundPackageUnit() const                                  { return (SVERunden_ == '1'); }
    bool            IsNarcTransfer() const                                      { return (SNarcTrans_ == '1'); }
    bool            IsPosSplit() const                                          { return (SPosSplit_ == '1'); }
    bool            IsDayNight() const                                          { return (SDayNight_ == '1'); }
    bool            IsNoCangeVal() const                                        { return (SNoCangeVal_ == '1'); }
    bool            IsKumPos() const                                            { return (SKumPos_ == '1'); }
    bool            IsAnzPrintCode() const                                      { return (SAnzPrintCode_  == '1'); }
    bool            IsOrderCriteria() const                                     { return (SOrderCriteria_  == '1'); }
    bool            IsSIbtCstOrg() const                                        { return (SIbtCstOrg_  == '1'); }
    bool            IsSDefOrderDF() const                                       { return (SDefOrderDF_  == '1'); }
    bool            IsSCrema() const                                            { return (SCrema_  == '1'); }
    bool            IsSDeferOrders() const                                      { return (SDeferOrders_ == 1); }
    bool            IsSDayNightMerge() const                                    { return (SDayNightMerge_  == 1); }
    bool            IsSCloseIBTAtonce() const                                   { return (SCloseIBTAtonce_  == 1); }
    bool            IsAutoIBTSubst() const                                      { return (AutoIBTSubst_  == 1); }
    bool            IsSRangeCalcBaseQtyConfirmed() const                        { return (SRangeCalcBase_  == 0); }
    bool            IsSRangeCalcBaseQtyOrdered() const                          { return (SRangeCalcBase_  == 1); }
    bool            IsSDiscountCalcBaseQtyConfirmed() const                     { return (SDiscountCalcBase_  == 0); }
    bool            IsSDiscountCalcBaseQtyOrdered() const                       { return (SDiscountCalcBase_  == 1); }
    bool            IsUseNewDiscountCalc() const                                { return (UseNewDiscountCalc_ == 1); }

    bool            IsNlevelIBT() const;
    bool            IsUseTourManager() const;
    bool            IsUseTourManagerWithTransportExclusion() const;
    bool            IsNewSuivra() const;
    bool            IsUseLatestIbtTour() const;

    bool            IsSendMSV3DeliveryTime() const                              { return (SendMSV3DeliveryTime_ == 1); }
    bool            IsMSV3OrderPeriodClosureActivated() const                   { return (MSV3OrderPeriodClosure_ == 1); }
    bool            IsUseIBTCustomerForDeliveryTimeActivated() const            { return (UseIBTCustomerForDeliveryTime_ == 1); }
    bool            IsIBTNormalTourActive() const;
    bool            IsSStopCrema() const                                        { return (SStopCrema_  == 1); }

    bool            IsSCloseRestDeliveryAtOnce() const                          { return (SCloseRestDeliveryAtOnce_  == 1); }
    bool            IsSCloseDispoAtOnce() const                                 { return (SCloseDispoAtOnce_  == 1); }
    bool            IsSCool20() const                                           { return (SCool20_  == 1); }
    bool            AreToursWithDepartureOnHolidayDisabled() const              { return (DisableGT24ToursForHoliday_ == 1); }

    char            AutomNachLief() const                                       { return AutomNachLief_; }
    char            BuchArt() const                                             { return BuchArt_; }
    char            BTMEExtra() const                                           { return BTM_Extra_; }
    char            DafueEntsDIorNL() const                                     { return DafueEntsDIorNL_; }
    char            DefektDispo() const                                         { return DefektDispo_; }
    char            KoArt() const                                               { return KoArt_; }
    char            SAuftragZusammen() const                                    { return SAuftragZusammen_; }
    char            SBatchTeilMenge() const                                     { return SBatchTeilMenge_; }
    char            SBearb06() const                                            { return SBearb06_; }
    char            SBTMKommi() const                                           { return SBTMKommi_; }
    char            SBTMSchein() const                                          { return SBTMSchein_; }
    char            SCrema() const                                              { return SCrema_; }
    char            SDayNight() const                                           { return SDayNight_; }
    char            SDefOrderDF() const                                         { return SDefOrderDF_; }
    char            SErweiterteTourAnz() const                                  { return SErweiterteTourAnz_; }
    char            SIbtCstOrg() const                                          { return SIbtCstOrg_; }
    char            SKdAuftragSplit() const                                     { return SKdAuftragSplit_; }
    char            SKLClose() const                                            { return SKLClose_; }
    char            SKuehlU8Grad() const                                        { return SKuehlU8Grad_; }
    char            SNarcTrans() const                                          { return SNarcTrans_; }
    char            SNewDiscount() const                                        { return SNewDiscount_; }
    char            SNOToAK() const                                             { return SNOToAK_; }
    char            SOrderCriteria() const                                      { return SOrderCriteria_; }
    char            SPosSplit() const                                           { return SPosSplit_; }
    char            SRRSa02() const                                             { return SRRSa02_; }
    char            SSammelKommi() const                                        { return SSammelKommi_; }
    char            SSepWannenEilbote() const                                   { return SSepWannenEilbote_; }
    char            SText99Nak() const                                          { return SText99Nak_; }
    char            STrennBei10ner() const                                      { return SRRSa02_; }
    char            SVerbundDirect() const                                      { return SVerbundDirect_; }
    char            SVERunden() const                                           { return SVERunden_; }
    char            SVorausBezg() const                                         { return SVorausBezg_; }
    char            SVorfaktura() const                                         { return SVorfaktura_; }
    char            SWerbung() const                                            { return SWerbung_; }

    double          MaxSurCharge() const                                        { return MaxSurCharge_; }
    double          RangePricePct() const                                       { return RangePricePct_; }

    long            AnzArtAlphaWSort() const                                    { return AnzArtAlphaWSort_; }
    long            AnzPosZu() const                                            { return AnzPosZu_; }
    long            AuftragZusammenHHH() const                                  { return AuftragZusammenHHH_; }
    long            AuftragZusammenMMM() const                                  { return AuftragZusammenMMM_; }
    long            DefwertKeinAbschl() const                                   { return DefwertKeinAbschl_; }
    long            DurchlaufEilbote() const                                    { return DurchlaufEilbote_; }
    long            DurchlaufNormal() const                                     { return DurchlaufNormal_; }
    long            EncloserTiltTime() const                                    { return EncloserTiltTime_; }
    long            KarenzTourSchein() const                                    { return KarenzTourSchein_; }
    long            MaxLineValue() const                                        { return MaxLineValue_; }
    long            MaxPosEil() const                                           { return MaxPosEil_; }
    long            MaxPosMenge() const                                         { return MaxPosMenge_; }
    long            MaxPosVerbund() const                                       { return MaxPosVerbund_; }
    long            MindestBestellWert() const                                  { return MindestBestellWert_; }
    long            PlusZeitBTM() const                                         { return PlusZeitBTM_; }
    long            PZNAddOnCharge() const                                      { return PZNAddOnCharge_; }
    long            PZNBTMSchein() const                                        { return PZNBTMSchein_; }
    long            PZNFranko() const                                           { return PZNFranko_; }
    long            PZNFreightage() const                                       { return PZNFreightage_; }
    long            PZNKuehlBox1() const                                        { return PZNKuehlBox1_; }
    long            PZNKuehlBox2() const                                        { return PZNKuehlBox2_; }
    long            PZNWerbefach() const                                        { return PZNWerbefach_; }
    long            PZNWerbefach2() const                                       { return PZNWerbefach2_; }
    long            PZNZytostatika() const                                      { return PZNZytostatika_; }
    long            SepWannenRestzeit() const                                   { return SepWannenRestzeit_; }
    long            TourenKippZeit() const                                      { return TourenKippZeit_; }
    long            TourVerspaetung() const                                     { return TourVerspaetung_; }

    short           AnzAufClose() const                                         { return AnzAufClose_   ; }
    short           AnzPosClose() const                                         { return AnzPosClose_   ; }
    short           AutoIBTSubst() const                                        { return AutoIBTSubst_; }
    short           CheckTimeToClose() const                                    { return CheckTimeToClose_; }
    short           ContainerLevel() const                                      { return ContainerLevel_; }
    short           ConsolidationDelay() const                                  { return ConsolidationDelay_; }
    short           DelayedDays() const                                         { return DelayedDays_; }
    short           MaxDPODays() const                                          { return MaxDPODays_; }
    short           MaxPosAuftrag() const                                       { return MaxPosAuftrag_ ; }
    short           MaxQtyRequest() const                                       { return MaxQtyRequest_; }
    short           MSV3ClosureTimeAdjustment() const                           { return MSV3ClosureTimeAdjustment_; }
    short           MSV3DeliveryTimeFrame() const                               { return MSV3DeliveryTimeFrame_; }
    short           MSV3OrderPeriodClosure() const                              { return MSV3OrderPeriodClosure_; }
    short           MSV3TourOption() const                                      { return MSV3TourOption_; }
    short           NoRoutingMM() const                                         { return NoRoutingMM_   ; }
    short           OrderPeriodTourAssignment() const                           { return OrderPeriodTourAssignment_; }
    short           ReserveMaxQty() const                                       { return ReserveMaxQty_ ; }
    short           ReservePeriod() const                                       { return ReservePeriod_ ; }
    short           SCloseIBTAtonce() const                                     { return SCloseIBTAtonce_; }
    short           SDayNightMerge() const                                      { return SDayNightMerge_; }
    short           SDeferOrders() const                                        { return SDeferOrders_; }
    short           SDiscountCalcBase() const                                   { return SDiscountCalcBase_; }
    short           SDiscountLocal() const                                      { return SDiscountLocal_; }
    short           SepWannenTyp() const                                        { return SepWannenTyp_; }
    short           SRangeCalcBase() const                                      { return SRangeCalcBase_; }
    short           Store() const                                               { return FilialNr_; }
    short           SWNewCallback() const                                       { return SWNewCallback_; }
    short           TourCheckTime() const                                       { return TourCheckTime_ ; }
    short           TourWeekDay() const                                         { return TourWeekDay_; }
    short           UseIBTCustomerForDeliveryTime() const                       { return UseIBTCustomerForDeliveryTime_; }
    short           UseNewDiscountCalc() const                                  { return UseNewDiscountCalc_; }
    short           UseTourManager() const                                      { return UseTourManager_; }
    short           WakeTime1() const                                           { return WakeTime1_     ; }
    short           WakeTime2() const                                           { return WakeTime2_     ; }
    short           getBranchNo() const                                         { return this->FilialNr_; }
    short           NlevelIBT() const                                           { return NlevelIBT_     ; }
    short           IBTQtyAvailabilityPercentage() const                        { return IBTQtyAvailabilityPercentage_; }
    short           ReverseSubstitutionDays() const                             { return ReverseSubstitutionDays_; }
    short           SStopCrema() const                                          { return SStopCrema_; }
    short           TimeCancelCremaOrder() const                                { return TimeCancelCremaOrder_; }
    short           SNoDispoClosed() const                                      { return SNoDispoClosed_; }
    short           IBTNormalTourActive() const                                 { return IBTNormalTourActive_; }
    short           SCloseRestDeliveryAtOnce() const                            { return SCloseRestDeliveryAtOnce_;}
    short           SCloseDispoAtOnce() const                                   { return SCloseDispoAtOnce_;}
    short           SCool20() const                                             { return SCool20_;}
    short           DisableGT24ToursForHoliday() const                          { return DisableGT24ToursForHoliday_; }
    short           SNewF6() const                                              { return SNewF6_; }
    short           SDispoImport() const                                        { return SDispoImport_; }
    short           DaysHandoverToDelivery() const                              { return DaysHandoverToDelivery_; }
    short           UseLatestIbtTour() const                                    { return UseLatestIbtTour_; }

    virtual    int    Read(const void *record);

protected:
    void            Init();

    short           FilialNr_;
    long            DurchlaufNormal_;
    long            DurchlaufEilbote_;
    long            KarenzTourSchein_;
    char            SSammelKommi_;
    char            SVorfaktura_;
    char            SBTMSchein_;
    char            SWerbung_;
    long            PZNKuehlBox1_;
    long            PZNKuehlBox2_;
    long            PZNBTMSchein_;
    long            PZNWerbefach_;
    long            PZNWerbefach2_;
    long            AnzArtAlphaWSort_;
    long            MaxPosMenge_;
    nString         TourWochentag_;
    long            TourVerspaetung_;
    nString         BahnhofDoppelkontr_;
    char            SErweiterteTourAnz_;
    char            SAuftragZusammen_;
    long            AuftragZusammenMMM_;
    long            AuftragZusammenHHH_;
    char            SSepWannenEilbote_;
    short           SepWannenTyp_;
    long            SepWannenRestzeit_;
    nString         KdAuftragArt_;
    char            BuchArt_;
    char            KoArt_;
    char            SKdAuftragSplit_;
    long            TourenKippZeit_;
    char            AutomNachLief_;
    char            DafueEntsDIorNL_;
    long            DefwertKeinAbschl_;
    long            MaxPosVerbund_;
    char            SKuehlU8Grad_;
    char            SRRSa02_;
    char            STrennBei10ner_;
    char            SText99Nak_;
    char            SBearb06_;
    char            BTM_Extra_;
    nClock          Time_No_BTM_;
    char            SVerbundDirect_;
    long            PZNZytostatika_;
    char            DefektDispo_;
    char            SVorausBezg_;
    char            SBTMKommi_;
    char            SNOToAK_;
    short           MaxPosAuftrag_;
    long            AnzPosZu_;
    long            MaxPosEil_;
    char            SNewDiscount_;
    short            NoRoutingMM_;
    char            SBatchTeilMenge_;
    char            SVERunden_;
    long            PlusZeitBTM_;
    pxArtClass      ETArtNoNatra_;
    long            MindestBestellWert_;
    long            PZNAddOnCharge_;
    short           ReservePeriod_;
    short           ReserveMaxQty_;
    double          RangePricePct_;
    char            SNarcTrans_;
    char            SPosSplit_;
    char            SDayNight_;
    short           TourCheckTime_;
    long            PZNFranko_;
    long            PZNFreightage_;
    short           AnzAufClose_;
    short           AnzPosClose_;
    char            SNoCangeVal_;
    char            SKumPos_;
    char            SAnzPrintCode_;
    char            SKLClose_;
    char            SOrderCriteria_;
    long            MaxLineValue_;
    short           WakeTime1_;
    short           WakeTime2_;
    short           ContainerLevel_;
    char            SIbtCstOrg_;
    double          MaxSurCharge_;
    char            SDefOrderDF_;
    long            EncloserTiltTime_;
    char            SCrema_;
    short           MaxQtyRequest_;
    short           CheckTimeToClose_;
    short           MaxDPODays_;
    short           DelayedDays_;
    short           SDiscountLocal_;
    short           SDeferOrders_;
    short           SDayNightMerge_;
    short           SCloseIBTAtonce_;
    short           ConsolidationDelay_;
    short           AutoIBTSubst_;
    short           SWNewCallback_;
    short           SRangeCalcBase_;
    short           SDiscountCalcBase_;
    short           MSV3DeliveryTimeFrame_;
    short           SendMSV3DeliveryTime_;
    short           MSV3TourOption_;
    short           UseTourManager_;
    short           TourWeekDay_;
    short           OrderPeriodTourAssignment_;
    short           MSV3OrderPeriodClosure_;
    short           MSV3ClosureTimeAdjustment_;
    short           UseIBTCustomerForDeliveryTime_;
    short           UseNewDiscountCalc_;
    short           NlevelIBT_;
    short           IBTQtyAvailabilityPercentage_;
    short           ReverseSubstitutionDays_;
    short           SStopCrema_;
    short           TimeCancelCremaOrder_;
    short           SNoDispoClosed_;
    short           IBTNormalTourActive_;
    short           SCloseRestDeliveryAtOnce_;
    short           SCloseDispoAtOnce_;
    short           SCool20_;
    short           DisableGT24ToursForHoliday_;
    short           SNewF6_;
    short           SDispoImport_;
    short           DaysHandoverToDelivery_;
    short           UseLatestIbtTour_;
};

#endif
