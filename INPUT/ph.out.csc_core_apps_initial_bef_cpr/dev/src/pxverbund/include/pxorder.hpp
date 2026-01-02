#ifndef PXORDER_HPP
#define PXORDER_HPP

#include "pxbase/pxrecord.hpp"
#include "types/pricetypeenum.inc"
#include "types/origintypeenum.inc"
#include "types/orderrelationnotypeenum.inc"
#include "types/splitttypeenum.inc"
#include <clock.hpp>
#include "pxorddef.h"
#include "pxdevicetypeenum.hpp"
#include "pxitem.hpp"
#include <cscorder/cscorderflags/icscorderflagsrepositoryptr.h>
#include <cscorder/cscorderflags/icscorderflagsptr.h>
#include <ibt/ibtrequest/iibtrequestrepositoryptr.h>
#include "ibtrequesthandler.h"
#include "pxorderentryparamptr.h"
#include "pxeventreason.hpp" // only needed for enum -> extract!
#include <liblockmanager/lockguard/ilockguardptr.h>
#include "tourinfo.hpp"
#include <cscordertype/icscordertypeptr.h>
#include "iordertypegetter.h"

class pxOrderRelationNoList;
class pxOrderPeriod;
class TourAssignmentUtil;
class pxPromotionQuotaCst;
class pxPromotionQuota;
class pxOrderCalcMode;
class pxOrderValues;
class pxValuesCollectList;
class pxBalanceCollectList;
class pxOrderDiscAccList;
class pxOrdTaxValues;
class pxTenderHead;
class pxCstDiscAccList;
class pxCstDiscAcc;
class pxRangeCollectList;
class pxRangeControl;
class pxRangeControlList;
class pxTextDoc;
class pxDiscount;
class pxDiscountList;
class pxTimeTypeList;
class pxSepOrderArtGroupList;
class pxCustRoute;
class pxCustRouteList;
class pxCustRouteWeekList;
class pxOrderValidTrans;
class pxSepOrderArtGroup;
class pxOrderList;
class pxItemDiscount;
class pxItemDiscountList;
class pxCustBase;
class pxOrderItemList;

namespace pxVerbund
{
    namespace subsequentDelivery
    {
        class pxDeliveryPos;
        class pxDeliveryPosList;
    }
}


class pxStockTrans;
class pxCommType;
class pxCustOrderType;
class pxCPValidityPeriodList;
class pxCPValidityPeriod;
class pxArtComPackList;
class pxKdAuftragDebtRel;
class pxDebitLimit;
class pxOrderItemTour;

struct tDISPOITEM;
struct tKDAUFTRAG;

class pxOrder : public pxDBRecord, public csc::pricing::IOrderTypeGetter
{
public:

    struct OrderItemCounts
    {
        OrderItemCounts()
        {
            NarcoticLines = 0;
            CoolChainLines = 0;
            CoolBelow8Lines = 0;
            CoolBelow20Lines = 0;
            DifferingTourLines = 0;
        }

        long NarcoticLines;
        long CoolChainLines;
        long CoolBelow8Lines;
        long CoolBelow20Lines;
        long DifferingTourLines;
    };

    enum OrderSendStatusEnum
    {
        // State definitions:
        cVSEnoTransmit = 0,              // 0 Caution: do NEVER change this value!!
        cVSEok,                          // 1 Order transmitted
        cVSEPosErr,                      // 2 Order transmitted, error in positions
        cVSEKdeErr,                      // 3 Order transmitted, error no customer
        cVSETidErr,                      // 4 Order transmitted, error no tourid found
        cVSEKdbErr,                      // 5 Order already on VSE
        cVSEAnyErr,                      // 6 Order transmitted, unknown error
        cVSECoCorrection,                // 7 kommikerrekturen
        cVSEDelDeliveryNoTransmit = 10  // 10 Order is Delayed Deliverable, do not transmit
    };

    enum TypeOfInfoOrder
    {
        INFO_ORDER_TYPE_DEFAULT,                    // 0 = Normal info order
        INFO_ORDER_TYPE_PROFORMA                    // 1 = Proforma order
    };


    static const long PSEUDO_ORDER_NUMBER = 9999999;


    // Constructors:
    pxOrder(pxSession* session, pxCustBase& customer);
    pxOrder(pxSession* session, pxCustBase* customer, const enum pxOrder::TypeOfInfoOrder type/* = INFO_ORDER_TYPE_DEFAULT*/);

    // Read constructors:
    pxOrder(pxSession* session, long KdAuftragNr, DBAccessMode mode);

    // destructor:
    virtual  ~pxOrder();

    virtual bool isNormal();
    virtual bool isTenderInvoice();

    /*@DS PUBLIC MEMBER FUNCTIONS */
    int              OpenOrder(DBAccessMode mode = cDBOPEN_READONLY, pxCustBase* customer = NULL);
    int              OpenInfo();
    int              OpenProforma();
    int              Close(Order::States s = Order::LeaveAsIs, Order::CloseArgs a = Order::cClose_Nohandle);
    int              AAClose(Order::States s = Order::LeaveAsIs, Order::CloseArgs a = Order::cClose_Nohandle);
    int              CancelOrder(pxDeviceType t, Order::CancelArgs a = Order::cCancel_Nohandle);
    int              EstimateDepartureTime(char* time);  //time in HH:MM
    int              SetOrderCompleted();

    bool             lock4Corpha();
    void             unlock4Corpha();

    MessageCodeEnum  isBatchValid(const nString& batchNr, bool isFixBatch);


    //  Overloaded order item entry:

    pxOrderItem* NewOrderItem_02(long ArtikelNr,
        long MengeBestellt,
        long MengeNatra,
        long MengeNachfrage,
        short PromoTyp = 0,
        short PromotionNo = 0,
        PriceTypeEnum  pricetype = FREESALE_PRICE,
        pxOrderItem::BookingType t = pxOrderItem::BookingTypeDefault,
        pxOrderItem::ItemType PosTyp = pxOrderItem::TypeProductStocked,
        int flags = bPOST_DEFAULT);

    pxOrderItem* NewOrderItem_03(long ArtikelNr,
        long MengeBestellt,
        long MengeNatra,
        long MengeNachfrage,
        PriceTypeEnum pricetype,
        pxOrderItem::BookingType t,
        pxOrderItem::ItemType PosTyp,
        int flags = bPOST_DEFAULT,
        long MengeNatraBestellt = 0);

    // MengeNatra = 0
    // MengeNachfrage = 0
    // pricetype = FREESALE_PRICE
    // t = pxOrderItem::BookingTypeDefault
    // PosTyp = pxOrderItem::TypeProductStocked
    // flags = bPOST_AUTO_ITEM | bPOST_IGN_LACK
    pxOrderItem* NewOrderItem_03_DefaultWithAutoItemAndIgnLack(long ArtikelNr, long MengeBestellt);

    // t = pxOrderItem::BookingTypeDefault
    // PosTyp = pxOrderItem::TypeProductStocked
    // flags = bPOST_RANGEARTICLE
    pxOrderItem* NewOrderItem_03_RangeArticle(
        long ArtikelNr,
        long MengeBestellt,
        long MengeNatra,
        long MengeNachfrage,
        PriceTypeEnum pricetype);

    // MengeBestellt = 0L
    // MengeNachfrage = 0L
    // t = pxOrderItem::BookingTypeDefault
    // PosTyp = pxOrderItem::TypeProductStocked
    // flags = bPOST_RANGEARTICLE
    pxOrderItem* NewOrderItem_03_NatraWithRangeArticle(long ArtikelNr, long MengeNatra, PriceTypeEnum pricetype);

    pxOrderItem* NewOrderItem_04(long ArtikelNr,
        long MengeBestellt,
        long MengeNatra = 0,
        long MengeNachfrage = -1,
        double DiscountValPctMan = 0.0,
        PriceTypeEnum  pricetype = FREESALE_PRICE,
        pxOrderItem::BookingType t = pxOrderItem::BookingTypeDefault,
        pxOrderItem::ItemType PosTyp = pxOrderItem::TypeProductStocked,
        int flags = bPOST_DEFAULT,
        long MengeNatraBestellt = 0);

    pxOrderItem* NewOrderItem_05(long ArtikelNr,
        long MengeBestellt,
        long MengeNatra = 0,
        long MengeNachfrage = -1,
        nMoney EKApoFreePrice = 0.0,
        PriceTypeEnum  pricetype = FREESALE_PRICE,
        pxOrderItem::BookingType t = pxOrderItem::BookingTypeDefault,
        pxOrderItem::ItemType PosTyp = pxOrderItem::TypeProductStocked,
        int flags = bPOST_DEFAULT,
        long MengeNatraBestellt = 0);

    pxOrderItem* NewOrderItem_06(long ArtikelNr,
        long MengeBestellt,
        long MengeNatra = 0,
        long MengeNachfrage = -1,
        nMoney EKApoFreePrice = 0.0,
        double DiscountValPctMan = 0.0,
        PriceTypeEnum  pricetype = FREESALE_PRICE,
        pxOrderItem::BookingType t = pxOrderItem::BookingTypeDefault,
        pxOrderItem::ItemType PosTyp = pxOrderItem::TypeProductStocked,
        int flags = bPOST_DEFAULT,
        long MengeNatraBestellt = 0);

    pxOrderItem* NewOrderItem_07(long ArtikelNr,
        long MengeBestellt,
        long MengeNatra = 0,
        long BatchOrderNo = 0,
        long BatchPosNo = 0,
        long MengeNachfrage = -1,
        PriceTypeEnum  pricetype = FREESALE_PRICE,
        pxOrderItem::BookingType t = pxOrderItem::BookingTypeDefault,
        pxOrderItem::ItemType PosTyp = pxOrderItem::TypeProductStocked,
        int flags = bPOST_DEFAULT);

    pxOrderItem* NewOrderItem_08(long ArtikelNr,
        long MengeBestellt,
        short VerbundFiliale,
        long MengeNatra = 0,
        long MengeNachfrage = -1,
        PriceTypeEnum  pricetype = FREESALE_PRICE,
        pxOrderItem::BookingType t = pxOrderItem::BookingTypeDefault,
        pxOrderItem::ItemType PosTyp = pxOrderItem::TypeProductStocked,
        int flags = bPOST_DEFAULT);

    pxOrderItem* NewOrderItem_09(long ArtikelNr,
        long MengeBestellt,
        short VerbundFiliale,
        nMoney EKApoFreePrice,
        long MengeNatra = 0,
        long MengeNachfrage = -1,
        PriceTypeEnum  pricetype = FREESALE_PRICE,
        pxOrderItem::BookingType t = pxOrderItem::BookingTypeDefault,
        pxOrderItem::ItemType PosTyp = pxOrderItem::TypeProductStocked,
        int flags = bPOST_DEFAULT);

    pxOrderItem* NewOrderItem_10(long    ArtikelNr,
        long       MengeBestellt,
        long       MengeNatra,
        double     Barrabatt,
        short      PromoType,
        short      PromotionNo,
        nString& PharmacyGroupId,
        PriceTypeEnum pricetype = FREESALE_PRICE);

    pxOrderItem* NewOrderItem_11(long    ArtikelNr,
        long       MengeBestellt,
        long       MengeNatra,
        double     Barrabatt,
        short      PromoType,
        short      PromotionNo,
        nString& PharmacyGroupId,
        long      DiscountGrpNo,
        long      BaseQty,
        double   BaseValue,
        long      CustomerNo,
        PriceTypeEnum  pricetype = FREESALE_PRICE);

    pxOrderItem* NewOrderItemRemarks(const long ProductId,
        const long QOrdered);

    pxOrderItem* NewOrderItemInfo(const long ProductId,
        const long QOrdered);

    pxOrderItem* NewOrderItem_12(const long  ArticleNo,
        const long QOrdered,
        const basar::VarString& XMLOrderReference,
        const basar::VarString& XMLLinereference,
        const bool RemAuxDel,
        const bool RemRestDel,
        const bool RemDispo,
        const bool RemPartDel,
        const PriceTypeEnum RemPriceType,
        const basar::VarString& Batch = "",
        const bool IsFixBatch = false);

    pxOrderItem* NewOrderItem_13(const long ArticleNo,
        const long QOrdered,
        const basar::VarString& XMLOrderReference,
        const basar::VarString& XMLLinereference,
        const bool RemAuxDel,
        const bool RemRestDel,
        const bool RemDispo,
        const bool RemPartDel,
        const PriceTypeEnum RemPriceType,
        const nMoney& PreisEKApo,
        const nMoney& PreisEKApoFree,
        const double DiscountValPctMan,
        const long QtyRebateInKind = 0,
        const basar::VarString& Batch = "",
        const bool IsFixBatch = false);

    pxOrderItem* NewOrderItem_15(tDISPOITEM& DispoItem, pxOrderItem::BookingType t = pxOrderItem::BookingTypeDefault, bool addSubSequent = true);

    pxOrderItem* NewOrderItem_15_DefaultWithAutoItemOCP(double freightCost);

    pxOrderItem* NewOrderTextItem(const nString& Text, const long MengeBestellt);

    pxOrderItem* ItemQuery(const long ProductId, const long QuanOrdered);

    pxOrderItem* NewOrderItem_16(pxVerbund::subsequentDelivery::pxDeliveryPos* delpos, pxOrderItem::BookingType t = pxOrderItem::BookingTypeDefault);

    pxOrderItem* CopyOrderItem(pxOrderItem* item, pxOrderItem::BookingType t, SplittTypeEnum s);

    pxOrderItem* CalcOrderItem(long ArtikelNr, long MengeBestellt,
        long MengeNatra = 0, long MengeNachfrage = -1,
        PriceTypeEnum  pricetype = FREESALE_PRICE,
        pxOrderItem::BookingType t =
        pxOrderItem::BookingTypeDefault,
        pxOrderItem::ItemType PosTyp =
        pxOrderItem::TypeProductStocked,
        int flags = bPOST_DEFAULT);

    pxOrderItem* ItemDiscountInfo(long ArtikelNr, PriceTypeEnum  pricetype = FREESALE_PRICE);

    pxOrderItem* NewOrderItemProforma(long ArtikelNr, long MengeBestellt,
        long MengeNatra = 0, long MengeNachfrage = -1,
        PriceTypeEnum  pricetype = FREESALE_PRICE,
        pxOrderItem::BookingType t =
        pxOrderItem::BookingTypeDefault,
        pxOrderItem::ItemType PosTyp =
        pxOrderItem::TypeProductStocked,
        int flags = bPOST_DEFAULT);

    // Menge = 0L
    // MengeNachfrage = 0L
    // t = pxOrderItem::BookingTypeDefault
    // PosTyp = pxOrderItem::TypeProductStocked,
    // flags = bPOST_RANGEARTICLE
    pxOrderItem* NewOrderItemProforma_NatraWithRangeArticle(long ArtikelNr, long MengeNatra, PriceTypeEnum pricetype);

    pxOrderItem* NewOrderTemporaryItem(long ArtikelNr, long MengeBestellt,
        long      MengeNatra,
        double   Barrabatt,
        short     PromoType,
        short     PromotionNo,
        nString& PharmacyGroupId,
        PriceTypeEnum  pricetype = FREESALE_PRICE,
        pxOrderItem::BookingType t =
        pxOrderItem::BookingTypeDefault,
        pxOrderItem::ItemType PosTyp =
        pxOrderItem::TypeProductStocked,
        int flags = bPOST_DEFAULT);

    // kdverbund legacy
    bool                        hasAtLeastOneCompletedIbtBooking();
    IbtRequestHandler   getIbtRequestHandler();
    IbtRequestHandler   m_IbtRequestHandler;


public:
    libcsc::ibt::IIbtRequestRepositoryPtr                           getIbtRequestRepository() const;

public:
    //  Queries:
    int               CountItems(int what, long lparm);
    int               CountDayNightMergePositions();
    int               CountSeparatedPositions();
    int               CountPriceTypeItems(PriceTypeEnum priceType);
    int               CountIBTDestinationBranchItems(const short destBranchno);
    int               countPriceTypeTargetItems(PriceTypeEnum priceType);
    int               countPriceTypeProductPromotionItems(PriceTypeEnum priceType);

    short             CloseOptions() { return CloseOptions_; }
    pxCustBase* Customer();
    pxCustBase* ShuttleCustomer(const short BranchNo);
    const nTime& DateTimeCreated();
    pxOrderItemList* ItemList();
    pxOrderItemList* ItemListProforma(const short pricetype = -1);
    pxOrderItemList* ItemListTemporary(const short pricetype = -1);
    pxTextDoc* HeadText();
    pxTextDoc* TailText();
    pxOrderEntryParamPtr   Param();
    pxRangeCollectList* RangeCollectList();
    pxTimeTypeList* StockReservTimeList();
    pxSepOrderArtGroupList* SepOrderArtGroupList();
    pxCstDiscAccList* CstDiscountAccount();
    pxTenderHead* TenderHead();
    pxOrdTaxValues* OrdTaxValues();
    pxOrderDiscAccList* OrderDiscAccList();
    pxBalanceCollectList* BalanceCollectList();
    pxValuesCollectList* ValuesCollectList(); // collection of order values
    pxOrderValues* OrderValues();         // Pointer KDAUFTRAGWERTE
    pxOrderCalcMode* OrderCalcMode();       // Pointer KDAUFTRAGRECHART
    pxDiscountList* OrderPosDiscountList(); // BG Performance test code
    int                DeleteOrderPosDiscountList(); // BG Performance test code
    int                DeleteOrderValues();          // BG for update K1/k2

    const pxStockTrans& StockTrans() { return *StockTrans_; }
    const pxCommType& CommType() { return *CommType_; }

    const pxCustOrderType& OrderType();         // implemented in pxorder.cpp

    const pxOrderItem* ItemQuery() { return ItemQuery_; }

    bool              isProductAvailabilityRequest() const;

    long              KdAuftragNr()       const { return KdAuftragNr_; }
    const nBitMap& State()             const { return State_; }
    long              IDFNr()             const { return IDFNr_; }
    const nString& GeraetName()        const { return GeraetName_; }
    const nString& TourIdAlt()         const { return TourIdAlt_; }
    long              RechnungNr()        const { return RechnungNr_; }
    long              PersonalNr()        const { return PersonalNr_; }
    short             FilialNr();
    short             OrderFilialNr()     const { return FilialNr_; }
    const nBitMap& ETAuftrag()         const { return ETAuftragSchalter_; }
    const nString& KdAuftragArt()      const { return KdAuftragArt_; }
    char              KoArt()             const { return KoArt_; }
    char              BuchArt()           const { return BuchArt_; }
    const nDate& DatumValuta()       const { return DatumValuta_; }
    const nMoney& WertAuftrag()       const { return WertAuftrag_; }
    const nMoney& WertLieferung()     const { return WertLieferung_; }
    const nMoney& WertZeilen()        const { return WertZeilen_; }
    long              AnzPos()            const { return AnzPos_; }
    long              AnzPosOB()          const { return AnzPosOB_; }
    long              AnzPosDafue()       const { return AnzPosDafue_; }
    long              AnzPosDafueFehler() const { return AnzPosDafueFehler_; }
    long              AnzAlphaText()      const { return AnzAlphaText_; }
    long              AnzBTM()            const { return AnzBTM_; }
    double            RabattBarProz()     const { return RabattBarProz_; }
    const nClock& EndAM()             const { return ZeitEndeAM_; }
    const nClock& EndPM()             const { return ZeitEndePM_; }
    OriginTypeEnum    BatchSchreiben()    const { return BatchSchreiben_; }

    short             HerkunftFiliale()   const { return HerkunftFiliale_; }
    const nString& NaechsteTour()      const { return NaechsteTour_; }
    const nString& LetzteTour()        const { return LetzteTour_; }
    const nString& Bemerkungen()       const { return Bemerkungen_; }
    long              DafueAuftragNr()    const { return DafueAuftragNr_; }
    const nString& DafueGeraeteName()  const { return DafueGeraeteName_; }
    long              KundenNr()          const { return KundenNr_; }
    short             Vertriebszentrum()  const { return VertriebsZentrumNr_; }
    OrderSendStatusEnum SendeStatus()     const { return SendeStatus_; }
    long              VSEAuftragNr()      const { return KdAuftragNrFiliale_; }
    const nBitMap& RCEntryDeffered()   const { return RCEntryDeffered_; }
    const nDate& DatumAuslieferung() const { return DatumAuslieferung_; }
    long              KdAuftragNrOrg()    const { return KdAuftragNrOrg_; }
    const nDate& DatumOrg()          const { return DatumOrg_; }
    long              BatchAuftragNr()    const { return BatchAuftragNr_; }
    char              KzRestored()        const { return KzRestored_; }
    const nString& ReferenceNr()       const { return ReferenceNr_; }
    const nString& SubOrderType()      const { return SubOrderType_; }
    const nString& PaymentTerm()       const { return PaymentTerm_; }
    short             AnzAuf()            const { return AnzAuf_; }
    const nDate& DatumValutaBatch()  const { return DatumValutaBatch_; }
    short             ValutaMonAuto()     const { return ValutaMonAuto_; }
    short             ValutaMonManuell()  const { return ValutaMonManuell_; }
    long              TenderNo()          const { return TenderNo_; }
    const nDate& DatumVersand()      const { return DatumVersand_; }
    const nDate& DatumBTM()          const { return DatumBTM_; }
    const nString& BTMFormularNr()     const { return BTMFormularNr_; }
    const nMoney& WertNetto()         const { return WertNetto_; }
    const nMoney& WertRabatt()        const { return WertRabatt_; }
    const nString& InvoiceNumber()     const { return InvoiceNumber_; }
    const nDate& PaymentDate()       const { return PaymentDate_; }
    char              PaymentType()       const { return PaymentType_; }
    long              DriverID()          const { return DriverID_; }
    const nString& XMLReferenceNo()    const { return XMLReferenceNo_; }
    long              LogisticVolume()    const { return LogisticVolume_; }
    const nString& OrderLabel()        const { return OrderLabel_; }
    short             DPODays()           const { return DPODays_; }
    long              OrderPeriodID()     const { return OrderPeriodID_; }

    //  Bulgarien application Rebate order
    long              ROMainCstNo()       const { return ROMainCstNo_; }
    const nDate& RODateFrom()        const { return RODateFrom_; }
    const nDate& RODateTo()          const { return RODateTo_; }
    const nMoney& SaveOrderValueDL()  const { return SaveOrderValueDL_; }
    long              KdAuftragNrOrgRO()  const { return KdAuftragNrOrgRO_; }

    int              ApprovalsNeeded()    const { return ApprovalsNeeded_; }
    bool             IsCremaReleased()    const { return IsReleased_; }
    bool             IsDiscussionNeeded() const { return DiscussionNeeded_; }


    bool    isArticlePartOfTender(const long articleno);
    bool    IsAvailableForOrderConsolidation();
    bool    IsInfoOrder() const { return KdAuftragNr_ == pxOrder::PSEUDO_ORDER_NUMBER; }
    bool    IsBGInfoOrder() const { return BGInfoOrder_; }
    bool    IsCollectiveOrderDiscountable();
    bool    IsCremaInsert(const nString& RelUser);
    bool    IsCremaOrderApproved(Order::CloseType closeType, bool insert, bool updateCounterOnUpdate, short changeValue);
    bool    IsDiscountable();
    bool    IsHoldOrder() { return IsNOTCLOSEORDER(); }
    bool    isMSV3Order() const;
    bool    IsMSV3InfoOrder() const;
    bool    IsNoCreditLimitCheck() { return NoCreditLimitCheck_; }
    bool    IsNoDebtLimitCheck() { return NoDebtLimitCheck_; }
    bool    isNonSatisfiedIBTPosition(pxOrderItem* item);
    bool    IsOpiateSplitt();
    bool    isOrderLabelEqual(nString orderlabel) const;
    bool    isProformaInvoiceAllowed();
    bool    IsPseudoLock() const { return PseudoLock_; }
    bool    isSalesWebOrder();
    bool    isTenderOrder();
    bool    IsValidRoute(const nString& RouteId);
    bool    IsValidRouteForOrderClose(const nString& RouteId);
    bool    IsOCPOrder();
    bool    getOCPOrderInfo(basar::VarString& channelId, int& offerID, double& freightCost, double& carriageFree);
    bool    getOCPOrderValue(double& value);



    OrderItemCounts     GetOrderItemCounts();

    libcsc::cscordertype::ICSCOrderTypePtr  getCscOrderType();

    bool              closeIBTAtOnce();

    //  Field Updates:
    virtual  long    SubAnzPosDafue(const long q);
    void              Bemerkungen(const nString& s)
    {
        Bemerkungen_ = s; SetDirty();
    }
    void              KdAuftragNrOrg(const long kdauftragnr)
    {
        KdAuftragNrOrg_ = kdauftragnr;
    }
    void              DatumOrg(const nDate& date)
    {
        DatumOrg_ = date;
    }
    void              DatumAuslieferung(const nDate& date)
    {
        DatumAuslieferung_ = date;
    }
    void              BTMFormularNr(const nString& BTMFormularNr)
    {
        BTMFormularNr_ = BTMFormularNr;
    }
    void              DatumBTM(const nDate& date)
    {
        DatumBTM_ = date;
    }
    void              DatumVersand(const nDate& date)
    {
        DatumVersand_ = date;
    }
    int              SetDatumAuslieferung(const long date);
    void              SetBuchArt(const char ba)
    {
        BuchArt_ = ba;
    }
    void              SetBatchOrderNr(long batchordernr)
    {
        BatchAuftragNr_ = batchordernr;
    }
    void              SetReferenceNr(const char* num)
    {
        ReferenceNr_ = num;
    }
    void              SetSubOrderType(const nString& subordertype)
    {
        SubOrderType_ = subordertype;
    }
    void              SetPaymentTerm(const nString& paymentterm)
    {
        PaymentTerm_ = paymentterm;
    }
    void              DoNoCustDestruct()
    {
        SetNoCustDestruct();
    }
    void              IncreaseAnzAuf()
    {
        AnzAuf_++;
    }
    void              SetDatumValutaBatch(const nDate& date)
    {
        DatumValutaBatch_ = date;
    }
    void              SetDatumValuta(const nDate& date)
    {
        DatumValuta_ = date;
    }
    void              SetValutaMonManuell(const short days)
    {
        ValutaMonManuell_ = days;
    }
    void              SetTenderNo(const long TenderNo);
    void              SetOrderRemarkText(const nString& RemarkText);
    void              SetBTMFormularNr(const long date, const nString& BTMFormularNr)
    {
        DatumBTM_ = nDate(date); BTMFormularNr_ = BTMFormularNr;
    }
    void              SetROMainCstNo(const long cstno)
    {
        ROMainCstNo_ = cstno;
    }
    void              SetRODateFrom(const long datefrom)
    {
        RODateFrom_ = nDate(datefrom);
    }
    void              SetRODateTo(const long dateto)
    {
        RODateTo_ = nDate(dateto);
    }
    void              SetROChain(const short ROChain)
    {
        ROChain_ = ROChain;
    }
    void              SetChangedToCashOrder()
    {
        ChangedToCashOrder_ = true;
    }
    bool              IsChangedToCashOrder()
    {
        return ChangedToCashOrder_;
    }
    void              SetRechnungNr(const long RechnungNr)
    {
        RechnungNr_ = RechnungNr; SetDirty();
    }
    void              SetInvoiceNumber(const basar::VarString& InvoiceNumber)
    {
        InvoiceNumber_ = InvoiceNumber.c_str(); SetDirty();
    }
    void              SetPaymentDate(const nDate& date)
    {
        PaymentDate_ = date;
    }
    void              SetPaymentType(const char type)
    {
        PaymentType_ = type;
    }
    void              SetDeliveryDatePreset()
    {
        DeliveryDatePreset_ = true;
    }
    bool              IsDeliveryDatePreset()
    {
        return DeliveryDatePreset_;
    }
    void              SetUpdateDebtlimitK2()
    {
        UpdateDebtlimitK2_ = true;
    }
    bool              IsUpdateDebtlimitK2()
    {
        return UpdateDebtlimitK2_;
    }
    void              ClearUpdateDebtlimitK2()
    {
        UpdateDebtlimitK2_ = false;
    }
    void              SetUpdateDebtlimitK1()
    {
        UpdateDebtlimitK1_ = true;
    }
    bool              IsUpdateDebtlimitK1()
    {
        return UpdateDebtlimitK1_;
    }
    void              ClearUpdateDebtlimitK1()
    {
        UpdateDebtlimitK1_ = false;
    }
    void              SetXMLReferenceNo(const nString& RefNo)
    {
        XMLReferenceNo_ = RefNo; SetDirty();
    }
    void              SetKdAuftragNrOrgRO(const long KdAuftragNrOrgRO)
    {
        KdAuftragNrOrgRO_ = KdAuftragNrOrgRO;
    }
    void              SetTourId(const nString& tourid)
    {
        OrderTourId_ = tourid; SetDirty();
    }
    void              SetOrderLabel(const nString& OrderLabel)
    {
        OrderLabel_ = OrderLabel; SetDirty();
    }
    void              SetOrderPeriodID(const long orderperiodid)
    {
        OrderPeriodID_ = orderperiodid; SetDirty();
    }

    void              SetBatchAuftragNr(long batchordernr)
    {
        BatchAuftragNr_ = batchordernr; SetDirty();
    }
    int               SetOrderToCash();
    int               SetOrderToCashAe();
    bool              isCashOrder()
    {
        return PaymentType_ == 'C';
    }
    int              SetOrderWithTimeForPayment();

    bool              isOrderWithTimeForPayment()
    {
        return PaymentType_ == 'Z';
    }

    void              SetDefaultOrderLabel();




    bool              hasDefaultOrderLabel();
    bool              checkOrderEntryRestrictions(const long ManufacturerNo);

    //  VSE State  / ordernr
    void              SendeStatus(OrderSendStatusEnum s)
    {
        SendeStatus_ = s; SetDirty();
    }
    void              OrderStatus(Order::States s = Order::LeaveAsIs);
    void              VSEAuftragNr(long n)
    {
        KdAuftragNrFiliale_ = n;
    }
    void              VSEPut();

    // Auftragstext/Bemerkungen ändern.

    void              BatchSchreiben(OriginTypeEnum batch)
    {
        BatchSchreiben_ = batch;
    }
    // Batch-Schreib-Modus setzen.

    void              CloseOptions(short closeoptions)
    {
        CloseOptions_ = closeoptions;
    }
    // Close-Options setzen.

    void              HerkunftFiliale(short filiale)
    {
        HerkunftFiliale_ = filiale;
    }
    // HerkunftFiliale_ setzen.

    void              DafueAuftragNr(const long n)
    {
        DafueAuftragNr_ = n;
    }
    // Kundeneigene Auftragsnummer setzen.
    void              SetHoldOrder()
    {
        SetNOTCLOSEORDER();
    }




    void              SetNoDebtLimitCheck() { NoDebtLimitCheck_ = true; }



    bool              WasOrderReleased();
    pxEventReason::EventCodes EventCode() { return EventCode_; }
    void              SetEventCode(const pxEventReason::EventCodes code) { EventCode_ = code; }
    void              SetNoCreditLimitCheck() { NoCreditLimitCheck_ = true; }
    void              ClearNoCreditLimitCheck() { NoCreditLimitCheck_ = false; }

    bool              DeleteCremaMail(long orderNo, short branchNo);

    bool              Croatia();
    bool              Austria();
    bool              Swiss();
    bool              Serbia();
    bool              Bulgaria();
    bool              France();
    bool              German();



    int               CountCoolerSplitt();
    int               CountNoSplittPositions();

    bool              hasToBeCheckEncloserScale();

    //  Get next valid TourId from DatumAuslieferung
    int              SetNextValidRoute(const nString& RouteId);

    //  Get next valid TourId for the actual day depending on durchlaufzeit
    int              SetNextValidRouteNormal(const nString& RouteId);

    int               OrderType(const nString& KdAuftragArtS, const char KoArt, const char BuchArt);
    // Setzen/Ändern von Auftragart, Kommi-Art und Buchungsart.
    int               OrderType(const nString& KdAuftragArtS, const char KoArt, const char BuchArt, const nString& SubOrdertype);
    // Setzen/Ändern von Auftragart, Kommi-Art und Buchungsart.

    int               ChangeCustomer(long NewIDFNr, short BranchNo);
    // Setzen/Ändern von kundennummer + (evtl.) filiale.

    // Book FreeArticle Position or a Package of Positions
    int               RangeDiscountArticle(const long ArticleNo, const long Qty, const short DiscountSpec,
        const bool internalDiscountFlag, const tDiscountCategory category, const nString& pharmacyGroup);

    // Book FreeArticle Position or a Package of Positions (BG Version)
    int               TargetDiscountArticle(pxRangeControl* rclentry, pxDiscount* discentry);
    // Martk  Targetpromotion Positions whit Problemstate 1 (BG Version)
    int               TargetDiscountArticleProforma(pxRangeControl* rclentry, pxDiscount* discentry);
    // Martk  Targetpromotion Positions whit Problemstate 1 (BG Version)
    int               TargetPositionsProblemState(pxRangeControl* rclentry, short ProblemSate);

    // Assign refundvalue on Tartget header (BG Version)
    int               AssignTargetRefundValue(pxRangeControl* rclentry);

    // Assign refundvalue on Tartget header for manually booked Targets(BG Version)
    int               AssignOrderEntryTargetRefundValue();
    // Assign refundvalue on Tartget header is called from AssignOrderEntryTargetRefundValue (BG Version)
    int               AssignTargetRefundValue(short PromtionNo);

    // Assign DiscountValPctProforma for each position within ths order (BG Version)
    int               AssignPosDiscountValPctProforma(pxItemDiscountList* posrablist);

    // Assign DiscountValPctProforma for each position within ths order to ItemListProforma_ (BG Version)
    int               AssignPosDiscountValPctProforma();

    // Delete promotioncollectlist on each Positions (BG Version)
    int               DeleteItemPromoCollectList();

    // Book ArticleCompackMenbers
    int               BookArtComPackMembers(pxOrderItem* item);

    // Book TenderProgress
    int               BookTenderProgress(pxOrderItem* item);

    // Calculate Promotion Quota  (Bulgarion Aplication
    int               CalcPromotionQuota(pxOrderItem* item);

    // Book FreeArticle Position
    int               BookDiscountArticle(pxOrderItem* item);

    // Erase Orderpositiondiscountentry
    int               EraseOrderpositionDiscountEntry(pxOrderItem* item);

    // Book DayNichtMergePosition
    pxOrderItem* bookDayNightMergePosition(pxOrderItem* item, const long QtyOrdered, const long QtyIBT);

    // CleanUp DayNichtMergePosition
    int               cleanupDayNightMergePosition(pxOrderItem* item, const nString& KdAuftragNr);

    // get DayNightMerge ibtposition  departure date YYYYMMDD
    long              getDayNightMergeIBTPositionDepartureDate(const short destBranchno);

    // Book FreeArticle Position
    int               SplittPartialIBTPosition(pxOrderItem* item);

    // Get Promotion Quota Customer depending on Promo Quota Branch  (Bulgarion Aplication
    pxPromotionQuotaCst* GetEntryPromotionQuotaCst(pxPromotionQuota* PromoQuotaBranch, const long Qty = 0);

    // Rebook complete order at order close time on delayed delivered orders. Bulgarion Aplication)
    int                ReCalculateOrder();

    // Close TenderPos
    int               CloseTenderPos();

    // Close TenderHead
    int               CloseTenderHead();

    // Show CreditLimit
    nMoney             ShowCreditLimit();
    nMoney             ShowCreditLimit1();
    nMoney             ShowCreditLimit2();

    // Count of No Transfer To Pharmos Positions
    long              CountNoTransferPositions();

    // Show Proformaivoice Values (Bulgarien application)
    int               ProformaInvoice(const short pricetype = -1);
    int               BestTargetPromotion(long* PromotionNo);
    nMoney             ReCalcValuesProforma(pxItemDiscountList* discl);
    void              ReCalcValuesCollectList();
    void              ReCalcValuesOrderValues();
    nMoney             GetValueNetCash(const PriceTypeEnum pricetype);
    nMoney             GetValueSalesTax(const PriceTypeEnum pricetype);
    nMoney             CalcGrossShipValue();

    //  Some Methodes to handle CustomerDiscountAccount (Bulgarien application)
    nMoney            IncreaseCstDiscAcc(nMoney shipvalue, short TaxLevel);
    nMoney            DecreaseCstDiscAcc(nMoney shipvalue, short TaxLevel);
    nMoney            SetCurrentCstDiscAccBalance(short TaxLevel);
    nMoney            GetOrderValueCstDiscAcc();
    int              UpdateCustomerDebtlimitK2();
    int              UpdateCustomerDebtlimitK1();
    nMoney            OrderValuesToCustomerDebtlimitK2();
    nMoney            OrderValuesToCustomerDebtlimitK1();
    int              SaveOrderValuesDebtLimit();
    nMoney            GetOrderValuesDebtlimit();
    int              CompleteCustomerDebtlimitK2();
    int              CompleteCustomerDebtlimitK1();
    nMoney            GetOrderValue(const PriceTypeEnum pricetype);
    nMoney            GetOrderValueListFiveMembers();
    nMoney            UndoCustomerDebtlimitK2();
    nMoney            UndoCustomerDebtlimitK1();

    int              CloseCstDiscAccBalance();
    int              LockCstDiscAccEntries();
    int              UnLockCstDiscAccEntries();
    int              ReCalcSumCstDiscAccBalances();
    long             GetCstDiscAccMainCstNo();
    int              ShrinkCstDiscountAccount(const long CustomerNo);
    int              SumCstDiscAccBalances();
    double          GetCstDiscAccBalance(const short TaxLevel);
    int              RemoveDiscAccEntries();
    int              CancelRebateOrder();
    int              UndoCreditDayTurnOver(nMoney orderValue);
    int              UndoCreditDayTurnOver();
    int              RedoCreditDayTurnOver(nMoney orderValue);
    int              CancelCurrentCreditDayTurnOver();
    nMoney           checkCreditLimitOverflow();
    void             injectPreisTypSavedForAllItemsInItemlist();

    int              CancelDebtLimitSumDayTurnOver();
    int              RevertCancelDebtLimitSumDayTurnOver();
    double          CalcAepInvoiceValue(double Aep, double Percentage);
    int              CloseOrderCalcMode();
    int              SyncCstDiscAccVse();
    int              ConfirmOrderDiscAcc();
    int              ChangeUsageCstDiscAcc(const short Branchno, const long CustomerNo,
        const long InvoiceDate, const nString& InvoiceNo,
        const nString& VoucherTyp);
    int              ChangePriorityCstDiscAcc(const short Branchno, const long CustomerNo,
        const long InvoiceDate, const nString& InvoiceNo,
        const nString& VoucherTyp, const short Priority);

    int              ReleaseCstDiscAccVSE();
    int              BookOrderValueCstDiscAccVSE();
    int              ReleaseChangeCstDiscAccVSE();
    int              CancelDelayedDeliveryOrderVSE();
    int              OrderDiscAcc();
    int              CheckPaymentDate();
    bool             mustDoRecalculateOrder();
    bool             mustDoCheckCreditLimitCheck();
    bool             getWithTransportExclusion();

    int              WriteProLink(const long date, const nString& InvoiceNumberPro, const long KdAuftragNrPro);
    bool             CheckEncloserTime();
    bool             CheckHighValuePositions();
    bool             checkQuantityLimit();
    long              CalcLogisticVolume();
    int              CheckDiscountListCroatia();
    int              DeleteRangeCollectList();
    int              DeleteItemListTemporary();
    pxOrder* GetOrderFromDestBranch(pxOrderList* olist, const long IDFNr, const short destfil, long itemDepartureDate);
    int              SetReleaseInfos(const nString& RelReason, const nString& RelComment, const nString& RelUser, Order::CloseType type, const nString& guid = "", const nString& URL = "", Order::ApprovalType approvalType = Order::CREDIT);
    bool             SendCremaReleaseInfoMail(Order::CloseType closeType, const nString& RelReason, const nString& RelUser, const nString& guid, const nString& URL, const nString& Comment, Order::ApprovalType approvalType);
    int              CopyReleaseInfos(const long orderNo);
    int              GetReleaseApprovalValues(const long orderNo, const short branchNo, short& ApprovalMax, short& ApprovalCancel, short& ApprovalClose);
    int              checkKdAuftragDebtlimtEntry(const long KdAuftragNr);
    int              BookAddOnChargeArticleNoDependOnCodeBlocage();
    int              WriteTourIdChangeEvent();
    int              WriteCommiTypeChangeEvent();
    int              WriteOrderTypeChangeEvent();
    int              WriteOrderCreationEvent();
    void             WriteOrderLabelChangedToDefaultEvent();

    pxOrder* getDeferredMSV3Order(pxOrderList* olist, const long IDFNr, const short branchno, const nString& _orderlabel);
    int              logItemDiscountValuePct();



    bool             UpdateCounterOnUpdate(const nString& RelUser, Order::CloseType type, short& changeValue);
    nMoney           calculateOrderValueDependOnCodeBlocage(const char codeblocage);
    nMoney           calculateOrderValueForAddOnChargeArticle();



    //  Some Rangecalculation methodes
    int                 BuildRangeCollectList();
    pxRangeControlList* BuildRangeControleList();
    int                 TargetPromotionCollectList();
    int                 PromotionScaleCollectList();
    pxRangeControlList* TargetPromotionControleList();
    pxRangeControlList* PromotionScaleControleList();

    int               calculateRangeGroupCondition(pxRangeControl* rclentry, pxItemDiscountList* posrablist = NULL);
    int               calculateGroupQuantityArticleNo(pxRangeControl* rclentry);
    int               calculateGroupPercentageArticleNo(pxRangeControl* rclentry);
    int               calculateGroupDiscountPct(pxRangeControl* rclentry, pxItemDiscountList* posrablist = NULL);
    int               calculateGroupFixedDiscountVal(pxRangeControl* rclentry);
    int               calculateGroupDiscountQty(pxRangeControl* rclentry);
    int               calculateGroupInvoiceValue(pxRangeControl* rclentry);
    int               calculateGroupNaturalRebateValue(pxRangeControl* rclentry);
    int               CommonProformaInvoice(const short pricetype = -1);

    int               cleanupCommonProformaInvoice(const short pricetype = -1, pxItemDiscountList* posrablist = NULL);

    pxCustRouteList* RouteList(const nString& KdAuftragArt = "");
    // Return a pointer to a list containing routes scheduled for the customer,
    // respecting current commission type and time parameter settings.
    // Returns NULL if a list of valid routes could not be produced. See nError
    // for details in that case.

    pxCustRouteList* ShuttleRouteList(const nString& KdAuftragArt = "");
    // Return a pointer to a list containing routes scheduled for Shuttle customer,
    // respecting current commission type and time parameter settings.
    // Returns NULL if a list of valid routes could not be produced. See nError
    // for details in that case.

    pxCustRouteWeekList* RouteWeekList(const nString& KdAuftragArt = "");
    // Return a pointer to a list containing routes scheduled for the customer,
    // over one week,
    // Returns NULL if a list of valid routes could not be produced. See nError
    // for details in that case.


    //             int     RouteAssignCustomerSpecials();
    int     RouteAssign();
    // Assign a default route.
    int     ShuttleRouteAssign(const short BranchNo);
    // Assign a default route.
    //             int     RouteAssignForward();
    // Assign a route in the future.(next guilty route)

    int     RouteAssignDayType(const nDate& date);
    // Assign a route in the future.(next guilty route)


    int      RouteAssignClearTourAssignment(); // remove the allocated tour from the order
    int     RouteAssignSpecificTour(const nString& r); // Ship order with route 'r'. De-allocates current route if 'r' is empty.

    int        RouteAssignNext(); // Assign the next tour (skip 1)
    int        RouteAssignNext(TourInfo* offsetTourInfo); // Assign the next tour (skip 1)

    int     RouteAssign(const nString& r, const short day);
    // Assign a route, if daytype = -1 assign r on today, otherwise on
    // that day defined by day(0 to 6 = Sunday till Saterday
    //             int     RouteAssignForward(const nString& r, const short day);
    // Assign  route on day(0 - 6)
    int     RouteClearKippZeit();
    // Assign  0 to route->KippZeit
    //             int     IBTRouteAssignForward(pxOrderItem* item);
    // Assign a IBT route in the future.(next guilty route)
    //             int     IBTRouteAssignDayType(const nDate& date, pxOrderItem* item );
    // Assign a IBT route in the future.(next guilty route)
    //             int     IBTRouteAssign( short IBTBranch, pxOrderItem* item);
    //           int     IBTRouteAssignTourManager( short IBTBranch, pxOrderItem* item );
    // Assign a IBT route
    int     CompleteNarcTransferEntries(long PharmosOrderNo);
    //             int     GetCommiTypeFromTour();
    // Assign  commitype by value within tourdefinition

    void     SetRoute(const nString& r); // OK

    void     SetRouteForOrderSeparation(const nString& tourid, const nDate& deliverydate);

    // Ship order with route 'r'.

    nDate    CalcDeliveryDate(const long nextday);
    //  Returns  date of delivery from now,  depend on nextday

    nDate    GetMaxValDate();
    //  Returns max validity date allowed for order type or a null date, if no
    //  validity allowed for current order type or customer.

    int     ValDate(const basar::Date& date);

    int     ValDate(const nDate& date);
    // Set validity date to 'date'. Returns current error state.

    int     ValDate(const int months);
    // Adds number of 'months' to current date and sets validity date to contain
    // the result. Returns current error state.

    int     ValDateMonAuto(const short months);
    // Adds number of 'months' to current date and sets validity date to contain
    // the result. Returns current error state.

    int     ValDate(const nString& months);
    // Adds number of 'months' to current date and sets validity date to contain
    // the result. Returns current error state.

    int     ValMonth();
    // Returns validity months, calculated from the difference between the validity
    // date currently stored in the order and the date of the order creation.
    // Returns 0 if either no validity date was set or the creation date could not
    // be retrieved from the order event log.

    short   ValMonthBatch();
    // Returns validity months, calculated from the difference between the validity
    // date currently stored in the order and the date of the order creation.
    // Returns 0 if either no validity date was set or the creation date could not
    // be retrieved from the order event log(based od DatumValutaBatch_)

    void     ValMonthManuell();
    // Performs validity months, calculated from the the validity
    // date currently stored in the order and the validity batch date of the order.

    short   ValMonthManuellInMonths();
    // Performs validity months, calculated from the the validity
    // date currently stored in the order and the validity batch date of the order.

    int     VerifyValDate(const nDate& date);
    // Performs a sanity check on the validity date passed as 'date'.
    // Returns current error state.
    void     CloseValDate();
    // Performs on Orderclose the automatic validity check
    void     CloseValDateCroatia();
    // Performs on Orderclose the automatic validity check for Croatia
    int     RestDeliveryValdate();
    // Performs on Orderclose the automatic storage of the Valdate into
    // the Restdelivery Positions within this order
    long    GetValutaDays();
    // Performs on Datatransfer to Pharmos It calculates the valuta days between
    // DatumValuta and current date of transfer

    nMoney   ReCalcValues();
    // Performs order value re-calculation. The entire item list is traversed to calc
    // each item's values. Use this method to ensure the order values being updated
    // after an item term update (quantities, prices etc.) has been performed.
    // Returns average item value.

    int     CheckDoubleOrder(char* message);
    // Multiplies Anzpos and WertAuftrag. The result is stored in Table
    // CustomerOrderNo(Used in XML/KSCSERVER application)

    int     CheckDoubleOrder();
    // Multiplies Anzpos and WertAuftrag. The result is stored in Table
    // CustomerOrderNo(Used in the normal XMIT environment
    // application (umk/bytec/hmk)

    bool     CheckCorruptLimit();
    // Check Orderpositions regarding CurroptLimit depend on entry within table paraauftragbearb

    long     LastStock()
    {
        return laststock_;
    }
    // Returns last stock value of a stocked product.

    void     LastStock(long stock)
    {
        laststock_ = stock;
    }
    // Sets last stock value.

    long     AuxStock()
    {
        return auxstock_;
    }
    // Returns auxiliary  stock value of a stocked product.

    void     AuxStock(long auxstock)
    {
        auxstock_ = auxstock;
    }
    // Sets auxiliary  stock value.

    short   AuxFil()
    {
        return auxfil_;
    }
    // Returns that alternate company corresponding to auxstock

    void     AuxFil(short auxfil)
    {
        auxfil_ = auxfil;
    }
    // Sets alternate deliver company.

    long     RestQuota()
    {
        return restquota_;
    }
    // Returns rest quota value of a stocked product.

    void     RestQuota(long quota)
    {
        restquota_ = quota;
    }
    // Sets rest quota for a stocked product.

    long     subArticleNo()
    {
        return subArticleNo_;
    }

    void     setSubArticleNo(const long articleno)
    {
        subArticleNo_ = articleno;
    }

    // Returns subtitution articleno

    int     PostRestDelivery();
    // Check for deliverable NachLieferPos entries for MSV3 orders
    int     MSV3PostRestDelivery(pxVerbund::subsequentDelivery::pxDeliveryPosList* dlist);
    // Release deliverable NachLieferPos entries
    int     releaseRestDeliveryItems(pxVerbund::subsequentDelivery::pxDeliveryPosList* dlist);
    // Release deliverable NachLieferPos entries
    int     checkRestDeliveryPosList(pxVerbund::subsequentDelivery::pxDeliveryPosList* dlist);
    // check pxdeliveryloglist
    bool    checkReleasedDeliveryPosInSameOrder(const long KdAuftragNr, const long ArtikelNr);


    // Poset deliverable NachLieferPos entries
    nMoney   DefektWert()
    {
        return DefektWert_;
    }
    // returns the value of all corrupt positions.
    long     FirstTransPos()
    {
        return FirstTransPos_;
    }
    // returns the value of the first position within the current transmission.
    void     ReCountDCTPositions();
    // counts the DCT Positions.
    bool     ShipUrgentVerification();
    // check order close for urgent shipment
    void     SetParentCompany() { SetAuftragSHWithS(); }
    void     SetCommiError() { SetAuftragSHWithC(); }
    // set bits for hostdatatransfer
    int     CountSpecialProducts(int& coolerq, int& opiateq, int& zytosq);
    // scan ItemList for cooler, opiate and zytostatica

    long getNumberOfPositions() { return static_cast<long>(ItemList_->Entries()); }
    const libcsc::discount::OrderPositionDiscountListPtr getDiscountList();

#include "pxordflg.hpp"
#include "pxordpr_.hpp"

public:
    pxGenericOrderRemarkList    getGenericOrderRemarks();


public:
    nString                     TourId();
    long                        getDeliveryTime();
    long                        getDeliveryDate();
    long                        getTourDate();
    TourAssignmentUtil* getTourAssignmentUtil();
    TourInfo* getTourInformation();
    bool                        hasTourInformation();
    void                        updateItemTours();
    const TourInfo& getNormalDeliveryTourInfo(const nString& tourid, const short weekday /*= -1*/);

    long                        getPurchaseOrderNo();
    bool                        setPurchaseOrderNo(const long purchaseorderno);

    long                        getIVCVoucherNo();
    bool                        setIVCVoucherNo(const long ivcvoucherno);
    bool                        removeIVCVoucherNo();

    long                        getOriginalInvoiceNo();
    bool                        setOriginalInvoiceNo(const long originalinvoiceno);
    bool                        removeOriginalInvoiceNo();

    void                        setNoDelayedDelivery(bool nodelayeddelivery = true);
    bool                        getNoDelayedDelivery() const;

    void                        setWaitForIbtPicking(bool waitForIbtPicking = true);
    bool                        getWaitForIbtPicking() const;


    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // private section
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
private:
    // friend declaratrion
    friend class TourAssignmentUtil;

    // member functions
    long                                                            getOrderRelationNo(OrderRelationNoTypeEnum type);
    pxOrderRelationNoList* getOrderRelationNoList();
    libcsc::cscorder::domMod::ICSCOrderFlagsPtr                     getCSCOrderFlags() const;
    libcsc::cscorder::repo::ICSCOrderFlagsRepositoryPtr             getCSCOrderFlagsRepository() const;

    bool                                                            setOrderRelationNo(OrderRelationNoTypeEnum type, const long originalinvoiceno);
    bool                                                            setTenderContractId(const nString& tendercontractid);

    bool                                                            removeOrderRelationNo(OrderRelationNoTypeEnum type);
    void                                                            verifyCurrentTourAssignment();

    // member variables
    mutable libcsc::cscorder::repo::ICSCOrderFlagsRepositoryPtr     m_CSCOrderFlagsRepository;
    mutable libcsc::ibt::IIbtRequestRepositoryPtr                   m_IbtRequestRepository;
    libcsc::cscordertype::ICSCOrderTypePtr                          m_CscOrderType;
    mutable libcsc::cscorder::domMod::ICSCOrderFlagsPtr             m_CSCOrderFlags;
    TourInfo                                                        m_NormalDeliveryTourInfo;
    TourInfo* m_TourInfo;
    TourAssignmentUtil* m_TourAssignmentUtil;
    pxOrderRelationNoList* m_OrderRelationNoList;
}; // class pxOrder


class pxOrderList : public nDListCollect, public nDBRecordSet
{
public:
    virtual           ~pxOrderList() { Clear(); }
    pxOrderList(pxSession* session);
    void              Clear() { nDBRecordSet::Clear(); }
    pxSession* Session() { return (pxSession*)DataBase(); }

    size_t            SelectByCustomerNo(const long IDFNr, const nString& TourId, const nString& GeraetName, const short FilialNr, ...);
    size_t            SelectForAutomaticClosure(const short branchno, const char* postponereason, ...);
    size_t            SelectVSE(const pxOrder::OrderSendStatusEnum VSEstatus, const int count, const short FilialNr, const int SelMod, ...);
    size_t            SelectBatchOrder(const short VertriebszentrumNr, const long KundenNr, const nString& ZuGrund, const long BatchAuftragNr, ...);
    //  Select orders from the database.

    pxOrder* NewOrder(pxCustBase& customer);
    pxOrder* NewOrder(pxCustBase* customer, pxOrderValidTrans* vt, const long n, const long DeliveryDate = 0, const OriginTypeEnum batchschreiben = cORTYPE_UNKNOWN);
    pxOrder* NewOrderMSV3(pxCustBase* customer, const pxOrderValidTrans* vt, const long n, const nString& _orderlabel, const pxOrderPeriod& _orderperiod);
    pxOrder* NewOrderInfo(pxCustBase* customer);
    pxOrder* NewOrderProforma(pxCustBase* customer);
    pxOrder* NewMSV3InfoOrder(pxCustBase* customer, const pxOrderPeriod& _orderperiod);
    //  Construct new order, append it to the list.

    enum SortFields                     // define list sort criteria
    {
        SortDefault,                     // default : order number
        SortIDFNr,                       // customer id
        SortTourId,                      // tour id
        SortBusyTime                     // Customer business time
    };

    SortFields        SortOrder() const
        //  Query current sort criteria.
    {
        return sort_;
    }
    void              SortOrder(SortFields sf)
        //  Set sort criteria. Use Sort() to sort the list.
    {
        sort_ = sf;
    }

protected:
    pxOrder* AddNewOrder(pxOrder* order);
    virtual  int      EndBrowse(const int cursorid);
    virtual
        nCollectable* AddToList(const void* record, const int row);
    virtual  int      GetNext(const void* record, const int cursorid);
    virtual  int      StartBrowse(const void* keys, const int cursorid);
    size_t            SelectByKDAUFTRAGStruct(tKDAUFTRAG* a, const int count = cDEFAULT, const int SelMod = cDEFAULT);
private:
    SortFields        sort_;         // current list sort order
    friend class      pxOrderListIter;
};

class pxOrderListIter : public nDListCollectIter
{

public:
    // constructors:
    pxOrderListIter(pxOrderList& list) : nDListCollectIter(list) { ; }
    // destructor:
    virtual  ~pxOrderListIter() { ; }
};

#endif // PXORDER_HPP
