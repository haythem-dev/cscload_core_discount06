#ifndef GUARD_LIBCSC_IBT_ARTICLEQUOTA_CHECKER_PTR_H
#define GUARD_LIBCSC_IBT_ARTICLEQUOTA_CHECKER_PTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc
{
namespace ibt
{
class ArticleQuotaChecker;
typedef boost::shared_ptr<libcsc::ibt::ArticleQuotaChecker> ArticleQuotaCheckerPtr;

} // end namespace ibt
} // end namespace libcsc

#endif // GUARD_LIBCSC_IBT_ARTICLEQUOTA_CHECKER_PTR_H
