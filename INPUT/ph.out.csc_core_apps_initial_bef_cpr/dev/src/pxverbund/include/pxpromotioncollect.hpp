/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

PXCALCRANGE.HPP

REVISION HISTORY

11 Jan 2011 V1.00 REV 00 written by Ysbrand Bouma.
*/

#ifndef PXPROMOCOLLECT_DOTH
#define PXPROMOCOLLECT_DOTH

#include "error.hpp"
#include "collect.hpp"
#include "dlistcol.hpp"
#include "money.hpp"

class pxPromoCollect : public nCollectable
{

public:
// constructors:
                pxPromoCollect(const short  PromotionNo,
                               const long   DiscountGrpNo,
                               const long   PosNr,
                               const long   ArticleNo
                              );

                pxPromoCollect(const pxPromoCollect &src);

// destructor:
                virtual  ~pxPromoCollect();
/*@DS
PUBLIC MEMBER OPERATORS
*/
    pxPromoCollect&   operator=(const pxPromoCollect& src);
//  Assigns the values of 'src' to self and returns a reference to it.


/*@DS
PUBLIC MEMBER FUNCTIONS
*/
    virtual  int      CompareTo(const nCollectable *that, void *p,
                                const long lparm) const;


// Some Queries
    short      PromotionNo()         { return PromotionNo_;       }
    long       DiscountGrpNo()       { return DiscountGrpNo_;     }
    long       PosNr()               { return PosNr_;             }
    long       ArticleNo()           { return ArticleNo_;         }
    double    DiscountValuePct()    { return DiscountValuePct_;  }
    long       DiscountQty()         { return DiscountQty_;       }
    short      PromotionType()       { return PromotionType_;     }
    char       AddOnPromoDiscOk()    { return AddOnPromoDiscOk_;  }
    char       AddOnStdDiscOk()      { return AddOnStdDiscOk_;    }
    short      Priority()            { return Priority_;          }
    double    GrossProfitPct()      { return GrossProfitPct_;    }
    double    RefundPct()           { return RefundPct_;         }
    nMoney      RefundValue()         { return RefundValue_;       }
    short      RefundType()          { return RefundType_;        }

    bool        IsAddOnPromoDiscOk()  const
                { return AddOnPromoDiscOk_ == '1';  }
    bool        IsAddOnStdDiscOk()  const
                { return AddOnStdDiscOk_   == '1';  }

//  Member set methodes
    void        SetDiscountValuePct(double value) { DiscountValuePct_ = value;   }
    void        SetDiscountQty(long qty)         { DiscountQty_      = qty;     }
    void        SetPromotionType(short type)     { PromotionType_    = type;    }
    void        SetAddOnPromoDiscOk(char flag)   { AddOnPromoDiscOk_ = flag;    }
    void        SetAddOnStdDiscOk(char flag)     { AddOnStdDiscOk_   = flag;    }
    void        SetPriority(short prio)          { Priority_         = prio;    }
    void        SetGrossProfitPct(double value)   { GrossProfitPct_   = value;   }
    void        SetRefundPct(double pct)          { RefundPct_        = pct;     }
    void        SetRefundValue(nMoney value)      { RefundValue_      = value;   }
    void        SetRefundType(short type)        { RefundType_       = type;    }

protected:
    short      PromotionNo_;         // Promotion Number
    long       DiscountGrpNo_;       // discountgroup number
    long       PosNr_;               // positionnummer witin order
    long       ArticleNo_;           // Articlenumber
    double    DiscountValuePct_;    // DiscountValue Percent
    long       DiscountQty_;         // Discount quantitiy
    short      PromotionType_;       // Promotion Type
    char       AddOnPromoDiscOk_;    // AddOn Promo discount
    char       AddOnStdDiscOk_;      // AddOn standard discount
    short      Priority_;            // Priority
    double    GrossProfitPct_;      // GrossProfitPct
    double    RefundPct_         ;      // Refund percentage
    nMoney      RefundValue_       ;      // Refund Value
    short      RefundType_        ;      // REFUNDTYPE

private:
    friend class pxPromoCollectList;
};

class pxPromoCollectList : public nDListCollect
{

public:
// constructors:

// destructor:
                virtual  ~pxPromoCollectList() {Clear();}
// member functions:
    void          Clear();
    pxPromoCollect*  BestTargetPromotion(const long ArticleNo = 0);

    bool             Find(short PromotionNo);
    bool             FindArticle(const long ArticleNo);

protected:
private:
    friend class pxPromoCollectListIter;
};

class pxPromoCollectListIter : public nDListCollectIter
{

public:
// constructors:
    pxPromoCollectListIter(pxPromoCollectList& list) : nDListCollectIter(list) {;}
// destructor:
    virtual  ~pxPromoCollectListIter() {;}
};
#endif
