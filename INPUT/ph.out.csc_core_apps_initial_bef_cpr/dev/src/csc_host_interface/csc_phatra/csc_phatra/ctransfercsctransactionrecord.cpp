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
#include "ctransfercsctransactionrecord.h"
#include "ctransfercsc_definitions.h"
#include "accessorinstancerefwrapper.h"
#include "property_definitions.h"
#include "recordtypeclassifier_definitions.h"
#include "pharmostransactionrecord.h"
#include <icsc_logger.h>

//-------------------------------------------------------------------------------------------------//
// class definition section
//-------------------------------------------------------------------------------------------------//
namespace domMod {
namespace pharmosTransaction {
namespace preparation {
    //--------------------------------------------------------------------------------------------------//
    // object definition section
    //--------------------------------------------------------------------------------------------------//
	CTransferCscTransactionRecord::CTransferCscTransactionRecord( basar::db::aspect::AccessorPropertyTable_YIterator yitTransactionRecord
		, AccessorInstanceRefWrapper& acc, libcsc_utils::ICSC_LoggerPtr csc_logger )
        : TransactionRecordBase( yitTransactionRecord, acc, csc_logger )	
	{
        METHODNAME_DEF( CTransferCscTransactionRecord, CTransferCscTransactionRecord )
        BLOG_TRACE_METHOD( getLogger(), fun );		
	}

	CTransferCscTransactionRecord::~CTransferCscTransactionRecord()
	{
        METHODNAME_DEF( CTransferCscTransactionRecord, ~CTransferCscTransactionRecord )
        BLOG_TRACE_METHOD( getLogger(), fun );
	}

    void CTransferCscTransactionRecord::log()
    {
        basar::VarString msg;
        basar::VarString type = getType();
        msg.format("processing CTransferCscTransactionRecord %d of type %s ", getTransferId(), type.c_str());

        m_CSC_Logger->log(log4cplus::INFO_LOG_LEVEL, msg);
    }

	basar::VarString CTransferCscTransactionRecord::getType() const
	{
        METHODNAME_DEF( CTransferCscTransactionRecord, getType )
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

		return util::recordtypes::RECORDTYPE_CHANGEARTICLEMASTERDATA;
	}

	void CTransferCscTransactionRecord::startProcessing()
	{
        METHODNAME_DEF( CTransferCscTransactionRecord, startProcessing )
        BLOG_TRACE_METHOD( getLogger(), fun );
		// no implementation needed for preparation phase
	}

	void CTransferCscTransactionRecord::finishProcessing()
	{
        METHODNAME_DEF( CTransferCscTransactionRecord, finishProcessing )
        BLOG_TRACE_METHOD( getLogger(), fun );
		// no implementation needed for preparation phase
	}

	basar::Int32 CTransferCscTransactionRecord::getTransferId() const
	{
		return m_YitTransactionRecord.getInt32(properties::ctransfercsc::TRANSFERID);
	}
	
	basar::DateTime CTransferCscTransactionRecord::getEntryDateTime() const
	{
		return m_YitTransactionRecord.getDateTime(properties::ctransfercsc::ENTRYDATETIME);
	}

	basar::Int32 CTransferCscTransactionRecord::getArticleNo() const
	{
		return m_YitTransactionRecord.getInt32(properties::ctransfercsc::ARTICLENO);
	}

	basar::VarString CTransferCscTransactionRecord::getFieldName() const
	{
		return m_YitTransactionRecord.getString(properties::ctransfercsc::FIELDNAME);
	}

	basar::VarString CTransferCscTransactionRecord::getFieldValue() const
	{
		return m_YitTransactionRecord.getString(properties::ctransfercsc::FIELDVALUE);
	}

	basar::Int32 CTransferCscTransactionRecord::getProcessedFlag() const
	{
		return m_YitTransactionRecord.getInt32(properties::ctransfercsc::PROCESSEDFLAG);
	}


	const basar::VarString& CTransferCscTransactionRecord::getSaveAccessMethod() const
	{
		return lit::acc_ctransfercsc::SAVE_CTRANSFERCSC;
	}

} // namespace preparation
} // namespace pharmosTransaction
} // namespace domMod
