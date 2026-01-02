#include "workingdayscalendarcomponentmanager.h"

#include <workingdayscalendar/workingdayscalendarrepository.h>
#include <workingdayscalendar/workingdayscalendarrepositoryptr.h>

#include <persistence/accessor.h>
#include <persistence/connection.h>
#include <logger/loggerpool.h>
#include <boost/make_shared.hpp>

namespace libcsc {
namespace workingdayscalendar {

	WorkingdaysCalendarComponentManager::WorkingdaysCalendarComponentManager()
	{
		BLOG_TRACE_METHOD(LoggerPool::getLoggerInfrastructure(),
			"WorkingdaysCalendarComponentManager::ReturnComponentManagerWorkingdaysCalendarComponentManager()");
	}

	WorkingdaysCalendarComponentManager::~WorkingdaysCalendarComponentManager()
	{
		BLOG_TRACE_METHOD(LoggerPool::getLoggerInfrastructure(),
			"WorkingdaysCalendarComponentManager::~ReturnComponentManagerWorkingdaysCalendarComponentManager()");
	}

	void WorkingdaysCalendarComponentManager::injectConnection(persistence::ConnectionPtr connection)
	{
		BLOG_TRACE_METHOD(LoggerPool::getLoggerInfrastructure(), "WorkingdaysCalendarComponentManager::injectConnection()");

		m_Connection = connection;
	}

	void WorkingdaysCalendarComponentManager::injectTransactionHandler(nDataBase * transactionHandler)
	{
		BLOG_TRACE_METHOD(LoggerPool::getLoggerInfrastructure(), "WorkingdaysCalendarComponentManager::injectTransactionHandler()");

		m_TransactionHandler = transactionHandler;
	}

	libcsc::persistence::TransactionGuard WorkingdaysCalendarComponentManager::createTransaction() const
	{
		BLOG_TRACE_METHOD(LoggerPool::getLoggerInfrastructure(), "WorkingdaysCalendarComponentManager::createTransaction()");

		return persistence::TransactionGuard(m_TransactionHandler);
	}

	IWorkingdaysCalendarRepositoryPtr WorkingdaysCalendarComponentManager::getWorkingdaysCalendarRepository()
	{
		BLOG_TRACE_METHOD(LoggerPool::getLoggerInfrastructure(), "WorkingdaysCalendarComponentManager::getWorkingdaysCalendarRepository()");

		if (NULL == m_WorkingdaysCalendarRepository.get())
		{
			WorkingdaysCalendarRepositoryPtr workingdaysCalendarRepository = boost::make_shared<WorkingdaysCalendarRepository>();
			workingdaysCalendarRepository->injectWorkingdaysCalendarAccessor(createAccessor());

			m_WorkingdaysCalendarRepository = workingdaysCalendarRepository;
		}

		return m_WorkingdaysCalendarRepository;
	}

	persistence::IAccessorPtr WorkingdaysCalendarComponentManager::createAccessor()
	{
		BLOG_TRACE_METHOD(LoggerPool::getLoggerInfrastructure(), "WorkingdaysCalendarComponentManager::createAccessor()");

		return persistence::IAccessorPtr(new persistence::Accessor(m_Connection->getDbSqlConnection()));
	}

} // end namespace workingdayscalendar
} // end namespace libscsc
