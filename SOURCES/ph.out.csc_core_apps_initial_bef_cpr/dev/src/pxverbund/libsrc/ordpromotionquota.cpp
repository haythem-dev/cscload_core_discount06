#include "pxrecord.h"
#include "pxsess.hpp"
#include "pxdevice.hpp"
#include "pxartbas.hpp"
#include "pxcstbas.hpp"
#include "pxdonepromoquotas.hpp"
#include "pxitem.hpp"
#include "pxorder.hpp"
#include "pxpromotionquota.hpp"
#include "pxpromotionquotacst.hpp"
#include "pxorderpospromo.hpp"
#include <logger/loggerpool.h>

/*----------------------------------------------------------------------------*/
/*  CalcPromotionQuota:                                                       */
/*----------------------------------------------------------------------------*/
int
pxOrder :: CalcPromotionQuota
(
    pxOrderItem* item
)
{
    BLOG_TRACE_METHOD( libcsc::LoggerPool::getLoggerOrderItem(), "pxOrderItem::CalcPromotionQuota()" );

    short      promoUsage       = 0;

    pxPromotionQuota*        PromoQuotaBranch    = NULL;
    pxPromotionQuotaList*    pQuotaBranchList    = NULL;
    pxPromotionQuotaCst*     PromoQuotaCustomer  = NULL;
    pxOrderPosPromo*                   pospromo  = NULL;
    long  restPromoQuotaBranchQty   = 0;
    long  restPromoQuotaCustomerQty = 0;
    long  newItemQty                = 0;
    long PromoBaseQty               = 0;

    if (!Session()->isBulgaria())                // just for bulgarian application
    {
        return ErrorState();
    }

    if ( item == NULL )
        return ErrorState();
    if (!item->IsGoodState() )
        return ErrorState();

    if ( item->PromotionNo() == 0 )                  // No Promotion available
    {
        return ErrorState();
    }

    // look at OrderposPromoList
    if ( item->OrderPosPromoList()  )
    {
        if ( item->OrderPosPromoList()->Entries() == 0 )
        {
            return ErrorState();
        }
        pospromo = item->GetOrderPosPromo(item->PromotionNo());
        if (pospromo )
        {
            PromoBaseQty = pospromo->BaseQty();
        }
        else
        {
            return ErrorState();
        }
    }

    // Get Main Branch Promoquota
    pQuotaBranchList = new pxPromotionQuotaList(Session());
    pQuotaBranchList->Select(FilialNr(), item->PromotionNo(), item->ArtikelNr() );
    if ( pQuotaBranchList->Entries() == 0 )
    {
        delete PromoQuotaBranch;
        return ErrorState();
    }
    PromoQuotaBranch = pQuotaBranchList->Find( item->ArtikelNr() );
    if (PromoQuotaBranch == NULL )
    {
        PromoQuotaBranch = (pxPromotionQuota*)(pQuotaBranchList->At(0) );
    }
    if ( PromoQuotaBranch == NULL )        // just for  being save
        return ErrorState();

    // now check how the main parameter is configured
    promoUsage = PromoQuotaBranch->CheckPromoQuotaUsage();

    switch ( promoUsage )
    {
        case pxPromotionQuota::UseBranchEntry :
        {
            restPromoQuotaBranchQty =  PromoQuotaBranch->BranchQuotaQty() - PromoQuotaBranch->SoldQtyBranch();
            if (  restPromoQuotaBranchQty <= 0 )      // PromotionQuota exceeded, cancel Promotion
            {
                cleanPromotionQuota(item, pospromo->DiscountValuePct());
                break;
            }

            // Get Customer PromoQuota
            PromoQuotaCustomer = GetEntryPromotionQuotaCst( PromoQuotaBranch, item->MengeBestaetigt());
            if ( PromoQuotaCustomer == NULL )        // promotion min qty not full filled
            {
                item->UndoProductPromotion();          // no Product Promotion
                item->UndoOrderPosPromo();             // delete entries
                item->SetDiscountArticleNo(0L);
                return ErrorState();
            }

            if ( restPromoQuotaBranchQty >= item->MengeBestaetigt() )
            {
                addSoldQtyBranch(PromoQuotaBranch, item->MengeBestaetigt());
                break;
            }
            // now restPromoQuotaBranchQty < item->MengeBestaetigt()
            if (!tryGetLowerPromoCondition(item, PromoBaseQty, restPromoQuotaBranchQty, pospromo->DiscountValuePct()))
            {
                break;
            }
            newItemQty = updateItemQuantity(item,  restPromoQuotaBranchQty);
            addSoldQtyBranch(PromoQuotaBranch, (restPromoQuotaBranchQty / PromoBaseQty) * PromoBaseQty);

            bookAsNewOrderItem(item, newItemQty);
            break;
        }

        case pxPromotionQuota::UseCustomerEntry :
        {
            // Get Customer PromoQuota
            PromoQuotaCustomer = GetEntryPromotionQuotaCst( PromoQuotaBranch, item->MengeBestaetigt());
            if ( PromoQuotaCustomer == NULL )        // promotion min qty not full filled
            {
                cleanPromotionQuota(item, pospromo->DiscountValuePct());
                return ErrorState();
            }

            PromoQuotaCustomer->ForceUpdate();       // Set Active

            restPromoQuotaCustomerQty = PromoQuotaCustomer->CustomerQuotaQty() - PromoQuotaCustomer->SoldQtyCst();
            if (  restPromoQuotaCustomerQty <= 0 )    // PromotionQuota exceeded, cancel Promotion
            {
                cleanPromotionQuota(item, pospromo->DiscountValuePct());

                addToDonePromoQuotas(PromoQuotaCustomer);
                break;
            }
            if ( restPromoQuotaCustomerQty >= item->MengeBestaetigt() )
            {
                addSoldQtyCst(PromoQuotaCustomer, item->MengeBestaetigt());

                addToDonePromoQuotasOnPromotionQuotaReached(PromoQuotaCustomer);
                break;
            }
            // now restPromoQuotaCustomerQty < item->MengeBestaetigt()
            if (!tryGetLowerPromoCondition(item, PromoBaseQty, restPromoQuotaCustomerQty, pospromo->DiscountValuePct()))
            {
                break;
            }
            newItemQty = updateItemQuantity(item, restPromoQuotaCustomerQty);
			addSoldQtyCst(PromoQuotaCustomer, restPromoQuotaCustomerQty);
            //addSoldQtyCst(PromoQuotaCustomer, (restPromoQuotaCustomerQty / PromoBaseQty) * PromoBaseQty);
            addToDonePromoQuotasOnPromotionQuotaReached(PromoQuotaCustomer);

            bookAsNewOrderItem(item, newItemQty);
            break;
        }
        case pxPromotionQuota::UseBothEntries :
        {
            restPromoQuotaBranchQty =  PromoQuotaBranch->BranchQuotaQty() - PromoQuotaBranch->SoldQtyBranch();
            // Get Customer PromoQuota
            PromoQuotaCustomer = GetEntryPromotionQuotaCst( PromoQuotaBranch, item->MengeBestaetigt());
            if ( PromoQuotaCustomer == NULL )        // promotion min qty not full filled
            {
                cleanPromotionQuota(item, pospromo->DiscountValuePct());
                return ErrorState();
            }

            PromoQuotaCustomer->ForceUpdate();       // Set Active

            restPromoQuotaCustomerQty = PromoQuotaCustomer->CustomerQuotaQty() - PromoQuotaCustomer->SoldQtyCst();

            // check first Customer
            if (  restPromoQuotaCustomerQty <= 0 )    // PromotionQuota exceeded, cancel Promotion
            {
                cleanPromotionQuota(item, pospromo->DiscountValuePct());
                break;
            }

            if ( restPromoQuotaCustomerQty >= item->MengeBestaetigt() )
            {
                if (  restPromoQuotaBranchQty <= 0 )      // PromotionQuota exceeded, cancel Promotion Sorry Customer
                {                                         // other customer were faster
                    cleanPromotionQuota(item, pospromo->DiscountValuePct());
                    break;
                }

                if ( restPromoQuotaBranchQty >= item->MengeBestaetigt() )
                {
                    addSoldQtyBranch(PromoQuotaBranch, item->MengeBestaetigt());
                    addSoldQtyCst(PromoQuotaCustomer, item->MengeBestaetigt());
                    break;
                }
            }
            // now restPromoQuotaCustomerQty <= restPromoQuotaBranchQty
            if (  restPromoQuotaCustomerQty <=  restPromoQuotaBranchQty )
            {
                if (!tryGetLowerPromoCondition(item, PromoBaseQty, restPromoQuotaCustomerQty, pospromo->DiscountValuePct()))
                {
                    break;
                }
                newItemQty = updateItemQuantity(item, restPromoQuotaCustomerQty);

                long qtyCustomer = (restPromoQuotaCustomerQty / PromoBaseQty) * PromoBaseQty;
                addSoldQtyCst(PromoQuotaCustomer, qtyCustomer);
                addSoldQtyBranch(PromoQuotaBranch, qtyCustomer);
                bookAsNewOrderItem(item, newItemQty);
                break;
            }

            // now restPromoQuotaCustomerQty > restPromoQuotaBranchQty
            if (!tryGetLowerPromoCondition(item, PromoBaseQty, restPromoQuotaBranchQty, pospromo->DiscountValuePct()))
            {
                break;
            }
            newItemQty = updateItemQuantity(item, restPromoQuotaBranchQty);

            long qtyBranch = (restPromoQuotaBranchQty / PromoBaseQty) * PromoBaseQty;
            addSoldQtyCst(PromoQuotaCustomer, qtyBranch);
            addSoldQtyBranch(PromoQuotaBranch, qtyBranch);
            bookAsNewOrderItem(item, newItemQty);
            break;
        }
        default :
        {
            break;
        }
    }
    if ( pQuotaBranchList )
        delete pQuotaBranchList;
    if ( PromoQuotaCustomer )
        delete PromoQuotaCustomer;

    return ErrorState();
}

bool pxOrder::tryGetLowerPromoCondition(pxOrderItem* item, long& promoBaseQty, long const restPromoQuotaCustomerQty, double const discountValuePct)
{
    if (promoBaseQty > restPromoQuotaCustomerQty)
    {
        promoBaseQty = item->GetLowerPromoCondition(restPromoQuotaCustomerQty, promoBaseQty);
        if (promoBaseQty == 0)
        {
            cleanPromotionQuota(item, discountValuePct);
            return false;
        }
    }
    return true;
}

long pxOrder::updateItemQuantity(pxOrderItem* item, long const restPromoQuotaQty)
{
	long restQty = item->MengeBestaetigt() - restPromoQuotaQty;
    //long restQty = (restPromoQuotaQty / promoBaseQty) * promoBaseQty;
    //long newItemQty = item->MengeBestaetigt() - restQty;
    //item->OrderQuantityRange_RangeArticle(restQty, 0L, restQty);
	item->OrderQuantityRange_RangeArticle(restPromoQuotaQty, 0L, restPromoQuotaQty);
    return restQty;
}

void pxOrder::addToDonePromoQuotasOnPromotionQuotaReached(pxPromotionQuotaCst* promoQuotaCustomer)
{
    if (promoQuotaCustomer->CustomerQuotaQty() == promoQuotaCustomer->SoldQtyCst())
    {
        addToDonePromoQuotas(promoQuotaCustomer);
    }
}

void pxOrder::addToDonePromoQuotas(pxPromotionQuotaCst* const promoQuotaCustomer)
{
    if (   Customer()->DonePromoQuotaList()
        && !Customer()->DonePromoQuotaList()->Find(promoQuotaCustomer->PromotionNo(), promoQuotaCustomer->ArticleNo()) )
    {
        pxDonePromoQuotas* donePromo = new pxDonePromoQuotas(promoQuotaCustomer->PromotionNo(), promoQuotaCustomer->ArticleNo());
        Customer()->DonePromoQuotaList()->Append(donePromo);
    }
}

void pxOrder::addSoldQtyCst(pxPromotionQuotaCst* const promoQuotaCustomer, long const q)
{
    promoQuotaCustomer->AddSoldQtyCst(q);
    nDBBeginTransaction(cDBTransRecord);
    promoQuotaCustomer->Put();
    if (promoQuotaCustomer->IsGoodState())
    {
        nDBCommit(cDBTransRecord);
    }
}

void pxOrder::addSoldQtyBranch(pxPromotionQuota* const PromoQuotaBranch, long const q)
{
    PromoQuotaBranch->AddSoldQtyBranch(q);
    nDBBeginTransaction(cDBTransRecord);
    PromoQuotaBranch->Put();
    if (PromoQuotaBranch->IsGoodState())
    {
        nDBCommit(cDBTransRecord);
    }
}

void pxOrder::bookAsNewOrderItem(pxOrderItem* item, long const newItemQty)
{
    if (item->IsGoodState() && (newItemQty > 0))
    {
        pxOrderItem* newitem = NewOrderItem_03_RangeArticle(
            item->ArtikelNr(), newItemQty, 0L, newItemQty, item->PreisTyp());
        if (newitem->IsGoodState())
        {
            newitem->SetArticleCodeValues(item->CodeType(), item->ArticleCode());
            newitem->SetXMLLinereference(item->XMLLinereference());
        }
    }
}

void pxOrder::cleanPromotionQuota(pxOrderItem* item, double const discountValuePct)
{
    item->UndoProductPromotion();          // no Product Promotion
    item->UndoOrderPosPromo();             // delete entries
    item->AddOnDiscountPct(0.0, discountValuePct);
    item->SetDiscountArticleNo(0L);
}

/*----------------------------------------------------------------------------*/
/*  GetEntryPromotionQuotaCst                                                 */
/*----------------------------------------------------------------------------*/
pxPromotionQuotaCst*
pxOrder :: GetEntryPromotionQuotaCst
(
    pxPromotionQuota* PromoQuotaBranch,
    long    Qty
)
{
    pxPromotionQuotaCst* PromoQuotaCustomer = NULL;
    pxPromotionQuotaCst* NewPromoQuotaCustomer = NULL;
    pxPromotionQuotaCstList* pQuotaCustomerList  = NULL;
    bool wARTICLENO                 = false;

    if ( PromoQuotaBranch == NULL )
        return  PromoQuotaCustomer;         // just for save

    if ( PromoQuotaBranch->ArticleNo() > 0 )  // its for entry with articleno
    {
        wARTICLENO = true;
    }

    // Get Customer PromoQuota
    pQuotaCustomerList = new pxPromotionQuotaCstList(Session());
    pQuotaCustomerList->Select(FilialNr(), PromoQuotaBranch->PromotionNo(), IDFNr_ ,PromoQuotaBranch->ArticleNo() );
    if ( pQuotaCustomerList->Entries() == 0 )
    {
        if ( PromoQuotaBranch->CustomerMinQty() != 0 )              // the first time, the customer must order at least Qty
        {
            if ( Qty < PromoQuotaBranch->CustomerMinQty() )
            {
                delete pQuotaCustomerList;
                return  PromoQuotaCustomer;         // just for save
            }
        }

        PromoQuotaCustomer = new pxPromotionQuotaCst(Session(), FilialNr(), PromoQuotaBranch->PromotionNo(), IDFNr_);
        if (wARTICLENO)
        {
            PromoQuotaCustomer->SetArticleNo(PromoQuotaBranch->ArticleNo());
        }
        else
        {
            PromoQuotaCustomer->SetArticleNo(0L);
        }
        PromoQuotaCustomer->SetCustomerQuotaQty(PromoQuotaBranch->CustomerQuotaQty());
        PromoQuotaCustomer->SetSoldQtyCst(0L);
        PromoQuotaCustomer->Put();          // insert into Database
        delete pQuotaCustomerList;
        return  PromoQuotaCustomer;         // just for save
    }

    if ( wARTICLENO )
    {
        PromoQuotaCustomer = pQuotaCustomerList->Find( PromoQuotaBranch->ArticleNo() );
        if ( PromoQuotaCustomer == NULL )
        {
            if ( PromoQuotaBranch->CustomerMinQty() != 0 )              // the first time, the customer must order at least Qty
            {
                if ( Qty < PromoQuotaBranch->CustomerMinQty() )
                {
                    delete pQuotaCustomerList;
                    return  PromoQuotaCustomer;         // just for save
                }
            }

            PromoQuotaCustomer = new pxPromotionQuotaCst(Session(), FilialNr(), PromoQuotaBranch->PromotionNo(), IDFNr_);
            PromoQuotaCustomer->SetArticleNo(PromoQuotaBranch->ArticleNo());
            PromoQuotaCustomer->SetCustomerQuotaQty(PromoQuotaBranch->CustomerQuotaQty());
            PromoQuotaCustomer->SetSoldQtyCst((long ) 0);
            PromoQuotaCustomer->Put();         // insert into Database
            delete pQuotaCustomerList;
            return PromoQuotaCustomer;
        }
        if ( PromoQuotaCustomer->SoldQtyCst() == 0 )
        {
            if ( PromoQuotaBranch->CustomerMinQty() != 0 )              // the first time, the customer must order at least Qty
            {
                if ( Qty < PromoQuotaBranch->CustomerMinQty() )
                {
                    delete pQuotaCustomerList;
                    PromoQuotaCustomer = NULL;
                    return  PromoQuotaCustomer;         // just for save
                }
            }
        }
        NewPromoQuotaCustomer = new pxPromotionQuotaCst(*PromoQuotaCustomer);
        delete pQuotaCustomerList;
        return NewPromoQuotaCustomer;
    }

    PromoQuotaCustomer =  (pxPromotionQuotaCst*)(pQuotaCustomerList->At(0));
    if ( PromoQuotaCustomer->ArticleNo() > 0 )
    {
        if ( PromoQuotaBranch->CustomerMinQty() != 0 )              // the first time, the customer must order at least Qty
        {
            if ( Qty < PromoQuotaBranch->CustomerMinQty() )
            {
                delete pQuotaCustomerList;
                return  PromoQuotaCustomer;         // just for save
            }
        }

        PromoQuotaCustomer = new pxPromotionQuotaCst(Session(), FilialNr(), PromoQuotaBranch->PromotionNo(), IDFNr_);
        PromoQuotaCustomer->SetArticleNo(0L );
        PromoQuotaCustomer->SetCustomerQuotaQty(PromoQuotaBranch->CustomerQuotaQty());
        PromoQuotaCustomer->SetSoldQtyCst(0L);
        PromoQuotaCustomer->Put();                     // insert into Database
        delete pQuotaCustomerList;
        return PromoQuotaCustomer;
    }
    NewPromoQuotaCustomer = new pxPromotionQuotaCst(*PromoQuotaCustomer);
    delete pQuotaCustomerList;
    return NewPromoQuotaCustomer;
}
