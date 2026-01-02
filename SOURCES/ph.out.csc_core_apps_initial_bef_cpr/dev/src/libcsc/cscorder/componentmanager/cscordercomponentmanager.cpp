#include "cscordercomponentmanager.h"
#include <persistence/accessor.h>
#include <persistence/connection.h>
#include <logger/loggerpool.h>
#include <boost/make_shared.hpp>

#include "cscorder/cscorderflags/cscorderflagsrepositoryptr.h"
#include "cscorder/cscorderflags/cscorderflagsrepository.h"
#include "cscorder/cscorderflags/icscorderflagsrepository.h"
#include "cscorder/cscorderibtpickingdata/cscorderibtpickingdatarepository.h"
#include "cscorder/cscorderibtpickingdata/cscorderibtpickingdatarepositoryptr.h"
#include "cscorder/usecase/savecsccallplanuc.h"
#include "cscorder/csccallplan/csccallplanrepository.h"
#include "cscorder/csccallplan/csccallplanrepositoryptr.h"

namespace libcsc
{
namespace cscorder
{

CSCOrderComponentManager::CSCOrderComponentManager()
{
}

CSCOrderComponentManager::~CSCOrderComponentManager()
{
}

void CSCOrderComponentManager::injectConnection( persistence::ConnectionPtr connection )
{
	m_Connection = connection;
}

persistence::IAccessorPtr CSCOrderComponentManager::createAccessor()
{
	return persistence::IAccessorPtr( new persistence::Accessor( m_Connection->getDbSqlConnection() ) );
}

void CSCOrderComponentManager::injectTransactionHandler (nDataBase * transHandler)
{
	m_TransactionHandler = transHandler;
}

persistence::TransactionGuard CSCOrderComponentManager::createTransaction() const
{
    return persistence::TransactionGuard(m_TransactionHandler);
}

repo::ICSCOrderFlagsRepositoryPtr CSCOrderComponentManager::createCSCOrderFlagsRepository()
{
	repo::CSCOrderFlagsRepositoryPtr repository = repo::CSCOrderFlagsRepositoryPtr( new repo::CSCOrderFlagsRepository() ); 	
	repository->injectDeleteAccessor( createAccessor() );
	repository->injectInsertAccessor( createAccessor() );
	repository->injectUpdateAccessor( createAccessor() );
	repository->injectFindAccessor( createAccessor() );
	repository->injectTransactionFactory(shared_from_this());    
	return repository;
}

repo::ICSCOrderFlagsRepositoryPtr CSCOrderComponentManager::getCSCOrderFlagsRepository()
{
    return createCSCOrderFlagsRepository();
}

repo::ICSCOrderIBTPickingdataRepositoryPtr CSCOrderComponentManager::createCSCOrderIBTPickingdataRepository()
{
    repo::CSCOrderIBTPickingdataRepositoryPtr repository =
        repo::CSCOrderIBTPickingdataRepositoryPtr(new repo::CSCOrderIBTPickingdataRepository());
    repository->injectInsertAccessor(createAccessor());
    repository->injectFindAccessor(createAccessor());
    repository->injectTransactionFactory(shared_from_this());
    return repository;
}

repo::ICSCOrderIBTPickingdataRepositoryPtr CSCOrderComponentManager::getCSCOrderIBTPickingdataRepository()
{
    return createCSCOrderIBTPickingdataRepository();
}

libcsc::base::IRunnablePtr CSCOrderComponentManager::saveCSCCallplanUC(short branchno, int customerno, int timeto)
{
	repo::CSCCallplanRepositoryPtr repository = repo::CSCCallplanRepositoryPtr(new repo::CSCCallplanRepository());
	repository->injectInsertAccessor(createAccessor());
	repository->injectUpdateAccessor(createAccessor());
	repository->injectFindAccessor(createAccessor());
	repository->injectTransactionFactory(shared_from_this());

	uc::SaveCSCCallplanUCPtr saveCSCCallplanUCPtr = boost::make_shared<uc::SaveCSCCallplanUC>(uc::SaveCSCCallplanUC());
	saveCSCCallplanUCPtr->injectRepository(repository);
	saveCSCCallplanUCPtr->setCallplan(branchno, customerno, timeto);

	return saveCSCCallplanUCPtr;
}

} // end namespace ibt
} // end namespace libcsc
