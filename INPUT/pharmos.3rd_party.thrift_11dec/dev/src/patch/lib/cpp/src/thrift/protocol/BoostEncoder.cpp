#include <thrift/protocol/BoostEncoder.h>
#include <thrift/Thrift.h>

namespace apache {
namespace thrift {
namespace protocol {

    const char* const BoostEncoder::CODEPAGE_NAME[] =
	{
#ifdef WIN32
		"CP1252",     // ANSI - Latin I
		"CP1251",     // ANSI - Cyrillic
		"CP1250"      // ANSI - Central European
#else
		"ISO-8859-15",      // ISO-8859-15 Latin 9
		"ISO-8859-5",       // ISO-8859-5  Cyrillic
		"ISO-8859-2"        // ISO-8859-2  Central Europe
#endif
     };

    BoostEncoder::BoostEncoder(const BoostEncoder::CodePage::CodePageEnum _codepage) :
		TEncoder()
	{
        if ( sizeof(CODEPAGE_NAME) / sizeof(CODEPAGE_NAME[0]) <= static_cast<unsigned int>(_codepage) )
        {
            throw thrift::TException("BoostEncoder::BoostEncoder: Unknown codepage requested");
        }

        m_CodePage = CODEPAGE_NAME[_codepage];

	}

    BoostEncoder::~BoostEncoder()
    {
    }

    const std::string BoostEncoder::to_utf8(const std::string& str) const
    {
        return boost::locale::conv::to_utf<char>(str, m_CodePage);
    }

    const std::string BoostEncoder::from_utf8(const std::string& str) const
	{
		return boost::locale::conv::from_utf(str, m_CodePage);
	}

}
}
}