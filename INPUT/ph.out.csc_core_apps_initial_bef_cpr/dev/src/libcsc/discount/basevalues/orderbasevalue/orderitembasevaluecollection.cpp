#include "orderitembasevaluecollection.h"
#include <set>
#include <sstream>
#include "orderitembasevalue.h"
#include <logger/loggerpool.h>

namespace libcsc
{
namespace discount
{
void OrderItemBaseValueCollection::insert( const basar::Int32 articleNo, libcsc::discount::OrderItemBaseValuePtr orderItemBaseValue )
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerOrderItemBaseValue(), "OrderItemBaseValueCollection::insert()" );

	if( LoggerPool::getLoggerOrderItemBaseValue().isEnabledFor( log4cplus::TRACE_LOG_LEVEL ) )
	{
		std::stringstream ss;
		ss << "OrderItemBaseValue::insert(): articleNo<" << articleNo << ">, positionNo<" << orderItemBaseValue->getPositionNo() << ">";
		LoggerPool::getLoggerOrderItemBaseValue().forcedLog( log4cplus::TRACE_LOG_LEVEL, ss.str().c_str(), __FILE__, __LINE__ );
	}
		
	std::multimap<basar::Int32, libcsc::discount::OrderItemBaseValuePtr>::insert( std::pair<basar::Int32, libcsc::discount::OrderItemBaseValuePtr>( articleNo, orderItemBaseValue ) );
}

basar::Int32 OrderItemBaseValueCollection::getArticleQuantity() const
{
	basar::Int32 quantity = 0;
	const_iterator iter = begin();
	for( ; iter != end(); ++iter )
	{
		quantity += iter->second->getItemQty();
	}

	return quantity;
}

const basar::Decimal OrderItemBaseValueCollection::getArticleValue( const basar::Int32 positionNo /* = -1 */ ) const
{
	basar::Decimal value;
	const_iterator iter = begin();
	for( ; iter != end(); ++iter )
	{
		if( -1 != positionNo )
		{
			if( positionNo != iter->second->getPositionNo() )
			{
				continue;
			}
		}
		value += iter->second->getItemValue();
	}

	return value;
}

const basar::Decimal OrderItemBaseValueCollection::getRiKValue( const basar::Int32 positionNo /* = -1 */ ) const
{
	basar::Decimal value;
	const_iterator iter = begin();
	for( ; iter != end(); ++iter )
	{
		if( -1 != positionNo )
		{
			if( positionNo != iter->second->getPositionNo() )
			{
				continue;
			}
		}
		value += iter->second->getRiKValue();
	}

	return value;
}

bool OrderItemBaseValueCollection::isArticleContained( const basar::Int32 articleNo ) const
{
	const_iterator iter = begin();
	for( ; iter != end(); ++iter )
	{
		if ( articleNo == iter->first )
			return true;
	}

	return false;
}

const basar::VarString OrderItemBaseValueCollection::getArticleNumbers() const
{
	std::set<basar::Int32> numbers;
	const_iterator iter = begin();
	for( ; iter != end(); ++iter )
	{
		numbers.insert( iter->first );
	}

	// create distinct list, because multiple items with the same articleno possible
	std::set<basar::Int32>::const_iterator numberIter = numbers.begin();
	basar::Int32 count = 0;
	std::stringstream ss;
	for( ; numberIter != numbers.end(); ++numberIter, ++count )
	{
		if( 0 < count )
		{
			ss << ", ";
		}
		ss << ( *numberIter );
	}

	return ss.str().c_str();
}

} // end namespace discount
} // end namespace libcsc

