//-----------------------------------------------------------------------------------------------------//
//! \file  importmedreg
// \brief  application class (main) for import medreg components
// \author Thomas Arnold / Bjoern Muenschke(QT Part)
// \date   09.05.2022 / 19.05.2022
// open ssl example
// xxx-https://stackoverflow.com/questions/41229601/openssl-in-c-socket-connection-https-client
// xxx-https://gist.github.com/raschupkin/88a1ff730bcfa1c5a12d5804bbf451c9
// QT File Open/Read/Write etc.
// xxx-https://www.youtube.com/watch?v=i4ciL8TxW_s
//-----------------------------------------------------------------------------------------------------//

//-----------------------------------------------------------------------------------------------------//
// includes
//-----------------------------------------------------------------------------------------------------//
#include <string>
#include <map>
#include "importmedreg.h"

#include <QtCore/QDebug>
#include <QtCore/QFile>
#include <QtCore/QString>

#include <iostream>
#include <fstream>
#include <sstream>

#define OPT_LOAD_MEDREG   "--load_medreg"
#define OPT_PROPERTIES    "--properties"
#define OPT_TOKEN_REFRESH "--token_refresh"
#define OPT_TOKEN_STORE   "--token_store"

//-----------------------------------------------------------------------------------------------------//
// namespace
//-----------------------------------------------------------------------------------------------------//
namespace importmedreg
{
	//-------------------------------------------------------------------------------------------------//
	//! standard constructor of importmedred
	//-------------------------------------------------------------------------------------------------//
	ImportMedReg::ImportMedReg() : m_Logger(importmedreg::LoggerPool::getLoggerImportMedReg())
	{
		METHODNAME_DEF(ImportMedReg, ImportMedReg);
		BLOG_TRACE_METHOD(getLogger(), fun);
	}

	//-------------------------------------------------------------------------------------------------//
	//! standard destructor of importmedred
	//-------------------------------------------------------------------------------------------------//
	ImportMedReg::~ImportMedReg()
	{
		METHODNAME_DEF(ImportMedReg, ~ImportMedReg);
		BLOG_TRACE_METHOD(getLogger(), fun);
	}

	//-------------------------------------------------------------------------------------------------//
	//! internal function to get the application logger
	//-------------------------------------------------------------------------------------------------//
	const log4cplus::Logger& ImportMedReg::getLogger() const
	{
		return m_Logger;
	}

	//-------------------------------------------------------------------------------------------------//
	//! initialization with handed over arguments
	//-------------------------------------------------------------------------------------------------//
	int ImportMedReg::init(std::string path, int argc, char* argv[])
	{
		METHODNAME_DEF(ImportMedReg, init);
		BLOG_TRACE_METHOD(getLogger(), fun);

		// take over the base path
		m_strBasePath = path;
		// parse and transfer the command line params into system
		bool ret = this->parseCommandLine(argc, argv);

		if ((ret == false) || (m_cmdParams.count(OPT_TOKEN_STORE) == 0) || (m_cmdParams[OPT_TOKEN_STORE].length() == 0))
		{
			this->printUsage();
			return RETURN_RESULT_WRONG_PARAMETERS_ERROR;
		}

		// Set token store into key managaer to read the current tokens before loading the properties
		if ((m_cmdParams.count(OPT_TOKEN_STORE)) && (m_cmdParams[OPT_TOKEN_STORE].length() > 0))
		{
			std::string kfile = m_strBasePath + "ini/" + m_cmdParams[OPT_TOKEN_STORE];
			printf("Token File: %s\n", kfile.c_str());
			m_keyManager.setKeyManagerFile(kfile);
			if (m_keyManager.readTokensFromFile() == false)
			{
				return RETURN_RESULT_READ_TOKENFILE_ERROR;
			}
		}
		else
		{
			this->printUsage();
			return RETURN_RESULT_WRONG_PARAMETERS_ERROR;
		}
		// read the properties for getting the data from webservice
		if ((m_cmdParams.count(OPT_PROPERTIES)) && (m_cmdParams[OPT_PROPERTIES].length() > 0))
		{
			std::string pfile = m_strBasePath + "ini/" + m_cmdParams[OPT_PROPERTIES];
			printf("Properties File: %s\n", pfile.c_str());
			if (this->loadProperties(pfile, m_cmdParams[OPT_LOAD_MEDREG]) == false)
			{
				return RETURN_RESULT_READ_PROPERTIESFILE_ERROR;
			}
		}
		else
		{
			this->printUsage();
			return RETURN_RESULT_WRONG_PARAMETERS_ERROR;
		}

		return RETURN_RESULT_INIT_OK;
	}

	//-------------------------------------------------------------------------------------------------//
	//! keymanager handler
	//-------------------------------------------------------------------------------------------------//
	int ImportMedReg::runKeyManager()
	{
		METHODNAME_DEF(ApplCtrlImpl, runKeyManager);
		BLOG_TRACE_METHOD(getLogger(), fun);

		int ret = RETURN_RESULT_NO_ACTION;
		// connect the KeyManager to obtain access-refresh token pair
		if (this->doRefreshTokenPair())
		{
			LOG4CPLUS_DEBUG(m_Logger, "KeyManager action enabled");
			if (m_blnWebProxy == true)
			{
				LOG4CPLUS_DEBUG(m_Logger, "Establishing Internet proxy for KeyManager call...");
				// phoenix proxy needs to be used for connecting to internet
				if (m_objWebKey.proxy(m_strWebProxyServer, atoi(m_strWebProxyPort.c_str()), m_strWebProxyAuth, m_strWebProxyCred) == false)
				{
					return RETURN_RESULT_PROXY_ERROR;
				}
			}
			// use the properties to set user and credentials
			m_objWebKey.authorize(m_strWebKeyAuth, m_strWebKeyCred);
			LOG4CPLUS_DEBUG(m_Logger, "KeyManager server connecting...");
			if (m_objWebKey.connect(m_strWebKeyServer, atoi(m_strWebKeyPort.c_str())) == true)
			{
				LOG4CPLUS_DEBUG(m_Logger, "KeyManager request calling...");
				if (m_objWebKey.request(m_strWebKeyType, m_strWebKeyRequest, m_strWebKeyBody, m_strWebKeyBodyType) == true)
				{
					std::string req = m_objWebKey.getLastRequest();
					writeProtocol(m_strWebKeyProtocolFile, "--------------\nKEY REQUEST\n--------------\n" + req);
					std::string resp = m_objWebKey.getLastResponse();
					writeProtocol(m_strWebKeyProtocolFile, "--------------\nKEY RESPONSE\n--------------\n" + resp);

					// transform raw response into json format
					std::string json = parseResponse(resp);
					// in case json response will be needed as file
					if (m_strWebKeyJSONFile.empty() == false)
					{
						writeFile(m_strWebKeyJSONFile, json);
					}

					// store it back into token store file for next use
					int resultValue = m_keyManager.generateNewKeyManagerFile(json);

					if (resultValue == 0)
					{
						LOG4CPLUS_DEBUG(m_Logger, "KeyManager Token received and write into file successful");
						ret = RETURN_RESULT_KEYMANAGER_OK;
					}
					else if (resultValue == -1)
					{
						LOG4CPLUS_DEBUG(m_Logger, "KeyManager Token received but write into file failed!");
						ret = RETURN_RESULT_KEYMANAGER_WRITEFILE_ERROR;
					}
					else
					{
						LOG4CPLUS_DEBUG(m_Logger, "KeyManager response not valid, no Token received!");
						ret = RETURN_RESULT_KEYMANAGER_RESPONSE_ERROR;
					}
				}
				else
				{
					ret = RETURN_RESULT_KEYMANAGER_REQUEST_ERROR;
				}
				// close the key manager connection
				m_objWebKey.close();
			}
			else
			{
				return RETURN_RESULT_KEYMANAGER_CONNECT_ERROR;
			}
		}
		return ret;
	}

	//-------------------------------------------------------------------------------------------------//
	// webservice handler
	//-------------------------------------------------------------------------------------------------//
	int ImportMedReg::runWebService()
	{
		METHODNAME_DEF(ApplCtrlImpl, runWebService);
		BLOG_TRACE_METHOD(getLogger(), fun);

		int ret = RETURN_RESULT_NO_ACTION;
		// connect the webservice to obtain medreg data
		if ((this->doLoadMedregCompanies()) || (this->doLoadMedregPersonals()))
		{
			LOG4CPLUS_DEBUG(m_Logger, "WebService action enabled");
			if (m_blnWebProxy == true)
			{
				LOG4CPLUS_DEBUG(m_Logger, "Establishing Internet proxy for WebService call...");
				// phoenix proxy needs to be used for connecting to internet
				if (m_objWebAPI.proxy(m_strWebProxyServer, atoi(m_strWebProxyPort.c_str()), m_strWebProxyAuth, m_strWebProxyCred) == false)
				{
					return RETURN_RESULT_PROXY_ERROR;
				}
			}
			// use the properties to set user and credentials
			m_objWebAPI.authorize(m_strWebAuth, m_strWebCred);
			LOG4CPLUS_DEBUG(m_Logger, "WebService server connecting...");

			// check if page counter is needed for requesting it
			int counter = 1;
			int maxcounter = 1; // default 1, only one request, if no counter is set
			bool stopcount = false;
			std::string webrequest;
			size_t start_pos = m_strWebRequest.find("<counter>");
			if (start_pos != std::string::npos)
			{
				// set a max counter of 100 to prevent endless loops
				maxcounter = 100;
			}
			while ((counter <= maxcounter) && (stopcount == false))
			{
				if (m_objWebAPI.connect(m_strWebServer, atoi(m_strWebPort.c_str())) == true)
				{
					if (maxcounter > 1)
					{
						std::string msg;
						msg = "WebService request page " + std::to_string(counter) + " calling...";
						LOG4CPLUS_DEBUG(m_Logger, msg.c_str());
					}
					else
					{
						LOG4CPLUS_DEBUG(m_Logger, "WebService request calling...");
					}
					// replace counter keyword with current counter number
					webrequest = m_strWebRequest;
					if (start_pos != std::string::npos)
					{
						webrequest.replace(start_pos, 9, std::to_string(counter));
					}
					if (m_objWebAPI.request(m_strWebType, webrequest, m_strWebBody, m_strWebBodyType) == true)
					{
						std::string req = m_objWebAPI.getLastRequest();
						writeProtocol(m_strWebCSVProtocolFile, "--------------\nWEB REQUEST\n--------------\n" + req);
						std::string resp = m_objWebAPI.getLastResponse();
						writeProtocol(m_strWebCSVProtocolFile, "--------------\nWEB RESPONSE\n--------------\n" + resp);

						// transform raw response into json format
						std::string json = parseResponse(resp);
						// in case json response will be needed as file
						if (m_strWebJSONFile.empty() == false)
						{
							writeFile(m_strWebJSONFile, json);
						}

						//Export to CSV File when flag is set
						if (m_strWebCSVFile.empty() == false)
						{
							// convert the json into CSV and save it into file
							std::string csvfile = m_strBasePath + m_strWebCSVFile;
							int resultValue = -2;
							if (this->doLoadMedregCompanies() == true)
							{
								// create at first round, then append, if counter is given
								resultValue = m_exportGenerator.generateCompaniesCSV(csvfile, counter>1, json);
							}
							else if (this->doLoadMedregPersonals() == true)
							{
								// create at first round, then append, if counter is given
								resultValue = m_exportGenerator.generatePersonalsCSV(csvfile, counter>1, json);
							}
							if (resultValue == 0)
							{
								LOG4CPLUS_DEBUG(m_Logger, "WebService data received and export into CSV file successful");
								ret = RETURN_RESULT_WEBSERVICE_OK;
							}
							else if (resultValue == -1)
							{
								LOG4CPLUS_DEBUG(m_Logger, "WebService data received but export into CSV file failed!");
								ret = RETURN_RESULT_WEBSERVICE_WRITEFILE_ERROR;
								stopcount = true;
							}
							else
							{
								stopcount = true;
								if (counter == 1)
								{
									LOG4CPLUS_DEBUG(m_Logger, "WebService response not valid, no data received!");
									ret = RETURN_RESULT_WEBSERVICE_RESPONSE_ERROR;
								}
							}
						}
						else
						{
							// do nothing with result
							ret = RETURN_RESULT_WEBSERVICE_OK;
						}
					}
					else
					{
						ret = RETURN_RESULT_WEBSERVICE_REQUEST_ERROR;
						stopcount = true;
					}
					// close the web service connection
					m_objWebAPI.close();
				}
				else
				{
					stopcount = true;
					ret = RETURN_RESULT_WEBSERVICE_CONNECT_ERROR;
				}
				// loop page counter
				counter++;
			}
		}
		return ret;
	}


	// lazy command line parameter management
	bool ImportMedReg::parseCommandLine(int argc, char* argv[])
	{
		bool answer = true;
		size_t delimPos;
		std::string optKey;
		std::string optValue;

		for (int i = 1; i < argc; i++)
		{
			std::string option(argv[i]);

			delimPos = option.find_first_of("=:");
			if (delimPos == std::string::npos)
			{
				/* simple option / flag */
				optKey = option;
				optValue = "";
			}
			else
			{
				/* option: key=value */
				optKey = option.substr(0, delimPos);
				optValue = option.substr(delimPos + 1);
			}

			// silently ignore options added twice
			if (!m_cmdParams.count(optKey))
			{
				m_cmdParams[optKey] = optValue;
			}
		}

		return answer;
	}

	void ImportMedReg::printUsage()
	{
		std::cout << "USAGE:" << std::endl << "importmedreg "
			OPT_LOAD_MEDREG "=companies/personals "
			OPT_PROPERTIES "=<properties file> "
			OPT_TOKEN_REFRESH "=yes/no "
			OPT_TOKEN_STORE "=<token file>" << std::endl << std::endl
			<< " - '" OPT_TOKEN_REFRESH "' defaults to 'no'" << std::endl
			<< " - '" OPT_LOAD_MEDREG "', '" OPT_PROPERTIES "' and '" OPT_TOKEN_STORE "' options are mandatory!" << std::endl;
	}

	bool ImportMedReg::doLoadMedregCompanies()
	{
		// only if --loadmedreg is set to 'companies'
		return (m_cmdParams.count(OPT_LOAD_MEDREG) > 0 && ("companies" == m_cmdParams[OPT_LOAD_MEDREG]));
	}

	bool ImportMedReg::doLoadMedregPersonals()
	{
		// only if --loadmedreg is set to 'companies'
		return (m_cmdParams.count(OPT_LOAD_MEDREG) > 0 && ("personals" == m_cmdParams[OPT_LOAD_MEDREG]));
	}

	bool ImportMedReg::doRefreshTokenPair()
	{
		// only if --token_refresh=yes command line parameter (so default is no)
		return m_cmdParams.count(OPT_TOKEN_REFRESH) && ("yes" == m_cmdParams[OPT_TOKEN_REFRESH]);
	}

	//-------------------------------------------------------------------------------------------------//
	//! load the properties file with the settings of the web service
	//-------------------------------------------------------------------------------------------------//
	bool ImportMedReg::loadProperties(std::string propertyfile, std::string webservicetype)
	{
		bool ret = true;
		std::string line;
		std::ifstream file;
		std::string prefix = "";
		m_blnWebProxy = false;
		
		if (webservicetype.compare("companies") == 0)
		{
			prefix = "WebComp";
		}
		else if (webservicetype.compare("personals") == 0)
		{
			prefix = "WebPers";
		}
		else
		{
			// no prefix, allowed for key calls only
			prefix = "---";
		}

		file.open(propertyfile.c_str(), std::ios_base::in);
		if (file.is_open() == true)
		{
			while ((std::getline(file, line)) && (ret == true))
			{
				if (line.empty() == false)
				{
					ret = parseParameter(line, prefix);
				}
			}
			file.close();
		}
		else
		{
			ret = false;
		}
		return ret;
	}

	//-------------------------------------------------------------------------------------------------//
	//! parses the line of the properties file to the set parameter value
	//-------------------------------------------------------------------------------------------------//
	bool ImportMedReg::parseParameter(std::string line, std::string prefix)
	{
		bool ret = true;

		if (line.find("//") == 0)
		{
			// ignore comment lines
			return ret;
		}
		if (prefix.empty() == true)
		{
			// no prefix so not clear which web servce is meant
			return ret;
		}
		int pos = (int)line.find(":");
		if (pos > 0)
		{
			std::string param = line.substr(0, pos);
			std::string value = line.substr(pos + 1);
			if ((param.compare("WebProxy") == 0) && (value.compare("yes") == 0)) { m_blnWebProxy = true; }
			else if (param.compare("WebProxyServer") == 0) { m_strWebProxyServer = value; }
			else if (param.compare("WebProxyPort") == 0) { m_strWebProxyPort = value; }
			else if (param.compare("WebProxyAuth") == 0) { m_strWebProxyAuth = value; }
			else if (param.compare("WebProxyCred") == 0) { m_strWebProxyCred = value; }
			else if (param.compare("WebKeyServer") == 0) { m_strWebKeyServer = value; }
			else if (param.compare("WebKeyRequest") == 0) { m_strWebKeyRequest = value; }
			else if (param.compare("WebKeyType") == 0) { m_strWebKeyType = value; }
			else if (param.compare("WebKeyPort") == 0) { m_strWebKeyPort = value; }
			else if (param.compare("WebKeyAccept") == 0) { m_strWebKeyAccept = value; }
			else if (param.compare("WebKeyAuth") == 0) { m_strWebKeyAuth = value; }
			else if (param.compare("WebKeyCred") == 0) { m_strWebKeyCred = value; }
			else if (param.compare("WebKeyBodyType") == 0) { m_strWebKeyBodyType = value; }
			else if (param.compare("WebKeyBody") == 0) { m_strWebKeyBody = parseValue(value); }
			else if (param.compare("WebKeyJSONFile") == 0) { m_strWebKeyJSONFile = value; }
			else if (param.compare("WebKeyProtocolFile") == 0) { m_strWebKeyProtocolFile = value; }
			else if (param.compare(prefix + "Server") == 0) { m_strWebServer = value; }
			else if (param.compare(prefix + "Port") == 0) { m_strWebPort = value; }
			else if (param.compare(prefix + "Accept") == 0) { m_strWebAccept = value; }
			else if (param.compare(prefix + "Auth") == 0) { m_strWebAuth = value; }
			else if (param.compare(prefix + "Cred") == 0) { m_strWebCred = parseValue(value); }
			else if (param.compare(prefix + "Request") == 0) { m_strWebRequest = value; }
			else if (param.compare(prefix + "Type") == 0) { m_strWebType = value; }
			else if (param.compare(prefix + "BodyType") == 0) { m_strWebBodyType = value; }
			else if (param.compare(prefix + "Body") == 0) { m_strWebBody = value; }
			else if (param.compare(prefix + "JSONFile") == 0) { m_strWebJSONFile = value; }
			else if (param.compare(prefix + "CSVFile") == 0) { m_strWebCSVFile = value; }
			else if (param.compare(prefix + "CSVProtocolFile") == 0) { m_strWebCSVProtocolFile = value; }
		}
		else
		{
			ret = false;
		}
		return ret;
	}


	//-------------------------------------------------------------------------------------------------//
	//! parses the properties values for dynamic replacements
	//-------------------------------------------------------------------------------------------------//
	std::string ImportMedReg::parseValue(std::string value)
	{
		std::string ret = value;

		int apos = (int)value.find('<', 0);
		int epos = (int)value.find('>', 0);
		if ((apos >= 0) && (epos >= apos))
		{
			// take the key and ask keymanager for token key
			std::string key = value.substr(apos + 1, epos - (apos+1));
			std::string token = m_keyManager.getToken(key);
			// replace keyword with token
			ret = value.substr(0, apos) + token + value.substr(epos + 1);
		}
		return ret;
	}

	//-------------------------------------------------------------------------------------------------//
	//! parses the raw http(s) response and split the data from the header
	//-------------------------------------------------------------------------------------------------//
	std::string ImportMedReg::parseResponse(std::string response)
	{
		std::string ret = "";

		// split response into http header and body
		int pos = (int)response.find("\r\n\r\n");
		if (pos > 0)
		{
			std::string head = toLower(response.substr(0, pos));
			std::string body = response.substr(pos + 4);

			bool chunked = false;
			if (head.find("transfer-encoding: chunked") != std::string::npos)
			{
				chunked = true;
			}
			if (chunked == true)
			{
				std::string newbody = "";
				do
				{
					pos = (int)body.find("\r\n");
					if (pos > 0)
					{
						std::string chunk = body.substr(0, pos);
						long chunksize = strtol(chunk.c_str(), NULL, 16);
						std::string chunkdata = body.substr(pos + 2, chunksize);
						newbody += chunkdata;
						body = body.substr(pos + 2 + chunksize + 2);
					}
				} while (pos > 0);
				// done, so transfer the new body back to body after transfer-decoding
				body = newbody;
			}
			ret = body;
		}
		return ret;
	}

	//-------------------------------------------------------------------------------------------------//
	//! temporary writes the protocol of the web data exchange, should be changed to log4c
	//-------------------------------------------------------------------------------------------------//
	void ImportMedReg::writeProtocol(std::string file, std::string text)
	{
		if (file.empty() == false)
		{
			std::ofstream protocolFile;
			std::string pfile = m_strBasePath + file;
			protocolFile.open(pfile.c_str(), std::ios_base::app);
			std::string prot_text = replace_all(text, "\r", "");
			protocolFile << prot_text << std::endl;
			protocolFile.close();
		}
	}

	//-------------------------------------------------------------------------------------------------//
	//! writes a file e.g. for the received data from web
	//-------------------------------------------------------------------------------------------------//
	void ImportMedReg::writeFile(std::string file, std::string text)
	{
		std::ofstream protocolFile;
		std::string pfile = m_strBasePath + file;
		protocolFile.open(pfile.c_str(), std::ios_base::app);
		protocolFile << text << std::endl;
		protocolFile.close();
	}

	//-------------------------------------------------------------------------------------------------//
	//! replaces characters in a text, as this method is not available in the std library
	//-------------------------------------------------------------------------------------------------//
	std::string ImportMedReg::replace_all(std::string text, std::string from, std::string to)
	{
		std::string ret = text;

		if (from.empty() == true)
		{
			return ret;
		}

		size_t start_pos = 0;
		while ((start_pos = ret.find(from, start_pos)) != std::string::npos)
		{
			ret.replace(start_pos, from.length(), to);
			start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
		}
		return ret;
	}

	std::string ImportMedReg::toLower(std::string data)
	{
		std::string ret = data;
		std::transform(ret.begin(), ret.end(), ret.begin(), ::tolower);
		return ret;
	}

}
