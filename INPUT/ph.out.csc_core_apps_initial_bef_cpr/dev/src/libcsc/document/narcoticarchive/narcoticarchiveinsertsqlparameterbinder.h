#ifndef GUARD_LIBCSC_DOCUMENT_NARCOTICARCHIVE_INSERT_SQL_PARAMETER_BINDER_H
#define GUARD_LIBCSC_DOCUMENT_NARCOTICARCHIVE_INSERT_SQL_PARAMETER_BINDER_H

#include <persistence/isqlparameterbinder.h>
#include "narcoticarchiveptr.h"

namespace libcsc 
{
	namespace document 
	{

		class NarcoticArchiveInsertSqlParameterBinder : public libcsc::persistence::ISqlParameterBinder
		{
		public:
			NarcoticArchiveInsertSqlParameterBinder(const NarcoticArchivePtr documentArchiveInfo);
			virtual ~NarcoticArchiveInsertSqlParameterBinder();

			virtual void bind(basar::db::sql::PreparedStatementRef preparedStatement) const;

		private:
			NarcoticArchivePtr	m_NarcoticArchivePtr;
		};

	} // end namespace document
} // end namespace libcsc

#endif // GUARD_LIBCSC_DOCUMENT_NARCOTICARCHIVE_INSERT_SQL_PARAMETER_BINDER_H
