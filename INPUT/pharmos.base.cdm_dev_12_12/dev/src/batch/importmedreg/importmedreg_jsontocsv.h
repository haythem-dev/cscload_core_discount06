//------------------------------------------------------------------------------------------------------------------//
//! \file  exportjsontocsv
// \brief  application class for export json response date to csv by using QT
// \author Bjoern Muenschke
// \date   18.05.2022
//------------------------------------------------------------------------------------------------------------------//
#ifndef GUARD_MEDREG_EXPORTJSONTOCSV_H
#define GUARD_MEDREG_EXPORTJSONTOCSV_H

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

namespace importmedreg
{

	class ExportJsonToCSV
	{
	public:
		ExportJsonToCSV();
		~ExportJsonToCSV();

		int generateCompaniesCSV(std::string file, bool append, std::string json);
		int generatePersonalsCSV(std::string file, bool append, std::string json);

	private:

		const log4cplus::Logger& getLogger() const;

		const log4cplus::Logger& m_Logger;

	};
}

#endif //end GUARD_MEDREG_EXPORTJSONTOCSV_H