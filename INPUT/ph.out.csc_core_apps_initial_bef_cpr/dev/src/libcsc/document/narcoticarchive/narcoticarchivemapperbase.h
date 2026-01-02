#ifndef GUARD_LIBCSC_DOCUMENT_NARCOTICARCHIVEMAPPER_BASE_H
#define GUARD_LIBCSC_DOCUMENT_NARCOTICARCHIVEMAPPER_BASE_H

#include <libbasar_definitions.h>
#include "narcoticarchiveptr.h"
#include <types/transactiontypeenum.inc>

namespace libcsc 
{
	namespace document 
	{
		class NarcoticArchiveMapperBase
		{
		public:
			NarcoticArchiveMapperBase(NarcoticArchivePtr narcoticArchivePtr);

			void			map();
		protected:
			virtual ~NarcoticArchiveMapperBase();

			virtual void	doMap() = 0;

			void	setAcknowledgementStatus(const basar::Int16& acknowledgementStatus);
			void	setArticleNo(const basar::Int32& articleNo);
			void	setBranchNo(const basar::Int16& branchNo);
			void	setCatalogId(const basar::Int32& CatalogId);
			void	setContributionVoucherNo(const basar::Int32& contributionVoucherNo);
			void	setContributionVoucherTransferDate(const basar::DateTime& contributionVoucherTransferDate);
			void	setContributionVoucherTransferStatus(const basar::Int16& contributionVoucherTransferStatus);
			void	setCustomerSupplierCip(const basar::VarString& customerSupplierCip);
			void	setCustomerSupplierCity(const basar::VarString& customerSupplierCity);
			void	setCustomerSupplierName(const basar::VarString& customerSupplierName);
			void	setCustomerSupplierNo(const basar::Int32& customerSupplierNo);
			void	setCustomerSupplierStreet(const basar::VarString& customerSupplierStreet);
			void	setDeletedFlag(const basar::VarString& celetedFlag);
			void  	setDeliveryNoteCopyTransferDate(const basar::DateTime& deliveryNoteCopyTransferDate);
			void	setDeliveryNoteCopyTransferStatus(const basar::Int16& celiveryNoteCopyTransferStatus);
			void	setForeName(const basar::VarString& foreName);
			void	setInvoiceNo(const basar::Int32& invoiceNo);
			void	setNarcFactor(const basar::Decimal& narcFactor);
			void	setNarcGroup(const basar::VarString& narcGroup);
			void	setNarcName(const basar::VarString& narcName);
			void	setNarcPotency(const basar::Decimal& narcPotency);
			void	setNarcUnit(const basar::VarString& narcUnit);
			void	setPrintedDate(const basar::Int32& printedDate);
			void	setPrintedTime(const basar::Int32& printedTime);
			void	setProcessedFlag(const basar::VarString& processedFlag);
			void	setPurchaseOrderNo(const basar::Int32& purchaseOrderNo);
			void	setQtyInstock(const basar::Int32& qtyInstock);
			void	setQtyTransaction(const basar::Int32& qtyTransaction);
			void	setSurname(const basar::VarString& surname);
			void	setTourId(const basar::VarString& tourId);
			void	setTransactionDate(const basar::Int32& transactionDate);
			void	setTransactionTime(const basar::Int32& transactionTime);
			void	setTransactionType(const TransactionTypeEnum& transactionType);
			void	setUsername(const basar::VarString& username);
			void	setWarehouseOrderNo(const basar::Int32& warehouseOrderNo);

			virtual void	setClean();
			//private:
			NarcoticArchivePtr m_NarcoticArchive;
		};

	} // end namespace document
} // end namespace libcsc

#endif // GUARD_LIBCSC_DOCUMENT_NARCOTICARCHIVEMAPPER_BASE_H
