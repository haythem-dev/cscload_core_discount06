//-------------------------------------------------------------------------------------------------//
/*! \file		ctransfercscdm.cpp
 *  \brief		main interface to access transaction records from ZDP
 *  \author		Frank Naumann
 *  \date		23.01.2015
 */
//-------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include "property_definitions.h"
#include "ctransfercsc_definitions.h"
#include "ctransfercscdm.h"
#include "ctransfercsctransactionrecord.h"
#include <icsc_logger.h>

//-------------------------------------------------------------------------------------------------//
namespace domMod {
namespace pharmosTransaction {
namespace preparation {

//--------------------------------------------------------------------------------------------------//

CTransferCscDM::CTransferCscDM( const basar::db::aspect::ConnectionRef conn, libcsc_utils::ICSC_LoggerPtr csc_logger ) : 
	pharmosTransaction::core::TransactionDMBase(conn, lit::acc_ctransfercsc::ACC_CTRANSFERCSC, csc_logger)
{
}

//--------------------------------------------------------------------------------------------------//

CTransferCscDM::~CTransferCscDM()
{
}

//--------------------------------------------------------------------------------------------------//

const basar::VarString& CTransferCscDM::getFindByPatternAccessMethod() const
{
	return lit::acc_ctransfercsc::SELECT_CTRANSFERCSC_BY_PATTERN;
}

//--------------------------------------------------------------------------------------------------//

core::TransactionRecordBasePtr CTransferCscDM::createTransactionRecord(basar::db::aspect::AccessorPropertyTable_YIterator yit, AccessorInstanceRefWrapper& acc)
{
	METHODNAME_DEF( CTransferCscDM, createTransactionRecord )
	BLOG_TRACE_METHOD( getLogger(), fun );		

	return core::TransactionRecordBasePtr( new CTransferCscTransactionRecord( yit, acc, getCSC_Logger() ) );
}

//--------------------------------------------------------------------------------------------------//

basar::db::aspect::AccessorPropertyTable_YIterator CTransferCscDM::prepareFindOpenSearchCriteria( const domMod::pharmosTransaction::core::OffSetNo )
{
	METHODNAME_DEF( CTransferCscDM, prepareFindOpenSearchCriteria )
	BLOG_TRACE_METHOD( getLogger(), fun );		

	resetSearchYit();
	basar::db::aspect::AccessorPropertyTable_YIterator yitSearch = getSearchYit();
	yitSearch.setInt16(properties::pharmostransaction::BRANCHNO, 0);
	yitSearch.setString(properties::ctransfercsc::ZDPHOST, m_InitCTransferCscDM.m_ZDPHost);
	yitSearch.setString(properties::ctransfercsc::ZDPDATABASE, m_InitCTransferCscDM.m_ZDPDatabase);
	// entrydatetime >= today 00:00:00
	basar::DateTime today(basar::Date::getCurrent().getDate(), 0);
	yitSearch.setDateTime(properties::ctransfercsc::ENTRYDATETIME, today);
	return yitSearch;
}

//--------------------------------------------------------------------------------------------------//

void CTransferCscDM::doInit( const InitCTransferCscDM& initDM )
{
	METHODNAME_DEF( CTransferCscDM, doInit );
	BLOG_TRACE_METHOD( getLogger(), fun );

    m_InitCTransferCscDM = initDM;
}

//--------------------------------------------------------------------------------------------------//

void CTransferCscDM::doShutdown()
{
	METHODNAME_DEF( CTransferCscDM, doShutdown );
	BLOG_TRACE_METHOD( getLogger(), fun );
	
	clearPropertyTable();
}

//--------------------------------------------------------------------------------------------------//

} // namespace preparation
} // namespace pharmosTransaction
} // namespace domMod

//--------------------------------------------------------------------------------------------------//
