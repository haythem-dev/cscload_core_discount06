#include "positiondiscountcalcuc.h"
#include <pxorder.hpp>
#include <pxitem.hpp>
#include <discount/calculator/commands/idiscountcalculatorcommand.h>
#include <discount/orderpositiondiscount/iorderpositiondiscountrepository.h>
#include <discount/orderpositiondiscount/orderpositiondiscount.h>
#include <discount/resultprocessor/irebateinkindrepository.h>
#include <discount/basevalues/discountbasevalue/idiscountbasevaluerepository.h>
#include <discount/logger/discountlogger/idiscountlogger.h>
#include <discount/basevalues/orderbasevalue/iorderbasevaluegetter.h>
#include <logger/loggerpool.h>

namespace libcsc
{
namespace discount
{
PositionDiscountCalcUC::PositionDiscountCalcUC()
{
}

PositionDiscountCalcUC::~PositionDiscountCalcUC()
{
}

void PositionDiscountCalcUC::inject( IDiscountCalculatorCommandPtr calculator )
{
	m_Calculator = calculator;
}

void PositionDiscountCalcUC::inject( IOrderPositionDiscountRepositoryPtr orderPositionDiscountRepository )
{
	m_OrderPositionDiscountRepository = orderPositionDiscountRepository;
}

void PositionDiscountCalcUC::inject( IRebateInKindRepositoryPtr rebateInKindRepository )
{
	m_RebateInKindRepository = rebateInKindRepository;
}

void PositionDiscountCalcUC::inject( IDiscountBaseValueRepositoryPtr discountBaseValueRepository )
{
	m_DiscountBaseValueRepository = discountBaseValueRepository;
}

void PositionDiscountCalcUC::inject( IOrderBaseValueGetterPtr orderBaseValueGetter )
{
	m_OrderBaseValueGetter = orderBaseValueGetter;
}

void PositionDiscountCalcUC::inject( IDiscountLoggerPtr logger )
{
	m_Logger = logger;
}

void PositionDiscountCalcUC::run()
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerDiscountCalc(), "PositionDiscountCalcUC::run()" );

	try
	{
		m_DiscountBaseValueRepository->findByArticle( m_OrderBaseValueGetter );
		m_Calculator->calculate();
		m_Calculator->processResult();
		m_RebateInKindRepository->save();
		m_OrderPositionDiscountRepository->save();
		m_Logger->save();
		
		//P-25000061 CSCService PA discount
		pxOrderItem* orderItem = m_OrderBaseValueGetter->getOrderItemPtr();
		if (orderItem != NULL)
		{
			pxOrder *order = orderItem->getOrder();
			if(orderItem->KdAuftragNr() == 9999999 && order->German() == true)
			{
				OrderPositionDiscountList::iterator iter = m_OrderPositionDiscountRepository->get()->begin();
				if (iter != m_OrderPositionDiscountRepository->get()->end())
				{
					basar::Decimal discountValue = basar::Decimal(0);
					if ((*iter)->getDiscountValue().get() > basar::Decimal(0))
						discountValue = (*iter)->getDiscountValue();
					if ((*iter)->getDiscountMode().get() == DM_SURCHARGE_EXF_MODE)
						discountValue = m_OrderBaseValueGetter->getExFactoryPrice() * (1 + ((*iter)->getDiscountPercent().get() / 100));
					if (discountValue > basar::Decimal(0))
					{
						orderItem->SetPreisFakturFixed(discountValue.toFloat64());
					}
				}
			}
		}
		// TODO DK: preis in pxOrderItem setzen -> SetPreisEKApoNetto(nMoney price)
	}
	catch( const exceptions::CSCExceptionBase & e )
	{
		std::stringstream ss;
		ss << "PositionDiscountCalcUC::run(): Error during calculation: " << e.reason().c_str();
		BLOG_ERROR( LoggerPool::getLoggerDiscountCalc(), ss.str().c_str() );
	}
}

} // end namespace discount
} // end namespace libcsc
