#include "returnshandler.h"

#include <returns/componentmanager/returncomponentmanager.h>
#include <returns/returnannouncement/ireturnannouncementrepositoryptr.h>
#include <returns/returnannouncement/ireturnannouncementrepository.h>
#include <returns/returnannouncement/returnannouncement.h>
#include <returns/returnannouncement/returnannouncementhead/returnannouncementhead.h>
#include <returns/returnannouncement/returnannouncementpos/returnannouncementpos.h>
#include <logger/loggerpool.h>
#include <exceptions/sqlduplicateexception.h>
#include "cscservicehelper.h"

#include <libbasarcmnutil_date.h>
#include <libbasarcmnutil_datetime.h>

#include <pxxmit.hpp>
#include <pxartbas.hpp>
#include <pxcstbas.hpp>
#include <pxarticlecodes.hpp>
#include <pxarticletext.hpp>
#include <types/messagecodeenum.inc>

namespace csc {
namespace service {

ReturnsHandler::ReturnsHandler()
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerSession(), "ReturnsHandler::ReturnsHandler()");
}

ReturnsHandler::~ReturnsHandler()
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerSession(), "ReturnsHandler::~ReturnsHandler()");
}

void ReturnsHandler::processReturnsRequest(
    ::csc::returns::ReturnsResponse& _return,
    const ::csc::returns::ReturnsRequest& request)
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerSession(), "ReturnsHandler::processReturnsRequest()");

    libcsc::returns::ReturnAnnouncementPtr returnAnnouncement = getReturnAnnouncement(request);
    getSession()->getReturnComponentManager()->getReturnPositionCheckUC()->setReturnAnnouncement(returnAnnouncement);

    csc::returns::ReturnsRequestPositionList::const_iterator it = request.ReturnsPositions.begin();
    while (it != request.ReturnsPositions.end())
    {
        csc::returns::ReturnsRequestPosition pos = (*it);
        libcsc::returns::ReturnAnnouncementPosPtr retPos = getReturnAnnouncementPosition(pos);
        getSession()->getReturnComponentManager()->getReturnPositionCheckUC()->checkPosition(retPos);
        ++it;
    }
    returnAnnouncement = getSession()->getReturnComponentManager()->getReturnPositionCheckUC()->getReturnAnnouncement();
    // save return announcement, but not return request!
    if (request.ReturnsHeadInformation.ReturnType == csc::types::ReturnTypeEnum::ReturnAnnouncement)
    {
        try
        {
            getSession()->getReturnComponentManager()->getReturnAnnouncementRepository()->saveReturnAnnouncement(returnAnnouncement);
        }
        catch (const libcsc::exceptions::SqlDuplicateException&)
        {
            nError error;
            error.ExternalError(getSession()->CMsgStream(), CMSG_XMIT_MSV3_DUPLICATE_TRANSMISSION, returnAnnouncement->getAnnouncementGuid().c_str());
            _return.__set_RetValue(Helper::getReturnStructFromError(error));
            return;
        }
    }
    fillReturnStructure(_return, returnAnnouncement);
}

void ReturnsHandler::fillReturnStructure(
    ::csc::returns::ReturnsResponse& _return,
    libcsc::returns::ReturnAnnouncementPtr returnAnnouncement)
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerSession(), "ReturnsHandler::fillReturnStructure()");

    _return.__set_RetValue(Helper::getReturnStructFromError(getSession()->Error()));
    csc::returns::ReturnsResponseGroupMap returnResponses;
    libcsc::returns::ReturnAnnouncementHeadCollection::const_iterator it = returnAnnouncement->getHeads()->begin();
    while (it != returnAnnouncement->getHeads()->end())
    {
        libcsc::returns::ReturnAnnouncementHeadPtr head = (*it);
        csc::returns::ReturnsResponseGroup group;
        fillReturnsResponseGroup(group, head, returnAnnouncement);
        returnResponses.insert(std::make_pair(getCheckResultEnum(head->getAccCheckResultCode()), group));
        ++it;
    }
    _return.__set_ReturnsResponses(returnResponses);
    _return.__set_BranchInformation(Helper::getBranchDetails(getSession(), returnAnnouncement->getBranchNo()));
    _return.__set_CustomerInformation(Helper::getCustomerDetails(getSession(), returnAnnouncement->getBranchNo(), returnAnnouncement->getCustomerNo()));
}

void  ReturnsHandler::fillReturnsResponseGroup(
    csc::returns::ReturnsResponseGroup& group,
    libcsc::returns::ReturnAnnouncementHeadPtr head,
    libcsc::returns::ReturnAnnouncementPtr returnAnnouncement)
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerSession(), "ReturnsHandler::fillReturnsResponseGroup()");

    group.__set_CSCAnnouncementID(head->getAnnouncementId());
    group.__set_CSCAnnouncementHeadID(head->getAnnouncementHeadId());
    group.__set_WholesalerReferenceID(head->getWholesalerReferenceId());
    group.__set_DocumentID(head->getDocumentId());
    group.__set_ReturnsTourID(head->getTourId());
    group.__set_ReturnsTourDeparture(Helper::getCscDateTimeFromInt(head->getTourDepartureDate(), head->getTourDepartureTime()));
    group.__set_ReturnsTourArrival(Helper::getCscDateTimeFromInt(head->getTourArrivalDate(), head->getTourArrivalTime()));
    csc::returns::ReturnsResponsePositionList returnsPositions;
    libcsc::returns::ReturnAnnouncementPosCollection::const_iterator it = head->getPositions()->begin();
    while (it != head->getPositions()->end())
    {
        csc::returns::ReturnsResponsePosition pos;
        pos.__set_PosNo((*it)->getPosNo());
        pos.__set_PositionReferenceNo((*it)->getAnnouncementPosRefId());
        pos.__set_DeliveryNoteNo((*it)->getDeliveryAdviceNo());
        pos.__set_ArticleCode((*it)->getArticleCode());
        pos.__set_ReturnQty((*it)->getReturnQty());
        pos.__set_ReturnReason(getReturnReasonEnumByString((*it)->getReturnReasonCode()));
        pos.__set_Batch((*it)->getBatch());
        if (0 != (*it)->getExpiryDate())
        {
            pos.__set_ExpiryDate(Helper::getCscDateFromIntDate((*it)->getExpiryDate()));
        }
        pos.__set_DeliveryNoteDate(Helper::getCscDateFromBasarDate((*it)->getDeliveryAdviceDate()));
        pos.__set_ArticleDetails(getArticleDetails(returnAnnouncement->getBranchNo(), (*it)));
        if (libcsc::returns::CHECK_UNKNOWN != (*it)->getFailedCheckId())
        {
            pos.__set_FailedCheckId(static_cast<int16_t>((*it)->getFailedCheckId()));
        }
        if (false == (*it)->getFailedCheckString().empty())
        {
            pos.__set_FailedCheckString((*it)->getFailedCheckString());
        }
        returnsPositions.push_back(pos);
        ++it;
    }
    group.__set_ReturnsPositions(returnsPositions);
}

csc::order::ArticleInformation ReturnsHandler::getArticleDetails(const basar::Int16 branchNo, const libcsc::returns::ReturnAnnouncementPosPtr pos)
{
    csc::order::ArticleInformation artinfo;
    basar::VarString tmp;
    pxArtBase* article = pxArtBase::CreateArticle(getSession().get(), pos->getArticleNo(), branchNo);
    artinfo.__set_ArticleNo(pos->getArticleNo());
    artinfo.__set_ArticleCode(pos->getArticleCode());

    tmp = getSession()->ConvertPzn2Ean(pos->getArticleNo(), 13)();
    tmp.trim(basar::cmnutil::BString::FIRST_END);
    artinfo.__set_Ean(tmp);

    if (article != NULL && article->IsGoodState())
    {
        basar::Int16 TextKey = article->TextKey();
        if (TextKey > 0)
        {
            pxArticleText ptext(getSession().get(), TextKey);
            if (!ptext.Get(cDBGET_READONLY))
            {
                tmp = ptext.Text()();
                tmp.trim(basar::cmnutil::BString::FIRST_END);
                artinfo.__set_ArticleText(tmp);
            }
        }
        tmp = article->Bezeichnung()();
        tmp.trim(basar::cmnutil::BString::FIRST_END);
        artinfo.__set_ArticleName(tmp);

        tmp = article->ArtikelLangname()();
        tmp.trim(basar::cmnutil::BString::FIRST_END);
        artinfo.__set_ArticleLongName(tmp);

        tmp = article->Einheit()();
        tmp.trim(basar::cmnutil::BString::FIRST_END);
        artinfo.__set_ArticleUnit(tmp);

        tmp = article->Darreichform()();
        tmp.trim(basar::cmnutil::BString::FIRST_END);
        artinfo.__set_ArticleHandout(tmp);
    }
    delete article;
    return artinfo;
}


libcsc::returns::ReturnAnnouncementPtr ReturnsHandler::getReturnAnnouncement(const csc::returns::ReturnsRequest& request)
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerSession(), "ReturnsHandler::getReturnAnnouncement()");

    libcsc::returns::IReturnAnnouncementRepositoryPtr repo = getSession()->getReturnComponentManager()->getReturnAnnouncementRepository();
    libcsc::returns::ReturnAnnouncementPtr returnAnnouncement = repo->createEmptyReturnAnnouncement();

    returnAnnouncement->setBranchNo(request.ReturnsHeadInformation.BranchNo);
    returnAnnouncement->setCustomerNo(request.ReturnsHeadInformation.CustomerNo);
    returnAnnouncement->setAnnouncementGuid(request.ReturnsHeadInformation.ReturnID); // GUID
    returnAnnouncement->setAnnouncementSupportId(request.ReturnsHeadInformation.SupportID); // RetoureSupportID
    returnAnnouncement->setAnnouncementDate(basar::cmnutil::Date::getCurrent().getDate());
    returnAnnouncement->setAnnouncementTime(basar::cmnutil::DateTime::getCurrent().getTime() / 1000);
    returnAnnouncement->setContainsWrongPickedItem(containsWrongPickedItem(request) ? 1 : 0); // contains both BN+ZG pos
    returnAnnouncement->setLocalCourt(request.ReturnsHeadInformation.LocalCourt);
    returnAnnouncement->setCompanyRegistrationNo(request.ReturnsHeadInformation.CompanyRegistrationNo);
    returnAnnouncement->setVatIdentificationNo(request.ReturnsHeadInformation.VATIdentificationNo);
    returnAnnouncement->setTaxIdentificationNo(request.ReturnsHeadInformation.TaxIdentificationNo);
    returnAnnouncement->setNameOfBank(request.ReturnsHeadInformation.CustomerBankAccount.NameOfBank);
    returnAnnouncement->setBIC(request.ReturnsHeadInformation.CustomerBankAccount.BIC);
    returnAnnouncement->setIBAN(request.ReturnsHeadInformation.CustomerBankAccount.IBAN);
    return returnAnnouncement;
}

libcsc::returns::ReturnAnnouncementPosPtr ReturnsHandler::getReturnAnnouncementPosition(const csc::returns::ReturnsRequestPosition& pos)
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerSession(), "ReturnsHandler::getReturnAnnouncementPosition()");

    libcsc::returns::ReturnAnnouncementPosPtr retPos = boost::shared_ptr<libcsc::returns::ReturnAnnouncementPos>(new libcsc::returns::ReturnAnnouncementPos());
    retPos->setPosNo(0); // will be set while adding to a ReturnsAnnouncementHead...
    retPos->setAnnouncementPosRefId(pos.PositionReferenceNo);

    retPos->setDeliveryAdviceNo(pos.DeliveryNoteNo);
    if (pos.__isset.DeliveryNoteDate)
    {
        retPos->setDeliveryAdviceDate(Helper::getIntDateFromCscDate(pos.DeliveryNoteDate));
    }
    else
    {
        basar::Date invalid;
        invalid.setInvalid();
        retPos->setDeliveryAdviceDate(invalid);
    }
    retPos->setDeliveryAdvicePosNo(0); // TODO Alle Positionen mit der PZN pruefen
    retPos->setReturnReasonCode(getReturnReasonStringByEnum(pos.ReturnReason));
    retPos->setReturnQty(pos.ReturnQty);
    pxArticleCodes code(getSession().get(), pos.ArticleCode.c_str());
    code.Get();
    if (code.IsGoodState())
    {
        retPos->setArticleNo(code.ArticleNo());
        retPos->setCodeType(code.CodeType());
    }
    retPos->setArticleCode(pos.ArticleCode);
    retPos->setBatch(pos.Batch);
    retPos->setExpiryDate(Helper::getIntDateFromCscDate(pos.ExpiryDate));
    return retPos;
}


basar::VarString ReturnsHandler::getReturnReasonStringByEnum(const csc::types::ReturnReasonEnum::type r) const
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerSession(), "ReturnsHandler::getReturnReasonStringByEnum()");

    switch (r)
    {
        case csc::types::ReturnReasonEnum::OrderingError:           return "BF"; // Bestellfehler
        case csc::types::ReturnReasonEnum::InvoicedNotDelivered:    return "BN"; // BerechnetNichtGeliefert
        case csc::types::ReturnReasonEnum::Damaged:                 return "BE"; // Beschaedigt
        case csc::types::ReturnReasonEnum::ShortExpiry:             return "VK"; // VerfallZuKurz
        case csc::types::ReturnReasonEnum::TooMuchDelivered:        return "ZG"; // ZuVielGeliefert
        default: break;
    }
    return basar::VarString();
}

csc::types::ReturnReasonEnum::type ReturnsHandler::getReturnReasonEnumByString(const basar::VarString& r) const
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerSession(), "ReturnsHandler::getReturnReasonEnumByString()");

    if ("BF" == r)  return csc::types::ReturnReasonEnum::OrderingError;
    if ("BN" == r)  return csc::types::ReturnReasonEnum::InvoicedNotDelivered;
    if ("BE" == r)  return csc::types::ReturnReasonEnum::Damaged;
    if ("VK" == r)  return csc::types::ReturnReasonEnum::ShortExpiry;
    if ("ZG" == r)  return csc::types::ReturnReasonEnum::TooMuchDelivered;
    return csc::types::ReturnReasonEnum::OrderingError;
}


//Accepted = 0, // RA = RetoureAkzeptiert
//AcceptedWithCallback = 1, // RR = RetoureAkzeptiertRueckspracheNoetig
//AcceptedWithoutReturnDelivery = 2,    // RK = RetoureAkzeptiertKeineRuecksendungNoetig
//QuantityExceeded = 3, // AM = MengeUeberschritten
//ReturnDeadlineExceeded = 4,   // AR = RueckgabefristUeberschritten
//NotAccepted = 5,  // AK = KeineRuecknahme
//ArticleNotOnInvoice = 6,  // AP = PznInLieferscheinnummerNichtEnthalten
//UnknownInvoiceNo = 7      // AL = LieferscheinnummerUnbekannt
csc::types::ReturnAcceptanceCheckResultEnum::type ReturnsHandler::getCheckResultEnum(const basar::VarString& accCheckResult) const
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerSession(), "ReturnsHandler::getCheckResultEnum()");

    if ("RA" == accCheckResult)
        return csc::types::ReturnAcceptanceCheckResultEnum::Accepted;
    if ("RR" == accCheckResult)
        return csc::types::ReturnAcceptanceCheckResultEnum::AcceptedWithCallback;
    if ("RK" == accCheckResult)
        return csc::types::ReturnAcceptanceCheckResultEnum::AcceptedWithoutReturnDelivery;
    if ("AM" == accCheckResult)
        return csc::types::ReturnAcceptanceCheckResultEnum::QuantityExceeded;
    if ("AR" == accCheckResult)
        return csc::types::ReturnAcceptanceCheckResultEnum::ReturnDeadlineExceeded;
    if ("AK" == accCheckResult)
        return csc::types::ReturnAcceptanceCheckResultEnum::NotAccepted;
    if ("AP" == accCheckResult)
        return csc::types::ReturnAcceptanceCheckResultEnum::ArticleNotOnInvoice;
    if ("AL" == accCheckResult)
        return csc::types::ReturnAcceptanceCheckResultEnum::UnknownInvoiceNo;
    return csc::types::ReturnAcceptanceCheckResultEnum::NotAccepted;
}


bool ReturnsHandler::containsWrongPickedItem(const csc::returns::ReturnsRequest& request) const
{
    // if request contains both "InvoicedNotDelivered" ("BN") and "TooMuchDelivered" ("ZG") -> return true
    bool foundBN = false;
    bool foundZG = false;
    csc::returns::ReturnsRequestPositionList::const_iterator it = request.ReturnsPositions.begin();
    while (it != request.ReturnsPositions.end())
    {
        if (csc::types::ReturnReasonEnum::InvoicedNotDelivered == (*it).ReturnReason)
        {
            foundBN = true;
        }
        if (csc::types::ReturnReasonEnum::TooMuchDelivered == (*it).ReturnReason)
        {
            foundZG = true;
        }
        if (true == foundBN && true == foundZG)
        {
            break;
        }
        ++it;
    }
    return (true == foundBN && true == foundZG);
}


} // namespace service
} // namespace csc
