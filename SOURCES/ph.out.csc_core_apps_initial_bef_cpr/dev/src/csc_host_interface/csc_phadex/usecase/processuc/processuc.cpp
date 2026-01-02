#include "processuc.h"
#include <loggerpool/csc_phadex_loggerpool.h>
#include "domainmodule/unknownrecordtypeexception.h"
#include <domainmodule/taskcontrol/itaskcontrol.h>
#include <domainmodule/phadextransaction/iphadextransactioncollection.h>
#include <domainmodule/phadextransaction/iphadextransaction.h>
#include <usecase/processuc/transactionrecordmapper/itransactionrecordmapper.h>
#include <libbasardbaspect_accessorpropertytable_yiterator.h>
#include <libbasardbaspect_accessorpropertytable.h>
#include <domainmodule/csc_phadex_properties_definitions.h>
#include <libutil/util.h>
#include <libutil/irunnableptr.h>

namespace csc_phadex
{
namespace useCase
{
ProcessUC::ProcessUC()
: m_Logger( LoggerPool::getLoggerUseCases() )
{
	METHODNAME_DEF( ProcessUC, ProcessUC )
	BLOG_TRACE_METHOD( m_Logger, fun );
}

ProcessUC::~ProcessUC()
{
	METHODNAME_DEF( ProcessUC, ~ProcessUC )
	BLOG_TRACE_METHOD( m_Logger, fun );
}

void ProcessUC::inject( csc_phadex::domMod::ITaskControlPtr taskControl )
{
	METHODNAME_DEF( ProcessUC, injectTaskControl )
	BLOG_TRACE_METHOD( m_Logger, fun );

	m_TaskControl = taskControl;
}

void ProcessUC::inject( csc_phadex::domMod::phadexTransaction::IPhadexTransactionCollectionPtr phadexTransactions )
{
	m_PhadexTransactions = phadexTransactions;
}

void ProcessUC::inject( csc_phadex::useCase::ITransactionRecordMapperPtr mapper )
{
	m_Mapper = mapper;
}

void ProcessUC::setDatabaseName(const basar::VarString& dbName)
{
	m_DatabaseName = dbName;
}

void ProcessUC::setBranchno( const basar::Int16 branchno )
{
	m_Branchno = branchno;
}

void ProcessUC::run()
{
	METHODNAME_DEF( ProcessUC, run )
	BLOG_TRACE_METHOD( m_Logger, fun );

	m_PhadexTransactions->resetSearchYit();
	basar::db::aspect::AccessorPropertyTable_YIterator yitSearch = m_PhadexTransactions->getSearchYit();
	yitSearch.setInt16( properties::BRANCH_NO, m_Branchno );
	if (false == m_DatabaseName.empty())
	{
		yitSearch.setString(properties::DATABASE_NAME, m_DatabaseName);
	}
	m_PhadexTransactions->findPhadexTransByPattern( yitSearch );
	basar::db::aspect::AccessorPropertyTable_YIterator yit = m_PhadexTransactions->get().begin();

	try
	{
		if( m_PhadexTransactions->isEmpty() )
		{
			return;
		}

		for( ; false == yit.isEnd(); ++yit )
		{
			csc_phadex::domMod::phadexTransaction::IPhadexTransactionPtr phadexTransaction = m_PhadexTransactions->getPhadexTransaction( yit );
			try
			{
				libutil::useCase::IRunnablePtr uc = m_Mapper->map(phadexTransaction);
				uc->run();
			}
			catch (csc_phadex::exception::UnknownRecordTypeException& urte)
			{
				BLOG_ERROR(m_Logger, urte.what());
			}

			if (false == m_DatabaseName.empty())
			{
				phadexTransaction->getYit().setString(properties::DATABASE_NAME, m_DatabaseName);
			}
			phadexTransaction->setProcessedFlag( 1 );
			m_PhadexTransactions->save(phadexTransaction);
			m_TaskControl->heartBeat();
		}
	}
	catch( basar::Exception & e )
	{
		BLOG_ERROR( m_Logger, e.what() );
	}
}

} // namespace usecase
} // namespace csc_phadex
