#ifndef GUARD_LIBCSC_ORDER_POSITION_DISCOUNT_SQL_MAPPER_H
#define GUARD_LIBCSC_ORDER_POSITION_DISCOUNT_SQL_MAPPER_H

#include "orderpositiondiscountmapperbase.h"
#include <libbasardbsql_resultsetref.h>
#include <discount/basevalues/orderbasevalue/iorderbasevaluegetterptr.h>
#include <persistence/isqlparameterbinderptr.h>
#include <libbasardbsql_preparedstatementref.h>

namespace libcsc
{
namespace discount
{
class OrderPositionDiscountSQLMapper : public OrderPositionDiscountMapperBase
{
public:
	OrderPositionDiscountSQLMapper( 
		OrderPositionDiscountPtr positionDiscount, 
		const basar::db::sql::ResultsetRef resultSet 
			);
	virtual ~OrderPositionDiscountSQLMapper();

	static bool isInsertable( const OrderPositionDiscountPtr positionDiscount );
	static bool isUpdatable( const OrderPositionDiscountPtr positionDiscount );

	static const basar::VarString & getInsertSQL();
	static const basar::VarString & getUpdateSQL();
	static const basar::VarString & getDeleteSQL();
	static const basar::VarString & getSingleArticleSelectSQL();
	static const basar::VarString & getOrderCompletionSelectSQL();
	static const basar::VarString & getRebateInKindEntrySelectSQL();

	static const libcsc::persistence::ISqlParameterBinderPtr getInsertSqlParameterBinder( const OrderPositionDiscountPtr positionDiscount );
	static const libcsc::persistence::ISqlParameterBinderPtr getUpdateSqlParameterBinder( const OrderPositionDiscountPtr positionDiscount );
	static const libcsc::persistence::ISqlParameterBinderPtr getDeleteSqlParameterBinder( const OrderPositionDiscountPtr positionDiscount );
	static const libcsc::persistence::ISqlParameterBinderPtr getSingleArticleSelectSqlParameterBinder( const basar::Int32 orderNo, const basar::Int32 positionNo );
	static const libcsc::persistence::ISqlParameterBinderPtr getRebateInKindEntrySelectSQLParameterBinder(const basar::Int32 rebateinkindorderNo, const basar::Int32 rebateinkindpositionNo);
	static const libcsc::persistence::ISqlParameterBinderPtr getOrderCompletionSelectSqlParameterBinder( const basar::Int32 orderNo );

	static void bindInsertSQL( basar::db::sql::PreparedStatementRef prepStmt, const OrderPositionDiscountPtr positionDiscount );
	static void bindUpdateSQL( basar::db::sql::PreparedStatementRef prepStmt, const OrderPositionDiscountPtr positionDiscount );
	static void bindDeleteSQL( basar::db::sql::PreparedStatementRef prepStmt, const OrderPositionDiscountPtr positionDiscount );
	static void bindSingleArticleSelectSQL( basar::db::sql::PreparedStatementRef prepStmt, const basar::Int32 orderNo, const basar::Int32 positionNo );
	static void bindRebateInKindEntrySelectSQL(basar::db::sql::PreparedStatementRef prepStmt, const basar::Int32 rebateinkindorderNo, const basar::Int32 rebateinkindpositionNo);
	static void bindOrderCompletionSelectSQL( basar::db::sql::PreparedStatementRef prepStmt, const basar::Int32 orderNo );

protected:
	virtual void doMap();

private:
	OrderPositionDiscountSQLMapper( const OrderPositionDiscountSQLMapper & );
	OrderPositionDiscountSQLMapper & operator=( const OrderPositionDiscountSQLMapper & );

	const basar::db::sql::ResultsetRef		m_ResultSet;
};

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_ORDER_POSITION_DISCOUNT_SQL_MAPPER_H
