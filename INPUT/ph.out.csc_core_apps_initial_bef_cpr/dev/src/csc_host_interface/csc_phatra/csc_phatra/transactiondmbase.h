//-------------------------------------------------------------------------------------------------//
/*! \file 
 *  \brief Domain module article
 *  \author 
 *  \date 
 */
//-------------------------------------------------------------------------------------------------//
#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_CORE_TRANSACTIONDMBASE_H
#define GUARD_DOMMOD_PHARMOSTRANSACTION_CORE_TRANSACTIONDMBASE_H

//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include <libbasardbaspect_definitions.h>
#include <accessorinstancerefwrapper.h>
#include <searchyiteratorptr.h>
#include "transactionrecordbaseptr.h"
#include "itransactionrecordcreator.h"
#include "transactiondmbase_definitions.h"
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
        }
    }
}

//-------------------------------------------------------------------------------------------------//
// namespace section
//-------------------------------------------------------------------------------------------------//
namespace domMod
{
namespace pharmosTransaction
{
namespace core
{
    //-------------------------------------------------------------------------------------------------//
    // class declaration section
    //-------------------------------------------------------------------------------------------------//
    /*!\brief  */
	class TransactionDMBase //: public util::ITransactionRecordCreator
	{
        //--------------------------------------------------------------------------------------------------//
        // object declaration section
        //--------------------------------------------------------------------------------------------------//
	    public:
		    ~TransactionDMBase();
            core::TransactionRecordBasePtr								getFirstTransactionRecord();
			core::TransactionRecordBasePtr								getNextTransactionRecord();
			TransactionRecordBasePtr									addEmptyTransactionRecord();

		    void                                                        resetSearchYit();
            basar::db::aspect::AccessorPropertyTable_YIterator          getSearchYit();

            virtual void                                                findOpen( const domMod::pharmosTransaction::core::OffSetNo offSetNo = INVALID_OFFSET );			
            
			virtual void                                                finishQuery() = 0;

        protected:
			TransactionDMBase( const basar::db::aspect::ConnectionRef conn, const basar::VarString& accDefName, libcsc_utils::ICSC_LoggerPtr csc_logger );
            void                                                        findByPattern( basar::db::aspect::AccessorPropertyTable_YIterator yitSearch );
            void                                                        executeAccessor( const basar::VarString& accessMethod, 
                                                                                         basar::db::aspect::AccessorPropertyTable_YIterator yit2Execute,
                                                                                         const bool clearBeforeSelect = true, 
                                                                                         const bool flagExcept = true, 
                                                                                         const basar::Int32 dbHint = basar::db::aspect::NO_HINT );

            virtual const log4cplus::Logger&							getLogger() const;
			virtual libcsc_utils::ICSC_LoggerPtr						getCSC_Logger() const;
			virtual TransactionRecordBasePtr							createTransactionRecord(basar::db::aspect::AccessorPropertyTable_YIterator yit, AccessorInstanceRefWrapper& acc) = 0;
            virtual const basar::VarString&								getFindByPatternAccessMethod() const = 0;            
			virtual void												evaluatePreconditionFindByPattern();
            virtual basar::db::aspect::AccessorPropertyTable_YIterator  prepareFindOpenSearchCriteria( const domMod::pharmosTransaction::core::OffSetNo ) = 0;
            
            void														clearPropertyTable();
			
			AccessorInstanceRefWrapper&									getAccessor();
	        /*void                                                    doInit( const ArticleInitParams& );
	        void                                                    doShutdown();*/

	    private:
            /////////////////////////////////////////////////////////////////////////
		    // private member methods
		    /////////////////////////////////////////////////////////////////////////
		    TransactionDMBase(const TransactionDMBase& );
		    TransactionDMBase& operator= (const TransactionDMBase& );

            searchyiterator::SearchYIteratorPtr             getSearchYIterator();
            basar::db::aspect::AccessorPropertyTableRef     getPropTab();

		    /////////////////////////////////////////////////////////////////////////
		    // private member variables
		    /////////////////////////////////////////////////////////////////////////
			libcsc_utils::ICSC_LoggerPtr			        m_CSC_Logger;
            //ArticleInitParams								m_InitParams;
            searchyiterator::SearchYIteratorPtr             m_SearchYIterator;
            AccessorInstanceRefWrapper                      m_Accessor;
			TransactionRecordBasePtr						m_TransactionRecord;
	};
} // namespace core
} // namespace pharmosTransaction
} // end namespace domMod

#endif

