/*(c)
 ********************* PHARMX Customer Order Entry Server *********************


    Embedded SQL for C application


    FILE: tpositionparking.c (.sqc)

    Database functions




    FUNCTIONS:

        pxPosParkingStartBrowse  declare and open Cursor
        pxPosParkingGetNext      get next record
        pxPosParkingEndBrowse    close cursor
        pxPosParkingRead         get one record
        pxPosParkingReadLock     get one record with lock
        pxPosParkingInsert       Insert record
        pxPosParkingUpdate       Update record
        pxPosParkingDelete       Delete record


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
#include <tpositionparking.h>
#include <keys.h>

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxPosParkingStartBrowse                                   */
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
int pxPosParkingStartBrowse
(
     struct tPOSITIONPARKING* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_POSITIONPARKING * recordp;
#ifdef MCtpositionparking
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_POSITIONPARKING*10+F_StartBrowse;
    recordp = (struct C_POSITIONPARKING *) record;

    if (!(sizeof(struct C_POSITIONPARKING) == sizeof(struct tPOSITIONPARKING)))
       return cDBXR_DEFINITION;


#ifdef MCtpositionparking
    strcpy(matchcode,recordp->MCtpositionparking);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        POSITIONPARKING_LISTE
    from POSITIONPARKING
    DWtpositionparking
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        POSITIONPARKING_LISTE
    from POSITIONPARKING
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C2 CURSOR FOR
        SELECT
        POSITIONPARKING_LISTE
    from POSITIONPARKING
    where BRANCHNO     = :recordp->BRANCHNO
    and   CUSTOMERNO   = :recordp->CUSTOMERNO
    and   ARTICLENO    = :recordp->ARTICLENO
    and   DATE         = :recordp->DATE
    and   ORDERNOORG   = :recordp->ORDERNOORG
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL OPEN C0;
          break;
       case cCRSPOSPARKING_ORDERTODAY:
          EXEC SQL OPEN C2;
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
/*  FUNCTION: pxPosParkingGetNext                                       */
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
int pxPosParkingGetNext
(
    struct tPOSITIONPARKING* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_POSITIONPARKING * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_POSITIONPARKING*10+F_GetNext;
    recordp = (struct C_POSITIONPARKING *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into POSITIONPARKING_ZEIGER(recordp);
          break;
       case cCRSPOSPARKING_ORDERTODAY:
          EXEC SQL FETCH C2
          into POSITIONPARKING_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into POSITIONPARKING_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxPosParkingEndBrowse                                     */
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
int pxPosParkingEndBrowse
(
    int browseid
)
{
    functionnr = F_POSITIONPARKING*10+F_EndBrowse;

    /* close the cursor */
    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL CLOSE C0;
          break;
       case cCRSPOSPARKING_ORDERTODAY:
          EXEC SQL CLOSE C2;
          break;
       default:
          EXEC SQL CLOSE C1;
          break;
    }
    return 0;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxPosParkingRead                                          */
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

int pxPosParkingRead
(
    struct tPOSITIONPARKING* record
#ifdef SKtpositionparking
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_POSITIONPARKING * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_POSITIONPARKING*10+F_Read;
    recordp = (struct C_POSITIONPARKING *) record;

#ifdef SKtpositionparking
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        POSITIONPARKING_LISTE
     into POSITIONPARKING_ZEIGER(recordp)
     from POSITIONPARKING
     where SKtpositionparking;
     break;
    default:
#endif

    EXEC SQL SELECT
        POSITIONPARKING_LISTE
     into POSITIONPARKING_ZEIGER(recordp)
     from POSITIONPARKING
     where PKtpositionparking;

#ifdef SKtpositionparking
    }
#endif
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
/*  FUNCTION: pxPosParkingReadLock                                      */
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
int pxPosParkingReadLock
(
    struct tPOSITIONPARKING* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_POSITIONPARKING * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_POSITIONPARKING*10+F_ReadLock;
    recordp = (struct C_POSITIONPARKING *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE tpositionparking_U1 CURSOR WITH HOLD FOR
        SELECT
        POSITIONPARKING_LISTE
    from POSITIONPARKING
    where PKtpositionparking
    FOR UPDATE;
    EXEC SQL OPEN tpositionparking_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH tpositionparking_U1
      into POSITIONPARKING_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         POSITIONPARKING_LISTE
    into POSITIONPARKING_ZEIGER(recordp)
    from POSITIONPARKING    HOLDLOCK
    where PKtpositionparking;
#endif


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
/*  FUNCTION: pxPosParkingUpdate                                        */
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

int pxPosParkingUpdate
(
    struct tPOSITIONPARKING* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_POSITIONPARKING * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_POSITIONPARKING*10+F_Update;
    recordp = (struct C_POSITIONPARKING *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    POSITIONPARKING
    SET
    POSITIONPARKING_UPDATE(recordp)
    where current of tpositionparking_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE tpositionparking_U1;
    }
#else

    EXEC SQL UPDATE
    POSITIONPARKING
    SET
    POSITIONPARKING_UPDATE(recordp)
    where PKtpositionparking;
#endif

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
/*  FUNCTION: pxPosParkingInsert                                       */
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
int pxPosParkingInsert
(
    struct tPOSITIONPARKING* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_POSITIONPARKING * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_POSITIONPARKING*10+F_Insert;
    recordp = (struct C_POSITIONPARKING *) record;

    EXEC SQL INSERT INTO
    POSITIONPARKING
    (POSITIONPARKING_LISTE)
    VALUES ( POSITIONPARKING_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    POSITIONPARKING
    VALUES ( POSITIONPARKING_ZEIGER(recordp) );   */


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
/*  FUNCTION: pxPosParkingDelete                                        */
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

int pxPosParkingDelete
(
    struct tPOSITIONPARKING* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_POSITIONPARKING * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_POSITIONPARKING*10+F_Delete;
    recordp = (struct C_POSITIONPARKING *) record;

    EXEC SQL DELETE FROM
    POSITIONPARKING
    where PKtpositionparking;

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
