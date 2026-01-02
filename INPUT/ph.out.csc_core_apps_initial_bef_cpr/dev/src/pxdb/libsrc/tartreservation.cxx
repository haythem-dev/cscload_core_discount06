
#include <stdio.h>          /* standard C run-time header */
#include <string.h>
#include <pxrecord.h>       /* all record structures */
#include "pxdbxx.h"
#include "pxdbfunc.h"
#include <ndefs.h>
#include <pxenv.h>
#include <tartreservation.h>
#include <keys.h>

/* Global variables */
extern int functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxArtReservationStartBrowse                                   */
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
int pxArtReservationStartBrowse
(
     struct tARTICLERESERVATION* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTICLERESERVATION * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_ARTICLERESERVATION*10+F_StartBrowse;
    recordp = (struct C_ARTICLERESERVATION *) record;

    if (!(sizeof(struct C_ARTICLERESERVATION) == sizeof(struct tARTICLERESERVATION)))
       return cDBXR_DEFINITION;

    switch (browseid)
    {
       case cCRS_NOWHERE:
         EXEC SQL DECLARE C0 CURSOR FOR
             SELECT
             ARTICLERESERVATION_LISTE
             FROM ARTICLERESERVATION;
          EXEC SQL OPEN C0;
          break;

       case cCRSARTICLERESERVATION_AllReservations :
          EXEC SQL DECLARE C1 CURSOR FOR
              SELECT
              ARTICLERESERVATION_LISTE
              FROM ARTICLERESERVATION
              WHERE BRANCHNO      = :recordp->BRANCHNO
              AND ARTICLENO       = :recordp->ARTICLENO;
          EXEC SQL OPEN C1;
          break;

	   case cCRSARTICLERESERVATION_Default :
	   default:
          EXEC SQL DECLARE C2 CURSOR FOR
              SELECT
              ARTICLERESERVATION_LISTE
              FROM ARTICLERESERVATION
              WHERE BRANCHNO      = :recordp->BRANCHNO
              AND PHARMACYGROUPID = :recordp->PHARMACYGROUPID
              AND ARTICLENO       = :recordp->ARTICLENO;
          EXEC SQL OPEN C2;
          break;
    }
    if (SQLCODE == 0)        return 0;
    if (SQLCODE == 100)      return cDBXR_NOTFOUND;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxArtReservationGetNext                                       */
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
int pxArtReservationGetNext
(
    struct tARTICLERESERVATION* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTICLERESERVATION * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_ARTICLERESERVATION*10+F_GetNext;
    recordp = (struct C_ARTICLERESERVATION *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0 INTO ARTICLERESERVATION_ZEIGER(recordp);
          break;
       case cCRSARTICLERESERVATION_AllReservations:
          EXEC SQL FETCH C1 INTO ARTICLERESERVATION_ZEIGER(recordp);
          break;
	   case cCRSARTICLERESERVATION_Default:
	   default:
          EXEC SQL FETCH C2 INTO ARTICLERESERVATION_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxArtReservationEndBrowse                                     */
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
int pxArtReservationEndBrowse
(
    int browseid
)
{
    functionnr = F_ARTICLERESERVATION*10+F_EndBrowse;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL CLOSE C0;
          break;
       case cCRSARTICLERESERVATION_AllReservations:
          EXEC SQL CLOSE C1;
          break;
       case cCRSARTICLERESERVATION_Default:
	   default:
          EXEC SQL CLOSE C2;
          break;
    }
    return 0;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxArtReservationRead                                          */
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

int pxArtReservationRead
(
    struct tARTICLERESERVATION* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTICLERESERVATION * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTICLERESERVATION*10+F_Read;
    recordp = (struct C_ARTICLERESERVATION *) record;

    EXEC SQL SELECT ARTICLERESERVATION_LISTE
        INTO ARTICLERESERVATION_ZEIGER(recordp)
        FROM ARTICLERESERVATION
        WHERE PKtartreservation;

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
/*  FUNCTION: pxArtReservationReadLock                               */
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
int pxArtReservationReadLock
(
    struct tARTICLERESERVATION* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTICLERESERVATION * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTICLERESERVATION*10+F_ReadLock;
    recordp = (struct C_ARTICLERESERVATION *) record;

    EXEC SQL DECLARE tartreservation_U1 CURSOR WITH HOLD FOR
        SELECT ARTICLERESERVATION_LISTE
        FROM ARTICLERESERVATION
        WHERE PKtartreservation
        FOR UPDATE;
    if (SQLCODE != 0)
    {
		return cDBXR_IOERROR;
    }
    EXEC SQL OPEN tartreservation_U1;
    if (SQLCODE != 0)
    {
		return cDBXR_IOERROR;
    }

    EXEC SQL FETCH tartreservation_U1 INTO ARTICLERESERVATION_ZEIGER(recordp);
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
/*  FUNCTION: pxArtReservationUpdate                                        */
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

int pxArtReservationUpdate
(
    struct tARTICLERESERVATION * record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTICLERESERVATION * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTICLERESERVATION*10+F_Update;
    recordp = (struct C_ARTICLERESERVATION *) record;

    EXEC SQL UPDATE
    ARTICLERESERVATION
    SET
    ARTICLERESERVATION_UPDATE(recordp)
    WHERE CURRENT OF tartreservation_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE tartreservation_U1;
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
/*  FUNCTION: pxArtReservationInsert                                       */
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
int pxArtReservationInsert
(
    struct tARTICLERESERVATION* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTICLERESERVATION * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTICLERESERVATION*10+F_Insert;
    recordp = (struct C_ARTICLERESERVATION *) record;

    EXEC SQL INSERT INTO
    ARTICLERESERVATION
    (ARTICLERESERVATION_LISTE)
    VALUES ( ARTICLERESERVATION_ZEIGER(recordp) );

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
/*  FUNCTION: pxArtReservationDelete                                        */
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

int pxArtReservationDelete
(
    struct tARTICLERESERVATION * record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTICLERESERVATION * recordp;
    EXEC SQL END DECLARE SECTION;

	functionnr = F_ARTICLERESERVATION*10+F_Delete;
    recordp = (struct C_ARTICLERESERVATION *) record;

    EXEC SQL DELETE FROM ARTICLERESERVATION	WHERE
		BRANCHNO = :recordp->BRANCHNO AND
		ARTICLENO = :recordp->ARTICLENO	AND
		RESERVTYPE = :recordp->RESERVTYPE;

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
