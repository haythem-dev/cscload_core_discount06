#include "discountlogpositioninsertsqlparameterbinder.h"
#include "discountlogpositionsqlmapper.h"

namespace libcsc
{
namespace discount
{
DiscountLogPositionInsertSqlParameterBinder::DiscountLogPositionInsertSqlParameterBinder( const DiscountLogPositionPtr discountLogPosition )
: m_DiscountLogPosition( discountLogPosition )
{
}

DiscountLogPositionInsertSqlParameterBinder::~DiscountLogPositionInsertSqlParameterBinder()
{
}

void DiscountLogPositionInsertSqlParameterBinder::bind( basar::db::sql::PreparedStatementRef preparedStatement ) const
{
	DiscountLogPositionSQLMapper::bindInsertSQL( preparedStatement, m_DiscountLogPosition );
}

} // end namespace discount
} // end namespace libcsc

