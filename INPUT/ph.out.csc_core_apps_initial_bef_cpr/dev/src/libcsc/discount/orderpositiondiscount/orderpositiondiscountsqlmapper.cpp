#include "orderpositiondiscountsqlmapper.h"
#include "orderpositiondiscount.h"
#include "orderpositiondiscountinsertsqlparameterbinder.h"
#include "orderpositiondiscountupdatesqlparameterbinder.h"
#include "orderpositiondiscountdeletesqlparameterbinder.h"
#include "orderpositiondiscountsinglearticleselectsqlparameterbinder.h"
#include "orderpositiondiscountordercompletionselectsqlparameterbinder.h"
#include "orderpositiondiscountrebateinkindentryselectsqlparameterbinder.h"
#include "discount/basevalues/orderbasevalue/iorderbasevaluegetter.h"
#include <sstream>
#include "logger/loggerpool.h"

namespace libcsc
{
namespace discount
{
OrderPositionDiscountSQLMapper::OrderPositionDiscountSQLMapper( 
	OrderPositionDiscountPtr positionDiscount, 
	const basar::db::sql::ResultsetRef resultSet 
		)
: OrderPositionDiscountMapperBase( positionDiscount ),
  m_ResultSet( resultSet )
{
}

OrderPositionDiscountSQLMapper::~OrderPositionDiscountSQLMapper()
{
}

bool OrderPositionDiscountSQLMapper::isInsertable( const OrderPositionDiscountPtr positionDiscount )
{
	// TODO: weitere checks?
	return positionDiscount->getDiscountMode().isDirty() || positionDiscount->getRebateInKindPositionNo().isDirty();
}

bool OrderPositionDiscountSQLMapper::isUpdatable( const OrderPositionDiscountPtr positionDiscount )
{
	// TODO: weitere checks?
	return positionDiscount->getDiscountMode().isClean() && positionDiscount->getRebateInKindPositionNo().isClean();
}

const basar::VarString & OrderPositionDiscountSQLMapper::getInsertSQL()
{
	static basar::VarString sql;
	if( sql.empty() )
	{
		sql =   "INSERT INTO orderpositiondiscount "
				"("
				"orderno, "
				"posno, "
				"discountmode, "
				"discountvalue, "
				"discountpercent, "
				"discountqty, "				
				"rebateinkindposno, "
				"rebateinkindorderno, "
				"pharmacygroupid "
				") "
				"VALUES "
				"(?, ?, ?, ?, ?, ?, ?, ?, ?)";
	}
	return sql;
}

const basar::VarString & OrderPositionDiscountSQLMapper::getUpdateSQL()
{
	static basar::VarString sql;
	if( sql.empty() )
	{
		sql =	"UPDATE orderpositiondiscount "

				"SET "
				"discountvalue = ?, "
				"discountpercent = ?, "
				"discountqty = ?, "
				"pharmacygroupid = ? "
				"WHERE "
				"rebateinkindposno = ? "
				"AND "
				"rebateinkindorderno = ? "
				"AND "
				"orderno = ? "
				"AND "
				"posno = ? "
				"AND "
				"discountmode = ? ";
	}
	return sql;
}

const basar::VarString & OrderPositionDiscountSQLMapper::getDeleteSQL()
{
	static basar::VarString sql;
	if( sql.empty() )
	{
		sql =	"DELETE orderpositiondiscount "

				"WHERE "
				"orderno = ? "
				"AND "
				"posno = ? "
				"AND "
				"discountmode = ? "
				"AND "
				"rebateinkindposno = ? "
				"AND "
				"rebateinkindorderno = ? ";

	}
	return sql;
}

const basar::VarString & OrderPositionDiscountSQLMapper::getSingleArticleSelectSQL()
{
	static basar::VarString sql;
	if( sql.empty() )
	{
		sql =	"SELECT "
				"orderno, "
				"posno, "
				"discountmode, "
				"discountvalue, "
				"discountpercent, "
				"discountqty, "
				"rebateinkindposno, "
				"rebateinkindorderno, "
				"pharmacygroupid "
				"FROM orderpositiondiscount "
				"WHERE "
				"orderno = ? "
				"AND "
				"posno = ? ";
	}
	return sql;
}

const basar::VarString & OrderPositionDiscountSQLMapper::getRebateInKindEntrySelectSQL()
{
	static basar::VarString sql;
	if (sql.empty())
	{
		sql = "SELECT "
			"orderno, "
			"posno, "
			"discountmode, "
			"discountvalue, "
			"discountpercent, "
			"discountqty, "
			"rebateinkindposno, "
			"rebateinkindorderno, "
			"pharmacygroupid "
			"FROM orderpositiondiscount "
			"WHERE "
			"rebateinkindorderno = ? "
			"AND "
			"rebateinkindposno = ? ";
	}
	return sql;
}

const basar::VarString & OrderPositionDiscountSQLMapper::getOrderCompletionSelectSQL()
{
	static basar::VarString sql;
	if( sql.empty() )
	{
		sql =	"SELECT "
				"orderno, "
				"posno, "
				"discountmode, "
				"discountvalue, "
				"discountpercent, "
				"discountqty, "
				"rebateinkindposno, "
				"rebateinkindorderno, "
				"pharmacygroupid "
				"FROM orderpositiondiscount "
				"WHERE "
				"orderno = ? ";
	}
	return sql;
}

const libcsc::persistence::ISqlParameterBinderPtr OrderPositionDiscountSQLMapper::getInsertSqlParameterBinder( const OrderPositionDiscountPtr positionDiscount )
{
	return libcsc::persistence::ISqlParameterBinderPtr( new OrderPositionDiscountInsertSqlParameterBinder( positionDiscount ) );
}

const libcsc::persistence::ISqlParameterBinderPtr OrderPositionDiscountSQLMapper::getUpdateSqlParameterBinder( const OrderPositionDiscountPtr positionDiscount )
{
	return libcsc::persistence::ISqlParameterBinderPtr( new OrderPositionDiscountUpdateSqlParameterBinder( positionDiscount ) );
}

const libcsc::persistence::ISqlParameterBinderPtr OrderPositionDiscountSQLMapper::getDeleteSqlParameterBinder( const OrderPositionDiscountPtr positionDiscount )
{
	return libcsc::persistence::ISqlParameterBinderPtr( new OrderPositionDiscountDeleteSqlParameterBinder( positionDiscount ) );
}

const libcsc::persistence::ISqlParameterBinderPtr OrderPositionDiscountSQLMapper::getSingleArticleSelectSqlParameterBinder( const basar::Int32 orderNo, const basar::Int32 positionNo )
{
	return libcsc::persistence::ISqlParameterBinderPtr( new OrderPositionDiscountSingleArticleSelectSqlParameterBinder( orderNo, positionNo ) );
}

const libcsc::persistence::ISqlParameterBinderPtr OrderPositionDiscountSQLMapper::getRebateInKindEntrySelectSQLParameterBinder(const basar::Int32 rebateinkindorderNo, const basar::Int32 rebateinkindpositionNo )
{
	return libcsc::persistence::ISqlParameterBinderPtr(new OrderPositionDiscountRebateInKindEntrySelectSQLParameterBinder(rebateinkindorderNo, rebateinkindpositionNo));
}

const libcsc::persistence::ISqlParameterBinderPtr OrderPositionDiscountSQLMapper::getOrderCompletionSelectSqlParameterBinder( const basar::Int32 orderNo )
{
	return libcsc::persistence::ISqlParameterBinderPtr( new OrderPositionDiscountOrderCompletionSelectSqlParameterBinder( orderNo ) );
}

void OrderPositionDiscountSQLMapper::bindInsertSQL( basar::db::sql::PreparedStatementRef prepStmt, const OrderPositionDiscountPtr positionDiscount )
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerOrderPositionDiscount(), "OrderPositionDiscountSQLMapper::bindInsertSQL()" );

	// Prepared statement setters take a reference and only move the address to the client sdk layer.
	// We have to take sure, variables are still existent at that moment execute() ist called!
	static basar::Int32 orderNo = 0;
	static basar::Int32 positionNo = 0;
	static basar::Int16 discountMode = 0;
	static basar::Decimal discountValue( 0 );
	static basar::Decimal discountPercent( 0 );
	static basar::Int16 discountQty = 0;
	static basar::Int32 rebateInKindPositionNo = 0;
	static basar::Int32 rebateInKindOrderNo = 0;
	static basar::VarString pharmacyGroupId = basar::VarString();

	if( LoggerPool::getLoggerOrderPositionDiscount().isEnabledFor( log4cplus::TRACE_LOG_LEVEL ) )
	{
		std::stringstream ss;
		ss << "OrderPositionDiscount: " << ( *positionDiscount );
		LoggerPool::getLoggerOrderPositionDiscount().forcedLog( log4cplus::TRACE_LOG_LEVEL, ss.str().c_str(), __FILE__, __LINE__ );
	}

	orderNo = positionDiscount->getOrderNo();
	positionNo = positionDiscount->getPositionNo();
	discountMode = static_cast<basar::Int16>( positionDiscount->getDiscountMode() );
	discountValue = positionDiscount->getDiscountValue().isUnset() ? libcsc::Decimal::zero() : positionDiscount->getDiscountValue();
	discountPercent = positionDiscount->getDiscountPercent().isUnset() ? libcsc::Decimal::zero() : positionDiscount->getDiscountPercent();
	discountQty = static_cast<basar::Int16>( positionDiscount->getDiscountQty().isUnset() ? libcsc::Int32( 0 ) : positionDiscount->getDiscountQty() );
	rebateInKindPositionNo = positionDiscount->getRebateInKindPositionNo();
	rebateInKindOrderNo = positionDiscount->getRebateInKindOrderNo();
	pharmacyGroupId = positionDiscount->getPharmacyGroupId();

	std::stringstream ss;
	ss << "OrderPositionDiscountSQLMapper::bindInsertSQL(), bind parameter values:" << std::endl;
	basar::UInt32 counter = 0;

	ss << counter << ": " << orderNo << " (orderNo)" << std::endl;
	prepStmt.setInt32( counter++, orderNo );
	ss << counter << ": " << positionNo << " (positionNo)" << std::endl;
	prepStmt.setInt32( counter++, positionNo );
	ss << counter << ": " << discountMode << " (discountMode)" << std::endl;
	prepStmt.setInt16( counter++, discountMode );
	ss << counter << ": " << discountValue << " (discountValue)" << std::endl;
	prepStmt.setDecimal( counter++, discountValue );
	ss << counter << ": " << discountPercent << " (discountPercent)" << std::endl;
	prepStmt.setDecimal( counter++, discountPercent );
	ss << counter << ": " << discountQty << " (discountQty)" << std::endl;
	prepStmt.setInt16( counter++, discountQty );
	ss << counter << ": " << rebateInKindPositionNo << " (rebateInKindPositionNo)" << std::endl;
	prepStmt.setInt32( counter++, rebateInKindPositionNo );
	ss << counter << ": " << rebateInKindOrderNo << " (rebateInKindOrderNo)" << std::endl;
	prepStmt.setInt32(counter++, rebateInKindOrderNo);
	ss << counter << ": " << pharmacyGroupId << " (pharmacyGroupId)" << std::endl;
	prepStmt.setString(counter++, pharmacyGroupId.c_str());

	BLOG_TRACE( LoggerPool::getLoggerOrderPositionDiscount(), ss.str().c_str() );
}

void OrderPositionDiscountSQLMapper::bindUpdateSQL( basar::db::sql::PreparedStatementRef prepStmt, const OrderPositionDiscountPtr positionDiscount )
{
	// Prepared statement setters take a reference and only move the address to the client sdk layer.
	// We have to take sure, variables are still existent at that moment execute() ist called!
	
	static basar::Int32 orderNo = 0;
	static basar::Int32 positionNo = 0;
	static basar::Int16 discountMode = 0;
	static basar::Decimal discountValue( 0 );
	static basar::Decimal discountPercent( 0 );
	static basar::Int16 discountQty = 0;
	static basar::Int32 rebateInKindPositionNo = 0;
	static basar::Int32 rebateInKindOrderNo = 0;
	static basar::VarString pharmacyGroupId = basar::VarString();

	orderNo = positionDiscount->getOrderNo();
	positionNo = positionDiscount->getPositionNo();
	discountMode = static_cast<basar::Int16>( positionDiscount->getDiscountMode() );
	discountValue = positionDiscount->getDiscountValue();
	discountPercent = positionDiscount->getDiscountPercent();
	discountQty = static_cast<basar::Int16>( positionDiscount->getDiscountQty() );
	rebateInKindPositionNo = positionDiscount->getRebateInKindPositionNo();
	rebateInKindOrderNo = positionDiscount->getRebateInKindOrderNo();
	pharmacyGroupId = positionDiscount->getPharmacyGroupId();

	std::stringstream ss;
	ss << "OrderPositionDiscountSQLMapper::bindUpdateSQL(), bind parameter values:" << std::endl;
	basar::UInt32 counter = 0;

	ss << counter << ": " << discountValue << " (discountValue)" << std::endl;
	prepStmt.setDecimal( counter++, discountValue );
	ss << counter << ": " << discountPercent << " (discountPercent)" << std::endl;
	prepStmt.setDecimal( counter++, discountPercent );
	ss << counter << ": " << discountQty << " (discountQty)" << std::endl;
	prepStmt.setInt16( counter++, discountQty );
	ss << counter << ": " << pharmacyGroupId << " (pharmacyGroupId)" << std::endl;
	prepStmt.setString(counter++, pharmacyGroupId.c_str());
	ss << counter << ": " << rebateInKindPositionNo << " (rebateInKindPositionNo)" << std::endl;
	prepStmt.setInt32( counter++, rebateInKindPositionNo );
	ss << counter << ": " << rebateInKindOrderNo << " (rebateInKindOrderNo)" << std::endl;
	prepStmt.setInt32(counter++, rebateInKindOrderNo);
	ss << counter << ": " << orderNo << " (orderNo)" << std::endl;
	prepStmt.setInt32( counter++, orderNo );
	ss << counter << ": " << positionNo << " (positionNo)" << std::endl;
	prepStmt.setInt32( counter++, positionNo );
	ss << counter << ": " << discountMode << " (discountMode)" << std::endl;
	prepStmt.setInt16( counter++, discountMode );

	BLOG_TRACE( LoggerPool::getLoggerOrderPositionDiscount(), ss.str().c_str() );
}

void OrderPositionDiscountSQLMapper::bindSingleArticleSelectSQL( basar::db::sql::PreparedStatementRef prepStmt, const basar::Int32 orderNo, const basar::Int32 positionNo )
{
	// Prepared statement setters take a reference and only move the address to the client sdk layer.
	// We have to take sure, variables are still existent at that moment execute() ist called!
	static basar::Int32 _orderNo = 0;
	static basar::Int32 _positionNo = 0;

	_orderNo = orderNo;
	_positionNo = positionNo;

	std::stringstream ss;
	ss << "OrderPositionDiscountSQLMapper::bindSingleArticleSelectSQL(), bind parameter values:" << std::endl;
	basar::UInt32 counter = 0;
	ss << counter << ": " << _orderNo << " (orderNo)" << std::endl;
	prepStmt.setInt32( counter++, _orderNo );
	ss << counter << ": " << _positionNo << " (positionNo)" << std::endl;
	prepStmt.setInt32( counter++, _positionNo );

	BLOG_TRACE( LoggerPool::getLoggerOrderPositionDiscount(), ss.str().c_str() );
}

void OrderPositionDiscountSQLMapper::bindRebateInKindEntrySelectSQL(basar::db::sql::PreparedStatementRef prepStmt, const basar::Int32 rebateinkindorderNo, const basar::Int32 rebateinkindpositionNo)
{
	// Prepared statement setters take a reference and only move the address to the client sdk layer.
	// We have to take sure, variables are still existent at that moment execute() ist called!
	static basar::Int32 _rebateinkindorderNo = 0;
	static basar::Int32 _rebateinkindpositionNo = 0;

	_rebateinkindorderNo = rebateinkindorderNo;
	_rebateinkindpositionNo = rebateinkindpositionNo;

	std::stringstream ss;
	ss << "OrderPositionDiscountSQLMapper::bindSingleArticleSelectSQL(), bind parameter values:" << std::endl;
	basar::UInt32 counter = 0;
	ss << counter << ": " << _rebateinkindorderNo << " (orderNo)" << std::endl;
	prepStmt.setInt32(counter++, _rebateinkindorderNo);
	ss << counter << ": " << _rebateinkindpositionNo << " (positionNo)" << std::endl;
	prepStmt.setInt32(counter++, _rebateinkindpositionNo);

	BLOG_TRACE(LoggerPool::getLoggerOrderPositionDiscount(), ss.str().c_str());
}

void OrderPositionDiscountSQLMapper::bindOrderCompletionSelectSQL( basar::db::sql::PreparedStatementRef prepStmt, const basar::Int32 orderNo )
{
	// Prepared statement setters take a reference and only move the address to the client sdk layer.
	// We have to take sure, variables are still existent at that moment execute() ist called!
	static basar::Int32 _orderNo = 0;

	_orderNo = orderNo;

	std::stringstream ss;
	ss << "OrderPositionDiscountSQLMapper::bindOrderCompletionSelectSQL(), bind parameter values:" << std::endl;
	basar::UInt32 counter = 0;
	ss << counter << ": " << _orderNo << " (orderNo)" << std::endl;
	prepStmt.setInt32( counter++, _orderNo );

	BLOG_TRACE( LoggerPool::getLoggerOrderPositionDiscount(), ss.str().c_str() );
}

void OrderPositionDiscountSQLMapper::bindDeleteSQL( basar::db::sql::PreparedStatementRef prepStmt, const OrderPositionDiscountPtr positionDiscount )
{
	// Prepared statement setters take a reference and only move the address to the client sdk layer.
	// We have to take sure, variables are still existent at that moment execute() ist called!
	static basar::Int32 orderNo = 0;
	static basar::Int32 positionNo = 0;
	static basar::Int16 discountMode = 0;
	static basar::Int32 rebateInKindPositionNo = 0;
	static basar::Int32 rebateInKindOrderNo = 0;

	orderNo = positionDiscount->getOrderNo();
	positionNo = positionDiscount->getPositionNo();
	discountMode = static_cast<basar::Int16>( positionDiscount->getDiscountMode() );
	rebateInKindPositionNo = positionDiscount->getRebateInKindPositionNo();
	rebateInKindOrderNo = positionDiscount->getRebateInKindOrderNo();

	std::stringstream ss;
	ss << "OrderPositionDiscountSQLMapper::bindDeleteSQL(), bind parameter values:" << std::endl;
	basar::UInt32 counter = 0;
	ss << counter << ": " << orderNo << " (orderNo)" << std::endl;
	prepStmt.setInt32( counter++, orderNo );
	ss << counter << ": " << positionNo << " (positionNo)" << std::endl;
	prepStmt.setInt32( counter++, positionNo );
	ss << counter << ": " << discountMode << " (discountMode)" << std::endl;
	prepStmt.setInt16( counter++, discountMode );
	ss << counter << ": " << rebateInKindPositionNo << " (rebateInKindPositionNo)" << std::endl;
	prepStmt.setInt32( counter++, rebateInKindPositionNo );
	ss << counter << ": " << rebateInKindOrderNo << " (rebateInKindOrderNo)" << std::endl;
	prepStmt.setInt32(counter++, rebateInKindOrderNo);


	BLOG_TRACE( LoggerPool::getLoggerOrderPositionDiscount(), ss.str().c_str() );
}

void OrderPositionDiscountSQLMapper::doMap()
{
	// TODO: check ResultSet
	if( m_ResultSet.isNull() )
	{
		throw;
	}

	// TODO: 
	setOrderNo( m_ResultSet.getInt32( "orderno" ) );
	setPositionNo( m_ResultSet.getInt32( "posno" ) );
	setDiscountMode( static_cast<OrderPositionDiscountModeEnum>( m_ResultSet.getInt16( "discountmode" ) ) );
	setDiscountValue( m_ResultSet.getDecimal( "discountvalue" ) );
	setDiscountPercent( m_ResultSet.getDecimal( "discountpercent" ) );
	setDiscountQty( m_ResultSet.getInt16( "discountqty" ) );
	setRebateInKindPositionNo( m_ResultSet.getInt32( "rebateinkindposno" ) );
	setRebateInKindOrderNo(m_ResultSet.getInt32("rebateinkindorderno"));
	setPharmacyGroupId(m_ResultSet.getString("pharmacygroupid"));
}

} // end namespace discount
} // end namespace libcsc

