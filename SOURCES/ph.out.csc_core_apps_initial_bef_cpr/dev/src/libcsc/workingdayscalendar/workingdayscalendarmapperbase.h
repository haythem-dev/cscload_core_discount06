#ifndef GUARD_LIBCSC_WORKINGDAYSCALENDAR_WORKINGDAYSCALENDARMAPPERBASE_H
#define GUARD_LIBCSC_WORKINGDAYSCALENDAR_WORKINGDAYSCALENDARMAPPERBASE_H

#include "workingdayscalendarptr.h"
#include <libbasar_definitions.h>

namespace libcsc {
namespace workingdayscalendar {

	class WorkingdaysCalendarMapperBase
	{
	public:
		WorkingdaysCalendarMapperBase(WorkingdaysCalendarPtr);

		void map();

	protected:
		virtual ~WorkingdaysCalendarMapperBase();

		virtual void doMap() = 0;

		void setBranchNo(const basar::Int16& branchNo);
		void setCalendarDate(const basar::Int32& calendarDate);
		void setDayOfYear(const basar::Int16& dayOfYear);
		void setWeekOfYear(const basar::Int16& weekOfYear);
		void setWorkingdayOfMonth(const basar::Int16& workingdayOfMonth);
		void setWorkingdayOfYear(const basar::Int16& workingdayOfYear);
		void setWorkingdayOfWeek(const basar::Int16& workingdayOfWeek);
		void setDayType(const basar::VarString& dayType);

	private:
		WorkingdaysCalendarPtr	m_WorkingdaysCalendar;

	};

}
}

#endif // GUARD_LIBCSC_WORKINGDAYSCALENDAR_WORKINGDAYSCALENDARMAPPERBASE_H
