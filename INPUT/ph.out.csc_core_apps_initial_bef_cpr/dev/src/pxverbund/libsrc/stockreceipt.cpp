#include "pxrecord.h"
#include "pxsess.hpp"
#include "pxdevice.hpp"
#include "pxartbas.hpp"
#include "pxgoodsdelivery.hpp"
#include "pxgoodsdeldefs.h"
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
#include "pxparameter.hpp"
#include "types/messagecodeenum.inc"
#include "pxarticlequotaptr.h"
#include "pxartbaseptr.h"

// Log added
#include <logger/loggerconfig.h>
#include <logger/loggerpool.h>

pxOrderList* gBORDERLIST = NULL;

/*----------------------------------------------------------------------------*/
/* DistributeIncomingGoods:                                                   */
/* This function works in the interface environment between Cisc(IBM) and     */
/* and Solaris. It is bounded to the stock control program (pvhx01) and is    */
/* called on function "WE" = stockreceipt.                                    */
/*----------------------------------------------------------------------------*/

int DistributeIncomingGoods(pxSession* session, short FilialNr, long ArtikelNr)
{
    pxParameter* partquota = NULL;
    bool bNew = false;

    partquota = new pxParameter(session, 0, (nString)cPAR_PHATRA_PROGRAMMNAME,
        (nString)cPAR_PHATRA_PARTNOTA, (nString)cPAR_PHATRA_PARAMNAME);
    BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), "Start of Distribute Incoming Goods");
    if (partquota->Get(cDBGET_READONLY))
    {
        bNew = false;
        delete partquota;
        partquota = NULL;
    }
    else
    {
        if (partquota->Wert() == 1) bNew = true;
    }
    if(bNew)
    {
        BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), "Distribute Incoming Goods_NEW"); 
        return DistributeIncomingGoods_New(session, FilialNr, ArtikelNr);
    }
    else
    {
        BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), "Distribute Incoming Goods_OLD");
        return DistributeIncomingGoods_Old(session, FilialNr, ArtikelNr);
    }
}

int DistributeIncomingGoods_New( pxSession* session, short FilialNr, long ArtikelNr )
{
    int retval = 0;
    nString bemerkungen;

    // Do nothing for Croatia . See Ticket SR-064132
    if( session->isCroatia()){ return retval; }

    const pxOrderEntryParamPtr para = session->getOrderEntryParam(FilialNr);
    if( para.get() == NULL ){ return retval; }

    /*----------------------------------------------------------------------------*/
    /*  First workup deliverpositions where kdauftragart not NO (OPL29)           */
    /*  After that, the NO positions are worked up                                */
    /*----------------------------------------------------------------------------*/
    WorkUpSpecialDeliveryPos(session, FilialNr, ArtikelNr);

    if (session->isFrance() || session->isFrancePrewhole()) {
        WorkUpSpecialCCDeliveryPos(session, FilialNr, ArtikelNr);
    }

    pxGoodsDeliveryList GDlist( session, ArtikelNr, FilialNr );
    if( !GDlist.Entries() ){ return retval; }

    pxGoodsDeliveryListIter GDiter( GDlist );

    pxGoodsDelivery*  GDentry = NULL;
    pxGoodsDeliveryListIter GDiterFl(GDlist);

    GDentry = (pxGoodsDelivery*)++GDiterFl;

    // Protection: do not create order for 'FLYER' entry
    // we exit if current article is a flyer
    bemerkungen = GDentry->DeliveryPos()->Bemerkungen();
    if (bemerkungen == "FLYER")
    {
        return retval;                      // exit
    }
    pxOrder* order = NULL;
    while ((GDentry = (pxGoodsDelivery*)++GDiter) != NULL)
    {
        if (!para->IsSCloseRestDeliveryAtOnce())
        {
            // Check if the corresponding order is already closed (SH, 05.06.2013)
            if (!GDentry->IsAvailableForOrderProcessing(session, GDentry->DeliveryPos()->KdAuftragNr()))
            {
                continue;
            }
        }
        if (para->IsSCloseRestDeliveryAtOnce())
        {
            if (!GDentry->DeliveryPos()->IsReadyForWorkUp())
            {
                continue;
            }
        }

        // Protection: do not touch Order Type UW within this loop
        nString KdAuftragArt = GDentry->DeliveryPos()->KdAuftragArt();
        KdAuftragArt.Strip();
        if (KdAuftragArt == "UW" || KdAuftragArt == "CC")
        {
            continue;
        }

        //read article and test for possible errors
        pxArtBasePtr artikel( pxArtBase::CreateArticle(session, ArtikelNr, FilialNr) );
        //pxArtBase* artikel = pxArtBase::CreateArticle(session, ArtikelNr, FilialNr);
        if (!artikel->IsGoodState())
        {
            break;
        }

        if (artikel->IsStopSelling() || artikel->IsNotSaleable())  // stock difference or not saleable
        {
            continue;
        }

        // read customer to generate order object
        pxCustBase customer(session, FilialNr, GDentry->IDFNr());
        if (!customer.IsGoodState())
        {
            continue;
        }

        // get quantity to post
        long subDeliveryQtyOpen = GDentry->DeliveryPos()->Menge() + GDentry->DeliveryPos()->MengeNatra();
        if (0 >= subDeliveryQtyOpen){ continue; }

        long stockLevelAvailable = session->getStockBooking()->GetAvailableQtyInStock(*artikel, customer);
        if (subDeliveryQtyOpen > stockLevelAvailable)
        {
            subDeliveryQtyOpen = stockLevelAvailable;
        }
        if (0 >= subDeliveryQtyOpen) { continue; }

        pxArticleQuotaPtr articleQuota;
        pxOrderType  orderType( session, session->OrderTypeList(FilialNr)->Find(KdAuftragArt, FilialNr) );
        // check ArticleQuota to prevent unpredictable results
        if ( !orderType.IsNoQuota() )
        {
            articleQuota = pxArticleQuotaPtr(new pxArticleQuota(session, FilialNr, GDentry->IDFNr(), ArtikelNr));
            if( !articleQuota->FindQuotaEntry() )
            {
                long quotaQtyOpen = articleQuota->Quota() - articleQuota->KumQty();
                if (0 >= quotaQtyOpen) { continue; }

                if (subDeliveryQtyOpen > quotaQtyOpen)
                {
                    subDeliveryQtyOpen = quotaQtyOpen;
                }
            }
            else
            {
                articleQuota.reset();
            }
        }

        session->nDBBeginTransaction(cDBTransSet);

        /*----------------------------------------------------------------------------*/
        /*     For Customer with NachLieferTyp_ == '6', we do reserv the ordered      */
        /*     quantity and swap type of the corresponding NachLieferPos Entry,       */
        /*     from 3 to 5                                                            */
        /*----------------------------------------------------------------------------*/
        if (GDentry->NachLieferTyp() == '6'  && KdAuftragArt == "NO")
        //if ( customer.IsReservOrderedQuantity() && KdAuftragArt == "NO")
        {
            artikel->Get(cDBGET_FORUPDATE);
            if ( !artikel->IsGoodState() )
            {
                session->nDBRollBack();
                break;
            }

            session->getStockBooking()->AddReservationForRestDelivery( *artikel, customer, subDeliveryQtyOpen);
            if ( 0 != articleQuota.get() )
            {
                articleQuota->Get(cDBGET_FORUPDATE);
                if (articleQuota->IsGoodState() )
                {
                    articleQuota->AddQuantity(subDeliveryQtyOpen);
                    articleQuota->Put();
                }
            }

//  Start New Ronnie
            //BB Mengenmäßig wird nichts an der Menge in der NL-Pos geändert!!!
//          GDentry->DeliveryPos()->Get(cDBGET_FORUPDATE);
            //RI Restmenge in neue NL-Pos schreiben
            int newqty = 0;
            if (subDeliveryQtyOpen < GDentry->DeliveryPos()->Menge())
            {
                newqty = GDentry->DeliveryPos()->Menge() - subDeliveryQtyOpen;
            }
            pxVerbund::subsequentDelivery::pxDeliveryPos nachlieferpos(session);
            nachlieferpos = *GDentry->DeliveryPos();
            nachlieferpos.SetDeliveryPosTyp(pxVerbund::subsequentDelivery::pxDPT_RESERVE_ITEM);
//          nachlieferpos.Get();
            nachlieferpos.Get(cDBGET_FORUPDATE);    // reservierte Nachlieferpos vorhanden
//          if (0   == nachlieferpos.Get(cDBGET_FORUPDATE)) // reservierte Nachlieferpos vorhanden
            if (nachlieferpos.IsGoodState())    // reservierte Nachlieferpos vorhanden
            {
                int reservemenge = nachlieferpos.Menge() + subDeliveryQtyOpen;
                nachlieferpos.SetMenge(reservemenge);
            }
            else
            {
                nachlieferpos.SetMenge(subDeliveryQtyOpen);
            }
            nachlieferpos.Put();
            GDentry->DeliveryPos()->Get(cDBGET_FORUPDATE);
            if (newqty > 0) // Restmenge zurückschreiben
            {
                GDentry->DeliveryPos()->SetMenge(newqty);
                GDentry->DeliveryPos()->Put();
            }
            else    //NL loeschen
            {
                GDentry->DeliveryPos()->Delete();
            }
            //RI Restmenge in NL-Pos zurückschreiben Ende

            if (GDentry->DeliveryPos()->IsGoodState())
            {
                artikel->Put();
                session->nDBCommit(cDBTransSet);        // commit changes
            }
//  Ende    New Ronnie

/* Start Old Ronnie
//BB Mengenmäßig wird nichts an der Menge in der NL-Pos geändert!!!
            GDentry->DeliveryPos()->Get(cDBGET_FORUPDATE);
            //RI Restmenge in neue NL-Pos schreiben
            int newqty = 0;
            pxVerbund::subsequentDelivery::pxDeliveryPos nachlieferpos(session);
            if (subDeliveryQtyOpen < GDentry->DeliveryPos()->Menge())
            {
                newqty = GDentry->DeliveryPos()->Menge() - subDeliveryQtyOpen;
                nachlieferpos = *GDentry->DeliveryPos();
                nachlieferpos.SetMenge(newqty);
            }
            //RI Restmenge in neue NL-Pos schreiben Ende
            GDentry->DeliveryPos()->SetPosTyp( pxVerbund::subsequentDelivery::pxDeliveryPos :: pxDPT_RESERVE_ITEM);

            if ( GDentry->DeliveryPos()->IsGoodState()  )
            {
                GDentry->DeliveryPos()->SetMenge(subDeliveryQtyOpen);
                GDentry->DeliveryPos()->Put();
                artikel->Put();
                if (newqty > 0) nachlieferpos.Put();    //RI
                session->nDBCommit(cDBTransSet);        // commit changes
            }
     Ende Old Ronnie    */
            else
            {
                session->nDBRollBack();                  // rollback changes and
            }
        }
        else
        {
            pxOrderItem* item = NULL;
            // If Nachliefertyp = 7 then generate back orders
            if ( customer.IsParkRestDeliveryOrder() && GDentry->DeliveryPos()->BatchAuftragNr() > 0)    // NachLieferTyp = '7'
            {
                //RI Restmenge in die NL-Pos schreiben
                int newqty = 0;
                if (subDeliveryQtyOpen < GDentry->DeliveryPos()->Menge())
                {
                    newqty = GDentry->DeliveryPos()->Menge() - subDeliveryQtyOpen;
                    GDentry->DeliveryPos()->SetMenge(subDeliveryQtyOpen);
                }
                //RI Restmenge in neue NL-Pos schreiben Ende
                customer.ParkDeliveryOrder(GDentry, &order, &item);
                if (customer.IsGoodState())
                {
                    // write restdelivery protocol
                    pxDeliveryLog  dlog(*item, *GDentry->DeliveryPos());
                    session->nDBBeginTransaction(cDBTransSet);
                    dlog.Put();
                    if ( dlog.IsGoodState() )
                    {
                        if (newqty == 0)
                        {
                            GDentry->DeliveryPos()->Delete();              // delete NachLieferPos entry
                        }
                        else
                        {
                            GDentry->DeliveryPos()->SetMenge(newqty);
                            GDentry->DeliveryPos()->ForceUpdate();
                            GDentry->DeliveryPos()->Put();

                        }
                        if (GDentry->DeliveryPos()->IsGoodState())   // if ok
                        {
                            delete GDiter.Remove();                    // delete object from list and
                            session->nDBCommit(cDBTransSet);           // commit changes
                        }
                        else
                        {
                            session->nDBRollBack();                    // rollback changes and
                        }
                    }
                }
                continue;
            }

            // Protection: Order Type NO only for Nachliefertype 4
            if ( KdAuftragArt == "NO" &&  GDentry->NachLieferTyp() != '4' ){ continue;}

            char KoArt = GDentry->DeliveryPos()->KoArt();
            char BuchArt = GDentry->DeliveryPos()->BuchArt();
            if (KoArt == ' ' && BuchArt == ' ')
            {
                KoArt = '0';
                BuchArt = '0';
            }

            if (order)
            {
                if (order->IDFNr() != GDentry->IDFNr())
                {
                    order->Close(Order::EntryClosed);      // close current order
                    delete order;
                    order = NULL;
                }
            }

            if (NULL == order)
            {
                order = new pxOrder(session, customer);
                if (!order->IsGoodState())
                {
                    delete order;
                    order = NULL;
                    continue;
                }

                pxOrderValidTrans* vtp = session->OrderValidTransList(FilialNr)->Find(customer, KdAuftragArt);
                if (!vtp)                        // this is an invalid order type
                {
                    KdAuftragArt.Clear();                   // will find the default order transaction
                    vtp = session->OrderValidTransList(FilialNr)->Find(customer, KdAuftragArt);
                }

                if (vtp)
                {
                    order->OrderType(vtp->KdAuftragArt(), KoArt, BuchArt);
                }
                nMessage text(session->CMsgStream(), CMSG_ITM_RESTDELIVERY);
                nString bem = text.String();
                bem.Compress('\n');
                order->Bemerkungen(bem);
            }

            // insert orderitem objects
            //RI Restmenge in die NL-Pos schreiben
            int newqty = 0;
            if (subDeliveryQtyOpen < GDentry->DeliveryPos()->Menge())
            {
                newqty = GDentry->DeliveryPos()->Menge() - subDeliveryQtyOpen;
                GDentry->DeliveryPos()->SetMenge(subDeliveryQtyOpen);
            }
            //RI Restmenge in neue NL-Pos schreiben Ende
            item = order->NewOrderItem_16(GDentry->DeliveryPos());
            if (item != NULL)
            {
                // SR-15007827: DistributeIncomingGoods: Item-Bemerkung nicht überschreiben wenn diese schon Text enthält! Barrabatte müssen erhalten bleiben! ('BR....')
                if( item->Bemerkungen().IsEmpty() )
                {
                    nMessage text(session->CMsgStream(), CMSG_ITM_RESTDELIVERY);
                    nString bem = text.String();
                    bem.Compress('\n');
                    item->Bemerkungen(bem);
                }

                // write restdelivery protocol
                pxDeliveryLog  dlog(*item, *GDentry->DeliveryPos());
                session->nDBBeginTransaction(cDBTransSet);
                dlog.Put();
                if ( dlog.IsGoodState() )
                {
                    if ( para->IsSCloseRestDeliveryAtOnce() )
                    {
                        if (newqty == 0)
                        {
                            GDentry->DeliveryPos()->SetStatus(pxVerbund::subsequentDelivery::DP_WORKUP_DONE);
                            GDentry->DeliveryPos()->ForceUpdate();
                            GDentry->DeliveryPos()->Put();
                        }
                        else
                        {
                            GDentry->DeliveryPos()->SetMenge(newqty);
//                          GDentry->DeliveryPos()->Update(GDentry->DeliveryPos());              // update NachLieferPos entry with new qty
                            GDentry->DeliveryPos()->ForceUpdate();
                            GDentry->DeliveryPos()->Put();
                        }
                    }
                    else
                    {
                        if (newqty == 0)
                        {
                            GDentry->DeliveryPos()->Delete();              // delete NachLieferPos entry
                        }
                        else
                        {
                            GDentry->DeliveryPos()->SetMenge(newqty);
//                          GDentry->DeliveryPos()->Update(GDentry->DeliveryPos());              // update NachLieferPos entry with new qty
                            GDentry->DeliveryPos()->ForceUpdate();
                            GDentry->DeliveryPos()->Put();
                        }
                    }

                    if ( GDentry->DeliveryPos()->IsGoodState() )   // if ok
                    {
                        delete GDiter.Remove();                    // delete object from list and
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

    } // end while

    if (order)
    {
        if (order->KdAuftragArt() != "CC") {
        order->Close(Order::EntryClosed);
        if (gBORDERLIST != NULL)
        {
            gBORDERLIST->Clear();
        }

        }
        
        delete order;
    }

    return retval;
}

int DistributeIncomingGoods_Old(pxSession* session, short FilialNr, long ArtikelNr)
{
    int    retval = 0;
    long   QToPost = 0;
    pxGoodsDelivery*  GDentry = NULL;
    pxArticleQuota*   ArtQuota = NULL;
    pxOrder*          order = NULL;
    pxOrderItem*      item = NULL;
    pxOrderValidTrans *vtp = NULL;

    nDate today;
    nString         KdAuftragArt;
    nString         bemerkungen;
    char   KoArt = ' ';                  // commi
    char   BuchArt = ' ';                  // book

                                           // Do nothing for Croatia . See Ticket SR-064132

    if (session->isCroatia())
    {
        return retval;
    }
    const pxOrderEntryParamPtr para = session->getOrderEntryParam(FilialNr);
    if (para.get() == NULL)
        return retval;

    /*----------------------------------------------------------------------------*/
    /*  First workup deliverpositions where kdauftragart not NO (OPL29)           */
    /*  After that, the NO positions are worked up                                */
    /*----------------------------------------------------------------------------*/
    WorkUpSpecialDeliveryPos(session, FilialNr, ArtikelNr);

    if (session->isFrance() || session->isFrancePrewhole()) {
        WorkUpSpecialCCDeliveryPos(session, FilialNr, ArtikelNr);
    }

    // builds a list of deliverable goods (NacnhLieferPos)
    pxGoodsDeliveryList* GDlist = new pxGoodsDeliveryList(session, ArtikelNr, FilialNr);
    if (!GDlist->Entries())               // no entries found
    {
        delete GDlist;                      // delete the list and
        return retval;                      // exit
    }
    pxGoodsDeliveryListIter GDiterFl(*GDlist);

     GDentry = (pxGoodsDelivery*)++GDiterFl;

    // Protection: do not create order for 'FLYER' entry
    // we exit if current article is a flyer
    bemerkungen = GDentry->DeliveryPos()->Bemerkungen();
    if (bemerkungen == "FLYER")
    {
        return retval;                      // exit
    }

    pxGoodsDeliveryListIter GDiter(*GDlist);

    // Main workup loop
    while ((GDentry = (pxGoodsDelivery *) ++GDiter) != NULL)
    {
        if (!para->IsSCloseRestDeliveryAtOnce())
        {
            // Check if the corresponding order is already closed (SH, 05.06.2013)
            if (!GDentry->IsAvailableForOrderProcessing(session, GDentry->DeliveryPos()->KdAuftragNr()))
            {
                continue;
            }
        }
        
        if (para->IsSCloseRestDeliveryAtOnce())
        {
            if (!GDentry->DeliveryPos()->IsReadyForWorkUp())
            {
                continue;
            }
        }
        KdAuftragArt = GDentry->DeliveryPos()->KdAuftragArt();
        KdAuftragArt.Strip();
        KoArt = GDentry->DeliveryPos()->KoArt();
        BuchArt = GDentry->DeliveryPos()->BuchArt();
        if (KoArt == ' ' && BuchArt == ' ')
        {
            KoArt = '0';      // preset
            BuchArt = '0';      // preset
        }

        // Protection: do not touch Order Tyoe UW within this loop
        if (KdAuftragArt == "UW" || KdAuftragArt == "CC")
        {
            continue;
        }

        //read article and test for possible errors
        pxArtBase* artikel = pxArtBase::CreateArticle(session, ArtikelNr, FilialNr);
        if (!artikel->IsGoodState())               // article in error
            break;                                 // exit this loop and exit function

        if (artikel->IsStopSelling() || artikel->IsNotSaleable())  // stock difference or not saleable
        {
            continue;
        }

        // get quantity to post
        QToPost = GDentry->DeliveryPos()->Menge() + GDentry->DeliveryPos()->MengeNatra();

        // read customer to generate order object
        pxCustBase customer(session, FilialNr, GDentry->IDFNr());
        if (!customer.IsGoodState())
        {
            continue;
        }
        if (session->getStockBooking()->GetAvailableQtyInStock(*artikel, customer) < QToPost)
        {
            continue;
        }

        pxOrderType  otp(session, session->OrderTypeList(FilialNr)->Find(KdAuftragArt, FilialNr));
        // check ArticleQuota to prevent unpredictable results
        if (!otp.IsNoQuota())       // no quota check for this order type
        {
            ArtQuota = new pxArticleQuota(session, FilialNr, GDentry->IDFNr(), ArtikelNr);
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
                                                     /*----------------------------------------------------------------------------*/
                                                     /*     For Customer with NachLieferTyp_ == '6', we do reserv the ordered      */
                                                     /*     quantity and swap type of the corresponding NachLieferPos Entry,       */
                                                     /*     from 3 to 5                                                            */
                                                     /*----------------------------------------------------------------------------*/
        if (GDentry->NachLieferTyp() == '6'  && KdAuftragArt == "NO")
        {
            artikel->Get(cDBGET_FORUPDATE);
            if (!artikel->IsGoodState())
            {
                session->nDBRollBack();                 // rollback changes and
                break;
            }
            session->getStockBooking()->AddReservationForRestDelivery(*artikel, customer, QToPost);
            if (ArtQuota)
            {
                ArtQuota->Get(cDBGET_FORUPDATE);
                if (ArtQuota->IsGoodState())
                {
                    ArtQuota->AddQuantity(QToPost);
                    ArtQuota->Put();
                }
            }

            GDentry->DeliveryPos()->Get(cDBGET_FORUPDATE);
            GDentry->DeliveryPos()->SetDeliveryPosTyp(pxVerbund::subsequentDelivery::pxDPT_RESERVE_ITEM);
            /*if ( para->IsSCloseRestDeliveryAtOnce() )
            {
            GDentry->DeliveryPos()->SetStatus(pxVerbund::subsequentDelivery::pxDeliveryPos :: DP_WORKUP_DONE);
            }
            */
            if (GDentry->DeliveryPos()->IsGoodState())
            {
                GDentry->DeliveryPos()->Put();
                artikel->Put();
                session->nDBCommit(cDBTransSet);         // commit changes
            }
            else
            {
                session->nDBRollBack();                  // rollback changes and
            }
            if (ArtQuota)
            {
                delete ArtQuota;
                ArtQuota = NULL;
            }
        }
        else
        {
            // If Nachliefertyp = 7 then generate back orders
            if (customer.IsParkRestDeliveryOrder() && GDentry->DeliveryPos()->BatchAuftragNr() > 0)    // NachLieferTyp = '7'
            {
                customer.ParkDeliveryOrder(GDentry, &order, &item);
                if (customer.IsGoodState())
                {
                    // write restdelivery protocol
                    pxDeliveryLog  dlog(*item, *GDentry->DeliveryPos());
                    session->nDBBeginTransaction(cDBTransSet);
                    dlog.Put();
                    if (dlog.IsGoodState())
                    {
                        GDentry->DeliveryPos()->Delete();              // delete NachLieferPos entry
                        if (GDentry->DeliveryPos()->IsGoodState())   // if ok
                        {
                            delete GDiter.Remove();                    // delete object from list and
                            session->nDBCommit(cDBTransSet);           // commit changes
                        }
                        else
                        {
                            session->nDBRollBack();                    // rollback changes and
                        }
                    }
                }
                continue;
            }

            // Protection: Order Type NO only for Nachliefertype 4
            if (KdAuftragArt == "NO" &&  GDentry->NachLieferTyp() != '4')
            {
                continue;
            }

            vtp = session->OrderValidTransList(FilialNr)->Find(customer, KdAuftragArt);
            if (!vtp)                        // this is an invalid order type
            {
                KdAuftragArt.Clear();                   // will find the default order transaction
                vtp = session->OrderValidTransList(FilialNr)->Find(customer, KdAuftragArt);
            }
            // now handle order
            if (!order)                             // no order opened at this time
            {
                order = new pxOrder(session, customer);
                if (!order->IsGoodState())
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
            }
            else
            {
                // order there but maybe customerchange
                if (order->IDFNr() != GDentry->IDFNr())
                {
                    order->Close(Order::EntryClosed);      // close current order
                    delete order;

                    order = new pxOrder(session, customer);
                    if (!order->IsGoodState())
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
                }
            }

            // insert orderitem objects
            item = order->NewOrderItem_16(GDentry->DeliveryPos());   // make item
            if (item != NULL)
            {
                // SR-15007827: DistributeIncomingGoods: Item-Bemerkung nicht überschreiben wenn diese schon Text enthält! Barrabatte müssen erhalten bleiben! ('BR....')
                if (item->Bemerkungen().IsEmpty())
                {
                    nMessage text(session->CMsgStream(), CMSG_ITM_RESTDELIVERY);
                    nString bem = text.String();
                    bem.Compress('\n');
                    item->Bemerkungen(bem);
                }

                // write restdelivery protocol
                pxDeliveryLog  dlog(*item, *GDentry->DeliveryPos());
                session->nDBBeginTransaction(cDBTransSet);
                dlog.Put();
                if (dlog.IsGoodState())
                {
                    if (para->IsSCloseRestDeliveryAtOnce())
                    {
                        GDentry->DeliveryPos()->SetStatus(pxVerbund::subsequentDelivery::DP_WORKUP_DONE);
                        GDentry->DeliveryPos()->ForceUpdate();
                        GDentry->DeliveryPos()->Put();
                    }
                    else
                    {
                        GDentry->DeliveryPos()->Delete();              // delete NachLieferPos entry
                    }
                    if (GDentry->DeliveryPos()->IsGoodState())   // if ok
                    {
                        delete GDiter.Remove();                    // delete object from list and
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
    }

    if (order)                                            // if last order ?
    {
        if (order->KdAuftragArt() != "CC") {
        order->Close(Order::EntryClosed);                 // close it
        if (gBORDERLIST != NULL)
            gBORDERLIST->Clear();
        }
        delete order;
    }

    delete GDlist;
    return retval;
}
