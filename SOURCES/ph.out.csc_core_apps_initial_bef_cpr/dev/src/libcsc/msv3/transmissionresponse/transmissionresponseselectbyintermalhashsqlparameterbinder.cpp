#include "transmissionresponseselectbyintermalhashsqlparameterbinder.h"
#include "transmissionresponsesqlmapper.h"

namespace libcsc {
namespace msv3 {

TransmissionResponseSelectByInternalHashSqlParameterBinder::TransmissionResponseSelectByInternalHashSqlParameterBinder(
	const basar::Int16& branchNo,
	const basar::Int32& customerNo,
	const basar::VarString& internalHash,
	const basar::DateTime& checkFrom) :
	m_BranchNo(branchNo),
	m_CustomerNo(customerNo),
	m_InternalHash(internalHash),
	m_CheckFrom(checkFrom)
{
}

TransmissionResponseSelectByInternalHashSqlParameterBinder::~TransmissionResponseSelectByInternalHashSqlParameterBinder()
{
}

void TransmissionResponseSelectByInternalHashSqlParameterBinder::bind(basar::db::sql::PreparedStatementRef preparedStatement) const
{
	TransmissionResponseSQLMapper::bindSelectByInternalHashSQL(preparedStatement, m_BranchNo, m_CustomerNo, m_InternalHash, m_CheckFrom);
}

} // end namespace msv3
} // end namespace libcsc
