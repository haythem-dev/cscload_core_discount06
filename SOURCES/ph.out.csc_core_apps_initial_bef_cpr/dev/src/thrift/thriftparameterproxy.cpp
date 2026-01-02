#include "thriftparameterproxy.h"
#include <boost/lexical_cast.hpp>
#include <util/configfilereader.h>
#include <libbasarcmnutil_cmdline.h>
#include "cscservice_definitions.h"

namespace cscservice {
namespace infrastructure {
namespace thrift {

ThriftParameterProxy::ThriftParameterProxy() : IThriftParameterProxy()
{
}

ThriftParameterProxy::~ThriftParameterProxy()
{
}

void ThriftParameterProxy::injectConfigFileReader(boost::shared_ptr<libcsc::util::ConfigFileReader> config)
{
	m_ConfigFileReader = config;
}

void ThriftParameterProxy::injectCmdLineArgs(boost::shared_ptr<basar::cmnutil::CmdLineTokenizer> cmdLine)
{
	m_CommandLine = cmdLine;
}

int32_t ThriftParameterProxy::getThriftPort() const
{
	
	return boost::lexical_cast<int32_t>(std::string(getenv("PORTNR")));
    //return m_ConfigFileReader->get<int32_t>(CONFIG_THRIFT_PORT);
}

int32_t ThriftParameterProxy::getThriftForkLimit() const
{
	return m_ConfigFileReader->get<int32_t>(CONFIG_THRIFT_FORK_LIMIT);
}

const std::string ThriftParameterProxy::getThriftEncoding() const
{
	return	m_ConfigFileReader->getString(CONFIG_THRIFT_ENCODING);
}

bool ThriftParameterProxy::getOnline() const
{
	return false;
}

bool ThriftParameterProxy::getDontFork() const
{
	return m_CommandLine->isParam(PARAM_DONTFORK);
}

void ThriftParameterProxy::reloadConfiguration()
{
	m_ConfigFileReader->read();
}


} // namespace thrift
} // namespace infrastructure
} // namespace cscservice
