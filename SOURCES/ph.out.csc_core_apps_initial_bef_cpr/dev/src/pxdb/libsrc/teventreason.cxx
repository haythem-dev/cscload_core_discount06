/*(c)
 ********************* PHARMX Customer Order Entry Server *********************


    Embedded SQL for C application


    FILE: teventreason.c (.sqc)

    Database functions




    FUNCTIONS:

        pxEventReasonStartBrowse  declare and open Cursor
        pxEventReasonGetNext      get next record
        pxEventReasonEndBrowse    close cursor
        pxEventReasonRead         get one record
        pxEventReasonReadLock     get one record with lock
        pxEventReasonInsert       Insert record
        pxEventReasonUpdate       Update record
        pxEventReasonDelete       Delete record


REVISION HISTORY

25 Jun 2004 V1.00 REV 00 written by Ysbrand Bouma

*/


#include <stddef.h>         /* standard C run-time header */
#include <stdio.h>          /* standard C run-time header */
#include <pxrecord.h>       /* all record structures */
#include "pxdbfunc.h"
#include "pxdbxx.h"
#include "ndefs.h"
#include <pxenv.h>
#include <teventreason.h>
#include <keys.h>

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxEventReasonStartBrowse                               */
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
int pxEventReasonStartBrowse
(
     struct tEVENTREASONS* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_EVENTREASONS * recordp;
#ifdef MCteventreason
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_EVENTREASONS*10+F_StartBrowse;
    recordp = (struct C_EVENTREASONS *) record;

    if (!(sizeof(struct C_EVENTREASONS) == sizeof(struct tEVENTREASONS)))
       return cDBXR_DEFINITION;


#ifdef MCteventreason
    strcpy(matchcode,recordp->MCteventreason);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        EVENTREASONS_LISTE
    from EVENTREASONS
    DWteventreason
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        EVENTREASONS_LISTE
    from EVENTREASONS
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
/*  FUNCTION: pxEventReasonGetNext                                       */
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
int pxEventReasonGetNext
(
    struct tEVENTREASONS* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_EVENTREASONS * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_EVENTREASONS*10+F_GetNext;
    recordp = (struct C_EVENTREASONS *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into EVENTREASONS_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into EVENTREASONS_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxEventReasonEndBrowse                                     */
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
int pxEventReasonEndBrowse
(
    int browseid
)
{
    functionnr = F_EVENTREASONS*10+F_EndBrowse;

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
/*  FUNCTION: pxEventReasonRead                                          */
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

int pxEventReasonRead
(
    struct tEVENTREASONS* record
#ifdef SKteventreason
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_EVENTREASONS * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_EVENTREASONS*10+F_Read;
    recordp = (struct C_EVENTREASONS *) record;

#ifdef SKteventreason
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        EVENTREASONS_LISTE
     into EVENTREASONS_ZEIGER(recordp)
     from EVENTREASONS
     where SKteventreason;
     break;
    default:
#endif

    EXEC SQL SELECT
        EVENTREASONS_LISTE
     into EVENTREASONS_ZEIGER(recordp)
     from EVENTREASONS
     where PKteventreason;

#ifdef SKteventreason
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
/*  FUNCTION: pxEventReasonReadLock                                      */
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
int pxEventReasonReadLock
(
    struct tEVENTREASONS* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_EVENTREASONS * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_EVENTREASONS*10+F_ReadLock;
    recordp = (struct C_EVENTREASONS *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE tEVENTREASONS_U1 CURSOR WITH HOLD FOR
        SELECT
        EVENTREASONS_LISTE
    from EVENTREASONS
    where PKteventreason
    FOR UPDATE;
    EXEC SQL OPEN tEVENTREASONS_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH tEVENTREASONS_U1
      into EVENTREASONS_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         EVENTREASONS_LISTE
    into EVENTREASONS_ZEIGER(recordp)
    from EVENTREASONS    HOLDLOCK
    where PKteventreason;
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
/*  FUNCTION: pxEventReasonUpdate                                        */
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

int pxEventReasonUpdate
(
    struct tEVENTREASONS* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_EVENTREASONS * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_EVENTREASONS*10+F_Update;
    recordp = (struct C_EVENTREASONS *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    EVENTREASONS
    SET
    EVENTREASONS_UPDATE(recordp)
    where current of tEVENTREASONS_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE tEVENTREASONS_U1;
    }
#else

    EXEC SQL UPDATE
    EVENTREASONS
    SET
    EVENTREASONS_UPDATE(recordp)
    where PKteventreason;
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
/*  FUNCTION: pxEventReasonInsert                                       */
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
int pxEventReasonInsert
(
    struct tEVENTREASONS* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_EVENTREASONS * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_EVENTREASONS*10+F_Insert;
    recordp = (struct C_EVENTREASONS *) record;

    EXEC SQL INSERT INTO
    EVENTREASONS
    (EVENTREASONS_LISTE)
    VALUES ( EVENTREASONS_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    EVENTREASONS
    VALUES ( EVENTREASONS_ZEIGER(recordp) );   */


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
/*  FUNCTION: pxEventReasonDelete                                        */
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

int pxEventReasonDelete
(
    struct tEVENTREASONS* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_EVENTREASONS * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_EVENTREASONS*10+F_Delete;
    recordp = (struct C_EVENTREASONS *) record;

    EXEC SQL DELETE FROM
    EVENTREASONS
    where PKteventreason;

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
