#include "narcoticarchiveinsertsqlparameterbinder.h"
#include "narcoticarchivesqlmapper.h"

namespace libcsc 
{
	namespace document 
	{
		NarcoticArchiveInsertSqlParameterBinder::NarcoticArchiveInsertSqlParameterBinder(const NarcoticArchivePtr narcoticArchivePtr) :
			m_NarcoticArchivePtr(narcoticArchivePtr)
		{
		}

		NarcoticArchiveInsertSqlParameterBinder::~NarcoticArchiveInsertSqlParameterBinder()
		{
		}

		void NarcoticArchiveInsertSqlParameterBinder::bind(basar::db::sql::PreparedStatementRef preparedStatement) const
		{
			NarcoticArchiveSQLMapper::bindInsertSQL(preparedStatement, m_NarcoticArchivePtr);
		}

	} // end namespace document
} // end namespace libcsc

