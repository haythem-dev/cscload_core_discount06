#ifndef GUARD_LIBCSC_I_SESSION_PARAMETER_GETTER_PTR_H
#define GUARD_LIBCSC_I_SESSION_PARAMETER_GETTER_PTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc
{
namespace parameter
{
class ISessionParameterGetter;
typedef boost::shared_ptr<libcsc::parameter::ISessionParameterGetter> ISessionParameterGetterPtr;

} // end namespace parameter
} // end namespace libcsc

#endif // GUARD_LIBCSC_I_SESSION_PARAMETER_GETTER_PTR_H
