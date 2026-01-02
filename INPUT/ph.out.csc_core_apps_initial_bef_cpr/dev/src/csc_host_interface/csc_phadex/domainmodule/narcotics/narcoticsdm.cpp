#include <libutil/domainmodule.h>

#include "narcoticsdm.h"
#include "loggerpool/csc_phadex_loggerpool.h"
#include "domainmodule/csc_phadex_properties_definitions.h"
#include "infrastructure/accessor/narcoticsacc_definitions.h"
#include <libutil/exception.h>


namespace csc_phadex
{
namespace domMod
{
namespace narcotics
{
using namespace basar::db::aspect;

NarcoticsDM::NarcoticsDM()
: m_Logger( csc_phadex::LoggerPool::getLoggerDomModules() )
{
    METHODNAME_DEF( NarcoticsDM, NarcoticsDM )
    BLOG_TRACE_METHOD( m_Logger, fun );
}

NarcoticsDM::~NarcoticsDM()
{
    METHODNAME_DEF( NarcoticsDM, ~NarcoticsDM )
    BLOG_TRACE_METHOD( m_Logger, fun );
}

void NarcoticsDM::injectNarcoticsAccessor( libutil::infrastructure::accessor::IAccessorPtr accessor )
{
    METHODNAME_DEF( NarcoticsDM, injectNarcoticsAccessor )
    BLOG_TRACE_METHOD( m_Logger, fun );

    m_Accessor = accessor;
}

basar::db::aspect::AccessorPropertyTableRef NarcoticsDM::get() const
{
    METHODNAME_DEF( NarcoticsDM, get )
    BLOG_TRACE_METHOD( m_Logger, fun );

    return m_Accessor->getPropertyTable();
}

libutil::infrastructure::accessor::IAccessorPtr NarcoticsDM::getNarcoticsAccessor() const
{
    CHECK_INSTANCE_EXCEPTION( m_Accessor.get() );
    return m_Accessor;
}

bool NarcoticsDM::isEmpty() const
{
    METHODNAME_DEF( NarcoticsDM, isEmpty )
    BLOG_TRACE_METHOD( m_Logger, fun );

    if(    0 == getNarcoticsAccessor().get() 
        || m_Accessor->getPropertyTable().isNull() 
        || m_Accessor->getPropertyTable().isEmpty() )
    {
        return true;
    }
    return false;
}

void NarcoticsDM::save( const basar::db::aspect::AccessorPropertyTable_YIterator yiterator)
{
    METHODNAME_DEF( NarcoticsDM, save )
    BLOG_TRACE_METHOD( LoggerPool::getLoggerDomModules(), fun );

    using infrastructure::accessor::narcotics::lit::SAVE_NARC_TRANSFER;

    basar::db::aspect::ExecuteResultInfo executeResultInfo;
    try
    {
        executeResultInfo = m_Accessor->execute( infrastructure::accessor::narcotics::lit::SAVE_NARC_TRANSFER, yiterator );
    }
    catch( basar::Exception& e )
    {
        libutil::exceptions::ExceptionHandler::processAccessorException( e, LoggerPool::getLoggerDomModules(), fun, SAVE_NARC_TRANSFER, __FILE__, __LINE__ );
    }
    if( executeResultInfo.hasError() )
    {
        THROW_ACCESSOR_EXECUTION_EXCEPTION( fun, SAVE_NARC_TRANSFER, executeResultInfo )
    }
}

void NarcoticsDM::resetSearchYit()
{
    METHODNAME_DEF( NarcoticsDM, resetSearchYit )
    BLOG_TRACE_METHOD( m_Logger, fun );

    getSearchYIterator()->reset();
}

AccessorPropertyTable_YIterator NarcoticsDM::getSearchYit() const
{
    METHODNAME_DEF( NarcoticsDM, getSearchYit )
    BLOG_TRACE_METHOD( m_Logger, fun );

    return getSearchYIterator()->get();
}

libutil::domMod::SearchYIteratorPtr NarcoticsDM::getSearchYIterator() const
{
    METHODNAME_DEF( NarcoticsDM, getSearchYIterator )
    BLOG_TRACE_METHOD( m_Logger, fun );

    if( NULL == m_SearchYIterator.get() )
    {
        m_SearchYIterator = libutil::domMod::SearchYIteratorPtr(
        new libutil::domMod::SearchYIterator( properties::BRANCH_NO.toDescriptionString() +
                                              properties::CUSTOMERSUPPLIERNO.toDescriptionString() +
                                              properties::ORDER_NO.toDescriptionString() + 
                                              properties::WAREHOUSE_ORDER_NO.toDescriptionString()
                                            ));
    }
    return m_SearchYIterator;
}

} // end namespace narcotics
} // end namespace domMod
} // end namespace csc_phadex