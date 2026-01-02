#ifndef GUARD_LIBCSC_DISCOUNT_LOG_POSITION_INSERT_SQL_PARAMETER_BINDER_H
#define GUARD_LIBCSC_DISCOUNT_LOG_POSITION_INSERT_SQL_PARAMETER_BINDER_H

#include <persistence/isqlparameterbinder.h>
#include <discount/logger/discountlogger/discountlogpositionptr.h>

namespace libcsc
{
namespace discount
{
class DiscountLogPositionInsertSqlParameterBinder : public libcsc::persistence::ISqlParameterBinder
{
public:
	DiscountLogPositionInsertSqlParameterBinder( const DiscountLogPositionPtr discountLogPosition );
	virtual ~DiscountLogPositionInsertSqlParameterBinder();

	virtual void bind( basar::db::sql::PreparedStatementRef preparedStatement ) const;

private:
	DiscountLogPositionPtr m_DiscountLogPosition;
};

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_DISCOUNT_LOG_POSITION_INSERT_SQL_PARAMETER_BINDER_H



