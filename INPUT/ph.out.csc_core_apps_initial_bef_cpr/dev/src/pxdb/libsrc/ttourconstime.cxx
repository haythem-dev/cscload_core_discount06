/*(c)
 ********************* PHARMX Customer Order Entry Server *********************


    Embedded SQL for C application


    FILE: ttourconstime.c (.sqc)

    Database functions




    FUNCTIONS:

        pxTourConsTimeStartBrowse  declare and open Cursor
        pxTourConsTimeGetNext      get next record
        pxTourConsTimeEndBrowse    close cursor
        pxTourConsTimeRead         get one record
        pxTourConsTimeReadLock     get one record with lock
        pxTourConsTimeInsert       Insert record
        pxTourConsTimeUpdate       Update record
        pxTourConsTimeDelete       Delete record


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
#include <ttourconstime.h>
#include <keys.h>

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxTourConsTimeStartBrowse                                   */
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
int pxTourConsTimeStartBrowse
(
     struct tTOURCONSTIME* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_TOURCONSTIME * recordp;
#ifdef MCttourconstime
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_TOURCONSTIME*10+F_StartBrowse;
    recordp = (struct C_TOURCONSTIME *) record;

    if (!(sizeof(struct C_TOURCONSTIME) == sizeof(struct tTOURCONSTIME)))
       return cDBXR_DEFINITION;


#ifdef MCttourconstime
    strcpy(matchcode,recordp->MCttourconstime);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        TOURCONSTIME_LISTE
    from TOURCONSTIME
    DWttourconstime
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        TOURCONSTIME_LISTE
    from TOURCONSTIME
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif
    EXEC SQL DECLARE C2 CURSOR FOR
        SELECT
        TOURCONSTIME_LISTE
    from TOURCONSTIME
    where FILIALNR      = :recordp->FILIALNR
    and   DATUMKOMMI    = :recordp->DATUMKOMMI
    and   CONSTIME      < :recordp->CONSTIME
    and   PROCESSSTATE  = :recordp->PROCESSSTATE
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
       case cCRSTCONSTIME_CTIMEPSTATE:
          EXEC SQL OPEN C2;
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
/*  FUNCTION: pxTourConsTimeGetNext                                       */
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
int pxTourConsTimeGetNext
(
    struct tTOURCONSTIME* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_TOURCONSTIME * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_TOURCONSTIME*10+F_GetNext;
    recordp = (struct C_TOURCONSTIME *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into TOURCONSTIME_ZEIGER(recordp);
          break;
       case cCRSTCONSTIME_CTIMEPSTATE:
          EXEC SQL FETCH C2
          into TOURCONSTIME_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into TOURCONSTIME_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxTourConsTimeEndBrowse                                     */
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
int pxTourConsTimeEndBrowse
(
    int browseid
)
{
    functionnr = F_TOURCONSTIME*10+F_EndBrowse;

    /* close the cursor */
    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL CLOSE C0;
          break;
       case cCRSTCONSTIME_CTIMEPSTATE:
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
/*  FUNCTION: pxTourConsTimeRead                                          */
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

int pxTourConsTimeRead
(
    struct tTOURCONSTIME* record
#ifdef SKttourconstime
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_TOURCONSTIME * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_TOURCONSTIME*10+F_Read;
    recordp = (struct C_TOURCONSTIME *) record;

#ifdef SKttourconstime
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        TOURCONSTIME_LISTE
     into TOURCONSTIME_ZEIGER(recordp)
     from TOURCONSTIME
     where SKttourconstime;
     break;
    default:
#endif

    EXEC SQL SELECT
        TOURCONSTIME_LISTE
     into TOURCONSTIME_ZEIGER(recordp)
     from TOURCONSTIME
     where PKttourconstime;

#ifdef SKttourconstime
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
/*  FUNCTION: pxTourConsTimeReadLock                                      */
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
int pxTourConsTimeReadLock
(
    struct tTOURCONSTIME* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_TOURCONSTIME * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_TOURCONSTIME*10+F_ReadLock;
    recordp = (struct C_TOURCONSTIME *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE ttourconstime_U1 CURSOR WITH HOLD FOR
        SELECT
        TOURCONSTIME_LISTE
    from TOURCONSTIME
    where PKttourconstime
    FOR UPDATE;
    EXEC SQL OPEN ttourconstime_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH ttourconstime_U1
      into TOURCONSTIME_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         TOURCONSTIME_LISTE
    into TOURCONSTIME_ZEIGER(recordp)
    from TOURCONSTIME    HOLDLOCK
    where PKttourconstime;
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
/*  FUNCTION: pxTourConsTimeUpdate                                        */
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

int pxTourConsTimeUpdate
(
    struct tTOURCONSTIME* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_TOURCONSTIME * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_TOURCONSTIME*10+F_Update;
    recordp = (struct C_TOURCONSTIME *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    TOURCONSTIME
    SET
    TOURCONSTIME_UPDATE(recordp)
    where current of ttourconstime_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE ttourconstime_U1;
    }
#else

    EXEC SQL UPDATE
    TOURCONSTIME
    SET
    TOURCONSTIME_UPDATE(recordp)
    where PKttourconstime;
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
/*  FUNCTION: pxTourConsTimeInsert                                       */
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
int pxTourConsTimeInsert
(
    struct tTOURCONSTIME* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_TOURCONSTIME * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_TOURCONSTIME*10+F_Insert;
    recordp = (struct C_TOURCONSTIME *) record;

    EXEC SQL INSERT INTO
    TOURCONSTIME
    (TOURCONSTIME_LISTE)
    VALUES ( TOURCONSTIME_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    TOURCONSTIME
    VALUES ( TOURCONSTIME_ZEIGER(recordp) );   */


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
/*  FUNCTION: pxTourConsTimeDelete                                        */
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

int pxTourConsTimeDelete
(
    struct tTOURCONSTIME* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_TOURCONSTIME * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_TOURCONSTIME*10+F_Delete;
    recordp = (struct C_TOURCONSTIME *) record;

    EXEC SQL DELETE FROM
    TOURCONSTIME
    where PKttourconstime;

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
