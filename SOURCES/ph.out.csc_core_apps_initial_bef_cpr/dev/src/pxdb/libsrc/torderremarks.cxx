#include <stddef.h>         
#include <stdio.h>          
#include <pxrecord.h>       
#include "pxdbfunc.h"
#include "pxdbxx.h"
#include "ndefs.h"
#include "torderremarks.h"
#include <pxenv.h>
#include <keys.h>

extern int  functionnr;

/*-------------------------------------------------------------------*/
/* open cursor                                                       */
/*-------------------------------------------------------------------*/
int pxGenericOrderRemarkStartBrowse( struct tORDERREMARKS* record, int browseid )
{
	EXEC SQL BEGIN DECLARE SECTION;	
	struct C_ORDERREMARKS* recordp;
	EXEC SQL END DECLARE SECTION;
    
	recordp = (struct C_ORDERREMARKS*) record;

	if( sizeof(struct C_ORDERREMARKS) != sizeof(struct tORDERREMARKS) )
	{
		return cDBXR_DEFINITION;
	}
	
	#ifndef pxDATABASE_INFORMIX
		EXEC SQL SET CURSORTYPE CUR_BROWSE;
	#endif

	// open cursor by browseid
	switch( browseid )
	{
		case cCRSORDERREMARKS_GETALLORDERLINEREMARKSBYTYPE:
			EXEC SQL DECLARE C3 CURSOR FOR
				SELECT cscorderno, positionno, remarktype, textnumber, remarktext
				FROM orderremarks
				WHERE cscorderno = :recordp->CSCORDERNO				
				AND positionno = :recordp->POSITIONNO
				AND remarktype = :recordp->REMARKTYPE
				AND remarktype IN (SELECT remarktype FROM orderremarktypes)
				ORDER BY cscorderno, positionno, remarktype, textnumber
				#ifndef pxDATABASE_INFORMIX
					FOR BROWSE;
				#else
					;
				#endif
			EXEC SQL OPEN C3;		
			break;


		case cCRSORDERREMARKS_GETALLORDERREMARKSBYTYPE:
			EXEC SQL DECLARE C2 CURSOR FOR
				SELECT cscorderno, positionno, remarktype, textnumber, remarktext
				FROM orderremarks
				WHERE cscorderno = :recordp->CSCORDERNO								
				AND remarktype = :recordp->REMARKTYPE
				AND remarktype IN (SELECT remarktype FROM orderremarktypes)
				ORDER BY cscorderno, positionno, remarktype, textnumber
				#ifndef pxDATABASE_INFORMIX
					FOR BROWSE;
				#else
					;
				#endif
			EXEC SQL OPEN C2;		
			break;

		case cCRSORDERREMARKS_GETALLORDERLINEREMARKS:
			EXEC SQL DECLARE C1 CURSOR FOR
				SELECT cscorderno, positionno, remarktype, textnumber, remarktext
				FROM orderremarks
				WHERE cscorderno = :recordp->CSCORDERNO				
				AND positionno = :recordp->POSITIONNO
				AND remarktype IN (SELECT remarktype FROM orderremarktypes)
				ORDER BY cscorderno, positionno, remarktype, textnumber
				#ifndef pxDATABASE_INFORMIX
					FOR BROWSE;
				#else
					;
				#endif
			EXEC SQL OPEN C1;		
			break;

		case cCRSORDERREMARKS_GETALLORDERREMARKS:
		default:
			EXEC SQL DECLARE C0 CURSOR FOR
				SELECT cscorderno, positionno, remarktype, textnumber, remarktext
				FROM orderremarks
				WHERE cscorderno = :recordp->CSCORDERNO				
				AND remarktype IN (SELECT remarktype FROM orderremarktypes)
				ORDER BY cscorderno, positionno, remarktype, textnumber
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
int pxGenericOrderRemarkGetNext( struct tORDERREMARKS* record, int browseid )
{
	EXEC SQL BEGIN DECLARE SECTION;
	struct C_ORDERREMARKS* recordp;
	EXEC SQL END DECLARE SECTION;
	
	recordp = (struct C_ORDERREMARKS*) record;

	switch( browseid )
	{    	
		case cCRSORDERREMARKS_GETALLORDERLINEREMARKSBYTYPE:
			EXEC SQL FETCH C3 into ORDERREMARKS_ZEIGER(recordp);
			break;					

		case cCRSORDERREMARKS_GETALLORDERREMARKSBYTYPE:
			EXEC SQL FETCH C2 into ORDERREMARKS_ZEIGER(recordp);
			break;					

		case cCRSORDERREMARKS_GETALLORDERLINEREMARKS:
			EXEC SQL FETCH C1 into ORDERREMARKS_ZEIGER(recordp);
			break;					

		case cCRSORDERREMARKS_GETALLORDERREMARKS:
		default:
			EXEC SQL FETCH C0 into ORDERREMARKS_ZEIGER(recordp);
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
int pxGenericOrderRemarkEndBrowse( int browseid )
{        
	switch( browseid )
	{		
		case cCRSORDERREMARKS_GETALLORDERLINEREMARKSBYTYPE:
			EXEC SQL CLOSE C3;
			break;

		case cCRSORDERREMARKS_GETALLORDERREMARKSBYTYPE:
			EXEC SQL CLOSE C2;
			break;

		case cCRSORDERREMARKS_GETALLORDERLINEREMARKS:
			EXEC SQL CLOSE C1;
			break;

		case cCRSORDERREMARKS_GETALLORDERREMARKS:
		default:
			EXEC SQL CLOSE C0;
			break;
	}
	return 0;
}

/*-------------------------------------------------------------------*/
/* read                                                              */
/*-------------------------------------------------------------------*/
int pxGenericOrderRemarkRead( struct tORDERREMARKS* record )
{
	EXEC SQL BEGIN DECLARE SECTION;
	struct C_ORDERREMARKS* recordp;
	EXEC SQL END DECLARE SECTION;

    functionnr = F_ORDERREMARKS * 10 + F_Read;
	recordp = (struct C_ORDERREMARKS*) record;

	EXEC SQL 
		select ORDERREMARKS_LISTE
		into ORDERREMARKS_ZEIGER( recordp )
		from orderremarks
		where cscorderno = :recordp->CSCORDERNO
		and positionno = :recordp->POSITIONNO
		and remarktype = :recordp->REMARKTYPE
		and textnumber = :recordp->TEXTNUMBER;

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
/* insert                                                            */
/*-------------------------------------------------------------------*/
int pxGenericOrderRemarkInsert( struct tORDERREMARKS* record )
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ORDERREMARKS* recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ORDERREMARKS * 10 + F_Insert;
    recordp = (struct C_ORDERREMARKS*) record;

    EXEC SQL insert into orderremarks(cscorderno, positionno, remarktype, textnumber, remarktext) values ( 
		:recordp->CSCORDERNO,
		:recordp->POSITIONNO,
		:recordp->REMARKTYPE,
		:recordp->TEXTNUMBER,		
		:recordp->REMARKTEXT );

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
/* update                                                            */
/*-------------------------------------------------------------------*/
int pxGenericOrderRemarkUpdate( struct tORDERREMARKS* record )
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ORDERREMARKS* recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ORDERREMARKS * 10 + F_Update;
    recordp = (struct C_ORDERREMARKS*) record;

    EXEC SQL update orderremarks
		set remarktext= :recordp->REMARKTEXT
		where cscorderno = :recordp->CSCORDERNO
		and positionno = :recordp->POSITIONNO
		and remarktype = :recordp->REMARKTYPE
		and textnumber = :recordp->TEXTNUMBER;

	switch( SQLCODE )
	{
		case 0:
			return 0;		
		default:
			return cDBXR_IOERROR;
	}        
}


/*-------------------------------------------------------------------*/
/* delete                                                            */
/*-------------------------------------------------------------------*/
int pxGenericOrderRemarkDelete( struct tORDERREMARKS* record )
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ORDERREMARKS* recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ORDERREMARKS * 10 + F_Delete;
    recordp = (struct C_ORDERREMARKS*) record;

    EXEC SQL delete from orderremarks		
			where cscorderno = :recordp->CSCORDERNO
			and positionno = :recordp->POSITIONNO
			and remarktype = :recordp->REMARKTYPE;			

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
