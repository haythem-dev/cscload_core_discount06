#include "workingdayscalendarmapperbase.h"
#include <workingdayscalendar/workingdayscalendar.h>


namespace libcsc {
namespace workingdayscalendar {

	WorkingdaysCalendarMapperBase::WorkingdaysCalendarMapperBase(WorkingdaysCalendarPtr workingdaysCalendar)
		: m_WorkingdaysCalendar(workingdaysCalendar)
	{

	}

	WorkingdaysCalendarMapperBase::~WorkingdaysCalendarMapperBase()
	{

	}

	void WorkingdaysCalendarMapperBase::map()
	{
		doMap();
	}

	void WorkingdaysCalendarMapperBase::setBranchNo(const basar::Int16& branchNo)
	{
		m_WorkingdaysCalendar->m_BranchNo = branchNo;
		m_WorkingdaysCalendar->m_BranchNo.setClean();
	}

	void WorkingdaysCalendarMapperBase::setCalendarDate(const basar::Int32& calendarDate)
	{
		m_WorkingdaysCalendar->m_CalendarDate = calendarDate;
		m_WorkingdaysCalendar->m_CalendarDate.setClean();
	}

	void WorkingdaysCalendarMapperBase::setDayOfYear(const basar::Int16& dayOfYear)
	{
		m_WorkingdaysCalendar->m_DayOfYear = dayOfYear;
		m_WorkingdaysCalendar->m_DayOfYear.setClean();
	}

	void WorkingdaysCalendarMapperBase::setWeekOfYear(const basar::Int16& weekOfYear)
	{
		m_WorkingdaysCalendar->m_WeekOfYear = weekOfYear;
		m_WorkingdaysCalendar->m_WeekOfYear.setClean();
	}

	void WorkingdaysCalendarMapperBase::setWorkingdayOfMonth(const basar::Int16& workingdayOfMonth)
	{
		m_WorkingdaysCalendar->m_WorkingDayOfMonth = workingdayOfMonth;
		m_WorkingdaysCalendar->m_WorkingDayOfMonth.setClean();
	}

	void WorkingdaysCalendarMapperBase::setWorkingdayOfYear(const basar::Int16& workingdayOfYear)
	{
		m_WorkingdaysCalendar->m_WorkingDayOfYear = workingdayOfYear;
		m_WorkingdaysCalendar->m_WorkingDayOfYear.setClean();
	}

	void WorkingdaysCalendarMapperBase::setWorkingdayOfWeek(const basar::Int16& workingdayOfWeek)
	{
		m_WorkingdaysCalendar->m_WorkingDayOfWeek = workingdayOfWeek;
		m_WorkingdaysCalendar->m_WorkingDayOfWeek.setClean();
	}

	void WorkingdaysCalendarMapperBase::setDayType(const basar::VarString& dayType)
	{
		m_WorkingdaysCalendar->m_DayType = dayType;
		m_WorkingdaysCalendar->m_DayType.setClean();
	}

} // end namespace workingdayscalendar
} // end namespace libcsc
