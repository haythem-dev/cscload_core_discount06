//-------------------------------------------------------------------------------------------//
/*! \file 
*   \brief csc_phatra's sole usecase
*   \author 
*   \date   
*/
//-------------------------------------------------------------------------------------------//

#include "transferfromzdpuc.h"
#include "pharmostransactiondm.h"
#include "ctransfercscdm.h"
#include "recordtypefactory.h"
#include "transactionrecordbase.h"
#include "transactiondmbaseptr.h"
#include "transactiondmbase.h"
#include "irecordtypecreatorptr.h"
#include "irecordtypecreator.h"
#include "irecordtypeprocessor.h"
#include "irecordtypetransformer.h"
#include <missingdependencyinjectionexception.h>
#include "accessorexecutionexception.h"
#include <icsc_logger.h>

//-------------------------------------------------------------------------------------------//

namespace csc_phatra {
namespace useCase {

//-------------------------------------------------------------------------------------------//

TransferFromZDPUC::TransferFromZDPUC() : TransferBaseUC()
{
}

//-------------------------------------------------------------------------------------------//

TransferFromZDPUC::~TransferFromZDPUC()
{
}

//-------------------------------------------------------------------------------------------//

void TransferFromZDPUC::doCheckInjections() const
{	
	METHODNAME_DEF( TransferFromZDPUC, doCheckInjections );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );	

	if ( 0 == m_cTransferCscDM.get() )
	{
		throw libcsc_utils::MissingDependencyInjectionException( basar::ExceptInfo(fun, "cTransferCscDM missing! Inject cTransferCscDM first!", __FILE__, __LINE__) );
	}
}

//-------------------------------------------------------------------------------------------//

void TransferFromZDPUC::injectCTransferCscDMPtr(domMod::pharmosTransaction::preparation::CTransferCscDMPtr cTransferCscDM)
{
	m_cTransferCscDM = cTransferCscDM;
}

//-------------------------------------------------------------------------------------------//

basar::appl::EventReturnStruct TransferFromZDPUC::doRun()
{
	METHODNAME_DEF( TransferFromZDPUC, doRun );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

	m_CSC_Logger->log(log4cplus::INFO_LOG_LEVEL, "transfering ZDP transactions");

	m_RecordsProcessed = 0;
	try
	{
		m_cTransferCscDM->findOpen(0);
	}
	catch(::util::AccessorExecutionException& ex)
	{
		m_CSC_Logger->logBasarException("text accessor exec exception", ex);
	}

	domMod::pharmosTransaction::core::TransactionRecordBasePtr	zdpRecord;
	domMod::pharmosTransaction::core::TransactionRecordBasePtr	phatraRecord;
	domMod::pharmosTransaction::util::IRecordTypeTransformerPtr transformer;

	for( zdpRecord = m_cTransferCscDM->getFirstTransactionRecord(); !zdpRecord->isEnd(); zdpRecord = m_cTransferCscDM->getNextTransactionRecord() )
	{
		zdpRecord->log();
		try
		{
			phatraRecord = m_pharmosTransactionDM->addEmptyTransactionRecord();
			transformer = m_RecordTypeFactory->createTransformer( zdpRecord );
			transformer->transform( zdpRecord, phatraRecord );
			phatraRecord->save();
			m_RecordsProcessed++;
//			zdpRecord->save(); do not save!!!
		}
		catch(...)
		{
			m_CSC_Logger->logGenericException("text cics pharmos transaction", phatraRecord);		
		}		
	}
	m_cTransferCscDM->finishQuery();
	return basar::appl::EventReturnStruct();
}

//-------------------------------------------------------------------------------------------//

} //namespace useCase
}//namespace csc_phatra

//-------------------------------------------------------------------------------------------//
