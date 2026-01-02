#include "cremamailhandler.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cstdio>
#include <ctime>

#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>

#include "pxrecord.h" /* tCREMAMAIL */
#include "pxsess.hpp"
#include "pxcstbas.hpp"
#include "pxsalesman.hpp"
#include "pxdebitlimit.hpp"
#include "pxcremamail.hpp"
#include "pxoeparm.hpp"
#include "pxbranch.hpp"
#include "pxxmldefs.h"
#include "types/messagecodeenum.inc"
#include <boost/algorithm/string.hpp>
#include <boost/numeric/conversion/cast.hpp>

#include <libbasarcmnutil_date.h>
#include <libbasarcmnutil_datetime.h>

extern int pxGlobalLanguageId;

CremaMailHandler::CremaMailHandler(pxSession* session)
{
    this->userSession = session;
}

CremaMailHandler::~CremaMailHandler()
{
}

std::ifstream* CremaMailHandler::CMsgStream() { return userSession->CMsgStream(); }

std::string CremaMailHandler::getLanguageForPartner(int partnerNo)
{
    pxCremaMailList dlist(this->userSession);

    dlist.SelectLanguageForPartner(partnerNo);

    if (dlist.Entries() <= 0)
    {
        return "DE";
    }

    pxCremaMail* dikp;
    pxCremaMailListIter cursor(dlist);
    nString language;
    dikp = (pxCremaMail*) ++cursor;
    dikp->Guid().GetData(language);
    dlist.Clear();

    return language();
}

std::string CremaMailHandler::getGuidForOrder(long orderNo)
{
    pxCremaMailList dlist(this->userSession);

    dlist.SelectGuidForOrder(orderNo);

    if (dlist.Entries() <= 0)
    {
        return "";
    }

    pxCremaMail* dikp;
    pxCremaMailListIter cursor(dlist);
    nString guid;
    dikp = (pxCremaMail*) ++cursor;
    dikp->Guid().GetData(guid);
    dlist.Clear();

    return guid();
}

bool CremaMailHandler::processWarningMailRequest(int partnerNo, short branchNo, pxDebitLimit debtLimit)
{
    bool retValue = false;
    tCREMAMAIL data;
    double creditLimit = -1;
    double usedCredit = -1;
    double dlPercentage = -1;
    int former_pxGlobalLanguageId = pxGlobalLanguageId;

    try
    {
        creditLimit = debtLimit.Limit();
        usedCredit = debtLimit.SumAdvanceAccount();
        dlPercentage = usedCredit / creditLimit * 100;

        setMailLevels(dlPercentage, usedCredit);

        pxCustBase custBase(this->userSession, branchNo, 0L);

        userSession->Branch()->Store() = branchNo;
        nString language = getLanguageForPartner(partnerNo).c_str();
        userSession->LanguageCode(custBase.ConvertLanguage(language));
        pxGlobalLanguageId = userSession->LanguageCode();

        if (levelPercentage != CremaMailHandler::NO_MAIL)
        {
            //If a warnmail should be send, but a warnmail for this customer was already send, dont send another one
            //If a lockmail shall be send and it was already send for this order, dont send again
            if (this->wasMailSendWarningPartner(partnerNo, branchNo, dlPercentage) == false)
            {
                if (this->getCremaMailDataLevel(WARN, branchNo, &data))
                {
                    //keine Ordermail
                    if (this->processConfiguredMailGroups(&data, -1, creditLimit, dlPercentage, usedCredit, -1, &custBase, WARN, partnerNo))
                    {
                        retValue = true;
                    }
                    else
                    {
                        nMessage error(CMsgStream(), CMSG_ORD_CREMA_MAILSEND_PARTNER_ERROR, partnerNo, dlPercentage);
                        userSession->WriteLog(error.String(), nSTATE_CONDITION, CMSG_ORD_CREMA_MAILSEND_PARTNER_ERROR);
                        retValue = false;
                    }
                }
            }
            else
            {
                retValue = true;
            }
        }

        if (levelAmount != CremaMailHandler::NO_MAIL && !wasMailSendAmountPartner(partnerNo, branchNo, usedCredit))
        {
            if (this->getCremaMailDataAmount(usedCredit, branchNo, &data))
            {
                if (this->processConfiguredMailGroups(&data, -1, creditLimit, dlPercentage, usedCredit, -1, &custBase, levelAmount, partnerNo))
                {
                    retValue = true;
                }
                else
                {
                    nMessage error(CMsgStream(), CMSG_ORD_CREMA_MAILSEND_PARTNER_ERROR_AMOUNT, partnerNo, usedCredit);
                    userSession->WriteLog(error.String(), nSTATE_CONDITION, CMSG_ORD_CREMA_MAILSEND_PARTNER_ERROR_AMOUNT);
                    retValue = false;
                }
            }
        }
    }
    catch (...)
    {
        nMessage error(CMsgStream(), CMSG_ORD_CREMA_MAILSEND_PARTNER_ERROR, partnerNo, dlPercentage);
        userSession->WriteLog(error.String(), nSTATE_ERROR, CMSG_ORD_CREMA_MAILSEND_PARTNER_ERROR);
    }

    pxGlobalLanguageId = former_pxGlobalLanguageId;
    return retValue;
}

bool CremaMailHandler::processWarningMailRequest(int partnerNo, pxDebitLimit debtLimit, pxCremaMailList& dlist)
{
    bool retValue = false;

    pxCremaMail* dikp;
    pxCremaMailListIter cursor(dlist);
    while (NULL != (dikp = (pxCremaMail*) ++cursor))
    {
        const pxOrderEntryParamPtr oeparam = this->userSession->getOrderEntryParam(dikp->BranchNo());
        if (oeparam->IsActive())  // then param not found
        {
            if (oeparam->IsSCrema() && !oeparam->IsSStopCrema())
            {
                retValue = processWarningMailRequest(partnerNo, dikp->BranchNo(), debtLimit);
                if (!retValue)
                {
                    nMessage error(CMsgStream(), CMSG_ORD_CREMA_MAILSEND_PARTNER_ERROR, partnerNo, -1);
                    userSession->WriteLog(error.String(), nSTATE_ERROR, CMSG_ORD_CREMA_MAILSEND_PARTNER_ERROR);
                }
            }
        }
    }

    return retValue;
}

bool CremaMailHandler::processWarningMailRequest(int partnerNo, pxCustBase* custBase)
{
    bool retValue = false;
    nMoney Nullm(0.00);
    pxDebitLimit debtLimit(this->userSession, partnerNo, cDBGET_READONLY);
    try
    {
        if (this->userSession->isBulgaria())
        {
            pxDebitLimit* debtLimitBG = NULL;
            // Checks debtlimit for BG at partnerno level (type = 2) for all articles
            debtLimitBG = custBase->DebitLimitK2();
            if (!debtLimitBG->IsGoodState() || (debtLimitBG->Limit() == nMoney(0.00)) || !(debtLimitBG->SumAdvanceAccount() > debtLimitBG->Limit()))
            {
                debtLimitBG = NULL;
                // Checks debtlimit for BG at partnerno level (type = 1) for all articles except List5 and uses chain level if exists
                debtLimitBG = custBase->DebitLimitK1();
                if (!debtLimitBG->IsGoodState() || (debtLimitBG->Limit() == nMoney(0.00)))
                {
                    return false;
                }
            }
            debtLimit = pxDebitLimit(*debtLimitBG);
        }
        else
        {
            if (!debtLimit.IsGoodState())
            {
                return false;
            }

            if (debtLimit.Limit() == Nullm)
            {
                return true;
            }
        }
        pxCremaMailList dlist(this->userSession);
        dlist.SelectPartnerVZS(partnerNo);
        if (dlist.Entries() <= 0)
        {
            nMessage error(CMsgStream(), CMSG_ORD_CREMA_PARTNER_VZ_ERROR, partnerNo);
            userSession->WriteLog(error.String(), nSTATE_ERROR, CMSG_ORD_CREMA_PARTNER_VZ_ERROR);
            return false;
        }
        processWarningMailRequest(partnerNo, debtLimit, dlist);
    }
    catch (...)
    {
        nMessage error(CMsgStream(), CMSG_ORD_CREMA_MAILSEND_PARTNER_ERROR, partnerNo, -1);
        userSession->WriteLog(error.String(), nSTATE_ERROR, CMSG_ORD_CREMA_MAILSEND_PARTNER_ERROR);
    }

    return retValue;
}

bool CremaMailHandler::sendMail(double dlPercentage, double creditLimit, double usedCredit, double orderValue, long orderNo,
    pxCustBase* custBase)
{
    bool retValue = true;
    tCREMAMAIL data;

    try
    {
        setMailLevels(dlPercentage, usedCredit);
        // Just for debugging
        //levelPercentage = CremaMailHandler::NO_MAIL;

        if (levelPercentage != CremaMailHandler::NO_MAIL)
        {
            //If a warnmail should be send, but a warnmail for this customer was already send, dont send another one
            if ((levelPercentage == CremaMailHandler::WARN && this->wasMailSendWarningPartner(custBase->PartnerNr(), custBase->Vertriebszentrum(), dlPercentage) == false)
                || (levelAmount != CremaMailHandler::NO_MAIL && !wasMailSendAmountPartner(custBase->PartnerNr(), custBase->Vertriebszentrum(), usedCredit))
                )
            {
                retValue = processWarningMailRequest(custBase->PartnerNr(), custBase);
            }

            //If a lockmail shall be send and it was already send for this order, dont send again
            if (levelPercentage != CremaMailHandler::WARN && this->wasMailSendOrder(orderNo, custBase->Vertriebszentrum()) == false)
            {
                if (this->getCremaMailDataPercentage(dlPercentage, custBase->Vertriebszentrum(), &data))
                {
                    if (this->processConfiguredMailGroups(&data, orderNo, creditLimit, dlPercentage, usedCredit, orderValue, custBase, levelPercentage, custBase->PartnerNr()))
                    {
                        retValue = true;
                    }
                    else
                    {
                        nMessage error(CMsgStream(), CMSG_ORD_CREMA_MAILSEND_ERROR, orderNo, dlPercentage);
                        userSession->WriteLog(error.String(), nSTATE_CONDITION, CMSG_ORD_CREMA_MAILSEND_ERROR);
                        retValue = false;
                    }
                }
            }
        }
    }
    catch (...)
    {
        nMessage error(CMsgStream(), CMSG_ORD_CREMA_MAILSEND_ERROR, orderNo, dlPercentage);
        userSession->WriteLog(error.String(), nSTATE_ERROR, CMSG_ORD_CREMA_MAILSEND_ERROR);
        retValue = false;
    }

    return retValue;
}

bool CremaMailHandler::setMailLevels(double dlPercentage, double usedCreditAmount)
{
    if (!this->setMailLevelPercentage(dlPercentage))
    {
        nMessage error(CMsgStream(), CMSG_ORD_NO_PERCENTAGE_DATA_FOR_CREMA);
        userSession->WriteLog(error.String(), nSTATE_CONDITION, CMSG_ORD_NO_PERCENTAGE_DATA_FOR_CREMA);
        levelPercentage = CremaMailHandler::NO_MAIL;
        return false;
    }

    //no error handling here because amount mails are optional
    this->setMailLevelAmount(usedCreditAmount);

    return true;
}

bool CremaMailHandler::setMailLevelAmount(double usedCreditAmount)
{
    pxCremaMailList dlist(this->userSession);

    dlist.SelectMailTypeAmount(usedCreditAmount);

    if (dlist.Entries() <= 0)
    {
        return false;
    }

    this->levelAmount = CremaMailHandler::AMOUNT;

    return true;
}

bool CremaMailHandler::setMailLevelPercentage(double dlPercentage)
{
    pxCremaMailList dlist(this->userSession);

    dlist.SelectMailTypePercentage(dlPercentage);

    if (dlist.Entries() <= 0)
    {
        nMessage error(CMsgStream(), CMSG_ORD_NO_PERCENTAGE_DATA_FOR_CREMA);
        userSession->WriteLog(error.String(), nSTATE_CONDITION, CMSG_ORD_NO_PERCENTAGE_DATA_FOR_CREMA);

        return false;
    }

    pxCremaMail* dikp;
    pxCremaMailListIter cursor(dlist);

    dikp = (pxCremaMail*) ++cursor;
    this->levelPercentage = static_cast<CremaMailHandler::MAILLEVEL>(dikp->LevelType());

    dlist.Clear();

    return true;
}

std::string CremaMailHandler::parseCurrency(double orderValue)
{
    const std::string radix = ".";
    const std::string thousands = ",";
    unsigned long v = boost::numeric_cast<unsigned long>((orderValue * 100.0) + .5);
    std::string fmt, digit;
    int i = -2;

    do
    {
        if (i == 0)
        {
            fmt = radix + fmt;
        }

        if ((i > 0) && (!(i % 3)))
        {
            fmt = thousands + fmt;
        }

        digit = (v % 10) + '0';
        fmt = digit + fmt;
        v /= 10;
        i++;
    } while ((v) || (i < 1));

    return fmt;
}

bool CremaMailHandler::getMailSentToAddresses(int smtpUserGroupId, CremaMailHandler::MAILTYPE type,
    std::vector< std::pair<std::string, CremaMailHandler::MAILTYPE> >& mailSentToAddresses)
{
    pxCremaMailList dlist(this->userSession);

    dlist.SelectMailAdresses(smtpUserGroupId, static_cast<short>(type));

    if (dlist.Entries() == 0)
    {
        nMessage error(CMsgStream(), CMSG_ORD_NO_DATA_FOR_CREMA, smtpUserGroupId);
        userSession->WriteLog(error.String(), nSTATE_CONDITION, CMSG_ORD_NO_DATA_FOR_CREMA);

        return false;
    }

    pxCremaMail* dikp;
    pxCremaMailListIter cursor(dlist);

    nString tmp;
    int count = 0;
    while ((dikp = (pxCremaMail*) ++cursor) != NULL)
    {
        count++;
        dikp->SentToAddress().GetData(tmp);
        mailSentToAddresses.push_back(convertToSendToAdress(tmp, (CremaMailHandler::MAILTYPE)(dikp->EmailType())));

        nMessage error(CMsgStream(), CMSG_ORD_LIBMAIL_MAILSEND_ADDRESS, __FUNCTION__, this->levelPercentage, type, count, tmp());
        userSession->WriteLog(error.String(), nSTATE_CONDITION, CMSG_ORD_LIBMAIL_MAILSEND_ADDRESS);
    }
    dlist.Clear();

    return true;
}

std::pair<std::string, CremaMailHandler::MAILTYPE> CremaMailHandler::convertToSendToAdress(nString& sendToAdress, CremaMailHandler::MAILTYPE mailtype)
{
    return std::pair<std::string, CremaMailHandler::MAILTYPE>(std::string(sendToAdress), mailtype);
}

bool CremaMailHandler::getGVLMailAddressesForPartner(int smtpUserGroupId, short branchNo, int partnerNo,
    CremaMailHandler::MAILTYPE type, std::vector< std::pair<std::string, CremaMailHandler::MAILTYPE> >& mailSentToAddresses)
{
    pxCremaMailList dlist(this->userSession);
    dlist.SelectGVLMailByType(smtpUserGroupId, static_cast<short>(type));
    if (dlist.Entries() == 0)
    {
        return true;//it's valid to have no gvl mail
    }

    pxCremaMail* dikp;
    pxCremaMailListIter cursor(dlist);
    pxSalesMan* sm;
    while (NULL != (dikp = (pxCremaMail*) ++cursor))
    {
        if (dikp->SendGVLMail() == 1)
        {
            pxSalesManList salesManList(this->userSession);
            salesManList.SelectByPartnerNo(partnerNo, branchNo);

            pxSalesManListIter smCursor(salesManList);

            while (NULL != (sm = (pxSalesMan*) ++smCursor))
            {
                nString tmp;

                sm->EmailAdress().GetData(tmp);
                mailSentToAddresses.push_back(convertToSendToAdress(tmp, (CremaMailHandler::MAILTYPE)(dikp->EmailType())));

                nMessage error(CMsgStream(), CMSG_ORD_LIBMAIL_MAILSEND_ADDRESS, __FUNCTION__, this->levelPercentage, type, 0, tmp());
                userSession->WriteLog(error.String(), nSTATE_CONDITION, CMSG_ORD_LIBMAIL_MAILSEND_ADDRESS);
            }

            salesManList.Clear();
        }
    }
    dlist.Clear();
    return true;
}

bool CremaMailHandler::getGVLMailSentToAddress(int smtpUserGroupId, short branchNo, short salesManNo, CremaMailHandler::MAILTYPE type, std::vector< std::pair<std::string, CremaMailHandler::MAILTYPE> >& mailSentToAddresses)
{
    pxCremaMailList dlist(this->userSession);
    dlist.SelectGVLMailByType(smtpUserGroupId, static_cast<short>(type));
    if (dlist.Entries() == 0)
    {
        return true;//it's valid to have no gvl mail
    }

    pxCremaMail* dikp;
    pxCremaMailListIter cursor(dlist);
    while ((dikp = (pxCremaMail*) ++cursor) != NULL)
    {
        if (dikp->SendGVLMail() == 1)
        {
            pxSalesManList salesManList(this->userSession);
            salesManList.SelectBySalesManNo(salesManNo, branchNo);

            if (salesManList.Entries() > 0)
            {
                nString tmp;
                pxSalesMan* sm;
                pxSalesManListIter smCursor(salesManList);
                sm = (pxSalesMan*) ++smCursor;

                sm->EmailAdress().GetData(tmp);
                mailSentToAddresses.push_back(convertToSendToAdress(tmp, (CremaMailHandler::MAILTYPE)(dikp->EmailType())));

                nMessage error(CMsgStream(), CMSG_ORD_LIBMAIL_MAILSEND_ADDRESS, __FUNCTION__, this->levelPercentage, type, 0, tmp());
                userSession->WriteLog(error.String(), nSTATE_CONDITION, CMSG_ORD_LIBMAIL_MAILSEND_ADDRESS);
            }

            salesManList.Clear();
        }
    }
    dlist.Clear();

    return true;
}

bool CremaMailHandler::sendEmailType(tCREMAMAIL* data, long orderNo, double creditLimit, double dlPercentage,
    double usedCredit, double orderValue, pxCustBase* custBase, CremaMailHandler::MAILLEVEL level, CremaMailHandler::MAILTYPE type, int partnerNo)
{
    bool retValue = true;
    std::vector< std::pair<std::string, CremaMailHandler::MAILTYPE> > mailSentToAddresses;

    if (level == WARN)
    {
        getGVLMailAddressesForPartner(data->SMTPUSERGROUPID, custBase->Vertriebszentrum(), partnerNo, type, mailSentToAddresses);
    }
    else
    {
        getGVLMailSentToAddress(data->SMTPUSERGROUPID, custBase->Vertriebszentrum(), static_cast<short>(custBase->PersonalNrVertr()), type, mailSentToAddresses);
    }

    getMailSentToAddresses(data->SMTPUSERGROUPID, type, mailSentToAddresses);

    if (mailSentToAddresses.size() > 0)
    {
        retValue = sendMail(data, orderNo, creditLimit, dlPercentage, usedCredit, orderValue, custBase, level, type, mailSentToAddresses, partnerNo);
    }
    return retValue;
}

bool CremaMailHandler::processConfiguredMailGroups(tCREMAMAIL* data, long orderNo, double creditLimit, double dlPercentage,
    double usedCredit, double orderValue, pxCustBase* custBase, CremaMailHandler::MAILLEVEL level, int partnerNo)
{
    bool retValue = sendEmailType(data, orderNo, creditLimit, dlPercentage, usedCredit, orderValue, custBase, level, CremaMailHandler::UNLOCK_DATA, partnerNo);
    if (retValue)
    {
        retValue = sendEmailType(data, orderNo, creditLimit, dlPercentage, usedCredit, orderValue, custBase, level, CremaMailHandler::UNLOCK_INFO, partnerNo);
    }
    return retValue;
}

bool CremaMailHandler::sendMail(tCREMAMAIL* data, long orderNo, double creditLimit, double dlPercentage,
    double usedCredit, double orderValue, pxCustBase* custBase, CremaMailHandler::MAILLEVEL level, CremaMailHandler::MAILTYPE type,
    std::vector< std::pair<std::string, CremaMailHandler::MAILTYPE> >& mailSentToAddresses, int partnerNo)
{
    bool infoMailType = type == CremaMailHandler::UNLOCK_INFO ? true : false;
    basar::cmnutil::Smtp::RetCodeEnum retCode = basar::cmnutil::Smtp::SMTP_SUCCESS;
    bool wasSend = false;
    pxCremaMail cremaMail(this->userSession, *data);
    std::string uuid = generateUUID();
    std::string url = data->URL;

    std::stringstream trimmer;
    trimmer << url;
    url.clear();
    trimmer >> url;

    url.append(uuid);

    try
    {
        if (this->userSession->isBulgaria())
        {
            basar::cmnutil::MailMessage message(basar::cmnutil::Locale::BULGARIAN_BG);
            this->initMail(*data, orderNo, creditLimit, dlPercentage, usedCredit, orderValue, url.c_str(), custBase, level, infoMailType, mailSentToAddresses, message, partnerNo);

            basar::cmnutil::Smtp mailService(data->SERVER, boost::numeric_cast<basar::Int16>(data->PORT));
            mailService.connect();
            retCode = mailService.send(message);
            if (retCode != basar::cmnutil::Smtp::SMTP_SUCCESS)
            {
                wasSend = false;
            }
            else
            {
                wasSend = true;
            }
            mailService.disconnect();

        }
        else
        {
            basar::cmnutil::MailMessage message;
            this->initMail(*data, orderNo, creditLimit, dlPercentage, usedCredit, orderValue, url.c_str(), custBase, level, infoMailType, mailSentToAddresses, message, partnerNo);

            basar::cmnutil::Smtp mailService(data->SERVER, boost::numeric_cast<basar::Int16>(data->PORT));
            mailService.connect();
            retCode = mailService.send(message);
            if (retCode != basar::cmnutil::Smtp::SMTP_SUCCESS)
            {
                wasSend = false;
            }
            else
            {
                wasSend = true;
            }
            mailService.disconnect();
        }
    }
    catch (...)
    {
        wasSend = false;
    }

    if (wasSend != true)
    {
        nMessage error(CMsgStream(), CMSG_ORD_LIBMAIL_SEND_ERROR_CREMA, orderNo, dlPercentage);
        userSession->WriteLog(error.String(), nSTATE_CONDITION, CMSG_ORD_LIBMAIL_SEND_ERROR_CREMA);

        nMessage error2(CMsgStream(), CMSG_ORD_LIBMAIL_SEND_ERROR_CREMA_RETCODE, retCode);
        userSession->WriteLog(error2.String(), nSTATE_CONDITION, CMSG_ORD_LIBMAIL_SEND_ERROR_CREMA_RETCODE);
    }

    strcpy(data->GUID, uuid.c_str());
    data->WASSEND = wasSend ? '1' : '0';
    data->SENDDATE = basar::cmnutil::Date::getCurrent().getDate();
    data->KDAUFTRAGNR = orderNo;
    data->BRANCHNO = custBase->Vertriebszentrum();
    data->PARTNERNO = custBase->PartnerNr() != 0 ? custBase->PartnerNr() : partnerNo;
    data->SENDTIME = basar::cmnutil::DateTime::getCurrent().getHour() * 10000 +
        basar::cmnutil::DateTime::getCurrent().getMinute() * 100 +
        basar::cmnutil::DateTime::getCurrent().getSec();
    data->EMAILTYPE = static_cast<short>(type);

    wasSend = cremaMail.InsertData(*data);

    return wasSend;
}

bool CremaMailHandler::replaceLineEndings(std::string& subject)
{
    size_t pos = 0;
    while ((pos = subject.find("\\n", pos)) != std::string::npos)
    {
        subject.replace(pos, 2, 1, '\n');
        pos++;//since we replace with only 1 char
    }
    return true;
}

void CremaMailHandler::setMailTextUnLock(long kdAuftragNr, double creditLimit, double dlPercentage, double usedCredit, double orderValue,
    const char* url, pxCustBase* custBase, bool infoMailGroup, std::string& body)
{
    std::string mailtext = "";

    mailtext.append(nMessage(CMsgStream(), CMSG_ORD_CREMA_MAILSEND_GREETING).String());
    if (this->userSession->isBulgaria()) {
        if (infoMailGroup) {
            mailtext.append(nMessage(CMsgStream(), CMSG_ORD_CREMA_MAILSEND_LINE_INFO,
                kdAuftragNr, custBase->IDFNr(), (custBase->NameApo())()).String());
        }
        else {
            mailtext.append(nMessage(CMsgStream(), CMSG_ORD_CREMA_MAILSEND_LINE_ORDER,
                kdAuftragNr, custBase->IDFNr(), (custBase->NameApo())()).String());
        }
    }
    else {
        mailtext.append(nMessage(CMsgStream(), CMSG_ORD_CREMA_MAILSEND_LINE_ORDER,
            kdAuftragNr, (custBase->NameApo())(), this->userSession->Country().c_str(), (custBase->Postleitzahl())(),
            (custBase->Ort())()).String());
    }

    if (!(this->userSession->isBulgaria() && infoMailGroup)) {

        std::string creditLimitCur = this->parseCurrency(creditLimit);
        mailtext.append(nMessage(CMsgStream(), CMSG_ORD_CREMA_MAILSEND_LINE_LIMIT, creditLimitCur.c_str()).String());

        std::string usedCreditCur = this->parseCurrency(usedCredit);
        mailtext.append(nMessage(CMsgStream(), CMSG_ORD_CREMA_MAILSEND_LINE_LIMIT_USED, usedCreditCur.c_str(), dlPercentage).String());

        std::string orderValueCur = this->parseCurrency(orderValue);
        mailtext.append(nMessage(CMsgStream(), CMSG_ORD_CREMA_MAILSEND_LINE_ORDER_VALUE, orderValueCur.c_str()).String());
    }

    if (!infoMailGroup)
    {
        mailtext.append(nMessage(CMsgStream(), CMSG_ORD_CREMA_MAILSEND_LINE_DECISION).String());
        mailtext.append(nMessage(CMsgStream(), CMSG_ORD_CREMA_MAILSEND_LINE_URL, url).String());
    }

    mailtext.append(nMessage(CMsgStream(), CMSG_ORD_CREMA_MAILSEND_LINE_THANKS).String());

    this->replaceLineEndings(mailtext);

    body = mailtext;
}

void CremaMailHandler::setMailTextWarning(std::string& partnerName, int partnerNo, double dlPercentage, double creditLimit, std::string& body)
{
    std::string mailtext = "";

    std::string creditLimitCur = this->parseCurrency(creditLimit);

    mailtext.append(nMessage(CMsgStream(), CMSG_ORD_CREMA_MAILSEND_GREETING).String());
    mailtext.append(nMessage(CMsgStream(), CMSG_ORD_CREMA_MAILSEND_LINE_WARNING, partnerName.c_str(), partnerNo, dlPercentage).String());
    mailtext.append(nMessage(CMsgStream(), CMSG_ORD_CREMA_MAILSEND_LINE_LIMIT_WARNING, creditLimitCur.c_str()).String());
    mailtext.append(nMessage(CMsgStream(), CMSG_ORD_CREMA_MAILSEND_LINE_BEST_REGARDS).String());

    this->replaceLineEndings(mailtext);

    body = mailtext;
}

void CremaMailHandler::setMailTextAmount(std::string& partnerName, int partnerNo, double thresholdAmount, double usedCredit, std::string& body)
{
    std::string mailtext = "";

    mailtext.append(nMessage(CMsgStream(), CMSG_ORD_CREMA_MAILSEND_GREETING).String());
    mailtext.append(nMessage(CMsgStream(), CMSG_ORD_CREMA_MAILSEND_LINE_AMOUNT, thresholdAmount, partnerName.c_str(), partnerNo, usedCredit).String());
    mailtext.append(nMessage(CMsgStream(), CMSG_ORD_CREMA_MAILSEND_LINE_BEST_REGARDS).String());

    this->replaceLineEndings(mailtext);

    body = mailtext;
}

bool CremaMailHandler::initMail(tCREMAMAIL mailData, long kdAuftragNr, double creditLimit, double dlPercentage,
    double usedCredit, double orderValue, const char* url, pxCustBase* custBase, CremaMailHandler::MAILLEVEL level, bool infoMailGroup,
    std::vector< std::pair<std::string, CremaMailHandler::MAILTYPE> >& mailSentToAddresses, basar::cmnutil::MailMessage& message, int partnerNo)
{
    std::string subject = "";
    std::string partnerName = "";
    std::string nameApo = custBase->NameApo()();
    std::string place = custBase->Ort()();
    std::string country = custBase->Land()();
    std::string postalCode = custBase->Postleitzahl()();

    if (level == CremaMailHandler::WARN || level == CremaMailHandler::AMOUNT)
    {
        pxDebitLimit limit(this->userSession, partnerNo);
        partnerName = limit.PartnerName();
        subject = nMessage(CMsgStream(), CMSG_ORD_CREMA_MAILSEND_SUBJECT_WARN, partnerNo, partnerName.c_str()).String();
    }
    else
    {
        if (this->userSession->isBulgaria()) {
            subject = nMessage(CMsgStream(), CMSG_ORD_CREMA_MAILSEND_SUBJECT, kdAuftragNr, custBase->IDFNr(), nameApo.c_str()).String();
        }
        else {
            subject = nMessage(CMsgStream(), CMSG_ORD_CREMA_MAILSEND_SUBJECT, kdAuftragNr, custBase->IDFNr(), nameApo.c_str(),
                country.c_str(), postalCode.c_str(), place.c_str()).String();
        }
    }
    boost::erase_all(subject, "\n");
    message.setSubject(subject);

    std::string tmp = mailData.SENTFROMADDRESS;
    tmp.erase(tmp.find_last_not_of(" \n\r\t") + 1);

    message.setFrom(tmp);
    message.setContentType(basar::cmnutil::MailMessage::TEXT_PLAIN);

    int count = 0;
    std::vector< std::pair<std::string, CremaMailHandler::MAILTYPE> >::iterator it = mailSentToAddresses.begin();
    for (; it != mailSentToAddresses.end(); ++it)
    {
        count++;
        tmp = (*it).first;
        tmp.erase(tmp.find_last_not_of(" \n\r\t") + 1);
        message.setTo(tmp);

        nMessage error(CMsgStream(), CMSG_ORD_LIBMAIL_MAILSEND_ADDRESS, __FUNCTION__, level, infoMailGroup ? CremaMailHandler::UNLOCK_INFO : CremaMailHandler::UNLOCK_DATA, count, tmp.c_str());
        userSession->WriteLog(error.String(), nSTATE_CONDITION, CMSG_ORD_LIBMAIL_MAILSEND_ADDRESS);
    }

    /* Not available with basar
     * TODO check how to get it
    if(level == CremaMailHandler::HIGH_UNLOCK)
    {
        this->mail.bImportant = true;
    }*/

    std::string body = "";
    switch (level)
    {
    case CremaMailHandler::AMOUNT:
        this->setMailTextAmount(partnerName, partnerNo, mailData.THRESHOLDAMOUNT, usedCredit, body);
        break;
    case CremaMailHandler::WARN:
        this->setMailTextWarning(partnerName, partnerNo, dlPercentage, creditLimit, body);
        break;
    case CremaMailHandler::UNLOCK:
    case CremaMailHandler::HIGH_UNLOCK:
    default:
        if (this->userSession->isBulgaria()) {
            //In case of Bulgaria, print both limits: chain level and IDF level
            pxDebitLimit* debtLimitK1 = NULL;
            pxDebitLimit* debtLimitK2 = NULL;
            // Checks debtlimit for BG at partnerno level
            debtLimitK1 = custBase->DebitLimitK1();
            debtLimitK2 = custBase->DebitLimitK2();
            if (!debtLimitK1->IsGoodState() || !debtLimitK2->IsGoodState())
            {
                return false;
            }
            this->setMailTextUnLock(kdAuftragNr, debtLimitK1->Limit(), dlPercentage, debtLimitK2->Limit(), orderValue, url, custBase, infoMailGroup, body);
        }
        else {
            this->setMailTextUnLock(kdAuftragNr, creditLimit, dlPercentage, usedCredit, orderValue, url, custBase, infoMailGroup, body);
        }
        break;

    }
    message.setBody(body);

    return true;
}

void CremaMailHandler::GetEmailAddressesForGUID(std::vector< std::pair<std::string, CremaMailHandler::MAILTYPE> >& mailSentToAddresses,
    std::string& sentFromAddress, std::string guid, std::string& server, int& port)
{
    pxCremaMailList dlist(this->userSession);

    dlist.SelectMailAdressesForGUID(guid);

    if (dlist.Entries() == 0)
    {
        nMessage error(CMsgStream(), CMSG_ORD_NO_DATA_FOR_CREMA, 0);
        userSession->WriteLog(error.String(), nSTATE_CONDITION, CMSG_ORD_NO_DATA_FOR_CREMA);
        return;
    }

    pxCremaMail* dikp;
    pxCremaMailListIter cursor(dlist);
    nString tmp;
    while ((dikp = (pxCremaMail*) ++cursor) != NULL)
    {
        dikp->SentToAddress().GetData(tmp);
        mailSentToAddresses.push_back(convertToSendToAdress(tmp, (CremaMailHandler::MAILTYPE)(dikp->EmailType())));
        sentFromAddress = dikp->SentFromAddress();
        server = dikp->Server();
        port = dikp->Port();
    }
    dlist.Clear();
}

bool CremaMailHandler::SendGUIDMail(basar::cmnutil::MailMessage& message, std::string server, int port)
{
    bool wasSend = false;
    basar::cmnutil::Smtp::RetCodeEnum retCode = basar::cmnutil::Smtp::SMTP_SUCCESS;
    try
    {
        basar::cmnutil::Smtp mailService(server.c_str(), boost::numeric_cast<basar::Int16>(port));
        mailService.connect();
        retCode = mailService.send(message);
        if (retCode != basar::cmnutil::Smtp::SMTP_SUCCESS)
        {
            wasSend = false;
        }
        else
        {
            wasSend = true;
        }
        mailService.disconnect();
    }
    catch (...)
    {
        wasSend = false;
    }

    if (wasSend != true)
    {
        //TODO
        nMessage error(CMsgStream(), CMSG_ORD_LIBMAIL_SEND_ERROR_CREMA, 0, 0);
        userSession->WriteLog(error.String(), nSTATE_CONDITION, CMSG_ORD_LIBMAIL_SEND_ERROR_CREMA);

        nMessage error2(CMsgStream(), CMSG_ORD_LIBMAIL_SEND_ERROR_CREMA_RETCODE, retCode);
        userSession->WriteLog(error2.String(), nSTATE_CONDITION, CMSG_ORD_LIBMAIL_SEND_ERROR_CREMA_RETCODE);
    }
    return wasSend;
}

bool CremaMailHandler::SendCremaDiscussionInfoMail(std::string guid, int orderNo, int customerNo, std::string customerName,
    std::string apothecary, std::string place, double orderAmount, std::string URL)
{
    std::vector< std::pair<std::string, CremaMailHandler::MAILTYPE> > mailSentToAddresses;
    std::string sentFromAddress = "";
    std::string server = "";
    int port = -1;
    basar::cmnutil::MailMessage* message = NULL;

    if (this->userSession->isBulgaria()) {
        message = new basar::cmnutil::MailMessage(basar::cmnutil::Locale::BULGARIAN_BG);
    }
    else {
        message = new basar::cmnutil::MailMessage();
    }
    std::string tmp = "";

    // only called from WebSite = no need to search for guid as it is always filled!
    GetEmailAddressesForGUID(mailSentToAddresses, sentFromAddress, guid, server, port);

    // URL sent from WebSite via XMLTEXTORG --> max. 100 signs
    // --> remove everything behind "=" and add guid again to be sure that link is complete:
    URL = URL.substr(0, URL.find_first_of("=") + 1);
    URL.append(guid);

    std::string subject = "";
    subject = nMessage(CMsgStream(), CMSG_ORD_CREMA_GUID_SUBJECT_DISCUSS, orderNo, customerNo, customerName.c_str(), place.c_str()).String();

    std::string bodyMessage = "";
    tmp = nMessage(CMsgStream(), CMSG_ORD_CREMA_MAIL_GUID_CURRENCY).String();
    boost::erase_all(tmp, "\n");
    bodyMessage = nMessage(CMsgStream(), CMSG_ORD_CREMA_MAIL_BODY_DISCUSS, orderNo, customerNo, apothecary.c_str(), tmp.c_str(), orderAmount, URL.c_str()).String();

    boost::erase_all(subject, "\n");
    replaceLineEndings(bodyMessage);
    message->setSubject(subject);
    message->setBody(bodyMessage);

    sentFromAddress.erase(sentFromAddress.find_last_not_of(" \n\r\t") + 1);
    message->setFrom(sentFromAddress);

    message->setContentType(basar::cmnutil::MailMessage::TEXT_PLAIN);

    int count = 0;
    std::vector< std::pair<std::string, CremaMailHandler::MAILTYPE> >::iterator it = mailSentToAddresses.begin();
    for (; it != mailSentToAddresses.end(); ++it)
    {
        count++;
        tmp = (*it).first;
        tmp.erase(tmp.find_last_not_of(" \n\r\t") + 1);
        message->setTo(tmp);

        nMessage error(CMsgStream(), CMSG_ORD_LIBMAIL_MAILSEND_ADDRESS, __FUNCTION__, 0, 0 ? CremaMailHandler::UNLOCK_INFO : CremaMailHandler::UNLOCK_DATA, count, tmp.c_str());
        userSession->WriteLog(error.String(), nSTATE_CONDITION, CMSG_ORD_LIBMAIL_MAILSEND_ADDRESS);
    }

    bool wasSend = SendGUIDMail(*message, server, port);

    delete message;
    message = NULL;
    return wasSend;
}

bool CremaMailHandler::SendCremaClosedInfoMail(std::string guid, int orderNo, int customerNo, std::string customerName,
    std::string apothecary, std::string place, std::string user, std::string reason, std::string comment, int approvalType)
{
    std::vector< std::pair<std::string, CremaMailHandler::MAILTYPE> > mailSentToAddresses;
    std::string sentFromAddress = "";
    std::string server = "";
    int port = -1;
    basar::cmnutil::MailMessage* message = NULL;

    if (this->userSession->isBulgaria()) {
        message = new basar::cmnutil::MailMessage(basar::cmnutil::Locale::BULGARIAN_BG);
    }
    else {
        message = new basar::cmnutil::MailMessage();
    }
    std::string tmp = "";

    std::time_t rawtime;
    std::tm* timeinfo;
    char time[40];
    char date[40];

    std::time(&rawtime);
    timeinfo = std::localtime(&rawtime);

    std::strftime(time, 80, "%H:%M:%S", timeinfo);
    std::strftime(date, 80, "%d.%m.%Y", timeinfo);

    if (guid.length() <= 0) // called directly from AE (not from WebSite) --> guid not filled yet
        guid = getGuidForOrder(orderNo);

    GetEmailAddressesForGUID(mailSentToAddresses, sentFromAddress, guid, server, port);

    std::string subject = "";
    std::string bodyMessage = "";


    if (this->userSession->isBulgaria())
    {
        if (approvalType == 1) {
            subject = nMessage(CMsgStream(), CMSG_ORD_CREMA_GUID_SUBJECT_CLOSE_CREDIT, orderNo, customerNo, customerName.c_str()).String();

            tmp = nMessage(CMsgStream(), CMSG_ORD_CREMA_MAIL_GUID_TIME_FILLER).String();
            bodyMessage = nMessage(CMsgStream(), CMSG_ORD_CREMA_MAIL_BODY_CLOSE_CREDIT, orderNo, customerNo, apothecary.c_str(), reason.c_str(), comment.c_str()).String();
        }
        else {
            subject = nMessage(CMsgStream(), CMSG_ORD_CREMA_GUID_SUBJECT_CLOSE, orderNo, customerNo, customerName.c_str()).String();

            tmp = nMessage(CMsgStream(), CMSG_ORD_CREMA_MAIL_GUID_TIME_FILLER).String();
            bodyMessage = nMessage(CMsgStream(), CMSG_ORD_CREMA_MAIL_BODY_CLOSE, orderNo, customerNo, apothecary.c_str(), reason.c_str(), comment.c_str()).String();

        }
    }
    else
    {
        subject = nMessage(CMsgStream(), CMSG_ORD_CREMA_GUID_SUBJECT_CLOSE, orderNo, customerNo, customerName.c_str(), place.c_str()).String();

        tmp = nMessage(CMsgStream(), CMSG_ORD_CREMA_MAIL_GUID_TIME_FILLER).String();
        bodyMessage = nMessage(CMsgStream(), CMSG_ORD_CREMA_MAIL_BODY_CLOSE, orderNo, customerNo, apothecary.c_str(), date,
            tmp.c_str(), time, user.c_str(), reason.c_str()).String();
    }
    boost::erase_all(subject, "\n");
    //boost::erase_all(bodyMessage, "\n");
    replaceLineEndings(bodyMessage);
    message->setSubject(subject);
    message->setBody(bodyMessage);

    sentFromAddress.erase(sentFromAddress.find_last_not_of(" \n\r\t") + 1);
    message->setFrom(sentFromAddress);

    message->setContentType(basar::cmnutil::MailMessage::TEXT_PLAIN);

    int count = 0;
    std::vector< std::pair<std::string, CremaMailHandler::MAILTYPE> >::iterator it = mailSentToAddresses.begin();
    for (; it != mailSentToAddresses.end(); ++it)
    {
        count++;
        tmp = (*it).first;
        tmp.erase(tmp.find_last_not_of(" \n\r\t") + 1);
        message->setTo(tmp);

        //TODO
        nMessage error(CMsgStream(), CMSG_ORD_LIBMAIL_MAILSEND_ADDRESS, __FUNCTION__, 0, 0 ? CremaMailHandler::UNLOCK_INFO : CremaMailHandler::UNLOCK_DATA, count, tmp.c_str());
        userSession->WriteLog(error.String(), nSTATE_CONDITION, CMSG_ORD_LIBMAIL_MAILSEND_ADDRESS);
    }

    bool wasSend = SendGUIDMail(*message, server, port);

    delete message;
    message = NULL;
    return wasSend;
}

bool CremaMailHandler::SendCremaCancelInfoMail(std::string guid, int orderNo, int customerNo, std::string customerName,
    std::string apothecary, std::string place, std::string user, std::string reason, std::string comment)
{
    std::vector< std::pair<std::string, CremaMailHandler::MAILTYPE> > mailSentToAddresses;
    std::string sentFromAddress = "";
    std::string server = "";
    int port = -1;
    basar::cmnutil::MailMessage* message = NULL;

    if (this->userSession->isBulgaria()) {
        message = new basar::cmnutil::MailMessage(basar::cmnutil::Locale::BULGARIAN_BG);
    }
    else {
        message = new basar::cmnutil::MailMessage();
    }
    std::string tmp;

    std::time_t rawtime;
    std::tm* timeinfo;
    char time[40];
    char date[40];

    std::time(&rawtime);
    timeinfo = std::localtime(&rawtime);

    std::strftime(time, 80, "%H:%M:%S", timeinfo);
    std::strftime(date, 80, "%d.%m.%Y", timeinfo);

    if (guid.length() <= 0) // called directly from AE or aaorderclose (not from WebSite) --> guid not filled yet
        guid = getGuidForOrder(orderNo);

    GetEmailAddressesForGUID(mailSentToAddresses, sentFromAddress, guid, server, port);

    std::string subject = "";
    std::string bodyMessage = "";

    if (this->userSession->isBulgaria())
    {
        subject = nMessage(CMsgStream(), CMSG_ORD_CREMA_GUID_SUBJECT_CANCEL, orderNo, customerNo, customerName.c_str()).String();

        bodyMessage = nMessage(CMsgStream(), CMSG_ORD_CREMA_MAIL_BODY_CANCEL, orderNo, customerNo, customerName.c_str(), reason.c_str(), comment.c_str()).String();
    }
    else
    {
        subject = nMessage(CMsgStream(), CMSG_ORD_CREMA_GUID_SUBJECT_CANCEL, orderNo, customerNo, customerName.c_str(), place.c_str()).String();

        tmp = nMessage(CMsgStream(), CMSG_ORD_CREMA_MAIL_GUID_TIME_FILLER).String();
        bodyMessage = nMessage(CMsgStream(), CMSG_ORD_CREMA_MAIL_BODY_CANCEL, orderNo, customerNo, apothecary.c_str(), date,
            tmp.c_str(), time, user.c_str(), reason.c_str()).String();
    }


    boost::erase_all(subject, "\n");
    //boost::erase_all(bodyMessage, "\n");
    replaceLineEndings(bodyMessage);
    message->setSubject(subject);
    message->setBody(bodyMessage);

    sentFromAddress.erase(sentFromAddress.find_last_not_of(" \n\r\t") + 1);
    message->setFrom(sentFromAddress);

    message->setContentType(basar::cmnutil::MailMessage::TEXT_PLAIN);

    int count = 0;
    std::vector< std::pair<std::string, CremaMailHandler::MAILTYPE> >::iterator it = mailSentToAddresses.begin();
    for (; it != mailSentToAddresses.end(); ++it)
    {
        count++;
        tmp = (*it).first;
        tmp.erase(tmp.find_last_not_of(" \n\r\t") + 1);
        message->setTo(tmp);

        //TODO
        nMessage error(CMsgStream(), CMSG_ORD_LIBMAIL_MAILSEND_ADDRESS, __FUNCTION__, 0, 0 ? CremaMailHandler::UNLOCK_INFO : CremaMailHandler::UNLOCK_DATA, count, tmp.c_str());
        userSession->WriteLog(error.String(), nSTATE_CONDITION, CMSG_ORD_LIBMAIL_MAILSEND_ADDRESS);
    }

    bool wasSend = SendGUIDMail(*message, server, port);

    delete message;
    message = NULL;
    return wasSend;
}

bool CremaMailHandler::wasMailSendWarningPartner(int partnerNo, short branchNo, double dlPercentage)
{
    bool wasSend = false;
    pxCremaMailList dlist(this->userSession);

    //C_CHECKWASSEND_WARNING_PARTNERNR
    dlist.SelectWasSendWarningPartner(partnerNo, branchNo, CremaMailHandler::WARN, dlPercentage);
    if (dlist.Entries() == 0)
    {
        wasSend = false;
    }
    else if (dlist.Entries() >= 1)
    {
        dlist.Clear();
        wasSend = true;
    }

    return wasSend;
}

bool CremaMailHandler::wasMailSendOrder(const long orderNo, const short branchno)
{
    bool wasSend = false;
    pxCremaMailList dlist(this->userSession);

    //cCRSDEBTMAIL_CHECKWASSEND_ORDER
    dlist.Clear();
    dlist.SelectWasSendOrder(orderNo, branchno);
    if (dlist.Entries() == 0)
    {
        wasSend = false;
    }
    else if (dlist.Entries() >= 1)
    {
        wasSend = true;
    }

    return wasSend;
}

bool CremaMailHandler::wasMailSendAmountPartner(const int partnerNo, const short branchNo, const double amount)
{
    bool wasSend = false;
    pxCremaMailList dlist(this->userSession);

    //cCRSDEBTMAIL_CHECKWASSEND_AMOUNT_PARTNER
    dlist.Clear();
    dlist.SelectWasSendAmountPartner(partnerNo, branchNo, amount);
    if (dlist.Entries() == 0)
    {
        wasSend = false;
    }
    else if (dlist.Entries() >= 1)
    {
        wasSend = true;
    }

    return wasSend;
}

void CremaMailHandler::fillCremaMailData(tCREMAMAIL* data, pxCremaMailList* dlist)
{
    pxCremaMail* dikp;               // ptr to list entry
    pxCremaMailListIter cursor(*dlist);  // define an iterator
    dikp = (pxCremaMail*) ++cursor;

    data->DLPERCENTAGE = dikp->DlPercentage();
    dikp->Guid().GetData(data->GUID);
    data->KDAUFTRAGNR = dikp->KdAuftragNr();
    data->PORT = dikp->Port();
    data->SENDDATE = dikp->SendDate();
    dikp->SentFromAddress().GetData(data->SENTFROMADDRESS);
    dikp->SentToAddress().GetData(data->SENTTOADDRESS);
    dikp->Server().GetData(data->SERVER);
    data->WASSEND = dikp->WasSend();
    data->SMTPUSERGROUPID = dikp->SmtpUserGroupID();
    dikp->URL().GetData(data->URL);
    data->THRESHOLDAMOUNT = dikp->ThresholdAmount();
    data->CREMATYPEID = dikp->CremaTypeID();

    dlist->Clear();
}

bool CremaMailHandler::getCremaMailDataLevel(CremaMailHandler::MAILLEVEL level, short branchNo, tCREMAMAIL* data)
{
    pxCremaMailList dlist(this->userSession);

    dlist.SelectDataForLevel(static_cast<short>(level), branchNo);

    if (dlist.Entries() == 0)
    {
        nMessage error(CMsgStream(), CMSG_ORD_NO_DATA_FOR_CREMA, level);
        userSession->WriteLog(error.String(), nSTATE_CONDITION, CMSG_ORD_NO_DATA_FOR_CREMA);

        return false;
    }
    else if (dlist.Entries() > 1)
    {
        nMessage error(CMsgStream(), CMSG_ORD_TO_MUCH_DATA_FOR_CREMA, level);
        userSession->WriteLog(error.String(), nSTATE_CONDITION, CMSG_ORD_TO_MUCH_DATA_FOR_CREMA);

        dlist.Clear();
        return false;
    }

    fillCremaMailData(data, &dlist);

    return true;
}

bool CremaMailHandler::getCremaMailDataPercentage(double dlPercentage, short branchNo, tCREMAMAIL* data)
{
    pxCremaMailList dlist(this->userSession);

    dlist.SelectDataForPercentage(dlPercentage, branchNo);

    if (dlist.Entries() == 0)
    {
        nMessage error(CMsgStream(), CMSG_ORD_NO_DATA_FOR_CREMA, dlPercentage);
        userSession->WriteLog(error.String(), nSTATE_CONDITION, CMSG_ORD_NO_DATA_FOR_CREMA);

        return false;
    }
    else if (dlist.Entries() > 1)
    {
        nMessage error(CMsgStream(), CMSG_ORD_TO_MUCH_DATA_FOR_CREMA, dlPercentage);
        userSession->WriteLog(error.String(), nSTATE_CONDITION, CMSG_ORD_TO_MUCH_DATA_FOR_CREMA);

        dlist.Clear();
        return false;
    }

    fillCremaMailData(data, &dlist);

    return true;
}

bool CremaMailHandler::getCremaMailDataAmount(double amount, short branchNo, tCREMAMAIL* data)
{
    pxCremaMailList dlist(this->userSession);

    dlist.SelectDataForAmount(amount, branchNo);

    if (dlist.Entries() == 0)
    {
        nMessage error(CMsgStream(), CMSG_ORD_NO_DATA_FOR_CREMA, amount);
        userSession->WriteLog(error.String(), nSTATE_CONDITION, CMSG_ORD_NO_DATA_FOR_CREMA);

        return false;
    }
    else if (dlist.Entries() > 1)
    {
        nMessage error(CMsgStream(), CMSG_ORD_TO_MUCH_DATA_FOR_CREMA, amount);
        userSession->WriteLog(error.String(), nSTATE_CONDITION, CMSG_ORD_TO_MUCH_DATA_FOR_CREMA);

        dlist.Clear();
        return false;
    }

    fillCremaMailData(data, &dlist);

    return true;
}

bool CremaMailHandler::deleteMail(long orderNo, short branchNo)
{
    tCREMAMAIL mail;
    mail.KDAUFTRAGNR = orderNo;
    mail.BRANCHNO = branchNo;
    pxCremaMail entry(this->userSession, mail);
    entry.Delete();
    if (!entry.IsGoodState())
    {
        nMessage error(CMsgStream(), CMSG_ORD_CREMA_MAIL_DELETE_ERROR, orderNo);
        userSession->WriteLog(error.String(), nSTATE_CONDITION, CMSG_ORD_CREMA_MAIL_DELETE_ERROR);
    }
    return true;
}

