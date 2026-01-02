//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include "sapbalancecollectiondm.h"

#include "infrastructure/accessor/sap/sapbalancecollectionacc_definitions.h"

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

    const libutil::misc::ClassInfo& SAPBalanceCollectionDM::getClassInfo()
    {
        static const libutil::misc::ClassInfo info( "SAPBalanceCollectionDM", libutil::misc::Version( 1, 0, 0, 0 ) );
        return info;
    }

    SAPBalanceCollectionDM::SAPBalanceCollectionDM()
    : m_Logger( libcsc_deli::LoggerPool::getLoggerDomModules() )
    {
        METHODNAME_DEF( SAPBalanceCollectionDM, SAPBalanceCollectionDM )
        BLOG_TRACE_METHOD( getLogger(), fun );
    }

    SAPBalanceCollectionDM::~SAPBalanceCollectionDM()
    {
        METHODNAME_DEF( SAPBalanceCollectionDM, ~SAPBalanceCollectionDM )
        BLOG_TRACE_METHOD( getLogger(), fun );
    }

    void SAPBalanceCollectionDM::injectSAPBalanceCollectionAccessor( libutil::infrastructure::accessor::IAccessorPtr accessor )
    {
        m_Accessor = accessor;
    }

    libutil::infrastructure::accessor::IAccessorPtr SAPBalanceCollectionDM::getAccessor() const
    {
        CHECK_INSTANCE_EXCEPTION( m_Accessor.get() );
        return m_Accessor;
    }

    basar::db::aspect::AccessorPropertyTableRef SAPBalanceCollectionDM::get() const
    {
        return getAccessor()->getPropertyTable();
    }

    bool SAPBalanceCollectionDM::isEmpty() const
    {
        return 0 == getAccessor().get() || m_Accessor->getPropertyTable().isNull() ||
               m_Accessor->getPropertyTable().isEmpty();
    }

    void SAPBalanceCollectionDM::readCollection()
    {
        METHODNAME_DEF( SAPBalanceCollectionDM, readCollection )
        BLOG_TRACE_METHOD( getLogger(), fun );

        using infrastructure::accessor::sap::lit::READ_SAP_BALANCE_COLLECTION;

        basar::db::aspect::ExecuteResultInfo executeResultInfo;
        try
        {
            executeResultInfo = getAccessor()->execute( READ_SAP_BALANCE_COLLECTION );
        }
        catch( basar::Exception& e )
        {
            libutil::exceptions::ExceptionHandler::processAccessorException( e, getLogger(), fun, READ_SAP_BALANCE_COLLECTION, 
                                                                             __FILE__, __LINE__ );
            throw;
        }

        if( executeResultInfo.hasError() )
        {
            THROW_ACCESSOR_EXECUTION_EXCEPTION( fun, READ_SAP_BALANCE_COLLECTION, executeResultInfo )
        }
    }

    void SAPBalanceCollectionDM::backup() const
    {
        METHODNAME_DEF( SAPBalanceCollectionDM, backup )
        BLOG_TRACE_METHOD( getLogger(), fun );

        using infrastructure::accessor::sap::lit::BACKUP_SAP_BALANCE;

        try
        {
            getAccessor()->execute( BACKUP_SAP_BALANCE ); // failing of backup is not critical
        }
        catch( basar::Exception & e  )
        {
            libutil::exceptions::ExceptionHandler::processAccessorException( e, getLogger(), fun, BACKUP_SAP_BALANCE,
                                                                             __FILE__, __LINE__ );
            throw;
        }
    }

    /*
    libutil::domMod::SearchYIteratorPtr SAPBalanceCollectionDM::getSearchYIterator()
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

    const log4cplus::Logger& SAPBalanceCollectionDM::getLogger() const
    {
        return m_Logger;
    }

} // end namespace sap
} // end namespace domMod
} // end namespace libcsc_deli
