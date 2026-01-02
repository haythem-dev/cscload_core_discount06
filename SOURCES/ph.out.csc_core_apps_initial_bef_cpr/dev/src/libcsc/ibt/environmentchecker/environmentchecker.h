#ifndef GUARD_LIBCSC_IBT_ENVIRONMENT_CHECKER_H
#define GUARD_LIBCSC_IBT_ENVIRONMENT_CHECKER_H

#include <ibt/environmentchecker/ienvironmentchecker.h>
#include <persistence/iaccessorptr.h>

namespace libcsc
{
namespace ibt
{
class EnvironmentChecker : public IEnvironmentChecker
{
public:
	EnvironmentChecker();
	virtual ~EnvironmentChecker();

	void injectSelectAccessor( persistence::IAccessorPtr accessor );

	virtual bool isUseOtherDB( const basar::Int16 branchNo, const basar::Int32 articleNo ) const;

private:
	persistence::IAccessorPtr			m_SelectAccessor;
};

} // end namespace ibt
} // end namespace libcsc

#endif // GUARD_LIBCSC_IBT_ENVIRONMENT_CHECKER_H
