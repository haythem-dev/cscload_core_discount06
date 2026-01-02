/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

                 (c) Copyright 1994-1995 by NORDAT Network GmbH
                              All rights reserved

    Embedded SQL for C application


    FILE: ttaskctl.c (.sqc)

    Database functions




    FUNCTIONS:

        pxTaskControlStartBrowse  declare and open Cursor
        pxTaskControlGetNext      get next record
        pxTaskControlEndBrowse    close cursor
        pxTaskControlRead         get one record
        pxTaskControlReadLock     get one record with lock
        pxTaskControlInsert       Insert record
        pxTaskControlUpdate       Update record
        pxTaskControlDelete       Delete record


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
#include <ttaskctl.h>
#include <keys.h>

/* Global variables */
extern int  functionnr;

#define UNUSED(x) (void)(x)

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxTaskControlStartBrowse                                   */
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
int pxTaskControlStartBrowse
(
     struct tTASKCONTROL* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
#ifdef MCttaskctl
    struct C_TASKCONTROL * recordp;
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_TASKCONTROL*10+F_StartBrowse;
#ifdef MCttaskctl
    recordp = (struct C_TASKCONTROL *) record;
#else
    UNUSED(record);
#endif

    if (!(sizeof(struct C_TASKCONTROL) == sizeof(struct tTASKCONTROL)))
       return cDBXR_DEFINITION;


#ifdef MCttaskctl
    strcpy(matchcode,recordp->MCttaskctl);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        TASKCONTROL_LISTE
    from TASKCONTROL
    DWttaskctl
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        TASKCONTROL_LISTE
    from TASKCONTROL
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
/*  FUNCTION: pxTaskControlGetNext                                       */
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
int pxTaskControlGetNext
(
    struct tTASKCONTROL* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_TASKCONTROL * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_TASKCONTROL*10+F_GetNext;
    recordp = (struct C_TASKCONTROL *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into TASKCONTROL_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into TASKCONTROL_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxTaskControlEndBrowse                                     */
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
int pxTaskControlEndBrowse
(
    int browseid
)
{
    functionnr = F_TASKCONTROL*10+F_EndBrowse;

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
/*  FUNCTION: pxTaskControlRead                                          */
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

int pxTaskControlRead
(
    struct tTASKCONTROL* record
#ifdef SKttaskctl
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_TASKCONTROL * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_TASKCONTROL*10+F_Read;
    recordp = (struct C_TASKCONTROL *) record;

#ifdef SKttaskctl
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        TASKCONTROL_LISTE
     into TASKCONTROL_ZEIGER(recordp)
     from TASKCONTROL
     where SKttaskctl;
     break;
    default:
#endif

    EXEC SQL SELECT
        TASKCONTROL_LISTE
     into TASKCONTROL_ZEIGER(recordp)
     from TASKCONTROL
     where PKttaskctl;

#ifdef SKttaskctl
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
/*  FUNCTION: pxTaskControlReadLock                                      */
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
int pxTaskControlReadLock
(
    struct tTASKCONTROL* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_TASKCONTROL * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_TASKCONTROL*10+F_ReadLock;
    recordp = (struct C_TASKCONTROL *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE TTASKCTL_U1 CURSOR WITH HOLD FOR
        SELECT
        TASKCONTROL_LISTE
    from TASKCONTROL
    where PKttaskctl
    FOR UPDATE;
    EXEC SQL OPEN TTASKCTL_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH TTASKCTL_U1
      into TASKCONTROL_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         TASKCONTROL_LISTE
    into TASKCONTROL_ZEIGER(recordp)
    from TASKCONTROL    HOLDLOCK
    where PKttaskctl;
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
/*  FUNCTION: pxTaskControlUpdate                                        */
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

int pxTaskControlUpdate
(
    struct tTASKCONTROL* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_TASKCONTROL * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_TASKCONTROL*10+F_Update;
    recordp = (struct C_TASKCONTROL *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    TASKCONTROL
    SET
    TASKCONTROL_UPDATE(recordp)
    where current of TTASKCTL_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE TTASKCTL_U1;
    }
#else

    EXEC SQL UPDATE
    TASKCONTROL
    SET
    TASKCONTROL_UPDATE(recordp)
    where PKttaskctl;
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
/*  FUNCTION: pxTaskControlInsert                                       */
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
int pxTaskControlInsert
(
    struct tTASKCONTROL* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_TASKCONTROL * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_TASKCONTROL*10+F_Insert;
    recordp = (struct C_TASKCONTROL *) record;

    EXEC SQL INSERT INTO
    TASKCONTROL
    (TASKCONTROL_LISTE)
    VALUES ( TASKCONTROL_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    TASKCONTROL
    VALUES ( TASKCONTROL_ZEIGER(recordp) );   */


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
/*  FUNCTION: pxTaskControlDelete                                        */
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

int pxTaskControlDelete
(
    struct tTASKCONTROL* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_TASKCONTROL * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_TASKCONTROL*10+F_Delete;
    recordp = (struct C_TASKCONTROL *) record;

    EXEC SQL DELETE FROM
    TASKCONTROL
    where PKttaskctl;

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
