#include "pxrecord.h"
#include "pxsess.hpp"
#include "pxdevice.hpp"
#include "pxartbas.hpp"
#include "pxgoodsdelivery.hpp"
#include "pxcstbas.hpp"
#include "pxitem.hpp"
#include "pxorder.hpp"
#include "pxdellog.hpp"
#include "pxdelpos.hpp"
#include "pxcustinf.hpp"
#include "pxordtyp.hpp"
#include "pxarticlequota.hpp"
#include "pxstockbooking.hpp"
#include "pxordvtr.hpp"
#include "pxoeparm.hpp"
#include "types/messagecodeenum.inc"

// Log added
#include <stdio.h>
#include <logger/loggerconfig.h>
#include <logger/loggerpool.h>



/*----------------------------------------------------------------------------*/
/* WorkUpSpecialDeliveryPos:                                                  */
/* This function works in the interface environment between Cisc(IBM) and     */
/* and Solaris. It is bounded to the stock control program (pvhx01) and is    */
/* called on function "WE" = stockreceipt This function just respects         */
/* NachlieferPos entries for KdAuftraArt UW                                   */
/*----------------------------------------------------------------------------*/
int
WorkUpSpecialDeliveryPos
(
    pxSession*    session,
    short         FilialNr,
    long          ArtikelNr
)
{
    int    retval  = 0;
    long   QToPost = 0;
    pxGoodsDelivery*  GDentry    = NULL;
    pxArticleQuota*   ArtQuota   = NULL;
    pxOrder*          order      = NULL;
    pxOrderItem*      item       = NULL;
    pxOrderValidTrans *vtp       = NULL;
    nString         KdAuftragArt = "UW";
    char   KoArt   = ' ';                  // commi
    char   BuchArt = ' ';                  // book

    nDate today;
    const pxOrderEntryParamPtr para = session->getOrderEntryParam(FilialNr);
    if ( para.get() == NULL )
       return retval;

    // builds a list of deliverable goods (NachLieferPos)
    pxGoodsDeliveryList* GDlist = new pxGoodsDeliveryList(session, ArtikelNr, FilialNr, KdAuftragArt);
    if ( !GDlist->Entries() )               // no entries found
    {
        delete GDlist;                       // delete the list and
        return retval;                       // exit
    }
    pxGoodsDeliveryListIter GDiter(*GDlist);

    // Main workup loop
    while ( ( GDentry =  ( pxGoodsDelivery *) ++GDiter ) != NULL )
    {
        if ( !para->IsSCloseRestDeliveryAtOnce() )
        {
            // Check if the corresponding order is already closed (SH, 05.06.2013)
            if( !GDentry->IsAvailableForOrderProcessing( session, GDentry->DeliveryPos()->KdAuftragNr() ) )
            {
                continue;
            }
        }
        if ( para->IsSCloseRestDeliveryAtOnce() )
        {
            if ( !GDentry->DeliveryPos()->IsReadyForWorkUp() )
            {
                continue;
            }
        }

        KoArt   =   GDentry->DeliveryPos()->KoArt();
        BuchArt =   GDentry->DeliveryPos()->BuchArt();

        if ( KoArt == ' ' && BuchArt == ' ' )
        {
            KoArt   = '0';      // preset
            BuchArt = '0';      // preset
        }

        pxOrderType  otp(session, session->OrderTypeList(FilialNr)->Find(KdAuftragArt,FilialNr));
        //read article and test for eventual errors
        pxArtBase* artikel = pxArtBase::CreateArticle( session, ArtikelNr, FilialNr );
        if (!artikel->IsGoodState())               // article in error
            break;                                 // exit this loop and exit function

        if (artikel->IsStopSelling() || artikel->IsNotSaleable())  // stock difference or not saleable
        {
            continue;
        }

        // get quantity to post
        QToPost = GDentry->DeliveryPos()->Menge() + GDentry->DeliveryPos()->MengeNatra();

        // read customer to generate order object
        pxCustBase customer(session,FilialNr,GDentry->IDFNr());
        if ( !customer.IsGoodState())
        {
            continue;
        }
        if (session->getStockBooking()->GetAvailableQtyInStock(*artikel, customer) < QToPost)
        {
            continue;
        }

        // check ArticleQuota to prevent unpredictable results
        if ( !otp.IsNoQuota() )       // no quota check for this order type
        {
            ArtQuota = new pxArticleQuota(session, FilialNr, GDentry->IDFNr(), ArtikelNr);
            if ( ArtQuota->FindQuotaEntry() )
            {
                delete ArtQuota;
                ArtQuota = NULL;
            }
            else
            if ( (ArtQuota->Quota() - ArtQuota->KumQty()) < QToPost )
            {
                delete ArtQuota;                       // it does not fit
                ArtQuota = NULL;                       // delete and
                continue;                              // ignore this entry
            }
        }

        session->nDBBeginTransaction(cDBTransSet);   // open database transaction


        vtp = session->OrderValidTransList(FilialNr)->Find(customer, KdAuftragArt);
        if ( ! vtp )                        // this is an invalid order type
        {
            KdAuftragArt.Clear();                   // will find the default order transaction
            vtp = session->OrderValidTransList(FilialNr)->Find(customer, KdAuftragArt);
        }
        // now handle order
        if ( !order )                             // no order opened at this time
        {
            order = new pxOrder(session, customer);
            if (!order->IsGoodState() )
            {
                delete order;
                order = NULL;
                continue;
            }
            if (vtp)
            {
                order->OrderType(vtp->KdAuftragArt(), KoArt, BuchArt);
            }
            nMessage text(session->CMsgStream(), CMSG_ITM_RESTDELIVERY);
            nString bem = text.String();
            bem.Compress('\n');
            order->Bemerkungen(bem);
            order->RouteAssign();
        }
        else
        {
            // order there but maybe customerchange
            /* if ( order->IDFNr() != GDentry->IDFNr())
            {*/
                //order->SetProblemClearance();
                order->Close(Order::EntryDeferred);      // close current order
                delete order;

                order = new pxOrder(session, customer);
                if (!order->IsGoodState() )
                {
                    delete order;
                    order = NULL;
                    continue;
                }
                if (vtp)
                {
                    order->OrderType(vtp->KdAuftragArt(), KoArt, BuchArt);
                }
                nMessage text(session->CMsgStream(), CMSG_ITM_RESTDELIVERY);
                nString bem = text.String();
                bem.Compress('\n');
                order->Bemerkungen(bem);
                order->RouteAssign();
            /*}*/
        }
        // insert orderitem objects
        item = order->NewOrderItem_16(GDentry->DeliveryPos());   // make item
        if (item != NULL)
        {
            /*nString itemtxt = item->Bemerkungen();
            nMessage text(session->CMsgStream(), pxOrderItem::CMSG_ITM_RESTDELIVERY);
            nString bem = text.String();
            bem.Compress('\n');
            if ( itemtxt.IsEmpty() )
            {
                itemtxt+=bem;
            }
            else
            {
                itemtxt = itemtxt+" "+bem;
            }
            item->Bemerkungen(itemtxt);
            */
            // write restdelivery protocol
            pxDeliveryLog  dlog(*item, *GDentry->DeliveryPos());
            session->nDBBeginTransaction(cDBTransSet);
            dlog.Put();
            if ( dlog.IsGoodState() )
            {
                if ( para->IsSCloseRestDeliveryAtOnce() )
                {
                   GDentry->DeliveryPos()->SetStatus(pxVerbund::subsequentDelivery::DP_WORKUP_DONE);
                   GDentry->DeliveryPos()->ForceUpdate();
                   GDentry->DeliveryPos()->Put();
                }
                else
                {
                   GDentry->DeliveryPos()->Delete();              // delete NachLieferPos entry
                }
                if ( GDentry->DeliveryPos()->IsGoodState() )   // if ok
                {
                    delete GDiter.Remove();                     // delete object from list and
                    session->nDBCommit(cDBTransSet);            // commit changes
                }
                else
                {
                    session->nDBRollBack();                     // rollback changes and
                    break;
                }
            }
        }
    }

    if ( order )                                            // if last order ?
    {
        //order->SetProblemClearance();
        order->Close(Order::EntryDeferred);                  // close it
        delete order;
    }

    delete GDlist;
    return retval;
}


/*----------------------------------------------------------------------------*/
/* WorkUpSpecialCCDeliveryPos:                                                  */
/* This function works in the interface environment between Cisc(IBM) and     */
/* and Solaris. It is bounded to the stock control program (pvhx01) and is    */
/* called on function "WE" = stockreceipt This function just respects         */
/* NachlieferPos entries for KdAuftraArt CC                                   */
/*----------------------------------------------------------------------------*/
int
WorkUpSpecialCCDeliveryPos
(
    pxSession* session,
    short         FilialNr,
    long          ArtikelNr
)
{
    int    retval = 0;
    long   QToPost = 0;
    pxGoodsDelivery* GDentry = NULL;
    pxArticleQuota* ArtQuota = NULL;
    pxOrder* order = NULL;
    pxOrderItem* item = NULL;
    nString         KdAuftragArt = "CC"; //chronical Illness Order

    nDate today;
    const pxOrderEntryParamPtr para = session->getOrderEntryParam(FilialNr);
    if (para.get() == NULL)
        return retval;

    pxGoodsDeliveryList* GDlist = new pxGoodsDeliveryList(session, ArtikelNr, FilialNr, KdAuftragArt);
    if (!GDlist->Entries())               // no entries found
    {
        delete GDlist;                       // delete the list and
        return retval;                       // exit
    }
    pxGoodsDeliveryListIter GDiter(*GDlist);

    BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), "workup special delivery CC");

    // Main workup loop
    while ((GDentry = (pxGoodsDelivery*) ++GDiter) != NULL)
    {
        std::stringstream text;
        text << "Checking Order  : " << GDentry->DeliveryPos()->KdAuftragNr();
        BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), text.str());

        if (!para->IsSCloseRestDeliveryAtOnce())
        {
            // Check if the corresponding order is already closed
            if (GDentry->IsAvailableForOrderProcessing(session, GDentry->DeliveryPos()->KdAuftragNr()))
            {
                // If order is closed we shouldn't have an entry in nachliferpos /
                // An error must have occured before deleting the entry
                // For safety raisons a delete nachliferpos has been added here
                text << "Order is already processed : " << GDentry->DeliveryPos()->KdAuftragNr();
                BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), text.str());
                GDentry->DeliveryPos()->Delete();              // delete NachLieferPos entry
                if (GDentry->DeliveryPos()->IsGoodState())   // if ok
                {
                    delete GDiter.Remove();                     // delete object from list and
                    session->nDBCommit(cDBTransSet);            // commit changes
                }
                else
                {
                    session->nDBRollBack();                     // rollback changes and
                    break;
                }

                continue;
            }
        }
        std::stringstream ss;

        if (order)
        {
            ss.clear();
            ss << "Closing previous open order : Order Number =" << GDentry->DeliveryPos()->KdAuftragNr();
            order->Close(Order::EntryDeferred);      // close current order
            delete order;
        }
        //Try and get the original_order : order is differed => not closed
        //For every nachliferpos we should find its corresponding order
        // If not found then it must have been archived/closed for some raison no need to proceed
        order = new pxOrder(session, GDentry->DeliveryPos()->KdAuftragNr(), cDBGET_FORUPDATE);

        BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), "Get the original Order");
        
        ss << "ORDER: " << GDentry->DeliveryPos()->KdAuftragNr() << " EVENT: " << "Get original order";
        BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), ss.str());

        order->OpenOrder(cDBOPEN_INSERT);

        if (!order->IsGoodState()) {

            delete order;
            order = NULL;
            BLOG_ERROR(libcsc::LoggerPool::getLoggerSession(), "Get the original Order :: Not Good state ");
            BLOG_ERROR(libcsc::LoggerPool::getLoggerSession(), order->ErrorMsg());
            break;
        }

        pxOrderType  otp(session, session->OrderTypeList(FilialNr)->Find(KdAuftragArt, FilialNr));

        if (!otp.IsSStockreservation()) {
            delete order;
            order = NULL;
            BLOG_ERROR(libcsc::LoggerPool::getLoggerSession(), "No stock reservation ");
            break;
        }
        
        //read article and test for eventual errors
        pxArtBase* artikel = pxArtBase::CreateArticle(session, ArtikelNr, FilialNr);
        if (!artikel->IsGoodState())               // article in error
            break;                                 // exit this loop and exit function

        if (artikel->IsStopSelling() || artikel->IsNotSaleable())  // stock difference or not saleable
        {
            continue;
        }

        // get quantity to post
        QToPost = GDentry->DeliveryPos()->Menge() + GDentry->DeliveryPos()->MengeNatra();

        ss.clear();
        ss << "Quantity to post: " << QToPost;
        BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), ss.str());
        
        if (session->getStockBooking()->GetAvailableQtyInStock(*artikel, *order->Customer()) < QToPost)
        {
            continue;
        }

        // check ArticleQuota to prevent unpredictable results
        if (!otp.IsNoQuota())       // no quota check for this order type
        {
            ArtQuota = new pxArticleQuota(session, FilialNr, order->IDFNr(), ArtikelNr);
            if (ArtQuota->FindQuotaEntry())
            {
                delete ArtQuota;
                ArtQuota = NULL;
            }
            else
                if ((ArtQuota->Quota() - ArtQuota->KumQty()) < QToPost)
                {
                    delete ArtQuota;                       // it does not fit
                    ArtQuota = NULL;                       // delete and
                    continue;                              // ignore this entry
                }
        }

        session->nDBBeginTransaction(cDBTransSet);   // open database transaction

        ss.clear();
        ss << "details : artikel nr =" << GDentry->DeliveryPos()->ArtikelNr() << " kdAuftragNr = " << order->KdAuftragNr();
        BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), ss.str());

        item = order->ItemList()->GetItem(GDentry->DeliveryPos()->PosNr());

        ss.clear();
        ss << "details : artikel nr =" << item->ArtikelNr();

        ss.clear();
        ss << "item INFO= Menge" << GDentry->DeliveryPos()->Menge() << " MengeNatra = " << GDentry->DeliveryPos()->MengeNatra() << "QToPost" << QToPost << "item->MengeBestellt " << item->MengeBestellt();
        ss << "item MengeAbgebucht " << item->MengeAbgebucht();
        BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), ss.str());

        if ((item != NULL) && (item->ArtikelNr() == GDentry->DeliveryPos()->ArtikelNr()))
        {
            if (item->Open() == nSTATE_GOOD)
            {
                item->OrderQuantity(item->MengeBestellt(), GDentry->DeliveryPos()->MengeNatra(), -1);
            }
        }
        else {
            // insert orderitem objects
            item = order->NewOrderItem_03(GDentry->DeliveryPos()->ArtikelNr(),
                GDentry->DeliveryPos()->Menge(), GDentry->DeliveryPos()->MengeNatra(), -1, GDentry->DeliveryPos()->PreisTyp(),
                pxOrderItem::BookingTypeDefault,
                pxOrderItem::TypeProductStocked,
                bPOST_DEFAULT); // make item
        }   

        if (item != NULL)
        {
        
            BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), "item has been added");

            GDentry->DeliveryPos()->Delete();              // delete NachLieferPos entry
            if (GDentry->DeliveryPos()->IsGoodState())   // if ok
            {
                delete GDiter.Remove();                     // delete object from list and
                session->nDBCommit(cDBTransSet);            // commit changes
            }
            else
            {
                session->nDBRollBack();                     // rollback changes and
                break;
            }
        }


    }
    if (order)   //last order
    {
      
        std::stringstream ss;
        ss << "closing last order kdauftragNr  =" << order->KdAuftragNr();
        BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), ss.str());
        order->Close(Order::EntryDeferred);                  // close it
        delete order;
    }

    delete GDlist;
    return retval;
}

