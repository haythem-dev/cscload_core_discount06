#include <stddef.h>
#include <stdio.h>
#include <pxrecord.h>
#include "pxdbfunc.h"
#include "pxdbxx.h"
#include "ndefs.h"
#include "tkundenotdienstplan.h"
#include <pxenv.h>
#include <keys.h>
#include "pxdatetime.h"

extern int  functionnr;

#define UNUSED(x) (void)(x)

int pxCustomerEmergencyServicePlanRead( struct tEMERGENCYSERVICEPLAN* record )
{
    EXEC SQL BEGIN DECLARE SECTION;
	struct C_KUNDENOTDIENSTPLAN* recordp;
	char query[2048];
	long currentdate;
    EXEC SQL END DECLARE SECTION;

	if( sizeof(struct C_KUNDENOTDIENSTPLAN) != sizeof(struct tEMERGENCYSERVICEPLAN) ) return cDBXR_DEFINITION;
	recordp = (struct C_KUNDENOTDIENSTPLAN*) record;

	currentdate = basardatetime_getCurrentDateYYYYMMDD();
	if (recordp->DATUM > 0)
	{
		currentdate = record->EmergencyServiceDate;
	}

	sprintf( query,
		"select first 1 knp.vertriebszentrumnr as branchno, knp.kundennr as customerno, knp.datum as emergencyservicedate "
		", 0 as emergencyservicetimefrom, knp.uhrzeitbis as emergencyservicetimeto, knp.bemerkungen as remarks " // time from should not be taken into account!!! set to 0.
		", knp.isbtm, knp.iskk, knp.isk08, knp.isk20 "
		"from kundenotdienstplan knp "
		"where knp.vertriebszentrumnr= ? and knp.kundennr= ? "
		"and knp.datum= ?;");

	EXEC SQL PREPARE pxcustomeremergencyserviceplanread_stmt FROM :query;
	EXEC SQL DECLARE pxcustomeremergencyserviceplanread_cur CURSOR WITH HOLD FOR pxcustomeremergencyserviceplanread_stmt;
	EXEC SQL OPEN pxcustomeremergencyserviceplanread_cur USING :recordp->VERTRIEBSZENTRUMNR, :recordp->KUNDENNR, :currentdate;

	switch( SQLCODE )
	{
		case 0:
			break;
		case 100:
			return cDBXR_NOTFOUND;
		default:
			return cDBXR_IOERROR;
	}

	EXEC SQL FETCH pxcustomeremergencyserviceplanread_cur INTO
		:recordp->VERTRIEBSZENTRUMNR,
		:recordp->KUNDENNR,
		:recordp->DATUM,
		:recordp->UHRZEITVON,
		:recordp->UHRZEITBIS,
		:recordp->BEMERKUNGEN,
		:recordp->ISBTM,
		:recordp->ISKK,
		:recordp->ISK08,
		:recordp->ISK20;

	switch( SQLCODE )
	{
		case 0:
			break;
		case 100:
			EXEC SQL CLOSE pxcustomeremergencyserviceplanread_cur;
			EXEC SQL FREE pxcustomeremergencyserviceplanread_stmt;
			return cDBXR_ENDOFDATA;
		default:
			EXEC SQL CLOSE pxcustomeremergencyserviceplanread_cur;
			EXEC SQL FREE pxcustomeremergencyserviceplanread_stmt;
			return cDBXR_IOERROR;
	}

	EXEC SQL CLOSE pxcustomeremergencyserviceplanread_cur;
	EXEC SQL FREE pxcustomeremergencyserviceplanread_stmt;
	return 0;
}
