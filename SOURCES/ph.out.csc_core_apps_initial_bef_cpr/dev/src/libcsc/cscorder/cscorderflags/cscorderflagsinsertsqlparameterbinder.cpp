#include "cscorderflagsinsertsqlparameterbinder.h"
#include "cscorderflagssqlmapper.h"

namespace libcsc {
namespace cscorder {
namespace repo {

CSCOrderFlagsInsertSqlParameterBinder::CSCOrderFlagsInsertSqlParameterBinder(domMod::ICSCOrderFlagsPtr cscOrderFlags)
    : m_CSCOrderFlags(cscOrderFlags)
{
}

CSCOrderFlagsInsertSqlParameterBinder::~CSCOrderFlagsInsertSqlParameterBinder()
{
}

void CSCOrderFlagsInsertSqlParameterBinder::bind(basar::db::sql::PreparedStatementRef preparedStatement) const
{
	CSCOrderFlagsSqlMapper::bindInsertSQL( preparedStatement, m_CSCOrderFlags );    
}

} // end namespace repo
} // end namespace cscorder
} // end namespace libcsc
