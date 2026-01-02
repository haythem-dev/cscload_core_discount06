#ifndef GUARD_LIBCSC_WORKINGDAYSCALENDARREPOSITORYPTR_H
#define GUARD_LIBCSC_WORKINGDAYSCALENDARREPOSITORYPTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc {
namespace workingdayscalendar {

	class WorkingdaysCalendarRepository;
	typedef boost::shared_ptr<WorkingdaysCalendarRepository> WorkingdaysCalendarRepositoryPtr;

} // end namespace workingdayscalendar
} // end namespace libcsc

#endif // GUARD_LIBCSC_WORKINGDAYSCALENDARREPOSITORYPTR_H
