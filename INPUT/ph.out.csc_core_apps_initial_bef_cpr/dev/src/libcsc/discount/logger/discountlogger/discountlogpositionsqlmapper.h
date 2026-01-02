#ifndef GUARD_LIBCSC_DISCOUNT_LOG_POSITION_SQL_MAPPER_H
#define GUARD_LIBCSC_DISCOUNT_LOG_POSITION_SQL_MAPPER_H

#include <discount/logger/discountlogger/discountlogpositionmapperbase.h>
#include <libbasardbsql_resultsetref.h>
#include <persistence/isqlparameterbinderptr.h>
#include <libbasardbsql_preparedstatementref.h>

namespace libcsc
{
namespace discount
{
class DiscountLogPositionSQLMapper : public DiscountLogPositionMapperBase
{
public:
	DiscountLogPositionSQLMapper( 
		DiscountLogPositionPtr discountLogPosition, 
		const basar::db::sql::ResultsetRef resultSet 
			);
	virtual ~DiscountLogPositionSQLMapper();

	static bool isInsertable( const DiscountLogPositionPtr discountLogPosition );
	static const basar::VarString & getInsertSQL();
	static const basar::VarString getDeleteSQL( const DiscountLogPositionPtr discountLogPosition );
	static const libcsc::persistence::ISqlParameterBinderPtr getInsertSqlParameterBinder( const DiscountLogPositionPtr discountLogPosition );
	static void bindInsertSQL( basar::db::sql::PreparedStatementRef prepStmt, const DiscountLogPositionPtr discountLogPosition );

protected:
	virtual void doMap();

private:
	DiscountLogPositionSQLMapper( const DiscountLogPositionSQLMapper & );
	DiscountLogPositionSQLMapper & operator=( const DiscountLogPositionSQLMapper & );

	const basar::db::sql::ResultsetRef		m_ResultSet;
};

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_DISCOUNT_LOG_POSITION_SQL_MAPPER_H
