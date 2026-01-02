#ifndef GUARD_IBTORDERIMPORT_COMPONENTMANAGER_IBTORDERIMPORTAPPLCOMPMGR_H
#define GUARD_IBTORDERIMPORT_COMPONENTMANAGER_IBTORDERIMPORTAPPLCOMPMGR_H

#include <libutil/irunnableptr.h>
#include "infrastructure/cmdline/ibtorderimportcmdlineevaluator.h"

#include <persistence/connectionptr.h>
#include <persistence/iaccessorptr.h>
#include <persistence/itransactionfactory.h>

#include "infrastructure/mail/imailalertptr.h"

#include <ibt/ibtrequest/iibtrequestrepositoryptr.h>
#include <ibt/ibtresponse/iibtresponserepositoryptr.h>
#include <ibt/componentmanager/ibtcomponentmanagerptr.h>

#include <domainmodule/ipxordertransmitptr.h>
#include <domainmodule/pxordertransmitptr.h>
#include "domainmodule/ipxtaskcontrolptr.h"

#include "iusecasegetter.h"
#include "usecase/iibtordergetterptr.h"

#include <libutil/applcomponent.h>
#include <boost/enable_shared_from_this.hpp>
#include <libutil/accessor.h>

#include <ibt/ibtresponse/iibtresponsefactoryptr.h>

#include <parameter/ibranchparametergetterptr.h>
#include <usecase/inachlieferposwriterptr.h>

namespace basar
{
    namespace db
    {
        namespace aspect
        {
            class ConnectionRef;
        }
    }
}

namespace log4cplus
{
    class Logger;
}

namespace ibtorderimport
{
namespace componentManager
{
class ApplCompMgr : public libcsc::persistence::ITransactionFactory,
				public libutil::componentManager::ApplCompMgrBase,
                public IUseCaseGetter,
                public boost::enable_shared_from_this< ApplCompMgr >
{
public:
    ApplCompMgr();
    virtual ~ApplCompMgr();

	void setCmdLineArguments( const infrastructure::cmdLine::AppArgs& appArgs );
	void injectMailAlert(infrastructure::mail::IMailAlertPtr );
	void injectCscDbConnection(libcsc::persistence::ConnectionPtr);

	virtual libcsc::persistence::TransactionGuard createTransaction() const;
    
	libutil::useCase::IRunnablePtr                                          getMainUC();
                
protected:
    virtual void                                                            doClear();

	libcsc::ibt::IIbtRequestRepositoryPtr getIbtRequestRepository();
	libcsc::ibt::IIbtResponseRepositoryPtr getIbtResponseRepository();
	domMod::IPxTaskControlPtr		  getTaskControl();
    libcsc::persistence::ConnectionPtr										getCscDbConnection() const;
	infrastructure::mail::IMailAlertPtr										getMailAlert();

private:
    ApplCompMgr( const ApplCompMgr& );
    ApplCompMgr& operator=( const ApplCompMgr& );

	libcsc::ibt::IbtComponentManagerPtr										getIbtComponentManager();
	useCase::IIbtOrderGetterPtr												getIbtOrderManager();
	//useCase::INachlieferPosWriterPtr										getNachlieferPosWriter();
	domMod::IPxOrderTransmitPtr												getPxOrderTransmit();
	libcsc::parameter::IBranchParameterGetterPtr							getBranchParamGetter();
	const log4cplus::Logger&												getLogger();
                
private:
    const log4cplus::Logger&                                                m_Logger;
	ibtorderimport::infrastructure::cmdLine::AppArgs						m_AppArgs;
	infrastructure::mail::IMailAlertPtr										m_MailAlert;
	libcsc::persistence::ConnectionPtr										m_CscDbConnection;
	domMod::PxOrderTransmitPtr												m_PxOrderTransmit;
	libcsc::ibt::IbtComponentManagerPtr										m_IbtComponentManagerPtr;
};

} // end namnespace componentManager
} // end namnespace ibtorderimport

#endif
