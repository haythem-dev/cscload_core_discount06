//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include "customerordercollectiondm.h"

#include "infrastructure/accessor/customerorder/customerordercollectionacc_definitions.h"
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
namespace customerOrder
{

    const libutil::misc::ClassInfo& CustomerOrderCollectionDM::getClassInfo()
    {
        static const libutil::misc::ClassInfo info( "CustomerOrderCollectionDM", libutil::misc::Version( 1, 0, 0, 0 ) );
        return info;
    }

    CustomerOrderCollectionDM::CustomerOrderCollectionDM()
    : m_Logger( libcsc_deli::LoggerPool::getLoggerDomModules() )
    {
        METHODNAME_DEF( CustomerOrderCollectionDM, CustomerOrderCollectionDM )
        BLOG_TRACE_METHOD( getLogger(), fun );
    }

    CustomerOrderCollectionDM::~CustomerOrderCollectionDM()
    {
        METHODNAME_DEF( CustomerOrderCollectionDM, ~CustomerOrderCollectionDM )
        BLOG_TRACE_METHOD( getLogger(), fun );
    }

    void CustomerOrderCollectionDM::injectCustomerOrderCollectionAccessor( libutil::infrastructure::accessor::IAccessorPtr accessor )
    {
        m_Accessor = accessor;
    }

    libutil::infrastructure::accessor::IAccessorPtr CustomerOrderCollectionDM::getAccessor() const
    {
        CHECK_INSTANCE_EXCEPTION( m_Accessor.get() );
        return m_Accessor;
    }

    basar::db::aspect::AccessorPropertyTableRef CustomerOrderCollectionDM::get() const
    {
        return m_Accessor->getPropertyTable();
    }

    bool CustomerOrderCollectionDM::isEmpty() const
    {
        return 0 == getAccessor().get() || m_Accessor->getPropertyTable().isNull() ||
               m_Accessor->getPropertyTable().isEmpty();
    }

    void CustomerOrderCollectionDM::resetSearchYit()
    {
        METHODNAME_DEF( CustomerOrderCollectionDM, resetSearchYit )
        BLOG_TRACE_METHOD( getLogger(), fun );

        getSearchYIterator()->reset();
    }

    basar::db::aspect::AccessorPropertyTable_YIterator CustomerOrderCollectionDM::getSearchYit()
    {
        METHODNAME_DEF( CustomerOrderCollectionDM, getSearchYit )
        BLOG_TRACE_METHOD( getLogger(), fun );

        return getSearchYIterator()->get();
    }

    void CustomerOrderCollectionDM::findByPartnerNo( basar::Int32 partnerNo )
    {
        METHODNAME_DEF( CustomerOrderCollectionDM, findByPartnerNo )
        BLOG_TRACE_METHOD( getLogger(), fun );

        resetSearchYit();
        basar::db::aspect::AccessorPropertyTable_YIterator searchYit = getSearchYit();
        searchYit.setInt32( properties::PARTNER_NO, partnerNo );

        using infrastructure::accessor::customerOrder::lit::FIND_CUSTOMER_ORDER_COLLECTION;

        basar::db::aspect::ExecuteResultInfo executeResultInfo;
        try
        {
            executeResultInfo = getAccessor()->execute( FIND_CUSTOMER_ORDER_COLLECTION, searchYit );
        }
        catch( basar::Exception & e  )
        {
            libutil::exceptions::ExceptionHandler::processAccessorException( e, getLogger(), fun, FIND_CUSTOMER_ORDER_COLLECTION, 
                                                                             __FILE__, __LINE__ );
            throw;
        }

        if( executeResultInfo.hasError() )
        {
            THROW_ACCESSOR_EXECUTION_EXCEPTION( fun, FIND_CUSTOMER_ORDER_COLLECTION, executeResultInfo )
        }
    }

    basar::Decimal CustomerOrderCollectionDM::getDeliveryValue()
    {
        METHODNAME_DEF( CustomerOrderCollectionDM, getDeliveryValue )
        BLOG_TRACE_METHOD( getLogger(), fun );

        basar::Decimal deliveryValue;
        for( basar::db::aspect::AccessorPropertyTable_YIterator yit = get().begin(); ! yit.isEnd(); ++yit )
        {
            deliveryValue += yit.getDecimal( properties::DELIVERY_VALUE );
        }

        return deliveryValue;
    }

    libutil::domMod::SearchYIteratorPtr CustomerOrderCollectionDM::getSearchYIterator()
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

    const log4cplus::Logger& CustomerOrderCollectionDM::getLogger() const
    {
        return m_Logger;
    }

} // end namespace customerOrder
} // end namespace domMod
} // end namespace libcsc_deli
