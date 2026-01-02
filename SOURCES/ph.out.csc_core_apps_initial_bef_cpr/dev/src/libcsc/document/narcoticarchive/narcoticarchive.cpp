#include "narcoticarchive.h"
#include <logger/loggerpool.h>

namespace libcsc {
	namespace document {

		NarcoticArchive::NarcoticArchive()
		{
			LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "NarcoticArchive::NarcoticArchive()");
		}

		NarcoticArchive::~NarcoticArchive()
		{
			LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "NarcoticArchive::~NarcoticArchive()");
		}

		const basar::Int16& NarcoticArchive::getAcknowledgementStatus() const
		{
			return m_AcknowledgementStatus;
		}
		const basar::Int32& NarcoticArchive::getArticleNo() const
		{
			return m_ArticleNo;
		}
		const basar::Int16& NarcoticArchive::getBranchNo() const
		{
			return m_BranchNo;
		}
		const basar::Int32& NarcoticArchive::getCatalogId() const
		{
			return m_CatalogId;
		}
		const basar::Int32& NarcoticArchive::getContributionVoucherNo() const
		{
			return m_ContributionVoucherNo;
		}
		const basar::DateTime& NarcoticArchive::getContributionVoucherTransferDate() const
		{
			return m_ContributionVoucherTransferDate;
		}
		const basar::Int16& NarcoticArchive::getContributionVoucherTransferStatus() const
		{
			return m_ContributionVoucherTransferStatus;
		}
		const basar::VarString& NarcoticArchive::getCustomerSupplierCip() const
		{
			return m_CustomerSupplierCip;
		}
		const basar::VarString& NarcoticArchive::getCustomerSupplierCity() const
		{
			return m_CustomerSupplierCity;
		}
		const basar::VarString& NarcoticArchive::getCustomerSupplierName() const
		{
			return m_CustomerSupplierName;
		}
		const basar::Int32& NarcoticArchive::getCustomerSupplierNo() const
		{
			return m_CustomerSupplierNo;
		}
		const basar::VarString& NarcoticArchive::getCustomerSupplierStreet() const
		{
			return m_CustomerSupplierStreet;
		}
		const basar::VarString& NarcoticArchive::getDeletedFlag() const
		{
			return m_DeletedFlag;
		}
		const basar::DateTime& NarcoticArchive::getDeliveryNoteCopyTransferDate() const
		{
			return m_DeliveryNoteCopyTransferDate;
		}
		const basar::Int16& NarcoticArchive::getDeliveryNoteCopyTransferStatus() const
		{
			return m_DeliveryNoteCopyTransferStatus;
		}
		const basar::VarString& NarcoticArchive::getForeName() const
		{
			return m_ForeName;
		}
		const basar::Int32& NarcoticArchive::getInvoiceNo() const
		{
			return m_InvoiceNo;
		}
		const basar::Decimal& NarcoticArchive::getNarcFactor() const
		{
			return m_NarcFactor;
		}
		const basar::VarString& NarcoticArchive::getNarcGroup() const
		{
			return m_NarcGroup;
		}
		const basar::VarString& NarcoticArchive::getNarcName() const
		{
			return m_NarcName;
		}
		const basar::Decimal& NarcoticArchive::getNarcPotency() const
		{
			return m_NarcPotency;
		}
		const basar::VarString& NarcoticArchive::getNarcUnit() const
		{
			return m_NarcUnit;
		}
		const basar::Int32& NarcoticArchive::getPrintedDate() const
		{
			return m_PrintedDate;
		}
		const basar::Int32& NarcoticArchive::getPrintedTime() const
		{
			return m_PrintedTime;
		}
		const basar::VarString& NarcoticArchive::getProcessedFlag() const
		{
			return m_ProcessedFlag;
		}
		const basar::Int32& NarcoticArchive::getPurchaseOrderNo() const
		{
			return m_PurchaseOrderNo;
		}
		const basar::Int32& NarcoticArchive::getQtyInstock() const
		{
			return m_QtyInstock;
		}
		const basar::Int32& NarcoticArchive::getQtyTransaction() const
		{
			return m_QtyTransaction;
		}
		const basar::VarString& NarcoticArchive::getSurname() const
		{
			return m_Surname;
		}
		const basar::VarString& NarcoticArchive::getTourId() const
		{
			return m_TourId;
		}
		const basar::Int32& NarcoticArchive::getTransactionDate() const
		{
			return m_TransactionDate;
		}
		const basar::Int32& NarcoticArchive::getTransactionTime() const
		{
			return m_TransactionTime;
		}
		const TransactionTypeEnum& NarcoticArchive::getTransactionType() const
		{
			return m_TransactionType;
		}
		const basar::VarString& NarcoticArchive::getUsername() const
		{
			return m_Username;
		}
		const basar::Int32& NarcoticArchive::getWarehouseOrderNo() const
		{
			return m_WarehouseOrderNo;
		}
		void NarcoticArchive::setAcknowledgementStatus(const basar::Int16& value)
		{
			m_AcknowledgementStatus = value;
		}
		void NarcoticArchive::setArticleNo(const basar::Int32& value)
		{
			m_ArticleNo = value;
		}
		void NarcoticArchive::setBranchNo(const basar::Int16& value)
		{
			m_BranchNo = value;
		}
		void NarcoticArchive::setCatalogId(const basar::Int32& value)
		{
			m_CatalogId = value;
		}
		void NarcoticArchive::setContributionVoucherNo(const basar::Int32& value)
		{
			m_ContributionVoucherNo = value;
		}
		void NarcoticArchive::setContributionVoucherTransferDate(const basar::DateTime& value)
		{
			m_ContributionVoucherTransferDate = value;
		}
		void NarcoticArchive::setContributionVoucherTransferStatus(const basar::Int16& value)
		{
			m_ContributionVoucherTransferStatus = value;
		}
		void NarcoticArchive::setCustomerSupplierCip(const basar::VarString& value)
		{
			m_CustomerSupplierCip = value;
		}
		void NarcoticArchive::setCustomerSupplierCity(const basar::VarString& value)
		{
			m_CustomerSupplierCity = value;
		}
		void NarcoticArchive::setCustomerSupplierName(const basar::VarString& value)
		{
			m_CustomerSupplierName = value;
		}
		void NarcoticArchive::setCustomerSupplierNo(const basar::Int32& value)
		{
			m_CustomerSupplierNo = value;
		}
		void NarcoticArchive::setCustomerSupplierStreet(const basar::VarString& value)
		{
			m_CustomerSupplierStreet = value;
		}
		void NarcoticArchive::setDeletedFlag(const basar::VarString& value)
		{
			m_DeletedFlag = value;
		}
		void NarcoticArchive::setDeliveryNoteCopyTransferDate(const basar::DateTime& value)
		{
			m_DeliveryNoteCopyTransferDate = value;
		}
		void NarcoticArchive::setDeliveryNoteCopyTransferStatus(const basar::Int16& value)
		{
			m_DeliveryNoteCopyTransferStatus = value;
		}
		void NarcoticArchive::setForeName(const basar::VarString& value)
		{
			m_ForeName = value;
		}
		void NarcoticArchive::setInvoiceNo(const basar::Int32& value)
		{
			m_InvoiceNo = value;
		}
		void NarcoticArchive::setNarcFactor(const basar::Decimal& value)
		{
			m_NarcFactor = value;
		}
		void NarcoticArchive::setNarcGroup(const basar::VarString& value)
		{
			m_NarcGroup = value;
		}
		void NarcoticArchive::setNarcName(const basar::VarString& value)
		{
			m_NarcName = value;
		}
		void NarcoticArchive::setNarcPotency(const basar::Decimal& value)
		{
			m_NarcPotency = value;
		}
		void NarcoticArchive::setNarcUnit(const basar::VarString& value)
		{
			m_NarcUnit = value;
		}
		void NarcoticArchive::setPrintedDate(const basar::Int32& value)
		{
			m_PrintedDate = value;
		}
		void NarcoticArchive::setPrintedTime(const basar::Int32& value)
		{
			m_PrintedTime = value;
		}
		void NarcoticArchive::setProcessedFlag(const basar::VarString& value)
		{
			m_ProcessedFlag = value;
		}
		void NarcoticArchive::setPurchaseOrderNo(const basar::Int32& value)
		{
			m_PurchaseOrderNo = value;
		}
		void NarcoticArchive::setQtyInstock(const basar::Int32& value)
		{
			m_QtyInstock = value;
		}
		void NarcoticArchive::setQtyTransaction(const basar::Int32& value)
		{
			m_QtyTransaction = value;
		}
		void NarcoticArchive::setSurname(const basar::VarString& value)
		{
			m_Surname = value;
		}
		void NarcoticArchive::setTourId(const basar::VarString& value)
		{
			m_TourId = value;
		}
		void NarcoticArchive::setTransactionDate(const basar::Int32& value)
		{
			m_TransactionDate = value;
		}
		void NarcoticArchive::setTransactionTime(const basar::Int32& value)
		{
			m_TransactionTime = value;
		}
		void NarcoticArchive::setTransactionType(const TransactionTypeEnum& value)
		{
			m_TransactionType = value;
		}
		void NarcoticArchive::setUsername(const basar::VarString& value)
		{
			m_Username = value;
		}
		void NarcoticArchive::setWarehouseOrderNo(const basar::Int32& value)
		{
			m_WarehouseOrderNo = value;
		}

		bool NarcoticArchive::isClean()
		{
			LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "NarcoticArchive::isClean()");
			return m_BranchNo.isClean() &&
				m_CatalogId.isClean() &&
				m_ContributionVoucherNo.isClean() &&
				m_CustomerSupplierNo.isClean();
		}

		bool NarcoticArchive::isDirty()
		{
			LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "NarcoticArchive::isDirty()");
			return m_BranchNo.isDirty() &&
				m_CatalogId.isDirty() &&
				m_ContributionVoucherNo.isDirty() &&
				m_CustomerSupplierNo.isDirty();
		}

		void NarcoticArchive::setClean()
		{
			LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "NarcoticArchive::setClean()");
		}

	} // namespace document
} // namespace libcsc
