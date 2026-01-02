#include "csccallplanselectsqlparameterbinder.h"
#include "csccallplansqlmapper.h"

namespace libcsc {
namespace cscorder {
namespace repo {

CSCCallplanSelectSqlParameterBinder::CSCCallplanSelectSqlParameterBinder(domMod::ICSCCallplanPtr cscCallplan)
    : m_CSCCallplan(cscCallplan)
{
}

CSCCallplanSelectSqlParameterBinder::~CSCCallplanSelectSqlParameterBinder()
{
}

void CSCCallplanSelectSqlParameterBinder::bind(basar::db::sql::PreparedStatementRef preparedStatement) const
{
    CSCCallplanSqlMapper::bindSelectSQL(preparedStatement, m_CSCCallplan);
}

} // end namespace repo
} // end namespace cscorder
} // end namespace libcsc
