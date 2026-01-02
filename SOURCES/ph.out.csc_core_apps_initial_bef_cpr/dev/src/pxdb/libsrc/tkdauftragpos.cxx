/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

                 (c) Copyright 1994-1995 by NORDAT Network GmbH
                              All rights reserved

    Embedded SQL for C application


    FILE: tposit.c (.sqc)

    Database functions




    FUNCTIONS:

        pxPositionStartBrowse  declare and open Cursor
        pxPositionGetNext      get next record
        pxPositionEndBrowse    close cursor
        pxPositionRead         get one record
        pxPositionReadLock     get one record with lock
        pxPositionInsert       Insert record
        pxPositionUpdate       Update record
        pxPositionDelete       Delete record


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
#include "tkdauftragpos.h"
#include "keys.h"

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxPositionStartBrowse                                   */
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
int pxPositionStartBrowse
(
     struct tKDAUFTRAGPOS* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGPOS * rp;
#ifdef MCtposit
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_KDAUFTRAGPOS*10+F_StartBrowse;
    rp = (struct C_KDAUFTRAGPOS *) record;

    if (!(sizeof(struct C_KDAUFTRAGPOS) == sizeof(struct tKDAUFTRAGPOS)))
       return cDBXR_DEFINITION;


#ifdef MCtposit
    strcpy(matchcode,rp->MCtposit);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        KDAUFTRAGPOS_LISTE
    from KDAUFTRAGPOS
    DWtposit
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        KDAUFTRAGPOS_LISTE
    from KDAUFTRAGPOS
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
/*  FUNCTION: pxPositionGetNext                                       */
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
int pxPositionGetNext
(
    struct tKDAUFTRAGPOS* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGPOS * rp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_KDAUFTRAGPOS*10+F_GetNext;
    rp = (struct C_KDAUFTRAGPOS *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into KDAUFTRAGPOS_ZEIGER(rp);
          break;
       default:
          EXEC SQL FETCH C1
          into KDAUFTRAGPOS_ZEIGER(rp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxPositionEndBrowse                                     */
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
int pxPositionEndBrowse
(
    int browseid
)
{
    functionnr = F_KDAUFTRAGPOS*10+F_EndBrowse;

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
/*  FUNCTION: pxPositionRead                                          */
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

int pxPositionRead
(
    struct tKDAUFTRAGPOS* record
#ifdef SKtposit
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGPOS * rp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRAGPOS*10+F_Read;
    rp = (struct C_KDAUFTRAGPOS *) record;

#ifdef SKtposit
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        KDAUFTRAGPOS_LISTE
     into KDAUFTRAGPOS_ZEIGER(rp)
     from KDAUFTRAGPOS
     where SKtposit;
     break;
    default:
#endif

    EXEC SQL SELECT
        KDAUFTRAGPOS_LISTE
     into KDAUFTRAGPOS_ZEIGER(rp)
     from KDAUFTRAGPOS
     where PKtposit;

#ifdef SKtposit
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
/*  FUNCTION: pxPositionReadLock                                      */
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
int pxPositionReadLock
(
    struct tKDAUFTRAGPOS* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGPOS * rp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRAGPOS*10+F_ReadLock;
    rp = (struct C_KDAUFTRAGPOS *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE TPOSIT_U1 CURSOR WITH HOLD FOR
        SELECT
        KDAUFTRAGPOS_LISTE
    from KDAUFTRAGPOS
    where PKtposit
    FOR UPDATE;
    EXEC SQL OPEN TPOSIT_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH TPOSIT_U1
      into KDAUFTRAGPOS_ZEIGER(rp)
      ;
    }
#else
    EXEC SQL SELECT
         KDAUFTRAGPOS_LISTE
    into KDAUFTRAGPOS_ZEIGER(rp)
    from KDAUFTRAGPOS    HOLDLOCK
    where PKtposit;
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
/*  FUNCTION: pxPositionUpdate                                        */
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

int pxPositionUpdate
(
    struct tKDAUFTRAGPOS* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGPOS * rp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRAGPOS*10+F_Update;
    rp = (struct C_KDAUFTRAGPOS *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    KDAUFTRAGPOS
    SET
    KDAUFTRAGPOS_UPDATE(rp)
    where current of TPOSIT_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE TPOSIT_U1;
    }
#else

    EXEC SQL UPDATE
    KDAUFTRAGPOS
    SET
    KDAUFTRAGPOS_UPDATE(rp)
    where PKtposit;
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
/*  FUNCTION: pxPositionInsert                                       */
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
int pxPositionInsert
(
    struct tKDAUFTRAGPOS* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGPOS * rp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRAGPOS*10+F_Insert;
    rp = (struct C_KDAUFTRAGPOS *) record;

#ifdef pxDATABASE_INFORMIX
    EXEC SQL INSERT INTO
    KDAUFTRAGPOS
    (KDAUFTRAGPOS_LISTE)
    VALUES ( KDAUFTRAGPOS_ZEIGER(rp) );
#else
    EXEC SQL INSERT INTO
    KDAUFTRAGPOS
    VALUES ( KDAUFTRAGPOS_ZEIGER(rp) );
#endif

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
/*  FUNCTION: pxPositionDelete                                        */
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

int pxPositionDelete
(
    struct tKDAUFTRAGPOS* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGPOS * rp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRAGPOS*10+F_Delete;
    rp = (struct C_KDAUFTRAGPOS *) record;

    EXEC SQL DELETE FROM
    KDAUFTRAGPOS
    where PKtposit;

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
