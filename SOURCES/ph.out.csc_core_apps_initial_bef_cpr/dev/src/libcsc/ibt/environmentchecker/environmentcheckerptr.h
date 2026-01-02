#ifndef GUARD_LIBCSC_IBT_ENVIRONMENT_CHECKER_PTR_H
#define GUARD_LIBCSC_IBT_ENVIRONMENT_CHECKER_PTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc
{
namespace ibt
{
class EnvironmentChecker;
typedef boost::shared_ptr<libcsc::ibt::EnvironmentChecker> EnvironmentCheckerPtr;

} // end namespace ibt
} // end namespace libcsc

#endif // GUARD_LIBCSC_IBT_ENVIRONMENT_CHECKER_PTR_H
