#ifndef GUARD_LIBCSC_DISCOUNT_BASE_VALUE_SQL_MAPPER_H
#define GUARD_LIBCSC_DISCOUNT_BASE_VALUE_SQL_MAPPER_H

#include "discountbasevaluemapperbase.h"
#include <libbasardbsql_resultsetref.h>
#include <discount/basevalues/orderbasevalue/iorderbasevaluegetterptr.h>
#include <persistence/isqlparameterbinderptr.h>
#include <libbasardbsql_preparedstatementref.h>

namespace libcsc
{
namespace discount
{
class DiscountBaseValueSQLMapper : public DiscountBaseValueMapperBase
{
public:
	DiscountBaseValueSQLMapper( 
		DiscountBaseValuePtr value, 
		const basar::db::sql::ResultsetRef resultSet 
			);
	virtual ~DiscountBaseValueSQLMapper();

	static const libcsc::persistence::ISqlParameterBinderPtr getSingleArticleSqlParameterBinder( const IOrderBaseValueGetterPtr orderBaseValue );
	static const basar::VarString & getSingleArticleSelectSQL();
	static const basar::VarString getSingleArticleSelectDESQL(const IOrderBaseValueGetterPtr orderBaseValue);
	static const basar::VarString getMultiArticleSelectSQL( const IOrderBaseValueGetterPtr orderBaseValue );
	static void bindSingleArticleSelectSQL( basar::db::sql::PreparedStatementRef prepStmt, const IOrderBaseValueGetterPtr orderBaseValue );

protected:
	virtual void doMap();

private:
	DiscountBaseValueSQLMapper( const DiscountBaseValueSQLMapper & );
	DiscountBaseValueSQLMapper & operator=( const DiscountBaseValueSQLMapper & );

	static const basar::VarString getSelectSQL( const IOrderBaseValueGetterPtr orderBaseValue, const bool isSelectForSingleArticle = false );
	static const basar::VarString combineSelectSQLParts		( const IOrderBaseValueGetterPtr orderBaseValue, const basar::Int16 section,const bool isSelectForSingleArticle );

	static const basar::VarString getSelectSQLBranchDate	( const IOrderBaseValueGetterPtr orderBaseValue, const bool isSelectForSingleArticle );
	static const basar::VarString getSelectSQLPharmGrp		( const IOrderBaseValueGetterPtr orderBaseValue, const bool onlyDedicated, const bool isSelectForSingleArticle );
	static const basar::VarString getSelectSQLCustPharmGrp	( const IOrderBaseValueGetterPtr orderBaseValue, const bool isSelectForSingleArticle );
	static const basar::VarString getSelectSQLDiscGrp		( const IOrderBaseValueGetterPtr orderBaseValue, const bool onlyDedicated,	const bool isSelectForSingleArticle );
	static const basar::VarString getSelectSQLManufacturerByArticles( const IOrderBaseValueGetterPtr orderBaseValue );
	static const basar::VarString getSelectSQLCustomer		( const IOrderBaseValueGetterPtr orderBaseValue, const bool onlyDedicated, const bool isSelectForSingleArticle );
	static const basar::VarString getSelectSQLArticle		( const IOrderBaseValueGetterPtr orderBaseValue, const bool onlyDedicated,	const bool isSelectForSingleArticle );
	static const basar::VarString getSelectSQLManufacturer	( const IOrderBaseValueGetterPtr orderBaseValue, const bool onlyDedicated,	const bool isSelectForSingleArticle );
	

	const basar::db::sql::ResultsetRef		m_ResultSet;
};

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_DISCOUNT_BASE_VALUE_SQL_MAPPER_H
