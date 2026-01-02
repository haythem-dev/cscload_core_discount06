/*(c)
 ********************* PHARMX Customer Order Entry Server *********************


	Embedded SQL for C application


	FILE: tcustrou.c (.sqc)

	Database functions




	FUNCTIONS:

		pxCustRoutingStartBrowse  declare and open Cursor
		pxCustRoutingGetNext      get next record
		pxCustRoutingEndBrowse    close cursor
		pxCustRoutingRead         get one record
		pxCustRoutingReadLock     get one record with lock
		pxCustRoutingInsert       Insert record
		pxCustRoutingUpdate       Update record
		pxCustRoutingDelete       Delete record


REVISION HISTORY

25 Jun 2004 V1.00 REV 00 written by Ysbrand Bouma

*/


#include <stddef.h>         /* standard C run-time header */
#include <stdio.h>          /* standard C run-time header */
#include <string.h>
#include <pxrecord.h>       /* all record structures */
#include "pxdbxx.h"
#include "pxdbfunc.h"
#include <ndefs.h>
#include <pxenv.h>
#include <tcustrou.h>
#include <keys.h>

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxCustRoutingStartBrowse                                   */
/*                                                                   */
/*      Declare and Open a Cursor   (general)                        */
/*                                                                   */
/*  PARAMETERS:                                                      */
/*                                                                   */
/*      record buffer                                                */
/*                                                                   */
/*  RETURNS: 0 if successful, 1 if error                             */
/*                                                                   */
/*  COMMENTS:                                                        */
/*                                                                   */
/*-------------------------------------------------------------------*/
int pxCustRoutingStartBrowse
(
	 struct tCUSTOMERROUTING* record,
	 int browseid
)
{
	EXEC SQL BEGIN DECLARE SECTION;
	struct C_CUSTOMERROUTING * recordp;
	EXEC SQL END   DECLARE SECTION;

	functionnr = F_CUSTOMERROUTING*10+F_StartBrowse;
	recordp = (struct C_CUSTOMERROUTING *) record;

	if (!(sizeof(struct C_CUSTOMERROUTING) == sizeof(struct tCUSTOMERROUTING)))
	   return cDBXR_DEFINITION;

	EXEC SQL DECLARE C3 CURSOR FOR
			SELECT CUSTOMERROUTING_LISTE 
			FROM customerrouting 
			WHERE customerno = :recordp->CUSTOMERNO
			AND destbranchno = :recordp->DESTBRANCHNO
			AND timefrom < :recordp->TIMEFROM
			AND weekday = :recordp->WEEKDAY;

	EXEC SQL DECLARE C2 CURSOR FOR
			SELECT CUSTOMERROUTING_LISTE 
			FROM customerrouting 
			WHERE branchno = :recordp->BRANCHNO
			AND customerno = :recordp->CUSTOMERNO
			AND destbranchno = :recordp->DESTBRANCHNO
			AND timefrom > :recordp->TIMEFROM
			AND weekday = :recordp->WEEKDAY;

	EXEC SQL DECLARE C1 CURSOR FOR
		SELECT CUSTOMERROUTING_LISTE from CUSTOMERROUTING DWtcustrou;

	EXEC SQL DECLARE C0 CURSOR FOR
		SELECT CUSTOMERROUTING_LISTE from CUSTOMERROUTING;

	switch (browseid)
	{
		case cCRSCUSTOMERROUTING_ISROUTED:
			EXEC SQL OPEN C3;
			break;
		case cCRSCUSTOMERROUTING_HASROUTINGSTARTINGTODAY:
			EXEC SQL OPEN C2;
			break;
		case cCRS_NOWHERE:
			  EXEC SQL OPEN C0;
		  break;
	   default:
		  EXEC SQL OPEN C1;
		  break;
	}
	if (SQLCODE == 0)        return 0;
	if (SQLCODE == 100)      return cDBXR_NOTFOUND;
	return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxCustRoutingGetNext                                       */
/*                                                                   */
/*      Fetch for a Cursor   (general)                               */
/*                                                                   */
/*  PARAMETERS:                                                      */
/*      record buffer                                                */
/*                                                                   */
/*  RETURNS: 0 if successful, 1 if error                             */
/*                                                                   */
/*  COMMENTS:                                                        */
/*                                                                   */
/*-------------------------------------------------------------------*/
int pxCustRoutingGetNext
(
	struct tCUSTOMERROUTING* record,
	int browseid
)
{
	EXEC SQL BEGIN DECLARE SECTION;
	struct C_CUSTOMERROUTING * recordp;
	EXEC SQL END   DECLARE SECTION;

	functionnr = F_CUSTOMERROUTING*10+F_GetNext;
	recordp = (struct C_CUSTOMERROUTING *) record;

	switch (browseid)
	{
		case cCRSCUSTOMERROUTING_ISROUTED:
			EXEC SQL FETCH C3 into CUSTOMERROUTING_ZEIGER(recordp);
			break;
		case cCRSCUSTOMERROUTING_HASROUTINGSTARTINGTODAY:
			EXEC SQL FETCH C2 into CUSTOMERROUTING_ZEIGER(recordp);
			break;
	   case cCRS_NOWHERE:
		  EXEC SQL FETCH C0
		  into CUSTOMERROUTING_ZEIGER(recordp);
		  break;
	   default:
		  EXEC SQL FETCH C1
		  into CUSTOMERROUTING_ZEIGER(recordp);
		  break;
	}
	if (SQLCODE == 0)    return 0;
	if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
	return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxCustRoutingEndBrowse                                     */
/*                                                                   */
/*      Close a Cursor   (general)                                   */
/*                                                                   */
/*  PARAMETERS:                                                      */
/*                                                                   */
/*                                                                   */
/*  RETURNS: 0 if successful, 1 if error                             */
/*                                                                   */
/*  COMMENTS:                                                        */
/*                                                                   */
/*-------------------------------------------------------------------*/
int pxCustRoutingEndBrowse
(
	int browseid
)
{
	functionnr = F_CUSTOMERROUTING*10+F_EndBrowse;

	/* close the cursor */
	switch (browseid)
	{
		case cCRSCUSTOMERROUTING_ISROUTED:
			EXEC SQL CLOSE C3;
			break;
		case cCRSCUSTOMERROUTING_HASROUTINGSTARTINGTODAY:
			EXEC SQL CLOSE C2;
			break;
	   case cCRS_NOWHERE:
		  EXEC SQL CLOSE C0;
		  break;
	   default:
		  EXEC SQL CLOSE C1;
		  break;
	}
	return 0;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxCustRoutingRead                                          */
/*                                                                   */
/*      Get one record                                               */
/*                                                                   */
/*  PARAMETERS:                                                      */
/*                                                                   */
/*      record buffer                                                */
/*                                                                   */
/*  RETURNS: 0 if successful, 1 if error                             */
/*                                                                   */
/*  COMMENTS:                                                        */
/*                                                                   */
/*-------------------------------------------------------------------*/

int pxCustRoutingRead
(
	struct tCUSTOMERROUTING* record
)
{
	EXEC SQL BEGIN DECLARE SECTION;
	struct C_CUSTOMERROUTING * recordp;
	EXEC SQL END DECLARE SECTION;

	functionnr = F_CUSTOMERROUTING*10+F_Read;
	recordp = (struct C_CUSTOMERROUTING *) record;

	EXEC SQL SELECT
		CUSTOMERROUTING_LISTE
	 into CUSTOMERROUTING_ZEIGER(recordp)
	 from CUSTOMERROUTING
	 where PKtcustrou;

	if (SQLCODE == 0)
	{
	   return 0;
	}
	else
	{
	   if (SQLCODE == 1)                /* found, but more than 1 exists */
	   {
		  return cDBXR_ISDUPLICATE;
	   }
	   if (SQLCODE == 100)
		  return cDBXR_NOTFOUND;
	   return cDBXR_IOERROR;
	}

}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxCustRoutingReadLock                                      */
/*                                                                   */
/*      Get one record with lock                                     */
/*                                                                   */
/*  PARAMETERS:                                                      */
/*                                                                   */
/*      record buffer                                                */
/*                                                                   */
/*  RETURNS: 0 if successful, 1 if error                             */
/*                                                                   */
/*  COMMENTS:                                                        */
/*                                                                   */
/*-------------------------------------------------------------------*/
int pxCustRoutingReadLock
(
	struct tCUSTOMERROUTING* record
)
{
	EXEC SQL BEGIN DECLARE SECTION;
	struct C_CUSTOMERROUTING * recordp;
	EXEC SQL END DECLARE SECTION;

	functionnr = F_CUSTOMERROUTING*10+F_ReadLock;
	recordp = (struct C_CUSTOMERROUTING *) record;

	EXEC SQL DECLARE TCUSTROU_U1 CURSOR WITH HOLD FOR
		SELECT
		CUSTOMERROUTING_LISTE
	from CUSTOMERROUTING
	where PKtcustrou
	FOR UPDATE;
	EXEC SQL OPEN TCUSTROU_U1;
	if (SQLCODE == 0)
	{
	  EXEC SQL FETCH TCUSTROU_U1
	  into CUSTOMERROUTING_ZEIGER(recordp)
	  ;
	}

	if (SQLCODE == 0)
	{
	   return 0;
	}
	else
	{
	   if (SQLCODE == 1)                /* found, but more than 1 exists */
	   {
		  return cDBXR_ISDUPLICATE;
	   }
	   if (SQLCODE == 100)
		  return cDBXR_NOTFOUND;
	   return cDBXR_IOERROR;
	}

}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxCustRoutingUpdate                                        */
/*                                                                   */
/*      Update  record                                               */
/*                                                                   */
/*  PARAMETERS:                                                      */
/*                                                                   */
/*      record buffer                                                */
/*                                                                   */
/*  RETURNS: 0 if successful, 1 if error                             */
/*                                                                   */
/*  COMMENTS:                                                        */
/*                                                                   */
/*-------------------------------------------------------------------*/

int pxCustRoutingUpdate
(
	struct tCUSTOMERROUTING* record
)
{
	EXEC SQL BEGIN DECLARE SECTION;
	struct C_CUSTOMERROUTING * recordp;
	EXEC SQL END DECLARE SECTION;

	functionnr = F_CUSTOMERROUTING*10+F_Update;
	recordp = (struct C_CUSTOMERROUTING *) record;

	EXEC SQL UPDATE
	CUSTOMERROUTING
	SET
	CUSTOMERROUTING_UPDATE(recordp)
	where current of TCUSTROU_U1
	;
	if (SQLCODE == 0)
	{
	  EXEC SQL CLOSE TCUSTROU_U1;
	}

	if (SQLCODE == 0)
	{
	   return 0;
	}
	else
	{
	   return cDBXR_IOERROR;
	}
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxCustRoutingInsert                                       */
/*                                                                   */
/*      Insert  record                                               */
/*                                                                   */
/*  PARAMETERS:                                                      */
/*                                                                   */
/*      record buffer                                                */
/*                                                                   */
/*  RETURNS: 0 if successful, 1 if error                             */
/*                                                                   */
/*  COMMENTS:                                                        */
/*                                                                   */
/*-------------------------------------------------------------------*/
int pxCustRoutingInsert
(
	struct tCUSTOMERROUTING* record
)
{
	EXEC SQL BEGIN DECLARE SECTION;
	struct C_CUSTOMERROUTING * recordp;
	EXEC SQL END DECLARE SECTION;

	functionnr = F_CUSTOMERROUTING*10+F_Insert;
	recordp = (struct C_CUSTOMERROUTING *) record;

	EXEC SQL INSERT INTO
	CUSTOMERROUTING
	(CUSTOMERROUTING_LISTE)
	VALUES ( CUSTOMERROUTING_ZEIGER(recordp) );

	if (SQLCODE == 0)
	{
	   return 0;
	}
	if (SQLCODE == -2601)
	{
	   return cDBXR_ISDUPLICATE;
	}
	return cDBXR_IOERROR;
}

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxCustRoutingDelete                                        */
/*                                                                   */
/*      delete  record                                               */
/*                                                                   */
/*  PARAMETERS:                                                      */
/*                                                                   */
/*      record buffer                                                */
/*                                                                   */
/*  RETURNS: 0 if successful, else error                             */
/*                                                                   */
/*  COMMENTS:                                                        */
/*                                                                   */
/*-------------------------------------------------------------------*/

int pxCustRoutingDelete
(
	struct tCUSTOMERROUTING* record
)
{
	EXEC SQL BEGIN DECLARE SECTION;
	struct C_CUSTOMERROUTING * recordp;
	EXEC SQL END DECLARE SECTION;

	functionnr = F_CUSTOMERROUTING*10+F_Delete;
	recordp = (struct C_CUSTOMERROUTING *) record;

	EXEC SQL DELETE FROM
	CUSTOMERROUTING
	where PKtcustrou;

	if (SQLCODE == 0)
	{
	   return 0;
	}
	else
	{
	   if (SQLCODE == 100)
		  return cDBXR_NOTFOUND;
	   return cDBXR_IOERROR;
	}
}
