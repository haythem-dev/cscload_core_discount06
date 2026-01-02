#ifndef GUARD_THRIFTPARAMETERPROXY_H
#define GUARD_THRIFTPARAMETERPROXY_H

#include "ithriftparameterproxy.h"
#include <boost/shared_ptr.hpp>

namespace basar {
	namespace cmnutil {
		class CmdLineTokenizer;
	}
}

namespace libcsc {
	namespace util {
		class ConfigFileReader;
	}
}

namespace cscservice {
namespace infrastructure {
namespace thrift {

class ThriftParameterProxy : public IThriftParameterProxy
{
public:
	ThriftParameterProxy();
	virtual ~ThriftParameterProxy();

	void injectConfigFileReader(boost::shared_ptr<libcsc::util::ConfigFileReader> config);
	void injectCmdLineArgs(boost::shared_ptr<basar::cmnutil::CmdLineTokenizer> cmdLine);

	virtual int32_t				getThriftPort() const;
	virtual int32_t				getThriftForkLimit() const;
	virtual const std::string	getThriftEncoding() const;
	virtual bool				getDontFork() const;
	virtual bool				getOnline() const;

	virtual void				reloadConfiguration();

private:
	ThriftParameterProxy(const ThriftParameterProxy&);
	ThriftParameterProxy& operator=(const ThriftParameterProxy&);

	boost::shared_ptr<libcsc::util::ConfigFileReader>	m_ConfigFileReader;
	boost::shared_ptr<basar::cmnutil::CmdLineTokenizer>	m_CommandLine;
};

} // namespace thrift
} // namespace infrastructure
} // namespace cscservice

#endif // GUARD_THRIFTPARAMETERPROXY_H
