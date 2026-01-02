/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

Implementation of class pxOrderEntryParam methods.

REVISION HISTORY

8 Aug 1995 V1.00 REV 00 written by Dietmar Schloetel.
*/

#include "pxoeparm.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"
#include "pxbranch.hpp"

/*----------------------------------------------------------------------------*/
bool pxOrderEntryParam::IsIBTNormalTourActive() const
{
    if ( 1 == IBTNormalTourActive_ )
        return true;
    return false;
}

/*----------------------------------------------------------------------------*/
bool pxOrderEntryParam::IsNlevelIBT() const
{
    return (NlevelIBT_ == 1);
}

/*----------------------------------------------------------------------------*/
bool pxOrderEntryParam::IsUseTourManager() const
{
    return (UseTourManager_ > 0);
}

/*----------------------------------------------------------------------------*/
bool pxOrderEntryParam::IsUseTourManagerWithTransportExclusion() const
{
    return (UseTourManager_ == 2);
}

/*----------------------------------------------------------------------------*/
bool pxOrderEntryParam::IsNewSuivra() const
{
    return IsSIbtCstOrg();
}

/*----------------------------------------------------------------------------*/
bool pxOrderEntryParam::IsUseLatestIbtTour() const
{
	return (UseLatestIbtTour_ == 1);
}

/*----------------------------------------------------------------------------*/
/*  Destruction.                                                              */
/*----------------------------------------------------------------------------*/
pxOrderEntryParam :: ~pxOrderEntryParam()
{
}

/*----------------------------------------------------------------------------*/
/*  Copy constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxOrderEntryParam :: pxOrderEntryParam
(
    pxOrderEntryParam& src
)
    : pxDBRecord(src.Session())
{
    FilialNr_ = src.FilialNr_;
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Read constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxOrderEntryParam :: pxOrderEntryParam
(
    pxSession *session,
    const short VertriebszentrumNr
)
    : pxDBRecord(session)
{
    FilialNr_ = VertriebszentrumNr;
    Init();
    Get(cDBGET_READONLY);
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tPARAAUFTRAGBEARB structure.   */
/*----------------------------------------------------------------------------*/
tPARAAUFTRAGBEARB&
Assign
(
    tPARAAUFTRAGBEARB&     dest,
    const pxOrderEntryParam& src
)
{
    dest.TourWochentag[0]   = ' ';
    src.TourWochentag_.GetData(dest.TourWochentag);
    dest.BahnhofDoppelkontr[0] = ' ';
    src.BahnhofDoppelkontr_.GetData(dest.BahnhofDoppelkontr);
    dest.KdAuftragArt[0]    = ' ';
    src.KdAuftragArt_.GetData(dest.KdAuftragArt);
    dest.BuchArt            =   src.BuchArt_                ;
    dest.KoArt              =   src.KoArt_                  ;
    dest.FilialNr           =   src.FilialNr_               ;
    dest.DurchlaufNormal    =   src.DurchlaufNormal_        ;
    dest.DurchlaufEilbote   =   src.DurchlaufEilbote_       ;
    dest.KarenzTourSchein   =   src.KarenzTourSchein_       ;
    dest.SSammelKommi       =   src.SSammelKommi_           ;
    dest.SVorfaktura        =   src.SVorfaktura_            ;
    dest.SBTMSchein         =   src.SBTMSchein_             ;
    dest.SWerbung           =   src.SWerbung_               ;
    dest.PZNKuehlBox1       =   src.PZNKuehlBox1_           ;
    dest.PZNKuehlBox2       =   src.PZNKuehlBox2_           ;
    dest.PZNBTMSchein       =   src.PZNBTMSchein_           ;
    dest.PZNWerbefach       =   src.PZNWerbefach_           ;
    dest.PZNWerbefach2      =   src.PZNWerbefach2_          ;
    dest.AnzArtAlphaWSort   =   src.AnzArtAlphaWSort_       ;
    dest.MaxPosMenge        =   src.MaxPosMenge_            ;
    dest.TourVerspaetung    =   src.TourVerspaetung_        ;
    dest.SErweiterteTourAnz =   src.SErweiterteTourAnz_     ;
    dest.SAuftragZusammen   =   src.SAuftragZusammen_       ;
    dest.AuftragZusammenMMM =   src.AuftragZusammenMMM_     ;
    dest.AuftragZusammenHHH =   src.AuftragZusammenHHH_     ;
    dest.SSepWannenEilbote  =   src.SSepWannenEilbote_      ;
    dest.SepWannenTyp       =   src.SepWannenTyp_           ;
    dest.SepWannenRestzeit  =   src.SepWannenRestzeit_      ;
    dest.SKdAuftragSplit    =   src.SKdAuftragSplit_        ;
    dest.TourenKippZeit     =   src.TourenKippZeit_         ;
    dest.AutomNachLief      =   src.AutomNachLief_          ;
    dest.DafueEntsDIorNL    =   src.DafueEntsDIorNL_        ;
    dest.DefwertKeinAbschl  =   src.DefwertKeinAbschl_      ;
    dest.MaxPosVerbund      =   src.MaxPosVerbund_          ;
    dest.SKuehlU8Grad       =   src.SKuehlU8Grad_           ;
    dest.SRRSa02            =   src.SRRSa02_                ;
    dest.STrennBei10ner     =   src.STrennBei10ner_         ;
    dest.SText99Nak         =   src.SText99Nak_             ;
    dest.SBearb06           =   src.SBearb06_               ;
    dest.BTM_Extra          =   src.BTM_Extra_             ;
    dest.Time_No_BTM        =   src.Time_No_BTM_.GetHHMMSS();
    dest.SVerbundDirect     =   src.SVerbundDirect_         ;
    dest.PZNZytostatika     =   src.PZNZytostatika_         ;
    dest.DefektDispo        =   src.DefektDispo_            ;
    dest.SVorausBezg        =   src.SVorausBezg_            ;
    dest.SBTMKommi          =   src.SBTMKommi_              ;
    dest.SNOToAK            =   src.SNOToAK_                ;
    dest.MaxPosAuftrag      =   src.MaxPosAuftrag_          ;
    dest.AnzPosZu           =   src.AnzPosZu_               ;
    dest.MaxPosEil          =   src.MaxPosEil_              ;
    dest.SNewDiscount       =   src.SNewDiscount_           ;
    dest.NoRoutingMM        =   src.NoRoutingMM_            ;
    dest.SBatchTeilMenge    =   src.SBatchTeilMenge_        ;
    dest.SVERunden          =   src.SVERunden_              ;
    dest.PlusZeitBTM        =   src.PlusZeitBTM_            ;
    dest.MindestBestellWert =   src.MindestBestellWert_     ;
    dest.PZNAddOnCharge     =   src.PZNAddOnCharge_         ;
    dest.ReservePeriod      =   src.ReservePeriod_          ;
    dest.ReserveMaxQty      =   src.ReserveMaxQty_          ;
    dest.RangePricePct      =   src.RangePricePct_          ;
    dest.SNarcTrans         =   src.SNarcTrans_             ;
    dest.SPosSplit          =   src.SPosSplit_              ;
    dest.SDayNight          =   src.SDayNight_              ;
    dest.TourCheckTime      =   src.TourCheckTime_          ;
    dest.PZNFranko          =   src.PZNFranko_              ;
    dest.PZNFreightage      =   src.PZNFreightage_          ;
    dest.AnzAufClose        =   src.AnzAufClose_            ;
    dest.AnzPosClose        =   src.AnzPosClose_            ;
    dest.SNoCangeVal        =   src.SNoCangeVal_            ;
    dest.SKumPos            =   src.SKumPos_                ;
    dest.SAnzPrintCode      =   src.SAnzPrintCode_          ;
    dest.SKLClose           =   src.SKLClose_               ;
    dest.SOrderCriteria     =   src.SOrderCriteria_         ;
    dest.MaxLineValue       =   src.MaxLineValue_           ;
    dest.WakeTime1          =   src.WakeTime1_              ;
    dest.WakeTime2          =   src.WakeTime2_              ;
    dest.ContainerLevel     =   src.ContainerLevel_         ;
    dest.SIbtCstOrg         =   src.SIbtCstOrg_             ;
    dest.MaxSurCharge       =   src.MaxSurCharge_           ;
    dest.SDefOrderDF        =   src.SDefOrderDF_            ;
    dest.EncloserTiltTime   =   src.EncloserTiltTime_       ;
    dest.SCrema             =   src.SCrema_                 ;
    dest.MaxQtyRequest      =   src.MaxQtyRequest_          ;
    dest.CheckTimeToClose   =   src.CheckTimeToClose_       ;
    dest.MaxDPODays         =   src.MaxDPODays_             ;
    dest.DelayedDays        =   src.DelayedDays_            ;
    dest.SDiscountLocal     =   src.SDiscountLocal_         ;
    dest.SDeferOrders       =   src.SDeferOrders_           ;
    dest.SDayNightMerge     =   src.SDayNightMerge_         ;
    dest.SCloseIBTAtonce    =   src.SCloseIBTAtonce_        ;
    dest.ConsolidationDelay =   src.ConsolidationDelay_     ;
    dest.AutoIBTSubst       =   src.AutoIBTSubst_           ;
    dest.SWNewCallback      =   src.SWNewCallback_          ;
    dest.SRangeCalcBase     =   src.SRangeCalcBase_         ;
    dest.SDiscountCalcBase  =   src.SDiscountCalcBase_       ;
    dest.MSV3DeliveryTimeFrame          = src.MSV3DeliveryTimeFrame_;
    dest.SendMSV3DeliveryTime           = src.SendMSV3DeliveryTime_;
    dest.MSV3TourOption                 = src.MSV3TourOption_;
    dest.UseTourManager                 = src.UseTourManager_;
    dest.TourWeekDay                    = src.TourWeekDay_;
    dest.OrderPeriodTourAssignment      = src.OrderPeriodTourAssignment_;
    dest.MSV3OrderPeriodClosure         = src.MSV3OrderPeriodClosure_;
    dest.MSV3ClosureTimeAdjustment      = src.MSV3ClosureTimeAdjustment_;
    dest.UseIBTCustomerForDeliveryTime  = src.UseIBTCustomerForDeliveryTime_;
    dest.UseNewDiscountCalc             = src.UseNewDiscountCalc_;
    dest.NlevelIBT                      = src.NlevelIBT_;
    dest.IBTQtyAvailabilityPercentage   = src.IBTQtyAvailabilityPercentage_;
    dest.ReverseSubstitutionDays        = src.ReverseSubstitutionDays_;
    dest.SStopCrema                     = src.SStopCrema_;
    dest.TimeCancelCremaOrder           = src.TimeCancelCremaOrder_;
    dest.SNoDispoClosed                 = src.SNoDispoClosed_;
    dest.IBTNormalTourActive            = src.IBTNormalTourActive_;
    dest.SCloseRestDeliveryAtOnce       = src.SCloseRestDeliveryAtOnce_;
    dest.SCloseDispoAtOnce              = src.SCloseDispoAtOnce_;
    dest.SCool20                        = src.SCool20_;
    dest.DisableGT24ToursForHoliday     = src.DisableGT24ToursForHoliday_;
    dest.SNewF6                         = src.SNewF6_;
    dest.SDispoImport                   = src.SDispoImport_;
    dest.DaysHandoverToDelivery         = src.DaysHandoverToDelivery_;
    dest.UseLatestIbtTour               = src.UseLatestIbtTour_;

    long dummy;
    src.ETArtNoNatra_.Export(dest.ETArtNoNatra, dummy);

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tPARAAUFTRAGBEARB structure to a pxOrderEntryParam */
/*  object.                                                                   */
/*----------------------------------------------------------------------------*/
pxOrderEntryParam&
Assign
(
    pxOrderEntryParam&    dest,
    const tPARAAUFTRAGBEARB&  src
)
{
    dest.TourWochentag_      =   src.TourWochentag;
    dest.BahnhofDoppelkontr_ =   src.BahnhofDoppelkontr;
    dest.FilialNr_           =   src.FilialNr               ;
    dest.KdAuftragArt_       =   src.KdAuftragArt           ;
    dest.BuchArt_            =   src.BuchArt                ;
    dest.KoArt_              =   src.KoArt                  ;
    dest.DurchlaufNormal_    =   src.DurchlaufNormal        ;
    dest.DurchlaufEilbote_   =   src.DurchlaufEilbote       ;
    dest.KarenzTourSchein_   =   src.KarenzTourSchein       ;
    dest.SSammelKommi_       =   src.SSammelKommi           ;
    dest.SVorfaktura_        =   src.SVorfaktura            ;
    dest.SBTMSchein_         =   src.SBTMSchein             ;
    dest.SWerbung_           =   src.SWerbung               ;
    dest.PZNKuehlBox1_       =   src.PZNKuehlBox1           ;
    dest.PZNKuehlBox2_       =   src.PZNKuehlBox2           ;
    dest.PZNBTMSchein_       =   src.PZNBTMSchein           ;
    dest.PZNWerbefach_       =   src.PZNWerbefach           ;
    dest.PZNWerbefach2_      =   src.PZNWerbefach2          ;
    dest.AnzArtAlphaWSort_   =   src.AnzArtAlphaWSort       ;
    dest.MaxPosMenge_        =   src.MaxPosMenge            ;
    dest.TourVerspaetung_    =   src.TourVerspaetung        ;
    dest.SErweiterteTourAnz_ =   src.SErweiterteTourAnz     ;
    dest.SAuftragZusammen_   =   src.SAuftragZusammen       ;
    dest.AuftragZusammenMMM_ =   src.AuftragZusammenMMM     ;
    dest.AuftragZusammenHHH_ =   src.AuftragZusammenHHH     ;
    dest.SSepWannenEilbote_  =   src.SSepWannenEilbote      ;
    dest.SepWannenTyp_       =   src.SepWannenTyp           ;
    dest.SepWannenRestzeit_  =   src.SepWannenRestzeit      ;
    dest.SKdAuftragSplit_    =   src.SKdAuftragSplit        ;
    dest.TourenKippZeit_     =   src.TourenKippZeit         ;
    dest.AutomNachLief_      =   src.AutomNachLief          ;
    dest.DafueEntsDIorNL_    =   src.DafueEntsDIorNL        ;
    dest.DefwertKeinAbschl_  =   src.DefwertKeinAbschl      ;
    dest.MaxPosVerbund_      =   src.MaxPosVerbund          ;
    dest.SKuehlU8Grad_       =   src.SKuehlU8Grad           ;
    dest.SRRSa02_            =   src.SRRSa02                ;
    dest.STrennBei10ner_     =   src.STrennBei10ner         ;
    dest.SText99Nak_         =   src.SText99Nak             ;
    dest.SBearb06_           =   src.SBearb06               ;
    dest.BTM_Extra_          =   src.BTM_Extra              ;
    dest.Time_No_BTM_        =   src.Time_No_BTM            ;
    dest.SVerbundDirect_     =   src.SVerbundDirect         ;
    dest.PZNZytostatika_     =   src.PZNZytostatika         ;
    dest.DefektDispo_        =   src.DefektDispo            ;
    dest.SVorausBezg_        =   src.SVorausBezg            ;
    dest.SBTMKommi_          =   src.SBTMKommi              ;
    dest.SNOToAK_            =   src.SNOToAK                ;
    dest.MaxPosAuftrag_      =   src.MaxPosAuftrag          ;
    dest.AnzPosZu_           =   src.AnzPosZu               ;
    dest.MaxPosEil_          =   src.MaxPosEil              ;
    dest.SNewDiscount_       =   src.SNewDiscount           ;
    dest.NoRoutingMM_        =   src.NoRoutingMM            ;
    dest.SBatchTeilMenge_    =   src.SBatchTeilMenge        ;
    dest.SVERunden_          =   src.SVERunden              ;
    dest.PlusZeitBTM_        =   src.PlusZeitBTM            ;
    dest.MindestBestellWert_ =   src.MindestBestellWert     ;
    dest.PZNAddOnCharge_     =   src.PZNAddOnCharge         ;
    dest.ReservePeriod_      =   src.ReservePeriod          ;
    dest.ReserveMaxQty_      =   src.ReserveMaxQty          ;
    dest.RangePricePct_      =   src.RangePricePct          ;
    dest.SNarcTrans_         =   src.SNarcTrans             ;
    dest.SPosSplit_          =   src.SPosSplit              ;
    dest.SDayNight_          =   src.SDayNight              ;
    dest.TourCheckTime_      =   src.TourCheckTime          ;
    dest.PZNFranko_          =   src.PZNFranko              ;
    dest.PZNFreightage_      =   src.PZNFreightage          ;
    dest.AnzAufClose_        =   src.AnzAufClose            ;
    dest.AnzPosClose_        =   src.AnzPosClose            ;
    dest.SNoCangeVal_        =   src.SNoCangeVal            ;
    dest.SKumPos_            =   src.SKumPos                ;
    dest.SAnzPrintCode_      =   src.SAnzPrintCode          ;
    dest.SKLClose_           =   src.SKLClose               ;
    dest.SOrderCriteria_     =   src.SOrderCriteria         ;
    dest.MaxLineValue_       =   src.MaxLineValue           ;
    dest.WakeTime1_          =   src.WakeTime1              ;
    dest.WakeTime2_          =   src.WakeTime2              ;
    dest.ContainerLevel_     =   src.ContainerLevel         ;
    dest.SIbtCstOrg_         =   src.SIbtCstOrg             ;
    dest.MaxSurCharge_       =   src.MaxSurCharge           ;
    dest.SDefOrderDF_        =   src.SDefOrderDF            ;
    dest.EncloserTiltTime_   =   src.EncloserTiltTime       ;
    dest.SCrema_             =   src.SCrema                 ;
    dest.MaxQtyRequest_      =   src.MaxQtyRequest          ;
    dest.CheckTimeToClose_   =   src.CheckTimeToClose       ;
    dest.MaxDPODays_         =   src.MaxDPODays             ;
    dest.DelayedDays_        =   src.DelayedDays            ;
    dest.SDiscountLocal_     =   src.SDiscountLocal         ;
    dest.SDeferOrders_       =   src.SDeferOrders           ;
    dest.SDayNightMerge_     =   src.SDayNightMerge         ;
    dest.SCloseIBTAtonce_    =   src.SCloseIBTAtonce        ;
    dest.ConsolidationDelay_ =   src.ConsolidationDelay    ;
    dest.AutoIBTSubst_       =   src.AutoIBTSubst           ;
    dest.SWNewCallback_      =   src.SWNewCallback          ;
    dest.SRangeCalcBase_     =   src.SRangeCalcBase         ;
    dest.SDiscountCalcBase_  =   src.SDiscountCalcBase      ;
    dest.MSV3DeliveryTimeFrame_         = src.MSV3DeliveryTimeFrame;
    dest.SendMSV3DeliveryTime_          = src.SendMSV3DeliveryTime;
    dest.MSV3TourOption_                = src.MSV3TourOption;
    dest.UseTourManager_                = src.UseTourManager;
    dest.TourWeekDay_                   = src.TourWeekDay;
    dest.OrderPeriodTourAssignment_     = src.OrderPeriodTourAssignment;

    dest.MSV3OrderPeriodClosure_        = src.MSV3OrderPeriodClosure;
    dest.MSV3ClosureTimeAdjustment_     = src.MSV3ClosureTimeAdjustment;
    dest.UseIBTCustomerForDeliveryTime_ = src.UseIBTCustomerForDeliveryTime;
    dest.UseNewDiscountCalc_            = src.UseNewDiscountCalc;
    dest.NlevelIBT_                     = src.NlevelIBT;
    dest.IBTQtyAvailabilityPercentage_  = src.IBTQtyAvailabilityPercentage;
    dest.ReverseSubstitutionDays_       = src.ReverseSubstitutionDays;
    dest.SStopCrema_                    = src.SStopCrema;
    dest.TimeCancelCremaOrder_          = src.TimeCancelCremaOrder;
    dest.SNoDispoClosed_                = src.SNoDispoClosed;
    dest.IBTNormalTourActive_           = src.IBTNormalTourActive;
    dest.SCloseRestDeliveryAtOnce_      = src.SCloseRestDeliveryAtOnce;
    dest.SCloseDispoAtOnce_             = src.SCloseDispoAtOnce;
    dest.SCool20_                       = src.SCool20;
    dest.DisableGT24ToursForHoliday_    = src.DisableGT24ToursForHoliday;
    dest.SNewF6_                        = src.SNewF6;
    dest.SDispoImport_                  = src.SDispoImport;
    dest.DaysHandoverToDelivery_        = src.DaysHandoverToDelivery;
    dest.UseLatestIbtTour_              = src.UseLatestIbtTour;

    long dummy = 0;
    dest.ETArtNoNatra_.Import(src.ETArtNoNatra, dummy);
    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Check ArticleNumber If ArticleNo is within Param, return 1 else 0         */
/*----------------------------------------------------------------------------*/
bool
pxOrderEntryParam :: IsParamArticle
(
    const long ArticleNo
) const
{
    return ( ArticleNo == PZNKuehlBox1_   ||
             ArticleNo == PZNKuehlBox2_   ||
             ArticleNo == PZNBTMSchein_   ||
             ArticleNo == PZNWerbefach_   ||
             ArticleNo == PZNWerbefach2_  ||
             ArticleNo == PZNZytostatika_ ||
             ArticleNo == PZNAddOnCharge_ ||
             ArticleNo == PZNFranko_      ||
             ArticleNo == PZNFreightage_ );
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxOrderEntryParam :: Init()
{
    tPARAAUFTRAGBEARB    record;
    memset(&record, 0 , sizeof(tPARAAUFTRAGBEARB));
    if ( FilialNr_ <= 0 )
    {
       record.FilialNr = Session()->Branch()->Store();
       FilialNr_ = record.FilialNr;
    }
    else
       record.FilialNr = FilialNr_;

    Assign(*this, record);
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the tPARAAUFTRAGBEARB       */
/*  struct and then imported to self.                                         */
/*----------------------------------------------------------------------------*/
pxOrderEntryParam&
pxOrderEntryParam :: operator=( const pxOrderEntryParam& src)
{
    tPARAAUFTRAGBEARB    record;                 // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tPARAAUFTRAGBEARB structure to this instance.        */
/*----------------------------------------------------------------------------*/
pxOrderEntryParam&
pxOrderEntryParam :: operator=( const tPARAAUFTRAGBEARB& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxOrderEntryParam :: Get
(
    DBAccessMode mode
)

{
    tPARAAUFTRAGBEARB record;
    memset(&record, 0, sizeof(tPARAAUFTRAGBEARB));
    record.FilialNr = FilialNr_;
    int retval = ( mode == cDBGET_FORUPDATE ) ? nDBReadLock(&record) : nDBRead(&record);
    if (!retval)
       (*this)= record;                 // import the data from tPARAAUFTRAGBEARB struct
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecord.                      */
/*----------------------------------------------------------------------------*/
int pxOrderEntryParam::Read( const void *record )
{
    return pxParaAuftragBearbRead((tPARAAUFTRAGBEARB *)record, Session()->getDatabaseName( ((tPARAAUFTRAGBEARB *)record)->FilialNr ).c_str());
}
