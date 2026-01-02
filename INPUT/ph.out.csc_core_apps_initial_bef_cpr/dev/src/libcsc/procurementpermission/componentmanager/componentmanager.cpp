/*
 * componentmanager.cpp
 *
 *  Created on: 09.02.2016
 *  Author: sebastian.barth
 */

#include "componentmanager.h"
#include <persistence/accessor.h>
#include <persistence/connection.h>
#include "logger/loggerpool.h"
#include "procurementpermission/repository/repository.h"

namespace libcsc {
namespace procurementpermission {

ComponentManager::ComponentManager()
{
}

ComponentManager::~ComponentManager()
{
}

void ComponentManager::injectConnection(persistence::ConnectionPtr connection)
{
    m_Connection = connection;
}

persistence::IAccessorPtr ComponentManager::createAccessor()
{
    return persistence::IAccessorPtr(new persistence::Accessor(m_Connection->getDbSqlConnection()));
}

repo::IRepositoryPtr ComponentManager::getRepository()
{
    return createRepository();
}

repo::IRepositoryPtr ComponentManager::createRepository()
{
    repo::IRepositoryPtr repository = repo::Repository::create(LoggerPool::getLoggerProcurementPermissionRequest());
    repository->injectFindAccessor(createAccessor());

    return repository;
}

} // end namespace procurementpermission
} // end namespace libcsc
