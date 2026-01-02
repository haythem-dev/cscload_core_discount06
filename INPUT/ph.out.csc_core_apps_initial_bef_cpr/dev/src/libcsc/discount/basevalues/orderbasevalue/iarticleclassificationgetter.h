#ifndef GUARD_LIBCSC_I_ARTICLE_CLASSIFICATION_GETTER_H
#define GUARD_LIBCSC_I_ARTICLE_CLASSIFICATION_GETTER_H

#include <discount/basevalues/orderbasevalue/articleclassificationcollection.h>
#include <discount/basevalues/orderbasevalue/iorderbasevaluegetterptr.h>

namespace libcsc
{
namespace discount
{
class IArticleClassificationGetter
{
public:
	virtual ~IArticleClassificationGetter() {}

	virtual const ArticleClassificationCollectionPtr getClassificationByArticleGroup( const IOrderBaseValueGetterPtr orderBaseValue ) const = 0;
	virtual const ArticleClassificationCollectionPtr getClassificationByManufacturer( const IOrderBaseValueGetterPtr orderBaseValue ) const = 0;
	virtual const ArticleClassificationCollectionPtr getClassificationByManufacturerGroup( const IOrderBaseValueGetterPtr orderBaseValue ) const = 0;
};

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_I_ARTICLE_CLASSIFICATION_GETTER_H
