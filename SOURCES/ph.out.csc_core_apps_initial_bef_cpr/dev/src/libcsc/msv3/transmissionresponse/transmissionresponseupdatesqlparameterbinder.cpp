#include "transmissionresponseupdatesqlparameterbinder.h"
#include "transmissionresponsesqlmapper.h"

namespace libcsc {
namespace msv3 {

TransmissionResponseUpdateSqlParameterBinder::TransmissionResponseUpdateSqlParameterBinder(const TransmissionResponsePtr transmissionResponse) :
	m_TransmissionResponse(transmissionResponse)
{
}

TransmissionResponseUpdateSqlParameterBinder::~TransmissionResponseUpdateSqlParameterBinder()
{
}

void TransmissionResponseUpdateSqlParameterBinder::bind( basar::db::sql::PreparedStatementRef preparedStatement ) const
{
	TransmissionResponseSQLMapper::bindUpdateSQL( preparedStatement, m_TransmissionResponse );
}

} // end namespace msv3
} // end namespace libcsc

