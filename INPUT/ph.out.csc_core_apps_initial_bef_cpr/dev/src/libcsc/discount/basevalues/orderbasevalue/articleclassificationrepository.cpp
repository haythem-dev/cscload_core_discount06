#include "articleclassificationrepository.h"
#include "exceptions/invalidparameterexception.h"
#include "persistence/iaccessor.h"
#include "articleclassificationsqlmapper.h"
#include <sstream>
#include "logger/loggerpool.h"

namespace libcsc
{
namespace discount
{
ArticleClassificationRepository::ArticleClassificationRepository()
{
}

ArticleClassificationRepository::~ArticleClassificationRepository()
{
	m_Accessor.reset();
}

void ArticleClassificationRepository::setOrderItemBaseValues( OrderItemBaseValueCollectionPtr orderItemBaseValues )
{
	m_OrderItemBaseValues = orderItemBaseValues;
}

void ArticleClassificationRepository::injectSelectAccessor( persistence::IAccessorPtr accessor )
{
	m_Accessor = accessor;
}

const ArticleClassificationCollectionPtr ArticleClassificationRepository::getClassificationByArticleGroup( const IOrderBaseValueGetterPtr orderBaseValue ) const
{
	if( NULL == m_ArticleGroups.get() )
	{
		findClassificationByArticleGroup( orderBaseValue );
	}
	return m_ArticleGroups;
}

const ArticleClassificationCollectionPtr ArticleClassificationRepository::getClassificationByManufacturer( const IOrderBaseValueGetterPtr orderBaseValue ) const
{
	if( NULL == m_Manufacturers.get() )
	{
		findClassificationByManufacturer( orderBaseValue );
	}
	return m_Manufacturers;
}

const ArticleClassificationCollectionPtr ArticleClassificationRepository::getClassificationByManufacturerGroup( const IOrderBaseValueGetterPtr orderBaseValue ) const
{
	if( NULL == m_ManufacturerGroups.get() )
	{
		findClassificationByManufacturerGroup( orderBaseValue );
	}
	return m_ManufacturerGroups;
}

void ArticleClassificationRepository::findClassificationByArticleGroup( const IOrderBaseValueGetterPtr orderBaseValue ) const
{
	if( NULL == orderBaseValue.get() )
	{
		throw exceptions::InvalidParameterException( basar::ExceptInfo( "ArticleClassificationRepository::findClassificationByArticleGroup()", "OrderBaseValue is empty!", __FILE__, __LINE__ ) );
	}

	m_ArticleGroups = ArticleClassificationCollectionPtr( new ArticleClassificationCollection() );
	basar::Int32 counter = 0;
	try
	{
		basar::db::sql::ResultsetRef resultset = m_Accessor->select( ArticleClassificationSQLMapper::getArticleGroupSelectSQL( orderBaseValue ) );
		while( resultset.next() )
		{
			ArticleClassificationSQLMapper mapper( m_OrderItemBaseValues, m_ArticleGroups, resultset );
			mapper.mapArticleGroups();
			++counter;
		} 
	}
	catch( basar::Exception & )
	{
		throw;
	}
}

void ArticleClassificationRepository::findClassificationByManufacturer( const IOrderBaseValueGetterPtr orderBaseValue ) const
{
	if( NULL == orderBaseValue.get() )
	{
		throw exceptions::InvalidParameterException( basar::ExceptInfo( "ArticleClassificationRepository::findClassificationByManufacturer()", "OrderBaseValue is empty!", __FILE__, __LINE__ ) );
	}

	m_Manufacturers = ArticleClassificationCollectionPtr( new ArticleClassificationCollection() );
	basar::Int32 counter = 0;
	try
	{
		basar::db::sql::ResultsetRef resultset = m_Accessor->select( ArticleClassificationSQLMapper::getManufacturerSelectSQL( orderBaseValue ) );
		while( resultset.next() )
		{
			ArticleClassificationSQLMapper mapper( m_OrderItemBaseValues, m_Manufacturers, resultset );
			mapper.mapArticleManufacturers();
			++counter;
		} 
	}
	catch( basar::Exception & )
	{
		throw;
	}
}

void ArticleClassificationRepository::findClassificationByManufacturerGroup( const IOrderBaseValueGetterPtr orderBaseValue ) const
{
	if( NULL == orderBaseValue.get() )
	{
		throw exceptions::InvalidParameterException( basar::ExceptInfo( "ArticleClassificationRepository::findClassificationByManufacturerGroup()", "OrderBaseValue is empty!", __FILE__, __LINE__ ) );
	}

	m_ManufacturerGroups = ArticleClassificationCollectionPtr( new ArticleClassificationCollection() );
	basar::Int32 counter = 0;
	try
	{
		basar::db::sql::ResultsetRef resultset = m_Accessor->select( ArticleClassificationSQLMapper::getManufacturerGroupSelectSQL( orderBaseValue ) );
		while( resultset.next() )
		{
			ArticleClassificationSQLMapper mapper( m_OrderItemBaseValues, m_ManufacturerGroups, resultset );
			mapper.mapArticleManufacturerGroups();
			++counter;
		} 
	}
	catch( basar::Exception & )
	{
		throw;
	}
}



/*

	std::stringstream ss;
	ss << "ArticleClassificationRepository::get(): " << counter << " discount base values added";
	BLOG_TRACE( LoggerPool::getLoggerDiscountBaseValue(), ss.str().c_str() );

*/


} // end namespace discount
} // end namespace libcsc
