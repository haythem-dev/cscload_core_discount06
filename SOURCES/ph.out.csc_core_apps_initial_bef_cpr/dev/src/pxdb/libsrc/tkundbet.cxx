/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

                 (c) Copyright 1994-1995 by NORDAT Network GmbH
                              All rights reserved

    Embedded SQL for C application


    FILE: tkundbet.c (.sqc)

    Database functions




    FUNCTIONS:

        pxKundeBetriebStartBrowse  declare and open Cursor
        pxKundeBetriebGetNext      get next record
        pxKundeBetriebEndBrowse    close cursor
        pxKundeBetriebRead         get one record
        pxKundeBetriebReadLock     get one record with lock
        pxKundeBetriebInsert       Insert record
        pxKundeBetriebUpdate       Update record
        pxKundeBetriebDelete       Delete record


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
#include "tkundbet.h"
#include "keys.h"

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxKundeBetriebStartBrowse                                   */
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
int pxKundeBetriebStartBrowse
(
     struct tKDBETRIEBSENDE* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDBETRIEBSENDE * recordp;
#ifdef MCtkundbet
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_KDBETRIEBSENDE*10+F_StartBrowse;
    recordp = (struct C_KDBETRIEBSENDE *) record;

    if (!(sizeof(struct C_KDBETRIEBSENDE) == sizeof(struct tKDBETRIEBSENDE)))
       return cDBXR_DEFINITION;


#ifdef MCtkundbet
    strcpy(matchcode,recordp->MCtkundbet);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        KDBETRIEBSENDE_LISTE
    from KDBETRIEBSENDE
    DWtkundbet
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        KDBETRIEBSENDE_LISTE
    from KDBETRIEBSENDE
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
/*  FUNCTION: pxKundeBetriebGetNext                                       */
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
int pxKundeBetriebGetNext
(
    struct tKDBETRIEBSENDE* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDBETRIEBSENDE * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_KDBETRIEBSENDE*10+F_GetNext;
    recordp = (struct C_KDBETRIEBSENDE *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into KDBETRIEBSENDE_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into KDBETRIEBSENDE_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxKundeBetriebEndBrowse                                     */
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
int pxKundeBetriebEndBrowse
(
    int browseid
)
{
    functionnr = F_KDBETRIEBSENDE*10+F_EndBrowse;

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
/*  FUNCTION: pxKundeBetriebRead                                          */
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

int pxKundeBetriebRead
(
    struct tKDBETRIEBSENDE* record
#ifdef SKtkundbet
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDBETRIEBSENDE * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDBETRIEBSENDE*10+F_Read;
    recordp = (struct C_KDBETRIEBSENDE *) record;

#ifdef SKtkundbet
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        KDBETRIEBSENDE_LISTE
     into KDBETRIEBSENDE_ZEIGER(recordp)
     from KDBETRIEBSENDE
     where SKtkundbet;
     break;
    default:
#endif

    EXEC SQL SELECT
        KDBETRIEBSENDE_LISTE
     into KDBETRIEBSENDE_ZEIGER(recordp)
     from KDBETRIEBSENDE
     where PKtkundbet;

#ifdef SKtkundbet
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
/*  FUNCTION: pxKundeBetriebReadLock                                      */
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
int pxKundeBetriebReadLock
(
    struct tKDBETRIEBSENDE* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDBETRIEBSENDE * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDBETRIEBSENDE*10+F_ReadLock;
    recordp = (struct C_KDBETRIEBSENDE *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE TKUNDBET_U1 CURSOR WITH HOLD FOR
        SELECT
        KDBETRIEBSENDE_LISTE
    from KDBETRIEBSENDE
    where PKtkundbet
    FOR UPDATE;
    EXEC SQL OPEN TKUNDBET_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH TKUNDBET_U1
      into KDBETRIEBSENDE_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         KDBETRIEBSENDE_LISTE
    into KDBETRIEBSENDE_ZEIGER(recordp)
    from KDBETRIEBSENDE    HOLDLOCK
    where PKtkundbet;
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
/*  FUNCTION: pxKundeBetriebUpdate                                        */
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

int pxKundeBetriebUpdate
(
    struct tKDBETRIEBSENDE* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDBETRIEBSENDE * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDBETRIEBSENDE*10+F_Update;
    recordp = (struct C_KDBETRIEBSENDE *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    KDBETRIEBSENDE
    SET
    KDBETRIEBSENDE_UPDATE(recordp)
    where current of TKUNDBET_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE TKUNDBET_U1;
    }
#else

    EXEC SQL UPDATE
    KDBETRIEBSENDE
    SET
    KDBETRIEBSENDE_UPDATE(recordp)
    where PKtkundbet;
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
/*  FUNCTION: pxKundeBetriebInsert                                       */
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
int pxKundeBetriebInsert
(
    struct tKDBETRIEBSENDE* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDBETRIEBSENDE * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDBETRIEBSENDE*10+F_Insert;
    recordp = (struct C_KDBETRIEBSENDE *) record;

    EXEC SQL INSERT INTO
    KDBETRIEBSENDE
    (KDBETRIEBSENDE_LISTE)
    VALUES ( KDBETRIEBSENDE_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    KDBETRIEBSENDE
    VALUES ( KDBETRIEBSENDE_ZEIGER(recordp) );   */


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
/*  FUNCTION: pxKundeBetriebDelete                                        */
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

int pxKundeBetriebDelete
(
    struct tKDBETRIEBSENDE* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDBETRIEBSENDE * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDBETRIEBSENDE*10+F_Delete;
    recordp = (struct C_KDBETRIEBSENDE *) record;

    EXEC SQL DELETE FROM
    KDBETRIEBSENDE
    where PKtkundbet;

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
