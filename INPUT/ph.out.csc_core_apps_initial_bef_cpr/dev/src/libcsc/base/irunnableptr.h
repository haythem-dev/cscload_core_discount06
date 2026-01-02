#ifndef GUARD_LIBCSC_BASE_IRUNNABLEPTR_H
#define GUARD_LIBCSC_BASE_IRUNNABLEPTR_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <boost/shared_ptr.hpp>

namespace libcsc {
namespace base {
	class IRunnable;
	typedef boost::shared_ptr< IRunnable > IRunnablePtr;
} // namespace base
} // namespace libcsc

#endif
