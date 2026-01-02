/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

                 (c) Copyright 1994-1995 by NORDAT Network GmbH
                              All rights reserved

    Embedded SQL for C application


    FILE: taufart.c (.sqc)

    Database functions




    FUNCTIONS:

        pxAuftragArtStartBrowse  declare and open Cursor
        pxAuftragArtGetNext      get next record
        pxAuftragArtEndBrowse    close cursor
        pxAuftragArtRead         get one record
        pxAuftragArtReadLock     get one record with lock
        pxAuftragArtInsert       Insert record
        pxAuftragArtUpdate       Update record
        pxAuftragArtDelete       Delete record


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
#include "taufart.h"
#include "keys.h"

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxAuftragArtStartBrowse                                   */
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
int pxAuftragArtStartBrowse
(
     struct tKDAUFTRAGART* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGART * recordp;
#ifdef MCtaufart
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_KDAUFTRAGART*10+F_StartBrowse;
    recordp = (struct C_KDAUFTRAGART *) record;

    if (!(sizeof(struct C_KDAUFTRAGART) == sizeof(struct tKDAUFTRAGART)))
       return cDBXR_DEFINITION;


#ifdef MCtaufart
    strcpy(matchcode,recordp->MCtaufart);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        KDAUFTRAGART_LISTE
    from KDAUFTRAGART
    DWtaufart
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        KDAUFTRAGART_LISTE
    from KDAUFTRAGART
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
/*  FUNCTION: pxAuftragArtGetNext                                       */
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
int pxAuftragArtGetNext
(
    struct tKDAUFTRAGART * record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGART * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_KDAUFTRAGART*10+F_GetNext;
    recordp = (struct C_KDAUFTRAGART *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into KDAUFTRAGART_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into KDAUFTRAGART_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxAuftragArtEndBrowse                                     */
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
int pxAuftragArtEndBrowse
(
    int browseid
)
{
    functionnr = F_KDAUFTRAGART*10+F_EndBrowse;

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
/*  FUNCTION: pxAuftragArtRead                                          */
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

int pxAuftragArtRead
(
    struct tKDAUFTRAGART * record
#ifdef SKtaufart
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGART * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRAGART*10+F_Read;
    recordp = (struct C_KDAUFTRAGART *) record;

#ifdef SKtaufart
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        KDAUFTRAGART_LISTE
     into KDAUFTRAGART_ZEIGER(recordp)
     from KDAUFTRAGART
     where SKtaufart;
     break;
    default:
#endif

    EXEC SQL SELECT
        KDAUFTRAGART_LISTE
     into KDAUFTRAGART_ZEIGER(recordp)
     from KDAUFTRAGART
     where PKtaufart;

#ifdef SKtaufart
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
/*  FUNCTION: pxAuftragArtReadLock                                      */
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
int pxAuftragArtReadLock
(
    struct tKDAUFTRAGART * record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGART * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRAGART*10+F_ReadLock;
    recordp = (struct C_KDAUFTRAGART *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE TAUFART_U1 CURSOR WITH HOLD FOR
        SELECT
        KDAUFTRAGART_LISTE
    from KDAUFTRAGART
    where PKtaufart
    FOR UPDATE;
    EXEC SQL OPEN TAUFART_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH TAUFART_U1
      into KDAUFTRAGART_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         KDAUFTRAGART_LISTE
    into KDAUFTRAGART_ZEIGER(recordp)
    from KDAUFTRAGART    HOLDLOCK
    where PKtaufart;
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
/*  FUNCTION: pxAuftragArtUpdate                                        */
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

int pxAuftragArtUpdate
(
    struct tKDAUFTRAGART * record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGART * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRAGART*10+F_Update;
    recordp = (struct C_KDAUFTRAGART *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    KDAUFTRAGART
    SET
    KDAUFTRAGART_UPDATE(recordp)
    where current of TAUFART_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE TAUFART_U1;
    }
#else

    EXEC SQL UPDATE
    KDAUFTRAGART
    SET
    KDAUFTRAGART_UPDATE(recordp)
    where PKtaufart;
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
/*  FUNCTION: pxAuftragArtInsert                                       */
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
int pxAuftragArtInsert
(
    struct tKDAUFTRAGART * record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGART * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRAGART*10+F_Insert;
    recordp = (struct C_KDAUFTRAGART *) record;

    EXEC SQL INSERT INTO
    KDAUFTRAGART
    (KDAUFTRAGART_LISTE)
    VALUES ( KDAUFTRAGART_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    KDAUFTRAGART
    VALUES ( KDAUFTRAGART_ZEIGER(recordp) );   */


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
/*  FUNCTION: pxAuftragArtDelete                                        */
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

int pxAuftragArtDelete
(
    struct tKDAUFTRAGART * record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGART * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRAGART*10+F_Delete;
    recordp = (struct C_KDAUFTRAGART *) record;

    EXEC SQL DELETE FROM
    KDAUFTRAGART
    where PKtaufart;

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
