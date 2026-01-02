/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

                 (c) Copyright 1994-1995 by NORDAT Network GmbH
                              All rights reserved

    Embedded SQL for C application


    FILE: tzeitart.c (.sqc)

    Database functions




    FUNCTIONS:

        pxZeitArtenStartBrowse  declare and open Cursor
        pxZeitArtenGetNext      get next record
        pxZeitArtenEndBrowse    close cursor
        pxZeitArtenRead         get one record
        pxZeitArtenReadLock     get one record with lock
        pxZeitArtenInsert       Insert record
        pxZeitArtenUpdate       Update record
        pxZeitArtenDelete       Delete record


REVISION HISTORY

06 Oct 1995 V1.00 REV 00 written by Dietmar Schloetel

*/


#include <stddef.h>         /* standard C run-time header */
#include <stdio.h>          /* standard C run-time header */
#include <string.h>
#include <pxrecord.h>       /* all record structures */
#include "pxdbxx.h"
#include "pxdbfunc.h"
#include <ndefs.h>
#include <pxenv.h>
#include "tzeitart.h"
#include "keys.h"

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxZeitArtenStartBrowse                                   */
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
int pxZeitArtenStartBrowse
(
     struct tZEITARTEN* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ZEITARTEN * recordp;
#ifdef MCtzeitart
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_ZEITARTEN*10+F_StartBrowse;
    recordp = (struct C_ZEITARTEN *) record;

    if (!(sizeof(struct C_ZEITARTEN) == sizeof(struct tZEITARTEN)))
       return cDBXR_DEFINITION;


#ifdef MCtzeitart
    strcpy(matchcode,recordp->MCtzeitart);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        ZEITARTEN_LISTE
    from ZEITARTEN
    DWtzeitart
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        ZEITARTEN_LISTE
    from ZEITARTEN
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
/*  FUNCTION: pxZeitArtenGetNext                                       */
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
int pxZeitArtenGetNext
(
    struct tZEITARTEN* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ZEITARTEN * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_ZEITARTEN*10+F_GetNext;
    recordp = (struct C_ZEITARTEN *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into ZEITARTEN_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into ZEITARTEN_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxZeitArtenEndBrowse                                     */
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
int pxZeitArtenEndBrowse
(
    int browseid
)
{
    functionnr = F_ZEITARTEN*10+F_EndBrowse;

    /* close the cursor */
    switch (browseid)
    {
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
/*  FUNCTION: pxZeitArtenRead                                          */
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

int pxZeitArtenRead
(
    struct tZEITARTEN* record
#ifdef SKtzeitart
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ZEITARTEN * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ZEITARTEN*10+F_Read;
    recordp = (struct C_ZEITARTEN *) record;

#ifdef SKtzeitart
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        ZEITARTEN_LISTE
     into ZEITARTEN_ZEIGER(recordp)
     from ZEITARTEN
     where SKtzeitart;
     break;
    default:
#endif

    EXEC SQL SELECT
        ZEITARTEN_LISTE
     into ZEITARTEN_ZEIGER(recordp)
     from ZEITARTEN
     where PKtzeitart;

#ifdef SKtzeitart
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
/*  FUNCTION: pxZeitArtenReadLock                                      */
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
int pxZeitArtenReadLock
(
    struct tZEITARTEN* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ZEITARTEN * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ZEITARTEN*10+F_ReadLock;
    recordp = (struct C_ZEITARTEN *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE TZEITART_U1 CURSOR WITH HOLD FOR
        SELECT
        ZEITARTEN_LISTE
    from ZEITARTEN
    where PKtzeitart
    FOR UPDATE;
    EXEC SQL OPEN TZEITART_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH TZEITART_U1
      into ZEITARTEN_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         ZEITARTEN_LISTE
    into ZEITARTEN_ZEIGER(recordp)
    from ZEITARTEN    HOLDLOCK
    where PKtzeitart;
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
/*  FUNCTION: pxZeitArtenUpdate                                        */
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

int pxZeitArtenUpdate
(
    struct tZEITARTEN* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ZEITARTEN * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ZEITARTEN*10+F_Update;
    recordp = (struct C_ZEITARTEN *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    ZEITARTEN
    SET
    ZEITARTEN_UPDATE(recordp)
    where current of TZEITART_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE TZEITART_U1;
    }
#else

    EXEC SQL UPDATE
    ZEITARTEN
    SET
    ZEITARTEN_UPDATE(recordp)
    where PKtzeitart;
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
/*  FUNCTION: pxZeitArtenInsert                                       */
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
int pxZeitArtenInsert
(
    struct tZEITARTEN* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ZEITARTEN * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ZEITARTEN*10+F_Insert;
    recordp = (struct C_ZEITARTEN *) record;

    EXEC SQL INSERT INTO
    ZEITARTEN
    (ZEITARTEN_LISTE)
    VALUES ( ZEITARTEN_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    ZEITARTEN
    VALUES ( ZEITARTEN_ZEIGER(recordp) );   */


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
/*  FUNCTION: pxZeitArtenDelete                                        */
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

int pxZeitArtenDelete
(
    struct tZEITARTEN* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ZEITARTEN * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ZEITARTEN*10+F_Delete;
    recordp = (struct C_ZEITARTEN *) record;

    EXEC SQL DELETE FROM
    ZEITARTEN
    where PKtzeitart;

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
