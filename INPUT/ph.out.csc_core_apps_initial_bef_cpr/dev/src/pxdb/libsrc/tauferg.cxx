/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

                 (c) Copyright 1994-1995 by NORDAT Network GmbH
                              All rights reserved

    Embedded SQL for C application


    FILE: tauferg.c (.sqc)

    Database functions




    FUNCTIONS:

        pxAuftragEreignisStartBrowse  declare and open Cursor
        pxAuftragEreignisGetNext      get next record
        pxAuftragEreignisEndBrowse    close cursor
        pxAuftragEreignisRead         get one record
        pxAuftragEreignisReadLock     get one record with lock
        pxAuftragEreignisInsert       Insert record
        pxAuftragEreignisUpdate       Update record
        pxAuftragEreignisDelete       Delete record


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
#include "tauferg.h"
#include "keys.h"

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxAuftragEreignisStartBrowse                                   */
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
int pxAuftragEreignisStartBrowse
(
     struct tKDAUFTRAGEREIGNIS* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGEREIGNIS * recordp;
#ifdef MCtauferg
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_KDAUFTRAGEREIGNIS*10+F_StartBrowse;
    recordp = (struct C_KDAUFTRAGEREIGNIS *) record;

    if (!(sizeof(struct C_KDAUFTRAGEREIGNIS) == sizeof(struct tKDAUFTRAGEREIGNIS)))
       return cDBXR_DEFINITION;


#ifdef MCtauferg
    strcpy(matchcode,recordp->MCtauferg);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        KDAUFTRAGEREIGNIS_LISTE
    from KDAUFTRAGEREIGNIS
    DWtauferg
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        KDAUFTRAGEREIGNIS_LISTE
    from KDAUFTRAGEREIGNIS
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
/*  FUNCTION: pxAuftragEreignisGetNext                                       */
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
int pxAuftragEreignisGetNext
(
    struct tKDAUFTRAGEREIGNIS* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGEREIGNIS * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_KDAUFTRAGEREIGNIS*10+F_GetNext;
    recordp = (struct C_KDAUFTRAGEREIGNIS *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into KDAUFTRAGEREIGNIS_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into KDAUFTRAGEREIGNIS_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxAuftragEreignisEndBrowse                                     */
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
int pxAuftragEreignisEndBrowse
(
    int browseid
)
{
    functionnr = F_KDAUFTRAGEREIGNIS*10+F_EndBrowse;

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
/*  FUNCTION: pxAuftragEreignisRead                                          */
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

int pxAuftragEreignisRead
(
    struct tKDAUFTRAGEREIGNIS* record
#ifdef SKtauferg
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGEREIGNIS * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRAGEREIGNIS*10+F_Read;
    recordp = (struct C_KDAUFTRAGEREIGNIS *) record;

#ifdef SKtauferg
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        KDAUFTRAGEREIGNIS_LISTE
     into KDAUFTRAGEREIGNIS_ZEIGER(recordp)
     from KDAUFTRAGEREIGNIS
     where SKtauferg;
     break;
    default:
#endif

    EXEC SQL SELECT
        KDAUFTRAGEREIGNIS_LISTE
     into KDAUFTRAGEREIGNIS_ZEIGER(recordp)
     from KDAUFTRAGEREIGNIS
     where PKtauferg;

#ifdef SKtauferg
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
/*  FUNCTION: pxAuftragEreignisReadLock                                      */
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
int pxAuftragEreignisReadLock
(
    struct tKDAUFTRAGEREIGNIS* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGEREIGNIS * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRAGEREIGNIS*10+F_ReadLock;
    recordp = (struct C_KDAUFTRAGEREIGNIS *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE TAUFERG_U1 CURSOR WITH HOLD FOR
        SELECT
        KDAUFTRAGEREIGNIS_LISTE
    from KDAUFTRAGEREIGNIS
    where PKtauferg
    FOR UPDATE;
    EXEC SQL OPEN TAUFERG_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH TAUFERG_U1
      into KDAUFTRAGEREIGNIS_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         KDAUFTRAGEREIGNIS_LISTE
    into KDAUFTRAGEREIGNIS_ZEIGER(recordp)
    from KDAUFTRAGEREIGNIS    HOLDLOCK
    where PKtauferg;
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
/*  FUNCTION: pxAuftragEreignisUpdate                                        */
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

int pxAuftragEreignisUpdate
(
    struct tKDAUFTRAGEREIGNIS* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGEREIGNIS * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRAGEREIGNIS*10+F_Update;
    recordp = (struct C_KDAUFTRAGEREIGNIS *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    KDAUFTRAGEREIGNIS
    SET
    KDAUFTRAGEREIGNIS_UPDATE(recordp)
    where current of TAUFERG_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE TAUFERG_U1;
    }
#else

    EXEC SQL UPDATE
    KDAUFTRAGEREIGNIS
    SET
    KDAUFTRAGEREIGNIS_UPDATE(recordp)
    where PKtauferg;
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
/*  FUNCTION: pxAuftragEreignisInsert                                       */
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
int pxAuftragEreignisInsert
(
    struct tKDAUFTRAGEREIGNIS* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGEREIGNIS * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRAGEREIGNIS*10+F_Insert;
    recordp = (struct C_KDAUFTRAGEREIGNIS *) record;

    EXEC SQL INSERT INTO
    KDAUFTRAGEREIGNIS
    (KDAUFTRAGEREIGNIS_LISTE)
    VALUES ( KDAUFTRAGEREIGNIS_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    KDAUFTRAGEREIGNIS
    VALUES ( KDAUFTRAGEREIGNIS_ZEIGER(recordp) );   */


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
/*  FUNCTION: pxAuftragEreignisDelete                                        */
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

int pxAuftragEreignisDelete
(
    struct tKDAUFTRAGEREIGNIS* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGEREIGNIS * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRAGEREIGNIS*10+F_Delete;
    recordp = (struct C_KDAUFTRAGEREIGNIS *) record;

    EXEC SQL DELETE FROM
    KDAUFTRAGEREIGNIS
    where PKtauferg;

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
