#include "cscorderibtpickingdatainsertsqlparameterbinder.h"
#include "cscorderibtpickingdatasqlmapper.h"

namespace libcsc {
namespace cscorder {
namespace repo {

CSCOrderIBTPickingdataInsertSqlParameterBinder::CSCOrderIBTPickingdataInsertSqlParameterBinder(
    domMod::ICSCOrderIBTPickingdataPtr pickingdata)
: m_Pickingdata(pickingdata)
{
}

CSCOrderIBTPickingdataInsertSqlParameterBinder::~CSCOrderIBTPickingdataInsertSqlParameterBinder()
{
}

void CSCOrderIBTPickingdataInsertSqlParameterBinder::bind(basar::db::sql::PreparedStatementRef preparedStatement) const
{
    CSCOrderIBTPickingdataSqlMapper::bindInsertSQL(preparedStatement, m_Pickingdata);
}

} // end namespace repo
} // end namespace cscorder
} // end namespace libcsc
