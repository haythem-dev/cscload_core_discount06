#ifndef GUARD_THRIFT_DEFINITIONS_H
#define GUARD_THRIFT_DEFINITIONS_H

namespace apache {
	namespace thrift {

		class TProcessor;
		typedef boost::shared_ptr<TProcessor> TProcessorPtr;

		namespace server {
			class TServerFramework;
			typedef boost::shared_ptr<TServerFramework> TServerFrameworkPtr;
		}

		namespace transport {
			class TServerTransport;
			typedef boost::shared_ptr<TServerTransport> TServerTransportPtr;

			class TTransportFactory;
			typedef boost::shared_ptr<TTransportFactory> TTransportFactoryPtr;
		}

		namespace protocol {
			class TProtocolFactory;
			typedef boost::shared_ptr<TProtocolFactory> TProtocolFactoryPtr;

			class TEncoder;
			typedef boost::shared_ptr<TEncoder> TEncoderPtr;
		}
	}
}

#endif // GUARD_THRIFT_DEFINITIONS_H
