//-------------------------------------------------------------------------------------------//
/*! \file 
*   \brief
*   \author 
*   \date   
*/
//-------------------------------------------------------------------------------------------//

#include "transferfromcicsuc.h"
#include <iremoteprocedurecaller.h>
#include <remoteprocedureresult.h>
#include "pharmostransactiondm.h"
#include "cicspharmostransactiondm.h"
#include "recordtypefactory.h"
#include "transactionrecordbase.h"
#include "transactiondmbaseptr.h"
#include "transactiondmbase.h"
#include "irecordtypetransformer.h"
#include <missingdependencyinjectionexception.h>
#include "accessorexecutionexception.h"
#include <icsc_logger.h>

//-------------------------------------------------------------------------------------------//

namespace csc_phatra {
namespace useCase {

//-------------------------------------------------------------------------------------------//

TransferFromCicsUC::TransferFromCicsUC() : TransferBaseUC()
{
}

//-------------------------------------------------------------------------------------------//

TransferFromCicsUC::~TransferFromCicsUC()
{
}

//-------------------------------------------------------------------------------------------//

basar::appl::EventReturnStruct TransferFromCicsUC::doRun()
{
	m_CSC_Logger->log(log4cplus::INFO_LOG_LEVEL, "transfering CICS/Pharmos transactions");				
	transferCICSPharmosTransactions();

	m_CSC_Logger->log(log4cplus::INFO_LOG_LEVEL, "calling remote procedure");
	m_RecordsProcessed = callRemoteProcedure();

	return basar::appl::EventReturnStruct();
}

//-------------------------------------------------------------------------------------------//

basar::Int32 TransferFromCicsUC::callRemoteProcedure()
{		
	libcsc_utils::RemoteProcedureResult rpRes(false, 0);
	try
	{
		rpRes = m_pdx010caller->call(); // TODO check ReturnValue -> Exception Handling???
		if (!rpRes.m_Success)
		{
			m_CSC_Logger->log(log4cplus::ERROR_LOG_LEVEL, "pdx010call failed", rpRes.m_InfoMessage);
		}
	}
	catch(libcsc_utils::MissingDependencyInjectionException& ex)
	{
		m_CSC_Logger->logBasarException("text missing remote ex", ex);
	}
	catch(basar::Exception& ex)
	{				
		m_CSC_Logger->logBasarException("text caught basar exception during RPC", ex);
	}
	catch(...)
	{
		m_CSC_Logger->log(log4cplus::ERROR_LOG_LEVEL, "text caught generic exception during RPC");
	}
	return rpRes.m_DatasetsProcessed;
}

//-------------------------------------------------------------------------------------------//

void TransferFromCicsUC::doCheckInjections() const
{	
	METHODNAME_DEF( TransferFromCicsUC, doCheckInjections );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );	

	if( 0 == m_pdx010caller.get() )
	{		
		throw libcsc_utils::MissingDependencyInjectionException( basar::ExceptInfo(fun, "PDX010Caller missing! Inject PDX010Caller first!", __FILE__, __LINE__) );
	}
	if ( 0 == m_cicsPharmosTransactionDM.get() )
	{
		throw libcsc_utils::MissingDependencyInjectionException( basar::ExceptInfo(fun, "CicsPharmosTransactionDM missing! Inject CicsPharmosTransactionDM first!", __FILE__, __LINE__) );
	}
}

//-------------------------------------------------------------------------------------------//

void TransferFromCicsUC::injectPDX010Caller(libcsc_utils::IRemoteProcedureCallerPtr pdx010caller)
{
	m_pdx010caller = pdx010caller;
}

void TransferFromCicsUC::injectCICSPharmosTransactionDMPtr(domMod::pharmosTransaction::preparation::CICSPharmosTransactionDMPtr cicsPharmosTransactionDM)
{
	m_cicsPharmosTransactionDM = cicsPharmosTransactionDM;
}

//-------------------------------------------------------------------------------------------//

void TransferFromCicsUC::transferCICSPharmosTransactions()
{
	domMod::pharmosTransaction::core::TransactionDMBasePtr tcaPhaTraDMPtr = m_cicsPharmosTransactionDM;
	domMod::pharmosTransaction::core::TransactionDMBasePtr ifxPhaTraDMPtr = m_pharmosTransactionDM;

	try
	{
		tcaPhaTraDMPtr->findOpen(0);
	}
	catch(::util::AccessorExecutionException& ex)
	{
		m_CSC_Logger->logBasarException("text accessor exec exception", ex);
	}

	domMod::pharmosTransaction::core::TransactionRecordBasePtr cicsrec = tcaPhaTraDMPtr->getFirstTransactionRecord();	
	if( cicsrec->isEnd() )
	{
		//finishQuery empties ProbTab of DM, needed b/c tcAcccess-Layer won't allow following database call if not done
		tcaPhaTraDMPtr->finishQuery();
		return;
	}		

	domMod::pharmosTransaction::core::RecordTypeFactoryPtr factory = m_RecordTypeFactory;
	domMod::pharmosTransaction::util::IRecordTypeTransformerPtr transformer;
	domMod::pharmosTransaction::core::TransactionRecordBasePtr record;

	for( ; !cicsrec->isEnd(); cicsrec = tcaPhaTraDMPtr->getNextTransactionRecord() )
	{
		cicsrec->log();
		try
		{
			record = ifxPhaTraDMPtr->addEmptyTransactionRecord();
			transformer = factory->createTransformer( cicsrec );
			transformer->transform( cicsrec, record );
			record->save();
		}
		catch(...)
		{
			m_CSC_Logger->logGenericException("text cics pharmos transaction", record);		
		}		
	}
	//finishQuery empties ProbTab of DM, needed b/c tcAcccess-Layer won't allow following database call if not done
	tcaPhaTraDMPtr->finishQuery();
}
		
//-------------------------------------------------------------------------------------------//

basar::Int32 TransferFromCicsUC::getRecordsProcessed()
{
	return m_RecordsProcessed;
}

//-------------------------------------------------------------------------------------------//

} //namespace useCase
}//namespace csc_phatra

//-------------------------------------------------------------------------------------------//
