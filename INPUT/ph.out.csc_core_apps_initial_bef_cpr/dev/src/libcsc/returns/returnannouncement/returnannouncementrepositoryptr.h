#ifndef GUARD_LIBCSC_RETURNS_RETURNANNOUNCEMENTREPOSITORYPTR_H
#define GUARD_LIBCSC_RETURNS_RETURNANNOUNCEMENTREPOSITORYPTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc {
namespace returns {

	class ReturnAnnouncementRepository;
	typedef boost::shared_ptr<ReturnAnnouncementRepository> ReturnAnnouncementRepositoryPtr;

} // namespace returns
} // namespace libcsc

#endif // GUARD_LIBCSC_RETURNS_RETURNANNOUNCEMENTREPOSITORYPTR_H
