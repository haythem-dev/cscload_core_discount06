#include "discountcomponentmanager.h"
#include "hrorderdiscountcalculatorcomponentmanager.h"
#include "hrpositiondiscountcalculatorcomponentmanager.h"

#include <discount/basevalues/discountbasevalue/discountbasevaluerepository.h>
#include <discount/basevalues/discountbasevalue/discountbasevaluecollection.h>
#include <discount/basevalues/orderbasevalue/orderitembasevalueptr.h>
#include <discount/basevalues/orderbasevalue/orderitembasevalue.h>
#include <discount/calculator/commands/dediscountcalculatorcommand.h>
#include <discount/calculator/commands/idiscountfilter.h>
#include <discount/calculator/commands/discountordertypefilter.h>
#include <discount/calculator/commands/discountcustomerordertypepermissionfilter.h>
#include <discount/calculator/commands/discountcustomerrxafilter.h>
#include <discount/calculator/commands/discounttaxspannencheckfilter.h>
#include <discount/calculator/commands/discountpriorityfilter.h>
#include <discount/calculator/commands/discountbestpricefilter.h>
#include <discount/calculator/commands/discountvisibilityfilter.h>
#include <discount/discountcollectionfinder/discountcollectionfinder.h>
#include <discount/discountcollectionfinder/discountcollectionfinderptr.h>
#include <discount/logger/discountlogger/nulldiscountlogger.h>
#include <discount/logger/discountlogger/log4cplusdiscountlogger.h>
#include <discount/orderpositiondiscount/orderpositiondiscountrepository.h>
#include <discount/orderpositiondiscountprocessed/orderpositiondiscountprocessedrepository.h>
#include <discount/tender/repository/tenderdiscountrepository.h>
#include <discount/usecase/positiondiscountcalcuc.h>
#include <discount/usecase/orderdiscountcalcuc.h>
#include <discount/usecase/nulldiscountcalcuc.h>

#include <persistence/accessor.h>
#include <persistence/connection.h>

#include <logger/loggerpool.h>

#include <parameter/isessionparametergetter.h>

#include <boost/make_shared.hpp>
#include <vector>

namespace libcsc
{
namespace discount
{
DiscountComponentManager::DiscountComponentManager()
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerInfrastructure(), "DiscountComponentManager::DiscountComponentManager()" );
}

DiscountComponentManager::~DiscountComponentManager()
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerInfrastructure(), "DiscountComponentManager::~DiscountComponentManager()" );
}

void DiscountComponentManager::injectConnection( persistence::ConnectionPtr connection )
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerInfrastructure(), "DiscountComponentManager::injectConnection()" );

	m_Connection = connection;
}

void DiscountComponentManager::injectParameterGetter( parameter::ISessionParameterGetterPtr parameterGetter )
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerInfrastructure(), "DiscountComponentManager::injectParameterGetter()" );

	m_SessionParameterGetter = parameterGetter;
}

libcsc::persistence::TransactionGuard DiscountComponentManager::createTransaction() const
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerInfrastructure(), "DiscountComponentManager::createTransaction()" );

	return persistence::TransactionGuard( m_TransactionHandler );
}

void DiscountComponentManager::injectTransactionHandler (nDataBase * transHandler)
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerInfrastructure(), "DiscountComponentManager::injectTransactionHandler()" );

	m_TransactionHandler = transHandler;
}

base::IRunnablePtr DiscountComponentManager::getPositionDiscountCalcUC( pxOrderItem * orderItem )
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerInfrastructure(), "DiscountComponentManager::getPositionDiscountCalcUC()" );

	OrderPositionDiscountRepositoryPtr orderPositionDiscountRepository( createOrderPositionDiscountRepository() );
	DiscountBaseValueRepositoryPtr discountBaseValueRepository( createDiscountBaseValueRepository() );

	OrderItemBaseValuePtr orderBaseValueGetter( new OrderItemBaseValue( orderItem ) );
	orderBaseValueGetter->injectArticleClassificationRepository( createArticleClassificationRepository() );
	orderBaseValueGetter->injectOrderPositionDiscountProcessedRepository( createPositionDiscountProcessedRepository() );

	IDiscountLoggerPtr discountLogger( createDiscountLogger() );

	RepositoryResultProcessorPtr repositoryResultProcessor( createRepositoryResultProcessor( orderPositionDiscountRepository ) );
	RebateInKindResultProcessorPtr rebateInKindResultProcessor( createRebateInKindResultProcessor( orderPositionDiscountRepository ) );

	CompositeResultProcessorPtr resultProcessor( createCompositeResultProcessor() );
	resultProcessor->add( repositoryResultProcessor );
	resultProcessor->add( rebateInKindResultProcessor );

	IDiscountCalculatorCommandPtr calculator;
	if( m_SessionParameterGetter->isCountryHR())
	{
		HRPositionDiscountCalculatorComponentManager cm;
		cm.inject( discountBaseValueRepository->get() );
		cm.inject( orderBaseValueGetter );
		cm.inject( discountLogger );
		cm.inject( resultProcessor );
		calculator = cm.getDiscountCalculator();
	}
	else if (m_SessionParameterGetter->isCountryDE())
	{
		boost::shared_ptr<DEDiscountCalculatorCommand> deCalculator = boost::make_shared<DEDiscountCalculatorCommand>();

		deCalculator->inject(discountBaseValueRepository->get());
		deCalculator->inject(orderBaseValueGetter);
		deCalculator->inject(resultProcessor);

		//NOTE: the order of filters is important.
		DiscountFilterList filters;
		filters.push_back(boost::make_shared < DiscountOrderTypeFilter >());
		filters.push_back(boost::make_shared < DiscountCustomerOrderTypePermissionFilter >());
		filters.push_back(boost::make_shared < DiscountCustomerRXAFilter>());
		filters.push_back(boost::make_shared < DiscountTaxSpannenCheckFilter >(m_SessionParameterGetter->getTaxSpannenFestBetrag()));
		filters.push_back(boost::make_shared < DiscountPriorityFilter >());
		filters.push_back(boost::make_shared < DiscountBestPriceFilter >());
		deCalculator->injectFilters( filters );

		calculator = deCalculator;
	}

	PositionDiscountCalcUCPtr calcUC( new PositionDiscountCalcUC() );
	calcUC->inject( orderPositionDiscountRepository );
	calcUC->inject( rebateInKindResultProcessor );
	calcUC->inject( discountBaseValueRepository );
	calcUC->inject( calculator );
	calcUC->inject( orderBaseValueGetter );
	calcUC->inject( discountLogger );

	return calcUC;
}

base::IRunnablePtr DiscountComponentManager::getOrderDiscountCalcUC( pxOrder * order )
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerInfrastructure(), "DiscountComponentManager::getOrderDiscountCalcUC()" );

	if (m_SessionParameterGetter->isCountryDE())  // DEPricing
	{
		NullDiscountCalcUCPtr calcUC(new NullDiscountCalcUC());
		return calcUC;
	}

	OrderPositionDiscountRepositoryPtr orderPositionDiscountRepository( createOrderPositionDiscountRepository() );
	//orderPositionDiscountRepository->setDeleteOldEntries( true );
	DiscountBaseValueRepositoryPtr discountBaseValueRepository( createDiscountBaseValueRepository() );
	OrderPositionDiscountProcessedRepositoryPtr orderPositionDiscountProcessedRepository( createPositionDiscountProcessedRepository() );

	OrderItemBaseValuePtr orderBaseValueGetter( new OrderItemBaseValue( order ) );
	orderBaseValueGetter->injectArticleClassificationRepository( createArticleClassificationRepository() );
	orderBaseValueGetter->injectOrderPositionDiscountProcessedRepository( orderPositionDiscountProcessedRepository );

	IDiscountLoggerPtr discountLogger( createDiscountLogger() );

	RepositoryResultProcessorPtr repositoryResultProcessor( createRepositoryResultProcessor( orderPositionDiscountRepository ) );
	RebateInKindResultProcessorPtr rebateInKindResultProcessor( createRebateInKindResultProcessor( orderPositionDiscountRepository ) );

	CompositeResultProcessorPtr resultProcessor( createCompositeResultProcessor() );
	resultProcessor->add( repositoryResultProcessor );
	resultProcessor->add( rebateInKindResultProcessor );

	IDiscountCalculatorCommandPtr calculator;
	if( m_SessionParameterGetter->isCountryHR())
	{
		HROrderDiscountCalculatorComponentManager cm;
		cm.inject( discountBaseValueRepository->get() );
		cm.inject( orderBaseValueGetter );
		cm.inject( discountLogger );
		cm.inject( resultProcessor );
		calculator = cm.getDiscountCalculator();
	}

	OrderDiscountCalcUCPtr calcUC( new OrderDiscountCalcUC() );
	calcUC->inject( orderPositionDiscountRepository );
	calcUC->inject( rebateInKindResultProcessor );
	calcUC->inject( discountBaseValueRepository );
	calcUC->inject( calculator );
	calcUC->inject( orderBaseValueGetter );
	calcUC->inject( discountLogger );
	calcUC->inject( orderPositionDiscountProcessedRepository );

	return calcUC;
}

DiscountBaseValueRepositoryPtr DiscountComponentManager::createDiscountBaseValueRepository()
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerInfrastructure(), "DiscountComponentManager::createDiscountBaseValueRepository()" );

	DiscountBaseValueRepositoryPtr repository( new DiscountBaseValueRepository() );
	repository->injectSingleSelectAccessor( createAccessor() );
	repository->injectMultiSelectAccessor( createAccessor() );

	if (m_SessionParameterGetter->isCountryDE())
	{
		repository->setIsGermany();
	}

	return repository;
}

libcsc::discount::IDiscountCollectionFinderPtr DiscountComponentManager::createDiscountCollectionFinder()
{
    BLOG_TRACE_METHOD(LoggerPool::getLoggerInfrastructure(), "DiscountComponentManager::createDiscountCollectionFinder()");

    libcsc::discount::DiscountCollectionFinderPtr discountCollectionFinder( boost::make_shared< DiscountCollectionFinder >() );
    discountCollectionFinder->injectDiscountBaseValueRepository( createDiscountBaseValueRepository() );

	if (m_SessionParameterGetter->isCountryDE())
	{
		//NOTE: the order of filters is important.
		DiscountFilterList filters;
		filters.push_back(boost::make_shared < DiscountOrderTypeFilter >());
		filters.push_back(boost::make_shared < DiscountCustomerOrderTypePermissionFilter >());
		filters.push_back(boost::make_shared < DiscountCustomerRXAFilter>());
		filters.push_back(boost::make_shared < DiscountTaxSpannenCheckFilter >(m_SessionParameterGetter->getTaxSpannenFestBetrag()));
		filters.push_back(boost::make_shared < DiscountPriorityFilter >());
		filters.push_back(boost::make_shared < DiscountVisibilityFilter >());
		discountCollectionFinder->injectFilters(filters);
	}
    return discountCollectionFinder;
}

OrderPositionDiscountRepositoryPtr DiscountComponentManager::createOrderPositionDiscountRepository()
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerInfrastructure(), "DiscountComponentManager::createOrderPositionDiscountRepository()" );

	OrderPositionDiscountRepositoryPtr repository( new OrderPositionDiscountRepository() );
	repository->injectSingleArticleSelectAccessor( createAccessor() );
	repository->injectRebateInKindEntrySelectAccessor( createAccessor() );
	repository->injectOrderCompletionSelectAccessor( createAccessor() );
	repository->injectInsertAccessor( createAccessor() );
	repository->injectUpdateAccessor( createAccessor() );
	repository->injectDeleteAccessor( createAccessor() );
	repository->injectTransactionFactory( shared_from_this() );

	return repository;
}

TenderDiscountRepositoryPtr DiscountComponentManager::createTenderDiscountRepository()
{
    BLOG_TRACE_METHOD( LoggerPool::getLoggerInfrastructure(), "DiscountComponentManager::createTenderDiscountRepository()" );

    TenderDiscountRepositoryPtr repository( new TenderDiscountRepository() );
    repository->injectSelectAccessor( createAccessor() );
    return repository;

}

OrderPositionDiscountProcessedRepositoryPtr DiscountComponentManager::createPositionDiscountProcessedRepository()
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerInfrastructure(), "DiscountComponentManager::createPositionDiscountProcessedRepository()" );

	OrderPositionDiscountProcessedRepositoryPtr repository( new OrderPositionDiscountProcessedRepository() );
	repository->injectSelectAccessor( createAccessor() );
	repository->injectInsertAccessor( createAccessor() );
	repository->injectTransactionFactory( shared_from_this() );

	return repository;
}

ArticleClassificationRepositoryPtr DiscountComponentManager::createArticleClassificationRepository()
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerInfrastructure(), "DiscountComponentManager::createArticleClassificationRepository()" );

	ArticleClassificationRepositoryPtr repository( new ArticleClassificationRepository() );
	repository->injectSelectAccessor( createAccessor() );

	return repository;
}


CompositeResultProcessorPtr DiscountComponentManager::createCompositeResultProcessor()
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerInfrastructure(), "DiscountComponentManager::createCompositeResultProcessor()" );

	CompositeResultProcessorPtr compositeResultProcessor( new CompositeResultProcessor() );

	return compositeResultProcessor;
}

RebateInKindResultProcessorPtr DiscountComponentManager::createRebateInKindResultProcessor( OrderPositionDiscountRepositoryPtr orderPositionDiscountRepository )
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerInfrastructure(), "DiscountComponentManager::createRebateInKindResultProcessor()" );

	RebateInKindResultProcessorPtr rebateInKindResultProcessor( new RebateInKindResultProcessor() );
	rebateInKindResultProcessor->inject( orderPositionDiscountRepository );	

	return rebateInKindResultProcessor;
}

RepositoryResultProcessorPtr DiscountComponentManager::createRepositoryResultProcessor( OrderPositionDiscountRepositoryPtr orderPositionDiscountRepository )
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerInfrastructure(), "DiscountComponentManager::createRepositoryResultProcessor()" );

	RepositoryResultProcessorPtr resultProcessor( new RepositoryResultProcessor() );
	resultProcessor->inject( orderPositionDiscountRepository );

	return resultProcessor;
}

IDiscountLoggerPtr DiscountComponentManager::createDiscountLogger()
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerInfrastructure(), "DiscountComponentManager::createDiscountLogger()" );

	// TODO: depending on proforma-order Log4CplusDiscountLogger or RepositoryDiscountLogger
	return Log4CplusDiscountLoggerPtr( new Log4CplusDiscountLogger() );
}

persistence::IAccessorPtr DiscountComponentManager::createAccessor()
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerInfrastructure(), "DiscountComponentManager::createAccessor()" );

	return persistence::IAccessorPtr( new persistence::Accessor( m_Connection->getDbSqlConnection() ) );
}

} // end namespace discount
} // end namespace libcsc
