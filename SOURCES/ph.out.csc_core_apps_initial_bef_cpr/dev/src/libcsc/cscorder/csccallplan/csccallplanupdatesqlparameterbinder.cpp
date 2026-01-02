#include "csccallplanupdatesqlparameterbinder.h"
#include "csccallplansqlmapper.h"

namespace libcsc {
namespace cscorder {
namespace repo {

CSCCallplanUpdateSqlParameterBinder::CSCCallplanUpdateSqlParameterBinder(domMod::ICSCCallplanPtr cscCallplan)
    : m_CSCCallplan(cscCallplan)
{
}

CSCCallplanUpdateSqlParameterBinder::~CSCCallplanUpdateSqlParameterBinder()
{
}

void CSCCallplanUpdateSqlParameterBinder::bind(basar::db::sql::PreparedStatementRef preparedStatement) const
{
    CSCCallplanSqlMapper::bindUpdateSQL(preparedStatement, m_CSCCallplan);
}

} // end namespace repo
} // end namespace cscorder
} // end namespace libcsc
