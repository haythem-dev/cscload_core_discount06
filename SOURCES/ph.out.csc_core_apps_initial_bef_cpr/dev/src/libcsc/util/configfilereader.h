#ifndef GUARD_LIBCSC_UTIL_CONFIGFILEREADER_H
#define GUARD_LIBCSC_UTIL_CONFIGFILEREADER_H

#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wtype-limits"
#endif
#include <boost/property_tree/ptree.hpp>
#ifdef __GNUC__
#pragma GCC diagnostic push
#endif

namespace libcsc {
namespace util {

class ConfigFileReader
{
public:
	enum ConfigFileFormatEnum
	{
		CONFIG_FORMAT_INI = 0,
		CONFIG_FORMAT_XML = 1
	};

	ConfigFileReader(const std::string& fileName, const enum ConfigFileFormatEnum = CONFIG_FORMAT_INI);
	virtual ~ConfigFileReader();
	
	bool				read();

	const std::string	getString(const std::string& key) const;
	const std::string	getEnvString(const std::string& key) const;
	int					getInt(const std::string& key) const;
	template<class T> T get(const std::string& key) const { return m_PropertyTree.get<T>(key); }

private:
	void				expandEnvVars(std::string& original) const;


	std::string 					m_FileName;
	ConfigFileFormatEnum			m_Format;
	boost::property_tree::ptree		m_PropertyTree;
};

} // end namespace util
} // end namespace libcsc


#endif	// GUARD_LIBCSC_UTIL_CONFIGFILEREADER_H
