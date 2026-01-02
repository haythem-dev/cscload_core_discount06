//-------------------------------------------------------------------------------------------------------------------//
/*! \file		
 *  \brief		domain module for handling batchorders (head and pos)
 *  \author		Julian Machata
 *  \date		17.10.2012
 */
//-------------------------------------------------------------------------------------------------------------------//

#ifndef GUARD_DOMMOD_PHARMOSBATCHORDER_PREPARATION_CICSBATCHORDERDM_H
#define GUARD_DOMMOD_PHARMOSBATCHORDER_PREPARATION_CICSBATCHORDERDM_H

#include "icsc_loggerptr.h"
#include "cicsbatchorderdminitstruct.h"
#include "batchorderdmbase.h"
#include "cicsbatchorderposdmptr.h"
#include "cicsbatchorderheaddmptr.h"
#include "cicsbatchorderposdm.h"
#include "cicsbatchorderheaddm.h"

//-------------------------------------------------------------------------------------------------//
// namespace
//-------------------------------------------------------------------------------------------------//

namespace domMod 
{		
namespace batchOrder
{
namespace preparation
{
    //-------------------------------------------------------------------------------------------------//
    // class declaration section
    //-------------------------------------------------------------------------------------------------//
	class CICSBatchOrderDM : public domMod::batchOrder::core::BatchOrderDMBase
    {
	    public:
			CICSBatchOrderDM( libcsc_utils::ICSC_LoggerPtr csc_logger ); 
		    virtual ~CICSBatchOrderDM(); 

			virtual basar::Int32										getLastKey();	
			virtual basar::db::aspect::AccessorPropertyTable_YIterator	getBatchOrderHeadSearchCriteria( const domMod::batchOrder::core::OffSetNo offSetNo, const basar::Int16 branchno );
			virtual basar::db::aspect::AccessorPropertyTable_YIterator	getBatchOrderPosSearchCriteria ( const basar::db::aspect::AccessorPropertyTable_YIterator yitBatchOrderHead );

			void injectCICSBatchOrderPosDMPtr		(domMod::batchOrder::preparation::CICSBatchOrderPosDMPtr		cscBatchOrderPosDMPtr		){ m_CICSBatchOrderPosDM = cscBatchOrderPosDMPtr; };
			void injectCICSBatchOrderHeadDMPtr		(domMod::batchOrder::preparation::CICSBatchOrderHeadDMPtr		cscBatchOrderHeadDMPtr		){ m_CICSBatchOrderHeadDM = cscBatchOrderHeadDMPtr; };

			void setStatusTransfered( basar::db::aspect::AccessorPropertyTable_YIterator yitCicsHead );

			void clearTables();
            
	    private:	
            /////////////////////////////////////////////////////////////////////////
		    // private member methods
		    /////////////////////////////////////////////////////////////////////////
		    CICSBatchOrderDM(const CICSBatchOrderDM& r);
		    CICSBatchOrderDM& operator=(const CICSBatchOrderDM& r);				

			virtual basar::db::aspect::AccessorPropertyTable_YIterator	getFirstOrderHead();
            virtual basar::db::aspect::AccessorPropertyTable_YIterator	getNextOrderHead();
			basar::Int32												getPositionCountFromPositions();
			basar::Int32												getPositionCountFromHead();
			
            /////////////////////////////////////////////////////////////////////////
		    // private member variables
		    /////////////////////////////////////////////////////////////////////////
			libcsc_utils::ICSC_LoggerPtr								m_CSC_Logger;

			domMod::batchOrder::preparation::CICSBatchOrderPosDMPtr		m_CICSBatchOrderPosDM;
			domMod::batchOrder::preparation::CICSBatchOrderHeadDMPtr	m_CICSBatchOrderHeadDM;
			domMod::batchOrder::core::OffSetNo							m_PreviousOffSetNo;
				
    }; 

} // namespace preparation
} // namespace batchOrder
} // namespace domMod

#endif 
