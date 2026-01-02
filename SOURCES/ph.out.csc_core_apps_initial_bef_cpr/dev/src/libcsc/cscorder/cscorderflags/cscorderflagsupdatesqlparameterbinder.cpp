#include "cscorderflagsupdatesqlparameterbinder.h"
#include "cscorderflagssqlmapper.h"

namespace libcsc {
namespace cscorder {
namespace repo {

CSCOrderFlagsUpdateSqlParameterBinder::CSCOrderFlagsUpdateSqlParameterBinder(domMod::ICSCOrderFlagsPtr cscOrderFlags)
    : m_CSCOrderFlags(cscOrderFlags)
{
}

CSCOrderFlagsUpdateSqlParameterBinder::~CSCOrderFlagsUpdateSqlParameterBinder()
{
}

void CSCOrderFlagsUpdateSqlParameterBinder::bind(basar::db::sql::PreparedStatementRef preparedStatement) const
{	    
	CSCOrderFlagsSqlMapper::bindUpdateSQL(preparedStatement, m_CSCOrderFlags);
}

} // end namespace repo
} // end namespace cscorder
} // end namespace libcsc
