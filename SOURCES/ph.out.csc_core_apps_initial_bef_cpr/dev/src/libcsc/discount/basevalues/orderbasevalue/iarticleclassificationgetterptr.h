#ifndef GUARD_LIBCSC_I_ARTICLE_CLASSIFICATION_GETTER_PTR_H
#define GUARD_LIBCSC_I_ARTICLE_CLASSIFICATION_GETTER_PTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc
{
namespace discount
{
class IArticleClassificationGetter;
typedef boost::shared_ptr<libcsc::discount::IArticleClassificationGetter> IArticleClassificationGetterPtr;

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_I_ARTICLE_CLASSIFICATION_GETTER_PTR_H
