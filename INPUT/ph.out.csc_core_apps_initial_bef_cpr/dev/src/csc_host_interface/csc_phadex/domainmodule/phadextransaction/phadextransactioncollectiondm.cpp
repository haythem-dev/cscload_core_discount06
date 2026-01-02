#include <libutil/domainmodule.h>

#include "phadextransactioncollectiondm.h"
#include "phadextransactiondm.h"
#include "loggerpool/csc_phadex_loggerpool.h"
#include "domainmodule/csc_phadex_properties_definitions.h"
#include "infrastructure/accessor/phadextransactionacc_definitions.h"
#include "iphadextransaction.h"

#include <libutil/searchyiterator.h>
#include <libutil/exception.h>
#include <libutil/util.h>
#include <libutil/accessor.h>

#include <libbasar_definitions.h>
#include <libbasardbaspect.h>
#include <libbasarcmnutil_exceptions.h>
#include <libbasardbaspect_exceptions.h>
#include <libbasardbsql_exceptions.h>

namespace csc_phadex
{
namespace domMod
{
namespace phadexTransaction
{
using namespace basar::db::aspect;

PhadexTransactionCollectionDM::PhadexTransactionCollectionDM()
: m_Logger( csc_phadex::LoggerPool::getLoggerDomModules() )
{
    METHODNAME_DEF( PhadexTransactionCollectionDM, PhadexTransactionCollectionDM )
    BLOG_TRACE_METHOD( m_Logger, fun );
}

PhadexTransactionCollectionDM::~PhadexTransactionCollectionDM()
{
    METHODNAME_DEF( PhadexTransactionCollectionDM, ~PhadexTransactionCollectionDM )
    BLOG_TRACE_METHOD( m_Logger, fun );
}

void PhadexTransactionCollectionDM::injectPhadexTransactionAccessor( libutil::infrastructure::accessor::IAccessorPtr accessor )
{
    METHODNAME_DEF( PhadexTransactionCollectionDM, injectPhadexTransactionAccessor )
    BLOG_TRACE_METHOD( m_Logger, fun );

    m_Accessor = accessor;
}

libutil::infrastructure::accessor::IAccessorPtr PhadexTransactionCollectionDM::getPhadexTransactionAccessor() const
{
    CHECK_INSTANCE_EXCEPTION( m_Accessor.get() );
    return m_Accessor;
}

void PhadexTransactionCollectionDM::clear()
{
	getPhadexTransactionAccessor()->getPropertyTable().clear();
}

bool PhadexTransactionCollectionDM::isEmpty() const
{
    METHODNAME_DEF( PhadexTransactionCollectionDM, isEmpty )
    BLOG_TRACE_METHOD( m_Logger, fun );

    if(    0 == getPhadexTransactionAccessor().get() 
        || getPhadexTransactionAccessor()->getPropertyTable().isNull() 
        || getPhadexTransactionAccessor()->getPropertyTable().isEmpty() )
    {
        return true;
    }
    return false;
}

void PhadexTransactionCollectionDM::findLastPhadexTransByPattern( const basar::db::aspect::AccessorPropertyTable_YIterator yitSearch )
{
    METHODNAME_DEF( PhadexTransactionCollectionDM, findLastPhadexTransByPattern )
    BLOG_TRACE_METHOD( m_Logger, fun );

    using infrastructure::accessor::phadex_transaction::lit::SELECT_LAST_PHADEX_TRANSACTION_BY_PATTERN;

    basar::db::aspect::ExecuteResultInfo executeResultInfo;
    try
    {
        m_Accessor->getPropertyTable().clear();
        executeResultInfo = m_Accessor->execute( SELECT_LAST_PHADEX_TRANSACTION_BY_PATTERN, yitSearch );
    }
    catch( basar::Exception & e  )
    {
        libutil::exceptions::ExceptionHandler::processAccessorException( e, LoggerPool::getLoggerDomModules(), fun, SELECT_LAST_PHADEX_TRANSACTION_BY_PATTERN, __FILE__, __LINE__ );
        throw;
    }

    if( executeResultInfo.hasError() )
    {
        THROW_ACCESSOR_EXECUTION_EXCEPTION( fun, SELECT_LAST_PHADEX_TRANSACTION_BY_PATTERN, executeResultInfo )
    }

}

void PhadexTransactionCollectionDM::findPhadexTransByPattern( const basar::db::aspect::AccessorPropertyTable_YIterator yitSearch )
{
    METHODNAME_DEF( PhadexTransactionCollectionDM, findPhadexTransByPattern )
    BLOG_TRACE_METHOD( m_Logger, fun );

    using infrastructure::accessor::phadex_transaction::lit::SELECT_PHADEX_TRANSACTION_BY_PATTERN;

    basar::db::aspect::ExecuteResultInfo executeResultInfo;
    try
    {
        executeResultInfo = m_Accessor->execute( SELECT_PHADEX_TRANSACTION_BY_PATTERN, yitSearch, true, true, basar::db::aspect::HOLD_RECORDSET );
    }
    catch( basar::Exception & e  )
    {
        libutil::exceptions::ExceptionHandler::processAccessorException( e, LoggerPool::getLoggerDomModules(), fun, SELECT_PHADEX_TRANSACTION_BY_PATTERN, __FILE__, __LINE__ );
        throw;
    }

    if( executeResultInfo.hasError() )
    {
        THROW_ACCESSOR_EXECUTION_EXCEPTION( fun, SELECT_PHADEX_TRANSACTION_BY_PATTERN, executeResultInfo )
    }
}

void PhadexTransactionCollectionDM::save( IPhadexTransactionPtr phadexTransaction )
{
    METHODNAME_DEF( PhadexTransactionCollectionDM, save )
    BLOG_TRACE_METHOD( LoggerPool::getLoggerDomModules(), fun );

    using infrastructure::accessor::phadex_transaction::lit::SAVE_PHADEX_TRANSACTION;

    basar::db::aspect::ExecuteResultInfo executeResultInfo;
    try
    {
        executeResultInfo = m_Accessor->execute( infrastructure::accessor::phadex_transaction::lit::SAVE_PHADEX_TRANSACTION, phadexTransaction->getYit() );
    }
    catch( basar::Exception& e )
    {
        libutil::exceptions::ExceptionHandler::processAccessorException( e, LoggerPool::getLoggerDomModules(), fun, SAVE_PHADEX_TRANSACTION, __FILE__, __LINE__ );
    }
    if( executeResultInfo.hasError() )
    {
        THROW_ACCESSOR_EXECUTION_EXCEPTION( fun, SAVE_PHADEX_TRANSACTION, executeResultInfo )
    }
}

basar::db::aspect::AccessorPropertyTableRef PhadexTransactionCollectionDM::get()
{
	return m_Accessor->getPropertyTable();
}

void PhadexTransactionCollectionDM::resetSearchYit()
{
    METHODNAME_DEF( PhadexTransactionCollectionDM, resetSearchYit )
    BLOG_TRACE_METHOD( m_Logger, fun );

    getSearchYIterator()->reset();
}

AccessorPropertyTable_YIterator PhadexTransactionCollectionDM::getSearchYit() const
{
    METHODNAME_DEF( PhadexTransactionCollectionDM, getSearchYit )
    BLOG_TRACE_METHOD( m_Logger, fun );

    return getSearchYIterator()->get();
}

libutil::domMod::SearchYIteratorPtr PhadexTransactionCollectionDM::getSearchYIterator() const
{
	METHODNAME_DEF(PhadexTransactionCollectionDM, getSearchYIterator)
		BLOG_TRACE_METHOD(m_Logger, fun);

	if (NULL == m_SearchYIterator.get())
	{
		m_SearchYIterator = libutil::domMod::SearchYIteratorPtr(
			new libutil::domMod::SearchYIterator(
				properties::DATABASE_NAME.toDescriptionString() +
				properties::BRANCH_NO.toDescriptionString() +
				properties::PROCESSED_FLAG.toDescriptionString() +
				properties::CREATION_DATETIME.toDescriptionString() +
				properties::RECORD_NO.toDescriptionString()
			));
	}
	return m_SearchYIterator;
}

IPhadexTransactionPtr PhadexTransactionCollectionDM::getPhadexTransaction( const basar::db::aspect::AccessorPropertyTable_YIterator yit ) const
{
    METHODNAME_DEF( PhadexTransactionCollectionDM, getPhadexTransaction )
    BLOG_TRACE_METHOD( m_Logger, fun );

    return IPhadexTransactionPtr( new PhadexTransactionDM( yit ) );
}

IPhadexTransactionPtr PhadexTransactionCollectionDM::createPhadexTransaction()
{
    METHODNAME_DEF( PhadexTransactionCollectionDM, createPhadexTransaction )
    BLOG_TRACE_METHOD( m_Logger, fun );

    return getPhadexTransaction( m_Accessor->getPropertyTable().insert( basar::FOR_INSERT ) );
}


} // end namespace phadexTransaction
} // end namespace domMod
} // end namespace csc_phadex