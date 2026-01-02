#ifndef GUARD_LIBCSC_WORKINGDAYSCALENDARPTR_H
#define GUARD_LIBCSC_WORKINGDAYSCALENDARPTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc {
namespace workingdayscalendar {

	class WorkingdaysCalendar;
	typedef boost::shared_ptr<WorkingdaysCalendar> WorkingdaysCalendarPtr;

} // end namespace workingdayscalendar
} // end namespace libcsc

#endif // GUARD_LIBCSC_WORKINGDAYSCALENDARPTR_H
