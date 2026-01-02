//------------------------------------------------------------------------------------------------------------------//
//! \file  importmedreg
// \brief  application class (main) for import medreg components
// \author Thomas Arnold
// \date   09.05.2022
//------------------------------------------------------------------------------------------------------------------//
#ifndef GUARD_IMPORTMEDREG_H
#define GUARD_IMPORTMEDREG_H

#include "importmedreg_loggerpool.h"
#include "importmedreg_webservice.h"
#include "importmedreg_keymanager.h"
#include "importmedreg_jsontocsv.h"

typedef std::map<std::string, std::string> string2string_t;

static const int RETURN_RESULT_NO_ACTION = 0;
static const int RETURN_RESULT_INIT_OK = 1;
static const int RETURN_RESULT_KEYMANAGER_OK = 2;
static const int RETURN_RESULT_WEBSERVICE_OK = 3;
static const int RETURN_RESULT_UNKNOWN_ERROR = -100;
static const int RETURN_RESULT_WRONG_PARAMETERS_ERROR = -101;
static const int RETURN_RESULT_READ_TOKENFILE_ERROR = -102;
static const int RETURN_RESULT_READ_PROPERTIESFILE_ERROR = -103;
static const int RETURN_RESULT_PROXY_ERROR = -104;
static const int RETURN_RESULT_KEYMANAGER_CONNECT_ERROR = -105;
static const int RETURN_RESULT_KEYMANAGER_REQUEST_ERROR = -106;
static const int RETURN_RESULT_KEYMANAGER_RESPONSE_ERROR = -107;
static const int RETURN_RESULT_KEYMANAGER_WRITEFILE_ERROR = -108;
static const int RETURN_RESULT_WEBSERVICE_CONNECT_ERROR = -110;
static const int RETURN_RESULT_WEBSERVICE_REQUEST_ERROR = -111;
static const int RETURN_RESULT_WEBSERVICE_RESPONSE_ERROR = -112;
static const int RETURN_RESULT_WEBSERVICE_WRITEFILE_ERROR = -113;

namespace importmedreg
{
	class ImportMedReg
	{
	public:
		ImportMedReg();
		~ImportMedReg();

		int     init(std::string path, int argc, char *argv[]);
		int     runKeyManager();
		int     runWebService();

	private:
		const log4cplus::Logger& getLogger() const;
		std::string replace_all(std::string text, std::string from, std::string to);
		std::string toLower(std::string data);
		void writeProtocol(std::string file, std::string text);
		void writeFile(std::string file, std::string text);
		bool loadProperties(std::string propertyfile, std::string webservicetype);
		bool parseParameter(std::string line, std::string prefix);
		bool parseCommandLine(int argc, char* argv[]);
		std::string parseValue(std::string value);
		bool doLoadMedregCompanies();
		bool doLoadMedregPersonals();
		bool doRefreshTokenPair();
		void printUsage();
		std::string parseResponse(std::string response);

		std::string						m_strBasePath;
		const log4cplus::Logger&		m_Logger;
		importmedreg::WebService		m_objWebAPI;
		importmedreg::WebService		m_objWebKey;
		importmedreg::KeyManager		m_keyManager;
		importmedreg::ExportJsonToCSV	m_exportGenerator;

		string2string_t m_cmdParams;

		bool m_blnWebProxy;
		std::string m_strWebProxyServer;
		std::string m_strWebProxyPort;
		std::string m_strWebProxyAuth;
		std::string m_strWebProxyCred;

		std::string m_strWebKeyServer;
		std::string m_strWebKeyType;
		std::string m_strWebKeyRequest;
		std::string m_strWebKeyPort;
		std::string m_strWebKeyAccept;
		std::string m_strWebKeyAuth;
		std::string m_strWebKeyCred;
		std::string m_strWebKeyBodyType;
		std::string m_strWebKeyBody;
		std::string m_strWebKeyJSONFile;
		std::string m_strWebKeyProtocolFile;

		std::string m_strWebServer;
		std::string m_strWebPort;
		std::string m_strWebAccept;
		std::string m_strWebAuth;
		std::string m_strWebCred;
		std::string m_strWebType;
		std::string m_strWebRequest;
		std::string m_strWebBodyType;
		std::string m_strWebBody;
		std::string m_strWebJSONFile;
		std::string m_strWebCSVFile;
		std::string m_strWebCSVProtocolFile;
	};
}
#endif //end GUARD_IMPORTMEDREG_H