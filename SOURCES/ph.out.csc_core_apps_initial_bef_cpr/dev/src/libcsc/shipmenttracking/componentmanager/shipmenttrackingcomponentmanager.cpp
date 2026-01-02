#include "shipmenttrackingcomponentmanager.h"
#include <shipmenttracking/shipmenttrackingrepository.h>
#include <util/loggingutils.h>
#include <boost/make_shared.hpp>
#include <parameter/branchparametergetter.h>


namespace libcsc {
namespace shipmenttracking {

ShipmentTrackingComponentManager::ShipmentTrackingComponentManager()
{
    BLOG_TRACE_METHODEX(LoggerPool::getLoggerShipmentTracking(), "ShipmentTrackingComponentManager::ShipmentTrackingComponentManager()" );
}

ShipmentTrackingComponentManager::~ShipmentTrackingComponentManager()
{
    BLOG_TRACE_METHODEX(LoggerPool::getLoggerShipmentTracking(), "ShipmentTrackingComponentManager::~ShipmentTrackingComponentManager()" );
}

void ShipmentTrackingComponentManager::injectTransactionHandler (nDataBase * transHandler)
{
    BLOG_TRACE_METHODEX(LoggerPool::getLoggerShipmentTracking(), "ShipmentTrackingComponentManager::injectTransactionHandler()" );

    m_TransactionHandler = transHandler;
}

void ShipmentTrackingComponentManager::injectBranchParameterGetter(parameter::IBranchParameterGetterPtr parameterGetter)
{
    m_BranchParameterGetter = parameterGetter;
}

libcsc::persistence::TransactionGuard ShipmentTrackingComponentManager::createTransaction() const
{
    BLOG_TRACE_METHODEX(LoggerPool::getLoggerShipmentTracking(), "ShipmentTrackingComponentManager::createTransaction()" );

    return persistence::TransactionGuard( m_TransactionHandler );
}

ShipmentTrackingRepositoryPtr ShipmentTrackingComponentManager::getShipmentTrackingRepository()
{
    BLOG_TRACE_METHODEX(LoggerPool::getLoggerShipmentTracking(), "ShipmentTrackingComponentManager::getShipmentTrackingRepository()");

    if (NULL == m_ShipmentTrackingRepository.get())
    {
        m_ShipmentTrackingRepository = boost::make_shared<ShipmentTrackingRepository>();
        m_ShipmentTrackingRepository->injectTransactionFactory(shared_from_this());
        m_ShipmentTrackingRepository->injectAccessorFactory(shared_from_this());
        m_ShipmentTrackingRepository->injectBranchParameterGetter(m_BranchParameterGetter);
    }

    return m_ShipmentTrackingRepository;
}


} // end namespace shipmenttracking
} // end namespace libcsc
