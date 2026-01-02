#ifndef GUARD_LIBCSC_IBT_COMPONENT_MANAGER_PTR_H
#define GUARD_LIBCSC_IBT_COMPONENT_MANAGER_PTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc
{
namespace ibt
{
	class IbtComponentManager;
	typedef boost::shared_ptr<libcsc::ibt::IbtComponentManager> IbtComponentManagerPtr;

} // end namespace ibt
} // end namespace libcsc

#endif // GUARD_LIBCSC_IBT_COMPONENT_MANAGER_PTR_H
