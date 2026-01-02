#include "discount/resultprocessor/repositoryresultprocessor.h"
#include "discount/orderpositiondiscount/iorderpositiondiscountrepository.h"
#include "discount/basevalues/orderbasevalue/iorderbasevaluegetter.h"
#include <logger/loggerpool.h>
#include <discount/calculator/discountcalculatortypemapper.h>
#include <pxorder.hpp>

namespace libcsc
{
namespace discount
{
RepositoryResultProcessor::RepositoryResultProcessor()
{
}

RepositoryResultProcessor::~RepositoryResultProcessor()
{
}

void RepositoryResultProcessor::inject( IOrderPositionDiscountRepositoryPtr repository )
{
	m_Repository = repository;
}

void RepositoryResultProcessor::process( 
	const DiscountCalculatorTypeEnum calcType, 
	const IOrderBaseValueGetterPtr baseValueGetter, 
	const DiscountCalculatorResult & calcResult 
		)
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerDiscountCalc(), "RepositoryResultProcessor::process()" );

	if( LoggerPool::getLoggerDiscountCalc().isEnabledFor( log4cplus::TRACE_LOG_LEVEL ) )
	{
		std::stringstream ss;
		ss << "CalculatorType: ";
		DiscountCalculatorTypeMapper::toStream( ss, calcType );
		ss << ", CalculatorResult: ";
		if( calcResult.isUnset() )
		{
			ss << "<UNSET>";
		}
		else
		{
			ss << calcResult;
		}
		LoggerPool::getLoggerDiscountCalc().forcedLog( log4cplus::TRACE_LOG_LEVEL, ss.str().c_str(), __FILE__, __LINE__ );

		ss.str( "" );
		ss << "baseValueGetter->getOrderPtr()->getNumberOfPositions(): " << baseValueGetter->getOrderPtr()->getNumberOfPositions();
		LoggerPool::getLoggerDiscountCalc().forcedLog( log4cplus::TRACE_LOG_LEVEL, ss.str().c_str(), __FILE__, __LINE__ );
	}

	if( calcResult.isUnset() )
	{
		BLOG_TRACE( LoggerPool::getLoggerDiscountCalc(), "Result is unset, skipping this result" );
		return;
	}

	processDiscount( calcType, baseValueGetter, calcResult );
}

void RepositoryResultProcessor::processDiscount( 
	const DiscountCalculatorTypeEnum calcType, 
	const IOrderBaseValueGetterPtr baseValueGetter, 
	const DiscountCalculatorResult & calcResult 
		)
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerDiscountCalc(), "RepositoryResultProcessor::processDiscount()" );
	
	DiscountResultCollection::const_iterator iter = calcResult.results.begin();
	for( ; iter != calcResult.results.end(); ++iter )
	{
		const basar::Int32 positionNo( iter->first );
		if( positionNo != baseValueGetter->getPositionNo() )
		{
			continue;
		}

		const DiscountResult & discountResult( iter->second );
		if( discountResult.containsDirty() )
		{
			if( LoggerPool::getLoggerDiscountCalc().isEnabledFor( log4cplus::TRACE_LOG_LEVEL ) )
			{
				std::stringstream ss;
				ss << "CalculatorType: ";
				DiscountCalculatorTypeMapper::toStream( ss, calcType );
				ss << ", positionNo = <" << positionNo << ">, discountResult=" << std::endl << discountResult;
				LoggerPool::getLoggerDiscountCalc().forcedLog( log4cplus::TRACE_LOG_LEVEL, ss.str().c_str(), __FILE__, __LINE__ );
			}

			OrderPositionDiscountPtr orderPositionDiscount = m_Repository->getOrderPositionDiscount( positionNo, getDiscountMode( calcType, false ) );

			// TODO: for debugging only - remove
			if( LoggerPool::getLoggerDiscountCalc().isEnabledFor( log4cplus::TRACE_LOG_LEVEL ) )
			{
				std::stringstream ss;
				ss << "OrderPositionDiscount before: " << ( *orderPositionDiscount ) << std::endl;
				LoggerPool::getLoggerDiscountCalc().forcedLog( log4cplus::TRACE_LOG_LEVEL, ss.str().c_str(), __FILE__, __LINE__ );
			}

			if( 0 < compareDiscountValues( *orderPositionDiscount, discountResult, baseValueGetter ) )
			{
				// new discount has a smaller value, so skip it
				BLOG_TRACE( LoggerPool::getLoggerDiscountCalc(), "Skipping DiscountResult" );
				if( 0 == orderPositionDiscount->getOrderNo() )
				{
					m_Repository->erase( orderPositionDiscount );
				}
				continue;
			}

			orderPositionDiscount->setOrderNo( baseValueGetter->getOrderNo() );

			if( discountResult.discountValue.isDirty() )
			{
				orderPositionDiscount->setDiscountValue( discountResult.discountValue );
			}
			else if( discountResult.discountedArticlePrice.isDirty() )
			{
				orderPositionDiscount->setDiscountValue( discountResult.discountedArticlePrice );
			}
			else
			{
				orderPositionDiscount->setDiscountValue( libcsc::Decimal::zero() );
			}

			orderPositionDiscount->setDiscountPercent( discountResult.discountPercent.isDirty() ? discountResult.discountPercent : libcsc::Decimal::zero() );
			orderPositionDiscount->setDiscountQty( 0 );
			orderPositionDiscount->setPharmacyGroupId(discountResult.source.pharmacyGroup);
			
			// TODO: for debugging only - remove
			if( LoggerPool::getLoggerDiscountCalc().isEnabledFor( log4cplus::TRACE_LOG_LEVEL ) )
			{
				std::stringstream ss;
				ss << "OrderPositionDiscount after: " << ( *orderPositionDiscount ) << std::endl;
				LoggerPool::getLoggerDiscountCalc().forcedLog( log4cplus::TRACE_LOG_LEVEL, ss.str().c_str(), __FILE__, __LINE__ );
			}
			if (discountResult.source.promotionNo > 0)
			{
				baseValueGetter->getOrderItemPtr()->SetPromotionNo(discountResult.source.promotionNo);
			}
			basar::VarString promotionName = discountResult.source.promotionName;
			if (false == promotionName.empty())
			{
				baseValueGetter->getOrderItemPtr()->setPromotionName(promotionName);
			}
		}
	}
}

basar::Int32 RepositoryResultProcessor::compareDiscountValues(
	const OrderPositionDiscount & orderPositionDiscount,
	const DiscountResult & discountResult,
	const IOrderBaseValueGetterPtr baseValueGetter
		) const
{
	basar::Decimal lhs( getDiscountValue( orderPositionDiscount, baseValueGetter ) );
	basar::Decimal rhs( getDiscountValue( discountResult, baseValueGetter ) );

	if( false == orderPositionDiscount.isDiscountValid() || lhs < rhs )
	{
		return -1;
	}
	else if( lhs > rhs )
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

const basar::Decimal RepositoryResultProcessor::getDiscountValue(
	const OrderPositionDiscount & orderPositionDiscount,
	const IOrderBaseValueGetterPtr baseValueGetter
		) const
{
	basar::Decimal value;

	if(    orderPositionDiscount.getDiscountValue().isClean()
		|| orderPositionDiscount.getDiscountValue().isDirty() )
	{
		if( DM_FIXED_PRICE_MODE == orderPositionDiscount.getDiscountMode() )
		{
			value = ( baseValueGetter->getItemPrice() - orderPositionDiscount.getDiscountValue() ) * baseValueGetter->getItemQty();
		}
		else
		{
			value = basar::Decimal( orderPositionDiscount.getDiscountValue() ) * baseValueGetter->getItemQty();
		}
	}
	if(    orderPositionDiscount.getDiscountPercent().isClean()
		|| orderPositionDiscount.getDiscountPercent().isDirty() )
	{
		value += ( baseValueGetter->getItemPrice() * orderPositionDiscount.getDiscountPercent() / basar::Decimal( 100 ) * baseValueGetter->getItemQty() );
	}

	return value;
}

const basar::Decimal RepositoryResultProcessor::getDiscountValue(
	const DiscountResult & discountResult,
	const IOrderBaseValueGetterPtr baseValueGetter
		) const
{
	basar::Decimal value;

	if( discountResult.discountValue.isDirty() )
	{
		value = basar::Decimal( discountResult.discountValue ) * baseValueGetter->getItemQty();
	}
	if( discountResult.discountedArticlePrice.isDirty() )
	{
		value += ( ( baseValueGetter->getItemPrice() - discountResult.discountedArticlePrice ) * baseValueGetter->getItemQty() );
	}
	if( discountResult.discountPercent.isDirty() )
	{
		value += ( baseValueGetter->getItemPrice() * discountResult.discountPercent / basar::Decimal( 100 ) * baseValueGetter->getItemQty() );
	}

	return value;
}

} // end namespace discount
} // end namespace libcsc
