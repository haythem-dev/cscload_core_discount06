//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include "customerinvoicedm.h"

#include "infrastructure/accessor/customerinvoice/customerinvoiceacc_definitions.h"
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
namespace customerInvoice
{

    const libutil::misc::ClassInfo& CustomerInvoiceDM::getClassInfo()
    {
        static const libutil::misc::ClassInfo info( "CustomerInvoiceDM", libutil::misc::Version( 1, 0, 0, 0 ) );
        return info;
    }

    CustomerInvoiceDM::CustomerInvoiceDM()
    : m_Logger( libcsc_deli::LoggerPool::getLoggerDomModules() )
    {
        METHODNAME_DEF( CustomerInvoiceDM, CustomerInvoiceDM )
        BLOG_TRACE_METHOD( getLogger(), fun );
    }

    CustomerInvoiceDM::~CustomerInvoiceDM()
    {
        METHODNAME_DEF( CustomerInvoiceDM, ~CustomerInvoiceDM )
        BLOG_TRACE_METHOD( getLogger(), fun );
    }

    void CustomerInvoiceDM::injectCustomerInvoiceAccessor( libutil::infrastructure::accessor::IAccessorPtr accessor )
    {
        m_Accessor = accessor;
    }

    void CustomerInvoiceDM::createEmptyInvoice()
    {
        getAccessor()->getPropertyTable().clear();
        getAccessor()->getPropertyTable().insert( basar::FOR_INSERT );
    }

    libutil::infrastructure::accessor::IAccessorPtr CustomerInvoiceDM::getAccessor() const
    {
        CHECK_INSTANCE_EXCEPTION( m_Accessor.get() );
        return m_Accessor;
    }

    basar::db::aspect::AccessorPropertyTable_YIterator CustomerInvoiceDM::get() const
    {
        return m_Accessor->getPropertyTable().begin();
    }

    bool CustomerInvoiceDM::isEmpty() const
    {
        return 0 == getAccessor().get() || m_Accessor->getPropertyTable().isNull() || get().isEnd();
    }

    bool CustomerInvoiceDM::isChanged() const
    {
        basar::property::PropertyStateSet stateSet;
        stateSet.insert( basar::SS_INSERT );
        stateSet.insert( basar::SS_UPDATE );

        return get().getState().contains( stateSet );
    }

    void CustomerInvoiceDM::resetSearchYit()
    {
        METHODNAME_DEF( CustomerInvoiceDM, resetSearchYit )
        BLOG_TRACE_METHOD( getLogger(), fun );

        getSearchYIterator()->reset();
    }

    basar::db::aspect::AccessorPropertyTable_YIterator CustomerInvoiceDM::getSearchYit()
    {
        METHODNAME_DEF( CustomerInvoiceDM, getSearchYit )
        BLOG_TRACE_METHOD( getLogger(), fun );

        return getSearchYIterator()->get();
    }

    void CustomerInvoiceDM::findByPattern( basar::db::aspect::AccessorPropertyTable_YIterator yit )
    {
        METHODNAME_DEF( CustomerInvoiceDM, findByPattern )
        BLOG_TRACE_METHOD( getLogger(), fun );

        using infrastructure::accessor::customerInvoice::lit::FIND_CUSTOMER_INVOICE_BY_PATTERN;

        basar::db::aspect::ExecuteResultInfo executeResultInfo;
        try
        {
            executeResultInfo = getAccessor()->execute( FIND_CUSTOMER_INVOICE_BY_PATTERN, yit );
        }
        catch( basar::Exception & e  )
        {
            libutil::exceptions::ExceptionHandler::processAccessorException( e, getLogger(), fun, FIND_CUSTOMER_INVOICE_BY_PATTERN, 
                                                                             __FILE__, __LINE__ );
            throw;
        }

        if( executeResultInfo.hasError() )
        {
            THROW_ACCESSOR_EXECUTION_EXCEPTION( fun, FIND_CUSTOMER_INVOICE_BY_PATTERN, executeResultInfo )
        }
    }

    void CustomerInvoiceDM::save()
    {
        METHODNAME_DEF( CustomerInvoiceDM, save )
        BLOG_TRACE_METHOD( getLogger(), fun );

        if( isEmpty() || ! isChanged() )
        {
            return;
        }

        using infrastructure::accessor::customerInvoice::lit::SAVE_CUSTOMER_INVOICE;

        basar::db::aspect::ExecuteResultInfo executeResultInfo;
        try
        {
            executeResultInfo = getAccessor()->execute( SAVE_CUSTOMER_INVOICE, get() );
        }
        catch( basar::Exception & e  )
        {
            libutil::exceptions::ExceptionHandler::processAccessorException( e, getLogger(), fun, SAVE_CUSTOMER_INVOICE, 
                                                                             __FILE__, __LINE__ );
            throw;
        }

        if( executeResultInfo.hasError() )
        {
            THROW_ACCESSOR_EXECUTION_EXCEPTION( fun, SAVE_CUSTOMER_INVOICE, executeResultInfo )
        }
    }

    void CustomerInvoiceDM::saveInvoicedFlag( basar::db::aspect::AccessorPropertyTable_YIterator yit )
    {
        METHODNAME_DEF( CustomerInvoiceDM, saveInvoicedFlag )
        BLOG_TRACE_METHOD( getLogger(), fun );

        using infrastructure::accessor::customerInvoice::lit::SET_INVOICED_FLAG;

        basar::db::aspect::ExecuteResultInfo executeResultInfo;
        try
        {
            executeResultInfo = getAccessor()->execute( SET_INVOICED_FLAG, yit );
        }
        catch( basar::Exception & e  )
        {
            libutil::exceptions::ExceptionHandler::processAccessorException( e, getLogger(), fun, SET_INVOICED_FLAG, __FILE__, __LINE__ );
            throw;
        }

        if( executeResultInfo.hasError() )
        {
            THROW_ACCESSOR_EXECUTION_EXCEPTION( fun, SET_INVOICED_FLAG, executeResultInfo )
        }
    }

    libutil::domMod::SearchYIteratorPtr CustomerInvoiceDM::getSearchYIterator()
    {
        if( NULL == m_SearchYIterator.get() )
        {
            m_SearchYIterator = libutil::domMod::SearchYIteratorPtr(
                new libutil::domMod::SearchYIterator( properties::BRANCH_NO.toDescriptionString()   +
                                                      properties::CUSTOMER_NO.toDescriptionString() +
                                                      properties::DOC_TYPE.toDescriptionString()    +
                                                      properties::DOC_NO.toDescriptionString()      +
                                                      properties::DATE.toDescriptionString()
                ) 
            );
        }

        return m_SearchYIterator;
    }

    const log4cplus::Logger& CustomerInvoiceDM::getLogger() const
    {
        return m_Logger;
    }

} // end namespace customerInvoice
} // end namespace domMod
} // end namespace libcsc_deli
