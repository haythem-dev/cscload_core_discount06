#include <libutil/domainmodule.h>

#include "cicstransactioncollectiondm.h"
#include "cicstransactiondm.h"
#include "loggerpool/csc_phadex_loggerpool.h"
#include "domainmodule/csc_phadex_properties_definitions.h" //sk
#include "infrastructure/accessor/cicsdataacc_definitions.h" //sk
#include "icicstransaction.h"

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
namespace cicsTransaction
{
using namespace basar::db::aspect;

CICSTransactionCollectionDM::CICSTransactionCollectionDM()
: m_Logger( csc_phadex::LoggerPool::getLoggerDomModules() )
{
    METHODNAME_DEF( CICSTransactionCollectionDM, CICSTransactionCollectionDM )
    BLOG_TRACE_METHOD( m_Logger, fun );
}

CICSTransactionCollectionDM::~CICSTransactionCollectionDM()
{
    METHODNAME_DEF( CICSTransactionCollectionDM, ~CICSTransactionCollectionDM )
    BLOG_TRACE_METHOD( m_Logger, fun );
}

void CICSTransactionCollectionDM::injectCICSTransactionAccessor(libutil::infrastructure::accessor::IAccessorPtr accessor)
{
	METHODNAME_DEF(CICSTransactionCollectionDM, injectCICSTransactionAccessor)
	BLOG_TRACE_METHOD(m_Logger, fun);

	m_Accessor = accessor;
}

void CICSTransactionCollectionDM::injectCICSTransactionUpdateAccessor(libutil::infrastructure::accessor::IAccessorPtr accessor)
{
	METHODNAME_DEF(CICSTransactionCollectionDM, injectCICSTransactionUpdateAccessor)
	BLOG_TRACE_METHOD(m_Logger, fun);

	m_UpdateAccessor = accessor;
}

libutil::infrastructure::accessor::IAccessorPtr CICSTransactionCollectionDM::getAccessor() const
{
    CHECK_INSTANCE_EXCEPTION( m_Accessor.get() );
    return m_Accessor;
}

bool CICSTransactionCollectionDM::isEmpty() const
{
    METHODNAME_DEF( CICSTransactionCollectionDM, findByPattern )
    BLOG_TRACE_METHOD( m_Logger, fun );

    if(    0 == getAccessor().get() 
		|| getAccessor()->getPropertyTable().isNull() 
		|| getAccessor()->getPropertyTable().isEmpty() )
    {
        return true;
    }
    return false;
}

void CICSTransactionCollectionDM::findByPattern( const AccessorPropertyTable_YIterator yitSearch )
{
    METHODNAME_DEF( CICSTransactionCollectionDM, findByPattern )
    BLOG_TRACE_METHOD( m_Logger, fun );

    using infrastructure::accessor::drksc::lit::SELECT_DRKSC_BY_PATTERN;

    basar::db::aspect::ExecuteResultInfo executeResultInfo;
    try
    {
        executeResultInfo = m_Accessor->execute( SELECT_DRKSC_BY_PATTERN, yitSearch, true, true, basar::db::aspect::HOLD_RECORDSET );
    }
    catch( basar::Exception & e  )
    {
        libutil::exceptions::ExceptionHandler::processAccessorException( e, LoggerPool::getLoggerDomModules(), fun, SELECT_DRKSC_BY_PATTERN, __FILE__, __LINE__ );
        throw;
    }

    if( executeResultInfo.hasError() )
    {
        THROW_ACCESSOR_EXECUTION_EXCEPTION( fun, SELECT_DRKSC_BY_PATTERN, executeResultInfo )
    }
}

void CICSTransactionCollectionDM::saveCICSTransaction(const basar::db::aspect::AccessorPropertyTable_YIterator cicsTrans) const
{
	METHODNAME_DEF(CICSTransactionCollectionDM, saveCICSTransaction)
	BLOG_TRACE_METHOD(m_Logger, fun);

	using infrastructure::accessor::drksc::lit::UPDATE_DRKSC;

	basar::db::aspect::ExecuteResultInfo executeResultInfo;
	try
	{
		executeResultInfo = m_UpdateAccessor->execute(UPDATE_DRKSC, cicsTrans);
	}
	catch (basar::Exception & e)
	{
		libutil::exceptions::ExceptionHandler::processAccessorException(e, LoggerPool::getLoggerDomModules(), fun, UPDATE_DRKSC, __FILE__, __LINE__);
		throw;
	}

	if (executeResultInfo.hasError())
	{
		THROW_ACCESSOR_EXECUTION_EXCEPTION(fun, UPDATE_DRKSC, executeResultInfo)
	}

}


basar::db::aspect::AccessorPropertyTableRef CICSTransactionCollectionDM::get()
{
	return m_Accessor->getPropertyTable();
}

void CICSTransactionCollectionDM::resetSearchYit()
{
    METHODNAME_DEF( CICSTransactionCollectionDM, resetSearchYit )
    BLOG_TRACE_METHOD( m_Logger, fun );

    getSearchYIterator()->reset();
}

AccessorPropertyTable_YIterator CICSTransactionCollectionDM::getSearchYit() const
{
    METHODNAME_DEF( CICSTransactionCollectionDM, getSearchYit )
    BLOG_TRACE_METHOD( m_Logger, fun );

    return getSearchYIterator()->get();
}

libutil::domMod::SearchYIteratorPtr CICSTransactionCollectionDM::getSearchYIterator() const
{
    METHODNAME_DEF( CICSTransactionCollectionDM, getSearchYIterator )
    BLOG_TRACE_METHOD( m_Logger, fun );

    if( NULL == m_SearchYIterator.get() )
    {
        m_SearchYIterator = libutil::domMod::SearchYIteratorPtr(
        new libutil::domMod::SearchYIterator( properties::RRDS_RRN.toDescriptionString() +
                                                properties::KSC_FIL.toDescriptionString() +
                                                properties::KSC_DATUM.toDescriptionString() +
                                                properties::KSC_ZEIT.toDescriptionString() +
										        properties::LIMIT.toDescriptionString()
                                            ));
    }
    return m_SearchYIterator;
}

ICICSTransactionPtr CICSTransactionCollectionDM::getCICSTransaction( const basar::db::aspect::AccessorPropertyTable_YIterator yit ) const
{
    METHODNAME_DEF( CICSTransactionCollectionDM, getCICSTransaction )
    BLOG_TRACE_METHOD( m_Logger, fun );

    return ICICSTransactionPtr( new CICSTransactionDM( yit ) );
}

} // end namespace cicsTransaction
} // end namespace domMod
} // end namespace csc_phadex