#ifndef GUARD_LIBCSC_SUD_I_WORKUP_COMPLETED_CHECKER_PTR_H
#define GUARD_LIBCSC_SUD_I_WORKUP_COMPLETED_CHECKER_PTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc
{
namespace sud
{
class IWorkupCompletedChecker;
typedef boost::shared_ptr<libcsc::sud::IWorkupCompletedChecker> IWorkupCompletedCheckerPtr;

} // end namespace sud
} // end namespace libcsc

#endif // GUARD_LIBCSC_SUD_I_WORKUP_COMPLETED_CHECKER_PTR_H
