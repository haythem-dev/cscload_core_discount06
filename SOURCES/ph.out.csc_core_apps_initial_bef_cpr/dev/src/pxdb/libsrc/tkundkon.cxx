/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

                 (c) Copyright 1994-1995 by NORDAT Network GmbH
                              All rights reserved

    Embedded SQL for C application


    FILE: tkundkon.c (.sqc)

    Database functions




    FUNCTIONS:

        pxKundeKondiStartBrowse  declare and open Cursor
        pxKundeKondiGetNext      get next record
        pxKundeKondiEndBrowse    close cursor
        pxKundeKondiRead         get one record
        pxKundeKondiReadLock     get one record with lock
        pxKundeKondiInsert       Insert record
        pxKundeKondiUpdate       Update record
        pxKundeKondiDelete       Delete record


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
#include "tkundkon.h"
#include "keys.h"

/* Global variables */
extern int  functionnr;

#define UNUSED(x) (void)(x)

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxKundeKondiStartBrowse                                   */
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
int pxKundeKondiStartBrowse
(
     struct tKUNDEKONDI* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
#ifdef MCtkundkon
    struct C_KUNDEKONDI * recordp;
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_KUNDEKONDI*10+F_StartBrowse;
#ifdef MCtkundkon
    recordp = (struct C_KUNDEKONDI *) record;
#else
    UNUSED(record);
#endif

    if (!(sizeof(struct C_KUNDEKONDI) == sizeof(struct tKUNDEKONDI)))
       return cDBXR_DEFINITION;


#ifdef MCtkundkon
    strcpy(matchcode,recordp->MCtkundkon);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        KUNDEKONDI_LISTE
    from KUNDEKONDI
    DWtkundkon
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        KUNDEKONDI_LISTE
    from KUNDEKONDI
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
/*  FUNCTION: pxKundeKondiGetNext                                       */
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
int pxKundeKondiGetNext
(
    struct tKUNDEKONDI* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KUNDEKONDI * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_KUNDEKONDI*10+F_GetNext;
    recordp = (struct C_KUNDEKONDI *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into KUNDEKONDI_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into KUNDEKONDI_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxKundeKondiEndBrowse                                     */
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
int pxKundeKondiEndBrowse
(
    int browseid
)
{
    functionnr = F_KUNDEKONDI*10+F_EndBrowse;

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
/*  FUNCTION: pxKundeKondiRead                                          */
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

int pxKundeKondiRead
(
    struct tKUNDEKONDI* record
#ifdef SKtkundkon
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KUNDEKONDI * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KUNDEKONDI*10+F_Read;
    recordp = (struct C_KUNDEKONDI *) record;

#ifdef SKtkundkon
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        KUNDEKONDI_LISTE
     into KUNDEKONDI_ZEIGER(recordp)
     from KUNDEKONDI
     where SKtkundkon;
     break;
    default:
#endif

    EXEC SQL SELECT
        KUNDEKONDI_LISTE
     into KUNDEKONDI_ZEIGER(recordp)
     from KUNDEKONDI
     where PKtkundkon;

#ifdef SKtkundkon
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
/*  FUNCTION: pxKundeKondiReadLock                                      */
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
int pxKundeKondiReadLock
(
    struct tKUNDEKONDI* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KUNDEKONDI * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KUNDEKONDI*10+F_ReadLock;
    recordp = (struct C_KUNDEKONDI *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE TKUNDKON_U1 CURSOR WITH HOLD FOR
        SELECT
        KUNDEKONDI_LISTE
    from KUNDEKONDI
    where PKtkundkon
    FOR UPDATE;
    EXEC SQL OPEN TKUNDKON_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH TKUNDKON_U1
      into KUNDEKONDI_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         KUNDEKONDI_LISTE
    into KUNDEKONDI_ZEIGER(recordp)
    from KUNDEKONDI    HOLDLOCK
    where PKtkundkon;
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
/*  FUNCTION: pxKundeKondiUpdate                                        */
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

int pxKundeKondiUpdate
(
    struct tKUNDEKONDI* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KUNDEKONDI * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KUNDEKONDI*10+F_Update;
    recordp = (struct C_KUNDEKONDI *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    KUNDEKONDI
    SET
    KUNDEKONDI_UPDATE(recordp)
    where current of TKUNDKON_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE TKUNDKON_U1;
    }
#else

    EXEC SQL UPDATE
    KUNDEKONDI
    SET
    KUNDEKONDI_UPDATE(recordp)
    where PKtkundkon;
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
/*  FUNCTION: pxKundeKondiInsert                                       */
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
int pxKundeKondiInsert
(
    struct tKUNDEKONDI* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KUNDEKONDI * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KUNDEKONDI*10+F_Insert;
    recordp = (struct C_KUNDEKONDI *) record;

    EXEC SQL INSERT INTO
    KUNDEKONDI
    (KUNDEKONDI_LISTE)
    VALUES ( KUNDEKONDI_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    KUNDEKONDI
    VALUES ( KUNDEKONDI_ZEIGER(recordp) );   */


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
/*  FUNCTION: pxKundeKondiDelete                                        */
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

int pxKundeKondiDelete
(
    struct tKUNDEKONDI* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KUNDEKONDI * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KUNDEKONDI*10+F_Delete;
    recordp = (struct C_KUNDEKONDI *) record;

    EXEC SQL DELETE FROM
    KUNDEKONDI
    where PKtkundkon;

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
