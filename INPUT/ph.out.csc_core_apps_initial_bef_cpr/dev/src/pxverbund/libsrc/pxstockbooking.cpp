#include "pxstockbooking.hpp"
#include "pxsess.hpp"
#include "articleaccountinfo.hpp"
#include "pxoeparm.hpp"
#include "pxartbas.hpp"
#include "iarticlestockbooking.hpp"
#include "pxcstbas.hpp"
#include "pxcustpharmgroup.hpp"
#include "pxorder.hpp"
#include "pxbranch.hpp"
#include "pxartrem.hpp"
#include "pxartacc.hpp"
#include "pxcuststockreserved.hpp"
#include "pxartreservation.hpp"
#include "pxcstot.hpp"
#include "pxcomtyp.hpp"
#include "pxstktra.hpp"
#include "types/origintypeenum.inc"
#include "ibttype.hpp"
#include <logger/loggerpool.h>
#include <stockbooking/componentmanager/stockbookingcomponentmanager.h>
#include <stockbooking/reservationconfig/ireservationconfigrepository.h>
#include <stockbooking/reservationconfig/ordertypereservationconfigptr.h>
#include <stockbooking/reservationconfig/ordertypereservationconfig.h>
#include <libbasarcmnutil_timespan.h>

extern bool pxGlobalNoDatabaseWrite;

pxStockBooking::pxStockBooking(pxSession* session) : pxErrorLoggable(),
    m_Session(session),
    m_CustomerStockReservationList(NULL),
    m_ArticleReservationList(NULL),
    //m_CurrentBranchNo(0),
    //m_CurrentArticleNo(0L),
    //m_CurrentCustomerNo(0L),
    //m_CurrentOrderNo(0L),
    //m_CurrentPositionNo(0L),
    m_CurrentArticle(NULL),
    m_CurrentCustomer(NULL),
    m_CurrentOrderItem(NULL),
    m_CurrentArticleReservation(NULL)
{
}

/***************************************************************************************************************************/

pxStockBooking::~pxStockBooking()
{
    // dont delete session object!
    m_Session = NULL;

    m_CurrentArticle            = NULL;
    m_CurrentCustomer           = NULL;
    m_CurrentOrderItem          = NULL;
    m_CurrentArticleReservation = NULL;

    if (m_CustomerStockReservationList != NULL)
    {
        delete m_CustomerStockReservationList;
        m_CustomerStockReservationList = NULL;
    }
    if (m_ArticleReservationList != NULL)
    {
        delete m_ArticleReservationList;
        m_ArticleReservationList = NULL;
    }
}

/***************************************************************************************************************************/

long pxStockBooking::AddQtyInStock(pxArtBase& article, const long qty, const TransactionType transactiontype, const struct ArticleAccountInfo* info, const bool checkResevation)
{
    BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerSession(), "pxStockBooking::AddQtyInStock()");

    long qtyAdded = 0L;

    InitContext(&article);

    if (CheckAndLockArticle())
    {
        if (true == checkResevation && CheckAndLockArticleReservation())
        {
            if (m_CurrentArticleReservation->IsReserveForPharmGroup())
            {
                long maxQty         = m_CurrentArticleReservation->GetMaxQty();
                long reservPercent  = m_CurrentArticleReservation->GetReservePct();
                long reservedQty    = m_CurrentArticleReservation->GetReservedQty();

                long qtyToReserv = (qty * reservPercent) / 100;

                if ((qtyToReserv + reservedQty) > maxQty)
                {
                    qtyToReserv = maxQty - reservedQty;
                }
                qtyAdded += m_CurrentArticleReservation->AddReservedQuantity(qtyToReserv);
            }
            m_CurrentArticleReservation->Put();
            if (!m_CurrentArticleReservation->IsGoodState())
            {
                Error() = m_CurrentArticleReservation->Error();
                BLOG_ERROR(libcsc::LoggerPool::getLoggerStockBooking(), ErrorMsg());
                return 0L;
            }
        }

        qtyAdded += m_CurrentArticle->AddQuantity(qty - qtyAdded);
        m_CurrentArticle->Put();
        if (!m_CurrentArticle->IsGoodState())
        {
            Error() = m_CurrentArticle->Error();
            BLOG_ERROR(libcsc::LoggerPool::getLoggerStockBooking(), ErrorMsg());
            return 0L;
        }
    }
    if (NULL != info)
    {
        WriteArticleAccount(qtyAdded, transactiontype, info);
    }
    else
    {
        ArticleAccountInfo defaultInfo;
        defaultInfo.StockTransaction    = StockReturn;    // 8
        defaultInfo.CommiType           = ShipNone;         // 2
        WriteArticleAccount(qtyAdded, transactiontype, &defaultInfo);
    }
    return qtyAdded;
}

/***************************************************************************************************************************/

long pxStockBooking::SubQtyInStock(pxArtBase& article, const long qty, const TransactionType transactiontype, const struct ArticleAccountInfo* info)
{
    BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerStockBooking(), "pxStockBooking::SubQtyInStock()");

    long qtySubtracted = 0L;

    InitContext(&article);

    if (CheckAndLockArticle())
    {
        qtySubtracted = m_CurrentArticle->SubQuantity(qty);
        m_CurrentArticle->Put();
        if (!m_CurrentArticle->IsGoodState())
        {
            Error() = m_CurrentArticle->Error();
            BLOG_ERROR(libcsc::LoggerPool::getLoggerStockBooking(), ErrorMsg());
            return 0L;
        }
    }
    if (NULL != info)
    {
        WriteArticleAccount((qtySubtracted * -1), transactiontype, info);
    }
    else
    {
        ArticleAccountInfo defaultInfo;
        defaultInfo.StockTransaction    = StockDebit;     // 3
        defaultInfo.CommiType           = ShipNone;         // 2
        WriteArticleAccount((qtySubtracted * -1), transactiontype, &defaultInfo);
    }
    return qtySubtracted;
}

/***************************************************************************************************************************/

long pxStockBooking::SetQtyInStock(pxArtBase& article, const long qty, const TransactionType transactiontype, const struct ArticleAccountInfo* info)
{
    BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerStockBooking(), "pxStockBooking::SetQtyInStock()");

    InitContext(&article);

    if (CheckAndLockArticle())
    {
        if (qty > 0)
        {
            long qtyExtern = GetReservedQtyInStockInternal(m_CurrentArticle);
            long qtyTotal  = m_CurrentArticle->GetQuantity() + qtyExtern;

            if (CheckAndLockArticleReservation())
            {
                if (m_CurrentArticleReservation->IsReserveForPharmGroup())
                {
                    long maxQty         = m_CurrentArticleReservation->GetMaxQty();
                    long reservPercent  = m_CurrentArticleReservation->GetReservePct();
                    long reservedQty    = m_CurrentArticleReservation->GetReservedQty();
                    
                    long qtyToReserv = (qty * reservPercent) / 100;

                    if ((qtyToReserv + reservedQty) > maxQty)
                    {
                        qtyToReserv = maxQty - reservedQty;
                    }
                    m_CurrentArticleReservation->SetReservedQuantity(reservedQty + qtyToReserv);
                    qtyExtern += qtyToReserv;
                    qtyTotal = qty - qtyToReserv;

                    long qtyStock = 0;

                    if ( (qtyTotal - qtyExtern) > 0 )
                    {
                        qtyStock = qtyTotal - qtyExtern;
                    }
                    m_CurrentArticle->SetQuantity(qtyStock);
                    m_CurrentArticleReservation->Put();
                    if (!m_CurrentArticleReservation->IsGoodState())
                    {
                        Error() = m_CurrentArticleReservation->Error();
                        BLOG_ERROR(libcsc::LoggerPool::getLoggerStockBooking(), ErrorMsg());
                        return 0L;
                    }
                }
                else
                {
                    long qtyStock = qty - qtyExtern;
                    if ( qtyStock < 0 )
                    {
                        qtyStock = 0;
                    }
                    m_CurrentArticle->SetQuantity( qtyStock );
                }
            }
            else
            {
                long qtyStock = qty - qtyExtern;
                if ( qtyStock < 0 )
                {
                    qtyStock = 0;
                }
                m_CurrentArticle->SetQuantity( qtyStock );
            }
        }
        else
        {
            //for record->getQuantity should not be < 0 (old interface programm and pharmos side)
            //we use the literal 0, because if control reaches this point
            //quantity is either 0 or < 0
            //
            //what happens if a negative value becomes valid in one case?
            m_CurrentArticle->SetQuantity( 0 );
        }
        m_CurrentArticle->Put();
        if (!m_CurrentArticle->IsGoodState())
        {
            Error() = m_CurrentArticle->Error();
            BLOG_ERROR(libcsc::LoggerPool::getLoggerStockBooking(), ErrorMsg());
            return 0L;
        }
    }
    if (NULL != info)
    {
        WriteArticleAccount(qty, transactiontype, info);
    }
    else
    {
        ArticleAccountInfo defaultInfo;
        defaultInfo.StockTransaction    = StockAccountCorrection; // 9
        defaultInfo.CommiType           = ShipNone;                 // 2
        WriteArticleAccount(qty, transactiontype, &defaultInfo);
    }
    return qty;
}

/***************************************************************************************************************************/

long pxStockBooking::GetAvailableQtyInStock(pxArtBase& article)
{
    BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerStockBooking(), "pxStockBooking::GetAvailableQtyInStock(pxArtBase&)");

    InitContext(&article);

    long qtyTotal = 0L;

    qtyTotal += m_CurrentArticle->GetQuantity();

    std::stringstream s;
    s << "GetAvailableQtyInStock(" << article.ArtikelNr() << ") returns " << qtyTotal;
    BLOG_TRACE(libcsc::LoggerPool::getLoggerStockBooking(), s.str());
    return qtyTotal;
}

/***************************************************************************************************************************/

long pxStockBooking::GetAvailableQtyInStock(pxArtBase& article, pxCustBase& customer)
{
    BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerStockBooking(), "pxStockBooking::GetAvailableQtyInStock(pxArtBase&, pxCustBase&)");

    InitContext(&article, &customer);

    long qtyTotal = 0L;

    qtyTotal += m_CurrentArticle->GetQuantity();

    if (NULL != m_CurrentArticleReservation)
    {
        qtyTotal += m_CurrentArticleReservation->GetReservedQty();
    }

    std::stringstream s;
    s << "GetAvailableQtyInStock(" << article.ArtikelNr() << ", " << customer.IDFNr() << ") returns " << qtyTotal;
    BLOG_TRACE(libcsc::LoggerPool::getLoggerStockBooking(), s.str());
    return qtyTotal;
}

/***************************************************************************************************************************/

long pxStockBooking::GetTotalQtyInStock(pxArtBase& article)
{
    long qtyTotal = GetAvailableQtyInStock(article);
    qtyTotal += GetReservedQtyInStock(article);
    return qtyTotal;
}

/***************************************************************************************************************************/

long pxStockBooking::GetReservedQtyInStock(pxArtBase& article)
{
    return GetReservedQtyInStockInternal(dynamic_cast<IArticleStockBooking*>(&article));
}

long pxStockBooking::GetReservedQtyInStockInternal(IArticleStockBooking* article)
{
    BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerStockBooking(), "pxStockBooking::GetReservedQtyInStock(pxArtBase&)");

    pxCustStockReservedList tmp(m_Session);
    tmp.SelectAllReservations(article->FilialNr(), article->ArtikelNr());
    long qtyReserved = 0L;

    pxCustStockReservedListIter iter(tmp);    // define iterator
    pxCustStockReserved* custStockReserved = NULL;
    while (NULL != (custStockReserved = (pxCustStockReserved*)++iter)) // browse list
    {
        qtyReserved += custStockReserved->ReservedQty();
    }

    std::stringstream s;
    s << "GetReservedQtyInStockInternal(" << article->ArtikelNr() << ") returns " << qtyReserved;
    BLOG_TRACE(libcsc::LoggerPool::getLoggerStockBooking(), s.str());
    return qtyReserved;
}

/***************************************************************************************************************************/

long pxStockBooking::GetReservedQtyInStock(pxArtBase& article, pxCustBase& customer, const enum OrderContext orderContext)
{
    BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerStockBooking(), "pxStockBooking::GetReservedQtyInStock(pxArtBase&, pxCustBase&, ordercontext)");

    InitContext(&article, &customer);

    pxCustStockReserved*    custStockReserved = NULL;
    long                    qtyReserved = 0L;

    if (m_CustomerStockReservationList != NULL)
    {
        pxCustStockReservedListIter iter(*m_CustomerStockReservationList);    // define iterator
        while (NULL != (custStockReserved = (pxCustStockReserved*)++iter)) // browse list
        {
            switch (orderContext)
            {
                case ORDER_CONTEXT_IBT:
                    if (RESTYPE_IBT_FREE == custStockReserved->ReservType() || RESTYPE_IBT_RESERVED == custStockReserved->ReservType())
                        qtyReserved += custStockReserved->ReservedQty();
                    break;
                case ORDER_CONTEXT_RESTDELIVERY:
                    if (RESTYPE_RESTDELIVERY_FREE == custStockReserved->ReservType() || RESTYPE_RESTDELIVERY_RESERVED == custStockReserved->ReservType())
                        qtyReserved += custStockReserved->ReservedQty();
                    break;
                case ORDER_CONTEXT_DEFAULT:
                default:
                    if (RESTYPE_INFOORDER_FREE == custStockReserved->ReservType() || RESTYPE_INFOORDER_RESERVED == custStockReserved->ReservType())
                        qtyReserved += custStockReserved->ReservedQty();
                    break;
            }
        }
    }

    if (m_CurrentArticleReservation != NULL)
    {
        qtyReserved += m_CurrentArticleReservation->GetReservedQty();
    }

    std::stringstream s;
    s << "GetReservedQtyInStock(" << article.ArtikelNr() << ", " << customer.IDFNr() << ") returns " << qtyReserved;
    BLOG_TRACE(libcsc::LoggerPool::getLoggerStockBooking(), s.str());
    return qtyReserved;
}

/***************************************************************************************************************************/

long pxStockBooking::GetBookableQuantity(pxOrderItem& item, pxArtBase& article)
{
    long qty = 0;
    InitContext(&article, item.Order().Customer(), &item);

    if (NULL != m_CurrentArticleReservation)
    {
        qty += m_CurrentArticleReservation->GetReservedQty();
    }
    if (NULL != m_CurrentReservationConfig.get() && true == m_CurrentReservationConfig->getReservedStockOnly())
    {
        return qty;
    }
    pxCustStockReserved* res;
    if (item.Order().BatchSchreiben() == cORTYPE_AUXILIARY)
    {
        res = FindCustomerStockReservation(RESTYPE_IBT_FREE);
        if (NULL != res)
        {
            qty += res->ReservedQty();
        }
        res = FindCustomerStockReservation(RESTYPE_IBT_RESERVED);
        if (NULL != res)
        {
            qty += res->ReservedQty();
        }
    }
    if (item.IsReleaseRestDelivery())
    {
        res = FindCustomerStockReservation(RESTYPE_RESTDELIVERY_FREE);
        if (NULL != res)
        {
            qty += res->ReservedQty();
        }
        res = FindCustomerStockReservation(RESTYPE_RESTDELIVERY_RESERVED);
        if (NULL != res)
        {
            qty += res->ReservedQty();
        }
    }
    res = FindCustomerStockReservation(RESTYPE_INFOORDER_FREE);
    if (NULL != res)
    {
        qty += res->ReservedQty();
    }
    res = FindCustomerStockReservation(RESTYPE_INFOORDER_RESERVED);
    if (NULL != res)
    {
        qty += res->ReservedQty();
    }
    qty += m_CurrentArticle->GetQuantity();

    return qty;
}

/***************************************************************************************************************************/

long pxStockBooking::AddReservationForInfoOrder(pxArtBase& article, pxCustBase& customer, const long qty)
{
    std::stringstream ss;
    ss << "AddReservationForInfoOrder(article=" << article.ArtikelNr() << ", customer=" << customer.IDFNr() << ", qty=" << qty << ")";
    BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerStockBooking(), ss.str());

    const pxOrderEntryParamPtr  param = m_Session->getOrderEntryParam(customer.Vertriebszentrum());
    long                qtyAlreadyReserved  = 0L;
    long                qtyReserved         = 0L;
    long                qtyToReserve        = qty;
    ArticleAccountInfo  info;

    InitContext(&article, &customer);

    // check max reservation qty
    qtyAlreadyReserved = GetReservedQty(GLOBAL_RESTYPE_INFOORDER);
    if (qtyToReserve + qtyAlreadyReserved > param->ReserveMaxQty())
    {
        qtyToReserve = param->ReserveMaxQty() - qtyAlreadyReserved;
    }

    if (CheckAndLockArticle())
    {
        // reserve from article reservation
        if (qtyToReserve > 0)
        {
            if (CheckAndLockArticleReservation())
            {
                qtyReserved = m_CurrentArticleReservation->SubReservedQuantity(qtyToReserve);
                if (qtyReserved > 0)
                {
                    AddCustomerStockReservation(qtyReserved, RESTYPE_INFOORDER_RESERVED);
                    info.MoveType =  RESTYPE_INFOORDER_RESERVED;
                    WriteArticleAccount(qtyReserved, TRANSACTIONTYPE_RESERVATION, &info);
                    qtyToReserve -= qtyReserved;
                    std::stringstream s1;
                    s1 << "reserved article " << m_CurrentArticle->ArtikelNr()
                       << ", quantity " << qtyReserved
                       << " for customer " << m_CurrentCustomer->IDFNr()
                       << " from articlereservation";
                    BLOG_TRACE(libcsc::LoggerPool::getLoggerStockBooking(), s1.str());
                }
                m_CurrentArticleReservation->Put();
                if (!m_CurrentArticleReservation->IsGoodState())
                {
                    Error() = m_CurrentArticleReservation->Error();
                    BLOG_ERROR(libcsc::LoggerPool::getLoggerStockBooking(), ErrorMsg());
                }
            }
        }

        // if there is remaining qty to reserve, reserve from artikellokal.bestand
        if (qtyToReserve > 0)
        {
            qtyReserved = m_CurrentArticle->SubQuantity(qtyToReserve);
            AddCustomerStockReservation(qtyReserved, RESTYPE_INFOORDER_FREE);
            info.MoveType =  RESTYPE_INFOORDER_FREE;
            WriteArticleAccount(qtyReserved, TRANSACTIONTYPE_RESERVATION, &info);
            std::stringstream s2;
            s2 << "reserved article " << m_CurrentArticle->ArtikelNr()
               << ", quantity " << qtyReserved
               << " for customer " << m_CurrentCustomer->IDFNr()
               << " from artikellokal.bestand";
            BLOG_TRACE(libcsc::LoggerPool::getLoggerStockBooking(), s2.str());
            qtyToReserve -= qtyReserved;
        }
        m_CurrentArticle->Put();
        if (!m_CurrentArticle->IsGoodState())
        {
            Error() = m_CurrentArticle->Error();
            BLOG_ERROR(libcsc::LoggerPool::getLoggerStockBooking(), ErrorMsg());
        }
    }
    if (!IsGoodState())
    {
        qtyToReserve = qty;
    }

    // return sum of both reserved quantities
    ss.str("");
    ss << "AddInfoOrder(article=" << article.ArtikelNr() << ", customer=" << customer.IDFNr() << ", qty=" << qty << ") "
       << "total reserved " << (qty - qtyToReserve);
    BLOG_DEBUG(libcsc::LoggerPool::getLoggerStockBooking(), ss.str());
    return (qty - qtyToReserve);
}

/***************************************************************************************************************************/

long pxStockBooking::CancelReservationForInfoOrder(pxArtBase& article, pxCustBase& customer, const long qty)
{
    std::stringstream s;
    s << "pxStockBooking::CancelReservationForInfoOrder(article=" << article.ArtikelNr() << ", customer=" << customer.IDFNr() << ", qty=" << qty << ")";
    BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerStockBooking(), s.str());

    long qtyToReduce = qty;
    long qtyReduced = 0L;
    ArticleAccountInfo info;
    
    InitContext(&article, &customer);

    if (CheckAndLockArticle())
    {
        if (qtyToReduce > 0)
        {
            if (CheckAndLockArticleReservation())
            {
                qtyReduced = ReduceCustomerStockReservation(qtyToReduce, RESTYPE_INFOORDER_RESERVED);
                if (qtyReduced > 0)
                {
                    m_CurrentArticleReservation->AddReservedQuantity(qtyReduced);
                    m_CurrentArticleReservation->Put();
                    if (!m_CurrentArticleReservation->IsGoodState())
                    {
                        Error() = m_CurrentArticleReservation->Error();
                        BLOG_ERROR(libcsc::LoggerPool::getLoggerStockBooking(), ErrorMsg());
                    }
                    info.MoveType = RESTYPE_INFOORDER_RESERVED;
                    WriteArticleAccount((qtyReduced * -1), TRANSACTIONTYPE_RESERVATION, &info);
                    qtyToReduce -= qtyReduced;
                }
            }
        }
        if (qtyToReduce > 0)
        {
            qtyReduced = ReduceCustomerStockReservation(qtyToReduce, RESTYPE_INFOORDER_FREE);
            if (qtyReduced > 0)
            {
                m_CurrentArticle->AddQuantity(qtyReduced);
                info.MoveType = RESTYPE_INFOORDER_FREE;
                WriteArticleAccount((qtyReduced * -1), TRANSACTIONTYPE_RESERVATION, &info);
                qtyToReduce -= qtyReduced;
            }
        }
        m_CurrentArticle->Put();
        if (!m_CurrentArticle->IsGoodState())
        {
            Error() = m_CurrentArticle->Error();
            BLOG_ERROR(libcsc::LoggerPool::getLoggerStockBooking(), ErrorMsg());
        }
    }

    if (!IsGoodState())
    {
        qtyToReduce = qty;
    }

    s.str("");
    s << "CancelInfoOrder(article=" << article.ArtikelNr() << ", customer=" << customer.IDFNr() << ", qty=" << qty << ") "
        << "cancelled " << (qty - qtyToReduce);
    BLOG_DEBUG(libcsc::LoggerPool::getLoggerStockBooking(), s.str());

    return (qty - qtyToReduce);
}

/***************************************************************************************************************************/

long pxStockBooking::AddReservationForRestDelivery(pxArtBase& article, pxCustBase& customer, const long qty)
{
    std::stringstream s;
    s << "pxStockBooking::AddReservationForRestDelivery(article=" << article.ArtikelNr() << ", customer=" << customer.IDFNr() << ", qty=" << qty << ")";
    BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerStockBooking(), s.str());

    long qtyReserved = 0L;
    long qtyToReserve = qty;

    InitContext(&article, &customer);

    ArticleAccountInfo info;
    info.PurchaseOrderNo    = 0;
    info.CustomerSupplierNo = m_CurrentCustomer->IDFNr();
    info.StockTransaction   = StockDebit;     // 3
    info.CommiType          = ShipNone;         // 2

    if (CheckAndLockArticle())
    {
        // reserve from article reservation
        if (qtyToReserve > 0)
        {
            if (CheckAndLockArticleReservation())
            {
                qtyReserved = m_CurrentArticleReservation->SubReservedQuantity(qtyToReserve);
                if (qtyReserved > 0)
                {
                    AddCustomerStockReservation(qtyReserved, RESTYPE_RESTDELIVERY_RESERVED);
                    qtyToReserve -= qtyReserved;
                    m_CurrentArticleReservation->Put();
                    if (!m_CurrentArticleReservation->IsGoodState())
                    {
                        Error() = m_CurrentArticleReservation->Error();
                        BLOG_ERROR(libcsc::LoggerPool::getLoggerStockBooking(), ErrorMsg());
                    }
                    info.MoveType = RESTYPE_RESTDELIVERY_RESERVED;
                    WriteArticleAccount(qtyReserved, TRANSACTIONTYPE_RESERVATION, &info);
                }
            }
        }

        // if there is remaining qty to reserve, reserve from artikellokal.bestand
        if (qtyToReserve > 0)
        {
            qtyReserved = m_CurrentArticle->SubQuantity(qtyToReserve);
            if (qtyReserved > 0)
            {
                AddCustomerStockReservation(qtyReserved, RESTYPE_RESTDELIVERY_FREE);
                qtyToReserve -= qtyReserved;
                info.MoveType = RESTYPE_RESTDELIVERY_FREE;
                WriteArticleAccount(qtyReserved, TRANSACTIONTYPE_RESERVATION, &info);
            }
        }
        m_CurrentArticle->Put();
        if (!m_CurrentArticle->IsGoodState())
        {
            Error() = m_CurrentArticle->Error();
            BLOG_ERROR(libcsc::LoggerPool::getLoggerStockBooking(), ErrorMsg());
        }
    }
    if (!IsGoodState())
    {
        qtyToReserve = qty;
    }

    s.str("");
    s << "AddRestDel(article=" << article.ArtikelNr() << ", customer=" << customer.IDFNr() << ", qty=" << qty << ") "
        << "reserved " << (qty - qtyToReserve);
    BLOG_DEBUG(libcsc::LoggerPool::getLoggerStockBooking(), s.str());

    // return sum of both reserved quantities
    return (qty - qtyToReserve);
}

/***************************************************************************************************************************/

long pxStockBooking::AddReservationForIBT(const long articleNo, const long customerNo, const short branchNoIBT, const long qty)
{
    std::stringstream s;
    s << "pxStockBooking::AddReservationForIBT(article=" << articleNo << ", customer=" << customerNo
      << ", branchNoIBT=" << branchNoIBT << ", qty=" << qty << ")";
    BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerStockBooking(), s.str());

    ClearError();

    long qtyReserved = 0L;

    pxArtRemote remoteArticle(m_Session, articleNo, branchNoIBT);
    m_CurrentArticle = &remoteArticle;
    if (CheckAndLockArticle())
    {
        // special initalization of list -> remote reservation list!
        if (NULL != m_CustomerStockReservationList)
        {
            delete m_CustomerStockReservationList;
            m_CustomerStockReservationList = NULL;
        }
        m_CustomerStockReservationList = new pxCustStockReservedList(m_Session);
        m_CustomerStockReservationList->SelectCustomerReservations(
            remoteArticle.FilialNr(),
            remoteArticle.ArtikelNr(),
            customerNo);
        qtyReserved = remoteArticle.SubQuantity(qty);
        if (qtyReserved > 0)
        {
            AddCustomerStockReservation(branchNoIBT, articleNo, customerNo, qty, RESTYPE_IBT_FREE);
        }
        remoteArticle.Put();
        if (!remoteArticle.IsGoodState())
        {
            Error() = remoteArticle.Error();
            BLOG_ERROR(libcsc::LoggerPool::getLoggerStockBooking(), ErrorMsg());
        }
        if (!IsGoodState())
        {
            qtyReserved = 0L;
        }
    }

    if (qtyReserved > 0)
    {
        ArticleAccountInfo info;
        // remote article account
        info.CustomerSupplierNo	= customerNo;
        info.MoveType			= RESTYPE_IBT_FREE;
        WriteArticleAccount(qtyReserved, TRANSACTIONTYPE_RESERVATION, &info);
    }

    if (!pxGlobalNoDatabaseWrite) //! \note workaround to not log
    {
        s.str("");
        s << "AddIBT(article=" << articleNo << ", customer=" << customerNo << ", ibtbranch=" << branchNoIBT << ", qty=" << qty << ") "
          << "reserved " << (qtyReserved);
        BLOG_DEBUG(libcsc::LoggerPool::getLoggerStockBooking(), s.str());
    }
    return qtyReserved;
}

/***************************************************************************************************************************/

long pxStockBooking::CancelReservationForIBT(const long articleNo, const long customerNo, const short branchNoIBT, const long qty)
{
    std::stringstream s;
    s << "pxStockBooking::CancelReservationForIBT(article=" << articleNo << ", customer=" << customerNo
      << ", branchNoIBT=" << branchNoIBT << ", qty=" << qty << ")";
    BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerStockBooking(), s.str());

    ClearError();

    long qtyReduced = 0L;

    pxArtRemote remoteArticle(m_Session, articleNo, branchNoIBT);
    m_CurrentArticle = &remoteArticle;
    if (CheckAndLockArticle())
    {
        // special initalization of list -> remote reservation list!
        if (NULL != m_CustomerStockReservationList)
        {
            delete m_CustomerStockReservationList;
            m_CustomerStockReservationList = NULL;
        }
        m_CustomerStockReservationList = new pxCustStockReservedList(m_Session);
        m_CustomerStockReservationList->SelectCustomerReservations(
            remoteArticle.FilialNr(),
            remoteArticle.ArtikelNr(),
            customerNo);

        qtyReduced = ReduceCustomerStockReservation(qty, RESTYPE_IBT_FREE);
        if (qtyReduced > 0)
        {
            remoteArticle.AddQuantity(qtyReduced);
        }
        remoteArticle.Put();
        if (!remoteArticle.IsGoodState())
        {
            Error() = remoteArticle.Error();
            BLOG_ERROR(libcsc::LoggerPool::getLoggerStockBooking(), ErrorMsg());
        }

        if (!IsGoodState())
        {
            qtyReduced = 0L;
        }
    }

    if (qtyReduced > 0)
    {
        ArticleAccountInfo info;
        // remote article account
        info.CustomerSupplierNo	= customerNo;
        info.MoveType			= RESTYPE_IBT_FREE;
        WriteArticleAccount((qtyReduced * -1), TRANSACTIONTYPE_RESERVATION, &info);
    }

    s.str("");
    s << "CancelIBT(article=" << articleNo << ", customer=" << customerNo << ", ibtbranch=" << branchNoIBT << ", qty=" << qty << ") "
      << "cancelled " << (qtyReduced);
    BLOG_DEBUG(libcsc::LoggerPool::getLoggerStockBooking(), s.str());

    return qtyReduced;
}

/***************************************************************************************************************************/
    // if (BookingType Nachlieferung)
    // {
    //  von custstockreserved type 8		-> custstockreserved type 12
    //  Rest von custstockreserved type 7	-> custstockreserved type 11
    // }
    // if (BookingType Verbund)
    // {
    //   von custstockreserved type 10		-> custstockreserved type 12
    //   Rest von custstockreserved type 9	-> custstockreserved type 11
    // }
    // if (Kunde.XMLInfolevel 3)
    // {
    //   Rest von custstockreserved type 6	-> custstockreserved type 12
    //   Rest von custstockreserved type 1	-> custstockreserved type 11
    // }
    // Rest von articlereservation			-> custstockreserved type 12
    // Rest von artikellokal.bestand		-> custstockreserved type 11

long pxStockBooking::AddReservationForOpenOrder(pxOrderItem& item, const long qty)
{
    std::stringstream s;
    s << "pxStockBooking::AddReservationForOpenOrder(pxOrderItem& item=(" << item.Order().KdAuftragNr() << ", " << item.PosNr() << ", "
      << item.ArtikelNr() << "), const long qty=" << qty << ")";
    BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerStockBooking(), s.str());

    if (NULL == item.ArtBase() || false == item.ArtBase()->IsGoodState())
        return 0L;

    long qtyReserved = 0L;
    long qtyToReserve = qty;

    InitContext(item.ArtBase(), item.Order().Customer(), &item);

    ArticleAccountInfo info;
    info.PurchaseOrderNo    = item.Order().KdAuftragNr();
    info.PositionNo         = item.PosNr();
    info.CustomerSupplierNo = item.Order().Customer()->IDFNr();
    info.StockTransaction   = item.Order().StockTrans().StockTransactionCode();
    info.CommiType          = item.Order().CommType().ShipCode();
    info.BelegArt           = item.Order().KdAuftragArt()();

    if (CheckAndLockArticle())
    {
        if (item.IsReleaseRestDelivery())
        {
            if (qtyToReserve > 0)
            {
                qtyReserved = ReduceCustomerStockReservation(qtyToReserve, RESTYPE_RESTDELIVERY_RESERVED);
                if (qtyReserved > 0)
                {
                    AddCustomerStockReservation(qtyReserved, RESTYPE_OPENORDER_RESERVED);
                    info.MoveType = RESTYPE_OPENORDER_RESERVED;
                    WriteArticleAccount(qtyReserved, TRANSACTIONTYPE_RESERVATION, &info);
                    qtyToReserve -= qtyReserved;
                }
            }
            if (qtyToReserve > 0)
            {
                qtyReserved = ReduceCustomerStockReservation(qtyToReserve, RESTYPE_RESTDELIVERY_FREE);
                if (qtyReserved > 0)
                {
                    AddCustomerStockReservation(qtyReserved, RESTYPE_OPENORDER_FREE);
                    info.MoveType = RESTYPE_OPENORDER_FREE;
                    WriteArticleAccount(qtyReserved, TRANSACTIONTYPE_RESERVATION, &info);
                    qtyToReserve -= qtyReserved;
                }
            }
        }
        
        if (item.Order().BatchSchreiben() == cORTYPE_AUXILIARY)
        {
            if (qtyToReserve > 0)
            {
                qtyReserved = ReduceCustomerStockReservation(qtyToReserve, RESTYPE_IBT_RESERVED);
                if (qtyReserved > 0)
                {
                    AddCustomerStockReservation(qtyReserved, RESTYPE_OPENORDER_RESERVED);
                    info.MoveType = RESTYPE_OPENORDER_RESERVED;
                    WriteArticleAccount(qtyReserved, TRANSACTIONTYPE_RESERVATION, &info);
                    qtyToReserve -= qtyReserved;
                }
            }
            if (qtyToReserve > 0)
            {
                qtyReserved = ReduceCustomerStockReservation(qtyToReserve, RESTYPE_IBT_FREE);
                if (qtyReserved > 0)
                {
                    AddCustomerStockReservation(qtyReserved, RESTYPE_OPENORDER_FREE);
                    info.MoveType = RESTYPE_OPENORDER_FREE;
                    WriteArticleAccount(qtyReserved, TRANSACTIONTYPE_RESERVATION, &info);
                    qtyToReserve -= qtyReserved;
                }
            }
        }

        // check for info order reservation
        if (m_CurrentCustomer->IsInfoLevelHigh())
        {
            if (qtyToReserve > 0)
            {
                qtyReserved = ReduceCustomerStockReservation(qtyToReserve, RESTYPE_INFOORDER_RESERVED);
                if (qtyReserved > 0)
                {
                    AddCustomerStockReservation(qtyReserved, RESTYPE_OPENORDER_RESERVED);
                    info.MoveType =  RESTYPE_OPENORDER_RESERVED;
                    WriteArticleAccount(qtyReserved, TRANSACTIONTYPE_RESERVATION, &info);
                    qtyToReserve -= qtyReserved;
                }
            }
            if (qtyToReserve > 0)
            {
                qtyReserved = ReduceCustomerStockReservation(qtyToReserve, RESTYPE_INFOORDER_FREE);
                if (qtyReserved > 0)
                {
                    AddCustomerStockReservation(qtyReserved, RESTYPE_OPENORDER_FREE);
                    info.MoveType =  RESTYPE_OPENORDER_FREE;
                    WriteArticleAccount(qtyReserved, TRANSACTIONTYPE_RESERVATION, &info);
                    qtyToReserve -= qtyReserved;
                }
            }
        }

        // new begin
        if (NULL != m_CurrentReservationConfig.get() && true == m_CurrentReservationConfig->getFreeStockHasPriority())
        {
            // TODO FN zuerst aus artikellokal buchen, falls nicht ausreichend, aus articlereservation (Sinn?)
        }
        // new end

        // if there is remaining qty to reserve, reserve from articlereservation
        if (CheckAndLockArticleReservation())
        {
            qtyReserved = m_CurrentArticleReservation->SubReservedQuantity(qtyToReserve);
            if (qtyReserved > 0)
            {
                AddCustomerStockReservation(qtyReserved, RESTYPE_OPENORDER_RESERVED);
                info.MoveType =  RESTYPE_OPENORDER_RESERVED;
                WriteArticleAccount(qtyReserved, TRANSACTIONTYPE_RESERVATION, &info);
                qtyToReserve -= qtyReserved;
                m_CurrentArticleReservation->Put();
                if (!m_CurrentArticleReservation->IsGoodState())
                {
                    Error() = m_CurrentArticleReservation->Error();
                    BLOG_ERROR(libcsc::LoggerPool::getLoggerStockBooking(), ErrorMsg());
                }
            }
        }

        // no reservation config found or booking from artikellokal allowed:
        if (NULL == m_CurrentReservationConfig.get() || false == m_CurrentReservationConfig->getReservedStockOnly())
        {
            // if there is remaining qty to reserve, reserve from artikellokal.bestand
            if (qtyToReserve > 0)
            {
                qtyReserved = m_CurrentArticle->SubQuantity(qtyToReserve);
                if (qtyReserved > 0)
                {
                    AddCustomerStockReservation(qtyReserved, RESTYPE_OPENORDER_FREE);
                    info.MoveType = RESTYPE_OPENORDER_FREE;
                    WriteArticleAccount(qtyReserved, TRANSACTIONTYPE_RESERVATION, &info);
                    qtyToReserve -= qtyReserved;

                    s.str("");
                    s << "AddReservationForOpenOrder(order=" << item.Order().KdAuftragNr() << ", pos=" << item.PosNr() << ", article="
                        << item.ArtikelNr() << ", qty=" << qty << ") "
                        << "reserved " << qtyReserved << " from artikellokal.bestand";
                    BLOG_TRACE(libcsc::LoggerPool::getLoggerStockBooking(), s.str());
                }
            }
        }
        m_CurrentArticle->Put();
        if (!m_CurrentArticle->IsGoodState())
        {
            Error() = m_CurrentArticle->Error();
            BLOG_ERROR(libcsc::LoggerPool::getLoggerStockBooking(), ErrorMsg());
        }
    }

    if (!IsGoodState())
    {
        BLOG_ERROR(libcsc::LoggerPool::getLoggerStockBooking(), ErrorMsg());
        qtyToReserve = qty;
    }

    s.str("");
    s << "AddOO(order=" << item.Order().KdAuftragNr() << ", pos=" << item.PosNr() << ", art="
      << item.ArtikelNr() << ", qty=" << qty << ") --> " << (qty - qtyToReserve);
    if (qtyToReserve > 0)
    {
        BLOG_ERROR(libcsc::LoggerPool::getLoggerStockBooking(), s.str());
    }
    else
    {
        if (!pxGlobalNoDatabaseWrite) //! \note workaround to not log 
            BLOG_DEBUG(libcsc::LoggerPool::getLoggerStockBooking(), s.str());
    }

    return (qty - qtyToReserve);
}

/***************************************************************************************************************************/

long pxStockBooking::CancelReservationForOpenOrder(pxOrderItem& item, const long qty)
{
    std::stringstream s;
    s << "pxStockBooking::CancelReservationForOpenOrder(pxOrderItem& item=(" << item.Order().KdAuftragNr() << ", " << item.PosNr() << ", "
      << item.ArtikelNr() << "), const long qty=" << qty << ")";
    BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerStockBooking(), s.str());

    if (NULL == item.ArtBase() || false == item.ArtBase()->IsGoodState())
        return 0L;

    long qtyToReduce = qty;
    long qtyReduced = 0L;

    InitContext(item.ArtBase(), item.Order().Customer(), &item);

    ArticleAccountInfo info;
    info.PurchaseOrderNo    = item.Order().KdAuftragNr();
    info.PositionNo         = item.PosNr();
    info.CustomerSupplierNo = item.Order().Customer()->IDFNr();
    info.StockTransaction   = item.Order().StockTrans().StockTransactionCode();
    info.CommiType          = item.Order().CommType().ShipCode();
    info.BelegArt           = item.Order().KdAuftragArt()();

    if (CheckAndLockArticle())
    {
        if (qtyToReduce > 0)
        {
            qtyReduced = ReduceCustomerStockReservation(qtyToReduce, RESTYPE_OPENORDER_RESERVED);
            if (qtyReduced > 0)
            {
                if (CheckAndLockArticleReservation())
                {
                    m_CurrentArticleReservation->AddReservedQuantity(qtyReduced);
                    m_CurrentArticleReservation->Put();
                    if (!m_CurrentArticleReservation->IsGoodState())
                    {
                        Error() = m_CurrentArticleReservation->Error();
                        BLOG_ERROR(libcsc::LoggerPool::getLoggerStockBooking(), ErrorMsg());
                    }
                    info.MoveType = RESTYPE_OPENORDER_RESERVED;
                    if (m_CurrentArticleReservation->IsReserveNoSalesEffectiv())
                    {
                        info.StockTransaction = StockDebit;	// Bestand abbuchen, Bedarf nicht kumulieren
                    }
                    WriteArticleAccount((qtyReduced * -1), TRANSACTIONTYPE_RESERVATION, &info);
                    info.StockTransaction = item.Order().StockTrans().StockTransactionCode(); // reset
                }
                else
                {
                    s.str("");
                    s << "CancelOO(ord=" << item.Order().KdAuftragNr() << ", pos=" << item.PosNr() << ", art="
                        << item.ArtikelNr() << ", qty=" << qty << ") --> Articlereservation not found! book back to free stock!";
                    BLOG_WARN(libcsc::LoggerPool::getLoggerStockBooking(), s.str());
                    m_CurrentArticle->AddQuantity(qtyReduced);
                    info.MoveType = RESTYPE_OPENORDER_FREE;
                    WriteArticleAccount((qtyReduced * -1), TRANSACTIONTYPE_RESERVATION, &info);
                }
                qtyToReduce -= qtyReduced;
            }
        }
        if (qtyToReduce > 0)
        {
            qtyReduced = ReduceCustomerStockReservation(qtyToReduce, RESTYPE_OPENORDER_FREE);
            if (qtyReduced > 0)
            {
                m_CurrentArticle->AddQuantity(qtyReduced);
                info.MoveType = RESTYPE_OPENORDER_FREE;
                WriteArticleAccount((qtyReduced * -1), TRANSACTIONTYPE_RESERVATION, &info);
                qtyToReduce -= qtyReduced;
            }
        }
        m_CurrentArticle->Put();
        if (!m_CurrentArticle->IsGoodState())
        {
            Error() = m_CurrentArticle->Error();
            BLOG_ERROR(libcsc::LoggerPool::getLoggerStockBooking(), ErrorMsg());
        }
    }

    if (!IsGoodState())
    {
        qtyToReduce = qty;
    }

    s.str("");
    s << "CancelOO(ord=" << item.Order().KdAuftragNr() << ", pos=" << item.PosNr() << ", art="
      << item.ArtikelNr() << ", qty=" << qty << ") --> " << (qty - qtyToReduce);
    BLOG_DEBUG(libcsc::LoggerPool::getLoggerStockBooking(), s.str());
    return (qty - qtyToReduce);
}

/***************************************************************************************************************************/

long pxStockBooking::ReleaseReservationForOpenOrder(pxOrderItem& item, const long qty)
{
    std::stringstream s;
    s << "pxStockBooking::ReleaseReservationForOpenOrder(pxOrderItem& item=(" << item.Order().KdAuftragNr() << ", " << item.PosNr() << ", "
      << item.ArtikelNr() << "), const long qty=" << qty << ")";
    BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerStockBooking(), s.str());

    if (NULL == item.ArtBase() || false == item.ArtBase()->IsGoodState())
        return 0L;

    long qtyToReduce = qty;
    long qtyReduced = 0L;
    
    InitContext(item.ArtBase(), item.Order().Customer(), &item, (qtyToReduce > 0));

    ArticleAccountInfo info;
    info.PurchaseOrderNo    = item.Order().KdAuftragNr();
    info.PositionNo         = item.PosNr();
    info.CustomerSupplierNo = item.Order().Customer()->IDFNr();
    info.StockTransaction   = item.Order().StockTrans().StockTransactionCode();
    info.CommiType          = item.Order().CommType().ShipCode();
    info.BelegArt           = item.Order().KdAuftragArt()();

    if (qtyToReduce > 0)
    {
        if (CheckAndLockArticle())
        {
            qtyReduced = ReduceCustomerStockReservation(qtyToReduce, RESTYPE_OPENORDER_RESERVED);
            if (qtyReduced > 0)
            {
                info.MoveType = RESTYPE_OPENORDER_RESERVED;
                if (m_CurrentArticleReservation != NULL && m_CurrentArticleReservation->IsReserveNoSalesEffectiv())
                {
                    info.StockTransaction = StockDebit;	// Bestand abbuchen, Bedarf nicht kumulieren
                }
                WriteArticleAccount(qtyReduced, TRANSACTIONTYPE_DEBIT, &info);
                info.StockTransaction = item.Order().StockTrans().StockTransactionCode(); // reset
                qtyToReduce -= qtyReduced;
            }
            if (qtyToReduce > 0)
            {
                qtyReduced = ReduceCustomerStockReservation(qtyToReduce, RESTYPE_OPENORDER_FREE);
                if (qtyReduced > 0)
                {
                    info.MoveType = RESTYPE_OPENORDER_FREE;
                    if (item.Order().BatchSchreiben() == cORTYPE_AUXILIARY)
                    {
                        // TODO FN determine stocktransaction according to ibttype.purchaserelevancemode (if paraauftragbearb.nlevelibt==1)
                        switch (GetPurchaseRelevanceMode())
                        {
                            case PRM_IBT_BRANCH :
                            case PRM_BOTH_BRANCHES :
                                info.StockTransaction = StockDebitAndDemand;  // Bestand abbuchen, Bedarf kumulieren
                                item.SetPurchaseRelevantQty(item.GetPurchaseRelevantQty() + qtyReduced);
                                break;
                            case PRM_ORIGINAL_BRANCH :
                            case PRM_UNKNOWN :
                            default :
                                info.StockTransaction = StockDebit;           // Bestand abbuchen, Bedarf nicht kumulieren
                                break;
                        }
                        WriteArticleAccount(qtyReduced, TRANSACTIONTYPE_AUXBOOKED, &info);
                        info.StockTransaction = item.Order().StockTrans().StockTransactionCode(); // reset
                    }
                    else
                    {
                        WriteArticleAccount(qtyReduced, TRANSACTIONTYPE_DEBIT, &info);
                        item.SetPurchaseRelevantQty(item.GetPurchaseRelevantQty() + qtyReduced);
                    }
                    qtyToReduce -= qtyReduced;
                }
            }
            m_CurrentArticle->Put();
            if (!m_CurrentArticle->IsGoodState())
            {
                Error() = m_CurrentArticle->Error();
                BLOG_ERROR(libcsc::LoggerPool::getLoggerStockBooking(), ErrorMsg());
            }
        }
    }

    if (!IsGoodState())
    {
        BLOG_ERROR(libcsc::LoggerPool::getLoggerStockBooking(), ErrorMsg());
        qtyToReduce = qty;
    }

    // check if there is remaining qtyToReduce
    if (qtyToReduce > 0)
    {
        s.str("");
        s << "RelOO(ord=" << item.Order().KdAuftragNr() << ", pos=" << item.PosNr() << ", art="
          << item.ArtikelNr() << ", qty=" << qty << ") --> " << (qty - qtyToReduce);
        if (!pxGlobalNoDatabaseWrite) //! \note workaround to not log 
            BLOG_ERROR(libcsc::LoggerPool::getLoggerStockBooking(), s.str());
    }

    // article account entry in case of shortage
    if (item.IsQStateNotOnHand())
    {
        long qtyShortage = item.MengeBestellt() - item.MengeAbgebucht() - item.MengeVerbund() - item.MengeNachgeliefert();
        if (qtyShortage > 0)
        {
            if (item.IsMengenKontigentDefekt())
            {
                WriteArticleAccount(qtyShortage, TRANSACTIONTYPE_QUOTA_EXCEEDED, &info);
            }
            else if (item.IsDayNightMergePosition()) 
            { 
               ; // do nothing 
            }
            else
            {
                WriteArticleAccount(qtyShortage, TRANSACTIONTYPE_SHORTAGE, &info);
            }
        }
    }

    // article account entry in case of inter branch transfer
    long qtyIBT = item.MengeVerbund();
    if (qtyIBT > 0)
    {
        // determine stocktransaction according to ibttype.purchaserelevancemode (if paraauftragbearb.nlevelibt==1)
        switch (GetPurchaseRelevanceMode())
        {
            case PRM_ORIGINAL_BRANCH :
            case PRM_BOTH_BRANCHES :
                info.StockTransaction = StockDemand;          // Keine Bestandsbewegung, Bedarf kumulieren
                item.SetPurchaseRelevantQty(item.GetPurchaseRelevantQty() + qtyIBT);
                break;
            case PRM_IBT_BRANCH :
                info.StockTransaction = StockNoTransaction;   // Keine Bestands-/Bedarfskontenbewegung
                break;
            case PRM_UNKNOWN :                                              // do nothing
            default :
                break;
        }
        WriteArticleAccount(qtyIBT, TRANSACTIONTYPE_AUXDELIVERY, &info);
        info.StockTransaction = item.Order().StockTrans().StockTransactionCode(); // reset
    }

    // article account entry in case of subsequent delivery
    long qtySupply = item.MengeNachgeliefert();
    if (qtySupply > 0)
    {
        WriteArticleAccount(qtySupply, TRANSACTIONTYPE_SUPPLY, &info);
    }

    s.str("");
    s << "RelOO(ord=" << item.Order().KdAuftragNr() << ", pos=" << item.PosNr() << ", art="
      << item.ArtikelNr() << ", qty=" << qty << ") --> " << (qty - qtyToReduce);
    if (!pxGlobalNoDatabaseWrite) //! \note workaround to not log 
        BLOG_DEBUG(libcsc::LoggerPool::getLoggerStockBooking(), s.str());
    return (qty - qtyToReduce);
}

/***************************************************************************************************************************/

void pxStockBooking::InitContext(pxArtBase* article, pxCustBase* customer, pxOrderItem* orderitem, const bool readReservations /* = true*/)
{
    std::stringstream s;
    s << "pxStockBooking::InitContext(article = " << (article == NULL ? NULL : article->ArtikelNr())
      << ", pxCustBase* customer = " << (customer == NULL ? NULL : customer->IDFNr())
      << ", pxOrderItem* orderitem = " << (orderitem == NULL ? NULL : orderitem->KdAuftragNr()) << ")";
    BLOG_TRACE(libcsc::LoggerPool::getLoggerStockBooking(), s.str());

    ClearError();

    m_CurrentArticle    = dynamic_cast<IArticleStockBooking*>(article);
    m_CurrentCustomer   = customer;
    m_CurrentOrderItem  = orderitem;

    if (true == readReservations)
    {
        InitCustomerStockReservation();
        InitArticleReservation();
    }
}

/***************************************************************************************************************************/

void pxStockBooking::InitCustomerStockReservation()
{
    // now read all existing reservations for this context
    if (NULL != m_CustomerStockReservationList)
    {
        delete m_CustomerStockReservationList;
        m_CustomerStockReservationList = NULL;
    }

    m_CustomerStockReservationList = new pxCustStockReservedList(m_Session);
    if (NULL != m_CurrentCustomer)
    {
        m_CustomerStockReservationList->SelectCustomerReservations(
            m_CurrentArticle->FilialNr(),
            m_CurrentArticle->ArtikelNr(),
            m_CurrentCustomer->IDFNr());
    }
    else
    {
        m_CustomerStockReservationList->SelectAllReservations(
            m_CurrentArticle->FilialNr(),
            m_CurrentArticle->ArtikelNr());
    }

    if (!m_CustomerStockReservationList->IsGoodState())
    {
        Error() = m_CustomerStockReservationList->Error();
        BLOG_ERROR(libcsc::LoggerPool::getLoggerStockBooking(), ErrorMsg());
        delete m_CustomerStockReservationList;
        m_CustomerStockReservationList = NULL;
    }
}

/***************************************************************************************************************************/

void pxStockBooking::InitArticleReservation()
{
    if (NULL != m_ArticleReservationList)
    {
        delete m_ArticleReservationList;
        m_ArticleReservationList = NULL;
    }
    m_CurrentArticleReservation = NULL;
    m_CurrentReservationConfig.reset();

    m_ArticleReservationList = new pxArtReservationList(m_Session);
    m_ArticleReservationList->Select(
        m_CurrentArticle->FilialNr(),
        m_CurrentArticle->ArtikelNr());
    if (!m_ArticleReservationList->IsGoodState())
    {
        Error() = m_ArticleReservationList->Error();
        BLOG_ERROR(libcsc::LoggerPool::getLoggerStockBooking(), ErrorMsg());
        delete m_ArticleReservationList;
        m_ArticleReservationList = NULL;
        return;
    }

    // new begin
    if (m_CurrentOrderItem != NULL)
    {
        libcsc::stockbooking::IOrderTypeReservationConfigCollectionPtr reservationConfigList =
            m_Session->getStockBookingComponentManager()->getReservationConfigRepository()->
                findOrderTypeReservationConfig(m_CurrentOrderItem->Order().OrderType().KdAuftragArt()());

        // iterate through configured reservation types per order type
        if (NULL != reservationConfigList.get())
        {
            libcsc::stockbooking::IOrderTypeReservationConfigCollection::const_iterator it = reservationConfigList->begin();
            while (it != reservationConfigList->end())
            {
                // search for an articlereservation with matching reservtype
                pxArtReservation* articleReservation;
                articleReservation = m_ArticleReservationList->FindReservationType(static_cast<ReservationTypeEnum>((*it)->getReservationType()));
                if (NULL != articleReservation)
                {
                    if (true == (*it)->getWithPharmacyGroup())
                    {
                        if ((*it)->containsPharmacyGroup(articleReservation->GetPharmacyGroupId()))
                        {
                            m_CurrentArticleReservation = articleReservation;
                            m_CurrentReservationConfig = (*it);
                            break;
                        }
                    }
                    else
                    {
                        m_CurrentArticleReservation = articleReservation;
                        m_CurrentReservationConfig = (*it);
                        break;
                    }
                }
                else
                {
                    // no articlereservation found, but...
                    if (true == (*it)->getReservedStockOnly())
                    {
                        // ... nevertheless break here
                        m_CurrentReservationConfig = (*it);
                        break;
                    }
                }
                ++it;
            }
        }
    }
    // did we found a matching reservation?
    if (NULL != m_CurrentArticleReservation)
    {
        return;
    }
    // or is it only allowed to book from reserved stock?
    if (NULL != m_CurrentReservationConfig.get() && true == m_CurrentReservationConfig->getReservedStockOnly())
    {
        return;
    }
    // new end

    // check if article reservation exists for current customer
    pxArtReservation*           articleReservation;
    pxArtReservationListIter    iter(*m_ArticleReservationList);
    
    while (NULL != (articleReservation = (pxArtReservation*)++iter))
    {
        if (articleReservation->IsReserveForPharmGroup() || articleReservation->IsReserveNoSalesEffectiv())
        {
            if (NULL != m_CurrentCustomer)
            {
                pxCustPharmGroupList* phglist = m_CurrentCustomer->PharmGroupList();
                if (phglist != NULL && phglist->Find(articleReservation->GetPharmacyGroupId().c_str()) != NULL)
                {
                    m_CurrentArticleReservation = articleReservation;
                    break;
                }
            }
            else
            {
                m_CurrentArticleReservation = articleReservation;
                break;
            }
        }

        //if (articleReservation->IsReserveNoCertificate() || articleReservation->IsReserveNoPackageInsert())
        //{
        //    if (NULL != m_CurrentOrderItem && m_CurrentOrderItem->Order().OrderType().IsQuarantineOrder())
        //    {
        //        m_CurrentArticleReservation = articleReservation;
        //        break;
        //    }
        //}

        //if (articleReservation->IsReserveBatchRecall())
        //{
        //    if (NULL != m_CurrentOrderItem && m_CurrentOrderItem->Order().OrderType().IsChargeRecallOrder())
        //    {
        //        m_CurrentArticleReservation = articleReservation;
        //        break;
        //    }
        //}
        //if (articleReservation->GetReservType() == RESTYPE_TENDER)
        //{
        //    if (NULL != m_CurrentOrderItem && m_CurrentOrderItem->Order().isTenderOrder())
        //    {
        //        m_CurrentArticleReservation = articleReservation;
        //        break;
        //    }
        //}
    }
}

/***************************************************************************************************************************/

pxCustStockReserved* pxStockBooking::FindCustomerStockReservation(const enum ReservationTypeEnum reserveType)
{
    pxCustStockReserved* custStockReserved = NULL;

    if (m_CustomerStockReservationList != NULL)
    {
        pxCustStockReservedListIter iter(*m_CustomerStockReservationList);    // define iterator
        while (NULL != (custStockReserved = (pxCustStockReserved*)++iter)) // browse list
        {
            if (custStockReserved->ReservType() == reserveType)
            {
                break;
            }
        }
    }
    return custStockReserved;
}

/***************************************************************************************************************************/

pxCustStockReserved* pxStockBooking::FindCustomerStockReservation(const enum ReservationTypeEnum reserveType, const long orderno)
{
    pxCustStockReserved* custStockReserved = NULL;

    if (m_CustomerStockReservationList != NULL)
    {
        pxCustStockReservedListIter iter(*m_CustomerStockReservationList);    // define iterator
        while (NULL != (custStockReserved = (pxCustStockReserved*)++iter)) // browse list
        {
            if (custStockReserved->ReservType() == reserveType && custStockReserved->KdAuftragNr() == orderno)
            {
                break;
            }
        }
    }
    return custStockReserved;
}

/***************************************************************************************************************************/

bool pxStockBooking::CheckAndLockArticle()
{
    BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerStockBooking(), "pxStockBooking::CheckAndLockArticle()");

    if (NULL == m_CurrentArticle)
    {
        BLOG_ERROR(libcsc::LoggerPool::getLoggerStockBooking(), "NULL == m_CurrentArticle");
        return false;
    }
    if (false == pxGlobalNoDatabaseWrite)
    {
        if (0 != m_CurrentArticle->Get(cDBGET_FORUPDATE))
        {
            BLOG_TRACE(libcsc::LoggerPool::getLoggerStockBooking(), " 0 != m_CurrentArticle->Get(cDBGET_FORUPDATE)");
            return false;
        }
    }
    if (false == m_CurrentArticle->IsGoodState())
    {
         Error() = m_CurrentArticle->Error();
         BLOG_ERROR(libcsc::LoggerPool::getLoggerStockBooking(), ErrorMsg());
         return false;
    }
    BLOG_TRACE(libcsc::LoggerPool::getLoggerStockBooking(), "m_CurrentArticle->Get(cDBGET_FORUPDATE) successful");
    return true;
}

/***************************************************************************************************************************/

bool pxStockBooking::CheckAndLockArticleReservation()
{
    BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerStockBooking(), "pxStockBooking::CheckAndLockArticleReservation()");

    if (NULL == m_CurrentArticleReservation)
    {
        BLOG_TRACE(libcsc::LoggerPool::getLoggerStockBooking(), "NULL == m_CurrentArticleReservation");
        return false;
    }
    if (false == pxGlobalNoDatabaseWrite)
    {
        if (0 != m_CurrentArticleReservation->Get(cDBGET_FORUPDATE))
        {
            BLOG_ERROR(libcsc::LoggerPool::getLoggerStockBooking(), "0 != m_CurrentArticleReservation->Get(cDBGET_FORUPDATE)");
            return false;
        }
    }
    if (!m_CurrentArticleReservation->IsGoodState())
    {
        Error() = m_CurrentArticleReservation->Error();
        BLOG_ERROR(libcsc::LoggerPool::getLoggerStockBooking(), ErrorMsg());
        return false;
    }
    BLOG_TRACE(libcsc::LoggerPool::getLoggerStockBooking(), "CurrentArticleReservation_->Get(cDBGET_FORUPDATE) successful");
    return true;
}

/***************************************************************************************************************************/

long pxStockBooking::AddCustomerStockReservation(const long qty, const enum ReservationTypeEnum reserveType)
{
    return AddCustomerStockReservation(
        m_CurrentArticle->FilialNr(),
        m_CurrentArticle->ArtikelNr(),
        m_CurrentCustomer->KundenNr(),
        qty,
        reserveType);
}

long pxStockBooking::AddCustomerStockReservation(const short branchno, const long articleno, const long customerno, const long qty, const enum ReservationTypeEnum reserveType)
{
    basar::DateTime         reservationStartDT = basar::DateTime::getCurrent();
    long                    qtyToReserve = qty;
    long                    reservedQty = 0;
    pxCustStockReserved*    custStockReserved = NULL;

    // if we have an order context, search for appropriate order reservation
    if (NULL != m_CurrentOrderItem && (RESTYPE_OPENORDER_RESERVED == reserveType || RESTYPE_OPENORDER_FREE == reserveType))
    {
        custStockReserved = FindCustomerStockReservation(reserveType, m_CurrentOrderItem->KdAuftragNr());
    }
    else
    {
        custStockReserved = FindCustomerStockReservation(reserveType);
    }

    if (NULL == custStockReserved)
    {
        // construct new pxCustStockReserved object
        custStockReserved = new pxCustStockReserved(
            m_Session,
            branchno,
            customerno,
            articleno,
            reservationStartDT,
            reserveType);
        m_CustomerStockReservationList->Append(custStockReserved);
    }

    reservedQty = custStockReserved->AddQuantity(qtyToReserve);

    // if we have an order context, set order number
    if (NULL != m_CurrentOrderItem)
    {
        custStockReserved->SetKdAuftragNr(m_CurrentOrderItem->KdAuftragNr());
    }

    // reservation for info order -> evaluate reserve period parameter
    if (reserveType == RESTYPE_INFOORDER_FREE || reserveType == RESTYPE_INFOORDER_RESERVED)
    {
        short reserveTimeInMinutes = m_Session->getOrderEntryParam(branchno)->ReservePeriod();
        basar::TimeSpan reserationTimeSpan;
        reserationTimeSpan.fromNumeric(reserveTimeInMinutes, basar::TimeSpan::TSUNIT_MIN);
        basar::DateTime reservationEndDT = reservationStartDT + reserationTimeSpan;
        custStockReserved->SetDateTimeTo(reservationEndDT);
    }

    custStockReserved->Put();               // update entry
    if (!custStockReserved->IsGoodState())
    {
        Error() = custStockReserved->Error();
        BLOG_ERROR(libcsc::LoggerPool::getLoggerStockBooking(), ErrorMsg());
        return 0L; // no reservation!
    }

    return reservedQty;
}

/***************************************************************************************************************************/

long pxStockBooking::ReduceCustomerStockReservation(const long qty, const enum ReservationTypeEnum reserveType)
{
    long qtyReduced = 0;
    pxCustStockReserved* custStockReserved = NULL;

    // if we have an order context, search for appropriate order reservation
    if (NULL != m_CurrentOrderItem && (RESTYPE_OPENORDER_RESERVED == reserveType || RESTYPE_OPENORDER_FREE == reserveType))
    {
        custStockReserved = FindCustomerStockReservation(reserveType, m_CurrentOrderItem->KdAuftragNr());
    }
    else
    {
        custStockReserved = FindCustomerStockReservation(reserveType);
    }

    if (NULL != custStockReserved)
    {
        qtyReduced = custStockReserved->SubQuantity(qty);
        if (custStockReserved->ReservedQty() == 0)
        {
            custStockReserved->Delete();
            if (!custStockReserved->IsGoodState())
            {
                Error() = custStockReserved->Error();
                BLOG_ERROR(libcsc::LoggerPool::getLoggerStockBooking(), ErrorMsg());
            }
            m_CustomerStockReservationList->Remove(custStockReserved);
            delete custStockReserved;
        }
        else
        {
            custStockReserved->Put();
            if (!custStockReserved->IsGoodState())
            {
                Error() = custStockReserved->Error();
                BLOG_ERROR(libcsc::LoggerPool::getLoggerStockBooking(), ErrorMsg());
            }
        }
    }
    if (!IsGoodState())
    {
        qtyReduced = 0L;
    }
    return qtyReduced;
}

/***************************************************************************************************************************/

long pxStockBooking::GetReservedQty(const enum GlobalReservationType reservationType)
{
    long qty = 0L;
    pxCustStockReserved* custStockReserved;
    
    switch (reservationType)
    {
        case GLOBAL_RESTYPE_INFOORDER :
            if (NULL != (custStockReserved = FindCustomerStockReservation(RESTYPE_INFOORDER_FREE)))
            {
                qty +=custStockReserved->ReservedQty();
            }
            if (NULL != (custStockReserved = FindCustomerStockReservation(RESTYPE_INFOORDER_RESERVED)))
            {
                qty +=custStockReserved->ReservedQty();
            }
            break;
        case GLOBAL_RESTYPE_RESTDELIVERY :
            if (NULL != (custStockReserved = FindCustomerStockReservation(RESTYPE_RESTDELIVERY_FREE)))
            {
                qty +=custStockReserved->ReservedQty();
            }
            if (NULL != (custStockReserved = FindCustomerStockReservation(RESTYPE_RESTDELIVERY_RESERVED)))
            {
                qty +=custStockReserved->ReservedQty();
            }
            break;
        case GLOBAL_RESTYPE_IBT :
            if (NULL != (custStockReserved = FindCustomerStockReservation(RESTYPE_IBT_FREE)))
            {
                qty +=custStockReserved->ReservedQty();
            }
            if (NULL != (custStockReserved = FindCustomerStockReservation(RESTYPE_IBT_RESERVED)))
            {
                qty +=custStockReserved->ReservedQty();
            }
            break;
        case GLOBAL_RESTYPE_OPENORDER :
            if (NULL != (custStockReserved = FindCustomerStockReservation(RESTYPE_OPENORDER_FREE)))
            {
                qty +=custStockReserved->ReservedQty();
            }
            if (NULL != (custStockReserved = FindCustomerStockReservation(RESTYPE_OPENORDER_RESERVED)))
            {
                qty +=custStockReserved->ReservedQty();
            }
            break;
    }
    return qty;
}

/***************************************************************************************************************************/

pxArtReservation* pxStockBooking::findArticleReservation(const enum ReservationTypeEnum type)
{
    pxArtReservation* reservation = NULL;

    if (m_ArticleReservationList != NULL)
    {
        pxArtReservationListIter iter(*m_ArticleReservationList);    // define iterator
        while (NULL != (reservation = (pxArtReservation*)++iter)) // browse list
        {
            if (reservation->GetReservType() == type)
            {
                std::stringstream s;
                s << "search for reservationtype " << type << ", found reservationtype " << reservation->GetReservType();
                BLOG_TRACE(libcsc::LoggerPool::getLoggerStockBooking(), s.str());
                return reservation;
            }
        }
    }
    return NULL;
}

/***************************************************************************************************************************/

long pxStockBooking::CreateEmptyArticleReservation(pxArtBase& article, const ReservationTypeEnum restype, const basar::VarString& pharmacygroup, const long maxqty, const short reservepct)
{
    BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerStockBooking(), "pxStockBooking::CreateEmptyArticleReservation()");

    InitContext(&article);

    pxArtReservation* reservation = new pxArtReservation(m_Session, m_CurrentArticle->FilialNr(), m_CurrentArticle->ArtikelNr());
    reservation->SetReservType(restype);
    reservation->SetReservePct(reservepct);
    reservation->SetMaxQty(maxqty);
    reservation->SetPharmacyGroupId(pharmacygroup);
    m_ArticleReservationList->Append(reservation);
    reservation->Put();

    if (!reservation->IsGoodState())
    {
        Error() = reservation->Error();
        BLOG_ERROR(libcsc::LoggerPool::getLoggerStockBooking(), ErrorMsg());
    }
    return 0L;
}

/***************************************************************************************************************************/

long pxStockBooking::DeleteArticleReservation(pxArtBase& article, const ReservationTypeEnum restype, const basar::VarString& pharmacygroup)
{
    BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerStockBooking(), "pxStockBooking::DeleteArticleReservation()");

    InitContext(&article);

    pxArtReservation* reservation = findArticleReservation(restype);
    if (NULL != reservation)
    {
        if (reservation->GetReservedQty() > 0 && 0 == reservation->GetReservePct())
        {
            //In case of absolutely amount reservation is already deleted by 
            ReleaseArticleReservation(article, restype, pharmacygroup, reservation->GetReservedQty());
        }
        else
        {	
            //In case of other reservations we have to delete it
            if (reservation->GetReservedQty() > 0)
            {
                ReleaseArticleReservation(article, restype, pharmacygroup, reservation->GetReservedQty());
            }
            reservation = findArticleReservation(restype);	//Liste in ReleaseArticleReservation mittels InitContext überschieben
            reservation->Delete();
            if (!reservation->IsGoodState())
            {
                Error() = reservation->Error();
                BLOG_ERROR(libcsc::LoggerPool::getLoggerStockBooking(), ErrorMsg());
            }
            m_ArticleReservationList->Remove(reservation);
            delete reservation;
        }
    }
    return 0L;
}

/***************************************************************************************************************************/

long pxStockBooking::AddArticleReservation(pxArtBase& article, const ReservationTypeEnum restype, const basar::VarString& pharmacygroup, const long qty)
{
    std::stringstream s;
    s << "pxStockBooking::AddArticleReservation(pxArtBase* article = " << article.ArtikelNr()
      << ", ReservationType = " << restype << ", pharmacygroup = " << pharmacygroup << ", qty = " << qty << ")";
    BLOG_TRACE(libcsc::LoggerPool::getLoggerStockBooking(), s.str());

    long qtyReserved = 0L;
    long qty2reserve = qty;

    InitContext(&article);
    if (CheckAndLockArticle())
    {
        pxArtReservation* reservation = findArticleReservation(restype);
        if (NULL == reservation)
        {
            reservation = new pxArtReservation(m_Session, m_CurrentArticle->FilialNr(), m_CurrentArticle->ArtikelNr());
            reservation->SetReservType(restype);
            reservation->SetPharmacyGroupId(pharmacygroup);
            m_ArticleReservationList->Append(reservation);
        }
        if (reservation->GetReservType() == RESTYPE_PHARMACYGROUP)
        {
            if (qty2reserve > reservation->GetMaxQty()) qty2reserve = reservation->GetMaxQty();
        }
        qtyReserved = m_CurrentArticle->SubQuantity(qty2reserve);
        m_CurrentArticle->Put();
        if (!m_CurrentArticle->IsGoodState())
        {
            Error() = m_CurrentArticle->Error();
            BLOG_ERROR(libcsc::LoggerPool::getLoggerStockBooking(), ErrorMsg());
        }
        if (IsGoodState())
        {
            reservation->AddReservedQuantity(qtyReserved);
            reservation->Put();
            if (!reservation->IsGoodState())
            {
                Error() = reservation->Error();
                BLOG_ERROR(libcsc::LoggerPool::getLoggerStockBooking(), ErrorMsg());
            }
        }
        if (!IsGoodState())
        {
            qtyReserved = 0L;
        }
    }

    if (qtyReserved > 0)
    {
        struct ArticleAccountInfo info;
        info.MoveType = restype;
        WriteArticleAccount(qtyReserved, TRANSACTIONTYPE_RESERVATION, &info);
    }
    return qtyReserved;
}

/***************************************************************************************************************************/

long pxStockBooking::ReleaseArticleReservation(pxArtBase& article, const ReservationTypeEnum restype, const basar::VarString& pharmacygroup, const long qty)
{
    std::stringstream s;
    s << "pxStockBooking::ReleaseArticleReservation(pxArtBase* article = " << article.ArtikelNr()
      << ", ReservationType = " << restype << ", pharmacygroup = " << pharmacygroup << ", qty = " << qty << ")";
    BLOG_TRACE(libcsc::LoggerPool::getLoggerStockBooking(), s.str());

    long qtyReleased = 0L;

    InitContext(&article);
    if (CheckAndLockArticle())
    {
        pxArtReservation* reservation = findArticleReservation(restype);
        if (NULL != reservation)
        {
            qtyReleased = reservation->SubReservedQuantity(qty);
            if (0 == reservation->GetReservedQty() && 0 == reservation->GetReservePct())
            {
                reservation->Delete();
                if (!reservation->IsGoodState())
                {
                    Error() = reservation->Error();
                    BLOG_ERROR(libcsc::LoggerPool::getLoggerStockBooking(), ErrorMsg());
                }
                m_ArticleReservationList->Remove(reservation);
                if (m_CurrentArticleReservation == reservation)
                {
                    m_CurrentArticleReservation = NULL;
                }
                delete reservation;
            }
            else
            {
                reservation->Put();
                if (!reservation->IsGoodState())
                {
                    Error() = reservation->Error();
                    BLOG_ERROR(libcsc::LoggerPool::getLoggerStockBooking(), ErrorMsg());
                }
            }

            if (IsGoodState())
            {
                m_CurrentArticle->AddQuantity(qtyReleased);
                m_CurrentArticle->Put();
                if (!m_CurrentArticle->IsGoodState())
                {
                    Error() = m_CurrentArticle->Error();
                    BLOG_ERROR(libcsc::LoggerPool::getLoggerStockBooking(), ErrorMsg());
                }
            }
            if (!IsGoodState())
            {
                qtyReleased = 0L;
            }
        }
    }

    if (qtyReleased > 0)
    {
        struct ArticleAccountInfo info;
        info.MoveType = restype;
        WriteArticleAccount((qtyReleased * -1), TRANSACTIONTYPE_RESERVATION, &info);
    }
    return qtyReleased;
}

/***************************************************************************************************************************/

long pxStockBooking::SetAbsoluteArticleReservation(pxArtBase& article, const ReservationTypeEnum restype, const basar::VarString& pharmacygroup, const long qty)
{
    std::stringstream s;
    s << "pxStockBooking::SetAbsoluteArticleReservation(pxArtBase* article = " << article.ArtikelNr()
      << ", ReservationType = " << restype << ", pharmacygroup = " << pharmacygroup << ", qty = " << qty << ")";
    BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerStockBooking(), s.str());

    long qtyReserved = 0L;

    InitContext(&article);
    if (CheckAndLockArticle())
    {
        pxArtReservation* reservation = findArticleReservation(restype);
        if (NULL == reservation)
        {
            if (qty == 0L)                                      // nothing to do
            {
                BLOG_TRACE(libcsc::LoggerPool::getLoggerStockBooking(), "nothing to do");
                return 0L;
            }
            BLOG_TRACE(libcsc::LoggerPool::getLoggerStockBooking(), "new pxArtReservation");
            reservation = new pxArtReservation(m_Session, m_CurrentArticle->FilialNr(), m_CurrentArticle->ArtikelNr());
            reservation->SetReservType(restype);
            reservation->SetPharmacyGroupId(pharmacygroup);
            m_ArticleReservationList->Append(reservation);
        }

        if (qty == reservation->GetReservedQty())                  // nothing to do
        {
            BLOG_TRACE(libcsc::LoggerPool::getLoggerStockBooking(), "nothing to do");
            return 0L;
        }
        else if (qty > reservation->GetReservedQty())              // reserve more
        {
            long qtyToAdd = qty - reservation->GetReservedQty();
            s.str("");
            s << "reserve more " << qtyToAdd << " on restype " << reservation->GetReservType();
            BLOG_TRACE(libcsc::LoggerPool::getLoggerStockBooking(), s.str());
            qtyReserved = m_CurrentArticle->SubQuantity(qtyToAdd);
            reservation->AddReservedQuantity(qtyReserved);
        }
        else                                                    // reserve less
        {
            long qtyToSubtract = reservation->GetReservedQty() - qty;
            s.str("");
            s << "reserve less " << qtyToSubtract << " on restype " << reservation->GetReservType();
            BLOG_TRACE(libcsc::LoggerPool::getLoggerStockBooking(), s.str());
            long qtySubtracted = reservation->SubReservedQuantity(qtyToSubtract);
            m_CurrentArticle->AddQuantity(qtySubtracted);
            qtyReserved = (qtySubtracted * -1);
        }
        m_CurrentArticle->Put();
        if (!m_CurrentArticle->IsGoodState())
        {
            Error() = m_CurrentArticle->Error();
            BLOG_ERROR(libcsc::LoggerPool::getLoggerStockBooking(), ErrorMsg());
        }
        reservation->Put();
        if (!reservation->IsGoodState())
        {
            Error() = reservation->Error();
            BLOG_ERROR(libcsc::LoggerPool::getLoggerStockBooking(), ErrorMsg());
        }
        if (!IsGoodState())
        {
            qtyReserved = 0L;
        }
    }
    
    if (qtyReserved != 0) // attention qtyReserved might be negative!!!
    {
        struct ArticleAccountInfo info;
        info.MoveType = restype;
        WriteArticleAccount(qtyReserved, TRANSACTIONTYPE_RESERVATION, &info);
    }
    return qtyReserved;
}

/***************************************************************************************************************************/

void pxStockBooking::WriteArticleAccount(const long qty, const TransactionType transactiontype, const struct ArticleAccountInfo* info)
{
    BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerStockBooking(), "pxStockBooking::WriteArticleAccount()");

    pxArtAccount acct(m_Session, static_cast<char>(transactiontype));
    if (NULL != m_CurrentArticle)
    {
        acct.FilialNr(m_CurrentArticle->FilialNr());
        acct.ArtikelNr(m_CurrentArticle->ArtikelNr());
        acct.MengeNeu(m_CurrentArticle->GetQuantity());
        acct.StockReserved(0);
    }
    else
    {
        acct.FilialNr(info->BranchNo);
        acct.ArtikelNr(info->ArticleNo);
        acct.MengeNeu(0);
        acct.StockReserved(0);
    }
    if (NULL != m_CurrentCustomer)
    {
        acct.IDFNr(m_CurrentCustomer->IDFNr());
    }
    else
    {
        acct.IDFNr(info->CustomerSupplierNo);
    }

    acct.Menge(qty);
    acct.TransActionKey(info->StockTransaction, info->CommiType);
    acct.BelegNr(info->PurchaseOrderNo);
    acct.Uid(m_Session->PersonnelNo());
    acct.MoveType(info->MoveType);
    acct.PosNr(info->PositionNo);
    acct.BelegArt(info->BelegArt.c_str());
    acct.Put();
    if (!acct.IsGoodState())
    {
        Error() = acct.Error();
        BLOG_ERROR(libcsc::LoggerPool::getLoggerStockBooking(), ErrorMsg());
    }
}

/***************************************************************************************************************************/

PURCHASE_RELEVANCE_MODE	pxStockBooking::GetPurchaseRelevanceMode()
{
    BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerStockBooking(), "pxStockBooking::GetPurchaseRelevanceMode()");

    PURCHASE_RELEVANCE_MODE mode = PRM_UNKNOWN;

    if (NULL == m_CurrentOrderItem)
    {
        return mode;
    }

    if (!m_CurrentOrderItem->Order().Param()->IsNlevelIBT())
    {
        return mode;
    }

    pxIBTType* ibtType = m_Session->IBTTypeList()->Find(m_CurrentOrderItem->getNLevelIBTTypeID()); // NLevelIBT -> Abverkaufswirksamkeit Artikelkonto
    if (NULL != ibtType)
    {
        mode = ibtType->PurchaseRelevanceMode();
    }
    return mode;
}

/***************************************************************************************************************************/
