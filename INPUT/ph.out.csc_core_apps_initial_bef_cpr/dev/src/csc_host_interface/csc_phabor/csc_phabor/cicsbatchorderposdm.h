//-------------------------------------------------------------------------------------------------------------------//
/*! \file		
 *  \brief		main interface for domain module of cicsorderheads (cics file VSAM.DKBAZP)
 *  \author		Julian Machata
 *  \date		17.10.2012
 */
//-------------------------------------------------------------------------------------------------------------------//

#ifndef GUARD_DOMMOD_PHARMOSBATCHORDER_PREPARATION_CICSBATCHORDERPOSDM_H
#define GUARD_DOMMOD_PHARMOSBATCHORDER_PREPARATION_CICSBATCHORDERPOSDM_H

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
namespace preparation
{
    //-------------------------------------------------------------------------------------------------//
    // class declaration section
    //-------------------------------------------------------------------------------------------------//
	class CICSBatchOrderPosDM : public domMod::batchOrder::core::SearchDMBase,
								public domMod::DMBase< InitParamsDMPtr, CICSBatchOrderPosDM >
    {
        //--------------------------------------------------------------------------------------------------//
        // static declaration section
        //--------------------------------------------------------------------------------------------------//
         public:
             static const char* getClassName() { return "CICSBatchOrderPosDM"; }

	    public:
			CICSBatchOrderPosDM( const basar::db::aspect::ConnectionRef tcaconnection,	libcsc_utils::ICSC_LoggerPtr csc_logger); 
		    virtual ~CICSBatchOrderPosDM(); 
			
			void clearTable();

        protected:
		    virtual const basar::VarString&								getFindByPatternAccessMethod() const;
			virtual const basar::VarString&								getFindLastKeyAccessMethod() const;
			virtual const basar::VarString&								getSaveAccessMethod() const;  
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
		    CICSBatchOrderPosDM(const CICSBatchOrderPosDM& r);
		    CICSBatchOrderPosDM& operator=(const CICSBatchOrderPosDM& r);				

            void                                                        finishQuery();

            /////////////////////////////////////////////////////////////////////////
		    // private member variables
		    /////////////////////////////////////////////////////////////////////////
            InitParamsDMPtr                                             m_InitParamsDMPtr;
			searchyiterator::SearchYIteratorPtr							m_SearchYIterator;
    }; 

} // namespace preparation
} // namespace batchOrder
} // namespace domMod

#endif 
