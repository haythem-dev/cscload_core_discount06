#include "thriftserverframework.h"
#include "ithriftparameterproxyptr.h"
#include "ithriftparameterproxy.h"
#include <boost/make_shared.hpp>

#include <thrift/protocol/TEncodedProtocol.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/protocol/BoostEncoder.h>
#include <thrift/server/TSimpleServer.h>
#ifndef WIN32
#include <thrift/server/TSimpleForkableServer.h>
#include <thrift/transport/TForkingServerSocket.h>
#endif
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

#include "cscservicebatchhandler.hpp"
#include "cscserviceonlinehandler.hpp"

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

namespace cscservice {
namespace infrastructure {

ThriftServerFramework* ThriftServerFramework::m_Instance = NULL;

ThriftServerFramework* ThriftServerFramework::instance()
{
	if (NULL == m_Instance)
		m_Instance = new ThriftServerFramework();
	return m_Instance;
}


ThriftServerFramework::ThriftServerFramework()
{
#ifndef WIN32
	setupSignalHandling();
#endif
}

ThriftServerFramework::~ThriftServerFramework()
{
	m_ServerTransport.reset();
}

void ThriftServerFramework::injectLogger(log4cplus::Logger logger)
{
	m_Logger = logger;
}

void ThriftServerFramework::injectParameterProxy(cscservice::infrastructure::thrift::IThriftParameterProxyPtr proxy)
{
	m_ParameterProxy = proxy;
}


void ThriftServerFramework::init()
{
	int32_t portNo = m_ParameterProxy->getThriftPort();
	std::string encoding = m_ParameterProxy->getThriftEncoding();
	int32_t forkLimit = m_ParameterProxy->getThriftForkLimit();

	std::stringstream s;
	s << "ThriftServerFramework::init(): starting on port <" << portNo << ">, encoding <" << encoding << ">, forklimit <" << forkLimit << ">";
	BLOG_INFO(m_Logger, s.str());
	
	BoostEncoder::CodePage::CodePageEnum codePage = determineCodePage(encoding);

	TProcessorPtr			processor;
	TTransportFactoryPtr	transportFactory		= boost::make_shared<TBufferedTransportFactory>();
	TProtocolFactoryPtr		binaryProtocolFactory	= boost::make_shared<TBinaryProtocolFactory>();
	TEncoderPtr				encoder 				= boost::make_shared<BoostEncoder>(codePage);
	TProtocolFactoryPtr 	encodedProtocolFactory	= boost::make_shared<TEncodedProtocolFactory>(binaryProtocolFactory, encoder);

	if (true == m_ParameterProxy->getOnline())
	{
		boost::shared_ptr<CscServiceOnlineHandler> handler(new CscServiceOnlineHandler());
		handler->setParentPort(portNo);
		processor = boost::make_shared<csc::service::CscServiceOnlineProcessor>(handler);
	}
	else
	{
		boost::shared_ptr<CscServiceBatchHandler> handler(new CscServiceBatchHandler());
		handler->setParentPort(portNo);
		processor = boost::make_shared<csc::service::CscServiceBatchProcessor>(handler);
	}
#ifndef WIN32
	if (true ==  m_ParameterProxy->getDontFork())
	{
#endif
		m_ServerTransport = boost::make_shared<TServerSocket>(portNo);
		m_ServerFramework = boost::make_shared<TSimpleServer>(processor, m_ServerTransport, transportFactory, encodedProtocolFactory);
#ifndef WIN32
	}
	else
	{
		m_ServerTransport = boost::make_shared<TForkingServerSocket>(portNo);
		(boost::dynamic_pointer_cast<TForkingServerSocket>(m_ServerTransport))->setForkCallback(&ThriftServerFramework::forkCallback);
		m_ServerFramework = boost::make_shared<TSimpleForkableServer>(processor, m_ServerTransport, transportFactory, encodedProtocolFactory);

		setMaxClients(forkLimit);

		std::stringstream s;
		s << "fork limit was set to " << getMaxClients();
		BLOG_INFO(m_Logger, s.str());
	}
#endif
}


void ThriftServerFramework::serve()
{
	m_ServerFramework->serve();
}


void ThriftServerFramework::reloadConfiguration()
{
	int32_t oldForkLimit = m_ParameterProxy->getThriftForkLimit();
	m_ParameterProxy->reloadConfiguration();
	int32_t newForkLimit = m_ParameterProxy->getThriftForkLimit();

	std::stringstream s;
	s << "ThriftServerFramework::reloadConfiguration(): Changing MaxClients from <" << oldForkLimit << "> to <" << newForkLimit << ">";
	BLOG_DEBUG(m_Logger, s.str());

	setMaxClients(newForkLimit);
}

int32_t ThriftServerFramework::getMaxClients()
{
#ifndef WIN32
	return (boost::dynamic_pointer_cast<TForkingServerSocket>(m_ServerTransport))->getMaxClients();
#else
	return 0;
#endif
}

int32_t ThriftServerFramework::getCurrentClients()
{
#ifndef WIN32
	return (boost::dynamic_pointer_cast<TForkingServerSocket>(m_ServerTransport))->getCurrentClients();
#else
	return 0;
#endif
}


void ThriftServerFramework::setMaxClients(const int32_t forkLimit)
{
	std::stringstream s;
	s << "ThriftServerFramework::setForkLimit(" << forkLimit << ")";
	BLOG_INFO(m_Logger, s.str());
#ifndef WIN32
	(boost::dynamic_pointer_cast<TForkingServerSocket>(m_ServerTransport))->setMaxClients(forkLimit);
#endif
}


BoostEncoder::CodePage::CodePageEnum ThriftServerFramework::determineCodePage(const std::string& encoding) const
{
	BoostEncoder::CodePage::CodePageEnum codePage = BoostEncoder::CodePage::WEST;

#ifdef WIN32
	if ("CP1252" == encoding)
		codePage = BoostEncoder::CodePage::WEST;
	if ("CP1251" == encoding)
		codePage = BoostEncoder::CodePage::CYRILLIC;
#else
	if ("ISO-8859-15" == encoding)
		codePage = BoostEncoder::CodePage::WEST;
	if ("ISO-8859-5" == encoding)
		codePage = BoostEncoder::CodePage::CYRILLIC;
#endif
	return codePage;
}

#ifndef WIN32

void ThriftServerFramework::handleSignal(int sig)
{
	instance()->handleSignalInst(sig);
}

void ThriftServerFramework::handleSignalInst(int sig)
{
	switch (sig)
	{
		case SIGUSR1:
			if (1 == getppid())
			{
				std::stringstream s;
				s << "cscservice parent [pid=" << getpid() << ", ppid=" << getppid()
					<< "]: SIGUSR1 catched -> change config!!!" << std::endl;
				BLOG_INFO(m_Logger, s.str());
				this->reloadConfiguration();
			}
			else
			{
				std::stringstream s;
				s << "cscservice child [pid=" << getpid() << ", ppid=" << getppid()
					<< "]: SIGUSR1 catched -> ignore!!!" << std::endl;
				BLOG_INFO(m_Logger, s.str());
			}
			break;
		case SIGUSR2:
			BLOG_INFO(m_Logger, "cscservice: SIGUSR2 catched");
			break;
		default:
			BLOG_INFO(m_Logger, "cscservice: other signal catched");
			break;
	}
}

void ThriftServerFramework::setupSignalHandling()
{
	//cheap signal handling
	struct sigaction act;
	act.sa_handler = ThriftServerFramework::handleSignal;

	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;

	sigaction(SIGUSR1, &act, 0); //register handling of SIGUSR1
	sigaction(SIGUSR2, &act, 0); //register handling of SIGUSR2 - same handler as above
}

void ThriftServerFramework::forkCallback()
{
	instance()->forkCallbackInst();
}

void ThriftServerFramework::forkCallbackInst()
{
	std::stringstream s;
	s << "ThriftServerFramework: current clients: " << getCurrentClients() << ", max clients: " << getMaxClients();
	
	if (getCurrentClients() == getMaxClients())
	{
		BLOG_WARN(m_Logger, s.str());
	}
	else
	{
		BLOG_TRACE(m_Logger, s.str());
	}
}

#endif 

}
}
