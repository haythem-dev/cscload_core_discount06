//-------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief Domain module article
 *  \author
 *  \date
 */
//-------------------------------------------------------------------------------------------------//
#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_CORE_TRANSACTION_RECORD_BASE_H
#define GUARD_DOMMOD_PHARMOSTRANSACTION_CORE_TRANSACTION_RECORD_BASE_H

//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include <classinfo_macros.h>
#include <libbasardbaspect.h>
#include "transactionrecordbaseptr.h"
#include "irecordtypeof.h"
#include <accessorinstancerefwrapper.h>
#include <icsc_loggerptr.h>

#include <iloggable.h>

//--------------------------------------------------------------------------------------------------//
// forward declaration section
//--------------------------------------------------------------------------------------------------//

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
class TransactionRecordBase : public IRecordTypeOf,
                              public libcsc_utils::ILoggable
{
    friend class TransactionDMBase;
    friend class CICSPharmosTransactionDM;

//--------------------------------------------------------------------------------------------------//
// object declaration section
//--------------------------------------------------------------------------------------------------//
public:
    ~TransactionRecordBase();

    virtual void                                    startProcessing() = 0;
    virtual void                                    finishProcessing() = 0;
    void                                            save();
    void                                            markAsProcessed();
    bool                                            wasProcessable();
    virtual void                                    log() = 0;

    virtual bool                                    hasFollowUpRecord();
    virtual bool                                    hasCMIFlag();

    //////////////////////////////////////////////////////////////////////////////////////////
    // IRecordTypeOf
    virtual bool                                    isTypeOf_ChangeOrderItem() const;
    virtual bool                                    isTypeOf_ArticleInfoGoodsIn() const;
    virtual bool                                    isTypeOf_StopSellingOfArticle() const;
    virtual bool                                    isTypeOf_ChangeIBTStockLevel() const;
    virtual bool                                    isTypeOf_ChangeQuarantine() const;
    virtual bool                                    isTypeOf_CodeBlocage() const;
    virtual bool                                    isTypeOf_Batch() const;
    virtual bool                                    isTypeOf_DealerVolumeTotal() const;
    virtual bool                                    isTypeOf_DealerVolumeElectronic() const;
    virtual bool                                    isTypeOf_DealerVolumeExclusiveTotal() const;
    virtual bool                                    isTypeOf_DealerVolumeExclusiveElectronic() const;
    virtual bool                                    isTypeOf_CreditLimitChain() const;
    virtual bool                                    isTypeOf_CreditLimitCustomer() const;
    virtual bool                                    isTypeOf_CreditLimitCustomerReturn() const;
    virtual bool                                    isTypeOf_CreditLimitGroup() const;
    virtual bool                                    isTypeOf_CreditLimit() const;
    virtual bool                                    isTypeOf_DiscountAccount() const;
    virtual bool                                    isTypeOf_ExpiryDate() const;
    virtual bool                                    isTypeOf_ChangeArticleDetails() const;
    virtual bool                                    isTypeOf_CustomerReturn() const;
    virtual bool                                    isTypeOf_ImportInvoiceNo() const;
    virtual bool                                    isTypeOf_TransferQuarantine() const;
    virtual bool                                    isTypeOf_GoodsIn() const;
    virtual bool                                    isTypeOf_TenderChangeCustomerReturn() const;
    virtual bool                                    isTypeOf_PickingLack() const;
    virtual bool                                    isTypeOf_StorageReconciliation() const;
    virtual bool                                    isTypeOf_BatchInconsistency() const;
    virtual bool                                    isTypeOf_PerpetualStocktaking() const;
    virtual bool                                    isTypeOf_StorageReconciliationPrewholesale() const;
    virtual bool                                    isTypeOf_InvoiceCancellation() const;
    virtual bool                                    isTypeOf_ChangeArticleMasterData() const;
    virtual bool                                    isTypeOf_IBTGoods() const;
    virtual bool                                    isTypeOf_OTHER() const;

    //////////////////////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////////////////////
    // getter for properties for CICSPharmosTransactionRecord
    virtual basar::DateTime                         getKbvzDX01DateTime() const;
    virtual basar::Int32                            getKbvzDX01Date() const;
    virtual basar::Int32                            getKbvzOffset() const;
    virtual basar::VarString                        getKbvzKSC() const;
    virtual basar::Int32                            getKbvzKSCTime() const;
    virtual basar::Int32                            getKbvzDX01Time() const;
    virtual basar::Int32                            getKbvzLfdNr() const;
    virtual basar::Int16                            getKbvzFil() const;
    virtual basar::Int32                            getKbvzPZN() const;
    virtual basar::Int32                            getKbvzMeng() const;
    virtual basar::Int16                            getKbvzBukz() const;
    virtual basar::Int32                            getKbvzTime() const;
    virtual basar::Int32                            getKbvzDate() const;
    virtual basar::VarString                        getKbvzLgfnr() const;
    virtual basar::Int32                            getKbvzKSCAnr() const;
    virtual basar::VarString                        getKbvzLgnr() const;
    virtual basar::VarString                        getKbvzStat() const;
    virtual basar::VarString                        getKbvzET3() const;
    virtual basar::VarString                        getKbvzWber() const;
    virtual basar::Int32                            getKbvzVerf() const;
    virtual basar::Int32                            getKbvzP1Pos() const;
    virtual basar::Decimal                          getKbvzGEP() const;
    virtual basar::Decimal                          getKbvzAEP() const;
    virtual basar::Decimal                          getKbvzAVP() const;
    virtual basar::VarString                        getKbvzKVerf() const;
    virtual basar::VarString                        getKbvzKLgfnr() const;
    virtual basar::VarString                        getKbvzKGEP() const;
    virtual basar::VarString                        getKbvzKAEP() const;
    virtual basar::VarString                        getKbvzKAVP() const;
    virtual basar::Int16                            getKbvzMFil() const;
    virtual basar::VarString                        getKbvzStatus() const;
    virtual basar::VarString                        getKbvzExport() const;
    virtual basar::Decimal                          getKbvzWert() const;
    virtual basar::VarString                        getKbvzCloSa() const;
    virtual basar::VarString                        getKbvzCloZeit() const;
    virtual basar::Int32                            getKbvzCloAnr() const;
    virtual basar::Int32                            getKbvzCloPos() const;
    virtual basar::VarString                        getKbvzCharge() const;
    virtual basar::VarString                        getKbvzBatch() const;
    virtual basar::Int32                            getKbvzDailyClosing() const;
    virtual basar::Int32                            getKbvzBeslaNr() const;
    //////////////////////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////////////////////
    // getter for properties for PharmosTransactionRecord
    virtual basar::Int16                            getBranchNo() const;
    virtual basar::DateTime                         getCreationDateTime() const;
    virtual basar::Int32                            getVSEOffset() const;
    virtual basar::VarString                        getProcessingState() const;
    virtual basar::DateTime                         getProcessedTimestamp() const;
    virtual basar::DateTime                         getTransferredTimestamp() const;
    virtual basar::Int32                            getDatasetSequenceNo() const;
    virtual basar::VarString                        getCustomerNo() const;
    virtual basar::Int16                            getBookingType() const;
    virtual basar::Int32                            getUserId() const;
    virtual basar::VarString                        getInvoiceNo() const;
    virtual basar::DateTime                         getInvoiceDateTime() const;
    virtual basar::Date                             getInvoiceDate() const;
    virtual basar::Int32                            getCustomerOrderNo() const;
    virtual basar::VarString                        getCSCOrderNo() const;
    virtual basar::Decimal                          getTurnover() const;
    virtual basar::Date                             getPaymentDate() const;
    virtual basar::VarString                        getPaymentType() const;
    virtual basar::VarString                        getPriceType() const;
    virtual basar::Int32                            getChainNo() const;
    virtual basar::Decimal                          getRemainingDiscAccValue() const;
    virtual basar::Decimal                          getInvoiceValue() const;
    virtual basar::Int32                            getDiscAccOperationNo() const;
    virtual basar::Int32                            getPriority() const;
    virtual basar::VarString                        getVoucherType() const;
    virtual basar::Int32                            getArticleNo() const;
    virtual basar::VarString                        getBatch() const;
    virtual basar::Date                             getExpiryDate() const;
    virtual basar::Int32                            getQuantity() const;
    virtual basar::Decimal                          getDebitValue() const;
    virtual basar::Decimal                          getLimitValue() const;
    virtual basar::Int32                            getSupplierNo() const;
    virtual basar::VarString                        getPurchaseOrderNo() const;
    virtual basar::Decimal                          getCostPrice() const;
    virtual basar::VarString                        getStorageLocation() const;
    virtual basar::VarString                        getStorageArea() const;
    virtual basar::VarString                        getStationNo() const;
    virtual basar::Int16                            getExpiryDateChangeFlag() const;
    virtual basar::Int16                            getStorageLocationChangeFlag() const;
    virtual basar::Int16                            getCostPriceChangeFlag() const;
    virtual basar::Int16                            getPharmacyPurchasePriceChangeFlag() const;
    virtual basar::Int16                            getPharmacySellPriceChangeFlag() const;
    virtual basar::Decimal                          getPharmacyPurchasePrice() const;
    virtual basar::Decimal                          getPharmacySellPrice() const;
    virtual basar::Int16                            getIbtBranchNo() const;
    virtual basar::VarString                        getCodeBlocage() const;
    virtual basar::Int32                            getQuantityNatra() const;
    virtual basar::Int32                            getOrderPositionNo() const;
    virtual basar::Int32                            getDailyClosing() const;
    virtual basar::Int16                            getOrigin() const;
    virtual basar::Int32                            getOrderSupplierNo() const;
    //////////////////////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////////////////////
    // setter for properties for PharmosTransactionRecord
    virtual void                                    setBranchNo(const basar::Int16 val);
    virtual void                                    setCreationDateTime(const basar::DateTime& val);
    virtual void                                    setVSEOffset(const basar::Int32 val);
    virtual void                                    setProcessedTimestamp(const basar::DateTime& val);
    virtual void                                    setTransferredTimestamp(const basar::DateTime& val);
    virtual void                                    setDatasetSequenceNo(const basar::Int32 val);
    virtual void                                    setRecordType(const basar::VarString& val);
    virtual void                                    setCustomerNo(const basar::VarString& val);
    virtual void                                    setBookingType(const basar::Int16 val);
    virtual void                                    setUserId(const basar::Int32 val);
    virtual void                                    setInvoiceNo(const basar::VarString& val);
    virtual void                                    setInvoiceDateTime(const basar::DateTime& val);
    virtual void                                    setCustomerOrderNo(const basar::Int32 val);
    virtual void                                    setCSCOrderNo(const basar::VarString& val);
    virtual void                                    setTurnover(const basar::Decimal& val);
    virtual void                                    setPaymentDate(const basar::Date& val);
    virtual void                                    setPaymentType(const basar::VarString& val);
    virtual void                                    setPriceType(const basar::VarString& val);
    virtual void                                    setChainNo(const basar::Int32 val);
    virtual void                                    setRemainingDiscAccValue(const basar::Decimal& val);
    virtual void                                    setInvoiceValue(const basar::Decimal& val);
    virtual void                                    setDiscAccOperationNo(const basar::Int32 val);
    virtual void                                    setPriority(const basar::Int32 val);
    virtual void                                    setVoucherType(const basar::VarString& val);
    virtual void                                    setArticleNo(const basar::Int32 val);
    virtual void                                    setBatch(const basar::VarString& val);
    virtual void                                    setExpiryDate(const basar::Date& val);
    virtual void                                    setQuantity(const basar::Int32 val);
    virtual void                                    setDebitValue(const basar::Decimal& val);
    virtual void                                    setLimitValue(const basar::Decimal& val);
    virtual void                                    setSupplierNo(const basar::Int32 val);
    virtual void                                    setPurchaseOrderNo(const basar::VarString& val);
    virtual void                                    setCostPrice(const basar::Decimal& val);
    virtual void                                    setStorageLocation(const basar::VarString& val);
    virtual void                                    setStorageArea(const basar::VarString& val);
    virtual void                                    setStationNo(const basar::VarString& val);
    virtual void                                    setExpiryDateChangeFlag(const basar::Int16 val);
    virtual void                                    setStorageLocationChangeFlag(const basar::Int16 val);
    virtual void                                    setCostPriceChangeFlag(const basar::Int16 val);
    virtual void                                    setPharmacyPurchasePriceChangeFlag(const basar::Int16 val);
    virtual void                                    setPharmacySellPriceChangeFlag(const basar::Int16 val);
    virtual void                                    setPharmacyPurchasePrice(const basar::Decimal& val);
    virtual void                                    setPharmacySellPrice(const basar::Decimal& val);
    virtual void                                    setIbtBranchNo(const basar::Int16 val);
    virtual void                                    setCodeBlocage(const basar::VarString& val);
    virtual void                                    setQuantityNatra(const basar::Int32 val);
    virtual void                                    setOrderPositionNo(const basar::Int32 val);
    virtual void                                    setDailyClosing(const basar::Int32 val);
    virtual void                                    setOrigin(const basar::Int16 val);
    virtual void                                    setOrderSupplierNo(const basar::Int32 val);
    //////////////////////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////////////////////
    // getter for properties for CTransferCscTransactionRecord
    virtual basar::Int32                            getTransferId() const;
    virtual basar::DateTime                         getEntryDateTime() const;
    virtual basar::VarString                        getFieldName() const;
    virtual basar::VarString                        getFieldValue() const;
    virtual basar::Int32                            getProcessedFlag() const;


    bool                                          isEnd() const;

public:
    TransactionRecordBase( basar::db::aspect::AccessorPropertyTable_YIterator yitTransactionRecord, AccessorInstanceRefWrapper& acc, libcsc_utils::ICSC_LoggerPtr csc_logger );
    virtual basar::VarString                getType() const = 0;
    virtual basar::VarString                getLogMessage() const;
    void                                                setTransactionRecord( basar::db::aspect::AccessorPropertyTable_YIterator yitTransactionRecord );
    basar::db::aspect::AccessorPropertyTable_YIterator  getTransactionRecord();

protected:

    basar::db::aspect::AccessorPropertyTable_YIterator  m_YitTransactionRecord;
    libcsc_utils::ICSC_LoggerPtr                        m_CSC_Logger;

    virtual const basar::VarString&                     getSaveAccessMethod() const = 0;

    virtual const log4cplus::Logger&                    getLogger() const;

private:
    /////////////////////////////////////////////////////////////////////////
    // private member methods
    /////////////////////////////////////////////////////////////////////////
    TransactionRecordBase            ( const TransactionRecordBase& );
    TransactionRecordBase& operator= ( const TransactionRecordBase& );


    virtual basar::VarString                        getRecordType() const;
    virtual basar::VarString                        getKbvzArt() const;

    AccessorInstanceRefWrapper&                         m_Accessor;
    bool                                                m_wasProcessed;
};

} // namespace core
} // namespace pharmosTransaction
} // end namespace domMod

#endif

