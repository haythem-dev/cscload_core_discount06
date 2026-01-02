#include "pxrecord.h"
#include "pxsess.hpp"
#include "pxdevice.hpp"
#include "pxcstbas.hpp"
#include "pxcustomergrpflags.hpp"
#include "pxitem.hpp"
#include "pxorder.hpp"
#include "pxoeparm.hpp"
#include "pxordtyp.hpp"
#include "pxcstot.hpp"
#include "pxrangemember.hpp"
#include "pxdiscountordtyp.hpp"
#include "pxrangecollect.hpp"
#include "pxrangecontrol.hpp"
#include "pxoclpar.hpp"
#include "pxitemdiscount.hpp"
#include "pxbase/pxconstants.hpp"
#include "types/origintypeenum.inc"
#include "types/messagecodeenum.inc"

#include <base/irunnable.h>
#include <discount/orderpositiondiscount/iorderpositiondiscountfinder.h>
#include <logger/loggerpool.h>

/*----------------------------------------------------------------------------*/
/* Do the main Rangecalculation on the pxOrderItemList                        */
/* First we build up the Rangecollectionlist, containing discountgroupmember  */
/* information for each position within this orderobject.                     */
/* Second: Build up the Rangecontrolelist, containing information for each    */
/* discountgroupnumber within the Rangecollectionlist.                        */
/* After that calculation takes place for each entry within the               */
/* Rangecontrolelist.                                                         */
/*----------------------------------------------------------------------------*/
int
pxOrder::RangeCalculation
(
)
{
    pxRangeControlList* rangcl = NULL;
    pxRangeControl* rentriep = NULL;             // RangeControlEntry Pointer
    pxOrderItem* item = NULL;             // OrderItem Entry
    short discounttype = 0;            // discounttype

    //temporary kill this function
    if (Session()->isBulgaria() && !Param()->IsSCrema())
    {
        return ErrorState();
    }
    else if (Param()->IsUseNewDiscountCalc())
    {
        if (IsDiscountable())
        {
            libcsc::base::IRunnablePtr calcUC(Session()->getOrderDiscountCalcUC(this));
            calcUC->run();
        }

        return  ErrorState();
    }

    if (false == IsDiscountable())
    {
        return ErrorState();
    }

    if (Param()->IsSIbtCstOrg() && BatchSchreiben() == cORTYPE_AUXILIARY)
    {
        if (!Session()->isFrancePrewhole())
        {
            return ErrorState();
        }
    }

    // just for the french application collectiv orders ordertype "CV"
    // KoArt_ and BuchArt_ must be 22, otherwise no range calculation
    if (OrderType().IsCollectiveOrder())
    {
        if (!(IsCollectiveOrderDiscountable()))
        {
            return ErrorState();
        }
    }

    pxDiscountOrdTypList* dotl = Session()->DiscountOrderTypList();
    if (dotl)
    {
        discounttype = dotl->Find(KdAuftragArt());
    }

    DeleteRangeCollectList();
    RangeCollectList();                 // init RangeCollectList
    BuildRangeCollectList();            // collection of discountgroupmembers
    if (!RangeCollectList()->Entries())
        return ErrorState();
    rangcl = BuildRangeControleList();  // collection of discountgroup numbers

    pxRangeControlListIter    it(*rangcl);
    if (rangcl->Entries())
    {
        while ((rentriep = (pxRangeControl*) ++it) != NULL)
        {
            pxDiscount* discp = rentriep->RangeCondition(Session(), this);
            if (discp)
            {
                if (discounttype != discp->DiscountType())
                {
                    continue;
                }

                if (rentriep->GrpDiscountTyp() > 0)
                {
                    calculateRangeGroupCondition(rentriep);
                    if (rentriep->GroupInvoiceValue() != pxConstants::mZero && Session()->isFrance())
                    {
                        if ((rentriep->InvoiceValue() - rentriep->NaturalRebateValue()) <= (rentriep->GroupInvoiceValue() - rentriep->GroupNaturalRebateValue()))
                        {
                            continue;
                        }
                    }
                }

                switch (rentriep->GrpDiscountTyp())
                {
                case pxRangeControl::RangeCond_QtyArticleNo:
                {
                    RangeDiscountArticle(discp->DiscountArticle(), discp->CalcDiscountQty(rentriep->QtyInRange()), discp->DiscountSpec(),
                        discp->InternalDiscount() == '1', discp->GetDiscountCategory(), discp->PharmacyGroupId());
                    if (!(IsGoodState()))
                    {
                        ExternalError(CMsgStream(), CMSG_ORD_RANGEARTICLE_ERROR, KdAuftragNr_, discp->DiscountArticle());
                    }
                    if (discp->DiscountValuePct() > 0)
                    {
                        AssignRangeDiscountPct(rentriep);          // assign DiscountPct for Rangemembers
                    }
                    break;
                }
                case pxRangeControl::RangeCond_PctArticleNo:
                {
                    double res = (rentriep->QtyInRange() * discp->DiscountQtyPct()) / 100 + 0.5;
                    item = NewOrderItem_03_NatraWithRangeArticle(discp->DiscountArticle(), (long)res, FREESALE_PRICE);
                    if (item == NULL)
                    {
                        ExternalError(CMsgStream(), CMSG_ORD_RANGEARTICLE_ERROR, KdAuftragNr_, discp->DiscountArticle());
                    }
                    break;
                }
                case pxRangeControl::RangeCond_PctMembers:
                {
                    AssignRangeDiscountPct(rentriep);          // assign DiscountPct for Rangemembers
                    break;
                }
                case pxRangeControl::RangeCond_FixDiscValMembers:
                {
                    AssignRangeFixedDiscountVal(rentriep);          // assign fixed discount valuie for Rangemembers
                    break;
                }
                case pxRangeControl::RangeCond_QtyMembers:
                {
                    AssignRangeDiscountQty(rentriep);          // assign DiscountQty for Rangemembers
                    break;
                }
                case pxRangeControl::RangeCond_QtyPctMembers:
                {
                    AssignRangeDiscountQtyPct(rentriep);       // assign DiscountQty and DiscountPct for Rangemembers
                    break;
                }
                case pxRangeControl::RangeCond_MultyCondArticle:
                {
                    AssignRangeMultyCondArticle(rentriep);     // special handling fore multy conditions
                    break;
                }
                case pxRangeControl::RangeCond_MultyCondManufacturer:
                {
                    AssignRangeMultyCondManuMacturer(rentriep); // special handling manufacturers conditions
                    break;
                }
                case pxRangeControl::RangeCond_BaseValue:
                {
                    AssignRangeBaseValue(rentriep);             // special handling base value conditions
                    break;
                }
                default:
                {
                    break;
                }
                }
            }
        }
    }
    delete rangcl;
    return ErrorState();
}

/*----------------------------------------------------------------------------*/
/* First we build up the Rangecollectionlist, containing discountgroupmember  */
/* information for each position within this orderobject.                     */
/*----------------------------------------------------------------------------*/
int
pxOrder::BuildRangeCollectList
(
)
{
    pxOrderItemListIter it(*ItemList_);     // define an iterator
    pxOrderItem* item;

    while ((item = (pxOrderItem*) ++it) != NULL)
    {
        if (!item->IsCancelled())
        {
            item->CollectRangeMember();
        }
    }
    return ErrorState();
}

/*----------------------------------------------------------------------------*/
/* Second: Build up the Rangecontrolelist, containing information for each    */
/* discountgroupnumber within the Rangecollectionlist.                        */
/*----------------------------------------------------------------------------*/
pxRangeControlList*
pxOrder::BuildRangeControleList
(
)
{
    pxRangeControlList* rangecl = new pxRangeControlList();
    pxRangeControl* rangecp = NULL;
    pxRangeCollectListIter  cursor(*RangeCollectList());
    pxRangeCollect* rc = NULL;
    short             VZ = Customer()->Vertriebszentrum(); // customers Branchno

    while ((rc = (pxRangeCollect*) ++cursor) != NULL)
	{
		if (rc->DiscountGrpNo() == 0)   // For HR CPR-250101
		{
            if (rangecp == NULL) 
            {   
                rangecp = new pxRangeControl(VZ, 0, rc->ArticleNo(), 0, 0, Customer()->IDFNr(), 0, rc->PreisTyp());
                rangecl->InsertAscending(rangecp);
                rangecp->AddQuantity(rc->Quantity());
                rangecp->AddQtyPack(rc->QtyPack());
                rangecp->AddShipValue(rc->ShipValue());
                rangecp->AddInvoiceValue(rc->InvoiceValue());
                rangecp->AddNaturalRebateValue(rc->NaturalRebateValue());
            }
            else 
            {
                //boucle inside rangecl and stop whether rc is found using articleno and discountgrpno=0
                bool found = false;
				pxRangeControlListIter it(*rangecl);
				pxRangeControl* rangecpfound = NULL;
				while ((rangecpfound = (pxRangeControl*) ++it) != NULL)
				{
					if (rangecpfound->DiscountGrpNo() == 0 && 
                        rc->ArticleNo() == rangecpfound->ArticleNo() && 
                        rc->PreisTyp() == rangecpfound->PreisTyp())
					{
                        rangecpfound->AddQuantity(rc->Quantity());
                        rangecpfound->AddQtyPack(rc->QtyPack());
                        rangecpfound->AddShipValue(rc->ShipValue());
                        rangecpfound->AddInvoiceValue(rc->InvoiceValue());
                        rangecpfound->AddNaturalRebateValue(rc->NaturalRebateValue());
                        found = true;
						break;
					}
				}
                rangecp = new pxRangeControl(VZ, 0, rc->ArticleNo(), 0, 0, Customer()->IDFNr(), 0, rc->PreisTyp());
				if (!found) // if not found, insert a new entry
                {
                    rangecl->InsertAscending(rangecp);
                    rangecp->AddQuantity(rc->Quantity());
                    rangecp->AddQtyPack(rc->QtyPack());
                    rangecp->AddShipValue(rc->ShipValue());
                    rangecp->AddInvoiceValue(rc->InvoiceValue());
                    rangecp->AddNaturalRebateValue(rc->NaturalRebateValue());
                }
            }
		}
		else    // scan the RangeCollectList, sorted by DiscountGrpNo
        {
			if (rangecp == NULL)
			{
				rangecp = new pxRangeControl(VZ, rc->DiscountGrpNo(), rc->ArticleNo(), 0, 0, Customer()->IDFNr(), 0, rc->PreisTyp());
				rangecl->InsertAscending(rangecp);
			}
			if (rc->DiscountGrpNo() == rangecp->DiscountGrpNo() && rc->PreisTyp() == rangecp->PreisTyp())
			{
				rangecp->AddQuantity(rc->Quantity());
				rangecp->AddQtyPack(rc->QtyPack());
				rangecp->AddShipValue(rc->ShipValue());
				rangecp->AddInvoiceValue(rc->InvoiceValue());
				rangecp->AddNaturalRebateValue(rc->NaturalRebateValue());
			}
			else
			{
				rangecp = new pxRangeControl(VZ, rc->DiscountGrpNo(), rc->ArticleNo(), 0, 0, Customer()->IDFNr(), 0, rc->PreisTyp());
				rangecl->InsertAscending(rangecp);
				rangecp->AddQuantity(rc->Quantity());
				rangecp->AddQtyPack(rc->QtyPack());
				rangecp->AddShipValue(rc->ShipValue());
				rangecp->AddInvoiceValue(rc->InvoiceValue());
				rangecp->AddNaturalRebateValue(rc->NaturalRebateValue());
			}
		}
	}
	return rangecl;
}

/*----------------------------------------------------------------------------*/
/* AssignRangeDiscountPct:  Base input for this methode is the                */
/* RangeControl List. This list contains the summary + conditions informations*/
/* for all RangeMember positions gouped by discountgroupnumber                */
/* There exist just one entry per discountgroupnumber                         */
/* The next basic input is the RangeCollect List. This list contains datailed */
/* informations per RangeMember Position and discount group number            */
/* Depend on those two lists, every rangemember postion becomes the           */
/* discountvaluepercentage depend on the RangeCondition located within the    */
/* RangeControl List for every discount group number                          */
/* Please take care for a well constructed RangeControl List and a well       */
/* constructed RangeCollect List, otherwise you become unpredictable results  */
/*----------------------------------------------------------------------------*/
int
pxOrder::AssignRangeDiscountPct
(
    pxRangeControl* rclentryp,
    pxItemDiscountList* discl
)
{
    pxRangeCollectListIter  cursor(*RangeCollectList());
    pxRangeCollect* rc = NULL;
    pxItemDiscount* itemdisc = NULL;
    // unused variable
    // pxDiscount*      rclRangeCond = NULL;
    pxOrderItemListIter iterator(*ItemList_); // define an iterator
    double         ValuePct(0.0);
    bool           AddOnOk = false;

    if (rclentryp->RangeCondition() == NULL) // condition not reached
    {
        return ErrorState();
    }
    // Loop throug the RangeCollect List
    cursor.Reset();
    while ((rc = (pxRangeCollect*) ++cursor) != NULL)
    {
        if (rc->DiscountGrpNo() == rclentryp->DiscountGrpNo()) // groupno equals
        {
            pxOrderItem* item = (pxOrderItem*)ItemList_->At(rc->PosNr() - 1); // get item
            if (item)
            {
                ValuePct = rclentryp->RangeCondition()->DiscountValuePct();
                if (discl == NULL)
                {
                    if (rclentryp->RangeCondition()->IsAddonDiscountOk())
                    {
                        AddOnOk = item->AddOnDiscountPct(ValuePct);
                    }
                    if (AddOnOk == false)
                    {
                        if (Session()->isSwitzerland())
                        {
                            // remove only conditionally discounts based on discount matrix
                            item->UndoItemDiscountCHforRPG();
                        }
                        else
                        {
                            // remove all existing discounts
                            item->UndoItemDiscount();                      // undo discount
                        }
                        if (Session()->isCroatia())
                        {
                            if (rclentryp->RangeCondition()->DiscountSpec() == DiscSpec_WholeSale)       // 2
                            {
                                itemdisc = new pxItemDiscount(Session(), KdAuftragNr_, item->PosNr(),
                                    (short)BestBuy_ValuePctWholeSale,                        // Pharmos E
                                    rclentryp->RangeCondition()->PharmacyGroupId());
                                itemdisc->SetDiscountValuePct(ValuePct);
                                itemdisc->SetInternalDiscountFlag(rclentryp->RangeCondition()->InternalDiscount() == '1' ? 1 : 0);
                                itemdisc->SetRefundValuePct(rclentryp->RangeCondition()->RefundPct());
                                itemdisc->SetDiscountCategory(rclentryp->RangeCondition()->GetDiscountCategory());
                                itemdisc->Put();
                                item->ItemDiscountList()->Append(itemdisc);
                            }
                            else if (rclentryp->RangeCondition()->DiscountSpec() == DiscSpec_WholeSale_Ind)    // 7
                            {
                                itemdisc = new pxItemDiscount(Session(), KdAuftragNr_, item->PosNr(),           // Pharmos M
                                    (short)BestBuy_ValuePctWholeSaleInd,
                                    rclentryp->RangeCondition()->PharmacyGroupId());
                                itemdisc->SetDiscountValuePct(ValuePct);
                                itemdisc->SetInternalDiscountFlag(rclentryp->RangeCondition()->InternalDiscount() == '1' ? 1 : 0);
                                itemdisc->SetRefundValuePct(rclentryp->RangeCondition()->RefundPct());
                                itemdisc->SetDiscountCategory(rclentryp->RangeCondition()->GetDiscountCategory());
                                itemdisc->Put();
                                item->ItemDiscountList()->Append(itemdisc);
                            }
                            else if (rclentryp->RangeCondition()->DiscountSpec() == DiscSpec_Retail)            // 3
                            {
                                itemdisc = new pxItemDiscount(Session(), KdAuftragNr_, item->PosNr(),           // Pharmos F
                                    (short)BestBuy_ValuePctRetail,
                                    rclentryp->RangeCondition()->PharmacyGroupId());
                                itemdisc->SetDiscountValuePct(ValuePct);
                                itemdisc->SetInternalDiscountFlag(rclentryp->RangeCondition()->InternalDiscount() == '1' ? 1 : 0);
                                itemdisc->SetRefundValuePct(rclentryp->RangeCondition()->RefundPct());
                                itemdisc->SetDiscountCategory(rclentryp->RangeCondition()->GetDiscountCategory());
                                itemdisc->Put();
                                item->ItemDiscountList()->Append(itemdisc);
                            }
                        }
                        else if ((Session()->isSwitzerland()) && (rclentryp->DiscountGrpNo() > 0))
                        {
#ifdef CHDISCLOG
                            basar::VarString logmsg("");
                            char type[10];
                            item->getOrder()->KdAuftragArt().GetData(type, 10);
#endif
                            // check at first if there are other discounts (e.g. OMG or UW)
                            if (isDiscountOMGorUW(item) == false)
                            {
                                // same discount group number, so set the values
#ifdef CHDISCLOG
                                logmsg.format("pxOrder::AssignRangeDiscountPct() - Assorted cash discount set for order=%d, ordertype=%s, pos=%d, no higher priorized discount found", item->getOrder()->KdAuftragNr(), type, item->PosNr());
                                BLOG_DEBUG(libcsc::LoggerPool::getLoggerDiscountCalc(), logmsg);
#endif
                                itemdisc = new pxItemDiscount(Session(), KdAuftragNr_, item->PosNr(),
                                    (short)BestBuy_ValuePctCashAssorted,
                                    rclentryp->RangeCondition()->PharmacyGroupId());      // 7
                                itemdisc->SetDiscountValuePct(ValuePct);
                                itemdisc->SetInternalDiscountFlag(rclentryp->RangeCondition()->InternalDiscount() == '1' ? 1 : 0);
                                itemdisc->SetRefundValuePct(rclentryp->RangeCondition()->RefundPct());
                                itemdisc->SetDiscountCategory(rclentryp->RangeCondition()->GetDiscountCategory());
                                itemdisc->Put();
                                item->ItemDiscountList()->Append(itemdisc);
                            }
                            else
                            {
#ifdef CHDISCLOG
                                logmsg.format("pxOrder::AssignRangeDiscountPct() - Assorted cash discount found for order=%d, ordertype=%s, pos=%d, but OMG or UW discount is higher priorized", item->getOrder()->KdAuftragNr(), type, item->PosNr());
                                BLOG_DEBUG(libcsc::LoggerPool::getLoggerDiscountCalc(), logmsg);
#endif
                            }
                        }
                        else
                        {
                            itemdisc = new pxItemDiscount(Session(), KdAuftragNr_, item->PosNr(),
                                (short)BestBuy_ValuePctCash,
                                rclentryp->RangeCondition()->PharmacyGroupId());      // 7
                            itemdisc->SetDiscountValuePct(ValuePct);
                            if (rclentryp->RangeCondition()->DiscountType() == DiscType_PhoenixMagic)     //  Discounttype 7  //France
                            {
                                itemdisc->SetDiscountType(BestBuy_ValuePctPhoenixMagic);                      // Pharmos K
                            }
                            itemdisc->SetInternalDiscountFlag(rclentryp->RangeCondition()->InternalDiscount() == '1' ? 1 : 0);
                            itemdisc->SetRefundValuePct(rclentryp->RangeCondition()->RefundPct());
                            itemdisc->SetDiscountCategory(rclentryp->RangeCondition()->GetDiscountCategory());
                            itemdisc->Put();
                            item->ItemDiscountList()->Append(itemdisc);
                            //SetDoNotSplittOrder();
                        }
                    }
                }
                else if ((itemdisc = discl->GetEntry(item->PosNr())) != NULL)
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
                    if ((Session()->isSwitzerland()) && (rclentryp->DiscountGrpNo() > 0))
                    {
#ifdef CHDISCLOG
                        basar::VarString logmsg("");
                        char type[10];
                        item->getOrder()->KdAuftragArt().GetData(type, 10);
#endif
                        // add check if exsting discount is OMG or UW, then RGP will be ignored
                        if (isDiscountOMGorUW(item) == false)
                        {
#ifdef CHDISCLOG
                            logmsg.format("pxOrder::AssignRangeDiscountPct() - Assorted cash discount added for order=%d, ordertype=%s, pos=%d, no higher priorized discount found", item->getOrder()->KdAuftragNr(), type, item->PosNr());
                            BLOG_DEBUG(libcsc::LoggerPool::getLoggerDiscountCalc(), logmsg);
#endif
                            itemdisc = new pxItemDiscount(Session(), KdAuftragNr_, item->PosNr(),
                                (short)BestBuy_ValuePctCashAssorted,      // 26
                                rclentryp->RangeCondition()->PharmacyGroupId());
                            itemdisc->SetDiscountValuePct(rclentryp->RangeCondition()->DiscountValuePct());
                            itemdisc->SetInternalDiscountFlag(rclentryp->RangeCondition()->InternalDiscount() == '1' ? 1 : 0);
                            itemdisc->SetRefundValuePct(rclentryp->RangeCondition()->RefundPct());
                            itemdisc->SetDiscountCategory(rclentryp->RangeCondition()->GetDiscountCategory());
                            discl->Append(itemdisc);
                        }
                        else
                        {
#ifdef CHDISCLOG
                            logmsg.format("pxOrder::AssignRangeDiscountPct() - Assorted cash discount found for order=%d, ordertype=%s, pos=%d, but OMG or UW discount is higher priorized", item->getOrder()->KdAuftragNr(), type, item->PosNr());
                            BLOG_DEBUG(libcsc::LoggerPool::getLoggerDiscountCalc(), logmsg);
#endif
                        }
                    }
                    else
                    {
                        itemdisc = new pxItemDiscount(Session(), KdAuftragNr_, item->PosNr(),
                            (short)BestBuy_ValuePctCash,      // 7
                            rclentryp->RangeCondition()->PharmacyGroupId());
                        itemdisc->SetDiscountValuePct(rclentryp->RangeCondition()->DiscountValuePct());
                        itemdisc->SetInternalDiscountFlag(rclentryp->RangeCondition()->InternalDiscount() == '1' ? 1 : 0);
                        itemdisc->SetRefundValuePct(rclentryp->RangeCondition()->RefundPct());
                        itemdisc->SetDiscountCategory(rclentryp->RangeCondition()->GetDiscountCategory());
                        discl->Append(itemdisc);
                    }
                }
                item->InvoiceValue(discl);
            }
        }
    }

    return ErrorState();
}

/*----------------------------------------------------------------------------*/
/* isDiscountOMG. Special case for CH to check if one of the existing         */
/* discounts contains a OMG or UW (manual) discount                           */
/* in this case the range discount (RPG) should not be used and ignore        */
/*----------------------------------------------------------------------------*/
bool pxOrder::isDiscountOMGorUW(pxOrderItem* item)
{
    // check discount list for any OMG entry
    bool ret = false;
    pxItemDiscount* itemdisc = NULL;

#ifdef CHDISCLOG
    basar::VarString logmsg("");
    BLOG_TRACE(libcsc::LoggerPool::getLoggerDiscountCalc(), "pxOrder::isDiscountOMGorUW() - start isDiscountOMGorUW");
#endif
    // check at first if position has a manual discount (for UW)
    if (item->getOrder()->OrderType().IsTransfer() == true)
    {
#ifdef CHDISCLOG
        logmsg.format("pxOrder::isDiscountOMGorUW() - manual discount set for transfer order, so its UW position");
        BLOG_TRACE(libcsc::LoggerPool::getLoggerDiscountCalc(), logmsg);
#endif
        ret = true;
    }
    // then check if position has a discount, which is an OMG
    pxItemDiscountList* discl = item->ItemDiscountList();
    if ((ret == false) && (discl != NULL))
    {
        size_t cnt = discl->Entries();
        for (size_t i = 0; i < cnt; i++)
        {
            itemdisc = (pxItemDiscount*)discl->At(i);
#ifdef CHDISCLOG
            logmsg.format("pxOrder::isDiscountOMGorUW() - check discount item %d, type=%d, category=%d, pct_man=%0.2lf, pct_val=%0.2lf, internal=%d", i, itemdisc->DiscountType(), itemdisc->DiscountCategory(), itemdisc->DiscountValPctMan(), itemdisc->DiscountValuePct(), itemdisc->InternalDiscountFlag());
            BLOG_TRACE(libcsc::LoggerPool::getLoggerDiscountCalc(), logmsg);
#endif
            if ((Session()->isSwitzerland()) && (itemdisc->DiscountType() == ValuePctOMG))
            {
                // found OMG for CH
#ifdef CHDISCLOG
                logmsg.format("pxOrder::isDiscountOMGorUW() - OMG discount set for order, so its OMG position");
                BLOG_TRACE(libcsc::LoggerPool::getLoggerDiscountCalc(), logmsg);
#endif
                ret = true;
            }
        }
    }
#ifdef CHDISCLOG
    BLOG_TRACE(libcsc::LoggerPool::getLoggerDiscountCalc(), "pxOrder::isDiscountOMGorUW() - end isDiscountOMGorUW");
#endif
    return ret;
}

/*----------------------------------------------------------------------------*/
/* AssignRangeDiscountQty. The same funtionality as  AssignRangeDiscountPct,  */
/* but in this methode every rangemember position becomes an additional       */
/* quantity free for the RangeMember Article depend on the discount condition */
/* Please take care for a well constructed RangeControl List and a well       */
/* constructed RangeCollect List, otherwise you become unpredictable results  */
/*----------------------------------------------------------------------------*/
int
pxOrder::AssignRangeDiscountQty
(
    pxRangeControl* rclentryp
)
{
    pxRangeCollectListIter  cursor(*RangeCollectList());
    pxRangeCollect* rc = NULL;
    // unused variable
    // pxItemDiscount*   itemdisc    = NULL;
    // pxDiscount*      rclRangeCond = NULL;
    pxOrderItemListIter iterator(*ItemList_); // define an iterator

    if (rclentryp->RangeCondition() == NULL) // condition not reached
        return ErrorState();
    // Loop throug the RangeCollect List
    cursor.Reset();
    while ((rc = (pxRangeCollect*) ++cursor) != NULL)
    {
        if (rc->DiscountGrpNo() == rclentryp->DiscountGrpNo()) // groupno equals
        {
            pxOrderItem* item = (pxOrderItem*)ItemList_->At(rc->PosNr() - 1); // get item
            if (item)
            {
                item->OrderQuantityRange_RangeArticle(item->MengeBestellt(), rclentryp->RangeCondition()->CalcDiscountQty(item->MengeBestellt()), item->MengeBestellt());
                if (rclentryp->RangeCondition()->InternalDiscount() == '1')
                {
                    item->SetNaturalRabattIntern();
                }
                item->SetNatraCategory(rclentryp->RangeCondition()->GetDiscountCategory());
                item->SetNatraPharmacyGroup(rclentryp->RangeCondition()->PharmacyGroupId());
            }
        }
    }
    return ErrorState();
}

/*----------------------------------------------------------------------------*/
int
pxOrder::AssignRangeFixedDiscountVal
(
    pxRangeControl* rclentryp
)
{
    pxRangeCollectListIter  cursor(*RangeCollectList());
    pxRangeCollect* rc = NULL;
    pxItemDiscount* itemdisc = NULL;

    pxOrderItemListIter iterator(*ItemList_); // define an iterator

    if (rclentryp->RangeCondition() == NULL) // condition not reached
        return ErrorState();

    // Loop throug the RangeCollect List
    cursor.Reset();
    while ((rc = (pxRangeCollect*) ++cursor) != NULL)
    {
        if (rc->DiscountGrpNo() == rclentryp->DiscountGrpNo()) // groupno equals
        {
            pxOrderItem* item = (pxOrderItem*)ItemList_->At(rc->PosNr() - 1); // get item
            if (item)
            {
                item->SetRabattFest(rclentryp->RangeCondition()->FixedDiscountValue());
                item->Put();

                itemdisc = new pxItemDiscount(Session(), KdAuftragNr_, item->PosNr(),
                    (short)BestBuy_FixedDiscountValue,
                    rclentryp->RangeCondition()->PharmacyGroupId());
                itemdisc->SetInternalDiscountFlag(rclentryp->RangeCondition()->InternalDiscount() == '1' ? 1 : 0);
                itemdisc->SetRefundValuePct(rclentryp->RangeCondition()->RefundPct());
                itemdisc->SetDiscountCategory(rclentryp->RangeCondition()->GetDiscountCategory());
                itemdisc->Put();
                item->ItemDiscountList()->Append(itemdisc);
            }
        }
    }
    return ErrorState();
}

/*----------------------------------------------------------------------------*/
/* AssignRangeDiscountQtyPct:  Base input for this methode is the             */
/* RangeControl List. This list contains the summary + conditions informations*/
/* for all RangeMember positions gouped by discountgroupnumber                */
/* There exist just one entry per discountgroupnumber                         */
/* The next basic input is the RangeCollect List. This list contains detailed */
/* informations per RangeMember Position and discount group number            */
/* Depend on those two lists, every rangemember postion becomes the           */
/* discountvaluepercentage and also a quantity for free depend on the         */
/* RangeCondition located within the RangeControl List for every discount     */
/* group number.                                                               */
/* Please take care for a well constructed RangeControl List and a well       */
/* constructed RangeCollect List, otherwise you become unpredictable results  */
/*----------------------------------------------------------------------------*/
int
pxOrder::AssignRangeDiscountQtyPct
(
    pxRangeControl* rclentryp,
    pxItemDiscountList* discl
)
{
    pxRangeCollectListIter  cursor(*RangeCollectList());
    pxRangeCollect* rc = NULL;
    pxItemDiscount* itemdisc = NULL;
    // unused variable
    // pxDiscount*      rclRangeCond = NULL;
    pxOrderItemListIter iterator(*ItemList_); // define an iterator

    if (rclentryp->RangeCondition() == NULL) // condition not reached
        return ErrorState();
    // Loop throug the RangeCollect List
    cursor.Reset();
    while ((rc = (pxRangeCollect*) ++cursor) != NULL)
    {
        if (rc->DiscountGrpNo() == rclentryp->DiscountGrpNo()) // groupno equals
        {
            pxOrderItem* item = (pxOrderItem*)ItemList_->At(rc->PosNr() - 1); // get item
            if (item)
            {
                item->OrderQuantityRange_RangeArticle(item->MengeBestellt(), rclentryp->RangeCondition()->CalcDiscountQty(item->MengeBestellt()), item->MengeBestellt());

                if (discl == NULL)
                {
                    item->UndoItemDiscount();                          // undo discount
                    itemdisc = new pxItemDiscount(Session(), KdAuftragNr_, item->PosNr(),
                        (short)BestBuy_ValuePctCash,
                        rclentryp->RangeCondition()->PharmacyGroupId());
                    itemdisc->SetDiscountValuePct(rclentryp->RangeCondition()->DiscountValuePct());
                    itemdisc->SetInternalDiscountFlag(rclentryp->RangeCondition()->InternalDiscount() == '1' ? 1 : 0);
                    itemdisc->SetRefundValuePct(rclentryp->RangeCondition()->RefundPct());
                    itemdisc->SetDiscountCategory(rclentryp->RangeCondition()->GetDiscountCategory());
                    itemdisc->Put();
                    item->ItemDiscountList()->Append(itemdisc);
                }
                else
                    if ((itemdisc = discl->GetEntry(item->PosNr())) != NULL)
                    {
                        itemdisc->SetDiscountValuePct(rclentryp->RangeCondition()->DiscountValuePct());
                    }
                    else
                    {
                        itemdisc = new pxItemDiscount(Session(), KdAuftragNr_, item->PosNr(),
                            (short)BestBuy_ValuePctCash,
                            rclentryp->RangeCondition()->PharmacyGroupId());
                        itemdisc->SetDiscountValuePct(rclentryp->RangeCondition()->DiscountValuePct());
                        itemdisc->SetInternalDiscountFlag(rclentryp->RangeCondition()->InternalDiscount() == '1' ? 1 : 0);
                        itemdisc->SetRefundValuePct(rclentryp->RangeCondition()->RefundPct());
                        itemdisc->SetDiscountCategory(rclentryp->RangeCondition()->GetDiscountCategory());
                        discl->Append(itemdisc);
                    }
                item->InvoiceValue(discl);
            }
        }
    }
    return ErrorState();
}

/*----------------------------------------------------------------------------*/
/* AssignRangeMultyCondArticle:  Base input for this methode is the             */
/* RangeControl List. This list contains the summary + conditions informations*/
/* for all RangeMember positions gouped by discountgroupnumber                */
/* There exist just one entry per discountgroupnumber                         */
/* The next basic input is the RangeCollect List. This list contains detailed */
/* informations per RangeMember Position and discount group number            */
/* Depend on those two lists, every rangemember postion becomes the           */
/* discountvaluepercentage and also a quantity for free depend on the         */
/* RangeCondition located within the RangeControl List for every discount     */
/* group number.                                                               */
/* Please take care for a well constructed RangeControl List and a well       */
/* constructed RangeCollect List, otherwise you become unpredictable results  */
/*----------------------------------------------------------------------------*/
int
pxOrder::AssignRangeMultyCondArticle
(
    pxRangeControl* rclentryp,
    pxItemDiscountList* discl
)
{
    pxRangeCollectListIter  cursor(*RangeCollectList());
    pxRangeCollect* rc = NULL;
    pxItemDiscount* itemdisc = NULL;
    // unused variable
    // pxDiscount* rclRangeCond = NULL;
    pxOrderItemListIter iterator(*ItemList_); // define an iterator
    bool cFoundCondition = false;
    // unused variable
    // double ValuePct(0.0);
    bool AddOnOk = false;

    if (rclentryp->RangeCondition() == NULL) // condition not reached
        return ErrorState();

    pxDiscountList* diskl = new pxDiscountList(Session());
    pxDiscountListIter itdiskl(*diskl);
    pxDiscount* diskentry = NULL;
    diskl->SelectRange(rclentryp->BranchNo(), rclentryp->DiscountGrpNo(), rclentryp->CustomerNo());

    // Loop throug the RangeCollect List
    cursor.Reset();
    while ((rc = (pxRangeCollect*) ++cursor) != NULL)
    {
        cFoundCondition = false;
        if (rc->DiscountGrpNo() == rclentryp->DiscountGrpNo()) // groupno equals
        {
            diskentry = 0;
            pxOrderItem* item = (pxOrderItem*)ItemList_->At(rc->PosNr() - 1); // get item
            if (item)
            {
                diskentry = diskl->Find(rc->ArticleNo());
                if (diskentry)
                {
                    if (diskentry->DiscountQty() > 0)
                    {
                        item->OrderQuantityRange_RangeArticle(item->MengeBestellt(), diskentry->CalcDiscountQty(item->MengeBestellt()), item->MengeBestellt());
                        cFoundCondition = true;
                    }
                    if (diskentry->DiscountValuePct() > 0)
                    {
                        if (discl == NULL)
                        {
                            if (diskentry->IsAddonDiscountOk())
                            {
                                AddOnOk = item->AddOnDiscountPct(diskentry->DiscountValuePct());
                            }
                            if (!AddOnOk)
                            {
                                item->UndoItemDiscount();                          // undo discount
                                itemdisc = new pxItemDiscount(Session(), KdAuftragNr_, item->PosNr(),
                                    (short)BestBuy_ValuePctCash,
                                    rclentryp->RangeCondition()->PharmacyGroupId());
                                itemdisc->SetDiscountValuePct(diskentry->DiscountValuePct());
                                itemdisc->SetInternalDiscountFlag(rclentryp->RangeCondition()->InternalDiscount() == '1' ? 1 : 0);
                                itemdisc->SetRefundValuePct(rclentryp->RangeCondition()->RefundPct());
                                itemdisc->SetDiscountCategory(rclentryp->RangeCondition()->GetDiscountCategory());
                                itemdisc->Put();
                                item->ItemDiscountList()->Append(itemdisc);
                                cFoundCondition = true;
                            }
                        }
                        else
                            if ((itemdisc = discl->GetEntry(item->PosNr())) != NULL)
                            {
                                if (diskentry->IsAddonDiscountOk())
                                {
                                    itemdisc->SetDiscountValuePct(itemdisc->DiscountValuePct() + diskentry->DiscountValuePct());
                                }
                                else
                                {
                                    itemdisc->SetDiscountValuePct(diskentry->DiscountValuePct());
                                    cFoundCondition = true;
                                }
                            }
                            else
                            {
                                itemdisc = new pxItemDiscount(Session(), KdAuftragNr_, item->PosNr(),
                                    (short)BestBuy_ValuePctCash,
                                    rclentryp->RangeCondition()->PharmacyGroupId());
                                itemdisc->SetInternalDiscountFlag(rclentryp->RangeCondition()->InternalDiscount() == '1' ? 1 : 0);
                                itemdisc->SetRefundValuePct(rclentryp->RangeCondition()->RefundPct());
                                itemdisc->SetDiscountCategory(rclentryp->RangeCondition()->GetDiscountCategory());
                                itemdisc->SetDiscountValuePct(diskentry->DiscountValuePct());
                                discl->Append(itemdisc);
                                cFoundCondition = true;
                            }
                        item->InvoiceValue(discl);
                    }
                    if (cFoundCondition)
                    {
                        continue;
                    }
                }

                if (rclentryp->RangeCondition()->DiscountQty() > 0)
                {
                    item->OrderQuantityRange_RangeArticle(item->MengeBestellt(), rclentryp->RangeCondition()->CalcDiscountQty(rclentryp->QtyInRange()), item->MengeBestellt());
                }
                if (rclentryp->RangeCondition()->DiscountValuePct() > 0)
                {
                    if (discl == NULL)
                    {
                        if (rclentryp->RangeCondition()->IsAddonDiscountOk())
                        {
                            AddOnOk = item->AddOnDiscountPct(rclentryp->RangeCondition()->DiscountValuePct());
                        }
                        if (!AddOnOk)
                        {
                            item->UndoItemDiscount();                          // undo discount
                            itemdisc = new pxItemDiscount(Session(), KdAuftragNr_, item->PosNr(),
                                (short)BestBuy_ValuePctCash,
                                rclentryp->RangeCondition()->PharmacyGroupId());
                            itemdisc->SetDiscountValuePct(rclentryp->RangeCondition()->DiscountValuePct());
                            itemdisc->SetInternalDiscountFlag(rclentryp->RangeCondition()->InternalDiscount() == '1' ? 1 : 0);
                            itemdisc->SetRefundValuePct(rclentryp->RangeCondition()->RefundPct());
                            itemdisc->SetDiscountCategory(rclentryp->RangeCondition()->GetDiscountCategory());
                            itemdisc->Put();
                            item->ItemDiscountList()->Append(itemdisc);
                        }
                    }
                    else
                        if ((itemdisc = discl->GetEntry(item->PosNr())) != NULL)
                        {
                            if (rclentryp->RangeCondition()->IsAddonDiscountOk())
                            {
                                itemdisc->SetDiscountValuePct(itemdisc->DiscountValuePct() + rclentryp->RangeCondition()->DiscountValuePct());
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
                            itemdisc->SetInternalDiscountFlag(rclentryp->RangeCondition()->InternalDiscount() == '1' ? 1 : 0);
                            itemdisc->SetRefundValuePct(rclentryp->RangeCondition()->RefundPct());
                            itemdisc->SetDiscountCategory(rclentryp->RangeCondition()->GetDiscountCategory());
                            discl->Append(itemdisc);
                        }
                    item->InvoiceValue(discl);
                }
            }
        }
    }
    delete diskl;
    return ErrorState();
}

/*----------------------------------------------------------------------------*/
/* AssignRangeMultyCondManuMacturer:  Base input for this methode is the      */
/* RangeControl List. This list contains the summary + conditions informations*/
/* for all RangeMember positions gouped by discountgroupnumber                */
/* There exist just one entry per discountgroupnumber                         */
/* The next basic input is the RangeCollect List. This list contains detailed */
/* informations per RangeMember Position and discount group number            */
/* Depend on those two lists, every rangemember postion becomes the           */
/* discountvaluepercentage and also a quantity for free depend on the         */
/* RangeCondition located within the RangeControl List for every discount     */
/* group number.                                                               */
/* Please take care for a well constructed RangeControl List and a well       */
/* constructed RangeCollect List, otherwise you become unpredictable results  */
/*----------------------------------------------------------------------------*/
int
pxOrder::AssignRangeMultyCondManuMacturer
(
    pxRangeControl* rclentryp,
    pxItemDiscountList* discl
)
{
    pxRangeCollectListIter  cursor(*RangeCollectList());
    pxRangeCollect* rc = NULL;
    pxItemDiscount* itemdisc = NULL;
    bool cFoundCondition = false;
    bool AddOnOk = false;
    pxOrderItemListIter iterator(*ItemList_); // define an iterator

    if (rclentryp->RangeCondition() == NULL) // condition not reached
        return ErrorState();

    pxDiscountList* diskl = new pxDiscountList(Session());
    pxDiscountListIter itdiskl(*diskl);
    pxDiscount* diskentry = NULL;
    diskl->SelectRange(rclentryp->BranchNo(), rclentryp->DiscountGrpNo(), rclentryp->CustomerNo());


    // Loop throug the RangeCollect List
    cursor.Reset();
    while ((rc = (pxRangeCollect*) ++cursor) != NULL)
    {
        cFoundCondition = false;
        if (rc->DiscountGrpNo() == rclentryp->DiscountGrpNo()) // groupno equals
        {
            diskentry = 0;
            pxOrderItem* item = (pxOrderItem*)ItemList_->At(rc->PosNr() - 1); // get item
            if (item)
            {
                diskentry = diskl->FindManuFactureNo(rc->ManufacturerNo());
                if (diskentry)
                {
                    if (diskentry->DiscountQty() > 0)
                    {
                        item->OrderQuantityRange_RangeArticle(item->MengeBestellt(), diskentry->CalcDiscountQty(item->MengeBestellt()), item->MengeBestellt());
                        cFoundCondition = true;
                    }
                    if (diskentry->DiscountValuePct() > 0)
                    {
                        if (discl == NULL)
                        {
                            if (diskentry->IsAddonDiscountOk())
                            {
                                AddOnOk = item->AddOnDiscountPct(diskentry->DiscountValuePct());
                            }
                            if (!AddOnOk)
                            {
                                item->UndoItemDiscount();                          // undo discount
                                itemdisc = new pxItemDiscount(Session(), KdAuftragNr_, item->PosNr(),
                                    (short)BestBuy_ValuePctCash,
                                    rclentryp->RangeCondition()->PharmacyGroupId());
                                itemdisc->SetDiscountValuePct(diskentry->DiscountValuePct());
                                itemdisc->SetInternalDiscountFlag(rclentryp->RangeCondition()->InternalDiscount() == '1' ? 1 : 0);
                                itemdisc->SetRefundValuePct(rclentryp->RangeCondition()->RefundPct());
                                itemdisc->SetDiscountCategory(rclentryp->RangeCondition()->GetDiscountCategory());
                                itemdisc->Put();
                                item->ItemDiscountList()->Append(itemdisc);
                                cFoundCondition = true;
                            }
                        }
                        else
                            if ((itemdisc = discl->GetEntry(item->PosNr())) != NULL)
                            {
                                if (diskentry->IsAddonDiscountOk())
                                {
                                    itemdisc->SetDiscountValuePct(itemdisc->DiscountValuePct() + diskentry->DiscountValuePct());
                                }
                                else
                                {
                                    itemdisc->SetDiscountValuePct(diskentry->DiscountValuePct());
                                    cFoundCondition = true;
                                }
                            }
                            else
                            {
                                itemdisc = new pxItemDiscount(Session(), KdAuftragNr_, item->PosNr(),
                                    (short)BestBuy_ValuePctCash,
                                    rclentryp->RangeCondition()->PharmacyGroupId());
                                itemdisc->SetDiscountValuePct(diskentry->DiscountValuePct());
                                itemdisc->SetInternalDiscountFlag(rclentryp->RangeCondition()->InternalDiscount() == '1' ? 1 : 0);
                                itemdisc->SetRefundValuePct(rclentryp->RangeCondition()->RefundPct());
                                itemdisc->SetDiscountCategory(rclentryp->RangeCondition()->GetDiscountCategory());
                                discl->Append(itemdisc);
                                cFoundCondition = true;
                            }
                        item->InvoiceValue(discl);
                    }
                    if (cFoundCondition)
                    {
                        continue;
                    }
                }

                if (rclentryp->RangeCondition()->DiscountQty() > 0)
                {
                    item->OrderQuantityRange_RangeArticle(item->MengeBestellt(), rclentryp->RangeCondition()->CalcDiscountQty(item->MengeBestellt()), item->MengeBestellt());
                }
                if (rclentryp->RangeCondition()->DiscountValuePct() > 0)
                {
                    if (discl == NULL)
                    {
                        if (rclentryp->RangeCondition()->IsAddonDiscountOk())
                        {
                            AddOnOk = item->AddOnDiscountPct(rclentryp->RangeCondition()->DiscountValuePct());
                        }
                        if (!AddOnOk)
                        {
                            item->UndoItemDiscount();                          // undo discount
                            itemdisc = new pxItemDiscount(Session(), KdAuftragNr_, item->PosNr(),
                                (short)BestBuy_ValuePctCash,
                                rclentryp->RangeCondition()->PharmacyGroupId());
                            itemdisc->SetDiscountValuePct(rclentryp->RangeCondition()->DiscountValuePct());
                            itemdisc->SetInternalDiscountFlag(rclentryp->RangeCondition()->InternalDiscount() == '1' ? 1 : 0);
                            itemdisc->SetRefundValuePct(rclentryp->RangeCondition()->RefundPct());
                            itemdisc->SetDiscountCategory(rclentryp->RangeCondition()->GetDiscountCategory());
                            itemdisc->Put();
                            item->ItemDiscountList()->Append(itemdisc);
                        }
                    }
                    else
                        if ((itemdisc = discl->GetEntry(item->PosNr())) != NULL)
                        {
                            if (rclentryp->RangeCondition()->IsAddonDiscountOk())
                            {
                                itemdisc->SetDiscountValuePct(itemdisc->DiscountValuePct() + rclentryp->RangeCondition()->DiscountValuePct());
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
                            itemdisc->SetInternalDiscountFlag(rclentryp->RangeCondition()->InternalDiscount() == '1' ? 1 : 0);
                            itemdisc->SetRefundValuePct(rclentryp->RangeCondition()->RefundPct());
                            itemdisc->SetDiscountCategory(rclentryp->RangeCondition()->GetDiscountCategory());
                            discl->Append(itemdisc);
                        }
                    item->InvoiceValue(discl);
                }
            }
        }
    }
    delete diskl;
    return ErrorState();
}

/*----------------------------------------------------------------------------*/
/* AssignRangeBaseValue:  Base input for this methode is the                  */
/* RangeControl List. This list contains the summary + conditions informations*/
/* for all RangeMember positions gouped by discountgroupnumber                */
/* There exist just one entry per discountgroupnumber                         */
/* The next basic input is the RangeCollect List. This list contains detailed */
/* informations per RangeMember Position and discount group number            */
/* Depend on those two lists, every rangemember postion becomes the           */
/* discountconditions depend on the RangeCondition located within the         */
/* RangeControl List for every discount group number                          */
/* Please take care for a well constructed RangeControl List and a well       */
/* constructed RangeCollect List, otherwise you become unpredictable results  */
/*----------------------------------------------------------------------------*/
int
pxOrder::AssignRangeBaseValue
(
    pxRangeControl* rclentryp,
    pxItemDiscountList* discl
)
{
    pxRangeCollectListIter  cursor(*RangeCollectList());
    pxOrderItemListIter iterator(*ItemList_); // define an iterator

    if (rclentryp->RangeCondition() == NULL) // condition not reached
        return ErrorState();
    if (rclentryp->RangeCondition()->DiscountQty() > 0)
    {
        AssignRangeDiscountQty(rclentryp);
    }

    if (rclentryp->RangeCondition()->DiscountValuePct() > 0)
    {
        AssignRangeDiscountPct(rclentryp, discl);
    }

    if (rclentryp->RangeCondition()->GrossProfitPct() > 0)
    {
        AssignRangeGrossProfitPct(rclentryp);
    }

    if (rclentryp->RangeCondition()->FixedDiscountValue() > 0)
    {
        AssignRangeFixedDiscountVal(rclentryp);
    }

    return ErrorState();
}

/*----------------------------------------------------------------------------*/
/* AssignRangeGrossProfitPct:  Base input for this methode is the             */
/* RangeControl List. This list contains the summary + conditions informations*/
/* for all RangeMember positions gouped by discountgroupnumber                */
/* There exist just one entry per discountgroupnumber                         */
/* The next basic input is the RangeCollect List. This list contains detailed */
/* informations per RangeMember Position and discount group number            */
/* Depend on those two lists, every rangemember postion becomes the           */
/* GrossProfit percentage depend  on the RangeCondition located within        */
/* the RangeControl List for every discount group number                      */
/* Please take care for a well constructed RangeControl List and a well       */
/* constructed RangeCollect List, otherwise you become unpredictable results  */
/*----------------------------------------------------------------------------*/
int
pxOrder::AssignRangeGrossProfitPct
(
    pxRangeControl* rclentryp
)
{
    pxRangeCollectListIter  cursor(*RangeCollectList());
    pxRangeCollect* rc = NULL;
    pxItemDiscount* itemdisc = NULL;
    pxOrderItemListIter iterator(*ItemList_); // define an iterator
    double grossprofit = 0.0;

    if (rclentryp->RangeCondition() == NULL) // condition not reached
        return ErrorState();
    // Loop throug the RangeCollect List
    cursor.Reset();
    while ((rc = (pxRangeCollect*) ++cursor) != NULL)
    {
        if (rc->DiscountGrpNo() == rclentryp->DiscountGrpNo()) // groupno equals
        {
            pxOrderItem* item = (pxOrderItem*)ItemList_->At(rc->PosNr() - 1); // get item
            if (item)
            {
                grossprofit = item->CalcDiscountPercentage(rclentryp->RangeCondition()->GrossProfitPct(), (short)pxOrderItem::CascadeLevelRangePromotion, item->MengeBestellt());

                itemdisc = new pxItemDiscount(Session(), KdAuftragNr_, item->PosNr(),
                    (short)BestBuy_GrossProfitPct,
                    rclentryp->RangeCondition()->PharmacyGroupId());
                itemdisc->SetDiscountValuePct(grossprofit);
                itemdisc->SetInternalDiscountFlag(rclentryp->RangeCondition()->InternalDiscount() == '1' ? 1 : 0);
                itemdisc->SetRefundValuePct(rclentryp->RangeCondition()->RefundPct());
                itemdisc->SetDiscountCategory(rclentryp->RangeCondition()->GetDiscountCategory());
                itemdisc->Put();
                item->ItemDiscountList()->Append(itemdisc);
                item->InvoiceValue();
            }
        }
    }
    return ErrorState();
}

const libcsc::discount::OrderPositionDiscountListPtr pxOrder::getDiscountList()
{
    BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerOrder(), "pxOrder::getDiscountList()");

    libcsc::discount::IOrderPositionDiscountFinderPtr finder = Session()->getOrderPositionDiscountFinder();
    return finder->findByID(KdAuftragNr(), 0);
}
