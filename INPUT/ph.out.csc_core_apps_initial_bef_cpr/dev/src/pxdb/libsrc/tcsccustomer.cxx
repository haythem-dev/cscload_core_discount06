#include <stddef.h>
#include <stdio.h>
#include <pxrecord.h>
#include "pxdbfunc.h"
#include "pxdbxx.h"
#include "ndefs.h"
#include "tcsccustomer.h"
#include <pxenv.h>
#include <keys.h>

extern int  functionnr;

int CSCCustomerRead( struct tCSCCUSTOMER* record, const char* dbname )
{
	int retval = cDBXR_NORMAL;

	EXEC SQL BEGIN DECLARE SECTION;
	struct tCSCCUSTOMER* recordp;
	char query[1024] = {' '};
	EXEC SQL END DECLARE SECTION;

	recordp = (struct tCSCCUSTOMER*) record;

	sprintf( query,
		"SELECT FIRST 1 "
			"k.filialnr, "
			"k.idfnr, "
			"k.nameapo, "
			"k.nameinhaber, "
			"k.strasse, "
			"k.ort, "
			"k.postleitzahl, "
			"k.telnr, "
			"k.telnrdafue, "
			"k.faxnr, "
			"k.anredekz, "
			"k.imsbezirknr, "
			"k.kdgruppe, "
			"k.personalnrvertr, "
			"k.stdaufkobuart, "
			"k.tourenkippzeit, "
			"k.kzsprache, "
			"s.skdversandapo, "
			"s.skdsepauft, "
            "s.skdfmd, "
			"k. dafuesystem "
		"FROM %s:kunde k "
		"JOIN %s:kundeschalter s ON s.idfnr=k.idfnr AND s.vertriebszentrumnr=k.filialnr "
		"WHERE k.filialnr = ? AND k.idfnr = ? "
		, dbname, dbname );

	EXEC SQL PREPARE csccustomerread_stmt FROM :query;
	EXEC SQL DECLARE csccustomerread_cur CURSOR WITH HOLD FOR csccustomerread_stmt;

	EXEC SQL OPEN csccustomerread_cur USING
		:recordp->FILIALNR,
		:recordp->IDFNR ;

	EXEC SQL FETCH csccustomerread_cur INTO
		:recordp->FILIALNR,
		:recordp->IDFNR,
		:recordp->NAMEAPO,
		:recordp->NAMEINHABER,
		:recordp->STRASSE,
		:recordp->ORT,
		:recordp->POSTLEITZAHL,
		:recordp->TELNR,
		:recordp->TELNRDAFUE,
		:recordp->FAXNR,
		:recordp->ANREDEKZ,
		:recordp->IMSBEZIRKNR,
		:recordp->KDGRUPPE,
		:recordp->PERSONALNRVERTR,
		:recordp->STDAUFKOBUART,
		:recordp->TOURENKIPPZEIT,
		:recordp->KZSPRACHE,
		:recordp->SKDVERSANDAPO,
		:recordp->SKDSEPAUFT,
        :recordp->SKDFMD,
		:recordp->DAFUESYSTEM;

	switch( SQLCODE )
	{
		case 0:			retval = cDBXR_NORMAL; break;
		case 1:			retval = cDBXR_ISDUPLICATE; break;
		case 100:		retval = cDBXR_NOTFOUND; break;
		default:		retval = cDBXR_IOERROR; break;
	}

	EXEC SQL CLOSE csccustomerread_cur;
	EXEC SQL FREE csccustomerread_stmt;

	return retval;
}

