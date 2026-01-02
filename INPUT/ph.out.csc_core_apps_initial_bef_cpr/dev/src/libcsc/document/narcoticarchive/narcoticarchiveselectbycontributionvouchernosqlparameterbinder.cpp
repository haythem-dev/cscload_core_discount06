#include "narcoticarchiveselectbycontributionvouchernosqlparameterbinder.h"
#include "narcoticarchivesqlmapper.h"
#include <libbasar_definitions.h>

namespace libcsc {
	namespace document {

		NarcoticArchiveSelectByContributionVoucherNoSqlParameterBinder::NarcoticArchiveSelectByContributionVoucherNoSqlParameterBinder(const basar::Int16 branchNo, const basar::Int32 contributionVoucherNo) :
			m_BranchNo(branchNo), m_ContributionVoucherNo(contributionVoucherNo)
		{
		}

		NarcoticArchiveSelectByContributionVoucherNoSqlParameterBinder::~NarcoticArchiveSelectByContributionVoucherNoSqlParameterBinder()
		{
		}

		void NarcoticArchiveSelectByContributionVoucherNoSqlParameterBinder::bind(basar::db::sql::PreparedStatementRef preparedStatement) const
		{
			NarcoticArchiveSQLMapper::bindSelectByContributionVoucherNoSQL(preparedStatement, m_BranchNo, m_ContributionVoucherNo);
		}

	} // end namespace document
} // end namespace libcsc
