//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include "mainwarehousedm.h"

#include "infrastructure/accessor/mainwarehouse/mainwarehouseacc_definitions.h"

#include "domainmodule/mainwarehousearticlesrelevantcalculator_properties_definitions.h"

#include "loggerpool/mainwarehousearticlesrelevantcalculator_loggerpool.h"
#include "exceptions/datanotfoundexception.h"

#include <libutil/domainmodule.h>
#include <libutil/version.h>
#include <libutil/exception.h>

#include <boost/make_shared.hpp>

//--------------------------------------------------------------------------------------------------//
// class definition section
//--------------------------------------------------------------------------------------------------//
namespace mainwarehousearticlesrelevantcalculator
{
namespace domMod
{
namespace mainwarehouse
{

    const libutil::misc::ClassInfo& MainwarehouseDM::getClassInfo()
    {
        static const libutil::misc::ClassInfo info( "MainwarehouseDM", libutil::misc::Version( 1, 0, 0, 0 ) );
        return info;
    }

    MainwarehouseDM::MainwarehouseDM()
    : m_Logger( LoggerPool::getLoggerDomModules() )
    {
        METHODNAME_DEF( MainwarehouseDM, MainwarehouseDM )
        BLOG_TRACE_METHOD( getLogger(), fun );
    }

    MainwarehouseDM::~MainwarehouseDM()
    {
        METHODNAME_DEF( MainwarehouseDM, ~MainwarehouseDM )
        BLOG_TRACE_METHOD( getLogger(), fun );
    }

    void MainwarehouseDM::injectMainwarehouseAccessor( libutil::infrastructure::accessor::IAccessorPtr accessor )
    {
        m_Accessor = accessor;
    }

    libutil::infrastructure::accessor::IAccessorPtr MainwarehouseDM::getAccessor() const
    {
        CHECK_INSTANCE_EXCEPTION( m_Accessor.get() );
        return m_Accessor;
    }

    basar::db::aspect::AccessorPropertyTable_YIterator MainwarehouseDM::get() const
    {
        METHODNAME_DEF( MainwarehouseDM, get )

        if( isEmpty() )
        {
            basar::VarString reason = "Could not find corresponding mainwarehouse branch number!";
            throw exceptions::DataNotFoundException( basar::ExceptInfo( fun, reason, __FILE__, __LINE__ ) );
        }

        return getAccessor()->getPropertyTable().begin();
    }

    bool MainwarehouseDM::isEmpty() const
    {
        return 0 == getAccessor().get() || m_Accessor->getPropertyTable().isNull() ||
               m_Accessor->getPropertyTable().isEmpty();
    }

    void MainwarehouseDM::findByBranchNo( basar::Int16 branchNo )
    {
        METHODNAME_DEF( MainwarehouseDM, findByBranchNo )
        BLOG_TRACE_METHOD( getLogger(), fun );

        using infrastructure::accessor::mainwarehouse::lit::SELECT_MAINWAREHOUSE_BY_BRANCH;

        basar::db::aspect::ExecuteResultInfo executeResultInfo;
        try
        {
			libutil::domMod::SearchYIteratorPtr searchYit = getSearchYIterator();
			searchYit->get().setInt16( properties::BRANCH_NO, branchNo );

            executeResultInfo = getAccessor()->execute( SELECT_MAINWAREHOUSE_BY_BRANCH, searchYit->get() );
        }
        catch( basar::Exception& e )
        {
            libutil::exceptions::ExceptionHandler::processAccessorException( e, getLogger(), fun, SELECT_MAINWAREHOUSE_BY_BRANCH,
                                                                             __FILE__, __LINE__ );
            throw;
        }

        if( executeResultInfo.hasError() )
        {
            THROW_ACCESSOR_EXECUTION_EXCEPTION( fun, SELECT_MAINWAREHOUSE_BY_BRANCH, executeResultInfo )
        }
    }

    basar::Int16 MainwarehouseDM::getMainwarehouseBranch() const
    {
        return get().getInt16( properties::BRANCH_NO_MAINWAREHOUSE );
    }

    libutil::domMod::SearchYIteratorPtr MainwarehouseDM::getSearchYIterator()
    {
        if( NULL == m_SearchYIterator.get() )
        {
            m_SearchYIterator = boost::make_shared< libutil::domMod::SearchYIterator >(
                properties::BRANCH_NO.toDescriptionString()
            );
        }

        return m_SearchYIterator;
    }

    const log4cplus::Logger& MainwarehouseDM::getLogger() const
    {
        return m_Logger;
    }

} // end namespace mainwarehouse
} // end namespace domMod
} // end namespace mainwarehousearticlesrelevantcalculator

