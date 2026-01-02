/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

                 (c) Copyright 1994-1995 by NORDAT Network GmbH
                              All rights reserved

    Embedded SQL for C application


    FILE: tartnum.c (.sqc)

    Database functions




    FUNCTIONS:

        pxArtikelNummernStartBrowse  declare and open Cursor
        pxArtikelNummernGetNext      get next record
        pxArtikelNummernEndBrowse    close cursor
        pxArtikelNummernRead         get one record
        pxArtikelNummernReadLock     get one record with lock
        pxArtikelNummernInsert       Insert record
        pxArtikelNummernUpdate       Update record
        pxArtikelNummernDelete       Delete record


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
#include <tartnum.h>
#include <keys.h>

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxArtikelNummernStartBrowse                                   */
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
int pxArtikelNummernStartBrowse
(
     struct tARTIKELNUMMERN* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTIKELNUMMERN * recordp;
#ifdef MCtartnum
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_ARTIKELNUMMERN*10+F_StartBrowse;
    recordp = (struct C_ARTIKELNUMMERN *) record;

    if (!(sizeof(struct C_ARTIKELNUMMERN) == sizeof(struct tARTIKELNUMMERN)))
       return cDBXR_DEFINITION;


#ifdef MCtartnum
    strcpy(matchcode,recordp->MCtartnum);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        ARTIKELNUMMERN_LISTE
    from ARTIKELNUMMERN
    DWtartnum
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        ARTIKELNUMMERN_LISTE
    from ARTIKELNUMMERN
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif
    EXEC SQL DECLARE C2 CURSOR FOR
        SELECT
        ARTIKELNUMMERN_LISTE
    from ARTIKELNUMMERN
    where PZN  = :recordp->PZN
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif
    EXEC SQL DECLARE C3 CURSOR FOR
        SELECT
        ARTIKELNUMMERN_LISTE
    from ARTIKELNUMMERN
    where ARTIKEL_NR  = :recordp->ARTIKEL_NR
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
       case cCRSARTNUM_PZN        :
          EXEC SQL OPEN C2;
          break;
       case cCRSARTNUM_ARTIKELNR  :
          EXEC SQL OPEN C3;
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
/*  FUNCTION: pxArtikelNummernGetNext                                       */
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
int pxArtikelNummernGetNext
(
    struct tARTIKELNUMMERN* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTIKELNUMMERN * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_ARTIKELNUMMERN*10+F_GetNext;
    recordp = (struct C_ARTIKELNUMMERN *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into ARTIKELNUMMERN_ZEIGER(recordp);
          break;
       case cCRSARTNUM_PZN                   :
          EXEC SQL FETCH C2
          into ARTIKELNUMMERN_ZEIGER(recordp);
          break;
       case cCRSARTNUM_ARTIKELNR             :
          EXEC SQL FETCH C3
          into ARTIKELNUMMERN_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into ARTIKELNUMMERN_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxArtikelNummernEndBrowse                                     */
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
int pxArtikelNummernEndBrowse
(
    int browseid
)
{
    functionnr = F_ARTIKELNUMMERN*10+F_EndBrowse;

    /* close the cursor */
    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL CLOSE C0;
          break;
       case cCRSARTNUM_PZN       :
          EXEC SQL CLOSE C2;
          break;
       case cCRSARTNUM_ARTIKELNR             :
          EXEC SQL CLOSE C3;
          break;
       default:
          EXEC SQL CLOSE C1;
          break;
    }
    return 0;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxArtikelNummernRead                                          */
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

int pxArtikelNummernRead
(
    struct tARTIKELNUMMERN* record
#ifdef SKtartnum
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTIKELNUMMERN * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTIKELNUMMERN*10+F_Read;
    recordp = (struct C_ARTIKELNUMMERN *) record;

#ifdef SKtartnum
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        ARTIKELNUMMERN_LISTE
     into ARTIKELNUMMERN_ZEIGER(recordp)
     from ARTIKELNUMMERN
     where SKtartnum;
     break;
    default:
#endif

    EXEC SQL SELECT
        ARTIKELNUMMERN_LISTE
     into ARTIKELNUMMERN_ZEIGER(recordp)
     from ARTIKELNUMMERN
     where PKtartnum;

#ifdef SKtartnum
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
/*  FUNCTION: pxArtikelNummernReadLock                                      */
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
int pxArtikelNummernReadLock
(
    struct tARTIKELNUMMERN* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTIKELNUMMERN * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTIKELNUMMERN*10+F_ReadLock;
    recordp = (struct C_ARTIKELNUMMERN *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE TARTNUM_U1 CURSOR WITH HOLD FOR
        SELECT
        ARTIKELNUMMERN_LISTE
    from ARTIKELNUMMERN
    where PKtartnum
    FOR UPDATE;
    EXEC SQL OPEN TARTNUM_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH TARTNUM_U1
      into ARTIKELNUMMERN_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         ARTIKELNUMMERN_LISTE
    into ARTIKELNUMMERN_ZEIGER(recordp)
    from ARTIKELNUMMERN    HOLDLOCK
    where PKtartnum;
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
/*  FUNCTION: pxArtikelNummernUpdate                                        */
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

int pxArtikelNummernUpdate
(
    struct tARTIKELNUMMERN* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTIKELNUMMERN * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTIKELNUMMERN*10+F_Update;
    recordp = (struct C_ARTIKELNUMMERN *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    ARTIKELNUMMERN
    SET
    ARTIKELNUMMERN_UPDATE(recordp)
    where current of TARTNUM_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE TARTNUM_U1;
    }
#else

    EXEC SQL UPDATE
    ARTIKELNUMMERN
    SET
    ARTIKELNUMMERN_UPDATE(recordp)
    where PKtartnum;
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
/*  FUNCTION: pxArtikelNummernInsert                                       */
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
int pxArtikelNummernInsert
(
    struct tARTIKELNUMMERN* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTIKELNUMMERN * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTIKELNUMMERN*10+F_Insert;
    recordp = (struct C_ARTIKELNUMMERN *) record;

    EXEC SQL INSERT INTO
    ARTIKELNUMMERN
    (ARTIKELNUMMERN_LISTE)
    VALUES ( ARTIKELNUMMERN_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    ARTIKELNUMMERN
    VALUES ( ARTIKELNUMMERN_ZEIGER(recordp) );   */


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
/*  FUNCTION: pxArtikelNummernDelete                                        */
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

int pxArtikelNummernDelete
(
    struct tARTIKELNUMMERN* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTIKELNUMMERN * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTIKELNUMMERN*10+F_Delete;
    recordp = (struct C_ARTIKELNUMMERN *) record;

    EXEC SQL DELETE FROM
    ARTIKELNUMMERN
    where PKtartnum;

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
