//----------------------------------------------------------------------------
/*! \file UnittestTableEntry.cpp
*  \brief Helper for creation of table entries only required to run unit tests.
*  \author	Stefan Suffa
*  \date 05.03.2008
*/
//----------------------------------------------------------------------------

#include "unittesttableentry.h"
#include <libbasardbaspect.h>
#include <libbasardbsql_connectionref.h>
#include <libbasardbsql_statementref.h>


namespace ivc
{
	namespace test
	{
		namespace ivcdm
		{
			namespace utils
			{
				UnittestTableEntry::UnittestTableEntry()
				{
				}

				UnittestTableEntry::~UnittestTableEntry()
				{
				}

				void UnittestTableEntry::prepareRfiliale(basar::db::sql::ConnectionRef connection)
				{
					basar::db::sql::StatementRef statement = connection.createStatement();

					if(true == connection.isInTransaction())  //only delete if protected by transaction
					{
						basar::VarString sqlStatement = "";
						sqlStatement = "DELETE FROM rfiliale";
						statement.execute(sqlStatement);
					}

					basar::VarString sqlStatement = "";
					sqlStatement.append("INSERT INTO rfiliale (");
					sqlStatement.append("filialnr,");
					sqlStatement.append("filial_art,");
					sqlStatement.append("name,");
					sqlStatement.append("standort_kurz,");
					sqlStatement.append("standort_lang,");
					sqlStatement.append("strasse,");
					sqlStatement.append("plz_strasse,");
					sqlStatement.append("postfach,");
					sqlStatement.append("plz_postfach,");
					sqlStatement.append("ort,");
					sqlStatement.append("bundesland,");
					sqlStatement.append("vorwahl,");
					sqlStatement.append("telnr,");
					sqlStatement.append("faxnr,");
					sqlStatement.append("edifakt_version,");
					sqlStatement.append("mail_nr_1,");
					sqlStatement.append("mail_nr_2,");
					sqlStatement.append("mwst_1,");
					sqlStatement.append("mwst_2,");
					sqlStatement.append("mwst_1_alt,");
					sqlStatement.append("mwst_2_alt,");
					sqlStatement.append("datum_mwst,");
					sqlStatement.append("versand_text,");
					sqlStatement.append("bganr,");
					sqlStatement.append("bankzins,");
					sqlStatement.append("warenaus_abgabe,");
					sqlStatement.append("warenaus_bestell,");
					sqlStatement.append("neuheitenregal,");
					sqlStatement.append("kuehlzelle,");
					sqlStatement.append("rechnertyp,");
					sqlStatement.append("bganr_ek,");
					sqlStatement.append("vorzieh_tage,");
					sqlStatement.append("region,");
					sqlStatement.append("automatenlagernr,");
					sqlStatement.append("stammhaus,");
					sqlStatement.append("besla_nr,");
					sqlStatement.append("mwst_3,");
					sqlStatement.append("mwst_4,");
					sqlStatement.append("mwst_5,");
					sqlStatement.append("mwst_3_alt,");
					sqlStatement.append("mwst_4_alt,");
					sqlStatement.append("mwst_5_alt,");
					sqlStatement.append("strasse2,");
					sqlStatement.append("waehrfaktor,");
					sqlStatement.append("ean1,");
					sqlStatement.append("ean2,");
					sqlStatement.append("woch_besla,");
					sqlStatement.append("gi_ivc_new");
					sqlStatement.append(") VALUES ( ");
					sqlStatement.append("90,");
					sqlStatement.append("'FILIAL_ART',");
					sqlStatement.append("'UNITTEST',");
					sqlStatement.append("'STANDORT_KURZ',");
					sqlStatement.append("'STANDORT_LANG',");
					sqlStatement.append("'STRASSE',");
					sqlStatement.append("'PLZ_STRASSE',");
					sqlStatement.append("'POSTFACH',");
					sqlStatement.append("'PLZ_POSTFACH',");
					sqlStatement.append("'ORT',");
					sqlStatement.append("'BUNDESLAND',");
					sqlStatement.append("'VORWAHL',");
					sqlStatement.append("'TELNR',");
					sqlStatement.append("'FAXNR',");
					sqlStatement.append("0,");
					sqlStatement.append("'MAILNR1',");
					sqlStatement.append("'MAILNR2',");
					sqlStatement.append("0,");
					sqlStatement.append("0,");
					sqlStatement.append("0,");
					sqlStatement.append("0,");
					sqlStatement.append("20080301,");
					sqlStatement.append("'VERSANDTEXT',");
					sqlStatement.append("0,");
					sqlStatement.append("0,");
					sqlStatement.append("'A',");
					sqlStatement.append("'B',");
					sqlStatement.append("'NEU',");
					sqlStatement.append("'K',");
					sqlStatement.append("'R',");
					sqlStatement.append("0,");
					sqlStatement.append("0,");
					sqlStatement.append("0,");
					sqlStatement.append("0,");
					sqlStatement.append("'S',");
					sqlStatement.append("0,");
					sqlStatement.append("0,");
					sqlStatement.append("0,");
					sqlStatement.append("0,");
					sqlStatement.append("0,");
					sqlStatement.append("0,");
					sqlStatement.append("0,");
					sqlStatement.append("'STRASSE',");
					sqlStatement.append("0,");
					sqlStatement.append("'EAN1',");
					sqlStatement.append("'EAN2',");
					sqlStatement.append("0,");
					sqlStatement.append("0);");

					statement.execute(sqlStatement, false); //dont throw if entry already exists
				}
			}
		}
	}
}

