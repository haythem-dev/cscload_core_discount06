#include "workingdayscalendar.h"

namespace libcsc {
namespace workingdayscalendar {

	WorkingdaysCalendar::WorkingdaysCalendar()
	{

	}

	WorkingdaysCalendar::~WorkingdaysCalendar()
	{

	}

	const libcsc::Int16& WorkingdaysCalendar::getBranchNo() const
	{
		return m_BranchNo;
	}

	const libcsc::Int32& WorkingdaysCalendar::getCalendarDate() const
	{
		return m_CalendarDate;
	}

	const libcsc::Int16& WorkingdaysCalendar::getDayOfYear() const
	{
		return m_DayOfYear;
	}

	const libcsc::Int16& WorkingdaysCalendar::getWeekOfYear() const
	{
		return m_WeekOfYear;
	}

	const libcsc::Int16& WorkingdaysCalendar::getWorkingDayOfMonth() const
	{
		return m_WorkingDayOfMonth;
	}

	const libcsc::Int16& WorkingdaysCalendar::getWorkingDayOfYear() const
	{
		return m_WorkingDayOfYear;
	}

	const libcsc::Int16& WorkingdaysCalendar::getWorkingDayOfWeek() const
	{
		return m_WorkingDayOfWeek;
	}

	const libcsc::VarString& WorkingdaysCalendar::getDayType() const
	{
		return m_DayType;
	}

} // end namespace workingdayscalendar
} // end namespace libcsc
