/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

PXITEM.HPP
Customer Order Item Classes.

REVISION HISTORY
*/

#ifndef PXITEM_DOTH
#define PXITEM_DOTH

#include "pxbase/pxrecord.hpp"
#include "types/pricetypeenum.inc"
#include "types/messagecodeenum.inc"
#include "types/splitttypeenum.inc"
#include "pxdelpos.hpp"
#include "pxartdsp.hpp"
#include "pxdevice.hpp"
#include "pxitmdef.h"
#include "pxdiscountdef.h"

#include <libbasarcmnutil_decimal.h>
#include <discount/orderpositiondiscount/orderpositiondiscountcollectionptr.h>
#include <ibt/ibtrequest/iibtrequestptr.h>

#include <discount/tender/repository/itenderdiscountfinder.h>
#include <discount/tender/tenderdiscount.h>
#include <discount/tender/tenderdiscountptr.h>

#include <cscorder/componentmanager/cscordercomponentmanager.h>
#include <cscorder/cscorderibtpickingdata/icscorderibtpickingdatarepositoryptr.h>
#include <cscorder/cscorderibtpickingdata/icscorderibtpickingdatarepository.h>
#include <cscorder/cscorderibtpickingdata/cscorderibtpickingdata.h>

#include "pxarticlequota.hpp"

//------------------------------------------------------------------------------
//  forward declarations
//------------------------------------------------------------------------------

class pxArtBase;
class pxArticleCodes;
class pxArticleInfo;
class pxArticleQuota;
class pxArtPrice;
class pxArtPriceList;
class pxArtDispo;
class pxArtStoreLoc;
class pxCalcDiscount;
class pxCalcDiscountList;
class pxCommType;
class pxCustBase;
class pxCustOrderType;
class pxCustomerSurchargeList;
class pxCustPharmGroupList;

namespace pxVerbund
{
    namespace subsequentDelivery
    {
        class pxDeliveryPos;
        class pxDeliveryPosList;
    }
}

class pxDiscount;
class pxDiscountList;
class pxDisInKindList;
class pxItemDiscount;
class pxItemDiscountList;
class pxGenericOrderRemarkList;
class pxItemAttributes;
class pxKdAuftragPosRefundList;
class pxOrder;
class pxOrderItemList;
class pxOrderPosCalcMode;
class pxOrderPosPromo;
class pxOrderPosPromoList;
class pxPromoCollect;
class pxPromoCollectList;
class pxRangeControl;
class pxRangeControlList;
class pxStockTrans;
class pxTenderPos;
class pxValidDiscInfoList;
class pxVartikelLokal;
class pxVartikelLokalList;
class ArticleSubstitutionUtil;
class TourInfo;
class IBTBranchesList;
struct tKDAUFTRAGPOS;

//------------------------------------------------------------------------------
//  Const
//------------------------------------------------------------------------------
const double MAX_RABPCT_EXCLUSIVE = 10.0;

/*----------------------------------------------------------------------------*/
/*  Internal constants and flags.                                             */
/*----------------------------------------------------------------------------*/
//  Item posting control flags:
#define bPOST_DEFAULT             0  // default behaviour during quantity posting
#define bPOST_IGN_LACK            1  // do not flag quantity lacks as an error
#define bPOST_AUTO_ITEM           2  // Server auto-item posting active
#define bPOST_NO_DEBIT            4  // do not debit the stock
#define bPOST_AUXDELIVERY         8  // auxdelivery posting from first auxcompany
#define bPOST_RANGEARTICLE       16  // Rangearticle booking
#define bPOST_IBTPOSREBOOK       32  // IBT Position Rebook(INC-043864)
#define bPOST_IGNORE_PRICELIMIT  64  // BG: Ignore Price Limit


/*----------------------------------------------------------------------------*/
/*  Customer order item base class.                                           */
/*----------------------------------------------------------------------------*/
class pxOrderItem : public pxDBRecord
{
public:
/*----------------------------------------------------------------------------*/
/*  Enumerations and manifest constants.                                      */
/*----------------------------------------------------------------------------*/
    enum ItemSendStatusEnum
    {
       // State definitions:
       cVSEok=0,                        // 0 Caution: do NEVER change this value!!
       cVSEArtErr,                      // 1 Article not found
       cVSEBstErr,                      // 2 amount not sufficient
       cVSEAnyErr,                      // 3 unknown error
       cVSECoCorrection = 7             // 7 kommikerrekturen
    };

    enum ItemType                       // order item type definition
    {
        TypeProductStocked,             // known product, found in ArtBase table
        TypeProductNotStocked,          // known product, but not in ArtBase table
        TypeProductUnknown,             // unknown product id
        TypeTextOnly,                   // Text item
        TypeDispoItem,                  // Dispo item
        TypeDispoItemValued             // Valued dispo item
    };


    enum ArticleState                   // article state definition
    {
        ArtStateGood,                   // no error or condition
        ArtStateIdMissing,              // Product id missing
        ArtStateInvalidDigit,           // invalid digits detected
        ArtStateInvalidCheckDigit,      // check digit invalid
        ArtStateNotFound,               // not found in data base
        ArtStateDescMissing,            // description missing for dispo item
        ArtStateNotAuthorized,          // Bitwert 512 not auth. to order this product
        ArtStateNotCertificated,        // no certificate for this product
        ArtStatePurchaseStop,           // Purchase stop for this product
        ArtStateNotOverDct,             // Article not via DCT/XML
        ArtStateNotInTender,            // Article not part of Tender
        ArtStateTransportExclusion,
        ArtStateNoBatchProvided,                            // BatchTracking
        ArtStateBatchGivenButNotProvided,                   // BatchTracking
        ArtStateDesiredBatchGivenOnlyFixedAllowed,          // BatchTracking
        ArtStateFixedBatchGivenButNotAllowed,               // BatchTracking
        ArtStateBatchProcessingNotPossible,                 // BatchTracking
        ArtStatePriceLimitCompViolationNHIFPriceMWPRefPrice, //CMSG_ITM_PRICE_LIMIT_COMPLIANCE_VIOLATION_NHIFPRICE_MWP_REFPRICE
        ArtStatePriceLimitCompViolationMWPAndRefPrice,       //CMSG_ITM_PRICE_LIMIT_COMPLIANCE_VIOLATION_MWP_AND_REFPRICE
        ArtStatePriceLimitDeletion,                         //CMSG_ITM_PRICE_LIMIT_PRODUCT_PRICE_DELETION
        ArtStatePriceLimitMWPExceedance                     //CMSG_ITM_PRICE_LIMIT_MWP_EXCEEDANCE
    };

    enum QuantityState
    {
        QStateGood,
        QStateInvalidDigit      =  1,   // invalid digits detected
        QStateInvalidCheckDigit =  2,   // check digit invalid
        QStateNotValid          =  4,   // not valid (missing, out of range)
        QStateNotOnHand         =  8,   // quantity not in stock
        QStateAlternate         = 16,   // alternate product chosen (automatically)
        QStateLimitCheck        = 32,   // off limit (too low, too high)
        QStateAlternateReimport = 64,   // alternate product possible(Reimport)
        QStateDelayedDelivery   = 128,  // this item will be delayed delivered
        QStateTenderQtyExceeded = 256   // Bestellmenge fuer Tenderpos ueberschritten
    };

    enum BookingType                    // Product booking type
    {
        BookingTypeDefault,
        PurchaseOrder       = bDisponieren,
        DeliveryConfirmed   = bZugesagt,
        RestDelivery        = bNachliefern,
        DemandBooking       = bNachFrageBuchung,
        AuxDelivery,
        SeparateDefect,
        DelayedDelivery,
        UpdateDelPos,
        ReservedRestDelivery,
        SeparateContainer,
        SeparateArticle,
        ReferenceItem,
        AuxDeliveryComplete,
        RestDeliveryItem,
        PurchaseItem,
        DispoItem,
        BookingTypeReserveCustomerStock,
        BookingTypeLimit
    };

    enum CascadeLevelBG                    // Cascade levels
    {
        CascadeLevelProductPromotion            =0,
        CascadeLevelArticle                     =1,
        CascadeLevelManufacturer                =2,
        CascadeLevelRPG                         =3,
        CascadeLevelArticleGroup                =4,
        CascadeLevelCustomer                    =5,
        CascadeLevelPurchaseGroup               =6,
        CascadeLevelRangePromotion              =99  //target promotion
    };

    enum CancelOption                 // Cancel Option
    {
        CancelOptionDefault,
        ClearMengeBestellt
    };

    enum ProblemState
    {
        PGood,
        PDiscountNoQty          =  1,   // Not enoungh quantity in stock for rebate article
        PDiscountArticleNotAV   =  2    // Discount Article not available
    };

        //BB

public:
    virtual           ~pxOrderItem();


                      pxOrderItem(pxOrder& Order, long PosNr);
                      pxOrderItem(pxOrderItem& src);
                      pxOrderItem(pxSession* session, long KdAuftragNr,
                                 long PosNr,DBAccessMode mode = cDBGET_READONLY);

    pxOrderItem&      operator=(const pxOrderItem& src);
//  Assigns the values of 'src' to self and returns a reference to it.

             int     Open();
             int     Close();
    virtual  int     Get(DBAccessMode mode = cDBGET_READONLY);
    virtual  int     Put();

//  Item entry core function for stocked products:
             int     InitOrderItem_Core(const long  ArtikelNr,
                                        const long  Menge,
                                        const long  MengeNatra,
                                        const long  MengeNachfrage,
                                        BookingType btype,
                                        ItemType    PosTyp,
                                        int         flags,
                                        const basar::VarString& Batch = "",
                                        const bool  IsFixBatch  = false,
                                        bool* bStockNotOk = 0);

//  Item entry core function for stocked products (AuxDelivery) :
             int     InitOrderItem_08(const long  ArtikelNr,
                                   const long  Menge,
                                   const long  MengeNatra,
                                   const long  MengeNachfrage,
                                   const short VerbundFiliale,
                                   BookingType  btype,
                                   ItemType     PosTyp,
                                   int          flags
                                   );

public:
//  Item entry core function for stocked products just for StockInformation:
             int  NewOrderItemInfo(const long  ArtikelNr,
                                    const long  Menge
                                   );

//  Item entry for a product that is not stocked:
             int      InitOrderItem_15(tDISPOITEM& di,
                                   BookingType btype = BookingTypeDefault,
                                   bool addSubSequent = true
                                   );

             int     NewOrderTextItem(const nString& text,
                                   const long Menge
                                   );

             int     NewOrderItemRemarks(const long ArtikelNr,
                                   const long Menge
                                   );

             int     NewOrderItemQuery(const long ArtikelNr,
                                   const long Menge
                                   );

             int      InitOrderItem_16(const long ArtikelNr,
                                   const long Menge,
                                   const nString& Hinweis,
                                   BookingType btype = BookingTypeDefault
                                   );

             int      CopyOrderItem(pxOrderItem* item,
                                   BookingType btype,
                                   SplittTypeEnum s);

             int      InitOrderItem_12(const long ArtikelNr,
                                   const long Menge,
                                   pxItemAttributes* Attributes,
                                   const long MengeNatra = 0,
                                   const basar::VarString& Batch = "",
                                   const bool IsFixBatch = false
                                   );
//  Item update methods:
             int     DispoSet    (tDISPOITEM& di, BookingType btype);
             int     OrderQuantity(
                                   long Menge,
                                   long MengeNatra = 0,
                                   long MengeNachfrage = -1,
                                   BookingType btype = BookingTypeDefault,
                                   int flags = bPOST_DEFAULT,
                                   short company = cDEFAULT,
                                   double DiscountValuePct = 0,
                                   long  MengeBestelltNatra = 0,
                                   const nString &batch = "",
                                   bool isFixBatch = false
                                   );

             int     OrderQuantityRange(
                                   long Menge,
                                   long MengeNatra,
                                   long MengeNachfrage,
                                   BookingType btype,
                                   int flags
                                   );

                     // btype = BookingTypeDefault,
                     // flags = bPOST_RANGEARTICLE
             int     OrderQuantityRange_RangeArticle(long Menge, long MengeNatra, long MengeNachfrage);

                     // Menge = 0L
                     // MengeNachfrage = 0L
                     // btype = BookingTypeDefault,
                     // flags = bPOST_RANGEARTICLE
             int     OrderQuantityRange_NatraWithRangeArticle(long MengeNatra);

             int     CalcOrderItem(const long  ArtikelNr,
                                   const long  Menge,
                                   const long  MengeNatra,
                                   const long  MengeNachfrage,
                                   BookingType  btype,
                                   ItemType     PosTyp,
                                   int          flags);

             int     ItemDiscountInfo(const long  ArtikelNr);

             long    getOriginalIBTQtyFromSplittedOrder();
             short   getOriginalIBTBranchFromSplittedOrder();

             libcsc::cscorder::domMod::CSCOrderIBTPickingdataCollectionPtr getIBTPickingDataCollection();

             int     CancelItem(const pxOrderItem::CancelOption option);
             int     CancelAndDeleteItem();
             int     CancelAuxPosting();
             int     AuxDeliveryCheck( short AuxFil, int flags, BookingType btype = BookingTypeDefault );
             int     CheckPossibilityForIBTDelivery( short AuxFil, int flags, BookingType btype = BookingTypeDefault );
             int     CheckPossibilityForIBTDeliveryCommonNonVideo( int flags, BookingType btype = BookingTypeDefault );
             int     checkPossibilityForNlevelIBTDelivery( IBTBranchesList& ibtbrancheslist, short ibtbranchno, int flags, BookingType btype = BookingTypeDefault );
             int     checkPossibilityForNlevelNonVideo( bool ibtcustomersonly, bool ibtperiodneeded, int flags, BookingType btype = BookingTypeDefault);
             int     checkPossibilityForNlevelVideo(IBTBranchesList* ibtbrancheslist, short ibtbranchno, bool ibtcustomersonly, bool ibtperiodneeded);
             int     checkPossibilityForNlevelCustomersOnly( int flags, BookingType btype = BookingTypeDefault );
             int     checkPossibilityForNlevelPeriodNeeded();
             int     CheckRestDelivery();
             int     RestDelRedunancyCheck();
             int     RestDeliveryValdate();
             bool    CheckSkipDiscountCalculations();
             long    CalcDiscount(long Menge, long QInStock = 0);
             long    CalcDiscountCH( long Menge, long QInStock = 0 );
             long    CalcDiscountBG(long Menge, long QInStock = 0);
             int     SaveArtDiscountInfoList( pxDiscountList* dlist, pxCalcDiscountList* calclist, long QOrdered);

             void    OrderRef(pxOrder& order) { Order_ = &order; }
//             long    ChangeToDiscountPrice(long orderq); // TODO DEPricing: remove code block after GoLive
             int     ArtBaseValidity( const long Menge,int flags);
             int     GetError( char* message );
             int     GetLackReason( char* message );
             basar::VarString GetLackReasonList();
//  Some Methodes to handle Article Quota
             long    CheckArtQuota( const long q);
             int     UndoArtQuota(const long Menge = 0);
             int     UpdateArtQuota();
             int     CancelArtQuota();
//  Some Methodes to handle item discount(Table kdauftragposrab
             int     UndoItemDiscount();
             int     UndoItemDiscountCHforRPG();
             int     UndoOrderPosPromo();
             int     UndoOrderPosRefund();
             int     UndoProductPromotion(pxOrderItemList* proformalist = NULL);
             int     UndoRedoItemDiscount(pxOrderItem* item);
             int     CopyItemDiscountList(pxOrderItem* item);
             int     CopyOrderPosCalcMode(pxOrderItem* item);
             int     UndoRedoOrderPosPromo(pxOrderItem* item);
             int     UndoRedoOrderPosRefund(pxOrderItem* item);
             int     RollBackOrderPosition();
//  Some Methodes to handle item discount(Table discountgrpmem
             int     CollectRangeMember();
//  Some Methodes to handle item discount(Table discountgrpmem
             int     CollectTargetPromoMembers();
//  Some Methodes to handle item promotionscale(Table promotionscale
             int     CollectPromotionScaleMembers();
//  Some Methodes to handle NarcTransfer(Table narctransactiontransfer
             int     DeleteNarcTransfer();
             int     InsertNarcTransfer();
//  Some Methodes to handle ArticlePackUnits and Positionparking
             long    CheckPackageUnit(const long QToPost, const long QInStock);
             int     UndoPosParking();
//  Some Methodes to handle TenderPos/TenderProgress serbian/bulgarien aplications
             int     UndoTenderProgress();
             int     UndoTenderProgressCH();
             int     GetTenderNoFromRemark();
             long    GetBookedTenderQty( const int tenderNo );
             nMoney  GetTenderContractPrice();
             bool    CalcTenderDiscount();
             double  GetTenderAddDiscountPct();
             nMoney  TenderChargedPrice();
             int     CloseTenderPos();
             long    getFreeTenderQty();
             int     UndoRedoTenderProgressCH(pxOrderItem* item);


//  Some Methodes for XML ItemQuery
             int     CompleteItemQueryResult();
             long    ArticleExpireDate();
    pxArticleInfo*   ArticleInfoRequest(const long ArticleNo, const long Qty);

    nMoney           GetLegallBreizhPrice();

    // Special Price for the Swiss XML Application(kscserver)
    nMoney           BasePrice();

//  Some Methodes for Overdrive(Swiss)
             long    OverDriveCondition(const long QToPost, const long QInStock);

//  Methode to  check Articlequota for a remote computer
    long    CheckRemoteArticleQuota(const short BranchNo, const long QToPost);

//  Methode to  delete AuxStoreLocList after booking of position
    int     DeleteAuxStoreLocList();

//  Queries:
    int               DispoGet(tDISPOITEM& di);
    int               GetBasePrices(const PriceTypeEnum priceType);
    pxVerbund::subsequentDelivery::pxDeliveryPosList* AuxDelList();
    pxVartikelLokalList* AuxStoreLocList();
    pxItemDiscountList* ItemDiscountList();
    pxKdAuftragPosRefundList* KdAuftragPosRefundList();
    pxItemAttributes*  ItemAttributes()    {return ItemAttributes_; }
    pxArtPriceList*    ArtPriceList();
    pxTenderPos*       TenderPos();
    pxDiscountList*    ArtDiscountList()   {return ArtDiscountList_; }
    pxOrderPosCalcMode*  OrderPosCalcMode();
    pxOrderPosPromoList* OrderPosPromoList();
    pxPromoCollectList*  PromoCollectList();    // Pointer to  PromoCollectList

    pxArtBase*         ArtBase  (DBAccessMode mode = cDBGET_READONLY);
    pxArtDispo*        ArtDispo (DBAccessMode mode = cDBGET_READONLY);




public:
    bool hasArticleQuota();

    nBitMap&           ItemFlags ()  { return ETPosSchalter_;}
    nBitMap&           ItemArtFlags(){ return ETArtSchalter_;}
    nBitMap&           ItemArtClass(){ return ETArtKlasse_;}

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // const getter
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ItemType            PosTyp() const                      { return PosTyp_; }
    pxDeviceType        GeraetTyp() const                   { return GeraetTyp_; }
    ArticleState        ArtState() const                    { return FehlerArtikel_; }

    bool                CustomerSurchargeAdded() const      { return CustomerSurchargeAdded_; }
    bool                IsArtStateGood() const              { return (FehlerArtikel_ == ArtStateGood); }
    bool                IsQStateGood() const                { return (FehlerMenge_ == QStateGood); }
    bool                IsQStateInvalidDigit() const        { return (IsFehlerMengeQState(QStateInvalidDigit) || IsFehlerMengeQState(QStateInvalidCheckDigit)); }
    bool                IsQStateNotValid() const            { return IsFehlerMengeQState(QStateNotValid); }
    bool                IsQStateNotOnHand() const           { return IsFehlerMengeQState(QStateNotOnHand); }
    bool                IsQStateAlternate() const           { return IsFehlerMengeQState(QStateAlternate); }
    bool                IsQStateLimitCheck() const          { return IsFehlerMengeQState(QStateLimitCheck); }
    bool                IsQStateAlternateReimport() const   { return IsFehlerMengeQState(QStateAlternateReimport); }
    bool                IsQStateDelayedDelivery() const     { return IsFehlerMengeQState(QStateDelayedDelivery); }
    bool                IsQStateTenderQtyExceeded() const   { return IsFehlerMengeQState(QStateTenderQtyExceeded); }
    bool                IsProductStocked() const            { return (PosTyp_ == TypeProductStocked); }
    bool                IsProduct() const                   { return (PosTyp_ == TypeProductStocked ) || (PosTyp_ == TypeProductNotStocked); }
    bool                IsKnownProduct() const              { return IsProduct(); }
    bool                IsUnKnownProduct() const            { return PosTyp_ == TypeProductUnknown; }
    bool                IsText() const                      { return (PosTyp_ == TypeTextOnly); }
    bool                IsDispoItem() const                 { return (PosTyp_ == TypeDispoItem) || (PosTyp_ == TypeDispoItemValued); }
    bool                IsDispoItemValued() const           { return (PosTyp_ == TypeDispoItemValued); }
    bool                IsBookRestDelivery() const          { return BookRestDelivery_; }
    bool                IsDispoMoeglich() const             { return DispoMoeglich_; }
    bool                IsQuotaExeeded() const              { return QuotaExeeded_; }
    bool                IsReleaseRestDelivery() const       { return ReleaseRestDelivery_; }
    bool                IsProFormaBooking() const           { return ProFormaBooking_; }
    bool                IsPriceTypeHealthFund() const       { return PreisTyp_ == HEALTHFUND_PRICE; }
    bool                IsPriceTypeRetail() const           { return PreisTyp_ == RETAIL_PRICE; }
    bool                IsPriceTypeFreeSale() const         { return PreisTyp_ == FREESALE_PRICE; }
    bool                IsRebateAccountExceeded() const     { return RebateAccountExceeded_; }
    bool                IsNoNarcoticsDiscAcc() const        { return NoNarcoticsDiscAcc_; }
    bool                IsArticleDiscountPromotion() const  { return 1 == PromoTyp_; }
    bool                IsFreeArticlePromotion() const      { return 2 == PromoTyp_; }
    bool                IsDiscountNoQty() const             { return ProblemState_ == PDiscountNoQty; }
    bool                IsDiscountArticleNotAV() const      { return ProblemState_ == PDiscountArticleNotAV; }
    bool                IsUpdateDebtlimitK1() const         { return UpdateDebtlimitK1_; }
    bool                IsUpdateDebtlimitK2() const         { return UpdateDebtlimitK2_; }
    bool                IsNotSaveDiscountList() const       { return NotSaveDiscountList_; }
    bool                IsPriso() const                     { return (KzPriso_ == '1'); }
    bool                IsCapPosition() const               { return (BusinessTypeNo_ == 4 ); }
    bool                IsIBTPosDayNightMerge() const       { return IBTPosDayNightMerge_; }
    bool                IsHigherConditionsAvailable()const  { return HigherConditionsAvailable_; }
    bool                IsArtStateNotFound() const          { return (FehlerArtikel_ == ArtStateNotFound); }

    char                Zuzahlung() const                   { return Zuzahlung_; }
    char                BewegungsArt() const                { return BewegungsArt_; }
    char                CodeBlocage() const                 { return CodeBlocage_; }
    char                KzPriso() const                     { return KzPriso_; }

    short               QState() const                      { return FehlerMenge_; }
    PriceTypeEnum       PreisTyp() const                    { return PreisTyp_; }
    short               BusinessTypeNo() const              { return BusinessTypeNo_; }
    short               MaxTargetNo() const                 { return MaxTargetNo_; }
    short               ContainerLevel() const              { return ContainerLevel_; }
    short               PromotionNo() const                 { return PromotionNo_; }
    short               PromoTyp() const                    { return PromoTyp_; }
    short               CodeType() const                    { return CodeType_; }
    short               ProblemState() const                { return ProblemState_; }
    short               SubGeraetTyp() const                { return SubGeraetTyp_; }
    short               IBTTourWeekDay() const              { return IBTTourWeekDay_; }
    short               getNLevelIBTTypeID() const          { return IBTTypeID_; }
    ItemSendStatusEnum  SendeStatus() const                 { return SendeStatus_; }
    PriceTypeEnum       PreisTypSaved() const               { return PreisTypSaved_; }
    tDiscountCategory   NatraCategory() const               { return NatraCategory_; }

    int                 Rabattfaehig() const                { return Rabattfaehig_; }

    long                ArtikelNr() const                   { return ArtikelNr_; }
    long                SubstProposalArticleNo() const      { return SubstProposalArticleNo_; }
    long                KdAuftragNr() const                 { return KdAuftragNr_; }
    long                MengeAbgebucht() const              { return MengeAbgebucht_; }
    long                MengeBestaetigt() const             { return MengeBestaetigt_; }
    long                MengeBestellt() const               { return MengeBestellt_; }
    long                MengeDispoMoeglich() const          { return MengeDispoMoeglich_; }
    long                MengeGeliefert() const              { return MengeGeliefert_; }
    long                MengeMoeglich() const               { return MengeMoeglich_; }
    long                MengeNatra() const                  { return MengeNatra_; }
    long                MengeNatraGrossH() const            { return MengeNatraGrossH_; }
    long                MengeNatraHerst() const             { return MengeNatraHerst_; }
    long                MengeNLMoeglich() const             { return MengeNLMoeglich_; }
    long                MengeReserviert() const             { return MengeReserviert_; }
    long                GetPurchaseRelevantQty() const      { return PurchaseRelevantQty_; }
    long                PosNr() const                       { return PosNr_; }
    long                ArtikelNrPassiv() const             { return ArtikelNrPassiv_; }
    long                MengeVorausBezug() const            { return MengeVorausBezug_; }
    long                BatchPosNr() const                  { return BatchPosNr_; }
    long                UhrZeitBestNachUpd() const          { return UhrZeitBestNachUpd_; }
    long                ArtBestNachUpd() const              { return ArtBestNachUpd_; }
    long                WannenNr() const                    { return WannenNr_; }
    long                LinkPosNr() const                   { return LinkPosNr_; }
    long                DiscountArticleNo() const           { return DiscountArticleNo_; }
    long                MengeNatraDiscountArticle() const   { return MengeNatraDiscountArticle_;  }
    long                ArticleNoPack() const               { return ArticleNoPack_; }
    long                MengeBestelltOrg() const            { return MengeBestelltOrg_; }
    long                MengeBestelltNatra() const          { return MengeBestelltNatra_;}

    double              RabattFest() const                  { return RabattFest_; }

    double              SalesTaxRate() const                { return SalesTaxRate_; }
    double              DiscountValPctMan() const           { return DiscountValPctMan_; }
    double              GrossProfitPctFV() const            { return GrossProfitPctFV_; }
    double              DiscountValPctProforma() const      { return DiscountValPctProforma_; }
    double              CustomerSurcharge() const           { return CustomerSurcharge_; }

    nMoney              PreisEKApo() const                  { return PreisEKApo_; }
    nMoney              PreisVKApo() const                  { return PreisVKApo_; }
    nMoney              PreisEKApoNetto() const             { return PreisEKApoNetto_; }
    nMoney              PreisEKGrosso() const               { return PreisEKGrosso_; }
    nMoney              PreisEKGrossoNA() const             { return PreisEKGrossoNA_; }
    nMoney              RabattFestDM() const                { return RabattFestDM_; }
    nMoney              PreisEKApoFree() const              { return PreisEKApoFree_; }
    nMoney              PreisFaktur() const                 { return PreisFaktur_; }
    nMoney              RefundValue() const                 { return RefundValue_; }
    nMoney              PreisAGP() const                    { return PreisAGP_; }
    nMoney              PreisFakturCstGr12() const          { return PreisFakturCstGr12_; }
    nMoney              FixedPricePaymentterms() const      { return FixedPricePaymentterms_; }

    nMoney              getPharmacySellPrice();

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // non const getter
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    const nString&      Bemerkungen() const                     { return Bemerkungen_; }
    const nString&      KdAuftragBestellNr() const              { return KdAuftragBestellNr_; }
    const nString&      ArticleCode() const                     { return ArticleCode_; }
    const nString&      TourIdIBT() const                       { return TourIdIBT_; }
    const nString&      TourId() const;
    const nString&      PharmacyGroupId() const                 { return PharmacyGroupId_; }
    const nString&      XMLLinereference() const                { return XMLLinereference_; }
    const nString&      NatraPharmacyGroup() const              { return NatraPharmacyGroup_; }
    pxOrder&            Order() const                           { return *Order_; }
    pxOrder*            getOrder() const                        { return Order_; }
    long                MengeVerbund();
    long                TotalIBTQuantity(); // return ibt quantity including quantities from linked positions
    long                MengeNachgeliefert();
    long                MengeDisponiert();
    long                VerbundUrIDFNr();
    long                VerbundUrKaufNr();
    short               VerbundFilialNr();
//    short               VerbundFilialNr2();
    short               IBTType();
    bool                IsDayIBT();
    pxOrderPosPromo*    GetOrderPosPromo( const short PromotionNo );

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // setter
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void                SetMengeNatraDiscountArticle( const long qty )      { MengeNatraDiscountArticle_ = qty;  }
    void                SetUpdateDebtlimitK1()                              { UpdateDebtlimitK1_ = true; }
    void                SetUpdateDebtlimitK2()                              { UpdateDebtlimitK2_ = true; }
    void                SetNotSaveDiscountList()                            { NotSaveDiscountList_ = true; }
    void                SetIBTPosDayNightMerge()                            { IBTPosDayNightMerge_ = true; }
    void                SetPosTyp( ItemType  typ)                           { PosTyp_ = typ; }
    void                SetHigherConditionsAvailable()                      { HigherConditionsAvailable_ = true; }
    void                ClearUpdateDebtlimitK1()                            { UpdateDebtlimitK1_ = false; }
    void                ClearUpdateDebtlimitK2()                            { UpdateDebtlimitK2_ = false; }
    void                ClearNotSaveDiscountList()                          { NotSaveDiscountList_ = false; }
    void                ClearIBTPosDayNightMerge()                          { IBTPosDayNightMerge_ = false; }
    void                ClearHigherConditionsAvailable()                    { HigherConditionsAvailable_ = false; }
    void                MengeBestaetigt(long q)                             { MengeBestaetigt_ = q; SetDirty(); }
    void                MengeAbgebucht(long q)                              { MengeAbgebucht_ = q; SetDirty(); }
    void                MengeGeliefert(long q)                              { MengeGeliefert_ = q; SetDirty(); }
    void                MengeReserviert(long q)                             { MengeReserviert_ = q; SetDirty(); }
    void                MengeBestellt(long q)                               { MengeBestellt_ = q; SetDirty(); }
    void                MengeNatra(long q)                                  { MengeNatra_ = q; SetDirty(); }
    void                MengeNatraGrossH(long q)                            { MengeNatraGrossH_ = q; SetDirty(); }
    void                MengeNatraHerst(long q)                             { MengeNatraHerst_ = q; SetDirty(); }
    void                SetMengeVerbund(long q)                             { MengeVerbund_ = q; }
    void                SetPurchaseRelevantQty(long q)                      { PurchaseRelevantQty_ = q; }
    void                SetPreisEKApoNetto(nMoney price)                    { PreisEKApoNetto_ = price; SetDirty(); }
    void                SetPreisEKGrosso(nMoney price)                      { PreisEKGrosso_ = price; SetDirty(); }
    void                SetPreisEKGrossoNA(nMoney price)                    { PreisEKGrossoNA_ = price; SetDirty(); }
    void                SetPreisEKApo(nMoney price)                         { PreisEKApo_ = price; SetDirty(); }
    void                SetPreisVKApo(nMoney price)                         { PreisVKApo_ = price; SetDirty(); }
    void                SetPreisAGP(nMoney price)                           { PreisAGP_ = price; SetDirty(); }
    void                SetPreisEKApoFree(nMoney price)                     { PreisEKApoFree_ = price; SetDirty(); }
    void                SetPreisFakturFixed(nMoney price)                   { PreisFaktur_ = price; SetFixedInvoicePrice(); SetDirty(); }
    void                SetBatchPosNr( long batchposnr )                    { BatchPosNr_ = batchposnr; }
    void                SetBewegungsArt( char BewegungsArt )                { BewegungsArt_ = BewegungsArt; }
    void                SetLinkPosNr( long PosNr )                          { LinkPosNr_ = PosNr; SetDirty(); }
    void                KdAuftragBestellNr( nString& KdAuftragBestellNr )   { KdAuftragBestellNr_ = KdAuftragBestellNr; SetDirty(); }
    void                SetArticleNoPack( long artno )                      { ArticleNoPack_ = artno; SetDirty(); }
    void                SetDiscountValPctMan( double value )                { DiscountValPctMan_ = value; SetDirty(); }
    void                SetContainerLevel( short level )                    { ContainerLevel_ = level; SetDirty(); }
    void                SetFixedPricePaymentterms( nMoney price )           { FixedPricePaymentterms_ = price; }
    void                SetGrossProfitPctFV( double pct )                   { GrossProfitPctFV_ = pct; SetDirty(); }
    void                SetRefundValue( nMoney value )                      { RefundValue_ = value; SetDirty(); }
    void                SetPromotionNo( short no )                          { PromotionNo_ = no; SetDirty(); }
    void                SetPromoTyp( short Typ )                            { PromoTyp_ = Typ; SetDirty(); }
    void                SetDiscountValPctPromo( double value )              { DiscountValPctPromo_ = value; SetDirty(); }
    void                SetPharmacyGroupId( nString& PharmacyGroupId )      { PharmacyGroupId_ = PharmacyGroupId; }
    void                SetDiscountValPctProforma( double value )           { DiscountValPctProforma_ = value; }
    void                SetProblemState( short State )                      { ProblemState_ = State; SetDirty(); }
    void                SetFehlerMenge( short State )                       { FehlerMenge_  = State; SetDirty(); }
    void                SetXMLLinereference( const nString& refnr )         { XMLLinereference_ = refnr; SetDirty(); }
    void                SetCustomerSurchargeAdded( bool value )             { CustomerSurchargeAdded_ = value; }
    void                SetCustomerSurcharge( double value )                { CustomerSurcharge_ = value; }
    void                SetSubGeraetTyp( short sdev )                       { SubGeraetTyp_ = sdev; }
    void                SetBusinessTypeNo( short type )                     { BusinessTypeNo_ = type; }
    void                SetIBTTourWeekDay( short weekday )                  { if (IBTTourWeekDay_ == 0 ) { IBTTourWeekDay_= weekday; SetDirty(); } }
    void                SetTourId( nString& tourid )                        { TourId_ = tourid; SetDirty(); }
    void                SetIBTType( short ibttype )                         { if (IBTType_ == 0 ) { IBTType_ =  ibttype; SetDirty(); } }
    void                SetIBTTypeID( short ibttypeid )                     { IBTTypeID_ = ibttypeid; SetDirty(); }
    void                SetGeraetTyp( pxDeviceType  gtyp )                  { GeraetTyp_ = gtyp; }
    void                SetBookRestDelivery()                               { BookRestDelivery_ = true; }
    void                ClearBookRestDelivery()                             { BookRestDelivery_ = false; }
    void                SetQuotaExeeded()                                   { QuotaExeeded_ =  true; }
    void                ClearQuotaExeeded()                                 { QuotaExeeded_ =  false; }
    void                SetReleaseRestDelivery()                            { ReleaseRestDelivery_ =  true; }
    void                SetDispoMoeglich()                                  { DispoMoeglich_ = true; }
    void                ClearDispoMoeglich()                                { DispoMoeglich_ = false; }
    void                SetProFormaBooking()                                { ProFormaBooking_ =  true; }
    void                SetRebateAccountExceeded()                          { RebateAccountExceeded_ =  true; }
    void                ClearRebateAccountExceeded()                        { RebateAccountExceeded_ =  false; }
    void                SetNoNarcoticsDiscAcc()                             { NoNarcoticsDiscAcc_ =  true; }
    void                SendeStatus(ItemSendStatusEnum s)                   { SendeStatus_ = s; SetDirty(); Put(); }
    void                SetPreisTypSaved(const PriceTypeEnum preistyp )     { PreisTypSaved_ = preistyp; }
    void                SetMengeBestelltOrg( long menge)                    { MengeBestelltOrg_ = menge; SetDirty(); }
    void                SetMengeBestelltNatra( long mengenatra)             { MengeBestelltNatra_ = mengenatra; SetDirty(); }
    void                SetNatraCategory(const tDiscountCategory category)  { NatraCategory_ = category; SetDirty(); }
    void                SetNatraPharmacyGroup(const nString& group)         { NatraPharmacyGroup_ = group; SetDirty(); }

    void                SetPreisTyp(const PriceTypeEnum preistyp)           { PreisTyp_ = preistyp;  }
    void                SetRabattFest( double fixedDiscountValue )          { RabattFest_ = fixedDiscountValue; SetDirty(); }


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // other functions
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    int                 Bemerkungen(const nString& s, const long LinkPosNr = 0);
    double              CalcAvp();
    long                CalcConditions();
    double              CalcDiscountPercentage( double GrossProfitPct, short CascadeLevel, long baseQuantity);
    nMoney              calculateInvoiceValue();
    nMoney              calculateNaturalRebateValue();
    double              calculateNewDiscount();
    void                changeDiscountInDB(double newDiscount);
    nMoney              CheckCreditLimitK1(nMoney OldValue);
    nMoney              CheckCreditLimitK2(nMoney OldValue);
    nMoney              GetCalcAvp();
    basar::Decimal      getCustomerGrossProfitPct(long baseQuantity);
    basar::Decimal      GetCustomerSurchargePct();
    bool                GetCustomerSurchargePctByManufacturer(long manufacturerNo, basar::Decimal& surcharge);
    double              GetLogisticAddition();
    double              getMarginGepAep();
    nMoney              GetMaxAvp();
    int                 checkPriceLimitations( bool ignorePriceLimitation /*= false*/, long& qtyToPost );
    nMoney              GetGepNaNa();

    nMoney              InvoiceValue(pxItemDiscountList* = NULL);
    bool                IsArticleListFiveMember();
    bool                IsChangeable();
    bool                IsDelayedDelivery();
    bool                IsOrderParamArticle();
    bool                IsRestDeliveryPossible();
    nMoney              NaturalRebateValue();
    nMoney              OrderCorruptValue();
    nMoney              OrderValue();
    nMoney              OrderValueDisc();
    void                PharmosDispoItem();
    nMoney              PreisEKApoFV();
    nMoney              PreisEKApoKK();
    nMoney              PreisEKGrossoFV();
    nMoney              PreisEKGrossoKK();
    void                PreisTyp( const PriceTypeEnum priceType );
    nMoney              Price();
    nMoney              PriceCstGr12();
    nMoney              ReimbursementPrice(const long ArticleNo, const char Type);
    void                SetDiscountArticleNo( long num );
    void                SetTourIdIBT( nString& tourid);
    nMoney              ShipValue();
    nMoney              ShipValueDisc();
    void                ToPharmosBatch( bool Abverkaufserhoehung );
    void                ToPharmosHMKText();
    nMoney              WertBrutto();
    nMoney              WertNetto();
    nMoney              WertRabatt();

    int                 writeToDB( basar::Decimal SurchargePct, basar::Decimal DeductionPct, basar::Decimal SurchargeCalc, basar::Decimal Avp, basar::Decimal SurchargeCalcDis, basar::Decimal AvpDis );

    nMoney      PreisEKGrossoNaByPriceType(const PriceTypeEnum priceType);
    double      AddDiscountToExistingOne(double newDiscount, nString PharmacyGroupId, double RefundValue, char TurnOverCalcImpact, short PromotionNo, const short DiscountType);
    void        AddSurchargeToAEP(basar::Decimal& surchargePct, const PriceTypeEnum priceType);
    void        AddNatraToExistingOne(long newDiscountQty, long DiscountArticleNo, double DiscountKey, nString PharmacyGroupId, double RefundValue, char TurnOverCalcImpact, short PromotionNo, const short DiscountType);
    void        ProcessCalclistForSerbia(pxCalcDiscountList* calclist, pxCustBase& customer);
    short       GetMaxTargetNoForSerbia(pxCalcDiscountList* calclist);
    int         WriteRefund(long OrderNo, long PosNo, double RefundValue, double RefundPct, long QtyToBeDelivered, short RefundSrc, short PromotionNo);
    int         WriteRefund(double RefundValue, double RefundPct, long QtyToBeDelivered, short RefundSrc, short PromotionNo);
    int         WriteKdAuftragPosRefund(long OrderNo, long PosNo, double RefundValue, double RefundPct, long QtyToBeDelivered, short RefundSrc, short PromotionNo);
    void        GetAddOnFlags(short PromotionNo, bool& AddOnPromoDiscount, bool& AddOnStdDiscount, bool& NotBySalesWeb);
    int         CheckRefund( pxDiscount* diskentry, pxPromoCollect* promocollect, pxRangeControl* rclentry );
    long        GetIBTQuantityOfLinkedPosition();
    int         ItemUpdateDiscountList();
    int         ItemUpdateDiscountListHR();
    double      GetDiscountValuePct();
    double      GetDiscountValPctMan();
    double      getOrderPositionDiscountDiscountValue();
    nMoney      CalcSalesTax();
    bool        AddOnDiscountPct(double ValuPct, double DiffValuePct = 0.0);

    MessageCodeEnum     checkBatchRequest(const nString& batchCode, const bool fixBatch);
    MessageCodeEnum     StoreFixBatchInfo(const nString& ChargenNr);
    MessageCodeEnum     StoreDesiredBatchInfo(const nString& ChargenNr);

    basar::VarString    GetChargenNr();
    bool                IsFixBatch() const;

    int        WriteOrderPosPromo(const nString& PharmacyGroupId, long DiscountGrpNo, long BaseQty, double BaseValue, long CustomerNo, short PromotionNo, char InternalDiscount='0', double DiscouValuePct = 0.0 );
    int        SetMengeNatra(const long MengeNatra);
    int        SetArticleCodeValues(const short typ, const nString& code,bool anyway=false);
    int        AssignDiscountPct(pxDiscount* diskentry, pxRangeControl* rclentry);
    int        AssignDiscountPctProforma(pxDiscount* diskentry,pxItemDiscountList* discl);
    int        AssignTargetDiscount(pxRangeControlList* rcl);
    int        AssignTargetDiscountProforma(pxRangeControlList* rcl,pxItemDiscountList* discl);
    double     GetPosPromoDiscountValuePct();
    int        DeletePromotionCollectList();
    int        DeleteItemDiscountList();
    bool       CheckPromoQuota(const short BranchNo, const short PromotionNo, const long PromoBaseQty);
    int        UndoPromoQuota();                         // orderentry BG
    int        ReleasePromoQuota(const long Qty);       // Batch pvhx01  BG
    long       GetLowerPromoCondition(const long restPromoQuota, const long PromoBaseQty);
    int        UndoCreditDayTurnOver(nMoney OldOrderValue, nMoney NewOrderValue);
    int        CscBatchCheckOrderPos(const long QtyNatra, const nString& remarks);
    //int        CscBatchCreateDeliveryPos(const long IDFNrOrg, const long OrderNoOrg, const long PosNrOrg);
    int        CscBatchUpdateDeliveryPos(const long QtyNatra, const nString& Remarks);
    int        changeArtBaseToSubstitutionArticle(const long SubstitutionArticleNo, const long QOrdered);
    int        setOrderItemAlternateRemarks( const long ArticleNoOrdered, const short MessageNo);
    long       getIBTQuantityInStock( const long qty, const short ibtfil, const int flags);
    long       GetQtyInStock(pxArtBase* artBase = NULL);
    int        bookDiscountValPctManProforma( double value);
    long       calculateRebateForOrderedQuantity(const long QOrdered);

    pxArticleCodes* GetArticleCode( const long articleno);
    bool       checkLongTermLack(const long QOrdered, const int flags, const BookingType btype);

    const libcsc::discount::OrderPositionDiscountListPtr getDiscountList();

public:
    pxGenericOrderRemarkList*   getGenericOrderRemarks();
    ArticleSubstitutionUtil*    getArticleSubstitutionUtil();

public:
    mutable TourInfo*           m_ItemTourInfoIBT;
    mutable TourInfo*           m_ItemTourInfo;
    TourInfo*                   getItemTourInformation(bool ibt = false) const;
    long                        getItemDeliveryTime(char& tourid, bool ibt = false);
    long                        getItemDeliveryDate(bool ibt = false);
    long                        getItemTourDate(bool ibt = false);
    short                       getItemDeliveryTimeBuffer(bool ibt = false);
    long                        getIBTCustomerNo();
    long                        getIBTCustomerDeliveryDate();

    void                        setXMLReferences( const basar::VarString& orderreference, const basar::VarString& orderlinereference );

    void                        setMSV3RequestID(const basar::VarString& requestid);
    void                        setMSV3RequestSupportID(const basar::VarString& bestellsupportid);
    void                        setMSV3OrderID(const basar::VarString& auftragid);
    void                        setMSV3OrderSupportID(const basar::VarString& auftragsupportid);
    void                        setPromotionName(const basar::VarString& promotionName);
    void                        setOCPOrderInfo(const basar::VarString& channelId, int offerID, double freightCost, double carriageFree);
    bool                        getOCPOrderInfo(basar::VarString& channelId, int& offerID, double& freightCost, double& carriageFree);
    bool                        hasOCPOrderInfo();

public:
    libcsc::ibt::IIbtRequestPtr             getIbtRequest() { return m_IbtRequest; }
    bool isIbtBookingCompleted();
    void setIbtRequest(libcsc::ibt::IIbtRequestPtr request) { m_IbtRequest = request; }
    libcsc::discount::TenderDiscountPtr     getTenderDiscount() { return m_TenderDiscount; }

public:
    bool     IsCancelled() const { return ETPosSchalter_.TestBit(bItemCancelled); }
    bool     IsToCommission() const { return ETPosSchalter_.TestBit(bToCommission); }
    bool     IsToCustomerService() const { return ETPosSchalter_.TestBit(bToCustomerService); }
    bool     IsToDisposal() const { return ETPosSchalter_.TestBit(bToDisposal); }
    bool     IsAuxPosted() const { return ETPosSchalter_.TestBit(bAuxPosted); }
    bool     IsAuxPostPossible() const { return ETPosSchalter_.TestBit(bAuxPostPossible); }
    bool     IsCustPurchase() const { return ETPosSchalter_.TestBit(bCustPurchase); }
    bool     IsCustRestDelivery() const { return ETPosSchalter_.TestBit(bCustRestDelivery); }
    bool     IsManualMaintenance() const { return ETPosSchalter_.TestBit(bManualMaintenance); }
    bool     IsDelayedDelivered() const { return ETPosSchalter_.TestBit(bDelayedDelivered); }
    bool     IsSperreRabattManuell() const { return ETPosSchalter_.TestBit(bSperreRabattManuell); }
    bool     IsInhibitTransferBem() const { return ETPosSchalter_.TestBit(bInhibitTransferBem); }
    bool     IsPartialIBTQantity() const { return ETPosSchalter_.TestBit(bPartialIBTQantity); }

    void     SetSeparatePosition() { ETPosSchalter_.SetBit(bSeparatePosition); }
    /*----------------------------------------------------------------------------*/
    /*  UNIPHARM/PHARMOS compatibilty.                                            */
    /*----------------------------------------------------------------------------*/

public:
    bool     IsDafue() const { return ETPosSchalter_.TestBit(bDafue); }
    bool     IsSeriellUebertragen() const { return ETPosSchalter_.TestBit(bSeriellUebertragen); }
    bool     IsFreierPreis() const { return ETPosSchalter_.TestBit(bFreierPreis); }
    bool     IsTextDategAlpha() const { return ETPosSchalter_.TestBit(bTextDategAlpha); }
    bool     IsDisponieren() const { return ETPosSchalter_.TestBit(bDisponieren); }
    bool     IsZugesagt() const { return ETPosSchalter_.TestBit(bZugesagt); }
    bool     IsNachliefern() const { return ETPosSchalter_.TestBit(bNachliefern); }
    bool     IsUeberMenge() const { return ETPosSchalter_.TestBit(bUeberMenge); }
    bool     IsNachFrageBuchung() const { return ETPosSchalter_.TestBit(bNachFrageBuchung); }
    bool     IsDefektPosition() const { return ETPosSchalter_.TestBit(bDefektPosition); }
    bool     IsAusweichArtikelGebucht() const { return ETPosSchalter_.TestBit(bAusweichArtikelGebucht); }
    bool     IsSeparatePosition() const { return ETPosSchalter_.TestBit(bSeparatePosition); }
    bool     IsMengenKontigentDefekt() const { return ETPosSchalter_.TestBit(bMengenKontigentDefekt); }
    bool     IsKeinBestandsDefekt() const { return ETPosSchalter_.TestBit(bKeinBestandsDefekt); }
    bool     IsNichtNachPharmos() const { return ETPosSchalter_.TestBit(bNichtNachPharmos); }
    bool     IsKuehlboxPosition() const { return ETPosSchalter_.TestBit(bKuehlboxPosition); }
    bool     IsMengenErhoehung() const { return ETPosSchalter_.TestBit(bMengenErhoehung); }
    bool     IsVerbundAuftragsPosition() const { return ETPosSchalter_.TestBit(bVerbundAuftragsPosition); }
    bool     IsAbverkaufsErhoehung() const { return ETPosSchalter_.TestBit(bAbverkaufsErhoehung); }
    bool     IsNachLieferungVerarbeitet() const { return ETPosSchalter_.TestBit(bNachLieferungVerarbeitet); }
    bool     IsReimportArtikel() const { return ETPosSchalter_.TestBit(bSubReimportArtikel); }
    bool     IsNaturalRabattIntern() const { return ETPosSchalter_.TestBit(bNaturalRabattIntern); }
    bool     IsNeuerPreisKsc() const { return ETPosSchalter_.TestBit(bNeuerPreisKsc); }
    bool     IsArtikelUmgeschluesselt() const { return ETPosSchalter_.TestBit(bArtikelUmgeschluesselt); }
    bool     IsInfoBelegDrucken() const { return ETPosSchalter_.TestBit(bInfoBelegDrucken); }
    bool     IsTHWertAusKsc() const { return ETPosSchalter_.TestBit(bTHWertAusKsc); }
    bool     IsDayNightMergePosition() const { return ETPosSchalter_.TestBit(bDayNightMergePosition); }
    bool     IsFixedInvoicePrice() const { return ETPosSchalter_.TestBit(bFixedInvoicePrice); }
    bool     IsProduserQuotaDefect() const { return ETPosSchalter_.TestBit(bProduserQuotaDefect); }

    bool     IsRestDeliveryPossibleForArticle();


    /*----------------------------------------------------------------------------*/
    /*  PHARMOS compatibility.                                                    */
    /*----------------------------------------------------------------------------*/
    bool    IsContainerPack() { return ETArtSchalter_.IsContainerArtikel(); }
    bool    IsBeiPackMulti() { return ETArtSchalter_.IsBeiPackMulti(); }
    void    SetContainerPack() { ETArtSchalter_.SetContainerArtikel(); }
    void    SetBeiPackMulti() { ETArtSchalter_.SetBeiPackMulti(); }
    void    ClearContainerPack() { ETArtSchalter_.ClearContainerArtikel(); }
    void    ClearBeiPackMulti() { ETArtSchalter_.ClearBeiPackMulti(); }

    bool    IsNetPrice() { return ETArtSchalter_.IsNettoAktion(); }
    void    SetNetPrice() { ETArtSchalter_.SetNettoAktion(); }
    void  ClearNetPrice() { ETArtSchalter_.ClearNettoAktion(); }

    void    SetInhibitTransferBem() { ETPosSchalter_.SetBit(bInhibitTransferBem); }
    void    SetPartialIBTQantity() { ETPosSchalter_.SetBit(bPartialIBTQantity); }
    void    SetVerbundAuftragsPosition() { ETPosSchalter_.SetBit(bVerbundAuftragsPosition); }

    /*----------------------------------------------------------------------------*/
    /*  Flag queries.                                                             */
    /*----------------------------------------------------------------------------*/
    bool    IsStellerKopf() const { return ETPosSchalter_.TestBit(bStellerKopf); }
    bool    IstStellerMitglied() const { return ETPosSchalter_.TestBit(bStellerMitglied); }

    /*----------------------------------------------------------------------------*/
    /*  Flag setting/resetting.                                                   */
    /*----------------------------------------------------------------------------*/
    void    SetDafue() { ETPosSchalter_.SetBit(bDafue); }
    void    SetCancelled() { ETPosSchalter_.SetBit(bItemCancelled); }
    void    SetToCommission() { ETPosSchalter_.SetBit(bToCommission); }
    void    SetToCustomerService() { ETPosSchalter_.SetBit(bToCustomerService); }
    void    SetToDisposal() { ETPosSchalter_.SetBit(bToDisposal); }
    void    SetAuxPosted() { ETPosSchalter_.SetBit(bAuxPosted); }
    void    SetAuxPostPossible() { ETPosSchalter_.SetBit(bAuxPostPossible); }
    void    SetCustPurchase() { ETPosSchalter_.SetBit(bCustPurchase); }
    void    SetCustRestDelivery() { ETPosSchalter_.SetBit(bCustRestDelivery); }
    void    SetDelayedDelivered() { ETPosSchalter_.SetBit(bDelayedDelivered); }
    void    SetSperreRabattManuell() { ETPosSchalter_.SetBit(bSperreRabattManuell); }
    void    SetDayNightMergePosition() { ETPosSchalter_.SetBit(bDayNightMergePosition); }
    void    SetFixedInvoicePrice() { ETPosSchalter_.SetBit(bFixedInvoicePrice); }
    void    SetProduserQuotaDefect() { ETPosSchalter_.SetBit(bProduserQuotaDefect); }

    void  ClearCancelled() { ETPosSchalter_.ClearBit(bItemCancelled); }
    void  ClearToCommission() { ETPosSchalter_.ClearBit(bToCommission); }
    void  ClearToCustomerService() { ETPosSchalter_.ClearBit(bToCustomerService); }
    void  ClearToDisposal() { ETPosSchalter_.ClearBit(bToDisposal); }
    void  ClearAuxPosted() { ETPosSchalter_.ClearBit(bAuxPosted); }
    void  ClearAuxPostPossible() { ETPosSchalter_.ClearBit(bAuxPostPossible); }
    void  ClearCustPurchase() { ETPosSchalter_.ClearBit(bCustPurchase); }
    void  ClearCustRestDelivery() { ETPosSchalter_.ClearBit(bCustRestDelivery); }
    void  ClearDelayedDelivered() { ETPosSchalter_.ClearBit(bDelayedDelivered); }
    void  ClearSperreRabattManuell() { ETPosSchalter_.ClearBit(bSperreRabattManuell); }
    void  ClearInhibitTransferBem() { ETPosSchalter_.ClearBit(bInhibitTransferBem); }
    void  ClearFreierPreis() { ETPosSchalter_.ClearBit(bFreierPreis); }
    void  ClearTextDategAlpha() { ETPosSchalter_.ClearBit(bTextDategAlpha); }
    void  ClearDisponieren() { ETPosSchalter_.ClearBit(bDisponieren); }
    void  ClearZugesagt() { ETPosSchalter_.ClearBit(bZugesagt); }
    void  ClearNachliefern() { ETPosSchalter_.ClearBit(bNachliefern); }
    void  ClearUeberMenge() { ETPosSchalter_.ClearBit(bUeberMenge); }
    void  ClearNachFrageBuchung() { ETPosSchalter_.ClearBit(bNachFrageBuchung); }
    void  ClearDefektPosition() { ETPosSchalter_.ClearBit(bDefektPosition); }
    void  ClearAusweichArtikelGebucht() { ETPosSchalter_.ClearBit(bAusweichArtikelGebucht); }
    void  ClearSeparatePosition() { ETPosSchalter_.ClearBit(bSeparatePosition); }
    void  ClearStellerKopf() { ETPosSchalter_.ClearBit(bStellerKopf); }
    void  ClearStellerMitglied() { ETPosSchalter_.ClearBit(bStellerMitglied); }
    void  ClearMengenKontigentDefekt() { ETPosSchalter_.ClearBit(bMengenKontigentDefekt); }
    void  ClearKeinBestandsDefekt() { ETPosSchalter_.ClearBit(bKeinBestandsDefekt); }
    void  ClearNichtNachPharmos() { ETPosSchalter_.ClearBit(bNichtNachPharmos); }
    void  ClearKuehlboxPosition() { ETPosSchalter_.ClearBit(bKuehlboxPosition); }
    void  ClearMengenErhoehung() { ETPosSchalter_.ClearBit(bMengenErhoehung); }
    void  ClearVerbundAuftragsPosition() { ETPosSchalter_.ClearBit(bVerbundAuftragsPosition); }
    void  ClearAbverkaufsErhoehung() { ETPosSchalter_.ClearBit(bAbverkaufsErhoehung); }
    void  ClearNachLieferungVerarbeitet() { ETPosSchalter_.ClearBit(bNachLieferungVerarbeitet); }
    void  ClearReimportArtikel() { ETPosSchalter_.ClearBit(bSubReimportArtikel); }
    void  ClearNaturalRabattIntern() { ETPosSchalter_.ClearBit(bNaturalRabattIntern); }
    void  ClearNeuerPreisKsc() { ETPosSchalter_.ClearBit(bNeuerPreisKsc); }
    void  ClearArtikelUmgeschluesselt() { ETPosSchalter_.ClearBit(bArtikelUmgeschluesselt); }
    void  ClearInfoBelegDrucken() { ETPosSchalter_.ClearBit(bInfoBelegDrucken); }
    void  ClearManualMaintenance() { ETPosSchalter_.ClearBit(bManualMaintenance); }
    void  ClearTHWertAusKsc() { ETPosSchalter_.ClearBit(bTHWertAusKsc); }
    void  ClearDayNightMergePosition() { ETPosSchalter_.ClearBit(bDayNightMergePosition); }
    void  ClearFixedInvoicePrice() { ETPosSchalter_.ClearBit(bFixedInvoicePrice); }
    void  ClearProduserQuotaDefect() { ETPosSchalter_.ClearBit(bProduserQuotaDefect); }

    void  SetFreierPreis() { ETPosSchalter_.SetBit(bFreierPreis); }
    void  SetTextDategAlpha() { ETPosSchalter_.SetBit(bTextDategAlpha); }
    void  SetDisponieren() { ETPosSchalter_.SetBit(bDisponieren); }
    void  SetZugesagt() { ETPosSchalter_.SetBit(bZugesagt); }
    void  SetNachliefern() { ETPosSchalter_.SetBit(bNachliefern); }
    void  SetUeberMenge() { ETPosSchalter_.SetBit(bUeberMenge); }
    void  SetNachFrageBuchung() { ETPosSchalter_.SetBit(bNachFrageBuchung); }
    void  SetDefektPosition() { ETPosSchalter_.SetBit(bDefektPosition); }
    void  SetAusweichArtikelGebucht() { ETPosSchalter_.SetBit(bAusweichArtikelGebucht); }
    void  SetStellerKopf() { ETPosSchalter_.SetBit(bStellerKopf); }
    void  SetStellerMitglied() { ETPosSchalter_.SetBit(bStellerMitglied); }
    void  SetMengenKontigentDefekt() { ETPosSchalter_.SetBit(bMengenKontigentDefekt); }
    void  SetKeinBestandsDefekt() { ETPosSchalter_.SetBit(bKeinBestandsDefekt); }
    void  SetNichtNachPharmos() { ETPosSchalter_.SetBit(bNichtNachPharmos); }
    void  SetKuehlboxPosition() { ETPosSchalter_.SetBit(bKuehlboxPosition); }
    void  SetMengenErhoehung() { ETPosSchalter_.SetBit(bMengenErhoehung); }
    void  SetAbverkaufsErhoehung() { ETPosSchalter_.SetBit(bAbverkaufsErhoehung); }
    void  SetNachLieferungVerarbeitet() { ETPosSchalter_.SetBit(bNachLieferungVerarbeitet); }
    void  SetReimportArtikel() { ETPosSchalter_.SetBit(bSubReimportArtikel); }
    void  SetMidasAbrechnung() { ETPosSchalter_.SetBit(bMidasAbrechnung); }
    void  SetNaturalRabattIntern() { ETPosSchalter_.SetBit(bNaturalRabattIntern); }
    void  SetNeuerPreisKsc() { ETPosSchalter_.SetBit(bNeuerPreisKsc); }
    void  SetArtikelUmgeschluesselt() { ETPosSchalter_.SetBit(bArtikelUmgeschluesselt); }
    void  SetInfoBelegDrucken() { ETPosSchalter_.SetBit(bInfoBelegDrucken); }
    void  SetManualMaintenance() { ETPosSchalter_.SetBit(bManualMaintenance); }
    void  SetTHWertAusKsc() { ETPosSchalter_.SetBit(bTHWertAusKsc); }

    void  SetCancelItem() { ETPosSchalter_.SetBit(bCancelItem); }
    void  ClearCancelItem() { ETPosSchalter_.ClearBit(bCancelItem); }
    bool  IsCancelItem() const { return ETPosSchalter_.TestBit(bCancelItem); }

    void  SetCancelAndDeleteItem() { ETPosSchalter_.SetBit(bCancelAndDeleteItem); }
    void  ClearCancelAndDeleteItem() { ETPosSchalter_.ClearBit(bCancelAndDeleteItem); }
    bool  IsCancelAndDeleteItem() const { return ETPosSchalter_.TestBit(bCancelAndDeleteItem); }

    void  SetItemClosed() { ETPosSchalter_.SetBit(bItemClosed); }
    void  ClearItemClosed() { ETPosSchalter_.ClearBit(bItemClosed); }
    bool  IsItemClosed() const { return ETPosSchalter_.TestBit(bItemClosed); }

    void  SetLongTermLack() { ETPosSchalter_.SetBit(bLongTermLack); }
    void  ClearLongTermLack() { ETPosSchalter_.ClearBit(bLongTermLack); }
    bool  IsLongTermLack() const { return ETPosSchalter_.TestBit(bLongTermLack); }

    void  SetPriceLimitExceeded() { ETPosSchalter_.SetBit(bPriceLimitExceeded); }
    void  ClearPriceLimitExceeded() { ETPosSchalter_.ClearBit(bPriceLimitExceeded); }
    bool  IsPriceLimitExceeded() const { return ETPosSchalter_.TestBit(bPriceLimitExceeded); }

protected:

    pxOrderItem(pxSession* session);
    pxOrderItem(pxSession* session, pxOrder& Order, tKDAUFTRAGPOS& src);

    pxOrderItem&      operator=(const tKDAUFTRAGPOS& src);
    //  Assigns the values of the record structure 'src' to self and returns a
    //  reference to self.

    void              Init();
    virtual  int     Delete();
    friend
        pxOrderItem&      Assign(pxOrderItem& dest, const tKDAUFTRAGPOS& src);
    friend
        tKDAUFTRAGPOS&    Assign(tKDAUFTRAGPOS& dest, const pxOrderItem& src);
    virtual  int      CompareTo(const nCollectable* that, void* p,
        const long lparm) const;

    static void InitOrderItem(tKDAUFTRAGPOS& record);

    virtual  int     Read(const void* record);
    virtual  int     Delete(const void* record);
    virtual  int     ReadLock(const void* record);
    virtual  int     Insert(const void* record);
    virtual  int     Update(const void* record);

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// private methods section
////////////////////////////////////////////////////////////////////////////////////////////////////////////
private:
    //long             CalcDisInKind(long Menge);
    //long             CalcDiscountPrice(long Menge);
    long             CalcTermsOnEntry(long QToPost, long QInStock);
    void              ReCalculate(long QToPost, long QInStock, int flags);

    // some new methodes to calculate discount based on the new table Discount

    BookingType       ConvertRemarks(const nString& remarks);
    //  Converts ordering remarks.
    void              HandleError(int flags = bPOST_DEFAULT);
    //  Register ordering format errors if input is from a non-video device.

    int              PostOrderQuantity(long QOrdered, long QDisInKind, long QDemanded,
        BookingType type,
        int   flags = bPOST_DEFAULT,
        short AuxFil = cDEFAULT,
        const nString& batchNr = "",
        bool isFixBatch = false,
        bool*       bStockNotOk = 0);
    int              IBTSubstitution(long QOrdered, long QDisInKind, long QDemanded,
        BookingType type,
        int   flags = bPOST_DEFAULT,
        short AuxFil = cDEFAULT);

    bool CheckStotinki(long QDisInKind, long Qordered);
    //  Post quantities, calculate conditions and terms for stocked products.
    pxVerbund::subsequentDelivery::pxDeliveryPos* NewDeliveryPos(const pxVerbund::subsequentDelivery::pxDelPosTyp PosTyp);
    //  Builds a new deliverypos entry
    long             QPostAux(const long q, /*pxVerbund::subsequentDelivery::pxDeliveryPos* dp,*/ pxVartikelLokal* stp);

    //  Post quantities from auxilarystock for stocked products.
//    pxVartikelLokal* GetAuxStockEntry(pxVerbund::subsequentDelivery::pxDeliveryPos* dp, const short fil);
    pxVartikelLokal* GetAuxStockEntry(const short fil);

    //  This function returns a pointer to the ArtStoreLoc entry where to post from
    int              UndoAuxPosting();
    int              AuxShipment();
    int              RestDeliveryService();
    pxVerbund::subsequentDelivery::pxDeliveryPos*    GetBackDeliveryPos();

    //  Posting flags:
    int              PostType(BookingType type);
    BookingType       PostType();
    void              UndoQuantityPosting(const pxStockTrans& stocktrans);
    int              DispoSanity(tDISPOITEM& s, BookingType btype);
    int              DispoUpdate(tDISPOITEM& s, BookingType btype);
    int              ArtBaseUpdate();
    int              ItemUpdate();
    int              ItemUpdateDiscountPos(pxOrderItem* item);
    int              ItemUpdateComPackMembers(pxOrderItem* item);
    int              ItemUpdateIBTPos(pxOrderItem* item);
    void              ItemRollBack();
    int              UndoRedo(const pxCustOrderType& ot, const pxCommType& ct,
        const pxStockTrans& st);
    int              UndoCommission();
    int              DoCommission();
    //  Undo condition calculation for a stocked product using the values passed
    //  as arguments, then redo condition calculation using the current order type
    //  values queried from the order object.

    int              UndoItem();
    //  Undo condition calculation for a stocked product using the values passed
    //  as arguments
    int              RedoItem(const pxCustOrderType& ot);
    //  Redo condition calculation for a stocked product using the values passed
    //  as arguments
    int              UndoItemBG();
    //  Undo condition calculation for a stocked product Bulagrian application

    int              RedoItemBG(const long QOrdered, const long QDisInKind, const long QDemanded);
    //  Redo condition calculation for a stocked product Bulgarian application

    int              CalculateContainer(pxOrderItem* item);
    int              UndoRedoAuxdelivery(pxOrderItem* item, const long QOrdered);
    int              UndoRedoAuxdeliveryComplete(pxOrderItem* item);
    int              UndoRedoRestDeliveryItem(pxOrderItem* item);
    int              UndoRedoPurchaseItem(pxOrderItem* item);
    int              UndoRedoDispoItem(pxOrderItem* item);
    int              UndoRedoReferenceItem(pxOrderItem* item);
    int              UndoRedoDelayedPurchaseItem(pxOrderItem* item);
    int              UndoRedoDelayedRestDeliveryItem(pxOrderItem* item);
    //int              IBTDeliveryItem(pxOrderItem* item);
    void             WriteOrderPosSplittInfo(const pxOrderItem* src, const SplittTypeEnum splitType);

    void              ToPharmos();
    void              ToPharmosRecord(tKDAUFTRAGPOS& record);
    void              ManualMaintenance();
    void              SalesTaxRate(const short TaxLevel);

    pxCalcDiscountList* createCalcDiscountList(int mode, long baseq, pxCustPharmGroupList* phglist, bool addOnPromoDiscount, bool addOnStdDiscount);
    pxCalcDiscountList* createCalcDiscountList(int mode, long baseq, pxCustPharmGroupList* phglist);
    void writeOrderPosPromoWithInternalDiscount(pxCalcDiscount* calcp);
    void writeOrderPosPromoWithInternalDiscountAndPromoBaseQty(pxCalcDiscount* calcp);
    void writeRefundWithDiscountKey(pxCalcDiscount* calcp);
    void writeRefund(pxCalcDiscount* calcp, double refundPct);
    void addDiscountToExistingOne(pxCalcDiscount* calcp, double newDiscount);
    pxItemDiscount* createItemDiscount(pxCalcDiscount* calcp);
    pxItemDiscount* createItemDiscount(short const discountType, nString const& pharmacyGroupId);
    void setSurchargePctOnCustomerSurcharge(pxItemDiscount* itemdisc);
    void putItemAndAppendToList(pxItemDiscount* itemdisc);
    void setMidasAbrechnung(char turnOverCalcImpact);
    void setNaturalRabattInternOrWriteKdAuftragPosRefund(bool isNrIntern, pxCalcDiscount* calcp, long baseq);
    void setNaturalRabattIntern(bool isNrIntern);
    void setOrClearNetPriceOnPreisEKApoNetto(bool clearWholesalePrice);
    void addDiscountAndWriteRefund(pxCalcDiscount* calcp, double pct, nString const& logevent);
    void blogDebugOnGlobalNoDatabaseWrite(nString const& logevent);
    void setPromotionNoOnPromoTypZero(short promotionNo);

    //  Item entry core function for stocked products just for StockInformation  :
    int                         AvailabilityQuery( const long  ArtikelNr );
    double                      CalculateRefundValueByRefundPct(double RefundPct, long QtyToBeDelivered);
    double                      CalculateRefundValue(double RefundPct);
    pxArticleQuota*             ArtQuota(DBAccessMode mode = cDBGET_READONLY);
    MessageCodeEnum             StoreBatchInfo(const nString& batchNr, bool isFixBatch);
    void                        assignItemTour();
    void                        assignItemIBTTour(short ibtbranchno, short nlevelibttype);
    TourInfo                    determineItemIBTTour( short ibtbranchno, short nlevelibttype );
    void                        removeItemTourAssignments();
    void                        copyGenericOrderRemarks(pxOrderItem* src);

    bool                        IsFehlerMengeQState(QuantityState state) const{ return ((FehlerMenge_ & state) == state); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// private variables section
////////////////////////////////////////////////////////////////////////////////////////////////////////////
private:
        pxOrder*           Order_;
        pxArtBase*         ArtBase_;
        pxArtPrice*        ArtPrice_;
        pxArtPriceList*    ArtPriceList_;
        pxArtDispo*        ArtDispo_;

        class ArticleQuotaProxy
        {
        public:
            ArticleQuotaProxy()
            : m_ArtQuota( NULL ), m_SearchRegistration( false )
            {
            }

            ~ArticleQuotaProxy()
            {
                reset();
            }

            void reset()
            {
                if( NULL != m_ArtQuota )
                {
                    delete m_ArtQuota;
                    m_ArtQuota = 0;
                }
                m_SearchRegistration = false;
            }

            void create( pxArticleQuota* articleQuota )
            {
                m_ArtQuota = new pxArticleQuota( *articleQuota );
            }

            void set( pxArticleQuota* articleQuota )
            {
                m_ArtQuota = articleQuota;
            }

            pxArticleQuota* get()
            {
                return m_ArtQuota;
            }

            void registerSearch()
            {
                m_SearchRegistration = true;
            }

            bool isSearchRegistered() const
            {
                return m_SearchRegistration;
            }


        private:
            pxArticleQuota* m_ArtQuota;
            bool            m_SearchRegistration;
        };

        ArticleQuotaProxy m_ArticleQuota;

        pxVerbund::subsequentDelivery::pxDeliveryPosList* AuxDelList_;          // link to aux delivery pos. list
        pxVartikelLokalList* AuxStoreLocList_;   // link to ibt artikellokal list
        pxItemDiscountList*  ItemDiscountList_;  // link to Itemdiscount list (kdauftragposrab)
        pxKdAuftragPosRefundList* KdAuftragPosRefundList_;  // link to list for KdAuftragPosRefund entries (kdauftragposrefund)
        pxItemAttributes* ItemAttributes_;      // link to incoming Attributes
        pxTenderPos*      TenderPos_;            // link to TenderPos entry
        pxDiscountList*   ArtDiscountList_;      // link to Article DiscountList(table discount)
        pxOrderPosCalcMode*   OrderPosCalcMode_; // link to table entry KDAUFTRPOSRECHART
        pxOrderPosPromoList* OrderPosPromoList_;  // link to list of kdauftragpospromo
        pxPromoCollectList*  PromoCollectList_;   // pointer PromoCollectList(BG)

        pxGenericOrderRemarkList* GenericOrderRemarkList_;

        pxCustomerSurchargeList* CustomerSurchargeList_; // link to manufacturer related surcharge for customer (table 'customersurcharge')

        long             KdAuftragNr_;     // Kundenauftragsnummer
        long             PosNr_;           // Positionsnummer Kundenauftrag
        long             ArtikelNr_;       // Artikelnummer
        long             SubstProposalArticleNo_; // ArticleCode of substitution proposal
        ItemType         PosTyp_;          // Positions-Typ
        pxDeviceType     GeraetTyp_;       // Geraete-Typ (erfassendes Geraet)
        short            FehlerMenge_;     // Dafue-Fehler Menge
        ArticleState     FehlerArtikel_;   //              Artikel
        long             MengeBestellt_;   // Menge Bestellt
        long             MengeBestaetigt_; // Menge Bestaetigt
        long             MengeGeliefert_;  // Menge Geliefert
        long             MengeReserviert_; // Menge Reserviert
        long             MengeAbgebucht_;  // Menge Abgebucht
        long             MengeNatra_;      // Menge Naturalrabatt
        long             MengeNatraGrossH_;// Menge Naturalrabatt Grosshandel
        long             MengeNatraHerst_; // Menge Naturalrabatt Hersteller
        long             PurchaseRelevantQty_; // Menge Abverkaufswirksam für Einkauf
        nMoney           PreisEKApo_;      // Preis EK Apotheke
        nMoney           PreisVKApo_;      // Preis VK Apotheke
        nMoney           PreisEKApoNetto_; // Preis EK Apotheke Nettoaktion
        nMoney           PreisEKGrosso_;   // Preis EK Grosso
        nMoney           PreisEKGrossoNA_; // Preis EK Grosso Nettoaktion
        double           RabattFest_;      // Rabatt Fest in %
        nMoney           RabattFestDM_;    // Rabatt Fest in DM
        nString          Bemerkungen_;     // Bemerkungen
        nBitMap          ETPosSchalter_;   // ETab Bestellpos Kundenauftrag
        pxArtClass       ETArtKlasse_;     // Bit Map Artikel Klassifizierung
        pxArtFlags       ETArtSchalter_;   // Bit Map Artikel Schalter
        char             Zuzahlung_;       // Kz Zuzahlung
        int              Rabattfaehig_;    // Rabattfaehigkeit Hinweis
        long             ArtBestNachUpd_;     // Bestand nach Update
        long             UhrZeitBestNachUpd_; // Bestand nach Update Aenderzeit

        long             MengeVorausBezug_;   // Menge VorausBezug
        long             BatchPosNr_;         // Batch Posnumber
        long             WannenNr_;           // WannenNr
        char             BewegungsArt_;       // BewgungsArt
        double           SalesTaxRate_;       // MWST SATZ
        nString          KdAuftragBestellNr_; // KundenBestellNummer, Referenznummer
        char             CodeBlocage_;        // codeblocage(Fr)
        nMoney           PreisEKApoFree_;     // Preis EK Apotheke freier Preis
        long             LinkPosNr_;          // LinkPosNr
        PriceTypeEnum    PreisTyp_;           // PreisType(BG)
        long             ArticleNoPack_;      // Steller Pseudeoartikelnummer
        nMoney           PreisFaktur_;        // Invoice Price
        nMoney           PreisFakturCstGr12_; // Intermediate Invoice Price for calculation for customer group 12
        short            MaxTargetNo_;        // Max Zahlungsziel
        short            ContainerLevel_;     // Lagerebene Container
        nMoney           RefundValue_;    // Refund Value
        short            PromotionNo_;    // Promotion Number
        short            PromoTyp_;    // Promotion Typ
        short            CodeType_;    // Articlecodes  Typ
        nString          ArticleCode_;    // Articlecodes  Articlecode
        short            ProblemState_;    // ProblemState
        short            SubGeraetTyp_;    // SubGeraetTyp
        char             KzPriso_;          // Kennzeichen Privatsortiment
        short            BusinessTypeNo_;  // BusinessTypeNo(Ivrylab)
        nString          TourIdIBT_;      // Verbundtour
        short            IBTTourWeekDay_;  // Verbundtour WochenTag
        short            IBTType_;  // Verbundtype
        short            IBTTypeID_;          // Verbundtyp N-Level-Verbund
        nString          TourId_;         // Normaltourtour
        long             MengeBestelltOrg_;   // original Bestellmenge
        long             MengeBestelltNatra_; // original BestellmengeNatra
        tDiscountCategory NatraCategory_;
        nString          NatraPharmacyGroup_;


        long             MengeVerbund_;        // Menge im Verbund Geliefert
        long             MengeMoeglich_;       // Menge im Verbund moeglich
        long             MengeNLMoeglich_;    // Menge Nachlieferung moeglich
        long             MengeDispoMoeglich_; // Menge Dispo moeglich
        short            VerbundFilialNr_;     // Filiale von wo MengeVerbund

        bool             DispoMoeglich_;      // Kann besorgt werde Swiss special

        bool             QuotaExeeded_;       // artikel Kontigierung erreicht
        bool             RebateAccountExceeded_;  // rebate account exceeded on Ordertype NR(BG)
        bool             NoNarcoticsDiscAcc_;  // no narcotics in ordertype NR(BG)

        bool             ReleaseRestDelivery_; // Release reserved Quanty from a Restdelivery pos
        ItemSendStatusEnum SendeStatus_;        // Status auf VSE-Maschine
        bool             BookRestDelivery_;   // Restdelivery position
        long             ArtikelNrPassiv_;    // Nummer passiv verknuefter Artikel
        long             DiscountArticleNo_;  // Discount ArticleNo
        long             MengeNatraDiscountArticle_;   // Natra for Free Article
        nMoney           PreisAGP_;           // Preis AGP Schweiz
        double           DiscountValPctMan_;  // work Manuall Discountvaluepct
        nMoney           FixedPricePaymentterms_; // Fixed Price Paymentterms (Serbia)
        bool             ProFormaBooking_;  // proformabooking rules
        double           GrossProfitPctFV_;      // Rohertrag Freiverkauf
        double           DiscountValPctPromo_;   // work Discountvaluepct Promotion target
        nString          PharmacyGroupId_;       // work PharmacyGroupId Promotion target
        double           DiscountValPctProforma_; // work during Proforma calculation
        nString          XMLLinereference_;       // xml line referencenr(BG comes from Salesweb
        bool             CustomerSurchargeAdded_;   // if special customersurcharge was added to aep (ID218)
        double           CustomerSurcharge_;      // manufacturer related surcharge for customer

        bool             UpdateDebtlimitK2_;    // Update Debtlimit
        bool             UpdateDebtlimitK1_;    // Update Debtlimit
        bool             NotSaveDiscountList_;  // BG Performance tset code
        bool             IBTPosDayNightMerge_;  // FR DayNight Merge IBT Position
        bool             HigherConditionsAvailable_;  // show more conditions
        PriceTypeEnum    PreisTypSaved_;           // PreisTypSave(BG) SR-16052924

    libcsc::discount::OrderPositionDiscountListPtr  m_DiscountList;
    ArticleSubstitutionUtil*                        m_ArticleSubstitutionUtil;

    friend class      pxOrderItemList;
    friend class      pxOrder;

    libcsc::discount::TenderDiscountPtr     m_TenderDiscount;
    libcsc::ibt::IIbtRequestPtr             m_IbtRequest;
};


/*----------------------------------------------------------------------------*/
/*  Customer order item container class.                                      */
/*----------------------------------------------------------------------------*/
class pxOrderItemList : public nDListCollect, public nDBRecordSet
{
public:
    virtual           ~pxOrderItemList() {Clear();}
                      pxOrderItemList(pxOrder& Order);
                      pxOrderItemList(pxSession* session);

    void              Clear()       {nDBRecordSet::Clear();}
    pxSession*        Session()       { return (pxSession*) DataBase();}
    size_t            Select (const int c = cDEFAULT);
    size_t            Select (const long KdAuftragNr, const int c = cDEFAULT);
    bool              Find(const long ArtikelNr);
    pxOrderItem*      FindArticle(const long ArtikelNr, const PriceTypeEnum pricetyp = FREESALE_PRICE );
    pxOrderItem*      FindItemByArticleNo(const long ArtikelNr );
    pxOrderItem*      getItemInhibitManualUpdateByArticleNo(const long ArtikelNr );
    bool              FindPromotionNo(const long PromotionNo);
    pxOrderItem*      GetTargetDiscountArticle(const long ArtikelNr, const long PosNr = 0);
    int              CountTargetDiscountArticle(const long ArtikelNr);
    pxOrderItem*      GetItem( const long PosNr );
    pxOrderItem*      GetItemFromSplitIbtPos( const long PosNr );

    enum SortFields             // define list sort criteria
    {
        SortDefault     = -1,   // default : PosNr
        SortByPosNr     = 1,    // default : PosNr
        SortByArticleNo = 2     // ArtikelNr
    };

protected:
    virtual  int     EndBrowse(const int cursorid);
    virtual
    nCollectable*    AddToList(const void* record, const int row);
    virtual  int     GetNext(const void* record, const int cursorid);
    virtual  int     StartBrowse(const void* keys, const int cursorid);
    size_t           Select (tKDAUFTRAGPOS* p,  const int count = 10000 );

private:
    pxOrder* Order_;
    friend class pxOrderItemListIter;
};

class pxOrderItemListIter : public nDListCollectIter
{
public:
// constructors:
    pxOrderItemListIter(pxOrderItemList& list) : nDListCollectIter(list) {}
// destructor:
    virtual  ~pxOrderItemListIter() {}
};


#endif
