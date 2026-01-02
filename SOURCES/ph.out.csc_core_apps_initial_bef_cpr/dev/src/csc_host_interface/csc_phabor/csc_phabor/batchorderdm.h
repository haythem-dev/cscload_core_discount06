//-------------------------------------------------------------------------------------------------------------------//
/*! \file		
 *  \brief		domain module for handling batchorders on ifx side
 *  \author		Julian Machata
 *  \date		17.10.2012
 */
//-------------------------------------------------------------------------------------------------------------------//

#ifndef GUARD_DOMMOD_PHARMOSBATCHORDER_PROCESSING_BATCHORDERDM_H
#define GUARD_DOMMOD_PHARMOSBATCHORDER_PROCESSING_BATCHORDERDM_H

#include "dmbase.h"
#include "icsc_loggerptr.h"
#include "batchorderdminitstruct.h"
#include "batchorderdmbaseinitstruct.h"
#include "batchorderdmbase.h"
#include "ibatchorderstatusupdater.h"

//-------------------------------------------------------------------------------------------------//
// using declarations section
//-------------------------------------------------------------------------------------------------//
namespace basar
{
    namespace db
    {
        namespace aspect
        {
            class AccessorPropertyTable_YIterator;                    
			class AccessorPropertyTableRef;
            class ConnectionRef;
        }
    }
}


namespace domMod 
{		
namespace batchOrder
{
namespace processing
{
    //-------------------------------------------------------------------------------------------------//
    // class declaration section
    //-------------------------------------------------------------------------------------------------//
	class BatchOrderDM : public domMod::batchOrder::core::BatchOrderDMBase,
						 public domMod::batchOrder::util::IBatchOrderStatusUpdater
    {
	    public:
			BatchOrderDM( libcsc_utils::ICSC_LoggerPtr csc_logger,
						  domMod::batchOrder::processing::BatchOrderHeadDMPtr batchOrderHeadDM,
						  domMod::batchOrder::processing::BatchOrderPosDMPtr batchOrderPosDM ); 

		    virtual ~BatchOrderDM(); 		

			basar::db::aspect::AccessorPropertyTable_YIterator	getBatchOrderHeadSearchCriteria( const domMod::batchOrder::core::OffSetNo offSetNo, const basar::Int16 branchno );
			basar::db::aspect::AccessorPropertyTable_YIterator  getBatchOrderPosSearchCriteria ( const basar::db::aspect::AccessorPropertyTable_YIterator yitBatchOrderHead );
			virtual void	setBatchOrderInProcess		( basar::db::aspect::AccessorPropertyTable_YIterator head );
			virtual void	setBatchOrderClosed			( basar::db::aspect::AccessorPropertyTable_YIterator head );
			virtual void	setBatchOrderPosInProcess	( basar::db::aspect::AccessorPropertyTable_YIterator pos  );
			virtual void	setBatchOrderPosClosed		( basar::db::aspect::AccessorPropertyTable_YIterator pos  );
            
	    private:	
            /////////////////////////////////////////////////////////////////////////
		    // private member methods
		    /////////////////////////////////////////////////////////////////////////
		    BatchOrderDM(const BatchOrderDM& r);
		    BatchOrderDM& operator=(const BatchOrderDM& r);				

            virtual basar::db::aspect::AccessorPropertyTable_YIterator	getNextOrderHead();
			
            /////////////////////////////////////////////////////////////////////////
		    // private member variables
		    /////////////////////////////////////////////////////////////////////////
			libcsc_utils::ICSC_LoggerPtr								m_CSC_Logger;

			domMod::batchOrder::processing::BatchOrderHeadDMPtr			m_BatchOrderHeadDM;
			domMod::batchOrder::processing::BatchOrderPosDMPtr			m_BatchOrderPosDM;
    }; 

} // namespace processing
} // namespace batchOrder
} // namespace domMod

#endif 
