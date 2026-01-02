/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

                 (c) Copyright 1994-1995 by NORDAT Network GmbH
                              All rights reserved

    Embedded SQL for C application


    FILE: tkunde.c (.sqc)

    Database functions




    FUNCTIONS:

        pxKundeStartBrowse  declare and open Cursor
        pxKundeGetNext      get next record
        pxKundeEndBrowse    close cursor
        pxKundeRead         get one record
        pxKundeReadLock     get one record with lock
        pxKundeInsert       Insert record
        pxKundeUpdate       Update record
        pxKundeDelete       Delete record


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
#include "tkunde.h"
#include "keys.h"

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxKundeStartBrowse                                   */
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
int pxKundeStartBrowse
(
     struct tKUNDE * record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KUNDE * recordp;
#ifdef MCtkunde
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_KUNDE*10+F_StartBrowse;
    recordp = (struct C_KUNDE *) record;

    if (!(sizeof(struct C_KUNDE) == sizeof(struct tKUNDE)))
       return cDBXR_DEFINITION;


#ifdef MCtkunde
    strcpy(matchcode,recordp->MCtkunde);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        KUNDE_LISTE
    from KUNDE
    DWtkunde;

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        KUNDE_LISTE
    from KUNDE;

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
/*  FUNCTION: pxKundeGetNext                                       */
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
int pxKundeGetNext
(
    struct tKUNDE * record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KUNDE * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_KUNDE*10+F_GetNext;
    recordp = (struct C_KUNDE *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into KUNDE_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into KUNDE_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxKundeEndBrowse                                     */
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
int pxKundeEndBrowse
(
    int browseid
)
{
    functionnr = F_KUNDE*10+F_EndBrowse;

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
/*  FUNCTION: pxKundeRead                                          */
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

int pxKundeRead
(
    struct tKUNDE * record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KUNDE * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KUNDE*10+F_Read;
    recordp = (struct C_KUNDE *) record;

    EXEC SQL SELECT
        KUNDE_LISTE
     into KUNDE_ZEIGER(recordp)
     from KUNDE
     where PKtkunde;

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
/*  FUNCTION: pxKundeReadLock                                      */
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
int pxKundeReadLock
(
    struct tKUNDE * record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KUNDE * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KUNDE*10+F_ReadLock;
    recordp = (struct C_KUNDE *) record;

    EXEC SQL DECLARE TKUNDE_U1 CURSOR WITH HOLD FOR
        SELECT
        KUNDE_LISTE
    from KUNDE
    where PKtkunde
    FOR UPDATE;
    EXEC SQL OPEN TKUNDE_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH TKUNDE_U1 INTO KUNDE_ZEIGER(recordp);
    }

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
/*  FUNCTION: pxKundeUpdate                                        */
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

int pxKundeUpdate
(
    struct tKUNDE * record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KUNDE * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KUNDE*10+F_Update;
    recordp = (struct C_KUNDE *) record;


    EXEC SQL UPDATE
    KUNDE
    SET
    KUNDE_UPDATE(recordp)
    where current of TKUNDE_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE TKUNDE_U1;
    }

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
/*  FUNCTION: pxKundeInsert                                       */
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
int pxKundeInsert
(
    struct tKUNDE * record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KUNDE * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KUNDE*10+F_Insert;
    recordp = (struct C_KUNDE *) record;

    EXEC SQL INSERT INTO
    KUNDE
    (KUNDE_LISTE)
    VALUES ( KUNDE_ZEIGER(recordp) );

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
/*  FUNCTION: pxKundeDelete                                          */
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

int pxKundeDelete
(
    struct tKUNDE * record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KUNDE * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KUNDE*10+F_Delete;
    recordp = (struct C_KUNDE *) record;

    EXEC SQL DELETE FROM
    KUNDE
    where PKtkunde;

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
