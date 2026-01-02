//-------------------------------------------------------------------------------------------------------------------//
/*! \file		
 *  \brief		main interface for domain module of ifxorderheads (table pharmosbatchorderheads)
 *  \author		Julian Machata
 *  \date		17.10.2012
 */
//-------------------------------------------------------------------------------------------------------------------//

#ifndef GUARD_DOMMOD_PHARMOSBATCHORDER_PROCESSING_BATCHORDERPOSDM_H
#define GUARD_DOMMOD_PHARMOSBATCHORDER_PROCESSING_BATCHORDERPOSDM_H

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
	class BatchOrderPosDM : public domMod::batchOrder::core::SearchDMBase,
								public domMod::DMBase< InitParamsDMPtr, BatchOrderPosDM >
    {
        //--------------------------------------------------------------------------------------------------//
        // static declaration section
        //--------------------------------------------------------------------------------------------------//
        public:
            static const char* getClassName() { return "BatchOrderPosDM"; }

	    public:
			BatchOrderPosDM( const basar::db::aspect::ConnectionRef tcaconnection, libcsc_utils::ICSC_LoggerPtr csc_logger); 
		    virtual ~BatchOrderPosDM(); 

			void setInProcess( basar::db::aspect::AccessorPropertyTable_YIterator yitPos );																					
			void setClosed( basar::db::aspect::AccessorPropertyTable_YIterator yitPos );

        protected:
			virtual const basar::VarString&								getSaveAccessMethod() const;
		    virtual const basar::VarString&								getFindByPatternAccessMethod() const;
			virtual const basar::VarString&								getFindLastKeyAccessMethod() const;
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
		    BatchOrderPosDM(const BatchOrderPosDM& r);
		    BatchOrderPosDM& operator=(const BatchOrderPosDM& r);				

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
