#ifndef GUARD_LIBCSC_MSV3_COMPONENT_MANAGER_PTR_H
#define GUARD_LIBCSC_MSV3_COMPONENT_MANAGER_PTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc {
namespace msv3 {

class MSV3ComponentManager;
typedef boost::shared_ptr<libcsc::msv3::MSV3ComponentManager> MSV3ComponentManagerPtr;

} // end namespace msv3
} // end namespace libcsc

#endif // GUARD_LIBCSC_MSV3_COMPONENT_MANAGER_PTR_H
