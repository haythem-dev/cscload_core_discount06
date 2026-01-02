//-------------------------------------------------------------------------------------------------------------------//
/*! \file		batchorder.h
 *  \brief		container for holding batchorder head with it's positions
 *  \author		Julian Machata
 *  \date		25.10.2012
 */
//-------------------------------------------------------------------------------------------------------------------//

#ifndef GUARD_DOMMOD_PHARMOSBATCHORDER_CORE_BATCHORDER_H
#define GUARD_DOMMOD_PHARMOSBATCHORDER_CORE_BATCHORDER_H

#include <iloggable.h>

#include "icsc_loggerptr.h"
#include "libbasardbaspect_accessorpropertytable_yiterator.h"
#include "libbasardbaspect_accessorpropertytable.h"
#include "batchorderptr.h"

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
	class BatchOrder : public libcsc_utils::ILoggable 
    {
        //--------------------------------------------------------------------------------------------------//
        // static declaration section
        //--------------------------------------------------------------------------------------------------//
	    public:
			BatchOrder(  basar::db::aspect::AccessorPropertyTable_YIterator yitOrderHead,  
						 basar::db::aspect::AccessorPropertyTableRef orderPositionsPropTab, 
						 libcsc_utils::ICSC_LoggerPtr csc_logger ); 

		    virtual ~BatchOrder(); 
			virtual basar::VarString									getLogMessage() const;

			basar::db::aspect::AccessorPropertyTable_YIterator			getOrderHead();				
			basar::db::aspect::AccessorPropertyTableRef					getOrderPositions();

			
            
	    private:	
            /////////////////////////////////////////////////////////////////////////
		    // private member methods
		    /////////////////////////////////////////////////////////////////////////
		    BatchOrder(const BatchOrder& r);
		    BatchOrder& operator=(const BatchOrder& r);				

            /////////////////////////////////////////////////////////////////////////
		    // private member variables
		    /////////////////////////////////////////////////////////////////////////
			libcsc_utils::ICSC_LoggerPtr										m_CSC_Logger;
			basar::db::aspect::AccessorPropertyTable_YIterator					m_OrderHead;		
			basar::db::aspect::AccessorPropertyTableRef							m_OrderPositions;
    }; 

} // namespace core
} // namespace batchOrder
} // namespace domMod

#endif 
