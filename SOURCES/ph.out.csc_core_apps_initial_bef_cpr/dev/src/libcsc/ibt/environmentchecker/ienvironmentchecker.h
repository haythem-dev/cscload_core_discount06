#ifndef GUARD_LIBCSC_IBT_I_ENVIRONMENT_CHECKER_H
#define GUARD_LIBCSC_IBT_I_ENVIRONMENT_CHECKER_H

#include <libbasar_definitions.h>

namespace libcsc
{
namespace ibt
{
class IEnvironmentChecker
{
public:
	virtual ~IEnvironmentChecker() {}

	virtual bool isUseOtherDB( const basar::Int16 branchNo, const basar::Int32 articleNo ) const = 0;
};

} // end namespace ibt
} // end namespace libcsc

#endif // GUARD_LIBCSC_I_IBT_ENVIRONMENT_CHECKER_H
