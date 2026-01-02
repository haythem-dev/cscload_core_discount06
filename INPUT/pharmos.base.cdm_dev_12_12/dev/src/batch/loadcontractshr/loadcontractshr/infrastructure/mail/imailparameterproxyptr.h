#ifndef GUARD_IMAILPARAMETERPROXYPTR_H
#define GUARD_IMAILPARAMETERPROXYPTR_H

#include <boost/shared_ptr.hpp>

namespace loadcontractshr {
namespace infrastructure {
namespace mail {

	class IMailParameterProxy;

	typedef boost::shared_ptr<IMailParameterProxy> IMailParameterProxyPtr;

} // namespace mail 
} // namespace infrastructure
} // namespace loadcontractshr

#endif // GUARD_IMAILPARAMETERPROXYPTR_H
