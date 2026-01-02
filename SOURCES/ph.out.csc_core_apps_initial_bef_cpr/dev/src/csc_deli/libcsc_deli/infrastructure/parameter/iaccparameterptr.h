#ifndef GUARD_LIBCSC_DELI_INFRASTRUCTURE_PARAMETER_IACCPARAMETERPTR_H
#define GUARD_LIBCSC_DELI_INFRASTRUCTURE_PARAMETER_IACCPARAMETERPTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc_deli
{
namespace infrastructure
{
namespace parameter
{
    class IACCParameter;
    typedef boost::shared_ptr< IACCParameter > IACCParameterPtr;

} // end namespace parameter
} // end namespace infrastructure
} // end namespace libcsc_deli

#endif // GUARD_LIBCSC_DELI_INFRASTRUCTURE_PARAMETER_IACCPARAMETERPTR_H
