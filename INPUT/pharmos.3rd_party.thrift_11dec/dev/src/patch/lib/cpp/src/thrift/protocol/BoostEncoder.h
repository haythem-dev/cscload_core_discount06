#ifndef THRIFT_TBOOSTENCODER_H_
#define THRIFT_TBOOSTENCODER_H_ 1

#include <thrift/protocol/TEncoder.h>
#include <boost/locale/encoding.hpp>

namespace apache {
namespace thrift {
namespace protocol {


class BoostEncoder : public TEncoder
{
	//IMPORTANT: CodePageEnum and CODEPAGE_NAME need to be in sync (i.e. index in enum needs to reference proper name)
public:
	struct CodePage
	{
		enum CodePageEnum
		{
			WEST,
			CYRILLIC,
			EAST
		};
	};

private:
	static const char* const CODEPAGE_NAME[];
	
public:
	BoostEncoder(const BoostEncoder::CodePage::CodePageEnum _codepage);

	virtual ~BoostEncoder();

	const std::string to_utf8(const std::string& str) const;

	const std::string from_utf8(const std::string& str) const;

private:
	std::string m_CodePage;
};


}
}
}

#endif // THRIFT_TBOOSTENCODER_H_
