#ifndef GUARD_LIBCSC_BLOCKEDARTICLES_BLOCKEDARTICLESSQLMAPPER_H
#define GUARD_LIBCSC_BLOCKEDARTICLES_BLOCKEDARTICLESSQLMAPPER_H

#include "blockedarticlesmapperbase.h"
#include <libbasardbsql_resultsetref.h>
#include <libbasarcmnutil_bstring.h>

#include "blockedarticlesptr.h"

namespace libcsc {
namespace blockedarticles {

	class BlockedArticlesSqlMapper : public BlockedArticlesMapperBase
	{
	public:
		BlockedArticlesSqlMapper(BlockedArticlesPtr blockedArticles, const basar::db::sql::ResultsetRef resultSet);
		BlockedArticlesSqlMapper(BlockedArticlesPtr blockedArticles);
		virtual ~BlockedArticlesSqlMapper();

		static const basar::VarString getSelectSQL(const basar::VarString& dbName, const basar::Int16 branchNo, const basar::Int32 blockID);
		static const basar::VarString getUpdateSQL(const basar::VarString& dbName, const BlockedArticlesPtr& blockedArticles);

	protected:
		virtual void doMap();


	private:
		BlockedArticlesSqlMapper(const BlockedArticlesSqlMapper&);
		BlockedArticlesSqlMapper& operator=(const BlockedArticlesSqlMapper&);

		const basar::db::sql::ResultsetRef m_ResultSet;
	};

} // namespace blockedarticles
} // namespace libcsc

#endif // !GUARD_LIBCSC_BLOCKEDARTICLES_BLOCKEDARTICLESSQLMAPPER_H
