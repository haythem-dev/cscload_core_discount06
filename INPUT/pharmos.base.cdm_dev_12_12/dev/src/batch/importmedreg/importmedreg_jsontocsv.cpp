//------------------------------------------------------------------------------------------------------------------//
//! \file  exportjsontocsv
// \brief  application class for export json response date to csv by using QT
// \author Bjoern Muenschke
// \date   18.05.2022
//------------------------------------------------------------------------------------------------------------------//

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include "importmedreg_jsontocsv.h"

//--------------------------------------------------------------------------------------------------//
// class definition section
//--------------------------------------------------------------------------------------------------//
namespace importmedreg
{

	ExportJsonToCSV::ExportJsonToCSV() : m_Logger(importmedreg::LoggerPool::getLoggerExportJsonToCSV())
	{
		METHODNAME_DEF(ExportJsonToCSV, ExportJsonToCSV);
		BLOG_TRACE_METHOD(getLogger(), fun);
	}

	ExportJsonToCSV::~ExportJsonToCSV()
	{
		METHODNAME_DEF(ExportJsonToCSV, ~ExportJsonToCSV);
		BLOG_TRACE_METHOD(getLogger(), fun);
	}

	const log4cplus::Logger& ExportJsonToCSV::getLogger() const
	{
		return m_Logger;
	}

	int ExportJsonToCSV::generateCompaniesCSV(std::string file, bool append, std::string json)
	{
		METHODNAME_DEF(ExportJsonToCSV, generateCompaniesCSV);
		BLOG_TRACE_METHOD(getLogger(), fun);

		int result = 1;

		try
		{
			QFile csvFile(file.c_str());

			if (append == true)
			{
				csvFile.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Append);
				csvFile.write("");
				LOG4CPLUS_DEBUG(getLogger(), "csv file appended");
			}
			else
			{ 
				csvFile.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Truncate);
				csvFile.write("");
				LOG4CPLUS_DEBUG(getLogger(), "csv file created" );
			}
			QString jsonRaw = QString::fromUtf8(json.c_str());
			QByteArray jsonData = jsonRaw.toUtf8();

			QJsonParseError parseError;
			// TODO: handle parse error
			QJsonDocument jsonResponse = QJsonDocument::fromJson(jsonData, &parseError);
			QJsonArray jsonArray = jsonResponse.array(); 
			long rowcount = 0;
			if (jsonArray.size() > 1) 
			{
				QTextStream out(&csvFile);
				if (append == false)
				{
					// CSV Header
					out << "\"glnEstablishment\";\"uid\";\"establishmentName\";\"establishmentZusatzname\";";
					out << "\"street\";\"houseNr\";\"pob\";\"zip\";\"city\";\"idCountry\";\"nameIdCountry\";";
					out << "\"idCanton\";\"nameIdCanton\";\"idEstablishmentType\";\"nameIDEstablishmentType\";";
					out << "\"idNarcExtent\";\"nameIdNarcExtend\";\"dateModification\";\"responsiblePersons\";\"glnPerson\";\"name\";\"firstname\"";
					endl(out);
				}
				for (int i = 0; i < jsonArray.size(); i++)
				{
					QJsonObject jsonDoc = jsonArray[i].toObject();
					for (QJsonValueRef d : jsonDoc.value("responsiblePersons").toArray())
					{
						QJsonObject responsiblePersons = d.toObject();

						out << "\"" << jsonDoc.value("glnEstablishment").toString() << "\";";
						out << "\"" << jsonDoc.value("uid").toString() << "\";";
						out << "\"" << jsonDoc.value("establishmentName").toString() << "\";";
						out << "\"" << jsonDoc.value("establishmentZusatzname").toString() << "\";";
						out << "\"" << jsonDoc.value("street").toString() << "\";";
						out << "\"" << jsonDoc.value("houseNr").toString() << "\";";
						out << "\"" << jsonDoc.value("pob").toString() << "\";";
						out << "\"" << jsonDoc.value("zip").toString() << "\";";
						out << "\"" << jsonDoc.value("city").toString() << "\";";
						out << "\"" << jsonDoc.value("idCountry").toString() << "\";";
						out << "\"" << jsonDoc.value("nameIdCountry").toString() << "\";";
						out << "\"" << jsonDoc.value("idCanton").toString() << "\";";
						out << "\"" << jsonDoc.value("nameIdCanton").toString() << "\";";
						out << "\"" << jsonDoc.value("idEstablishmentType").toString() << "\";";
						out << "\"" << jsonDoc.value("nameIDEstablishmentType").toString() << "\";";
						out << "\"" << jsonDoc.value("idNarcExtent").toString() << "\";";
						out << "\"" << jsonDoc.value("nameIdNarcExtend").toString() << "\";";
						out << "\"" << jsonDoc.value("dateModification").toString() << "\";";
						out << "\"" << jsonDoc.value("responsiblePersons").toString() << "\";";

						out << "\"" << responsiblePersons.value("glnPerson").toString() << "\";";
						out << "\"" << responsiblePersons.value("name").toString() << "\";";
						out << "\"" << responsiblePersons.value("firstName").toString() << "\"";
						rowcount++;
						endl(out);
					}
				}
				csvFile.close();

				std::string msg = "Data (" + std::to_string(rowcount)+ " rows) successfully written!";
				LOG4CPLUS_DEBUG(m_Logger, msg.c_str());
				result = 0;
			}
			else
			{
				if (append == false)
				{
					LOG4CPLUS_DEBUG(m_Logger, "No Data written, please check connection!");
				}
			}
		}
		catch (const std::exception& ex)
		{
			LOG4CPLUS_DEBUG(m_Logger, "Something went wrong ... Error: " << ex.what());
			result = -1;
		}
		return result;
	}

	int ExportJsonToCSV::generatePersonalsCSV(std::string file, bool append, std::string json)
	{
		METHODNAME_DEF(ExportJsonToCSV, generatePersonalsCSV);
		BLOG_TRACE_METHOD(getLogger(), fun);

		int result = 1;

		try
		{
			QFile csvFile(file.c_str());

			if (append == true)
			{
				csvFile.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Append);
				csvFile.write("");
				LOG4CPLUS_DEBUG(getLogger(), "csv file appended");
			}
			else
			{
				csvFile.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Truncate);
				csvFile.write("");
				LOG4CPLUS_DEBUG(getLogger(), "csv file created");
			}

			QString jsonRaw = QString::fromLatin1(json.c_str());
			QByteArray jsonData = jsonRaw.toLatin1();

			QJsonParseError parseError;
			// TODO: handle parse error
			QJsonDocument jsonResponse = QJsonDocument::fromJson(jsonData, &parseError);
			QJsonArray jsonPersonalsArray = jsonResponse.array();
			long rowcount = 0;

			if (jsonPersonalsArray.size() > 1)
			{
				QTextStream out(&csvFile);
				if (append == false)
				{
					// CSV Header
					out << "\"gln\";\"name\";\"firstName\";\"idDiplomaKind\";\"nameDiplomaKind\";\"idCanton\";\"nameCanton\";\"idNarcExtend\";\"nameNarcExtend\";";
					out << "\"doctorsOfficeName\";\"street\";\"zip\";\"city\";\"idLicenceSelfdispensation\";\"nameLicenceSelfdispensation\";";
					endl(out);
				}
				// loop each medical person
				for (int i = 0; i < jsonPersonalsArray.size(); i++)
				{
					QJsonObject jsonPersonals = jsonPersonalsArray[i].toObject();
					QJsonArray jsonDiplomaArray = jsonPersonals.value("diploma").toArray();
					// loop each diploma of medical person
					for (int j = 0; j < jsonDiplomaArray.size(); j++)
					{
						QJsonObject jsonDiploma = jsonDiplomaArray[j].toObject();
						QJsonArray jsonLicenceArray = jsonDiploma.value("licence").toArray();
						// loop each licence of diploma
						for (int k = 0; k < jsonLicenceArray.size(); k++)
						{
							QJsonObject jsonLicence = jsonLicenceArray[k].toObject();
							QJsonArray jsonLocationArray = jsonLicence.value("location").toArray();
							// loop each location of licence
							for (int l = 0; l < jsonLocationArray.size(); l++)
							{
								QJsonObject jsonLocation = jsonLocationArray[l].toObject();
								// stream the informations in the csv file
								out << "\"" << jsonPersonals.value("gln").toString() << "\";";
								out << "\"" << jsonPersonals.value("name").toString() << "\";";
								out << "\"" << jsonPersonals.value("firstName").toString() << "\";";
								out << "\"" << jsonDiploma.value("idDiplomaKind").toString() << "\";";
								out << "\"" << jsonDiploma.value("nameIdDiplomaKind").toString() << "\";";
								out << "\"" << jsonLicence.value("idCanton").toString() << "\";";
								out << "\"" << jsonLicence.value("nameIdCanton").toString() << "\";";
								out << "\"" << jsonLicence.value("idNarcExtend").toString() << "\";";
								out << "\"" << jsonLicence.value("nameIdNarcExtend").toString() << "\";";
								out << "\"" << jsonLocation.value("doctorsOfficeName").toString() << "\";";
								out << "\"" << jsonLocation.value("street").toString() << "\";";
								out << "\"" << jsonLocation.value("zip").toString() << "\";";
								out << "\"" << jsonLocation.value("city").toString() << "\";";
								out << "\"" << jsonLocation.value("idLicenceSelfdispensation").toString() << "\";";
								out << "\"" << jsonLocation.value("nameIdLicenceSelfdispensation").toString() << "\";";
								rowcount++;
								endl(out);
							}
						}
					}
				}
				csvFile.close();

				std::string msg = "Data (" + std::to_string(rowcount) + " rows) successfully written!";
				LOG4CPLUS_DEBUG(m_Logger, msg.c_str());
				result = 0;
			}
			else
			{
				if (append == false)
				{
					LOG4CPLUS_DEBUG(m_Logger, "No Data written, please check connection!");
				}
			}
		}
		catch (const std::exception& ex)
		{
			LOG4CPLUS_DEBUG(m_Logger, "Something went wrong ... Error: " << ex.what());
			result = -1;
		}
		return result;
	}
}
