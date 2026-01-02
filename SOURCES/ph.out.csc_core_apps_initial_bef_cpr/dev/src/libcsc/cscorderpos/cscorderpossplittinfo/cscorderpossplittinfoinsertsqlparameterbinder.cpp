#include "cscorderpossplittinfoinsertsqlparameterbinder.h"
#include "cscorderpossplittinfosqlmapper.h"

namespace libcsc {
namespace cscorderpos {
namespace repo {

CSCOrderposSplittinfoInsertSqlParameterBinder::CSCOrderposSplittinfoInsertSqlParameterBinder(
    domMod::ICSCOrderposSplittinfoPtr splittinfo)
: m_Splittinfo(splittinfo)
{
}

CSCOrderposSplittinfoInsertSqlParameterBinder::~CSCOrderposSplittinfoInsertSqlParameterBinder()
{
}

void CSCOrderposSplittinfoInsertSqlParameterBinder::bind(basar::db::sql::PreparedStatementRef preparedStatement) const
{
    CSCOrderposSplittinfoSqlMapper::bindInsertSQL(preparedStatement, m_Splittinfo);
}

} // end namespace repo
} // end namespace cscorderpos
} // end namespace libcsc
