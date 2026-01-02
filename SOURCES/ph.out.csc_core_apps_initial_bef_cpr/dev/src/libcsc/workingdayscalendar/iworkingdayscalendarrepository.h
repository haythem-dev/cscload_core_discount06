#ifndef GUARD_LIBCSC_IWORKINGDAYSCALENDARREPOSITORY_H
#define GUARD_LIBCSC_IWORKINGDAYSCALENDARREPOSITORY_H

#include <libbasar_definitions.h>
#include <workingdayscalendar/workingdayscalendarptr.h>

namespace libcsc {
namespace workingdayscalendar {

	class IWorkingdaysCalendarRepository
	{
	public:
		virtual ~IWorkingdaysCalendarRepository() {}

		virtual WorkingdaysCalendarPtr findWorkingdaysCalendar(const basar::Int16& branchNo, const basar::Int32& calendarDate) const = 0;
		virtual basar::Int32           getWorkingdaysCalendarDifferenceBetween(const basar::Int16& branchNo, const basar::Int32& calendarDateFrom, const basar::Int32& calendarDateTo) const = 0;
	};

} // end namespace workingdayscalendar
} // end namespace libcsc

#endif // GUARD_LIBCSC_IWORKINGDAYSCALENDARREPOSITORY_H
