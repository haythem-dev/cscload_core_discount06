#include <persistence/accessor.h>
#include <persistence/connection.h>
#include "cscorderposcomponentmanager.h"
#include "cscorderpos/cscorderpossplittinfo/cscorderpossplittinforepository.h"
#include "cscorderpos/cscorderpossplittinfo/cscorderpossplittinforepositoryptr.h"


namespace libcsc {
namespace cscorderpos {

CSCOrderposComponentManager::CSCOrderposComponentManager()
{
}

CSCOrderposComponentManager::~CSCOrderposComponentManager()
{
}

void CSCOrderposComponentManager::injectConnection(persistence::ConnectionPtr connection)
{
    m_Connection = connection;
}

persistence::IAccessorPtr CSCOrderposComponentManager::createAccessor()
{
    return persistence::IAccessorPtr(new persistence::Accessor(m_Connection->getDbSqlConnection()));
}

void CSCOrderposComponentManager::injectTransactionHandler(nDataBase* transHandler)
{
    m_TransactionHandler = transHandler;
}

persistence::TransactionGuard CSCOrderposComponentManager::createTransaction() const
{
    return persistence::TransactionGuard(m_TransactionHandler);
}

repo::ICSCOrderposSplittinfoRepositoryPtr CSCOrderposComponentManager::createCSCOrderposSplittinfoRepository()
{
    repo::CSCOrderposSplittinfoRepositoryPtr repository =
        repo::CSCOrderposSplittinfoRepositoryPtr(new repo::CSCOrderposSplittinfoRepository());
    repository->injectInsertAccessor(createAccessor());
    repository->injectFindAccessor(createAccessor());
    repository->injectTransactionFactory(shared_from_this());
    return repository;
}

repo::ICSCOrderposSplittinfoRepositoryPtr CSCOrderposComponentManager::getCSCOrderposSplittinfoRepository()
{
    return createCSCOrderposSplittinfoRepository();
}

} // end namespace cscorderpos
} // end namespace libcsc
