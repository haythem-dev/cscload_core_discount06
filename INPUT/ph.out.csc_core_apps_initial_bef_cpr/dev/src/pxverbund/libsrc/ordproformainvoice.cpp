#include "pxrecord.h"
#include "pxdevice.hpp"
#include "pxsess.hpp"
#include "pxcstbas.hpp"
#include "pxcustomergrpflags.hpp"
#include "pxartbas.hpp"
#include "pxitem.hpp"
#include "pxcomtyp.hpp"
#include "pxstktra.hpp"
#include "pxorder.hpp"
#include "pxoeparm.hpp"
#include "pxcstot.hpp"
#include "pxcstrou.hpp"
#include "pxoclpar.hpp"
#include "pxrangecollect.hpp"
#include "pxrangemember.hpp"
#include "pxdiscountordtyp.hpp"
#include "pxrangecontrol.hpp"
#include "pxitemdiscount.hpp"
#include "types/messagecodeenum.inc"

/*----------------------------------------------------------------------------*/
/*  ProformaInvoice: This is a special methode devoloped for the bulgarian    */
/*  order entry system.                                                       */
/*  This methode calculates the invoice price for this order under respect    */
/*  of all rebate conditions                                                  */
/*  It recalculates the members WertAuftrag, Wertlieferung, WertZeilen.       */
/*  This fuction is most reflected by the XML application. It is very         */
/*  important to send all information recarding quantities, correct prices and*/
/*  correct discount percentages to the customer                              */
/*----------------------------------------------------------------------------*/
int pxOrder::ProformaInvoice( const short pricetype /* = -1 as default */)
{
    pxCustBase*       customer    = Customer();       // customer
    pxRangeControlList*    rangcl = NULL;
    pxRangeControl*      rentriep = NULL;             // RangeControlEntry Pointer
    pxOrderItem*             item = NULL;             // OrderItem Entry
    pxItemDiscountList* posrablist = NULL;
    tKDAUFTRAGPOSRAB        record;
    pxDiscount*         diskentry = NULL;             // Discount entry

/*----------------------------------------------------------------------------*/
/*  Basic sanity checks.                                                      */
/*----------------------------------------------------------------------------*/
     ClearError();
    if (!ItemList_ )                    // then order item processing not open
       return ExternalError(CMsgStream(), CMSG_ORD_NOTOPEN, KdAuftragNr_);
/*----------------------------------------------------------------------------*/
/*  Additional sanity checks.                                                 */
/*----------------------------------------------------------------------------*/
    if ( !IsPseudoLock() )
    {
       if ( !IsLocked() )                  // order still locked ??
       {
          ExternalError(CMsgStream(),CMSG_ORD_LOCK_DISAPPEARED, KdAuftragNr_);
          return NULL;
       }
    }
    if (AnzPos() == 0 )
       return ErrorState();

    if (!Session()->isBulgaria() && !Session()->isFrance()) // CPR-171543 - also needed for France
       return NULL;

    // OrderType is not discountable
    if ( !OrderType().IsDiscountable() )
          return ErrorState();

    // Customer Group is not discountable(Group 8,9,13)
    if ( !customer->CustomerGroupFlagsList()->IsKscDiscountEnabled()  )
          return ErrorState();

    if ( ItemListProforma_ )
    {
       delete ItemListProforma_;
       ItemListProforma_ = NULL;
    }

    ItemListProforma( pricetype );
	if (ItemListProforma_->Entries() == 0)
	{
		return ErrorState();
	}

/*----------------------------------------------------------------------------*/
/*  First collect all rebates(percentages) until now into a temporary         */
/*  pxItemDiscountList(posrablist). Scan for that the order position list     */
/*----------------------------------------------------------------------------*/
    posrablist = new pxItemDiscountList(Session());
    pxOrderItemListIter it(*ItemListProforma_);
    while ( (item = (pxOrderItem*) ++it) != NULL )
    {
        pxItemDiscount* posrabp = item->ItemDiscountList()->FindDiscountValuePct();
       if (posrabp)
       {
          Assign(record, *posrabp);
          posrablist->AddToList(&record,0);
       }
    }

	// Ticket SR-17113789
	if (OrderType().IsSNoPromotions())
	{
		AssignPosDiscountValPctProforma(posrablist); // call  InvoiceValue for each position
		ItemListProforma(pricetype);
		AssignPosDiscountValPctProforma();
		ReCalcValuesProforma(posrablist);
		delete posrablist;
		return ErrorState();
	}

/*----------------------------------------------------------------------------*/
/*  Now look for discount groups like we do while orderclosing under respect  */
/*  of the temporary itemdiscountlist posrablist                              */
/*  Be carefull if there are no target promotions within this order. In that  */
/*  case it is stingently necessary to recalculate the  InvoiceValue for Item */
/*  under respect of the posrablist aswas build above. The meaning for doing  */
/*  this,is to get the DiscountValPctProforma(pxOrderItem member) for each    */
/*  position. DiscountValPctProforma will be send back to the customer.       */
/*----------------------------------------------------------------------------*/
    RangeCollectList();                     // init RangeCollectList
    TargetPromotionCollectList();           // collection of discountgroupmembers
    if ( !RangeCollectList()->Entries() )
    {
       AssignPosDiscountValPctProforma( posrablist ); // call  InvoiceValue for each position
       ItemListProforma( pricetype );
       AssignPosDiscountValPctProforma();
       ReCalcValuesProforma(posrablist);
       delete posrablist;
       delete RangeCollectList_;
       RangeCollectList_ = NULL;
       return ErrorState();
    }

    rangcl = TargetPromotionControleList();  // collection of discountgroup numbers
/*----------------------------------------------------------------------------*/
/*  First check validity of Rangecontrol Entries                              */
/*  every non quilty entry will be removed from the list                      */
/*----------------------------------------------------------------------------*/
    pxRangeControlListIter    cursor(*rangcl);
    if ( rangcl->Entries() )
    {
       while ( (rentriep = (pxRangeControl*) ++cursor) != NULL )
       {
          if ( !rentriep->IsValidTargetPromotion(Session(),this))
          {
              RangeCollectList()->DeleteInvalidEntries (rentriep->DiscountGrpNo(), rentriep->PreisTyp());
              delete cursor.Remove();
          }
       }
    }
    if ( rangcl->Entries() == 0)
    {
       AssignPosDiscountValPctProforma( posrablist ); // call  InvoiceValue for each position
       ItemListProforma( pricetype );
       AssignPosDiscountValPctProforma();
       ReCalcValuesProforma(posrablist);
       delete rangcl;
       delete posrablist;
       delete RangeCollectList_;
       RangeCollectList_ = NULL;
       rangcl = NULL;
       return ErrorState();
    }
    cursor.Reset();

/*----------------------------------------------------------------------------*/
/*  Second: collect promotion information to each entry of TargetPromotion    */
/*  where articleno > 0                                                       */
/*----------------------------------------------------------------------------*/
    while ( (rentriep = (pxRangeControl*) ++cursor) != NULL )
    {
       if ( rentriep->TargetPromoList() == NULL)
          continue;

       CollectItemTargetPromotions(rentriep);            // per Position
    }

/*----------------------------------------------------------------------------*/
/* Assign best Promotion to each position                                     */
/*----------------------------------------------------------------------------*/
    AssignDiscountToPosition(rangcl, posrablist);

/*----------------------------------------------------------------------------*/
/*  Third: Assign TargetPromotion depend on condition                         */
/*  where articleno > 0                                                       */
/*----------------------------------------------------------------------------*/
    cursor.Reset();
    while ( (rentriep = (pxRangeControl*) ++cursor) != NULL )
    {
       if ( rentriep->TargetPromoList() == NULL)
          continue;
       pxDiscountListIter dCursor(*(rentriep->TargetPromoList()));
       while ( (diskentry = (pxDiscount*) ++dCursor) != NULL )
       {
          rentriep->SetGrpDiscountTyp(diskentry);
          switch (rentriep->GrpDiscountTyp())
          {
             case  pxRangeControl :: Cond_DiscountArticleQty_PctAllMembers   :
             {
                TargetDiscountArticleProforma(rentriep,diskentry );
                if ( !(IsGoodState()) )
                {
                   ExternalError(CMsgStream(), CMSG_ORD_RANGEARTICLE_ERROR, KdAuftragNr_, diskentry->DiscountArticle());
                }
                AssignDiscountPctToAllMembers ( rentriep, diskentry,posrablist);          // assign DiscountPct for TargetPromotion Members
                break;
             }
             case  pxRangeControl ::  Cond_PctAllMembers :
             {
                AssignDiscountPctToAllMembers ( rentriep, diskentry,posrablist);
                break;
             }
             case  pxRangeControl ::  Cond_QtyPctAllMembers :
             {
                AssignDiscountPctToAllMembers ( rentriep, diskentry, posrablist );          // assign DiscountPct for TargetPromotion Members
                //AssignDiscountQtyToAllMembers( rentriep, diskentry );
                break;
             }
             case  pxRangeControl :: Cond_DiscountArticleQty:
             {
                TargetDiscountArticleProforma(rentriep,diskentry );
                if ( !(IsGoodState()) )
                {
                   ExternalError(CMsgStream(), CMSG_ORD_RANGEARTICLE_ERROR, KdAuftragNr_, diskentry->DiscountArticle());
                }
                break;
             }
             //case  pxRangeControl ::  Cond_ArticleNo :
             //{
             //   AssignDiscountToPosition ( rentriep, diskentry );               // assign DiscountPct for TargetPromotion Member
             //   break;
             //}
             default:
             {
                break;
             }
          }
       }
    }
/*----------------------------------------------------------------------------*/
/*  Now copy DiscountValuePctProforma to ItemListProforma()                   */
/*----------------------------------------------------------------------------*/
    AssignPosDiscountValPctProforma();

/*----------------------------------------------------------------------------*/
/*  Now build up the new delivery value of this order (WertLieferung)         */
/*  on respect of the temporary itemdiscountlist posrablist                   */
/*----------------------------------------------------------------------------*/
    ReCalcValuesProforma(posrablist);

    delete posrablist;
    if ( rangcl )
       delete rangcl;
    if (RangeCollectList_ )
    {
       delete RangeCollectList_;
       RangeCollectList_ = NULL;
    }
    DeleteItemPromoCollectList();
    return ErrorState();
}
/*----------------------------------------------------------------------------*/
/*  DeleteItemPromoCollectList()                                              */
/*  deletes on each item the PromoCollectList                                 */
/*----------------------------------------------------------------------------*/
int
pxOrder :: DeleteItemPromoCollectList
(
)
{
    pxOrderItem*      item        = NULL;
    pxOrderItemListIter it(*ItemList_);     // define an iterator

    while ( (item = (pxOrderItem*) ++it) != NULL )
    {
       item->DeletePromotionCollectList();
    }
    return ErrorState();
}
/*----------------------------------------------------------------------------*/
/*  AssignPosDiscountValPctProforma                                           */
/*----------------------------------------------------------------------------*/
int
pxOrder :: AssignPosDiscountValPctProforma
(
    pxItemDiscountList* posrablist
)
{
    pxOrderItem*      item        = NULL;
    pxOrderItemListIter it(*ItemList_);     // define an iterator

    while ( (item = (pxOrderItem*) ++it) != NULL )
    {
       item->InvoiceValue(posrablist);
    }
    return ErrorState();
}
/*----------------------------------------------------------------------------*/
/*  AssignPosDiscountValPctProforma                                           */
/*----------------------------------------------------------------------------*/
int
pxOrder :: AssignPosDiscountValPctProforma
(
)
{
    pxOrderItem*          item = NULL;
    pxOrderItemListIter it(*ItemList_);     // define an iterator

    if ( ItemListProforma_ == NULL )        // nothing to do
       return ErrorState();

    while ( (item = (pxOrderItem*) ++it) != NULL )
    {
        pxOrderItem* pos = (pxOrderItem*)ItemListProforma()->At(item->PosNr() - 1); // get proformaitem
       if (pos)
       {
          pos->SetDiscountValPctProforma(item->DiscountValPctProforma());
       }
    }
    return ErrorState();
}
