#include "returnannouncement.h"
#include <logger/loggerpool.h>
#include <returns/returnannouncement/returnannouncementhead/returnannouncementhead.h>
#include <boost/make_shared.hpp>

namespace libcsc {
namespace returns {

	ReturnAnnouncement::ReturnAnnouncement()
	{
		m_Heads = boost::make_shared<ReturnAnnouncementHeadCollection>();
	}

	ReturnAnnouncement::~ReturnAnnouncement()
	{
	}

	basar::Int32 ReturnAnnouncement::getAnnouncementId() const
	{
		return m_AnnouncementId;
	}

	basar::Int16 ReturnAnnouncement::getBranchNo() const
	{
		return m_BranchNo;
	}

	basar::Int32 ReturnAnnouncement::getCustomerNo() const
	{
		return m_CustomerNo;
	}

	const basar::VarString& ReturnAnnouncement::getAnnouncementGuid() const
	{
		return m_AnnouncementGuid;
	}

	basar::Int32 ReturnAnnouncement::getAnnouncementSupportId() const
	{
		return m_AnnouncementSupportId;
	}

	basar::Int32 ReturnAnnouncement::getAnnouncementDate() const
	{
		return m_AnnouncementDate;
	}

	basar::Int32 ReturnAnnouncement::getAnnouncementTime() const
	{
		return m_AnnouncementTime;
	}

	basar::Int16 ReturnAnnouncement::getContainsWrongPickedItem() const
	{
		return m_ContainsWrongPickedItem;
	}

	const basar::VarString& ReturnAnnouncement::getLocalCourt() const
	{
		return m_LocalCourt;
	}

	const basar::VarString& ReturnAnnouncement::getCompanyRegistrationNo() const
	{
		return m_CompanyRegistrationNo;
	}

	const basar::VarString& ReturnAnnouncement::getVatIdentificationNo() const
	{
		return m_VatIdentificationNo;
	}

	const basar::VarString& ReturnAnnouncement::getTaxIdentificationNo() const
	{
		return m_TaxIdentificationNo;
	}

	const basar::VarString& ReturnAnnouncement::getNameOfBank() const
	{
		return m_NameOfBank;
	}

	const basar::VarString& ReturnAnnouncement::getBIC() const
	{
		return m_BIC;
	}

	const basar::VarString& ReturnAnnouncement::getIBAN() const
	{
		return m_IBAN;
	}

	void ReturnAnnouncement::setBranchNo(const basar::Int16 branchNo)
	{
		m_BranchNo = branchNo;
	}

	void ReturnAnnouncement::setCustomerNo(const basar::Int32 customerNo)
	{
		m_CustomerNo = customerNo;
	}

	void ReturnAnnouncement::setAnnouncementGuid(const basar::VarString& guid)
	{
		m_AnnouncementGuid = guid;
	}

	void ReturnAnnouncement::setAnnouncementSupportId(const basar::Int32 id)
	{
		m_AnnouncementSupportId = id;
	}

	void ReturnAnnouncement::setAnnouncementDate(const basar::Int32 date)
	{
		m_AnnouncementDate = date;
	}

	void ReturnAnnouncement::setAnnouncementTime(const basar::Int32  time)
	{
		m_AnnouncementTime = time;
	}

	void ReturnAnnouncement::setContainsWrongPickedItem(const basar::Int16 wpi)
	{
		m_ContainsWrongPickedItem = wpi;
	}

	void ReturnAnnouncement::setLocalCourt(const basar::VarString& localCourt)
	{
		m_LocalCourt = localCourt;
	}

	void ReturnAnnouncement::setCompanyRegistrationNo(const basar::VarString& regNo)
	{
		m_CompanyRegistrationNo = regNo;
	}

	void ReturnAnnouncement::setVatIdentificationNo(const basar::VarString& vatNo)
	{
		m_VatIdentificationNo = vatNo;
	}

	void ReturnAnnouncement::setTaxIdentificationNo(const basar::VarString& taxNo)
	{
		m_TaxIdentificationNo = taxNo;
	}

	void ReturnAnnouncement::setNameOfBank(const basar::VarString& bank)
	{
		m_NameOfBank = bank;
	}

	void ReturnAnnouncement::setBIC(const basar::VarString& bic)
	{
		m_BIC = bic;
	}

	void ReturnAnnouncement::setIBAN(const basar::VarString& iban)
	{
		m_IBAN = iban;
	}


	const ReturnAnnouncementHeadCollectionPtr ReturnAnnouncement::getHeads() const
	{
		return m_Heads;
	}

	ReturnAnnouncementHeadPtr ReturnAnnouncement::getAddHead(const basar::VarString& accCheckResult)
	{
		LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerReturns(), "ReturnAnnouncement::getAddHead()");

		ReturnAnnouncementHeadPtr head;
		ReturnAnnouncementHeadCollection::const_iterator it = m_Heads->begin();
		while (it != m_Heads->end())
		{
			head = *it;
			if (head->getAccCheckResultCode() == accCheckResult)
			{
				return head;
			}
			++it;
		}
		// insert new
		head = boost::make_shared<ReturnAnnouncementHead>();
		head->setAccCheckResultCode(accCheckResult);
		m_Heads->push_back(head);
		return head;
	}

	bool ReturnAnnouncement::isInsertable() const
	{
		return m_AnnouncementDate.isDirty() &&
			   m_AnnouncementGuid.isDirty() &&
			   m_AnnouncementSupportId.isDirty() &&
			   m_AnnouncementTime.isDirty() &&
			   m_BIC.isDirty() &&
			   m_BranchNo.isDirty() &&
			   m_CompanyRegistrationNo.isDirty() &&
			   m_ContainsWrongPickedItem.isDirty() &&
			   m_CustomerNo.isDirty() &&
			   m_IBAN.isDirty() &&
			   m_LocalCourt.isDirty() &&
			   m_NameOfBank.isDirty() &&
			   m_TaxIdentificationNo.isDirty() &&
			   m_VatIdentificationNo.isDirty();
	}

} // namespace returns
} // namespace libcsc
