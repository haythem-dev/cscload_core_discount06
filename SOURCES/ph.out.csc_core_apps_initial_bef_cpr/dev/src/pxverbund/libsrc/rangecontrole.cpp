#include "pxrecord.h"
#include "pxsess.hpp"
#include "pxdevice.hpp"
#include "pxartbas.hpp"
#include "pxitem.hpp"
#include "pxorder.hpp"
#include "pxcustpharmgroup.hpp"
#include "pxcstbas.hpp"
#include "pxrangecollect.hpp"
#include "pxrangecontrol.hpp"
#include "pxdiscount.hpp"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxRangeControl :: pxRangeControl
(
    const short BranchNo,              // Branchnumber
    const long  DiscountGrpNo,         // DiscountGrpNo
	const long  ArticleNo,            // ArticleNo
    const long  QtyInRange,            // Sum within Range
    const long  QtyPackInRange,        // Sum within Range
    const long  CustomerNo,            // CustomerNo
    const double ShipValue,           // ShipValue
    const PriceTypeEnum PreisTyp              // PreisTyp
)
{
    Init();
    BranchNo_         = BranchNo;
    DiscountGrpNo_    = DiscountGrpNo;
	ArticleNo_        = ArticleNo;
    QtyInRange_       = QtyInRange;
    QtyPackInRange_   = QtyPackInRange;
    CustomerNo_       = CustomerNo;
    ShipValue_        = ShipValue;
    PreisTyp_         = PreisTyp;
    PromotionNo_      = 0;
    RangeCondition_   = NULL;
    TargetPromoList_  = NULL;
    RangePreviewList_ = NULL;

}

/*----------------------------------------------------------------------------*/
/*  Copy constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxRangeControl :: pxRangeControl
(
    const pxRangeControl& src
)
{
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxRangeControl :: ~pxRangeControl()
{
    if ( RangeCondition_ )
       delete RangeCondition_;
    if ( TargetPromoList_ )
       delete TargetPromoList_;
    if ( RangePreviewList_ )
       delete RangePreviewList_;
}
/*----------------------------------------------------------------------------*/
/*  Init      .                                                               */
/*----------------------------------------------------------------------------*/
void
pxRangeControl :: Init()
{
    ShipValue_                 = 0.0;
    InvoiceValue_              = 0.0;
    NaturalRebateValue_        = 0.0;
    GroupInvoiceValue_         = 0.0;
    GroupNaturalRebateValue_   = 0.0;
}
/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*----------------------------------------------------------------------------*/
pxRangeControl&
pxRangeControl :: operator=( const pxRangeControl& src)
{
    BranchNo_         = src.BranchNo_;
    DiscountGrpNo_    = src.DiscountGrpNo_;
	ArticleNo_        = src.ArticleNo_;
    QtyInRange_       = src.QtyInRange_;
    QtyPackInRange_   = src.QtyPackInRange_;
    CustomerNo_       = src.CustomerNo_;
    ShipValue_        = src.ShipValue_;
    PreisTyp_         = src.PreisTyp_;
    InvoiceValue_     = src.InvoiceValue_;
    NaturalRebateValue_ = src.NaturalRebateValue_;
    GroupInvoiceValue_ = src.GroupInvoiceValue_;
    GroupNaturalRebateValue_ = src.GroupNaturalRebateValue_;
    return *this;
}
/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxRangeCollec list objects being inserted in the following        */
/*  ascending  sequence:                                                      */
/*  BranchNo, DiscountGrpNo                                                   */
/*----------------------------------------------------------------------------*/
int
pxRangeControl :: CompareTo
(
    const nCollectable   *That,
          void           * /*p*/,
    const long           /*lparm*/
)   const
{
    pxRangeControl *that = (pxRangeControl*)That;
    int retval = (BranchNo_ == that->BranchNo_) ? 0
                  : (BranchNo_ > that->BranchNo_ ? 1 : -1);

    if ( retval == 0 )
        retval = (DiscountGrpNo_ == that->DiscountGrpNo_) ? 0
                  : (DiscountGrpNo_ > that->DiscountGrpNo_ ? 1 : -1);

    return retval;
}
/*----------------------------------------------------------------------------*/
/*  Add quantity q from quantity ordered. Returns quantity added.             */
/*----------------------------------------------------------------------------*/
long
pxRangeControl :: AddQuantity
(
    const long q
)
{
    QtyInRange_ += q;
    return q;
}
/*----------------------------------------------------------------------------*/
/*  Add quantity q from quantity ordered. Returns quantity added.             */
/*----------------------------------------------------------------------------*/
long
pxRangeControl :: AddQtyPack
(
    const long q
)
{
    QtyPackInRange_ += q;
    return q;
}
/*----------------------------------------------------------------------------*/
/*  Add Shipvalue q from . Returns quantity added.                            */
/*----------------------------------------------------------------------------*/
double
pxRangeControl :: AddShipValue
(
    const double q
)
{
    ShipValue_ += q;
    return q;
}
/*----------------------------------------------------------------------------*/
/*  Add InvoiceValue q  . Returns quantity added.                             */
/*----------------------------------------------------------------------------*/
nMoney
pxRangeControl :: AddInvoiceValue
(
    const nMoney q
)
{
    InvoiceValue_ += q;
    return q;
}
/*----------------------------------------------------------------------------*/
/*  Add InvoiceValue q  . Returns quantity added.                             */
/*----------------------------------------------------------------------------*/
nMoney
pxRangeControl :: AddNaturalRebateValue
(
    const nMoney q
)
{
    NaturalRebateValue_ += q;
    return q;
}
/*----------------------------------------------------------------------------*/
/*  Add GroupInvoiceValue q  . Returns quantity added.                            */
/*----------------------------------------------------------------------------*/
nMoney
pxRangeControl :: AddGroupInvoiceValue
(
    const nMoney q
)
{
    GroupInvoiceValue_ += q;
    return q;
}
/*----------------------------------------------------------------------------*/
/*  Add GroupInvoiceValue q  . Returns quantity added.                            */
/*----------------------------------------------------------------------------*/
nMoney
pxRangeControl :: AddGroupNaturalRebateValue
(
    const nMoney q
)
{
    GroupNaturalRebateValue_ += q;
    return q;
}
/*----------------------------------------------------------------------------*/
/* RangeCondition: look for an DiscountGrp entry for Branchno, DisccountGrpNo */
/* and PharmacyGroupId. If entries found, so pick up the entry, that fits the */
/* SumInRange_ and return this entry to the caller.                           */
/* Take care for a well constructed pxRangeControl object, to prevent         */
/* unpredictable results                                                      */
/*----------------------------------------------------------------------------*/
pxDiscount*
pxRangeControl :: RangeCondition
(
    pxSession   *session,
    pxOrder*    order
)
{
    pxDiscountList*  diskl = new pxDiscountList(session);
    pxDiscountListIter cursor(*diskl);
    pxDiscount*      diskentry = NULL;
    pxRangeCollectList* rcl = order->RangeCollectList();
    pxCustBase&       customer   = *order->Customer();
    pxCustPharmGroupList *phglist   = customer.PharmGroupList();
    diskl->SelectRange(BranchNo_, DiscountGrpNo_,CustomerNo_);
    diskl->ShrinkGroupExcluded(phglist);
    diskl->ShrinkDiscountPriceType(PreisTyp_);
    diskl->ShrinkCashPaymentPriceType(order, PreisTyp_);
	//diskl->ShrinkDateDelivery(order);

    if (diskl->ReduceToValidOffers())
    {
       for ( cursor.ToLast(); (diskentry = (pxDiscount*)cursor.Current()) != NULL; --cursor )
       {
          if ( (diskentry->BaseQty() > 0  && diskentry->ArticleNo() == 0 ))
          {
             if ( QtyInRange_ >= diskentry->BaseQty() )
                break;
          }
          else
          if  ( diskentry->BaseMultSTDQty() > 0 && diskentry->ArticleNo() == 0 )
          {
             if ( QtyPackInRange_ >= diskentry->BaseMultSTDQty() )
                break;
          }
          else
          if  ( diskentry->BaseValue() > 0.0 )
          {
             if ( ShipValue_ >= (nMoney)diskentry->BaseValue() )
                break;
          }
       }
    }
    if ( diskentry != NULL )
    {
       RangeCondition_ = new pxDiscount(*diskentry);
       if ( diskl->Entries() > 1 )          // more then one entry found
       {
          if (!(IsValidMultyCondRange(diskl,rcl)) )
          {
             delete RangeCondition_;
             RangeCondition_ = NULL;
             delete diskl;
             return RangeCondition_;
          }
       }
       DefineRangeDiscountTyp(diskl,rcl);
    }
    delete diskl;
    return RangeCondition_;
}
/*---------------------------------------------------------------------------*/
/*  Clear entire list.                                                        */
/*----------------------------------------------------------------------------*/
void
pxRangeControlList :: Clear()
{

    pxRangeControl  *curp;
    pxRangeControlListIter cursor(*this);
    while ( (curp = (pxRangeControl*) ++cursor) != NULL )
    {
       cursor.Remove();
       delete curp;
    }
}
/*----------------------------------------------------------------------------*/
/*  DefineRangeDiscountTyp. Try to find out the correct GrpDiscountTyp        */
/*  depend on the available members within RangeCondition_ entry              */
/*----------------------------------------------------------------------------*/
int
pxRangeControl :: DefineRangeDiscountTyp
(
    pxDiscountList*  diskl,
    pxRangeCollectList* rcl
)
{
    // avoid "unused" compiler warning
    { rcl = rcl; }

    int  retval = 0;
    if ( RangeCondition_ )
    {
       // first check for multiple entries
        GrpDiscountTyp_ = CheckMultipleConditions(diskl, rcl);
       if (GrpDiscountTyp_)
       {
          return retval;
       }
       else
       if ( RangeCondition_->DiscountQty() > 0 &&
            RangeCondition_->DiscountArticle() > 0 )
       {
          GrpDiscountTyp_ = RangeCond_QtyArticleNo;
       }
       else
       if ( RangeCondition_->BaseQty() > 0           &&
            RangeCondition_->BaseMultSTDQty() == 0   &&
            RangeCondition_->DiscountValuePct() > 0  &&
            RangeCondition_->DiscountQty() == 0      &&
            RangeCondition_->DiscountArticle() == 0 )
       {
          GrpDiscountTyp_ = RangeCond_PctMembers;
       }
       else
       if ( RangeCondition_->BaseMultSTDQty() > 0    &&
            RangeCondition_->BaseQty() == 0          &&
            RangeCondition_->DiscountValuePct() > 0  &&
            RangeCondition_->DiscountQty() == 0      &&
            RangeCondition_->DiscountArticle() == 0 )
       {
          GrpDiscountTyp_ = RangeCond_PctMembers;
       }
	   else
       if ( RangeCondition_->BaseQty() > 0           &&
            RangeCondition_->BaseMultSTDQty() == 0   &&
            RangeCondition_->DiscountValuePct() == 0  &&
            RangeCondition_->DiscountQty() == 0      &&
            RangeCondition_->DiscountArticle() == 0 && 
			RangeCondition_->FixedDiscountValue() > 0)
       {
          GrpDiscountTyp_ = RangeCond_FixDiscValMembers;
       }	   
       else
       if ( RangeCondition_->BaseQty() > 0           &&
            RangeCondition_->BaseMultSTDQty() == 0   &&
            RangeCondition_->DiscountQty() > 0       &&
            RangeCondition_->DiscountValuePct() == 0 &&
            RangeCondition_->DiscountArticle() == 0 )
       {
          GrpDiscountTyp_ = RangeCond_QtyMembers;
       }
       else
       if ( RangeCondition_->BaseMultSTDQty() > 0    &&
            RangeCondition_->BaseQty() == 0          &&
            RangeCondition_->DiscountQty() > 0       &&
            RangeCondition_->DiscountValuePct() == 0 &&
            RangeCondition_->DiscountArticle() == 0 )
       {
          GrpDiscountTyp_ = RangeCond_QtyMembers;
       }
       else
       if ( RangeCondition_->DiscountQtyPct() > 0 &&
            RangeCondition_->DiscountArticle() > 0)
       {
          GrpDiscountTyp_ = RangeCond_PctArticleNo;
       }
       else
       if ( RangeCondition_->BaseQty() > 0          &&
            RangeCondition_->BaseMultSTDQty() == 0   &&
            RangeCondition_->DiscountQty() > 0       &&
            RangeCondition_->DiscountValuePct() > 0)
       {
          GrpDiscountTyp_ = RangeCond_QtyPctMembers;
       }
       else
       if ( RangeCondition_->BaseQty() == 0          &&
            RangeCondition_->BaseMultSTDQty() == 0   &&
            RangeCondition_->BaseValue() > 0)
       {
          GrpDiscountTyp_ = RangeCond_BaseValue;
       }
    }

    return retval;
}
/*----------------------------------------------------------------------------*/
/*  CheckMultipleConditions. Try to find out the correct GrpDiscountTyp       */
/*  depend on the available members within diskl                              */
/*  Returns retval = GrpDiscountTyp 0 or > 0                                  */
/*----------------------------------------------------------------------------*/
short
pxRangeControl :: CheckMultipleConditions
(
    pxDiscountList*  diskl,
    pxRangeCollectList* rcl
)
{
    // avoid "unused" compiler warning
    { rcl = rcl; }

    short  retval = 0;
    pxDiscountListIter cursor(*diskl);
    pxDiscount*      diskentry = NULL;
    if (diskl->Entries() == 1 )
    {
        return retval;
    }

    while ( (diskentry = (pxDiscount*) ++cursor) != NULL )
    {
       if ( diskentry->ArticleNo() == 0 && diskentry->DiscountQty() > 0 &&
            diskentry->DiscountArticle() > 0  && diskentry->BaseQty() > 0 )
       {
          retval = 0;
          break;
       }
       if ( diskentry->ArticleNo() > 0 && diskentry->BaseQty() > 0  )
       {
          retval = RangeCond_MultyCondArticle;
       }
       else
       if (diskentry->ManufacturerNo() > 0 && diskentry->BaseValue() > 0 )
       {
          retval = RangeCond_MultyCondManufacturer;
       }
       else
       if (diskentry->ManufacturerNo() > 0 && diskentry->DiscountValuePct() > 0.0 )
       {
          retval = RangeCond_MultyCondManufacturer;
       }
    }
    return retval;
}
/*----------------------------------------------------------------------------*/
/*  IsValidMultyCondRange; this methode check the entries of diskl against the*/
/*  entries of the Range Collection List. The result should be a true if all */
/*  conditions within the Discount list are satisfied.                        */
/*----------------------------------------------------------------------------*/
bool
pxRangeControl :: IsValidMultyCondRange
(
    pxDiscountList*  diskl,
    pxRangeCollectList* rcl
)
{
    pxDiscountListIter cursor(*diskl);
    pxDiscount*      diskentry = NULL;
    // unused variable
    // pxRangeCollect*    rc      = NULL;
    if (diskl->Entries() == 1 )
    {
        return true;
    }

    while ( (diskentry = (pxDiscount*) ++cursor) != NULL )
    {
       if ( diskentry->ArticleNo() > 0 &&  diskentry->BaseQty()  > 0 )
       {
          if ( rcl->SumQtyCollect(diskentry->ArticleNo(), diskentry->DiscountGrpNo()) < diskentry->BaseQty() )
          {
              return false;                       // condition does not fit
          }
       }
       else
       if ( diskentry->ArticleNo() == 0 &&  diskentry->BaseQty()  == 0 )
       {
           if ( diskentry->BaseValue() > 0 && diskentry->ManufacturerNo() > 0 )
           {
              if (rcl->SumShipValue( diskentry->ManufacturerNo(), diskentry->DiscountGrpNo() ) < diskentry->BaseValue() )
              {
                 return false;                    // condition does not fit
              }
          }
       }
    }
    return true;
}
/*----------------------------------------------------------------------------*/
/* IsValidTargetPromotion:                                                    */
/* Take care for a well constructed pxRangeControl object, to prevent         */
/* unpredictable results                                                      */
/*----------------------------------------------------------------------------*/
bool
pxRangeControl :: IsValidTargetPromotion
(
    pxSession   *session,
    pxOrder*    order
)
{
    bool retval = true;
    TargetPromoList_ = new pxDiscountList(session);
    pxDiscountListIter cursor(*TargetPromoList_);
    pxDiscount*           diskentry       = NULL;
    pxRangeCollectList*   rcl             = order->RangeCollectList();
    pxCustBase&           customer        = *order->Customer();
    pxCustPharmGroupList *phglist         = customer.PharmGroupList();
    TargetPromoList_->SelectRange(BranchNo_, DiscountGrpNo_,CustomerNo_);
    TargetPromoList_->ShrinkRangePharmacyGroup(phglist);
    TargetPromoList_->ShrinkGroupExcluded(phglist);
    TargetPromoList_->ShrinkDiscountPriceType(PreisTyp_);
    TargetPromoList_->ShrinkCashPaymentPriceType(order, PreisTyp_);
    //TargetPromoList_-->ShrinkDateDelivery(order);

    if ( TargetPromoList_->Entries() == 0 )
    {
       return false;
    }

    while ( (diskentry = (pxDiscount*) ++cursor) != NULL )
    {
       if ( diskentry->ArticleNo() > 0 )
       {
          if (!(rcl->Find( diskentry->ArticleNo(),diskentry ->DiscountGrpNo() )) )
          {
             retval = false;
             break;
          }
       }
       if ( !IsValidCondition(diskentry, rcl) )
       {
          retval = false;
          break;
       }
       SetPromotionNo(diskentry->PromotionNo());
    }
    return retval;
}

/*----------------------------------------------------------------------------*/
/* IsValidCondition                                                           */
/* Take care for a well constructed pxRangeControl object, to prevent         */
/* unpredictable results                                                      */
/*----------------------------------------------------------------------------*/
bool
pxRangeControl :: IsValidCondition
(
    pxDiscount*   diskentry,
    pxRangeCollectList* rcl
)
{
    bool retval = true;
    if ( (diskentry->BaseQty() > 0  && diskentry->ArticleNo() == 0 ))
    {
       if ( QtyInRange_ < diskentry->BaseQty() )
       {
          retval = false;
       }
    }
    else
    if  ( diskentry->BaseMultSTDQty() > 0 && diskentry->ArticleNo() == 0 )
    {
       if ( QtyPackInRange_ < diskentry->BaseMultSTDQty() )
       {
          retval = false;
       }
    }
    else
    if  ( diskentry->BaseValue() > 0.0 && diskentry->ArticleNo() == 0)
    {
       if ( ShipValue_ < (nMoney)diskentry->BaseValue() )
       {
          retval = false;
       }
    }
    else
    if ( diskentry->ArticleNo() > 0 &&  diskentry->BaseQty()  > 0  )
    {
       if ( rcl->SumQtyCollect(diskentry->ArticleNo(), diskentry->DiscountGrpNo()) < diskentry->BaseQty() )
       {
          retval = false;                       // condition does not fit
       }
    }
    else
    if ( diskentry->ArticleNo() > 0 &&  diskentry->BaseValue() > 0.0 )
    {
       if ( rcl->ArticleSumShipValue (diskentry->ArticleNo(), diskentry->DiscountGrpNo()) < diskentry->BaseValue() )
       {
          retval = false;                       // condition does not fit
       }
    }
    else
    if ( diskentry->ArticleNo() == 0 &&  diskentry->BaseQty()  == 0 )
    {
       if ( diskentry->BaseValue() > 0 && diskentry->ManufacturerNo() > 0 )
       {
          if (rcl->SumShipValue( diskentry->ManufacturerNo(), diskentry->DiscountGrpNo() ) < diskentry->BaseValue() )
          {
             retval = false;                    // condition does not fit
          }
       }
    }
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  SetGrpDiscountTyp. Try to find out the correct GrpDiscountTyp             */
/*  depend on the available members within RangeCondition_ entry              */
/*----------------------------------------------------------------------------*/
int
pxRangeControl :: SetGrpDiscountTyp
(
    pxDiscount*   diskentry
)
{
    int  retval = 0;
    if ( diskentry )                    // just for check
    {
       if ( diskentry->ArticleNo() == 0)  // controle record
       {
          if ( diskentry->DiscountQty() > 0 && diskentry->DiscountArticle() > 0 &&
               diskentry->DiscountValuePct() > 0.0 )
          {
             GrpDiscountTyp_ = Cond_DiscountArticleQty_PctAllMembers;
          }
          else
          if ( diskentry->DiscountQty() > 0 && diskentry->DiscountArticle() > 0  &&
               diskentry->DiscountValuePct() == 0.0 )
          {
             GrpDiscountTyp_ = Cond_DiscountArticleQty;
          }
          else
          if ( diskentry->DiscountQty() > 0 && diskentry->DiscountValuePct() == 0.0 &&
               diskentry->DiscountArticle() == 0  )
          {
             GrpDiscountTyp_ = Cond_QtyAllMembers;
          }
          else
          if ( diskentry->DiscountQty() > 0 && diskentry->DiscountValuePct() > 0.0 &&
               diskentry->DiscountArticle() == 0  )
          {
             GrpDiscountTyp_ = Cond_QtyPctAllMembers;
          }
          else
          if ( diskentry->DiscountQty() == 0 && diskentry->DiscountValuePct() > 0.0 &&
               diskentry->DiscountArticle() == 0  )
          {
             GrpDiscountTyp_ = Cond_PctAllMembers;
          }
         // else
         // if ( diskentry->DiscountValuePct() > 0.0 && diskentry->DiscountArticle() > 0 )
         // {
         //    GrpDiscountTyp_ = Cond_PctArticleNo;
         // }
       }
       else
       {
          GrpDiscountTyp_ = Cond_ArticleNo;
       }
    }

    return retval;
}
/*----------------------------------------------------------------------------*/
/* Find                                                                       */
/*----------------------------------------------------------------------------*/
pxRangeControl*
pxRangeControlList :: Find
(
    const short PromotionNo
)
{
    pxRangeControlListIter    it(*this);
    pxRangeControl*      rentriep = NULL;             // RangeControlEntry Pointer


    while ( (rentriep = (pxRangeControl*) ++it) != NULL )
    {
       if (rentriep->PromotionNo() == PromotionNo )
       {
          break;
       }
    }
    return rentriep;
}

/*----------------------------------------------------------------------------*/
/* GetTargetControlEntry:                                                     */
/*----------------------------------------------------------------------------*/
pxDiscount*
pxRangeControl :: GetTargetControlEntry
(
)
{
    pxDiscountListIter it(*TargetPromoList_);
    pxDiscount*      diskentry = NULL;
    if (  TargetPromoList_ )
    {
       while ( (diskentry = (pxDiscount*) ++it) != NULL )
       {
          if ( diskentry->ArticleNo() == 0 && diskentry->ManufacturerNo() == 0 )
          {
             if ( diskentry->DiscountValuePct() > 0.0 || diskentry->DiscountArticle() > 0 ||
                  diskentry->BaseValue() > 0 || diskentry->BaseQty())
             {
                 break;
             }
          }
       }
    }
    return diskentry;
}
/*----------------------------------------------------------------------------*/
/* GetTargetControlBaseValue:                                                 */
/*----------------------------------------------------------------------------*/
double
pxRangeControl :: GetTargetControlBaseValue
(
)
{
    double  retval = 0.0;
    pxDiscountListIter it(*TargetPromoList_);
    pxDiscount*      diskentry = NULL;
    if (  TargetPromoList_ )
    {
       while ( (diskentry = (pxDiscount*) ++it) != NULL )
       {
          if ( diskentry->ArticleNo() == 0 && diskentry->ManufacturerNo() == 0 &&
               diskentry->DiscountGrpNo() > 0  && diskentry->PromotionNo() > 0 )
          {
             retval = diskentry->BaseValue();
             break;
          }
       }
    }
    return retval;
}
/*----------------------------------------------------------------------------*/
/* GetTargetControlBaseQty:                                                   */
/*----------------------------------------------------------------------------*/
long
pxRangeControl :: GetTargetControlBaseQty
(
)
{
    long  retval = 0;
    pxDiscountListIter it(*TargetPromoList_);
    pxDiscount*      diskentry = NULL;
    if (  TargetPromoList_ )
    {
       while ( (diskentry = (pxDiscount*) ++it) != NULL )
       {
          if ( diskentry->ArticleNo() == 0 && diskentry->ManufacturerNo() == 0 &&
               diskentry->DiscountGrpNo() > 0 && diskentry->PromotionNo() > 0 )
          {
             retval = diskentry->BaseQty();
             break;
          }
       }
    }
    return retval;
}

/*----------------------------------------------------------------------------*/
/* IsValidTargetPromotion:                                                    */
/* Take care for a well constructed pxRangeControl object, to prevent         */
/* unpredictable results                                                      */
/*----------------------------------------------------------------------------*/
bool
pxRangeControl :: RangeConditionPreview
(
    pxSession   *session,
    pxOrder*    order
)
{
    if(RangePreviewList_ != NULL)
        return false;
    RangePreviewList_ = new pxDiscountList(session);
    pxDiscountListIter cursor(*RangePreviewList_);
    // unused variable
    // pxDiscount*           diskentry       = NULL;
    // unused variable
    /* pxRangeCollectList*   rcl             = */ order->RangeCollectList();
    pxCustBase&           customer        = *order->Customer();
    pxCustPharmGroupList *phglist         = customer.PharmGroupList();
    
    if (DiscountGrpNo_ == 0)    // For HR CPR-250101 
    {
        RangePreviewList_->Select(21, BranchNo_, ArticleNo_, customer.IDFNr());
    }
    else 
    {
        RangePreviewList_->SelectRange(BranchNo_, DiscountGrpNo_, CustomerNo_);
    }
    RangePreviewList_->ShrinkGroupExcluded(phglist);
    RangePreviewList_->ShrinkDiscountPriceType(PreisTyp_);
    RangePreviewList_->ShrinkCashPaymentPriceType(order, PreisTyp_);

    if ( RangePreviewList_->Entries() == 0 )
    {
       return false;
    }

    return true;
}
