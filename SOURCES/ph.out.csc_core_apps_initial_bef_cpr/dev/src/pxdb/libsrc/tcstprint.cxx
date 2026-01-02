/*(c)
 ********************* PHARMX Customer Order Entry Server *********************


    Embedded SQL for C application


    FILE: tcstprint.c (.sqc)

    Database functions




    FUNCTIONS:

        pxCstPrintStartBrowse  declare and open Cursor
        pxCstPrintGetNext      get next record
        pxCstPrintEndBrowse    close cursor
        pxCstPrintRead         get one record
        pxCstPrintReadLock     get one record with lock
        pxCstPrintInsert       Insert record
        pxCstPrintUpdate       Update record
        pxCstPrintDelete       Delete record


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
#include <tcstprint.h>
#include <keys.h>

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxCstPrintStartBrowse                                   */
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
int pxCstPrintStartBrowse
(
     struct tCSTPRINT* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CSTPRINT * recordp;
#ifdef MCtcstprint
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_CSTPRINT*10+F_StartBrowse;
    recordp = (struct C_CSTPRINT *) record;

    if (!(sizeof(struct C_CSTPRINT) == sizeof(struct tCSTPRINT)))
       return cDBXR_DEFINITION;


#ifdef MCtcstprint
    strcpy(matchcode,recordp->MCtcstprint);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        CSTPRINT_LISTE
    from CSTPRINT
    DWtcstprint
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        CSTPRINT_LISTE
    from CSTPRINT
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
/*  FUNCTION: pxCstPrintGetNext                                       */
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
int pxCstPrintGetNext
(
    struct tCSTPRINT* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CSTPRINT * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_CSTPRINT*10+F_GetNext;
    recordp = (struct C_CSTPRINT *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into CSTPRINT_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into CSTPRINT_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxCstPrintEndBrowse                                     */
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
int pxCstPrintEndBrowse
(
    int browseid
)
{
    functionnr = F_CSTPRINT*10+F_EndBrowse;

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
/*  FUNCTION: pxCstPrintRead                                          */
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

int pxCstPrintRead
(
    struct tCSTPRINT* record
#ifdef SKtcstprint
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CSTPRINT * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_CSTPRINT*10+F_Read;
    recordp = (struct C_CSTPRINT *) record;

#ifdef SKtcstprint
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        CSTPRINT_LISTE
     into CSTPRINT_ZEIGER(recordp)
     from CSTPRINT
     where SKtcstprint;
     break;
    default:
#endif

    EXEC SQL SELECT
        CSTPRINT_LISTE
     into CSTPRINT_ZEIGER(recordp)
     from CSTPRINT
     where PKtcstprint;

#ifdef SKtcstprint
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
/*  FUNCTION: pxCstPrintReadLock                                      */
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
int pxCstPrintReadLock
(
    struct tCSTPRINT* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CSTPRINT * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_CSTPRINT*10+F_ReadLock;
    recordp = (struct C_CSTPRINT *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE tcstprint_U1 CURSOR WITH HOLD FOR
        SELECT
        CSTPRINT_LISTE
    from CSTPRINT
    where PKtcstprint
    FOR UPDATE;
    EXEC SQL OPEN tcstprint_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH tcstprint_U1
      into CSTPRINT_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         CSTPRINT_LISTE
    into CSTPRINT_ZEIGER(recordp)
    from CSTPRINT    HOLDLOCK
    where PKtcstprint;
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
/*  FUNCTION: pxCstPrintUpdate                                        */
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

int pxCstPrintUpdate
(
    struct tCSTPRINT* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CSTPRINT * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_CSTPRINT*10+F_Update;
    recordp = (struct C_CSTPRINT *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    CSTPRINT
    SET
    CSTPRINT_UPDATE(recordp)
    where current of tcstprint_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE tcstprint_U1;
    }
#else

    EXEC SQL UPDATE
    CSTPRINT
    SET
    CSTPRINT_UPDATE(recordp)
    where PKtcstprint;
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
/*  FUNCTION: pxCstPrintInsert                                       */
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
int pxCstPrintInsert
(
    struct tCSTPRINT* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CSTPRINT * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_CSTPRINT*10+F_Insert;
    recordp = (struct C_CSTPRINT *) record;

    EXEC SQL INSERT INTO
    CSTPRINT
    (CSTPRINT_LISTE)
    VALUES ( CSTPRINT_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    CSTPRINT
    VALUES ( CSTPRINT_ZEIGER(recordp) );   */


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
/*  FUNCTION: pxCstPrintDelete                                        */
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

int pxCstPrintDelete
(
    struct tCSTPRINT* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CSTPRINT * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_CSTPRINT*10+F_Delete;
    recordp = (struct C_CSTPRINT *) record;

    EXEC SQL DELETE FROM
    CSTPRINT
    where PKtcstprint;

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
