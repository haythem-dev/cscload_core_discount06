#include "cicsdataacc.h"
#include "cicsdataacc_definitions.h"
#include "domainmodule/csc_phadex_properties_definitions.h"
#include "loggerpool/csc_phadex_loggerpool.h"

namespace infrastructure {
namespace accessor {
namespace drksc {

BEGIN_ACCESSOR_DEFINITION( lit::DRKSC_ACC )

    BEGIN_PROPERTY_DESCRIPTION_LIST
        PROPERTY_DESCRIPTION_LIST_ADD( properties::RRDS_RRN );
        PROPERTY_DESCRIPTION_LIST_ADD( properties::KSC_FIL );
        PROPERTY_DESCRIPTION_LIST_ADD( properties::KSC_SA );
        PROPERTY_DESCRIPTION_LIST_ADD( properties::KSC_DATUM );
        PROPERTY_DESCRIPTION_LIST_ADD( properties::KSC_ZEIT );
        PROPERTY_DESCRIPTION_LIST_ADD( properties::KSC_STATUS );
        PROPERTY_DESCRIPTION_LIST_ADD( properties::KSC_DATA );
    END_PROPERTY_DESCRIPTION_LIST

    ACCESS_METHOD( lit::SELECT_DRKSC_BY_PATTERN )
		SQL_BUILDER_CREATE( SelectDRKSCByPattern )
		SQL_BUILDER_PUSH_BACK( SelectDRKSCByPattern )

    ACCESS_METHOD(lit::UPDATE_DRKSC)
        SQL_BUILDER_CREATE(UpdateDRKSC)
        SQL_BUILDER_PUSH_BACK(UpdateDRKSC)
END_ACCESSOR_DEFINITION


BUILDER_DEFINITION( SelectDRKSCByPattern )

bool SelectDRKSCByPattern::isExecutable() const
{
    basar::cmnutil::ParameterList searchValues;
    searchValues.push_back( properties::RRDS_RRN.getName() );
    searchValues.push_back( properties::KSC_FIL.getName() );
    return arePropertiesSet( searchValues );
}

void SelectDRKSCByPattern::buildSQLString()
{
	static const basar::VarString sql(
		"SELECT "
			"DRKSC.RRDS_RRN AS "	+ properties::RRDS_RRN.getName()	+ ", "
			"DRKSC.KSC_FIL AS "		+ properties::KSC_FIL.getName()		+ ", "
			"DRKSC.KSC_SA AS "		+ properties::KSC_SA.getName()		+ ", "
			"DRKSC.KSC_DATUM AS "	+ properties::KSC_DATUM.getName()	+ ", "
			"DRKSC.KSC_ZEIT AS "	+ properties::KSC_ZEIT.getName()	+ ", "
			"DRKSC.KSC_STATUS AS "	+ properties::KSC_STATUS.getName()	+ ", "
			"DRKSC.KSC_DATA AS "	+ properties::KSC_DATA.getName()	+ " "
		"FROM "
			"VSAM.DRKSC "
		"WHERE "
			"DRKSC.RRDS_RRN > "	+ properties::RRDS_RRN.toSQLReplacementString()	+ " AND "
			"DRKSC.KSC_FIL = "	+ properties::KSC_FIL.toSQLReplacementString()	+ " AND "
			"DRKSC.KSC_STATUS <> '1' "
		"ORDER BY "
			"DRKSC.RRDS_RRN ASC"
	);
	resolve(sql);
	BLOG_DEBUG(csc_phadex::LoggerPool::getLoggerDomModules(), getSQLString());
}


BUILDER_DEFINITION(UpdateDRKSC)

bool UpdateDRKSC::isExecutable() const
{
	basar::cmnutil::ParameterList searchValues;
	searchValues.push_back(properties::RRDS_RRN.getName());
	searchValues.push_back(properties::KSC_FIL.getName());
	searchValues.push_back(properties::KSC_STATUS.getName());
	return arePropertiesSet(searchValues);
}

void UpdateDRKSC::buildSQLString()
{
	static const basar::VarString sql(
		"UPDATE VSAM.DRKSC SET "
			"DRKSC.KSC_STATUS = '"	+ properties::KSC_STATUS.toSQLReplacementString()	+ "' "
		"WHERE "
			"DRKSC.RRDS_RRN = "		+ properties::RRDS_RRN.toSQLReplacementString()		+ " AND "
			"DRKSC.KSC_FIL = "		+ properties::KSC_FIL.toSQLReplacementString()
	);
	resolve(sql);
	BLOG_DEBUG(csc_phadex::LoggerPool::getLoggerDomModules(), getSQLString());
}

}
}
}


/*
1. Lauf   06:00     IFX kein eintrag -> SELECT mit KEY > 0   				IFX = 00  TCA SELECT mit KEY=0 ==> SELECT mit KEY>0
X. Lauf 07:00        IFX Eintrag da  -> SELECT mit KEY > Eintrag    IFX = 01  TCA SELECT mit KEY 01 ==> SELECT mit KEY>01
Y. Lauf 00:05+      IFX kein eintrag zu aktuellem datum  -> SELECT mit KEY > 0    IFX = 99    TCA SELECT mit KEY 99 ==> SELECT mit KEY>99
TA   IFX = 101   TCA SELECT mit KEY 101 !=> SELECT mit KEY>0




int 8stellig  FIELD=RRDS_RRN,       Y,       F,        N,          0,         4,      0,        ,       
FIELD=KSC_FIL,        Y,       Z,        N,          0,         2,      0,     101,       
Satzart/recordtype	int 3stellig FIELD=KSC_SA,         Y,       Z,        N,          2,         3,      0,     101,       
FIELD=KSC_DATUM,      Y,       Z,        N,          5,         8,      0,     101,       
FIELD=KSC_ZEIT,       Y,       Z,        N,         13,         6,      0,     101,       
FIELD=KSC_STATUS,     Y,       Z,        N,         19,         1,      0,     101,       
FIELD=KSC_DATA,       Y,       M,        N,         20,       480,      0,        ,  

transfer/processtimestamp in infx

IFX Key:
	Filiale, RRN, DateTime (KSC_DATUM und KSC_ZEIT)

	


IFXTAB						DRKSC
-									-									06:00			SELECT IFX => Key 00		SELECT TCA => Key 00  => Nicht gefunden --> SELECT TCA KEY > 00				00 ALS Default Start			letzter Satz 05 INSERT IFX
05								05								07:00		  SELECT IFX => Key 05	 	SELECT TCA => Key 05  => Gefunden       --> SELECT TCA KEY > 05
99								99								00:05+	  SELECT IFX => Key 99    SELECT TCA => Key 99  => Gefunden			  --> SELECT TCA KEY > 99
TAGESABSCHLUSS leert DRKSC
101               -									06:00+		SELECT IFX => Key 101		SELECT TCA => Key 101 => Nicht gefunden --> SELECT TCA KEY > 00				00 ALS Default Start




-									-									06:00			SELECT IFX => Key 00		SELECT TCA => Key 00  => Nicht gefunden --> SELECT TCA KEY > 00				00 ALS Default Start			letzter Satz 05 INSERT IFX
05								05								07:00		  SELECT IFX => Key 05	 	SELECT TCA => Key 05  => Gefunden       --> SELECT TCA KEY > 05
TAGESABSCHLUSS vor Mitternacht
05								05								23:00			SELECT IFX => Key 05		SELECT TCA => Key 05	=> Nicht gefunden --> SELECT TCA KEY > 00

																																			SELECT TCA mit Key, Fil, Datum, Uhrzeit
																																			(letzten verarbeiteten Satz gefunden?)
																																			
																																			
IFX-Tabelle		phadextransaction 																																			

*/
