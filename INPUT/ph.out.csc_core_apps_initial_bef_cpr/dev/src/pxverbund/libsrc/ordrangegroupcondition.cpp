#include "pxrecord.h"
#include "pxdevice.hpp"
#include "pxsess.hpp"
#include "pxcstbas.hpp"
#include "pxartbas.hpp"
#include "pxitem.hpp"
#include "pxcomtyp.hpp"
#include "pxstktra.hpp"
#include "pxorder.hpp"
#include "pxoeparm.hpp"
#include "pxcstot.hpp"
#include "pxcstrou.hpp"
#include "pxcustomergrpflags.hpp"
#include "pxoclpar.hpp"
#include "pxrangecollect.hpp"
#include "pxrangemember.hpp"
#include "pxdiscountordtyp.hpp"
#include "pxrangecontrol.hpp"
#include "pxitemdiscount.hpp"
#include "types/messagecodeenum.inc"

/*----------------------------------------------------------------------------*/
/*  calculateRangeGroupCondition: This is a  methode to calculate the group   */
/*  condition depend on pxRangeControl entry rclentriep                       */
/*  Depend on rclentriep->GrpDiscountType, several methodes are called to     */
/*  build up rclentriep->GroupInvoiceValue_ and                               */
/*  rclentriep->GroupNaturalRebateValue_                                      */
/*  This funcionallity is needed to give the best condition to the customer.  */
/*  Maybe the product related conditions are better as the range group        */
/*  conditions. (rclentriep->InvoiceValue_ and rclentriep->NaturalRebateValue_*/
/*  Take care for a well constructet RangeCollectList_                        */
/*----------------------------------------------------------------------------*/
int pxOrder :: calculateRangeGroupCondition( pxRangeControl* rclentryp, pxItemDiscountList* posrablist )
{
    short            pricetype   = 0;

/*----------------------------------------------------------------------------*/
/*  Basic sanity checks.                                                      */
/*----------------------------------------------------------------------------*/
     ClearError();
    if (!ItemList_ )                    // then order item processing not open
       return ExternalError(CMsgStream(), CMSG_ORD_NOTOPEN, KdAuftragNr_);
/*----------------------------------------------------------------------------*/
/*  Additional sanity checks.                                                 */
/*----------------------------------------------------------------------------*/
    if (!isProformaInvoiceAllowed())
    {
        return NULL;
    }

    if (rclentryp == NULL )
       return ErrorState();

    if ( rclentryp->RangeCondition() == NULL ) // condition not reached
       return ErrorState();

    if ( ItemListProforma_ )
    {
        if (ItemListProforma_->Entries() == 0)
        {
            return ErrorState();
        }
    }
    else
    {
        ItemListProforma(pricetype);
    }

/*----------------------------------------------------------------------------*/
/*  Now check what to do depend on rclentryp->GrpDiscountTyp()                */
/*----------------------------------------------------------------------------*/

    switch (rclentryp->GrpDiscountTyp())
    {
       case pxRangeControl :: RangeCond_QtyArticleNo    :
       {
          calculateGroupQuantityArticleNo(rclentryp);
          if ( !(IsGoodState()) )
          {
             ExternalError(CMsgStream(), CMSG_ORD_RANGEARTICLE_ERROR, KdAuftragNr_, rclentryp->RangeCondition()->DiscountArticle());
          }
          if ( rclentryp->RangeCondition()->DiscountValuePct() )
          {
             calculateGroupDiscountPct(rclentryp, posrablist );
          }
          break;
       }

       case pxRangeControl :: RangeCond_PctArticleNo    :
       {
          calculateGroupPercentageArticleNo(rclentryp);
          break;
       }

       case pxRangeControl :: RangeCond_PctMembers      :
       {
          calculateGroupDiscountPct(rclentryp, posrablist);
          break;
       }

       case pxRangeControl :: RangeCond_FixDiscValMembers      :
        {
            calculateGroupFixedDiscountVal( rclentryp );
            break;
        }

       case pxRangeControl :: RangeCond_QtyMembers      :
       {
          calculateGroupDiscountQty(rclentryp);
          break;
       }

       case pxRangeControl :: RangeCond_QtyPctMembers      :
       {
          calculateGroupDiscountQty(rclentryp);
          calculateGroupDiscountPct(rclentryp, posrablist);
          break;
       }
       default:
       {
          break;
       }
    }
    calculateGroupInvoiceValue(rclentryp);
    calculateGroupNaturalRebateValue(rclentryp);


    return ErrorState();
}
/*----------------------------------------------------------------------------*/
/* calculateGroupInvoiceValuet:  Base input for this methode is the           */
/* ItemListProformat.                                                         */
/*----------------------------------------------------------------------------*/
int
pxOrder :: calculateGroupInvoiceValue
(
    pxRangeControl* rclentryp
)
{
    pxRangeCollectListIter  cursor(*RangeCollectList());
    pxRangeCollect*    rc         = NULL;
    pxOrderItemListIter iterator(*ItemList_); // define an iterator

    if ( rclentryp->RangeCondition() == NULL ) // condition not reached
       return ErrorState();
    // Loop throug the RangeCollect List
    cursor.Reset();
    while ( (rc = (pxRangeCollect*) ++ cursor) != NULL )
    {
       if ( rc->DiscountGrpNo() == rclentryp->DiscountGrpNo() ) // groupno equals
       {
           pxOrderItem* item  = (pxOrderItem*)ItemListProforma_->At(rc->PosNr() - 1); // get item
          if (item)
          {
             rclentryp->AddGroupInvoiceValue(item->calculateInvoiceValue());
          }
       }
    }

    return ErrorState();
}
/*----------------------------------------------------------------------------*/
/* calculateGroupNaturalRebateValue:  Base input for this methode is the      */
/* ItemListProformat.                                                         */
/*----------------------------------------------------------------------------*/
int
pxOrder :: calculateGroupNaturalRebateValue
(
    pxRangeControl* rclentryp
)
{
    pxRangeCollectListIter  cursor(*RangeCollectList());
    pxRangeCollect*    rc         = NULL;
    pxOrderItemListIter iterator(*ItemList_); // define an iterator

    if ( rclentryp->RangeCondition() == NULL ) // condition not reached
       return ErrorState();
    // Loop throug the RangeCollect List
    cursor.Reset();
    while ( (rc = (pxRangeCollect*) ++ cursor) != NULL )
    {
       if ( rc->DiscountGrpNo() == rclentryp->DiscountGrpNo() ) // groupno equals
       {
           pxOrderItem* item = (pxOrderItem*)ItemListProforma_->At(rc->PosNr() - 1); // get item
          if (item)
          {
             rclentryp->AddGroupNaturalRebateValue(item->calculateNaturalRebateValue());
          }
       }
    }

    return ErrorState();
}

/*----------------------------------------------------------------------------*/
/* calulateGroupDiscountPct:  Base input for this methode is the               */
/* RangeControl List. This list contains the summary + conditions informations*/
/* for all RangeMember positions gouped by discountgroupnumber                */
/* There exist just one entry per discountgroupnumber                         */
/* The next basic input is the RangeCollect List. This list contains datailed */
/* informations per RangeMember Position and discount group number            */
/* Depend on those two lists, every rangemember postion becomes the           */
/* discountvaluepercentage depend on the RangeCondition located within the    */
/* RangeControl List for every discount group number                          */
/* Please take care for a well constructed RangeControl List and a well       */
/* constructed RangeCollect List and a well constucted ItemListProforma       */
/* otherwise you become unpredictable results                                 */
/*----------------------------------------------------------------------------*/
int pxOrder :: calculateGroupDiscountPct( pxRangeControl* rclentryp, pxItemDiscountList* posrablist )
{
    pxRangeCollectListIter  cursor(*RangeCollectList());
    pxRangeCollect*    rc         = NULL;
    pxOrderItemListIter iterator(*ItemList_); // define an iterator
    double         ValuePct(0.0);

    if ( rclentryp->RangeCondition() == NULL ) // condition not reached
       return ErrorState();
    // Loop throug the RangeCollect List
    cursor.Reset();
    while ( (rc = (pxRangeCollect*) ++ cursor) != NULL )
    {
       if ( rc->DiscountGrpNo() == rclentryp->DiscountGrpNo() ) // groupno equals
       {
           pxOrderItem* item = (pxOrderItem*)ItemListProforma_->At(rc->PosNr() - 1); // get item
          if (item)
          {
             ValuePct = rclentryp->RangeCondition()->DiscountValuePct();
             if (posrablist == NULL)
             {
                 pxItemDiscount* itemdisc = item->ItemDiscountList()->FindDiscountValuePct();
                 if (itemdisc)
                 {
                     if (rclentryp->RangeCondition()->IsAddonDiscountOk())
                     {
                         itemdisc->SetDiscountValuePct(itemdisc->DiscountValuePct() + ValuePct);
                     }
                     else
                     {
                         itemdisc->SetDiscountValuePct(rclentryp->RangeCondition()->DiscountValuePct());
                     }
                 }
                 else
                 {
                     itemdisc = new pxItemDiscount(Session(), KdAuftragNr_, item->PosNr(),
                         (short)BestBuy_ValuePctCash,
                         rclentryp->RangeCondition()->PharmacyGroupId());
                     itemdisc->SetDiscountValuePct(rclentryp->RangeCondition()->DiscountValuePct());
                     item->ItemDiscountList()->Append(itemdisc);
                 }
             }
             else
             {
                 pxItemDiscount* itemdisc = posrablist->GetEntry(item->PosNr());
                 if ( itemdisc != NULL )
                 {
                    if (rclentryp->RangeCondition()->IsAddonDiscountOk())
                    {
                        itemdisc->SetDiscountValuePct(itemdisc->DiscountValuePct() + ValuePct);
                    }
                    else
                    {
                       itemdisc->SetDiscountValuePct(rclentryp->RangeCondition()->DiscountValuePct());
                    }
                 }
                 else
                 {
                     itemdisc = new pxItemDiscount(Session(), KdAuftragNr_, item->PosNr(), (short)BestBuy_ValuePctCash, rclentryp->RangeCondition()->PharmacyGroupId());
                     itemdisc->SetDiscountValuePct(rclentryp->RangeCondition()->DiscountValuePct());
                     posrablist->Append(itemdisc);
                 }
             }
             item->InvoiceValue(posrablist);
          }
       }
    }

    return ErrorState();
}

/*----------------------------------------------------------------------------*/
int
pxOrder :: calculateGroupFixedDiscountVal
(
    pxRangeControl* rclentryp
)
{
    pxRangeCollectListIter  cursor(*RangeCollectList());
    pxRangeCollect*    rc         = NULL;
    pxOrderItemListIter iterator(*ItemList_); // define an iterator

    if ( rclentryp->RangeCondition() == NULL ) // condition not reached
       return ErrorState();

    // Loop throug the RangeCollect List
    cursor.Reset();
    while ( (rc = (pxRangeCollect*) ++ cursor) != NULL )
    {
       if ( rc->DiscountGrpNo() == rclentryp->DiscountGrpNo() ) // groupno equals
       {
           pxOrderItem* item = (pxOrderItem*)ItemListProforma_->At(rc->PosNr() - 1); // get item
          if (item)
          {
                /*
                if ( rclentryp->RangeCondition()->IsAddonDiscountOk() )
                {
                   item->SetRabattFest(item->RabattFest() + rclentryp->RangeCondition()->FixedDiscountValue());
                }
                else*/
                {
                   item->SetRabattFest(rclentryp->RangeCondition()->FixedDiscountValue());
                }
          }
       }
    }

    return ErrorState();
}


