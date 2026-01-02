/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

Implementation of class pxPromoCollect.

REVISION HISTORY

23 Feb 2006 V1.00 REV 00 written by Ysbrand Bouma.
*/
#include "pxpromotioncollect.hpp"
#include "pxrecord.h"
#include "pxsess.hpp"
#include "pxdevice.hpp"
#include "pxartbas.hpp"
#include "pxitem.hpp"
#include "pxorder.hpp"
#include "pxstktra.hpp"
#include "pxcomtyp.hpp"
#include "pxordtyp.hpp"
#include "pxcstot.hpp"
#include "pxcstbas.hpp"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxPromoCollect :: pxPromoCollect
(
    const short PromotionNo,           // PromotionNumber
    const long  DiscountGrpNo,         // DiscountGrpNo
    const long  PosNr,                 // Positionnumber
    const long  ArticleNo              // ArtikelNumberPositionnumber
)
{
    PromotionNo_      = PromotionNo;
    DiscountGrpNo_    = DiscountGrpNo;
    PosNr_            = PosNr;
    ArticleNo_        = ArticleNo;
    DiscountValuePct_ = 0.0;
    DiscountQty_      = 0;
    PromotionType_    = 0;
    AddOnPromoDiscOk_ = '0';
    AddOnStdDiscOk_   = '0';
    Priority_         = 0;
    GrossProfitPct_   = 0.0;
    RefundPct_        = 0.0;
    RefundValue_      = 0.0;
    RefundType_       = 0;
}

/*----------------------------------------------------------------------------*/
/*  Copy constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxPromoCollect :: pxPromoCollect
(
    const pxPromoCollect& src
)
{
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxPromoCollect :: ~pxPromoCollect()
{
    ;
}
/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*----------------------------------------------------------------------------*/
pxPromoCollect&
pxPromoCollect :: operator=( const pxPromoCollect& src)
{
    PromotionNo_      = src.PromotionNo_;
    DiscountGrpNo_    = src.DiscountGrpNo_;
    PosNr_            = src.PosNr_;
    ArticleNo_        = src.ArticleNo_;
    DiscountValuePct_ = src.DiscountValuePct_;
    DiscountQty_      = src.DiscountQty_;
    AddOnPromoDiscOk_ = src.AddOnPromoDiscOk_;
    AddOnStdDiscOk_   = src.AddOnStdDiscOk_;
    Priority_         = src.Priority_;
    GrossProfitPct_   = src.GrossProfitPct_;
    RefundPct_        = src.RefundPct_;
    RefundValue_      = src.RefundValue_;
    RefundType_       = src.RefundType_;
    return *this;
}
/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxRangeCollec list objects being inserted in the following        */
/*  ascending  sequence:                                                      */
/*  BranchNo, DiscountGrpNo                                                   */
/*----------------------------------------------------------------------------*/
int
pxPromoCollect :: CompareTo
(
    const nCollectable   *That,
          void           * /* p */,
    const long           /* lparm */
)   const
{
    pxPromoCollect *that = (pxPromoCollect*)That;
    int retval = (Priority_ == that->Priority_) ? 0
                : (Priority_ > that->Priority_ ? 1 : -1);

    if ( retval == 0 )
         retval = (PromotionNo_ == that->PromotionNo_) ? 0
              : (PromotionNo_ > that->PromotionNo_ ? 1 : -1);
    if ( retval == 0 )
       retval = (ArticleNo_ == that->ArticleNo_) ? 0
                : (ArticleNo_ > that->ArticleNo_ ? 1 : -1);

    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Clear entire list.                                                        */
/*----------------------------------------------------------------------------*/
void
pxPromoCollectList :: Clear()
{

    pxPromoCollect  *curp;
    pxPromoCollectListIter cursor(*this);
    while ( (curp = (pxPromoCollect*) ++cursor) != NULL )
    {
       cursor.Remove();
       delete curp;
    }
}

/*----------------------------------------------------------------------------*/
/*  Clear entire list.                                                        */
/*----------------------------------------------------------------------------*/
pxPromoCollect*
pxPromoCollectList :: BestTargetPromotion
(
    const long ArticleNo
)
{

    pxPromoCollect  *curp;
    pxPromoCollect  *bestp = NULL;         // init best-buy pointer
    pxPromoCollectListIter cursor((pxPromoCollectList&)*this); // cast away constness

    if (ArticleNo > 0 )
    {
       if ( FindArticle(ArticleNo) )
       {
          cursor.Reset();
          while ( (curp = (pxPromoCollect*) ++cursor) != NULL )
          {
             if ( curp->ArticleNo() == 0 )
                continue;
             if ( !bestp)
             {
                bestp = curp;
                continue;
             }
             if ( curp->AddOnPromoDiscOk() == '0' &&  bestp->AddOnPromoDiscOk() == '0' &&
                  curp->Priority() < bestp->Priority())
             {
                 bestp = curp;
             }
             else
             if ( curp->AddOnPromoDiscOk() == '0' &&  bestp->AddOnPromoDiscOk() == '1' )
             {
                bestp = curp;
             }
             else
             if ( curp->AddOnPromoDiscOk() == '1' &&  bestp->AddOnPromoDiscOk() == '1' &&
                  curp->Priority() < bestp->Priority())
             {
                bestp = curp;
             }
          }
       }
       else
       {
          cursor.Reset();
          while ( (curp = (pxPromoCollect*) ++cursor) != NULL )
          {
             if ( curp->ArticleNo() > 0 )
                continue;
             if ( !bestp)
             {
                bestp = curp;
                continue;
             }
             if ( curp->AddOnPromoDiscOk() == '0' &&  bestp->AddOnPromoDiscOk() == '0' &&
                  curp->Priority() < bestp->Priority())
             {
                bestp = curp;
             }
             else
             if ( curp->AddOnPromoDiscOk() == '0' &&  bestp->AddOnPromoDiscOk() == '1' )
             {
                bestp = curp;
             }
             else
             if ( curp->AddOnPromoDiscOk() == '1' &&  bestp->AddOnPromoDiscOk() == '1' &&
                  curp->Priority() < bestp->Priority())
             {
                bestp = curp;
             }
          }
       }
    }
    else
    {
       cursor.Reset();
       while ( (curp = (pxPromoCollect*) ++cursor) != NULL )
       {
          if ( curp->ArticleNo() > 0 )
             continue;
          if ( !bestp)
          {
             bestp = curp;
             continue;
          }
          if ( curp->AddOnPromoDiscOk() == '0' &&  bestp->AddOnPromoDiscOk() == '0' &&
               curp->Priority() < bestp->Priority())
          {
              bestp = curp;
          }
          else
          if ( curp->AddOnPromoDiscOk() == '0' &&  bestp->AddOnPromoDiscOk() == '1' )
          {
             bestp = curp;
          }
          else
          if ( curp->AddOnPromoDiscOk() == '1' &&  bestp->AddOnPromoDiscOk() == '1' &&
               curp->Priority() < bestp->Priority())
          {
             bestp = curp;
          }
       }
    }
    return bestp;
}

/*----------------------------------------------------------------------------*/
/*  Find PromotionNo                                                          */
/*----------------------------------------------------------------------------*/
bool
pxPromoCollectList :: Find
(
    short PromotionNo
)
{
    bool retval = false;
    pxPromoCollect  *curp;
    pxPromoCollectListIter cursor((pxPromoCollectList&)*this); // cast away constness


    while ( (curp = (pxPromoCollect*) ++cursor) != NULL )
    {
       if ( curp->PromotionNo() == PromotionNo )
       {
           retval = true;
           break;
       }
    }
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  FindArticle      .                                                        */
/*----------------------------------------------------------------------------*/
bool
pxPromoCollectList :: FindArticle
(
    const long ArticleNo
)
{
    bool retval = false;
    pxPromoCollect* curp;
    pxPromoCollectListIter cursor((pxPromoCollectList&)*this); // cast away constness

    while ( (curp = (pxPromoCollect*) ++cursor) != NULL )
    {
       if ( curp->ArticleNo() == ArticleNo )
       {
           retval = true;
           break;
       }
    }
    return retval;
}
