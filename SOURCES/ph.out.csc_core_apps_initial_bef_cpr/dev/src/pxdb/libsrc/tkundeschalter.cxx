/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

                 (c) Copyright 1994-1995 by NORDAT Network GmbH
                              All rights reserved

    Embedded SQL for C application


    FILE: tkundkz.c (.sqc)

    Database functions




    FUNCTIONS:

        pxKundeSchalterStartBrowse  declare and open Cursor
        pxKundeSchalterGetNext      get next record
        pxKundeSchalterEndBrowse    close cursor
        pxKundeSchalterRead         get one record
        pxKundeSchalterReadLock     get one record with lock
        pxKundeSchalterInsert       Insert record
        pxKundeSchalterUpdate       Update record
        pxKundeSchalterDelete       Delete record


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
#include "tkundeschalter.h"
#include "keys.h"

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxKundeSchalterStartBrowse                             */
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
int pxKundeSchalterStartBrowse
(
     struct tKUNDESCHALTER * record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KUNDESCHALTER * rp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_KUNDESCHALTER*10+F_StartBrowse;
    rp = (struct C_KUNDESCHALTER *) record;

    if (!(sizeof(struct C_KUNDESCHALTER) == sizeof(struct tKUNDESCHALTER)))
       return cDBXR_DEFINITION;

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        KUNDESCHALTER_LISTE
    from KUNDESCHALTER
    DWtkundkz;

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        KUNDESCHALTER_LISTE
    from KUNDESCHALTER;

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
/*  FUNCTION: pxKundeSchalterGetNext                                 */
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
int pxKundeSchalterGetNext
(
    struct tKUNDESCHALTER * record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KUNDESCHALTER * rp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_KUNDESCHALTER*10+F_GetNext;
    rp = (struct C_KUNDESCHALTER *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into KUNDESCHALTER_ZEIGER(rp);
          break;
       default:
          EXEC SQL FETCH C1
          into KUNDESCHALTER_ZEIGER(rp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxKundeSchalterEndBrowse                               */
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
int pxKundeSchalterEndBrowse
(
    int browseid
)
{
    functionnr = F_KUNDESCHALTER*10+F_EndBrowse;

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
/*  FUNCTION: pxKundeSchalterRead                                    */
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

int pxKundeSchalterRead
(
    struct tKUNDESCHALTER * record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KUNDESCHALTER * rp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KUNDESCHALTER*10+F_Read;
    rp = (struct C_KUNDESCHALTER *) record;

    EXEC SQL SELECT
        KUNDESCHALTER_LISTE
     into KUNDESCHALTER_ZEIGER(rp)
     from KUNDESCHALTER
     where PKtkundkz;

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
/*  FUNCTION: pxKundeSchalterReadLock                                */
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
int pxKundeSchalterReadLock
(
    struct tKUNDESCHALTER * record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KUNDESCHALTER * rp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KUNDESCHALTER*10+F_ReadLock;
    rp = (struct C_KUNDESCHALTER *) record;

    EXEC SQL DECLARE TKUNDKZ_U1 CURSOR WITH HOLD FOR
        SELECT
        KUNDESCHALTER_LISTE
    from KUNDESCHALTER
    where PKtkundkz
    FOR UPDATE;
    EXEC SQL OPEN TKUNDKZ_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH TKUNDKZ_U1
      into KUNDESCHALTER_ZEIGER(rp);
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
/*  FUNCTION: pxKundeSchalterUpdate                                  */
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

int pxKundeSchalterUpdate
(
    struct tKUNDESCHALTER * record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KUNDESCHALTER * rp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KUNDESCHALTER*10+F_Update;
    rp = (struct C_KUNDESCHALTER *) record;

    EXEC SQL UPDATE
    KUNDESCHALTER
    SET
    KUNDESCHALTER_UPDATE(rp)
    where current of TKUNDKZ_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE TKUNDKZ_U1;
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
/*  FUNCTION: pxKundeSchalterInsert                                  */
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
int pxKundeSchalterInsert
(
    struct tKUNDESCHALTER * record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KUNDESCHALTER * rp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KUNDESCHALTER*10+F_Insert;
    rp = (struct C_KUNDESCHALTER *) record;

    EXEC SQL INSERT INTO
    KUNDESCHALTER
    (KUNDESCHALTER_LISTE)
    VALUES ( KUNDESCHALTER_ZEIGER(rp) );

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
/*  FUNCTION: pxKundeSchalterDelete                                  */
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

int pxKundeSchalterDelete
(
    struct tKUNDESCHALTER * record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KUNDESCHALTER * rp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KUNDESCHALTER*10+F_Delete;
    rp = (struct C_KUNDESCHALTER *) record;

    EXEC SQL DELETE FROM
    KUNDESCHALTER
    where PKtkundkz;

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
