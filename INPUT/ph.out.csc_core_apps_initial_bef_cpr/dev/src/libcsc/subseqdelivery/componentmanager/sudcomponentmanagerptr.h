#ifndef GUARD_LIBCSC_SUD_COMPONENT_MANAGER_PTR_H
#define GUARD_LIBCSC_SUD_COMPONENT_MANAGER_PTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc
{
namespace sud
{
class SudComponentManager;
typedef boost::shared_ptr<libcsc::sud::SudComponentManager> SudComponentManagerPtr;

} // end namespace sud
} // end namespace libcsc

#endif // GUARD_LIBCSC_SUD_COMPONENT_MANAGER_PTR_H
