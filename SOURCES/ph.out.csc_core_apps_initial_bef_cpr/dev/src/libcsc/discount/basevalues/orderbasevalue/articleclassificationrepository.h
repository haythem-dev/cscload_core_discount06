#ifndef GUARD_LIBCSC_ARTICLE_CLASSIFICATION_REPOSITORY_H
#define GUARD_LIBCSC_ARTICLE_CLASSIFICATION_REPOSITORY_H

#include <discount/basevalues/orderbasevalue/iarticleclassificationgetter.h>
#include <persistence/iaccessorptr.h>
#include <boost/shared_ptr.hpp>

namespace libcsc
{
namespace discount
{
class ArticleClassificationRepository : public IArticleClassificationGetter
{
public:
	ArticleClassificationRepository();
	virtual ~ArticleClassificationRepository();

	void setOrderItemBaseValues( OrderItemBaseValueCollectionPtr orderItemBaseValues );
	void injectSelectAccessor( persistence::IAccessorPtr accessor );

	virtual const ArticleClassificationCollectionPtr getClassificationByArticleGroup( const IOrderBaseValueGetterPtr orderBaseValue ) const;
	virtual const ArticleClassificationCollectionPtr getClassificationByManufacturer( const IOrderBaseValueGetterPtr orderBaseValue ) const;
	virtual const ArticleClassificationCollectionPtr getClassificationByManufacturerGroup( const IOrderBaseValueGetterPtr orderBaseValue ) const;

private:
	void findClassificationByArticleGroup( const IOrderBaseValueGetterPtr orderBaseValue ) const;
	void findClassificationByManufacturer( const IOrderBaseValueGetterPtr orderBaseValue ) const;
	void findClassificationByManufacturerGroup( const IOrderBaseValueGetterPtr orderBaseValue ) const;

	mutable ArticleClassificationCollectionPtr		m_ArticleGroups;
	mutable ArticleClassificationCollectionPtr		m_Manufacturers;
	mutable ArticleClassificationCollectionPtr		m_ManufacturerGroups;
	OrderItemBaseValueCollectionPtr					m_OrderItemBaseValues;
	persistence::IAccessorPtr						m_Accessor;
};

typedef boost::shared_ptr<libcsc::discount::ArticleClassificationRepository> ArticleClassificationRepositoryPtr;

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_ARTICLE_CLASSIFICATION_REPOSITORY_H
