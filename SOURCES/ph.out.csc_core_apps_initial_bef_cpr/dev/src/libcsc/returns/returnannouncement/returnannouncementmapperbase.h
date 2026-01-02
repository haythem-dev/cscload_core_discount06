#ifndef GUARD_LIBCSC_RETURNS_RETURNANNOUNCEMENTMAPPERBASE_H
#define GUARD_LIBCSC_RETURNS_RETURNANNOUNCEMENTMAPPERBASE_H

#include "returnannouncementptr.h"
#include <libbasar_definitions.h>

namespace libcsc {
namespace returns {

	class ReturnAnnouncementMapperBase
	{
	public:
		ReturnAnnouncementMapperBase(ReturnAnnouncementPtr returnannouncement);

		void map();
		void mapSerial(const basar::Int32 id);


	protected:
		virtual ~ReturnAnnouncementMapperBase();

		virtual void doMap() = 0;
		virtual void doMapSerial(const basar::Int32 id) = 0;

		void setAnnouncementId(const basar::Int32 announcementId);
		void setBranchNo(const basar::Int16 branchNo);
		void setCustomerNo(const basar::Int32 customerNo);
		void setAnnouncementGuid(const basar::VarString& announcementGuid);
		void setAnnouncementSupportId(const basar::Int32 announcementSupportId);
		void setAnnouncementDate(const basar::Int32 announcementDate);
		void setAnnouncementTime(const basar::Int32 announcementTime);
		void setContainsWrongPickedItem(const basar::Int16 containsWrongPickedItem);
		void setLocalCourt(const basar::VarString& localCourt);
		void setCompanyRegistrationNo(const basar::VarString& companyRegistrationNo);
		void setVatIdentificationNo(const basar::VarString& vatIdentificationNo);
		void setTaxIdentificationNo(const basar::VarString& taxIdentificationNo);
		void setNameOfBank(const basar::VarString& nameOfBank);
		void setBIC(const basar::VarString& bic);
		void setIBAN(const basar::VarString& iban);

	private:
		ReturnAnnouncementPtr m_ReturnAnnouncement;
	};

} // namespace returns
} // namespace libcsc

#endif // !GUARD_LIBCSC_RETURNS_RETURNANNOUNCEMENTMAPPERBASE_H
