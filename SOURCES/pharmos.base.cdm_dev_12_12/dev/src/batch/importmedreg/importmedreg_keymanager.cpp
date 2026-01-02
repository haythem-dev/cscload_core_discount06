//------------------------------------------------------------------------------------------------------------------//
//! \file  importmedreg_keymanger.cpp
// \brief  application class for export json response date to csv by using QT
// \author Bjoern Muenschke
// \date   27.06.2022
//
// QT File Example
// xxx-https://stackoverflow.com/questions/56690101/how-can-i-convert-from-json-to-csv-in-qt
// xxx-https://www.youtube.com/watch?v=i4ciL8TxW_s
// xxx-https://forum.qt.io/topic/72088/check-if-file-exists-qt/4
// xxx-https://cpp.hotexamples.com/examples/-/QJsonArray/size/cpp-qjsonarray-size-method-examples.html
//------------------------------------------------------------------------------------------------------------------//

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include "importmedreg_keymanager.h"
//--------------------------------------------------------------------------------------------------//
// class definition section
//--------------------------------------------------------------------------------------------------//
namespace importmedreg
{
	const log4cplus::Logger & KeyManager::getLogger() const
	{
		return m_Logger;
	}

	KeyManager::KeyManager() : m_Logger(importmedreg::LoggerPool::getLoggerKeymanager())
	{
		METHODNAME_DEF(KeyManager, KeyManager);
		BLOG_TRACE_METHOD(getLogger(), fun);

		m_KeyManagerFile = "";
		m_returnTokens.clear();
	}

	KeyManager::~KeyManager()
	{
		METHODNAME_DEF(KeyManager, ~KeyManager);
		BLOG_TRACE_METHOD(getLogger(), fun);
	}

	void KeyManager::setKeyManagerFile(const std::string file)
	{
		METHODNAME_DEF(KeyManager, setKeyManagerFile);
		BLOG_TRACE_METHOD(getLogger(), fun);

		m_KeyManagerFile = (QString)file.c_str();
	}

	int KeyManager::generateNewKeyManagerFile(std::string data)
	{
		METHODNAME_DEF(KeyManager, generateNewKeyManagerFile);
		BLOG_TRACE_METHOD(getLogger(), fun);

		int result = 1;

		try
		{
			QString jsonRaw = (QString)data.c_str();
			QByteArray jsonData = jsonRaw.toUtf8();

			QJsonParseError parseError;
			// TODO: handle parse error
			QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &parseError);

			QJsonObject root = jsonDoc.object();

			QJsonValue valueAccessToken = root.value("access_token");
			QJsonValue valueRefreshToken = root.value("refresh_token");
			QJsonValue valueScope = root.value("scope");
			QJsonValue valueTokenType = root.value("token_type");
			QJsonValue valueExpiresIn = root.value("expires_in");
			
			//TODO: manage if something goes wrong
			if (valueAccessToken.toString() != "")
			{
				QFile csvFile(m_KeyManagerFile);

				if (!csvFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
				{
					csvFile.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Truncate);
					csvFile.write("");
					LOG4CPLUS_DEBUG(getLogger(), "file created");
				}

				QTextStream out(&csvFile);
				// CSV Header

				out << "access_token;refresh_token;scope;default;expires_in";
				endl(out);

				out << valueAccessToken.toString() << ';';
				out << valueRefreshToken.toString() << ';';
				out << valueScope.toString() << ';';
				out << valueTokenType.toString() << ';';
				out << valueExpiresIn.toInt() << ';';

				endl(out);

				csvFile.close();

				LOG4CPLUS_DEBUG(m_Logger, "Data successfully written!");
				result = 0;
			}
			else
			{
				LOG4CPLUS_DEBUG(m_Logger, "Data not written - access token is empty!");
			}
		}
		catch (const std::exception& ex)
		{
			LOG4CPLUS_ERROR(m_Logger, ex.what());
			result = -1;
		}

		return result;
	}

	bool KeyManager::readTokensFromFile()
	{
		METHODNAME_DEF(KeyManager, readTokensFromFile);
		BLOG_TRACE_METHOD(getLogger(), fun);

		bool ret = false;
		std::ifstream file;
		m_returnTokens.clear();

		file.open(m_KeyManagerFile.toStdString(), std::ios_base::in);
		if (file.is_open() == true)
		{
			std::string line;
			std::vector<std::vector<std::string> > parsedCsv;
			while (std::getline(file, line))
			{
				// read each line
				std::stringstream lineStream(line);
				std::string cell;
				std::vector<std::string> parsedRow;
				// split it into cells
				while (std::getline(lineStream, cell, ';'))
				{
					parsedRow.push_back(cell);
				}

				parsedCsv.push_back(parsedRow);
			}
			file.close();
			// take the first and second cell as access and refresh token in memory
			m_returnTokens.insert({ "refresh_token", parsedCsv.at(1).at(1) });
			m_returnTokens.insert({ "access_token", parsedCsv.at(1).at(0) });
			ret = true;
		}

		return ret;
	}

	std::string KeyManager::getToken(std::string key)
	{
		std::string ret = "";
		try
		{
			ret = m_returnTokens[key];
		}
		catch (const std::exception& ex)
		{
			// key not exist
			LOG4CPLUS_ERROR(m_Logger, ex.what());
		}
		return ret;
	}
}