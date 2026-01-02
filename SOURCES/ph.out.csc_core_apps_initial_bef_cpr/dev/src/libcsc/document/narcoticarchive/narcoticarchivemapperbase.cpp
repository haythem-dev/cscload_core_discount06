#include "narcoticarchivemapperbase.h"
#include "narcoticarchive.h"
#include "logger/loggerpool.h"

namespace libcsc 
{
	namespace document 
	{
		NarcoticArchiveMapperBase::NarcoticArchiveMapperBase(NarcoticArchivePtr documentArchiveInfo) :
			m_NarcoticArchive(documentArchiveInfo)
		{
			LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "NarcoticArchiveMapperBase::NarcoticArchiveMapperBase()");
		}

		NarcoticArchiveMapperBase::~NarcoticArchiveMapperBase()
		{
			LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "NarcoticArchiveMapperBase::~NarcoticArchiveMapperBase()");
		}

		void NarcoticArchiveMapperBase::map()
		{
			LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "NarcoticArchiveMapperBase::map()");

			doMap();
		}

		void NarcoticArchiveMapperBase::setContributionVoucherTransferDate(const basar::DateTime& contributionVoucherTransferDate)
		{
			LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "NarcoticArchiveMapperBase::setContributionVoucherTransferDate()");

			m_NarcoticArchive->m_ContributionVoucherTransferDate = contributionVoucherTransferDate;
			m_NarcoticArchive->m_ContributionVoucherTransferDate.setClean();
		}

		void NarcoticArchiveMapperBase::setDeliveryNoteCopyTransferDate(const basar::DateTime& deliveryNoteCopyTransferDate)
		{
			LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "NarcoticArchiveMapperBase::setDeliveryNoteCopyTransferDate()");

			m_NarcoticArchive->m_DeliveryNoteCopyTransferDate = deliveryNoteCopyTransferDate;
			m_NarcoticArchive->m_DeliveryNoteCopyTransferDate.setClean();
		}

		void NarcoticArchiveMapperBase::setNarcFactor(const basar::Decimal& narcFactor)
		{
			LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "NarcoticArchiveMapperBase::setNarcFactor()");

			m_NarcoticArchive->m_NarcFactor = narcFactor;
			m_NarcoticArchive->m_NarcFactor.setClean();
		}

		void NarcoticArchiveMapperBase::setNarcPotency(const basar::Decimal& narcPotency)
		{
			LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "NarcoticArchiveMapperBase::setNarcPotency()");

			m_NarcoticArchive->m_NarcPotency = narcPotency;
			m_NarcoticArchive->m_NarcPotency.setClean();
		}

		void NarcoticArchiveMapperBase::setAcknowledgementStatus(const basar::Int16& acknowledgementStatus)
		{
			LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "NarcoticArchiveMapperBase::setAcknowledgementStatus()");

			m_NarcoticArchive->m_AcknowledgementStatus = acknowledgementStatus;
			m_NarcoticArchive->m_AcknowledgementStatus.setClean();
		}

		void NarcoticArchiveMapperBase::setBranchNo(const basar::Int16& branchNo)
		{
			LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "NarcoticArchiveMapperBase::setBranchNo()");

			m_NarcoticArchive->m_BranchNo = branchNo;
			m_NarcoticArchive->m_BranchNo.setClean();
		}

		void NarcoticArchiveMapperBase::setContributionVoucherTransferStatus(const basar::Int16& contributionVoucherTransferStatus)
		{
			LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "NarcoticArchiveMapperBase::setContributionVoucherTransferStatus()");

			m_NarcoticArchive->m_ContributionVoucherTransferStatus = contributionVoucherTransferStatus;
			m_NarcoticArchive->m_ContributionVoucherTransferStatus.setClean();
		}

		void NarcoticArchiveMapperBase::setDeliveryNoteCopyTransferStatus(const basar::Int16& deliveryNoteCopyTransferStatus)
		{
			LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "NarcoticArchiveMapperBase::setDeliveryNoteCopyTransferStatus()");

			m_NarcoticArchive->m_DeliveryNoteCopyTransferStatus = deliveryNoteCopyTransferStatus;
			m_NarcoticArchive->m_DeliveryNoteCopyTransferStatus.setClean();
		}

		void NarcoticArchiveMapperBase::setArticleNo(const basar::Int32& articleNo)
		{
			LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "NarcoticArchiveMapperBase::setArticleNo()");

			m_NarcoticArchive->m_ArticleNo = articleNo;
			m_NarcoticArchive->m_ArticleNo.setClean();
		}

		void NarcoticArchiveMapperBase::setContributionVoucherNo(const basar::Int32& contributionVoucherNo)
		{
			LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "NarcoticArchiveMapperBase::setContributionVoucherNo()");

			m_NarcoticArchive->m_ContributionVoucherNo = contributionVoucherNo;
			m_NarcoticArchive->m_ContributionVoucherNo.setClean();
		}

		void NarcoticArchiveMapperBase::setCustomerSupplierNo(const basar::Int32& customerSupplierNo)
		{
			LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "NarcoticArchiveMapperBase::setCustomerSupplierNo()");

			m_NarcoticArchive->m_CustomerSupplierNo = customerSupplierNo;
			m_NarcoticArchive->m_CustomerSupplierNo.setClean();
		}

		void NarcoticArchiveMapperBase::setInvoiceNo(const basar::Int32& invoiceNo)
		{
			LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "NarcoticArchiveMapperBase::setInvoiceNo()");

			m_NarcoticArchive->m_InvoiceNo = invoiceNo;
			m_NarcoticArchive->m_InvoiceNo.setClean();
		}

		void NarcoticArchiveMapperBase::setPrintedDate(const basar::Int32& printedDate)
		{
			LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "NarcoticArchiveMapperBase::setPrintedDate()");

			m_NarcoticArchive->m_PrintedDate = printedDate;
			m_NarcoticArchive->m_PrintedDate.setClean();
		}

		void NarcoticArchiveMapperBase::setPrintedTime(const basar::Int32& printedTime)
		{
			LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "NarcoticArchiveMapperBase::setPrintedTime()");

			m_NarcoticArchive->m_PrintedTime = printedTime;
			m_NarcoticArchive->m_PrintedTime.setClean();
		}

		void NarcoticArchiveMapperBase::setPurchaseOrderNo(const basar::Int32& purchaseOrderNo)
		{
			LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "NarcoticArchiveMapperBase::setPurchaseOrderNo()");

			m_NarcoticArchive->m_PurchaseOrderNo = purchaseOrderNo;
			m_NarcoticArchive->m_PurchaseOrderNo.setClean();
		}

		void NarcoticArchiveMapperBase::setQtyInstock(const basar::Int32& qtyInstock)
		{
			LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "NarcoticArchiveMapperBase::setQtyInstock()");

			m_NarcoticArchive->m_QtyInstock = qtyInstock;
			m_NarcoticArchive->m_QtyInstock.setClean();
		}

		void NarcoticArchiveMapperBase::setQtyTransaction(const basar::Int32& qtyTransaction)
		{
			LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "NarcoticArchiveMapperBase::setQtyTransaction()");

			m_NarcoticArchive->m_QtyTransaction = qtyTransaction;
			m_NarcoticArchive->m_QtyTransaction.setClean();
		}

		void NarcoticArchiveMapperBase::setTransactionDate(const basar::Int32& transactionDate)
		{
			LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "NarcoticArchiveMapperBase::setTransactionDate()");

			m_NarcoticArchive->m_TransactionDate = transactionDate;
			m_NarcoticArchive->m_TransactionDate.setClean();
		}

		void NarcoticArchiveMapperBase::setTransactionTime(const basar::Int32& transactionTime)
		{
			LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "NarcoticArchiveMapperBase::setTransactionTime()");

			m_NarcoticArchive->m_TransactionTime = transactionTime;
			m_NarcoticArchive->m_TransactionTime.setClean();
		}

		void NarcoticArchiveMapperBase::setWarehouseOrderNo(const basar::Int32& warehouseOrderNo)
		{
			LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "NarcoticArchiveMapperBase::setWarehouseOrderNo()");

			m_NarcoticArchive->m_WarehouseOrderNo = warehouseOrderNo;
			m_NarcoticArchive->m_WarehouseOrderNo.setClean();
		}

		void NarcoticArchiveMapperBase::setCatalogId(const basar::Int32& catalogId)
		{
			LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "NarcoticArchiveMapperBase::setCatalogId()");

			m_NarcoticArchive->m_CatalogId = catalogId;
			m_NarcoticArchive->m_CatalogId.setClean();
		}

		void NarcoticArchiveMapperBase::setCustomerSupplierCip(const basar::VarString& customerSupplierCip)
		{
			LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "NarcoticArchiveMapperBase::setCustomerSupplierCip()");

			m_NarcoticArchive->m_CustomerSupplierCip = customerSupplierCip;
			m_NarcoticArchive->m_CustomerSupplierCip.setClean();
		}

		void NarcoticArchiveMapperBase::setCustomerSupplierCity(const basar::VarString& customerSupplierCity)
		{
			LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "NarcoticArchiveMapperBase::setCustomerSupplierCity()");

			m_NarcoticArchive->m_CustomerSupplierCity = customerSupplierCity;
			m_NarcoticArchive->m_CustomerSupplierCity.setClean();
		}

		void NarcoticArchiveMapperBase::setCustomerSupplierName(const basar::VarString& customerSupplierName)
		{
			LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "NarcoticArchiveMapperBase::setCustomerSupplierName()");

			m_NarcoticArchive->m_CustomerSupplierName = customerSupplierName;
			m_NarcoticArchive->m_CustomerSupplierName.setClean();
		}

		void NarcoticArchiveMapperBase::setCustomerSupplierStreet(const basar::VarString& customerSupplierStreet)
		{
			LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "NarcoticArchiveMapperBase::setCustomerSupplierStreet()");

			m_NarcoticArchive->m_CustomerSupplierStreet = customerSupplierStreet;
			m_NarcoticArchive->m_CustomerSupplierStreet.setClean();
		}

		void NarcoticArchiveMapperBase::setDeletedFlag(const basar::VarString& deletedFlag)
		{
			LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "NarcoticArchiveMapperBase::setDeletedFlag()");

			m_NarcoticArchive->m_DeletedFlag = deletedFlag;
			m_NarcoticArchive->m_DeletedFlag.setClean();
		}

		void NarcoticArchiveMapperBase::setForeName(const basar::VarString& foreName)
		{
			LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "NarcoticArchiveMapperBase::setForeName()");

			m_NarcoticArchive->m_ForeName = foreName;
			m_NarcoticArchive->m_ForeName.setClean();
		}

		void NarcoticArchiveMapperBase::setNarcGroup(const basar::VarString& narcGroup)
		{
			LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "NarcoticArchiveMapperBase::setNarcGroup()");

			m_NarcoticArchive->m_NarcGroup = narcGroup;
			m_NarcoticArchive->m_NarcGroup.setClean();
		}

		void NarcoticArchiveMapperBase::setNarcName(const basar::VarString& narcName)
		{
			LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "NarcoticArchiveMapperBase::setNarcName()");

			m_NarcoticArchive->m_NarcName = narcName;
			m_NarcoticArchive->m_NarcName.setClean();
		}

		void NarcoticArchiveMapperBase::setNarcUnit(const basar::VarString& narcUnit)
		{
			LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "NarcoticArchiveMapperBase::setNarcUnit()");

			m_NarcoticArchive->m_NarcUnit = narcUnit;
			m_NarcoticArchive->m_NarcUnit.setClean();
		}

		void NarcoticArchiveMapperBase::setProcessedFlag(const basar::VarString& processedFlag)
		{
			LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "NarcoticArchiveMapperBase::setProcessedFlag()");

			m_NarcoticArchive->m_ProcessedFlag = processedFlag;
			m_NarcoticArchive->m_ProcessedFlag.setClean();
		}

		void NarcoticArchiveMapperBase::setSurname(const basar::VarString& surname)
		{
			LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "NarcoticArchiveMapperBase::setSurname()");

			m_NarcoticArchive->m_Surname = surname;
			m_NarcoticArchive->m_Surname.setClean();
		}

		void NarcoticArchiveMapperBase::setTourId(const basar::VarString& tourId)
		{
			LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "NarcoticArchiveMapperBase::setTourId()");

			m_NarcoticArchive->m_TourId = tourId;
			m_NarcoticArchive->m_TourId.setClean();
		}

		void NarcoticArchiveMapperBase::setUsername(const basar::VarString& username)
		{
			LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "NarcoticArchiveMapperBase::setUsername()");

			m_NarcoticArchive->m_Username = username;
			m_NarcoticArchive->m_Username.setClean();
		}

		void NarcoticArchiveMapperBase::setTransactionType(const TransactionTypeEnum& transactionType)
		{
			LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "NarcoticArchiveMapperBase::setTransactionType()");

			m_NarcoticArchive->m_TransactionType = transactionType;
			m_NarcoticArchive->m_TransactionType.setClean();
		}


		void NarcoticArchiveMapperBase::setClean()
		{
			LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "NarcoticArchiveMapperBase::setClean()");

			m_NarcoticArchive->m_TransactionType.setClean();
			m_NarcoticArchive->m_NarcFactor.setClean();
			m_NarcoticArchive->m_NarcPotency.setClean();
			m_NarcoticArchive->m_AcknowledgementStatus.setClean();
			m_NarcoticArchive->m_BranchNo.setClean();
			m_NarcoticArchive->m_ContributionVoucherTransferStatus.setClean();
			m_NarcoticArchive->m_DeliveryNoteCopyTransferStatus.setClean();
			m_NarcoticArchive->m_ArticleNo.setClean();
			m_NarcoticArchive->m_ContributionVoucherNo.setClean();
			m_NarcoticArchive->m_CustomerSupplierNo.setClean();
			m_NarcoticArchive->m_InvoiceNo.setClean();
			m_NarcoticArchive->m_PrintedDate.setClean();
			m_NarcoticArchive->m_PrintedTime.setClean();
			m_NarcoticArchive->m_PurchaseOrderNo.setClean();
			m_NarcoticArchive->m_QtyInstock.setClean();
			m_NarcoticArchive->m_QtyTransaction.setClean();
			m_NarcoticArchive->m_TransactionDate.setClean();
			m_NarcoticArchive->m_TransactionTime.setClean();
			m_NarcoticArchive->m_WarehouseOrderNo.setClean();
			m_NarcoticArchive->m_CatalogId.setClean();
			m_NarcoticArchive->m_CustomerSupplierCip.setClean();
			m_NarcoticArchive->m_CustomerSupplierCity.setClean();
			m_NarcoticArchive->m_CustomerSupplierName.setClean();
			m_NarcoticArchive->m_CustomerSupplierStreet.setClean();
			m_NarcoticArchive->m_DeletedFlag.setClean();
			m_NarcoticArchive->m_ForeName.setClean();
			m_NarcoticArchive->m_NarcGroup.setClean();
			m_NarcoticArchive->m_NarcName.setClean();
			m_NarcoticArchive->m_NarcUnit.setClean();
			m_NarcoticArchive->m_ProcessedFlag.setClean();
			m_NarcoticArchive->m_Surname.setClean();
			m_NarcoticArchive->m_TourId.setClean();
			m_NarcoticArchive->m_Username.setClean();
		}

	} // end namespace document
} // end namespace libcsc
