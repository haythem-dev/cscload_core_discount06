#ifndef GUARD_MAILPARAMETERPROXYPTR_H
#define GUARD_MAILPARAMETERPROXYPTR_H

#include <boost/shared_ptr.hpp>

namespace ibtorderimport {
namespace infrastructure {
namespace mail {

	class MailParameterProxy;

	typedef boost::shared_ptr<MailParameterProxy> MailParameterProxyPtr;

}
}
}

#endif // GUARD_MAILPARAMETERPROXYPTR_H
