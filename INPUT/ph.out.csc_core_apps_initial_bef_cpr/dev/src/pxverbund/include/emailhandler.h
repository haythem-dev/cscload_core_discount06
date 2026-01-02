#ifndef __PP_EMAILHANDLER_H_
#define __PP_EMAILHANDLER_H_

#include <libbasarcmnutil_email.h>

class EMailHandler
{
public:
    EMailHandler(const basar::VarString& server, const short port);
    ~EMailHandler();
    void setSender(const basar::VarString& sender);                     //Absender
    void addRecipient(const basar::VarString& recipient);               //Empfänger
    void setRecipientList(const basar::VarString& recipientlist);       //EmpfängerListe
    void setTitle(const basar::VarString& title);                       //Betreffzeile (old)
    void setSubject(const basar::VarString& subject);                   //Betreffzeile
    void setText(const basar::VarString& text);                         //Mailtext
    bool sendMail();

private:
    basar::VarString m_Server;
    short            m_Port;
    basar::cmnutil::MailMessage mailMsg;
};

#endif
