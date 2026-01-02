/*(c)
 ********************* PHARMX Customer Order Entry Server *********************


    Embedded SQL for C application


    FILE: ttourplanwoche.c (.sqc)

    Database functions




    FUNCTIONS:

        pxTourPlanWocheStartBrowse  declare and open Cursor
        pxTourPlanWocheGetNext      get next record
        pxTourPlanWocheEndBrowse    close cursor
        pxTourPlanWocheRead         get one record
        pxTourPlanWocheReadLock     get one record with lock
        pxTourPlanWocheInsert       Insert record
        pxTourPlanWocheUpdate       Update record
        pxTourPlanWocheDelete       Delete record


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
#include <ttourplanwoche.h>
#include <keys.h>

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxTourPlanWocheStartBrowse                                   */
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
int pxTourPlanWocheStartBrowse
(
     struct tTOURPLANWOCHE* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_TOURPLANWOCHE * recordp;
#ifdef MCttourplanwoche
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_TOURPLANWOCHE*10+F_StartBrowse;
    recordp = (struct C_TOURPLANWOCHE *) record;

    if (!(sizeof(struct C_TOURPLANWOCHE) == sizeof(struct tTOURPLANWOCHE)))
       return cDBXR_DEFINITION;


#ifdef MCttourplanwoche
    strcpy(matchcode,recordp->MCttourplanwoche);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        TOURPLANWOCHE_LISTE
    from TOURPLANWOCHE
    DWttourplanwoche
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        TOURPLANWOCHE_LISTE
    from TOURPLANWOCHE
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
/*  FUNCTION: pxTourPlanWocheGetNext                                       */
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
int pxTourPlanWocheGetNext
(
    struct tTOURPLANWOCHE* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_TOURPLANWOCHE * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_TOURPLANWOCHE*10+F_GetNext;
    recordp = (struct C_TOURPLANWOCHE *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into TOURPLANWOCHE_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into TOURPLANWOCHE_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxTourPlanWocheEndBrowse                                     */
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
int pxTourPlanWocheEndBrowse
(
    int browseid
)
{
    functionnr = F_TOURPLANWOCHE*10+F_EndBrowse;

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
/*  FUNCTION: pxTourPlanWocheRead                                          */
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

int pxTourPlanWocheRead
(
    struct tTOURPLANWOCHE* record
#ifdef SKttourplanwoche
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_TOURPLANWOCHE * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_TOURPLANWOCHE*10+F_Read;
    recordp = (struct C_TOURPLANWOCHE *) record;

#ifdef SKttourplanwoche
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        TOURPLANWOCHE_LISTE
     into TOURPLANWOCHE_ZEIGER(recordp)
     from TOURPLANWOCHE
     where SKttourplanwoche;
     break;
    default:
#endif

    EXEC SQL SELECT
        TOURPLANWOCHE_LISTE
     into TOURPLANWOCHE_ZEIGER(recordp)
     from TOURPLANWOCHE
     where PKttourplanwoche;

#ifdef SKttourplanwoche
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
/*  FUNCTION: pxTourPlanWocheReadLock                                      */
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
int pxTourPlanWocheReadLock
(
    struct tTOURPLANWOCHE* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_TOURPLANWOCHE * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_TOURPLANWOCHE*10+F_ReadLock;
    recordp = (struct C_TOURPLANWOCHE *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE ttourplanwoche_U1 CURSOR WITH HOLD FOR
        SELECT
        TOURPLANWOCHE_LISTE
    from TOURPLANWOCHE
    where PKttourplanwoche
    FOR UPDATE;
    EXEC SQL OPEN ttourplanwoche_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH ttourplanwoche_U1
      into TOURPLANWOCHE_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         TOURPLANWOCHE_LISTE
    into TOURPLANWOCHE_ZEIGER(recordp)
    from TOURPLANWOCHE    HOLDLOCK
    where PKttourplanwoche;
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
/*  FUNCTION: pxTourPlanWocheUpdate                                        */
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

int pxTourPlanWocheUpdate
(
    struct tTOURPLANWOCHE* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_TOURPLANWOCHE * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_TOURPLANWOCHE*10+F_Update;
    recordp = (struct C_TOURPLANWOCHE *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    TOURPLANWOCHE
    SET
    TOURPLANWOCHE_UPDATE(recordp)
    where current of ttourplanwoche_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE ttourplanwoche_U1;
    }
#else

    EXEC SQL UPDATE
    TOURPLANWOCHE
    SET
    TOURPLANWOCHE_UPDATE(recordp)
    where PKttourplanwoche;
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
/*  FUNCTION: pxTourPlanWocheInsert                                       */
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
int pxTourPlanWocheInsert
(
    struct tTOURPLANWOCHE* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_TOURPLANWOCHE * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_TOURPLANWOCHE*10+F_Insert;
    recordp = (struct C_TOURPLANWOCHE *) record;

    EXEC SQL INSERT INTO
    TOURPLANWOCHE
    (TOURPLANWOCHE_LISTE)
    VALUES ( TOURPLANWOCHE_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    TOURPLANWOCHE
    VALUES ( TOURPLANWOCHE_ZEIGER(recordp) );   */


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
/*  FUNCTION: pxTourPlanWocheDelete                                        */
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

int pxTourPlanWocheDelete
(
    struct tTOURPLANWOCHE* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_TOURPLANWOCHE * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_TOURPLANWOCHE*10+F_Delete;
    recordp = (struct C_TOURPLANWOCHE *) record;

    EXEC SQL DELETE FROM
    TOURPLANWOCHE
    where PKttourplanwoche;

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
