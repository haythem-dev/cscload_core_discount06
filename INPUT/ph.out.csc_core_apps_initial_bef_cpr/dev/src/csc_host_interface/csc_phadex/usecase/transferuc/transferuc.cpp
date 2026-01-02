#include "transferuc.h"
#include "loggerpool/csc_phadex_loggerpool.h"
#include <libutil/util.h>
#include <domainmodule/phadextransaction/iphadextransactioncollection.h>
#include <domainmodule/phadextransaction/iphadextransaction.h>
#include <domainmodule/cicstransaction/icicstransactioncollectionfinder.h>
#include <domainmodule/cicstransaction/icicstransaction.h>
#include <domainmodule/csc_phadex_properties_definitions.h>
#include <libbasardbaspect_accessorpropertytable_yiterator.h>
#include <libbasardbaspect_accessorpropertytable.h>

namespace csc_phadex
{
namespace useCase
{
TransferUC::TransferUC()
: m_Logger( LoggerPool::getLoggerUseCases() )
{
	METHODNAME_DEF( TransferUC, TransferUC );
	BLOG_TRACE_METHOD( m_Logger, fun );
}

TransferUC::~TransferUC()
{
	METHODNAME_DEF( TransferUC, ~TransferUC );
	BLOG_TRACE_METHOD( m_Logger, fun );
}

void TransferUC::inject( csc_phadex::domMod::phadexTransaction::IPhadexTransactionCollectionPtr phadexTransactions )
{
	m_PhadexTransactions = phadexTransactions;
}

void TransferUC::inject( csc_phadex::domMod::cicsTransaction::ICICSTransactionCollectionFinderPtr cicsTransactions )
{
	m_CICSTransactions = cicsTransactions;
}

void TransferUC::setBranchno( const basar::Int16 branchno )
{
	m_Branchno = branchno;
}

void TransferUC::setTransferLimit( const basar::Int32 limit )
{
	m_TransferLimit = limit;
}

void TransferUC::run()
{
	METHODNAME_DEF( TransferUC, run );
	BLOG_TRACE_METHOD( m_Logger, fun );

	m_PhadexTransactions->resetSearchYit();
	basar::db::aspect::AccessorPropertyTable_YIterator yitSearch = m_PhadexTransactions->getSearchYit();
	yitSearch.setInt16( properties::BRANCH_NO, m_Branchno );
	m_PhadexTransactions->findLastPhadexTransByPattern( yitSearch );
	basar::db::aspect::AccessorPropertyTable_YIterator yitLast = m_PhadexTransactions->get().begin();

	m_CICSTransactions->resetSearchYit();
	yitSearch = m_CICSTransactions->getSearchYit();
	yitSearch.setInt16( properties::KSC_FIL, m_Branchno );
	yitSearch.setInt32( properties::LIMIT, m_TransferLimit );

	basar::Int32 key = 0;
	if(    false == yitLast.isNull()
		&& false == yitLast.isEnd() )
	{
		csc_phadex::domMod::phadexTransaction::IPhadexTransactionPtr lastPhadexTransaction = m_PhadexTransactions->getPhadexTransaction( yitLast );
		basar::Int32 today = basar::DateTime::getCurrent().getDate();
		basar::Int32 transferDate = lastPhadexTransaction->getTransferDateTime().getDate();
		key = lastPhadexTransaction->getRecordNo();
		if( today != transferDate ) // TODO FN was soll das?
		{
			key = 0;
		}
/*
1. Lauf   06:00     IFX kein eintrag -> SELECT mit KEY > 0   						IFX = 00  TCA SELECT mit KEY=0 ==> SELECT mit KEY>0
X. Lauf 07:00        IFX Eintrag da  -> SELECT mit KEY > Eintrag					IFX = 01  TCA SELECT mit KEY 01 ==> SELECT mit KEY>01
Y. Lauf 00:05+      IFX kein eintrag zu aktuellem datum  -> SELECT mit KEY > 0		IFX = 99  TCA SELECT mit KEY 99 ==> SELECT mit KEY>99
TA   IFX = 101   TCA SELECT mit KEY 101 !=> SELECT mit KEY>0
*/
	}

	yitSearch.setInt32( properties::RRDS_RRN, key );
	m_CICSTransactions->findByPattern( yitSearch );
	if( m_CICSTransactions->isEmpty() )
	{
		return;
	}

	static basar::DateTime invalid;
	invalid.setInvalid();

	m_LastTransferredCount = 0;
	m_PhadexTransactions->clear();
	basar::db::aspect::AccessorPropertyTable_YIterator yit = m_CICSTransactions->get().begin();
	for( ; false == yit.isEnd(); ++yit )
	{
		csc_phadex::domMod::cicsTransaction::ICICSTransactionPtr cicsTransaction = m_CICSTransactions->getCICSTransaction( yit );
		csc_phadex::domMod::phadexTransaction::IPhadexTransactionPtr phadexTransaction = m_PhadexTransactions->createPhadexTransaction();

		phadexTransaction->setBranchno( cicsTransaction->getBranchno() );
		phadexTransaction->setData( cicsTransaction->getData() );
		phadexTransaction->setProcessedFlag( 0 );
		phadexTransaction->setCreationDateTime( basar::DateTime( cicsTransaction->getCreationDate(), cicsTransaction->getCreationTime() * 1000 ) );
		phadexTransaction->setTransferDateTime( basar::DateTime::getCurrent() );
		phadexTransaction->setProcessDateTime( invalid );
		phadexTransaction->setRecordType( cicsTransaction->getRecordType() );
		phadexTransaction->setRecordNo( cicsTransaction->getRecordNo() );
		m_PhadexTransactions->save(phadexTransaction);

		++m_LastTransferredCount;
		if( m_LastTransferredCount == m_TransferLimit )
		{
			break;
		}
	}

	// update DRKSC status
	m_CICSTransactions->get().clear();
	basar::db::aspect::AccessorPropertyTable_YIterator yitCICSUpdate;
	basar::db::aspect::AccessorPropertyTable_YIterator yitPhadex;
	yitCICSUpdate = m_CICSTransactions->get().insert(basar::FOR_CLEAN);
	yitPhadex = m_PhadexTransactions->get().begin();
	while (false == yitPhadex.isEnd())
	{
		yitCICSUpdate.setInt16(properties::KSC_FIL, yitPhadex.getInt16(properties::BRANCH_NO));
		yitCICSUpdate.setInt32(properties::RRDS_RRN, yitPhadex.getInt32(properties::RECORD_NO));
		yitCICSUpdate.setString(properties::KSC_STATUS, "1");
		m_CICSTransactions->saveCICSTransaction(yitCICSUpdate);
		++yitPhadex;
	}
	
}

bool TransferUC::hasRecordsLeft() const
{
	return ( m_LastTransferredCount == m_TransferLimit );
}

} // namespace usecase
} // namespace csc_phadex
