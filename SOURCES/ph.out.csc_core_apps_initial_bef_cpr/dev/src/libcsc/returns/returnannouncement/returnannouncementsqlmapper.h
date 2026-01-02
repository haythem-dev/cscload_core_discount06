#ifndef GUARD_LIBCSC_RETURNS_RETURNANNOUNCEMENTSQLMAPPER_H
#define GUARD_LIBCSC_RETURNS_RETURNANNOUNCEMENTSQLMAPPER_H

#include "returnannouncementmapperbase.h"
#include <libbasardbsql_resultsetref.h>
#include <libbasarcmnutil_bstring.h>

namespace libcsc {
namespace returns {

	class ReturnAnnouncementSqlMapper : public ReturnAnnouncementMapperBase
	{
	public:
		ReturnAnnouncementSqlMapper(ReturnAnnouncementPtr returnAnnouncement, const basar::db::sql::ResultsetRef resultSet);
		ReturnAnnouncementSqlMapper(ReturnAnnouncementPtr returnAnnouncement);
		virtual ~ReturnAnnouncementSqlMapper();

		static const basar::VarString getSelectSQL(const basar::Int32 announcementId);
		static const basar::VarString getInsertSQL(const ReturnAnnouncementPtr& returnAnnouncement);

	protected:
		virtual void doMap();
		virtual void doMapSerial(const basar::Int32 id);


	private:
		ReturnAnnouncementSqlMapper(const ReturnAnnouncementSqlMapper&);
		ReturnAnnouncementSqlMapper& operator=(const ReturnAnnouncementSqlMapper&);

		const basar::db::sql::ResultsetRef		m_ResultSet;
	};

} // namespace returns
} // namespace libcsc

#endif // !GUARD_LIBCSC_RETURNS_RETURNANNOUNCEMENTSQLMAPPER_H
