//-------------------------------------------------------------------------------------------------------------------//
/*! \file		
 *  \brief		main interface for domain module of ifxorderitems (table pharmosbatchorderpos)
 *  \author		Julian Machata
 *  \date		17.10.2012
 */
//-------------------------------------------------------------------------------------------------------------------//

#ifndef GUARD_DOMMOD_PHARMOSBATCHORDER_PROCESSING_BATCHORDERHEADDM_H
#define GUARD_DOMMOD_PHARMOSBATCHORDER_PROCESSING_BATCHORDERHEADDM_H

#include "dmbase.h"
#include "icsc_loggerptr.h"
#include "searchdmbase.h"
#include "initparamsdmptr.h"

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
	class BatchOrderHeadDM : public domMod::batchOrder::core::SearchDMBase,
							 public domMod::DMBase< InitParamsDMPtr, BatchOrderHeadDM >
    {
        //--------------------------------------------------------------------------------------------------//
        // static declaration section
        //--------------------------------------------------------------------------------------------------//
        public:
            static const char* getClassName() { return "BatchOrderHeadDM"; }

	    public:
			BatchOrderHeadDM( const basar::db::aspect::ConnectionRef tcaconnection, libcsc_utils::ICSC_LoggerPtr csc_logger); 
		    virtual ~BatchOrderHeadDM(); 

			void														setInProcess( basar::db::aspect::AccessorPropertyTable_YIterator yitHead );																					
			void														setClosed( basar::db::aspect::AccessorPropertyTable_YIterator yitHead );

        protected:
		   
			virtual const basar::VarString&								getFindByPatternAccessMethod() const;
			virtual const basar::VarString&								getFindLastKeyAccessMethod() const;
			virtual const basar::VarString&								getSaveAccessMethod() const;
			basar::db::aspect::AccessorPropertyTable_YIterator			getBatchOrderHeadSearchCriteria( const domMod::batchOrder::core::OffSetNo offSetNo );

			virtual searchyiterator::SearchYIteratorPtr					getSearchYIterator();
			
		    virtual void												evaluatePreconditionFindByPattern();
            virtual void                                                doInit( const InitParamsDMPtr );
	        virtual void                                                doShutdown();
            virtual basar::db::aspect::AccessorPropertyTable_YIterator  prepareFindOpenSearchCriteria( basar::db::aspect::AccessorPropertyTable_YIterator yitSearch );
			virtual basar::db::aspect::AccessorPropertyTable_YIterator  prepareFindLastKeySearchCriteria( const basar::Int16 branchno );

	    private:	
            /////////////////////////////////////////////////////////////////////////
		    // private member methods
		    /////////////////////////////////////////////////////////////////////////
		    BatchOrderHeadDM(const BatchOrderHeadDM& r);
		    BatchOrderHeadDM& operator=(const BatchOrderHeadDM& r);				

            void                                                        finishQuery();

            /////////////////////////////////////////////////////////////////////////
		    // private member variables
		    /////////////////////////////////////////////////////////////////////////
            InitParamsDMPtr                                             m_InitParamsDMPtr;
			searchyiterator::SearchYIteratorPtr							m_SearchYIterator;
    }; 

} // namespace processing
} // namespace batchOrder
} // namespace domMod

#endif 
