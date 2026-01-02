//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include "debtlimitdm.h"

#include "infrastructure/accessor/debtlimit/debtlimitacc_definitions.h"
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
namespace debtLimit
{

    const libutil::misc::ClassInfo& DebtLimitDM::getClassInfo()
    {
        static const libutil::misc::ClassInfo info( "DebtLimitDM", libutil::misc::Version( 1, 0, 0, 0 ) );
        return info;
    }

    DebtLimitDM::DebtLimitDM()
    : m_Logger( libcsc_deli::LoggerPool::getLoggerDomModules() )
    {
        METHODNAME_DEF( DebtLimitDM, DebtLimitDM )
        BLOG_TRACE_METHOD( getLogger(), fun );
    }

    DebtLimitDM::~DebtLimitDM()
    {
        METHODNAME_DEF( DebtLimitDM, ~DebtLimitDM )
        BLOG_TRACE_METHOD( getLogger(), fun );
    }

    void DebtLimitDM::injectDebtLimitAccessor( libutil::infrastructure::accessor::IAccessorPtr accessor )
    {
        m_Accessor = accessor;
    }

    libutil::infrastructure::accessor::IAccessorPtr DebtLimitDM::getAccessor() const
    {
        CHECK_INSTANCE_EXCEPTION( m_Accessor.get() );
        return m_Accessor;
    }

    void DebtLimitDM::set( basar::db::aspect::AccessorPropertyTable_YIterator yit )
    {
        m_YitDebtLimit = yit;
    }

    basar::db::aspect::AccessorPropertyTable_YIterator DebtLimitDM::get() const
    {
        return m_YitDebtLimit;
    }

    basar::db::aspect::AccessorPropertyTable_YIterator DebtLimitDM::get()
    {
        return m_YitDebtLimit;
    }
    
    bool DebtLimitDM::isChanged() const
    {
        basar::property::PropertyStateSet stateSet;
        stateSet.insert( basar::SS_INSERT );
        stateSet.insert( basar::SS_UPDATE );

        return get().getState().contains( stateSet );
    }

    bool DebtLimitDM::isEmpty() const
    {
        return get().isEnd();
    }

    void DebtLimitDM::erase()
    {
        METHODNAME_DEF( DebtLimitDM, erase )
        BLOG_TRACE_METHOD( getLogger(), fun );

        using infrastructure::accessor::debtLimit::lit::DELETE_DEBTLIMIT;

        basar::db::aspect::ExecuteResultInfo executeResultInfo;
        try
        {
            executeResultInfo = getAccessor()->execute( DELETE_DEBTLIMIT, get() );
        }
        catch( basar::Exception& e )
        {
            libutil::exceptions::ExceptionHandler::processAccessorException( e, getLogger(), fun, DELETE_DEBTLIMIT, __FILE__, __LINE__ );
            throw;
        }

        if( executeResultInfo.hasError() )
        {
            THROW_ACCESSOR_EXECUTION_EXCEPTION( fun, DELETE_DEBTLIMIT, executeResultInfo )
        }
    }

    void DebtLimitDM::save()
    {
        METHODNAME_DEF( DebtLimitDM, save )
        BLOG_TRACE_METHOD( getLogger(), fun );

        if( isEmpty() )
        {
            return;
        }

        using infrastructure::accessor::debtLimit::lit::SAVE_DEBTLIMIT;

        basar::db::aspect::ExecuteResultInfo executeResultInfo;
        try
        {
            executeResultInfo = getAccessor()->execute( SAVE_DEBTLIMIT, get() );
        }
        catch( basar::Exception& e )
        {
            libutil::exceptions::ExceptionHandler::processAccessorException( e, getLogger(), fun, SAVE_DEBTLIMIT, __FILE__, __LINE__ );
            throw;
        }

        if( executeResultInfo.hasError() )
        {
            THROW_ACCESSOR_EXECUTION_EXCEPTION( fun, SAVE_DEBTLIMIT, executeResultInfo )
        }
    }

    /*
    libutil::domMod::SearchYIteratorPtr DebtLimitDM::getSearchYIterator()
    {
        if( NULL == m_SearchYIterator.get() )
        {
            m_SearchYIterator = libutil::domMod::SearchYIteratorPtr(
                new libutil::domMod::SearchYIterator( properties::PARTNER_NO.toDescriptionString() ) 
            );
        }

        return m_SearchYIterator;
    }
    */

    const log4cplus::Logger& DebtLimitDM::getLogger() const
    {
        return m_Logger;
    }

} // end namespace debtLimit
} // end namespace domMod
} // end namespace libcsc_deli
