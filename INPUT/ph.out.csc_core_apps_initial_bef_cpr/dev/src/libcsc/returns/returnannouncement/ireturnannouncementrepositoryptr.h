#ifndef GUARD_LIBCSC_RETURNS_IRETURNANNOUNCEMENTPTR_H
#define GUARD_LIBCSC_RETURNS_IRETURNANNOUNCEMENTPTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc {
namespace returns {

	class IReturnAnnouncementRepository;

	typedef boost::shared_ptr<IReturnAnnouncementRepository> IReturnAnnouncementRepositoryPtr;

} // namespace returns
} // namespace libcsc

#endif // GUARD_LIBCSC_RETURNS_RETURNANNOUNCEMENTPTR_H
