#ifndef GUARD_LIBCSC_WORKINGDAYSCALENDAR_WORKINGDAYSCALENDARSQLMAPPER_H
#define GUARD_LIBCSC_WORKINGDAYSCALENDAR_WORKINGDAYSCALENDARSQLMAPPER_H

#include "workingdayscalendarmapperbase.h"
#include <workingdayscalendar/workingdayscalendarptr.h>
#include <libbasardbsql_resultsetref.h>

namespace libcsc {
namespace workingdayscalendar {

	class WorkingdaysCalendarSQLMapper : public WorkingdaysCalendarMapperBase
	{
	public:
		WorkingdaysCalendarSQLMapper(WorkingdaysCalendarPtr workingdaysCalendar, const basar::db::sql::ResultsetRef resultSet);
		virtual ~WorkingdaysCalendarSQLMapper();

		static const basar::VarString getSelectSQL(const basar::Int16& branchNo, const basar::Int32& calendarDate);
		static const basar::VarString getSelectBetweenSQL(const basar::Int16& branchNo, const basar::Int32& calendarDateFrom, const basar::Int32& calendarDateTo);

	protected:
		virtual void doMap();

	private:
		WorkingdaysCalendarSQLMapper(const WorkingdaysCalendarSQLMapper&);
		WorkingdaysCalendarSQLMapper& operator=(const WorkingdaysCalendarSQLMapper&);

		const basar::db::sql::ResultsetRef m_ResultSet;

	};

}
}

#endif // GUARD_LIBCSC_WORKINGDAYSCALENDAR_WORKINGDAYSCALENDARSQLMAPPER_H
