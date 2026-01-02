//-------------------------------------------------------------------------------------------------------------------//
/*! \file		
 *  \brief		container for iterating batchorders
 *  \author		Julian Machata
 *  \date		17.10.2012
 */
//-------------------------------------------------------------------------------------------------------------------//

#ifndef GUARD_DOMMOD_PHARMOSBATCHORDER_CORE_BATCHORDERCOLLECTION_H
#define GUARD_DOMMOD_PHARMOSBATCHORDER_CORE_BATCHORDERCOLLECTION_H

#include <icsc_loggerptr.h>

#include "libbasardbaspect_accessorpropertytable_yiterator.h"
#include "libbasardbaspect_accessorpropertytable.h"
#include "batchorderptr.h"
#include "batchorder.h"
#include "ibatchordergetterptr.h"
#include "ibatchordergetter.h"

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
namespace core
{
    //-------------------------------------------------------------------------------------------------//
    // class declaration section
    //-------------------------------------------------------------------------------------------------//
	class BatchOrderCollection 
    {
	    public:
			BatchOrderCollection( domMod::batchOrder::util::IBatchOrderGetterPtr batchOrderGetter, 
								  libcsc_utils::ICSC_LoggerPtr csc_logger ); 

		    virtual ~BatchOrderCollection(); 

			domMod::batchOrder::core::BatchOrderPtr getFirst();
			domMod::batchOrder::core::BatchOrderPtr getNext();
            
	    private:	
            /////////////////////////////////////////////////////////////////////////
		    // private member methods
		    /////////////////////////////////////////////////////////////////////////
		    BatchOrderCollection(const BatchOrderCollection& r);
		    BatchOrderCollection& operator=(const BatchOrderCollection& r);		

			domMod::batchOrder::core::BatchOrderPtr						getNewBatchOrder();

			basar::db::aspect::AccessorPropertyTableRef					getPositions();


            /////////////////////////////////////////////////////////////////////////
		    // private member variables
		    /////////////////////////////////////////////////////////////////////////
			libcsc_utils::ICSC_LoggerPtr								m_CSC_Logger;
			domMod::batchOrder::util::IBatchOrderGetterPtr				m_BatchOrderGetterPtr;
			domMod::batchOrder::core::BatchOrderPtr						m_CurrentBatchOrderPtr;
			basar::db::aspect::AccessorPropertyTable_YIterator			m_CurrentBatchOrderHeadYit;
    }; 

} // namespace core
} // namespace batchOrder
} // namespace domMod

#endif 
