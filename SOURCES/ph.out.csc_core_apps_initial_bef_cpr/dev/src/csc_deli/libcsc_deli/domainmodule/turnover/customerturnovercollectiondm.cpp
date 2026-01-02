//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include "customerturnovercollectiondm.h"

#include "infrastructure/accessor/customerturnover/customerturnovercollectionacc_definitions.h"
#include "domainmodule/libcsc_deli_properties_definitions.h"
#include "loggerpool/libcsc_deli_loggerpool.h"

#include <libutil/domainmodule.h>
#include <libutil/version.h>
#include <libutil/exception.h>

//--------------------------------------------------------------------------------------------------//
// class definition section
//--------------------------------------------------------------------------------------------------//
namespace libcsc_deli
{
namespace domMod
{
namespace turnover
{

    const libutil::misc::ClassInfo& CustomerTurnoverCollectionDM::getClassInfo()
    {
        static const libutil::misc::ClassInfo info( "CustomerTurnoverCollectionDM", libutil::misc::Version( 1, 0, 0, 0 ) );
        return info;
    }

    CustomerTurnoverCollectionDM::CustomerTurnoverCollectionDM()
    : m_Logger( libcsc_deli::LoggerPool::getLoggerDomModules() )
    {
        METHODNAME_DEF( CustomerTurnoverCollectionDM, CustomerTurnoverCollectionDM )
        BLOG_TRACE_METHOD( getLogger(), fun );
    }

    CustomerTurnoverCollectionDM::~CustomerTurnoverCollectionDM()
    {
        METHODNAME_DEF( CustomerTurnoverCollectionDM, ~CustomerTurnoverCollectionDM )
        BLOG_TRACE_METHOD( getLogger(), fun );
    }

    void CustomerTurnoverCollectionDM::injectCustomerTurnoverCollectionAccessor( libutil::infrastructure::accessor::IAccessorPtr accessor )
    {
        m_Accessor = accessor;
    }

    libutil::infrastructure::accessor::IAccessorPtr CustomerTurnoverCollectionDM::getAccessor() const
    {
        CHECK_INSTANCE_EXCEPTION( m_Accessor.get() );
        return m_Accessor;
    }

    basar::db::aspect::AccessorPropertyTableRef CustomerTurnoverCollectionDM::get() const
    {
        return m_Accessor->getPropertyTable();
    }

    bool CustomerTurnoverCollectionDM::isEmpty() const
    {
        return 0 == getAccessor().get() || m_Accessor->getPropertyTable().isNull() ||
               m_Accessor->getPropertyTable().isEmpty();
    }

    /*
    void CustomerTurnoverCollectionDM::resetSearchYit()
    {
        METHODNAME_DEF( CustomerTurnoverCollectionDM, resetSearchYit )
        BLOG_TRACE_METHOD( getLogger(), fun );

        getSearchYIterator()->reset();
    }

    basar::db::aspect::AccessorPropertyTable_YIterator CustomerTurnoverCollectionDM::getSearchYit()
    {
        METHODNAME_DEF( CustomerTurnoverCollectionDM, getSearchYit )
        BLOG_TRACE_METHOD( getLogger(), fun );

        return getSearchYIterator()->get();
    }
    */

    void CustomerTurnoverCollectionDM::load()
    {
        METHODNAME_DEF( CustomerTurnoverCollectionDM, load )
        BLOG_TRACE_METHOD( getLogger(), fun );

        using infrastructure::accessor::customerTurnover::lit::FIND_CUSTOMER_TURNOVER_COLLECTION;

        basar::db::aspect::ExecuteResultInfo executeResultInfo;
        try
        {
            executeResultInfo = getAccessor()->execute( FIND_CUSTOMER_TURNOVER_COLLECTION );
        }
        catch( basar::Exception & e  )
        {
            libutil::exceptions::ExceptionHandler::processAccessorException( e, getLogger(), fun, FIND_CUSTOMER_TURNOVER_COLLECTION, 
                                                                             __FILE__, __LINE__ );
            throw;
        }

        if( executeResultInfo.hasError() )
        {
            THROW_ACCESSOR_EXECUTION_EXCEPTION( fun, FIND_CUSTOMER_TURNOVER_COLLECTION, executeResultInfo )
        }
    }

    /*
    libutil::domMod::SearchYIteratorPtr CustomerTurnoverCollectionDM::getSearchYIterator()
    {
        if( NULL == m_SearchYIterator.get() )
        {
            m_SearchYIterator = libutil::domMod::SearchYIteratorPtr(
                new libutil::domMod::SearchYIterator( properties::PARTNER_NO.toDescriptionString()
                ) 
            );
        }

        return m_SearchYIterator;
    }
    */

    const log4cplus::Logger& CustomerTurnoverCollectionDM::getLogger() const
    {
        return m_Logger;
    }

} // end namespace turnover
} // end namespace domMod
} // end namespace libcsc_deli
