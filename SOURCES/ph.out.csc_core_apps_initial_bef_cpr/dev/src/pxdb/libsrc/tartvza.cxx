/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

                 (c) Copyright 1994-2000 by NORDAT Network GmbH
                              All rights reserved

    Embedded SQL for C application


    FILE: tartvza.c (.sqc)

    Database functions for local article data




    FUNCTIONS:

        pxFArtikelStartBrowse  declare and open Cursor
        pxFArtikelGetNext      get next record
        pxFArtikelEndBrowse    close cursor
        pxFArtikelRead         get one record
        pxFArtikelReadLock     get one record with lock
        pxFArtikelInsert       Insert record
        pxFArtikelUpdate       Update record
        pxFArtikelDelete       Delete record


REVISION HISTORY

25 Apr 2000 V1.00 REV 00 written by Dietmar Schloetel

*/


#include <stddef.h>         /* standard C run-time header */
#include <stdio.h>          /* standard C run-time header */
#include <pxrecord.h>       /* all record structures */
#include "pxdbxx.h"
#include "pxdbfunc.h"
#include <ndefs.h>
#include <pxenv.h>
#include "tartvza.h"
#include "keys.h"

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxFArtikelStartBrowse                                   */
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
int pxFArtikelStartBrowse
(
     struct tFARTIKEL* record,
     int browseid
)
{

    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTIKELLOKAL * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_ARTIKELLOKAL*10+F_StartBrowse;
    recordp = (struct C_ARTIKELLOKAL *) record;

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        ARTIKELLOKAL_LISTE
    from ARTIKELLOKAL
    DWtartvza
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        ARTIKELLOKAL_LISTE
    from ARTIKELLOKAL
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
/*  FUNCTION: pxFArtikelGetNext                                       */
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
int pxFArtikelGetNext
(
    struct tFARTIKEL* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTIKELLOKAL * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_ARTIKELLOKAL*10+F_GetNext;
    recordp = (struct C_ARTIKELLOKAL *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into ARTIKELLOKAL_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into ARTIKELLOKAL_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxFArtikelEndBrowse                                     */
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
int pxFArtikelEndBrowse
(
    int browseid
)
{
    functionnr = F_ARTIKELLOKAL*10+F_EndBrowse;

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
/*  FUNCTION: pxFArtikelRead                                          */
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

int pxFArtikelRead
(
    struct tFARTIKEL* record
)
{

    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTIKELLOKAL * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTIKELLOKAL*10+F_Read;
    recordp = (struct C_ARTIKELLOKAL *) record;



    EXEC SQL SELECT
        ARTIKELLOKAL_LISTE
     into ARTIKELLOKAL_ZEIGER(recordp)
    from ARTIKELLOKAL
     where PKtartvza;

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
/*  FUNCTION: pxFArtikelReadLock                                      */
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
int pxFArtikelReadLock
(
    struct tFARTIKEL* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTIKELLOKAL * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTIKELLOKAL*10+F_ReadLock;
    recordp = (struct C_ARTIKELLOKAL *) record;

#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE TARTIKELLOKAL_U1 CURSOR WITH HOLD FOR
        SELECT
        ARTIKELLOKAL_LISTE
    from ARTIKELLOKAL
    where PKtartvza
    FOR UPDATE;
    EXEC SQL OPEN TARTIKELLOKAL_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH TARTIKELLOKAL_U1
      into ARTIKELLOKAL_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         ARTIKELLOKAL_LISTE
    into ARTIKELLOKAL_ZEIGER(recordp)
    from ARTIKELLOKAL    HOLDLOCK
    where PKtartvza;
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
/*  FUNCTION: pxFArtikelUpdate                                        */
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

int pxFArtikelUpdate
(
    struct tFARTIKEL* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTIKELLOKAL * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTIKELLOKAL*10+F_Update;
    recordp = (struct C_ARTIKELLOKAL *) record;

#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    ARTIKELLOKAL
    SET
    ARTIKELLOKAL_UPDATE(recordp)
    where current of TARTIKELLOKAL_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE TARTIKELLOKAL_U1;
    }
#else
    EXEC SQL UPDATE
    ARTIKELLOKAL
    SET
    ARTIKELLOKAL_UPDATE(recordp)
    where PKtartvza;
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
/*  FUNCTION: pxFArtikelInsert                                       */
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
int pxFArtikelInsert
(
    struct tFARTIKEL* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTIKELLOKAL * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTIKELLOKAL*10+F_Insert;
    recordp = (struct C_ARTIKELLOKAL *) record;

    EXEC SQL INSERT INTO
    ARTIKELLOKAL
    (ARTIKELLOKAL_LISTE)
    VALUES ( ARTIKELLOKAL_ZEIGER(recordp) );


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
/*  FUNCTION: pxFArtikelDelete                                        */
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

int pxFArtikelDelete
(
    struct tFARTIKEL* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTIKELLOKAL * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTIKELLOKAL*10+F_Delete;
    recordp = (struct C_ARTIKELLOKAL *) record;

    EXEC SQL DELETE FROM
    ARTIKELLOKAL
    where PKtartvza;

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
