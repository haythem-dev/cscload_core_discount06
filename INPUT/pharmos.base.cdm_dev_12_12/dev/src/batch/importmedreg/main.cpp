//----------------------------------------------------------------------------
//! \file: main.cpp
// \brief: standard execution of backend application
// \author Thomas Arnold
// \date   09.05.2022
//----------------------------------------------------------------------------

#include <iostream>
#include "importmedreg.h"
#include "importmedreg_jsontocsv.h"
#include "importmedreg_keymanager.h"

#if defined UNIX
#include <unistd.h>
#endif

std::string convertResultCodeToString(int resultcode)
{
	std::string resultstring = "unknown code";
	if (resultcode == RETURN_RESULT_NO_ACTION) resultstring = "no actions done";
	else if (resultcode == RETURN_RESULT_INIT_OK) resultstring = "initialization successully done";
	else if (resultcode == RETURN_RESULT_KEYMANAGER_OK) resultstring = "KeyManager call successully done";
	else if (resultcode == RETURN_RESULT_WEBSERVICE_OK) resultstring = "WebService call successully done";
	else if (resultcode == RETURN_RESULT_WRONG_PARAMETERS_ERROR) resultstring = "Initialization failed, wrong parameters!";
	else if (resultcode == RETURN_RESULT_READ_TOKENFILE_ERROR) resultstring = "Initialization failed, cannot read token file!";
	else if (resultcode == RETURN_RESULT_READ_PROPERTIESFILE_ERROR) resultstring = "Initialization failed, cannot read properties file!";
	else if (resultcode == RETURN_RESULT_PROXY_ERROR) resultstring = "proxy connection failed!";
	else if (resultcode == RETURN_RESULT_KEYMANAGER_CONNECT_ERROR) resultstring = "KeyManager connection call failed!";
	else if (resultcode == RETURN_RESULT_KEYMANAGER_REQUEST_ERROR) resultstring = "KeyManager request invalid, call failed!";
	else if (resultcode == RETURN_RESULT_KEYMANAGER_RESPONSE_ERROR) resultstring = "KeyManager response invalid, parse failed!";
	else if (resultcode == RETURN_RESULT_KEYMANAGER_WRITEFILE_ERROR) resultstring = "KeyManager response valid, but token file write failed!";
	else if (resultcode == RETURN_RESULT_WEBSERVICE_CONNECT_ERROR) resultstring = "WebService connection call failed!";
	else if (resultcode == RETURN_RESULT_WEBSERVICE_REQUEST_ERROR) resultstring = "WebService request invalid, call failed!";
	else if (resultcode == RETURN_RESULT_WEBSERVICE_RESPONSE_ERROR) resultstring = "WebService response invalid, parse failed!";
	else if (resultcode == RETURN_RESULT_WEBSERVICE_WRITEFILE_ERROR) resultstring = "WebService response valid, but csv file write failed!";
	return resultstring;
}

void __testCSVGenerator()
{
	QString filepath = "companies_all.json";
	QString csvFilePath = "testdata.csv";
	QFile file(filepath);
	if (file.open(QIODevice::ReadOnly | QIODevice::Text | QIODevice::Truncate))
	{
		importmedreg::ExportJsonToCSV exporter;
		std::string resp = file.readAll().toStdString();
		exporter.generateCompaniesCSV(csvFilePath.toStdString(),false,resp);
		file.close();
	}
}

int main(int argc, char* argv[])
{
	int result = RETURN_RESULT_NO_ACTION;

	try
	{
		std::string path = std::string(argv[0]);
		if (path.find_last_of("\\") != -1) 
		{
			// windows version
			path = path.substr(0, path.find_last_of("\\"));
		}
		else if (path.find_last_of("//") != -1)
		{
			// unix version
			path = path.substr(0, path.find_last_of("//"));
		}
		else
		{
			// no path given, so take current directory
			char spath[1024];
#if defined WIN32
			GetCurrentDirectory(1024, (LPSTR)spath);
#else
			getcwd(spath, sizeof(spath));
#endif
			path = std::string(spath);
		}
#if defined WIN32
		path = path + "/";
#else
		path = path + "/../";
#endif
		//Class initialisation
		//Logger init
		::log4cplus::initialize();
		std::string configfile = path + std::string("ini/importmedreg_log.cfg");
		::log4cplus::PropertyConfigurator::doConfigure(configfile);
		::log4cplus::Logger logger(log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("importmedreg")));

		importmedreg::ImportMedReg app;
		//for testing the csv generation call __testCSVGenerator()

		LOG4CPLUS_DEBUG(logger, "App.Init() calling...");
		result = app.init(path, argc, argv);
		LOG4CPLUS_DEBUG(logger, "App.Init() result: " << convertResultCodeToString(result) << " (" << result << ")");
		if (result == RETURN_RESULT_INIT_OK)
		{
			LOG4CPLUS_DEBUG(logger, "App.runKeyManager() calling...");
			int result1 = app.runKeyManager();
			LOG4CPLUS_DEBUG(logger, "App.runKeyManager() result: " << convertResultCodeToString(result1) << " (" << result1 << ")");

			LOG4CPLUS_DEBUG(logger, "App.runWebService() calling...");
			int result2 = app.runWebService();
			LOG4CPLUS_DEBUG(logger, "App.runWebService() result: " << convertResultCodeToString(result2) << " (" << result2 << ")");

			LOG4CPLUS_DEBUG(logger, "App done");
			result = result1;
			if (result2 != 0)
			{
				result = result2;
			}
		}
	}
	catch (...)
	{
		// default error, when something happend unexpected
		result = RETURN_RESULT_UNKNOWN_ERROR;
	}
	return result;
}