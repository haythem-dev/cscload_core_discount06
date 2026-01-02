/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

                 (c) Copyright 1994-1995 by NORDAT Network GmbH
                              All rights reserved

    Embedded SQL for C application


    FILE: ttourpt.c (.sqc)

    Database functions




    FUNCTIONS:

        pxTourPlanTagStartBrowse  declare and open Cursor
        pxTourPlanTagGetNext      get next record
        pxTourPlanTagEndBrowse    close cursor
        pxTourPlanTagRead         get one record
        pxTourPlanTagReadLock     get one record with lock
        pxTourPlanTagInsert       Insert record
        pxTourPlanTagUpdate       Update record
        pxTourPlanTagDelete       Delete record

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
#include "ttourpt.h"
#include "keys.h"

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxTourPlanTagStartBrowse                                   */
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
int pxTourPlanTagStartBrowse
(
     struct tTOURPLANTAG* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_TOURPLANTAG * recordp;
#ifdef MCttourpt
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_TOURPLANTAG*10+F_StartBrowse;
    recordp = (struct C_TOURPLANTAG *) record;

    if (!(sizeof(struct C_TOURPLANTAG) == sizeof(struct tTOURPLANTAG)))
       return cDBXR_DEFINITION;


#ifdef MCttourpt
    strcpy(matchcode,recordp->MCttourpt);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        TOURPLANTAG_LISTE
    from TOURPLANTAG
    DWttourpt
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        TOURPLANTAG_LISTE
    from TOURPLANTAG
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C2 CURSOR FOR
        SELECT
        TOURPLANTAG_LISTE
    from TOURPLANTAG
    where VERTRIEBSZENTRUMNR = :recordp->VERTRIEBSZENTRUMNR
    and KUNDENNR = :recordp->KUNDENNR
    and ISTVERBUNDTOUR = :recordp->ISTVERBUNDTOUR
    and DATUMKOMMI     = :recordp->DATUMKOMMI
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

       case cCRSTOURPTG_ISAUXREM         :
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
/*  FUNCTION: pxTourPlanTagGetNext                                       */
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
int pxTourPlanTagGetNext
(
    struct tTOURPLANTAG* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_TOURPLANTAG * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_TOURPLANTAG*10+F_GetNext;
    recordp = (struct C_TOURPLANTAG *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into TOURPLANTAG_ZEIGER(recordp);
          break;

       case cCRSTOURPTG_ISAUXREM         :
          EXEC SQL FETCH C2
          into TOURPLANTAG_ZEIGER(recordp);
          break;

       default:
          EXEC SQL FETCH C1
          into TOURPLANTAG_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxTourPlanTagEndBrowse                                     */
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
int pxTourPlanTagEndBrowse
(
    int browseid
)
{
    functionnr = F_TOURPLANTAG*10+F_EndBrowse;

    /* close the cursor */
    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL CLOSE C0;
          break;

       case cCRSTOURPTG_ISAUXREM         :
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
/*  FUNCTION: pxTourPlanTagRead                                          */
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

int pxTourPlanTagRead
(
    struct tTOURPLANTAG* record
#ifdef SKttourpt
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_TOURPLANTAG * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_TOURPLANTAG*10+F_Read;
    recordp = (struct C_TOURPLANTAG *) record;

#ifdef SKttourpt
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        TOURPLANTAG_LISTE
     into TOURPLANTAG_ZEIGER(recordp)
     from TOURPLANTAG
     where SKttourpt;
     break;
    default:
#endif

    EXEC SQL SELECT
        TOURPLANTAG_LISTE
     into TOURPLANTAG_ZEIGER(recordp)
     from TOURPLANTAG
     where PKttourpt;

#ifdef SKttourpt
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
/*  FUNCTION: pxTourPlanTagReadLock                                      */
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
int pxTourPlanTagReadLock
(
    struct tTOURPLANTAG* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_TOURPLANTAG * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_TOURPLANTAG*10+F_ReadLock;
    recordp = (struct C_TOURPLANTAG *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE TTOURPT_U1 CURSOR WITH HOLD FOR
        SELECT
        TOURPLANTAG_LISTE
    from TOURPLANTAG
    where PKttourpt
    FOR UPDATE;
    EXEC SQL OPEN TTOURPT_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH TTOURPT_U1
      into TOURPLANTAG_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         TOURPLANTAG_LISTE
    into TOURPLANTAG_ZEIGER(recordp)
    from TOURPLANTAG    HOLDLOCK
    where PKttourpt;
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
/*  FUNCTION: pxTourPlanTagUpdate                                        */
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

int pxTourPlanTagUpdate
(
    struct tTOURPLANTAG* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_TOURPLANTAG * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_TOURPLANTAG*10+F_Update;
    recordp = (struct C_TOURPLANTAG *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    TOURPLANTAG
    SET
    TOURPLANTAG_UPDATE(recordp)
    where current of TTOURPT_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE TTOURPT_U1;
    }
#else

    EXEC SQL UPDATE
    TOURPLANTAG
    SET
    TOURPLANTAG_UPDATE(recordp)
    where PKttourpt;
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
/*  FUNCTION: pxTourPlanTagInsert                                       */
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
int pxTourPlanTagInsert
(
    struct tTOURPLANTAG* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_TOURPLANTAG * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_TOURPLANTAG*10+F_Insert;
    recordp = (struct C_TOURPLANTAG *) record;

    EXEC SQL INSERT INTO
    TOURPLANTAG
    (TOURPLANTAG_LISTE)
    VALUES ( TOURPLANTAG_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    TOURPLANTAG
    VALUES ( TOURPLANTAG_ZEIGER(recordp) );   */


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
/*  FUNCTION: pxTourPlanTagDelete                                        */
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

int pxTourPlanTagDelete
(
    struct tTOURPLANTAG* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_TOURPLANTAG * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_TOURPLANTAG*10+F_Delete;
    recordp = (struct C_TOURPLANTAG *) record;

    EXEC SQL DELETE FROM
    TOURPLANTAG
    where PKttourpt;

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
