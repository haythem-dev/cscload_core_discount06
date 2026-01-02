/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

                 (c) Copyright 1994-1995 by NORDAT Network GmbH
                              All rights reserved

    Embedded SQL for C application


    FILE: tdispart.c (.sqc)

    Database functions




    FUNCTIONS:

        pxDispoArtikelStartBrowse  declare and open Cursor
        pxDispoArtikelGetNext      get next record
        pxDispoArtikelEndBrowse    close cursor
        pxDispoArtikelRead         get one record
        pxDispoArtikelReadLock     get one record with lock
        pxDispoArtikelInsert       Insert record
        pxDispoArtikelUpdate       Update record
        pxDispoArtikelDelete       Delete record


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
#include "tdispart.h"
#include "keys.h"

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxDispoArtikelStartBrowse                                   */
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
int pxDispoArtikelStartBrowse
(
     struct tDISPOARTIKEL* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_DISPOARTIKEL * recordp;
#ifdef MCtdispart
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_DISPOARTIKEL*10+F_StartBrowse;
    recordp = (struct C_DISPOARTIKEL *) record;

    if (!(sizeof(struct C_DISPOARTIKEL) == sizeof(struct tDISPOARTIKEL)))
       return cDBXR_DEFINITION;


#ifdef MCtdispart
    strcpy(matchcode,recordp->MCtdispart);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        DISPOARTIKEL_LISTE
    from DISPOARTIKEL
    DWtdispart
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        DISPOARTIKEL_LISTE
    from DISPOARTIKEL
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
/*  FUNCTION: pxDispoArtikelGetNext                                       */
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
int pxDispoArtikelGetNext
(
    struct tDISPOARTIKEL* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_DISPOARTIKEL * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_DISPOARTIKEL*10+F_GetNext;
    recordp = (struct C_DISPOARTIKEL *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into DISPOARTIKEL_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into DISPOARTIKEL_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxDispoArtikelEndBrowse                                     */
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
int pxDispoArtikelEndBrowse
(
    int browseid
)
{
    functionnr = F_DISPOARTIKEL*10+F_EndBrowse;

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
/*  FUNCTION: pxDispoArtikelRead                                          */
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

int pxDispoArtikelRead
(
    struct tDISPOARTIKEL* record
#ifdef SKtdispart
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_DISPOARTIKEL * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_DISPOARTIKEL*10+F_Read;
    recordp = (struct C_DISPOARTIKEL *) record;

#ifdef SKtdispart
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        DISPOARTIKEL_LISTE
     into DISPOARTIKEL_ZEIGER(recordp)
     from DISPOARTIKEL
     where SKtdispart;
     break;
    default:
#endif

    EXEC SQL SELECT
        DISPOARTIKEL_LISTE
     into DISPOARTIKEL_ZEIGER(recordp)
     from DISPOARTIKEL
     where PKtdispart;

#ifdef SKtdispart
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
/*  FUNCTION: pxDispoArtikelReadLock                                      */
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
int pxDispoArtikelReadLock
(
    struct tDISPOARTIKEL* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_DISPOARTIKEL * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_DISPOARTIKEL*10+F_ReadLock;
    recordp = (struct C_DISPOARTIKEL *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE TDISPART_U1 CURSOR WITH HOLD FOR
        SELECT
        DISPOARTIKEL_LISTE
    from DISPOARTIKEL
    where PKtdispart
    FOR UPDATE;
    EXEC SQL OPEN TDISPART_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH TDISPART_U1
      into DISPOARTIKEL_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         DISPOARTIKEL_LISTE
    into DISPOARTIKEL_ZEIGER(recordp)
    from DISPOARTIKEL    HOLDLOCK
    where PKtdispart;
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
/*  FUNCTION: pxDispoArtikelUpdate                                        */
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

int pxDispoArtikelUpdate
(
    struct tDISPOARTIKEL* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_DISPOARTIKEL * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_DISPOARTIKEL*10+F_Update;
    recordp = (struct C_DISPOARTIKEL *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    DISPOARTIKEL
    SET
    DISPOARTIKEL_UPDATE(recordp)
    where current of TDISPART_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE TDISPART_U1;
    }
#else

    EXEC SQL UPDATE
    DISPOARTIKEL
    SET
    DISPOARTIKEL_UPDATE(recordp)
    where PKtdispart;
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
/*  FUNCTION: pxDispoArtikelInsert                                       */
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
int pxDispoArtikelInsert
(
    struct tDISPOARTIKEL* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_DISPOARTIKEL * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_DISPOARTIKEL*10+F_Insert;
    recordp = (struct C_DISPOARTIKEL *) record;

    EXEC SQL INSERT INTO
    DISPOARTIKEL
    (DISPOARTIKEL_LISTE)
    VALUES ( DISPOARTIKEL_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    DISPOARTIKEL
    VALUES ( DISPOARTIKEL_ZEIGER(recordp) );   */


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
/*  FUNCTION: pxDispoArtikelDelete                                        */
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

int pxDispoArtikelDelete
(
    struct tDISPOARTIKEL* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_DISPOARTIKEL * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_DISPOARTIKEL*10+F_Delete;
    recordp = (struct C_DISPOARTIKEL *) record;

    EXEC SQL DELETE FROM
    DISPOARTIKEL
    where PKtdispart;

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
