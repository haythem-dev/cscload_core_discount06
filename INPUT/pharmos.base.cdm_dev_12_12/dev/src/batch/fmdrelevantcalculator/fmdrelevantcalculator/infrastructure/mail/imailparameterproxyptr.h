#ifndef GUARD_IMAILPARAMETERPROXYPTR_H
#define GUARD_IMAILPARAMETERPROXYPTR_H

#include <boost/shared_ptr.hpp>

namespace fmdrelevantcalculator {
namespace infrastructure {
namespace mail {

	class IMailParameterProxy;

	typedef boost::shared_ptr<IMailParameterProxy> IMailParameterProxyPtr;

} // namespace mail 
} // namespace infrastructure
} // namespace fmdrelevantcalculator

#endif // GUARD_IMAILPARAMETERPROXYPTR_H
