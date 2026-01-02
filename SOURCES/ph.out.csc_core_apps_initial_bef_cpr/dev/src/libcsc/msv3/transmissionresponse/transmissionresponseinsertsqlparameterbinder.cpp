#include "transmissionresponseinsertsqlparameterbinder.h"
#include "transmissionresponsesqlmapper.h"

namespace libcsc {
namespace msv3 {

TransmissionResponseInsertSqlParameterBinder::TransmissionResponseInsertSqlParameterBinder(const TransmissionResponsePtr transmissionResponse) :
	m_TransmissionResponse(transmissionResponse)
{
}

TransmissionResponseInsertSqlParameterBinder::~TransmissionResponseInsertSqlParameterBinder()
{
}

void TransmissionResponseInsertSqlParameterBinder::bind( basar::db::sql::PreparedStatementRef preparedStatement ) const
{
	TransmissionResponseSQLMapper::bindInsertSQL( preparedStatement, m_TransmissionResponse );
}

} // end namespace msv3
} // end namespace libcsc

