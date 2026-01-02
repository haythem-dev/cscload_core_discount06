#ifndef GUARD_LIBCSC_WORKINGDAYSCALENDARREPOSITORY_H
#define GUARD_LIBCSC_WORKINGDAYSCALENDARREPOSITORY_H

#include "iworkingdayscalendarrepository.h"
#include <persistence/iaccessorptr.h>
#include <libbasar_definitions.h>
#include <workingdayscalendar/workingdayscalendarptr.h>

namespace basar {
	namespace db {
		namespace sql {
			class ResultsetRef;
		}
	}
}

namespace libcsc {
namespace workingdayscalendar {

	class WorkingdaysCalendarRepository : public IWorkingdaysCalendarRepository
	{
	public:
		WorkingdaysCalendarRepository();
		virtual ~WorkingdaysCalendarRepository();

		virtual void injectWorkingdaysCalendarAccessor(persistence::IAccessorPtr accessor);

		virtual WorkingdaysCalendarPtr findWorkingdaysCalendar(const basar::Int16& branchNo, const basar::Int32& calendarDate) const;
		virtual basar::Int32           getWorkingdaysCalendarDifferenceBetween(const basar::Int16& branchNo, const basar::Int32& calendarDateFrom, const basar::Int32& calendarDateTo) const;

	private:
		persistence::IAccessorPtr m_SelectWorkingdaysCalendarAccessor;

	};

} // end namespace workingdayscalendar
} // end namespace libcsc

#endif // GUARD_LIBCSC_WORKINGDAYSCALENDARREPOSITORY_H
