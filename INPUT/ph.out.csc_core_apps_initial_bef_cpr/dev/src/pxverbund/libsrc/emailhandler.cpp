#include "emailhandler.h"

EMailHandler::EMailHandler(const basar::VarString& server, const short port) :
    m_Server(server),
    m_Port(port)
{
    mailMsg.setContentType(basar::cmnutil::MailMessage::TEXT_PLAIN);
}

EMailHandler::~EMailHandler()
{
}

void EMailHandler::setSender(const basar::VarString& sender)            //Absender
{
    mailMsg.setFrom(sender);
}

void EMailHandler::addRecipient(const basar::VarString& recipient)      //Empfänger
{
    mailMsg.setTo(recipient);
}

void EMailHandler::setRecipientList(const basar::VarString& recipientlist)      //Empfängerliste
{
    basar::cmnutil::CollBString recipients = recipientlist.tokenizeAndTrim(";", basar::cmnutil::BString::FIRST_END, true, true);
    basar::cmnutil::CollBString::const_iterator it = recipients.begin();
    while (it != recipients.end())
    {
        this->addRecipient(*it);
        ++it;
    }
}

void EMailHandler::setTitle(const basar::VarString& title)      //Betreffzeile (old)
{
    mailMsg.setSubject(title);
}

void EMailHandler::setSubject(const basar::VarString& subject)  //Betreffzeile
{
    mailMsg.setSubject(subject);
}

void EMailHandler::setText(const basar::VarString& text)                //Mailtext
{
    mailMsg.setBody(text);
}

bool EMailHandler::sendMail()
{
    if (m_Server.empty())
    {
        return false;
    }
    basar::cmnutil::Smtp mailService(m_Server, m_Port);
//  basar::cmnutil::Smtp mailService("10.100.121.30", 25); // TODO FN read from database (table smtp)
    basar::cmnutil::Smtp::RetCodeEnum retCode;
    try
    {
        mailService.connect();
        retCode = mailService.send(mailMsg);
        mailService.disconnect();
    }
    catch (...)
    {
        mailService.disconnect();
        return false;
    }
    return (retCode == basar::cmnutil::Smtp::SMTP_SUCCESS);
}
