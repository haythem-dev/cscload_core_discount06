#include "pxitem.hpp"
#include <pxdbxx.h>
#include <nntypes.h>
#include "pxsess.hpp"
#include "pxdefs.hpp"
#include "pxartbas.hpp"
#include "pxartprc.hpp"
#include "pxorder.hpp"
#include "pxoeparm.hpp"
#include "types/origintypeenum.inc"
#include "types/pricetypeenum.inc"
#include "types/messagecodeenum.inc"
#include "types/orderremarktypeenum.inc"
#include "pxcstbas.hpp"
#include "pxtaxrates.hpp"
#include "pxdiscount.hpp"
#include "pxitemdiscount.hpp"
#include "pxitemattributes.hpp"
#include "pxkdauftragposrefund.hpp"
#include "pxarticlequota.hpp"
#include "pxorderremarks.hpp"
#include "pxpromotioncollect.hpp"
#include "pxorderpospromo.hpp"
#include "pxorderposcalcmode.hpp"
#include "pxtenderpos.hpp"
#include "pxvartikellokallist.hpp"
#include "articlesubstitutionutil.hpp"
#include "tourinfo.hpp"
#include <logger/loggerpool.h>
#include <base/irunnableptr.h>

static const int cItmFlagEntries  = 8;
extern bool pxGlobalNoDatabaseWrite;
extern bool pxGlobalNoWriteToLog;

/*----------------------------------------------------------------------------*/
/*  The real default constructor.                                             */
/*----------------------------------------------------------------------------*/
pxOrderItem :: pxOrderItem
(
    pxSession *session
)
    : pxDBRecord(session)
{
    Init();
}

/*----------------------------------------------------------------------------*/
/*  Constructor to be used for order item entry.                              */
/*----------------------------------------------------------------------------*/
pxOrderItem :: pxOrderItem
(
    pxOrder&    Order,
    long       PosNr
)
    : pxDBRecord(Order.Session())
{
    Init();
    GeraetTyp_   = Session()->Device()->Type();
    Order_ = &Order;
    KdAuftragNr_ = Order.KdAuftragNr();
    PosNr_ = PosNr;
}

/*----------------------------------------------------------------------------*/
/*  Copy constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxOrderItem :: pxOrderItem
(
    pxOrderItem& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tKDAUFTRAGPOS structure to construct this instance.                   */
/*  This constructor is used for selecting/reading from the data base.        */
/*----------------------------------------------------------------------------*/
pxOrderItem :: pxOrderItem
(
    pxSession *session,
    pxOrder&  Order,
    tKDAUFTRAGPOS& src
)
    : pxDBRecord(session)
{
    Init();
    Order_ = &Order;
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Read constructors.                                                        */
/*----------------------------------------------------------------------------*/
pxOrderItem :: pxOrderItem
(
    pxSession *session,
    long    KdAuftragNrL,              // Read via these types
    long    PosNrL,
    DBAccessMode mode
)
    : pxDBRecord(session)
{
    Init();
    KdAuftragNr_ = KdAuftragNrL;
    PosNr_ = PosNrL;
    Get(mode);
}

/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxOrderItem :: ~pxOrderItem()
{
    if( NULL != m_ArticleSubstitutionUtil )
    {
        delete m_ArticleSubstitutionUtil;
        m_ArticleSubstitutionUtil = NULL;
    }
    if( NULL != m_ItemTourInfoIBT )
    {
        delete m_ItemTourInfoIBT;
        m_ItemTourInfoIBT = NULL;
    }

    if( NULL != m_ItemTourInfo )
    {
        delete m_ItemTourInfo;
        m_ItemTourInfo = NULL;
    }

    if( GenericOrderRemarkList_ != NULL )
    {
        delete GenericOrderRemarkList_;
        GenericOrderRemarkList_ = NULL;
    }

    if ( ArtBase_ != NULL )
    {
        delete ArtBase_;
        ArtBase_ = NULL;
    }

    if ( ArtDispo_ != NULL )
    {
        delete ArtDispo_;
        ArtDispo_ = NULL;
    }
    if ( AuxDelList_ != NULL )
    {
        delete AuxDelList_;
        AuxDelList_ = NULL;
    }
    if ( AuxStoreLocList_ != NULL )
    {
        delete AuxStoreLocList_;
        AuxStoreLocList_ = NULL;
    }

    m_ArticleQuota.reset();

    if ( ItemDiscountList_ != NULL )
    {
        delete ItemDiscountList_;
        ItemDiscountList_ = NULL;
    }
    if ( KdAuftragPosRefundList_ != NULL )
    {
        delete KdAuftragPosRefundList_;
        KdAuftragPosRefundList_ = NULL;
    }
    if ( ItemAttributes_ != NULL )
    {
        delete ItemAttributes_;
        ItemAttributes_ = NULL;
    }
    if ( ArtPriceList_ != NULL )
    {
        delete ArtPriceList_;
        ArtPriceList_ = NULL;
    }
    if ( ArtPrice_ != NULL )
    {
        ArtPrice_ = NULL;
    }
    if ( TenderPos_ != NULL )
    {
        delete TenderPos_;
        TenderPos_ = NULL;
    }
    if ( ArtDiscountList_ != NULL )
    {
        delete ArtDiscountList_;
        ArtDiscountList_ = NULL;
    }
    if ( OrderPosCalcMode_ != NULL )
    {
        delete OrderPosCalcMode_;
        OrderPosCalcMode_ = NULL;
    }
    if ( OrderPosPromoList_ != NULL )
    {
        delete OrderPosPromoList_;
        OrderPosPromoList_ = NULL;
    }
    if ( PromoCollectList_ )
    {
        delete PromoCollectList_;
        PromoCollectList_ = NULL;
    }
}

/*----------------------------------------------------------------------------*/
void pxOrderItem::setMSV3RequestID(const basar::VarString& requestid)
{
    pxGenericOrderRemarkList remarklist(Session());
    remarklist.AddOrderRemark(this->KdAuftragNr(), this->PosNr(), eMSV3RequestId, requestid);
}

/*----------------------------------------------------------------------------*/
void pxOrderItem::setMSV3RequestSupportID(const basar::VarString& bestellsupportid)
{
    pxGenericOrderRemarkList remarklist(Session());
    remarklist.AddOrderRemark(this->KdAuftragNr(), this->PosNr(), eMSV3RequestSupportId, bestellsupportid);
}

/*----------------------------------------------------------------------------*/
void pxOrderItem::setMSV3OrderID(const basar::VarString& auftragid)
{
    pxGenericOrderRemarkList remarklist(Session());
    remarklist.AddOrderRemark(this->KdAuftragNr(), this->PosNr(), eMSV3OrderId, auftragid);
}

/*----------------------------------------------------------------------------*/
void pxOrderItem::setMSV3OrderSupportID(const basar::VarString& auftragsupportid)
{
    pxGenericOrderRemarkList remarklist(Session());
    remarklist.AddOrderRemark(this->KdAuftragNr(), this->PosNr(), eMSV3OrderSupportID, auftragsupportid);
}

/*----------------------------------------------------------------------------*/
void pxOrderItem::setXMLReferences( const basar::VarString& orderreference, const basar::VarString& orderlinereference )
{
    try
    {
        pxGenericOrderRemarkList remarklist(Session());
        if (false == orderreference.empty())
        {
            remarklist.AddOrderRemark( this->KdAuftragNr(), this->PosNr(), eOrderReferenceXML, orderreference );
        }
        if (false == orderlinereference.empty())
        {
            remarklist.AddOrderRemark( this->KdAuftragNr(), this->PosNr(), eOrderLineReferenceXML, orderlinereference );
        }
    }
    catch(...)
    {
    }
}

/*----------------------------------------------------------------------------*/

void pxOrderItem::setPromotionName(const basar::VarString& promotionName)
{
    pxGenericOrderRemarkList remarklist(Session());
    remarklist.AddOrderRemark(this->KdAuftragNr(), this->PosNr(), ePromotionName, promotionName);
}

/*----------------------------------------------------------------------------*/
void pxOrderItem::setOCPOrderInfo(const basar::VarString & channelId, int offerID, double freightCost, double carriageFree)
{
    basar::VarString sOfferlId;
    basar::VarString sFreightCost;
    basar::VarString sCarriageFree;
    pxGenericOrderRemarkList remarklist(Session());
    
    sOfferlId.itos(offerID);
    sFreightCost.ftos(freightCost);
    sCarriageFree.ftos(carriageFree);
    remarklist.AddOrderRemark(this->KdAuftragNr(), this->PosNr(), eOCPChannelId, channelId);
    remarklist.AddOrderRemark(this->KdAuftragNr(), this->PosNr(), eOCPOfferId, sOfferlId);
    remarklist.AddOrderRemark(this->KdAuftragNr(), this->PosNr(), eOCPFreightCost, sFreightCost);
    remarklist.AddOrderRemark(this->KdAuftragNr(), this->PosNr(), eOCPCarriageFree, sCarriageFree);
}

/*----------------------------------------------------------------------------*/
bool pxOrderItem::getOCPOrderInfo(basar::VarString& channelId, int& offerID, double& freightCost, double& carriageFree)
{
    pxGenericOrderRemarkList remarklist(Session());
    pxGenericOrderRemarkListIter iter = pxGenericOrderRemarkListIter(remarklist);
    pxGenericOrderRemark* remark;

    channelId = basar::VarString("");
    offerID = 0;
    freightCost = 0;
    carriageFree = 0;

    remarklist.SelectOrderRemarksByOrderLineAndType(this->KdAuftragNr(), this->PosNr(), eOCPChannelId);
    if (remarklist.Entries() == 1)
    {
        iter = pxGenericOrderRemarkListIter(remarklist);
        if (NULL != (remark = (pxGenericOrderRemark*)++iter))
        {
            channelId = remark->RemarkText();
        }
        remarklist.SelectOrderRemarksByOrderLineAndType(this->KdAuftragNr(), this->PosNr(), eOCPOfferId);
        if (remarklist.Entries() == 1)
        {
            iter = pxGenericOrderRemarkListIter(remarklist);
            if (NULL != (remark = (pxGenericOrderRemark*)++iter))
            {
                offerID = remark->RemarkText().stoi();
            }
            remarklist.SelectOrderRemarksByOrderLineAndType(this->KdAuftragNr(), this->PosNr(), eOCPFreightCost);
            if (remarklist.Entries() == 1)
            {
                iter = pxGenericOrderRemarkListIter(remarklist);
                if (NULL != (remark = (pxGenericOrderRemark*)++iter))
                {
                    freightCost = remark->RemarkText().stof();
                }
                remarklist.SelectOrderRemarksByOrderLineAndType(this->KdAuftragNr(), this->PosNr(), eOCPCarriageFree);
                if (remarklist.Entries() == 1)
                {
                    iter = pxGenericOrderRemarkListIter(remarklist);
                    if (NULL != (remark = (pxGenericOrderRemark*)++iter))
                    {
                        carriageFree = remark->RemarkText().stof();
                    }
                    return true;
                }
            }
        }
    }
    return false;
}

/*----------------------------------------------------------------------------*/
bool pxOrderItem::hasOCPOrderInfo()
{
    pxGenericOrderRemarkList remarklist(Session());
    remarklist.SelectOrderRemarksByOrderLineAndType(this->KdAuftragNr(), this->PosNr(), eOCPChannelId);
    if (remarklist.Entries() == 1)
    {
        remarklist.SelectOrderRemarksByOrderLineAndType(this->KdAuftragNr(), this->PosNr(), eOCPOfferId);
        if (remarklist.Entries() == 1)
        {
            remarklist.SelectOrderRemarksByOrderLineAndType(this->KdAuftragNr(), this->PosNr(), eOCPFreightCost);
            if (remarklist.Entries() == 1)
            {
                remarklist.SelectOrderRemarksByOrderLineAndType(this->KdAuftragNr(), this->PosNr(), eOCPCarriageFree);
                if (remarklist.Entries() == 1)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

void pxOrderItem::copyGenericOrderRemarks(pxOrderItem* src)
{
    pxGenericOrderRemarkList* remarklist = src->getGenericOrderRemarks();
    pxGenericOrderRemarkListIter iter = pxGenericOrderRemarkListIter(*remarklist);
    pxGenericOrderRemark* remark;
    while (NULL != (remark = (pxGenericOrderRemark*)++iter))
    {
        getGenericOrderRemarks()->AddOrderRemark(KdAuftragNr(), PosNr(), remark->RemarkType(), remark->RemarkText());
    }
}


/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tKDAUFTRAGPOS structure.       */
/*----------------------------------------------------------------------------*/
tKDAUFTRAGPOS&
Assign
(
    tKDAUFTRAGPOS&       dest,
    const pxOrderItem&   src
)
{
    // Copy native data types:
    dest.KdAuftragNr           = src.KdAuftragNr_                             ;
    dest.PosNr                 = src.PosNr_                                   ;
    dest.ArtikelNr             = src.ArtikelNr_                               ;
    dest.PosTyp                = static_cast<short>(src.PosTyp_)              ;
    dest.GeraetTyp             = static_cast<short>(src.GeraetTyp_)           ;
    dest.FehlerMenge           = src.FehlerMenge_                             ;
    dest.FehlerArtikel         = static_cast<short>(src.FehlerArtikel_)       ;
    dest.MengeBestellt         = src.MengeBestellt_                           ;
    dest.MengeBestaetigt       = src.MengeBestaetigt_                         ;
    dest.MengeGeliefert        = src.MengeGeliefert_                          ;
    dest.MengeAbgebucht        = src.MengeAbgebucht_                          ;
    dest.MengeNatra            = src.MengeNatra_                              ;
    dest.MengeNatraGrossH      = src.MengeNatraGrossH_                        ;
    dest.MengeNatraHerst       = src.MengeNatraHerst_                         ;
    dest.PreisEKApo            = src.PreisEKApo_                              ;
    dest.PreisVKApo            = src.PreisVKApo_                              ;
    dest.PreisEKApoNetto       = src.PreisEKApoNetto_                         ;
    dest.PreisEKGrosso         = src.PreisEKGrosso_                           ;
    dest.PreisEKGrossoNA       = src.PreisEKGrossoNA_                         ;
    dest.RabattFest            = src.RabattFest_                              ;
    dest.RabattFestDM          = src.RabattFestDM_                            ;
    dest.PreisFest             = 0                                            ;
    dest.PreisProzent          = 0                                            ;
    dest.ArtBestNachUpd        = src.ArtBestNachUpd_                          ;
    dest.UhrZeitBestNachUpd    = src.UhrZeitBestNachUpd_                      ;
    dest.SendeStatus           = static_cast<short>(src.SendeStatus_)         ;
    dest.MengeVorausBezug      = src.MengeVorausBezug_                        ;
    dest.BatchPosNr            = src.BatchPosNr_                              ;
    dest.WannenNr              = src.WannenNr_                                ;
    dest.BewegungsArt          = src.BewegungsArt_                            ;
    dest.SalesTaxRate          = src.SalesTaxRate_                            ;
    dest.CodeBlocage           = src.CodeBlocage_                             ;
    dest.PreisEKApoFree        = src.PreisEKApoFree_                          ;
    dest.LinkPosNr             = src.LinkPosNr_                               ;
    dest.Preis_Typ             = static_cast<short>(src.PreisTyp_)            ;
    dest.Article_No_Pack       = src.ArticleNoPack_                           ;
    dest.PreisFaktur           = src.PreisFaktur_                             ;
    dest.MaxTargetNo           = src.MaxTargetNo_                             ;
    dest.ContainerLevel        = src.ContainerLevel_                          ;
    dest.RefundValue           = src.RefundValue_                             ;
    dest.Promotion_No          = src.PromotionNo_                             ;
    dest.PromoTyp              = src.PromoTyp_                                ;
    dest.Code_Type             = src.CodeType_                                ;
    dest.ProblemState          = src.ProblemState_                            ;
    dest.SubGeraetTyp          = src.SubGeraetTyp_                            ;
    dest.KzPriso               = src.KzPriso_                                 ;
    dest.BusinessTypeNo        = src.BusinessTypeNo_                          ;
    dest.IBTTourWeekDay        = src.IBTTourWeekDay_                          ;
    dest.IBTType               = src.IBTType_                                 ;
    dest.IBTTypeID             = src.IBTTypeID_                               ;
    dest.PurchaseRelevantQty   = src.PurchaseRelevantQty_                     ;
    dest.MengeBestellt_Org     = src.MengeBestelltOrg_                        ;
    dest.MengeBestelltNatra    = src.MengeBestelltNatra_                      ;
    dest.NatraCategory         = static_cast<short>(src.NatraCategory_)       ;
    dest.PreisEKAgp            = src.PreisAGP_                                ;

    // Strings
    if ( src.Bemerkungen_.IsEmpty() )
    {
        memcpy(dest.Bemerkungen, " ", mSIZEOF(tKDAUFTRAGPOS, Bemerkungen));
    }
    else
    {
        dest.Bemerkungen[0] = ' ';
        src.Bemerkungen_.GetData(dest.Bemerkungen, (mSIZEOF(tKDAUFTRAGPOS, Bemerkungen)) - 1);
    }
    dest.Hinweis[0] = ' ';
    dest.KdAuftragBestellNr[0] = ' ';
    src.KdAuftragBestellNr_.GetData(dest.KdAuftragBestellNr, (mSIZEOF(tKDAUFTRAGPOS, KdAuftragBestellNr)) - 1);
    dest.Article_Code[0] = ' ';
    src.ArticleCode_.GetData(dest.Article_Code, (mSIZEOF(tKDAUFTRAGPOS, Article_Code)) - 1);

    dest.TourIdIBT[0] = ' ';
    src.TourIdIBT_.GetData(dest.TourIdIBT, (mSIZEOF(tKDAUFTRAGPOS, TourIdIBT)) - 1);

    dest.NatraPharmacyGroup[0] = ' ';
    src.NatraPharmacyGroup_.GetData(dest.NatraPharmacyGroup, (mSIZEOF(tKDAUFTRAGPOS, NatraPharmacyGroup)) - 1);

    // Conversions:
    sprintf(dest.Rabattfaehig, "%02d", src.Rabattfaehig_);

    // Bit Map Exporting.
    // Define an array of longs be cause the flags must be exported in one array.
    unsigned long LongArray[cItmFlagEntries];
    src.ETPosSchalter_.Export(LongArray, cItmFlagEntries, cFlagBytesPerLong);

    // Copy flag longs into record structure:
    dest.ETPosSchalter1 = (long) LongArray[0];
    dest.ETPosSchalter2 = (long) LongArray[1];
    dest.ETPosSchalter3 = (long) LongArray[2];
    dest.ETPosSchalter4 = (long) LongArray[3];
    dest.ETPosSchalter5 = (long) LongArray[4];
    dest.ETPosSchalter6 = (long) LongArray[5];
    dest.ETPosSchalter7 = (long) LongArray[6];
    dest.ETPosSchalter8 = (long) LongArray[7];

    long nothing;
    src.ETArtSchalter_.Export(dest.ETArtSchalter1, dest.ETArtSchalter2, dest.ETArtSchalter3, nothing, nothing);

    src.ETArtKlasse_.Export(dest.ETArtKlasse1, nothing);

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tKDAUFTRAGPOS struct to pxOrderItem object */
/*----------------------------------------------------------------------------*/
pxOrderItem&
Assign
(
    pxOrderItem&         dest,
    const tKDAUFTRAGPOS& src
)
{
    // Copy native data types:
    dest.KdAuftragNr_          = src.KdAuftragNr                              ;
    dest.PosNr_                = src.PosNr                                    ;
    dest.ArtikelNr_            = src.ArtikelNr                                ;
    dest.PosTyp_               = (pxOrderItem::ItemType)src.PosTyp            ;
    dest.GeraetTyp_            = (pxDeviceType)src.GeraetTyp                  ;
    dest.FehlerMenge_          = (pxOrderItem::QuantityState)src.FehlerMenge  ;
    dest.FehlerArtikel_        = (pxOrderItem::ArticleState)src.FehlerArtikel ;
    dest.MengeBestellt_        = src.MengeBestellt                            ;
    dest.MengeBestaetigt_      = src.MengeBestaetigt                          ;
    dest.MengeGeliefert_       = src.MengeGeliefert                           ;
    dest.MengeAbgebucht_       = src.MengeAbgebucht                           ;
    dest.MengeNatra_           = src.MengeNatra                               ;
    dest.MengeNatraGrossH_     = src.MengeNatraGrossH                         ;
    dest.MengeNatraHerst_      = src.MengeNatraHerst                          ;
    dest.PreisEKApo_           = src.PreisEKApo                               ;
    dest.PreisVKApo_           = src.PreisVKApo                               ;
    dest.PreisEKApoNetto_      = src.PreisEKApoNetto                          ;
    dest.PreisEKGrosso_        = src.PreisEKGrosso                            ;
    dest.PreisEKGrossoNA_      = src.PreisEKGrossoNA                          ;
    dest.RabattFest_           = src.RabattFest                               ;
    dest.RabattFestDM_         = src.RabattFestDM                             ;
    dest.ArtBestNachUpd_       = src.ArtBestNachUpd                           ;
    dest.UhrZeitBestNachUpd_   = src.UhrZeitBestNachUpd                       ;
    dest.Zuzahlung_            = src.Zuzahlung                                ;
    dest.SendeStatus_          = static_cast<pxOrderItem::ItemSendStatusEnum>(src.SendeStatus);
    dest.MengeVorausBezug_     = src.MengeVorausBezug;
    dest.BatchPosNr_           = src.BatchPosNr                               ;
    dest.WannenNr_             = src.WannenNr                                 ;
    dest.BewegungsArt_         = src.BewegungsArt                             ;
    dest.SalesTaxRate_         = src.SalesTaxRate                             ;
    dest.CodeBlocage_          = src.CodeBlocage                              ;
    dest.PreisEKApoFree_       = src.PreisEKApoFree                           ;
    dest.LinkPosNr_            = src.LinkPosNr                                ;
    dest.PreisTyp_             = static_cast<PriceTypeEnum>(src.Preis_Typ)    ;
    dest.ArticleNoPack_        = src.Article_No_Pack                          ;
    dest.PreisFaktur_          = src.PreisFaktur                              ;
    dest.MaxTargetNo_          = src.MaxTargetNo                              ;
    dest.ContainerLevel_       = src.ContainerLevel                           ;
    dest.RefundValue_          = src.RefundValue                              ;
    dest.PromotionNo_          = src.Promotion_No                             ;
    dest.PromoTyp_             = src.PromoTyp                                 ;
    dest.CodeType_             = src.Code_Type                                ;
    dest.ProblemState_         = src.ProblemState                             ;
    dest.SubGeraetTyp_         = src.SubGeraetTyp                             ;
    dest.KzPriso_              = src.KzPriso                                  ;
    dest.BusinessTypeNo_       = src.BusinessTypeNo                           ;
    dest.PreisAGP_             = src.PreisEKAgp;

    // Strings:
    dest.Bemerkungen_          = src.Bemerkungen                              ;
    dest.Bemerkungen_.Strip();
    dest.KdAuftragBestellNr_   = src.KdAuftragBestellNr;
    dest.ArticleCode_          = src.Article_Code;
    dest.TourIdIBT_            = src.TourIdIBT;
    dest.IBTTourWeekDay_       = src.IBTTourWeekDay;
    dest.IBTType_              = src.IBTType;
    dest.IBTTypeID_            = src.IBTTypeID;
    dest.PurchaseRelevantQty_  = src.PurchaseRelevantQty;
    dest.MengeBestelltOrg_     = src.MengeBestellt_Org;
    dest.MengeBestelltNatra_   = src.MengeBestelltNatra;
    dest.NatraCategory_        = static_cast<tDiscountCategory>(src.NatraCategory);
    dest.NatraPharmacyGroup_   = src.NatraPharmacyGroup;

    // Conversions:
    dest.Rabattfaehig_         = atoi(src.Rabattfaehig);
    // Bit Maps:

    // define an array of longs to ensure the flags being stored in one array:
    unsigned long LongArray[cItmFlagEntries];
    LongArray[0] = (unsigned long)src.ETPosSchalter1;  // copy flag longs from record struct
    LongArray[1] = (unsigned long)src.ETPosSchalter2;
    LongArray[2] = (unsigned long)src.ETPosSchalter3;
    LongArray[3] = (unsigned long)src.ETPosSchalter4;
    LongArray[4] = (unsigned long)src.ETPosSchalter5;
    LongArray[5] = (unsigned long)src.ETPosSchalter6;
    LongArray[6] = (unsigned long)src.ETPosSchalter7;
    LongArray[7] = (unsigned long)src.ETPosSchalter8;
    // Import flagssrc. into bit map:
    dest.ETPosSchalter_.Import(LongArray, cItmFlagEntries, cFlagBytesPerLong);

    dest.ETArtSchalter_.Import(src.ETArtSchalter1, src.ETArtSchalter2, src.ETArtSchalter3, 0L, 0L);

    dest.ETArtKlasse_.Import(src.ETArtKlasse1, 0L);

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxOrderItem list objects being inserted in the following ascending*/
/*  sequence:    KdAuftragNr_, PosNr_                                         */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: CompareTo
(
    const nCollectable   *That,
          void           * /*p*/,
    const long           lparm
)   const
{
    pxOrderItem *that = (pxOrderItem*)That;
    int retval = 0;
    switch (lparm)
    {
        case pxOrderItemList::SortByArticleNo:
            retval = (ArtikelNr_ == that->ArtikelNr_) ? 0 : (ArtikelNr_ > that->ArtikelNr_ ? 1 : -1);
            if ( retval == 0 )               // ArtikelNr ==
                retval = (PosNr_ == that->PosNr_) ? 0 : (PosNr_ > that->PosNr_ ? 1 : -1);
            break;
        case pxOrderItemList::SortByPosNr:
        case pxOrderItemList::SortDefault:
        default:
            retval = (KdAuftragNr_ == that->KdAuftragNr_) ? 0 : (KdAuftragNr_ > that->KdAuftragNr_ ? 1 : -1);
            if ( retval == 0 )               // AuftragNr ==
                retval = (PosNr_ == that->PosNr_) ? 0 : (PosNr_ > that->PosNr_ ? 1 : -1);
            break;
    }

    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxOrderItem :: Init()
{
    BLOG_TRACE_METHOD( libcsc::LoggerPool::getLoggerOrderItem(), "pxOrderItem::Init()" );

    tKDAUFTRAGPOS      record;

    m_ArticleSubstitutionUtil = NULL;
    m_ItemTourInfoIBT = NULL;
    m_ItemTourInfo = NULL;
    GenericOrderRemarkList_ = NULL;
    Order_             = NULL;
    ArtBase_           = NULL;
    ArtPrice_          = NULL;
    ArtDispo_          = NULL;
    AuxDelList_        = NULL;
    AuxStoreLocList_   = NULL;
    //ValidDiscBarList_  = NULL;
    //ValidDiscOmgList_  = NULL;
    ItemDiscountList_  = NULL;
    KdAuftragPosRefundList_  = NULL;
    OrderPosPromoList_ = NULL;
    PromoCollectList_  = NULL;

    ItemAttributes_    = NULL;
    ArtPriceList_      = NULL;
    ArtDiscountList_   = NULL;
    OrderPosCalcMode_  = NULL;
    TenderPos_         = NULL;
    MengeVerbund_      = 0;
    MengeMoeglich_     = 0;
    MengeNLMoeglich_   = 0;
    MengeDispoMoeglich_ = 0;
    MengeReserviert_   = 0;
    VerbundFilialNr_   = 0;
    ArtikelNrPassiv_   = 0;
    MengeNatraDiscountArticle_ = 0;
    DiscountArticleNo_ = 0;
    BookRestDelivery_       = false;
    DispoMoeglich_          = false;
    QuotaExeeded_           = false;
    ReleaseRestDelivery_    = false;
    ProFormaBooking_        = false;
    RebateAccountExceeded_  = false;
    NoNarcoticsDiscAcc_     = false;
    UpdateDebtlimitK2_      = false;
    UpdateDebtlimitK1_      = false;
    NotSaveDiscountList_    = false;
    IBTPosDayNightMerge_    = false;
    HigherConditionsAvailable_ = false;
    CustomerSurchargeAdded_ = false;
    InitOrderItem(record);
    Assign(*this, record);
    CodeBlocage_ = ' ';
    PreisTyp_    = FREESALE_PRICE; // default
    PreisEKApoFree_ = 0.0;
    FixedPricePaymentterms_ = 0.0;
    DiscountValPctMan_      = 0.0;
    GrossProfitPctFV_       = 0.0;
    DiscountValPctPromo_    = 0.0;
    DiscountValPctProforma_ = 0.0;
    CustomerSurcharge_ = 0.0;
    KzPriso_ = '0';
    SubstProposalArticleNo_ = 0L;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the tKDAUFTRAGPOS struct*/
/*  and then imported to self.                                                */
/*----------------------------------------------------------------------------*/
pxOrderItem&
pxOrderItem :: operator=( const pxOrderItem& src)
{
    tKDAUFTRAGPOS  record;                 // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    Order_ = src.Order_;                // copy pxOrder class pointer
    DiscountValPctProforma_ = src.DiscountValPctProforma_;
    XMLLinereference_       = src.XMLLinereference_;

    if (ArtBase_)                       // then do a deep copy of the ArtBase class
    {
        pxArtBase   *ab = pxArtBase::CopyArticle(ArtBase_);
        delete ArtBase_;
        ArtBase_ = ab;
    }

    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tKDAUFTRAGPOS structure 'src' to this instance.  */
/*----------------------------------------------------------------------------*/
pxOrderItem&
pxOrderItem :: operator=( const tKDAUFTRAGPOS& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: Get
(
    DBAccessMode mode
)
{
    tKDAUFTRAGPOS record;
    memset(&record, 0, sizeof(tKDAUFTRAGPOS));
    record.KdAuftragNr = KdAuftragNr_;
    record.PosNr = PosNr_;
    int retval = ( mode == cDBGET_FORUPDATE ) ? nDBReadLock(&record) : nDBRead(&record);
    if (!retval)
        (*this)= record;                 // import the data from tKDAUFTRAGPOS struct
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Put this object into the data source.                                     */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: Put()
{
    int retval = cDBXR_NORMAL;
    tKDAUFTRAGPOS record;
    //::pxInitOrderItem(&record);
    InitOrderItem(record);
    Assign(record, *this);

    if (IsActive())
    {
        Assign(record, *this);           // get keys
        retval = nDBReadLock(&record);   // read-lock record for subsequent update
    }

    if ( retval == cDBXR_NORMAL )
    {
        ToPharmos();                     // Translate values for old PHARMOS
        Assign(record, *this);           // export object values
        ToPharmosRecord( record );       // additional values for old PHARMOS
        retval = nDBWrite(&record, sizeof(tKDAUFTRAGPOS));
    }

    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Delete this object from the data source.                                  */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: Delete
(
)
{
    tKDAUFTRAGPOS record;
    memset(&record, 0, sizeof(tKDAUFTRAGPOS));
    Assign(record, *this);
    return Delete(&record);
}

/*----------------------------------------------------------------------------*/
/*  Return article base class pointer. If the article base class object is not*/
/*  already referenced, its read constructor is called.                       */
/*  If DBAccessMode is cDBGET_FORUPDATE and the record is not already locked, */
/*  the record is read and locked.                                            */
/*----------------------------------------------------------------------------*/
pxArtBase*
pxOrderItem :: ArtBase
(
    DBAccessMode mode
)
{
    if ( (ArtBase_) && ArtBase_->IsActive() && mode != cDBGET_FORUPDATE )
        return ArtBase_;                 // simply return the pointer

    if (!ArtBase_)                   // then must construct pxArtBase object
        ArtBase_ = pxArtBase::CreateArticle(Session(), ArtikelNr_, Order_->FilialNr(), mode);
    else if ( (mode == cDBGET_FORUPDATE) && !(ArtBase_->IsLocked()) )
        ArtBase_->Get(mode);

    if ( !(ArtBase_->IsGoodState()) )    // then article not found
    {
        if (ArtikelNr_ > 0 && IsKnownProduct())
        {
            Error() = ArtBase_->Error(); // copy error object
        }
        return ArtBase_;
    }

    // for the Swiss apllication: Set language into ArtBase
    if (Session()->isSwitzerland())
    {
        ArtBase_->SetSprache(Order().Customer()->Sprache());
    }

    // everything is ok
    SalesTaxRate(ArtBase_->TaxLevel());
    if ( ArtBase_->IsSteller() )
    {
        SetStellerKopf();
    }
    SetBusinessTypeNo(ArtBase_->BusinessTypeNo());

    return ArtBase_;
}

/*----------------------------------------------------------------------------*/
/*  Test if current order item object may be updated anyway.                  */
/*----------------------------------------------------------------------------*/
bool
pxOrderItem :: IsChangeable()
{
    if ( !Order().IsChangeable() )
        return false;
    if ( !IsActive() || IsCancelled() )
    {
        ExternalError(CMsgStream(), CMSG_ITM_UPDATE_DENIED, PosNr_, KdAuftragNr_);
        return false;
    }
    return true;
}

/*----------------------------------------------------------------------------*/
/*  Check the condition on ArtBase                                            */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: ArtBaseValidity
(
    const long Menge,
          int  flags
)
{
    ClearError();
    if ( ArtBase_ )
    {
        if ( !ArtBase_->IsGoodState() )
        {
            if ( pxGlobalNoDatabaseWrite)
                pxGlobalNoWriteToLog = true;
            FehlerArtikel_ = ArtStateNotFound;
            MengeBestellt_ = Menge;
            PosTyp_ = TypeProductUnknown;    // create an order item for an unknown
            ExternalCondition(CMsgStream(), CMSG_ITM_NOT_ONSTOCK, ArtBase_->ArtikelNr());
            pxGlobalNoWriteToLog = false;
            return ErrorState();
        }

        if (ArtBase_->IsNotSaleable())
        {
            if ( Session()->isFrance() && Order().Param()->IsAnzPrintCode() )
            {
                CodeBlocage_ = ArtBase_->CodeBlocage();
                nString CBPrintCode;
                nMessage pCode( CBPrintCode = ArtBase_->GetCBPrintCode());
                ExternalError(pCode);
            }
            else
            {
                ExternalCondition(CMsgStream(), CMSG_ART_NOTACTIVE, ArtikelNr_);
            }
            ArtBase_->Put();              // unlock artbase
            FehlerArtikel_ = ArtStateNotFound;
            FehlerMenge_  |= QStateAlternate; // mark item
            MengeBestellt_ = Menge;
            HandleError();                // product or return the error
            if ( IsGoodState() )
            {
                return 1;                  // return pseudo error
            }
            return ErrorState();
        }

        if (ArtBase_->IsStopSelling())   // stock difference
        {
            FehlerMenge_ |= QStateNotOnHand;;
            MengeBestellt_ = Menge;
            //PosTyp_ = TypeProductUnknown;    // create an order item for an unknown // Heinlein, 2014-10-02 auskommentiert CMSG_ITM_STOCK_DIFFERENCE
            ExternalCondition(CMsgStream(), CMSG_ITM_STOCK_DIFFERENCE, ArtBase_->ArtikelNr());
            SetInhibitTransferBem();      // do not transfer text to pharmos
            return ErrorState();
        }

        // Authorization check (skipped if server's auto item posting is active):
        if ( !(flags & bPOST_AUTO_ITEM) &&
            !(Order().BatchSchreiben() == cORTYPE_AUXILIARY) &&
            !(ArtBase_->ArtClass().IsAuthorized(Order().Customer()->ArtClass())) )
        {                                // then: customer no authorized
            FehlerArtikel_ = ArtStateNotAuthorized;
            MengeBestellt_ = 0;
            if ( Session()->Device()->IsVideo() )   // is not dct
            {
                ExternalCondition(CMsgStream(), CMSG_ITM_NOT_AUTHORIZED);
            }
            else
            {
                ExternalCondition(CMsgStream(), CMSG_ITM_NOT_AUTHORIZED_DCT,ArtikelNr_);
            }
            HandleError();
        }
    }

    return ErrorState();
}

/*----------------------------------------------------------------------------*/
/*  Set item posting type flags.                                              */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: PostType
(
    BookingType btype                   // item posting type
)
{
    ClearDisponieren();
    ClearZugesagt();
    ClearNachliefern();
    ClearNachFrageBuchung();
    // Update quantity booking type flags in self:
    if ( btype > BookingTypeDefault )
        ETPosSchalter_.SetBit(btype);
    SetDirty();
    return ErrorState();
}

/*----------------------------------------------------------------------------*/
/*  Return posting type.                                                      */
/*----------------------------------------------------------------------------*/
pxOrderItem::BookingType
pxOrderItem :: PostType()
{
    BookingType btype = BookingTypeDefault;

    if (IsNachFrageBuchung())
        btype = DemandBooking;
    if (IsDisponieren())
        btype = PurchaseOrder;
    if (IsNachliefern())
        btype = RestDelivery;
    if (IsZugesagt())
        btype = DeliveryConfirmed;
    return btype;
}

/*----------------------------------------------------------------------------*/
/*  Set SaleTaxRate                                                           */
/*----------------------------------------------------------------------------*/
void
pxOrderItem :: SalesTaxRate
(
    const short TaxLevel
)
{
    pxTaxRates* taxrate = Session()->TaxRatesList()->Find(TaxLevel);
    if (taxrate)
    {
        SalesTaxRate_ = taxrate->SalesTaxRate();
    }
}

/*----------------------------------------------------------------------------*/
/*  Constructor used for order item processing.                               */
/*----------------------------------------------------------------------------*/
pxOrderItemList :: pxOrderItemList
(
    pxOrder&    Order
)
    : nDBRecordSet(Order.Session())
{
    Order_ = &Order;
    nDBSetList(this);
}

/*----------------------------------------------------------------------------*/
/*  Constructor to be used for item processing without an order reference.    */
/*----------------------------------------------------------------------------*/
pxOrderItemList :: pxOrderItemList
(
    pxSession   *session
)
    : nDBRecordSet(session)
{
    Order_ = NULL;
    nDBSetList(this);
}

int pxOrderItemList::EndBrowse(const int cursorid)
{
    return pxPositionEndBrowse(cursorid);
}

int pxOrderItemList::GetNext(const void* record, const int cursorid)
{
    return pxPositionGetNext((tKDAUFTRAGPOS*)record, cursorid);
}

int pxOrderItemList::StartBrowse(const void *keys, const int cursorid)
{
    return pxPositionStartBrowse((tKDAUFTRAGPOS*)keys, cursorid);
}

/*----------------------------------------------------------------------------*/
/*  Initialize selection using the current customer order reference.          */
/*----------------------------------------------------------------------------*/
size_t
pxOrderItemList :: Select
(
    const int     count_                // Max number of records to read
)
{
    tKDAUFTRAGPOS record;
    memset(&record, 0, sizeof(tKDAUFTRAGPOS)); // zero out entire record buffer
    record.KdAuftragNr = Order_->KdAuftragNr();
    return Select(&record, count_);
}

/*----------------------------------------------------------------------------*/
/*  Initialize selection using single integer value arguments.                */
/*----------------------------------------------------------------------------*/
size_t
pxOrderItemList :: Select
(
    const long    KdAuftragNr,
    const int     count_                // Max number of records to read
)
{
    tKDAUFTRAGPOS record;
    memset(&record, 0, sizeof(tKDAUFTRAGPOS)); // zero out entire record buffer
    record.KdAuftragNr = KdAuftragNr;
    return Select(&record, count_);
}

/*----------------------------------------------------------------------------*/
/*  Do the selection based upon the values stored in a tKDAUFTRAGPOS struct.  */
/*  Note that unused search criteria must have the appropiate default values, */
/*  i.e. '\0' for a string value, 0 for an integer etc.                       */
/*----------------------------------------------------------------------------*/
size_t
pxOrderItemList :: Select
(
    tKDAUFTRAGPOS  *record,
    const int     count_
)
{
    int cursorid = cCRS_DEFAULT;       // set cursor id
    nDBSelect(record, cursorid, count_);
    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxOrderItemList :: AddToList
(
    const void  *record,
    const int  row
)
{
    // avoid "unused" compiler warning
    { int i = row; i = i; }


    pxOrderItem *objectp = new pxOrderItem(Session(), *Order_, *(tKDAUFTRAGPOS*) record); // construct new object
    InsertAscending(objectp);
    return objectp;
}

/*----------------------------------------------------------------------------*/
/*  Find: This methode looks for an article wihin this list depend on         */
/*  ArtikelNr. Return values: false =  not found, true = found                */
/*----------------------------------------------------------------------------*/
bool
pxOrderItemList :: Find
(
    const long ArtikelNr
)
{
    bool retval = false;
    pxOrderItem*  entryp = NULL;
    pxOrderItemListIter cursor(*this);

    while ( (entryp = (pxOrderItem*) ++cursor) != NULL )
    {
        if (entryp->ArtikelNr() == ArtikelNr )
        {
            retval = true;
            break;
        }
    }
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  FindPromotionNo: This methode looks for an entry depend on promotionno    */
/*  Return values: false =  not found, true = found                           */
/*----------------------------------------------------------------------------*/
bool
pxOrderItemList :: FindPromotionNo
(
    const long PromotionNo
)
{
    bool retval = false;
    pxOrderItem*  entryp = NULL;
    pxOrderItemListIter cursor(*this);

    while ( (entryp = (pxOrderItem*) ++cursor) != NULL )
    {
        if (entryp->PromotionNo() == PromotionNo )
        {
            retval = true;
            break;
        }
    }
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  FindArticle: This methode looks for the first item with ArtikelNr         */
/*----------------------------------------------------------------------------*/
pxOrderItem* pxOrderItemList::FindItemByArticleNo(const long ArtikelNr )
{
    pxOrderItem*  entryp = NULL;
    pxOrderItemListIter cursor(*this);
    while ( (entryp = (pxOrderItem*) ++cursor) != NULL )
    {
        if( entryp->ArtikelNr() == ArtikelNr )
        {
            break;
        }
    }
    return entryp;
}

/*----------------------------------------------------------------------------*/
/*  FindArticle: This methode looks for an article wihin this list depend on  */
/*  ArtikelNr and PriceTyp. Return NULLP or entryp                            */
/*----------------------------------------------------------------------------*/
pxOrderItem*
pxOrderItemList :: FindArticle
(
    const long ArtikelNr,
    const PriceTypeEnum  PriceTyp
)
{
    pxOrderItem*  entryp = NULL;
    pxOrderItemListIter cursor(*this);

    while ( (entryp = (pxOrderItem*) ++cursor) != NULL )
    {
        if (entryp->ArtikelNr() == ArtikelNr  && entryp->PreisTyp() == PriceTyp )
        {
            break;
        }
    }
    return entryp;
}

/*----------------------------------------------------------------------------*/
/*  CountTargetDiscountArticle This methode returns a count of                */
/*  TargetDiscountArticle depend on ArtikelNr and PromoType 2 on the position */
/*  ArtikelNr. Return values: false =  not found, true = found                */
/*----------------------------------------------------------------------------*/
int
pxOrderItemList :: CountTargetDiscountArticle
(
    const long ArtikelNr
)
{
    int   retval      = 0;
    pxOrderItem*  entryp = NULL;
    pxOrderItemListIter cursor(*this);

    while ( (entryp = (pxOrderItem*) ++cursor) != NULL )
    {
        if ( entryp->ArtikelNr() == ArtikelNr && entryp->IsFreeArticlePromotion() )
        {
            ++retval;
        }
    }
    return retval;
}
/*----------------------------------------------------------------------------*/
/*  GetTargetDiscountArticle This methode returns a pointer to an             */
/*  TargetDiscountArticle depend on ArtikelNr and PromoType 2 on the position */
/*  PosNr is position number from where cursor starts                         */
/*----------------------------------------------------------------------------*/
pxOrderItem*
pxOrderItemList :: GetTargetDiscountArticle
(
    const long ArtikelNr,
    const long PosNr
)
{
    // unused variable
    // int   retval      = 0;
    pxOrderItem*  entryp = NULL;
    pxOrderItemListIter cursor(*this);

    if ( PosNr > 0 )
    {
        cursor += PosNr;
    }
    while ( (entryp = (pxOrderItem*) ++cursor) != NULL )
    {
        if ( entryp->ArtikelNr() == ArtikelNr && entryp->IsFreeArticlePromotion() )
        {
            break;
        }
    }
    return entryp;
}

pxOrderItem * pxOrderItemList::GetItem( const long PosNr )
{
    pxOrderItem*  entryp = NULL;
    pxOrderItemListIter cursor(*this);

    while ( (entryp = (pxOrderItem*) ++cursor) != NULL )
    {
        if ( entryp->PosNr() == PosNr )
        {
            break;
        }
    }
    return entryp;
}

pxOrderItem * pxOrderItemList::GetItemFromSplitIbtPos( const long PosNr )
{
    pxOrderItem*  entryp = NULL;
    pxOrderItemListIter cursor(*this);

    while ( (entryp = (pxOrderItem*) ++cursor) != NULL )
    {
        if ( entryp->LinkPosNr() == PosNr )
        {
            break;
        }
    }
    return entryp;
}

/*----------------------------------------------------------------------------*/
/*  FindArticle: This methode looks for the first item with ArtikelNr and     */
/*  InhibitManualUpdate bit is on. ET2->16                                    */
/*----------------------------------------------------------------------------*/
pxOrderItem* pxOrderItemList::getItemInhibitManualUpdateByArticleNo(const long ArtikelNr )
{
    pxOrderItem*  entryp = NULL;
    pxOrderItemListIter cursor(*this);
    while ( (entryp = (pxOrderItem*) ++cursor) != NULL )
    {
        if( entryp->ArtikelNr() == ArtikelNr && entryp->IsSperreRabattManuell() )
        {
            break;
        }
    }
    return entryp;
}

void pxOrderItem :: InitOrderItem(tKDAUFTRAGPOS& rp)
{
    memset(&rp, 0, sizeof(tKDAUFTRAGPOS));

    rp.Rabatthilfe        = ' ';
    strcpy(rp.Rabattfaehig, "00");
    rp.StationNr      [0] = ' ';
    rp.LagerFachNr    [0] = ' ';
    rp.Zuzahlung          = ' ';
    rp.Bemerkungen    [0] = ' ';
    rp.BewegungsArt       = ' ';
}

int pxOrderItem::Read(const void *record)
{
    return pxPositionRead((tKDAUFTRAGPOS*)record);
}

int pxOrderItem::Delete(const void *record)
{
    return pxPositionDelete((tKDAUFTRAGPOS*)record);
}

int pxOrderItem::ReadLock(const void *record)
{
    return pxPositionReadLock((tKDAUFTRAGPOS*)record);
}

int pxOrderItem::Insert(const void *record)
{
    return pxPositionInsert((tKDAUFTRAGPOS*)record);
}

int pxOrderItem::Update(const void *record)
{
    return pxPositionUpdate((tKDAUFTRAGPOS*)record);
}

/*----------------------------------------------------------------------------*/
/*  Set Bemerkungen under respect of an existing RestDeliverery Pos           */
/*  This methode takes care for bem = "BRxxx". It prevents writing            */
/*  dp->Bemerkungen with text behind BRxxx, because the invoice program does  */
/*  not handle such positions                                                 */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: Bemerkungen
(
    const nString& bem,
    const long lPosNr
)
{
    Bemerkungen_     = bem;
    if (Session()->Device()->IsVideo())
    {
        if (IsNachliefern())      // there should exist a deliverypos entry
        {
            if ( AuxDelList() )
            {
                pxVerbund::subsequentDelivery::pxDeliveryPos* dp = AuxDelList_->Find(KdAuftragNr_, PosNr_, pxVerbund::subsequentDelivery::pxDPT_RESTDELIVERY_ITEM);
                if (dp && dp->IsRestDeliveryItem())
                {
                    dp->nDBBeginTransaction(cDBTransRecord);
                    if ( dp->Get(cDBGET_FORUPDATE) == 0 )
                    {
                        int length = 0;
                        nString dpbemwork = bem;
                        nString dpbem = bem;
                        dpbemwork.Trim(2);

                        if ( dpbemwork == "BR" )
                        {
                            length = static_cast<int>(dpbem.FindChar(' '));
                            dpbem.Trim(length);
                            dp->SetBemerkungen(dpbem);
                        }
                        else
                        {
                            dp->SetBemerkungen(bem);
                        }
                        dp->Put();
                    }
                    if (dp->IsGoodState() )
                    {
                        dp->nDBCommit(cDBTransRecord);     // commit changes
                    }
                    else
                    {
                        dp->nDBRollBack();
                    }
                }
            }
        }

        if ( LinkPosNr() > 0 && IsGoodState() && lPosNr == 0 )
        {
            pxOrderItem* ibtpos = (pxOrderItem*)Order().ItemList()->At(this->LinkPosNr() - 1);
            if (ibtpos) // get item
            {
                ibtpos->nDBBeginTransaction(cDBTransRecord);
                ibtpos->Bemerkungen(bem,LinkPosNr());
                ibtpos->SetDirty();
                ibtpos->Put();
                if (ibtpos->IsGoodState() )
                {
                    ibtpos->nDBCommit(cDBTransRecord);     // commit changes
                }
                else
                {
                    ibtpos->nDBRollBack();
                }
            }
        }
    }
    SetDirty();
    return ErrorState();
}

/*----------------------------------------------------------------------------*/
/*  SetArticleCodeValues                                                      */
/*  This methode sets the values of CodeType and ArticleCode into this object */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: SetArticleCodeValues
(
    const short   CodeType,
    const nString& ArticleCode,
    bool anyway
)
{
    nString aCode;
    aCode = this->ArticleCode();
    aCode.Strip();                   // delete blanks
    if ( aCode == "" || anyway )     // auf jeden Fall übernehmen
    {
        CodeType_      = CodeType;
        ArticleCode_   = ArticleCode;
        SetDirty();
    }

    if ( IsAuxPosted() )
    {
        nDBBeginTransaction(cDBTransRecord);
        try
        {
            Order().getIbtRequestHandler().setArticleCodeValues(this, CodeType_, ArticleCode_());
        }
        catch (nError& err)
        {
            Error() = err;
            return ErrorState();
        }
        nDBCommit(cDBTransRecord);
    }
    else if (IsDisponieren())
    {
        pxVerbund::subsequentDelivery::pxDeliveryPos* dp = 
            AuxDelList()->Find(KdAuftragNr_, PosNr_, pxVerbund::subsequentDelivery::pxDPT_DISPOSAL_ITEM);
        if (dp)
        {
            dp->nDBBeginTransaction(cDBTransRecord);
            dp->SetArticleCodeValues(CodeType_, ArticleCode_);
            dp->Put();
            if ( !dp->IsGoodState() )
            {
                Error() = (dp->Error());         // copy error object instance
                return ErrorState();
            }
            dp->nDBCommit(cDBTransRecord);
        }
    }
    else if (IsNachliefern())
    {
        pxVerbund::subsequentDelivery::pxDeliveryPos* dp =
            AuxDelList()->Find(KdAuftragNr_, PosNr_, pxVerbund::subsequentDelivery::pxDPT_RESTDELIVERY_ITEM);
        if (dp)
        {
            dp->nDBBeginTransaction(cDBTransRecord);
            dp->SetArticleCodeValues(CodeType_, ArticleCode_);
            dp->Put();
            if ( !dp->IsGoodState() )
            {
                Error() = (dp->Error());         // copy error object instance
                return ErrorState();
            }
            dp->nDBCommit(cDBTransRecord);
        }
    }

    return ErrorState();
}

/*----------------------------------------------------------------------------*/
/*  DeletePromotionCollectList                                                */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: DeletePromotionCollectList
(
)
{
    int   retval = 0;
    if ( PromoCollectList_ )
    {
        delete PromoCollectList_;
        PromoCollectList_ = NULL;
    }
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  DeleteItemDiscountList                                                    */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: DeleteItemDiscountList
(
)
{
    int   retval = 0;
    if ( ItemDiscountList_ )
    {
        delete ItemDiscountList_;
        ItemDiscountList_ = NULL;
    }
    return retval;
}

/*----------------------------------------------------------------------------*/
void pxOrderItem::SetDiscountArticleNo( long num )
{
    BLOG_TRACE_METHOD( libcsc::LoggerPool::getLoggerOrderItem(), "pxOrderItem::SetDiscountArticleNo()" );

    if ( libcsc::LoggerPool::getLoggerOrderItem().isEnabledFor( log4cplus::TRACE_LOG_LEVEL ) )
    {
        std::stringstream ss;
        ss << "num == " << num;
        libcsc::LoggerPool::getLoggerOrderItem().forcedLog( log4cplus::TRACE_LOG_LEVEL, ss.str().c_str(), __FILE__, __LINE__ );
    }

    DiscountArticleNo_ = num;
}

/*----------------------------------------------------------------------------*/
