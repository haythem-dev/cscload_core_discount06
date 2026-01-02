/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

PXCALCRANGE.HPP

REVISION HISTORY

05 Jan 2006 V1.00 REV 00 written by Ysbrand Bouma.
*/

#ifndef PXCALCRANGE_DOTH
#define PXCALCRANGE_DOTH

#include "pxdiscount.hpp"
#include "types/pricetypeenum.inc"

class pxRangeControl : public nCollectable
{

public:
/*----------------------------------------------------------------------------*/
/*  Discount RangeCondistion enumeration.                                     */
/*----------------------------------------------------------------------------*/
enum  tRangeCondition
{
    RangeCond_QtyArticleNo       = 1,   // NatraQty for ArticleNo
    RangeCond_PctArticleNo,             // Quantity Pct for ArticleNo on Rangesum
    RangeCond_PctMembers,               // Quantity Pct for all Rangemembers on Rangesum
    RangeCond_QtyMembers,               // NatraQty for all Rangemembers on Rangesum
    RangeCond_QtyPctMembers,            // Natraqty and Pct for all Range members on Rangesum
    RangeCond_MultyCondArticle,         // This is a Main Range with Subconditions on article level
    RangeCond_MultyCondManufacturer,    // This is a Main Range with Subconditions on Manufacturer level
    RangeCond_BaseValue,                // This is a Main Range base on a base range value
    RangeCond_FixDiscValMembers,        // Fixed discount value for all Rangemembers on Rangesum
    RangeCond_Last
};

/*----------------------------------------------------------------------------*/
/*  Discount RangeCondistion enumeration.                                     */
/*----------------------------------------------------------------------------*/
enum  tTargetPromoCondition
{
    Cond_DiscountArticleQty_PctAllMembers  = 1,   // NatraQty for DiscountArticle and Pct for all Rangemembers
    Cond_DiscountArticleQty,                      // NatraQty for DiscountArticle
    Cond_PctAllMembers,                           // Quantity Pct for all Rangemembers on Rangesum
    Cond_QtyAllMembers,                           // NatraQty for all Rangemembers on Rangesum
    Cond_QtyPctAllMembers,                        // Natraqty and Pct for all Range members on Rangesum
    Cond_PctArticleNo,                            // Quantity Pct for ArticleNo
    Cond_ArticleNo,                               // Quantity Pct for ArticleNo
    Cond_Last
};
// constructors:
                pxRangeControl(const short  BranchNo,
                               const long   DiscountGrpNo,
					           const long   ArticleNo,
                               const long   QtyInRange,
                               const long   QtyPackInRange,
                               const long   CustomerNo,
                               const double ShipValue,
                               const PriceTypeEnum PreisTyp
                              );

                pxRangeControl(const pxRangeControl &src);

// destructor:
                virtual  ~pxRangeControl();
/*@DS
PUBLIC MEMBER OPERATORS
*/
    pxRangeControl&   operator=(const pxRangeControl& src);
//  Assigns the values of 'src' to self and returns a reference to it.


/*@DS
PUBLIC MEMBER FUNCTIONS
*/
    virtual  int      CompareTo(const nCollectable *that, void *p,
                                const long lparm) const;
    virtual  long     AddQuantity(const long q);
             long     AddQtyPack(const long q);
             double   AddShipValue (const double q);
             nMoney   AddInvoiceValue (const nMoney q);
             nMoney   AddNaturalRebateValue (const nMoney q);
             nMoney   AddGroupInvoiceValue  (const nMoney q);
             nMoney   AddGroupNaturalRebateValue  (const nMoney q);


// Some Queries
    short       BranchNo()            { return BranchNo_;          }
    long        DiscountGrpNo()       { return DiscountGrpNo_ ;    }
	long        ArticleNo()           { return ArticleNo_ ;        }
    long        QtyInRange()          { return QtyInRange_ ;       }
    long        QtyPackInRange()      { return QtyPackInRange_ ;   }
    long        CustomerNo()          { return CustomerNo_;        }
    nMoney      ShipValue()           { return ShipValue_;         }
    short       GrpDiscountTyp()      { return GrpDiscountTyp_;    }
    PriceTypeEnum PreisTyp()          { return PreisTyp_;          }
    short       PromotionNo()         { return PromotionNo_;       }
    nMoney      InvoiceValue()        { return InvoiceValue_;      }
    nMoney      NaturalRebateValue()  { return NaturalRebateValue_;}
    nMoney      GroupInvoiceValue()   { return GroupInvoiceValue_; }
    nMoney      GroupNaturalRebateValue()   { return GroupNaturalRebateValue_; }
    pxDiscount* RangeCondition()      { return RangeCondition_;    }
    pxDiscountList* TargetPromoList() { return TargetPromoList_;   }
    pxDiscountList* RangePreviewList(){ return RangePreviewList_;  }

// Member Methodes
    pxDiscount* RangeCondition(pxSession* session,pxOrder* order);
    int         DefineRangeDiscountTyp(pxDiscountList*  diskl, pxRangeCollectList* rcl);
    short       CheckMultipleConditions(pxDiscountList*  diskl, pxRangeCollectList* rcl);
    bool        IsValidMultyCondRange( pxDiscountList*  diskl,pxRangeCollectList* rcl);
    bool        IsValidTargetPromotion(pxSession* session,pxOrder* order);
    bool        IsValidCondition(pxDiscount* discentry,pxRangeCollectList* rcl);
    int         SetGrpDiscountTyp(pxDiscount* diskentry);
    pxDiscount* GetTargetControlEntry();
    double      GetTargetControlBaseValue();
    long        GetTargetControlBaseQty();
    bool        RangeConditionPreview(pxSession* session,pxOrder* order);

// Member Set und Update
    void        SetPromotionNo(const short PromotionNo)
                {PromotionNo_ = PromotionNo;}
    void        SetGroupInvoiceValue(const double value)
                {GroupInvoiceValue_ = value;}
    void        SetInvoiceValue(const double value)
                {InvoiceValue_ = value;}
    void        SetNaturalRebateValue(const double value)
                {NaturalRebateValue_ = value;}
    void        SetGroupNaturalRebateValue(const double value)
                {GroupNaturalRebateValue_ = value;}

protected:
    void        Init();

    short      BranchNo_;            // Branchno
    long       DiscountGrpNo_;       // discountgroup number
	long       ArticleNo_;		     // ArticleNo
    long       QtyInRange_;          // Total quantit within this range
    long       QtyPackInRange_;      // Total quantit packages(StdMenge) in Range
    long       CustomerNo_;          // CustomerNo
    nMoney      ShipValue_ ;          // Shipvalue
    short       GrpDiscountTyp_;      // GroupDiscounttyp
    PriceTypeEnum PreisTyp_;            // price type
    short       PromotionNo_;         // Promotion number
    nMoney      InvoiceValue_;        // invoice value of the entire group
    nMoney      NaturalRebateValue_;  // natural rebate value of the entire group
    nMoney      GroupInvoiceValue_;   // invoice value of the entire group with Group Condition
    nMoney      GroupNaturalRebateValue_;   // natural rebate  value of the entire group with Group Condition

    pxDiscount*     RangeCondition_;  // Rangecondition
    pxDiscountList* TargetPromoList_; //
    pxDiscountList* RangePreviewList_; //


private:
    friend class pxRangeControlList;
};

class pxRangeControlList : public nDListCollect
{

public:
// constructors:

// destructor:
                virtual  ~pxRangeControlList() {Clear();}
// member functions:
    void        Clear();
    pxRangeControl*  Find(const short PromotionNo);
protected:
private:
    friend class pxRangeControlListIter;
};

class pxRangeControlListIter : public nDListCollectIter
{

public:
// constructors:
    pxRangeControlListIter(pxRangeControlList& list) : nDListCollectIter(list) {;}
// destructor:
    virtual  ~pxRangeControlListIter() {;}
};
#endif
