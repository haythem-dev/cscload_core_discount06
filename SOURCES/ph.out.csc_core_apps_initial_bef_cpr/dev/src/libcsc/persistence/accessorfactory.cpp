#include "persistence/accessorfactory.h"
#include <logger/loggerpool.h>
#include <exceptions/cscexceptionbase.h>
#include <exceptions/persistenceexception.h>
#include <persistence/accessor.h>
#include <persistence/connection.h>
#include <sstream>

namespace libcsc
{
namespace persistence
{
AccessorFactory::AccessorFactory()
    : m_DirtyReadSet(false)
{
    BLOG_TRACE_METHOD( LoggerPool::getLoggerInfrastructure(), "AccessorFactory::AccessorFactory()" );
}

AccessorFactory::~AccessorFactory()
{
    BLOG_TRACE_METHOD( LoggerPool::getLoggerInfrastructure(), "AccessorFactory::~AccessorFactory()" );
}


void AccessorFactory::injectConnection(persistence::ConnectionPtr connection)
{
    BLOG_TRACE_METHOD(LoggerPool::getLoggerInfrastructure(), "AccessorFactory::injectConnection()");

    m_Connection = connection;
}

bool AccessorFactory::EnsureDBConnectionWithDirtyRead()
{
    if (!m_DirtyReadSet &&
        m_Connection.get() != NULL &&
        !m_Connection->getDbSqlConnection().isNull()
        )
    {
        LOG4CPLUS_TRACE(libcsc::LoggerPool::getLoggerDocuments(), "AccessorFactory::EnsureDBConnectionWithDirtyRead() Setting DB Connection to Dirty Read...");
        
        m_Connection->setIsolationLevel(basar::INFX_DIRTYREAD);
        m_DirtyReadSet = true;

        LOG4CPLUS_INFO(libcsc::LoggerPool::getLoggerDocuments(), "AccessorFactory::EnsureDBConnectionWithDirtyRead() DB Connection is set to Dirty Read!");
    }

    return m_DirtyReadSet;
}

persistence::IAccessorPtr AccessorFactory::createAccessor() const
{
    BLOG_TRACE_METHOD(LoggerPool::getLoggerInfrastructure(), "AccessorFactory::createAccessor()");
    return persistence::IAccessorPtr(new persistence::Accessor(m_Connection->getDbSqlConnection()));
}



} // end namespace persistence
} // end namespace libcsc

