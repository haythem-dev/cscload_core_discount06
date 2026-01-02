#ifndef GUARD_CSC_PHADEX_USECASE_PROCESS_UC_H
#define GUARD_CSC_PHADEX_USECASE_PROCESS_UC_H

#include <domainmodule/taskcontrol/itaskcontrolptr.h>
#include <domainmodule/phadextransaction/iphadextransactioncollectionptr.h>
#include <usecase/processuc/transactionrecordmapper/itransactionrecordmapperptr.h>
#include <libutil/irunnable.h>
#include <libbasar_definitions.h>
#include <libbasarcmnutil_bstring.h>

namespace log4cplus
{
	class Logger;
}

namespace csc_phadex
{
namespace useCase
{
class ProcessUC : public libutil::useCase::IRunnable
{
public:
	ProcessUC();
	virtual ~ProcessUC();

	void inject( csc_phadex::domMod::ITaskControlPtr );
	void inject( csc_phadex::domMod::phadexTransaction::IPhadexTransactionCollectionPtr phadexTransactions );
	void inject( csc_phadex::useCase::ITransactionRecordMapperPtr mapper );

	void setDatabaseName(const basar::VarString& dbName);
	void setBranchno( const basar::Int16 branchno );
	virtual void run();

private:
	ProcessUC(	const ProcessUC & );
	ProcessUC & operator= ( const ProcessUC & );

	const log4cplus::Logger &													m_Logger;
	csc_phadex::domMod::ITaskControlPtr											m_TaskControl;
	csc_phadex::domMod::phadexTransaction::IPhadexTransactionCollectionPtr		m_PhadexTransactions;
	csc_phadex::useCase::ITransactionRecordMapperPtr							m_Mapper;
	basar::VarString															m_DatabaseName;
	basar::Int16																m_Branchno;
};

} // namespace useCase
} // namespace csc_phadex

#endif //end GUARD_CSC_PHADEX_USECASE_PROCESS_UC_H
