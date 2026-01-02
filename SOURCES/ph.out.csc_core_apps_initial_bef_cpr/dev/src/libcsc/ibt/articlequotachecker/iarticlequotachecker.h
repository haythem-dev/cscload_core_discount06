#ifndef GUARD_LIBCSC_IBT_I_ARTICLEQUOTA_CHECKER_H
#define GUARD_LIBCSC_IBT_I_ARTICLEQUOTA_CHECKER_H

#include <libbasar_definitions.h>

namespace libcsc
{
namespace ibt
{
class IArticleQuotaChecker
{
public:
	virtual ~IArticleQuotaChecker() {}	

	virtual bool isArticleQuotaAvailable( const basar::Int16 localBranchNo, const basar::Int16 ibtBranchNo, const basar::Int32 articleNo, basar::Int32& remainingQty ) const = 0;
};

} // end namespace ibt
} // end namespace libcsc

#endif // GUARD_LIBCSC_IBT_I_ARTICLEQUOTA_CHECKER_H
