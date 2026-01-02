#ifndef PXCALCDISCOUNT_DOTH
#define PXCALCDISCOUNT_DOTH

#include "pxcustpharmgroup.hpp"
#include "pxdiscount.hpp"
#include "pxerrorloggable.hpp"


enum  Mode
{
    MODE_SERBIA=1,
    MODE_BULGARIA
};

class pxCalcDiscount : public nCollectable
{
        // calclist
public:
// constructors:
                pxCalcDiscount(const short   Discounttype,
                               const long    QOrdered,
                               const long    DiscountQty,
                               const double  Discountkey,
                               const short   DiscountBestBuy,
                               const long    DiscountArticle,
                               const nString& PharmacyGroupId,
                               const nMoney  RefundValue,
                               const short   Promotion_No,
                               const char    TurnOverCalcImpact,
                               const short   CascadeLevel,
                               const char    InternalDiscount,
                               const long    PromoBaseQty,
                               const double  RefundPct,
                               const long    CustomerNo,
                               const short   DiscountCalcFrom,
                               const short   DiscountApplyTo
                              );

                pxCalcDiscount(const short   type,
                               const long    QOrdered,
                               const nMoney  FixedPrice,
                               const double  Discountkey,
                               const short   DiscountBestBuy,
                               const nString& PharmacyGroupId,
                               const nMoney  RefundValue,
                               const short   Promotion_No,
                               const char    TurnOverCalcImpact,
                               const short   CascadeLevel,
                               const char    InternalDiscount,
                               const long    PromoBaseQty,
                               const double  RefundPct,
                               const long    CustomerNo,
                               const short   DiscountCalcFrom,
                               const short   DiscountApplyTo
                );

                pxCalcDiscount(const short   type,
                               const long    QOrdered,
                               const double  DiscountValuePct,
                               const double  Discountkey,
                               const short   DiscountBestBuy,
                               const nString& PharmacyGroupId,
                               const nMoney  RefundValue,
                               const short   Promotion_No,
                               const char    TurnOverCalcImpact,
                               const short   CascadeLevel,
                               const char    InternalDiscount,
                               const long    PromoBaseQty,
                               const double  RefundPct,
                               const long    CustomerNo,
                               const short   DiscountCalcFrom,
                               const short   DiscountApplyTo
                );

                pxCalcDiscount(const short   type,
                               const long    QOrdered,
                               const double  DiscountValuePct,
                               const double  GrossProfitPct,
                               const double  Discountkey,
                               const short   DiscountBestBuy,
                               const nString& PharmacyGroupId,
                               const short   PaymentTargetNo,
                               const nMoney  RefundValue,
                               const short   Promotion_No,
                               const char    TurnOverCalcImpact,
                               const short   CascadeLevel,
                               const char    InternalDiscount,
                               const long    PromoBaseQty,
                               const double  RefundPct,
                               const long    CustomerNo,
                               const short   DiscountCalcFrom,
                               const short   DiscountApplyTo
                );

                pxCalcDiscount(const short   type,
                               const long    QOrdered,
                               const double  Discountkey,
                               const short   DiscountBestBuy,
                               const nString& PharmacyGroupId,
                               const nMoney  RefundValue,
                               const short   Promotion_No,
                               const char    TurnOverCalcImpact,
                               const short   CascadeLevel,
                               const char    InternalDiscount,
                               const long    PromoBaseQty,
                               const double  FixedDiscountValue,
                               const double  RefundPct,
                               const long    CustomerNo,
                               const short   DiscountCalcFrom,
                               const short   DiscountApplyTo
                );

                pxCalcDiscount(const pxCalcDiscount &src);

// destructor:
                virtual  ~pxCalcDiscount();
/*@DS
PUBLIC MEMBER OPERATORS
*/
    pxCalcDiscount&   operator=(const pxCalcDiscount& src);
//  Assigns the values of 'src' to self and returns a reference to it.


/*@DS
PUBLIC MEMBER FUNCTIONS
*/
    virtual  int      CompareTo(const nCollectable *that, void *p, const long lparm) const;
    short    DiscountType() const     {return Discounttype_;        }
    long     QOrdered() const         {return QOrdered_;            }
    long     DiscountQty() const      {return DiscountQty_;         }
    nMoney   FixedPrice() const       {return FixedPrice_ ;         }
    double   DiscountKey() const      {return Discountkey_;         }
    double   DiscountValuePct() const {return DiscountValuePct_;    }
    short    DiscountBestBuy() const  {return DiscountBestBuy_;     }
    long     DiscountArticle() const  {return DiscountArticle_;     }
    const nString& PharmacyGroupId() const  {return PharmacyGroupId_;     }
    double   GrossProfitPct() const   {return GrossProfitPct_;      }
    short    PaymentTargetNo() const  {return PaymentTargetNo_;     }
    double   RefundValue()      const {return RefundValue_;         }
    short    Promotion_No()     const {return Promotion_No_;        }
    char     TurnOverCalcImpact() const {return TurnOverCalcImpact_; }
    short    CascadeLevel()     const {return CascadeLevel_;        }
    char     InternalDiscount() const {return InternalDiscount_;    }
    short    PromotionNo()     const  {return PromotionNo_;         }
    long     PromoBaseQty()     const {return PromoBaseQty_;        }
    double   FixedDiscountValue()const{return FixedDiscountValue_;    }
    double   RefundPct() const        {return RefundPct_;}
    long     CustomerNo() const       {return CustomerNo_; }
    short    DiscountCalcFrom() const {return DiscountCalcFrom_; }
    short    DiscountApplyTo() const  {return DiscountApplyTo_; }

    enum tDiscountCategory GetDiscountCategory() const;

    inline bool IsRaised(const pxCalcDiscountList& list) const;

// Some Queries
    bool        IsNatraDefault()                      const
                {return DiscountBestBuy_ == BestBuy_NatraDefault;      }
    bool        IsNatraTeam()                         const
                {return DiscountBestBuy_ == BestBuy_NatraTeam;         }
    bool        IsNatraDiabetes()                     const
                {return DiscountBestBuy_ == BestBuy_NatraDiabetes;     }
    bool        IsFixedPriceDefault()                 const
                {return DiscountBestBuy_ == BestBuy_FixedPriceDefault; }
    bool        IsFixedPriceTeam()                    const
                {return DiscountBestBuy_ == BestBuy_FixedPriceTeam;    }
    bool        IsFixedPriceDiabetes()                const
                {return DiscountBestBuy_ == BestBuy_FixedPriceDiabetes;}
    bool        IsValuePctCash()                      const
                {return DiscountBestBuy_ == BestBuy_ValuePctCash;      }
    bool        IsValuePctShort()                     const
                {return DiscountBestBuy_ == BestBuy_ValuePctShort;     }
    bool        IsValuePctShortLine()                 const
                {return DiscountBestBuy_ == BestBuy_ValuePctShortLine; }
    bool        IsValuePctGenerika()                  const
                {return DiscountBestBuy_ == BestBuy_ValuePctGenerika;  }
    bool        IsValuePctPartenariat()               const
                {return DiscountBestBuy_ == BestBuy_ValuePctPartenariat;}
    bool        IsValuePctWholeSale()                 const
                {return DiscountBestBuy_ == BestBuy_ValuePctWholeSale; }
    bool        IsValuePctRetail()                    const
                {return DiscountBestBuy_ == BestBuy_ValuePctRetail;    }
    bool        IsValuePctTena()                      const
                {return DiscountBestBuy_ == BestBuy_ValuePctTena;      }
    bool        IsLogisticAddition()                  const
                {return DiscountBestBuy_ == BestBuy_LogisticAddition;  }
    bool        IsFixedPricePharmGroup()              const
                {return DiscountBestBuy_ == BestBuy_FixedPricePharmGroup;  }
    bool        IsValuePctPharmgroupExcluded()      const
                {return DiscountBestBuy_ == BestBuy_ValuePctPharmgroupExcluded;  }
    bool        IsValuePctPhoenixMagic()             const
                {return DiscountBestBuy_ == BestBuy_ValuePctPhoenixMagic;  }
    bool        IsValuePctOverDrive()                 const
                {return DiscountBestBuy_ == BestBuy_ValuePctOverdrive;  }
    bool        IsValuePctWholeSaleInd()                 const
                {return DiscountBestBuy_ == BestBuy_ValuePctWholeSaleInd; }
    bool        IsSpecialPrice()                        const
                {return DiscountBestBuy_ == BestBuy_SpecialPrice;        }
    bool        IsGrossProfitPct()                      const
                {return DiscountBestBuy_ == BestBuy_GrossProfitPct;      }
    bool        IsFixedDiscountValue()                  const
                {return DiscountBestBuy_ == BestBuy_FixedDiscountValue;  }
    bool        IsLogisticAdditionDataTransfer()         const
                {return DiscountBestBuy_ == BestBuy_LogisticDataTransfer; }
    bool        IsValuePctCashAssorted()                const
                {return DiscountBestBuy_ == BestBuy_ValuePctCashAssorted; }

protected:
    short      Discounttype_;
    long       QOrdered_;
    long       DiscountQty_;
    nMoney     FixedPrice_;
    double     DiscountValuePct_;
    double     Discountkey_;
    short      DiscountBestBuy_;
    long       DiscountArticle_;
    nString    PharmacyGroupId_;
    double     GrossProfitPct_;
    short      PaymentTargetNo_;
    nMoney     RefundValue_;
    short      Promotion_No_;
    char       TurnOverCalcImpact_;
    short      CascadeLevel_;
    char       InternalDiscount_;
    short      PromotionNo_;
    long       PromoBaseQty_;
    double     FixedDiscountValue_;
    double     RefundPct_;
    long       CustomerNo_;
    short      DiscountCalcFrom_;
    short      DiscountApplyTo_;

private:
    friend class pxCalcDiscountList;
};

//****************************************************************************************************
class pxCalcDiscountList : public nDListCollect, public pxErrorLoggable
{

public:
// constructors:
                pxCalcDiscountList(pxCustBase& customer,
                                pxArtBase& article,
                                pxOrderItem* item,
                                long QOrderedt,
                                pxCustPharmGroupList* phglist = NULL);

                pxCalcDiscountList(pxCustBase& customer,
                                pxDiscountList *dlist,
                                long MengeBestellt);

                                pxCalcDiscountList(pxCustBase& customer,
                                pxArtBase& article,
                                pxOrderItem* item,
                                long QOrderedt,
                                int mode,
                                bool AddOnPromoDiscount,
                                bool AddOnStdDiscount,
                                pxCustPharmGroupList* phglist = NULL);

// destructor:
    virtual     ~pxCalcDiscountList() {Clear();}
// member functions:
    void        Clear();
    long        QOrdered() const        {return QOrdered_;}
    char        NrIntern()   const      {return NrIntern_ ;}
    pxSession*  Session()               {return session_;}
    std::ifstream* CMsgStream()            {return Session()->CMsgStream();}
    pxCalcDiscount* BestBuyNatra() const;
    pxCalcDiscount* BestBuyNatra(long QOrdered) const;
    pxCalcDiscount* BestBuyNetto() const;
    pxCalcDiscount* BestBuyCash() const;
    pxCalcDiscount* BestBuyCash(long QOrdered) const;
    pxCalcDiscount* BestBuyGrossProfitPct() const;
    pxCalcDiscount* BestBuyLogAddition() const;
    pxCalcDiscount* BestBuyLogAdditionDataTransfer() const;
    pxCalcDiscount* BestBuyFixedDiscountValue() const;
    int         DeleteRaises(const short type);
    bool        IsNrIntern()            {return NrIntern_ == '1';}
    double      PromotionValuePct()     {return PromotionValuePct_;}
    int         PromotionNatraQty()     {return PromotionNatraQty_;}
    long        QOrderedPromo() const   {return QOrderedPromo_;            }
    double      DiscountKeyPromo() const      {return DiscountkeyPromo_;         }
    short       DiscountTypePromo() const     {return DiscounttypePromo_;         }
    long        DiscountArticlePromo() const  {return DiscountArticlePromo_;     }
    short       DiscountBestBuyPromo() const  {return DiscountBestBuyPromo_;     }
    nString&    PharmacyGroupIdPromo()        {return PharmacyGroupIdPromo_;     }
    double      RefundValuePromo()      const {return RefundValuePromo_;         }
    double      RefundPctPromo()      const   {return RefundPctPromo_;         }
    short       Promotion_NoPromo()     const {return Promotion_NoPromo_;        }
    char        TurnOverCalcImpactPromo() const {return TurnOverCalcImpactPromo_;}
    char        InternalDiscountPromo() const {return InternalDiscountPromo_;}
    size_t      ShrinkMultipleEntries();

protected:
    void        init(pxCustBase& customer, long qOrdered);
    void        CalcDiscount(pxCustBase& customer,
                             pxDiscountList *dlist,
                             long QOrdered,
                             short CascadeLevel
                                );
    void        calcDiscountNatra(short discounttype, pxDiscountList* dlist, short cascadeLevel);
    void        calcDiscountNetto(short discounttype, pxDiscountList* dlist, short cascadeLevel);
    void        calcDiscountCashWithGrossProfitPctZero(short discounttype, pxDiscountList* dlist, short cascadeLevel);
    void        calcDiscountCash(short discounttype, pxDiscountList* dlist, short cascadeLevel);
	void        calcDiscountFixedValue(short discounttype, pxDiscountList* dlist, short cascadeLevel);

private:
    pxSession  *session_;
    long       QOrdered_;
    char       NrIntern_;
    double     PromotionValuePct_;
    int        PromotionNatraQty_;
    long       QOrderedPromo_;
    double     DiscountkeyPromo_;
    short      DiscounttypePromo_;
    long       DiscountArticlePromo_;
    short      DiscountBestBuyPromo_;
    nString    PharmacyGroupIdPromo_;
    double     RefundValuePromo_;
    double     RefundPctPromo_;
    short      Promotion_NoPromo_;
    char       TurnOverCalcImpactPromo_;
    char       InternalDiscountPromo_;
    int        CountryMode;
    friend class pxCalcDiscountListIter;
    void        ShrinkDiscountListBG(pxDiscountList* dlist, pxOrderItem* item, long QOrdered, pxCustPharmGroupList* Phglist);
    void        CheckDiscountList(int mode, pxDiscountList *dlist, pxCustBase& customer, pxOrderItem* item, long QOrdered, pxCustPharmGroupList* Phglist);
    void        CheckDiscountListBG(int mode,pxDiscountList* dlist, pxCustBase& customer, pxOrderItem* item, long QOrdered, pxCustPharmGroupList* Phglist, short CascadeLevel);
    void        InsertZeroDiscount(pxDiscountList *dlist, long QOrdered);
    bool        SplitAndProcess(pxCustBase& customer, pxOrderItem* item, long QOrdered, int mode, pxCustPharmGroupList* Phglist, pxDiscountList* dlist, int maxptn);
    void        CreateSubdlist(pxDiscountList* dlist, pxDiscountList* subdlist, int ptn);
    void        CreateSubdlistByIndex(pxDiscountList* dlist, const int index, pxDiscountList* subdlist);
};

class pxCalcDiscountListIter : public nDListCollectIter
{
public:
// constructors:
    pxCalcDiscountListIter(pxCalcDiscountList& list) : nDListCollectIter(list) {}
// destructor:
    virtual  ~pxCalcDiscountListIter() {}
};

    inline bool pxCalcDiscount::IsRaised(const pxCalcDiscountList& list) const
                              { return (QOrdered_ > list.QOrdered());}

#endif
