#ifndef GUARD_LIBCSC_DELI_INFRASTRUCTURE_PARAMETER_ACCPARAMETERPTR_H
#define GUARD_LIBCSC_DELI_INFRASTRUCTURE_PARAMETER_ACCPARAMETERPTR_H

#include <boost/shared_ptr.hpp>

namespace log4cplus 
{
    class Logger;
}

namespace libcsc_deli
{
namespace infrastructure
{
namespace parameter
{
	class ACCParameter;
    typedef boost::shared_ptr< ACCParameter > ACCParameterPtr;

} // end namespace parameter
} // end namespace infrastructure
} // end namespace libcsc_deli

#endif // GUARD_LIBCSC_DELI_INFRASTRUCTURE_PARAMETER_ACCPARAMETERPTR_H
