#include "discountlogpositionsqlmapper.h"
#include "discountlogposition.h"
#include "discountlogpositioninsertsqlparameterbinder.h"
#include <sstream>
#include "logger/loggerpool.h"

namespace libcsc
{
namespace discount
{
DiscountLogPositionSQLMapper::DiscountLogPositionSQLMapper( 
	DiscountLogPositionPtr discountLogPosition, 
	const basar::db::sql::ResultsetRef resultSet 
		)
: DiscountLogPositionMapperBase( discountLogPosition ),
  m_ResultSet( resultSet )
{
}

DiscountLogPositionSQLMapper::~DiscountLogPositionSQLMapper()
{
}

bool DiscountLogPositionSQLMapper::isInsertable( const DiscountLogPositionPtr discountLogPosition )
{
	// TODO: weitere checks?
	return discountLogPosition->getPositionNo().isDirty();
}

const basar::VarString & DiscountLogPositionSQLMapper::getInsertSQL()
{
	static basar::VarString sql;
	if( sql.empty() )
	{
		sql =   "INSERT INTO discountcalclog "
				"("
				"orderno, "
				"posno, "
				"calctype, "
				"discountvalue, "
				"discountpercent, "
				"discountqty, "
				"rebateinkindposno "
				") "
				"VALUES "
				"(?, ?, ?, ?, ?, ?, ?)";
	}

	return sql;
}

const basar::VarString DiscountLogPositionSQLMapper::getDeleteSQL( const DiscountLogPositionPtr discountLogPosition )
{
	std::stringstream ss;
	ss <<	"DELETE "
			
			"FROM discountcalclog "

			"WHERE "
			"orderno = ";
	ss << discountLogPosition->getOrderNo();
	return ss.str().c_str();
}

const libcsc::persistence::ISqlParameterBinderPtr DiscountLogPositionSQLMapper::getInsertSqlParameterBinder( const DiscountLogPositionPtr discountLogPosition )
{
	return libcsc::persistence::ISqlParameterBinderPtr( new DiscountLogPositionInsertSqlParameterBinder( discountLogPosition ) );
}

void DiscountLogPositionSQLMapper::bindInsertSQL( basar::db::sql::PreparedStatementRef prepStmt, const DiscountLogPositionPtr discountLogPosition )
{
	// Prepared statement setters take a reference and only move the address to the client sdk layer.
	// We have to take sure, variables are still existent at that moment execute() ist called!
	static basar::Int32 orderNo = 0;
	static basar::Int32 positionNo = 0;
	static basar::Int16 calcType = 0;
	static basar::Decimal discountValue( 0 );
	static basar::Decimal discountPercent( 0 );
	static basar::Int16 discountQty = 0;
	static basar::Int32 rebateInKindPosNo = 0;

	orderNo = discountLogPosition->getOrderNo();
	positionNo = discountLogPosition->getPositionNo();
	calcType = static_cast<basar::Int16>( discountLogPosition->getDiscountCalculatorType() );
	discountValue = discountLogPosition->getDiscountValue();
	discountPercent = discountLogPosition->getDiscountPercent();
	discountQty = static_cast<basar::Int16>( discountLogPosition->getDiscountQty() );
	rebateInKindPosNo = discountLogPosition->getRebateInKindPosNo();

	std::stringstream ss;
	ss << "DiscountLogPositionSQLMapper::bindInsertSQL(), bind parameter values:" << std::endl;
	basar::UInt32 counter = 0;

	ss << counter << ": " << orderNo << " (orderNo)" << std::endl;
	prepStmt.setInt32( counter++, orderNo );
	ss << counter << ": " << positionNo << " (positionNo)" << std::endl;
	prepStmt.setInt32( counter++, positionNo );
	ss << counter << ": " << calcType << " (calcType)" << std::endl;
	prepStmt.setInt16( counter++, calcType );
	ss << counter << ": " << discountValue << " (discountValue)" << std::endl;
	prepStmt.setDecimal( counter++, discountValue );
	ss << counter << ": " << discountPercent << " (discountPercent)" << std::endl;
	prepStmt.setDecimal( counter++, discountPercent );
	ss << counter << ": " << discountQty << " (discountQty)" << std::endl;
	prepStmt.setInt16( counter++, discountQty );
	ss << counter << ": " << rebateInKindPosNo << " (rebateInKindPosNo)" << std::endl;
	prepStmt.setInt32( counter++, rebateInKindPosNo );

	BLOG_TRACE( LoggerPool::getLoggerDiscountLog(), ss.str().c_str() );
}

void DiscountLogPositionSQLMapper::doMap()
{
}

} // end namespace discount
} // end namespace libcsc

