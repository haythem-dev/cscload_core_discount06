#include "accessorproxyuniondecorator.h"
#include "infrastructure/connectionpool/iconnectionpoolgetter.h"

#include "loggerpool/libcsc_deli_loggerpool.h"
#include <numeric>
#include <boost/make_shared.hpp>

namespace libcsc_deli
{
namespace infrastructure
{
namespace accessor
{
    AccessorProxyUnionDecorator::AccessorProxyUnionDecorator( const basar::VarString & accessorName, connectionPool::IConnectionPoolGetterPtr connectionPool,
                                                              const basar::db::aspect::CachingPolicyEnum /*eCachePolicy = basar::db::aspect::ON_DEMAND_CACHING */,
                                                              const bool storeInInstanceList /* = true */ )
     : m_Logger( LoggerPool::getLoggerAccessors() )
    {
        METHODNAME_DEF( AccessorProxyUnionDecorator, AccessorProxyUnionDecorator );
        BLOG_TRACE_METHOD( getLogger(), fun );

        // create an accessor for each configured connection
        using connectionPool::IConnectionPoolGetter;
        const IConnectionPoolGetter::ConnectionNameCollection& connectionNames = connectionPool->getConnectionNames();
        for( IConnectionPoolGetter::ConnectionNameCollection::const_iterator it = connectionNames.begin(); it != connectionNames.end(); ++it )
        {
            m_Accessors.push_back( boost::make_shared< libutil::infrastructure::accessor::AccessorProxy >( accessorName,
                                                                                                           connectionPool->getConnection( *it )->getCurrentConnection(),
                                                                                                           basar::db::aspect::FULL_CACHING, storeInInstanceList ) );
        }
        m_DefaultAccessor = *m_Accessors.begin(); // set Accessor to first item (equals default accessor)
    }

    AccessorProxyUnionDecorator::~AccessorProxyUnionDecorator()
    {
        METHODNAME_DEF( AccessorProxyUnionDecorator, ~AccessorProxyUnionDecorator );
        BLOG_TRACE_METHOD( getLogger(), fun );
    }

    const log4cplus::Logger& AccessorProxyUnionDecorator::getLogger() const
    {
        return m_Logger;
    }

    void AccessorProxyUnionDecorator::appendToDefaultAccessor( basar::db::aspect::AccessorPropertyTableRef propTab )
    {
        // append to default accessor
        for( basar::db::aspect::AccessorPropertyTable_YIterator yit = propTab.begin(); ! yit.isEnd(); ++yit )
        {
            basar::db::aspect::AccessorPropertyTable_YIterator newYit = m_DefaultAccessor->getPropertyTable().insert( basar::FOR_CLEAN );
            newYit.match( yit );
        }

        std::ostringstream msg;
        msg << "AccessorPropTab Entries: " << m_DefaultAccessor->getPropertyTable().size() << std::endl;
        BLOG_TRACE( LoggerPool::getLoggerAccessors(), msg.str() );
    }

    const basar::db::aspect::AccessorPropertyTableRef AccessorProxyUnionDecorator::getPropertyTable() const
    {
        return m_DefaultAccessor->getPropertyTable();
    }

    basar::db::aspect::AccessorPropertyTableRef AccessorProxyUnionDecorator::getPropertyTable()
    {
        return m_DefaultAccessor->getPropertyTable();
    }

    const basar::db::aspect::ExecuteResultInfo AccessorProxyUnionDecorator::execute( const basar::db::aspect::AccessMethodName& accessMethodName,
                                                                                     const bool clearBeforeSelect, const bool flagExcept,
                                                                                     const basar::db::aspect::DatabaseHintEnum dbHint )
    {
        METHODNAME_DEF( AccessorProxyUnionDecorator, execute );
        BLOG_TRACE_METHOD( getLogger(), fun );

        basar::db::aspect::ExecuteResultInfo resInfo;
        for( AccessorCollection::iterator it = m_Accessors.begin(); it != m_Accessors.end(); ++it )
        {
            resInfo = (*it)->execute( accessMethodName, clearBeforeSelect, flagExcept, dbHint );
            if( *it != m_DefaultAccessor )
            {
                appendToDefaultAccessor( (*it)->getPropertyTable() );
            }
        }

        return resInfo;
    }

    const basar::db::aspect::ExecuteResultInfo AccessorProxyUnionDecorator::execute( const basar::db::aspect::AccessMethodName& accessMethodName,
                                                                                     basar::db::aspect::AccessorPropertyTable_YIterator yit_,
                                                                                     const bool clearBeforeSelect, const bool flagExcept,
                                                                                     const basar::db::aspect::DatabaseHintEnum dbHint )
    {
        METHODNAME_DEF( AccessorProxyUnionDecorator, execute );
        BLOG_TRACE_METHOD( getLogger(), fun );

        basar::db::aspect::ExecuteResultInfo resInfo;
        for( AccessorCollection::iterator it = m_Accessors.begin(); it != m_Accessors.end(); ++it )
        {
            resInfo = (*it)->execute( accessMethodName, yit_, clearBeforeSelect, flagExcept, dbHint );
            if( *it != m_DefaultAccessor )
            {
                appendToDefaultAccessor( (*it)->getPropertyTable() );
            }
        }

        basar::db::aspect::AccessorPropertyTableRef tab = getPropertyTable();
        LOG_PROPTAB( tab, getLogger(), fun );

        return resInfo;
    }

    const basar::db::aspect::ExecuteResultInfo AccessorProxyUnionDecorator::execute( const basar::db::aspect::AccessMethodName& accessMethodName,
                                                                                     basar::db::aspect::AccessorPropertyTable_YIterator yitBegin,
                                                                                     basar::db::aspect::AccessorPropertyTable_YIterator yitEnd,
                                                                                     const bool clearBeforeSelect, const bool flagExcept,
                                                                                     const basar::db::aspect::DatabaseHintEnum dbHint )
    {
        METHODNAME_DEF( AccessorProxyUnionDecorator, execute );
        BLOG_TRACE_METHOD( getLogger(), fun );

        basar::db::aspect::ExecuteResultInfo resInfo;
        for( AccessorCollection::iterator it = m_Accessors.begin(); it != m_Accessors.end(); ++it )
        {
            resInfo = (*it)->execute( accessMethodName, yitBegin, yitEnd, clearBeforeSelect, flagExcept, dbHint );
            if( *it != m_DefaultAccessor )
            {
                appendToDefaultAccessor( (*it)->getPropertyTable() );
            }
        }

        basar::db::aspect::AccessorPropertyTableRef tab = getPropertyTable();
        LOG_PROPTAB( tab, getLogger(), fun );

        return resInfo;
    }

    const std::pair<bool, basar::Decimal> AccessorProxyUnionDecorator::executeAggregate( const basar::db::aspect::AccessMethodName& accessMethodName )
    {
        METHODNAME_DEF( AccessorProxyUnionDecorator, executeAggregate );
        BLOG_TRACE_METHOD( getLogger(), fun );

        std::pair<bool, basar::Decimal> resultInfo, resInfo;
        for( AccessorCollection::iterator it = m_Accessors.begin(); it != m_Accessors.end(); ++it )
        {
            resInfo = (*it)->executeAggregate( accessMethodName );
            if( *it != m_DefaultAccessor && resInfo.first )
            {
                resultInfo.second += resInfo.second;
            }
        }

        return resultInfo;
    }

    const std::pair<bool, basar::Decimal> AccessorProxyUnionDecorator::executeAggregate( const basar::db::aspect::AccessMethodName& accessMethodName,
                                                                               basar::db::aspect::AccessorPropertyTable_YIterator yit )
    {
        METHODNAME_DEF( AccessorProxyUnionDecorator, executeAggregate );
        BLOG_TRACE_METHOD( getLogger(), fun );

        std::pair<bool, basar::Decimal> resultInfo, resInfo;
        for( AccessorCollection::iterator it = m_Accessors.begin(); it != m_Accessors.end(); ++it )
        {
            resInfo = (*it)->executeAggregate( accessMethodName, yit );
            if( *it != m_DefaultAccessor && resInfo.first )
            {
                resultInfo.second += resInfo.second;
            }
        }

        return resultInfo;
    }

    basar::Int64 AccessorProxyUnionDecorator::getLastInsertedSerial()
    {
        return m_DefaultAccessor->getLastInsertedSerial();
    }

    basar::Int64 AccessorProxyUnionDecorator::getInsertedSerial( const basar::Int32 index )
    {
        return m_DefaultAccessor->getInsertedSerial( index );
    }

    basar::Int32 AccessorProxyUnionDecorator::getNumberOfLastInsertedSerials()
    {
        return m_DefaultAccessor->getNumberOfLastInsertedSerials();
    }

    bool AccessorProxyUnionDecorator::hasLastInsertedSerial()
    {
        return m_DefaultAccessor->hasLastInsertedSerial();
    }

    void AccessorProxyUnionDecorator::clearLastInsertedSerials()
    {
        m_DefaultAccessor->clearLastInsertedSerials();
    }

} // end namespace accessor
} // end namespace infrastructure
} // end namespace libcsc_deli
