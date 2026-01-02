#ifndef GUARD_ITHRIFTPARAMETERPROXYPTR_H
#define GUARD_ITHRIFTPARAMETERPROXYPTR_H

#include <boost/shared_ptr.hpp>

namespace cscservice {
namespace infrastructure {
namespace thrift {

	class IThriftParameterProxy;

	typedef boost::shared_ptr<IThriftParameterProxy> IThriftParameterProxyPtr;
}
}
}

#endif // GUARD_ITHRIFTPARAMETERPROXYPTR_H
