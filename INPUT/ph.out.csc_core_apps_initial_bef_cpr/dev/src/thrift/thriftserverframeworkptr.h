#ifndef GUARD_THRIFTSERVERFRAMEWORKPTR_H
#define GUARD_THRIFTSERVERFRAMEWORKPTR_H

#include <boost/shared_ptr.hpp>

namespace cscservice {
namespace infrastructure {

	class ThriftServerFramework;
	typedef boost::shared_ptr<ThriftServerFramework> ThriftServerFrameworkPtr;
}
}

#endif // GUARD_THRIFTSERVERFRAMEWORKPTR_H
