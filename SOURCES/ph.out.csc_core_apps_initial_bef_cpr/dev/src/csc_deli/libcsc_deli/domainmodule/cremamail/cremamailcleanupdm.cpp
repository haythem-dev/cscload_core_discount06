//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include "cremamailcleanupdm.h"

#include "infrastructure/accessor/cremamail/cremamailcleanupacc_definitions.h"

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
namespace cremaMail
{

    const libutil::misc::ClassInfo& CremaMailCleanupDM::getClassInfo()
    {
        static const libutil::misc::ClassInfo info( "CremaMailCleanupDM", libutil::misc::Version( 1, 0, 0, 0 ) );
        return info;
    }

    CremaMailCleanupDM::CremaMailCleanupDM()
    : m_Logger( libcsc_deli::LoggerPool::getLoggerDomModules() )
    {
        METHODNAME_DEF( CremaMailCleanupDM, CremaMailCleanupDM )
        BLOG_TRACE_METHOD( getLogger(), fun );
    }

    CremaMailCleanupDM::~CremaMailCleanupDM()
    {
        METHODNAME_DEF( CremaMailCleanupDM, ~CremaMailCleanupDM )
        BLOG_TRACE_METHOD( getLogger(), fun );
    }

    void CremaMailCleanupDM::injectCremaMailCleanupAccessor( libutil::infrastructure::accessor::IAccessorPtr accessor )
    {
        m_Accessor = accessor;
    }

    libutil::infrastructure::accessor::IAccessorPtr CremaMailCleanupDM::getAccessor() const
    {
        CHECK_INSTANCE_EXCEPTION( m_Accessor.get() );
        return m_Accessor;
    }

    /*
    basar::db::aspect::AccessorPropertyTable_YIterator CremaMailCleanupDM::get() const
    {
        return getAccessor()->getPropertyTable().begin();
    }

    bool CremaMailCleanupDM::isEmpty() const
    {
        return 0 == getAccessor().get() || m_Accessor->getPropertyTable().isNull() ||
               m_Accessor->getPropertyTable().isEmpty();
    }
    */

    void CremaMailCleanupDM::cleanup()
    {
        METHODNAME_DEF( CremaMailCleanupDM, cleanup )
        BLOG_TRACE_METHOD( getLogger(), fun );

        using infrastructure::accessor::cremaMail::lit::CLEANUP_SEND_MAIL_FLAG;

        basar::db::aspect::ExecuteResultInfo executeResultInfo;
        try
        {
            executeResultInfo = getAccessor()->execute( CLEANUP_SEND_MAIL_FLAG  );
        }
        catch( basar::Exception& e )
        {
            libutil::exceptions::ExceptionHandler::processAccessorException( e, getLogger(), fun, CLEANUP_SEND_MAIL_FLAG, 
                                                                             __FILE__, __LINE__ );
            throw;
        }

        if( executeResultInfo.hasError() )
        {
            THROW_ACCESSOR_EXECUTION_EXCEPTION( fun, CLEANUP_SEND_MAIL_FLAG, executeResultInfo )
        }
    }

    /*
    libutil::domMod::SearchYIteratorPtr CremaMailCleanupDM::getSearchYIterator()
    {
        if( NULL == m_SearchYIterator.get() )
        {
            m_SearchYIterator = libutil::domMod::SearchYIteratorPtr(
                new libutil::domMod::SearchYIterator( // TODO
                )
            );
        }

        return m_SearchYIterator;
    }
    */

    const log4cplus::Logger& CremaMailCleanupDM::getLogger() const
    {
        return m_Logger;
    }

} // end namespace cremaMail
} // end namespace domMod
} // end namespace libcsc_deli
