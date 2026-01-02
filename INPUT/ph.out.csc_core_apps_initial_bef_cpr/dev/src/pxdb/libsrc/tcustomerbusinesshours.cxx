#include <stddef.h>         
#include <stdio.h>          
#include <pxrecord.h>       
#include "pxdbfunc.h"
#include "pxdbxx.h"
#include "ndefs.h"
#include "tcustomerbusinesshours.h"
#include <pxenv.h>
#include <keys.h>

extern int  functionnr;

#define UNUSED(x) (void)(x)

/*-------------------------------------------------------------------*/
/* open cursor                                                       */
/*-------------------------------------------------------------------*/
int CustomerBusinessHoursStartBrowse( struct tCUSTOMERBUSINESSHOURS* record, const char* dbName, int browseid )
{
	EXEC SQL BEGIN DECLARE SECTION;	
	struct C_CUSTOMERBUSINESSHOURS* recordp;
	char query[1024] = {' '};	
	EXEC SQL END DECLARE SECTION;   
		
	recordp = (struct C_CUSTOMERBUSINESSHOURS*) record;	
		
	switch( browseid )
	{
		case cCUSTOMERBUSINESSHOURS_DEFAULT:
		default:
			sprintf( query, 
				"select a.vertriebszentrumnr, a.idfnr, a.weekday "
				", case when (a.zeitbeginpm > 0 and a.zeitbeginam > a.zeitbeginpm) or (a.zeitbeginam = 0 and a.zeitbeginpm > 0) then a.zeitbeginpm else a.zeitbeginam end as businesshoursstart "
				", case when a.zeitendepm > a.zeitendeam then a.zeitendepm else a.zeitendeam end as businesshoursend "
				"from %s:kdbetriebsende a where a.vertriebszentrumnr = ? and a.idfnr = ? order by a.weekday asc; "
				, dbName );
			break;		
	}

	EXEC SQL PREPARE customerbusinesshoursstartbrowse_stmt FROM :query;
	EXEC SQL DECLARE customerbusinesshoursstartbrowse_cur CURSOR WITH HOLD FOR customerbusinesshoursstartbrowse_stmt;

	switch( browseid )
	{
		case cCUSTOMERBUSINESSHOURS_DEFAULT:
		default:
			EXEC SQL OPEN customerbusinesshoursstartbrowse_cur USING :recordp->BRANCHNO, :recordp->CUSTOMERNO;			
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
int CustomerBusinessHoursGetNext( struct tCUSTOMERBUSINESSHOURS* record, int browseid )
{
	EXEC SQL BEGIN DECLARE SECTION;
	struct C_CUSTOMERBUSINESSHOURS* recordp;
	EXEC SQL END DECLARE SECTION;
	
	recordp = (struct C_CUSTOMERBUSINESSHOURS*) record;

	switch( browseid )
	{				
		case cCUSTOMERBUSINESSHOURS_DEFAULT:
		default:
			EXEC SQL FETCH customerbusinesshoursstartbrowse_cur INTO	
				:recordp->BRANCHNO, 
				:recordp->CUSTOMERNO, 
				:recordp->WEEKDAY, 
				:recordp->BUSINESSHOURSSTART, 				
				:recordp->BUSINESSHOURSEND;
			break;		
	}

	switch( SQLCODE )
	{
		case 0:		return 0;
		case 100:	return cDBXR_ENDOFDATA;
		default:	return cDBXR_IOERROR;
	}		
}

/*-------------------------------------------------------------------*/
/* close cursor                                                      */
/*-------------------------------------------------------------------*/
int CustomerBusinessHoursEndBrowse( int browseid )
{
    UNUSED(browseid);
	EXEC SQL CLOSE customerbusinesshoursstartbrowse_cur;
	EXEC SQL FREE customerbusinesshoursstartbrowse_stmt;	
	return 0;
}


