
#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDPROCESSHELPER_H
#define GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDPROCESSHELPER_H
//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include <icsc_loggerptr.h>

#include "ipxvbsessionptr.h"
#include "ipxvbdbconnectionptr.h"
#include "ipxvborderentryparamcheckerptr.h"
#include "pvhx01_includes.h"
#include "transactionrecordbaseptr.h"
#include "pxartbaseptr.h"
//----------------------------------------------------------------------------//
// forward declaration section
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
// class declaration setcion
//----------------------------------------------------------------------------//
namespace domMod
{
namespace pharmosTransaction
{
namespace processing
{
	class RecordProcessHelper
    {
        public:
	        RecordProcessHelper(pxVerbund::IPXVBSessionPtr session, pxVerbund::IPXVBOrderEntryParamCheckerPtr oeparam, pxVerbund::IPXVBDBConnectionPtr connection, libcsc_utils::ICSC_LoggerPtr logger);
	        virtual ~RecordProcessHelper(void);
			
            void                                        writeNarcTransferEntries(pxArtBasePtr artBase, const core::TransactionRecordBasePtr record);
			void                                        calcArtBaseStock(pxArtBasePtr artBase, const core::TransactionRecordBasePtr record);
			void                                        changeBatchSaleability(pxArtBasePtr artBase, const core::TransactionRecordBasePtr record);
            void                                        updateTenderProgress( const core::TransactionRecordBasePtr record );
			TransactionType                             getTransactionType(const core::TransactionRecordBasePtr record);

		private:
	        RecordProcessHelper(RecordProcessHelper&);
	        RecordProcessHelper& operator= (RecordProcessHelper&);

			basar::Int32                                getCustomerSupplierNo(const core::TransactionRecordBasePtr record);
            void                                        deleteLongTermLack(const core::TransactionRecordBasePtr record);

	        pxVerbund::IPXVBSessionPtr                  m_PXVBSession;
	        pxVerbund::IPXVBOrderEntryParamCheckerPtr   m_pxOrderEntryParam;
	        pxVerbund::IPXVBDBConnectionPtr             m_PXVBConnection;
			libcsc_utils::ICSC_LoggerPtr                m_CSC_Logger;
};
}//end namespace processing
}//end namespace pharmosTransaction
}//end namespace domMod
#endif //#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDPROCESSHELPER_H

