#include "orderdiscountcalcuc.h"
#include <discount/calculator/commands/idiscountcalculatorcommand.h>
#include <discount/orderpositiondiscount/iorderpositiondiscountrepository.h>
#include <discount/resultprocessor/irebateinkindrepository.h>
#include <discount/basevalues/discountbasevalue/idiscountbasevaluerepository.h>
#include <discount/logger/discountlogger/idiscountlogger.h>
#include <discount/basevalues/orderbasevalue/orderitembasevalue.h>
#include <discount/orderpositiondiscountprocessed/iorderpositiondiscountprocessedrepository.h>
#include <discount/basevalues/orderbasevalue/orderitembasevaluecollection.h>
#include <discount/orderpositiondiscountprocessed/orderpositiondiscountprocessed.h>
//#include <discount/orderpositiondiscountprocessed/orderpositiondiscountprocessedptr.h>
#include <discount/orderpositiondiscountprocessed/orderpositiondiscountprocessedcollection.h>
#include <logger/loggerpool.h>

namespace libcsc
{
namespace discount
{
OrderDiscountCalcUC::OrderDiscountCalcUC()
{
}

OrderDiscountCalcUC::~OrderDiscountCalcUC()
{
}

void OrderDiscountCalcUC::inject( IDiscountCalculatorCommandPtr calculator )
{
	m_Calculator = calculator;
}

void OrderDiscountCalcUC::inject( IOrderPositionDiscountRepositoryPtr orderPositionDiscountRepository )
{
	m_OrderPositionDiscountRepository = orderPositionDiscountRepository;
}

void OrderDiscountCalcUC::inject( IRebateInKindRepositoryPtr rebateInKindRepository )
{
	m_RebateInKindRepository = rebateInKindRepository;
}

void OrderDiscountCalcUC::inject( IDiscountBaseValueRepositoryPtr discountBaseValueRepository )
{
	m_DiscountBaseValueRepository = discountBaseValueRepository;
}

void OrderDiscountCalcUC::inject( IOrderBaseValueGetterPtr orderBaseValueGetter )
{
	m_OrderBaseValueGetter = orderBaseValueGetter;
}

void OrderDiscountCalcUC::inject( IDiscountLoggerPtr logger )
{
	m_Logger = logger;
}

void OrderDiscountCalcUC::inject( IOrderPositionDiscountProcessedRepositoryPtr orderPositionDiscountProcessedRepository )
{
	m_OrderPositionDiscountProcessedRepository = orderPositionDiscountProcessedRepository;
}

void OrderDiscountCalcUC::run()
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerDiscountCalc(), "OrderDiscountCalcUC::run()" );

	try
	{
		m_DiscountBaseValueRepository->findByOrder( m_OrderBaseValueGetter );
		m_OrderPositionDiscountRepository->findByID( m_OrderBaseValueGetter->getOrderNo() );

		OrderItemBaseValueCollectionPtr orderItemBaseValueCollection = m_OrderBaseValueGetter->getOrderItemBaseValueCollection();
		OrderItemBaseValueCollection::const_iterator iter = orderItemBaseValueCollection->begin();
		for( ; iter != orderItemBaseValueCollection->end(); ++iter )
		{
			m_OrderBaseValueGetter->setOrderItem( iter->second->getOrderItemPtr() );
			m_DiscountBaseValueRepository->findByArticle( m_OrderBaseValueGetter );
			m_Calculator->calculate();
			m_Calculator->processResult();
		}

		// TODO test
		m_RebateInKindRepository->save4ever();
		m_OrderPositionDiscountRepository->save();
		m_OrderPositionDiscountRepository->reset();		// necessary?

		markOrderPositionsProcessed();
		m_OrderPositionDiscountProcessedRepository->save();
		m_Logger->save();

		// TODO DK: preis in pxOrderItem setzen -> SetPreisEKApoNetto(nMoney price)
	}
	catch( const exceptions::CSCExceptionBase & e )
	{
		std::stringstream ss;
		ss << "OrderDiscountCalcUC::run(): Error during calculation: " << e.reason().c_str();
		BLOG_ERROR( LoggerPool::getLoggerDiscountCalc(), ss.str().c_str() );
	}
}

void OrderDiscountCalcUC::markOrderPositionsProcessed()
{
	OrderItemBaseValueCollection::const_iterator iter = m_OrderBaseValueGetter->getOrderItemBaseValueCollection()->begin();
	for( ; iter != m_OrderBaseValueGetter->getOrderItemBaseValueCollection()->end(); ++iter )
	{
		OrderItemBaseValuePtr orderItemBaseValue( iter->second );
		OrderPositionDiscountProcessedPtr orderPositionDiscountProcessed( new OrderPositionDiscountProcessed() );
		orderPositionDiscountProcessed->setOrderNo( orderItemBaseValue->getOrderNo() );
		orderPositionDiscountProcessed->setPositionNo( orderItemBaseValue->getPositionNo() );
		orderPositionDiscountProcessed->setProcessingTime( basar::DateTime::getCurrent() );
		m_OrderPositionDiscountProcessedRepository->get()->insert( orderItemBaseValue->getPositionNo(), orderPositionDiscountProcessed );
	}
}

} // end namespace discount
} // end namespace libcsc
