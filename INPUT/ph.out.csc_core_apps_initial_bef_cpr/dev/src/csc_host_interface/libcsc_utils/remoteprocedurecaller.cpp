//-------------------------------------------------------------------------------------------------------------------//
/*! \file		
 *  \brief		implementation of class RemoteProcedureCaller
 *  \author		Steffen Heinlein
 *  \date		20.06.2012
 */
//-------------------------------------------------------------------------------------------------------------------//

#include <libbasardbaspect.h>
#include <classinfo_macros.h>
#include "remoteprocedurecaller.h"
#include "iremoteprocedure.h"
#include "missingdependencyinjectionexception.h"
#include "remoteprocedureresult.h"
#include "icsc_logger.h"
#include "csc_logger.h"

#include "remoteprocedureacc.h"

namespace libcsc_utils
{	

//-------------------------------------------------------------------------------------------------------------------//
RemoteProcedureCaller::RemoteProcedureCaller( const basar::db::aspect::ConnectionRef tcaconn, ICSC_LoggerPtr csc_logger, 
					      const basar::VarString& stp /*= lit::acc_remoteprocedure::DEFAULT_STORED_PROCEDURE*/ )
	: m_TCAConnection(tcaconn)
	, m_CSC_Logger(csc_logger)
	, m_StoredProcedure( stp )
	, m_Accessor( lit::acc_remoteprocedure::ACC_REMOTEPROCEDURE, tcaconn )
{
	METHODNAME_DEF( RemoteProcedureCaller, RemoteProcedureCaller );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
	// dummy object for static linking of libCSC_Utils
	acc_remoteprocedure::CallRemoteProcedure();
}

//-------------------------------------------------------------------------------------------------------------------//
RemoteProcedureCaller::~RemoteProcedureCaller()
{		
	METHODNAME_DEF( RemoteProcedureCaller, ~RemoteProcedureCaller );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

	shutdown();
}

//-------------------------------------------------------------------------------------------------------------------//
void RemoteProcedureCaller::init()
{
	METHODNAME_DEF( RemoteProcedureCaller, init );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
}

//-------------------------------------------------------------------------------------------------------------------//
void RemoteProcedureCaller::shutdown()
{
	METHODNAME_DEF( RemoteProcedureCaller, shutdown );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );		
}

//-------------------------------------------------------------------------------------------------------------------//
void RemoteProcedureCaller::injectRemoteProcedure( IRemoteProcedurePtr remoteprocedure )
{
	METHODNAME_DEF( RemoteProcedureCaller, injectRemoteProcedure );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );		

	m_RemoteProcedure = remoteprocedure;
}

//-------------------------------------------------------------------------------------------------------------------//
basar::db::aspect::AccessorInstanceRef RemoteProcedureCaller::getRemoteProcedureACC()
{
	METHODNAME_DEF( RemoteProcedureCaller, getRemoteProcedureACC );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );		

	return m_Accessor.get();
}

//-------------------------------------------------------------------------------------------------------------------//	
basar::db::aspect::AccessorPropertyTableRef RemoteProcedureCaller::getRemoteProcedureACCPropTab()
{
	METHODNAME_DEF( PharmosTransactionDM, getRemoteProcedureACCPropTab );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

	return getRemoteProcedureACC().getPropertyTable();	
}

//-------------------------------------------------------------------------------------------------------------------//	
basar::db::aspect::AccessorPropertyTable_YIterator RemoteProcedureCaller::addEmptyRemoteProcedureYit()
{
	METHODNAME_DEF( PharmosTransactionDM, addEmptyRemoteProcedureYit );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

	basar::db::aspect::AccessorPropertyTable_YIterator yit;
	getRemoteProcedureACCPropTab().clear();	
	yit = getRemoteProcedureACCPropTab().insert(basar::FOR_CLEAN);		
		
	return yit;		
}

//-------------------------------------------------------------------------------------------------------------------//
void RemoteProcedureCaller::checkInjections() const
{
	METHODNAME_DEF( RemoteProcedureCaller, checkInjections );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );		

	if( NULL == m_RemoteProcedure.get() )
	{		
		throw libcsc_utils::MissingDependencyInjectionException( basar::ExceptInfo(fun, "RemoteProcedure missing! Inject RemoteProcedure first!", __FILE__, __LINE__) );
	}
}

//-------------------------------------------------------------------------------------------------------------------//
RemoteProcedureResult RemoteProcedureCaller::call()
{
	METHODNAME_DEF( RemoteProcedureCaller, call );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

	checkInjections();

	RemoteProcedureResult retval(false, 0);	

	basar::db::aspect::ExecuteResultInfo rc;

	basar::db::aspect::AccessorPropertyTable_YIterator yit = addEmptyRemoteProcedureYit();
	yit.setString( lit::acc_remoteprocedure::REMOTEPROCEDURENAME, m_RemoteProcedure->getProcedureName() );
	yit.setString( lit::acc_remoteprocedure::REMOTEPROCEDUREQUERY, m_RemoteProcedure->serializeQuery() );
	yit.setString( lit::acc_remoteprocedure::STOREDPROCEDURE, m_StoredProcedure );

	rc = getRemoteProcedureACC().execute( lit::acc_remoteprocedure::CALL_REMOTEPROCEDURE, yit, true, false );

	if( !rc.hasError() )
	{
		basar::db::aspect::AccessorPropertyTable_YIterator yitResult = getRemoteProcedureACCPropTab().begin();
		if( !yitResult.isEnd() )
		{
			if( yitResult.isContainedAndSet(lit::acc_remoteprocedure::REMOTEPROCEDUREQUERY ) )
			{
				m_RemoteProcedure->deserializeResult( yitResult.getString( lit::acc_remoteprocedure::REMOTEPROCEDUREQUERY ) );				
				retval = m_RemoteProcedure->checkResult();
			}
		}
	}

	getRemoteProcedureACCPropTab().clear(); //! \todo new function finishQuery()

	return retval;
}

} 
