#ifndef GUARD_THRIFTSERVERFRAMEWORK_H
#define GUARD_THRIFTSERVERFRAMEWORK_H

#include <boost/shared_ptr.hpp>
#include <thrift/protocol/BoostEncoder.h>
#include <log4cplus/logger.h>
#include "ithriftparameterproxyptr.h"
#include "thrift_definitions.h"


namespace basar {
	namespace cmnutil {
		class CmdLineTokenizer;
	}
}

namespace cscservice {
namespace infrastructure {

class ThriftServerFramework
{
public:
	virtual ~ThriftServerFramework();

	void injectLogger(log4cplus::Logger logger);
	void injectParameterProxy(cscservice::infrastructure::thrift::IThriftParameterProxyPtr proxy);

	void init();
	void serve();

	int32_t getMaxClients();
	int32_t getCurrentClients();
	
	static ThriftServerFramework* instance();
#ifndef WIN32
	static void handleSignal(int);
	static void forkCallback();
#endif

private:
	ThriftServerFramework();
	ThriftServerFramework(const ThriftServerFramework&);

	void reloadConfiguration();

#ifndef WIN32
	void setupSignalHandling();
	void handleSignalInst(int);
	void forkCallbackInst();
#endif

	apache::thrift::protocol::BoostEncoder::CodePage::CodePageEnum determineCodePage(const std::string& encoding) const;
	void setMaxClients(const int32_t forkLimit);

	apache::thrift::server::TServerFrameworkPtr						m_ServerFramework;
	apache::thrift::transport::TServerTransportPtr					m_ServerTransport;

	cscservice::infrastructure::thrift::IThriftParameterProxyPtr	m_ParameterProxy;
	log4cplus::Logger												m_Logger;

	static ThriftServerFramework*									m_Instance;
};

}
}

#endif // GUARD_THRIFTSERVERFRAMEWORK_H
