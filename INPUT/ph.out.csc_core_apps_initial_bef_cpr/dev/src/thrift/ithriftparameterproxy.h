#ifndef GUARD_ITHRIFTPARAMETERPROXY_H
#define GUARD_ITHRIFTPARAMETERPROXY_H

#include <stdint.h>
#include <string>

namespace cscservice {
namespace infrastructure {
namespace thrift {

class IThriftParameterProxy
{
public:
	virtual ~IThriftParameterProxy() {};

	virtual int32_t				getThriftPort() const = 0;
	virtual int32_t				getThriftForkLimit() const = 0;
	virtual const std::string	getThriftEncoding() const = 0;
	virtual bool				getDontFork() const = 0;
	virtual bool				getOnline() const = 0;

	virtual void				reloadConfiguration() = 0;
};

} // namespace thrift
} // namespace infrastructure
} // namespace cscservice

#endif // GUARD_ITHRIFTPARAMETERPROXY_H
