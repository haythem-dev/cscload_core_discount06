/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

                 (c) Copyright 1994-1995 by NORDAT Network GmbH
                              All rights reserved

    Embedded SQL for C application


    FILE: taufbem.c (.sqc)

    Database functions




    FUNCTIONS:

        pxAuftragBemStartBrowse  declare and open Cursor
        pxAuftragBemGetNext      get next record
        pxAuftragBemEndBrowse    close cursor
        pxAuftragBemRead         get one record
        pxAuftragBemReadLock     get one record with lock
        pxAuftragBemInsert       Insert record
        pxAuftragBemUpdate       Update record
        pxAuftragBemDelete       Delete record


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
#include "taufbem.h"
#include "keys.h"

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxAuftragBemStartBrowse                                   */
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
int pxAuftragBemStartBrowse
(
     struct tKDAUFTRAGBEM* record,
     int browseid
)
{

    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGBEM * recordp;
#ifdef MCtaufbem
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_KDAUFTRAGBEM*10+F_StartBrowse;
    recordp = (struct C_KDAUFTRAGBEM *) record;

    if (!(sizeof(struct C_KDAUFTRAGBEM) == sizeof(struct tKDAUFTRAGBEM)))
       return cDBXR_DEFINITION;


#ifdef MCtaufbem
    strcpy(matchcode,recordp->MCtaufbem);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        KDAUFTRAGBEM_LISTE
    from KDAUFTRAGBEM
    DWtaufbem
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        KDAUFTRAGBEM_LISTE
    from KDAUFTRAGBEM
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
/*  FUNCTION: pxAuftragBemGetNext                                       */
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
int pxAuftragBemGetNext
(
    struct tKDAUFTRAGBEM* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGBEM * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_KDAUFTRAGBEM*10+F_GetNext;
    recordp = (struct C_KDAUFTRAGBEM *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into KDAUFTRAGBEM_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into KDAUFTRAGBEM_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxAuftragBemEndBrowse                                     */
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
int pxAuftragBemEndBrowse
(
    int browseid
)
{
    functionnr = F_KDAUFTRAGBEM*10+F_EndBrowse;

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
/*  FUNCTION: pxAuftragBemRead                                          */
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

int pxAuftragBemRead
(
    struct tKDAUFTRAGBEM* record
#ifdef SKtaufbem
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{

    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGBEM * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRAGBEM*10+F_Read;
    recordp = (struct C_KDAUFTRAGBEM *) record;

#ifdef SKtaufbem
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        KDAUFTRAGBEM_LISTE
     into KDAUFTRAGBEM_ZEIGER(recordp)
     from KDAUFTRAGBEM
     where SKtaufbem;
     break;
    default:
#endif

    EXEC SQL SELECT
        KDAUFTRAGBEM_LISTE
     into KDAUFTRAGBEM_ZEIGER(recordp)
     from KDAUFTRAGBEM
     where PKtaufbem;

#ifdef SKtaufbem
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
/*  FUNCTION: pxAuftragBemReadLock                                      */
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
int pxAuftragBemReadLock
(
    struct tKDAUFTRAGBEM* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGBEM * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRAGBEM*10+F_ReadLock;
    recordp = (struct C_KDAUFTRAGBEM *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE TAUFBEM_U1 CURSOR WITH HOLD FOR
        SELECT
        KDAUFTRAGBEM_LISTE
    from KDAUFTRAGBEM
    where PKtaufbem
    FOR UPDATE;
    EXEC SQL OPEN TAUFBEM_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH TAUFBEM_U1
      into KDAUFTRAGBEM_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         KDAUFTRAGBEM_LISTE
    into KDAUFTRAGBEM_ZEIGER(recordp)
    from KDAUFTRAGBEM    HOLDLOCK
    where PKtaufbem;
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
/*  FUNCTION: pxAuftragBemUpdate                                        */
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

int pxAuftragBemUpdate
(
    struct tKDAUFTRAGBEM* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGBEM * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRAGBEM*10+F_Update;
    recordp = (struct C_KDAUFTRAGBEM *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    KDAUFTRAGBEM
    SET
    KDAUFTRAGBEM_UPDATE(recordp)
    where current of TAUFBEM_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE TAUFBEM_U1;
    }
#else

    EXEC SQL UPDATE
    KDAUFTRAGBEM
    SET
    KDAUFTRAGBEM_UPDATE(recordp)
    where PKtaufbem;
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
/*  FUNCTION: pxAuftragBemInsert                                       */
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
int pxAuftragBemInsert
(
    struct tKDAUFTRAGBEM* record
)
{

    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGBEM * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRAGBEM*10+F_Insert;
    recordp = (struct C_KDAUFTRAGBEM *) record;

    EXEC SQL INSERT INTO
    KDAUFTRAGBEM
    (KDAUFTRAGBEM_LISTE)
    VALUES ( KDAUFTRAGBEM_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    KDAUFTRAGBEM
    VALUES ( KDAUFTRAGBEM_ZEIGER(recordp) );   */


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
/*  FUNCTION: pxAuftragBemDelete                                        */
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

int pxAuftragBemDelete
(
    struct tKDAUFTRAGBEM* record
)
{

    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGBEM * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRAGBEM*10+F_Delete;
    recordp = (struct C_KDAUFTRAGBEM *) record;

    EXEC SQL DELETE FROM
    KDAUFTRAGBEM
    DWtaufbem;

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
