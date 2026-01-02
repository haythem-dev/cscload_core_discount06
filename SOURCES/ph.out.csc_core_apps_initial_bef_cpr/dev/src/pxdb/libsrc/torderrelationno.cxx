#include <stddef.h>         
#include <stdio.h>          
#include <pxrecord.h>       
#include "pxdbfunc.h"
#include "pxdbxx.h"
#include "ndefs.h"
#include "torderrelationno.h"
#include <pxenv.h>
#include <keys.h>

extern int  functionnr;

#define UNUSED(x) (void)(x)

/*-------------------------------------------------------------------*/
int pxOrderRelationNoStartBrowse( struct tORDERRELATIONNO* record, int browseid )
{
	EXEC SQL BEGIN DECLARE SECTION;
		struct C_ORDERRELATIONNO* recordp;
		char query[2048] = {' '};								
	EXEC SQL END DECLARE SECTION;	

	functionnr = F_ORDERRELATIONNO*10 + F_StartBrowse;		
    recordp = (struct C_ORDERRELATIONNO*) record;			

	switch( browseid )
	{		
		case cCRSORDERRELATIONNO_GETBYTYPE:
			sprintf( query, "SELECT cscorderno, relationnotype, relationno FROM orderrelationno WHERE cscorderno=? AND relationnotype=? ORDER BY relationnotype;" );
			break;

		case cCRSORDERRELATIONNO_GETORDERRELATIONNO:								
		default:			
			sprintf( query, "SELECT cscorderno, relationnotype, relationno FROM orderrelationno WHERE cscorderno=? ORDER BY relationnotype;" );
			break;		
	}

	EXEC SQL PREPARE	pxorderrelationnostartbrowse_stmt FROM :query;
	EXEC SQL DECLARE	pxorderrelationnostartbrowse_cur CURSOR WITH HOLD FOR pxorderrelationnostartbrowse_stmt;

	switch( browseid )
	{		
		case cCRSORDERRELATIONNO_GETBYTYPE:
			EXEC SQL OPEN pxorderrelationnostartbrowse_cur USING :recordp->CSCORDERNO, :recordp->RELATIONNOTYPE;		
			break;

		case cCRSORDERRELATIONNO_GETORDERRELATIONNO:								
		default:	
			EXEC SQL OPEN pxorderrelationnostartbrowse_cur USING :recordp->CSCORDERNO;		
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
int pxOrderRelationNoGetNext( struct tORDERRELATIONNO* record, int browseid )
{
	EXEC SQL BEGIN DECLARE SECTION;
		struct C_ORDERRELATIONNO* recordp;
	EXEC SQL END DECLARE SECTION;
	
	functionnr = F_ORDERRELATIONNO*10 + F_GetNext;		
	recordp = (struct C_ORDERRELATIONNO*) record;

	switch( browseid )
	{				
		case cCRSORDERRELATIONNO_GETBYTYPE:			
		case cCRSORDERRELATIONNO_GETORDERRELATIONNO:								
		default:			
			EXEC SQL FETCH pxorderrelationnostartbrowse_cur INTO	
				:recordp->CSCORDERNO, 
				:recordp->RELATIONNOTYPE, 
				:recordp->RELATIONNO;
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
int pxOrderRelationNoEndBrowse( int browseid )
{
    UNUSED(browseid);
	functionnr = F_ORDERRELATIONNO*10 + F_EndBrowse;		
	EXEC SQL CLOSE pxorderrelationnostartbrowse_cur;
	EXEC SQL FREE pxorderrelationnostartbrowse_stmt;	
	return 0;
}

/*-------------------------------------------------------------------*/
int pxOrderRelationNoRead( struct tORDERRELATIONNO* record )
{
	EXEC SQL BEGIN DECLARE SECTION;
		struct C_ORDERRELATIONNO* recordp;
	EXEC SQL END DECLARE SECTION;
    
	functionnr = F_ORDERRELATIONNO*10 + F_Read;		
	recordp = (struct C_ORDERRELATIONNO*) record;

	EXEC SQL 
		select ORDERRELATIONNO_LISTE
		into ORDERRELATIONNO_ZEIGER( recordp )
		from orderrelationno
		where cscorderno = :recordp->CSCORDERNO
		and relationnotype = :recordp->RELATIONNOTYPE;		

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

/*-------------------------------------------------------------------*/
int pxOrderRelationNoInsert( struct tORDERRELATIONNO* record )
{
    EXEC SQL BEGIN DECLARE SECTION;
		struct C_ORDERRELATIONNO* recordp;
    EXEC SQL END DECLARE SECTION;

	functionnr = F_ORDERRELATIONNO* 10 + F_Insert;	
    recordp = (struct C_ORDERRELATIONNO*) record;

    EXEC SQL insert into orderrelationno(cscorderno, relationnotype, relationno) 
		values ( :recordp->CSCORDERNO, :recordp->RELATIONNOTYPE, :recordp->RELATIONNO );

	switch( SQLCODE )
	{
		case 0:
			return 0;
		case -2601:
			return cDBXR_ISDUPLICATE;
		default:
			return cDBXR_IOERROR;
	} 
}

/*-------------------------------------------------------------------*/
int pxOrderRelationNoUpdate( struct tORDERRELATIONNO* record )
{
	EXEC SQL BEGIN DECLARE SECTION;
		struct C_ORDERRELATIONNO* recordp;
    EXEC SQL END DECLARE SECTION;
    
	functionnr = F_ORDERRELATIONNO * 10 + F_Update;    
    recordp = (struct C_ORDERRELATIONNO*) record;

    EXEC SQL update orderrelationno
		set relationno = :recordp->RELATIONNO
		where cscorderno = :recordp->CSCORDERNO		
		and relationnotype = :recordp->RELATIONNOTYPE;

	switch( SQLCODE )
	{
		case 0:
			return 0;		
		default:
			return cDBXR_IOERROR;
	}   
}

/*-------------------------------------------------------------------*/
int pxOrderRelationNoDelete( struct tORDERRELATIONNO* record )
{
	EXEC SQL BEGIN DECLARE SECTION;
		struct C_ORDERRELATIONNO* recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ORDERRELATIONNO * 10 + F_Delete;    
    recordp = (struct C_ORDERRELATIONNO*) record;

    EXEC SQL delete from orderrelationno		
			where cscorderno = :recordp->CSCORDERNO			
			and relationnotype = :recordp->RELATIONNOTYPE;			

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
