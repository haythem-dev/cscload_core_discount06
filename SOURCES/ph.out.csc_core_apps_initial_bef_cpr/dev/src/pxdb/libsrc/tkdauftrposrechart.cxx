/*(c)
 ********************* PHARMX Customer Order Entry Server *********************


    Embedded SQL for C application


    FILE: tkdauftrposrechart.c (.sqc)

    Database functions




    FUNCTIONS:

        pxOrderPosCalcModeStartBrowse  declare and open Cursor
        pxOrderPosCalcModeGetNext      get next record
        pxOrderPosCalcModeEndBrowse    close cursor
        pxOrderPosCalcModeRead         get one record
        pxOrderPosCalcModeReadLock     get one record with lock
        pxOrderPosCalcModeInsert       Insert record
        pxOrderPosCalcModeUpdate       Update record
        pxOrderPosCalcModeDelete       Delete record


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
#include <tkdauftrposrechart.h>
#include <keys.h>

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxOrderPosCalcModeStartBrowse                                   */
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
int pxOrderPosCalcModeStartBrowse
(
     struct tKDAUFTRPOSRECHART* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRPOSRECHART * recordp;
#ifdef MCtkdauftrposrechart
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_KDAUFTRPOSRECHART*10+F_StartBrowse;
    recordp = (struct C_KDAUFTRPOSRECHART *) record;

    if (!(sizeof(struct C_KDAUFTRPOSRECHART) == sizeof(struct tKDAUFTRPOSRECHART)))
       return cDBXR_DEFINITION;


#ifdef MCtkdauftrposrechart
    strcpy(matchcode,recordp->MCtkdauftrposrechart);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        KDAUFTRPOSRECHART_LISTE
    from KDAUFTRPOSRECHART
    DWtkdauftrposrechart
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        KDAUFTRPOSRECHART_LISTE
    from KDAUFTRPOSRECHART
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
/*  FUNCTION: pxOrderPosCalcModeGetNext                                       */
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
int pxOrderPosCalcModeGetNext
(
    struct tKDAUFTRPOSRECHART* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRPOSRECHART * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_KDAUFTRPOSRECHART*10+F_GetNext;
    recordp = (struct C_KDAUFTRPOSRECHART *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into KDAUFTRPOSRECHART_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into KDAUFTRPOSRECHART_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxOrderPosCalcModeEndBrowse                                     */
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
int pxOrderPosCalcModeEndBrowse
(
    int browseid
)
{
    functionnr = F_KDAUFTRPOSRECHART*10+F_EndBrowse;

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
/*  FUNCTION: pxOrderPosCalcModeRead                                          */
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

int pxOrderPosCalcModeRead
(
    struct tKDAUFTRPOSRECHART* record
#ifdef SKtkdauftrposrechart
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRPOSRECHART * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRPOSRECHART*10+F_Read;
    recordp = (struct C_KDAUFTRPOSRECHART *) record;

#ifdef SKtkdauftrposrechart
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        KDAUFTRPOSRECHART_LISTE
     into KDAUFTRPOSRECHART_ZEIGER(recordp)
     from KDAUFTRPOSRECHART
     where SKtkdauftrposrechart;
     break;
    default:
#endif

    EXEC SQL SELECT
        KDAUFTRPOSRECHART_LISTE
     into KDAUFTRPOSRECHART_ZEIGER(recordp)
     from KDAUFTRPOSRECHART
     where PKtkdauftrposrechart;

#ifdef SKtkdauftrposrechart
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
/*  FUNCTION: pxOrderPosCalcModeReadLock                                      */
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
int pxOrderPosCalcModeReadLock
(
    struct tKDAUFTRPOSRECHART* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRPOSRECHART * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRPOSRECHART*10+F_ReadLock;
    recordp = (struct C_KDAUFTRPOSRECHART *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE tkdauftrposrechart_U1 CURSOR WITH HOLD FOR
        SELECT
        KDAUFTRPOSRECHART_LISTE
    from KDAUFTRPOSRECHART
    where PKtkdauftrposrechart
    FOR UPDATE;
    EXEC SQL OPEN tkdauftrposrechart_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH tkdauftrposrechart_U1
      into KDAUFTRPOSRECHART_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         KDAUFTRPOSRECHART_LISTE
    into KDAUFTRPOSRECHART_ZEIGER(recordp)
    from KDAUFTRPOSRECHART    HOLDLOCK
    where PKtkdauftrposrechart;
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
/*  FUNCTION: pxOrderPosCalcModeUpdate                                        */
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

int pxOrderPosCalcModeUpdate
(
    struct tKDAUFTRPOSRECHART* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRPOSRECHART * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRPOSRECHART*10+F_Update;
    recordp = (struct C_KDAUFTRPOSRECHART *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    KDAUFTRPOSRECHART
    SET
    KDAUFTRPOSRECHART_UPDATE(recordp)
    where current of tkdauftrposrechart_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE tkdauftrposrechart_U1;
    }
#else

    EXEC SQL UPDATE
    KDAUFTRPOSRECHART
    SET
    KDAUFTRPOSRECHART_UPDATE(recordp)
    where PKtkdauftrposrechart;
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
/*  FUNCTION: pxOrderPosCalcModeInsert                                       */
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
int pxOrderPosCalcModeInsert
(
    struct tKDAUFTRPOSRECHART* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRPOSRECHART * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRPOSRECHART*10+F_Insert;
    recordp = (struct C_KDAUFTRPOSRECHART *) record;

    EXEC SQL INSERT INTO
    KDAUFTRPOSRECHART
    (KDAUFTRPOSRECHART_LISTE)
    VALUES ( KDAUFTRPOSRECHART_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    KDAUFTRPOSRECHART
    VALUES ( KDAUFTRPOSRECHART_ZEIGER(recordp) );   */


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
/*  FUNCTION: pxOrderPosCalcModeDelete                                        */
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

int pxOrderPosCalcModeDelete
(
    struct tKDAUFTRPOSRECHART* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRPOSRECHART * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRPOSRECHART*10+F_Delete;
    recordp = (struct C_KDAUFTRPOSRECHART *) record;

    EXEC SQL DELETE FROM
    KDAUFTRPOSRECHART
    where PKtkdauftrposrechart;

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
