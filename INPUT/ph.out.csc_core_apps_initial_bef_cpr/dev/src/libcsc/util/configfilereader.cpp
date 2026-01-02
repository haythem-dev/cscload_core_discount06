#include "configfilereader.h"
#include <iostream>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>


namespace libcsc {
namespace util {

ConfigFileReader::ConfigFileReader(const std::string& fileName, const enum ConfigFileFormatEnum fmt) :
	m_FileName(fileName),
	m_Format(fmt)
{
}

ConfigFileReader::~ConfigFileReader()
{
}

bool ConfigFileReader::read()
{
	bool retVal = true;

	switch (m_Format)
	{
		case CONFIG_FORMAT_INI:
		{
			try
			{
				boost::property_tree::ini_parser::read_ini(m_FileName, m_PropertyTree);
			}
			catch (const boost::property_tree::ini_parser::ini_parser_error& e)
			{
				std::cout << e.what() << std::endl;
				retVal = false;
			}
			break;
		}
		case CONFIG_FORMAT_XML:
		{
			try
			{
				boost::property_tree::xml_parser::read_xml(m_FileName, m_PropertyTree);
			}
			catch (const boost::property_tree::xml_parser::xml_parser_error& e)
			{
				std::cout << e.what() << std::endl;
				retVal = false;
			}
			break;
		}
		default:
			break;
	}
	return retVal;
}

const std::string ConfigFileReader::getString(const std::string& key) const
{
	std::string retVal;
	try
	{
		retVal = m_PropertyTree.get<std::string>(key);
	}
	catch (const boost::property_tree::ptree_error& e)
	{
		std::cout << e.what() << std::endl;
	}
	return retVal;
}

const std::string ConfigFileReader::getEnvString(const std::string& key) const
{
	std::string value = getString(key);
	expandEnvVars(value);
	return value;
}

int ConfigFileReader::getInt(const std::string& key) const
{
	int retVal = 0;
	try
	{
		retVal = m_PropertyTree.get<int>(key);
	}
	catch (const boost::property_tree::ptree_error& e)
	{
		std::cout << e.what() << std::endl;
	}
	return retVal;
}

void ConfigFileReader::expandEnvVars(std::string& original) const
{
	const boost::regex envscan("\\$([0-9A-Za-z_]*)");
	const boost::sregex_iterator end;
	typedef std::list<std::pair<const std::string,const std::string> > StringPairList;
	StringPairList replacements;

	for (boost::sregex_iterator rit(original.begin(), original.end(), envscan); rit != end; ++rit)
	{
		replacements.push_back(std::make_pair((*rit)[0],(*rit)[1]));
	}

	for (StringPairList::const_iterator lit = replacements.begin(); lit != replacements.end(); ++lit)
	{
		const char* expanded = std::getenv(lit->second.c_str());
		if (expanded == NULL)
			continue;
		boost::replace_all(original, lit->first, expanded);
	}
}



} // end namespace util
} // end namespace libcsc


