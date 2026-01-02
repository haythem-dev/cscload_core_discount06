//-------------------------------------------------------------------------------------------------//
/*! \file 
 *  \brief Domain module article
 *  \author 
 *  \date 
 */
//-------------------------------------------------------------------------------------------------//
#ifndef GUARD_CTRANSFERCSCTRANSACTIONRECORD_H
#define GUARD_CTRANSFERCSCTRANSACTIONRECORD_H

//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include "transactionrecordbase.h"

//-------------------------------------------------------------------------------------------------//
// namespace section
//-------------------------------------------------------------------------------------------------//
namespace domMod {
namespace pharmosTransaction {
namespace preparation {
    //-------------------------------------------------------------------------------------------------//
    // class declaration section
    //-------------------------------------------------------------------------------------------------//
	class CTransferCscTransactionRecord : public core::TransactionRecordBase
	{
        //--------------------------------------------------------------------------------------------------//
        // object declaration section
        //--------------------------------------------------------------------------------------------------//
	    public:

			CTransferCscTransactionRecord( basar::db::aspect::AccessorPropertyTable_YIterator yitTransactionRecord, AccessorInstanceRefWrapper& acc, libcsc_utils::ICSC_LoggerPtr csc_logger );
		    ~CTransferCscTransactionRecord();

            virtual void					startProcessing();
            virtual void					finishProcessing();

            virtual void					log();

			virtual basar::Int32			getTransferId() const;
			virtual basar::DateTime			getEntryDateTime() const; 
			virtual basar::Int32			getArticleNo() const;
			virtual basar::VarString		getFieldName() const;
			virtual basar::VarString		getFieldValue() const;
			virtual basar::Int32			getProcessedFlag() const;

			// BAD EVIL EX ORBITANT HACK 
			virtual basar::Int16			getKbvzFil() const { return 0; }
			virtual basar::Int32			getKbvzOffset() const { return 0; }
			virtual basar::Int32			getKbvzLfdNr() const { return 0; }
			virtual basar::DateTime			getKbvzDX01DateTime() const { return basar::DateTime::getCurrent(); }
			virtual basar::Int32			getKbvzDailyClosing() const { return 0; }
			virtual basar::VarString		getKbvzLgnr() const { return "";}
			// BAD EVIL EX ORBITANT HACK 

			virtual basar::VarString		getType() const;

		protected:
			virtual const basar::VarString&	getSaveAccessMethod() const;  

	    private:
		    CTransferCscTransactionRecord( const CTransferCscTransactionRecord& );
		    CTransferCscTransactionRecord& operator= ( const CTransferCscTransactionRecord& );                       			
	};

} // namespace preparation
} // namespace pharmosTransaction
} // end namespace domMod

#endif // GUARD_CTRANSFERCSCTRANSACTIONRECORD_H

