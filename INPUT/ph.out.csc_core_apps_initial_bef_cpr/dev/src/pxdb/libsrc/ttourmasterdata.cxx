#include "ndefs.h"
#include "pxdbfunc.h"
#include "ttourmasterdata.h"
#include <stdio.h>

extern int functionnr;

/*-------------------------------------------------------------------*/
int TourMasterDataStartBrowse( struct tTOURMASTERDATA* record, const char* dbName, int browseid)
{
	EXEC SQL BEGIN DECLARE SECTION;
		struct tTOURMASTERDATA* recordp;
		char query[1024] = {' '};	
	EXEC SQL END DECLARE SECTION;	

	functionnr = F_TOUR * 10 + F_StartBrowse;
	recordp = record;
	
	switch( browseid )
	{
		case cCRSTOURMASTERDATA_GETBYTOURID:
		default:
			sprintf( query,
				"SELECT FIRST 1 t.datumkommi, t.filialnr, t.tourid, t.lagrechtour "
				"FROM %s:tour t "
				"WHERE t.filialnr = ? AND t.tourid = ? "
				"ORDER BY t.datumkommi ASC;"
				, dbName );
			break;
	}

	EXEC SQL PREPARE tourmasterdatastartbrowse_stmt FROM :query;
	EXEC SQL DECLARE tourmasterdatastartbrowse_cur CURSOR WITH HOLD FOR tourmasterdatastartbrowse_stmt;

	switch( browseid )
	{
		case cCRSTOURMASTERDATA_GETBYTOURID:
		default:
			EXEC SQL OPEN tourmasterdatastartbrowse_cur USING
				:recordp->BranchNo,
				:recordp->TourID;
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
int TourMasterDataGetNext(struct tTOURMASTERDATA* record, int browseid)
{
	EXEC SQL BEGIN DECLARE SECTION;
	struct tTOURMASTERDATA* recordp;
	EXEC SQL END DECLARE SECTION;
	
	functionnr = F_TOUR * 10 + F_GetNext;
	recordp = record;

	switch( browseid )
	{		
		case cCRSTOURMASTERDATA_GETBYTOURID:
		default:
			EXEC SQL FETCH tourmasterdatastartbrowse_cur INTO :recordp->PickingDate, :recordp->BranchNo, :recordp->TourID, :recordp->DecTour;
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
int TourMasterDataEndBrowse(int browseid)
{        
	functionnr = F_TOUR * 10 + F_EndBrowse;

	switch( browseid )
	{
		case cCRSTOURMASTERDATA_GETBYTOURID:
		default:
			EXEC SQL CLOSE tourmasterdatastartbrowse_cur;
			EXEC SQL FREE tourmasterdatastartbrowse_stmt;	
	}

	return 0;
}
