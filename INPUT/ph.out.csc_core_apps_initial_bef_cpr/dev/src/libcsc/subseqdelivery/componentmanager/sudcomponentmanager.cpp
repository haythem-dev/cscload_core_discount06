#include "sudcomponentmanager.h"

#include <subseqdelivery/workupcompletedchecker/workupcompletedchecker.h>
#include <subseqdelivery/workupcompletedchecker/workupcompletedcheckerptr.h>
#include <persistence/accessor.h>
#include <persistence/connection.h>
#include <logger/loggerpool.h>

namespace libcsc
{
namespace sud
{
SudComponentManager::SudComponentManager()
{
}

SudComponentManager::~SudComponentManager()
{
}

void SudComponentManager::injectConnection( persistence::ConnectionPtr connection )
{
	m_Connection = connection;
}

IWorkupCompletedCheckerPtr SudComponentManager::getWorkupCompletedChecker()
{
	WorkupCompletedCheckerPtr checker( new WorkupCompletedChecker() );
	checker->injectSelectAccessor( createAccessor() );
	return checker;
}

persistence::IAccessorPtr SudComponentManager::createAccessor()
{
	return persistence::IAccessorPtr( new persistence::Accessor( m_Connection->getDbSqlConnection() ) );
}

void SudComponentManager::injectTransactionHandler (nDataBase * transHandler)
{
	m_TransactionHandler = transHandler;
}

persistence::TransactionGuard SudComponentManager::createTransaction() const
{
    return persistence::TransactionGuard(m_TransactionHandler);
}

} // end namespace sud
} // end namespace libcsc
