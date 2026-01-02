/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

                 (c) Copyright 1994-1995 by NORDAT Network GmbH
                              All rights reserved

    Embedded SQL for C application


    FILE: taufartk.c (.sqc)

    Database functions




    FUNCTIONS:

        pxAuftragArtKdStartBrowse  declare and open Cursor
        pxAuftragArtKdGetNext      get next record
        pxAuftragArtKdEndBrowse    close cursor
        pxAuftragArtKdRead         get one record
        pxAuftragArtKdReadLock     get one record with lock
        pxAuftragArtKdInsert       Insert record
        pxAuftragArtKdUpdate       Update record
        pxAuftragArtKdDelete       Delete record


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
#include "taufartk.h"
#include "keys.h"

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxAuftragArtKdStartBrowse                                   */
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
int pxAuftragArtKdStartBrowse
(
     struct tAUFTRAGARTKD * record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_AUFTRAGARTKD * recordp;
#ifdef MCtaufartk
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_AUFTRAGARTKD*10+F_StartBrowse;
    recordp = (struct C_AUFTRAGARTKD *) record;

    if (!(sizeof(struct C_AUFTRAGARTKD) == sizeof(struct tAUFTRAGARTKD)))
       return cDBXR_DEFINITION;


#ifdef MCtaufartk
    strcpy(matchcode,recordp->MCtaufartk);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        AUFTRAGARTKD_LISTE
    from AUFTRAGARTKD
    DWtaufartk
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        AUFTRAGARTKD_LISTE
    from AUFTRAGARTKD
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
/*  FUNCTION: pxAuftragArtKdGetNext                                       */
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
int pxAuftragArtKdGetNext
(
    struct tAUFTRAGARTKD * record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_AUFTRAGARTKD * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_AUFTRAGARTKD*10+F_GetNext;
    recordp = (struct C_AUFTRAGARTKD *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into AUFTRAGARTKD_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into AUFTRAGARTKD_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxAuftragArtKdEndBrowse                                     */
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
int pxAuftragArtKdEndBrowse
(
    int browseid
)
{
    functionnr = F_AUFTRAGARTKD*10+F_EndBrowse;

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
/*  FUNCTION: pxAuftragArtKdRead                                          */
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

int pxAuftragArtKdRead
(
    struct tAUFTRAGARTKD * record
#ifdef SKtaufartk
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_AUFTRAGARTKD * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_AUFTRAGARTKD*10+F_Read;
    recordp = (struct C_AUFTRAGARTKD *) record;

#ifdef SKtaufartk
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        AUFTRAGARTKD_LISTE
     into AUFTRAGARTKD_ZEIGER(recordp)
     from AUFTRAGARTKD
     where SKtaufartk;
     break;
    default:
#endif

    EXEC SQL SELECT
        AUFTRAGARTKD_LISTE
     into AUFTRAGARTKD_ZEIGER(recordp)
     from AUFTRAGARTKD
     where PKtaufartk;

#ifdef SKtaufartk
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
/*  FUNCTION: pxAuftragArtKdReadLock                                      */
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
int pxAuftragArtKdReadLock
(
    struct tAUFTRAGARTKD * record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_AUFTRAGARTKD * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_AUFTRAGARTKD*10+F_ReadLock;
    recordp = (struct C_AUFTRAGARTKD *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE TAUFARTK_U1 CURSOR WITH HOLD FOR
        SELECT
        AUFTRAGARTKD_LISTE
    from AUFTRAGARTKD
    where PKtaufartk
    FOR UPDATE;
    EXEC SQL OPEN TAUFARTK_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH TAUFARTK_U1
      into AUFTRAGARTKD_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         AUFTRAGARTKD_LISTE
    into AUFTRAGARTKD_ZEIGER(recordp)
    from AUFTRAGARTKD    HOLDLOCK
    where PKtaufartk;
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
/*  FUNCTION: pxAuftragArtKdUpdate                                        */
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

int pxAuftragArtKdUpdate
(
    struct tAUFTRAGARTKD * record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_AUFTRAGARTKD * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_AUFTRAGARTKD*10+F_Update;
    recordp = (struct C_AUFTRAGARTKD *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    AUFTRAGARTKD
    SET
    AUFTRAGARTKD_UPDATE(recordp)
    where current of TAUFARTK_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE TAUFARTK_U1;
    }
#else

    EXEC SQL UPDATE
    AUFTRAGARTKD
    SET
    AUFTRAGARTKD_UPDATE(recordp)
    where PKtaufartk;
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
/*  FUNCTION: pxAuftragArtKdInsert                                       */
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
int pxAuftragArtKdInsert
(
    struct tAUFTRAGARTKD * record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_AUFTRAGARTKD * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_AUFTRAGARTKD*10+F_Insert;
    recordp = (struct C_AUFTRAGARTKD *) record;

    EXEC SQL INSERT INTO
    AUFTRAGARTKD
    (AUFTRAGARTKD_LISTE)
    VALUES ( AUFTRAGARTKD_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    AUFTRAGARTKD
    VALUES ( AUFTRAGARTKD_ZEIGER(recordp) );   */


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
/*  FUNCTION: pxAuftragArtKdDelete                                        */
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

int pxAuftragArtKdDelete
(
    struct tAUFTRAGARTKD * record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_AUFTRAGARTKD * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_AUFTRAGARTKD*10+F_Delete;
    recordp = (struct C_AUFTRAGARTKD *) record;

    EXEC SQL DELETE FROM
    AUFTRAGARTKD
    where PKtaufartk;

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
