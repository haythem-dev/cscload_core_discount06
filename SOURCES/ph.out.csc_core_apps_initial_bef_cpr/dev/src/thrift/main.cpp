#include <boost/make_shared.hpp>
#include <libbasarcmnutil_bstring.h>
#include <libbasarcmnutil_cmdline.h>

#include <util/configfilereader.h>
#include <logger/loggerpool.h>

#include "thriftserverframework.h"
#include "thriftserverframeworkptr.h"
#include "ithriftparameterproxyptr.h"
#include "thriftparameterproxyptr.h"
#include "thriftparameterproxy.h"
#include "cscservice_definitions.h"
#ifndef WIN32
#include "gitversioninfo.h"
#endif

extern "C"
{
	extern const char versioninfo[];
}

//--------------------------------------------------------------------------------------------------
// main
//--------------------------------------------------------------------------------------------------

int main(int argc, char *argv[])
{
	boost::shared_ptr<basar::cmnutil::CmdLineTokenizer> args = boost::make_shared<basar::cmnutil::CmdLineTokenizer>();
	args->setCmdLine(argc, argv);

#ifndef WIN32
	if (args->isParam("-version"))
	{
		std::cout << versioninfo << std::endl;
		std::cout << GitVersionInfo::instance() << std::endl;
		exit( 0 );
	}		
#endif
	
	basar::VarString iniFile = getenv("INI_PATH");
	if (iniFile.empty())
	{
		iniFile = "../ini";
	}
	iniFile += "/cscservice.ini";
	boost::shared_ptr<libcsc::util::ConfigFileReader> configFileReader = boost::make_shared<libcsc::util::ConfigFileReader>(iniFile);
	configFileReader->read();

	cscservice::infrastructure::thrift::ThriftParameterProxyPtr parameterProxy;
	parameterProxy = boost::make_shared<cscservice::infrastructure::thrift::ThriftParameterProxy>();
	parameterProxy->injectCmdLineArgs(args);
	parameterProxy->injectConfigFileReader(configFileReader);

	cscservice::infrastructure::ThriftServerFrameworkPtr serverFramework;
	serverFramework = cscservice::infrastructure::ThriftServerFrameworkPtr(cscservice::infrastructure::ThriftServerFramework::instance());
	serverFramework->injectLogger(libcsc::LoggerPool::getLoggerSession());
	serverFramework->injectParameterProxy(parameterProxy);
	serverFramework->init();
	serverFramework->serve();
	return 0;
}
