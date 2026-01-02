#include "documentcomponentmanager.h"
#include <document/documentarchiveinfo/documentarchiveinforepository.h>
#include <document/narcoticarchive/narcoticarchiverepository.h>
#include <document/deliveryadvice/deliveryadvicerepository.h>
#include <document/documentprintinfo/documentprintinforepository.h>
#include <document/taxrates/taxratesrepository.h>
#include <persistence/accessor.h>
#include <persistence/connection.h>
#include <logger/loggerpool.h>
#include <boost/make_shared.hpp>
#include <parameter/branchparametergetter.h>


namespace libcsc {
namespace document {

DocumentComponentManager::DocumentComponentManager()
{
    BLOG_TRACE_METHOD( LoggerPool::getLoggerInfrastructure(), "DocumentComponentManager::DocumentComponentManager()" );
}

DocumentComponentManager::~DocumentComponentManager()
{
    BLOG_TRACE_METHOD( LoggerPool::getLoggerInfrastructure(), "DocumentComponentManager::~DocumentComponentManager()" );
}

void DocumentComponentManager::injectConnection( persistence::ConnectionPtr connection )
{
    BLOG_TRACE_METHOD( LoggerPool::getLoggerInfrastructure(), "DocumentComponentManager::injectConnection()" );

    m_Connection = connection;
}

void DocumentComponentManager::injectTransactionHandler (nDataBase * transHandler)
{
    BLOG_TRACE_METHOD( LoggerPool::getLoggerInfrastructure(), "DocumentComponentManager::injectTransactionHandler()" );

    m_TransactionHandler = transHandler;
}

void DocumentComponentManager::injectBranchParameterGetter(parameter::IBranchParameterGetterPtr parameterGetter)
{
    m_BranchParameterGetter = parameterGetter;
}

libcsc::persistence::TransactionGuard DocumentComponentManager::createTransaction() const
{
    BLOG_TRACE_METHOD( LoggerPool::getLoggerInfrastructure(), "DocumentComponentManager::createTransaction()" );

    return persistence::TransactionGuard( m_TransactionHandler );
}

DocumentArchiveInfoRepositoryPtr DocumentComponentManager::getDocumentArchiveInfoRepository()
{
    BLOG_TRACE_METHOD(LoggerPool::getLoggerInfrastructure(), "DocumentComponentManager::getDocumentArchiveInfoRepository()");

    if (NULL == m_DocumentArchiveInfoRepository.get())
    {
        m_DocumentArchiveInfoRepository = boost::make_shared<DocumentArchiveInfoRepository>();
        m_DocumentArchiveInfoRepository->injectFindAccessor(createAccessor());
        m_DocumentArchiveInfoRepository->injectFindbyGuidAccessor(createAccessor());
        m_DocumentArchiveInfoRepository->injectInsertAccessor(createAccessor());
        m_DocumentArchiveInfoRepository->injectUpdateAccessor(createAccessor());
        m_DocumentArchiveInfoRepository->injectTransactionFactory(shared_from_this());
        m_DocumentArchiveInfoRepository->injectBranchParameterGetter(m_BranchParameterGetter);
    }
    return m_DocumentArchiveInfoRepository;
}

NarcoticArchiveRepositoryPtr DocumentComponentManager::getNarcoticArchiveRepository()
{
    BLOG_TRACE_METHOD(LoggerPool::getLoggerInfrastructure(), "DocumentComponentManager::getNarchoticArchiveRepository()");

    if (NULL == m_NarcoticArchiveRepository.get())
    {
        m_NarcoticArchiveRepository = boost::make_shared<NarcoticArchiveRepository>();
        m_NarcoticArchiveRepository->injectFindAccessor(createAccessor());
        m_NarcoticArchiveRepository->injectFindByContributionVoucherNoAccessor(createAccessor());
        m_NarcoticArchiveRepository->injectInsertAccessor(createAccessor());
        m_NarcoticArchiveRepository->injectUpdateAccessor(createAccessor());
        m_NarcoticArchiveRepository->injectTransactionFactory(shared_from_this());
        m_NarcoticArchiveRepository->injectBranchParameterGetter(m_BranchParameterGetter);
    }
    return m_NarcoticArchiveRepository;
}

DeliveryAdviceRepositoryPtr DocumentComponentManager::getDeliveryAdviceRepository()
{
    BLOG_TRACE_METHOD(LoggerPool::getLoggerInfrastructure(), "DocumentComponentManager::getDeliveryAdviceRepository()");

    if (NULL == m_DeliveryAdviceRepository.get())
    {
        m_DeliveryAdviceRepository = boost::make_shared<DeliveryAdviceRepository>();
        m_DeliveryAdviceRepository->injectSelectDeliveryAdviceHeadAccessor(createAccessor());
        m_DeliveryAdviceRepository->injectSelectDeliveryAdviceVatTotalsAccessor(createAccessor());
        m_DeliveryAdviceRepository->injectSelectDeliveryAdviceLinesAccessor(createAccessor());
        m_DeliveryAdviceRepository->injectSelectDeliveryAdviceLineSingleAccessor(createAccessor());
        m_DeliveryAdviceRepository->injectSelectDeliveryAdviceLineRemarksAccessor(createAccessor());
        m_DeliveryAdviceRepository->injectSelectDeliveryAdviceLineDiscountAccessor(createAccessor());
        m_DeliveryAdviceRepository->injectSelectDeliveryAdviceLineDetailsAccessor(createAccessor());
        m_DeliveryAdviceRepository->injectSelectDeliveryAdviceLineReturnAccessor(createAccessor());
        m_DeliveryAdviceRepository->injectSelectDeliveryAdviceLineIbtLinkAccessor(createAccessor());
        m_DeliveryAdviceRepository->injectSelectDnNumbersByReferencesAccessor(createAccessor());

        m_DeliveryAdviceRepository->injectSelectCustomerOrdersAccessor(createAccessor());
        m_DeliveryAdviceRepository->injectSelectCustomerOrderDetailsAccessor(createAccessor());

        m_DeliveryAdviceRepository->injectSelectDeliveryAdviceDetailsAccessor(createAccessor());

        m_DeliveryAdviceRepository->injectSelectDeliveryAdviceLineDetailsAccessor(createAccessor());
        m_DeliveryAdviceRepository->injectInsertDeliveryAdviceLineIbtLinkAccessor(createAccessor());
        m_DeliveryAdviceRepository->injectSelectDeliveryAdviceLineExtrasATAccessor(createAccessor());
        m_DeliveryAdviceRepository->injectUpdateDeliveryAdviceHeadAccessor(createAccessor());
        m_DeliveryAdviceRepository->injectTransactionFactory(shared_from_this());
        m_DeliveryAdviceRepository->injectBranchParameterGetter(m_BranchParameterGetter);
    }
    return m_DeliveryAdviceRepository;
}

DocumentPrintInfoRepositoryPtr DocumentComponentManager::getDocumentPrintInfoRepository()
{
    BLOG_TRACE_METHOD(LoggerPool::getLoggerInfrastructure(), "DocumentComponentManager::getDocumentPrintInfoRepository()");

    if (NULL == m_DocumentPrintInfoRepository.get())
    {
        m_DocumentPrintInfoRepository = boost::make_shared<DocumentPrintInfoRepository>();
        m_DocumentPrintInfoRepository->injectInsertAccessor(createAccessor());
        m_DocumentPrintInfoRepository->injectFindAccessor(createAccessor());
        m_DocumentPrintInfoRepository->injectTransactionFactory(shared_from_this());
        m_DocumentPrintInfoRepository->injectBranchParameterGetter(m_BranchParameterGetter);
    }
    return m_DocumentPrintInfoRepository;
}

TaxratesRepositoryPtr DocumentComponentManager::getTaxratesRepository()
{
    BLOG_TRACE_METHOD(LoggerPool::getLoggerInfrastructure(), "DocumentComponentManager::getTaxratesRepository()");

    if (m_TaxratesRepository.get() == NULL)
    {
        m_TaxratesRepository = boost::make_shared<TaxratesRepository>();
        m_TaxratesRepository->injectFindAccessor(createAccessor());
    }
    return m_TaxratesRepository;
}

persistence::IAccessorPtr DocumentComponentManager::createAccessor()
{
    BLOG_TRACE_METHOD( LoggerPool::getLoggerInfrastructure(), "DocumentComponentManager::createAccessor()" );
    return persistence::IAccessorPtr( new persistence::Accessor( m_Connection->getDbSqlConnection() ) );
}

} // end namespace document
} // end namespace libcsc
