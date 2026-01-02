#ifndef GUARD_LIBCSC_RETURNS_RETURNANNOUNCEMENT_H
#define GUARD_LIBCSC_RETURNS_RETURNANNOUNCEMENT_H

#include <datatypes/int16.h>
#include <datatypes/int32.h>
#include <datatypes/varstring.h>

#include <returns/returnannouncement/returnannouncementhead/returnannouncementheadptr.h>

namespace libcsc {
namespace returns {

	class ReturnAnnouncement
	{
		friend class ReturnAnnouncementMapperBase;
		friend class ReturnAnnouncementRepository;

	public:
		ReturnAnnouncement();
		virtual ~ReturnAnnouncement();

		virtual       basar::Int32		getAnnouncementId() const;
		virtual       basar::Int16		getBranchNo() const;
		virtual       basar::Int32		getCustomerNo() const;
		virtual const basar::VarString&	getAnnouncementGuid() const;
		virtual	      basar::Int32		getAnnouncementSupportId() const;
		virtual	      basar::Int32		getAnnouncementDate() const;
		virtual	      basar::Int32		getAnnouncementTime() const;
		virtual	      basar::Int16		getContainsWrongPickedItem() const;
		virtual const basar::VarString&	getLocalCourt() const;
		virtual const basar::VarString&	getCompanyRegistrationNo() const;
		virtual const basar::VarString&	getVatIdentificationNo() const;
		virtual const basar::VarString&	getTaxIdentificationNo() const;
		virtual const basar::VarString&	getNameOfBank() const;
		virtual const basar::VarString&	getBIC() const;
		virtual const basar::VarString&	getIBAN() const;

		virtual void					setBranchNo(const basar::Int16);
		virtual void					setCustomerNo(const basar::Int32);
		virtual	void					setAnnouncementGuid(const basar::VarString&);
		virtual	void					setAnnouncementSupportId(const basar::Int32);
		virtual	void					setAnnouncementDate(const basar::Int32);
		virtual	void					setAnnouncementTime(const basar::Int32);
		virtual	void					setContainsWrongPickedItem(const basar::Int16);
		virtual void					setLocalCourt(const basar::VarString&);
		virtual void					setCompanyRegistrationNo(const basar::VarString&);
		virtual void					setVatIdentificationNo(const basar::VarString&);
		virtual void					setTaxIdentificationNo(const basar::VarString&);
		virtual void					setNameOfBank(const basar::VarString&);
		virtual void					setBIC(const basar::VarString&);
		virtual void					setIBAN(const basar::VarString&);


		virtual const ReturnAnnouncementHeadCollectionPtr getHeads() const;
		virtual	ReturnAnnouncementHeadPtr	getAddHead(const basar::VarString& accCheckResult);

		bool isInsertable() const;


	private:
		libcsc::Int32		m_AnnouncementId;
		libcsc::Int16		m_BranchNo;
		libcsc::Int32		m_CustomerNo;
		libcsc::VarString	m_AnnouncementGuid;
		libcsc::Int32		m_AnnouncementSupportId;
		libcsc::Int32		m_AnnouncementDate;
		libcsc::Int32		m_AnnouncementTime;
		libcsc::Int16		m_ContainsWrongPickedItem;
		libcsc::VarString	m_LocalCourt;
		libcsc::VarString	m_CompanyRegistrationNo;
		libcsc::VarString	m_VatIdentificationNo;
		libcsc::VarString	m_TaxIdentificationNo;
		libcsc::VarString	m_NameOfBank;
		libcsc::VarString	m_BIC;
		libcsc::VarString	m_IBAN;

		ReturnAnnouncementHeadCollectionPtr m_Heads;
	};

} // namespace returns
} // namespace libcsc

#endif // !GUARD_LIBCSC_RETURNS_RETURNANNOUNCEMENT_H
