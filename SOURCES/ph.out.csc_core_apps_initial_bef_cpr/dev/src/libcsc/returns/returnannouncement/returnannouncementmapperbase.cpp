#include "returnannouncementmapperbase.h"
#include "returnannouncement.h"

namespace libcsc {
namespace returns {

	ReturnAnnouncementMapperBase::ReturnAnnouncementMapperBase(ReturnAnnouncementPtr returnAnnouncement)
		: m_ReturnAnnouncement(returnAnnouncement)
	{

	}

	ReturnAnnouncementMapperBase::~ReturnAnnouncementMapperBase()
	{

	}

	void ReturnAnnouncementMapperBase::map()
	{
		doMap();
	}

	void ReturnAnnouncementMapperBase::mapSerial(const basar::Int32 id)
	{
		doMapSerial(id);
	}

	void ReturnAnnouncementMapperBase::setAnnouncementId(const basar::Int32 announcementId)
	{
		m_ReturnAnnouncement->m_AnnouncementId = announcementId;
		m_ReturnAnnouncement->m_AnnouncementId.setClean();
	}

	void ReturnAnnouncementMapperBase::setBranchNo(const basar::Int16 branchNo)
	{
		m_ReturnAnnouncement->m_BranchNo = branchNo;
		m_ReturnAnnouncement->m_BranchNo.setClean();
	}

	void ReturnAnnouncementMapperBase::setCustomerNo(const basar::Int32 customerNo)
	{
		m_ReturnAnnouncement->m_CustomerNo = customerNo;
		m_ReturnAnnouncement->m_CustomerNo.setClean();
	}

	void ReturnAnnouncementMapperBase::setAnnouncementGuid(const basar::VarString& announcementGuid)
	{
		m_ReturnAnnouncement->m_AnnouncementGuid = announcementGuid;
		m_ReturnAnnouncement->m_AnnouncementGuid.setClean();
	}

	void ReturnAnnouncementMapperBase::setAnnouncementSupportId(const basar::Int32 announcementSupportId)
	{
		m_ReturnAnnouncement->m_AnnouncementSupportId = announcementSupportId;
		m_ReturnAnnouncement->m_AnnouncementSupportId.setClean();
	}

	void ReturnAnnouncementMapperBase::setAnnouncementDate(const basar::Int32 announcementDate)
	{
		m_ReturnAnnouncement->m_AnnouncementDate = announcementDate;
		m_ReturnAnnouncement->m_AnnouncementDate.setClean();
	}

	void ReturnAnnouncementMapperBase::setAnnouncementTime(const basar::Int32 announcementTime)
	{
		m_ReturnAnnouncement->m_AnnouncementTime = announcementTime;
		m_ReturnAnnouncement->m_AnnouncementTime.setClean();
	}

	void ReturnAnnouncementMapperBase::setContainsWrongPickedItem(const basar::Int16 containsWrongPickedItem)
	{
		m_ReturnAnnouncement->m_ContainsWrongPickedItem = containsWrongPickedItem;
		m_ReturnAnnouncement->m_ContainsWrongPickedItem.setClean();
	}

	void ReturnAnnouncementMapperBase::setLocalCourt(const basar::VarString& localCourt)
	{
		m_ReturnAnnouncement->m_LocalCourt = localCourt;
		m_ReturnAnnouncement->m_LocalCourt.setClean();
	}

	void ReturnAnnouncementMapperBase::setCompanyRegistrationNo(const basar::VarString& companyRegistrationNo)
	{
		m_ReturnAnnouncement->m_CompanyRegistrationNo = companyRegistrationNo;
		m_ReturnAnnouncement->m_CompanyRegistrationNo.setClean();
	}

	void ReturnAnnouncementMapperBase::setVatIdentificationNo(const basar::VarString& vatIdentificationNo)
	{
		m_ReturnAnnouncement->m_VatIdentificationNo = vatIdentificationNo;
		m_ReturnAnnouncement->m_VatIdentificationNo.setClean();
	}

	void ReturnAnnouncementMapperBase::setTaxIdentificationNo(const basar::VarString& taxIdentificationNo)
	{
		m_ReturnAnnouncement->m_TaxIdentificationNo = taxIdentificationNo;
		m_ReturnAnnouncement->m_TaxIdentificationNo.setClean();
	}

	void ReturnAnnouncementMapperBase::setNameOfBank(const basar::VarString& nameOfBank)
	{
		m_ReturnAnnouncement->m_NameOfBank = nameOfBank;
		m_ReturnAnnouncement->m_NameOfBank.setClean();
	}

	void ReturnAnnouncementMapperBase::setBIC(const basar::VarString& bic)
	{
		m_ReturnAnnouncement->m_BIC = bic;
		m_ReturnAnnouncement->m_BIC.setClean();
	}

	void ReturnAnnouncementMapperBase::setIBAN(const basar::VarString& iban)
	{
		m_ReturnAnnouncement->m_IBAN = iban;
		m_ReturnAnnouncement->m_IBAN.setClean();
	}

} // namespace returns
} // namespace libcsc
