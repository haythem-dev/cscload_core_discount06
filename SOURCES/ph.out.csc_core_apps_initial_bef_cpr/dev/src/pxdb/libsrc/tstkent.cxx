/*(c)
 ********************* PHARMX Customer Order Entry Server *********************


    Embedded SQL for C application


    FILE: tstkent.c (.sqc)

    Database functions




    FUNCTIONS:

        pxStockEntryStartBrowse  declare and open Cursor
        pxStockEntryGetNext      get next record
        pxStockEntryEndBrowse    close cursor
        pxStockEntryRead         get one record
        pxStockEntryReadLock     get one record with lock
        pxStockEntryInsert       Insert record
        pxStockEntryUpdate       Update record
        pxStockEntryDelete       Delete record


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
#include <tstkent.h>
#include <keys.h>

/* Global variables */
extern int  functionnr;

#define UNUSED(x) (void)(x)

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxStockEntryStartBrowse                                   */
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
int pxStockEntryStartBrowse
(
     struct tSTOCKENTRY* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
#ifdef MCtstkent
    struct C_STOCKENTRY * recordp;
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_STOCKENTRY*10+F_StartBrowse;
#ifdef MCtstkent
    recordp = (struct C_STOCKENTRY *) record;
#else
    UNUSED(record);
#endif

    if (!(sizeof(struct C_STOCKENTRY) == sizeof(struct tSTOCKENTRY)))
       return cDBXR_DEFINITION;


#ifdef MCtstkent
    strcpy(matchcode,recordp->MCtstkent);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        STOCKENTRY_LISTE
    from STOCKENTRY
    DWtstkent
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        STOCKENTRY_LISTE
    from STOCKENTRY
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
/*  FUNCTION: pxStockEntryGetNext                                       */
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
int pxStockEntryGetNext
(
    struct tSTOCKENTRY* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_STOCKENTRY * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_STOCKENTRY*10+F_GetNext;
    recordp = (struct C_STOCKENTRY *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into STOCKENTRY_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into STOCKENTRY_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxStockEntryEndBrowse                                     */
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
int pxStockEntryEndBrowse
(
    int browseid
)
{
    functionnr = F_STOCKENTRY*10+F_EndBrowse;

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
/*  FUNCTION: pxStockEntryRead                                          */
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

int pxStockEntryRead
(
    struct tSTOCKENTRY* record
#ifdef SKtstkent
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_STOCKENTRY * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_STOCKENTRY*10+F_Read;
    recordp = (struct C_STOCKENTRY *) record;

#ifdef SKtstkent
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        STOCKENTRY_LISTE
     into STOCKENTRY_ZEIGER(recordp)
     from STOCKENTRY
     where SKtstkent;
     break;
    default:
#endif

    EXEC SQL SELECT
        STOCKENTRY_LISTE
     into STOCKENTRY_ZEIGER(recordp)
     from STOCKENTRY
     where PKtstkent;

#ifdef SKtstkent
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
/*  FUNCTION: pxStockEntryReadLock                                      */
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
int pxStockEntryReadLock
(
    struct tSTOCKENTRY* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_STOCKENTRY * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_STOCKENTRY*10+F_ReadLock;
    recordp = (struct C_STOCKENTRY *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE TSTKENT_U1 CURSOR WITH HOLD FOR
        SELECT
        STOCKENTRY_LISTE
    from STOCKENTRY
    where PKtstkent
    FOR UPDATE;
    EXEC SQL OPEN TSTKENT_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH TSTKENT_U1
      into STOCKENTRY_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         STOCKENTRY_LISTE
    into STOCKENTRY_ZEIGER(recordp)
    from STOCKENTRY    HOLDLOCK
    where PKtstkent;
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
/*  FUNCTION: pxStockEntryUpdate                                        */
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

int pxStockEntryUpdate
(
    struct tSTOCKENTRY* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_STOCKENTRY * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_STOCKENTRY*10+F_Update;
    recordp = (struct C_STOCKENTRY *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    STOCKENTRY
    SET
    STOCKENTRY_UPDATE(recordp)
    where current of TSTKENT_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE TSTKENT_U1;
    }
#else

    EXEC SQL UPDATE
    STOCKENTRY
    SET
    STOCKENTRY_UPDATE(recordp)
    where PKtstkent;
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
/*  FUNCTION: pxStockEntryInsert                                       */
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
int pxStockEntryInsert
(
    struct tSTOCKENTRY* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_STOCKENTRY * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_STOCKENTRY*10+F_Insert;
    recordp = (struct C_STOCKENTRY *) record;

    EXEC SQL INSERT INTO
    STOCKENTRY
    (STOCKENTRY_LISTE)
    VALUES ( STOCKENTRY_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    STOCKENTRY
    VALUES ( STOCKENTRY_ZEIGER(recordp) );   */


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
/*  FUNCTION: pxStockEntryDelete                                        */
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

int pxStockEntryDelete
(
    struct tSTOCKENTRY* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_STOCKENTRY * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_STOCKENTRY*10+F_Delete;
    recordp = (struct C_STOCKENTRY *) record;

    EXEC SQL DELETE FROM
    STOCKENTRY
    where PKtstkent;

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
