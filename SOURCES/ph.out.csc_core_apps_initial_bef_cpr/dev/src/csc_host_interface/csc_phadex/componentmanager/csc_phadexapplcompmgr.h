#ifndef GUARD_CSC_PHADEX_COMPONENTMANAGER_CSC_PHADEXAPPLCOMPMGR_H
#define GUARD_CSC_PHADEX_COMPONENTMANAGER_CSC_PHADEXAPPLCOMPMGR_H

#include <libutil/irunnableptr.h>
#include "iusecasegetter.h"
#include <componentmanager/csc_phadexapplcompmgrptr.h>
#include <domainmodule/taskcontrol/itaskcontrolptr.h>
#include <domainmodule/cicstransaction/icicstransactioncollectionfinderptr.h>
#include <domainmodule/phadextransaction/iphadextransactioncollectionptr.h>
#include <boost/enable_shared_from_this.hpp>
#include <infrastructure/config/phadexconfigstruct.h>

#include <infrastructure/session/isessionptr.h>
#include <libutil/applcomponent.h>
#include <domainmodule/narcotics/inarcoticsptr.h>
#include <libutil/accessor.h>
#include <usecase/narcprintupdateuc/narcprintupdateucptr.h>
#include <usecase/processuc/transactionrecordmapper/itransactionrecordmapperptr.h>

#include <pxsessionptr.h>

#include <usecase/deliverynotecompleteduc/deliverynotecompleteducptr.h>
#include <usecase/deliverynotecancellationuc/deliverynotecancellationucptr.h>
#include <usecase/blockedarticleuc/blockedarticleucptr.h>
#include <usecase/documentprintinfouc/documentprintinfoucptr.h>
#include <usecase/sapreferencenouc/sapreferencenoucptr.h>
#include <pxordertransmitptr.h>

namespace basar {
namespace db {
namespace aspect {
	class ConnectionRef;
}
}
}

namespace log4cplus
{
	class Logger;
}


namespace csc_phadex
{
namespace componentManager
{
class ApplCompMgr : public libutil::componentManager::ApplCompMgrBase,
					public IUseCaseGetter,
					public boost::enable_shared_from_this< ApplCompMgr >
{
public:
	ApplCompMgr();
	virtual ~ApplCompMgr();

	libutil::useCase::IRunnablePtr getMainUC();
	virtual csc_phadex::useCase::ITransferUCPtr getTransferUC();
	virtual libutil::useCase::IRunnablePtr getProcessUC();
    virtual csc_phadex::useCase::ITenderCancellationUCPtr getTenderCancellationUC();
    virtual csc_phadex::useCase::INarcPrintUpdateUCPtr getNarcPrintUpdateUC();
    virtual csc_phadex::useCase::IDeliveryNoteCompletedUCPtr getDeliveryNoteCompletedUC();
    virtual csc_phadex::useCase::IDeliveryNoteCancellationUCPtr getDeliveryNoteCancellationUC();
	virtual csc_phadex::useCase::IBlockedArticleUCPtr getBlockedArticleUC();
	virtual csc_phadex::useCase::IDocumentPrintInfoUCPtr getDocumentPrintInfoUC();
	virtual csc_phadex::useCase::ISAPReferenceNoUCPtr getSAPReferenceNoUC();
	void injectCICSConnection( basar::db::aspect::ConnectionRef connection );
	void setConfig( const csc_phadex::infrastructure::PhadexConfigStruct & config );

protected:
	virtual void doClear();

    libutil::infrastructure::session::ISessionPtr getSession();

	csc_phadex::domMod::ITaskControlPtr getTaskControl();
	libutil::infrastructure::db::dbConnection::IDBConnectionDataGetterPtr getDBConnection();
    csc_phadex::domMod::narcotics::INarcoticsPtr getNarcoticsDM();
    libutil::infrastructure::accessor::IAccessorPtr getNarcoticsAccessor();

	libutil::infrastructure::accessor::IAccessorPtr getCICSDataAccessor();
	libutil::infrastructure::accessor::IAccessorPtr getPhadexTransactionAccessor();

	basar::db::aspect::ConnectionRef getCICSConnection();

	csc_phadex::domMod::phadexTransaction::IPhadexTransactionCollectionPtr getPhadexTransactionCollectionDM();
	csc_phadex::domMod::cicsTransaction::ICICSTransactionCollectionFinderPtr getCICSTransactionCollectionDM();

	csc_phadex::useCase::ITransactionRecordMapperPtr getTransactionRecordMapper();

	pxOrderTransmitPtr getPxOrderTransmit();


private:
	ApplCompMgr( const ApplCompMgr & );
	ApplCompMgr & operator=( const ApplCompMgr & );

    libutil::infrastructure::session::ISessionPtr           m_Session;
    csc_phadex::useCase::NarcPrintUpdateUCPtr               m_NarcPrintUpdateUC;
	csc_phadex::useCase::DeliveryNoteCompletedUCPtr         m_DeliveryNoteCompletedUC;
    csc_phadex::useCase::DeliveryNoteCancellationUCPtr      m_DeliveryNoteCancellationUC;
	csc_phadex::useCase::BlockedArticleUCPtr                m_BlockedArticleUC;
	csc_phadex::useCase::DocumentPrintInfoUCPtr             m_DocumentPrintInfoUC;
	csc_phadex::useCase::SAPReferenceNoUCPtr                m_SAPReferenceNoUC;
	basar::db::aspect::ConnectionRef						m_CICSConnection;
	csc_phadex::infrastructure::PhadexConfigStruct			m_Config;
	pxOrderTransmitPtr										m_pxOrderTransmit;
    PxSessionPtr                                            m_PxSession;

private:
	const log4cplus::Logger &	m_Logger;
};

} // end namnespace componentManager
} // end namnespace csc_phadex

#endif
