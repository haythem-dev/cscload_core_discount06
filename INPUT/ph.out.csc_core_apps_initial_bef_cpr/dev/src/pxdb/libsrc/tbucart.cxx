/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

                 (c) Copyright 1994-1995 by NORDAT Network GmbH
                              All rights reserved

    Embedded SQL for C application


    FILE: tbucart.c (.sqc)

    Database functions




    FUNCTIONS:

        pxBuchArtStartBrowse  declare and open Cursor
        pxBuchArtGetNext      get next record
        pxBuchArtEndBrowse    close cursor
        pxBuchArtRead         get one record
        pxBuchArtReadLock     get one record with lock
        pxBuchArtInsert       Insert record
        pxBuchArtUpdate       Update record
        pxBuchArtDelete       Delete record


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
#include "tbucart.h"
#include "keys.h"

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxBuchArtStartBrowse                                   */
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
int pxBuchArtStartBrowse
(
     struct tBUCHUNGSART * record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_BUCHUNGSART * recordp;
#ifdef MCtbucart
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_BUCHUNGSART*10+F_StartBrowse;
    recordp = (struct C_BUCHUNGSART *) record;

    if (!(sizeof(struct C_BUCHUNGSART) == sizeof(struct tBUCHUNGSART)))
       return cDBXR_DEFINITION;


#ifdef MCtbucart
    strcpy(matchcode,recordp->MCtbucart);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        BUCHUNGSART_LISTE
    from BUCHUNGSART
    DWtbucart
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        BUCHUNGSART_LISTE
    from BUCHUNGSART
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
/*  FUNCTION: pxBuchArtGetNext                                       */
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
int pxBuchArtGetNext
(
    struct tBUCHUNGSART * record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_BUCHUNGSART * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_BUCHUNGSART*10+F_GetNext;
    recordp = (struct C_BUCHUNGSART *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into BUCHUNGSART_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into BUCHUNGSART_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxBuchArtEndBrowse                                     */
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
int pxBuchArtEndBrowse
(
    int browseid
)
{
    functionnr = F_BUCHUNGSART*10+F_EndBrowse;

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
/*  FUNCTION: pxBuchArtRead                                          */
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

int pxBuchArtRead
(
    struct tBUCHUNGSART * record
#ifdef SKtbucart
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_BUCHUNGSART * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_BUCHUNGSART*10+F_Read;
    recordp = (struct C_BUCHUNGSART *) record;

#ifdef SKtbucart
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        BUCHUNGSART_LISTE
     into BUCHUNGSART_ZEIGER(recordp)
     from BUCHUNGSART
     where SKtbucart;
     break;
    default:
#endif

    EXEC SQL SELECT
        BUCHUNGSART_LISTE
     into BUCHUNGSART_ZEIGER(recordp)
     from BUCHUNGSART
     where PKtbucart;

#ifdef SKtbucart
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
/*  FUNCTION: pxBuchArtReadLock                                      */
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
int pxBuchArtReadLock
(
    struct tBUCHUNGSART * record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_BUCHUNGSART * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_BUCHUNGSART*10+F_ReadLock;
    recordp = (struct C_BUCHUNGSART *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE TBUCART_U1 CURSOR WITH HOLD FOR
        SELECT
        BUCHUNGSART_LISTE
    from BUCHUNGSART
    where PKtbucart
    FOR UPDATE;
    EXEC SQL OPEN TBUCART_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH TBUCART_U1
      into BUCHUNGSART_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         BUCHUNGSART_LISTE
    into BUCHUNGSART_ZEIGER(recordp)
    from BUCHUNGSART    HOLDLOCK
    where PKtbucart;
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
/*  FUNCTION: pxBuchArtUpdate                                        */
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

int pxBuchArtUpdate
(
    struct tBUCHUNGSART * record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_BUCHUNGSART * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_BUCHUNGSART*10+F_Update;
    recordp = (struct C_BUCHUNGSART *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    BUCHUNGSART
    SET
    BUCHUNGSART_UPDATE(recordp)
    where current of TBUCART_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE TBUCART_U1;
    }
#else

    EXEC SQL UPDATE
    BUCHUNGSART
    SET
    BUCHUNGSART_UPDATE(recordp)
    where PKtbucart;
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
/*  FUNCTION: pxBuchArtInsert                                       */
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
int pxBuchArtInsert
(
    struct tBUCHUNGSART * record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_BUCHUNGSART * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_BUCHUNGSART*10+F_Insert;
    recordp = (struct C_BUCHUNGSART *) record;

    EXEC SQL INSERT INTO
    BUCHUNGSART
    (BUCHUNGSART_LISTE)
    VALUES ( BUCHUNGSART_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    BUCHUNGSART
    VALUES ( BUCHUNGSART_ZEIGER(recordp) );   */


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
/*  FUNCTION: pxBuchArtDelete                                        */
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

int pxBuchArtDelete
(
    struct tBUCHUNGSART * record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_BUCHUNGSART * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_BUCHUNGSART*10+F_Delete;
    recordp = (struct C_BUCHUNGSART *) record;

    EXEC SQL DELETE FROM
    BUCHUNGSART
    where PKtbucart;

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
