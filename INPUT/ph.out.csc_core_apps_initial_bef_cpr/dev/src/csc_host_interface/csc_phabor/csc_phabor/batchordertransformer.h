//-------------------------------------------------------------------------------------------------------------------//
/*! \file		
 *  \brief		main interface for domain module of cicsorderheads (cics file VSAM.PHARMOSBATCHORDERPOS)
 *  \author		Julian Machata
 *  \date		17.10.2012
 */
//-------------------------------------------------------------------------------------------------------------------//

#ifndef GUARD_DOMMOD_PHARMOSBATCHORDER_PREPARATION_BATCHORDERTRANSFORMER_H
#define GUARD_DOMMOD_PHARMOSBATCHORDER_PREPARATION_BATCHORDERTRANSFORMER_H

#include "icsc_loggerptr.h"
#include "batchorder.h"
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
	class BatchOrderTransformer 
    {
	    public:
			BatchOrderTransformer( const libcsc_utils::ICSC_LoggerPtr csc_logger ); 
			virtual ~BatchOrderTransformer(); 

			void transformCics2Ifx ( domMod::batchOrder::core::BatchOrderPtr sourceCICS, domMod::batchOrder::core::BatchOrderPtr targetIFX );		    

	    private:	
            /////////////////////////////////////////////////////////////////////////
		    // private member methods
		    /////////////////////////////////////////////////////////////////////////
		    BatchOrderTransformer(const BatchOrderTransformer& r);
		    BatchOrderTransformer& operator=(const BatchOrderTransformer& r);

			void transformHead ( basar::db::aspect::AccessorPropertyTable_YIterator yitCicsHead, basar::db::aspect::AccessorPropertyTable_YIterator yitIfxHead );
			void transformPos  ( basar::db::aspect::AccessorPropertyTableRef yitCicsPosPropTab, basar::db::aspect::AccessorPropertyTable_YIterator yitCicsHead, basar::db::aspect::AccessorPropertyTableRef yitIfxPosPropTab );
			
			void transformHeadIfx2Pvxb ( basar::db::aspect::AccessorPropertyTable_YIterator yitIfxHead, basar::db::aspect::AccessorPropertyTable_YIterator yitPxvbHead );
			void transformPosIfx2Pvxb  ( basar::db::aspect::AccessorPropertyTableRef yitIfxPosPropTab, basar::db::aspect::AccessorPropertyTableRef yitPxvbPosPropTab );

			basar::Int16    strToInt16   		( basar::I18nString strInt );
			basar::Date 	intDate2BasarDate ( basar::Int32 valDate	);

			basar::db::aspect::AccessorPropertyTable_YIterator addPos( basar::db::aspect::AccessorPropertyTableRef propTab );

            /////////////////////////////////////////////////////////////////////////
		    // private member variables
		    /////////////////////////////////////////////////////////////////////////
			libcsc_utils::ICSC_LoggerPtr			m_CSC_Logger;
    }; 

} // namespace core
} // namespace batchOrder
} // namespace domMod

#endif 
