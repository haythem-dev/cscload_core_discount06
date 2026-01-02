//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include "customerinvoicingcollectiondm.h"

#include "icustomerinvoice.h"
#include "componentmanager/icustomerinvoiceconnectedfactory.h"

#include "infrastructure/accessor/customerinvoice/customerinvoicingcollectionacc_definitions.h"
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

    const libutil::misc::ClassInfo& CustomerInvoicingCollectionDM::getClassInfo()
    {
        static const libutil::misc::ClassInfo info( "CustomerInvoicingCollectionDM", libutil::misc::Version( 1, 0, 0, 0 ) );
        return info;
    }

    CustomerInvoicingCollectionDM::CustomerInvoicingCollectionDM()
    : m_Logger( libcsc_deli::LoggerPool::getLoggerDomModules() )
    {
        METHODNAME_DEF( CustomerInvoicingCollectionDM, CustomerInvoicingCollectionDM )
        BLOG_TRACE_METHOD( getLogger(), fun );
    }

    CustomerInvoicingCollectionDM::~CustomerInvoicingCollectionDM()
    {
        METHODNAME_DEF( CustomerInvoicingCollectionDM, ~CustomerInvoicingCollectionDM )
        BLOG_TRACE_METHOD( getLogger(), fun );
    }

    void CustomerInvoicingCollectionDM::injectCustomerInvoicingCollectionAccessor( libutil::infrastructure::accessor::IAccessorPtr accessor )
    {
        m_Accessor = accessor;
    }

    libutil::infrastructure::accessor::IAccessorPtr CustomerInvoicingCollectionDM::getAccessor() const
    {
        CHECK_INSTANCE_EXCEPTION( m_Accessor.get() );
        return m_Accessor;
    }

    void CustomerInvoicingCollectionDM::injectCustomerInvoiceFactory( componentManager::ICustomerInvoiceConnectedFactoryPtr factory )
    {
        m_CustomerInvoiceFactory = factory;
    }

    componentManager::ICustomerInvoiceConnectedFactoryPtr CustomerInvoicingCollectionDM::getCustomerInvoiceFactory()
    {
        CHECK_INSTANCE_EXCEPTION( m_CustomerInvoiceFactory.get() );
        return m_CustomerInvoiceFactory;
    }

    ICustomerInvoicePtr CustomerInvoicingCollectionDM::getCustomerInvoice( basar::db::aspect::AccessorPropertyTable_YIterator yit )
    {
        ICustomerInvoicePtr cstInvoice = getCustomerInvoiceFactory()->create( yit );
        if( cstInvoice->isEmpty() ) // dataset is missing in DB -> create new
        {
            cstInvoice->createEmptyInvoice();
            cstInvoice->get().match( yit );   // copy our data to newly created invoice
        }

        return cstInvoice;
    }

    basar::db::aspect::AccessorPropertyTableRef CustomerInvoicingCollectionDM::get() const
    {
        return m_Accessor->getPropertyTable();
    }

    bool CustomerInvoicingCollectionDM::isEmpty() const
    {
        return 0 == getAccessor().get() || m_Accessor->getPropertyTable().isNull() ||
               m_Accessor->getPropertyTable().isEmpty();
    }

    void CustomerInvoicingCollectionDM::readCollection()
    {
        METHODNAME_DEF( CustomerInvoicingCollectionDM, readCollection )
        BLOG_TRACE_METHOD( getLogger(), fun );

        using infrastructure::accessor::customerInvoice::lit::READ_CUSTOMER_INVOICING_COLLECTION;

        basar::db::aspect::ExecuteResultInfo executeResultInfo;
        
        try
        {
            executeResultInfo = getAccessor()->execute( READ_CUSTOMER_INVOICING_COLLECTION );
        }
        catch( basar::Exception & e  )
        {
            libutil::exceptions::ExceptionHandler::processAccessorException( e, getLogger(), fun, READ_CUSTOMER_INVOICING_COLLECTION, 
                                                                             __FILE__, __LINE__ );
            throw;
        }

        if( executeResultInfo.hasError() )
        {
            THROW_ACCESSOR_EXECUTION_EXCEPTION( fun, READ_CUSTOMER_INVOICING_COLLECTION, executeResultInfo );
        }
    }

    void CustomerInvoicingCollectionDM::save()
    {
        METHODNAME_DEF( CustomerInvoicingCollectionDM, save )
        BLOG_TRACE_METHOD( getLogger(), fun );

        for( basar::db::aspect::AccessorPropertyTable_YIterator yit = get().begin(); ! yit.isEnd(); ++yit )
        {
            ICustomerInvoicePtr customerInvoice = getCustomerInvoice( yit );
            customerInvoice->get().setDecimal( properties::AMOUNT, yit.getDecimal( properties::AMOUNT ) );
            
            customerInvoice->save();
        }

        backup();
    }

    void CustomerInvoicingCollectionDM::backup() const
    {
        METHODNAME_DEF( CustomerInvoicingCollectionDM, backup )
        BLOG_TRACE_METHOD( getLogger(), fun );

        using infrastructure::accessor::customerInvoice::lit::BACKUP_INVOICING;

        try
        {
            getAccessor()->execute( BACKUP_INVOICING ); // failing of backup is not critical
        }
        catch( basar::Exception & e  )
        {
            libutil::exceptions::ExceptionHandler::processAccessorException( e, getLogger(), fun, BACKUP_INVOICING,
                                                                             __FILE__, __LINE__ );
            throw;
        }
    }

    /*
    libutil::domMod::SearchYIteratorPtr CustomerInvoicingCollectionDM::getSearchYIterator()
    {
        if( NULL == m_SearchYIterator.get() )
        {
            m_SearchYIterator = libutil::domMod::SearchYIteratorPtr(
                new libutil::domMod::SearchYIterator( properties::SUM_RETURNS.toDescriptionString() // dummy - empty prop not allowed
                ) 
            );
        }

        return m_SearchYIterator;
    }
    */

    const log4cplus::Logger& CustomerInvoicingCollectionDM::getLogger() const
    {
        return m_Logger;
    }

} // end namespace customerInvoice
} // end namespace domMod
} // end namespace libcsc_deli
