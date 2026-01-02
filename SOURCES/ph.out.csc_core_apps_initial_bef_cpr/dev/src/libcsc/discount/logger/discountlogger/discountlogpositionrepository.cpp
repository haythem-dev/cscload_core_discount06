#include "discountlogpositionrepository.h"
#include "discountlogpositionptr.h"
#include "discountlogposition.h"
#include "discountlogpositionsqlmapper.h"
#include <persistence/itransactionfactory.h>
#include <persistence/iaccessor.h>
#include "logger/loggerpool.h"

namespace libcsc
{
namespace discount
{
DiscountLogPositionRepository::DiscountLogPositionRepository()
: m_DiscountLogPositions( new DiscountLogPositionCollection() )
{
}

DiscountLogPositionRepository::~DiscountLogPositionRepository()
{
	m_InsertAccessor.reset();
	m_DeleteAccessor.reset();
}

void DiscountLogPositionRepository::injectInsertAccessor( persistence::IAccessorPtr accessor )
{
	m_InsertAccessor = accessor;
}

void DiscountLogPositionRepository::injectDeleteAccessor( persistence::IAccessorPtr accessor )
{
	m_DeleteAccessor = accessor;
}

void DiscountLogPositionRepository::injectTransactionFactory( persistence::ITransactionFactoryPtr transactionFactory )
{
	m_TransactionFactory = transactionFactory;
}

DiscountLogPositionCollectionPtr DiscountLogPositionRepository::get()
{
	return m_DiscountLogPositions;
}

void DiscountLogPositionRepository::save()
{
	persistence::TransactionGuard guard = m_TransactionFactory->createTransaction();
	try
	{
		guard.begin();
		DiscountLogPositionCollection::iterator iter = m_DiscountLogPositions->begin();
		DiscountLogPositionPtr discountLogPosition( *iter );

		m_DeleteAccessor->execute( DiscountLogPositionSQLMapper::getDeleteSQL( discountLogPosition ) );

		for( ; iter != m_DiscountLogPositions->end(); ++iter )
		{
			discountLogPosition = ( *iter );
			if( DiscountLogPositionSQLMapper::isInsertable( discountLogPosition ) )
			{
				m_InsertAccessor->execute( DiscountLogPositionSQLMapper::getInsertSQL(), DiscountLogPositionSQLMapper::getInsertSqlParameterBinder( discountLogPosition ) );
			}
			else
			{
				// nothing to do
			}
		}

		guard.commit();
	}
	catch( const basar::Exception & e )
	{
		guard.rollback();
		std::stringstream ss;
		ss << "DiscountLogPositionRepository::save(): " << e.what().c_str();
		BLOG_ERROR( LoggerPool::getLoggerDiscountLog(), ss.str().c_str() );
	}
}

} // end namespace discount
} // end namespace libcsc

