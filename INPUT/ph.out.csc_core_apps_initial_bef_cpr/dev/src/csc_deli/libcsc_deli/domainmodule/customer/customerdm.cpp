//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include "customerdm.h"

#include "infrastructure/accessor/customer/customeracc_definitions.h"
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
namespace customer
{

    const libutil::misc::ClassInfo& CustomerDM::getClassInfo()
    {
        static const libutil::misc::ClassInfo info( "CustomerDM", libutil::misc::Version( 1, 0, 0, 0 ) );
        return info;
    }

    CustomerDM::CustomerDM()
    : m_Logger( libcsc_deli::LoggerPool::getLoggerDomModules() )
    {
        METHODNAME_DEF( CustomerDM, CustomerDM )
        BLOG_TRACE_METHOD( getLogger(), fun );
    }

    CustomerDM::~CustomerDM()
    {
        METHODNAME_DEF( CustomerDM, ~CustomerDM )
        BLOG_TRACE_METHOD( getLogger(), fun );
    }

    void CustomerDM::injectCustomerAccessor( libutil::infrastructure::accessor::IAccessorPtr accessor )
    {
        m_Accessor = accessor;
    }

    libutil::infrastructure::accessor::IAccessorPtr CustomerDM::getAccessor() const
    {
        CHECK_INSTANCE_EXCEPTION( m_Accessor.get() );
        return m_Accessor;
    }

    basar::db::aspect::AccessorPropertyTable_YIterator CustomerDM::get() const
    {
        return m_Accessor->getPropertyTable().begin();
    }

    bool CustomerDM::isEmpty() const
    {
        return 0 == getAccessor().get() || m_Accessor->getPropertyTable().isNull() || get().isEnd();
    }

    void CustomerDM::findByPartnerNo( basar::Int32 partnerNo )
    {
        METHODNAME_DEF( CustomerDM, findByPartnerNo )
        BLOG_TRACE_METHOD( getLogger(), fun );

        getSearchYIterator()->reset();
        getSearchYIterator()->get().setInt32( properties::PARTNER_NO, partnerNo );

        using infrastructure::accessor::customer::lit::SELECT_CUSTOMER_BY_PARTNERNO;

        basar::db::aspect::ExecuteResultInfo executeResultInfo;
        try
        {
            executeResultInfo = getAccessor()->execute( SELECT_CUSTOMER_BY_PARTNERNO, getSearchYIterator()->get() );
        }
        catch( basar::Exception & e  )
        {
            libutil::exceptions::ExceptionHandler::processAccessorException( e, getLogger(), fun, SELECT_CUSTOMER_BY_PARTNERNO, __FILE__, __LINE__ );
            throw;
        }

        if( executeResultInfo.hasError() )
        {
            THROW_ACCESSOR_EXECUTION_EXCEPTION( fun, SELECT_CUSTOMER_BY_PARTNERNO, executeResultInfo )
        }
    }

    libutil::domMod::SearchYIteratorPtr CustomerDM::getSearchYIterator()
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

    const log4cplus::Logger& CustomerDM::getLogger() const
    {
        return m_Logger;
    }

} // end namespace customer
} // end namespace domMod
} // end namespace libcsc_deli
