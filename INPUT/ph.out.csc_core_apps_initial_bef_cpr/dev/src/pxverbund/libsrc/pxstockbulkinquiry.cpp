#include "pxstockbulkinquiry.hpp"
#include "pxstockbooking.hpp"
#include "pxsess.hpp"
#include "pxcstbas.hpp"
#include "pxartbas.hpp"
#include "pxvartikellokal.hpp"
#include "pxvartikellokallist.hpp"
#include "pxarticlecodes.hpp"
#include "pxarticlecharge.hpp"
#include "pxartreservation.hpp"
#include "stockbooking/componentmanager/stockbookingcomponentmanager.h"
#include "stockbooking/longtermlack/ilongtermlackchecker.h"
#include <logger/loggerpool.h>

/***************************************************************************************************************************/

pxStockBulkInquiry::pxStockBulkInquiry(pxSession* session) : pxErrorLoggable(),
    m_Session(session),
    m_Booking(session->getStockBooking()),
    m_BranchNo(0),
    m_Customer(NULL),
    m_ArticleChargeList(NULL),
    m_ArticleReservationList(NULL)
{
}

/***************************************************************************************************************************/

pxStockBulkInquiry::~pxStockBulkInquiry()
{
    if (m_Customer != NULL)
    {
        delete m_Customer;
        m_Customer = NULL;
    }

    if (m_ArticleChargeList != NULL)
    {
        delete m_ArticleChargeList;
        m_ArticleChargeList = NULL;
    }

    if (m_ArticleReservationList != NULL)
    {
        delete m_ArticleReservationList;
        m_ArticleReservationList = NULL;
    }

    m_Session = NULL;
}

/***************************************************************************************************************************/

void pxStockBulkInquiry::setBranchAndCustomer(const basar::Int16 branchNo, const basar::Int32 customerNo)
{
    std::stringstream ss;
    ss << "pxStockBulkInquiry::setBranchAndCustomer(branchno=" << branchNo << ", customerNo=" << customerNo << ")";
    BLOG_DEBUG(libcsc::LoggerPool::getLoggerSession(), ss.str());

    m_BranchNo = branchNo;
    if (NULL != m_Customer)
    {
        delete m_Customer;
        m_Customer = NULL;
    }
    if (customerNo > 0)
    {
        m_Customer = new pxCustBase(m_Session, branchNo, customerNo);
        if (false == m_Customer->IsGoodState())
        {
            Error() = m_Customer->Error();
            BLOG_ERROR(libcsc::LoggerPool::getLoggerStockBooking(), ErrorMsg());
        }
    }
}

/***************************************************************************************************************************/

basar::VarString pxStockBulkInquiry::getArticleAvailability(const basar::VarString& queryString)
{
    basar::VarString result;
    basar::cmnutil::CollBString queryArticles = queryString.tokenizeAndTrim(";", basar::cmnutil::BString::FIRST_END, true, true);
    basar::cmnutil::CollBString resultArticles = getArticleAvailabilityColl(queryArticles);

    basar::cmnutil::CollBString::iterator it = resultArticles.begin();
    while (it != resultArticles.end())
    {
        if (result.length() + (*it).length() <= MAX_OUTPUT_LEN)
        {
            result += *it;
        }
        ++it;
    }

    std::stringstream ss;
    ss << "pxStockBulkInquiry::getAvailableArticles(branchno=" << m_BranchNo << ", customerNo=" << (m_Customer != NULL ? m_Customer->IDFNr() : 0)
        << ") articles in: " << queryArticles.size() << ", articles out: " << resultArticles.size();
    BLOG_INFO(libcsc::LoggerPool::getLoggerStockBooking(), ss.str());
    return result;
}

/***************************************************************************************************************************/

basar::cmnutil::CollBString pxStockBulkInquiry::getArticleAvailabilityColl(const basar::cmnutil::CollBString& queryArticles)
{
    basar::cmnutil::CollBString resultArticles;
    basar::cmnutil::CollBString::const_iterator it;

    for (it = queryArticles.begin(); it != queryArticles.end(); ++it)
    {
        bool available = getArticleAvailabilitySingle((*it));
        if (true == available)
        {
            std::stringstream ss;
            ss << (*it) << ";";
            resultArticles.push_back(ss.str());
        }
    }
    return resultArticles;
}

bool pxStockBulkInquiry::getArticleAvailabilitySingle(const basar::VarString& articleCode) // public for Thrift
{
    basar::Int32 articleNo = convertArticleCodeToArticleNo(articleCode);
    if (0 == articleNo)
    {
        return false;
    }

    // determine local stock
    boost::shared_ptr<pxArtBase> article = boost::shared_ptr<pxArtBase>(pxArtBase::CreateArticle(m_Session, articleNo, m_BranchNo));
    if (false == article->IsGoodState())
    {
        return false;
    }

    //check if article is longtermlack
    if (m_Session->getStockBookingComponentManager()->getLongTermLackChecker()->isLongTermLack(articleNo))
    {
        return false;
    }

    if (NULL == m_Customer) // check only local stock
    {
        return (m_Booking->GetAvailableQtyInStock(*article) > 0);
    }

    // customer context: check local and ibt stock
    if (m_Booking->GetAvailableQtyInStock(*article, *m_Customer) > 0)
    {
        return true;
    }

    // determine IBT stock
    if (true == m_Customer->IsNotAuxDeliveryUser() || true == m_Customer->IsNeverAuxDeliveryUser())
    {
        return false;
    }

    pxVartikelLokalList ibtList(m_Session, m_Session->getOrderEntryParam(m_BranchNo));
    ibtList.getIBTWarehouseStockListWithoutTimeCheck(articleNo, m_BranchNo, m_Customer->IDFNr(), NULL );

    pxVartikelLokal* stp = ibtList.QuantityInList(INT_MAX);
    if (NULL != stp)
    {
        return (stp->Bestand() > 0);
    }
    return false;
}

/***************************************************************************************************************************/

basar::Int32 pxStockBulkInquiry::convertArticleCodeToArticleNo(const basar::VarString& articlecode)
{
    pxArticleCodes ArtCode(m_Session, articlecode.c_str());
    if (ArtCode.Get())
    {
        return 0;
    }
    return ArtCode.ArticleNo();
}

/***************************************************************************************************************************/

basar::VarString pxStockBulkInquiry::getArticleStock(const basar::VarString& queryString)
{
    basar::VarString result;
    basar::cmnutil::CollBString queryArticles = queryString.tokenizeAndTrim(";", basar::cmnutil::BString::FIRST_END, true, true);
    basar::cmnutil::CollBString resultArticles = getArticleStockColl(queryArticles);

    basar::cmnutil::CollBString::iterator it = resultArticles.begin();
    while (it != resultArticles.end())
    {
        if (result.length() + (*it).length() <= MAX_OUTPUT_LEN)
        {
            result += *it;
        }
        ++it;
    }

    return result;
}

/***************************************************************************************************************************/

basar::cmnutil::CollBString pxStockBulkInquiry::getArticleStockColl(const basar::cmnutil::CollBString& queryArticles)
{
    basar::cmnutil::CollBString resultArticles;
    basar::VarString            articleCode;
    basar::Int32                qtyInStock;
    std::stringstream           ss;
    basar::UInt32               retLen = 0;

    basar::cmnutil::CollBString::const_iterator it;
    for (it = queryArticles.begin(); it != queryArticles.end(); ++it)
    {
        ClearError();
        ss.str("");

        articleCode = (*it);
        qtyInStock = getArticleStockSingle(articleCode);

        ss << articleCode << ";" << qtyInStock << ";";
        retLen += static_cast<basar::UInt32>(ss.str().length());

        if (retLen <= MAX_OUTPUT_LEN)
        {
            resultArticles.push_back(ss.str());
        }
        else
        {
            ss.str("");
            ss << "input data too long, cutting at article " << articleCode;
            ExternalCondition(ss.str().c_str(), ERR_OUTPUT_TOO_LONG);
            BLOG_WARN(libcsc::LoggerPool::getLoggerStockBooking(), ErrorMsg());
            break;
        }
    }
    return resultArticles;
}


basar::Int32 pxStockBulkInquiry::getArticleStockSingle(const basar::VarString& articleCode)
{
    basar::Int32    articleNo;
    basar::Int32    qtyInStock;

    qtyInStock = -1;

    articleNo = convertArticleCodeToArticleNo(articleCode);

    if (articleNo > 0)
    {
        // determine local stock
        pxArtBase* article = pxArtBase::CreateArticle(m_Session, articleNo, m_BranchNo);
        if (article->IsGoodState())
        {
            if (NULL != m_Customer)
            {
                qtyInStock = m_Booking->GetAvailableQtyInStock(*article, *m_Customer);
            }
            else
            {
                qtyInStock = m_Booking->GetAvailableQtyInStock(*article);
            }
        }
        delete article;
    }
    return qtyInStock;
}

pxArticleChargeList* pxStockBulkInquiry::getArticleStockBatchSingle(const basar::VarString& articleCode)
{
    basar::Int32    articleNo;

    if (m_ArticleChargeList == NULL)
    {
        m_ArticleChargeList = new pxArticleChargeList(m_Session);
    }

    articleNo = convertArticleCodeToArticleNo(articleCode);

    if (articleNo > 0)
    {
        m_ArticleChargeList->Select(m_BranchNo, articleNo);
    }
    return m_ArticleChargeList;
}

pxArtReservationList* pxStockBulkInquiry::getArticleReservationListSingle(const basar::VarString& articleCode)
{
    basar::Int32    articleNo;

    if (m_ArticleReservationList == NULL)
    {
        m_ArticleReservationList = new pxArtReservationList(m_Session);
    }

    articleNo = convertArticleCodeToArticleNo(articleCode);

    if (articleNo > 0)
    {
        m_ArticleReservationList->Select(m_BranchNo, articleNo);
    }
    return m_ArticleReservationList;
}
