/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

                 (c) Copyright 1994-1995 by NORDAT Network GmbH
                              All rights reserved

    Embedded SQL for C application


    FILE: tnlprot.c (.sqc)

    Database functions




    FUNCTIONS:

        pxNachLiefProtStartBrowse  declare and open Cursor
        pxNachLiefProtGetNext      get next record
        pxNachLiefProtEndBrowse    close cursor
        pxNachLiefProtRead         get one record
        pxNachLiefProtReadLock     get one record with lock
        pxNachLiefProtInsert       Insert record
        pxNachLiefProtUpdate       Update record
        pxNachLiefProtDelete       Delete record


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
#include "tnlprot.h"
#include "keys.h"

/* Global variables */
extern int  functionnr;

#define UNUSED(x) (void)(x)

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxNachLiefProtStartBrowse                                   */
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
int pxNachLiefProtStartBrowse
(
     struct tNACHLIEFPROT* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
	struct C_NACHLIEFPROT * recordp;
#ifdef MCtnlprot
    struct C_NACHLIEFPROT * recordp;
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_NACHLIEFPROT*10+F_StartBrowse;
#ifdef MCtnlprot
    recordp = (struct C_NACHLIEFPROT *) record;
#else
    UNUSED(record);
#endif
	recordp = (struct C_NACHLIEFPROT *) record;
    if (!(sizeof(struct C_NACHLIEFPROT) == sizeof(struct tNACHLIEFPROT)))
       return cDBXR_DEFINITION;


#ifdef MCtnlprot
    strcpy(matchcode,recordp->MCtnlprot);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        NACHLIEFPROT_LISTE
    from NACHLIEFPROT
    DWtnlprot
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        NACHLIEFPROT_LISTE
    from NACHLIEFPROT
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
/*  FUNCTION: pxNachLiefProtGetNext                                       */
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
int pxNachLiefProtGetNext
(
    struct tNACHLIEFPROT* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_NACHLIEFPROT * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_NACHLIEFPROT*10+F_GetNext;
    recordp = (struct C_NACHLIEFPROT *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into NACHLIEFPROT_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into NACHLIEFPROT_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxNachLiefProtEndBrowse                                     */
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
int pxNachLiefProtEndBrowse
(
    int browseid
)
{
    functionnr = F_NACHLIEFPROT*10+F_EndBrowse;

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
/*  FUNCTION: pxNachLiefProtRead                                          */
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

int pxNachLiefProtRead
(
    struct tNACHLIEFPROT* record
#ifdef SKtnlprot
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_NACHLIEFPROT * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_NACHLIEFPROT*10+F_Read;
    recordp = (struct C_NACHLIEFPROT *) record;

#ifdef SKtnlprot
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        NACHLIEFPROT_LISTE
     into NACHLIEFPROT_ZEIGER(recordp)
     from NACHLIEFPROT
     where SKtnlprot;
     break;
    default:
#endif

    EXEC SQL SELECT
        NACHLIEFPROT_LISTE
     into NACHLIEFPROT_ZEIGER(recordp)
     from NACHLIEFPROT
     where PKtnlprot;

#ifdef SKtnlprot
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
/*  FUNCTION: pxNachLiefProtReadLock                                      */
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
int pxNachLiefProtReadLock
(
    struct tNACHLIEFPROT* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_NACHLIEFPROT * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_NACHLIEFPROT*10+F_ReadLock;
    recordp = (struct C_NACHLIEFPROT *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE TNLPROT_U1 CURSOR WITH HOLD FOR
        SELECT
        NACHLIEFPROT_LISTE
    from NACHLIEFPROT
    where PKtnlprot
    FOR UPDATE;
    EXEC SQL OPEN TNLPROT_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH TNLPROT_U1
      into NACHLIEFPROT_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         NACHLIEFPROT_LISTE
    into NACHLIEFPROT_ZEIGER(recordp)
    from NACHLIEFPROT    HOLDLOCK
    where PKtnlprot;
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
/*  FUNCTION: pxNachLiefProtUpdate                                        */
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

int pxNachLiefProtUpdate
(
    struct tNACHLIEFPROT* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_NACHLIEFPROT * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_NACHLIEFPROT*10+F_Update;
    recordp = (struct C_NACHLIEFPROT *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    NACHLIEFPROT
    SET
    NACHLIEFPROT_UPDATE(recordp)
    where current of TNLPROT_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE TNLPROT_U1;
    }
#else

    EXEC SQL UPDATE
    NACHLIEFPROT
    SET
    NACHLIEFPROT_UPDATE(recordp)
    where PKtnlprot;
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
/*  FUNCTION: pxNachLiefProtInsert                                       */
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
int pxNachLiefProtInsert
(
    struct tNACHLIEFPROT* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_NACHLIEFPROT * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_NACHLIEFPROT*10+F_Insert;
    recordp = (struct C_NACHLIEFPROT *) record;

    EXEC SQL INSERT INTO
    NACHLIEFPROT
    (NACHLIEFPROT_LISTE)
    VALUES ( NACHLIEFPROT_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    NACHLIEFPROT
    VALUES ( NACHLIEFPROT_ZEIGER(recordp) );   */


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
/*  FUNCTION: pxNachLiefProtDelete                                        */
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

int pxNachLiefProtDelete
(
    struct tNACHLIEFPROT* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_NACHLIEFPROT * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_NACHLIEFPROT*10+F_Delete;
    recordp = (struct C_NACHLIEFPROT *) record;

    EXEC SQL DELETE FROM
    NACHLIEFPROT
    where PKtnlprot;

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
