#include <stddef.h>         
#include <stdio.h>          
#include <pxrecord.h>       
#include "pxdbfunc.h"
#include "pxdbxx.h"
#include "ndefs.h"
#include "torderremarktypes.h"
#include <pxenv.h>
#include <keys.h>

extern int  functionnr;

#define UNUSED(x) (void)(x)

/*-------------------------------------------------------------------*/
/* open cursor                                                       */
/*-------------------------------------------------------------------*/
int pxOrderRemarkTypesStartBrowse( struct tORDERREMARKTYPES* record, int browseid )
{
	EXEC SQL BEGIN DECLARE SECTION;	
	EXEC SQL END DECLARE SECTION;

    UNUSED(record);

	if( sizeof(struct C_ORDERREMARKTYPES) != sizeof(struct tORDERREMARKTYPES) )
	{
		return cDBXR_DEFINITION;
	}
	
	#ifndef pxDATABASE_INFORMIX
		EXEC SQL SET CURSORTYPE CUR_BROWSE;
	#endif

	// open cursor by browseid
	switch( browseid )
	{
		case cCRSORDERREMARKTYPES_GETHEADERORDERREMARKTYPES:
			EXEC SQL DECLARE C1 CURSOR FOR
				SELECT remarktype, level, remarkname 
				FROM orderremarktypes
				WHERE level in (0, 2)
				ORDER BY remarktype		
				#ifndef pxDATABASE_INFORMIX
					FOR BROWSE;
				#else
					;
				#endif
			EXEC SQL OPEN C1;
			break;
		case cCRSORDERREMARKTYPES_GETLINEORDERREMARKTYPES:
			EXEC SQL DECLARE C2 CURSOR FOR
				SELECT remarktype, level, remarkname 
				FROM orderremarktypes
				WHERE level in (1, 2)
				ORDER BY remarktype		
				#ifndef pxDATABASE_INFORMIX
					FOR BROWSE;
				#else
					;
				#endif
			EXEC SQL OPEN C2;
			break;
		case cCRSORDERREMARKTYPES_GETALLORDERREMARKTYPES:
		default:
			EXEC SQL DECLARE C0 CURSOR FOR
				SELECT remarktype, level, remarkname 
				FROM orderremarktypes				
				ORDER BY remarktype		
				#ifndef pxDATABASE_INFORMIX
					FOR BROWSE;
				#else
					;
				#endif
			EXEC SQL OPEN C0;
			break;		
	}

	// check SQLCODE
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
int pxOrderRemarkTypesGetNext( struct tORDERREMARKTYPES* record, int browseid )
{
	EXEC SQL BEGIN DECLARE SECTION;
	struct C_ORDERREMARKTYPES* recordp;
	EXEC SQL END DECLARE SECTION;
	
	recordp = (struct C_ORDERREMARKTYPES*) record;

	switch( browseid )
	{    		
		case cCRSORDERREMARKTYPES_GETALLORDERREMARKTYPES:
			EXEC SQL FETCH C0 into ORDERREMARKTYPES_ZEIGER(recordp);
			break;
		case cCRSORDERREMARKTYPES_GETHEADERORDERREMARKTYPES:
			EXEC SQL FETCH C1 into ORDERREMARKTYPES_ZEIGER(recordp);
			break;
		case cCRSORDERREMARKTYPES_GETLINEORDERREMARKTYPES:
			EXEC SQL FETCH C2 into ORDERREMARKTYPES_ZEIGER(recordp);
			break;
		default:
			EXEC SQL FETCH C0 into ORDERREMARKTYPES_ZEIGER(recordp);
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
int pxOrderRemarkTypesEndBrowse( int browseid )
{        
	switch( browseid )
	{		
		case cCRSORDERREMARKTYPES_GETALLORDERREMARKTYPES:
			EXEC SQL CLOSE C0;
			break;
		case cCRSORDERREMARKTYPES_GETHEADERORDERREMARKTYPES:
			EXEC SQL CLOSE C1;
			break;
		case cCRSORDERREMARKTYPES_GETLINEORDERREMARKTYPES:
			EXEC SQL CLOSE C2;
			break;
		default:
			EXEC SQL CLOSE C0;
			break;
	}
	return 0;
}

/*-------------------------------------------------------------------*/
/* read                                                              */
/*-------------------------------------------------------------------*/
int pxOrderRemarkTypesRead( struct tORDERREMARKTYPES* record )
{
	EXEC SQL BEGIN DECLARE SECTION;
	struct C_ORDERREMARKTYPES* recordp;
	EXEC SQL END DECLARE SECTION;

    functionnr = F_ORDERREMARKTYPES * 10 + F_Read;
	recordp = (struct C_ORDERREMARKTYPES*) record;

	EXEC SQL 
		select ORDERREMARKTYPES_LISTE
		into ORDERREMARKTYPES_ZEIGER( recordp )
		from orderremarktypes
		where remarktype = :recordp->REMARKTYPE
		and level = :recordp->LEVEL;

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
/* insert                                                              */
/*-------------------------------------------------------------------*/
int pxOrderRemarkTypesInsert( struct tORDERREMARKTYPES* record )
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ORDERREMARKTYPES* recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ORDERREMARKTYPES * 10 + F_Insert;
    recordp = (struct C_ORDERREMARKTYPES*) record;

    EXEC SQL insert into orderremarktypes(remarktype, level, remarkname) values ( 
		(SELECT NVL(max(remarktype)+1, 0) FROM orderremarktypes), 
		:recordp->LEVEL, 
		:recordp->REMARKNAME);

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
