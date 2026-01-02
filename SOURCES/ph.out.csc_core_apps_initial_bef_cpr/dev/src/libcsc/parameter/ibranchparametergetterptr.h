#ifndef GUARD_LIBCSC_I_BRANCH_PARAMETER_GETTER_PTR_H
#define GUARD_LIBCSC_I_BRANCH_PARAMETER_GETTER_PTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc
{
namespace parameter
{
class IBranchParameterGetter;
typedef boost::shared_ptr<libcsc::parameter::IBranchParameterGetter> IBranchParameterGetterPtr;

} // end namespace parameter
} // end namespace libcsc

#endif // GUARD_LIBCSC_I_BRANCH_PARAMETER_GETTER_PTR_H
