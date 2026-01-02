//-------------------------------------------------------------------------------------------------------------------//
/*! \file		
 *  \brief		domain module for handling batchorders
 *  \author		Julian Machata
 *  \date		17.10.2012
 */
//-------------------------------------------------------------------------------------------------------------------//

#ifndef GUARD_DOMMOD_PHARMOSBATCHORDER_CORE_BATCHORDERDMBASE_H
#define GUARD_DOMMOD_PHARMOSBATCHORDER_CORE_BATCHORDERDMBASE_H

#include "dmbase.h"
#include "icsc_loggerptr.h"
#include "searchdmbase_definitions.h"
#include "searchdmbaseptr.h"
#include "searchdmbase.h"
#include "batchordercollectionptr.h"
#include "batchordercollection.h"
#include "initparamsdmptr.h"
#include "itransferkeygetter.h"
#include "batchorderdmbaseinitstruct.h"

//-------------------------------------------------------------------------------------------------//
// namespace
//-------------------------------------------------------------------------------------------------//

namespace domMod 
{		
namespace batchOrder
{
namespace core
{
    //-------------------------------------------------------------------------------------------------//
    // class declaration section
    //-------------------------------------------------------------------------------------------------//
	class BatchOrderDMBase : public domMod::batchOrder::util::ITransferKeyGetter,
						 public	domMod::batchOrder::util::IBatchOrderGetter,
						 public domMod::DMBase< BatchOrderDMBaseInitStruct, BatchOrderDMBase >
    {
		//friend class IBatchOrderGetter;

        //--------------------------------------------------------------------------------------------------//
        // static declaration section
        //--------------------------------------------------------------------------------------------------//
        public:
            static const char* getClassName() { return "BatchOrderDMBase"; }

	    public:
			BatchOrderDMBase( libcsc_utils::ICSC_LoggerPtr csc_logger ); 

		    virtual ~BatchOrderDMBase(); 

            domMod::batchOrder::core::BatchOrderCollectionPtr			findOpenOrders( const domMod::batchOrder::core::OffSetNo offSetNo, const basar::Int16 branchno );
			domMod::batchOrder::core::BatchOrderPtr						getEmptyBatchOrder();
			void														saveBatchOrder( domMod::batchOrder::core::BatchOrderPtr	batchOrder );
			
			virtual basar::Int32										getLastKey( const basar::Int16 branchno );			

        protected:
		    virtual void                                                doInit( const BatchOrderDMBaseInitStruct );
	        virtual void                                                doShutdown();
			virtual basar::db::aspect::AccessorPropertyTable_YIterator	getCurrentHead();
			virtual void												setCurrentHead( basar::db::aspect::AccessorPropertyTable_YIterator next );
			virtual basar::db::aspect::AccessorPropertyTableRef			getCurrentPositions();
			virtual basar::db::aspect::AccessorPropertyTable_YIterator	getFirstOrderHead();
			virtual basar::db::aspect::AccessorPropertyTable_YIterator	getNextOrderHead() = 0;
			virtual basar::db::aspect::AccessorPropertyTableRef			getBatchOrderHeads();
			virtual basar::db::aspect::AccessorPropertyTableRef			getBatchOrderPositions( basar::db::aspect::AccessorPropertyTable_YIterator yitBatchOrderHead );

			virtual basar::db::aspect::AccessorPropertyTable_YIterator	getBatchOrderHeadSearchCriteria(const domMod::batchOrder::core::OffSetNo offSetNo, const basar::Int16 branchno) = 0;
			virtual basar::db::aspect::AccessorPropertyTable_YIterator	getBatchOrderPosSearchCriteria(const basar::db::aspect::AccessorPropertyTable_YIterator yitBatchOrderHead ) = 0;
			basar::db::aspect::AccessorPropertyTable_YIterator			getOrderHeadSearchYit();
			basar::db::aspect::AccessorPropertyTable_YIterator			getOrderPosSearchYit();
            
	    private:	
            /////////////////////////////////////////////////////////////////////////
		    // private member methods
		    /////////////////////////////////////////////////////////////////////////
		    BatchOrderDMBase(const BatchOrderDMBase& r);
		    BatchOrderDMBase& operator=(const BatchOrderDMBase& r);				

            void                                                        finishQuery();
			domMod::batchOrder::core::BatchOrderCollectionPtr			getNewBatchOrderCollection( domMod::batchOrder::util::IBatchOrderGetterPtr batchOrderGetter);
			domMod::batchOrder::util::IBatchOrderGetterPtr				getBatchOrderGetter();

            /////////////////////////////////////////////////////////////////////////
		    // private member variables
		    /////////////////////////////////////////////////////////////////////////
			libcsc_utils::ICSC_LoggerPtr								m_CSC_Logger;
            InitParamsDMPtr                                             m_InitParamsDMPtr;
			domMod::batchOrder::core::SearchDMBasePtr					m_OrderHeadDMPtr;
			domMod::batchOrder::core::SearchDMBasePtr					m_OrderPosDMPtr;
			domMod::batchOrder::util::IBatchOrderGetterPtr				m_BatchOrderGetterPtr;
			basar::db::aspect::AccessorPropertyTable_YIterator			m_CurrentBatchOrderHeadYit;
    }; 

} // namespace core
} // namespace batchOrder
} // namespace domMod

#endif 
