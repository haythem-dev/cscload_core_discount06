#ifndef GUARD_LIBCSC_RETURNS_RETURNCOMPONENTMANAGERPTR_H
#define GUARD_LIBCSC_RETURNS_RETURNCOMPONENTMANAGERPTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc {
namespace returns {

	class ReturnComponentManager;
	typedef boost::shared_ptr<ReturnComponentManager> ReturnComponentManagerPtr;

} // namespace returns
} // namespace libcsc

#endif // GUARD_LIBCSC_RETURNS_RETURNCOMPONENTMANAGERPTR_H
