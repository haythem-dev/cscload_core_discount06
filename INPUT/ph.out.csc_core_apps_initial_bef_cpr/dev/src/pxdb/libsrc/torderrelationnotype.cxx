#include <stddef.h>
#include <stdio.h>
#include <pxrecord.h>
#include "pxdbfunc.h"
#include "pxdbxx.h"
#include "ndefs.h"
#include <pxenv.h>
#include <torderrelationnotypes.h>
#include <keys.h>

extern int functionnr;

#define UNUSED(x) (void)(x)

/*--------------------------------------------------------------------------------------------------*/
int pxOrderRelationNoTypesStartBrowse ( struct tORDERRELATIONNOTYPES* record, int browseid )
{
	EXEC SQL BEGIN DECLARE SECTION;
		char query[2048] = {' '};								
	EXEC SQL END DECLARE SECTION;	

    UNUSED(record);

	functionnr = F_ORDERRELATIONNOTYPES*10 + F_StartBrowse;

	switch( browseid )
	{		
		case cCRSORDERRELATIONNOTYPES:								
		default:			
			sprintf( query,
				"SELECT o.relationnotype, o.relationdescription "
				"FROM orderrelationnotypes o " 
				"ORDER BY o.relationnotype ASC; "
			);
			break;		
	}

	EXEC SQL PREPARE pxorderrelationnotypesstartbrowse_stmt FROM :query;
	EXEC SQL DECLARE pxorderrelationnotypesstartbrowse_cur CURSOR WITH HOLD FOR pxorderrelationnotypesstartbrowse_stmt;
	EXEC SQL OPEN pxorderrelationnotypesstartbrowse_cur; 

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
/*--------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------*/
int pxOrderRelationNoTypesGetNext( struct tORDERRELATIONNOTYPES* record, int browseid )
{
    EXEC SQL BEGIN DECLARE SECTION;
		struct C_ORDERRELATIONNOTYPES * recordp;
    EXEC SQL END   DECLARE SECTION;
    
	functionnr = F_ORDERRELATIONNOTYPES*10 + F_GetNext;
    recordp = (struct C_ORDERRELATIONNOTYPES *) record;

	switch( browseid )
	{
		case cCRSORDERRELATIONNOTYPES:								
		default:
			EXEC SQL FETCH pxorderrelationnotypesstartbrowse_cur INTO ORDERRELATIONNOTYPES_ZEIGER( recordp );
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
/*--------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------*/
int pxOrderRelationNoTypesEndBrowse( int browseid )
{
	functionnr = F_ORDERRELATIONNOTYPES*10 + F_EndBrowse;

	switch( browseid )
	{
		default:
			EXEC SQL CLOSE pxorderrelationnotypesstartbrowse_cur;			
			break;
	}

    return 0;
}
/*--------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------*/
int pxOrderRelationNoTypesRead( struct tORDERRELATIONNOTYPES* record )
{	
	EXEC SQL BEGIN DECLARE SECTION;
		struct C_ORDERRELATIONNOTYPES* recordp;
	EXEC SQL END DECLARE SECTION;
    
	functionnr = F_ORDERRELATIONNOTYPES*10 + F_Read;
	recordp = (struct C_ORDERRELATIONNOTYPES*) record;

	EXEC SQL 
		select ORDERRELATIONNOTYPES_LISTE
		into ORDERRELATIONNOTYPES_ZEIGER( recordp )
		from orderrelationnotypes
		where relationnotype = :recordp->RELATIONNOTYPE;

	switch( SQLCODE )
	{
		case 0:
			return 0;
		case 1:
			return cDBXR_ISDUPLICATE;
		case 100:
			return cDBXR_NOTFOUND;
		default:
			return cDBXR_IOERROR;
	}   
}
/*--------------------------------------------------------------------------------------------------*/
