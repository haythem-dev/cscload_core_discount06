/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

Implementation of class pxDiscount methods.

REVISION HISTORY

01 Nov 2005 V1.00 REV 00 written by Ysbrand Bouma.
*/

#include "pxdiscount.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"
#include "pxitem.hpp"
#include "pxorder.hpp"
#include "pxcstpaymentterms.hpp"
#include "pxdonepromoquotas.hpp"
#include "pxcstbas.hpp"
#include "pxordtyp.hpp"
#include "pxcstot.hpp"
#include "pxcustpharmgroup.hpp"
#include "pxbase/pxconstants.hpp"
#include <logger/loggerpool.h>

extern bool pxGlobalDataBaseSort;

/*----------------------------------------------------------------------------*/
/*  DiscountSpec->BestBay table Used for the HR rebate calculation            */
/*----------------------------------------------------------------------------*/
struct DiscountSpecTabEntry
{
    short  DiscountSpec;             // discountspec
    short  BestBuyType;              // corresponding bestbuy type(kdauftragposrab->DiscountType(not good))
};

static DiscountSpecTabEntry DiscountSpecBestbuyTable[]=
{
    {(short)DiscSpec_WholeSale      ,(short)BestBuy_ValuePctWholeSale},
    {(short)DiscSpec_Retail         ,(short)BestBuy_ValuePctRetail},
    {(short)DiscSpec_WholeSale_Ind  ,(short)BestBuy_ValuePctWholeSaleInd}
};

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxDiscount :: pxDiscount
(
    pxSession   *session
)
    : pxDBRecord(session)
{
    Init();
}

/*----------------------------------------------------------------------------*/
/*  Copy constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxDiscount :: pxDiscount
(
    pxDiscount& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tDISCOUNT structure to construct this instance.                       */
/*----------------------------------------------------------------------------*/
pxDiscount :: pxDiscount
(
    pxSession  *session,
    tDISCOUNT& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Read constructors.                                                        */
/*----------------------------------------------------------------------------*/
pxDiscount :: pxDiscount
(
    pxSession   *session,
    short       BranchNo,               // Read via this type and
    long        ArticleNo               // this type
)
    : pxDBRecord(session)
{
    Init();
    BranchNo_   = BranchNo;
    ArticleNo_  = ArticleNo;
}

/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxDiscount :: ~pxDiscount()
{
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tDISCOUNT structure.           */
/*----------------------------------------------------------------------------*/
tDISCOUNT&
Assign
(
    tDISCOUNT&           dest,
    const pxDiscount&    src
)
{
    dest.BranchNo                  = src.BranchNo_               ;
    dest.ArticleNo                 = src.ArticleNo_              ;
    dest.DiscountGrpNo             = src.DiscountGrpNo_          ;
    dest.PharmacyGroupId[0] = ' ';
    src.PharmacyGroupId_.GetData(dest.PharmacyGroupId);
    dest.CustomerNo                = src.CustomerNo_             ;
    dest.GrpDiscountTyp            = src.GrpDiscountTyp_         ;
    dest.DateFrom                  = src.DateFrom_.GetYYYYMMDD() ;
    dest.DateTo                    = src.DateTo_.GetYYYYMMDD()   ;
    dest.BaseQty                   = src.BaseQty_                ;
    dest.DiscountSpec              = src.DiscountSpec_           ;
    dest.DiscountType              = src.DiscountType_           ;
    dest.DiscountQty               = src.DiscountQty_            ;
    dest.DiscountValuePct          = src.DiscountValuePct_       ;
    dest.DiscountQtyPct            = src.DiscountQtyPct_         ;
    dest.SurchargePct              = src.SurchargePct_           ;
    dest.PharmGrpExcluded[0] = ' ';
    src.PharmGrpExcluded_.GetData(dest.PharmGrpExcluded)         ;
    dest.FixedPrice                = src.FixedPrice_             ;
    dest.RefundPct                 = src.RefundPct_              ;
    dest.InternalDiscount          = src.InternalDiscount_       ;
    dest.DiscountArticle           = src.DiscountArticle_        ;
    dest.PharmGrpExcluded_2[0] = ' ';
    src.PharmGrpExcluded_2_.GetData(dest.PharmGrpExcluded_2)     ;
    dest.PharmGrpExcluded_3[0] = ' ';
    src.PharmGrpExcluded_3_.GetData(dest.PharmGrpExcluded_3)     ;
    dest.Base_Value                = src.BaseValue_              ;
    dest.Base_Mult_STD_Qty         = src.BaseMultSTDQty_         ;
    dest.No_Multiple_Qty           = src.NoMultipleQty_          ;
    dest.FixedDiscountValue        = src.FixedDiscountValue_     ;
    dest.ManufacturerNo            = src.ManufacturerNo_         ;
    dest.ArtCategoryNo             = src.ArtCategoryNo_          ;
    dest.PaymentTargetNo           = src.PaymentTargetNo_        ;
    dest.GrossProfitPct            = src.GrossProfitPct_         ;
    dest.AddonDiscountOk           = src.AddonDiscountOk_        ;
    dest.PaymentTermType           = src.PaymentTermType_        ;
    dest.TargetQty                 = src.TargetQty_              ;
    dest.ExceedancePct             = src.ExceedancePct_          ;
    dest.RefundType                = src.RefundType_             ;
    dest.Article_No_Pack           = src.ArticleNoPack_          ;
    dest.RefundValue               = src.RefundValue_            ;
    dest.Promotion_No              = src.PromotionNo_            ;
    dest.MaxQty                    = src.MaxQty_                 ;
    dest.TurnOverCalcImpact        = src.TurnOverCalcImpact_     ;
    dest.AddonDiscount             = src.AddonDiscount_          ;
    dest.MonthlyDiscount           = src.MonthlyDiscount_        ;
    dest.DiscountCalcFrom          = src.DiscountCalcFrom_       ;
    dest.DiscountApplyTo           = src.DiscountApplyTo_        ;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tDISCOUNT structure to                     */
/*  a pxDiscount object.                                                      */
/*----------------------------------------------------------------------------*/
pxDiscount&
Assign
(
    pxDiscount&         dest,
    const tDISCOUNT&    src
)
{
    dest.BranchNo_                 = src.BranchNo                ;
    dest.ArticleNo_                = src.ArticleNo               ;
    dest.DiscountGrpNo_            = src.DiscountGrpNo           ;
    dest.PharmacyGroupId_          = src.PharmacyGroupId         ;
    dest.CustomerNo_               = src.CustomerNo              ;
    dest.GrpDiscountTyp_           = src.GrpDiscountTyp          ;
    dest.DateFrom_                 = nDate(src.DateFrom)         ;
    dest.DateTo_                   = nDate(src.DateTo)           ;
    dest.BaseQty_                  = src.BaseQty                 ;
    dest.DiscountSpec_             = src.DiscountSpec            ;
    dest.DiscountType_             = src.DiscountType            ;
    dest.DiscountQty_              = src.DiscountQty             ;
    dest.DiscountValuePct_         = src.DiscountValuePct        ;
    dest.DiscountQtyPct_           = src.DiscountQtyPct          ;
    dest.SurchargePct_             = src.SurchargePct            ;
    dest.PharmGrpExcluded_         = src.PharmGrpExcluded        ;
    dest.FixedPrice_               = src.FixedPrice              ;
    dest.RefundPct_                = src.RefundPct               ;
    dest.InternalDiscount_         = src.InternalDiscount        ;
    dest.DiscountArticle_          = src.DiscountArticle         ;
    dest.PharmGrpExcluded_2_       = src.PharmGrpExcluded_2      ;
    dest.PharmGrpExcluded_3_       = src.PharmGrpExcluded_3      ;
    dest.BaseValue_                = src.Base_Value              ;
    dest.BaseMultSTDQty_           = src.Base_Mult_STD_Qty       ;
    dest.NoMultipleQty_            = src.No_Multiple_Qty         ;
    dest.FixedDiscountValue_       = src.FixedDiscountValue      ;
    dest.ManufacturerNo_           = src.ManufacturerNo          ;
    dest.ArtCategoryNo_            = src.ArtCategoryNo           ;
    dest.PaymentTargetNo_          = src.PaymentTargetNo         ;
    dest.GrossProfitPct_           = src.GrossProfitPct          ;
    dest.AddonDiscountOk_          = src.AddonDiscountOk         ;
    dest.PaymentTermType_          = src.PaymentTermType         ;
    dest.TargetQty_                = src.TargetQty               ;
    dest.ExceedancePct_            = src.ExceedancePct           ;
    dest.RefundType_               = src.RefundType              ;
    dest.ArticleNoPack_            = src.Article_No_Pack         ;
    dest.RefundValue_              = src.RefundValue             ;
    dest.PromotionNo_              = src.Promotion_No            ;
    dest.MaxQty_                   = src.MaxQty                  ;
    dest.TurnOverCalcImpact_       = src.TurnOverCalcImpact      ;
    dest.AddonDiscount_            = src.AddonDiscount           ;
    dest.MonthlyDiscount_          = src.MonthlyDiscount         ;
    dest.DiscountCalcFrom_         = src.DiscountCalcFrom        ;
    dest.DiscountApplyTo_          = src.DiscountApplyTo         ;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxDiscount :: Init()
{
    tDISCOUNT record;
    memset(&record, 0, sizeof(tDISCOUNT));
    Assign(*this, record);
    RemainInList_ = false;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tDISCOUNT struct and then imported to self.                               */
/*----------------------------------------------------------------------------*/
pxDiscount&
pxDiscount :: operator=( const pxDiscount& src)
{
    tDISCOUNT record;               // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tDISCOUNT structure 'src' to                     */
/*  this instance.                                                            */
/*----------------------------------------------------------------------------*/
pxDiscount&
pxDiscount :: operator=( const tDISCOUNT& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxDiscount :: Get
(
    DBAccessMode mode
)
{
    tDISCOUNT record;
    memset(&record, 0, sizeof(tDISCOUNT));
    int retval = ( mode == cDBGET_FORUPDATE ) ? nDBReadLock(&record) : nDBRead(&record);
    if (!retval)
        (*this)= record;        // import the data from tDISCOUNT struct
    /* else if ( retval > cDBXR_NORMAL )
        ExternalCondition(CMsgStream(), CMSG_AD_DELPOS_NOTFOUND, KdAuftragNr_,PosNr_);
    */
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxDiscount :: Read
(
    const void *record
)
{
    return pxDiscountRead((tDISCOUNT*)record);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxDiscount list objects being inserted in the                  */
/*  following ascending sequence:                                             */
/*  KdAuftragNr,PosNr                                                         */
/*----------------------------------------------------------------------------*/
int
pxDiscount :: CompareTo
(
    const nCollectable   *That,
          void           * /* p */,
    const long           /* lparm */
)   const
{
    if ( pxGlobalDataBaseSort )
        return  0;

    pxDiscount *that = (pxDiscount*)That;
    int retval = (DiscountType_ == that->DiscountType_) ? 0
               : (DiscountType_ > DiscountType_ ? 1 : -1);

    if ( retval == 0 )
        retval = (BaseQty_ == that->BaseQty_) ? 0
               : (BaseQty_ > that->BaseQty_ ? 1 : -1);

   /* if ( retval == 0 )
        retval = (DateFrom_ == that->DateFrom_) ? 0
               : (DateFrom_ > that->DateFrom_ ? 1 : -1);
   */
    if ( retval == 0 )
        retval = (DiscountQty_ == that->DiscountQty_) ? 0
               : (DiscountQty_ > that->DiscountQty_ ? 1 : -1);

    if ( retval == 0 )
        retval = (FixedPrice_ == that->FixedPrice_) ? 0
               : (FixedPrice_ > that->FixedPrice_ ? 1 : -1);

    if ( retval == 0 )
        retval = (DiscountValuePct_ == that->DiscountValuePct_) ? 0
               : (DiscountValuePct_ > that->DiscountValuePct_ ? 1 : -1);

    if ( retval == 0 )
        retval = (PharmacyGroupId_ == that->PharmacyGroupId_) ? 0
               : (PharmacyGroupId_ > that->PharmacyGroupId_ ? 1 : -1);

    return retval;
}

/*----------------------------------------------------------------------------*/
/*  CalcDiscountQty: This methode calculates the real discountqty             */
/*  on this pxDiscount entry depend on the given quantity to post             */
/*  Returns the correct discountqty                                           */
/*----------------------------------------------------------------------------*/
long
pxDiscount :: CalcDiscountQty
(
    const long QToPost
)
{
    long            q = QToPost;
    long  discountqty = 0;


    if ( BaseQty_ == 0 )
    {
        discountqty  += DiscountQty_;
        return discountqty;
    }

    while ( q >= BaseQty_ )
    {                                // as long as this entry fits:
        discountqty  += DiscountQty_;
        q            -= BaseQty_;
        if ( IsNonProportional() )
            break;
    }
    return discountqty;
}

/*----------------------------------------------------------------------------*/
/* ConvertDiscountSpecToBestBuy:                                              */
/* This function converts discountspec to best buy type.                      */
/* The best buy type is unfortunately used as memeber discounttype within     */
/* the table kdauftragposrab(contains calculated rebates for one article)     */
/* The fuction is used in the croatian orderentry application.                */
/*----------------------------------------------------------------------------*/
short
pxDiscount :: ConvertDiscountSpecToBestBuy
(
    const short bestbuy
)
{
    short BestBuy = bestbuy;                              //
    int x = sizeof(DiscountSpecBestbuyTable) / sizeof(DiscountSpecTabEntry);  // index calculation

    for (int i = 0; i < x; i++)
    {
        if ( DiscountSpec_ == DiscountSpecBestbuyTable[i].DiscountSpec )
        {
            BestBuy = DiscountSpecBestbuyTable[i].BestBuyType;         // match
            break;
        }
    }
    return BestBuy;
}

enum tDiscountCategory
pxDiscount::GetDiscountCategory() const
{
    if (CustomerNo_ > 0)
    {
        return DiscCategory_Customer;
    }
    else if (PharmacyGroupId_ != "000" && false == PharmacyGroupId_.IsEmpty())
    {
        return DiscCategory_PharmacyGroup;
    }
    return DiscCategory_Common;
}

/*----------------------------------------------------------------------------*/
/*  List Constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxDiscountList :: pxDiscountList
(
    pxSession   *session
)
    : nDBRecordSet(session)
{
    nDBSetList(this);

    for (KindOffRebateIndex_ = 0;KindOffRebateIndex_ < cMaxKindOffRebate;++KindOffRebateIndex_)
    {
        ArrayKindOffRebate_[KindOffRebateIndex_] = 0;
    }
    KindOffRebateIndex_ = 0;

    for (CasCadeNoIndex_ = 0;CasCadeNoIndex_ < cMaxCasCadeNo;++CasCadeNoIndex_)
    {
        ArrayCasCadeNo_[CasCadeNoIndex_] = 0;
    }
    CasCadeNoIndex_ = 0;
    ArtikelNr_      = 0;
}

/*----------------------------------------------------------------------------*/
/*  Initialize and do selection of all records.                               */
/*----------------------------------------------------------------------------*/
size_t
pxDiscountList :: Select
(
    const int     count_
)
{
    tDISCOUNT fil;
    memset(&fil, 0, sizeof(tDISCOUNT));  // zero out entire record buffer
    int cursorid = cCRS_NOWHERE;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Initialize and do selection via KdAuftragNr, PosNr                        */
/*----------------------------------------------------------------------------*/
size_t
pxDiscountList :: Select
(
    const short   BranchNo,
    const long    ArticleNo,
    const int     count_
)
{
    tDISCOUNT fil;
    memset(&fil, 0, sizeof(tDISCOUNT));  // zero out entire record buffer
    fil.BranchNo  = BranchNo;
    fil.ArticleNo = ArticleNo;
    int cursorid = cCRS_DEFAULT;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Initialize and do selection via KdAuftragNr, PosNr                        */
/*----------------------------------------------------------------------------*/
size_t
pxDiscountList :: Select
(
    const short   BranchNo,
    const long    ArticleNo,
    const long    CustomerNo,
    const int     count_
)
{
    tDISCOUNT fil;
    memset(&fil, 0, sizeof(tDISCOUNT));  // zero out entire record buffer
    fil.BranchNo   = BranchNo;
    fil.ArticleNo  = ArticleNo;
    fil.CustomerNo = CustomerNo;
    int cursorid   = cCRSDISCOUNT_BRARTCUST;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Initialize and do selection via Customer number                           */
/*----------------------------------------------------------------------------*/
size_t
pxDiscountList :: Select
(
    const short   BranchNo,
    const long    ArticleNo,
    const short   Discounttype,
    const int     count_
)
{
    tDISCOUNT fil;
    memset(&fil, 0, sizeof(tDISCOUNT));  // zero out entire record buffer
    fil.BranchNo        = BranchNo;
    fil.ArticleNo       = ArticleNo;
    fil.DiscountType    = Discounttype;
    int cursorid        = cCRSDISCOUNT_DISCOUNTTYPE;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

//----------------------------------------------------------------------------
//  Initialize and do selection via
//  branch no, article no, customer no, manufacturer no
//  Author: Bea
//  Version: 01.07.2009
//----------------------------------------------------------------------------
size_t
pxDiscountList :: Select
(
    const int     CacadeNo,
    const short   BranchNo,
    const long    ArticleNo,
    const long    CustomerNo,
    const long    ManufacturerNo,
    const short   DiscountSpec,
    const int     count_
)
{
    tDISCOUNT fil;
    memset(&fil, 0, sizeof(tDISCOUNT));  // zero out entire record buffer
    fil.BranchNo   = BranchNo;
    fil.ArticleNo  = ArticleNo;
    fil.CustomerNo = CustomerNo;
    fil.ManufacturerNo = ManufacturerNo;
    fil.DiscountSpec = DiscountSpec;

    int cursorid=-1;

    switch(CacadeNo)
    {
    case CASCADE_OCCASIONS:
        cursorid  = cCRSDISCOUNT_BROCCASIONS;
        break;
    case CASCADE_ART_AND_MAN_0:
        cursorid  = cCRSDISCOUNT_BRARTMAN_0;
        break;
    case CASCADE_ART_AND_MAN_1:
        cursorid  = cCRSDISCOUNT_BRARTMAN_1;
        break;
    case CASCADE_ARTICLE_0:
        cursorid  = cCRSDISCOUNT_BRART_0;
        break;
    case CASCADE_ARTICLE_1:
        cursorid  = cCRSDISCOUNT_BRART_1;
        break;
    case CASCADE_MANUFACTURER_0:
        cursorid  = cCRSDISCOUNT_BRARTMANUFACTURER_0;
        break;
    case CASCADE_MANUFACTURER_1:
        cursorid  = cCRSDISCOUNT_BRARTMANUFACTURER_1;
        break;
    case CASCADE_ARTICLEGROUP_0:
        cursorid  = cCRSDISCOUNT_BRMANCUSTARTGRP_0;
        break;
    case CASCADE_ARTICLEGROUP_1:
        cursorid  = cCRSDISCOUNT_BRMANCUSTARTGRP_1;
        break;
    case CASCADE_CUSTOMER:
        cursorid  = cCRSDISCOUNT_BRCUST;
        break;
    case CASCADE_PHARMACYGROUP:
        cursorid  = cCRSDISCOUNT_BRCUSTGRP;
        break;
    case CASCADE_SINGLEART_0:
        cursorid  = cCRSDISCOUNT_BRSINGLEART_0;
        break;
    case CASCADE_SINGLEART_1:
        cursorid  = cCRSDISCOUNT_BRSINGLEART_1;
        break;
    case CASCADE_PROMOTION_0:
        {
            pxGlobalDataBaseSort = true;
            cursorid  = cCRSDISCOUNT_BRPROMOTION_0;
            break;
        }
    case CASCADE_PROMOTION_1:
        {
            pxGlobalDataBaseSort = true;
            cursorid  = cCRSDISCOUNT_BRPROMOTION_1;
            break;
        }
    case CASCADE_ALL_PROMOTIONS:
        cursorid  = cCRSDISCOUNT_BRALLPROMOTIONS;
        break;
    }

    nDBSelect(&fil, cursorid, count_);
    pxGlobalDataBaseSort = false;

    return Entries();
}

//----------------------------------------------------------------------------
//  Initialize and do selection via
//  branch no, article no, customer no, discountgrpno = 0
//----------------------------------------------------------------------------
size_t
pxDiscountList :: Select
(
    const int     CacadeNo,
    const short   BranchNo,
    const long    ArticleNo,
    const long    CustomerNo,
    const int     count_
)
{
    tDISCOUNT fil;
    memset(&fil, 0, sizeof(tDISCOUNT));  // zero out entire record buffer
    fil.BranchNo   = BranchNo;
    fil.ArticleNo  = ArticleNo;
    fil.CustomerNo = CustomerNo;

    int cursorid=-1;

    switch(CacadeNo)
    {
    case CASCADE_JUST_JOIN_PHARMACYGROUP:
        cursorid  = cCRSDISCOUNT_JOIN_CSTPHARMGRP ;
        break;
    case CASCADE_JUST_JOIN_PHARMACYGROUP_1:
        cursorid = cCRSDISCOUNT_JOIN_CSTPHARMGRP_1;
        break;
	case CASCADE_JUST_JOIN_PHARMACYGROUP_2:
		cursorid = cCRSDISCOUNT_JOIN_CSTPHARMGRP_2;
		break;
    case  CASCADE_JUST_PHARMACYGROUP_ZERO:
        cursorid  = cCRSDISCOUNT_BRCUSTGRP_0;
        break;
    }

    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Initialize and do selection via BrancNo,DiscountGrpNo, PharmacyGroupId    */
/*----------------------------------------------------------------------------*/
size_t
pxDiscountList :: SelectRange
(
    const short   BranchNo,
    const long    DiscountGrpNo,
    const long    CustomerNo,
    const int     count_
)
{
    tDISCOUNT fil;

    memset(&fil, 0, sizeof(tDISCOUNT));  // zero out entire record buffer
    fil.BranchNo        = BranchNo;
    fil.DiscountGrpNo   = DiscountGrpNo;
    fil.CustomerNo      = CustomerNo;
    int cursorid        = cCRSDISCOUNT_DISCOUNTGRP;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Initialize and do selection via BrancNo,ArticleNo, Discounttype and       */
/*  PharmacyGroupId                                                           */
/*----------------------------------------------------------------------------*/
size_t
pxDiscountList :: Select
(
    const short   BranchNo,
    const long    ArticleNo,
    const short   Discounttype,
    nString&      PharmacyGroupId,
    const int     count_
)
{
    tDISCOUNT fil;
    memset(&fil, 0, sizeof(tDISCOUNT));  // zero out entire record buffer
    fil.BranchNo        = BranchNo;
    fil.ArticleNo       = ArticleNo;
    fil.DiscountType    = Discounttype;
    fil.PharmacyGroupId[0] = ' ';
    PharmacyGroupId.GetData(fil.PharmacyGroupId);
    int cursorid        = cCRSDISCOUNT_SHORT_LIST ;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Initialize and do selection via BranchNo,ArticleNo,CustomerNo             */
/*----------------------------------------------------------------------------*/
size_t
pxDiscountList :: SelectPromotion
(
    const short   BranchNo,
    const short   PromotionNo,
    const long    ArticleNo,
    const long    CustomerNo,
    const short   DiscountSpec,
    const int     count_
)
{
    tDISCOUNT fil;

    memset(&fil, 0, sizeof(tDISCOUNT));  // zero out entire record buffer
    fil.BranchNo      = BranchNo;
    fil.Promotion_No  = PromotionNo;
    fil.ArticleNo     = ArticleNo;
    fil.CustomerNo    = CustomerNo;
    fil.DiscountSpec  = DiscountSpec;
    int cursorid      = cCRSDISCOUNT_BRPROMOTIONNO;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Reduce a list of discount-in-kind table entries to contain only valid     */
/*  offers.                                                                   */
/*----------------------------------------------------------------------------*/
int
pxDiscountList :: ReduceToValidOffers
(
    const long QOrdered
)
{
/*----------------------------------------------------------------------------*/
/*  Scan the list and delete all expired offers.                              */
/*----------------------------------------------------------------------------*/
    pxDiscount    *dikp;               // ptr to list entry
    nDate         today;               // this days date
    //short         Discounttype;
    //bool          DiscountQtyAvailable = false;
    //size_t        countNatra = 0;

    pxDiscountListIter  cursor(*this);  // define an iterator
    while ( (dikp = (pxDiscount*) ++cursor) != NULL )
    {
        if ( (today > dikp->DateTo_ || today < dikp->DateFrom_))
            delete cursor.Remove();       // offer expired
        if ( QOrdered > 0 && Session()->isSwitzerland() )
        {
            if ( dikp->BaseQty() > 0 )
            {
                if ( QOrdered < dikp->BaseQty() )
                {
#ifdef CHDISCLOG
                    std::stringstream v;
                    v << "pxDiscountList::ReduceToValidOffers() - Discount removed";
                    v << ": BranchNo = " << dikp->BranchNo();
                    v << ", ArticleNo = " << dikp->ArticleNo();
                    v << ", BaseQty = " << dikp->BaseQty();
                    v << ", DiscountType = " << dikp->DiscountType();
                    v << ", DiscountSpec = " << dikp->DiscountSpec();
                    v << ", DiscountGroupNo = " << dikp->DiscountGrpNo();
                    v << ", DiscountValuePct = " << dikp->DiscountValuePct();
                    v << ", DiscountQty = " << dikp->DiscountQty();
                    v << ", DiscountQtyPct = " << dikp->DiscountQtyPct();
                    v << ", BaseValue = " << dikp->BaseValue();
                    v << ", MaxQty = " << dikp->MaxQty();
                    v << ", SurchargePct = " << dikp->SurchargePct();
                    v << ", RefundPct = " << dikp->RefundPct();
                    BLOG_DEBUG(libcsc::LoggerPool::getLoggerDiscountCalc(), v.str());
#endif
                    delete cursor.Remove();       // offer does not fitt
                }
            }
        }
    }

/*----------------------------------------------------------------------------*/
/*  Look for combined entries barrabbat + Natra in the Swiss application.     */
/*----------------------------------------------------------------------------*/
/*    if (Session()->isSwitzerland())
    {
        cursor.Reset();
        while ( (dikp = (pxDiscount*) ++cursor) != NULL )
        {
            if ( dikp->DiscountQty() > 0 )
            {
                DiscountQtyAvailable = true;
                ++countNatra;
            }
        }
    }
*/
/*----------------------------------------------------------------------------*/
/*  Delete invalid offers. Only offers with the lowest duration are considered*/
/*  to be the actual ones.                                                    */
/*----------------------------------------------------------------------------*/
/*
    if (Session()->isSwitzerland() && DiscountQtyAvailable)
    {
        if ((Entries() == countNatra) || (countNatra > 0))
        {
            for ( Discounttype = DiscType_Default; Discounttype != DiscType_Last; Discounttype++ )
            {
                DeleteInvalidOffers(Discounttype);
            }
        }
    }*/
    return static_cast<int>(Entries());
}

/*----------------------------------------------------------------------------*/
/*  Within a term group and a discount code, the offers with lowest duration  */
/*  time are considered to be the valid offers for a discount calculation.    */
/*  All other offers are removed from the list and deleted.                   */
/*----------------------------------------------------------------------------*/
void
pxDiscountList :: DeleteInvalidOffers
(
    short Discounttype
)
{
    long lduration = 256*256*256;      // init to max duration
    long duration;                     // duration of current entry
    pxDiscount *curp = NULL;                   // ptr to current entry
    pxDiscount *lowp = NULL;                   // ptr to entry with lowest duration
    pxDiscountListIter  cursor(*this);  // define an iterator

/*----------------------------------------------------------------------------*/
/*  Find lowest duration within group.                                        */
/*----------------------------------------------------------------------------*/
    while ( (curp = (pxDiscount*) ++cursor) != NULL )
    {
        if ( Discounttype == curp->DiscountType_)
        {
            if ( (duration = curp->DateTo_ - curp->DateFrom_) < lduration )
            {
                lduration = duration;      // this one is low
                lowp = curp;               // hold its pointer
            }
        }
    }

/*----------------------------------------------------------------------------*/
/*  Delete all other offers.                                                  */
/*----------------------------------------------------------------------------*/
    cursor.Reset();
    while ( (curp = (pxDiscount*) ++cursor) != NULL )
    {
        if ( Discounttype == curp->DiscountType_)
        {
            if (curp->DateTo_ != lowp->DateTo_ || curp->DateFrom_ != lowp->DateFrom_ )
            {
                delete cursor.Remove();
            }
        }
    }
}

/*----------------------------------------------------------------------------*/
/*  Check NrIntern: This methode returns the NrIntern value of the first entry*/
/*----------------------------------------------------------------------------*/
char
pxDiscountList :: CheckNrIntern
(
)
{
    char  nrintern = '0';
    pxDiscount *curp;                   // ptr to current entry
    pxDiscountListIter  cursor(*this);  // define an iterator
    while ( (curp = (pxDiscount*) ++cursor) != NULL )
    {
        nrintern = curp->InternalDiscount_;
        break;
    }
    return nrintern;
}

//----------------------------------------------------------------------------
//  Checks, whether possibly further discounts are granted on top if this discount.
//  This is the case, if addondiscountok is set.
//----------------------------------------------------------------------------
bool
pxDiscountList :: CheckAddOnDiscountOK
(
)
{
    bool retval = false;
    pxDiscount *dikp;               // ptr to list entry
    pxDiscountListIter cursor(*this);  // define an iterator

    while ( (dikp = (pxDiscount*) ++cursor) != NULL )
    {
        if( dikp->IsAddonDiscountOk())
        {
            retval = true;
            break;
        }
    }

    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Shrink list to valid entries depend on hlist                              */
/*----------------------------------------------------------------------------*/
size_t
pxDiscountList :: Shrink
(
    pxCustPharmGroupList *hlist
)
{
    pxCustPharmGroupListIter cursor(*hlist);
    pxDiscountListIter  iter(*this);
    pxCustPharmGroup*   discinfop;
    pxDiscount*         artdikp;

/*----------------------------------------------------------------------------*/
/*  If there is a well constucted pxCustPharmGroupList containing entries,    */
/*  so shrink  the pxDiscountList depend on the pharmacygroupid of the        */
/*  pxCustPharmGroupList entries, otherwise delete all entries of the         */
/*  the pxDiscountList where PharmacyGroupId > 0                              */
/*----------------------------------------------------------------------------*/
    if (hlist > NULL)
    {
        while ( (discinfop  = (pxCustPharmGroup*) ++cursor) != NULL )
        {
            iter.Reset();
            while ( (artdikp = (pxDiscount*) ++iter) != NULL )
            {
                if (artdikp->PharmacyGroupId() == discinfop->PharmacyGroupId())
                    artdikp->SetRemainInList();
                if ( artdikp->PharmacyGroupId() == "000" )
                    artdikp->SetRemainInList();

                if ( hlist->Find(artdikp->PharmGrpExcluded()) ||
                     hlist->Find(artdikp->PharmGrpExcluded2())||
                     hlist->Find(artdikp->PharmGrpExcluded3()) )
                {
#ifdef CHDISCLOG
                    BLOG_DEBUG(libcsc::LoggerPool::getLoggerDiscountCalc(), "pxDiscountList::Shrink -> remove discount because of pharmacygroup exclusion");
#endif
                    delete iter.Remove();
                    continue;
                }
                if ( artdikp->CustomerNo() > 0 )
                {
                    if ( artdikp->CustomerNo() != discinfop->CustomerNo() )
                    {
#ifdef CHDISCLOG
                        BLOG_DEBUG(libcsc::LoggerPool::getLoggerDiscountCalc(), "pxDiscountList::Shrink -> remove discount because of different customer no");
#endif
                        delete iter.Remove();
                        continue;
                    }
                }
            }
        }
        iter.Reset();
        while ( (artdikp = (pxDiscount*) ++iter) != NULL )
        {
            if ( !artdikp->IsRemainInList() )
            {
#ifdef CHDISCLOG
                BLOG_DEBUG(libcsc::LoggerPool::getLoggerDiscountCalc(), "pxDiscountList::Shrink -> remove discount because of remaining article list");
#endif
                delete iter.Remove();
            }
        }
    }
    else
    {
        iter.Reset();
        while ( (artdikp = (pxDiscount*) ++iter) != NULL )
        {
#ifdef CHDISCLOG
            BLOG_DEBUG(libcsc::LoggerPool::getLoggerDiscountCalc(), "pxDiscountList::Shrink -> remove discount because of pharmacy group id > 000");
#endif
            if ( artdikp->PharmacyGroupId() > "000")
            {
                delete iter.Remove();
            }
        }
    }
    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  ShrinkRangePharmacyGroup shrink list to valid entries depend on hlist     */
/*----------------------------------------------------------------------------*/
size_t
pxDiscountList :: ShrinkRangePharmacyGroup
(
    pxCustPharmGroupList *hlist
)
{
    pxCustPharmGroupListIter cursor(*hlist);
    pxDiscountListIter  iter(*this);
    pxDiscount*         discp;
    bool bPharmgroupInList     = false;
    bool bManufacturerNoInList = false;

    if (hlist > NULL)
    {
        iter.Reset();
        while ( (discp = (pxDiscount*) ++iter) != NULL )
        {
            if ( hlist->Find(discp->PharmacyGroupId()) )
            {
                bPharmgroupInList = true;
                discp->SetRemainInList();
            }
            if ( discp->ManufacturerNo() > 0 )
            {
                bManufacturerNoInList = true;
                discp->SetRemainInList();
            }

            if ( hlist->Find(discp->PharmGrpExcluded()) ||
                 hlist->Find(discp->PharmGrpExcluded2())||
                 hlist->Find(discp->PharmGrpExcluded3()) )
            {
                delete iter.Remove();
                continue;
            }
        }

        if (  bPharmgroupInList && bManufacturerNoInList )
        {
            iter.Reset();
            while ( (discp = (pxDiscount*) ++iter) != NULL )
            {
                if ( !discp->IsRemainInList() )
                {
                    delete iter.Remove();
                }
            }
        }
    }
    return Entries();
}

//----------------------------------------------------------------------------
//  Shrink list to valid entries depending on what is valid for item:
//  health fund (KK) or voluntary sale (FF)
//  AND shrink to entries with valid baseqty (according to the order)
//  only active for Bulgaria
//----------------------------------------------------------------------------
size_t
pxDiscountList :: ShrinkPriceType
(
    pxOrderItem* item,
    long QOrdered
)
{
    pxDiscount *dikp;               // ptr to list entry
    pxDiscountListIter cursor(*this);  // define an iterator

    if(!item)  // error
    {
        return Entries();
    }

    bool blnOk = true;
    while ( (dikp = (pxDiscount*) ++cursor) != NULL )
    {
        blnOk = true;
        switch(dikp->DiscountSpec_)
        {
        case 0:
            // store freesale grossprofitpct for calculation for health fund (whole margin):
            //+++ gleiche Logik wie in discountutil.cpp:ComputeGrossProfitPct! Zusammenfassen!!!
            if(item->GrossProfitPctFV() <= pxConstants::dZero || dikp->GrossProfitPct_ < item->GrossProfitPctFV() ) // Attention: the less the GrossProfit, the more the discount for the customer
                if(dikp->GrossProfitPct_ > pxConstants::dZero)
                {
                    item->SetGrossProfitPctFV(dikp->GrossProfitPct_);
                }
            break;
        case DiscSpec_VoluntarySale: // this is for freesale and also for retail!
            // store freesale grossprofitpct for calculation for health fund (whole margin):
            //+++ gleiche Logik wie in discountutil.cpp:ComputeGrossProfitPct! Zusammenfassen!!!
            if(item->GrossProfitPctFV() <= pxConstants::dZero || dikp->GrossProfitPct_ < item->GrossProfitPctFV()) // Attention: the less the GrossProfit, the more the discount for the customer
            {
                if(dikp->GrossProfitPct_ > pxConstants::dZero)
                {
                    item->SetGrossProfitPctFV(dikp->GrossProfitPct_);
                }
            }
            if(HEALTHFUND_PRICE == item->PreisTyp())
                blnOk = false;
            break;
        case DiscSpec_HealthFund:
            if(HEALTHFUND_PRICE != item->PreisTyp())
                blnOk = false;
            break;
        }

        if(QOrdered < dikp->BaseQty())
            blnOk = false;

        if(!blnOk)
            delete cursor.Remove();       // offer has wrong PriceType (discount specification)
    }

    return Entries();
}

//----------------------------------------------------------------------------
//  Shrink list to valid entries reagarding product promotions:
//  If promotion with highest priority does not allow other promotions,
//  those are removed from the list.
//  Only active for Bulgaria
//----------------------------------------------------------------------------
size_t
pxDiscountList :: ShrinkPromotions
(
    pxOrderItem* item
)
{
    pxDiscount *dikp;               // ptr to list entry
    pxDiscountListIter cursor(*this);  // define an iterator
    pxCustBase* customer = (item->Order().Customer());
    pxDonePromoQuotasList* DonePromoList = customer->DonePromoQuotaList();
    const pxCustOrderType&  ot = item->Order().OrderType();

    if(!item)  // error
    {
        return Entries();
    }

    bool blnDeleteEverythingElse = false;
    short PromotionNo = 0;
    int count_ = 0;
    while ( (dikp = (pxDiscount*) ++cursor) != NULL )
    {
        if ( ot.IsSNoPromotions() &&  dikp->PromotionNo() > 0 )
        {
            delete cursor.Remove();
            continue;
        }

        // get first promotion (highest prio):
        if(0 == count_)
        {
            // if no promotion, do nothing
            if(0 == dikp->PromotionNo())
            {
                return Entries();
            }
            // check for fullfilled Promotionquota
            bool AddOnPromoDiscountOfProductPromo;
            if (   deleteCursorAndContinueOnFullfilledPromotionquota(DonePromoList, cursor, item)
                || deleteCursorAndContinueOnNotBySalesWeb(cursor, item, AddOnPromoDiscountOfProductPromo) )
            {
                continue;
            }

            // If promotion allows no further promotions, remove all following promotions from list.
            // Otherwise only those promotions have to be deleted, that have AddOnPromoDiscOk=false
            if(!AddOnPromoDiscountOfProductPromo)
            {
                blnDeleteEverythingElse = true;
                PromotionNo = dikp->PromotionNo();
            }
        }
        else
        {
            if(blnDeleteEverythingElse)
            {
                if ( dikp->PromotionNo() != PromotionNo )
                {
                    delete cursor.Remove();
                }
            }
            else
            {
                // check for fullfilled Promotionquota
                bool AddOnPromoDiscountOfProductPromo;
                if (   deleteCursorAndContinueOnFullfilledPromotionquota(DonePromoList, cursor, item)
                    || deleteCursorAndContinueOnNotBySalesWeb(cursor, item, AddOnPromoDiscountOfProductPromo) )
                {
                    continue;
                }

                // if promotion allow further promotions, only those promotions have to be deleted, that have AddOnPromoDiscOk=false
                if(!AddOnPromoDiscountOfProductPromo)
                {
                    delete cursor.Remove();
                }
            }
        }
        ++count_;
    }

    return Entries();
}

bool pxDiscountList::deleteCursorAndContinueOnFullfilledPromotionquota(pxDonePromoQuotasList* donePromoList, pxDiscountListIter& cursor, pxOrderItem* item)
{
    pxDiscount* dikp = (pxDiscount*)cursor.Current();

    if (donePromoList)
    {
        if (donePromoList->Find(dikp->PromotionNo(), item->ArtikelNr()))
        {
            delete cursor.Remove();
            return true;
        }
        else if (item->CheckPromoQuota(dikp->BranchNo(), dikp->PromotionNo(), dikp->BaseQty()))
        {
            pxDonePromoQuotas* DonePromoEntriep = new pxDonePromoQuotas(dikp->PromotionNo(), item->ArtikelNr());
            donePromoList->Append(DonePromoEntriep);
            delete cursor.Remove();
            return true;
        }
    }
    return false;
}

bool pxDiscountList::deleteCursorAndContinueOnNotBySalesWeb(pxDiscountListIter& cursor, pxOrderItem* item, bool& addOnPromoDiscountOfProductPromo)
{
    pxDiscount* dikp = (pxDiscount*)cursor.Current();

    bool addOnStdDiscountOfProductPromo;
    bool notBySalesWeb;
    item->GetAddOnFlags(dikp->PromotionNo(), addOnPromoDiscountOfProductPromo, addOnStdDiscountOfProductPromo, notBySalesWeb);
    if (notBySalesWeb)
    {
        delete cursor.Remove();
        return true;
    }
    return false;
}

//----------------------------------------------------------------------------
//  Shrink list to valid entries depending on cash payment for bulgaria
//  only active for Bulgaria
//----------------------------------------------------------------------------
size_t
pxDiscountList :: ShrinkCashPayment
(
    pxOrderItem* item
)
{
    if(!item)  // error
    {
        return Entries();
    }

    bool IsCashPayment = false;

    if("CO"==item->Order().KdAuftragArt() || item->Order().isCashOrder())
        IsCashPayment = true;

    pxCustBase& customer = *(item->Order().Customer());
    pxCstPaymentTermsList* PaymentTermsList=customer.CstPaymentTermsList();
    if(PaymentTermsList)
    {
        pxCstPaymentTerms*  PaymentTerms = PaymentTermsList->Find(item->PreisTyp());
        if(PaymentTerms)
        {
            if(PaymentTerms->PaymentTarget()<=0)
                IsCashPayment = true;
        }
    }

    if(IsCashPayment)  // nothing has to be deleted, cause all discounts are valid
        return Entries();

    pxDiscount *dikp;               // ptr to list entry
    pxDiscountListIter cursor(*this);  // define an iterator
    while ( (dikp = (pxDiscount*) ++cursor) != NULL )
    {
        //+++Bea Konstante für Barzahler
        if('1' == dikp->PaymentTermType_)
        {
            delete cursor.Remove();       // offer has wrong PriceType (discount specification)
        }
    }

    return Entries();
}

//----------------------------------------------------------------------------
//  Shrink list to entries with discountspec=0
//  only active for Serbia
//----------------------------------------------------------------------------
size_t
pxDiscountList :: ShrinkDiscountSpec
(
)
{
    pxDiscount     *dikp;               // ptr to list entry
    pxDiscountListIter  cursor(*this);  // define an iterator

    while ( (dikp = (pxDiscount*) ++cursor) != NULL )
    {
        if(0 != dikp->DiscountSpec_)
            delete cursor.Remove();       // offer has wrong PriceType (discount specification)
    }

    return Entries();
}

//----------------------------------------------------------------------------
//  This method scans the entire discount list and returns a reference to the
//  entry containing the highest cash discount.
//----------------------------------------------------------------------------
pxDiscount*
pxDiscountList :: BestBuyCash_dlist
(
    long QOrdered
)
{
    pxDiscount  *curp;
    pxDiscount  *bestp = NULL;         // init best-buy pointer
    pxDiscountListIter cursor((pxDiscountList&)*this); // cast away constness
    while ( (curp = (pxDiscount*) ++cursor) != NULL )
    {
        if(curp->IsValuePctCash())
        {
            if( (!bestp) || (bestp->DiscountValuePct() < curp->DiscountValuePct() && QOrdered >= curp->BaseQty()) )
                bestp = curp;              // far the best at this moment
//          else
//              delete cursor.Remove();      // this discount is not better than bestp
        }
    }
    return bestp;
}

//----------------------------------------------------------------------------
//  This method scans the entire discount list and returns a reference to the
//  entry containing the highest discount quantity.
//----------------------------------------------------------------------------
pxDiscount*
pxDiscountList :: BestBuyNatra_dlist
(
    long QOrdered
)
{
    pxDiscount  *curp;
    pxDiscount  *bestp = NULL;         // init best-buy pointer
    pxDiscountListIter cursor((pxDiscountList&)*this); // cast away constness
    while ( (curp = (pxDiscount*) ++cursor) != NULL )
    {
        if(curp->IsNatraDefault())
        {
            if( (!bestp) || (bestp->DiscountQty() < curp->DiscountQty() && QOrdered >= curp->BaseQty()) )
                bestp = curp;              // far the best at this moment
//          else
//              delete cursor.Remove();      // this discount is not better than bestp
        }
    }
    return bestp;
}

/*----------------------------------------------------------------------------*/
/*  ShrinkGroupExcluded: shrinks list regarding PharmGrpExcluded.             */
/*  PharmGrpExcluded2,PharmGrpExcluded3. This methode is only needed during   */
/*  Rangecalculation                                                          */
/*----------------------------------------------------------------------------*/
size_t
pxDiscountList :: ShrinkGroupExcluded
(
    pxCustPharmGroupList *hlist
)
{
    pxCustPharmGroupListIter cursor(*hlist);
    pxDiscountListIter  iter(*this);
    pxCustPharmGroup*   discinfop;
    pxDiscount*         artdikp;

/*----------------------------------------------------------------------------*/
/*  If there is a well constucted pxCustPharmGroupList containing entries,    */
/*  so shrink  the pxDiscountList depend on the pharmacygroupid of the        */
/*  pxCustPharmGroupList entries, otherwise delete all entries of the         */
/*  the pxDiscountList where PharmacyGroupId > 0                              */
/*----------------------------------------------------------------------------*/
    if (hlist > NULL)
    {
        while ( (discinfop  = (pxCustPharmGroup*) ++cursor) != NULL )
        {
            iter.Reset();
            while ( (artdikp = (pxDiscount*) ++iter) != NULL )
            {
                if ( hlist->Find(artdikp->PharmGrpExcluded()) ||
                     hlist->Find(artdikp->PharmGrpExcluded2())||
                     hlist->Find(artdikp->PharmGrpExcluded3()) )
                {
                    delete iter.Remove();
                    continue;
                }
            }
        }
    }
    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  ShrinkCashPaymentPriceType: shrinks list regarding PaymentTermType        */
/*  pricetype This list contain only entries with the same discountgrpno      */
/*  Looks for entries just for cashpayers                                     */
/*  This methode works only for the bulgarien applicarion                     */
/*----------------------------------------------------------------------------*/
size_t
pxDiscountList :: ShrinkCashPaymentPriceType
(
   pxOrder* order,
   const PriceTypeEnum PriceType
)
{
    pxDiscountListIter  iter(*this);
    pxDiscount*         dikp;
    pxCustBase&         customer = *order->Customer();
    pxCstPaymentTerms*  PaymentTerms = NULL;

    if (!Session()->isBulgaria())
        return Entries();

    if ( order->isCashOrder() )                   // cash order
        return Entries();
    if (  customer.CstPaymentTermsList() == NULL )  // cash payer
        return Entries();

    PaymentTerms = customer.CstPaymentTermsList()->Find(PriceType);
    if ( PaymentTerms == NULL )
        return Entries();                      // cash payer

    if( PaymentTerms->PaymentTarget() <= 0 )
        return Entries();                      // cash payer

    iter.Reset();
    while ( (dikp = (pxDiscount*) ++iter) != NULL )
    {
        if ( dikp->IsJustForCashPayer() )
        {
            delete iter.Remove();             // offer has wrong PriceType (discount specification)
        }
    }
    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  ShrinkDiscountPriceType: shrinks list regarding doscountspec and orderitem*/
/*  pricetype This list contain only entries with the same discountgrpno      */
/*  This methode works only for the bulgarien applicarion                     */
/*----------------------------------------------------------------------------*/
size_t
pxDiscountList :: ShrinkDiscountPriceType
(
    const PriceTypeEnum PriceType
)
{
    pxDiscountListIter  iter(*this);
    pxDiscount*         dikp;

    if (!Session()->isBulgaria())
        return Entries();

    iter.Reset();
    while ( (dikp = (pxDiscount*) ++iter) != NULL )
    {
        if ( (PriceType == HEALTHFUND_PRICE && dikp->DiscountSpec() == DiscSpec_VoluntarySale) ||
             (PriceType == FREESALE_PRICE   && dikp->DiscountSpec() == DiscSpec_HealthFund) )
        {
            delete iter.Remove();
            continue;
        }
    }
    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  ShrinkDateDelivery: shrinks list regarding Dateto and orders delivery date*/
/*  If entry->DateTo < orders delivery date, so this entry will be removed    */
/*  from the list.                                                            */
/*  This methode works only for the bulgarien application                     */
/*----------------------------------------------------------------------------*/
size_t
pxDiscountList :: ShrinkDateDelivery
(
    pxOrder* order
)
{
    pxDiscountListIter  iter(*this);
    pxDiscount*         dikp;
    nDate OrderDeldate;

    if (!Session()->isBulgaria())
        return Entries();

    if (order == NULL )
        return Entries();

    OrderDeldate = order->DatumAuslieferung();

    if ( OrderDeldate == pxConstants::NullDate )
        return Entries();

    iter.Reset();
    while ( (dikp = (pxDiscount*) ++iter) != NULL )
    {
        if ( dikp->DateTo() < OrderDeldate )
        {
            delete iter.Remove();
            continue;
        }
    }
    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Find return entryp depend on articleno                                    */
/*----------------------------------------------------------------------------*/
pxDiscount*
pxDiscountList :: Find
(
    const long ArticleNo
)
{
    pxDiscount *curp = NULL;             // ptr to current entry
    pxDiscountListIter  cursor(*this);  // define an iterator
    while ( (curp = (pxDiscount*) ++cursor) != NULL )
    {
        if (curp->ArticleNo() == ArticleNo && curp->DiscountGrpNo() > 0 )
        {
            break;
        }
    }
    return curp;
}

/*----------------------------------------------------------------------------*/
/*  FindManuFactureNo return entryp depend on ManufacturerNo                  */
/*----------------------------------------------------------------------------*/
pxDiscount*
pxDiscountList :: FindManuFactureNo
(
    const long ManufacturerNo
)
{
    pxDiscount *curp = NULL;             // ptr to current entry
    pxDiscountListIter  cursor(*this);  // define an iterator
    while ( (curp = (pxDiscount*) ++cursor) != NULL )
    {
        if (curp->ManufacturerNo() == ManufacturerNo && curp->DiscountGrpNo() > 0 )
        {
            break;
        }
    }
    return curp;
}

/*----------------------------------------------------------------------------*/
/*  FindTypeOffRebate: returns true if TypeOffRebate is available within      */
/*  the ArrayKindOffRebate,otherwise false will be returned                   */
/*----------------------------------------------------------------------------*/
bool
pxDiscountList :: FindTypeOffRebate
(
    const short TypeOffRebate
)
{
    bool retval = false;
    for (KindOffRebateIndex_ = 0;KindOffRebateIndex_ < cMaxKindOffRebate; ++KindOffRebateIndex_)
    {
        if ( ArrayKindOffRebate_[KindOffRebateIndex_] == TypeOffRebate )
        {
            retval = true;
            break;
        }
    }
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  FindKindOfCasCade: returns true if CasCadeNo  is available within         */
/*  the ArrayCasCadeNo,otherwise false will be returned                       */
/*----------------------------------------------------------------------------*/
bool
pxDiscountList :: FindKindOfCasCade
(
    const short CasCadeNo
)
{
    bool retval = false;
    for (CasCadeNoIndex_ = 0;CasCadeNoIndex_ < cMaxCasCadeNo; ++CasCadeNoIndex_)
    {
        if ( ArrayCasCadeNo_[CasCadeNoIndex_] == CasCadeNo )
        {
            retval = true;
            break;
        }
    }
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  FindEntryQty return entryp which fits Qty                                 */
/*----------------------------------------------------------------------------*/
pxDiscount*
pxDiscountList :: FindEntryQty
(
    const long Qty
)
{
    pxDiscount *curp  = NULL;             // ptr to current entry
    pxDiscount *bestp = NULL;
    pxDiscountListIter  cursor(*this);   // define an iterator
    while ( (curp = (pxDiscount*) ++cursor) != NULL )
    {
        if ( curp->BaseQty() <= Qty )
        {
            bestp = curp;
        }
    }
    return bestp;
}

/*----------------------------------------------------------------------------*/
/*  SetKindOffRebate: if  TypeOffRebate if already within the                 */
/*  ArrayKindOffRebate_  no action takes place, otherwise TypeOffRebate       */
/*  will be stored on the next free place within the ArrayKindOffRebate       */
/*----------------------------------------------------------------------------*/
void
pxDiscountList :: SetKindOffRebate
(
    const short TypeOffRebate
)
{
    if ( FindTypeOffRebate(TypeOffRebate) )
        return;

    // now place TypeOfRebate
    for (KindOffRebateIndex_ = 0;KindOffRebateIndex_ < cMaxKindOffRebate; ++KindOffRebateIndex_)
    {
        if ( ArrayKindOffRebate_[KindOffRebateIndex_] == 0 )
        {
            ArrayKindOffRebate_[KindOffRebateIndex_] = TypeOffRebate ;
            break;
        }
    }
}

/*----------------------------------------------------------------------------*/
/*  SetKindOffCasCade: if  CasCadeNo is already within the                    */
/*  ArrayCasCadeNo_  no action takes place, otherwise CasCadeNo               */
/*  will be stored on the next free place within the ArrayCasCadeNo_          */
/*----------------------------------------------------------------------------*/
void
pxDiscountList :: SetKindOffCasCade
(
    const short CasCadeNo
)
{
    if ( FindKindOfCasCade(CasCadeNo ) )
        return;

    // now place TypeOfRebate
    for (CasCadeNoIndex_ = 0;CasCadeNoIndex_ < cMaxCasCadeNo; ++CasCadeNoIndex_)
    {
        if ( ArrayCasCadeNo_[CasCadeNoIndex_] == 0 )
        {
            ArrayCasCadeNo_[CasCadeNoIndex_] = CasCadeNo ;
            break;
        }
    }
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxDiscountList :: AddToList
(
    const void *record,
    const int  /* row */
)
{
    // construct new 'pxDiscount' object:
    pxDiscount *objectp = new pxDiscount(Session(), *(tDISCOUNT*)record);
    InsertAscending(objectp);
    return objectp;
}

int
pxDiscountList :: EndBrowse
(
    const int  cursorid
)
{
    return pxDiscountEndBrowse(cursorid);
}


int
pxDiscountList :: GetNext
(
    const void *record,
    const int  cursorid
)
{
    return pxDiscountGetNext((tDISCOUNT*)record, cursorid);
}

int
pxDiscountList :: StartBrowse
(
    const void *keys,
    const int  cursorid
)
{
    return pxDiscountStartBrowse((tDISCOUNT*)keys, cursorid);
}
