#ifndef THRIFT_TENCODEDPROTOCOL_H_
#define THRIFT_TENCODEDPROTOCOL_H_ 1

#include <thrift/protocol/TEncoder.h>
#include <thrift/protocol/TProtocolDecorator.h>

namespace apache {
namespace thrift {
namespace protocol {

class TEncodedProtocol : public TProtocolDecorator
{
public:
	TEncodedProtocol(boost::shared_ptr<TProtocol> _protocol, boost::shared_ptr<TEncoder> _encoder) :
		TProtocolDecorator(_protocol),
		m_Encoder(_encoder)
	{
	}

	virtual ~TEncodedProtocol()
	{
	}

	uint32_t writeString_virt(const std::string& str)
	{
		std::string utf8str = m_Encoder->to_utf8(str);
		return TProtocolDecorator::writeString_virt(utf8str);
	}
	
	uint32_t readString_virt(std::string& str)
	{
		std::string utf8str;
		uint32_t ret = TProtocolDecorator::readString_virt(utf8str);
		str = m_Encoder->from_utf8(utf8str);
		return ret;
	}

private:
	const boost::shared_ptr<TEncoder> m_Encoder;
};

class TEncodedProtocolFactory : public TProtocolFactory
{
public:
	TEncodedProtocolFactory(boost::shared_ptr<TProtocolFactory> _factory, boost::shared_ptr<TEncoder> _encoder) :
		m_WrappedFactory(_factory),
		m_Encoder(_encoder)
	{
	}

	virtual ~TEncodedProtocolFactory()
	{
	}

	boost::shared_ptr<TProtocol> getProtocol(boost::shared_ptr<TTransport> trans)
	{
		boost::shared_ptr<TProtocol> wrappedProtocol = m_WrappedFactory->getProtocol(trans);
		return boost::shared_ptr<TProtocol>(new TEncodedProtocol(wrappedProtocol, m_Encoder));
	}

private:	
	boost::shared_ptr<TProtocolFactory> m_WrappedFactory;
	const boost::shared_ptr<TEncoder>	m_Encoder;
};

}
}
}

#endif // THRIFT_TMULTIPLEXEDPROTOCOL_H_
