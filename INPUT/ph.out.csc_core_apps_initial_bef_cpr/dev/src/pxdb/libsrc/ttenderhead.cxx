/*(c)
 ********************* PHARMX Customer Order Entry Server *********************


    Embedded SQL for C application


    FILE: ttenderhead.c (.sqc)

    Database functions




    FUNCTIONS:

        pxTenderHeadStartBrowse  declare and open Cursor
        pxTenderHeadGetNext      get next record
        pxTenderHeadEndBrowse    close cursor
        pxTenderHeadRead         get one record
        pxTenderHeadReadLock     get one record with lock
        pxTenderHeadInsert       Insert record
        pxTenderHeadUpdate       Update record
        pxTenderHeadDelete       Delete record


REVISION HISTORY

25 Jun 2004 V1.00 REV 00 written by Ysbrand Bouma

*/


#include <stddef.h>         /* standard C run-time header */
#include <stdio.h>          /* standard C run-time header */
#include <string.h>
#include <pxrecord.h>       /* all record structures */
#include "pxdbxx.h"
#include "pxdbfunc.h"
#include <ndefs.h>
#include <pxenv.h>
#include <ttenderhead.h>
#include <keys.h>

/* Global variables */
extern int  functionnr;

#define UNUSED(x) (void)(x)

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxTenderHeadStartBrowse                                */
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
int pxTenderHeadStartBrowse
(
     struct tTENDERHEAD* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    EXEC SQL END   DECLARE SECTION;

    UNUSED(record);

    functionnr = F_TENDERHEAD*10+F_StartBrowse;

    if (!(sizeof(struct C_TENDERHEAD) == sizeof(struct tTENDERHEAD)))
       return cDBXR_DEFINITION;

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        TENDERHEAD_LISTE
    from TENDERHEAD;

    switch (browseid)
    {
       case cCRS_NOWHERE:
       default:
          EXEC SQL OPEN C0;
          break;
    }
    if (SQLCODE == 0)        return 0;
    if (SQLCODE == 100)      return cDBXR_NOTFOUND;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxTenderHeadGetNext                                    */
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
int pxTenderHeadGetNext
(
    struct tTENDERHEAD* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_TENDERHEAD * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_TENDERHEAD*10+F_GetNext;
    recordp = (struct C_TENDERHEAD *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
       default:
          EXEC SQL FETCH C0
          into TENDERHEAD_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxTenderHeadEndBrowse                                  */
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
int pxTenderHeadEndBrowse
(
    int browseid
)
{
    functionnr = F_TENDERHEAD*10+F_EndBrowse;

    /* close the cursor */
    switch (browseid)
    {
       case cCRS_NOWHERE:
       default:
          EXEC SQL CLOSE C0;
          break;
    }
    return 0;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxTenderHeadRead                                       */
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

int pxTenderHeadRead
(
    struct tTENDERHEAD* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_TENDERHEAD * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_TENDERHEAD*10+F_Read;
    recordp = (struct C_TENDERHEAD *) record;

    EXEC SQL SELECT
        TENDERHEAD_LISTE
     into TENDERHEAD_ZEIGER(recordp)
     from TENDERHEAD
     where TENDERNO = :recordp->TENDERNO;

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
/*  FUNCTION: pxTenderHeadReadLock                                   */
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
int pxTenderHeadReadLock
(
    struct tTENDERHEAD* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_TENDERHEAD * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_TENDERHEAD*10+F_ReadLock;
    recordp = (struct C_TENDERHEAD *) record;

    EXEC SQL DECLARE ttenderhead_U1 CURSOR WITH HOLD FOR
        SELECT
        TENDERHEAD_LISTE
    from TENDERHEAD
    where TENDERNO = :recordp->TENDERNO
    FOR UPDATE;
    EXEC SQL OPEN ttenderhead_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH ttenderhead_U1
      into TENDERHEAD_ZEIGER(recordp);
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
/*  FUNCTION: pxTenderHeadUpdate                                     */
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

int pxTenderHeadUpdate
(
    struct tTENDERHEAD* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_TENDERHEAD * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_TENDERHEAD*10+F_Update;
    recordp = (struct C_TENDERHEAD *) record;


    EXEC SQL UPDATE
    TENDERHEAD
    SET
    TENDERHEAD_UPDATE(recordp)
    where current of ttenderhead_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE ttenderhead_U1;
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
/*  FUNCTION: pxTenderHeadInsert                                     */
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
int pxTenderHeadInsert
(
    struct tTENDERHEAD* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_TENDERHEAD * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_TENDERHEAD*10+F_Insert;
    recordp = (struct C_TENDERHEAD *) record;

    EXEC SQL INSERT INTO
    TENDERHEAD
    (TENDERHEAD_LISTE)
    VALUES ( TENDERHEAD_ZEIGER(recordp) );

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
/*  FUNCTION: pxTenderHeadDelete                                     */
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

int pxTenderHeadDelete
(
    struct tTENDERHEAD* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_TENDERHEAD * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_TENDERHEAD*10+F_Delete;
    recordp = (struct C_TENDERHEAD *) record;

    EXEC SQL DELETE FROM
    TENDERHEAD
    where TENDERNO = :recordp->TENDERNO;

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
