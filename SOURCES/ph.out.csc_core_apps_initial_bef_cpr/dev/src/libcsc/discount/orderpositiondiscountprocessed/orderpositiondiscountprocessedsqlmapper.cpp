#include "orderpositiondiscountprocessedsqlmapper.h"
#include "orderpositiondiscountprocessed.h"
#include "orderpositiondiscountprocessedinsertsqlparameterbinder.h"
#include "orderpositiondiscountprocessedselectsqlparameterbinder.h"
#include <sstream>
#include "logger/loggerpool.h"

namespace libcsc
{
namespace discount
{
OrderPositionDiscountProcessedSQLMapper::OrderPositionDiscountProcessedSQLMapper( 
	OrderPositionDiscountProcessedPtr positionDiscountProcessed, 
	const basar::db::sql::ResultsetRef resultSet 
		)
: OrderPositionDiscountProcessedMapperBase( positionDiscountProcessed ),
  m_ResultSet( resultSet )
{
}

OrderPositionDiscountProcessedSQLMapper::~OrderPositionDiscountProcessedSQLMapper()
{
}

bool OrderPositionDiscountProcessedSQLMapper::isInsertable( const OrderPositionDiscountProcessedPtr positionDiscountProcessed )
{
	// TODO: weitere checks?
	return positionDiscountProcessed->getPositionNo().isDirty();
}

const basar::VarString & OrderPositionDiscountProcessedSQLMapper::getInsertSQL()
{
	static basar::VarString sql;
	if( sql.empty() )
	{
		sql =   "INSERT INTO orderpositiondiscountprocessed "
				"("
				"orderno, "
				"posno, "
				"processingtime "
				") "
				"VALUES "
				"(?, ?, CURRENT)";
	}
	return sql;
}

const basar::VarString & OrderPositionDiscountProcessedSQLMapper::getSelectSQL()
{
	static basar::VarString sql;
	if( sql.empty() )
	{
		sql =	"SELECT "
				"orderno, "
				"posno, "
				"processingtime "

				"FROM orderpositiondiscountprocessed "

				"WHERE "
				"orderno = ?";
	}
	return sql;
}

const libcsc::persistence::ISqlParameterBinderPtr OrderPositionDiscountProcessedSQLMapper::getInsertSqlParameterBinder( const OrderPositionDiscountProcessedPtr positionDiscountProcessed )
{
	return libcsc::persistence::ISqlParameterBinderPtr( new OrderPositionDiscountProcessedInsertSqlParameterBinder( positionDiscountProcessed ) );
}

const libcsc::persistence::ISqlParameterBinderPtr OrderPositionDiscountProcessedSQLMapper::getSelectSqlParameterBinder( const basar::Int32 orderNo )
{
	return libcsc::persistence::ISqlParameterBinderPtr( new OrderPositionDiscountProcessedSelectSqlParameterBinder( orderNo ) );
}

void OrderPositionDiscountProcessedSQLMapper::bindInsertSQL( basar::db::sql::PreparedStatementRef prepStmt, const OrderPositionDiscountProcessedPtr positionDiscountProcessed )
{
	// Prepared statement setters take a reference and only move the address to the client sdk layer.
	// We have to take sure, variables are still existent at that moment execute() ist called!
	static basar::Int32 orderNo = 0;
	static basar::Int32 positionNo = 0;

	orderNo = positionDiscountProcessed->getOrderNo();
	positionNo = positionDiscountProcessed->getPositionNo();

	std::stringstream ss;
	ss << "OrderPositionDiscountProcessedSQLMapper::bindInsertSQL(), bind parameter values:" << std::endl;
	basar::UInt32 counter = 0;

	ss << counter << ": " << orderNo << " (orderNo)" << std::endl;
	prepStmt.setInt32( counter++, orderNo );
	ss << counter << ": " << positionNo << " (positionNo)" << std::endl;
	prepStmt.setInt32( counter++, positionNo );

	BLOG_TRACE( LoggerPool::getLoggerOrderPositionDiscount(), ss.str().c_str() );
}

void OrderPositionDiscountProcessedSQLMapper::bindSelectSQL( basar::db::sql::PreparedStatementRef prepStmt, const basar::Int32 orderNo )
{
	// Prepared statement setters take a reference and only move the address to the client sdk layer.
	// We have to take sure, variables are still existent at that moment execute() ist called!
	static basar::Int32 _orderNo = 0;

	_orderNo = orderNo;

	std::stringstream ss;
	ss << "OrderPositionDiscountProcessedSQLMapper::bindSelectSQL(), bind parameter values:" << std::endl;
	basar::UInt32 counter = 0;
	ss << counter << ": " << _orderNo << " (orderNo)" << std::endl;
	prepStmt.setInt32( counter++, _orderNo );

	BLOG_TRACE( LoggerPool::getLoggerOrderPositionDiscount(), ss.str().c_str() );
}

void OrderPositionDiscountProcessedSQLMapper::doMap()
{
	// TODO: check ResultSet
	if( m_ResultSet.isNull() )
	{
		throw;
	}

	setOrderNo( m_ResultSet.getInt32( "orderno" ) );
	setPositionNo( m_ResultSet.getInt32( "posno" ) );
	setProcessingTime( m_ResultSet.getDateTime( "processingtime" ) );
}

} // end namespace discount
} // end namespace libcsc

