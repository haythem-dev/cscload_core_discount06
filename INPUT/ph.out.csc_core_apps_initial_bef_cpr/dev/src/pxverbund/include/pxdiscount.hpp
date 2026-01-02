/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

PXDISCOUNT.HPP
Discount class

REVISION HISTORY

01 Dec 2005 V1.00 REV 00 written by Ysbrand Bouma.
*/

#ifndef PXDISCOUNT_INC
#define PXDISCOUNT_INC

#include "pxbase/pxrecord.hpp"
#include "types/pricetypeenum.inc"
#include <date.hpp>
#include <money.hpp>
#include "pxdiscountdef.h"

class pxDiscount;
class pxOrder;
class pxOrderItem;
class pxCustPharmGroupList;
class pxDonePromoQuotasList;
class pxDiscountListIter;
struct tDISCOUNT;

enum  CASCADE
{
  CASCADE_ARTICLE,
  CASCADE_MANUFACTURER_0,
  CASCADE_MANUFACTURER_1,
  CASCADE_MANUFACTURER,
  CASCADE_ARTICLEGROUP_0,
  CASCADE_ARTICLEGROUP_1,
  CASCADE_CUSTOMER,
  CASCADE_PHARMACYGROUP,
  CASCADE_ART_AND_MAN_0,
  CASCADE_ART_AND_MAN_1,
  CASCADE_SINGLEART_0,
  CASCADE_SINGLEART_1,
  CASCADE_OCCASIONS,
  CASCADE_ARTICLE_0,
  CASCADE_ARTICLE_1,
  CASCADE_PROMOTION_0,
  CASCADE_PROMOTION_1,
  CASCADE_ALL_PROMOTIONS,
  CASCADE_JUST_JOIN_PHARMACYGROUP,
  CASCADE_JUST_PHARMACYGROUP_ZERO,
  CASCADE_JUST_JOIN_PHARMACYGROUP_1,
  CASCADE_JUST_JOIN_PHARMACYGROUP_2
};


class pxDiscount : public pxDBRecord
{

public:

// constructors:
                pxDiscount(pxDiscount& src);
                pxDiscount(pxSession *session);
                pxDiscount(pxSession *session, tDISCOUNT& src);
                pxDiscount(pxSession *session,
                         short  BranchNo,
                         long  ArticleNo);
// destructor:
                virtual  ~pxDiscount();
/*@DS
PUBLIC MEMBER OPERATORS
*/
    pxDiscount&   operator=(const pxDiscount& src);
//  Assigns the values of 'src' to self and returns a reference to it.

    pxDiscount&   operator=(const tDISCOUNT& src);
//  Assigns the values of the record structure 'src' to self and returns a
//  reference to self.


/*@DS
PUBLIC MEMBER FUNCTIONS
*/
    friend   pxDiscount&
                Assign(pxDiscount& dest, const tDISCOUNT& src);
    friend   tDISCOUNT&
                Assign(tDISCOUNT& dest, const pxDiscount& src);

    virtual  int      CompareTo(const nCollectable *that, void *p,
                                const long lparm) const;

    virtual  int     Read(const void *record);
    virtual  int     Get(DBAccessMode mode = cDBGET_READONLY);

//  Queries:
    short          BranchNo()          const {return BranchNo_          ;}
    long           ArticleNo()         const {return ArticleNo_         ;}
    long           DiscountGrpNo()     const {return DiscountGrpNo_     ;}
    const nString& PharmacyGroupId()   const {return PharmacyGroupId_   ;}
    long           CustomerNo()        const {return CustomerNo_        ;}
    short          GrpDiscountTyp()    const {return GrpDiscountTyp_    ;}
	const nDate&   DateFrom()          const {return DateFrom_          ;}
	const nDate&   DateTo()            const {return DateTo_            ;}
    long           BaseQty()           const {return BaseQty_           ;}
    short          DiscountSpec()      const {return DiscountSpec_      ;}
    short          DiscountType()      const {return DiscountType_      ;}
    short          DiscountQty()       const {return DiscountQty_       ;}
    double         DiscountValuePct()  const {return DiscountValuePct_  ;}
    double         DiscountQtyPct()    const {return DiscountQtyPct_    ;}
    double         SurchargePct()      const {return SurchargePct_      ;}
	const nString& PharmGrpExcluded()  const {return PharmGrpExcluded_  ;}
    const nMoney&  FixedPrice()        const {return FixedPrice_        ;}
    double         RefundPct()         const {return RefundPct_         ;}
    char           InternalDiscount()  const {return InternalDiscount_  ;}
    long           DiscountArticle()   const {return DiscountArticle_   ;}
	const nString& PharmGrpExcluded2() const {return PharmGrpExcluded_2_;}
	const nString& PharmGrpExcluded3() const {return PharmGrpExcluded_3_;}
    double         BaseValue()         const {return BaseValue_         ;}
    long           BaseMultSTDQty()    const {return BaseMultSTDQty_    ;}
    char           NoMultipleQty()     const {return NoMultipleQty_     ;}
    double         FixedDiscountValue()const {return FixedDiscountValue_;}
    long           ManufacturerNo()    const {return ManufacturerNo_    ;}
    long           ArtCategoryNo()     const {return ArtCategoryNo_     ;}
    short          PaymentTargetNo()   const {return PaymentTargetNo_   ;}
    double         GrossProfitPct()    const {return GrossProfitPct_    ;}
    char           AddonDiscountOk()   const {return AddonDiscountOk_   ;}
    char           PaymentTermType()   const {return PaymentTermType_   ;}
    long           TargetQty()         const {return TargetQty_         ;}
    double         ExceedancePct()     const {return ExceedancePct_     ;}
    short          RefundType()        const {return RefundType_        ;}
    long           ArticleNoPack()     const {return ArticleNoPack_     ;}
    const nMoney&  RefundValue()       const {return RefundValue_       ;}
    short          PromotionNo()       const {return PromotionNo_       ;}
    long           MaxQty()            const {return MaxQty_            ;}
    char           TurnOverCalcImpact()const {return TurnOverCalcImpact_;}
    char           AddonDiscount()     const {return AddonDiscount_     ;}
    char           MonthlyDiscount()   const {return MonthlyDiscount_   ;}
    short          CasCadeNo()         const {return CasCadeNo_         ;}
	short          DiscountCalcFrom()  const {return DiscountCalcFrom_  ;}
	short          DiscountApplyTo()   const {return DiscountApplyTo_   ;}

//  for internal usage
    bool            RemainInList()      {return RemainInList_      ;}
    bool            IsRemainInList()    {return RemainInList_      ;}
    bool            IsNonProportional() {return NoMultipleQty_ == '1';}
    long            CalcDiscountQty     ( const long Qty);
    bool            IsAddonDiscountOk() { return AddonDiscountOk_ == '1'; }
    bool            IsTurnOverCalcImpact() { return TurnOverCalcImpact_ == '1'; }
    bool            IsJustForCashPayer(){ return PaymentTermType_ == '1'; }
    bool            IsAddonDiscount()   { return AddonDiscount_ == '1';   }
    bool            IsMonthlyDiscount() { return MonthlyDiscount_ == '1'; }


//  Some additional Queries:
    bool        IsNatraDefault()                      const
                {return BestBuy_ == BestBuy_NatraDefault;      }
    bool        IsNatraTeam()                         const
                {return BestBuy_ == BestBuy_NatraTeam;         }
    bool        IsNatraDiabetes()                     const
                {return BestBuy_ == BestBuy_NatraDiabetes;     }
    bool        IsFixedPriceDefault()                 const
                {return BestBuy_ == BestBuy_FixedPriceDefault; }
    bool        IsFixedPriceTeam()                    const
                {return BestBuy_ == BestBuy_FixedPriceTeam;    }
    bool        IsFixedPriceDiabetes()                const
                {return BestBuy_ == BestBuy_FixedPriceDiabetes;}
    bool        IsValuePctCash()                      const
                {return BestBuy_ == BestBuy_ValuePctCash;      }
    bool        IsValuePctShort()                     const
                {return BestBuy_ == BestBuy_ValuePctShort;     }
    bool        IsValuePctShortLine()                 const
                {return BestBuy_ == BestBuy_ValuePctShortLine; }
    bool        IsValuePctGenerika()                  const
                {return BestBuy_ == BestBuy_ValuePctGenerika;  }
    bool        IsValuePctPartenariat()               const
                {return BestBuy_ == BestBuy_ValuePctPartenariat;}
    bool        IsValuePctWholeSale()                 const
                {return BestBuy_ == BestBuy_ValuePctWholeSale; }
    bool        IsValuePctRetail()                    const
                {return BestBuy_ == BestBuy_ValuePctRetail;    }
    bool        IsValuePctTena()                      const
                {return BestBuy_ == BestBuy_ValuePctTena;      }
    bool        IsLogisticAddition()                  const
                {return BestBuy_ == BestBuy_LogisticAddition;  }
    bool        IsFixedPricePharmGroup()              const
                {return BestBuy_ == BestBuy_FixedPricePharmGroup;  }
    bool        IsValuePctPharmgroupExcluded()      const
                {return BestBuy_ == BestBuy_ValuePctPharmgroupExcluded;  }
    bool        IsValuePctPhoenixMagic()                  const
                {return BestBuy_ == BestBuy_ValuePctPhoenixMagic;  }
    bool        IsValuePctOverDrive()                const
                {return BestBuy_ == BestBuy_ValuePctOverdrive;  }
    bool        IsSpecialPrice()                      const
                {return BestBuy_ == BestBuy_SpecialPrice;       }
	bool        IsFixedDiscountValue()                  const
				{return BestBuy_ == BestBuy_FixedDiscountValue;  }
    bool        IsLogisticAdditionDataTransfer()         const
                {return BestBuy_ == BestBuy_LogisticDataTransfer;  }
    bool        IsValuePctCashAssorted()                const
                {return BestBuy_ == BestBuy_ValuePctCashAssorted;  }

// Set Methodes
    void        SetRemainInList()              { RemainInList_     = true;    }
    void        DiscountSpec( short spec)      { DiscountSpec_     = spec;    }
    void        DiscountValuePct(double value) { DiscountValuePct_ = value;   }
    void        SurchargePct( double value)    { SurchargePct_     = value;   }
    void        FixedPrice( nMoney price)      { FixedPrice_       = price;   }
    void        SetCasCadeNo( short num )      { CasCadeNo_        = num;     }
    short       ConvertDiscountSpecToBestBuy(const short bestbuy);
	enum tDiscountCategory GetDiscountCategory() const;

protected:
    void        Init();

    short      BranchNo_          ;      // Branchnumber
    long       ArticleNo_         ;      // Articlenumber
    long       DiscountGrpNo_     ;      // DiscountGroupNumber(Range)
    nString    PharmacyGroupId_   ;      // Pharmacy Group Id
    long       CustomerNo_        ;      // Customerno
    short      GrpDiscountTyp_    ;      // GroupDiscounttyp
    nDate      DateFrom_          ;      // Date from
    nDate      DateTo_            ;      // Date to
    long       BaseQty_           ;      // Base Quanty
    short      DiscountSpec_      ;      // Discountspecification
    short      DiscountType_      ;      // DiscountType
    short      DiscountQty_       ;      // DiscountQuantity
    double     DiscountValuePct_  ;      // DiscountValue Percent
    double     DiscountQtyPct_    ;      // Discount Quantity Percent
    double     SurchargePct_      ;      // Discount Quantity Percent
    nString    PharmGrpExcluded_  ;      // Pharmacy Group Id Excluded
    nMoney     FixedPrice_        ;      // Fixed Price
    double     RefundPct_         ;      // Refund percentage
    char       InternalDiscount_  ;      // Internal Discount
    long       DiscountArticle_   ;      // Discount Article Number
    nString    PharmGrpExcluded_2_;      // Pharmacy Group Id Excluded
    nString    PharmGrpExcluded_3_;      // Pharmacy Group Id Excluded
    double     BaseValue_         ;      // Base Value
    long       BaseMultSTDQty_    ;      // Base multiple standard quantity
    char       NoMultipleQty_     ;      // KZ No_mutiple quantity
    double     FixedDiscountValue_;      // ??
    long       ManufacturerNo_    ;      // manufacturerno
    long       ArtCategoryNo_     ;      // ARTCATEGORYNO
    short      PaymentTargetNo_   ;      // PAYMENTTARGETNO
    double     GrossProfitPct_    ;      // GrossProfitPct
    char       AddonDiscountOk_   ;      // ADDONDISCOUNTOK
    char       PaymentTermType_   ;      // PaymentTermType
    long       TargetQty_         ;      // TARGETQTY
    double     ExceedancePct_     ;      // EXCEEDANCEPCT
    short      RefundType_        ;      // REFUNDTYPE
    long       ArticleNoPack_     ;      // Article number Pack(Steller(Pseudoartikelno)
    nMoney     RefundValue_       ;      // Refund Value
    short      PromotionNo_       ;      // Promotion Number
    long       MaxQty_            ;      // Max quantity to order
    char       TurnOverCalcImpact_ ;     // TurnOverCalcImpact
    char       AddonDiscount_     ;      // AddOnDiscount
    char       MonthlyDiscount_   ;      // Monthly Discount
    short      DiscountCalcFrom_  ;      // DISCOUNTCALCFROM
    short      DiscountApplyTo_   ;      // DISCOUNTAPPLYTO

    short      CasCadeNo_         ;      // BG Performance test code

    // internal usage
    bool       RemainInList_      ;      // RemainInList
    short      BestBuy_           ;      // BestBuy

private:
    friend class pxDiscountList;
};

class pxDiscountList : public nDBRecordSet, public nDListCollect
{

public:

//  constructors:
                pxDiscountList(pxSession *session);
//  destructor:
                virtual ~pxDiscountList() {Clear();}
//  member functions:
                pxSession* Session()       { return (pxSession*) DataBase();}

    size_t      Select ( const int  count = 50 );
    size_t      Select ( const short BranchNo,
                         const long  ArticleNo,
                         const int   count  = 500
                       );

    size_t      Select ( const short BranchNo,
                         const long  ArticleNo,
                         const long  CustomerNo,
                         const int   count  = 500
                       );
    size_t      Select ( const short BranchNo,
                         const long  ArticleNo,
                         const long  CustomerNo,
                         const long  ManufacturerNo,
                         const int   count  = 500
                       );
    size_t      Select ( const short BranchNo,
                         const long  ArticleNo,
                         const short Discounttype,
                         const int   count  = 500
                       );
    size_t      SelectRange ( const short BranchNo,
                         const long  DiscountGrpNo,
                         const long  CustomerNo,
                         const int   count  = 500
                       );
    size_t      Select ( const short BranchNo,
                         const long  ArticleNo,
                         const short Discounttype,
                         nString& PharmacyGroupId,
                         const int   count  = 500
                       );
    size_t      Select ( const int   CacadeNo,
                                                 const short BranchNo,
                         const long  ArticleNo,
                         const long  CustomerNo,
                         const long  ManufacturerNo,
                         const short DiscountSpec,
                         const int   count  = 500
                       );
    size_t      SelectPromotion( const short BranchNo,
                                const short Promotion_no,
                                const long  ArticleNo,
                                const long  CustomerNo,
                                const short DiscountSpec,
                                const int   count  = 500
                              );
    size_t      Select ( const int   CacadeNo,
                         const short BranchNo,
                         const long  ArticleNo,
                         const long  CustomerNo,
                         const int   count  = 500
                       );


    long       CalcDiscountNatra(long    *orderq,
                                  short    Discounttype,
                                  double *Discountkey,
                                  short   *DiscountBestBuy ,
                                  long    *DiscountArticle,
                                  nMoney   *pRefundValue,
                                  short   *pPromotion_No,
                                  char    *pTurnOverCalcImpact,
                                  char    *pInternalDiscount,
                                  long    *pPromoBaseQty,
		                          double  *pRefundPct,
		                          long    *pCustomerNo,
                                  short   *pDiscountCalcFrom,
                                  short   *pDiscountApplyTo
	);

    nMoney      CalcDiscountNetto(long    *orderq,
                                  short    Discounttype,
                                  double *Discountkey,
                                  short   *DiscountBestBuy,
                                  nMoney   *pRefundValue,
                                  short   *pPromotion_No,
                                  char    *pTurnOverCalcImpact,
                                  char    *pInternalDiscount,
                                  long    *pPromoBaseQty,
                                  double  *pRefundPct,
                                  long    *pCustomerNo
	);

    double    CalcDiscountCash (long    *orderq,
                                  short    Discounttype,
                                  double *Discountkey,
                                  short   *DiscountBestBuy,
                                  nMoney   *pRefundValue,
                                  short   *pPromotion_No,
                                  char    *pTurnOverCalcImpact,
                                  char    *pInternalDiscount,
                                  long    *pPromoBaseQty,
                                  double  *pRefundPct,
                                  long    *pCustomerNo,
                                  short   *pDiscountCalcFrom,
                                  short   *pDiscountApplyTo
	);

    double    CalcGrossProfitPct(long    *orderq,
                                  short    Discounttype,
                                  double *Discountkey,
                                  short   *DiscountBestBuy,
                                  nMoney   *pRefundValue,
                                  short   *pPromotion_No,
                                  char    *pTurnOverCalcImpact,
                                  char    *pInternalDiscount,
                                  long    *pPromoBaseQty,
                                  double  *pRefundPct,
                                  long    *pCustomerNo
	);

	double	CalcFixedDiscountValue(long    *orderq,
                                  short    Discounttype,
                                  double *Discountkey,
                                  short   *DiscountBestBuy,
                                  nMoney   *pRefundValue,
                                  short   *pPromotion_No,
                                  char    *pTurnOverCalcImpact,
                                  char    *pInternalDiscount,
                                  long    *pPromoBaseQty,
                                  double  *pRefundPct,
                                  long    *pCustomerNo
	);

    long       ComputeNatra     (long    *orderq,
                                  double *Discountkey,
                                  short   *DiscountBestBuy,
                                  long    *DiscountArticle,
                                  nMoney   *pRefundValue,
                                  short   *pPromotion_No,
                                  char    *pTurnOverCalcImpact,
                                  char    *pInternalDiscount,
                                  long    *pPromoBaseQty,
                                  double  *pRefundPct,
                                  long    *pCustomerNo,
                                  short   *pDiscountCalcFrom,
                                  short   *pDiscountApplyTo
	);

    nMoney      ComputeNetto     (long    *orderq,
                                  double *Discountkey,
                                  short   *DiscountBestBuy,
                                  nMoney   *pRefundValue,
                                  short   *pPromotion_No,
                                  char    *pTurnOverCalcImpact,
                                  char    *pInternalDiscount,
                                  long    *pPromoBaseQty,
                                  double  *pRefundPct,
                                  long    *pCustomerNo
	);

    double    ComputeCash      (long    *orderq,
                                  double *Discountkey,
                                  short   *DiscountBestBuy,
                                  nMoney   *pRefundValue,
                                  short   *pPromotion_No,
                                  char    *pTurnOverCalcImpact,
                                  char    *pInternalDiscount,
                                  long    *pPromoBaseQty,
                                  double  *pRefundPct,
                                  long    *pCustomerNo,
                                  short   *pDiscountCalcFrom,
                                  short   *pDiscountApplyTo
	);

    double    ComputeGrossProfitPct(long    *orderq,
                                  double *Discountkey,
                                  short   *DiscountBestBuy,
                                  nMoney   *pRefundValue,
                                  short   *pPromotion_No,
                                  char    *pTurnOverCalcImpact,
                                  char    *pInternalDiscount,
                                  long    *pPromoBaseQty,
                                  double  *pRefundPct,
                                  long    *pCustomerNo
	);

	double  ComputeFixedDiscountValue(long    *orderq,
                                  double *Discountkey,
                                  short   *DiscountBestBuy,
                                  nMoney   *pRefundValue,
                                  short   *pPromotion_No,
                                  char    *pTurnOverCalcImpact,
                                  char    *pInternalDiscount,
                                  long    *pPromoBaseQty,
                                  double  *pRefundPct,
                                  long    *pCustomerNo
	);

    double    ComputeLogAdd    (long    *orderq,
                                  double *Discountkey,
                                  short   *DiscountBestBuy,
                                  nMoney   *pRefundValue,
                                  short   *pPromotion_No,
                                  char    *pTurnOverCalcImpact,
                                  char    *pInternalDiscount,
                                  long    *pPromoBaseQty,
                                  double  *pRefundPct,
                                  long    *pCustomerNo,
                                  short   *pDiscountCalcFrom,
                                  short   *pDiscountApplyTo
	);

        nMoney      GetRefundValue   ();

    short      GetPromotionNo   ();

    char       CheckNrIntern();

    int        CheckList(pxOrderItem* item);

    int        LogAddSpecials(pxOrderItem* item);   // FR

    int        SpecialPrice(pxOrderItem* item);     // HR

    int        ArtComPackMembers(pxOrderItem* item);

    int        ReduceToValidOffers(const long QOrdered = 0);
    void        DeleteInvalidOffers(short type);
    bool        CheckAddOnDiscountOK();
    bool        checkHigherConditions(pxOrderItem* item, const long Qordered);
    size_t      Shrink(pxCustPharmGroupList* phghlist = NULL);
    size_t      ShrinkRangePharmacyGroup(pxCustPharmGroupList* phghlist = NULL);
    size_t      ShrinkPriceType(pxOrderItem* item, long QOrdered);
    size_t      ShrinkPromotions(pxOrderItem* item);
    size_t      ShrinkCashPayment(pxOrderItem* item);
    size_t      ShrinkDiscountSpec();
    size_t      ShrinkGroupExcluded(pxCustPharmGroupList* phghlist = NULL);
    size_t      ShrinkDiscountPriceType(const PriceTypeEnum PriceType );
    size_t      ShrinkCashPaymentPriceType( pxOrder* order, const PriceTypeEnum PriceType);
    size_t      ShrinkDateDelivery( pxOrder* order);
        pxDiscount* BestBuyNatra_dlist(long QOrdered);
        pxDiscount* BestBuyCash_dlist(long QOrdered);

    pxDiscount* Find(const long ArticleNo );
    pxDiscount* FindManuFactureNo(const long ManufacturerNo );
    void        SetKindOffRebate(const short type);        // methode for  ArrayKindOffRebate
    bool        FindTypeOffRebate(const short type);       // methode for  ArrayKindOffRebate
    pxDiscount* FindEntryQty(const long Qty);              // methode for  ArrayKindOffRebate
    void        SetKindOffCasCade(const short num);         // methode for  ArrayCasCadeNo
    bool        FindKindOfCasCade(const short num);        // methode for  ArrayCasCadeNo
    // BG Performance test code
    int         SaveDiscountList(pxDiscountList* dlist, const short CasCadeNo);
    int         ReloadDiscountList(pxDiscountList* dlist, const short CasCadeNo);
    bool        FindCasCadeNo( const short CasCadeNo);
    long        ArtikelNr() { return ArtikelNr_; }
    void        SetArtikelNr( const long ArtikelNr) { ArtikelNr_ = ArtikelNr; }

// Some Queries
    void        Clear()        {nDBRecordSet::Clear();}

    nString&    PharmacyGroupId()
                {return PharmacyGroupId_;                     }
    short       PaymentTargetNo()
                {return PaymentTargetNo_;                     }
    short*      ArrayKindOffRebate()
                {return ArrayKindOffRebate_;                  }
    short*      ArrayCasCadeNo()
                {return ArrayCasCadeNo_;                      }

    virtual  nCollectable*
                      AddToList(const void *record, const int row);
    virtual  int     GetNext(const void* record, const int cursorid);
    virtual  int     StartBrowse(const void *keys, const int cursorid);
    virtual  int     EndBrowse(const int cursorid);


protected:

private:
    nString  PharmacyGroupId_;          // PharmacyGroupId
    short   PaymentTargetNo_;          // PaymentTargetNo       (RS)

    short   ArrayKindOffRebate_[cMaxKindOffRebate];
    int     KindOffRebateIndex_;
    short   ArrayCasCadeNo_[cMaxCasCadeNo];
    int     CasCadeNoIndex_;
    long    ArtikelNr_;

    static bool deleteCursorAndContinueOnFullfilledPromotionquota(pxDonePromoQuotasList* donePromoList, pxDiscountListIter& cursor, pxOrderItem* item);
    static bool deleteCursorAndContinueOnNotBySalesWeb(pxDiscountListIter& cursor, pxOrderItem* item, bool& addOnPromoDiscountOfProductPromo);

    friend class pxDiscountListIter;
};

class pxDiscountListIter : public nDListCollectIter
{

public:
// constructors:
    pxDiscountListIter(pxDiscountList& list) : nDListCollectIter(list) {;}
// destructor:
    virtual  ~pxDiscountListIter() {;}
};
#endif
