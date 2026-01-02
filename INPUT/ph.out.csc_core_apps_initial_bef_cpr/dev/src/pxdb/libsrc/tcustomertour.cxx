#include <stddef.h>
#include <stdio.h>
#include <pxrecord.h>
#include "pxdbfunc.h"
#include "pxdbxx.h"
#include "ndefs.h"
#include "tcustomertour.h"
#include <pxenv.h>
#include <keys.h>

extern int  functionnr;

#define UNUSED(x) (void)(x)

/*-------------------------------------------------------------------*/
/* open cursor                                                       */
/*-------------------------------------------------------------------*/
int CustomerTourStartBrowse( struct tCUSTOMERTOUR* record, const char* dbName, int browseid )
{
	EXEC SQL BEGIN DECLARE SECTION;
		struct C_CUSTOMERTOUR* recordp;
		char query[2048];
	EXEC SQL END DECLARE SECTION;

	if( sizeof(struct C_CUSTOMERTOUR) != sizeof(struct tCUSTOMERTOUR) )
	{
		return cDBXR_DEFINITION;
	}

	recordp = (struct C_CUSTOMERTOUR*) record;

	switch( browseid )
	{
		case cCUSTOMERTOUR_BYTOURIDWEEK:
			sprintf( query,
				"SELECT tptw.kundennr, 0, tptw.tourid, tptw.fahrtzeit, tptw.istverbundtour, tptw.vertriebszentrumnr, "
				"'0', 0, '1', tptw.kdauftragart, 0, tptw.weekday, 0, tptw.iskk, tptw.isk08, tptw.isk20, tptw.isbtm, "
				"' ', tpw.karenzzeit, tpw.lagrechtour, tptw.returnstour, tptw.transpexclpsycho "
				"FROM %s:tourplantagwoche tptw "
				"JOIN %s:tourplanwoche tpw ON tpw.tourid=tptw.tourid AND tpw.filialnr=tptw.vertriebszentrumnr AND tpw.weekday=tptw.weekday "
				"WHERE tptw.vertriebszentrumnr = ? AND tptw.kundennr = ? AND tptw.tourid = ? "
				"ORDER BY tptw.weekday "
				, dbName, dbName );
			break;

		case cCUSTOMERTOUR_BYTOURID:
			sprintf( query,
				"SELECT tpt.idfnr, tpt.datumkommi, tpt.tourid, tpt.fahrtzeit, tpt.istverbundtour, "
				"tpt.vertriebszentrumnr, tpt.tourinaktiv, tpt.kippzeit, tpt.kzautozuord, tpt.kdauftragart, "
				"t.kippzeit, -1, t.zeitkoende, tpt.iskk, tpt.isk08, tpt.isk20, tpt.isbtm, "
				"tpt.koart, t.karenzzeit, 0, tpt.returnstour, tpt.transpexclpsycho "
				"FROM %s:tourplantag tpt "
				"JOIN %s:tour t ON t.tourid=tpt.tourid AND t.filialnr=tpt.vertriebszentrumnr AND t.datumkommi=tpt.datumkommi "
				"WHERE tpt.tourinaktiv = '0' AND t.tourinaktiv != '1' AND tpt.vertriebszentrumnr = ? "
				"AND tpt.kundennr = ? AND tpt.tourid = ? ORDER BY tpt.datumkommi ASC "
				, dbName, dbName );
			break;

		case cCUSTOMERTOUR_WHOLEWEEK:
			sprintf( query,
				"SELECT tptw.kundennr, 0, tptw.tourid, tptw.fahrtzeit, tptw.istverbundtour, tptw.vertriebszentrumnr, "
				"'0', 0, '1', tptw.kdauftragart, 0, tptw.weekday, 0, tptw.iskk, tptw.isk08, tptw.isk20, tptw.isbtm, "
				"' ', tpw.karenzzeit, tpw.lagrechtour, tptw.returnstour, tptw.transpexclpsycho "
				"FROM %s:tourplantagwoche tptw "
				"JOIN %s:tourplanwoche tpw ON tpw.tourid=tptw.tourid AND tpw.filialnr=tptw.vertriebszentrumnr AND tpw.weekday=tptw.weekday "
				"WHERE tptw.vertriebszentrumnr = ? AND tptw.kundennr = ? "
				"ORDER BY tptw.weekday, tptw.tourid "
				, dbName, dbName );
			break;

		case cCUSTOMERTOUR_DEFAULT:
		default:
			sprintf( query,
				"SELECT tpt.idfnr, tpt.datumkommi, tpt.tourid, tpt.fahrtzeit, tpt.istverbundtour, "
				"tpt.vertriebszentrumnr, tpt.tourinaktiv, tpt.kippzeit, tpt.kzautozuord, tpt.kdauftragart, "
				"t.kippzeit, -1, t.zeitkoende, tpt.iskk, tpt.isk08, tpt.isk20, tpt.isbtm, "
				"tpt.koart, t.karenzzeit, 0, tpt.returnstour, tpt.transpexclpsycho "
				"FROM %s:tourplantag tpt "
				"JOIN %s:tour t ON t.tourid=tpt.tourid AND t.filialnr=tpt.vertriebszentrumnr AND t.datumkommi=tpt.datumkommi "
				"WHERE tpt.tourinaktiv = '0' AND t.tourinaktiv != '1' "
				"AND tpt.vertriebszentrumnr = ? AND tpt.kundennr = ? AND tpt.datumkommi = ? "
				"ORDER BY tpt.datumkommi, tpt.tourid "
				, dbName, dbName );
			break;

	}

	EXEC SQL PREPARE customertourstartbrowse_stmt FROM :query;
	EXEC SQL DECLARE customertourstartbrowse_cur CURSOR WITH HOLD FOR customertourstartbrowse_stmt;

	switch( browseid )
	{
		case cCUSTOMERTOUR_BYTOURIDWEEK:
			EXEC SQL OPEN customertourstartbrowse_cur USING
				:recordp->BRANCHNO,
				:recordp->CUSTOMERNO,
				:recordp->TOURID;
			break;

		case cCUSTOMERTOUR_BYTOURID:
			EXEC SQL OPEN customertourstartbrowse_cur USING
				:recordp->BRANCHNO,
				:recordp->CUSTOMERNO,
				:recordp->TOURID;
			break;

		case cCUSTOMERTOUR_WHOLEWEEK:
			EXEC SQL OPEN customertourstartbrowse_cur USING
				:recordp->BRANCHNO,
				:recordp->CUSTOMERNO;
			break;

		case cCUSTOMERTOUR_DEFAULT:
		default:
			EXEC SQL OPEN customertourstartbrowse_cur USING
				:recordp->BRANCHNO,
				:recordp->CUSTOMERNO,
				:recordp->PICKINGDATE;
			break;
	}


	switch( SQLCODE )
	{
		case 0:
			return 0;
		case 100:
			return cDBXR_NOTFOUND;
		default:
			return cDBXR_IOERROR;
	}
}

/*-------------------------------------------------------------------*/
/* get next cursors                                                  */
/*-------------------------------------------------------------------*/
int CustomerTourGetNext( struct tCUSTOMERTOUR* record, int browseid )
{
	EXEC SQL BEGIN DECLARE SECTION;
	struct C_CUSTOMERTOUR* recordp;
	EXEC SQL END DECLARE SECTION;

	recordp = (struct C_CUSTOMERTOUR*) record;

	switch( browseid )
	{
		case cCUSTOMERTOUR_BYTOURIDWEEK:
			EXEC SQL FETCH customertourstartbrowse_cur INTO CUSTOMERTOUR_ZEIGER(recordp);
			break;

		case cCUSTOMERTOUR_BYTOURID:
			EXEC SQL FETCH customertourstartbrowse_cur INTO CUSTOMERTOUR_ZEIGER(recordp);
			break;

		case cCUSTOMERTOUR_WHOLEWEEK:
			EXEC SQL FETCH customertourstartbrowse_cur INTO CUSTOMERTOUR_ZEIGER(recordp);
			break;

		case cCUSTOMERTOUR_DEFAULT:
		default:
			EXEC SQL FETCH customertourstartbrowse_cur INTO CUSTOMERTOUR_ZEIGER(recordp);
			break;
	}

	switch( SQLCODE )
	{
		case 0:
			return 0;
		case 100:
			return cDBXR_ENDOFDATA;
		default:
			return cDBXR_IOERROR;
	}
}

/*-------------------------------------------------------------------*/
/* close cursor                                                      */
/*-------------------------------------------------------------------*/
int CustomerTourEndBrowse( int browseid )
{
    UNUSED(browseid);
	EXEC SQL CLOSE customertourstartbrowse_cur;
	EXEC SQL FREE customertourstartbrowse_stmt;
	return 0;
}
