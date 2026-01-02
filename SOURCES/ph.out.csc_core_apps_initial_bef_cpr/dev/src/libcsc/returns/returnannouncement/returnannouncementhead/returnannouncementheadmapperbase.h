#ifndef GUARD_LIBCSC_RETURNS_RETURNANNOUNCEMENTHEADMAPPERBASE_H
#define GUARD_LIBCSC_RETURNS_RETURNANNOUNCEMENTHEADMAPPERBASE_H

#include "returnannouncementheadptr.h"
#include <libbasar_definitions.h>

namespace libcsc {
namespace returns {

	class ReturnAnnouncementHeadMapperBase
	{
	public:
		ReturnAnnouncementHeadMapperBase(ReturnAnnouncementHeadPtr returnAnnouncementHead);

		void map();
		void mapSerial(const basar::Int32 id);

	protected:
		virtual ~ReturnAnnouncementHeadMapperBase();

		virtual void doMap() = 0;
		virtual void doMapSerial(const basar::Int32 id) = 0;

		void setAnnouncementHeadId(const basar::Int32 announcementHeadId);
		void setAnnouncementId(const basar::Int32 announcementId);
		void setAccCheckResultCode(const basar::VarString accCheckResultCode);
		void setWholesalerReferenceId(const basar::VarString& wholesalerReferenceId);
		void setDocumentId(const basar::VarString& documentId);
		void setTourId(const basar::VarString& tourId);
		void setTourDepartureDate(const basar::Int32 tourDepartureDate);
		void setTransferStatus(const basar::Int16 transferStatus);

	private:
		ReturnAnnouncementHeadPtr m_returnAnnouncementHead;
	};

} //returns
} //libcsc

#endif // !GUARD_LIBCSC_RETURNS_RETURNANNOUNCEMENTHEADMAPPERBASE_H
