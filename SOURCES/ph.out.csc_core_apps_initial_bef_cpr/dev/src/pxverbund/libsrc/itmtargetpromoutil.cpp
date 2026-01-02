/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

Class pxOrderItem:
the main purpose of this module is Targetpromotion handling

REVISION HISTORY

28 July 2011 V1.00 REV 00 written by Ysbrand Bouma.
*/

#include "pxitem.hpp"
#include "pxdiscount.hpp"
#include "pxpromotioncollect.hpp"
#include "pxkdauftragposrefund.hpp"
#include "pxbase/pxconstants.hpp"

/*----------------------------------------------------------------------------*/
/*  AssignDiscountPct: first look for an rangememberentry on the database     */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: CheckRefund
(
    pxDiscount*       diskentry,        // must be Targetheader
    pxPromoCollect*   promocollect,     // best promotion
    pxRangeControl*   /*rclentry*/
)
{
    // unused variable
    /* pospromo = */ GetOrderPosPromo(promocollect->PromotionNo());
    // just for save coding
    if ( diskentry == NULL )
    {
       return ErrorState();
    }
    if ( promocollect == NULL )
    {
       return ErrorState();
    }

    if ( diskentry->ArticleNo() > 0 )     // just promotion header
    {
       return ErrorState();
    }

    if ( diskentry->PromotionNo() != promocollect->PromotionNo() )
    {
       return ErrorState();
    }

    // nothing to do if
    if ( diskentry->RefundValue() != pxConstants::mZero && diskentry->RefundPct() == 0.0 )
    {
       return ErrorState();
    }
    if ( diskentry->RefundPct() )          // mistake in masterdata
    {
       if ( KdAuftragPosRefundList())        // there is a List
       {
           pxKdAuftragPosRefund* refund = KdAuftragPosRefundList()->Find(promocollect->PromotionNo());
          if (refund == NULL)
          {
             WriteRefund(pxConstants::mZero, diskentry->RefundPct(), 1, 1, promocollect->PromotionNo());
          }
       }
    }

    return ErrorState();
}
