/*(c)
 ********************* PHARMX Customer Order Entry Server *********************


    Embedded SQL for C application


    FILE: ttourpltwoche.c (.sqc)

    Database functions




    FUNCTIONS:

        pxTourPlanTagWocheStartBrowse  declare and open Cursor
        pxTourPlanTagWocheGetNext      get next record
        pxTourPlanTagWocheEndBrowse    close cursor
        pxTourPlanTagWocheRead         get one record
        pxTourPlanTagWocheReadLock     get one record with lock
        pxTourPlanTagWocheInsert       Insert record
        pxTourPlanTagWocheUpdate       Update record
        pxTourPlanTagWocheDelete       Delete record


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
#include <ttourpltwoche.h>
#include <keys.h>

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxTourPlanTagWocheStartBrowse                                   */
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
int pxTourPlanTagWocheStartBrowse
(
     struct tTOURPLANTAGWOCHE* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_TOURPLANTAGWOCHE * recordp;
#ifdef MCttourpltwoche
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_TOURPLANTAGWOCHE*10+F_StartBrowse;
    recordp = (struct C_TOURPLANTAGWOCHE *) record;

    if (!(sizeof(struct C_TOURPLANTAGWOCHE) == sizeof(struct tTOURPLANTAGWOCHE)))
       return cDBXR_DEFINITION;


#ifdef MCttourpltwoche
    strcpy(matchcode,recordp->MCttourpltwoche);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        TOURPLANTAGWOCHE_LISTE
    from TOURPLANTAGWOCHE
    DWttourpltwoche
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        TOURPLANTAGWOCHE_LISTE
    from TOURPLANTAGWOCHE
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif
    EXEC SQL DECLARE C2 CURSOR FOR
        SELECT
        TOURPLANTAGWOCHE_LISTE
    from TOURPLANTAGWOCHE
    where VERTRIEBSZENTRUMNR   = :recordp->VERTRIEBSZENTRUMNR
    and   KUNDENNR             = :recordp->KUNDENNR
    and   WEEKDAY              = :recordp->WEEKDAY
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif
    EXEC SQL DECLARE C3 CURSOR FOR
        SELECT
        TOURPLANTAGWOCHE_LISTE
    from TOURPLANTAGWOCHE
    where VERTRIEBSZENTRUMNR   = :recordp->VERTRIEBSZENTRUMNR
    and   KUNDENNR             = :recordp->KUNDENNR
    and   ISTVERBUNDTOUR       = :recordp->ISTVERBUNDTOUR
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
       case cCRSTPLTWOCHE_DAYTYPE:
          EXEC SQL OPEN C2;
          break;
       case cCRSTPLTWOCHE_IBT:
          EXEC SQL OPEN C3;
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
/*  FUNCTION: pxTourPlanTagWocheGetNext                                      */
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
int pxTourPlanTagWocheGetNext
(
    struct tTOURPLANTAGWOCHE* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_TOURPLANTAGWOCHE * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_TOURPLANTAGWOCHE*10+F_GetNext;
    recordp = (struct C_TOURPLANTAGWOCHE *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into TOURPLANTAGWOCHE_ZEIGER(recordp);
          break;
       case cCRSTPLTWOCHE_DAYTYPE:
          EXEC SQL FETCH C2
          into TOURPLANTAGWOCHE_ZEIGER(recordp);
          break;
       case cCRSTPLTWOCHE_IBT:
          EXEC SQL FETCH C3
          into TOURPLANTAGWOCHE_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into TOURPLANTAGWOCHE_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxTourPlanTagWocheEndBrowse                            */
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
int pxTourPlanTagWocheEndBrowse
(
    int browseid
)
{
    functionnr = F_TOURPLANTAGWOCHE*10+F_EndBrowse;

    /* close the cursor */
    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL CLOSE C0;
          break;
       case cCRSTPLTWOCHE_DAYTYPE:
          EXEC SQL CLOSE C2;
          break;
       case cCRSTPLTWOCHE_IBT:
          EXEC SQL CLOSE C3;
          break;
       default:
          EXEC SQL CLOSE C1;
          break;
    }
    return 0;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxTourPlanTagWocheRead                                          */
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

int pxTourPlanTagWocheRead
(
    struct tTOURPLANTAGWOCHE* record
#ifdef SKttourpltwoche
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_TOURPLANTAGWOCHE * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_TOURPLANTAGWOCHE*10+F_Read;
    recordp = (struct C_TOURPLANTAGWOCHE *) record;

#ifdef SKttourpltwoche
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        TOURPLANTAGWOCHE_LISTE
     into TOURPLANTAGWOCHE_ZEIGER(recordp)
     from TOURPLANTAGWOCHE
     where SKttourpltwoche;
     break;
    default:
#endif

    EXEC SQL SELECT
        TOURPLANTAGWOCHE_LISTE
     into TOURPLANTAGWOCHE_ZEIGER(recordp)
     from TOURPLANTAGWOCHE
     where PKttourpltwoche;

#ifdef SKttourpltwoche
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
/*  FUNCTION: pxTourPlanTagWocheReadLock                                      */
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
int pxTourPlanTagWocheReadLock
(
    struct tTOURPLANTAGWOCHE* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_TOURPLANTAGWOCHE * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_TOURPLANTAGWOCHE*10+F_ReadLock;
    recordp = (struct C_TOURPLANTAGWOCHE *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE ttourpltwoche_U1 CURSOR WITH HOLD FOR
        SELECT
        TOURPLANTAGWOCHE_LISTE
    from TOURPLANTAGWOCHE
    where PKttourpltwoche
    FOR UPDATE;
    EXEC SQL OPEN ttourpltwoche_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH ttourpltwoche_U1
      into TOURPLANTAGWOCHE_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         TOURPLANTAGWOCHE_LISTE
    into TOURPLANTAGWOCHE_ZEIGER(recordp)
    from TOURPLANTAGWOCHE    HOLDLOCK
    where PKttourpltwoche;
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
/*  FUNCTION: pxTourPlanTagWocheUpdate                                        */
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

int pxTourPlanTagWocheUpdate
(
    struct tTOURPLANTAGWOCHE* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_TOURPLANTAGWOCHE * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_TOURPLANTAGWOCHE*10+F_Update;
    recordp = (struct C_TOURPLANTAGWOCHE *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    TOURPLANTAGWOCHE
    SET
    TOURPLANTAGWOCHE_UPDATE(recordp)
    where current of ttourpltwoche_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE ttourpltwoche_U1;
    }
#else

    EXEC SQL UPDATE
    TOURPLANTAGWOCHE
    SET
    TOURPLANTAGWOCHE_UPDATE(recordp)
    where PKttourpltwoche;
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
/*  FUNCTION: pxTourPlanTagWocheInsert                                       */
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
int pxTourPlanTagWocheInsert
(
    struct tTOURPLANTAGWOCHE* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_TOURPLANTAGWOCHE * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_TOURPLANTAGWOCHE*10+F_Insert;
    recordp = (struct C_TOURPLANTAGWOCHE *) record;

    EXEC SQL INSERT INTO
    TOURPLANTAGWOCHE
    (TOURPLANTAGWOCHE_LISTE)
    VALUES ( TOURPLANTAGWOCHE_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    TOURPLANTAGWOCHE
    VALUES ( TOURPLANTAGWOCHE_ZEIGER(recordp) );   */


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
/*  FUNCTION: pxTourPlanTagWocheDelete                                        */
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

int pxTourPlanTagWocheDelete
(
    struct tTOURPLANTAGWOCHE* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_TOURPLANTAGWOCHE * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_TOURPLANTAGWOCHE*10+F_Delete;
    recordp = (struct C_TOURPLANTAGWOCHE *) record;

    EXEC SQL DELETE FROM
    TOURPLANTAGWOCHE
    where PKttourpltwoche;

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
