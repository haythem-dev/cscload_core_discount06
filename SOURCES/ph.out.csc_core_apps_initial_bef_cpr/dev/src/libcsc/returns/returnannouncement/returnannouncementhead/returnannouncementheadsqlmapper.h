#ifndef GUARD_LIBCSC_RETURNS_RETURNANNOUNCEMENTHEADSQLMAPPER_H
#define GUARD_LIBCSC_RETURNS_RETURNANNOUNCEMENTHEADSQLMAPPER_H

#include "returnannouncementheadmapperbase.h"
#include <libbasardbsql_resultsetref.h>
#include <libbasarcmnutil_bstring.h>

namespace libcsc {
namespace returns {

	class ReturnAnnouncementHeadSqlMapper : public ReturnAnnouncementHeadMapperBase
	{

	public:
		ReturnAnnouncementHeadSqlMapper(ReturnAnnouncementHeadPtr returnAnnouncementHead, const basar::db::sql::ResultsetRef resultSet);
		ReturnAnnouncementHeadSqlMapper(ReturnAnnouncementHeadPtr returnAnnouncementHead);
		virtual ~ReturnAnnouncementHeadSqlMapper();

		static const basar::VarString getSelectSQL(const basar::Int32 announcementId);
		static const basar::VarString getInsertSQL(const ReturnAnnouncementHeadPtr& head);
		static const basar::VarString getUpdateSQL(const ReturnAnnouncementHeadPtr& head);

	protected:
		virtual void doMap();
		virtual void doMapSerial(const basar::Int32 id);

	private:
		ReturnAnnouncementHeadSqlMapper(const ReturnAnnouncementHeadSqlMapper&);
		ReturnAnnouncementHeadSqlMapper& operator=(const ReturnAnnouncementHeadSqlMapper&);

		const basar::db::sql::ResultsetRef		m_ResultSet;
	};

} //returns
} //libcsc

#endif // !GUARD_LIBCSC_RETURNS_RETURNANNOUNCEMENTHEADSQLMAPPER_H
