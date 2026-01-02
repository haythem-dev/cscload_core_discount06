#ifndef GUARD_LIBCSC_RETURNS_RETURNANNOUNCEMENTPOSSQLMAPPER_H
#define GUARD_LIBCSC_RETURNS_RETURNANNOUNCEMENTPOSSQLMAPPER_H

#include "returnannouncementposmapperbase.h"
#include <libbasardbsql_resultsetref.h>
#include <libbasarcmnutil_bstring.h>

namespace libcsc {
namespace returns {

	class ReturnAnnouncementPosSQLMapper : public ReturnAnnouncementPosMapperBase
	{
	public:
		ReturnAnnouncementPosSQLMapper(ReturnAnnouncementPosPtr returnannouncementPos, const basar::db::sql::ResultsetRef resultSet);
		virtual ~ReturnAnnouncementPosSQLMapper();

		static const basar::VarString getSelectSQL(const basar::Int32 announcementHeadId);
		static const basar::VarString getInsertSQL(const ReturnAnnouncementPosPtr& position);

	protected:
		virtual void doMap();

	private:
		ReturnAnnouncementPosSQLMapper(const ReturnAnnouncementPosSQLMapper&);
		ReturnAnnouncementPosSQLMapper& operator=(const ReturnAnnouncementPosSQLMapper&);

		const basar::db::sql::ResultsetRef		m_ResultSet;
	};

} // returns
} // libcsc

#endif // !GUARD_LIBCSC_RETURNS_RETURNANNOUNCEMENTPOSSQLMAPPER_H
