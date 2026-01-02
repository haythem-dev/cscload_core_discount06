/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

                 (c) Copyright 1994-1995 by NORDAT Network GmbH
                              All rights reserved

    Embedded SQL for C application


    FILE: taufende.c (.sqc)

    Database functions




    FUNCTIONS:

        pxAuftragEndeZeitStartBrowse  declare and open Cursor
        pxAuftragEndeZeitGetNext      get next record
        pxAuftragEndeZeitEndBrowse    close cursor
        pxAuftragEndeZeitRead         get one record
        pxAuftragEndeZeitReadLock     get one record with lock
        pxAuftragEndeZeitInsert       Insert record
        pxAuftragEndeZeitUpdate       Update record
        pxAuftragEndeZeitDelete       Delete record


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
#include "taufende.h"
#include "keys.h"

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxAuftragEndeZeitStartBrowse                                   */
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
int pxAuftragEndeZeitStartBrowse
(
     struct tKDAUFTRAGENDEZEIT* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGENDEZEIT * recordp;
#ifdef MCtaufende
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_KDAUFTRAGENDEZEIT*10+F_StartBrowse;
    recordp = (struct C_KDAUFTRAGENDEZEIT *) record;

    if (!(sizeof(struct C_KDAUFTRAGENDEZEIT) == sizeof(struct tKDAUFTRAGENDEZEIT)))
       return cDBXR_DEFINITION;


#ifdef MCtaufende
    strcpy(matchcode,recordp->MCtaufende);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        KDAUFTRAGENDEZEIT_LISTE
    from KDAUFTRAGENDEZEIT
    DWtaufende
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        KDAUFTRAGENDEZEIT_LISTE
    from KDAUFTRAGENDEZEIT
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
/*  FUNCTION: pxAuftragEndeZeitGetNext                                       */
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
int pxAuftragEndeZeitGetNext
(
    struct tKDAUFTRAGENDEZEIT* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGENDEZEIT * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_KDAUFTRAGENDEZEIT*10+F_GetNext;
    recordp = (struct C_KDAUFTRAGENDEZEIT *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into KDAUFTRAGENDEZEIT_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into KDAUFTRAGENDEZEIT_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxAuftragEndeZeitEndBrowse                                     */
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
int pxAuftragEndeZeitEndBrowse
(
    int browseid
)
{
    functionnr = F_KDAUFTRAGENDEZEIT*10+F_EndBrowse;

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
/*  FUNCTION: pxAuftragEndeZeitRead                                          */
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

int pxAuftragEndeZeitRead
(
    struct tKDAUFTRAGENDEZEIT* record
#ifdef SKtaufende
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGENDEZEIT * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRAGENDEZEIT*10+F_Read;
    recordp = (struct C_KDAUFTRAGENDEZEIT *) record;

#ifdef SKtaufende
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        KDAUFTRAGENDEZEIT_LISTE
     into KDAUFTRAGENDEZEIT_ZEIGER(recordp)
     from KDAUFTRAGENDEZEIT
     where SKtaufende;
     break;
    default:
#endif

    EXEC SQL SELECT
        KDAUFTRAGENDEZEIT_LISTE
     into KDAUFTRAGENDEZEIT_ZEIGER(recordp)
     from KDAUFTRAGENDEZEIT
     where PKtaufende;

#ifdef SKtaufende
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
/*  FUNCTION: pxAuftragEndeZeitReadLock                                      */
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
int pxAuftragEndeZeitReadLock
(
    struct tKDAUFTRAGENDEZEIT* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGENDEZEIT * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRAGENDEZEIT*10+F_ReadLock;
    recordp = (struct C_KDAUFTRAGENDEZEIT *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE TAUFENDE_U1 CURSOR WITH HOLD FOR
        SELECT
        KDAUFTRAGENDEZEIT_LISTE
    from KDAUFTRAGENDEZEIT
    where PKtaufende
    FOR UPDATE;
    EXEC SQL OPEN TAUFENDE_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH TAUFENDE_U1
      into KDAUFTRAGENDEZEIT_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         KDAUFTRAGENDEZEIT_LISTE
    into KDAUFTRAGENDEZEIT_ZEIGER(recordp)
    from KDAUFTRAGENDEZEIT    HOLDLOCK
    where PKtaufende;
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
/*  FUNCTION: pxAuftragEndeZeitUpdate                                        */
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

int pxAuftragEndeZeitUpdate
(
    struct tKDAUFTRAGENDEZEIT* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGENDEZEIT * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRAGENDEZEIT*10+F_Update;
    recordp = (struct C_KDAUFTRAGENDEZEIT *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    KDAUFTRAGENDEZEIT
    SET
    KDAUFTRAGENDEZEIT_UPDATE(recordp)
    where current of TAUFENDE_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE TAUFENDE_U1;
    }
#else

    EXEC SQL UPDATE
    KDAUFTRAGENDEZEIT
    SET
    KDAUFTRAGENDEZEIT_UPDATE(recordp)
    where PKtaufende;
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
/*  FUNCTION: pxAuftragEndeZeitInsert                                       */
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
int pxAuftragEndeZeitInsert
(
    struct tKDAUFTRAGENDEZEIT* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGENDEZEIT * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRAGENDEZEIT*10+F_Insert;
    recordp = (struct C_KDAUFTRAGENDEZEIT *) record;

    EXEC SQL INSERT INTO
    KDAUFTRAGENDEZEIT
    (KDAUFTRAGENDEZEIT_LISTE)
    VALUES ( KDAUFTRAGENDEZEIT_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    KDAUFTRAGENDEZEIT
    VALUES ( KDAUFTRAGENDEZEIT_ZEIGER(recordp) );   */


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
/*  FUNCTION: pxAuftragEndeZeitDelete                                        */
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

int pxAuftragEndeZeitDelete
(
    struct tKDAUFTRAGENDEZEIT* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGENDEZEIT * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRAGENDEZEIT*10+F_Delete;
    recordp = (struct C_KDAUFTRAGENDEZEIT *) record;

    EXEC SQL DELETE FROM
    KDAUFTRAGENDEZEIT
    where PKtaufende;

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
