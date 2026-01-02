#include "returncomponentmanager.h"

#include <returns/returnrulebook/returnrulebookrepository.h>
#include <returns/returnrulebook/returnrulebookrepositoryptr.h>
#include <returns/returnannouncement/returnannouncementrepository.h>
#include <returns/returnannouncement/returnannouncementrepositoryptr.h>
#include <returns/returnperiod/returnperiodrepository.h>
#include <returns/returnperiod/returnperiodrepositoryptr.h>
#include <document/componentmanager/documentcomponentmanagerptr.h>
#include <document/componentmanager/documentcomponentmanager.h>
#include <workingdayscalendar/componentmanager/workingdayscalendarcomponentmanagerptr.h>
#include <workingdayscalendar/componentmanager/workingdayscalendarcomponentmanager.h>

#include <persistence/accessor.h>
#include <persistence/connection.h>
#include <logger/loggerpool.h>
#include <boost/make_shared.hpp>
#include "pxsess.hpp"
#include "pxparameter.hpp"

namespace libcsc {
namespace returns {

	ReturnComponentManager::ReturnComponentManager()
	{
		BLOG_TRACE_METHOD(LoggerPool::getLoggerInfrastructure(), "ReturnComponentManager::ReturnComponentManager()");
	}

	ReturnComponentManager::~ReturnComponentManager()
	{
		BLOG_TRACE_METHOD(LoggerPool::getLoggerInfrastructure(), "ReturnComponentManager::~ReturnComponentManager()");
	}

	void ReturnComponentManager::injectConnection(persistence::ConnectionPtr connection)
	{
		BLOG_TRACE_METHOD(LoggerPool::getLoggerInfrastructure(), "ReturnComponentManager::injectConnection()");

		m_Connection = connection;
	}

	void ReturnComponentManager::injectTransactionHandler(nDataBase * transactionHandler)
	{
		BLOG_TRACE_METHOD(LoggerPool::getLoggerInfrastructure(), "ReturnComponentManager::injectTransactionHandler()");

		m_TransactionHandler = transactionHandler;
	}

	void ReturnComponentManager::injectSession(pxSession* sess)
	{
		BLOG_TRACE_METHOD(LoggerPool::getLoggerInfrastructure(), "ReturnComponentManager::injectSession()");

		m_Session = sess;
	}

	libcsc::persistence::TransactionGuard ReturnComponentManager::createTransaction() const
	{
		BLOG_TRACE_METHOD(LoggerPool::getLoggerInfrastructure(), "ReturnComponentManager::createTransaction()");

		return persistence::TransactionGuard(m_TransactionHandler);
	}

	IReturnRuleBookRepositoryPtr ReturnComponentManager::getReturnRuleBookRepository()
	{
		BLOG_TRACE_METHOD(LoggerPool::getLoggerInfrastructure(), "ReturnComponentManager::getReturnRuleBookRepository()");

		if (NULL == m_ReturnRuleBookRepository.get())
		{
			ReturnRuleBookRepositoryPtr returnRuleBook = boost::make_shared<ReturnRuleBookRepository>();
			returnRuleBook->injectReturnRuleBookAccessor(createAccessor());

			m_ReturnRuleBookRepository = returnRuleBook;
		}

		return m_ReturnRuleBookRepository;
	}

	IReturnAnnouncementRepositoryPtr ReturnComponentManager::getReturnAnnouncementRepository()
	{
		BLOG_TRACE_METHOD(LoggerPool::getLoggerInfrastructure(), "ReturnComponentManager::getReturnAnnouncementRepository()");

		if (NULL == m_ReturnAnnouncementRepository.get())
		{
			ReturnAnnouncementRepositoryPtr repository = boost::make_shared<ReturnAnnouncementRepository>();
			repository->injectTransactionFactory(shared_from_this());
			repository->injectInsertAccessor(createAccessor());
			repository->injectUpdateAccessor(createAccessor());
			repository->injectReturnAnnouncementAccessor(createAccessor());
			repository->injectReturnAnnouncementHeadAccessor(createAccessor());
			repository->injectReturnAnnouncementPosAccessor(createAccessor());

			m_ReturnAnnouncementRepository = repository;
		}

		return m_ReturnAnnouncementRepository;
	}

	IReturnPeriodRepositoryPtr ReturnComponentManager::getReturnPeriodRepository()
	{
		BLOG_TRACE_METHOD(LoggerPool::getLoggerInfrastructure(), "ReturnComponentManager::getReturnPeriodRepository()");

		if (NULL == m_ReturnPeriodRepository.get())
		{
			ReturnPeriodRepositoryPtr repository = boost::make_shared<ReturnPeriodRepository>();
			repository->injectReturnPeriodAccessor(createAccessor());
			m_ReturnPeriodRepository = repository;
		}
		return m_ReturnPeriodRepository;
	}

	ReturnPositionCheckUCPtr ReturnComponentManager::getReturnPositionCheckUC()
	{
		if (NULL == m_ReturnPositionCheckUC.get())
		{
			m_ReturnPositionCheckUC = boost::make_shared<ReturnPositionCheckUC>();
			m_ReturnPositionCheckUC->injectSession(m_Session);
			m_ReturnPositionCheckUC->injectReturnRuleBookRepository(getReturnRuleBookRepository());
			m_ReturnPositionCheckUC->injectReturnPeriodRepository(getReturnPeriodRepository());
			m_ReturnPositionCheckUC->injectDeliveryAdviceRepository(m_Session->getDocumentComponentManager()->getDeliveryAdviceRepository());
			m_ReturnPositionCheckUC->injectWorkingdaysCalendarRepository(m_Session->getWorkingdaysCalendarComponentManager()->getWorkingdaysCalendarRepository());
			pxParameter parm(m_Session, 0, cPAR_KSC_GROUP, cPAR_KSC_PURPOSE_MSV3RETURNS, cPAR_KSC_PARAMNAME_HIGHPRICELIMIT);
			if (0 == parm.Get())
			{
				basar::Decimal highPriceLimit(static_cast<basar::Int32>(parm.Wert()));
				m_ReturnPositionCheckUC->injectHighPriceLimit(highPriceLimit);
			}
		}
		return m_ReturnPositionCheckUC;
	}

	persistence::IAccessorPtr ReturnComponentManager::createAccessor()
	{
		BLOG_TRACE_METHOD(LoggerPool::getLoggerInfrastructure(), "ReturnComponentManager::createAccessor()");

		return persistence::IAccessorPtr(new persistence::Accessor(m_Connection->getDbSqlConnection()));
	}

} //returns
} //libcsc
