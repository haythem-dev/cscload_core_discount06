#ifndef GUARD_LIBCSC_I_ORDER_PARAMETER_GETTER_PTR_H
#define GUARD_LIBCSC_I_ORDER_PARAMETER_GETTER_PTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc
{
namespace parameter
{
class IOrderParameterGetter;
typedef boost::shared_ptr<libcsc::parameter::IOrderParameterGetter> IOrderParameterGetterPtr;

} // end namespace parameter
} // end namespace libcsc

#endif // GUARD_LIBCSC_I_ORDER_PARAMETER_GETTER_PTR_H
