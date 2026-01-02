#ifndef GUARD_LIBCSC_IBT_ARTICLEQUOTA_CHECKER_H
#define GUARD_LIBCSC_IBT_ARTICLEQUOTA_CHECKER_H

#include <ibt/articlequotachecker/iarticlequotachecker.h>
#include <persistence/iaccessorptr.h>

namespace libcsc
{
namespace ibt
{
class ArticleQuotaChecker : public IArticleQuotaChecker
{
public:
	ArticleQuotaChecker();
	virtual ~ArticleQuotaChecker();

	void injectSelectAccessor( persistence::IAccessorPtr accessor );		

	virtual bool isArticleQuotaAvailable( const basar::Int16 localBranchNo, const basar::Int16 ibtBranchNo, const basar::Int32 articleNo, basar::Int32& remainingQty ) const;	

private:	

	persistence::IAccessorPtr			m_SelectAccessor;
};

} // end namespace ibt
} // end namespace libcsc

#endif // GUARD_LIBCSC_IBT_ARTICLEQUOTA_CHECKER_H
