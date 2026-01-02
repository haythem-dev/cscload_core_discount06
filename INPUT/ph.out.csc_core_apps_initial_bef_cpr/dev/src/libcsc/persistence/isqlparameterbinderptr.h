#ifndef GUARD_LIBCSC_PERSISTENCE_I_SQL_PARAMETER_BINDER_PTR_H
#define GUARD_LIBCSC_PERSISTENCE_I_SQL_PARAMETER_BINDER_PTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc
{
namespace persistence
{
class ISqlParameterBinder;
typedef boost::shared_ptr<libcsc::persistence::ISqlParameterBinder> ISqlParameterBinderPtr;

} // end namespace persistence
} // end namespace libcsc

#endif // GUARD_LIBCSC_PERSISTENCE_I_SQL_PARAMETER_BINDER_PTR_H
