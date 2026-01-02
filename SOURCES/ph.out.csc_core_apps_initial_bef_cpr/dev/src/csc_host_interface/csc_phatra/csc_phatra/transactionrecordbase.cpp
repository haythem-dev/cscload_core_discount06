//-------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief Domain module article
 *  \author
 *  \date
 */
//-------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include <libbasardbaspect.h>
#include <libbasarproperty.h>
#include <transactionguard.h>
#include <executeerrorenum2stringmapper.h>
#include <exceptionhandler.h>
#include <accessorexecutionexception.h>
#include "transactionrecordbase.h"
#include "recordtypeclassifier.h"
#include "accessorinstancerefwrapper.h"
#include "methodcallnotsupportedexception.h"
#include <icsc_logger.h>
#include <iomanip>

#ifdef WIN32
    //#pragma warning (push)
        #pragma warning(disable: 4702)
    //#pragma warning (pop)
#endif

//-------------------------------------------------------------------------------------------------//
// class definition section
//-------------------------------------------------------------------------------------------------//
namespace domMod
{
namespace pharmosTransaction
{
namespace core
{
    //--------------------------------------------------------------------------------------------------//
    // object definition section
    //--------------------------------------------------------------------------------------------------//
    TransactionRecordBase::TransactionRecordBase( basar::db::aspect::AccessorPropertyTable_YIterator yitTransactionRecord, AccessorInstanceRefWrapper& acc, libcsc_utils::ICSC_LoggerPtr csc_logger )
        : m_YitTransactionRecord( yitTransactionRecord ),
        m_CSC_Logger( csc_logger ),
        m_Accessor( acc ),
        m_wasProcessed(false)
    {
        METHODNAME_DEF( TransactionRecordBase, TransactionRecordBase )
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
    }

    TransactionRecordBase::~TransactionRecordBase()
    {
        METHODNAME_DEF( TransactionRecordBase, ~TransactionRecordBase )
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
    }

    bool TransactionRecordBase::wasProcessable()
    {
        METHODNAME_DEF( TransactionRecordBase, wasProcessable )
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

        return m_wasProcessed;
    }

    void TransactionRecordBase::markAsProcessed()
    {
        METHODNAME_DEF( TransactionRecordBase, markAsProcessed )
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

        m_wasProcessed = true;
    }

    basar::VarString TransactionRecordBase::getLogMessage() const
    {
        std::stringstream ss; ss << ": ";
        if( m_YitTransactionRecord.isNull() ){
            ss << "YIterator is Null()!";
        } else if( m_YitTransactionRecord.isEnd() ){
            ss << "YIterator is empty()!";
        } else {
            ss << std::endl;
            basar::db::aspect::AccessorPropertyTableRef propTab = m_YitTransactionRecord.getPropertyTable();
            basar::db::aspect::PropertyDescriptionListRef descriptList =
                propTab.getPropertyDescriptionList();
            basar::db::aspect::AccessorPropertyTable_XIterator xit = m_YitTransactionRecord.begin();
            basar::I18nString value = "";
            for( int i = 1; !xit.isEnd(); ++xit, ++i ){
                value = "";
                if( basar::SS_UNSET != xit.getState().getState() ){
                    value = xit.getSQLString();
                }
                ss << std::left << std::setw(2) << i << ". " << xit.getName() << "(>" << value << "<, "
                    << xit.getState().toString() << ")" << std::endl;
            }
        }

        return ss.str().c_str();
    }


    void TransactionRecordBase::setTransactionRecord( basar::db::aspect::AccessorPropertyTable_YIterator yitTransactionRecord )
    {
        METHODNAME_DEF( TransactionRecordBase, setTransactionRecord )
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
        m_YitTransactionRecord = yitTransactionRecord;
    }

    basar::db::aspect::AccessorPropertyTable_YIterator TransactionRecordBase::getTransactionRecord()
    {
        METHODNAME_DEF( TransactionRecordBase, getTransactionRecord )
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
        return m_YitTransactionRecord;
    }

    bool TransactionRecordBase::isEnd() const
    {
        METHODNAME_DEF( TransactionRecordBase, isEnd )
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
        return m_YitTransactionRecord.isEnd();
    }

    bool TransactionRecordBase::hasFollowUpRecord()
    {
        return "N" == getStorageArea();
    }

    //the CMI flag 'C' is set in the storage location (bvz-lgnr)
    bool TransactionRecordBase::hasCMIFlag()
    {
        return "C" == getStorageArea();
    }

    bool TransactionRecordBase::isTypeOf_StorageReconciliation() const
    {
        RecordTypeClassifier recordTypeClassifier( getType() );
        return recordTypeClassifier.isTypeOf_StorageReconciliation();
    }

    bool TransactionRecordBase::isTypeOf_BatchInconsistency() const
    {
        RecordTypeClassifier recordTypeClassifier( getType() );
        return recordTypeClassifier.isTypeOf_BatchInconsistency();
    }

    bool TransactionRecordBase::isTypeOf_PerpetualStocktaking() const
    {
        RecordTypeClassifier recordTypeClassifier( getType() );
        return recordTypeClassifier.isTypeOf_PerpetualStocktaking();
    }

    bool TransactionRecordBase::isTypeOf_StorageReconciliationPrewholesale() const
    {
        RecordTypeClassifier recordTypeClassifier( getType() );
        return recordTypeClassifier.isTypeOf_StorageReconciliationPrewholesale();
    }

    bool TransactionRecordBase::isTypeOf_ChangeOrderItem() const
    {
        RecordTypeClassifier recordTypeClassifier( getType() );
        return recordTypeClassifier.isTypeOf_ChangeOrderItem();
    }

    bool TransactionRecordBase::isTypeOf_ArticleInfoGoodsIn() const
    {
        RecordTypeClassifier recordTypeClassifier( getType() );
        return recordTypeClassifier.isTypeOf_ArticleInfoGoodsIn();
    }

    bool TransactionRecordBase::isTypeOf_StopSellingOfArticle() const
    {
        RecordTypeClassifier recordTypeClassifier( getType() );
        return recordTypeClassifier.isTypeOf_StopSellingOfArticle();
    }

    bool TransactionRecordBase::isTypeOf_ChangeIBTStockLevel() const
    {
        RecordTypeClassifier recordTypeClassifier( getType() );
        return recordTypeClassifier.isTypeOf_ChangeIBTStockLevel();
    }

    bool TransactionRecordBase::isTypeOf_ChangeQuarantine() const
    {
        RecordTypeClassifier recordTypeClassifier( getType() );
        return recordTypeClassifier.isTypeOf_ChangeQuarantine();
    }

    bool TransactionRecordBase::isTypeOf_CodeBlocage() const
    {
        RecordTypeClassifier recordTypeClassifier( getType() );
        return recordTypeClassifier.isTypeOf_CodeBlocage();
    }

    bool TransactionRecordBase::isTypeOf_Batch() const
    {
        RecordTypeClassifier recordTypeClassifier( getType() );
        return recordTypeClassifier.isTypeOf_Batch();
    }

    bool TransactionRecordBase::isTypeOf_DealerVolumeTotal() const
    {
        RecordTypeClassifier recordTypeClassifier( getType() );
        return recordTypeClassifier.isTypeOf_DealerVolumeTotal();
    }

    bool TransactionRecordBase::isTypeOf_DealerVolumeElectronic() const
    {
        RecordTypeClassifier recordTypeClassifier( getType() );
        return recordTypeClassifier.isTypeOf_DealerVolumeElectronic();
    }

    bool TransactionRecordBase::isTypeOf_CustomerReturn() const
    {
        RecordTypeClassifier recordTypeClassifier( getType() );
        return recordTypeClassifier.isTypeOf_CustomerReturn();
    }

    bool TransactionRecordBase::isTypeOf_DealerVolumeExclusiveTotal() const
    {
        RecordTypeClassifier recordTypeClassifier( getType() );
        return recordTypeClassifier.isTypeOf_DealerVolumeExclusiveTotal();
    }

    bool TransactionRecordBase::isTypeOf_DealerVolumeExclusiveElectronic() const
    {
        RecordTypeClassifier recordTypeClassifier( getType() );
        return recordTypeClassifier.isTypeOf_DealerVolumeExclusiveElectronic();
    }

    bool TransactionRecordBase::isTypeOf_CreditLimitChain() const
    {
        RecordTypeClassifier recordTypeClassifier( getType() );
        return recordTypeClassifier.isTypeOf_CreditLimitChain();
    }

    bool TransactionRecordBase::isTypeOf_CreditLimitGroup() const
    {
        RecordTypeClassifier recordTypeClassifier( getType() );
        return recordTypeClassifier.isTypeOf_CreditLimitGroup();

    }

    bool TransactionRecordBase::isTypeOf_CreditLimitCustomer() const
    {
        RecordTypeClassifier recordTypeClassifier( getType() );
        return recordTypeClassifier.isTypeOf_CreditLimitCustomer();
    }

    bool TransactionRecordBase::isTypeOf_CreditLimitCustomerReturn() const
    {
        RecordTypeClassifier recordTypeClassifier( getType() );
        return recordTypeClassifier.isTypeOf_CreditLimitCustomerReturn();
    }

    bool TransactionRecordBase::isTypeOf_CreditLimit() const
    {
        RecordTypeClassifier recordTypeClassifier( getType() );
        return recordTypeClassifier.isTypeOf_CreditLimit();
    }

    bool TransactionRecordBase::isTypeOf_DiscountAccount() const
    {
        RecordTypeClassifier recordTypeClassifier( getType() );
        return recordTypeClassifier.isTypeOf_DiscountAccount();
    }

    bool TransactionRecordBase::isTypeOf_ExpiryDate() const
    {
        RecordTypeClassifier recordTypeClassifier( getType() );
        return recordTypeClassifier.isTypeOf_ExpiryDate();
    }

    bool TransactionRecordBase::isTypeOf_ChangeArticleDetails() const
    {
        RecordTypeClassifier recordTypeClassifier( getType() );
        return recordTypeClassifier.isTypeOf_ChangeArticleDetails();
    }

    bool TransactionRecordBase::isTypeOf_ImportInvoiceNo() const
    {
        RecordTypeClassifier recordTypeClassifier( getType() );
        return recordTypeClassifier.isTypeOf_ImportInvoiceNo();
    }

    bool TransactionRecordBase::isTypeOf_TransferQuarantine() const
    {
        RecordTypeClassifier recordTypeClassifier( getType() );
        return recordTypeClassifier.isTypeOf_TransferQuarantine();
    }

    bool TransactionRecordBase::isTypeOf_GoodsIn() const
    {
        RecordTypeClassifier recordTypeClassifier( getType() );
        return recordTypeClassifier.isTypeOf_GoodsIn();
    }

    bool TransactionRecordBase::isTypeOf_TenderChangeCustomerReturn() const
    {
        RecordTypeClassifier recordTypeClassifier( getType() );
        return recordTypeClassifier.isTypeOf_TenderChangeCustomerReturn();
    }

    bool TransactionRecordBase::isTypeOf_InvoiceCancellation() const
    {
        RecordTypeClassifier recordTypeClassifier( getType() );
        return recordTypeClassifier.isTypeOf_InvoiceCancellation();
    }

    bool TransactionRecordBase::isTypeOf_PickingLack() const
    {
        RecordTypeClassifier recordTypeClassifier( getType() );
        return recordTypeClassifier.isTypeOf_PickingLack();
    }

    bool TransactionRecordBase::isTypeOf_ChangeArticleMasterData() const
    {
        RecordTypeClassifier recordTypeClassifier( getType() );
        return recordTypeClassifier.isTypeOf_ChangeArticleMasterData();
    }

    bool TransactionRecordBase::isTypeOf_IBTGoods() const
    {
        RecordTypeClassifier recordTypeClassifier( getType() );
        return recordTypeClassifier.isTypeOf_IBTGoods();
    }

    bool TransactionRecordBase::isTypeOf_OTHER() const
    {
        RecordTypeClassifier recordTypeClassifier( getType() );
        return recordTypeClassifier.isTypeOf_OTHER();
    }

    void TransactionRecordBase::save()
    {
        METHODNAME_DEF( TransactionRecordBase, save )
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

        basar::db::aspect::ExecuteResultInfo executeResultInfo;
        const basar::VarString& accessMethod = getSaveAccessMethod();
        try
        {
            domMod::TransactionGuard guard( m_Accessor.getConnection() );
            guard.beginTransaction ();

            executeResultInfo = m_Accessor.get().execute( accessMethod, m_YitTransactionRecord );

            guard.commitTransaction ();
        }
        catch( basar::Exception& e )
        {
            ::util::ExceptionHandler::processAccessorException( e, m_CSC_Logger->getLogger(), fun, accessMethod, __FILE__, __LINE__ );
        }
        if( executeResultInfo.hasError() )
        {
            std::stringstream msg;
            msg << fun << ": DB-Error <" <<  ExecuteErrorEnum2StringMapper::map(executeResultInfo.m_error) << "> with executing '"
            << accessMethod;
            throw ::util::AccessorExecutionException( basar::ExceptInfo( fun, msg.str().c_str(), __FILE__, __LINE__ ) );
        }
    }

    const log4cplus::Logger& TransactionRecordBase::getLogger() const
    {
        METHODNAME_DEF( TransactionRecordBase, getLogger )
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
        return m_CSC_Logger->getLogger();
    }

    basar::Int32 TransactionRecordBase::getDailyClosing() const
    {
        METHODNAME_DEF( TransactionRecordBase, getDailyClosing )
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getDailyClosing not supported!", __FILE__, __LINE__));
        return -1;
    }

    basar::Int16 TransactionRecordBase::getOrigin() const
    {
        METHODNAME_DEF( TransactionRecordBase, getOrigin )
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getOrigin not supported!", __FILE__, __LINE__));
        return -1;
    }

    basar::Int32 TransactionRecordBase::getOrderSupplierNo() const
    {
        METHODNAME_DEF(TransactionRecordBase, getOrderSupplierNo)
            BLOG_TRACE_METHOD(m_CSC_Logger->getLogger(), fun);
        throw libcsc_utils::MethodCallNotSupportedException(basar::ExceptInfo(fun, "getOrderSupplierNo not supported!", __FILE__, __LINE__));
        return -1;
    }

    basar::Int16 TransactionRecordBase::getBranchNo() const
    {
        METHODNAME_DEF( TransactionRecordBase, getBranchNo )
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getBranchNo not supported!", __FILE__, __LINE__));
        return -1;
    }

    basar::DateTime TransactionRecordBase::getCreationDateTime() const
    {
        METHODNAME_DEF( TransactionRecordBase, getCreationDateTime )
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getCreationDateTime not supported!", __FILE__, __LINE__));
        return basar::DateTime();
    }

    basar::Int32 TransactionRecordBase::getVSEOffset() const
    {
        METHODNAME_DEF( TransactionRecordBase, getVSEOffset )
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getVSEOffset not supported!", __FILE__, __LINE__));
        return 0;
    }

    basar::VarString TransactionRecordBase::getProcessingState() const
    {
        METHODNAME_DEF( TransactionRecordBase, getProcessingState )
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getProcessingState not supported!", __FILE__, __LINE__));
        return "";
    }

    basar::DateTime TransactionRecordBase::getProcessedTimestamp() const
    {
        METHODNAME_DEF( TransactionRecordBase, getProcessedTimestamp )
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getProcessedTimestamp not supported!", __FILE__, __LINE__));
        return basar::DateTime();
    }

    basar::DateTime TransactionRecordBase::getTransferredTimestamp() const
    {
        METHODNAME_DEF( TransactionRecordBase, getTransferredTimestamp )
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getTransferredTimestamp not supported!", __FILE__, __LINE__));
        return basar::DateTime();
    }

    basar::Int32 TransactionRecordBase::getDatasetSequenceNo() const
    {
        METHODNAME_DEF( TransactionRecordBase, getDatasetSequenceNo )
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getDatasetSequenceNo not supported!", __FILE__, __LINE__));
        return 0;
    }

    basar::VarString TransactionRecordBase::getRecordType() const
    {
        METHODNAME_DEF( TransactionRecordBase, getRecordType )
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getRecordType not supported!", __FILE__, __LINE__));
        return "";
    }

    basar::VarString TransactionRecordBase::getCustomerNo() const
    {
        METHODNAME_DEF( TransactionRecordBase, getCustomerNo )
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getCustomerNo not supported!", __FILE__, __LINE__));
        return "";
    }

    basar::Int16 TransactionRecordBase::getBookingType() const
    {
        METHODNAME_DEF( TransactionRecordBase, getBookingType )
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getBookingType not supported!", __FILE__, __LINE__));
        return 0;
    }

    basar::Int32 TransactionRecordBase::getUserId() const
    {
        METHODNAME_DEF( TransactionRecordBase, getUserId )
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getUserId not supported!", __FILE__, __LINE__));
        return 0;
    }

    basar::VarString TransactionRecordBase::getInvoiceNo() const
    {
        METHODNAME_DEF( TransactionRecordBase, getInvoiceNo )
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getInvoiceNo not supported!", __FILE__, __LINE__));
        return "";
    }

    basar::DateTime TransactionRecordBase::getInvoiceDateTime() const
    {
        METHODNAME_DEF( TransactionRecordBase, getInvoiceDateTime )
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getInvoiceDateTime not supported!", __FILE__, __LINE__));
        return basar::DateTime();
    }

    basar::Date TransactionRecordBase::getInvoiceDate() const
    {
        METHODNAME_DEF( TransactionRecordBase, getInvoiceDate )
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getInvoiceDateTime not supported!", __FILE__, __LINE__));
        return basar::Date();
    }

    basar::Int32 TransactionRecordBase::getCustomerOrderNo() const
    {
        METHODNAME_DEF( TransactionRecordBase, getCustomerOrderNo )
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getCustomerOrderNo not supported!", __FILE__, __LINE__));
        return 0;
    }

    basar::VarString TransactionRecordBase::getCSCOrderNo() const
    {
        METHODNAME_DEF( TransactionRecordBase, getCSCOrderNo )
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getCSCOrderNo not supported!", __FILE__, __LINE__));
        return "";
    }

    basar::Decimal TransactionRecordBase::getTurnover() const
    {
        METHODNAME_DEF( TransactionRecordBase, getTurnover )
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getTurnover not supported!", __FILE__, __LINE__));
        return basar::Decimal(0.0);
    }

    basar::Date TransactionRecordBase::getPaymentDate() const
    {
        METHODNAME_DEF( TransactionRecordBase, getPaymentDate )
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getPaymentDate not supported!", __FILE__, __LINE__));
        return basar::Date();
    }

    basar::VarString TransactionRecordBase::getPaymentType() const
    {
        METHODNAME_DEF( TransactionRecordBase, getPaymentType )
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getPaymentType not supported!", __FILE__, __LINE__));
        return "";
    }

    basar::VarString TransactionRecordBase::getPriceType() const
    {
        METHODNAME_DEF( TransactionRecordBase, getPriceType )
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getPriceType not supported!", __FILE__, __LINE__));
        return "";
    }

    basar::Int32 TransactionRecordBase::getChainNo() const
    {
        METHODNAME_DEF( TransactionRecordBase, getChainNo )
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getChainNo not supported!", __FILE__, __LINE__));
        return 0;
    }

    basar::Decimal TransactionRecordBase::getRemainingDiscAccValue() const
    {
        METHODNAME_DEF( TransactionRecordBase, getRemainingDiscAccValue )
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getRemainingDiscAccValue not supported!", __FILE__, __LINE__));
        return basar::Decimal(0.0);
    }

    basar::Decimal TransactionRecordBase::getInvoiceValue() const
    {
        METHODNAME_DEF( TransactionRecordBase, getInvoiceValue )
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getInvoiceValue not supported!", __FILE__, __LINE__));
        return basar::Decimal(0.0);
    }

    basar::Int32 TransactionRecordBase::getDiscAccOperationNo() const
    {
        METHODNAME_DEF( TransactionRecordBase, getDiscAccOperationNo )
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getDiscAccOperationNo not supported!", __FILE__, __LINE__));
        return 0;
    }

    basar::Int32 TransactionRecordBase::getPriority() const
    {
        METHODNAME_DEF( TransactionRecordBase, getPriority )
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getPriority not supported!", __FILE__, __LINE__));
        return 0;
    }

    basar::VarString TransactionRecordBase::getVoucherType() const
    {
        METHODNAME_DEF( TransactionRecordBase, getVoucherType )
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getVoucherType not supported!", __FILE__, __LINE__));
        return "";
    }

    basar::Int32 TransactionRecordBase::getArticleNo() const
    {
        METHODNAME_DEF( TransactionRecordBase, getArticleNo )
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getArticleNo not supported!", __FILE__, __LINE__));
        return 0;
    }

    basar::VarString TransactionRecordBase::getBatch() const
    {
        METHODNAME_DEF( TransactionRecordBase, getBatch )
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getBatch not supported!", __FILE__, __LINE__));
        return "";
    }

    basar::Date TransactionRecordBase::getExpiryDate() const
    {
        METHODNAME_DEF( TransactionRecordBase, getExpiryDate )
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getExpiryDate not supported!", __FILE__, __LINE__));
        return basar::Date();
    }

    basar::Int32 TransactionRecordBase::getQuantity() const
    {
        METHODNAME_DEF( TransactionRecordBase, getQuantity )
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getQuantity not supported!", __FILE__, __LINE__));
        return 0;
    }

    basar::Decimal TransactionRecordBase::getDebitValue() const
    {
        METHODNAME_DEF( TransactionRecordBase, getDebitValue )
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getDebitValue not supported!", __FILE__, __LINE__));
        return basar::Decimal(0.0);
    }

    basar::Decimal TransactionRecordBase::getLimitValue() const
    {
        METHODNAME_DEF( TransactionRecordBase, getLimitValue )
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getLimitValue not supported!", __FILE__, __LINE__));
        return basar::Decimal(0.0);
    }

    basar::Int32 TransactionRecordBase::getSupplierNo() const
    {
        METHODNAME_DEF( TransactionRecordBase, getSupplierNo )
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getSupplierNo not supported!", __FILE__, __LINE__));
        return 0;
    }

    basar::VarString TransactionRecordBase::getPurchaseOrderNo() const
    {
        METHODNAME_DEF( TransactionRecordBase, getPurchaseOrderNo )
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getPurchaseOrderNo not supported!", __FILE__, __LINE__));
        return "";
    }

    basar::Decimal TransactionRecordBase::getCostPrice() const
    {
        METHODNAME_DEF( TransactionRecordBase, getCostPrice )
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getCostPrice not supported!", __FILE__, __LINE__));
        return basar::Decimal(0.0);
    }

    basar::VarString TransactionRecordBase::getStorageLocation() const
    {
        METHODNAME_DEF( TransactionRecordBase, getStorageLocation )
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getStorageLocation not supported!", __FILE__, __LINE__));
        return "";
    }

    basar::VarString TransactionRecordBase::getStorageArea() const
    {
        METHODNAME_DEF( TransactionRecordBase, getStorageArea )
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getStorageArea not supported!", __FILE__, __LINE__));
        return "";
    }

    basar::VarString TransactionRecordBase::getStationNo() const
    {
        METHODNAME_DEF( TransactionRecordBase, getStationNo )
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getStationNo not supported!", __FILE__, __LINE__));
        return "";
    }

    basar::Int16 TransactionRecordBase::getExpiryDateChangeFlag() const
    {
        METHODNAME_DEF( TransactionRecordBase, getExpiryDateChangeFlag )
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getExpiryDateChangeFlag not supported!", __FILE__, __LINE__));
        return 0;
    }

    basar::Int16 TransactionRecordBase::getStorageLocationChangeFlag() const
    {
        METHODNAME_DEF( TransactionRecordBase, getStorageLocationChangeFlag )
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getStorageLocationChangeFlag not supported!", __FILE__, __LINE__));
        return 0;
    }

    basar::Int16 TransactionRecordBase::getCostPriceChangeFlag() const
    {
        METHODNAME_DEF( TransactionRecordBase, getCostPriceChangeFlag )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getcostPriceChangeFlag not supported!", __FILE__, __LINE__));
        return 0;
    }

    basar::Int16 TransactionRecordBase::getPharmacyPurchasePriceChangeFlag() const
    {
        METHODNAME_DEF( TransactionRecordBase, getPharmacyPurchasePriceChangeFlag )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getPharmacyPurchasePriceChangeFlag not supported!", __FILE__, __LINE__));
        return 0;
    }

    basar::Int16 TransactionRecordBase::getPharmacySellPriceChangeFlag() const
    {
        METHODNAME_DEF( TransactionRecordBase, getPharmacySellPriceChangeFlag )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getPharmacySellPriceChangeFlag not supported!", __FILE__, __LINE__));
        return 0;
    }

    basar::Decimal TransactionRecordBase::getPharmacyPurchasePrice() const
    {
        METHODNAME_DEF( TransactionRecordBase, getPharmacyPurchasePrice )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getPharmacyPurchasePrice not supported!", __FILE__, __LINE__));
        return basar::Decimal(0.0);
    }

    basar::Decimal TransactionRecordBase::getPharmacySellPrice() const
    {
        METHODNAME_DEF( TransactionRecordBase, getPharmacySellPrice )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getPharmacySellPrice not supported!", __FILE__, __LINE__));
        return basar::Decimal(0.0);
    }

    basar::Int16 TransactionRecordBase::getIbtBranchNo() const
    {
        METHODNAME_DEF( TransactionRecordBase, getIbtBranchNo )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getIbtBranchNo not supported!", __FILE__, __LINE__));
        return 0;
    }

    basar::VarString TransactionRecordBase::getCodeBlocage() const
    {
        METHODNAME_DEF( TransactionRecordBase, getCodeBlocage )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getCodeBlocage not supported!", __FILE__, __LINE__));
        return "";
    }

    basar::Int32 TransactionRecordBase::getQuantityNatra() const
    {
        METHODNAME_DEF( TransactionRecordBase, getQuantityNatra )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getQuantityNatra not supported!", __FILE__, __LINE__));
        return 0;
    }

    basar::Int32 TransactionRecordBase::getOrderPositionNo() const
    {
        METHODNAME_DEF( TransactionRecordBase, getOrderPositionNo )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getOrderPositionNo not supported!", __FILE__, __LINE__));
        return 0;
    }

    basar::DateTime TransactionRecordBase::getKbvzDX01DateTime() const
    {
        METHODNAME_DEF( TransactionRecordBase, getKbvzDX01DateTime )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getKbvzDX01DateTime not supported!", __FILE__, __LINE__));
        return basar::DateTime();
    }


    basar::Int32 TransactionRecordBase::getKbvzDX01Date() const
    {
        METHODNAME_DEF( TransactionRecordBase, getKbvzDX01Date )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getKbvzDX01Date not supported!", __FILE__, __LINE__));
        return 0;
    }

    basar::Int32 TransactionRecordBase::getKbvzOffset() const
    {
        METHODNAME_DEF( TransactionRecordBase, getKbvzOffset )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getKbvzOffset not supported!", __FILE__, __LINE__));
        return 0;
    }

    basar::VarString TransactionRecordBase::getKbvzKSC() const
    {
        METHODNAME_DEF( TransactionRecordBase, getKbvzKSC )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getKbvzKSC not supported!", __FILE__, __LINE__));
        return "";
    }

    basar::Int32 TransactionRecordBase::getKbvzKSCTime() const
    {
        METHODNAME_DEF( TransactionRecordBase, getKbvzKSCTime )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getKbvzKSCTime not supported!", __FILE__, __LINE__));
        return 0;
    }

    basar::Int32 TransactionRecordBase::getKbvzDX01Time() const
    {
        METHODNAME_DEF( TransactionRecordBase, getKbvzDX01Time )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getKbvzDX01Time not supported!", __FILE__, __LINE__));
        return 0;
    }

    basar::Int32 TransactionRecordBase::getKbvzLfdNr() const
    {
        METHODNAME_DEF( TransactionRecordBase, getKbvzLfdNr )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getKbvzLfdNr not supported!", __FILE__, __LINE__));
        return 0;
    }

    basar::Int16 TransactionRecordBase::getKbvzFil() const
    {
        METHODNAME_DEF( TransactionRecordBase, getKbvzFil )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getKbvzFil not supported!", __FILE__, __LINE__));
        return 0;
    }

    basar::Int32 TransactionRecordBase::getKbvzPZN() const
    {
        METHODNAME_DEF( TransactionRecordBase, getKbvzPZN )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getKbvzPZN not supported!", __FILE__, __LINE__));
        return 0;
    }

    basar::Int32 TransactionRecordBase::getKbvzMeng() const
    {
        METHODNAME_DEF( TransactionRecordBase, getKbvzMeng )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getKbvzMeng not supported!", __FILE__, __LINE__));
        return 0;
    }

    basar::Int16 TransactionRecordBase::getKbvzBukz() const
    {
        METHODNAME_DEF( TransactionRecordBase, getKbvzBukz )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getKbvzBukz not supported!", __FILE__, __LINE__));
        return 0;
    }

    basar::VarString TransactionRecordBase::getKbvzArt() const
    {
        METHODNAME_DEF( TransactionRecordBase, getKbvzArt )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getKbvzArt not supported!", __FILE__, __LINE__));
        return "";
    }

    basar::Int32 TransactionRecordBase::getKbvzTime() const
    {
        METHODNAME_DEF( TransactionRecordBase, getKbvzTime )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getKbvzTime not supported!", __FILE__, __LINE__));
        return 0;
    }

    basar::Int32 TransactionRecordBase::getKbvzDate() const
    {
        METHODNAME_DEF( TransactionRecordBase, getKbvzDate )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getKbvzDate not supported!", __FILE__, __LINE__));
        return 0;
    }

    basar::VarString TransactionRecordBase::getKbvzLgfnr() const
    {
        METHODNAME_DEF( TransactionRecordBase, getKbvzLgfnr )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getKbvzLgfnr not supported!", __FILE__, __LINE__));
        return "";
    }

    basar::Int32 TransactionRecordBase::getKbvzKSCAnr() const
    {
        METHODNAME_DEF( TransactionRecordBase, getKbvzKSCAnr )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getKbvzKSCAnr not supported!", __FILE__, __LINE__));
        return 0;
    }

    basar::VarString TransactionRecordBase::getKbvzLgnr() const
    {
        METHODNAME_DEF( TransactionRecordBase, getKbvzLgnr )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getKbvzLgnr not supported!", __FILE__, __LINE__));
        return "";
    }

    basar::VarString TransactionRecordBase::getKbvzStat() const
    {
        METHODNAME_DEF( TransactionRecordBase, getKbvzStat )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getKbvzStat not supported!", __FILE__, __LINE__));
        return "";
    }

    basar::VarString TransactionRecordBase::getKbvzET3() const
    {
        METHODNAME_DEF( TransactionRecordBase, getKbvzET3 )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getKbvzET3 not supported!", __FILE__, __LINE__));
        return "";
    }

    basar::VarString TransactionRecordBase::getKbvzWber() const
    {
        METHODNAME_DEF( TransactionRecordBase, getKbvzWber )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getKbvzWber not supported!", __FILE__, __LINE__));
        return "";
    }

    basar::Int32 TransactionRecordBase::getKbvzVerf() const
    {
        METHODNAME_DEF( TransactionRecordBase, getKbvzVerf )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getKbvzVerf not supported!", __FILE__, __LINE__));
        return 0;
    }

    basar::Int32 TransactionRecordBase::getKbvzP1Pos() const
    {
        METHODNAME_DEF( TransactionRecordBase, getKbvzP1Pos )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getKbvzP1Pos not supported!", __FILE__, __LINE__));
        return 0;
    }

    basar::Decimal TransactionRecordBase::getKbvzGEP() const
    {
        METHODNAME_DEF( TransactionRecordBase, getKbvzGEP )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getKbvzGEP not supported!", __FILE__, __LINE__));
        return basar::Decimal(0.0);
    }

    basar::Decimal TransactionRecordBase::getKbvzAEP() const
    {
        METHODNAME_DEF( TransactionRecordBase, getKbvzAEP )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getKbvzAEP not supported!", __FILE__, __LINE__));
        return basar::Decimal(0.0);
    }

    basar::Decimal TransactionRecordBase::getKbvzAVP() const
    {
        METHODNAME_DEF( TransactionRecordBase, getKbvzAVP )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getKbvzAVP not supported!", __FILE__, __LINE__));
        return basar::Decimal(0.0);
    }

    basar::VarString TransactionRecordBase::getKbvzKVerf() const
    {
        METHODNAME_DEF( TransactionRecordBase, getKbvzKVerf )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getKbvzKVerf not supported!", __FILE__, __LINE__));
        return "";
    }

    basar::VarString TransactionRecordBase::getKbvzKLgfnr() const
    {
        METHODNAME_DEF( TransactionRecordBase, getKbvzKLgfnr )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getKbvzKLgfnr not supported!", __FILE__, __LINE__));
        return "";
    }

    basar::VarString TransactionRecordBase::getKbvzKGEP() const
    {
        METHODNAME_DEF( TransactionRecordBase, getKbvzKGEP )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getKbvzKGEP not supported!", __FILE__, __LINE__));
        return "";
    }

    basar::VarString TransactionRecordBase::getKbvzKAEP() const
    {
        METHODNAME_DEF( TransactionRecordBase, getKbvzKAEP )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getKbvzKAEP not supported!", __FILE__, __LINE__));
        return "";
    }

    basar::VarString TransactionRecordBase::getKbvzKAVP() const
    {
        METHODNAME_DEF( TransactionRecordBase, getKbvzKAVP )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getKbvzKAVP not supported!", __FILE__, __LINE__));
        return "";
    }

    basar::Int16 TransactionRecordBase::getKbvzMFil() const
    {
        METHODNAME_DEF( TransactionRecordBase, getKbvzMFil )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getKbvzMFil not supported!", __FILE__, __LINE__));
        return 0;
    }

    basar::VarString TransactionRecordBase::getKbvzStatus() const
    {
        METHODNAME_DEF( TransactionRecordBase, getKbvzStatus )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getKbvzStatus not supported!", __FILE__, __LINE__));
        return "";
    }

    basar::VarString TransactionRecordBase::getKbvzExport() const
    {
        METHODNAME_DEF( TransactionRecordBase, getKbvzExport )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getKbvzExport not supported!", __FILE__, __LINE__));
        return "";
    }

    basar::Decimal TransactionRecordBase::getKbvzWert() const
    {
        METHODNAME_DEF( TransactionRecordBase, getKbvzWert )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getKbvzWert not supported!", __FILE__, __LINE__));
        return basar::Decimal(0.0);
    }

    basar::VarString TransactionRecordBase::getKbvzCloSa() const
    {
        METHODNAME_DEF( TransactionRecordBase, getKbvzCloSa )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getKbvzCloSa not supported!", __FILE__, __LINE__));
        return "";
    }

    basar::VarString TransactionRecordBase::getKbvzCloZeit() const
    {
        METHODNAME_DEF( TransactionRecordBase, getKbvzCloZeit )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getKbvzCloZeit not supported!", __FILE__, __LINE__));
        return "";
    }

    basar::Int32 TransactionRecordBase::getKbvzCloAnr() const
    {
        METHODNAME_DEF( TransactionRecordBase, getKbvzCloAnr )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getKbvzCloAnr not supported!", __FILE__, __LINE__));
        return 0;
    }

    basar::Int32 TransactionRecordBase::getKbvzCloPos() const
    {
        METHODNAME_DEF( TransactionRecordBase, getKbvzCloPos )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getKbvzCloPos not supported!", __FILE__, __LINE__));
        return 0;
    }

    basar::VarString TransactionRecordBase::getKbvzCharge() const
    {
        METHODNAME_DEF( TransactionRecordBase, getKbvzCharge )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getKbvzCharge not supported!", __FILE__, __LINE__));
        return "";
    }

    basar::VarString TransactionRecordBase::getKbvzBatch() const
    {
        METHODNAME_DEF( TransactionRecordBase, getKbvzBatch )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getKbvzBatch not supported!", __FILE__, __LINE__));
        return "";
    }

    basar::Int32 TransactionRecordBase::getKbvzDailyClosing() const
    {
        METHODNAME_DEF( TransactionRecordBase, getKbvzDailyClosing )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getKbvzDailyClosing not supported!", __FILE__, __LINE__));
        return 0;
    }

    basar::Int32 TransactionRecordBase::getKbvzBeslaNr() const
    {
        METHODNAME_DEF(TransactionRecordBase, getKbvzBeslaNr)
            BLOG_TRACE_METHOD(getLogger(), fun);
        throw libcsc_utils::MethodCallNotSupportedException(basar::ExceptInfo(fun, "getKbvzBeslaNr not supported!", __FILE__, __LINE__));
        return 0;
    }

    void TransactionRecordBase::setBranchNo(const basar::Int16)
    {
        METHODNAME_DEF( TransactionRecordBase, setBranchNo )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "setBranchNo not supported!", __FILE__, __LINE__));
    }

    void TransactionRecordBase::setCreationDateTime(const basar::DateTime&)
    {
        METHODNAME_DEF( TransactionRecordBase, setCreationDateTime )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "setCreationDateTime not supported!", __FILE__, __LINE__));
    }

    void TransactionRecordBase::setVSEOffset(const basar::Int32)
    {
        METHODNAME_DEF( TransactionRecordBase, setVSEOffset )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "setVSEOffset not supported!", __FILE__, __LINE__));
    }

    void TransactionRecordBase::setProcessedTimestamp(const basar::DateTime&)
    {
        METHODNAME_DEF( TransactionRecordBase, setProcessedTimestamp )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "setProcessedTimestamp not supported!", __FILE__, __LINE__));
    }

    void TransactionRecordBase::setTransferredTimestamp(const basar::DateTime&)
    {
        METHODNAME_DEF( TransactionRecordBase, setTransferredTimestamp )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "setTransferredTimestamp not supported!", __FILE__, __LINE__));
    }

    void TransactionRecordBase::setDailyClosing(const basar::Int32)
    {
        METHODNAME_DEF( TransactionRecordBase, setDailyClosing )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "setDailyClosing not supported!", __FILE__, __LINE__));
    }

    void TransactionRecordBase::setOrigin(const basar::Int16)
    {
        METHODNAME_DEF( TransactionRecordBase, setOrigin )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "setOrigin not supported!", __FILE__, __LINE__));
    }

    void TransactionRecordBase::setOrderSupplierNo(const basar::Int32)
    {
        METHODNAME_DEF(TransactionRecordBase, setOrigin)
            BLOG_TRACE_METHOD(getLogger(), fun);
        throw libcsc_utils::MethodCallNotSupportedException(basar::ExceptInfo(fun, "setOrderSupplierNo not supported!", __FILE__, __LINE__));
    }

    void TransactionRecordBase::setDatasetSequenceNo(const basar::Int32)
    {
        METHODNAME_DEF( TransactionRecordBase, setDatasetSequenceNo )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "setDatasetSequenceNo not supported!", __FILE__, __LINE__));
    }

    void TransactionRecordBase::setRecordType(const basar::VarString&)
    {
        METHODNAME_DEF( TransactionRecordBase, setRecordType )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "setRecordType not supported!", __FILE__, __LINE__));
    }

    void TransactionRecordBase::setCustomerNo(const basar::VarString&)
    {
        METHODNAME_DEF( TransactionRecordBase, setCustomerNo )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "setCustomerNo not supported!", __FILE__, __LINE__));
    }

    void TransactionRecordBase::setBookingType(const basar::Int16)
    {
        METHODNAME_DEF( TransactionRecordBase, setBookingType )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "setBookingType not supported!", __FILE__, __LINE__));
    }

    void TransactionRecordBase::setUserId(const basar::Int32)
    {
        METHODNAME_DEF( TransactionRecordBase, setUserId )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "setUserId not supported!", __FILE__, __LINE__));
    }

    void TransactionRecordBase::setInvoiceNo(const basar::VarString&)
    {
        METHODNAME_DEF( TransactionRecordBase, setInvoiceNo )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "setInvoiceNo not supported!", __FILE__, __LINE__));
    }

    void TransactionRecordBase::setInvoiceDateTime(const basar::DateTime&)
    {
        METHODNAME_DEF( TransactionRecordBase, setInvoiceDateTime )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "setInvoiceDateTime not supported!", __FILE__, __LINE__));
    }

    void TransactionRecordBase::setCustomerOrderNo(const basar::Int32)
    {
        METHODNAME_DEF( TransactionRecordBase, setCustomerOrderNo )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "setCustomerOrderNo not supported!", __FILE__, __LINE__));
    }

    void TransactionRecordBase::setCSCOrderNo(const basar::VarString&)
    {
        METHODNAME_DEF( TransactionRecordBase, setCSCOrderNo )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "setCSCOrderNo not supported!", __FILE__, __LINE__));
    }

    void TransactionRecordBase::setTurnover(const basar::Decimal&)
    {
        METHODNAME_DEF( TransactionRecordBase, setTurnover )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "setTurnover not supported!", __FILE__, __LINE__));
    }

    void TransactionRecordBase::setPaymentDate(const basar::Date&)
    {
        METHODNAME_DEF( TransactionRecordBase, setPaymentDate )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "setPaymentDate not supported!", __FILE__, __LINE__));
    }

    void TransactionRecordBase::setPaymentType(const basar::VarString&)
    {
        METHODNAME_DEF( TransactionRecordBase, setPaymentType )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "setPaymentType not supported!", __FILE__, __LINE__));
    }

    void TransactionRecordBase::setPriceType(const basar::VarString&)
    {
        METHODNAME_DEF( TransactionRecordBase, setPriceType )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "setPriceType not supported!", __FILE__, __LINE__));
    }

    void TransactionRecordBase::setChainNo(const basar::Int32)
    {
        METHODNAME_DEF( TransactionRecordBase, setChainNo )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "setChainNo not supported!", __FILE__, __LINE__));
    }

    void TransactionRecordBase::setRemainingDiscAccValue(const basar::Decimal&)
    {
        METHODNAME_DEF( TransactionRecordBase, setRemainingDiscAccValue )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "setRemainingDiscAccValue not supported!", __FILE__, __LINE__));
    }

    void TransactionRecordBase::setInvoiceValue(const basar::Decimal&)
    {
        METHODNAME_DEF( TransactionRecordBase, setInvoiceValue )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "setInvoiceValue not supported!", __FILE__, __LINE__));
    }

    void TransactionRecordBase::setDiscAccOperationNo(const basar::Int32)
    {
        METHODNAME_DEF( TransactionRecordBase, setDiscAccOperationNo )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "setDiscAccOperationNo not supported!", __FILE__, __LINE__));
    }

    void TransactionRecordBase::setPriority(const basar::Int32)
    {
        METHODNAME_DEF( TransactionRecordBase, setPriority )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "setPriority not supported!", __FILE__, __LINE__));
    }

    void TransactionRecordBase::setVoucherType(const basar::VarString&)
    {
        METHODNAME_DEF( TransactionRecordBase, setVoucherType )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "setVoucherType not supported!", __FILE__, __LINE__));
    }

    void TransactionRecordBase::setArticleNo(const basar::Int32)
    {
        METHODNAME_DEF( TransactionRecordBase, setArticleNo )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "setArticleNo not supported!", __FILE__, __LINE__));
    }

    void TransactionRecordBase::setBatch(const basar::VarString&)
    {
        METHODNAME_DEF( TransactionRecordBase, setBatch )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "setBatch not supported!", __FILE__, __LINE__));
    }

    void TransactionRecordBase::setExpiryDate(const basar::Date&)
    {
        METHODNAME_DEF( TransactionRecordBase, setExpiryDate )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "setExpiryDate not supported!", __FILE__, __LINE__));
    }

    void TransactionRecordBase::setQuantity(const basar::Int32)
    {
        METHODNAME_DEF( TransactionRecordBase, setQuantity )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "setQuantity not supported!", __FILE__, __LINE__));
    }

    void TransactionRecordBase::setDebitValue(const basar::Decimal&)
    {
        METHODNAME_DEF( TransactionRecordBase, setDebitValue )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "setDebitValue not supported!", __FILE__, __LINE__));
    }

    void TransactionRecordBase::setLimitValue(const basar::Decimal&)
    {
        METHODNAME_DEF( TransactionRecordBase, setLimitValue )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "setLimitValue not supported!", __FILE__, __LINE__));
    }

    void TransactionRecordBase::setSupplierNo(const basar::Int32)
    {
        METHODNAME_DEF( TransactionRecordBase, setSupplierNo )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "setSupplierNo not supported!", __FILE__, __LINE__));
    }

    void TransactionRecordBase::setPurchaseOrderNo(const basar::VarString&)
    {
        METHODNAME_DEF( TransactionRecordBase, setPurchaseOrderNo )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "setPurchaseOrderNo not supported!", __FILE__, __LINE__));
    }

    void TransactionRecordBase::setCostPrice(const basar::Decimal&)
    {
        METHODNAME_DEF( TransactionRecordBase, setCostPrice )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "setCostPrice not supported!", __FILE__, __LINE__));
    }

    void TransactionRecordBase::setStorageLocation(const basar::VarString&)
    {
        METHODNAME_DEF( TransactionRecordBase, setStorageLocation )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "setStorageLocation not supported!", __FILE__, __LINE__));
    }

    void TransactionRecordBase::setStorageArea(const basar::VarString&)
    {
        METHODNAME_DEF( TransactionRecordBase, setStorageArea )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "setStorageArea not supported!", __FILE__, __LINE__));
    }

    void TransactionRecordBase::setStationNo(const basar::VarString&)
    {
        METHODNAME_DEF( TransactionRecordBase, setStationNo )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "setStationNo not supported!", __FILE__, __LINE__));
    }

    void TransactionRecordBase::setExpiryDateChangeFlag(const basar::Int16)
    {
        METHODNAME_DEF( TransactionRecordBase, setExpiryDateChangeFlag )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "setExpiryDateChangeFlag not supported!", __FILE__, __LINE__));
    }

    void TransactionRecordBase::setStorageLocationChangeFlag(const basar::Int16)
    {
        METHODNAME_DEF( TransactionRecordBase, setStorageLocationChangeFlag )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "setStorageLocationChangeFlag not supported!", __FILE__, __LINE__));
    }

    void TransactionRecordBase::setCostPriceChangeFlag(const basar::Int16)
    {
        METHODNAME_DEF( TransactionRecordBase, setCostPriceChangeFlag )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "setCostPriceChangeFlag not supported!", __FILE__, __LINE__));
    }

    void TransactionRecordBase::setPharmacyPurchasePriceChangeFlag(const basar::Int16)
    {
        METHODNAME_DEF( TransactionRecordBase, setPharmacyPurchasePriceChangeFlag )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "setPharmacyPurchasePriceChangeFlag not supported!", __FILE__, __LINE__));
    }

    void TransactionRecordBase::setPharmacySellPriceChangeFlag(const basar::Int16)
    {
        METHODNAME_DEF( TransactionRecordBase, setPharmacySellPriceChangeFlag )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "setPharmacySellPriceChangeFlag not supported!", __FILE__, __LINE__));
    }

    void TransactionRecordBase::setPharmacyPurchasePrice(const basar::Decimal&)
    {
        METHODNAME_DEF( TransactionRecordBase, setPharmacyPurchasePrice )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "setPharmacyPurchasePrice not supported!", __FILE__, __LINE__));
    }

    void TransactionRecordBase::setPharmacySellPrice(const basar::Decimal&)
    {
        METHODNAME_DEF( TransactionRecordBase, setPharmacySellPrice )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "setPharmacySellPrice not supported!", __FILE__, __LINE__));
    }

    void TransactionRecordBase::setIbtBranchNo(const basar::Int16)
    {
        METHODNAME_DEF( TransactionRecordBase, setIbtBranchNo )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "setIbtBranchNo not supported!", __FILE__, __LINE__));
    }

    void TransactionRecordBase::setCodeBlocage(const basar::VarString&)
    {
        METHODNAME_DEF( TransactionRecordBase, setCodeBlocage )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "setCodeBlocage not supported!", __FILE__, __LINE__));
    }

    void TransactionRecordBase::setQuantityNatra(const basar::Int32)
    {
        METHODNAME_DEF( TransactionRecordBase, setQuantityNatra )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "setQuantityNatra not supported!", __FILE__, __LINE__));
    }

    void TransactionRecordBase::setOrderPositionNo(const basar::Int32)
    {
        METHODNAME_DEF( TransactionRecordBase, setOrderPositionNo )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "setOrderPositionNo not supported!", __FILE__, __LINE__));
    }

    basar::Int32 TransactionRecordBase::getTransferId() const
    {
        METHODNAME_DEF( TransactionRecordBase, getTransferId )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getTransferId not supported!", __FILE__, __LINE__));
    }

    basar::DateTime TransactionRecordBase::getEntryDateTime() const
    {
        METHODNAME_DEF( TransactionRecordBase, getEntryDateTime )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getEntryDateTime not supported!", __FILE__, __LINE__));
    }

    basar::VarString TransactionRecordBase::getFieldName() const
    {
        METHODNAME_DEF( TransactionRecordBase, getFieldName )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getFieldName not supported!", __FILE__, __LINE__));
    }

    basar::VarString TransactionRecordBase::getFieldValue() const
    {
        METHODNAME_DEF( TransactionRecordBase, setOrderPositionNo )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "setOrderPositionNo not supported!", __FILE__, __LINE__));
    }

    basar::Int32 TransactionRecordBase::getProcessedFlag() const
    {
        METHODNAME_DEF( TransactionRecordBase, setOrderPositionNo )
        BLOG_TRACE_METHOD( getLogger(), fun );
        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "setOrderPositionNo not supported!", __FILE__, __LINE__));
    }

} // namespace core
} // namespace pharmosTransaction
} // namespace domMod
