#include "orderpositiondiscountrepository.h"
#include "exceptions/invalidparameterexception.h"
#include "persistence/iaccessor.h"
#include "orderpositiondiscountcollection.h"
#include "orderpositiondiscountsqlmapper.h"
#include <sstream>
#include "logger/loggerpool.h"
#include "orderpositiondiscount.h"
#include <persistence/itransactionfactory.h>

namespace libcsc
{
namespace discount
{
OrderPositionDiscountRepository::OrderPositionDiscountRepository()
: m_OrderPositionDiscounts( new OrderPositionDiscountList() )
{
}

OrderPositionDiscountRepository::~OrderPositionDiscountRepository()
{
	m_RebateInKindEntrySelectAccessor.reset();
	m_SingleArticleSelectAccessor.reset();
	m_OrderCompletionSelectAccessor.reset();
	m_InsertAccessor.reset();
	m_UpdateAccessor.reset();
	m_DeleteAccessor.reset();
}

void OrderPositionDiscountRepository::injectRebateInKindEntrySelectAccessor(persistence::IAccessorPtr accessor)
{
	m_RebateInKindEntrySelectAccessor = accessor;
}

void OrderPositionDiscountRepository::injectSingleArticleSelectAccessor( persistence::IAccessorPtr accessor )
{
	m_SingleArticleSelectAccessor = accessor;
}

void OrderPositionDiscountRepository::injectOrderCompletionSelectAccessor( persistence::IAccessorPtr accessor )
{
	m_OrderCompletionSelectAccessor = accessor;
}

void OrderPositionDiscountRepository::injectInsertAccessor( persistence::IAccessorPtr accessor )
{
	m_InsertAccessor = accessor;
}

void OrderPositionDiscountRepository::injectUpdateAccessor( persistence::IAccessorPtr accessor )
{
	m_UpdateAccessor = accessor;
}

void OrderPositionDiscountRepository::injectDeleteAccessor( persistence::IAccessorPtr accessor )
{
	m_DeleteAccessor = accessor;
}

void OrderPositionDiscountRepository::injectTransactionFactory( persistence::ITransactionFactoryPtr transactionFactory )
{
	m_TransactionFactory = transactionFactory;
}

void OrderPositionDiscountRepository::reset()
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerOrderPositionDiscount(), "OrderPositionDiscountRepository::reset()" );

	m_OrderPositionDiscounts->clear();
}

OrderPositionDiscountPtr OrderPositionDiscountRepository::getOrderPositionDiscount( 
	const basar::Int32 positionNo, 
	const OrderPositionDiscountMode discountMode
		)
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerOrderPositionDiscount(), "OrderPositionDiscountRepository::getOrderPositionDiscount()" );

	OrderPositionDiscountList::iterator iter = m_OrderPositionDiscounts->begin();
	for( ; iter != m_OrderPositionDiscounts->end(); ++iter )
	{
		OrderPositionDiscountPtr orderPositionDiscount( *iter );
		if(    positionNo == orderPositionDiscount->getPositionNo()
			&& discountMode == orderPositionDiscount->getDiscountMode() )
		{
			return orderPositionDiscount;
		}
	}

	OrderPositionDiscountPtr orderPositionDiscount( new OrderPositionDiscount() );
	orderPositionDiscount->setPositionNo( positionNo );
	orderPositionDiscount->setDiscountMode( discountMode );
	orderPositionDiscount->setRebateInKindPositionNo( 0 );
	orderPositionDiscount->setRebateInKindOrderNo(0);
	orderPositionDiscount->setPharmacyGroupId( basar::VarString());
	m_OrderPositionDiscounts->push_back( orderPositionDiscount );
	return orderPositionDiscount;
}

OrderPositionDiscountPtr OrderPositionDiscountRepository::getOrderPositionDiscount(
	const basar::Int32 positionNo,
	const OrderPositionDiscountMode discountMode,
	const basar::Int32 rebInKindPosNo,
	const basar::Int32 rebInKindOrderNo
)
{
	BLOG_TRACE_METHOD(LoggerPool::getLoggerOrderPositionDiscount(), "OrderPositionDiscountRepository::getOrderPositionDiscount()");

	OrderPositionDiscountList::iterator iter = m_OrderPositionDiscounts->begin();
	for (; iter != m_OrderPositionDiscounts->end(); ++iter)
	{
		OrderPositionDiscountPtr orderPositionDiscount(*iter);
		if (positionNo == orderPositionDiscount->getPositionNo()
			&& discountMode == orderPositionDiscount->getDiscountMode()
			&& rebInKindPosNo == orderPositionDiscount->getRebateInKindPositionNo()
			&& rebInKindOrderNo == orderPositionDiscount->getRebateInKindOrderNo())
		{
			return orderPositionDiscount;
		}
	}

	OrderPositionDiscountPtr orderPositionDiscount(new OrderPositionDiscount());
	orderPositionDiscount->setPositionNo(positionNo);
	orderPositionDiscount->setDiscountMode(discountMode);
	orderPositionDiscount->setRebateInKindPositionNo(rebInKindPosNo);
	orderPositionDiscount->setRebateInKindOrderNo(rebInKindOrderNo);
	orderPositionDiscount->setPharmacyGroupId( basar::VarString());
	m_OrderPositionDiscounts->push_back(orderPositionDiscount);
	return orderPositionDiscount;
}

OrderPositionDiscountListPtr OrderPositionDiscountRepository::get()
{
	return m_OrderPositionDiscounts;
}

void OrderPositionDiscountRepository::save()
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerOrderPositionDiscount(), "OrderPositionDiscountRepository::save()" );

	persistence::TransactionGuard guard = m_TransactionFactory->createTransaction();
	try
	{
		guard.begin();
		OrderPositionDiscountList::iterator iter = m_OrderPositionDiscounts->begin();
		for (; iter != m_OrderPositionDiscounts->end(); ++iter)
		{
			OrderPositionDiscountPtr orderPositionDiscount(*iter);
			if (orderPositionDiscount->getRebateInKindPositionNo() >= 0 )
			{
				if (OrderPositionDiscountSQLMapper::isInsertable(orderPositionDiscount))
				{
					m_InsertAccessor->execute(OrderPositionDiscountSQLMapper::getInsertSQL(), OrderPositionDiscountSQLMapper::getInsertSqlParameterBinder(orderPositionDiscount));
				}
				else if (OrderPositionDiscountSQLMapper::isUpdatable(orderPositionDiscount))
				{
					m_UpdateAccessor->execute(OrderPositionDiscountSQLMapper::getUpdateSQL(), OrderPositionDiscountSQLMapper::getUpdateSqlParameterBinder(orderPositionDiscount));
				}
				else
				{
					// nothing to do
				}
			}
		}

		guard.commit();
	}
	catch( const basar::Exception & e )
	{
		guard.rollback();
		std::stringstream ss;
		ss << "OrderPositionDiscountRepository::save(): " << e.what().c_str();
		BLOG_ERROR( LoggerPool::getLoggerOrderPositionDiscount(), ss.str().c_str() );
	}
}

void OrderPositionDiscountRepository::erase( OrderPositionDiscountPtr orderPositionDiscount )
{
	OrderPositionDiscountList::iterator iter = m_OrderPositionDiscounts->begin();
	for( ; iter != m_OrderPositionDiscounts->end(); ++iter )
	{
		if( orderPositionDiscount == ( *iter ) )
		{
			if( orderPositionDiscount->getOrderNo().isClean() )
			{
				try
				{
					m_DeleteAccessor->execute( OrderPositionDiscountSQLMapper::getDeleteSQL(), OrderPositionDiscountSQLMapper::getDeleteSqlParameterBinder( orderPositionDiscount ) );
				}
				catch( const basar::Exception & e )
				{
					std::stringstream ss;
					ss << "OrderPositionDiscountRepository::erase(): " << e.what().c_str();
					BLOG_ERROR( LoggerPool::getLoggerOrderPositionDiscount(), ss.str().c_str() );
				}
			}
			m_OrderPositionDiscounts->erase( iter );
			return;
		}
	}
}

OrderPositionDiscountListPtr OrderPositionDiscountRepository::findByID( 
	const basar::Int32 orderNo, 
	const basar::Int32 positionNo /* = 0 */
		) const
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerOrderPositionDiscount(), "OrderPositionDiscountRepository::findByID()" );

	m_OrderPositionDiscounts->clear();
	//OrderPositionDiscountListPtr orderPositionDiscounts( new OrderPositionDiscountList() );
	basar::Int32 counter = 0;
	try
	{
		basar::db::sql::ResultsetRef resultset;
		if( 0 == positionNo )
		{
			resultset = m_OrderCompletionSelectAccessor->select( OrderPositionDiscountSQLMapper::getOrderCompletionSelectSQL(), OrderPositionDiscountSQLMapper::getOrderCompletionSelectSqlParameterBinder( orderNo ) );
		}
		else
		{
			resultset = m_SingleArticleSelectAccessor->select( OrderPositionDiscountSQLMapper::getSingleArticleSelectSQL(), OrderPositionDiscountSQLMapper::getSingleArticleSelectSqlParameterBinder( orderNo, positionNo ) );
		}
		
		while( resultset.next() )
		{
			OrderPositionDiscountPtr orderPositionDiscount( new OrderPositionDiscount() );
			OrderPositionDiscountSQLMapper mapper( orderPositionDiscount, resultset );
			mapper.map();
			m_OrderPositionDiscounts->push_back( orderPositionDiscount );
			++counter;
		} 
	}
	catch( basar::Exception & )
	{
		throw;
	}

	std::stringstream ss;
	ss << "OrderPositionDiscountRepository::findByID(): orderNo<" << orderNo << ">, positionNo<" << positionNo << "> - " << counter << " discounts added";
	BLOG_TRACE( LoggerPool::getLoggerOrderPositionDiscount(), ss.str().c_str() );

	return m_OrderPositionDiscounts;
}

OrderPositionDiscountListPtr OrderPositionDiscountRepository::findByIDBackward(
	const basar::Int32 rebateinkindorderno,
	const basar::Int32 rebateinkindpositionNo 
) const
{
	BLOG_TRACE_METHOD(LoggerPool::getLoggerOrderPositionDiscount(), "OrderPositionDiscountRepository::findByIDBackward()");

	m_OrderPositionDiscounts->clear();
	basar::Int32 counter = 0;
	try
	{
		basar::db::sql::ResultsetRef resultset;
		resultset = m_RebateInKindEntrySelectAccessor->select(OrderPositionDiscountSQLMapper::getRebateInKindEntrySelectSQL(), OrderPositionDiscountSQLMapper::getRebateInKindEntrySelectSQLParameterBinder(rebateinkindorderno, rebateinkindpositionNo));

		while (resultset.next())
		{
			OrderPositionDiscountPtr orderPositionDiscount(new OrderPositionDiscount());
			OrderPositionDiscountSQLMapper mapper(orderPositionDiscount, resultset);
			mapper.map();
			m_OrderPositionDiscounts->push_back(orderPositionDiscount);
			++counter;
		}
	}
	catch (basar::Exception &)
	{
		throw;
	}

	std::stringstream ss;
	ss << "OrderPositionDiscountRepository::findByIDBackward(): orderNo<" << rebateinkindorderno << ">, positionNo<" << rebateinkindpositionNo << "> - " << counter << " discounts added";
	BLOG_TRACE(LoggerPool::getLoggerOrderPositionDiscount(), ss.str().c_str());

	return m_OrderPositionDiscounts;
}

} // end namespace discount
} // end namespace libcsc
