#include "articleclassificationsqlmapper.h"
#include <discount/basevalues/discountbasevalue/discountbasevalue.h>
#include "discount/basevalues/orderbasevalue/iorderbasevaluegetter.h"
#include <sstream>
#include "logger/loggerpool.h"
#include "orderitembasevaluecollection.h"

namespace libcsc
{
namespace discount
{
ArticleClassificationSQLMapper::ArticleClassificationSQLMapper(
	const OrderItemBaseValueCollectionPtr orderItemBaseValues,
	ArticleClassificationCollectionPtr collection,
	const basar::db::sql::ResultsetRef resultSet 
		)
: m_OrderItemBaseValues( orderItemBaseValues ),
  m_ArticleClassificationCollection( collection ),
  m_ResultSet( resultSet )
{
}

ArticleClassificationSQLMapper::~ArticleClassificationSQLMapper()
{
}


const basar::VarString ArticleClassificationSQLMapper::getArticleGroupSelectSQL( const IOrderBaseValueGetterPtr orderBaseValue )
{
	std::stringstream ss;
	ss <<
	"SELECT DISTINCT "
		"m.discountgrpno, "
		"m.articleno "
	"FROM "
		"discountgrpmem m "
		"INNER JOIN discount d ON d.discountgrpno = m.discountgrpno and d.branchno = m.branchno "
	"WHERE "
		"m.articleno IN ( " << orderBaseValue->getOrderItemBaseValueCollection()->getArticleNumbers() << " ) AND "
		"d.monthlydiscount = 0 AND "
		"d.datefrom <= cast(to_char(current, '%Y%m%d') as integer) AND "
		"d.dateto >= cast(to_char(current, '%Y%m%d') as integer) AND "
		"m.branchno = " << orderBaseValue->getBranchNo();
	return ss.str();
}

const basar::VarString ArticleClassificationSQLMapper::getManufacturerSelectSQL( const IOrderBaseValueGetterPtr orderBaseValue )
{
	// wenn jedes OrderItem seine HNR bereits kennen würde, wäre das hier überflüssig!

	std::stringstream ss;
	ss << "SELECT hersteller_nr, artikel_nr FROM artikelzentral WHERE artikel_nr IN ( " << orderBaseValue->getOrderItemBaseValueCollection()->getArticleNumbers() << " ); ";
	return ss.str().c_str();
}

const basar::VarString ArticleClassificationSQLMapper::getManufacturerGroupSelectSQL( const IOrderBaseValueGetterPtr orderBaseValue )
{
	std::stringstream ss;
	ss << 
	"SELECT DISTINCT "
		"m.discountgrpno, "
		"z.artikel_nr "
	"FROM "
		"discountgrpmem m "
		"INNER JOIN artikelzentral z ON m.manufacturerno = z.hersteller_nr "
		"INNER JOIN discount d ON d.discountgrpno = m.discountgrpno and d.branchno = m.branchno "
	"WHERE "
		"artikel_nr IN ( " << orderBaseValue->getOrderItemBaseValueCollection()->getArticleNumbers() << " ) AND "
		"d.monthlydiscount = 0 AND "
		"d.datefrom <= cast(to_char(current, '%Y%m%d') as integer) AND "
		"d.dateto >= cast(to_char(current, '%Y%m%d') as integer) AND "
		"m.branchno = " << orderBaseValue->getBranchNo();
	return ss.str();
}

void ArticleClassificationSQLMapper::mapArticleGroups()
{
	// TODO: check ResultSet
	if( m_ResultSet.isNull() )
	{
		throw;
	}

	basar::Int32 groupNo = m_ResultSet.getInt32( "discountgrpno" );
	basar::Int32 articleNo = m_ResultSet.getInt32( "articleno" );
	map( groupNo, articleNo );
}

void ArticleClassificationSQLMapper::mapArticleManufacturers()
{
	// TODO: check ResultSet
	if( m_ResultSet.isNull() )
	{
		throw;
	}

	basar::Int32 groupNo = m_ResultSet.getInt32( "hersteller_nr" );
	basar::Int32 articleNo = m_ResultSet.getInt32( "artikel_nr" );
	map( groupNo, articleNo );
}

void ArticleClassificationSQLMapper::mapArticleManufacturerGroups()
{
	// TODO: check ResultSet
	if( m_ResultSet.isNull() )
	{
		throw;
	}

	basar::Int32 groupNo = m_ResultSet.getInt32( "discountgrpno" );
	basar::Int32 articleNo = m_ResultSet.getInt32( "artikel_nr" );
	map( groupNo, articleNo );
}

void ArticleClassificationSQLMapper::map( const basar::Int32 groupNo, const basar::Int32 articleNo )
{
	std::pair<OrderItemBaseValueCollection::const_iterator, OrderItemBaseValueCollection::const_iterator> range = m_OrderItemBaseValues->equal_range( articleNo );
	OrderItemBaseValueCollection::const_iterator iter = range.first;
	if( iter == m_OrderItemBaseValues->end() )
	{
		return;
	}

	OrderItemBaseValueCollectionPtr collection = getCollection( groupNo );
	for( ; iter != range.second; ++iter )
	{
		collection->insert( articleNo, iter->second );
	}
}

OrderItemBaseValueCollectionPtr ArticleClassificationSQLMapper::getCollection( const basar::Int32 key )
{
	OrderItemBaseValueCollectionPtr collection;
	ArticleClassificationCollection::iterator iter = m_ArticleClassificationCollection->find( key );
	if( iter == m_ArticleClassificationCollection->end() )
	{
		collection = OrderItemBaseValueCollectionPtr( new OrderItemBaseValueCollection() );
		m_ArticleClassificationCollection->insert( std::pair<basar::Int32, libcsc::discount::OrderItemBaseValueCollectionPtr>( key, collection ) );
	}
	else
	{
		collection = iter->second;
	}

	return collection;
}

} // end namespace discount
} // end namespace libcsc

