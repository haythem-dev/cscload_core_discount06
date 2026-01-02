#include "customercomponentmanager.h"
#include <parameter/branchparametergetter.h>
#include <persistence/accessor.h>
#include <persistence/connection.h>

#include <customer/customerrepositoryptr.h>
#include <customer/customerrepository.h>

namespace libcsc {
namespace customer {

CustomerComponentManager::CustomerComponentManager()
{
}

CustomerComponentManager::~CustomerComponentManager()
{
}

void CustomerComponentManager::injectConnection(persistence::ConnectionPtr connection)
{
    m_Connection = connection;
}

persistence::IAccessorPtr CustomerComponentManager::createAccessor()
{
    return persistence::IAccessorPtr(new persistence::Accessor(m_Connection->getDbSqlConnection()));
}

void CustomerComponentManager::injectBranchParameterGetter(parameter::IBranchParameterGetterPtr parameterGetter)
{
    m_BranchParameterGetter = parameterGetter;
}

ICustomerRepositoryPtr CustomerComponentManager::createCustomerRepository()
{
    CustomerRepositoryPtr repository = CustomerRepositoryPtr(new CustomerRepository());
    repository->injectFindAccessor(createAccessor());
    repository->injectBranchParameterGetter(m_BranchParameterGetter);
    return repository;
}

ICustomerRepositoryPtr CustomerComponentManager::getCustomerRepository()
{
    return createCustomerRepository();
}

} // end namespace customer
} // end namespace libcsc
