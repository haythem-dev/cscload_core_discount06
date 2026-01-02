#ifndef GUARD_LIBCSC_TENDER_DISCOUNT_SQL_MAPPER_H
#define GUARD_LIBCSC_TENDER_DISCOUNT_SQL_MAPPER_H

#include "tenderdiscountmapperbase.h"
#include <libbasardbsql_resultsetref.h>
#include <discount/tender/repository/tenderdiscountsearchparams.h>
#include <persistence/isqlparameterbinderptr.h>
#include <libbasardbsql_preparedstatementref.h>

namespace libcsc
{
namespace discount
{
class TenderDiscountSQLMapper : public TenderDiscountMapperBase
{
public:
	TenderDiscountSQLMapper( 
		TenderDiscountPtr tenderDiscount, 
		const basar::db::sql::ResultsetRef resultSet 
			);
	virtual ~TenderDiscountSQLMapper();

    static const basar::VarString  getSelectSQL(const TenderDiscountSearchParams & params);
	//static const basar::VarString & getSelectSQL();
	//static const libcsc::persistence::ISqlParameterBinderPtr getSelectSqlParameterBinder( const TenderDiscountSearchParams & params );
	//static void bindSelectSQL( basar::db::sql::PreparedStatementRef prepStmt, const TenderDiscountSearchParams & params );

protected:
	virtual void doMap();

private:
	TenderDiscountSQLMapper( const TenderDiscountSQLMapper & );
	TenderDiscountSQLMapper & operator=( const TenderDiscountSQLMapper & );

	const basar::db::sql::ResultsetRef		m_ResultSet;
};

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_TENDER_DISCOUNT_SQL_MAPPER_H
