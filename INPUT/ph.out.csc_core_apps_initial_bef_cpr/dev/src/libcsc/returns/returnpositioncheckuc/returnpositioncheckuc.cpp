#include "returnpositioncheckuc.h"
#include <returns/returnrulebook/returnrulebookptr.h>
#include <returns/returnrulebook/returnrulebook.h>
#include <returns/returnrulebook/ireturnrulebookrepository.h>
#include <returns/returnperiod/ireturnperiodrepository.h>
#include <returns/returnperiod/returnperiodarticletypeenum.h>
#include <returns/returnperiod/returnperiod.h>
#include <returns/returnannouncement/returnannouncementptr.h>
#include <returns/returnannouncement/returnannouncement.h>
#include <returns/returnannouncement/returnannouncementhead/returnannouncementheadptr.h>
#include <returns/returnannouncement/returnannouncementhead/returnannouncementhead.h>
#include <returns/returnannouncement/returnannouncementpos/returnannouncementposptr.h>
#include <returns/returnannouncement/returnannouncementpos/returnannouncementpos.h>
#include <document/deliveryadvice/deliveryadvicerepository.h>
#include <document/deliveryadvice/deliveryadviceinformationfilter.h>
#include <document/deliveryadvice/deliveryadvice.h>
#include <document/deliveryadvice/deliveryadviceline/deliveryadviceline.h>
#include <document/deliveryadvice/deliveryadviceline/deliveryadvicelinereturn.h>
#include <document/deliveryadvice/deliveryadviceline/deliveryadvicelinedetails.h>
#include <workingdayscalendar/iworkingdayscalendarrepositoryptr.h>
#include <workingdayscalendar/iworkingdayscalendarrepository.h>
#include <cscordertype/componentmanager/cscordertypecomponentmanagerptr.h>
#include <cscordertype/componentmanager/cscordertypecomponentmanager.h>
#include <cscordertype/repository/icscordertyperepositoryptr.h>
#include <cscordertype/repository/icscordertyperepository.h>
#include <cscordertype/icscordertype.h>
#include <libbasarcmnutil_date.h>
#include <date.hpp>
#include "pxxmldefs.h"
#include "pxbase/pxconstants.hpp"
#include "pxartbas.hpp"
#include "pxartprc.hpp"
#include "tourmanager.hpp"

namespace libcsc {
namespace returns {

ReturnPositionCheckUC::ReturnPositionCheckUC()
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerReturns(), "ReturnPositionCheckUC::ReturnPositionCheckUC()");

    m_HighPriceLimit = basar::Decimal(0.0);
}

ReturnPositionCheckUC::~ReturnPositionCheckUC()
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerReturns(), "ReturnPositionCheckUC::~ReturnPositionCheckUC()");
}

void ReturnPositionCheckUC::injectReturnRuleBookRepository(IReturnRuleBookRepositoryPtr rulebook)
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerReturns(), "ReturnPositionCheckUC::injectReturnRuleBookRepository()");

    m_ReturnRuleBookRepository = rulebook;
}

void ReturnPositionCheckUC::injectReturnPeriodRepository(IReturnPeriodRepositoryPtr repo)
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerReturns(), "ReturnPositionCheckUC::injectReturnPeriodRepository()");

    m_ReturnPeriodRepository = repo;
}

void ReturnPositionCheckUC::injectDeliveryAdviceRepository(document::DeliveryAdviceRepositoryPtr repo)
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerReturns(), "ReturnPositionCheckUC::injectDeliveryAdviceRepository()");

    m_DeliveryAdviceRepository = repo;
}

void ReturnPositionCheckUC::injectWorkingdaysCalendarRepository(workingdayscalendar::IWorkingdaysCalendarRepositoryPtr repo)
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerReturns(), "ReturnPositionCheckUC::injectWorkingdaysCalendarRepository()");

    m_WorkingdaysCalendarRepository = repo;
}


void ReturnPositionCheckUC::injectHighPriceLimit(const basar::Decimal& limit)
{
    m_HighPriceLimit = limit;
}

void ReturnPositionCheckUC::injectSession(pxSession* sess)
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerReturns(), "ReturnPositionCheckUC::injectSession()");

    m_Session = sess;
}

void ReturnPositionCheckUC::setReturnAnnouncement(ReturnAnnouncementPtr returnAnnouncement)
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerReturns(), "ReturnPositionCheckUC::setReturnAnnouncement()");

    m_ReturnAnnouncement = returnAnnouncement;
}

ReturnAnnouncementPtr ReturnPositionCheckUC::getReturnAnnouncement() const
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerReturns(), "ReturnPositionCheckUC::getReturnAnnouncement()");

    return m_ReturnAnnouncement;
}

void ReturnPositionCheckUC::checkPosition(ReturnAnnouncementPosPtr pos)
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerReturns(), "ReturnPositionCheckUC::checkPosition()");

    pxArtBasePtr article = pxArtBasePtr(pxArtBase::CreateArticle(m_Session, pos->getArticleNo(), m_ReturnAnnouncement->getBranchNo()));
    basar::VarString reasonCode = pos->getReturnReasonCode();
    basar::VarString defaultAccCheckResult;

    libcsc::document::DeliveryAdvicePtr deliveryAdvice = findDeliveryAdvice(pos);
    if (NULL != deliveryAdvice.get())
    {
        pos->setDeliveryAdviceDate(deliveryAdvice->getDeliveryAdviceDate());
    }

    ReturnRuleBookCollectionPtr ruleBook = m_ReturnRuleBookRepository->findReturnRuleBook(reasonCode);
    ReturnRuleBookCollection::const_iterator it = ruleBook->begin();
    if (it != ruleBook->end())
    {
        defaultAccCheckResult = (*it)->getDefaultAccCheckResultCode();
    }
    while (it != ruleBook->end())
    {
        if (matchesRule(pos, (*it), article))
        {
            basar:: VarString accCheckResult = (*it)->getAccCheckResultCode();
            pos->setFailedCheckId((*it)->getReturnAccCheckId());
            pos->setFailedCheckString((*it)->getReturnAccCheckDescription());
            insertPosition(accCheckResult, pos);
            return;
        }
        ++it;
    }

    // if no rule matches: use default check result
    insertPosition(defaultAccCheckResult, pos);
}

void ReturnPositionCheckUC::insertPosition(const basar::VarString& accCheckResult, ReturnAnnouncementPosPtr pos)
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerReturns(), "ReturnPositionCheckUC::insertPosition()");

    ReturnAnnouncementHeadPtr head = m_ReturnAnnouncement->getAddHead(accCheckResult);
    TourInfo info = TourManager::determineReturnsTour(m_Session, m_ReturnAnnouncement->getBranchNo(), m_ReturnAnnouncement->getCustomerNo());
    head->addPosition(pos);
    pos->setPosNo(static_cast<basar::Int32>(head->getPositions()->size()));

    head->setDocumentId("");
    if ("RA" == accCheckResult || "RR" == accCheckResult || "RK" == accCheckResult)
    {
        head->setDocumentId(generateUUID()); // GUID erzeugen, wenn akzeptiert...
    }
    head->setTourDepartureDate(info.getTourDepartureDateTimeNormalized().GetYYYYMMDD());
    head->setTourDepartureTime(
        info.getTourDepartureDateTimeNormalized().GetHours() * 100 * 100 +
        info.getTourDepartureDateTimeNormalized().GetMinutes() * 100 +
        info.getTourDepartureDateTimeNormalized().GetSeconds());
    head->setTourArrivalDate(info.getCustomerDeliveryDateTimeMin().GetYYYYMMDD());
    head->setTourArrivalTime(
        info.getCustomerDeliveryDateTimeMin().GetHours() * 100 * 100 +
        info.getCustomerDeliveryDateTimeMin().GetMinutes() * 100 +
        info.getCustomerDeliveryDateTimeMin().GetSeconds());
    head->setTourId(info.getTourID()());
    head->setTransferStatus(0);
    head->setAnnouncementId(0);         // will be set in save() (needs serial)
    head->setAnnouncementHeadId(0);     // will be set in save() (needs serial)
    head->setWholesalerReferenceId(""); // will be set in save() (needs serial)
}


//returnacceptancecheckid   shortname   description
//1     Rechnungsnr.Unbekannt   Rechnung in Rechnungshistorie nicht gefunden
//2     Rechnung storniert  Rechnung ist storniert
//3     Artikel nicht auf Rechnung  Artikelcode ist nicht Teil der Rechnung
//4     Menge erschoepft    Komplette Menge bereits retourniert oder abgelehnt
//5     Außer Handel    Artikel ist Außer Handel
//6     Retouren - Sperre   Artikel ist für Retouren gesperrt
//7     Vertriebs - Sperre  Artikel ist fuer den Vertrieb gesperrt
//8     Hersteller - Rueckruf   Artikel mit Hersteller - Rueckruf
//9     Chargen - Rueckruf  Artikel mit Chargenrueckruf fuer alle Chargen
//10    Rueckgabefrist GÜG  Rueckgabefrist fuer meldepflichtige Artikel(GÜG) ueberschritten
//11    Rueckgabefrist BTM  Reuckgabefrist fuer BTM - Artikel ueberschritten
//12    Rueckgabefrist KK   Rueckgabefrist fuer KK - Artikel ueberschritten
//13    Rueckgabefrist K8   Rueckgabefrist fuer K8 - Artikel ueberschritten
//14    Rueckgabefrist K20  Rueckgabefrist fuer K20 - Artikel ueberschritten
//15    Rueckgabefrist Retouren Allgemeine Rueckgabefrist ueberschritten
//16    GÜG - Artikel   Artikel ist meldepflichtig(GÜG)
//17    BTM - Artikel   Artikel ist BTM
//18    KK - Artikel    Artikel ist Kuehlartikel(KK)
//19    K8 - Artikel    Artikel ist Kuehlartikel(K8)
//20    K20 - Artikel   Artikel ist Kuehlartikel(K20)
//21    Hochpreis   Artikel ist Hochpreisartikel
//22    Rücksprache Auftragsart Rechnung zu Auftragsart mit Ruecksprache

bool ReturnPositionCheckUC::matchesRule(ReturnAnnouncementPosPtr pos, ReturnRuleBookPtr rule, pxArtBasePtr article) const
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerReturns(), "ReturnPositionCheckUC::matchesRule()");

    switch (rule->getReturnAccCheckId())
    {
        case CHECK_01_INVOICE_UNKNOWN:              return C01_InvoiceUnknown           (pos, article);
        case CHECK_02_INVOICE_CANCELLED:            return C02_InvoiceCancelled         (pos, article);
        case CHECK_03_ARTICLE_NOT_IN_INVOICE:       return C03_ArticleNotInInvoice      (pos, article);

        case CHECK_23_BATCH_NOT_IN_INVOICE:         return C23_BatchNotInInvoice        (pos, article);
        case CHECK_24_EXPIRYDATE_NOT_IN_INVOICE:    return C24_ExpiryDateNotInInvoice   (pos, article);

        case CHECK_04_QUANTITY_EXCEEDED:            return C04_QuantityExceeded         (pos, article);
        case CHECK_05_OUT_OF_TRADE:                 return C05_OutOfTrade               (pos, article);
        case CHECK_06_BLOCKED_FOR_RETURNS:          return C06_BlockedForReturns        (pos, article);
        case CHECK_07_BLOCKED_BY_SALES:             return C07_BlockedBySales           (pos, article);
        case CHECK_08_MANUFACTURER_RECALL:          return C08_ManufacturerRecall       (pos, article);
        case CHECK_09_BATCH_RECALL:                 return C09_BatchRecall              (pos, article);
        case CHECK_10_DEADLINE_GUG:                 return C10_DeadlineGUG              (pos, article);
        case CHECK_11_DEADLINE_NARC:                return C11_DeadlineNarc             (pos, article);
        case CHECK_12_DEADLINE_COLDCHAIN:           return C12_DeadlineColdchain        (pos, article);
        case CHECK_13_DEADLINE_COLD08:              return C13_DeadlineCold08           (pos, article);
        case CHECK_14_DEADLINE_COLD20:              return C14_DeadlineCold20           (pos, article);
        case CHECK_15_DEADLINE_RETURNS:             return C15_DeadlineReturns          (pos, article);
        case CHECK_16_GUG_ARTICLE:                  return C16_GUGArticle               (pos, article);
        case CHECK_17_NARC_ARTICLE:                 return C17_NarcArticle              (pos, article);
        case CHECK_18_COLDCHAIN_ARTICLE:            return C18_ColdchainArticle         (pos, article);
        case CHECK_19_COLD08_ARTICLE:               return C19_Cold08Article            (pos, article);
        case CHECK_20_COLD20_ARTICLE:               return C20_Cold20Article            (pos, article);
        case CHECK_21_HIGH_PRICE_ARTICLE:           return C21_HighPriceArticle         (pos, article);
        case CHECK_22_CALLBACK_ORDERTYPE:           return C22_CallbackOrderType        (pos, article);
        default: break;
    }
    return false;
}

/////////////////////////////////////////////////////////////////////////////////
// 1    Rechnungsnr.Unbekannt   Rechnung in Rechnungshistorie nicht gefunden
/////////////////////////////////////////////////////////////////////////////////
bool ReturnPositionCheckUC::C01_InvoiceUnknown(const ReturnAnnouncementPosPtr pos, const pxArtBasePtr /*article*/) const
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerReturns(), "ReturnPositionCheckUC::C01_InvoiceUnknown()");

    libcsc::document::DeliveryAdvicePtr deliveryAdvice = findDeliveryAdvice(pos);
    return (NULL == deliveryAdvice.get());
}

/////////////////////////////////////////////////////////////////////////////////
// 2    Rechnung storniert  Rechnung ist storniert
/////////////////////////////////////////////////////////////////////////////////
bool ReturnPositionCheckUC::C02_InvoiceCancelled(const ReturnAnnouncementPosPtr pos, const pxArtBasePtr /*article*/) const
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerReturns(), "ReturnPositionCheckUC::C02_InvoiceCancelled()");

    libcsc::document::DeliveryAdvicePtr deliveryAdvice = findDeliveryAdvice(pos);
    if (NULL != deliveryAdvice.get())
    {
        return deliveryAdvice->isCancelled();
    }
    return false;
}

/////////////////////////////////////////////////////////////////////////////////
// 3    Artikel nicht auf Rechnung  Artikelcode ist nicht Teil der Rechnung
/////////////////////////////////////////////////////////////////////////////////
bool ReturnPositionCheckUC::C03_ArticleNotInInvoice(const ReturnAnnouncementPosPtr pos, const pxArtBasePtr /*article*/) const
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerReturns(), "ReturnPositionCheckUC::C03_ArticleNotInInvoice()");

    bool articleNotInInvoice = true;

    libcsc::document::DeliveryAdvicePtr deliveryAdvice = findDeliveryAdvice(pos);
    if (NULL != deliveryAdvice.get())
    {
        document::DeliveryAdviceLineCollection::const_iterator it = deliveryAdvice->getDeliveryAdviceLineCollection()->begin();
        while (it != deliveryAdvice->getDeliveryAdviceLineCollection()->end())
        {
            if ((*it)->getArticleNo() == pos->getArticleNo())
            {
                articleNotInInvoice = false;
                break;
            }
            ++it;
        }
    }
    return articleNotInInvoice;
}

/////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////
bool ReturnPositionCheckUC::C23_BatchNotInInvoice(const ReturnAnnouncementPosPtr pos, const pxArtBasePtr /*article*/) const
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerReturns(), "ReturnPositionCheckUC::C23_BatchNotInInvoice()");

    if (pos->getBatch().empty())
    {
        return false;
    }

    bool batchNotInInvoice = true;

    libcsc::document::DeliveryAdvicePtr deliveryAdvice = findDeliveryAdvice(pos);
    if (NULL != deliveryAdvice.get())
    {
        document::DeliveryAdviceLineCollection::const_iterator it = deliveryAdvice->getDeliveryAdviceLineCollection()->begin();
        while (it != deliveryAdvice->getDeliveryAdviceLineCollection()->end())
        {
            if ((*it)->getArticleNo() == pos->getArticleNo())
            {
                document::DeliveryAdviceLinePtr line = *it;
                if (false == pos->getBatch().empty())
                {
                    document::DeliveryAdviceLineDetailsCollection::const_iterator detailsIt = line->getDetailsCollection()->begin();
                    while (detailsIt != line->getDetailsCollection()->end())
                    {
                        if (pos->getBatch() == (*detailsIt)->getBatch())
                        {
                            batchNotInInvoice = false;
                            break;
                        }
                        // if we dont have a batch in deliveryadvice data, we cannot reject!
                        if ((*detailsIt)->getBatch().empty())
                        {
                            batchNotInInvoice = false;
                            break;
                        }
                        ++detailsIt;
                    }
                }
            }
            if (false == batchNotInInvoice)
            {
                break;
            }
            ++it;
        }
    }
    return batchNotInInvoice;
}

/////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////
bool ReturnPositionCheckUC::C24_ExpiryDateNotInInvoice(const ReturnAnnouncementPosPtr pos, const pxArtBasePtr /*article*/) const
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerReturns(), "ReturnPositionCheckUC::C24_ExpiryDateNotInInvoice()");

    if (0 == pos->getExpiryDate())
    {
        return false;
    }
    bool expiryDateNotInInvoice = true;

    libcsc::document::DeliveryAdvicePtr deliveryAdvice = findDeliveryAdvice(pos);
    if (NULL != deliveryAdvice.get())
    {
        document::DeliveryAdviceLineCollection::const_iterator it = deliveryAdvice->getDeliveryAdviceLineCollection()->begin();
        while (it != deliveryAdvice->getDeliveryAdviceLineCollection()->end())
        {
            if ((*it)->getArticleNo() == pos->getArticleNo())
            {
                document::DeliveryAdviceLinePtr line = *it;
                if (0 != pos->getExpiryDate())
                {
                    document::DeliveryAdviceLineDetailsCollection::const_iterator detailsIt = line->getDetailsCollection()->begin();
                    while (detailsIt != line->getDetailsCollection()->end())
                    {
                        if (pos->getExpiryDate() / 100 == (*detailsIt)->getExpiryDate().getDate() / 100)
                        // compare only YYYYMM of expiry date (getExpiryDate() / 100)
                        {
                            expiryDateNotInInvoice = false;
                            break;
                        }
                        // if we dont have expirydate in deliveryadvice data, we cannot reject!
                        // deliveryadvicelinedetails.expirydate seems to be either 99991231 or 0!
                        if (false == (*detailsIt)->getExpiryDate().isValid())
                        {
                            expiryDateNotInInvoice = false;
                            break;
                        }
                        ++detailsIt;
                    }
                }
            }
            if (false == expiryDateNotInInvoice)
            {
                break;
            }
            ++it;
        }
    }
    return expiryDateNotInInvoice;
}

/////////////////////////////////////////////////////////////////////////////////
// 4 Menge erschoepft   Komplette Menge bereits retourniert oder abgelehnt
/////////////////////////////////////////////////////////////////////////////////
bool ReturnPositionCheckUC::C04_QuantityExceeded(const ReturnAnnouncementPosPtr pos, const pxArtBasePtr /*article*/) const
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerReturns(), "ReturnPositionCheckUC::C04_QuantityExceeded()");

    basar::Int32 qtyAvailableForReturn = 0;

    libcsc::document::DeliveryAdvicePtr deliveryAdvice = findDeliveryAdvice(pos);
    if (NULL != deliveryAdvice.get())
    {
        document::DeliveryAdviceLineCollection::const_iterator it = deliveryAdvice->getDeliveryAdviceLineCollection()->begin();
        while (it != deliveryAdvice->getDeliveryAdviceLineCollection()->end())
        {
            if ((*it)->getArticleNo() == pos->getArticleNo())
            {
                document::DeliveryAdviceLinePtr line = *it;
                /*if (false == pos->getBatch().empty() || 0 != pos->getExpiryDate())
                {
                    document::DeliveryAdviceLineDetailsCollection::const_iterator detailsIt = line->getDetailsCollection()->begin();
                    while (detailsIt != line->getDetailsCollection()->end())
                    {
                        if ((pos->getBatch() == (*detailsIt)->getBatch() || pos->getBatch().empty() || (*detailsIt)->getBatch().empty()) && // if we dont have batch in deliveryadvice data, we cannot reject!
                            (pos->getExpiryDate() / 100 == (*detailsIt)->getExpiryDate().getDate() / 100 || pos->getExpiryDate() == 0 || false == (*detailsIt)->getExpiryDate().isValid())) // if we dont have expirydate in deliveryadvice data, we cannot reject!
                            // compare only YYYYMM of expiry date (getExpiryDate() / 100)
                        {
                            qtyAvailableForReturn += (*detailsIt)->getQuantityDelivery();
                        }
                        ++detailsIt;
                    }
                }
                else
                {
                    qtyAvailableForReturn += line->getQuantityConfirmed() + line->getQuantityRebateInKind();
                }*/

                qtyAvailableForReturn += line->getQuantityConfirmed() + line->getQuantityRebateInKind();

                document::DeliveryAdviceLineReturnCollection::const_iterator itReturn = line->getReturnCollection()->begin();
                while (itReturn != line->getReturnCollection()->end())
                {
                    qtyAvailableForReturn -= (*itReturn)->getQuantityReturned();
                    qtyAvailableForReturn -= (*itReturn)->getQuantityReturnedRebateInKind();
                    qtyAvailableForReturn -= (*itReturn)->getQuantityReturnRejected();
                    ++itReturn;
                }
                // set deliveryposno to return announcement pos
                if (pos->getDeliveryAdvicePosNo() == 0 && qtyAvailableForReturn > 0)
                {
                    pos->setDeliveryAdvicePosNo(line->getDeliveryAdvicePosNo());
                }
            }
            ++it;
        }
    }
    return (qtyAvailableForReturn < pos->getReturnQty());
}

/////////////////////////////////////////////////////////////////////////////////
// 5 Außer Handel   Artikel ist Außer Handel
/////////////////////////////////////////////////////////////////////////////////
bool ReturnPositionCheckUC::C05_OutOfTrade(const ReturnAnnouncementPosPtr /*pos*/, const pxArtBasePtr article) const
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerReturns(), "ReturnPositionCheckUC::C05_OutOfTrade()");

    return article->ArtFlags().IsAusserHandel(); // TODO FN steht noch nicht genau fest!
}

/////////////////////////////////////////////////////////////////////////////////
// 6 Retouren - Sperre  Artikel ist für Retouren gesperrt
/////////////////////////////////////////////////////////////////////////////////
bool ReturnPositionCheckUC::C06_BlockedForReturns(const ReturnAnnouncementPosPtr /*pos*/, const pxArtBasePtr article) const
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerReturns(), "ReturnPositionCheckUC::C06_BlockedForReturns()");

    return article->IsArticleBlockedForReturns();
}

/////////////////////////////////////////////////////////////////////////////////
// 7 Vertriebs - Sperre Artikel ist fuer den Vertrieb gesperrt
/////////////////////////////////////////////////////////////////////////////////
bool ReturnPositionCheckUC::C07_BlockedBySales(const ReturnAnnouncementPosPtr /*pos*/, const pxArtBasePtr article) const
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerReturns(), "ReturnPositionCheckUC::C07_BlockedBySales()");

    return article->ArtFlags().IsOhneZertifikat();
}

/////////////////////////////////////////////////////////////////////////////////
// 8 Hersteller - Rueckruf  Artikel mit Hersteller - Rueckruf
/////////////////////////////////////////////////////////////////////////////////
bool ReturnPositionCheckUC::C08_ManufacturerRecall(const ReturnAnnouncementPosPtr /*pos*/, const pxArtBasePtr article) const
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerReturns(), "ReturnPositionCheckUC::C08_ManufacturerRecall()");

    return article->HasManufacturerRecall();
}

/////////////////////////////////////////////////////////////////////////////////
// 9 Chargen - Rueckruf Artikel mit Chargenrueckruf fuer alle Chargen
/////////////////////////////////////////////////////////////////////////////////
bool ReturnPositionCheckUC::C09_BatchRecall(const ReturnAnnouncementPosPtr /*pos*/, const pxArtBasePtr article) const
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerReturns(), "ReturnPositionCheckUC::C09_BatchRecall()");

    return article->HasBatchRecallForReturns();
}

/////////////////////////////////////////////////////////////////////////////////
// 10 Rueckgabefrist GÜG    Rueckgabefrist fuer meldepflichtige Artikel(GÜG) ueberschritten
/////////////////////////////////////////////////////////////////////////////////
bool ReturnPositionCheckUC::C10_DeadlineGUG(const ReturnAnnouncementPosPtr pos, const pxArtBasePtr article) const
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerReturns(), "ReturnPositionCheckUC::C10_DeadlineGUG()");

    if (false == C16_GUGArticle(pos, article))
    {
        return false;
    }
    return returnPeriodExceeded(pos, RETURN_ARTICLE_GUG);
}

/////////////////////////////////////////////////////////////////////////////////
// 11 Rueckgabefrist BTM    Reuckgabefrist fuer BTM - Artikel ueberschritten
/////////////////////////////////////////////////////////////////////////////////
bool ReturnPositionCheckUC::C11_DeadlineNarc(const ReturnAnnouncementPosPtr pos, const pxArtBasePtr article) const
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerReturns(), "ReturnPositionCheckUC::C11_DeadlineNarc()");

    if (false == C17_NarcArticle(pos, article))
    {
        return false;
    }
    return returnPeriodExceeded(pos, RETURN_ARTICLE_NARCOTICS);
}

/////////////////////////////////////////////////////////////////////////////////
// 12 Rueckgabefrist KK Rueckgabefrist fuer KK - Artikel ueberschritten
/////////////////////////////////////////////////////////////////////////////////
bool ReturnPositionCheckUC::C12_DeadlineColdchain(const ReturnAnnouncementPosPtr pos, const pxArtBasePtr article) const
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerReturns(), "ReturnPositionCheckUC::C12_DeadlineColdchain()");

    if (false == C18_ColdchainArticle(pos, article))
    {
        return false;
    }
    return returnPeriodExceeded(pos, RETURN_ARTICLE_COOLCHAIN);
}

/////////////////////////////////////////////////////////////////////////////////
// 13 Rueckgabefrist K8 Rueckgabefrist fuer K8 - Artikel ueberschritten
/////////////////////////////////////////////////////////////////////////////////
bool ReturnPositionCheckUC::C13_DeadlineCold08(const ReturnAnnouncementPosPtr pos, const pxArtBasePtr article) const
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerReturns(), "ReturnPositionCheckUC::C13_DeadlineCold08()");

    if (false == C19_Cold08Article(pos, article))
    {
        return false;
    }
    return returnPeriodExceeded(pos, RETURN_ARTICLE_COOL08);
}

/////////////////////////////////////////////////////////////////////////////////
// 14 Rueckgabefrist K20    Rueckgabefrist fuer K20 - Artikel ueberschritten
/////////////////////////////////////////////////////////////////////////////////
bool ReturnPositionCheckUC::C14_DeadlineCold20(const ReturnAnnouncementPosPtr pos, const pxArtBasePtr article) const
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerReturns(), "ReturnPositionCheckUC::C14_DeadlineCold20()");

    if (false == C20_Cold20Article(pos, article))
    {
        return false;
    }

    return returnPeriodExceeded(pos, RETURN_ARTICLE_COOL20);
}

/////////////////////////////////////////////////////////////////////////////////
// 15 Rueckgabefrist Retouren   Allgemeine Rueckgabefrist ueberschritten
/////////////////////////////////////////////////////////////////////////////////
bool ReturnPositionCheckUC::C15_DeadlineReturns(const ReturnAnnouncementPosPtr pos, const pxArtBasePtr /*article*/) const
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerReturns(), "ReturnPositionCheckUC::C15_DeadlineReturns()");

    return returnPeriodExceeded(pos, RETURN_ARTICLE_DEFAULT);
}

/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
bool ReturnPositionCheckUC::C16_GUGArticle(const ReturnAnnouncementPosPtr /*pos*/, const pxArtBasePtr article) const //16   GÜG - Artikel   Artikel ist meldepflichtig(GÜG)
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerReturns(), "ReturnPositionCheckUC::C16_GUGArticle()");

    return article->ArtFlags().IsArtikelMeldePflichtig();
}

/////////////////////////////////////////////////////////////////////////////////
// 17 BTM - Artikel Artikel ist BTM
/////////////////////////////////////////////////////////////////////////////////
bool ReturnPositionCheckUC::C17_NarcArticle(const ReturnAnnouncementPosPtr /*pos*/, const pxArtBasePtr article) const
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerReturns(), "ReturnPositionCheckUC::C17_NarcArticle()");

    return article->ArtClass().IsOpiat();
}

/////////////////////////////////////////////////////////////////////////////////
// 18 KK - Artikel  Artikel ist Kuehlartikel(KK)
/////////////////////////////////////////////////////////////////////////////////
bool ReturnPositionCheckUC::C18_ColdchainArticle(const ReturnAnnouncementPosPtr /*pos*/, const pxArtBasePtr article) const
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerReturns(), "ReturnPositionCheckUC::C18_ColdchainArticle()");

    return article->ArtFlags().IsKuehlKette();
}

/////////////////////////////////////////////////////////////////////////////////
// 19 K8 - Artikel  Artikel ist Kuehlartikel(K8)
/////////////////////////////////////////////////////////////////////////////////
bool ReturnPositionCheckUC::C19_Cold08Article(const ReturnAnnouncementPosPtr /*pos*/, const pxArtBasePtr article) const
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerReturns(), "ReturnPositionCheckUC::C19_Cold08Article()");

    return article->ArtFlags().IsGekuehlt08();
}

/////////////////////////////////////////////////////////////////////////////////
// 20 K20 - Artikel Artikel ist Kuehlartikel(K20)
/////////////////////////////////////////////////////////////////////////////////
bool ReturnPositionCheckUC::C20_Cold20Article(const ReturnAnnouncementPosPtr /*pos*/, const pxArtBasePtr article) const
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerReturns(), "ReturnPositionCheckUC::C20_Cold20Article()");

    return article->ArtFlags().IsGekuehlt20();
}

/////////////////////////////////////////////////////////////////////////////////
// 21 Hochpreis Artikel ist Hochpreisartikel
/////////////////////////////////////////////////////////////////////////////////
bool ReturnPositionCheckUC::C21_HighPriceArticle(const ReturnAnnouncementPosPtr pos, const pxArtBasePtr /*article*/) const
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerReturns(), "ReturnPositionCheckUC::C21_HighPriceArticle()");

    if (basar::Decimal(0.0) >= m_HighPriceLimit)
        return false;

    pxArtPriceList ArtPriceList(m_Session);
    ArtPriceList.Select(pos->getArticleNo());
    ArtPriceList.DeleteExpired();      // remove expired prices, so only guilty entries stay in the list
    basar::Decimal price(ArtPriceList.GetPreisEKApo());
    return (price > m_HighPriceLimit);
}

/////////////////////////////////////////////////////////////////////////////////
// 22 Rücksprache Auftragsart   Rechnung zu Auftragsart mit Ruecksprache
/////////////////////////////////////////////////////////////////////////////////
bool ReturnPositionCheckUC::C22_CallbackOrderType(const ReturnAnnouncementPosPtr pos, const pxArtBasePtr /*article*/) const
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerReturns(), "ReturnPositionCheckUC::C22_CallbackOrderType()");

    libcsc::document::DeliveryAdvicePtr deliveryAdvice = findDeliveryAdvice(pos);
    if (NULL != deliveryAdvice.get())
    {
        basar::VarString orderType = deliveryAdvice->getOrderType();

        libcsc::cscordertype::ICSCOrderTypeRepositoryPtr repo = m_Session->getCSCOrderTypeComponentManager()->getCSCOrderTypeRepository();
        libcsc::cscordertype::ICSCOrderTypePtr ot = repo->findOrderType(m_ReturnAnnouncement->getBranchNo(), orderType);
        if (NULL != ot.get())
        {
            return ot->isFlagSet(libcsc::cscordertype::CONSULTATION_FOR_MSV3_RETURNS_NECESSARY);
        }
    }
    return false;
}

bool ReturnPositionCheckUC::returnPeriodExceeded(const ReturnAnnouncementPosPtr pos, const ReturnPeriodArticleTypeEnum& type) const
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerReturns(), "ReturnPositionCheckUC::returnPeriodExceeded()");

    ReturnPeriodPtr period = m_ReturnPeriodRepository->findReturnPeriod(pos->getReturnReasonCode(), type);
    if (NULL != period.get())
    {
        return (m_WorkingDaysSinceDelivery > period->getPeriodOfValidReturn());
    }
    return false;
}

basar::Int16 ReturnPositionCheckUC::determineWorkingDaysSinceDelivery(const basar::Int16& branchNo, const basar::Date& deliveryAdviceDate) const
{
    basar::Int32 deliveryDate = deliveryAdviceDate.getDate();
    basar::Int32 nowDate = basar::Date::getCurrent().getDate();
    basar::Int32 returnPeriod = m_WorkingdaysCalendarRepository->getWorkingdaysCalendarDifferenceBetween(branchNo, deliveryDate, nowDate);
    return static_cast<basar::Int16>(returnPeriod);
}

document::DeliveryAdvicePtr ReturnPositionCheckUC::findDeliveryAdvice(ReturnAnnouncementPosPtr pos) const
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerReturns(), "ReturnPositionCheckUC::findDeliveryAdvice()");

    if (NULL != m_DeliveryAdvice.get())
    {
        if (m_DeliveryAdvice->getBranchNo() == m_ReturnAnnouncement->getBranchNo() &&
            m_DeliveryAdvice->getCustomerNo() == m_ReturnAnnouncement->getCustomerNo() &&
            m_DeliveryAdvice->getDeliveryAdviceNo() == pos->getDeliveryAdviceNo()) // &&
//          m_DeliveryAdvice->getDeliveryAdviceDate() == pos->getDeliveryAdviceDate())
        {
            return m_DeliveryAdvice;
        }
    }

    libcsc::document::DeliveryAdviceKey key;
    key.branchNo = m_ReturnAnnouncement->getBranchNo();
    key.customerNo = m_ReturnAnnouncement->getCustomerNo();
    key.deliveryAdviceNo = pos->getDeliveryAdviceNo();
    key.deliveryAdviceDate = pos->getDeliveryAdviceDate();

    libcsc::document::DeliveryAdviceInformationFilter filter;
    filter.SendTotals = false;
    filter.SendLineInformation = true;
    filter.SendLinePickingInformation = true;
    filter.SendLineDiscountInformation = false;
    filter.SendLineReturn = true;
    filter.SendCustomerInformation = false;

    bool incrementRequestCounter = false;
    bool completedOnly = true;

    m_DeliveryAdvice = m_DeliveryAdviceRepository->findDeliveryAdvice(key, filter, incrementRequestCounter, completedOnly);
    if (NULL != m_DeliveryAdvice.get())
    {
        m_WorkingDaysSinceDelivery = determineWorkingDaysSinceDelivery(
            m_DeliveryAdvice->getBranchNo(),
            m_DeliveryAdvice->getDeliveryAdviceDate()
        );
    }
    else
    {
        m_WorkingDaysSinceDelivery = 0;
    }
    return m_DeliveryAdvice;
}

} // end namespace returns
} // end namespace libcsc
