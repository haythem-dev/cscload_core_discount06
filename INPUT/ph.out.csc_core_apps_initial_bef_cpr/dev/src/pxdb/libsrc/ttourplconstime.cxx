/*(c)
 ********************* PHARMX Customer Order Entry Server *********************


    Embedded SQL for C application


    FILE: ttourplconstime.c (.sqc)

    Database functions




    FUNCTIONS:

        pxTourPlanConsTimeStartBrowse  declare and open Cursor
        pxTourPlanConsTimeGetNext      get next record
        pxTourPlanConsTimeEndBrowse    close cursor
        pxTourPlanConsTimeRead         get one record
        pxTourPlanConsTimeReadLock     get one record with lock
        pxTourPlanConsTimeInsert       Insert record
        pxTourPlanConsTimeUpdate       Update record
        pxTourPlanConsTimeDelete       Delete record


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
#include <ttourplconstime.h>
#include <keys.h>

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxTourPlanConsTimeStartBrowse                                   */
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
int pxTourPlanConsTimeStartBrowse
(
     struct tTOURPLANCONSTIME* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_TOURPLANCONSTIME * recordp;
#ifdef MCttourplconstime
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_TOURPLANCONSTIME*10+F_StartBrowse;
    recordp = (struct C_TOURPLANCONSTIME *) record;

    if (!(sizeof(struct C_TOURPLANCONSTIME) == sizeof(struct tTOURPLANCONSTIME)))
       return cDBXR_DEFINITION;


#ifdef MCttourplconstime
    strcpy(matchcode,recordp->MCttourplconstime);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        TOURPLANCONSTIME_LISTE
    from TOURPLANCONSTIME
    DWttourplconstime
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        TOURPLANCONSTIME_LISTE
    from TOURPLANCONSTIME
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C2 CURSOR FOR
        SELECT
        TOURPLANCONSTIME_LISTE
    from TOURPLANCONSTIME
    where VERTRIEBSZENTRUMNR      = :recordp->VERTRIEBSZENTRUMNR
    and   DATUMKOMMI              = :recordp->DATUMKOMMI
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
       case cCRSTPLCONSTIME_CTIMEPSTATE:
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
/*  FUNCTION: pxTourPlanConsTimeGetNext                                       */
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
int pxTourPlanConsTimeGetNext
(
    struct tTOURPLANCONSTIME* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_TOURPLANCONSTIME * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_TOURPLANCONSTIME*10+F_GetNext;
    recordp = (struct C_TOURPLANCONSTIME *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into TOURPLANCONSTIME_ZEIGER(recordp);
          break;
       case cCRSTPLCONSTIME_CTIMEPSTATE:
          EXEC SQL FETCH C2
          into TOURPLANCONSTIME_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into TOURPLANCONSTIME_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxTourPlanConsTimeEndBrowse                                     */
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
int pxTourPlanConsTimeEndBrowse
(
    int browseid
)
{
    functionnr = F_TOURPLANCONSTIME*10+F_EndBrowse;

    /* close the cursor */
    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL CLOSE C0;
          break;
       case cCRSTPLCONSTIME_CTIMEPSTATE:
          EXEC SQL CLOSE C2;
          break;
       default:
          EXEC SQL CLOSE C1;
          break;
    }
    return 0;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxTourPlanConsTimeRead                                          */
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

int pxTourPlanConsTimeRead
(
    struct tTOURPLANCONSTIME* record
#ifdef SKttourplconstime
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_TOURPLANCONSTIME * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_TOURPLANCONSTIME*10+F_Read;
    recordp = (struct C_TOURPLANCONSTIME *) record;

#ifdef SKttourplconstime
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        TOURPLANCONSTIME_LISTE
     into TOURPLANCONSTIME_ZEIGER(recordp)
     from TOURPLANCONSTIME
     where SKttourplconstime;
     break;
    default:
#endif

    EXEC SQL SELECT
        TOURPLANCONSTIME_LISTE
     into TOURPLANCONSTIME_ZEIGER(recordp)
     from TOURPLANCONSTIME
     where PKttourplconstime;

#ifdef SKttourplconstime
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
/*  FUNCTION: pxTourPlanConsTimeReadLock                                      */
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
int pxTourPlanConsTimeReadLock
(
    struct tTOURPLANCONSTIME* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_TOURPLANCONSTIME * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_TOURPLANCONSTIME*10+F_ReadLock;
    recordp = (struct C_TOURPLANCONSTIME *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE ttourplconstime_U1 CURSOR WITH HOLD FOR
        SELECT
        TOURPLANCONSTIME_LISTE
    from TOURPLANCONSTIME
    where PKttourplconstime
    FOR UPDATE;
    EXEC SQL OPEN ttourplconstime_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH ttourplconstime_U1
      into TOURPLANCONSTIME_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         TOURPLANCONSTIME_LISTE
    into TOURPLANCONSTIME_ZEIGER(recordp)
    from TOURPLANCONSTIME    HOLDLOCK
    where PKttourplconstime;
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
/*  FUNCTION: pxTourPlanConsTimeUpdate                                        */
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

int pxTourPlanConsTimeUpdate
(
    struct tTOURPLANCONSTIME* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_TOURPLANCONSTIME * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_TOURPLANCONSTIME*10+F_Update;
    recordp = (struct C_TOURPLANCONSTIME *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    TOURPLANCONSTIME
    SET
    TOURPLANCONSTIME_UPDATE(recordp)
    where current of ttourplconstime_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE ttourplconstime_U1;
    }
#else

    EXEC SQL UPDATE
    TOURPLANCONSTIME
    SET
    TOURPLANCONSTIME_UPDATE(recordp)
    where PKttourplconstime;
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
/*  FUNCTION: pxTourPlanConsTimeInsert                                       */
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
int pxTourPlanConsTimeInsert
(
    struct tTOURPLANCONSTIME* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_TOURPLANCONSTIME * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_TOURPLANCONSTIME*10+F_Insert;
    recordp = (struct C_TOURPLANCONSTIME *) record;

    EXEC SQL INSERT INTO
    TOURPLANCONSTIME
    (TOURPLANCONSTIME_LISTE)
    VALUES ( TOURPLANCONSTIME_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    TOURPLANCONSTIME
    VALUES ( TOURPLANCONSTIME_ZEIGER(recordp) );   */


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
/*  FUNCTION: pxTourPlanConsTimeDelete                                        */
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

int pxTourPlanConsTimeDelete
(
    struct tTOURPLANCONSTIME* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_TOURPLANCONSTIME * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_TOURPLANCONSTIME*10+F_Delete;
    recordp = (struct C_TOURPLANCONSTIME *) record;

    EXEC SQL DELETE FROM
    TOURPLANCONSTIME
    where PKttourplconstime;

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
