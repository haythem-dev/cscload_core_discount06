#include "pxorder.hpp"
#include "pxsess.hpp"
#include "pxcstbas.hpp"
#include "pxartbas.hpp"
#include "pxcstot.hpp"
#include "pxstockbooking.hpp"
#include <logger/loggerpool.h>
#include "types/messagecodeenum.inc"
#include <map>

struct pxCollectStockInfo
{
    long       m_QtyInStock_;          // Quantity in Stock (available)
    long       m_QuotaAvailable_;      // Quota (avaliable)
    bool       m_IsQuotaActive_;
};

typedef std::map<long, pxCollectStockInfo> pxCollectStockInfoMap;



/*----------------------------------------------------------------------------*/
/* This methode builds a list of deliverable Restdelivery positions of the    */
/* current customer. The entries are checked(quantity on stock,               */
/* check article quota and so on). At the end, only deliverable entries       */
/* are within the list                                                        */
/*----------------------------------------------------------------------------*/
int  pxOrder :: checkRestDeliveryPosList(pxVerbund::subsequentDelivery::pxDeliveryPosList* dlist)
{
     BLOG_TRACE_METHOD( libcsc::LoggerPool::getLoggerOrder(), "pxOrder::checkRestDeliveryPosList()" );

     pxVerbund::subsequentDelivery::pxDeliveryPosListIter  cursor(*dlist);
     pxVerbund::subsequentDelivery::pxDeliveryPos*         dpos = NULL;
     pxCollectStockInfoMap                                 stockInfoMap;

     if ( dlist == NULL)        // just to be carefull
     {
         return ErrorState();
     }
/*----------------------------------------------------------------------------*/
/*  Look for RestDelivery Positions with reserved quantity.                   */
/*  Just for customers with NachLiferTyp = 4,5 and 6                          */
/*----------------------------------------------------------------------------*/
     if (Customer()->IsImmediateRestDeliveryUser() ||
         Customer()->IsAskRestDeliveryUser()       ||
         Customer()->IsReservOrderedQuantity())
     {
        dlist->SelectCustomersRestDeliveryAndReserveItems(IDFNr_, FilialNr());
     }
     else
     {
     // Look for RestDelivery Positions within the database. (type 3)
        dlist->SelectCustomersRestDelivery(IDFNr_, FilialNr());
     }
     if (! dlist->Entries() )
     {
        return ErrorState();
     }
     cursor.Reset();                  // top of list
     while ( ( dpos = (pxVerbund::subsequentDelivery::pxDeliveryPos *) ++cursor ) != NULL )
     {
        if ( dpos->IsWorkUpDone() )
        {
            delete cursor.Remove();
            continue;
        }

        nString tmp = dpos->KdAuftragArt();
        tmp.Strip();
        if ( !tmp.IsEmpty() && dpos->KdAuftragArt() != KdAuftragArt_ )
        {
            delete cursor.Remove();
            continue;
        }
        pxArtBase* artikel = pxArtBase::CreateArticle( Session(), dpos->ArtikelNr(), FilialNr());
        if (!artikel->IsGoodState())
        {
            this->Error() = artikel->Error();
            BLOG_ERROR(libcsc::LoggerPool::getLoggerOrder(), ErrorMsg());
            ClearError();
            delete cursor.Remove();
            delete artikel;
            continue;
        }
        long qtyAvailable = 0;
        long qtyReserved  = 0;
        if ( dpos->DeliveryPosTyp() == (short) pxVerbund::subsequentDelivery::pxDPT_RESTDELIVERY_ITEM )
        {
           qtyAvailable = Session()->getStockBooking()->GetAvailableQtyInStock(*artikel, *Customer());
        }
        else if (dpos->DeliveryPosTyp() == (short) pxVerbund::subsequentDelivery::pxDPT_RESERVE_ITEM )
        {
           qtyReserved = Session()->getStockBooking()->GetReservedQtyInStock(*artikel, *Customer(), ORDER_CONTEXT_RESTDELIVERY);
        }
        if ( IsGoodState() )
        {
            if ( qtyAvailable + qtyReserved  == 0 )
            {
                delete cursor.Remove();
                delete artikel;
                continue;
            }

            if ( artikel->IsStopSelling() )
            {
                ExternalCondition(CMsgStream(), CMSG_ITM_STOCK_DIFFERENCE, artikel->ArtikelNr());
                BLOG_ERROR(libcsc::LoggerPool::getLoggerOrder(), ErrorMsg());
                ClearError();
                delete cursor.Remove();
                delete artikel;
                continue;
            }

            if ( FilialNr() != dpos->VertriebszentrumNr() )
            {
                delete cursor.Remove();
                delete artikel;
                continue;
            }
            if (stockInfoMap.find(dpos->ArtikelNr()) == stockInfoMap.end())
            {
                pxCollectStockInfo stockinfo;
                stockinfo.m_QtyInStock_ = qtyAvailable + qtyReserved;
                stockinfo.m_IsQuotaActive_ = false;
                stockinfo.m_QuotaAvailable_ = 0;
                if (false == OrderType().IsNoQuota())
                {
                    short quotafil = FilialNr(); //SR-15043828
                    if (Customer()->OriginalFilialNr() > 0)
                    {
                        quotafil = Customer()->OriginalFilialNr();   //Quota des Kunden immer im Orginalhaus
                    }
                    pxArticleQuota ArtQuota(Session(), quotafil, IDFNr_, dpos->ArtikelNr());
                    if (!ArtQuota.FindQuotaEntry())
                    {
                        stockinfo.m_QuotaAvailable_ = ArtQuota.Quota() - ArtQuota.KumQty();
                        stockinfo.m_IsQuotaActive_ = true;
                    }
                }
                stockInfoMap.insert(std::pair<long, pxCollectStockInfo>(dpos->ArtikelNr(), stockinfo));
            }
        }
        delete artikel;
     }

     cursor.Reset();                  // top of list
     while ( ( dpos = (pxVerbund::subsequentDelivery::pxDeliveryPos *) ++cursor ) != NULL )
     {
         pxCollectStockInfoMap::iterator it = stockInfoMap.find(dpos->ArtikelNr());
         if ( it != stockInfoMap.end() )
         {
             pxCollectStockInfo& info = (*it).second;
             if ( info.m_QtyInStock_ < dpos->Menge() )
             {
                delete cursor.Remove();
                continue;
             }
             info.m_QtyInStock_ -= dpos->Menge();

             /*----------------------------------------------------------------------------*/
             /*        ArticleQuota: keine Prüfung bei Nachlieferpos Typ 5                 */
             /*        Für Typ 5 wurde die Prüfung in der pvhx01 beim Wareneingang         */
             /*        vollzogen.                                                          */
             /*----------------------------------------------------------------------------*/
             if (false == OrderType().IsNoQuota() && false == dpos->IsReserveItem())
             {
                 if (info.m_IsQuotaActive_)
                 {
                     if (info.m_QuotaAvailable_ < dpos->Menge())
                     {
                         delete cursor.Remove();
                         continue;
                     }
                     info.m_QuotaAvailable_ -= dpos->Menge();
                 }
             }
        }
    }
    return ErrorState();
}
