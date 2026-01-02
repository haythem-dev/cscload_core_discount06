#include "orderpositiondiscountprocessedrepository.h"
#include "exceptions/invalidparameterexception.h"
#include "persistence/iaccessor.h"
#include "orderpositiondiscountprocessedcollection.h"
#include "orderpositiondiscountprocessedsqlmapper.h"
#include <sstream>
#include "logger/loggerpool.h"
#include "orderpositiondiscountprocessed.h"
#include <persistence/itransactionfactory.h>

namespace libcsc
{
namespace discount
{
OrderPositionDiscountProcessedRepository::OrderPositionDiscountProcessedRepository()
: m_OrderPositionDiscountProcessedList( new OrderPositionDiscountProcessedCollection() )
{
}

OrderPositionDiscountProcessedRepository::~OrderPositionDiscountProcessedRepository()
{
	m_SelectAccessor.reset();
	m_InsertAccessor.reset();
}

void OrderPositionDiscountProcessedRepository::injectSelectAccessor( persistence::IAccessorPtr accessor )
{
	m_SelectAccessor = accessor;
}

void OrderPositionDiscountProcessedRepository::injectInsertAccessor( persistence::IAccessorPtr accessor )
{
	m_InsertAccessor = accessor;
}

void OrderPositionDiscountProcessedRepository::injectTransactionFactory( persistence::ITransactionFactoryPtr transactionFactory )
{
	m_TransactionFactory = transactionFactory;
}

IOrderPositionDiscountProcessedCollectionPtr OrderPositionDiscountProcessedRepository::get() const
{
	return m_OrderPositionDiscountProcessedList;
}

IOrderPositionDiscountProcessedCollectionPtr OrderPositionDiscountProcessedRepository::findByID( const libcsc::Int32 orderNo ) const
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerOrderPositionDiscount(), "OrderPositionDiscountProcessedRepository::findByID()" );

	OrderPositionDiscountProcessedCollectionPtr orderPositionDiscountProcessedList( new OrderPositionDiscountProcessedCollection() );
	basar::Int32 counter = 0;
	try
	{
		basar::db::sql::ResultsetRef resultset = m_SelectAccessor->select( OrderPositionDiscountProcessedSQLMapper::getSelectSQL(), OrderPositionDiscountProcessedSQLMapper::getSelectSqlParameterBinder( orderNo ) );
		while( resultset.next() )
		{
			OrderPositionDiscountProcessedPtr orderPositionDiscountProcessed( new OrderPositionDiscountProcessed() );
			OrderPositionDiscountProcessedSQLMapper mapper( orderPositionDiscountProcessed, resultset );
			mapper.map();
			orderPositionDiscountProcessedList->insert( orderPositionDiscountProcessed->getPositionNo(), orderPositionDiscountProcessed );
			++counter;
		} 
	}
	catch( basar::Exception & )
	{
		throw;
	}

	std::stringstream ss;
	ss << "OrderPositionDiscountProcessedRepository::findByID(): orderNo<" << orderNo << "> - " << counter << " discount processed elements added";
	BLOG_TRACE( LoggerPool::getLoggerOrderPositionDiscount(), ss.str().c_str() );

	return orderPositionDiscountProcessedList;
}

void OrderPositionDiscountProcessedRepository::save()
{
	persistence::TransactionGuard guard = m_TransactionFactory->createTransaction();
	try
	{
		guard.begin();
		OrderPositionDiscountProcessedCollection::const_iterator iter = m_OrderPositionDiscountProcessedList->begin();
		for( ; iter != m_OrderPositionDiscountProcessedList->end(); ++iter )
		{
			OrderPositionDiscountProcessedPtr orderPositionDiscountProcessed( iter->second );
			if( OrderPositionDiscountProcessedSQLMapper::isInsertable( orderPositionDiscountProcessed ) )
			{
				m_InsertAccessor->execute( OrderPositionDiscountProcessedSQLMapper::getInsertSQL(), OrderPositionDiscountProcessedSQLMapper::getInsertSqlParameterBinder( orderPositionDiscountProcessed ) );
			}
			else
			{
				// nothing to do
			}
		}

		guard.commit();

		// TODO: set clean?
	}
	catch( const basar::Exception & e )
	{
		guard.rollback();
		std::stringstream ss;
		ss << "OrderPositionDiscountProcessedRepository::save(): " << e.what().c_str();
		BLOG_ERROR( LoggerPool::getLoggerOrderPositionDiscount(), ss.str().c_str() );
	}
}

} // end namespace discount
} // end namespace libcsc
