#ifndef GUARD_IBTORDERIMPORT_USECASE_MAINUC_H
#define GUARD_IBTORDERIMPORT_USECASE_MAINUC_H

#include "componentmanager/ibtorderimportapplcompmgrptr.h"
#include "componentmanager/iusecasegetterptr.h"
#include <persistence/itransactionfactoryptr.h>
#include <infrastructure/mail/imailalertptr.h>
#include <libutil/irunnable.h>
#include <libbasarcmnutil_bstring.h>
#include "iibtordergetterptr.h"
#include <ibt/ibtrequest/iibtrequestrepositoryptr.h>
#include <ibt/ibtresponse/iibtresponserepositoryptr.h>
#include "domainmodule/ipxtaskcontrolptr.h"
#include <infrastructure/session/isessionptr.h>
#include "domainmodule/ipxordertransmitptr.h"
//#include <usecase/inachlieferposwriterptr.h>

namespace log4cplus
{
    class Logger;
}

namespace ibtorderimport
{
namespace useCase
{
class MainUC : public libutil::useCase::IRunnable
{
public:
    MainUC();
    virtual ~MainUC();

    void injectMailAlert( infrastructure::mail::IMailAlertPtr mailAlert );
	void injectIbtOrderGetter( IIbtOrderGetterPtr );
	void injectIbtRequestRepository( libcsc::ibt::IIbtRequestRepositoryPtr repo );
	void injectIbtResponseRepository( libcsc::ibt::IIbtResponseRepositoryPtr repo );
	void injectTaskControl( domMod::IPxTaskControlPtr );
	void injectSession( libutil::infrastructure::session::ISessionPtr );
	void injectPxOrderTransmit(domMod::IPxOrderTransmitPtr);
    void injectTransactionFactory( libcsc::persistence::ITransactionFactoryPtr transactionFactory );
    //void injectNachlieferPosWriter( INachlieferPosWriterPtr nachlieferPosWriter );

	void setBranchNo( const basar::Int16 branchno );
		
	virtual void run();

private:
    MainUC(const MainUC& );
    MainUC& operator= (const MainUC& );

	infrastructure::mail::IMailAlertPtr										getMailAlert();
	libutil::infrastructure::session::ISessionPtr							getSession();
	domMod::IPxOrderTransmitPtr												getPxOrderTransmit();

	void																	sendMail(basar::cmnutil::CollBString& errorList);
				
	IIbtOrderGetterPtr														getIbtOrderGetter();
	const log4cplus::Logger&												getLogger();				
	domMod::IPxTaskControlPtr												getTaskControl();
                    
				
    const log4cplus::Logger&												m_Logger;
	infrastructure::mail::IMailAlertPtr										m_MailAlert;

	IIbtOrderGetterPtr														m_IIbtOrderGetter; // only read once per branch, resultset is collection of several parameter rows!
	domMod::IPxTaskControlPtr												m_TaskControl;

	libutil::infrastructure::session::ISessionPtr							m_Session;
				
	libcsc::ibt::IIbtRequestRepositoryPtr									m_IbtRequestRepository;     
	libcsc::ibt::IIbtResponseRepositoryPtr									m_IbtResponseRepository;     
	domMod::IPxOrderTransmitPtr												m_PxOrderTransmit;
    libcsc::persistence::ITransactionFactoryPtr								m_TransactionFactory;
	//INachlieferPosWriterPtr													m_NachlieferPosWriter;
	basar::Int16															m_BranchNo;
};

} // namespace useCase
} // namespace ibtorderimport

#endif //end GUARD_IBTORDERIMPORT_USECASE_MAINUC_H
