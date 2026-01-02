#ifndef THRIFT_TENCODER_H_
#define THRIFT_TENCODER_H_ 1

#include <string>

namespace apache {
namespace thrift {
namespace protocol {


class TEncoder
{
public:
	TEncoder() {}
	virtual ~TEncoder() {}

	virtual const std::string to_utf8(const std::string& str) const = 0;
	virtual const std::string from_utf8(const std::string& str) const = 0;
};


class TDummyEncoder : public TEncoder
{
public:
	TDummyEncoder() : TEncoder() {}
	virtual ~TDummyEncoder() {}

	const std::string to_utf8(const std::string& str) const { return str; }
	const std::string from_utf8(const std::string& str) const { return str; }
};


}
}
}

#endif // THRIFT_TENCODER_H_
