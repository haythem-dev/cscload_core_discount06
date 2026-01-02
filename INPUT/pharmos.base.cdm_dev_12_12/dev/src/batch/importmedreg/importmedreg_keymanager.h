//------------------------------------------------------------------------------------------------------------------//
//! \file  importmedreg_keymanger.h
// \brief  application class for Load and SAVE ther Access- and Refreshtoken
// \author Bjoern Muenschke
// \date   27.06.2022
//------------------------------------------------------------------------------------------------------------------//
#ifndef GUARD_IMPORTMEDREG_KEYMANAGER_H
#define GUARD_IMPORTMEDREG_KEYMANAGER_H

#include <iostream>
#include <QtCore/QDebug>
#include <QtCore/QFile>
#include <QtCore/QString>

#include <QtCore/QJsonArray>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>

#include <fstream>
#include <sstream>
#include <vector>
#include "importmedreg_loggerpool.h"

typedef std::map<std::string, std::string> string2string_t;

namespace importmedreg
{
	class KeyManager
	{
	public:
		KeyManager();
		~KeyManager();

		void			setKeyManagerFile(const std::string file);
		int				generateNewKeyManagerFile(std::string data);
		bool			readTokensFromFile();
		std::string		getToken(std::string key);

	private:
		QString			m_KeyManagerFile;

		const			log4cplus::Logger& getLogger() const;
		const			log4cplus::Logger& m_Logger;
		string2string_t	m_returnTokens;
	};
}


#endif //end GUARD_IMPORTMEDREG_KEYMANAGER_H