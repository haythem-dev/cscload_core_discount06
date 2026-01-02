//-------------------------------------------------------------------------------------------------//
/*! \file transactionrecordbase.h
 *  \brief container for informix pharmos transaction record
 *  \author Julian Machata
 *  \date 27.06.2012
 */
//-------------------------------------------------------------------------------------------------//
#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_PREPARATION_PHARMOSTRANSACTIONRECORD_H
#define GUARD_DOMMOD_PHARMOSTRANSACTION_PREPARATION_PHARMOSTRANSACTIONRECORD_H

//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include "transactionrecordbase.h"
#include <icsc_loggerptr.h>

//--------------------------------------------------------------------------------------------------//
// forward declaration section
//--------------------------------------------------------------------------------------------------//
namespace basar
{
	namespace db
	{
		namespace aspect
		{
            //class AccessorInstanceRef;
			//class ConnectionRef;
			class AccessorPropertyTable_YIterator;
			//class AccessorPropertyTableRef;
		}
	}
}

//-------------------------------------------------------------------------------------------------//
// namespace section
//-------------------------------------------------------------------------------------------------//
namespace domMod
{
namespace pharmosTransaction
{
namespace core
{
    //-------------------------------------------------------------------------------------------------//
    // class declaration section
    //-------------------------------------------------------------------------------------------------//
    /*!\brief  */
	class PharmosTransactionRecord : public core::TransactionRecordBase
	{
        public:
		    struct ProcessingStatus
		    {
			    static basar::ConstString OPEN; // ( "O" );
			    static basar::ConstString IN_PROCESS; // ( "I" );
			    static basar::ConstString CLOSED; // ( "C" );
		    };
			struct Origin
			{
				static basar::Int16 PHARMOS;
				static basar::Int16 ZDP;
			};

        //--------------------------------------------------------------------------------------------------//
        // object declaration section
        //--------------------------------------------------------------------------------------------------//
	    public:
			PharmosTransactionRecord( basar::db::aspect::AccessorPropertyTable_YIterator yitTransactionRecord, AccessorInstanceRefWrapper& acc, libcsc_utils::ICSC_LoggerPtr csc_logger );
		    ~PharmosTransactionRecord();

            virtual void                                        startProcessing();
            virtual void                                        finishProcessing();

            virtual void                                        log();

			virtual basar::Int16							getBranchNo() const;
			virtual basar::DateTime							getCreationDateTime() const;
			virtual basar::Int32							getVSEOffset() const;
			virtual basar::VarString						getProcessingState() const;
			virtual basar::DateTime							getProcessedTimestamp() const;
			virtual basar::DateTime							getTransferredTimestamp() const;
			virtual basar::Int32							getDatasetSequenceNo() const;
			virtual basar::VarString						getCustomerNo() const;
			virtual basar::Int16							getBookingType() const;
			virtual basar::Int32							getUserId() const;
			virtual basar::VarString						getInvoiceNo() const;
			virtual basar::DateTime							getInvoiceDateTime() const;
			virtual basar::Int32							getCustomerOrderNo() const;
			virtual basar::VarString						getCSCOrderNo() const;
			virtual basar::Decimal							getTurnover() const;
			virtual basar::Date								getPaymentDate() const;
			virtual basar::VarString						getPaymentType() const;
			virtual basar::VarString						getPriceType() const;
			virtual basar::Int32							getChainNo() const;
			virtual basar::Decimal							getRemainingDiscAccValue() const;
			virtual basar::Decimal							getInvoiceValue() const;
			virtual basar::Int32							getDiscAccOperationNo() const;
			virtual basar::Int32							getPriority() const;
			virtual basar::VarString						getVoucherType() const;
			virtual basar::Int32							getArticleNo() const;
			virtual basar::VarString						getBatch() const;
			virtual basar::Date								getExpiryDate() const;
			virtual basar::Int32							getQuantity() const;
			virtual basar::Decimal							getDebitValue() const;
			virtual basar::Decimal							getLimitValue() const;
			virtual basar::Int32							getSupplierNo() const;
			virtual basar::VarString						getPurchaseOrderNo() const;
			virtual basar::Decimal							getCostPrice() const;
			virtual basar::VarString						getStorageLocation() const;
			virtual basar::VarString						getStorageArea() const;
			virtual basar::VarString						getStationNo() const;
			virtual basar::Int16							getExpiryDateChangeFlag() const;
			virtual basar::Int16							getStorageLocationChangeFlag() const;
			virtual basar::Int16							getCostPriceChangeFlag() const;
			virtual basar::Int16							getPharmacyPurchasePriceChangeFlag() const;
			virtual basar::Int16							getPharmacySellPriceChangeFlag() const;
			virtual basar::Decimal							getPharmacyPurchasePrice() const;
			virtual basar::Decimal							getPharmacySellPrice() const;
			virtual basar::Int16							getIbtBranchNo() const;
			virtual basar::VarString						getCodeBlocage() const;
			virtual basar::Int32							getQuantityNatra() const;
			virtual basar::Int32							getOrderPositionNo() const;
			virtual basar::Int32							getDailyClosing() const;
			virtual basar::Int16							getOrigin() const;
			virtual basar::Int32							getOrderSupplierNo() const;


			virtual void										setBranchNo(const basar::Int16 val);
			virtual void										setCreationDateTime(const basar::DateTime& val);
			virtual void										setVSEOffset(const basar::Int32 val);
			virtual void 										setProcessedTimestamp(const basar::DateTime& val);
			virtual void										setTransferredTimestamp(const basar::DateTime& val);
			virtual void										setDatasetSequenceNo(const basar::Int32 val);
			virtual void										setRecordType(const basar::VarString& val);
			virtual void										setCustomerNo(const basar::VarString& val);
			virtual void										setBookingType(const basar::Int16 val);
			virtual void										setUserId(const basar::Int32 val);
			virtual void										setInvoiceNo(const basar::VarString& val);
			virtual void										setInvoiceDateTime(const basar::DateTime& val);
			virtual void										setCustomerOrderNo(const basar::Int32 val);
			virtual void										setCSCOrderNo(const basar::VarString& val);
			virtual void 										setTurnover(const basar::Decimal& val);
			virtual void										setPaymentDate(const basar::Date& val);
			virtual void										setPaymentType(const basar::VarString& val);
			virtual void										setPriceType(const basar::VarString& val);
			virtual void										setChainNo(const basar::Int32 val);
			virtual void										setRemainingDiscAccValue(const basar::Decimal& val);
			virtual void										setInvoiceValue(const basar::Decimal& val);
			virtual void 										setDiscAccOperationNo(const basar::Int32 val);
			virtual void										setPriority(const basar::Int32 val);
			virtual void										setVoucherType(const basar::VarString& val);
			virtual void										setArticleNo(const basar::Int32 val);
			virtual void										setBatch(const basar::VarString& val);
			virtual void										setExpiryDate(const basar::Date& val);
			virtual void										setQuantity(const basar::Int32 val);
			virtual void										setDebitValue(const basar::Decimal& val);
			virtual void										setLimitValue(const basar::Decimal& val);
			virtual void										setSupplierNo(const basar::Int32 val);
			virtual void										setPurchaseOrderNo(const basar::VarString& val);
			virtual void										setCostPrice(const basar::Decimal& val);
			virtual void										setStorageLocation(const basar::VarString& val);
			virtual void										setStorageArea(const basar::VarString& val);
			virtual void										setStationNo(const basar::VarString& val);
			virtual void										setExpiryDateChangeFlag(const basar::Int16 val);
			virtual void										setStorageLocationChangeFlag(const basar::Int16 val);
			virtual void										setCostPriceChangeFlag(const basar::Int16 val);
			virtual void										setPharmacyPurchasePriceChangeFlag(const basar::Int16 val);
			virtual void										setPharmacySellPriceChangeFlag(const basar::Int16 val);
			virtual void										setPharmacyPurchasePrice(const basar::Decimal& val);
			virtual void										setPharmacySellPrice(const basar::Decimal& val);
			virtual void										setIbtBranchNo(const basar::Int16 val);
			virtual void										setCodeBlocage(const basar::VarString& val);
			virtual void										setQuantityNatra(const basar::Int32 val);
			virtual void										setOrderPositionNo(const basar::Int32 val);
			virtual void										setDailyClosing(const basar::Int32 val);
			virtual void										setOrigin(const basar::Int16 val);
			virtual void										setOrderSupplierNo(const basar::Int32 val);

			virtual basar::VarString							getType() const;

		protected:
			virtual const basar::VarString&						getSaveAccessMethod() const;

	    private:
            /////////////////////////////////////////////////////////////////////////
		    // private member methods
		    /////////////////////////////////////////////////////////////////////////
		    PharmosTransactionRecord            ( const PharmosTransactionRecord& );
		    PharmosTransactionRecord& operator= ( const PharmosTransactionRecord& );

			void												setProcessingStateOpen();
			void												setProcessingStateInProcess();
			void												setProcessingStateClosed();

			virtual basar::VarString						getRecordType() const;
	};
} // namespace core
} // namespace pharmosTransaction
} // end namespace domMod

#endif // GUARD_DOMMOD_PHARMOSTRANSACTION_PREPARATION_PHARMOSTRANSACTIONRECORD_H

