/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

                 (c) Copyright 1994-1995 by NORDAT Network GmbH
                              All rights reserved

    Embedded SQL for C application


    FILE: tkundgrp.c (.sqc)

    Database functions




    FUNCTIONS:

        pxKundenGruppeStartBrowse  declare and open Cursor
        pxKundenGruppeGetNext      get next record
        pxKundenGruppeEndBrowse    close cursor
        pxKundenGruppeRead         get one record
        pxKundenGruppeReadLock     get one record with lock
        pxKundenGruppeInsert       Insert record
        pxKundenGruppeUpdate       Update record
        pxKundenGruppeDelete       Delete record


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
#include "tkundgrp.h"
#include "keys.h"

/* Global variables */
extern int  functionnr;

#define UNUSED(x) (void)(x)

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxKundenGruppeStartBrowse                                   */
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
int pxKundenGruppeStartBrowse
(
     struct tKUNDENGRUPPE* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
#ifdef MCtkundgrp
    struct C_KUNDENGRUPPE * recordp;
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_KUNDENGRUPPE*10+F_StartBrowse;
#ifdef MCtkundgrp
    recordp = (struct C_KUNDENGRUPPE *) record;
#else
    UNUSED(record);
#endif

    if (!(sizeof(struct C_KUNDENGRUPPE) == sizeof(struct tKUNDENGRUPPE)))
       return cDBXR_DEFINITION;


#ifdef MCtkundgrp
    strcpy(matchcode,recordp->MCtkundgrp);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        KUNDENGRUPPE_LISTE
    from KUNDENGRUPPE
    DWtkundgrp
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        KUNDENGRUPPE_LISTE
    from KUNDENGRUPPE
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
/*  FUNCTION: pxKundenGruppeGetNext                                       */
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
int pxKundenGruppeGetNext
(
    struct tKUNDENGRUPPE* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KUNDENGRUPPE * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_KUNDENGRUPPE*10+F_GetNext;
    recordp = (struct C_KUNDENGRUPPE *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into KUNDENGRUPPE_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into KUNDENGRUPPE_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxKundenGruppeEndBrowse                                     */
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
int pxKundenGruppeEndBrowse
(
    int browseid
)
{
    functionnr = F_KUNDENGRUPPE*10+F_EndBrowse;

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
/*  FUNCTION: pxKundenGruppeRead                                          */
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

int pxKundenGruppeRead
(
    struct tKUNDENGRUPPE* record
#ifdef SKtkundgrp
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KUNDENGRUPPE * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KUNDENGRUPPE*10+F_Read;
    recordp = (struct C_KUNDENGRUPPE *) record;

#ifdef SKtkundgrp
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        KUNDENGRUPPE_LISTE
     into KUNDENGRUPPE_ZEIGER(recordp)
     from KUNDENGRUPPE
     where SKtkundgrp;
     break;
    default:
#endif

    EXEC SQL SELECT
        KUNDENGRUPPE_LISTE
     into KUNDENGRUPPE_ZEIGER(recordp)
     from KUNDENGRUPPE
     where PKtkundgrp;

#ifdef SKtkundgrp
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
/*  FUNCTION: pxKundenGruppeReadLock                                      */
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
int pxKundenGruppeReadLock
(
    struct tKUNDENGRUPPE* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KUNDENGRUPPE * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KUNDENGRUPPE*10+F_ReadLock;
    recordp = (struct C_KUNDENGRUPPE *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE TKUNDGRP_U1 CURSOR WITH HOLD FOR
        SELECT
        KUNDENGRUPPE_LISTE
    from KUNDENGRUPPE
    where PKtkundgrp
    FOR UPDATE;
    EXEC SQL OPEN TKUNDGRP_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH TKUNDGRP_U1
      into KUNDENGRUPPE_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         KUNDENGRUPPE_LISTE
    into KUNDENGRUPPE_ZEIGER(recordp)
    from KUNDENGRUPPE    HOLDLOCK
    where PKtkundgrp;
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
/*  FUNCTION: pxKundenGruppeUpdate                                        */
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

int pxKundenGruppeUpdate
(
    struct tKUNDENGRUPPE* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KUNDENGRUPPE * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KUNDENGRUPPE*10+F_Update;
    recordp = (struct C_KUNDENGRUPPE *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    KUNDENGRUPPE
    SET
    KUNDENGRUPPE_UPDATE(recordp)
    where current of TKUNDGRP_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE TKUNDGRP_U1;
    }
#else

    EXEC SQL UPDATE
    KUNDENGRUPPE
    SET
    KUNDENGRUPPE_UPDATE(recordp)
    where PKtkundgrp;
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
/*  FUNCTION: pxKundenGruppeInsert                                       */
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
int pxKundenGruppeInsert
(
    struct tKUNDENGRUPPE* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KUNDENGRUPPE * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KUNDENGRUPPE*10+F_Insert;
    recordp = (struct C_KUNDENGRUPPE *) record;

    EXEC SQL INSERT INTO
    KUNDENGRUPPE
    (KUNDENGRUPPE_LISTE)
    VALUES ( KUNDENGRUPPE_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    KUNDENGRUPPE
    VALUES ( KUNDENGRUPPE_ZEIGER(recordp) );   */


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
/*  FUNCTION: pxKundenGruppeDelete                                        */
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

int pxKundenGruppeDelete
(
    struct tKUNDENGRUPPE* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KUNDENGRUPPE * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KUNDENGRUPPE*10+F_Delete;
    recordp = (struct C_KUNDENGRUPPE *) record;

    EXEC SQL DELETE FROM
    KUNDENGRUPPE
    where PKtkundgrp;

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
