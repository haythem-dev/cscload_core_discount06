//-------------------------------------------------------------------------------------------//
/*! \file 
*   \brief
*   \author 
*   \date   
*/
//-------------------------------------------------------------------------------------------//

#include "transferbaseuc.h"
#include <classinfo_macros.h>
#include <missingdependencyinjectionexception.h>
#include <icsc_logger.h>

//-------------------------------------------------------------------------------------------//

namespace csc_phatra {
namespace useCase {

//-------------------------------------------------------------------------------------------//

TransferBaseUC::TransferBaseUC()
{
}

TransferBaseUC::~TransferBaseUC()
{
}

//-------------------------------------------------------------------------------------------//

basar::appl::EventReturnStruct TransferBaseUC::run()
{
	checkInjections();

	m_RecordsProcessed = 0;
	return doRun();
}

//-------------------------------------------------------------------------------------------//

basar::Int32 TransferBaseUC::getRecordsProcessed()
{
	return m_RecordsProcessed;
}

//-------------------------------------------------------------------------------------------//

void TransferBaseUC::checkInjections() const
{	
	METHODNAME_DEF( TransferBaseUC, checkInjections );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );	

	if ( 0 == m_RecordTypeFactory.get() )
	{
		throw libcsc_utils::MissingDependencyInjectionException( basar::ExceptInfo(fun, "RecordTypeFactory missing! Inject RecordTypeFactory first!", __FILE__, __LINE__) );
	}
	if ( 0 == m_pharmosTransactionDM.get() )
	{
		throw libcsc_utils::MissingDependencyInjectionException( basar::ExceptInfo(fun, "PharmosTransactionDM missing! Inject PharmosTransactionDM first!", __FILE__, __LINE__) );
	}
	if ( 0 == m_CSC_Logger.get() )
	{
		throw libcsc_utils::MissingDependencyInjectionException( basar::ExceptInfo(fun, "CicsPharmosTransactionDM missing! Inject CicsPharmosTransactionDM first!", __FILE__, __LINE__) );
	}

	doCheckInjections();
}

//-------------------------------------------------------------------------------------------//

void TransferBaseUC::injectPharmosTransactionDMPtr(domMod::pharmosTransaction::core::PharmosTransactionDMPtr pharmosTransactionDM)
{
	m_pharmosTransactionDM = pharmosTransactionDM;
}

void TransferBaseUC::injectRecordTypeFactoryPtr(domMod::pharmosTransaction::core::RecordTypeFactoryPtr recordTypeFactory)
{
	m_RecordTypeFactory = recordTypeFactory;
}

void TransferBaseUC::injectICSC_LoggerPtr(libcsc_utils::ICSC_LoggerPtr csc_logger)
{
	m_CSC_Logger = csc_logger;
}

//-------------------------------------------------------------------------------------------//

} //namespace useCase
}//namespace csc_phatra

//-------------------------------------------------------------------------------------------//
