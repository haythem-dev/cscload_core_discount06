#ifndef GUARD_LIBCSC_ARTICLE_CLASSIFICATION_SQL_MAPPER_H
#define GUARD_LIBCSC_ARTICLE_CLASSIFICATION_SQL_MAPPER_H

#include <libbasardbsql_resultsetref.h>
#include <discount/basevalues/orderbasevalue/articleclassificationcollection.h>
#include <discount/basevalues/orderbasevalue/iorderbasevaluegetterptr.h>

namespace libcsc
{
namespace discount
{
class ArticleClassificationSQLMapper
{
public:
	ArticleClassificationSQLMapper( 
		const OrderItemBaseValueCollectionPtr orderItemBaseValues,
		ArticleClassificationCollectionPtr collection,
		const basar::db::sql::ResultsetRef resultSet 
			);
	virtual ~ArticleClassificationSQLMapper();

	static const basar::VarString getArticleGroupSelectSQL( const IOrderBaseValueGetterPtr orderBaseValue );
	static const basar::VarString getManufacturerSelectSQL( const IOrderBaseValueGetterPtr orderBaseValue );
	static const basar::VarString getManufacturerGroupSelectSQL( const IOrderBaseValueGetterPtr orderBaseValue );
	void mapArticleGroups();
	void mapArticleManufacturers();
	void mapArticleManufacturerGroups();

private:
	ArticleClassificationSQLMapper( const ArticleClassificationSQLMapper & );
	ArticleClassificationSQLMapper & operator=( const ArticleClassificationSQLMapper & );

	void map( const basar::Int32 groupNo, const basar::Int32 articleNo );
	OrderItemBaseValueCollectionPtr getCollection( const basar::Int32 key );

	OrderItemBaseValueCollectionPtr			m_OrderItemBaseValues;
	ArticleClassificationCollectionPtr		m_ArticleClassificationCollection;
	const basar::db::sql::ResultsetRef		m_ResultSet;
};

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_ARTICLE_CLASSIFICATION_SQL_MAPPER_H
