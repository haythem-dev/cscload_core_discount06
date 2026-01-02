#ifndef GUARD_LIBCSC_ARTICLE_CLASSIFICATION_COLLECTION_H
#define GUARD_LIBCSC_ARTICLE_CLASSIFICATION_COLLECTION_H

#include <vector>
#include <map>
#include <libbasar_definitions.h>
#include <boost/shared_ptr.hpp>
#include <discount/basevalues/orderbasevalue/orderitembasevaluecollectionptr.h>

namespace libcsc
{
namespace discount
{
	// TODO: change to typedef std::map<basar::Int32, libcsc::discount::IOrderItemBaseValueCollectionPtr> ArticleClassificationCollection;
typedef std::map<basar::Int32, libcsc::discount::OrderItemBaseValueCollectionPtr> ArticleClassificationCollection;
typedef boost::shared_ptr<libcsc::discount::ArticleClassificationCollection> ArticleClassificationCollectionPtr;

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_ARTICLE_CLASSIFICATION_COLLECTION_H
