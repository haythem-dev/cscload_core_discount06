#include "ibtcomponentmanager.h"

#include <ibt/articlequotachecker/articlequotachecker.h>
#include <ibt/articlequotachecker/articlequotacheckerptr.h>

#include <ibt/bookingcompletedchecker/bookingcompletedchecker.h>
#include <ibt/bookingcompletedchecker/bookingcompletedcheckerptr.h>

#include <ibt/environmentchecker/environmentchecker.h>
#include <ibt/environmentchecker/environmentcheckerptr.h>

#include <ibt/transportexclusionchecker/transportexclusionchecker.h>
#include <ibt/transportexclusionchecker/transportexclusioncheckerptr.h>

#include <ibt/ibtrequest/ibtrequestrepositoryptr.h>
#include <ibt/ibtrequest/ibtrequestrepository.h>

#include <ibt/ibtresponse/ibtresponserepositoryptr.h>
#include <ibt/ibtresponse/ibtresponserepository.h>

#include <ibt/ibtbranch/ibtbranchrepositoryptr.h>
#include <ibt/ibtbranch/ibtbranchrepository.h>

#include <parameter/branchparametergetter.h>
#include <parameter/orderparametergetter.h>

#include <persistence/accessor.h>
#include <persistence/nullaccessor.h>
#include <persistence/connection.h>
#include <logger/loggerpool.h>
#include <boost/make_shared.hpp>

namespace libcsc
{
namespace ibt
{
IbtComponentManager::IbtComponentManager()
{
}

IbtComponentManager::~IbtComponentManager()
{
}

void IbtComponentManager::injectConnection( persistence::ConnectionPtr connection )
{
    m_Connection = connection;
}

void IbtComponentManager::injectTransactionHandler (nDataBase * transHandler)
{
    m_TransactionHandler = transHandler;
}

IArticleQuotaCheckerPtr IbtComponentManager::getArticleQuotaChecker()
{
    ArticleQuotaCheckerPtr checker( new ArticleQuotaChecker() );
    checker->injectSelectAccessor( createAccessor() );
    return checker;
}

IBookingCompletedCheckerPtr IbtComponentManager::getBookingCompletedChecker()
{
    BookingCompletedCheckerPtr checker( new BookingCompletedChecker() );
    checker->injectSelectAccessor( createAccessor() );
    return checker;
}

IEnvironmentCheckerPtr IbtComponentManager::getEnvironmentChecker()
{
    EnvironmentCheckerPtr checker( new EnvironmentChecker() );
    checker->injectSelectAccessor( createAccessor() );
    return checker;
}

ITransportExclusionCheckerPtr IbtComponentManager::getTransportExclusionChecker()
{
    TransportExclusionCheckerPtr checker( new TransportExclusionChecker() );
    checker->injectSelectAccessor( createAccessor() );
    return checker;
}

parameter::IOrderParameterGetterPtr IbtComponentManager::createOrderParameterGetter( const pxOrder * order )
{
	return parameter::IOrderParameterGetterPtr( new parameter::OrderParameterGetter( order ) );
}

persistence::IAccessorPtr IbtComponentManager::createAccessor( const pxOrder * order )
{
	if( createOrderParameterGetter( order )->isInfoOrder() )
	{
		return persistence::IAccessorPtr( new persistence::NullAccessor() );
	}

    return persistence::IAccessorPtr( new persistence::Accessor( m_Connection->getDbSqlConnection() ) );
}

persistence::IAccessorPtr IbtComponentManager::createAccessor()
{
    return persistence::IAccessorPtr( new persistence::Accessor( m_Connection->getDbSqlConnection() ) );
}

persistence::TransactionGuard IbtComponentManager::createTransaction() const
{
    return persistence::TransactionGuard(m_TransactionHandler);
}

ibt::IIbtRequestRepositoryPtr IbtComponentManager::createIbtRequestRepository()
{
    ibt::IbtRequestRepositoryPtr repository( new ibt::IbtRequestRepository() );

	repository->injectTransactionFactory( shared_from_this() );
	repository->injectAccessor( createAccessor() );
    return repository;
}

ibt::IIbtRequestRepositoryPtr IbtComponentManager::createIbtRequestRepository( const pxOrder * order )
{
    ibt::IbtRequestRepositoryPtr repository( new ibt::IbtRequestRepository() );

	repository->injectTransactionFactory( shared_from_this() );
	repository->injectAccessor( createAccessor( order ) );
    return repository;
}

ibt::IIbtResponseRepositoryPtr IbtComponentManager::createIbtResponseRepository()
{
	ibt::IbtResponseRepositoryPtr repository( new ibt::IbtResponseRepository() );
	repository->injectTransactionFactory( shared_from_this() );
	repository->injectAccessor( createAccessor() );
    return repository;
}

ibt::IIbtBranchRepositoryPtr IbtComponentManager::createIbtBranchRepository()
{
	ibt::IbtBranchRepositoryPtr repository(new ibt::IbtBranchRepository());
	repository->injectBranchSettingAccessor(createAccessor());
	return repository;
}

} // end namespace ibt
} // end namespace libcsc
