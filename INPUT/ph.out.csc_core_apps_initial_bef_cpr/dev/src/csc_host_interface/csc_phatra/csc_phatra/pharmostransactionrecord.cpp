//-------------------------------------------------------------------------------------------------//
/*! \file transactionrecordbase.cpp
 *  \brief container for informix pharmos transaction record
 *  \author Julian Machata
 *  \date 27.06.2012
 */
//-------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include "pharmostransactionrecord.h"
#include "accessorinstancerefwrapper.h"
#include "property_definitions.h"
#include "pharmostransactionacc_definitions.h"
#include "invalidstatuschangeexception.h"
#include <icsc_logger.h>

//-------------------------------------------------------------------------------------------------//
// class definition section
//-------------------------------------------------------------------------------------------------//
namespace domMod
{
namespace pharmosTransaction
{
namespace core
{
    //using namespace properties::pharmostransaction;

	basar::ConstString PharmosTransactionRecord::ProcessingStatus::CLOSED = "C";
	basar::ConstString PharmosTransactionRecord::ProcessingStatus::OPEN = "O";
	basar::ConstString PharmosTransactionRecord::ProcessingStatus::IN_PROCESS = "I";

	basar::Int16 PharmosTransactionRecord::Origin::PHARMOS = 0;
	basar::Int16 PharmosTransactionRecord::Origin::ZDP = 1;

    //--------------------------------------------------------------------------------------------------//
    // object definition section
    //--------------------------------------------------------------------------------------------------//
	PharmosTransactionRecord::PharmosTransactionRecord( basar::db::aspect::AccessorPropertyTable_YIterator yitTransactionRecord
		, AccessorInstanceRefWrapper& acc, libcsc_utils::ICSC_LoggerPtr csc_logger )
        : TransactionRecordBase( yitTransactionRecord, acc, csc_logger )
	{
        METHODNAME_DEF( PharmosTransactionRecord, TransactionRecordBase )
        BLOG_TRACE_METHOD( getLogger(), fun );
		setProcessingStateOpen();
	}

	PharmosTransactionRecord::~PharmosTransactionRecord()
	{
        METHODNAME_DEF( PharmosTransactionRecord, ~PharmosTransactionRecord )
        BLOG_TRACE_METHOD( getLogger(), fun );
	}

    void PharmosTransactionRecord::log()
    {
        basar::VarString msg;
        basar::VarString type = getType();
        msg.format("processing PharmosTransactionRecord %d of type %s ",getVSEOffset(), type.c_str());

        m_CSC_Logger->log(log4cplus::INFO_LOG_LEVEL, msg);
    }

	basar::VarString PharmosTransactionRecord::getType() const
	{
		return getRecordType();
	}

	void PharmosTransactionRecord::startProcessing()
	{
        METHODNAME_DEF( PharmosTransactionRecord, startProcessing )
        BLOG_TRACE_METHOD( getLogger(), fun );

		if( ProcessingStatus::OPEN != m_YitTransactionRecord.getString( properties::pharmostransaction::PROCESSINGSTATUS.getName() )  )
		{
			throw libcsc_utils::InvalidStatusChangeException( basar::ExceptInfo( fun, "Invalid status change detected in startProcessing", __FILE__, __LINE__ ) );
		}

		basar::DateTime now = basar::DateTime::getCurrent();
		m_YitTransactionRecord.setDateTime( properties::pharmostransaction::PROCESSEDTIMESTAMP.getName(), now );
		m_YitTransactionRecord.setString( properties::pharmostransaction::PROCESSINGSTATUS.getName(), ProcessingStatus::IN_PROCESS );
        save();
	}

	void PharmosTransactionRecord::finishProcessing()
	{
        METHODNAME_DEF( PharmosTransactionRecord, finishProcessing )
        BLOG_TRACE_METHOD( getLogger(), fun );

		if( ProcessingStatus::IN_PROCESS != m_YitTransactionRecord.getString( properties::pharmostransaction::PROCESSINGSTATUS.getName() )  )
		{
			throw libcsc_utils::InvalidStatusChangeException( basar::ExceptInfo( fun, "Invalid status change detected in finishProcessing", __FILE__, __LINE__ ) );
		}

        if (wasProcessable())
        {
		    basar::DateTime now = basar::DateTime::getCurrent();
		    m_YitTransactionRecord.setDateTime( properties::pharmostransaction::PROCESSEDTIMESTAMP.getName(), now );
		    m_YitTransactionRecord.setString( properties::pharmostransaction::PROCESSINGSTATUS.getName(), ProcessingStatus::CLOSED );
            save();
        }
	}

	basar::Int32 PharmosTransactionRecord::getDailyClosing() const
	{
        METHODNAME_DEF( PharmosTransactionRecord, getDailyClosing )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return m_YitTransactionRecord.getInt32( properties::pharmostransaction::DAILYCLOSING.getName() );
	}

	basar::Int16 PharmosTransactionRecord::getOrigin() const
	{
        METHODNAME_DEF( PharmosTransactionRecord, getOrigin )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return m_YitTransactionRecord.getInt16( properties::pharmostransaction::ORIGIN.getName() );
	}

	basar::Int16 PharmosTransactionRecord::getBranchNo() const
	{
        METHODNAME_DEF( PharmosTransactionRecord, getBranchNo )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return m_YitTransactionRecord.getInt16( properties::pharmostransaction::BRANCHNO.getName() );
	}

	basar::DateTime PharmosTransactionRecord::getCreationDateTime() const
	{
        METHODNAME_DEF( PharmosTransactionRecord, getCreationDateTime )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return m_YitTransactionRecord.getDateTime( properties::pharmostransaction::CREATIONDATETIME.getName() );
	}

	basar::Int32 PharmosTransactionRecord::getVSEOffset() const
	{
        METHODNAME_DEF( PharmosTransactionRecord, getVSEOffset )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return m_YitTransactionRecord.getInt32( properties::pharmostransaction::VSEOFFSET.getName() );
	}

	basar::VarString PharmosTransactionRecord::getProcessingState() const
	{
        METHODNAME_DEF( PharmosTransactionRecord, getProcessingState )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return m_YitTransactionRecord.getString( properties::pharmostransaction::PROCESSINGSTATUS.getName() );
	}

	basar::DateTime PharmosTransactionRecord::getProcessedTimestamp() const
	{
        METHODNAME_DEF( PharmosTransactionRecord, getProcessedTimestamp )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return m_YitTransactionRecord.getDateTime( properties::pharmostransaction::PROCESSEDTIMESTAMP.getName() );
	}

	basar::DateTime PharmosTransactionRecord::getTransferredTimestamp() const
	{
        METHODNAME_DEF( PharmosTransactionRecord, getTransferredTimestamp )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return m_YitTransactionRecord.getDateTime( properties::pharmostransaction::TRANSFERREDTIMESTAMP.getName() );
	}

	basar::Int32 PharmosTransactionRecord::getDatasetSequenceNo() const
	{
        METHODNAME_DEF( PharmosTransactionRecord, getDatasetSequenceNo )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return m_YitTransactionRecord.getInt32( properties::pharmostransaction::DATASETSEQUENCENO.getName() );
	}

	basar::VarString PharmosTransactionRecord::getRecordType() const
	{
        METHODNAME_DEF( PharmosTransactionRecord, getRecordType )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return m_YitTransactionRecord.getString( properties::pharmostransaction::RECORDTYPE.getName() );
	}

	basar::VarString PharmosTransactionRecord::getCustomerNo() const
	{
        METHODNAME_DEF( PharmosTransactionRecord, getCustomerNo )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return m_YitTransactionRecord.getString( properties::pharmostransaction::CUSTOMERNO.getName() );
	}

	basar::Int16 PharmosTransactionRecord::getBookingType() const
	{
        METHODNAME_DEF( PharmosTransactionRecord, getBookingType )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return m_YitTransactionRecord.getInt16( properties::pharmostransaction::BOOKINGTYPE.getName() );
	}

	basar::Int32 PharmosTransactionRecord::getUserId() const
	{
        METHODNAME_DEF( PharmosTransactionRecord, getUserId )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return m_YitTransactionRecord.getInt32( properties::pharmostransaction::USERID.getName() );
	}

	basar::VarString PharmosTransactionRecord::getInvoiceNo() const
	{
        METHODNAME_DEF( PharmosTransactionRecord, getInvoiceNo )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return m_YitTransactionRecord.getString( properties::pharmostransaction::INVOICENO.getName() );
	}

	basar::DateTime PharmosTransactionRecord::getInvoiceDateTime() const
	{
        METHODNAME_DEF( PharmosTransactionRecord, getInvoiceDateTime )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return m_YitTransactionRecord.getDateTime( properties::pharmostransaction::INVOICETIMESTAMP.getName() );
	}

	basar::Int32 PharmosTransactionRecord::getCustomerOrderNo() const
	{
        METHODNAME_DEF( PharmosTransactionRecord, getCustomerOrderNo )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return m_YitTransactionRecord.getInt32( properties::pharmostransaction::CUSTOMERORDERNO.getName() );
	}

	basar::VarString PharmosTransactionRecord::getCSCOrderNo() const
	{
        METHODNAME_DEF( PharmosTransactionRecord, getCSCOrderNo )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return m_YitTransactionRecord.getString( properties::pharmostransaction::CSCORDERNO.getName() );
	}

	basar::Decimal PharmosTransactionRecord::getTurnover() const
	{
        METHODNAME_DEF( PharmosTransactionRecord, getTurnover )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return m_YitTransactionRecord.getDecimal( properties::pharmostransaction::TURNOVER.getName() );
	}

	basar::Date PharmosTransactionRecord::getPaymentDate() const
	{
        METHODNAME_DEF( PharmosTransactionRecord, getPaymentDate )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return m_YitTransactionRecord.getDate( properties::pharmostransaction::PAYMENTDATE.getName() );
	}

	basar::VarString PharmosTransactionRecord::getPaymentType() const
	{
        METHODNAME_DEF( PharmosTransactionRecord, getPaymentType )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return m_YitTransactionRecord.getString( properties::pharmostransaction::PAYMENTTYPE.getName() );
	}

	basar::VarString PharmosTransactionRecord::getPriceType() const
	{
        METHODNAME_DEF( PharmosTransactionRecord, getPriceType )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return m_YitTransactionRecord.getString( properties::pharmostransaction::PRICETYPE.getName() );
	}

	basar::Int32 PharmosTransactionRecord::getChainNo() const
	{
        METHODNAME_DEF( PharmosTransactionRecord, getChainNo )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return m_YitTransactionRecord.getInt32( properties::pharmostransaction::CHAINNO.getName() );
	}

	basar::Decimal PharmosTransactionRecord::getRemainingDiscAccValue() const
	{
        METHODNAME_DEF( PharmosTransactionRecord, getRemainingDiscAccValue )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return m_YitTransactionRecord.getDecimal( properties::pharmostransaction::REMAININGDISCACCVALUE.getName() );
	}

	basar::Decimal PharmosTransactionRecord::getInvoiceValue() const
	{
        METHODNAME_DEF( PharmosTransactionRecord, getInvoiceValue )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return m_YitTransactionRecord.getDecimal( properties::pharmostransaction::INVOICEVALUE.getName() );
	}

	basar::Int32 PharmosTransactionRecord::getDiscAccOperationNo() const
	{
        METHODNAME_DEF( PharmosTransactionRecord, getDiscAccOperationNo )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return m_YitTransactionRecord.getInt32( properties::pharmostransaction::DISCACCOPERATIONNO.getName() );
	}

	basar::Int32 PharmosTransactionRecord::getPriority() const
	{
        METHODNAME_DEF( PharmosTransactionRecord, getPriority )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return m_YitTransactionRecord.getInt32( properties::pharmostransaction::PRIORITY.getName() );
	}

	basar::VarString PharmosTransactionRecord::getVoucherType() const
	{
        METHODNAME_DEF( PharmosTransactionRecord, getVoucherType )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return m_YitTransactionRecord.getString( properties::pharmostransaction::VOUCHERTYPE.getName() );
	}

	basar::Int32 PharmosTransactionRecord::getArticleNo() const
	{
        METHODNAME_DEF( PharmosTransactionRecord, getArticleNo )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return m_YitTransactionRecord.getInt32( properties::pharmostransaction::ARTICLENO.getName() );
	}

	basar::VarString PharmosTransactionRecord::getBatch() const
	{
        METHODNAME_DEF( PharmosTransactionRecord, getBatch )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return m_YitTransactionRecord.getString( properties::pharmostransaction::BATCH.getName() );
	}

	basar::Date PharmosTransactionRecord::getExpiryDate() const
	{
        METHODNAME_DEF( PharmosTransactionRecord, getExpiryDate )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return m_YitTransactionRecord.getDate( properties::pharmostransaction::EXPIRYDATE.getName() );
	}

	basar::Int32 PharmosTransactionRecord::getQuantity() const
	{
        METHODNAME_DEF( PharmosTransactionRecord, getQuantity )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return m_YitTransactionRecord.getInt32( properties::pharmostransaction::QUANTITY.getName() );
	}

	basar::Decimal PharmosTransactionRecord::getDebitValue() const
	{
        METHODNAME_DEF( PharmosTransactionRecord, getDebitValue )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return m_YitTransactionRecord.getDecimal( properties::pharmostransaction::DEBITVALUE.getName() );
	}

	basar::Decimal PharmosTransactionRecord::getLimitValue() const
	{
        METHODNAME_DEF( PharmosTransactionRecord, getLimitValue )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return m_YitTransactionRecord.getDecimal( properties::pharmostransaction::LIMITVALUE.getName() );
	}

	basar::Int32 PharmosTransactionRecord::getSupplierNo() const
	{
        METHODNAME_DEF( PharmosTransactionRecord, getSupplierNo )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return m_YitTransactionRecord.getInt32( properties::pharmostransaction::SUPPLIERNO.getName() );
	}

	basar::VarString PharmosTransactionRecord::getPurchaseOrderNo() const
	{
        METHODNAME_DEF( PharmosTransactionRecord, getPurchaseOrderNo )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return m_YitTransactionRecord.getString( properties::pharmostransaction::PURCHASEORDERNO.getName() );
	}

	basar::Decimal PharmosTransactionRecord::getCostPrice() const
	{
        METHODNAME_DEF( PharmosTransactionRecord, getCostPrice )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return m_YitTransactionRecord.getDecimal( properties::pharmostransaction::COSTPRICE.getName() );
	}

	basar::VarString PharmosTransactionRecord::getStorageLocation() const
	{
        METHODNAME_DEF( PharmosTransactionRecord, getStorageLocation )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return m_YitTransactionRecord.getString( properties::pharmostransaction::STORAGELOCATION.getName() );
	}

	basar::VarString PharmosTransactionRecord::getStorageArea() const
	{
        METHODNAME_DEF( PharmosTransactionRecord, getStorageArea )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return m_YitTransactionRecord.getString( properties::pharmostransaction::STORAGEAREA.getName() );
	}

	basar::VarString PharmosTransactionRecord::getStationNo() const
	{
        METHODNAME_DEF( PharmosTransactionRecord, getStationNo )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return m_YitTransactionRecord.getString( properties::pharmostransaction::STATIONNO.getName() );
	}

	basar::Int16 PharmosTransactionRecord::getExpiryDateChangeFlag() const
	{
        METHODNAME_DEF( PharmosTransactionRecord, getExpiryDateChangeFlag )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return m_YitTransactionRecord.getInt16( properties::pharmostransaction::EXPIRYDATECHANGEFLAG.getName() );
	}

	basar::Int16 PharmosTransactionRecord::getStorageLocationChangeFlag() const
	{
        METHODNAME_DEF( PharmosTransactionRecord, getStorageLocationChangeFlag )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return m_YitTransactionRecord.getInt16( properties::pharmostransaction::STORAGELOCATIONCHANGEFLAG.getName() );
	}

	basar::Int16 PharmosTransactionRecord::getCostPriceChangeFlag() const
	{
		METHODNAME_DEF( PharmosTransactionRecord, getCostPriceChangeFlag )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return m_YitTransactionRecord.getInt16( properties::pharmostransaction::COSTPRICECHANGEFLAG.getName() );
	}

	basar::Int16 PharmosTransactionRecord::getPharmacyPurchasePriceChangeFlag() const
	{
        METHODNAME_DEF( PharmosTransactionRecord, getPharmacyPurchasePriceChangeFlag )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return m_YitTransactionRecord.getInt16( properties::pharmostransaction::PHARMACYPURCHASEPRICECHANGEFLAG.getName() );
	}

	basar::Int16 PharmosTransactionRecord::getPharmacySellPriceChangeFlag() const
	{
        METHODNAME_DEF( PharmosTransactionRecord, getPharmacySellPriceChangeFlag )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return m_YitTransactionRecord.getInt16( properties::pharmostransaction::PHARMACYSELLPRICECHANGEFLAG.getName() );
	}

	basar::Decimal PharmosTransactionRecord::getPharmacyPurchasePrice() const
	{
        METHODNAME_DEF( PharmosTransactionRecord, getPharmacyPurchasePrice )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return m_YitTransactionRecord.getDecimal( properties::pharmostransaction::PHARMACYPURCHASEPRICE.getName() );
	}

	basar::Decimal PharmosTransactionRecord::getPharmacySellPrice() const
	{
        METHODNAME_DEF( PharmosTransactionRecord, getPharmacySellPrice )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return m_YitTransactionRecord.getDecimal( properties::pharmostransaction::PHARMACYSELLPRICE.getName() );
	}

	basar::Int16 PharmosTransactionRecord::getIbtBranchNo() const
	{
        METHODNAME_DEF( PharmosTransactionRecord, getIbtBranchNo )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return m_YitTransactionRecord.getInt16( properties::pharmostransaction::IBTBRANCHNO.getName() );
	}

	basar::VarString PharmosTransactionRecord::getCodeBlocage() const
	{
        METHODNAME_DEF( PharmosTransactionRecord, getCodeBlocage )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return m_YitTransactionRecord.getString( properties::pharmostransaction::CODEBLOCAGE.getName() );
	}

	basar::Int32 PharmosTransactionRecord::getQuantityNatra() const
	{
        METHODNAME_DEF( PharmosTransactionRecord, getQuantityNatra )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return m_YitTransactionRecord.getInt32( properties::pharmostransaction::QUANTITYNATRA.getName() );
	}

	basar::Int32 PharmosTransactionRecord::getOrderPositionNo() const
	{
        METHODNAME_DEF( PharmosTransactionRecord, getOrderPositionNo )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return m_YitTransactionRecord.getInt32( properties::pharmostransaction::ORDERPOSITIONNO.getName() );
	}

	basar::Int32 PharmosTransactionRecord::getOrderSupplierNo() const
	{
		METHODNAME_DEF(PharmosTransactionRecord, getOrderSupplierNo)
			BLOG_TRACE_METHOD(getLogger(), fun);
		return m_YitTransactionRecord.getInt32(properties::pharmostransaction::ORDERSUPPLIERNO.getName());
	}

	void PharmosTransactionRecord::setBranchNo(const basar::Int16 val)
	{
        METHODNAME_DEF( PharmosTransactionRecord, setBranchNo )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		m_YitTransactionRecord.setInt16( properties::pharmostransaction::BRANCHNO.getName(), val );
	}

	void PharmosTransactionRecord::setCreationDateTime(const basar::DateTime& val)
	{
        METHODNAME_DEF( PharmosTransactionRecord, setCreationDateTime )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		m_YitTransactionRecord.setDateTime( properties::pharmostransaction::CREATIONDATETIME.getName(), val );
	}

	void PharmosTransactionRecord::setVSEOffset(const basar::Int32 val)
	{
        METHODNAME_DEF( PharmosTransactionRecord, setVSEOffset )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		m_YitTransactionRecord.setInt32( properties::pharmostransaction::VSEOFFSET.getName(), val );
	}

	void PharmosTransactionRecord::setProcessingStateOpen()
	{
        METHODNAME_DEF( PharmosTransactionRecord, setProcessingStateOpen )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		if( m_YitTransactionRecord.isEnd() ){ return; }
		m_YitTransactionRecord.setString( properties::pharmostransaction::PROCESSINGSTATUS.getName(), PharmosTransactionRecord::ProcessingStatus::OPEN );
	}

	void PharmosTransactionRecord::setProcessingStateInProcess()
	{
        METHODNAME_DEF( PharmosTransactionRecord, setProcessingStateInProcess )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		m_YitTransactionRecord.setString( properties::pharmostransaction::PROCESSINGSTATUS.getName(), PharmosTransactionRecord::ProcessingStatus::IN_PROCESS );
	}

	void PharmosTransactionRecord::setProcessingStateClosed()
	{
        METHODNAME_DEF( PharmosTransactionRecord, setProcessingStateClosed )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		m_YitTransactionRecord.setString( properties::pharmostransaction::PROCESSINGSTATUS.getName(), PharmosTransactionRecord::ProcessingStatus::CLOSED );
	}

	void PharmosTransactionRecord::setProcessedTimestamp(const basar::DateTime& val)
	{
        METHODNAME_DEF( PharmosTransactionRecord, setProcessedTimestamp )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		m_YitTransactionRecord.setDateTime( properties::pharmostransaction::PROCESSEDTIMESTAMP.getName(), val );
	}

	void PharmosTransactionRecord::setTransferredTimestamp(const basar::DateTime& val)
	{
        METHODNAME_DEF( PharmosTransactionRecord, setTransferredTimestamp )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		m_YitTransactionRecord.setDateTime( properties::pharmostransaction::TRANSFERREDTIMESTAMP, val );
	}

	void PharmosTransactionRecord::setDatasetSequenceNo(const basar::Int32 val)
	{
        METHODNAME_DEF( PharmosTransactionRecord, setDatasetSequenceNo )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		m_YitTransactionRecord.setInt32( properties::pharmostransaction::DATASETSEQUENCENO.getName(), val );
	}

	void PharmosTransactionRecord::setRecordType(const basar::VarString& val)
	{
        METHODNAME_DEF( PharmosTransactionRecord, setRecordType )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		m_YitTransactionRecord.setString( properties::pharmostransaction::RECORDTYPE.getName(), val );
	}

	void PharmosTransactionRecord::setCustomerNo(const basar::VarString& val)
	{
        METHODNAME_DEF( PharmosTransactionRecord, setCustomerNo )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		m_YitTransactionRecord.setString( properties::pharmostransaction::CUSTOMERNO.getName(), val );
	}

	void PharmosTransactionRecord::setBookingType(const basar::Int16 val)
	{
        METHODNAME_DEF( PharmosTransactionRecord, setBookingType )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		m_YitTransactionRecord.setInt16( properties::pharmostransaction::BOOKINGTYPE.getName(), val );
	}

	void PharmosTransactionRecord::setUserId(const basar::Int32 val)
	{
        METHODNAME_DEF( PharmosTransactionRecord, setUserId )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		m_YitTransactionRecord.setInt32( properties::pharmostransaction::USERID.getName(), val );
	}

	void PharmosTransactionRecord::setInvoiceNo(const basar::VarString& val)
	{
        METHODNAME_DEF( PharmosTransactionRecord, setInvoiceNo )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		m_YitTransactionRecord.setString( properties::pharmostransaction::INVOICENO.getName(), val );
	}

	void PharmosTransactionRecord::setInvoiceDateTime(const basar::DateTime& val)
	{
        METHODNAME_DEF( PharmosTransactionRecord, setInvoiceDateTime )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		m_YitTransactionRecord.setDateTime( properties::pharmostransaction::INVOICETIMESTAMP.getName(), val );
	}

	void PharmosTransactionRecord::setCustomerOrderNo(const basar::Int32 val)
	{
        METHODNAME_DEF( PharmosTransactionRecord, setCustomerOrderNo )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		m_YitTransactionRecord.setInt32( properties::pharmostransaction::CUSTOMERORDERNO.getName(), val );
	}

	void PharmosTransactionRecord::setCSCOrderNo(const basar::VarString& val)
	{
        METHODNAME_DEF( PharmosTransactionRecord, setCSCOrderNo )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		m_YitTransactionRecord.setString( properties::pharmostransaction::CSCORDERNO.getName(), val );
	}

	void PharmosTransactionRecord::setTurnover(const basar::Decimal& val)
	{
        METHODNAME_DEF( PharmosTransactionRecord, setTurnover )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		m_YitTransactionRecord.setDecimal( properties::pharmostransaction::TURNOVER.getName(), val );
	}

	void PharmosTransactionRecord::setPaymentDate(const basar::Date& val)
	{
        METHODNAME_DEF( PharmosTransactionRecord, setPaymentDate )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		m_YitTransactionRecord.setDate( properties::pharmostransaction::PAYMENTDATE.getName(), val );
	}

	void PharmosTransactionRecord::setPaymentType(const basar::VarString& val)
	{
        METHODNAME_DEF( PharmosTransactionRecord, setPaymentType )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		m_YitTransactionRecord.setString( properties::pharmostransaction::PAYMENTTYPE.getName(), val );
	}

	void PharmosTransactionRecord::setPriceType(const basar::VarString& val)
	{
        METHODNAME_DEF( PharmosTransactionRecord, setPriceType )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		m_YitTransactionRecord.setString( properties::pharmostransaction::PRICETYPE.getName(), val );
	}

	void PharmosTransactionRecord::setChainNo(const basar::Int32 val)
	{
        METHODNAME_DEF( PharmosTransactionRecord, setChainNo )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		m_YitTransactionRecord.setInt32( properties::pharmostransaction::CHAINNO.getName(), val );
	}

	void PharmosTransactionRecord::setRemainingDiscAccValue(const basar::Decimal& val)
	{
        METHODNAME_DEF( PharmosTransactionRecord, setRemainingDiscAccValue )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		m_YitTransactionRecord.setDecimal( properties::pharmostransaction::REMAININGDISCACCVALUE.getName(), val );
	}

	void PharmosTransactionRecord::setInvoiceValue(const basar::Decimal& val)
	{
        METHODNAME_DEF( PharmosTransactionRecord, setInvoiceValue )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		m_YitTransactionRecord.setDecimal( properties::pharmostransaction::INVOICEVALUE.getName(), val );
	}

	void PharmosTransactionRecord::setDiscAccOperationNo(const basar::Int32 val)
	{
        METHODNAME_DEF( PharmosTransactionRecord, setDiscAccOperationNo )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		m_YitTransactionRecord.setInt32( properties::pharmostransaction::DISCACCOPERATIONNO.getName(), val );
	}

	void PharmosTransactionRecord::setPriority(const basar::Int32 val)
	{
        METHODNAME_DEF( PharmosTransactionRecord, setPriority )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		m_YitTransactionRecord.setInt32( properties::pharmostransaction::PRIORITY.getName(), val );
	}

	void PharmosTransactionRecord::setVoucherType(const basar::VarString& val)
	{
        METHODNAME_DEF( PharmosTransactionRecord, setVoucherType )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		m_YitTransactionRecord.setString( properties::pharmostransaction::VOUCHERTYPE.getName(), val );
	}

	void PharmosTransactionRecord::setArticleNo(const basar::Int32 val)
	{
        METHODNAME_DEF( PharmosTransactionRecord, setArticleNo )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		m_YitTransactionRecord.setInt32( properties::pharmostransaction::ARTICLENO.getName(), val );
	}

	void PharmosTransactionRecord::setBatch(const basar::VarString& val)
	{
        METHODNAME_DEF( PharmosTransactionRecord, setBatch )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		m_YitTransactionRecord.setString( properties::pharmostransaction::BATCH.getName(), val );
	}

	void PharmosTransactionRecord::setExpiryDate(const basar::Date& val)
	{
        METHODNAME_DEF( PharmosTransactionRecord, setExpiryDate )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		m_YitTransactionRecord.setDate( properties::pharmostransaction::EXPIRYDATE.getName(), val );
	}

	void PharmosTransactionRecord::setQuantity(const basar::Int32 val)
	{
        METHODNAME_DEF( PharmosTransactionRecord, setQuantity )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		m_YitTransactionRecord.setInt32( properties::pharmostransaction::QUANTITY.getName(), val );
	}

	void PharmosTransactionRecord::setDebitValue(const basar::Decimal& val)
	{
        METHODNAME_DEF( PharmosTransactionRecord, setDebitValue )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		m_YitTransactionRecord.setDecimal( properties::pharmostransaction::DEBITVALUE.getName(), val );
	}

	void PharmosTransactionRecord::setLimitValue(const basar::Decimal& val)
	{
        METHODNAME_DEF( PharmosTransactionRecord, setLimitValue )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		m_YitTransactionRecord.setDecimal( properties::pharmostransaction::LIMITVALUE.getName(), val );
	}

	void PharmosTransactionRecord::setSupplierNo(const basar::Int32 val)
	{
        METHODNAME_DEF( PharmosTransactionRecord, setSupplierNo )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		m_YitTransactionRecord.setInt32( properties::pharmostransaction::SUPPLIERNO.getName(), val );
	}

	void PharmosTransactionRecord::setPurchaseOrderNo(const basar::VarString& val)
	{
        METHODNAME_DEF( PharmosTransactionRecord, setPurchaseOrderNo )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		m_YitTransactionRecord.setString( properties::pharmostransaction::PURCHASEORDERNO.getName(), val );
	}

	void PharmosTransactionRecord::setCostPrice(const basar::Decimal& val)
	{
        METHODNAME_DEF( PharmosTransactionRecord, setCostPrice )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		m_YitTransactionRecord.setDecimal( properties::pharmostransaction::COSTPRICE.getName(), val );
	}

	void PharmosTransactionRecord::setStorageLocation(const basar::VarString& val)
	{
        METHODNAME_DEF( PharmosTransactionRecord, setStorageLocation )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		m_YitTransactionRecord.setString( properties::pharmostransaction::STORAGELOCATION.getName(), val );
	}

	void PharmosTransactionRecord::setStorageArea(const basar::VarString& val)
	{
        METHODNAME_DEF( PharmosTransactionRecord, setStorageArea )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		m_YitTransactionRecord.setString( properties::pharmostransaction::STORAGEAREA.getName(), val );
	}

	void PharmosTransactionRecord::setStationNo(const basar::VarString& val)
	{
        METHODNAME_DEF( PharmosTransactionRecord, setStationNo )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		m_YitTransactionRecord.setString( properties::pharmostransaction::STATIONNO.getName(), val );
	}

	void PharmosTransactionRecord::setExpiryDateChangeFlag(const basar::Int16 val)
	{
        METHODNAME_DEF( PharmosTransactionRecord, setExpiryDateChangeFlag )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		m_YitTransactionRecord.setInt16( properties::pharmostransaction::EXPIRYDATECHANGEFLAG.getName(), val );
	}

	void PharmosTransactionRecord::setStorageLocationChangeFlag(const basar::Int16 val)
	{
        METHODNAME_DEF( PharmosTransactionRecord, setStorageLocationChangeFlag )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		m_YitTransactionRecord.setInt16( properties::pharmostransaction::STORAGELOCATIONCHANGEFLAG.getName(), val );
	}

	void PharmosTransactionRecord::setCostPriceChangeFlag(const basar::Int16 val)
	{
        METHODNAME_DEF( PharmosTransactionRecord, setCostPriceChangeFlag )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		m_YitTransactionRecord.setInt16( properties::pharmostransaction::COSTPRICECHANGEFLAG.getName(), val );
	}

	void PharmosTransactionRecord::setPharmacyPurchasePriceChangeFlag(const basar::Int16 val)
	{
        METHODNAME_DEF( PharmosTransactionRecord, setPharmacyPurchasePriceChangeFlag )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		m_YitTransactionRecord.setInt16( properties::pharmostransaction::PHARMACYPURCHASEPRICECHANGEFLAG.getName(), val );
	}

	void PharmosTransactionRecord::setPharmacySellPriceChangeFlag(const basar::Int16 val)
	{
        METHODNAME_DEF( PharmosTransactionRecord, setPharmacySellPriceChangeFlag )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		m_YitTransactionRecord.setInt16( properties::pharmostransaction::PHARMACYSELLPRICECHANGEFLAG.getName(), val );
	}

	void PharmosTransactionRecord::setPharmacyPurchasePrice(const basar::Decimal& val)
	{
        METHODNAME_DEF( PharmosTransactionRecord, setPharmacyPurchasePrice )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		m_YitTransactionRecord.setDecimal( properties::pharmostransaction::PHARMACYPURCHASEPRICE.getName(), val );
	}

	void PharmosTransactionRecord::setPharmacySellPrice(const basar::Decimal& val)
	{
        METHODNAME_DEF( PharmosTransactionRecord, setPharmacySellPrice )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		m_YitTransactionRecord.setDecimal( properties::pharmostransaction::PHARMACYSELLPRICE.getName(), val );
	}

	void PharmosTransactionRecord::setIbtBranchNo(const basar::Int16 val)
	{
        METHODNAME_DEF( PharmosTransactionRecord, setIbtBranchNo )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		m_YitTransactionRecord.setInt16( properties::pharmostransaction::IBTBRANCHNO.getName(), val );
	}

	void PharmosTransactionRecord::setCodeBlocage(const basar::VarString& val)
	{
        METHODNAME_DEF( PharmosTransactionRecord, setCodeBlocage )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		m_YitTransactionRecord.setString( properties::pharmostransaction::CODEBLOCAGE.getName(), val );
	}

	void PharmosTransactionRecord::setQuantityNatra(const basar::Int32 val)
	{
        METHODNAME_DEF( PharmosTransactionRecord, setQuantityNatra )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		m_YitTransactionRecord.setInt32( properties::pharmostransaction::QUANTITYNATRA.getName(), val );
	}

	void PharmosTransactionRecord::setOrderPositionNo(const basar::Int32 val)
	{
        METHODNAME_DEF( PharmosTransactionRecord, setOrderPositionNo )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		m_YitTransactionRecord.setInt32( properties::pharmostransaction::ORDERPOSITIONNO.getName(), val );
	}

	void PharmosTransactionRecord::setDailyClosing(const basar::Int32 val)
	{
        METHODNAME_DEF( PharmosTransactionRecord, setDailyClosing )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		m_YitTransactionRecord.setInt32( properties::pharmostransaction::DAILYCLOSING.getName(), val );
	}

	void PharmosTransactionRecord::setOrigin(const basar::Int16 val)
	{
        METHODNAME_DEF( PharmosTransactionRecord, setOrigin)
	    BLOG_TRACE_METHOD( getLogger(), fun );
		m_YitTransactionRecord.setInt16( properties::pharmostransaction::ORIGIN.getName(), val );
	}

	void PharmosTransactionRecord::setOrderSupplierNo(const basar::Int32 val)
	{
		METHODNAME_DEF(PharmosTransactionRecord, setOrderSupplierNo)
			BLOG_TRACE_METHOD(getLogger(), fun);
		m_YitTransactionRecord.setInt32(properties::pharmostransaction::ORDERSUPPLIERNO.getName(), val);
	}

	const basar::VarString& PharmosTransactionRecord::getSaveAccessMethod() const
	{
        METHODNAME_DEF( PharmosTransactionRecord, getSaveAccessMethod )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return lit::acc_pharmostransaction::SAVE_PHARMOSTRANSACTION;
	}

} // namespace core
} // namespace pharmosTransaction
} // namespace domMod
