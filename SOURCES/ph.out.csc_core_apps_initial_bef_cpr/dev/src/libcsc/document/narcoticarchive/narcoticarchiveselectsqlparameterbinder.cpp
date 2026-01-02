#include "narcoticarchiveselectsqlparameterbinder.h"
#include "narcoticarchivesqlmapper.h"

namespace libcsc 
{
	namespace document 
	{
		NarcoticArchiveSelectSqlParameterBinder::NarcoticArchiveSelectSqlParameterBinder(const basar::Int16 branchNo, const basar::Int32 customerSupplierNo, const basar::Int32 transactionDate) :
			m_BranchNo(branchNo), m_CustomerSupplierNo(customerSupplierNo), m_TransactionDate(transactionDate)
		{
		}

		NarcoticArchiveSelectSqlParameterBinder::~NarcoticArchiveSelectSqlParameterBinder()
		{
		}

		void NarcoticArchiveSelectSqlParameterBinder::bind(basar::db::sql::PreparedStatementRef preparedStatement) const
		{
			NarcoticArchiveSQLMapper::bindSelectSQL(preparedStatement, m_BranchNo, m_CustomerSupplierNo, m_TransactionDate);
		}

	} // end namespace document
} // end namespace libcsc
