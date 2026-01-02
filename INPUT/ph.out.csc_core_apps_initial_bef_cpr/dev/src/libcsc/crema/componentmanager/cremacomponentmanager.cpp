#include "cremacomponentmanager.h"
#include <persistence/accessor.h>
#include <persistence/connection.h>

#include <crema/repository/repositoryptr.h>
#include <crema/repository/repository.h>

namespace libcsc {
namespace crema {

CremaComponentManager::CremaComponentManager()
{
}

CremaComponentManager::~CremaComponentManager()
{
}

void CremaComponentManager::injectConnection(persistence::ConnectionPtr connection)
{
	m_Connection = connection;
}

persistence::IAccessorPtr CremaComponentManager::createAccessor()
{
	return persistence::IAccessorPtr(new persistence::Accessor(m_Connection->getDbSqlConnection()));
}

repo::IRepositoryPtr CremaComponentManager::createRepository()
{
	repo::IRepositoryPtr repository = repo::Repository::create(LoggerPool::getLoggerCrema());
	repository->injectFindAccessor(createAccessor());
    repository->injectInsertAccessor(createAccessor());
    repository->injectUpdateAccessor(createAccessor());
    return repository;
}

repo::IRepositoryPtr CremaComponentManager::getRepository()
{
    return createRepository();
}

} // end namespace crema
} // end namespace libcsc
