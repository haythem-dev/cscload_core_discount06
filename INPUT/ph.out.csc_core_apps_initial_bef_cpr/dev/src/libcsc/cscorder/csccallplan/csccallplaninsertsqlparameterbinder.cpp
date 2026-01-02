#include "csccallplaninsertsqlparameterbinder.h"
#include "csccallplansqlmapper.h"

namespace libcsc {
namespace cscorder {
namespace repo {

CSCCallplanInsertSqlParameterBinder::CSCCallplanInsertSqlParameterBinder(domMod::ICSCCallplanPtr cscCallplan)
    : m_CSCCallplan(cscCallplan)
{
}

CSCCallplanInsertSqlParameterBinder::~CSCCallplanInsertSqlParameterBinder()
{
}

void CSCCallplanInsertSqlParameterBinder::bind(basar::db::sql::PreparedStatementRef preparedStatement) const
{
    CSCCallplanSqlMapper::bindInsertSQL(preparedStatement, m_CSCCallplan);
}

} // end namespace repo
} // end namespace cscorder
} // end namespace libcsc
