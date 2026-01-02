#ifndef GUARD_LIBCSC_I_HIERARCHY_LOGGER_PTR_H
#define GUARD_LIBCSC_I_HIERARCHY_LOGGER_PTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc
{
namespace discount
{
class IHierarchyLogger;
typedef boost::shared_ptr<libcsc::discount::IHierarchyLogger> IHierarchyLoggerPtr;

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_I_HIERARCHY_LOGGER_PTR_H
