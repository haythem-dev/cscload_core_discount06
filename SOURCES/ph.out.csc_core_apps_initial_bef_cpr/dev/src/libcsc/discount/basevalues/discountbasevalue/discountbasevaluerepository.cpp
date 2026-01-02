#include "discountbasevaluerepository.h"
#include "exceptions/invalidparameterexception.h"
#include "persistence/iaccessor.h"
#include "discountbasevaluesqlmapper.h"
#include "discountbasevalue.h"
#include "discountbasevaluecollection.h"
#include <sstream>
#include "logger/loggerpool.h"

namespace libcsc
{
namespace discount
{
DiscountBaseValueRepository::DiscountBaseValueRepository()
: m_DiscountBaseValues( new DiscountBaseValueCollection() ),
  m_SingleArticleDiscountBaseValues( new DiscountBaseValueCollection() ),
  m_MultiArticleDiscountBaseValues( new DiscountBaseValueCollection() ),
  m_IsGermany(false)
{
}

DiscountBaseValueRepository::~DiscountBaseValueRepository()
{
	m_SingleAccessor.reset();
	m_MultiAccessor.reset();
}

void DiscountBaseValueRepository::setIsGermany()
{
	m_IsGermany = true;
}


void DiscountBaseValueRepository::injectSingleSelectAccessor( persistence::IAccessorPtr singleAccessor )
{
	m_SingleAccessor = singleAccessor;
}

void DiscountBaseValueRepository::injectMultiSelectAccessor( persistence::IAccessorPtr multiAccessor )
{
	m_MultiAccessor = multiAccessor;
}

DiscountBaseValueCollectionPtr DiscountBaseValueRepository::get()
{
	if( m_DiscountBaseValues->empty() )
	{
		combineDiscountBaseValues();
	}
	return m_DiscountBaseValues;
}

void DiscountBaseValueRepository::combineDiscountBaseValues() const
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerDiscountBaseValue(), "DiscountBaseValueRepository::combineDiscountBaseValues()" );

	// add range discount values if present
	DiscountBaseValueList::const_iterator multiIter = m_MultiArticleDiscountBaseValues->getCollection().begin();
	for( ; multiIter != m_MultiArticleDiscountBaseValues->getCollection().end(); ++multiIter )
	{
		m_DiscountBaseValues->add( *multiIter );
	}

	// add article discount values if present
	DiscountBaseValueList coll;
	if (m_IsGermany)
	{
		coll = m_SingleArticleDiscountBaseValues->getCollection();
	}
	else
	{
		coll = m_SingleArticleDiscountBaseValues->getCollectionByArticleNo();
	}
	DiscountBaseValueList::const_iterator singleIter = coll.begin();
	for( ; singleIter != coll.end(); ++singleIter )
	{
		m_DiscountBaseValues->add( *singleIter );
	}

	if( LoggerPool::getLoggerDiscountBaseValue().isEnabledFor( log4cplus::TRACE_LOG_LEVEL ) )
	{
		std::stringstream ss;
		if( m_DiscountBaseValues->empty() )
		{
			ss << "m_DiscountBaseValues is empty!" << std::endl;
		}
		else
		{
			DiscountBaseValueList::const_iterator iter = m_DiscountBaseValues->getCollection().begin();
			for( ; iter != m_DiscountBaseValues->getCollection().end(); ++iter )
			{
				DiscountBaseValuePtr baseValue( *iter );
				ss << ( *baseValue ) << std::endl;
			}
		}

		LoggerPool::getLoggerDiscountBaseValue().forcedLog( log4cplus::TRACE_LOG_LEVEL, ss.str().c_str(), __FILE__, __LINE__ );
	}
}

DiscountBaseValueCollectionPtr DiscountBaseValueRepository::findByArticle( const IOrderBaseValueGetterPtr orderBaseValue ) const
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerDiscountBaseValue(), "DiscountBaseValueRepository::findByArticle()" );

	if( NULL == orderBaseValue.get() )
	{
		throw exceptions::InvalidParameterException( basar::ExceptInfo( "DiscountBaseValueRepository::findByArticle()", "OrderBaseValue is empty!", __FILE__, __LINE__ ) );
	}

	m_DiscountBaseValues->clear();
	m_SingleArticleDiscountBaseValues->clear();
	basar::Int32 counter = 0;
	try
	{
		basar::db::sql::ResultsetRef resultset;
		if (m_IsGermany)
		{
			resultset = m_SingleAccessor->select(DiscountBaseValueSQLMapper::getSingleArticleSelectDESQL(orderBaseValue));
		}
		else
		{
			resultset = m_SingleAccessor->select(DiscountBaseValueSQLMapper::getSingleArticleSelectSQL(), DiscountBaseValueSQLMapper::getSingleArticleSqlParameterBinder(orderBaseValue));
		}
		while( resultset.next() )
		{
			DiscountBaseValuePtr discountBaseValue( new DiscountBaseValue() );
			DiscountBaseValueSQLMapper mapper( discountBaseValue, resultset );
			mapper.map();
			m_SingleArticleDiscountBaseValues->add( discountBaseValue );
			++counter;
		}
	}
	catch( basar::Exception & )
	{
		throw;
	}

	std::stringstream ss;
	ss << "DiscountBaseValueRepository::findByArticle(): " << counter << " discount base values added";
	BLOG_TRACE( LoggerPool::getLoggerDiscountBaseValue(), ss.str().c_str() );

	combineDiscountBaseValues();

	return m_SingleArticleDiscountBaseValues;
}

DiscountBaseValueCollectionPtr DiscountBaseValueRepository::findByOrder( const IOrderBaseValueGetterPtr orderBaseValue ) const
{
	if( NULL == orderBaseValue.get() )
	{
		throw exceptions::InvalidParameterException( basar::ExceptInfo( "DiscountBaseValueRepository::findByOrder()", "OrderBaseValue is empty!", __FILE__, __LINE__ ) );
	}

	m_DiscountBaseValues->clear();
	m_MultiArticleDiscountBaseValues->clear();
	basar::Int32 counter = 0;
	try
	{
		//basar::db::sql::ResultsetRef resultset = m_Accessor->select( DiscountBaseValueSQLMapper::getMultiArticleSelectSQL(), DiscountBaseValueSQLMapper::getOrderCompletionSqlParameterBinder( orderBaseValue ) );
		basar::db::sql::ResultsetRef resultset = m_MultiAccessor->select( DiscountBaseValueSQLMapper::getMultiArticleSelectSQL( orderBaseValue ) );
		while( resultset.next() )
		{
			DiscountBaseValuePtr discountBaseValue( new DiscountBaseValue() );
			DiscountBaseValueSQLMapper mapper( discountBaseValue, resultset );
			mapper.map();
			m_MultiArticleDiscountBaseValues->add( discountBaseValue );
			++counter;
		}
	}
	catch( basar::Exception & )
	{
		throw;
	}

	std::stringstream ss;
	ss << "DiscountBaseValueRepository::findByOrder(): " << counter << " discount base values added";
	BLOG_TRACE( LoggerPool::getLoggerDiscountBaseValue(), ss.str().c_str() );

	return m_MultiArticleDiscountBaseValues;
}

} // end namespace discount
} // end namespace libcsc
