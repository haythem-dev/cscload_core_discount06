/*
 * writenewcallbackuc.cpp
 *
 *  Created on: 08.06.2016
 *  Author: sebastian.barth
 */

#include "writenewcallbackuc.h"
#include "callback/domainmodule/callbackcustomerdm.h"
#include "callback/domainmodule/callbackitemdmptr.h"
#include "callback/domainmodule/callbackitemdm.h"
#include "callback/domainmodule/callbackreasondm.h"
#include "callback/domainmodule/callbackdivisiondm.h"
#include "callback/domainmodule/icallbackcustomerptr.h"
#include "callback/domainmodule/icallbackreasonptr.h"
#include "callback/domainmodule/critdmptr.h"
#include "callback/domainmodule/critdm.h"
#include "callback/domainmodule/critposdmptr.h"
#include "callback/domainmodule/critposdm.h"
#include "callback/domainmodule/newcallbackdm.h"
#include "callback/exceptions/customernotfoundexception.h"
#include "callback/repository/irepository.h"
#include "logger/loggerpool.h"
#include <libbasarcmnutil_datetime.h>
#include <emailhandler.h>
#include <boost/algorithm/string/replace.hpp>
#include "exceptions/sqlnotfoundexception.h"
#include "types/messagecodeenum.inc"

namespace libcsc {
namespace callback {
namespace uc {

basar::VarString const WriteNewCallbackUC::BaseMailFormatString("%s: %s\n%s\n\n%s\n%s %s\n%s: %s\n%s: %s\n%s: %s / %d\n%s: %d\n\n%s: %s");
basar::VarString const WriteNewCallbackUC::ExtendedMailFormatString("%s\n\n%s:\n%s");
basar::VarString const WriteNewCallbackUC::MailLinkFormatString("<%s?callbackno=%d&branchno=%d>");
basar::VarString const WriteNewCallbackUC::CritFormatString("%s\r\n%s: %s\r\n%s");
basar::VarString const WriteNewCallbackUC::MailSubjectFormatString("%s: %s / %s");

WriteNewCallbackUC::WriteNewCallbackUC()
    : m_CallbackItem(domMod::CallbackItemDM::create()), m_Crit(domMod::CritDM::create()), m_CritPos(domMod::CritPosDM::create()),
      m_CallbackNo(0)
{
}

WriteNewCallbackUC::~WriteNewCallbackUC()
{
}

void WriteNewCallbackUC::injectRepository(repo::IRepositoryPtr repository)
{
    m_Repository = repository;
}

void WriteNewCallbackUC::injectStringResource(util::IStringResourcePtr stringResource)
{
    m_StringResource = stringResource;
}

void WriteNewCallbackUC::injectSmptServer(const basar::VarString& smtpServer, const short smtpPort)
{
	m_MailServer = smtpServer;
	m_MailPort = smtpPort;
}


void WriteNewCallbackUC::setNewCallback(domMod::INewCallbackPtr const newCallback)
{
    m_Crit->setBranchNo(newCallback->getBranchNo());
    m_Crit->setCritLevel(newCallback->getCritLevel());
    m_Crit->setCustomerNo(newCallback->getCustomerNo());
    m_Crit->setCstBranchNo(newCallback->getCstBranchNo());
    m_Crit->setUId(newCallback->getUId());

    m_CritPos->setBranchNo(newCallback->getBranchNo());
    m_CritPos->setWindowsUserId(newCallback->getWindowsUser());
    m_CritPos->setSourceApplication(newCallback->getSourceApplication());
    m_CritPos->setUId(newCallback->getUId());

    m_CallbackItem->setCallbackDateWished(newCallback->getCallbackDateWished());
    m_CallbackItem->setCallbackTimeWished(newCallback->getCallbackTimeWished());
    m_CallbackItem->setCallbackPartNo((Int32)newCallback->getDivisionNo());
    m_CallbackItem->setDivisionNo(newCallback->getDivisionNo());
    m_CallbackItem->setReasonNo(newCallback->getReasonNo());
    m_CallbackItem->setState(newCallback->getState());
    m_CallbackItem->setCallbackStatus(newCallback->getCallbackStatus());
    m_CallbackItem->setReference(newCallback->getReference());

    m_CritText = newCallback->getCritText();
    m_CritText.trim();
    m_ContactPerson = newCallback->getContactPerson();
    m_ContactPerson.trim();
    m_CallbackWantedText = newCallback->getCallbackWantedText();
    m_CallbackWantedText.trim();
    m_CallbackUrl = newCallback->getWebSiteBaseUrl();
    m_CallbackUrl.trim();

    m_SendEmail = newCallback->getSendEmail();
}

void WriteNewCallbackUC::run()
{
    BLOG_TRACE_METHOD(LoggerPool::getLoggerCallback(), "WriteNewCallbackUC::run()");

    writeCallback();

    if (m_SendEmail)
    {
        sendMail();
    }
}

void WriteNewCallbackUC::writeCallback()
{
    BLOG_TRACE_METHOD(LoggerPool::getLoggerCallback(), "WriteNewCallbackUC::writeCallback()");
    
    domMod::ICallbackReasonPtr reason = m_Repository->findCallbackReason(m_Crit->getCstBranchNo(), m_CallbackItem->getDivisionNo(), m_CallbackItem->getReasonNo());

    basar::DateTime now = basar::DateTime::getCurrent();

    m_Crit->setTitle(reason->getReasonName());
    m_Crit->setDate(now.getDate());
    m_Crit->setTime(now.getTime() / 1000);

    m_CritPos->setText(formatCritText());
    m_CritPos->setDate(now.getDate());
    m_CritPos->setTime(now.getTime() / 1000);
    m_CritPos->setPosTypeTag(VarString("1"));

    m_CallbackItem->setCallbackTime(30);
    m_CallbackItem->setLockTag(VarString("0"));
    m_CallbackItem->setPosTypeTag(m_CritPos->getPosTypeTag());
    m_CallbackItem->setPosNoDone(0);

    m_CallbackNo = m_Repository->writeNewCallback(m_CallbackItem, m_Crit, m_CritPos);
}

basar::VarString WriteNewCallbackUC::formatCritText()
{
    basar::VarString critText;
    basar::VarString txtContact = m_StringResource->getString(idToString(CMSG_LIBCSC_CONTACT));
    critText.format(CritFormatString.c_str(), m_CallbackWantedText.c_str(), txtContact.c_str(), m_ContactPerson.c_str(), m_CritText.c_str());
    return critText;
}

basar::VarString WriteNewCallbackUC::idToString(int const msgId)
{
    basar::VarString key;
    key.itos(msgId);
    return key;
}

#define EMAILADDRESS "ae@phoenixgroup.eu" // TODO
void WriteNewCallbackUC::sendMail()
{
    basar::VarString mailingList = m_Repository->getCallbackMailingList(m_Crit->getCstBranchNo(), m_CallbackItem->getDivisionNo(), m_CallbackItem->getReasonNo());
    mailingList.trim();
    if (mailingList.empty())
    {
        return;
    }

    EMailHandler mail(m_MailServer, m_MailPort);
    mail.setSender(EMAILADDRESS);
    mail.setRecipientList((char*)mailingList.c_str());
    mail.setSubject(formatMailSubject());
    mail.setText(formatMailText());
    if (!mail.sendMail())
    {
        throw basar::Exception(basar::ExceptInfo("WriteNewCallbackUC::sendMail()", "eMail not sent", __FILE__, __LINE__), "");
    }
}

basar::VarString WriteNewCallbackUC::formatMailSubject()
{
    const basar::Int16 critLevel = m_Crit->getCritLevel();
    basar::VarString txtCritLevel = m_StringResource->getString(idToString(CMSG_LIBCSC_CRITLEVEL_0 + critLevel));

    basar::VarString mailSubject;
    domMod::ICallbackDivisionPtr division = m_Repository->findCallbackDivision(m_Crit->getCstBranchNo(), m_CallbackItem->getDivisionNo());

    mailSubject.format(MailSubjectFormatString.c_str(), txtCritLevel.c_str(), division->getDivisionName().c_str(), m_Crit->getTitle().c_str());

    return mailSubject;
}

basar::VarString WriteNewCallbackUC::formatMailText()
{
    basar::VarString userName;

    domMod::ICallbackCustomerPtr customer = m_Repository->findCustomer(m_Crit->getBranchNo(), m_Crit->getCustomerNo());
    if (m_CritPos->getUId() == static_cast<libcsc::Int32>(0))
    {
        userName = m_CritPos->getWindowsUserId();
    }
    else
    {
        userName = m_Repository->findUserName(m_CritPos->getBranchNo(), m_CritPos->getUId());
    }
    userName.trim();

    basar::VarString txtCreator = m_StringResource->getString(idToString(CMSG_LIBCSC_CREATOR));
    basar::VarString txtContact = m_StringResource->getString(idToString(CMSG_LIBCSC_CONTACT));
    basar::VarString txtTelefon = m_StringResource->getString(idToString(CMSG_LIBCSC_TELEFON));
    basar::VarString txtSpeedDial = m_StringResource->getString(idToString(CMSG_LIBCSC_SPEEDDIAL));
    basar::VarString txtCustomerNo = m_StringResource->getString(idToString(CMSG_LIBCSC_CUSTOMERNO));
    basar::VarString txtLink = m_StringResource->getString(idToString(CMSG_LIBCSC_LINK));
    basar::VarString link;
    link.format(MailLinkFormatString.c_str(), m_CallbackUrl.c_str(), m_CallbackNo, basar::Int16(m_Crit->getBranchNo()));
    boost::replace_all(link, " ", "%20");

    basar::VarString mailText;
    mailText.format(BaseMailFormatString.c_str(),
        txtCreator.c_str(), userName.c_str(), m_CallbackWantedText.c_str(), customer->getPharmacyName().c_str(), customer->getZipCode().c_str(), customer->getCity().c_str(),
        txtContact.c_str(), m_ContactPerson.c_str(),
        txtTelefon.c_str(), customer->getTelefonNo().c_str(),
        txtSpeedDial.c_str(), customer->getSpeedDialNo().c_str(), basar::Int16(customer->getBranchNo()),
        txtCustomerNo.c_str(), basar::Int32(customer->getCustomerNo()), txtLink.c_str(), link.c_str());
    if (!basar::VarString(m_CritPos->getText()).empty())
    {
        basar::VarString txtMoreInfo = m_StringResource->getString(idToString(CMSG_LIBCSC_MOREINFO));
        mailText.format(ExtendedMailFormatString.c_str(), mailText.c_str(), txtMoreInfo.c_str(), m_CritText.c_str());
    }
    return mailText;
}

basar::Int32 WriteNewCallbackUC::getInt32Result() const
{
    return m_CallbackNo;
}

} // end namespace uc
} // end namespace callback
} // end namespace libcsc
