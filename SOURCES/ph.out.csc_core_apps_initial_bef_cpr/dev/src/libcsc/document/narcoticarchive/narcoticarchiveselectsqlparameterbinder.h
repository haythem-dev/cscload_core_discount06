#ifndef GUARD_LIBCSC_DOCUMENT_NARCOTICARCHIVE_SELECT_SQL_PARAMETER_BINDER_H
#define GUARD_LIBCSC_DOCUMENT_NARCOTICARCHIVE_SELECT_SQL_PARAMETER_BINDER_H

#include <persistence/isqlparameterbinder.h>
#include <libbasarcmnutil_bstring.h>
#include <types/documenttypeenum.inc>

namespace libcsc 
{
	namespace document 
	{
		class NarcoticArchiveSelectSqlParameterBinder : public libcsc::persistence::ISqlParameterBinder
		{
		public:
			NarcoticArchiveSelectSqlParameterBinder(const basar::Int16 branchNo, const basar::Int32 customerSupplierNo, const basar::Int32 transactionDate);

			virtual ~NarcoticArchiveSelectSqlParameterBinder();

			virtual void bind(basar::db::sql::PreparedStatementRef preparedStatement) const;

		private:

			basar::Int16		m_BranchNo;
			basar::Int32		m_CustomerSupplierNo;
			basar::Int32		m_TransactionDate;
		};

	} // end namespace document
} // end namespace libcsc

#endif // GUARD_LIBCSC_DOCUMENT_NARCOTICARCHIVE_SELECT_SQL_PARAMETER_BINDER_H

