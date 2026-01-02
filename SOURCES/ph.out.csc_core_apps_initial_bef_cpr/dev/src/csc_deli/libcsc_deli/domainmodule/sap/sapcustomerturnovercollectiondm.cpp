//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include "sapcustomerturnovercollectiondm.h"

#include "infrastructure/accessor/sap/sapcustomerturnovercollectionacc_definitions.h"

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
namespace sap
{

    const libutil::misc::ClassInfo& SAPCustomerTurnoverCollectionDM::getClassInfo()
    {
        static const libutil::misc::ClassInfo info( "SAPCustomerTurnoverCollectionDM", libutil::misc::Version( 1, 0, 0, 0 ) );
        return info;
    }

    SAPCustomerTurnoverCollectionDM::SAPCustomerTurnoverCollectionDM()
    : m_Logger( libcsc_deli::LoggerPool::getLoggerDomModules() )
    {
        METHODNAME_DEF( SAPCustomerTurnoverCollectionDM, SAPCustomerTurnoverCollectionDM )
        BLOG_TRACE_METHOD( getLogger(), fun );
    }

    SAPCustomerTurnoverCollectionDM::~SAPCustomerTurnoverCollectionDM()
    {
        METHODNAME_DEF( SAPCustomerTurnoverCollectionDM, ~SAPCustomerTurnoverCollectionDM )
        BLOG_TRACE_METHOD( getLogger(), fun );
    }

    void SAPCustomerTurnoverCollectionDM::injectSAPCustomerTurnoverCollectionAccessor( libutil::infrastructure::accessor::IAccessorPtr accessor )
    {
        m_Accessor = accessor;
    }

    libutil::infrastructure::accessor::IAccessorPtr SAPCustomerTurnoverCollectionDM::getAccessor() const
    {
        CHECK_INSTANCE_EXCEPTION( m_Accessor.get() );
        return m_Accessor;
    }

    basar::db::aspect::AccessorPropertyTableRef SAPCustomerTurnoverCollectionDM::get() const
    {
        return getAccessor()->getPropertyTable();
    }

    bool SAPCustomerTurnoverCollectionDM::isEmpty() const
    {
        return 0 == getAccessor().get() || m_Accessor->getPropertyTable().isNull() ||
               m_Accessor->getPropertyTable().isEmpty();
    }

    void SAPCustomerTurnoverCollectionDM::insert( basar::db::aspect::AccessorPropertyTable_YIterator turnoverCollYit )
    {
        basar::db::aspect::AccessorPropertyTable_YIterator yit = get().insert( basar::FOR_INSERT );
        yit.match( turnoverCollYit );
    }

    void SAPCustomerTurnoverCollectionDM::writeCollection()
    {
        METHODNAME_DEF( SAPCustomerTurnoverCollectionDM, writeCollection )
        BLOG_TRACE_METHOD( getLogger(), fun );

        using infrastructure::accessor::sap::lit::WRITE_SAP_CUSTOMER_TURNOVER_COLLECTION;

        basar::db::aspect::ExecuteResultInfo executeResultInfo;
        try
        {
            executeResultInfo = getAccessor()->execute( WRITE_SAP_CUSTOMER_TURNOVER_COLLECTION );
        }
        catch( basar::Exception& e )
        {
            libutil::exceptions::ExceptionHandler::processAccessorException( e, getLogger(), fun, WRITE_SAP_CUSTOMER_TURNOVER_COLLECTION, 
                                                                             __FILE__, __LINE__ );
            throw;
        }

        if( executeResultInfo.hasError() )
        {
            THROW_ACCESSOR_EXECUTION_EXCEPTION( fun, WRITE_SAP_CUSTOMER_TURNOVER_COLLECTION, executeResultInfo )
        }
    }

    /*
    libutil::domMod::SearchYIteratorPtr SAPCustomerTurnoverCollectionDM::getSearchYIterator()
    {
        if( NULL == m_SearchYIterator.get() )
        {
            m_SearchYIterator = libutil::domMod::SearchYIteratorPtr(
                new libutil::domMod::SearchYIterator( 
                )
            );
        }

        return m_SearchYIterator;
    }
    */

    const log4cplus::Logger& SAPCustomerTurnoverCollectionDM::getLogger() const
    {
        return m_Logger;
    }

} // end namespace sap
} // end namespace domMod
} // end namespace libcsc_deli
