//-------------------------------------------------------------------------------------------//
/*! \file
*   \brief
*   \author
*   \date
*/
//-------------------------------------------------------------------------------------------//

#include "transfertocscuc.h"
#include "pharmostransactiondm.h"
#include "recordtypefactory.h"
#include "transactionrecordbase.h"
#include "irecordtypecreatorptr.h"
#include "irecordtypecreator.h"
#include "irecordtypeprocessor.h"
#include "irecordtypetransformer.h"

#include <invalidstatuschangeexception.h>
#include <accessorexecutionexception.h>

#include <icsc_logger.h>

//-------------------------------------------------------------------------------------------//

namespace csc_phatra {
namespace useCase {

//-------------------------------------------------------------------------------------------//

TransferToCscUC::TransferToCscUC() : TransferBaseUC()
{
}

//-------------------------------------------------------------------------------------------//

TransferToCscUC::~TransferToCscUC()
{
}

//-------------------------------------------------------------------------------------------//

basar::appl::EventReturnStruct TransferToCscUC::doRun()
{
	METHODNAME_DEF( TransferToCscUC, doRun );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

	m_CSC_Logger->log(log4cplus::INFO_LOG_LEVEL, "processing Pharmos transactions");

	m_RecordsProcessed = 0;
	try
	{
		m_pharmosTransactionDM->findOpen();
	}
	catch(::util::AccessorExecutionException& ex)
	{
		m_CSC_Logger->logBasarException("accessor exec exception", ex);
	}

	domMod::pharmosTransaction::core::TransactionRecordBasePtr recordSet = m_pharmosTransactionDM->getFirstTransactionRecord();
	if( recordSet->isEnd() )
	{
		return basar::appl::EventReturnStruct();
	}

	domMod::pharmosTransaction::util::IRecordTypeCreatorPtr creator = m_RecordTypeFactory;
	domMod::pharmosTransaction::util::IRecordTypeProcessorPtr recordTypeProcessor;

	for( ; !recordSet->isEnd(); recordSet = m_pharmosTransactionDM->getNextTransactionRecord() )
	{
		recordSet->log();
		try
		{
			recordSet->startProcessing();
			recordTypeProcessor = creator->createRecordType( recordSet );
			recordTypeProcessor->process( recordSet );
			recordSet->finishProcessing();
			m_RecordsProcessed++;
		}
		catch(libcsc_utils::InvalidStatusChangeException& ex)
		{
			m_CSC_Logger->logBasarException("invalid status change exception", ex, recordSet);
		}
		catch( ... )
		{
			m_CSC_Logger->logGenericException("process pharmos transaction", recordSet);
		}
	}
	return basar::appl::EventReturnStruct();
}

//-------------------------------------------------------------------------------------------//

} //namespace useCase
}//namespace csc_phatra

//-------------------------------------------------------------------------------------------//
