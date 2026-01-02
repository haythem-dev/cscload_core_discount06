//-------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief      base functionality for batchorder domain modules
 *  \author     Julian Machata
 *  \date       26.10.2012
 */
//-------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include "cmndm.h"
#include <libbasar_definitions.h>
#include <libbasardbaspect.h>
#include "searchdmbase.h"
#include "exceptionhandler.h"
#include "executeerrorenum2stringmapper.h"
#include "accessorexecutionexception.h"
#include "searchyiteratorptr.h"
#include <icsc_logger.h>

//-------------------------------------------------------------------------------------------------//
// using declarations section
//-------------------------------------------------------------------------------------------------//
namespace domMod
{
    namespace batchOrder
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
namespace batchOrder
{
namespace core
{
    //-------------------------------------------------------------------------------------------------------------------//
    SearchDMBase::SearchDMBase( const basar::db::aspect::ConnectionRef conn,
                                        const basar::VarString& accDefName,
                                        libcsc_utils::ICSC_LoggerPtr csc_logger )
        : m_CSC_Logger( csc_logger ),
          m_Accessor( accDefName, conn )
    {
        METHODNAME_DEF( SearchDMBase, SearchDMBase )
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
    }

    //-------------------------------------------------------------------------------------------------------------------//
    SearchDMBase::~SearchDMBase()
    {
        METHODNAME_DEF( SearchDMBase, ~SearchDMBase )
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
    }

    //-------------------------------------------------------------------------------------------------------------------//
    void SearchDMBase::clearPropertyTable()
    {
        METHODNAME_DEF( SearchDMBase, clearPropertyTable );
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

        if (!m_Accessor.isNull())
        {
            m_Accessor.get().getPropertyTable().clear();
        }
    }

    //-------------------------------------------------------------------------------------------------------------------//
    AccessorInstanceRefWrapper& SearchDMBase::getAccessor()
    {
        METHODNAME_DEF( SearchDMBase, getAccessor );
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

        return m_Accessor;
    }

    //-------------------------------------------------------------------------------------------------------------------//
    AccessorPropertyTableRef SearchDMBase::getPropTab()
    {
        METHODNAME_DEF( SearchDMBase, getPropTab )
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

        return getAccessor().get().getPropertyTable();
    }

    //-------------------------------------------------------------------------------------------------------------------//
    void SearchDMBase::resetSearchYit()
    {
        METHODNAME_DEF( SearchDMBase, resetSearchYit )
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

        if (NULL != getSearchYIterator().get())
        {
           getSearchYIterator()->reset();
        }
    }

    //-------------------------------------------------------------------------------------------------------------------//
    AccessorPropertyTable_YIterator SearchDMBase::getSearchYit()
    {
        METHODNAME_DEF( SearchDMBase, getSearchYit )
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

        return getSearchYIterator()->get();
    }

    //-------------------------------------------------------------------------------------------------------------------//
    void SearchDMBase::evaluatePreconditionFindByPattern()
    {
        METHODNAME_DEF( SearchDMBase, evaluatePreconditionFindByPattern )
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
    }

    //-------------------------------------------------------------------------------------------------------------------//
    void SearchDMBase::findOpen( basar::db::aspect::AccessorPropertyTable_YIterator yitSearch  )
    {
        METHODNAME_DEF( SearchDMBase, findOpen )
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

        findByPattern( prepareFindOpenSearchCriteria( yitSearch ) );
    }

    //-------------------------------------------------------------------------------------------------------------------//
    basar::Int32 SearchDMBase::findLastKey( const basar::Int16 branchno )
    {
        METHODNAME_DEF( SearchDMBase, findLastKey )
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

        const basar::VarString& accessMethod = getFindLastKeyAccessMethod();
        basar::db::aspect::AccessorPropertyTable_YIterator yitSearch = prepareFindLastKeySearchCriteria( branchno );

        return executeAggregateAccessor( accessMethod, yitSearch ).toInt32();
    }

    //-------------------------------------------------------------------------------------------------------------------//
    void SearchDMBase::findByPattern( basar::db::aspect::AccessorPropertyTable_YIterator yitSearch )
    {
        METHODNAME_DEF( SearchDMBase, findByPattern )
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );


        const basar::VarString& accessMethod      = getFindByPatternAccessMethod();
        bool              clearBeforeSelect = true;
        bool              flagExcept        = true;
        const basar::Int32      dbHint            = basar::db::aspect::HOLD_RECORDSET;

        evaluatePreconditionFindByPattern();
        executeAccessor( accessMethod, yitSearch, clearBeforeSelect, flagExcept, dbHint );
    }

    //-------------------------------------------------------------------------------------------------------------------//
    void SearchDMBase::executeAccessor( const basar::VarString& accessMethod,
                                            basar::db::aspect::AccessorPropertyTable_YIterator yit2Execute,
                                            bool clearBeforeSelect /*= true*/,
                                            bool flagExcept /*= true*/,
                                            const basar::Int32 dbHint /*= basar::db::aspect::NO_HINT*/ )
    {
        METHODNAME_DEF( SearchDMBase, executeAccessor )
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

        basar::db::aspect::ExecuteResultInfo executeResultInfo;

        try {
            basar::db::aspect::AccessorInstanceRef acc = m_Accessor.get();
            const basar::db::aspect::DatabaseHintEnum hint = static_cast<const basar::db::aspect::DatabaseHintEnum>(dbHint);
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

    //-------------------------------------------------------------------------------------------------------------------//
    basar::Decimal SearchDMBase::executeAggregateAccessor( const basar::VarString& accessMethod,
                                            basar::db::aspect::AccessorPropertyTable_YIterator yit2Execute )
    {
        METHODNAME_DEF( SearchDMBase, executeAccessor )
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

        basar::db::aspect::ExecuteResultInfo executeResultInfo;
        basar::Decimal ret (0);

        try {
            basar::db::aspect::AccessorInstanceRef acc = m_Accessor.get();
            ret = acc.executeAggregate( accessMethod, yit2Execute ).second;
        } catch( basar::Exception& e ){
            ::util::ExceptionHandler::processAccessorException( e, m_CSC_Logger->getLogger(), fun, accessMethod, __FILE__, __LINE__ );
        }

        if( executeResultInfo.hasError() ){
            std::stringstream msg;
            msg << fun << ": DB-Error <" <<  ExecuteErrorEnum2StringMapper::map(executeResultInfo.m_error) << "> with executing '"
            << accessMethod;
            throw ::util::AccessorExecutionException( basar::ExceptInfo( fun, msg.str().c_str(), __FILE__, __LINE__ ) );
        }

        return ret;
    }

    //-------------------------------------------------------------------------------------------------------------------//
    const log4cplus::Logger& SearchDMBase::getLogger() const
    {
        METHODNAME_DEF( SearchDMBase, getLogger )
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

        return m_CSC_Logger->getLogger();
    }

    //-------------------------------------------------------------------------------------------------------------------//
    libcsc_utils::ICSC_LoggerPtr SearchDMBase::getCSC_Logger() const
    {
        METHODNAME_DEF( SearchDMBase, getCSC_Logger )
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

        return m_CSC_Logger;
    }

    //-------------------------------------------------------------------------------------------------------------------//
    void SearchDMBase::save ( basar::db::aspect::AccessorPropertyTable_YIterator yitSave )
    {
        METHODNAME_DEF( BatchOrderPosDM, save )
        BLOG_TRACE_METHOD( getLogger(), fun );

       const basar::VarString& accessMethod      = getSaveAccessMethod();
       bool              clearBeforeSelect = false;
       bool              flagExcept        = true;
       const basar::Int32      dbHint            = basar::db::aspect::HOLD_RECORDSET;

       executeAccessor( accessMethod, yitSave, clearBeforeSelect, flagExcept, dbHint );
    }

} // namespace core
} // namespace batchOrder
} // namespace domMod
