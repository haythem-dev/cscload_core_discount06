#ifndef GUARD_LIBCSC_CSCORDER_COMPONENT_MANAGER_PTR_H
#define GUARD_LIBCSC_CSCORDER_COMPONENT_MANAGER_PTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc
{
namespace cscorder
{
class CSCOrderComponentManager;
typedef boost::shared_ptr<libcsc::cscorder::CSCOrderComponentManager> CSCOrderComponentManagerPtr;

} // end namespace cscorder
} // end namespace libcsc

#endif // GUARD_LIBCSC_CSCORDER_COMPONENT_MANAGER_PTR_H
