#ifndef GUARD_LIBCSC_CREMA_COMPONENT_MANAGER_PTR_H
#define GUARD_LIBCSC_CREMA_COMPONENT_MANAGER_PTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc {
namespace crema {

class CremaComponentManager;
typedef boost::shared_ptr<libcsc::crema::CremaComponentManager> CremaComponentManagerPtr;

} // end namespace crema
} // end namespace libcsc

#endif // GUARD_LIBCSC_CREMA_COMPONENT_MANAGER_PTR_H
