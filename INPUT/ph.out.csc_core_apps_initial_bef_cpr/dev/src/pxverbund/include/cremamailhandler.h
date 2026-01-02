#ifndef __PP_CREMAMAILHANDLER_H_
#define __PP_CREMAMAILHANDLER_H_

#include <string>
#include <vector>
#include <libbasarcmnutil_email.h>

class pxSession;
class pxCustBase;
class pxDebitLimit;
class pxCremaMailList;
class nString;
struct tCREMAMAIL;

namespace basar {
    namespace cmnutil {
        class MailMessage;
    }
}

class CremaMailHandler
{
public:
    CremaMailHandler( pxSession* session );
    ~CremaMailHandler();

    bool sendMail(double dlPercentage, double creditLimit, double usedCredit, double orderValue, long orderNo,
            pxCustBase* custBase);
    bool processWarningMailRequest(int partnerNo, pxCustBase* custBase = NULL);
    bool deleteMail(long orderNo, short branchNo);
    bool SendCremaDiscussionInfoMail(std::string guid, int orderNo, int customerNo, std::string customerName, std::string apothecary, std::string place, double orderAmount, std::string URL);
    bool SendCremaClosedInfoMail(std::string guid, int orderNo, int customerNo, std::string customerName, std::string apothecary, std::string place, std::string user, std::string reason, std::string comment = "", int approvalType = 1);
    bool SendCremaCancelInfoMail(std::string guid, int orderNo, int customerNo, std::string customerName, std::string apothecary, std::string place, std::string user, std::string reason, std::string comment = "");

    enum MAILTYPE{UNLOCK_DATA, UNLOCK_INFO};

private:
    // forbidden
    CremaMailHandler();

    static const int MAX_SIZE = 10260;
    static const int MAX_SIZE_SUBJECT = 100;
    static const int MAIL_SIZE = 50;

    pxSession* userSession;
    enum MAILLEVEL{NO_MAIL, WARN, UNLOCK, HIGH_UNLOCK, AMOUNT};
    CremaMailHandler::MAILLEVEL levelPercentage;
    CremaMailHandler::MAILLEVEL levelAmount;

    bool initMail(tCREMAMAIL mailData, long kdAuftragNr, double creditLimit, double dlPercentage,
            double usedCredit, double orderValue, const char* url, pxCustBase* custBase, CremaMailHandler::MAILLEVEL level, bool infoMailGroup,
            std::vector< std::pair<std::string, CremaMailHandler::MAILTYPE> >& mailSentToAddresses, basar::cmnutil::MailMessage& message, int partnerNo);

    bool processWarningMailRequest(int partnerNo, short branchNo, pxDebitLimit debtLimit);
    bool processWarningMailRequest(int partnerNo, pxDebitLimit debtLimit, pxCremaMailList& dlist);

    bool wasMailSendWarningPartner(const int partnerNo, const short branchNo, const double dlPercentage);
    bool wasMailSendOrder(const long orderNo,const short branchno);
    bool wasMailSendAmountPartner(const int partnerNo, const short branchNo, const double amount);

    bool getCremaMailDataPercentage(double dlPercentage, short branchNo, tCREMAMAIL* data);
    bool getCremaMailDataAmount(double amount, short branchNo, tCREMAMAIL* data);
    bool getCremaMailDataLevel(CremaMailHandler::MAILLEVEL level, short branchNo, tCREMAMAIL* data);

    void fillCremaMailData(tCREMAMAIL* data, pxCremaMailList *dlist);
    bool sendMail(tCREMAMAIL* data, long orderNo, double creditLimit, double dlPercentage,
            double usedCredit, double orderValue, pxCustBase* custBase, CremaMailHandler::MAILLEVEL level, CremaMailHandler::MAILTYPE type,
            std::vector< std::pair<std::string, CremaMailHandler::MAILTYPE> >& mailSentToAddresses, int partnerNo);

    void setMailTextWarning(std::string& partnerName, int partnerNo, double dlPercentage, double creditLimit, std::string& body);
    void setMailTextAmount(std::string& partnerName, int partnerNo, double thresholdAmount, double usedCredit, std::string& body);
    void setMailTextUnLock(long kdAuftragNr, double creditLimit, double dlPercentage, double usedCredit, double orderValue,
            const char* url, pxCustBase* custBase, bool infoMailGroup, std::string& body);

    bool setMailLevels(double dlPercentage, double usedCreditAmount);
    bool setMailLevelAmount(double usedCreditAmount);
    bool setMailLevelPercentage(double dlPercentage);

    std::ifstream* CMsgStream();
    bool replaceLineEndings(std::string& subject);
    std::string parseCurrency(double orderValue);
    bool processConfiguredMailGroups(tCREMAMAIL* data, long orderNo, double creditLimit, double dlPercentage,
            double usedCredit, double orderValue, pxCustBase* custBase, CremaMailHandler::MAILLEVEL level, int partnerNo = -1);
    bool getMailSentToAddresses(int smtpUserGroupId, CremaMailHandler::MAILTYPE type, std::vector< std::pair<std::string, CremaMailHandler::MAILTYPE> >& mailSentToAddresses);
    bool getGVLMailSentToAddress(int smtpUserGroupId, short branchNo, short salesManNo, CremaMailHandler::MAILTYPE type, std::vector< std::pair<std::string, CremaMailHandler::MAILTYPE> >& mailSentToAddresses);
    bool getGVLMailAddressesForPartner(int smtpUserGroupId, short branchNo, int partnerNo,
            CremaMailHandler::MAILTYPE type, std::vector< std::pair<std::string, CremaMailHandler::MAILTYPE> >& mailSentToAddresses);
    bool sendEmailType(tCREMAMAIL* data, long orderNo, double creditLimit, double dlPercentage,
            double usedCredit, double orderValue, pxCustBase* custBase, CremaMailHandler::MAILLEVEL level, CremaMailHandler::MAILTYPE type, int partnerNo);

    void GetEmailAddressesForGUID(std::vector< std::pair<std::string, CremaMailHandler::MAILTYPE> >& mailSentToAddresses, std::string& sentFromAddress, std::string guid, std::string&server, int& port);
    bool SendGUIDMail(basar::cmnutil::MailMessage& message, std::string server, int port);
    std::string getLanguageForPartner(int partnerNo);
    std::string getGuidForOrder(long orderNo);

    std::pair<std::string, CremaMailHandler::MAILTYPE> convertToSendToAdress(nString& sendToAdress, CremaMailHandler::MAILTYPE mailtype);
};

#endif
