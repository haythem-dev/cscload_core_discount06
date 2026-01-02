#ifndef GUARD_LIBCSC_RETURNS_RETURNANNOUNCEMENTPOSPTR_H
#define GUARD_LIBCSC_RETURNS_RETURNANNOUNCEMENTPOSPTR_H

#include <boost/shared_ptr.hpp>
#include <list>

namespace libcsc {
namespace returns {

	class ReturnAnnouncementPos;

	typedef boost::shared_ptr<ReturnAnnouncementPos> ReturnAnnouncementPosPtr;

	typedef std::list<ReturnAnnouncementPosPtr> ReturnAnnouncementPosCollection;

	typedef boost::shared_ptr<ReturnAnnouncementPosCollection> ReturnAnnouncementPosCollectionPtr;

} // namespace returns
} // namespace libcsc

#endif // GUARD_LIBCSC_RETURNS_RETURNANNOUNCEMENTPOSPTR_H
