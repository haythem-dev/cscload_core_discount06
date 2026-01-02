#ifndef GUARD_LIBCSC_DOCUMENT_NARCOTICARCHIVESQLMAPPER_H
#define GUARD_LIBCSC_DOCUMENT_NARCOTICARCHIVESQLMAPPER_H

#include "narcoticarchivemapperbase.h"
#include <libbasardbsql_resultsetref.h>
#include <libbasardbsql_preparedstatementref.h>
#include <libbasarcmnutil_bstring.h>
#include <persistence/isqlparameterbinderptr.h>

namespace libcsc 
{
	namespace document 
	{

		class NarcoticArchiveSQLMapper : public NarcoticArchiveMapperBase
		{
		public:
			NarcoticArchiveSQLMapper(NarcoticArchivePtr narcoticArchivePtr, const basar::db::sql::ResultsetRef resultSet);
			NarcoticArchiveSQLMapper(NarcoticArchivePtr narcoticArchivePtr);
			virtual ~NarcoticArchiveSQLMapper();

			static const basar::VarString getSelectSQL(const basar::Int32 documentDate);
			static const basar::VarString getSelectByContributionVoucherNoSQL();
			static const basar::VarString getInsertSQL();
			static const basar::VarString getUpdateAcknowledgementStatusSQL(const NarcoticArchivePtr narcoticArchivePtr);

			static const libcsc::persistence::ISqlParameterBinderPtr getSelectSqlParameterBinder(const basar::Int16 branchNo, const basar::Int32 customerSupplierNo, const basar::Int32 transactionDate);
			static const libcsc::persistence::ISqlParameterBinderPtr getSelectByContributionVoucherNoSqlParameterBinder(const basar::Int16 branchNo, const basar::Int32 contributionVoucherNo);
			static const libcsc::persistence::ISqlParameterBinderPtr getInsertSqlParameterBinder(const NarcoticArchivePtr narcoticArchivePtr);

			static void bindSelectSQL(basar::db::sql::PreparedStatementRef prepStmt, const basar::Int16 branchNo, const basar::Int32 customerSupplierNo, basar::Int32 transactionDate);
			static void bindSelectByContributionVoucherNoSQL(basar::db::sql::PreparedStatementRef prepStmt, const basar::Int16 branchNo, const basar::Int32 contributionVoucherNo);
			static void bindInsertSQL(basar::db::sql::PreparedStatementRef prepStmt, const NarcoticArchivePtr narcoticArchivePtr);

		protected:
			virtual void doMap();

		private:
			NarcoticArchiveSQLMapper(const NarcoticArchiveSQLMapper&);
			NarcoticArchiveSQLMapper& operator=(const NarcoticArchiveSQLMapper&);

			const basar::db::sql::ResultsetRef		m_ResultSet;
		};

	} // end namespace document
} // end namespace libcsc

#endif // GUARD_LIBCSC_DOCUMENT_NARCOTICARCHIVESQLMAPPER_H
