#include "customerdataselectsqlparameterbinder.h"
#include "customerdatasqlmapper.h"

namespace libcsc {
namespace msv3 {

CustomerDataSelectSqlParameterBinder::CustomerDataSelectSqlParameterBinder(const short branchno, const int customerno) 
	: m_BranchNo( branchno ), m_CustomerNo( customerno )
{
}

CustomerDataSelectSqlParameterBinder::~CustomerDataSelectSqlParameterBinder()
{
}

void CustomerDataSelectSqlParameterBinder::bind(basar::db::sql::PreparedStatementRef preparedStatement) const
{
	CustomerDataSQLMapper::bindSelectSQL(preparedStatement, m_BranchNo, m_CustomerNo);
}

} // end namespace msv3
} // end namespace libcsc
