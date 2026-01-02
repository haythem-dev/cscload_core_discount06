#ifndef GUARD_CSC_PHADEX_USECASE_TRANSFER_UC_H
#define GUARD_CSC_PHADEX_USECASE_TRANSFER_UC_H

#include "itransferuc.h"
#include <domainmodule/phadextransaction/iphadextransactioncollectionptr.h>
#include <domainmodule/cicstransaction/icicstransactioncollectionfinderptr.h>
#include <libbasar_definitions.h>

namespace log4cplus
{
	class Logger;
}

namespace csc_phadex
{
namespace useCase
{
class TransferUC : public ITransferUC
{
public:
	TransferUC();
	virtual ~TransferUC();

	void inject( csc_phadex::domMod::phadexTransaction::IPhadexTransactionCollectionPtr phadexTransactions );
	void inject( csc_phadex::domMod::cicsTransaction::ICICSTransactionCollectionFinderPtr cicsTransactions );
	void setBranchno( const basar::Int16 branchno );
	void setTransferLimit( const basar::Int32 limit );

	virtual void run();
	virtual bool hasRecordsLeft() const;

private:
	TransferUC(	const TransferUC & );
	TransferUC & operator= ( const TransferUC & );

	const log4cplus::Logger &													m_Logger;
	csc_phadex::domMod::phadexTransaction::IPhadexTransactionCollectionPtr		m_PhadexTransactions;
	csc_phadex::domMod::cicsTransaction::ICICSTransactionCollectionFinderPtr	m_CICSTransactions;
	basar::Int16																m_Branchno;
	basar::Int32																m_TransferLimit;
	basar::Int32																m_LastTransferredCount;
};

} // namespace useCase
} // namespace csc_phadex

#endif //end GUARD_CSC_PHADEX_USECASE_TRANSFER_UC_H
