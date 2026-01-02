//-------------------------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief      implementation of CICSOrderAccessorBase
 *  \author     Steffen Heinlein
 *  \date       27.05.2013
 */
//-------------------------------------------------------------------------------------------------------------------//

#include <icsc_logger.h>
#include <classinfo_macros.h>
#include <searchyiterator.h>
#include <csc_logger.h>
#include <transactionguard.h>
#include <accessorexecutionexception.h>
#include <libbasardbaspect.h>
#include "bulkinserter.h"
#include "cicsorderaccessorbase.h"
#include "property_definitions.h"
#include "accessorinstancerefwrapper.h"
#include "recordtypecollection.h"
#include "recordtypebase_definitions.h"

namespace domMod
{
namespace corpha
{
namespace processOrder
{
    //-------------------------------------------------------------------------------------------------------------------//
    CICSOrderAccessorBase::~CICSOrderAccessorBase()
    {
        METHODNAME_DEF( CICSOrderAccessorBase, ~CICSOrderAccessorBase );
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );
    }
    //-------------------------------------------------------------------------------------------------------------------//

    ////-------------------------------------------------------------------------------------------------------------------//
    CICSOrderAccessorBase::CICSOrderAccessorBase( libcsc_utils::ICSC_LoggerPtr logger, basar::VarString accname, const basar::db::aspect::ConnectionRef tca ) :
        m_Logger( logger ), m_Accessor( accname, tca ),
        m_BulkInserter(new domMod::util::BulkInserter(tca.getSqlConnection(), const_cast<log4cplus::Logger&>(logger->getLogger())))
    {
        METHODNAME_DEF( CICSOrderAccessorBase, CICSOrderAccessorBase );
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );
    }
    //-------------------------------------------------------------------------------------------------------------------//

    //-------------------------------------------------------------------------------------------------------------------//
    libcsc_utils::ICSC_LoggerPtr CICSOrderAccessorBase::getLogger() const
    {
        METHODNAME_DEF( CICSOrderAccessorBase, getLogger );
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );
        return m_Logger;
    }
    //-------------------------------------------------------------------------------------------------------------------//

    //-------------------------------------------------------------------------------------------------------------------//
    void CICSOrderAccessorBase::send()
    {
        METHODNAME_DEF( CICSOrderAccessorBase, send );
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );
    }
    //-------------------------------------------------------------------------------------------------------------------//

    //-------------------------------------------------------------------------------------------------------------------//
    void CICSOrderAccessorBase::addOrderItemYit( const recordtypes::RecordTypeBasePtr, const basar::Int32, const basar::Int32 )
    {
        METHODNAME_DEF( CICSOrderAccessorBase, addOrderItemYit );
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );
    }
    //-------------------------------------------------------------------------------------------------------------------//

    //-------------------------------------------------------------------------------------------------------------------//
    CICSRecord CICSOrderAccessorBase::getCICSRecord( basar::db::aspect::AccessorPropertyTable_YIterator )
    {
        METHODNAME_DEF( CICSOrderAccessorBase, getCICSRecord );
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

        CICSRecord retval;
        return retval;
    }
    //-------------------------------------------------------------------------------------------------------------------//

    //-------------------------------------------------------------------------------------------------------------------//
    basar::db::aspect::AccessorPropertyTableRef CICSOrderAccessorBase::getPropTab()
    {
        METHODNAME_DEF( CICSOrderAccessorOdd, getPropTab );
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );
        return getAccessor().get().getPropertyTable();
    }
    //-------------------------------------------------------------------------------------------------------------------//

    //-------------------------------------------------------------------------------------------------------------------//
    basar::db::aspect::AccessorPropertyTable_YIterator CICSOrderAccessorBase::addEmptyYit()
    {
        METHODNAME_DEF( CICSOrderAccessorBase, addEmptyYit );
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

        basar::db::aspect::AccessorPropertyTable_YIterator yit;
        yit = getPropTab().insert( basar::FOR_INSERT );
        return yit;
    }
    //-------------------------------------------------------------------------------------------------------------------//

    //-------------------------------------------------------------------------------------------------------------------//
    void CICSOrderAccessorBase::shutdown()
    {
        METHODNAME_DEF( CICSOrderAccessorBase, shutdown );
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );
        getPropTab().clear();
    }
    //-------------------------------------------------------------------------------------------------------------------//

    //-------------------------------------------------------------------------------------------------------------------//
    void CICSOrderAccessorBase::doSetTransferCompleted( const basar::VarString& AccMethodName )
    {
        METHODNAME_DEF( CICSOrderAccessorBase, doSetTransferCompleted );
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

        m_Logger->log( log4cplus::INFO_LOG_LEVEL, "     -> SetTransferCompleted started" );

        const bool clearbeforeselect = true;
        const bool flagexcept = false;

        basar::db::aspect::ExecuteResultInfo result;
        basar::db::aspect::AccessorPropertyTable_YIterator yit = getPropTab().begin(); // update will be done for all records with the key values orderno and time

        result = getAccessor().get().execute( AccMethodName, yit, clearbeforeselect, flagexcept );
        if( result.hasError() )
        {
            if( basar::db::aspect::SQL_ERROR_DUPL_INSERT != result.m_error )
            {
                if( basar::db::aspect::SQL_ERROR_NONSPECIFIC == result.m_error )
                {
                    m_Logger->log( log4cplus::ERROR_LOG_LEVEL, "sendOrder SetTransferCompleted error! Check DKOTO.FTB/DKOTE.FTB? CICS available? DKOTE/DKOTO opened in CICS?" );
                    throw ::util::AccessorExecutionException( basar::ExceptInfo( fun, "sendOrder error!", __FILE__, __LINE__ ) );
                }
                else
                {
                    m_Logger->log( log4cplus::ERROR_LOG_LEVEL, "sendOrder SetTransferCompleted error!" );
                    throw ::util::AccessorExecutionException( basar::ExceptInfo( fun, "sendOrder SetTransferCompleted error!", __FILE__, __LINE__ ) );
                }
            }
        }
        m_Logger->log( log4cplus::INFO_LOG_LEVEL, "     -> SetTransferCompleted finished" );
    }
    //-------------------------------------------------------------------------------------------------------------------//

    //-------------------------------------------------------------------------------------------------------------------//
    void CICSOrderAccessorBase::doSend( const basar::VarString& AccMethodName )
    {
        METHODNAME_DEF( CICSOrderAccessorBase, doSend );
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

        basar::db::aspect::AccessorPropertyTable_YIterator  yit;
        basar::db::aspect::ExecuteResultInfo                result;
        basar::db::aspect::SQLStringBuilderRef              builder;
        const bool                                          clearbeforeselect = true;
        const bool                                          flagexcept = false;
        basar::VarString                                    logmsg;
        basar::VarString                                    tmpBulkSQL("");

        if (m_BulkInsert)
        {
            builder = getAccessor().get().getAccessMethod(AccMethodName).getBuilder(0);
            m_BulkInserter->init();
        }

        for( yit = getPropTab().begin(); yit != getPropTab().end(); ++yit )
        {
            if (m_BulkInsert)
            {
                if (builder.build(yit))
                {
                    m_BulkInserter->insert(builder.getSQLString());
                    tmpBulkSQL += builder.getSQLString();
                }
            }
            else
            {
                result = getAccessor().get().execute( AccMethodName, yit, clearbeforeselect, flagexcept );
                if( result.hasError() )
                {
                    if( basar::db::aspect::SQL_ERROR_DUPL_INSERT != result.m_error )
                    {
                        if( basar::db::aspect::SQL_ERROR_NONSPECIFIC == result.m_error )
                        {
                            m_Logger->log( log4cplus::ERROR_LOG_LEVEL, "sendOrder error! Check DKOTO.FTB/DKOTE.FTB? CICS available? DKOTE/DKOTO opened in CICS?" );
                            throw ::util::AccessorExecutionException( basar::ExceptInfo( fun, "sendOrder error!", __FILE__, __LINE__ ) );
                        }
                        else
                        {
                            m_Logger->log( log4cplus::ERROR_LOG_LEVEL, "sendOrder error!" );
                            throw ::util::AccessorExecutionException( basar::ExceptInfo( fun, "sendOrder error!", __FILE__, __LINE__ ) );
                        }
                    }
                }
            }
        }

        if (m_BulkInsert)
        {
            m_BulkInserter->finish();

            yit = getPropTab().begin();
            basar::db::aspect::AccessorPropertyTable_YIterator yitSearch = getSearchYit()->get();
            yitSearch.match(yit);
            basar::Int32 toInsert = static_cast<basar::Int32>(getPropTab().size());
            basar::Int32 inserted = getCountByPattern();
            logmsg.format("rows to insert: %d, rows inserted %d", toInsert, inserted);
            m_Logger->log( log4cplus::INFO_LOG_LEVEL, logmsg );

            if( toInsert != inserted )
            {
                m_Logger->log( log4cplus::ERROR_LOG_LEVEL, "sendOrder error - BulkInsert failed! Rows inserted != Number of Rows that have to be inserted!" );
                m_Logger->log( log4cplus::ERROR_LOG_LEVEL, "SQL-Statement failed: " );
                m_Logger->log( log4cplus::ERROR_LOG_LEVEL, tmpBulkSQL );
                throw ::util::AccessorExecutionException( basar::ExceptInfo( fun, "sendOrder error! BulkInsert failed! Rows inserted != Number of Rows that have to be inserted!", __FILE__, __LINE__ ) );
            }
        }
    }
    //-------------------------------------------------------------------------------------------------------------------//

    //-------------------------------------------------------------------------------------------------------------------//
    void CICSOrderAccessorBase::doFindByPattern( const basar::VarString& AccMethodName )
    {
        METHODNAME_DEF( CICSOrderAccessorBase, doFindByPattern );
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

        const bool          clearbeforeselect = true;
        const bool          flagexcept = true;
        const basar::Int32  dbhint = basar::db::aspect::HOLD_RECORDSET;

        basar::db::aspect::ExecuteResultInfo result;
        try
        {
            const basar::db::aspect::DatabaseHintEnum hint = static_cast<const basar::db::aspect::DatabaseHintEnum>(dbhint);
            result = getAccessor().get().execute( AccMethodName, m_SearchYit->get(), clearbeforeselect, flagexcept, hint );
        }
        catch( basar::Exception& /*e*/ )
        {
            throw;
        }
        if( result.hasError() )
        {
            throw basar::cmnutil::BasarException( basar::ExceptInfo( fun, "accessor execution error", __FILE__, __LINE__ ), "ERROR" );
        }
    }
    //-------------------------------------------------------------------------------------------------------------------//

    //-------------------------------------------------------------------------------------------------------------------//
    basar::Int32 CICSOrderAccessorBase::doGetCountByPattern( const basar::VarString& AccMethodName )
    {
        METHODNAME_DEF( CICSOrderAccessorBase, doGetCountByPattern );
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

        std::pair<bool, basar::Decimal> result;
        try
        {
            result = getAccessor().get().executeAggregate( AccMethodName, m_SearchYit->get());
        }
        catch( basar::Exception& /*e*/ )
        {
            throw;
        }
        if( !result.first )
        {
            throw basar::cmnutil::BasarException( basar::ExceptInfo( fun, "accessor execution error", __FILE__, __LINE__ ), "ERROR" );
        }
        getAccessor().get().getPropertyTable().clear();
        return result.second.toInt32();
    }

    //-------------------------------------------------------------------------------------------------------------------//

} // namespace processOrder
} // namespace corpha
} // namespace domMod
