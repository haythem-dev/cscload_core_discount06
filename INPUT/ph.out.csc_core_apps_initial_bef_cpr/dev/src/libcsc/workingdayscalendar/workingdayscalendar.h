#ifndef GUARD_LIBCSC_WORKINGDAYSCALENDAR_H
#define GUARD_LIBCSC_WORKINGDAYSCALENDAR_H

#include <datatypes/int32.h>
#include <datatypes/int16.h>
#include <datatypes/varstring.h>

namespace libcsc {
namespace workingdayscalendar {

	class WorkingdaysCalendar
	{
		friend class WorkingdaysCalendarMapperBase;

	public:
		WorkingdaysCalendar();
		virtual ~WorkingdaysCalendar();

		const libcsc::Int16&		getBranchNo() const;
		const libcsc::Int32&		getCalendarDate() const;
		const libcsc::Int16&		getDayOfYear() const;
		const libcsc::Int16&		getWeekOfYear() const;
		const libcsc::Int16&		getWorkingDayOfMonth() const;
		const libcsc::Int16&		getWorkingDayOfYear() const;
		const libcsc::Int16&		getWorkingDayOfWeek() const;
		const libcsc::VarString&	getDayType() const;

	private:
		libcsc::Int16		m_BranchNo;
		libcsc::Int32		m_CalendarDate;
		libcsc::Int16		m_DayOfYear;
		libcsc::Int16		m_WeekOfYear;
		libcsc::Int16		m_WorkingDayOfMonth;
		libcsc::Int16		m_WorkingDayOfYear;
		libcsc::Int16		m_WorkingDayOfWeek;
		libcsc::VarString	m_DayType;

	};

} // end namespace workingdayscalendar
} // end namespace libcsc

#endif // GUARD_LIBCSC_WORKINGDAYSCALENDAR_H
