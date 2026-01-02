#include "msv3componentmanager.h"
#include <msv3/orderresponse/orderresponserepository.h>
#include <msv3/transmissionresponse/transmissionresponserepository.h>
#include <msv3/customerdata/customerdatarepository.h>
#include <persistence/accessor.h>
#include <persistence/connection.h>
#include <logger/loggerpool.h>
#include <boost/make_shared.hpp>

namespace libcsc {
namespace msv3 {

MSV3ComponentManager::MSV3ComponentManager()
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerInfrastructure(), "MSV3ComponentManager::MSV3ComponentManager()" );
}

MSV3ComponentManager::~MSV3ComponentManager()
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerInfrastructure(), "MSV3ComponentManager::~MSV3ComponentManager()" );
}

void MSV3ComponentManager::injectConnection( persistence::ConnectionPtr connection )
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerInfrastructure(), "MSV3ComponentManager::injectConnection()" );

	m_Connection = connection;
}

libcsc::persistence::TransactionGuard MSV3ComponentManager::createTransaction() const
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerInfrastructure(), "MSV3ComponentManager::createTransaction()" );

	return persistence::TransactionGuard( m_TransactionHandler );
}

void MSV3ComponentManager::injectTransactionHandler (nDataBase * transHandler)
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerInfrastructure(), "MSV3ComponentManager::injectTransactionHandler()" );

	m_TransactionHandler = transHandler;
}

OrderResponseRepositoryPtr MSV3ComponentManager::getOrderResponseRepository()
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerInfrastructure(), "MSV3ComponentManager::getOrderResponseRepository()" );

	if (NULL == m_OrderResponseRepository.get())
	{
		m_OrderResponseRepository = boost::make_shared<OrderResponseRepository>();
		m_OrderResponseRepository->injectFindAccessor(createAccessor());
		m_OrderResponseRepository->injectInsertAccessor(createAccessor());
		m_OrderResponseRepository->injectUpdateAccessor(createAccessor());
	}
	return m_OrderResponseRepository;
}

TransmissionResponseRepositoryPtr MSV3ComponentManager::getTransmissionResponseRepository()
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerInfrastructure(), "MSV3ComponentManager::getTransmissionResponseRepository()" );

	if (NULL == m_TransmissionResponseRepository.get())
	{
		m_TransmissionResponseRepository = boost::make_shared<TransmissionResponseRepository>();
		m_TransmissionResponseRepository->injectFindAccessor(createAccessor());
		m_TransmissionResponseRepository->injectFindByInternalHashAccessor(createAccessor());
		m_TransmissionResponseRepository->injectInsertAccessor(createAccessor());
		m_TransmissionResponseRepository->injectUpdateAccessor(createAccessor());
	}
	return m_TransmissionResponseRepository;
}

CustomerDataRepositoryPtr MSV3ComponentManager::getCustomerDataRepository()
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerInfrastructure(), "MSV3ComponentManager::getCustomerDataRepository()" );

	if (NULL == m_CustomerDataRepository.get())
	{
		m_CustomerDataRepository = boost::make_shared<CustomerDataRepository>();
		m_CustomerDataRepository->injectFindAccessor(createAccessor());					
	}
	return m_CustomerDataRepository;
}

persistence::IAccessorPtr MSV3ComponentManager::createAccessor()
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerInfrastructure(), "MSV3ComponentManager::createAccessor()" );

	return persistence::IAccessorPtr( new persistence::Accessor( m_Connection->getDbSqlConnection() ) );
}

} // end namespace msv3
} // end namespace libcsc
