#ifndef GUARD_LIBCSC_RETURNS_RETURNANNOUNCEMENTHEADPTR_H
#define GUARD_LIBCSC_RETURNS_RETURNANNOUNCEMENTHEADPTR_H

#include <boost/shared_ptr.hpp>
#include <list>

namespace libcsc {
namespace returns {

	class ReturnAnnouncementHead;

	typedef boost::shared_ptr<ReturnAnnouncementHead> ReturnAnnouncementHeadPtr;

	typedef std::list<ReturnAnnouncementHeadPtr> ReturnAnnouncementHeadCollection;

	typedef boost::shared_ptr<ReturnAnnouncementHeadCollection> ReturnAnnouncementHeadCollectionPtr;

} // namespace returns
} // namespace libcsc

#endif // GUARD_LIBCSC_RETURNS_RETURNANNOUNCEMENTHEADPTR_H
