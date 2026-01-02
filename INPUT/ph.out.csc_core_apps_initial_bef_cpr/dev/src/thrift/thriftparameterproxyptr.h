#ifndef GUARD_THRIFTPARAMETERPROXYPTR_H
#define GUARD_THRIFTPARAMETERPROXYPTR_H

#include <boost/shared_ptr.hpp>

namespace cscservice {
namespace infrastructure {
namespace thrift {

	class ThriftParameterProxy;

	typedef boost::shared_ptr<ThriftParameterProxy> ThriftParameterProxyPtr;
}
}
}

#endif // GUARD_THRIFTPARAMETERPROXYPTR_H
