/*
 * writenewcallbackuc.h
 *
 *  Created on: 08.06.2016
 *  Author: sebastian.barth
 */

#ifndef GUARD_LIBCSC_IBT_UC_WRITENEWCALLBACKUC_H
#define GUARD_LIBCSC_IBT_UC_WRITENEWCALLBACKUC_H

#include "callback/repository/irepositoryptr.h"
#include "callback/domainmodule/icallbackitemptr.h"
#include "callback/domainmodule/icritptr.h"
#include "callback/domainmodule/icritposptr.h"
#include "callback/domainmodule/inewcallbackptr.h"
#include <libbasarcmnutil_bstring.h>
#include <base/irunnable.h>
#include <base/iint32result.h>
#include "util/istringresource.h"

namespace libcsc {
namespace callback {
namespace uc {

class WriteNewCallbackUC : public base::IRunnable, public base::IInt32Result
{
public:
    WriteNewCallbackUC();
    virtual ~WriteNewCallbackUC();

    void injectRepository(repo::IRepositoryPtr repository);
    void injectStringResource(util::IStringResourcePtr stringResource);
	void injectSmptServer(const basar::VarString& smtpServer, const short smtpPort);
    void setNewCallback(domMod::INewCallbackPtr const newCallback);
    void run();

    basar::Int32 getInt32Result() const;

private:
    static basar::VarString const BaseMailFormatString;
    static basar::VarString const ExtendedMailFormatString;
    static basar::VarString const MailLinkFormatString;
    static basar::VarString const CritFormatString;
    static basar::VarString const MailSubjectFormatString;

    repo::IRepositoryPtr m_Repository;
    util::IStringResourcePtr m_StringResource;
    domMod::ICallbackItemPtr m_CallbackItem;
    domMod::ICritPtr m_Crit;
    domMod::ICritPosPtr m_CritPos;
    basar::VarString m_CritText;
    basar::VarString m_ContactPerson;
    basar::VarString m_CallbackWantedText;
    basar::VarString m_CallbackUrl;
    bool m_SendEmail;
	basar::VarString m_MailServer;
	short m_MailPort;

    basar::Int32 m_CallbackNo;

    void writeCallback();
    basar::VarString formatCritText();

    void sendMail();
    basar::VarString formatMailSubject();
    basar::VarString formatMailText();

    basar::VarString idToString(int const msgId);
};

typedef boost::shared_ptr<WriteNewCallbackUC> WriteNewCallbackUCPtr;

} // end namespace uc
} // end namespace callback
} // end namespace libcsc

#endif // GUARD_LIBCSC_IBT_UC_WRITENEWCALLBACKUC_H
