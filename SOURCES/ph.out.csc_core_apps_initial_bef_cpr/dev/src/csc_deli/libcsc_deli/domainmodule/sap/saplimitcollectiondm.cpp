//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include "saplimitcollectiondm.h"

#include "infrastructure/accessor/sap/saplimitcollectionacc_definitions.h"

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

    const libutil::misc::ClassInfo& SAPLimitCollectionDM::getClassInfo()
    {
        static const libutil::misc::ClassInfo info( "SAPLimitCollectionDM", libutil::misc::Version( 1, 0, 0, 0 ) );
        return info;
    }

    SAPLimitCollectionDM::SAPLimitCollectionDM()
    : m_Logger( libcsc_deli::LoggerPool::getLoggerDomModules() )
    {
        METHODNAME_DEF( SAPLimitCollectionDM, SAPLimitCollectionDM )
        BLOG_TRACE_METHOD( getLogger(), fun );
    }

    SAPLimitCollectionDM::~SAPLimitCollectionDM()
    {
        METHODNAME_DEF( SAPLimitCollectionDM, ~SAPLimitCollectionDM )
        BLOG_TRACE_METHOD( getLogger(), fun );
    }

    void SAPLimitCollectionDM::injectSAPLimitCollectionAccessor( libutil::infrastructure::accessor::IAccessorPtr accessor )
    {
        m_Accessor = accessor;
    }

    libutil::infrastructure::accessor::IAccessorPtr SAPLimitCollectionDM::getAccessor() const
    {
        CHECK_INSTANCE_EXCEPTION( m_Accessor.get() );
        return m_Accessor;
    }

    basar::db::aspect::AccessorPropertyTableRef SAPLimitCollectionDM::get() const
    {
        return getAccessor()->getPropertyTable();
    }

    bool SAPLimitCollectionDM::isEmpty() const
    {
        return 0 == getAccessor().get() || m_Accessor->getPropertyTable().isNull() ||
               m_Accessor->getPropertyTable().isEmpty();
    }

    void SAPLimitCollectionDM::readCollection()
    {
        METHODNAME_DEF( SAPLimitCollectionDM, readCollection )
        BLOG_TRACE_METHOD( getLogger(), fun );

        using infrastructure::accessor::sap::lit::READ_SAP_LIMIT_COLLECTION;

        basar::db::aspect::ExecuteResultInfo executeResultInfo;
        try
        {
            executeResultInfo = getAccessor()->execute( READ_SAP_LIMIT_COLLECTION );
        }
        catch( basar::Exception& e )
        {
            libutil::exceptions::ExceptionHandler::processAccessorException( e, getLogger(), fun, READ_SAP_LIMIT_COLLECTION, 
                                                                             __FILE__, __LINE__ );
            throw;
        }

        if( executeResultInfo.hasError() )
        {
            THROW_ACCESSOR_EXECUTION_EXCEPTION( fun, READ_SAP_LIMIT_COLLECTION, executeResultInfo )
        }
    }
    
    void SAPLimitCollectionDM::backup() const
    {
        METHODNAME_DEF( SAPLimitCollectionDM, backup )
        BLOG_TRACE_METHOD( getLogger(), fun );

        using infrastructure::accessor::sap::lit::BACKUP_SAP_LIMIT;

        try
        {
            getAccessor()->execute( BACKUP_SAP_LIMIT ); // failing of backup is not critical
        }
        catch( basar::Exception & e  )
        {
            libutil::exceptions::ExceptionHandler::processAccessorException( e, getLogger(), fun, BACKUP_SAP_LIMIT,
                                                                             __FILE__, __LINE__ );
            throw;
        }
    }

    /*
    libutil::domMod::SearchYIteratorPtr SAPLimitCollectionDM::getSearchYIterator()
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

    const log4cplus::Logger& SAPLimitCollectionDM::getLogger() const
    {
        return m_Logger;
    }

} // end namespace sap
} // end namespace domMod
} // end namespace libcsc_deli
