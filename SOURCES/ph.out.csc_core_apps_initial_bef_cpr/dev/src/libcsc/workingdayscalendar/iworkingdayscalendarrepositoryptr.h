#ifndef GUARD_LIBCSC_IWORKINGDAYSCALENDARREPOSITORYPTR_H
#define GUARD_LIBCSC_IWORKINGDAYSCALENDARREPOSITORYPTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc {
namespace workingdayscalendar {

	class IWorkingdaysCalendarRepository;
	typedef boost::shared_ptr<IWorkingdaysCalendarRepository> IWorkingdaysCalendarRepositoryPtr;

} // end namespace workingdayscalendar
} // end namespace libcsc

#endif // GUARD_LIBCSC_IWORKINGDAYSCALENDARREPOSITORYPTR_H
