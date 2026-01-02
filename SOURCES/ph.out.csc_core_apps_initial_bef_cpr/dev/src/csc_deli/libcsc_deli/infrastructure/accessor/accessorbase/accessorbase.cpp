#include "accessorbase.h"

#include <accessor/aspectmanagertools.h>
#include <boost/bind.hpp>

namespace libcsc_deli
{
namespace infrastructure
{
namespace accessor
{
    AccessorBase::AccessorBase( const basar::VarString& accessorName )
    {
        m_AccessorDefinitionName = libutil::AspectManagerTools::createUniqueAccessorInstanceName( accessorName + "_Instance" );
    }

    AccessorBase::~AccessorBase()
    {
        destroyAccessor();
    }

    void AccessorBase::init()
    {
        if( ! m_AccessMethodCaller.isInitialized() )
        {
            registerAccessorMethods( m_AccessMethodCaller );
        }
    }

    bool AccessorBase::isInitialized() const
    {
        return ! m_Accessor.isNull();
    }

    void AccessorBase::initAccessor() const
	{
		if( ! isInitialized() )
		{
			using namespace basar::db::aspect;

            if( ! Manager::getInstance().hasAccessorDefinition( m_AccessorDefinitionName ) )
            {
                using namespace basar::db::aspect;
                AccessorDefinitionRef adr = Manager::getInstance().createAccessorDefinition( m_AccessorDefinitionName );
                setupPropertyDescriptionList( adr.getPropertyDescriptionList() );
            }

			basar::VarString instanceName = libutil::AspectManagerTools::createUniqueAccessorInstanceName( m_AccessorDefinitionName + "_Instance" );
			m_Accessor = Manager::getInstance().createAccessorInstance( instanceName, m_AccessorDefinitionName, 
				ConnectionRef(), FULL_CACHING, true );
		}
	}

    void AccessorBase::destroyAccessor()
    {
        if( isInitialized() )
        {
            if( ! m_Accessor.isNull() )
		    {
			    basar::db::aspect::Manager::getInstance().releaseAccessorInstance( m_Accessor.getAccessorName() );
			    m_Accessor.reset();
		    }

		    basar::db::aspect::Manager::getInstance().releaseAccessorDefinition( m_AccessorDefinitionName );
        }
    }

    void AccessorBase::clear( bool /*doClear*/ )
    {
        /*
        if( isInitialized() && doClear )
        {
            getPropertyTable().clear();
        }
        */
    }

    basar::db::aspect::AccessorInstanceRef AccessorBase::getAccessor() const
    {
        initAccessor();
        return m_Accessor;
    }

    const basar::db::aspect::AccessorPropertyTableRef AccessorBase::getPropertyTable() const
    {
        return getAccessor().getPropertyTable();
    }

    basar::db::aspect::AccessorPropertyTableRef AccessorBase::getPropertyTable()
    {
        return getAccessor().getPropertyTable();
    }

    const basar::db::aspect::ExecuteResultInfo AccessorBase::execute( const basar::db::aspect::AccessMethodName& accessMethod,
                                                                          const bool clearBeforeSelect, const bool flagExcept, 
                                                                          const basar::db::aspect::DatabaseHintEnum )
    {
        init();
        clear( clearBeforeSelect );

        return m_AccessMethodCaller.execute( accessMethod, getPropertyTable().end(), flagExcept );
    }

    const basar::db::aspect::ExecuteResultInfo AccessorBase::execute( const basar::db::aspect::AccessMethodName& accessMethod, 
                                                                          basar::db::aspect::AccessorPropertyTable_YIterator yit,
	                                                                      const bool clearBeforeSelect, const bool flagExcept, 
	                                                                      const basar::db::aspect::DatabaseHintEnum )
    {
        init();
        clear( clearBeforeSelect );

        return m_AccessMethodCaller.execute( accessMethod, yit, flagExcept );
    }

    const basar::db::aspect::ExecuteResultInfo AccessorBase::execute( const basar::db::aspect::AccessMethodName& accessMethod,
	                                                                      basar::db::aspect::AccessorPropertyTable_YIterator yitBegin, 
                                                                          basar::db::aspect::AccessorPropertyTable_YIterator yitEnd,
	                                                                      const bool clearBeforeSelect, const bool flagExcept,
	                                                                      const basar::db::aspect::DatabaseHintEnum )
    {
        init();
        clear( clearBeforeSelect );

        basar::db::aspect::ExecuteResultInfo resultInfo;
        for( basar::db::aspect::AccessorPropertyTable_YIterator yit = yitBegin; yit != yitEnd; ++yit )
        {
            const basar::db::aspect::ExecuteResultInfo resInfo = m_AccessMethodCaller.execute( accessMethod, yit, flagExcept );
            resultInfo.m_affectedRows += resInfo.getAffectedRows();

            if( resInfo.hasError() )
            {
                resultInfo.m_error = resInfo.getError();
                break;
            }
        }

        return resultInfo;
    }

    const std::pair<bool, basar::Decimal> AccessorBase::executeAggregate( const basar::db::aspect::AccessMethodName& accessMethod )
    {
        basar::db::aspect::ExecuteResultInfo e = m_AccessMethodCaller.execute( accessMethod, getPropertyTable().end(), false );

        return std::make_pair< bool, basar::Decimal >( e.hasError(), basar::Decimal() ); // TODO dummy
    }

	const std::pair<bool, basar::Decimal> AccessorBase::executeAggregate( const basar::db::aspect::AccessMethodName& accessMethod,
                                                                              basar::db::aspect::AccessorPropertyTable_YIterator yit )
    {
        basar::db::aspect::ExecuteResultInfo e = m_AccessMethodCaller.execute( accessMethod, yit, false );

        return std::make_pair< bool, basar::Decimal >( e.hasError(), basar::Decimal() ); // TODO dummy
    }

    //-----------------------------------------------------------------------------------//
	// Serial id methods -> not needed in a file accessor (dummy implementation)
	//-----------------------------------------------------------------------------------//
    basar::Int64 AccessorBase::getLastInsertedSerial()
    {
        return 0;
    }

    basar::Int64 AccessorBase::getInsertedSerial( const basar::Int32 )
    {
        return 0;
    }

    basar::Int32 AccessorBase::getNumberOfLastInsertedSerials()
    {
        return 0;
    }

    bool AccessorBase::hasLastInsertedSerial()
    {
        return false;
    }

    void AccessorBase::clearLastInsertedSerials()
    {
    }

} // end namespace accessor
} // end namespace infrastructure
} // end namespace libcsc_deli
