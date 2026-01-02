#ifndef GUARD_LIBCSC_RETURNS_IRETURNANNOUNCEMENTREPOSITORY_H
#define GUARD_LIBCSC_RETURNS_IRETURNANNOUNCEMENTREPOSITORY_H

#include <libbasar_definitions.h>
#include <returns/returnannouncement/returnannouncementptr.h>
#include <returns/returnannouncement/returnannouncementhead/returnannouncementheadptr.h>
#include <returns/returnannouncement/returnannouncementpos/returnannouncementposptr.h>

namespace libcsc {
namespace returns{

	class IReturnAnnouncementRepository
	{
	public:
		virtual ~IReturnAnnouncementRepository() {}

		virtual ReturnAnnouncementPtr createEmptyReturnAnnouncement() const = 0;
		virtual ReturnAnnouncementPtr findReturnAnnouncement(basar::Int32 returnAnnouncementId) const = 0;

		virtual void saveReturnAnnouncement(const ReturnAnnouncementPtr& returnAnnouncement) const = 0;
		virtual void saveReturnAnnouncementHeads(const ReturnAnnouncementPtr& returnAnnouncement) const = 0;
		virtual void saveReturnAnnouncementPositions(const ReturnAnnouncementHeadPtr& returnAnnouncementHead) const = 0;
	};

} //returns
} //libcsc

#endif // !GUARD_LIBCSC_RETURNS_IRETURNANNOUNCEMENTREPOSITORY_H
