#ifndef GUARD_LIBCSC_ORDER_POSITION_DISCOUNT_PROCESSED_SQL_MAPPER_H
#define GUARD_LIBCSC_ORDER_POSITION_DISCOUNT_PROCESSED_SQL_MAPPER_H

#include <discount/orderpositiondiscountprocessed/orderpositiondiscountprocessedmapperbase.h>
#include <libbasardbsql_resultsetref.h>




#include <discount/basevalues/orderbasevalue/iorderbasevaluegetterptr.h>
#include <persistence/isqlparameterbinderptr.h>
#include <libbasardbsql_preparedstatementref.h>

namespace libcsc
{
namespace discount
{
class OrderPositionDiscountProcessedSQLMapper : public OrderPositionDiscountProcessedMapperBase
{
public:
	OrderPositionDiscountProcessedSQLMapper( 
		OrderPositionDiscountProcessedPtr positionDiscountProcessed, 
		const basar::db::sql::ResultsetRef resultSet 
			);
	virtual ~OrderPositionDiscountProcessedSQLMapper();

	static bool isInsertable( const OrderPositionDiscountProcessedPtr positionDiscountProcessed );
	static const basar::VarString & getInsertSQL();
	static const basar::VarString & getSelectSQL();
	static const libcsc::persistence::ISqlParameterBinderPtr getInsertSqlParameterBinder( const OrderPositionDiscountProcessedPtr positionDiscountProcessed );
	static const libcsc::persistence::ISqlParameterBinderPtr getSelectSqlParameterBinder( const basar::Int32 orderNo );
	static void bindInsertSQL( basar::db::sql::PreparedStatementRef prepStmt, const OrderPositionDiscountProcessedPtr positionDiscountProcessed );
	static void bindSelectSQL( basar::db::sql::PreparedStatementRef prepStmt, const basar::Int32 orderNo );

protected:
	virtual void doMap();

private:
	OrderPositionDiscountProcessedSQLMapper( const OrderPositionDiscountProcessedSQLMapper & );
	OrderPositionDiscountProcessedSQLMapper & operator=( const OrderPositionDiscountProcessedSQLMapper & );

	const basar::db::sql::ResultsetRef		m_ResultSet;
};

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_ORDER_POSITION_DISCOUNT_PROCESSED_SQL_MAPPER_H
