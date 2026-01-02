//-------------------------------------------------------------------------------------------------//
/*! \file 
 *  \brief		base functionality for batchorder domain modules
 *  \author		Julian Machata	
 *  \date		26.10.2012
 */
//-------------------------------------------------------------------------------------------------//
#ifndef GUARD_DOMMOD_BATCHORDER_CORE_SEARCHDMBASE_H
#define GUARD_DOMMOD_BATCHORDER_CORE_SEARCHDMBASE_H

//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include <libbasar_definitions.h>
#include <libbasardbaspect_definitions.h>
#include <accessorinstancerefwrapper.h>
#include <searchyiteratorptr.h>
#include <libbasardbaspect_accessorpropertytable.h>

#include "cmndm.h"
#include "searchdmbase_definitions.h"
#include "icsc_loggerptr.h"

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

//-------------------------------------------------------------------------------------------------//
// namespace section
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
    /*!\brief  */
	class SearchDMBase 
	{
        //--------------------------------------------------------------------------------------------------//
        // object declaration section
        //--------------------------------------------------------------------------------------------------//
	    public:
		    ~SearchDMBase();

			virtual void                                                findOpen( basar::db::aspect::AccessorPropertyTable_YIterator yitSearch );
			virtual basar::Int32                                        findLastKey( const basar::Int16 branchno );
			virtual void												save ( basar::db::aspect::AccessorPropertyTable_YIterator yitSave );

		    void                                                        resetSearchYit();
            basar::db::aspect::AccessorPropertyTable_YIterator          getSearchYit();
			basar::db::aspect::AccessorPropertyTableRef					getPropTab();
      	
        protected:
			SearchDMBase( const basar::db::aspect::ConnectionRef conn, const basar::VarString& accDefName, libcsc_utils::ICSC_LoggerPtr csc_logger );

			virtual void												evaluatePreconditionFindByPattern() = 0;
            virtual basar::db::aspect::AccessorPropertyTable_YIterator  prepareFindOpenSearchCriteria( basar::db::aspect::AccessorPropertyTable_YIterator yitSearch ) = 0;
			virtual basar::db::aspect::AccessorPropertyTable_YIterator  prepareFindLastKeySearchCriteria( const basar::Int16 branchno ) = 0;
			virtual const basar::VarString&								getFindByPatternAccessMethod() const = 0;            
			virtual const basar::VarString&								getFindLastKeyAccessMethod() const = 0;
			virtual const basar::VarString&								getSaveAccessMethod() const = 0;            
			void                                                        findByPattern( basar::db::aspect::AccessorPropertyTable_YIterator yitSearch );

			void                                                        executeAccessor( const basar::VarString& accessMethod, 
                                                                                         basar::db::aspect::AccessorPropertyTable_YIterator yit2Execute,
                                                                                         bool clearBeforeSelect = true, 
                                                                                         bool flagExcept = true, 
                                                                                         const basar::Int32 dbHint = basar::db::aspect::NO_HINT );

			basar::Decimal                                              executeAggregateAccessor( const basar::VarString& accessMethod, 
                                                                                         basar::db::aspect::AccessorPropertyTable_YIterator yit2Execute );

			void														clearPropertyTable();
			AccessorInstanceRefWrapper&									getAccessor();
			virtual searchyiterator::SearchYIteratorPtr					getSearchYIterator() = 0;
			virtual const log4cplus::Logger&							getLogger() const;
			virtual libcsc_utils::ICSC_LoggerPtr						getCSC_Logger() const;        

	    private:
            /////////////////////////////////////////////////////////////////////////
		    // private member methods
		    /////////////////////////////////////////////////////////////////////////
		    SearchDMBase(const SearchDMBase& );
		    SearchDMBase& operator= (const SearchDMBase& );

		    /////////////////////////////////////////////////////////////////////////
		    // private member variables
		    /////////////////////////////////////////////////////////////////////////
			libcsc_utils::ICSC_LoggerPtr					m_CSC_Logger;
            AccessorInstanceRefWrapper                      m_Accessor;
	};
} // namespace core
} // namespace batchOrder
} // end namespace domMod

#endif
