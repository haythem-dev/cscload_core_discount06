//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include "storagelocationdm.h"

#include "domainmodule/mainwarehousearticlesrelevantcalculator_properties_definitions.h"
#include "infrastructure/accessor/storagelocationslot/storagelocationslotacc_definitions.h"
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
namespace storageLocation
{

    const libutil::misc::ClassInfo& StorageLocationDM::getClassInfo()
    {
        static const libutil::misc::ClassInfo info( "StorageLocationDM", libutil::misc::Version( 1, 0, 0, 0 ) );
        return info;
    }

    StorageLocationDM::StorageLocationDM()
    : m_Logger( LoggerPool::getLoggerDomModules() )
    {
        METHODNAME_DEF( StorageLocationDM, StorageLocationDM )
        BLOG_TRACE_METHOD( getLogger(), fun );
    }

    StorageLocationDM::~StorageLocationDM()
    {
        METHODNAME_DEF( StorageLocationDM, ~StorageLocationDM )
        BLOG_TRACE_METHOD( getLogger(), fun );
    }

    void StorageLocationDM::injectStorageLocationSlotAccessor( libutil::infrastructure::accessor::IAccessorPtr accessor )
    {
        m_Accessor = accessor;
    }

    libutil::infrastructure::accessor::IAccessorPtr StorageLocationDM::getAccessor() const
    {
        CHECK_INSTANCE_EXCEPTION( m_Accessor.get() );
        return m_Accessor;
    }

    basar::db::aspect::AccessorPropertyTable_YIterator StorageLocationDM::get() const
    {
        return getAccessor()->getPropertyTable().begin();
    }

    bool StorageLocationDM::isEmpty() const
    {
        return 0 == getAccessor().get() || m_Accessor->getPropertyTable().isNull() ||
               m_Accessor->getPropertyTable().isEmpty();
    }

    libutil::domMod::SearchYIteratorPtr StorageLocationDM::getSearchYIterator()
    {
        if( NULL == m_SearchYIterator.get() )
        {
            m_SearchYIterator = boost::make_shared< libutil::domMod::SearchYIterator >( properties::BRANCH_NO.toDescriptionString() );
        }

        return m_SearchYIterator;
    }

    const log4cplus::Logger& StorageLocationDM::getLogger() const
    {
        return m_Logger;
    }

    void StorageLocationDM::findByBranchNo( basar::Int16 branchNo )
    {
        METHODNAME_DEF( StorageLocationDM, findByBranchNo );
        BLOG_TRACE_METHOD( getLogger(), fun );

        using infrastructure::accessor::storageSlot::lit::SELECT_PSEUDO_STORAGE_SLOT_BY_BRANCH;

        basar::db::aspect::ExecuteResultInfo executeResultInfo;
        try
        {
            getSearchYIterator()->get().setInt16( properties::BRANCH_NO, branchNo );
            executeResultInfo = getAccessor()->execute( SELECT_PSEUDO_STORAGE_SLOT_BY_BRANCH, getSearchYIterator()->get() );
        }
        catch( basar::Exception& e )
        {
            libutil::exceptions::ExceptionHandler::processAccessorException( e, getLogger(), fun, SELECT_PSEUDO_STORAGE_SLOT_BY_BRANCH, 
                                                                             __FILE__, __LINE__ );
            throw;
        }

        if( executeResultInfo.hasError() )
        {
            THROW_ACCESSOR_EXECUTION_EXCEPTION( fun, SELECT_PSEUDO_STORAGE_SLOT_BY_BRANCH, executeResultInfo )
        }
    }

    bool StorageLocationDM::hasStorageLocation( const basar::VarString& storageLocationSlot ) const
    {
        METHODNAME_DEF( StorageLocationDM, hasStorageLocation );
        BLOG_TRACE_METHOD( getLogger(), fun );

        if( isEmpty() )
        {
            const basar::VarString reason = "Pseudo storage location slot could not be found!";
            throw exceptions::DataNotFoundException( basar::ExceptInfo( fun, reason, __FILE__, __LINE__ ) );
        }

        return getPseudoStorageLocation() != storageLocationSlot;
    }

    basar::VarString StorageLocationDM::getPseudoStorageLocation() const
    {
        return get().getString( properties::STORAGE_LOCATION );
    }
} // end namespace storageLocation
} // end namespace domMod
} // end namespace mainwarehousearticlesrelevantcalculator
