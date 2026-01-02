/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

                 (c) Copyright 1994-1995 by NORDAT Network GmbH
                              All rights reserved

    Embedded SQL for C application


    FILE: tlagrev.c (.sqc)

    Database functions




    FUNCTIONS:

        pxLagerRevisionStartBrowse  declare and open Cursor
        pxLagerRevisionGetNext      get next record
        pxLagerRevisionEndBrowse    close cursor
        pxLagerRevisionRead         get one record
        pxLagerRevisionReadLock     get one record with lock
        pxLagerRevisionInsert       Insert record
        pxLagerRevisionUpdate       Update record
        pxLagerRevisionDelete       Delete record


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
#include <tlagrev.h>
#include <keys.h>

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxLagerRevisionStartBrowse                                   */
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
int pxLagerRevisionStartBrowse
(
     struct tLAGERREVISION* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_LAGERREVISION * recordp;
#ifdef MCtlagrev
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_LAGERREVISION*10+F_StartBrowse;
    recordp = (struct C_LAGERREVISION *) record;

    if (!(sizeof(struct C_LAGERREVISION) == sizeof(struct tLAGERREVISION)))
       return cDBXR_DEFINITION;


#ifdef MCtlagrev
    strcpy(matchcode,recordp->MCtlagrev);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        LAGERREVISION_LISTE
    from LAGERREVISION
    DWtlagrev
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        LAGERREVISION_LISTE
    from LAGERREVISION
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
/*  FUNCTION: pxLagerRevisionGetNext                                       */
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
int pxLagerRevisionGetNext
(
    struct tLAGERREVISION* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_LAGERREVISION * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_LAGERREVISION*10+F_GetNext;
    recordp = (struct C_LAGERREVISION *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into LAGERREVISION_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into LAGERREVISION_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxLagerRevisionEndBrowse                                     */
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
int pxLagerRevisionEndBrowse
(
    int browseid
)
{
    functionnr = F_LAGERREVISION*10+F_EndBrowse;

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
/*  FUNCTION: pxLagerRevisionRead                                          */
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

int pxLagerRevisionRead
(
    struct tLAGERREVISION* record
#ifdef SKtlagrev
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_LAGERREVISION * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_LAGERREVISION*10+F_Read;
    recordp = (struct C_LAGERREVISION *) record;

#ifdef SKtlagrev
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        LAGERREVISION_LISTE
     into LAGERREVISION_ZEIGER(recordp)
     from LAGERREVISION
     where SKtlagrev;
     break;
    default:
#endif

    EXEC SQL SELECT
        LAGERREVISION_LISTE
     into LAGERREVISION_ZEIGER(recordp)
     from LAGERREVISION
     where PKtlagrev;

#ifdef SKtlagrev
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
/*  FUNCTION: pxLagerRevisionReadLock                                      */
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
int pxLagerRevisionReadLock
(
    struct tLAGERREVISION* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_LAGERREVISION * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_LAGERREVISION*10+F_ReadLock;
    recordp = (struct C_LAGERREVISION *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE TLAGREV_U1 CURSOR WITH HOLD FOR
        SELECT
        LAGERREVISION_LISTE
    from LAGERREVISION
    where PKtlagrev
    FOR UPDATE;
    EXEC SQL OPEN TLAGREV_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH TLAGREV_U1
      into LAGERREVISION_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         LAGERREVISION_LISTE
    into LAGERREVISION_ZEIGER(recordp)
    from LAGERREVISION    HOLDLOCK
    where PKtlagrev;
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
/*  FUNCTION: pxLagerRevisionUpdate                                        */
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

int pxLagerRevisionUpdate
(
    struct tLAGERREVISION* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_LAGERREVISION * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_LAGERREVISION*10+F_Update;
    recordp = (struct C_LAGERREVISION *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    LAGERREVISION
    SET
    LAGERREVISION_UPDATE(recordp)
    where current of TLAGREV_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE TLAGREV_U1;
    }
#else

    EXEC SQL UPDATE
    LAGERREVISION
    SET
    LAGERREVISION_UPDATE(recordp)
    where PKtlagrev;
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
/*  FUNCTION: pxLagerRevisionInsert                                       */
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
int pxLagerRevisionInsert
(
    struct tLAGERREVISION* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_LAGERREVISION * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_LAGERREVISION*10+F_Insert;
    recordp = (struct C_LAGERREVISION *) record;

    EXEC SQL INSERT INTO
    LAGERREVISION
    (LAGERREVISION_LISTE)
    VALUES ( LAGERREVISION_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    LAGERREVISION
    VALUES ( LAGERREVISION_ZEIGER(recordp) );   */


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
/*  FUNCTION: pxLagerRevisionDelete                                        */
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

int pxLagerRevisionDelete
(
    struct tLAGERREVISION* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_LAGERREVISION * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_LAGERREVISION*10+F_Delete;
    recordp = (struct C_LAGERREVISION *) record;

    EXEC SQL DELETE FROM
    LAGERREVISION
    where PKtlagrev;

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
