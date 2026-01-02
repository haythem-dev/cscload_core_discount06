#ifndef GUARD_LIBCSC_DOCUMENT_NARCOTICARCHIVE_SELECT_BY_CONTRIBUTIONVOUCHERNO_SQL_PARAMETER_BINDER_H
#define GUARD_LIBCSC_DOCUMENT_NARCOTICARCHIVE_SELECT_BY_CONTRIBUTIONVOUCHERNO_SQL_PARAMETER_BINDER_H

#include <persistence/isqlparameterbinder.h>
#include <libbasarcmnutil_bstring.h>

namespace libcsc 
{
	namespace document 
	{
		class NarcoticArchiveSelectByContributionVoucherNoSqlParameterBinder : public libcsc::persistence::ISqlParameterBinder
		{
		public:
			NarcoticArchiveSelectByContributionVoucherNoSqlParameterBinder(const basar::Int16 branchNo, const basar::Int32 contributionVoucherNo);

			virtual ~NarcoticArchiveSelectByContributionVoucherNoSqlParameterBinder();

			virtual void bind(basar::db::sql::PreparedStatementRef preparedStatement) const;

		private:
			basar::Int16		m_BranchNo;
			basar::Int32		m_ContributionVoucherNo;
		};

	} // end namespace document
} // end namespace libcsc

#endif // GUARD_LIBCSC_DOCUMENT_NARCOTICARCHIVE_SELECT_BY_CONTRIBUTIONVOUCHERNO_SQL_PARAMETER_BINDER_H

