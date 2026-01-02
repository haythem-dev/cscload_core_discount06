#ifndef GUARD_LIBCSC_RETURNS_RETURNANNOUNCEMENTPTR_H
#define GUARD_LIBCSC_RETURNS_RETURNANNOUNCEMENTPTR_H

#include <boost/shared_ptr.hpp>
#include <list>

namespace libcsc {
namespace returns {

	class ReturnAnnouncement;

	typedef boost::shared_ptr<ReturnAnnouncement> ReturnAnnouncementPtr;

	typedef std::list<ReturnAnnouncementPtr> ReturnAnnouncementCollection;

	typedef boost::shared_ptr<ReturnAnnouncementCollection> ReturnAnnouncementCollectionPtr;

} // namespace returns
} // namespace libcsc

#endif // GUARD_LIBCSC_RETURNS_RETURNANNOUNCEMENTPTR_H
