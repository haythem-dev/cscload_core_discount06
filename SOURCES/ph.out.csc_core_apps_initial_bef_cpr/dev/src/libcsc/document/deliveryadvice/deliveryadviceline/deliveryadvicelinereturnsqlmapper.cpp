#include "deliveryadvicelinereturnsqlmapper.h"
#include "deliveryadvicelinereturn.h"
#include <libbasarcmnutil_date.h>
#include <logger/loggerpool.h>

namespace libcsc {
namespace document {

DeliveryAdviceLineReturnSQLMapper::DeliveryAdviceLineReturnSQLMapper( DeliveryAdviceLineReturnPtr deliveryAdviceLineReturn, const basar::db::sql::ResultsetRef resultSet) :
	DeliveryAdviceLineReturnMapperBase( deliveryAdviceLineReturn ),
	m_ResultSet(resultSet)
{
}

DeliveryAdviceLineReturnSQLMapper::~DeliveryAdviceLineReturnSQLMapper()
{
}

const basar::VarString DeliveryAdviceLineReturnSQLMapper::getSelectSQL( const basar::VarString & dbName, 
																		const basar::Int16 branchNo, 
																		const basar::Int32 customerNo, 
																		const basar::Date& deliveryAdviceDate,
																		const basar::VarString &  deliveryAdviceNo,
																		const basar::Int32 deliveryAdvicePosNo )
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DeliveryAdviceLineReturnSQLMapper::getSelectSQL()");

	std::stringstream sSql;

	sSql <<
		"SELECT "
		"branchno, "
		"customerno, "
		"deliveryadvicedate, "
		"deliveryadviceno, "
		"deliveryadviceposno, "
		"blockedforreturns, "
		"qty_returned, "
		"qty_returned_rebateinkind, "
		"qty_return_rejected "
		"FROM " << dbName << ":deliveryadvicelinereturn "
		"WHERE ";
	sSql << " branchno = " << branchNo << " and customerno = " << customerNo << " and deliveryadvicedate = " << deliveryAdviceDate.getDate() <<
		" and deliveryadviceno = '" << deliveryAdviceNo << "' and deliveryadviceposno =" << deliveryAdvicePosNo;
	return sSql.str();
}


//----------------------------------------------------------------------------------
// Mapping from database
//----------------------------------------------------------------------------------
void DeliveryAdviceLineReturnSQLMapper::doMap()
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DeliveryAdviceLineReturnSQLMapper::doMap()");

	if( m_ResultSet.isNull() )
	{
		throw;
	}

	setBranchNo( m_ResultSet.getInt16("branchno") );
	setCustomerNo( m_ResultSet.getInt32("customerno") );
	setDeliveryAdviceDate( basar::Date(m_ResultSet.getInt32("deliveryadvicedate") ));
	setDeliveryAdviceNo( m_ResultSet.getString("deliveryadviceno") );
	setDeliveryAdvicePosNo( m_ResultSet.getInt32("deliveryadviceposno") );

	setBlockedForreturns( m_ResultSet.getInt16("blockedforreturns") );
	setQuantityReturned(m_ResultSet.getInt32("qty_returned") );
	setQuantityReturnedRebateInKind( m_ResultSet.getInt32("qty_returned_rebateinkind") );
	setQuantityReturnRejected( m_ResultSet.getInt32("qty_return_rejected") );
}

} // end namespace document
} // end namespace libcsc
