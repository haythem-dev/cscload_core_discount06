/*(c)
 ********************* PHARMX Customer Order Entry Server *********************


    Embedded SQL for C application


    FILE: tkdauftragrechart.c (.sqc)

    Database functions




    FUNCTIONS:

        pxOrderCalcModeStartBrowse  declare and open Cursor
        pxOrderCalcModeGetNext      get next record
        pxOrderCalcModeEndBrowse    close cursor
        pxOrderCalcModeRead         get one record
        pxOrderCalcModeReadLock     get one record with lock
        pxOrderCalcModeInsert       Insert record
        pxOrderCalcModeUpdate       Update record
        pxOrderCalcModeDelete       Delete record


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
#include <tkdauftragrechart.h>
#include <keys.h>

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxOrderCalcModeStartBrowse                                   */
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
int pxOrderCalcModeStartBrowse
(
     struct tKDAUFTRAGRECHART* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGRECHART * recordp;
#ifdef MCtkdauftragrechart
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_KDAUFTRAGRECHART*10+F_StartBrowse;
    recordp = (struct C_KDAUFTRAGRECHART *) record;

    if (!(sizeof(struct C_KDAUFTRAGRECHART) == sizeof(struct tKDAUFTRAGRECHART)))
       return cDBXR_DEFINITION;


#ifdef MCtkdauftragrechart
    strcpy(matchcode,recordp->MCtkdauftragrechart);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        KDAUFTRAGRECHART_LISTE
    from KDAUFTRAGRECHART
    DWtkdauftragrechart
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        KDAUFTRAGRECHART_LISTE
    from KDAUFTRAGRECHART
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
/*  FUNCTION: pxOrderCalcModeGetNext                                       */
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
int pxOrderCalcModeGetNext
(
    struct tKDAUFTRAGRECHART* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGRECHART * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_KDAUFTRAGRECHART*10+F_GetNext;
    recordp = (struct C_KDAUFTRAGRECHART *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into KDAUFTRAGRECHART_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into KDAUFTRAGRECHART_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxOrderCalcModeEndBrowse                                     */
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
int pxOrderCalcModeEndBrowse
(
    int browseid
)
{
    functionnr = F_KDAUFTRAGRECHART*10+F_EndBrowse;

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
/*  FUNCTION: pxOrderCalcModeRead                                          */
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

int pxOrderCalcModeRead
(
    struct tKDAUFTRAGRECHART* record
#ifdef SKtkdauftragrechart
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGRECHART * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRAGRECHART*10+F_Read;
    recordp = (struct C_KDAUFTRAGRECHART *) record;

#ifdef SKtkdauftragrechart
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        KDAUFTRAGRECHART_LISTE
     into KDAUFTRAGRECHART_ZEIGER(recordp)
     from KDAUFTRAGRECHART
     where SKtkdauftragrechart;
     break;
    default:
#endif

    EXEC SQL SELECT
        KDAUFTRAGRECHART_LISTE
     into KDAUFTRAGRECHART_ZEIGER(recordp)
     from KDAUFTRAGRECHART
     where PKtkdauftragrechart;

#ifdef SKtkdauftragrechart
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
/*  FUNCTION: pxOrderCalcModeReadLock                                      */
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
int pxOrderCalcModeReadLock
(
    struct tKDAUFTRAGRECHART* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGRECHART * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRAGRECHART*10+F_ReadLock;
    recordp = (struct C_KDAUFTRAGRECHART *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE tkdauftragrechart_U1 CURSOR WITH HOLD FOR
        SELECT
        KDAUFTRAGRECHART_LISTE
    from KDAUFTRAGRECHART
    where PKtkdauftragrechart
    FOR UPDATE;
    EXEC SQL OPEN tkdauftragrechart_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH tkdauftragrechart_U1
      into KDAUFTRAGRECHART_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         KDAUFTRAGRECHART_LISTE
    into KDAUFTRAGRECHART_ZEIGER(recordp)
    from KDAUFTRAGRECHART    HOLDLOCK
    where PKtkdauftragrechart;
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
/*  FUNCTION: pxOrderCalcModeUpdate                                        */
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

int pxOrderCalcModeUpdate
(
    struct tKDAUFTRAGRECHART* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGRECHART * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRAGRECHART*10+F_Update;
    recordp = (struct C_KDAUFTRAGRECHART *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    KDAUFTRAGRECHART
    SET
    KDAUFTRAGRECHART_UPDATE(recordp)
    where current of tkdauftragrechart_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE tkdauftragrechart_U1;
    }
#else

    EXEC SQL UPDATE
    KDAUFTRAGRECHART
    SET
    KDAUFTRAGRECHART_UPDATE(recordp)
    where PKtkdauftragrechart;
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
/*  FUNCTION: pxOrderCalcModeInsert                                       */
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
int pxOrderCalcModeInsert
(
    struct tKDAUFTRAGRECHART* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGRECHART * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRAGRECHART*10+F_Insert;
    recordp = (struct C_KDAUFTRAGRECHART *) record;

    EXEC SQL INSERT INTO
    KDAUFTRAGRECHART
    (KDAUFTRAGRECHART_LISTE)
    VALUES ( KDAUFTRAGRECHART_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    KDAUFTRAGRECHART
    VALUES ( KDAUFTRAGRECHART_ZEIGER(recordp) );   */


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
/*  FUNCTION: pxOrderCalcModeDelete                                        */
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

int pxOrderCalcModeDelete
(
    struct tKDAUFTRAGRECHART* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGRECHART * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRAGRECHART*10+F_Delete;
    recordp = (struct C_KDAUFTRAGRECHART *) record;

    EXEC SQL DELETE FROM
    KDAUFTRAGRECHART
    where PKtkdauftragrechart;

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
