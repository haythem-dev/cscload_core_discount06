    //-------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief Domain module article
 *  \author
 *  \date
 */
//-------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include <libbasar_definitions.h>
#include <libbasardbaspect.h>
#include "transactiondmbase.h"
#include "transactionrecordbase.h"
#include "transactiondmbase_definitions.h"
#include "property_definitions.h"
#include <icsc_logger.h>
#include <searchyiterator.h>
#include <executeerrorenum2stringmapper.h>
#include <exceptionhandler.h>
#include <accessorexecutionexception.h>

//-------------------------------------------------------------------------------------------------//
// using declarations section
//-------------------------------------------------------------------------------------------------//
namespace domMod
{
    namespace pharmosTransaction
    {
        namespace core
        {
            using basar::db::aspect::AccessorPropertyTable_YIterator;
            using basar::db::aspect::AccessorPropertyTable_XIterator;
            using basar::db::aspect::AccessorPropertyTableRef;
            using basar::db::aspect::ExecuteResultInfo;
            using basar::db::aspect::AccessorInstanceRef;
            using basar::db::aspect::HOLD_RECORDSET;
        }
    }
}

//-------------------------------------------------------------------------------------------------//
// class definition section
//-------------------------------------------------------------------------------------------------//
namespace domMod
{
namespace pharmosTransaction
{
namespace core
{
    //--------------------------------------------------------------------------------------------------//
    // object definition section
    //--------------------------------------------------------------------------------------------------//
    TransactionDMBase::TransactionDMBase( const basar::db::aspect::ConnectionRef conn, const basar::VarString& accDefName, libcsc_utils::ICSC_LoggerPtr csc_logger )
        : m_CSC_Logger( csc_logger ), m_Accessor( accDefName, conn )
    {
        METHODNAME_DEF( TransactionDM, TransactionDM )
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
    }

    TransactionDMBase::~TransactionDMBase()
    {
        METHODNAME_DEF( TransactionDMBase, ~TransactionDMBase )
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
    }

    //-------------------------------------------------------------------------------------------------------------------//
    void TransactionDMBase::clearPropertyTable()
    {
        METHODNAME_DEF( TransactionDMBase, clearPropertyTable );
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

        if (!m_Accessor.isNull())
        {
            m_Accessor.get().getPropertyTable().clear();
        }
    }

    //-------------------------------------------------------------------------------------------------------------------//
    AccessorInstanceRefWrapper& TransactionDMBase::getAccessor()
    {
        METHODNAME_DEF( TransactionDMBase, getFirstTransactionRecord );
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

        return m_Accessor;
    }

    //-------------------------------------------------------------------------------------------------------------------//
    core::TransactionRecordBasePtr TransactionDMBase::getFirstTransactionRecord()
    {
        METHODNAME_DEF( TransactionDMBase, getFirstTransactionRecord );
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

        if( 0 == m_TransactionRecord.get() )
        {
            m_TransactionRecord = createTransactionRecord( getPropTab().begin(), m_Accessor );
        }
        else
        {
            m_TransactionRecord->setTransactionRecord( getPropTab().begin() );
        }

        return m_TransactionRecord;
    }

    core::TransactionRecordBasePtr TransactionDMBase::getNextTransactionRecord()
    {
        METHODNAME_DEF( TransactionDMBase, getNextTransactionRecord );
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

        AccessorPropertyTable_YIterator yitTrans = m_TransactionRecord->getTransactionRecord();
        m_TransactionRecord->setTransactionRecord(++yitTrans);
        return m_TransactionRecord;
    }

    TransactionRecordBasePtr TransactionDMBase::addEmptyTransactionRecord()
    {
        METHODNAME_DEF( TransactionDMBase, addEmptyTransactionRecord )
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

        return createTransactionRecord( getPropTab().insert( basar::FOR_INSERT ), m_Accessor );
    }

    AccessorPropertyTableRef TransactionDMBase::getPropTab()
    {
        METHODNAME_DEF( TransactionDMBase, getPropTab )
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

        return getAccessor().get().getPropertyTable();
    }

    void TransactionDMBase::resetSearchYit()
    {
        METHODNAME_DEF( TransactionDMBase, resetSearchYit )
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

        if (NULL != m_SearchYIterator.get())
        {
            m_SearchYIterator->reset();
        }
    }

    AccessorPropertyTable_YIterator TransactionDMBase::getSearchYit()
    {
        METHODNAME_DEF( TransactionDMBase, getSearchYit )
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

        return getSearchYIterator()->get();
    }

    searchyiterator::SearchYIteratorPtr TransactionDMBase::getSearchYIterator()
    {
        METHODNAME_DEF( TransactionDMBase, getSearchYIterator )
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

        //using namespace properties;
        if( NULL == m_SearchYIterator.get() ){
            m_SearchYIterator = domMod::searchyiterator::SearchYIteratorPtr(
                new domMod::searchyiterator::SearchYIterator( properties::dkbvz::RECORDOFFSET.toDescriptionString() +
                                                      properties::dkbvz::CSCPROCESSINGSTATUS.toDescriptionString() +
                                                      properties::pharmostransaction::PROCESSINGSTATUS.toDescriptionString() +
                                                      properties::pharmostransaction::BRANCHNO.toDescriptionString() +
                                                      properties::ctransfercsc::ZDPHOST.toDescriptionString() +
                                                      properties::ctransfercsc::ZDPDATABASE.toDescriptionString() +
                                                      properties::ctransfercsc::ENTRYDATETIME.toDescriptionString(),
                                                      // TODO indiviualisierung der searchyit attribute
                                                      m_CSC_Logger->getLogger()
                                                    )
            );
        }

        return m_SearchYIterator;
    }

    void TransactionDMBase::evaluatePreconditionFindByPattern()
    {
        METHODNAME_DEF( TransactionDMBase, evaluatePreconditionFindByPattern )
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
    }

    void TransactionDMBase::executeAccessor( const basar::VarString& accessMethod, basar::db::aspect::AccessorPropertyTable_YIterator yit2Execute,
                                             const bool clearBeforeSelect /*= true*/, const bool flagExcept /*= true*/,
                                             const basar::Int32 dbHint /*= basar::db::aspect::NO_HINT*/ )
    {
        METHODNAME_DEF( TransactionDMBase, executeAccessor )
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

        basar::db::aspect::ExecuteResultInfo executeResultInfo;
        try {
            basar::db::aspect::AccessorInstanceRef acc = m_Accessor.get();
            const basar::db::aspect::DatabaseHintEnum hint = static_cast<basar::db::aspect::DatabaseHintEnum>(dbHint);
            executeResultInfo = acc.execute( accessMethod, yit2Execute, clearBeforeSelect, flagExcept, hint );
        } catch( basar::Exception& e ){
            ::util::ExceptionHandler::processAccessorException( e, m_CSC_Logger->getLogger(), fun, accessMethod, __FILE__, __LINE__ );
        }

        if( executeResultInfo.hasError() ){
            std::stringstream msg;
            msg << fun << ": DB-Error <" <<  ExecuteErrorEnum2StringMapper::map(executeResultInfo.m_error) << "> with executing '"
            << accessMethod;
            throw ::util::AccessorExecutionException( basar::ExceptInfo( fun, msg.str().c_str(), __FILE__, __LINE__ ) );
        }
    }

    void TransactionDMBase::findOpen( const OffSetNo offSetNo /*= INVALID_OFFSET*/ )
    {
        METHODNAME_DEF( TransactionDMBase, findOpen )
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

        findByPattern( prepareFindOpenSearchCriteria(offSetNo) );
    }

    void TransactionDMBase::findByPattern( basar::db::aspect::AccessorPropertyTable_YIterator yitSearch )
    {
        METHODNAME_DEF( TransactionDMBase, findByPattern )
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );


        const basar::VarString& accessMethod      = getFindByPatternAccessMethod();
        const bool              clearBeforeSelect = true;
        const bool              flagExcept        = true;
        const basar::Int32      dbHint            = basar::db::aspect::HOLD_RECORDSET;

        evaluatePreconditionFindByPattern();
        executeAccessor( accessMethod, yitSearch, clearBeforeSelect, flagExcept, dbHint );
    }

    const log4cplus::Logger& TransactionDMBase::getLogger() const
    {
        METHODNAME_DEF( TransactionDMBase, getLogger )
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

        return m_CSC_Logger->getLogger();
    }

    libcsc_utils::ICSC_LoggerPtr TransactionDMBase::getCSC_Logger() const
    {
        return m_CSC_Logger;
    }

} // namespace core
} // namespace pharmosTransaction
} // namespace domMod
