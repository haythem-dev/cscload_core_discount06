#include <stddef.h>         
#include <stdio.h>          
#include <pxrecord.h>       
#include "pxdbfunc.h"
#include "pxdbxx.h"
#include "ndefs.h"
#include "tkdauftragpostour.h"
#include <pxenv.h>
#include <keys.h>

extern int  functionnr;

/*-------------------------------------------------------------------*/
/* open cursor                                                       */
/*-------------------------------------------------------------------*/
int KdAuftragPosTourStartBrowse( struct tKDAUFTRAGPOSTOUR* record, int browseid )
{
	EXEC SQL BEGIN DECLARE SECTION;	
	struct C_KDAUFTRAGPOSTOUR* recordp;
	EXEC SQL END DECLARE SECTION;    

	functionnr = F_KDAUFTRAGPOSTOUR * 10 + F_StartBrowse;

	if( sizeof(struct C_KDAUFTRAGPOSTOUR) != sizeof(struct tKDAUFTRAGPOSTOUR) )
	{
		return cDBXR_DEFINITION;
	}

	recordp = (struct C_KDAUFTRAGPOSTOUR*) record;	
	
	switch( browseid )
	{
		case cKDAUFTRAGPOSTOUR_ORDER:
			EXEC SQL DECLARE C2 CURSOR FOR
			SELECT KDAUFTRAGPOSTOUR_LISTE
			FROM kdauftragpostour 			
			WHERE kdauftragnr = :recordp->KDAUFTRAGNR 
			ORDER BY departuredate, tourid, posnr;
			EXEC SQL OPEN C2;
			break;
		case cCRS_DEFAULT:
		default:
			EXEC SQL DECLARE C1 CURSOR FOR
			SELECT FIRST 1 KDAUFTRAGPOSTOUR_LISTE
			FROM kdauftragpostour 			
			WHERE kdauftragnr = :recordp->KDAUFTRAGNR 
			AND posnr in( 0, :recordp->POSNR) ORDER BY posnr desc;
			EXEC SQL OPEN C1;
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
int KdAuftragPosTourGetNext( struct tKDAUFTRAGPOSTOUR* record, int browseid )
{
	EXEC SQL BEGIN DECLARE SECTION;
	struct C_KDAUFTRAGPOSTOUR* recordp;
	EXEC SQL END DECLARE SECTION;

	functionnr = F_KDAUFTRAGPOSTOUR * 10 + F_GetNext;
	recordp = (struct C_KDAUFTRAGPOSTOUR*) record;

	switch( browseid )
	{		
		case cKDAUFTRAGPOSTOUR_ORDER:
			EXEC SQL FETCH C2 into KDAUFTRAGPOSTOUR_ZEIGER(recordp);
			break;		
		case cCRS_DEFAULT:
		default:
			EXEC SQL FETCH C1 into KDAUFTRAGPOSTOUR_ZEIGER(recordp);
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
int KdAuftragPosTourEndBrowse( int browseid )
{        
	functionnr = F_KDAUFTRAGPOSTOUR * 10 + F_EndBrowse;
	switch( browseid )
	{
		case cKDAUFTRAGPOSTOUR_ORDER:
			EXEC SQL CLOSE C2;
			break;		
		case cCRS_DEFAULT:
		default:
			EXEC SQL CLOSE C1;
			break;		
	}
	return 0;
}

/*-------------------------------------------------------------------*/
/* read                                                              */
/*-------------------------------------------------------------------*/
int KdAuftragPosTourRead( struct tKDAUFTRAGPOSTOUR* record )
{
	EXEC SQL BEGIN DECLARE SECTION;
	struct C_KDAUFTRAGPOSTOUR* recordp;
	EXEC SQL END DECLARE SECTION;

	functionnr = F_KDAUFTRAGPOSTOUR * 10 + F_Read;

	recordp = (struct C_KDAUFTRAGPOSTOUR*) record;

	EXEC SQL 
		select FIRST 1 KDAUFTRAGPOSTOUR_LISTE		
		into KDAUFTRAGPOSTOUR_ZEIGER( recordp )
		from kdauftragpostour
		where kdauftragnr = :recordp->KDAUFTRAGNR
		and posnr in (0, :recordp->POSNR)
		and deliverybranchno = :recordp->DELIVERYBRANCHNO
		order by posnr desc;

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
int KdAuftragPosTourInsert( struct tKDAUFTRAGPOSTOUR* record )
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGPOSTOUR* recordp;
	char query[1024] = {' '};	
    EXEC SQL END DECLARE SECTION;
    
	functionnr = F_KDAUFTRAGPOSTOUR * 10 + F_Insert;
    recordp = (struct C_KDAUFTRAGPOSTOUR*) record;

	sprintf( query,
		"INSERT INTO kdauftragpostour(kdauftragnr, posnr, deliverybranchno, deliverydate, deliverytime, tourid, "
		"departuredate, departuretime, drivingduration, deliverytimebuffer, ibttourid, ibtcustomerno, ibttype, dayibt, ibttourdate) "
		" VALUES ( %ld, %ld, %d, %ld, %d, '%s', %ld, %d, %ld, %d, '%s', %ld, %d, %d, %ld ); "
		, recordp->KDAUFTRAGNR, recordp->POSNR, recordp->DELIVERYBRANCHNO, recordp->DELIVERYDATE, recordp->DELIVERYTIME
		, recordp->TOURID, recordp->DEPARTUREDATE, recordp->DEPARTURETIME, recordp->DRIVINGDURATION, recordp->DELIVERYTIMEBUFFER
		, recordp->IBTTOURID, recordp->IBTCUSTOMERNO, recordp->IBTTYPE, recordp->DAYIBT, recordp->IBTTOURDATE );	

    EXEC SQL INSERT INTO kdauftragpostour(kdauftragnr, posnr, deliverybranchno, deliverydate, deliverytime, tourid, 
		departuredate, departuretime, drivingduration, deliverytimebuffer, ibttourid, ibtcustomerno, ibttype, dayibt, ibttourdate )
		VALUES (	:recordp->KDAUFTRAGNR
				,	:recordp->POSNR
				,	:recordp->DELIVERYBRANCHNO
				,	:recordp->DELIVERYDATE
				,	:recordp->DELIVERYTIME
				,	:recordp->TOURID
				,	:recordp->DEPARTUREDATE
				,	:recordp->DEPARTURETIME
				,	:recordp->DRIVINGDURATION
				,	:recordp->DELIVERYTIMEBUFFER 
				,	:recordp->IBTTOURID
				,	:recordp->IBTCUSTOMERNO
				,	:recordp->IBTTYPE
				,	:recordp->DAYIBT
				,   :recordp->IBTTOURDATE);

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
int KdAuftragPosTourUpdate( struct tKDAUFTRAGPOSTOUR* record )
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGPOSTOUR* recordp;
    EXEC SQL END DECLARE SECTION;
    
	functionnr = F_KDAUFTRAGPOSTOUR * 10 + F_Update;
    recordp = (struct C_KDAUFTRAGPOSTOUR*) record;

    EXEC SQL 
		UPDATE kdauftragpostour
		SET deliverydate = :recordp->DELIVERYDATE
		, deliverytime = :recordp->DELIVERYTIME
		, tourid = :recordp->TOURID
		, departuredate = :recordp->DEPARTUREDATE
		, departuretime = :recordp->DEPARTURETIME
		, drivingduration = :recordp->DRIVINGDURATION
		, deliverytimebuffer = :recordp->DELIVERYTIMEBUFFER
		, ibttourid = :recordp->IBTTOURID
		, ibtcustomerno = :recordp->IBTCUSTOMERNO
		, ibttype = :recordp->IBTTYPE
		, dayibt = :recordp->DAYIBT
		, ibttourdate = :recordp->IBTTOURDATE
		WHERE kdauftragnr = :recordp->KDAUFTRAGNR
		AND posnr = :recordp->POSNR
		AND deliverybranchno = :recordp->DELIVERYBRANCHNO;

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
int KdAuftragPosTourDelete( struct tKDAUFTRAGPOSTOUR* record )
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGPOSTOUR* recordp;
    EXEC SQL END DECLARE SECTION;
    
	functionnr = F_KDAUFTRAGPOSTOUR * 10 + F_Delete;
    recordp = (struct C_KDAUFTRAGPOSTOUR*) record;

	if( 0 == record->LineNo )
	{
		EXEC SQL DELETE FROM kdauftragpostour WHERE kdauftragnr = :recordp->KDAUFTRAGNR AND deliverybranchno = 0;
	}
	else
	{
		EXEC SQL DELETE FROM kdauftragpostour WHERE kdauftragnr = :recordp->KDAUFTRAGNR AND posnr = :recordp->POSNR;		
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
/* delete ibt                                                        */
/*-------------------------------------------------------------------*/
int KdAuftragPosTourDeleteIBT( struct tKDAUFTRAGPOSTOUR* record )
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGPOSTOUR* recordp;
    EXEC SQL END DECLARE SECTION;
    
	functionnr = F_KDAUFTRAGPOSTOUR * 10 + F_Delete;
    recordp = (struct C_KDAUFTRAGPOSTOUR*) record;
	
	EXEC SQL DELETE FROM kdauftragpostour WHERE kdauftragnr = :recordp->KDAUFTRAGNR AND posnr = :recordp->POSNR AND deliverybranchno > 0;		
	
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