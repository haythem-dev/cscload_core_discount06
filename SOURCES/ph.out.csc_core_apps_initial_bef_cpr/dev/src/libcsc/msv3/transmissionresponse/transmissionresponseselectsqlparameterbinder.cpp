#include "transmissionresponseselectsqlparameterbinder.h"
#include "transmissionresponsesqlmapper.h"

namespace libcsc {
namespace msv3 {

TransmissionResponseSelectSqlParameterBinder::TransmissionResponseSelectSqlParameterBinder(const basar::VarString& transmissionUuid) :
	m_TransmissionUuid(transmissionUuid)
{
}

TransmissionResponseSelectSqlParameterBinder::~TransmissionResponseSelectSqlParameterBinder()
{
}

void TransmissionResponseSelectSqlParameterBinder::bind(basar::db::sql::PreparedStatementRef preparedStatement) const
{
	TransmissionResponseSQLMapper::bindSelectSQL(preparedStatement, m_TransmissionUuid);
}

} // end namespace msv3
} // end namespace libcsc
