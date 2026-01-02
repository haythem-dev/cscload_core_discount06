#ifndef GUARD_LIBCSC_DOCUMENT_NARCOTICARCHIVE_H
#define GUARD_LIBCSC_DOCUMENT_NARCOTICARCHIVE_H

#include <datatypes/boolean.h>
#include <datatypes/int16.h>
#include <datatypes/int32.h>
#include <datatypes/date.h>
#include <datatypes/datetime.h>
#include <datatypes/varstring.h>
#include <datatypes/decimal.h>

#include <types/transactiontypeenum.inc>

namespace libcsc 
{
	namespace document 
	{

		typedef Property<TransactionTypeEnum>TransactionType;

		class NarcoticArchive
		{
			friend class NarcoticArchiveMapperBase;
			friend class NarcoticArchiveSQLMapper;

		public:
			NarcoticArchive();
			virtual ~NarcoticArchive();

			virtual const basar::Int16& getAcknowledgementStatus() const;
			virtual const basar::Int32& getArticleNo() const;
			virtual const basar::Int16& getBranchNo() const;
			virtual const basar::Int32& getCatalogId() const;
			virtual const basar::Int32& getContributionVoucherNo() const;
			virtual const basar::DateTime& getContributionVoucherTransferDate() const;
			virtual const basar::Int16& getContributionVoucherTransferStatus() const;
			virtual const basar::VarString& getCustomerSupplierCip() const;
			virtual const basar::VarString& getCustomerSupplierCity() const;
			virtual const basar::VarString& getCustomerSupplierName() const;
			virtual const basar::Int32& getCustomerSupplierNo() const;
			virtual const basar::VarString& getCustomerSupplierStreet() const;
			virtual const basar::VarString& getDeletedFlag() const;
			virtual const basar::DateTime& getDeliveryNoteCopyTransferDate() const;
			virtual const basar::Int16& getDeliveryNoteCopyTransferStatus() const;
			virtual const basar::VarString& getForeName() const;
			virtual const basar::Int32& getInvoiceNo() const;
			virtual const basar::Decimal& getNarcFactor() const;
			virtual const basar::VarString& getNarcGroup() const;
			virtual const basar::VarString& getNarcName() const;
			virtual const basar::Decimal& getNarcPotency() const;
			virtual const basar::VarString& getNarcUnit() const;
			virtual const basar::Int32& getPrintedDate() const;
			virtual const basar::Int32& getPrintedTime() const;
			virtual const basar::VarString& getProcessedFlag() const;
			virtual const basar::Int32& getPurchaseOrderNo() const;
			virtual const basar::Int32& getQtyInstock() const;
			virtual const basar::Int32& getQtyTransaction() const;
			virtual const basar::VarString& getSurname() const;
			virtual const basar::VarString& getTourId() const;
			virtual const basar::Int32& getTransactionDate() const;
			virtual const basar::Int32& getTransactionTime() const;
			virtual const TransactionTypeEnum& getTransactionType() const;
			virtual const basar::VarString& getUsername() const;
			virtual const basar::Int32& getWarehouseOrderNo() const;

			virtual void setAcknowledgementStatus(const basar::Int16& value);
			virtual void setArticleNo(const basar::Int32& value);
			virtual void setBranchNo(const basar::Int16& value);
			virtual void setCatalogId(const basar::Int32& value);
			virtual void setContributionVoucherNo(const basar::Int32& value);
			virtual void setContributionVoucherTransferDate(const basar::DateTime& value);
			virtual void setContributionVoucherTransferStatus(const basar::Int16& value);
			virtual void setCustomerSupplierCip(const basar::VarString& value);
			virtual void setCustomerSupplierCity(const basar::VarString& value);
			virtual void setCustomerSupplierName(const basar::VarString& value);
			virtual void setCustomerSupplierNo(const basar::Int32& value);
			virtual void setCustomerSupplierStreet(const basar::VarString& value);
			virtual void setDeletedFlag(const basar::VarString& value);
			virtual void setDeliveryNoteCopyTransferDate(const basar::DateTime& value);
			virtual void setDeliveryNoteCopyTransferStatus(const basar::Int16& value);
			virtual void setForeName(const basar::VarString& value);
			virtual void setInvoiceNo(const basar::Int32& value);
			virtual void setNarcFactor(const basar::Decimal& value);
			virtual void setNarcGroup(const basar::VarString& value);
			virtual void setNarcName(const basar::VarString& value);
			virtual void setNarcPotency(const basar::Decimal& value);
			virtual void setNarcUnit(const basar::VarString& value);
			virtual void setPrintedDate(const basar::Int32& value);
			virtual void setPrintedTime(const basar::Int32& value);
			virtual void setProcessedFlag(const basar::VarString& value);
			virtual void setPurchaseOrderNo(const basar::Int32& value);
			virtual void setQtyInstock(const basar::Int32&);
			virtual void setQtyTransaction(const basar::Int32& value);
			virtual void setSurname(const basar::VarString& value);
			virtual void setTourId(const basar::VarString& value);
			virtual void setTransactionDate(const basar::Int32& value);
			virtual void setTransactionTime(const basar::Int32& value);
			virtual void setTransactionType(const TransactionTypeEnum& value);
			virtual void setUsername(const basar::VarString& value);
			virtual void setWarehouseOrderNo(const basar::Int32& value);

			virtual bool isClean();
			virtual bool isDirty();
			virtual void setClean();

		protected:

		private:

			libcsc::Int16      	m_AcknowledgementStatus;
			libcsc::Int32      	m_ArticleNo;
			libcsc::Int16      	m_BranchNo;
			libcsc::Int32       m_CatalogId;
			libcsc::Int32      	m_ContributionVoucherNo;
			libcsc::DateTime    m_ContributionVoucherTransferDate;
			libcsc::Int16      	m_ContributionVoucherTransferStatus;
			libcsc::VarString   m_CustomerSupplierCip;
			libcsc::VarString   m_CustomerSupplierCity;
			libcsc::VarString   m_CustomerSupplierName;
			libcsc::Int32      	m_CustomerSupplierNo;
			libcsc::VarString   m_CustomerSupplierStreet;
			libcsc::VarString   m_DeletedFlag;
			libcsc::DateTime    m_DeliveryNoteCopyTransferDate;
			libcsc::Int16      	m_DeliveryNoteCopyTransferStatus;
			libcsc::VarString   m_ForeName;
			libcsc::Int32      	m_InvoiceNo;
			libcsc::Decimal     m_NarcFactor;
			libcsc::VarString   m_NarcGroup;
			libcsc::VarString   m_NarcName;
			libcsc::Decimal     m_NarcPotency;
			libcsc::VarString   m_NarcUnit;
			libcsc::Int32      	m_PrintedDate;
			libcsc::Int32      	m_PrintedTime;
			libcsc::VarString   m_ProcessedFlag;
			libcsc::Int32      	m_PurchaseOrderNo;
			libcsc::Int32      	m_QtyInstock;
			libcsc::Int32      	m_QtyTransaction;
			libcsc::VarString   m_Surname;
			libcsc::VarString   m_TourId;
			libcsc::Int32      	m_TransactionDate;
			libcsc::Int32      	m_TransactionTime;
			TransactionType		m_TransactionType;
			libcsc::VarString   m_Username;
			libcsc::Int32      	m_WarehouseOrderNo;
		};
	} // namespace document
} // namespace libcsc

#endif // GUARD_LIBCSC_DOCUMENT_NARCOTICARCHIVE_H
