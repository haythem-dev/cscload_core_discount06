/*(c)
 ********************* PHARMX Customer Order Entry Server *********************


    Embedded SQL for C application


    FILE: tholiday.c (.sqc)

    Database functions




    FUNCTIONS:

        pxHoliDayStartBrowse  declare and open Cursor
        pxHoliDayGetNext      get next record
        pxHoliDayEndBrowse    close cursor
        pxHoliDayRead         get one record
        pxHoliDayReadLock     get one record with lock
        pxHoliDayInsert       Insert record
        pxHoliDayUpdate       Update record
        pxHoliDayDelete       Delete record


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
#include <tholiday.h>
#include <keys.h>

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxHoliDayStartBrowse                                   */
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
int pxHoliDayStartBrowse
(
     struct tFEIERTAG* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_FEIERTAG * recordp;
#ifdef MCtholiday
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_FEIERTAG*10+F_StartBrowse;
    recordp = (struct C_FEIERTAG *) record;

    if (!(sizeof(struct C_FEIERTAG) == sizeof(struct tFEIERTAG)))
       return cDBXR_DEFINITION;


#ifdef MCtholiday
    strcpy(matchcode,recordp->MCtholiday);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        FEIERTAG_LISTE
    from FEIERTAG
    DWtholiday
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        FEIERTAG_LISTE
    from FEIERTAG
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
/*  FUNCTION: pxHoliDayGetNext                                       */
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
int pxHoliDayGetNext
(
    struct tFEIERTAG* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_FEIERTAG * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_FEIERTAG*10+F_GetNext;
    recordp = (struct C_FEIERTAG *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into FEIERTAG_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into FEIERTAG_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxHoliDayEndBrowse                                     */
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
int pxHoliDayEndBrowse
(
    int browseid
)
{
    functionnr = F_FEIERTAG*10+F_EndBrowse;

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
/*  FUNCTION: pxHoliDayRead                                          */
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

int pxHoliDayRead
(
    struct tFEIERTAG* record
#ifdef SKtholiday
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_FEIERTAG * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_FEIERTAG*10+F_Read;
    recordp = (struct C_FEIERTAG *) record;

#ifdef SKtholiday
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        FEIERTAG_LISTE
     into FEIERTAG_ZEIGER(recordp)
     from FEIERTAG
     where SKtholiday;
     break;
    default:
#endif

    EXEC SQL SELECT
        FEIERTAG_LISTE
     into FEIERTAG_ZEIGER(recordp)
     from FEIERTAG
     where PKtholiday;

#ifdef SKtholiday
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
/*  FUNCTION: pxHoliDayReadLock                                      */
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
int pxHoliDayReadLock
(
    struct tFEIERTAG* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_FEIERTAG * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_FEIERTAG*10+F_ReadLock;
    recordp = (struct C_FEIERTAG *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE THOLIDAY_U1 CURSOR WITH HOLD FOR
        SELECT
        FEIERTAG_LISTE
    from FEIERTAG
    where PKtholiday
    FOR UPDATE;
    EXEC SQL OPEN THOLIDAY_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH THOLIDAY_U1
      into FEIERTAG_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         FEIERTAG_LISTE
    into FEIERTAG_ZEIGER(recordp)
    from FEIERTAG    HOLDLOCK
    where PKtholiday;
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
/*  FUNCTION: pxHoliDayUpdate                                        */
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

int pxHoliDayUpdate
(
    struct tFEIERTAG* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_FEIERTAG * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_FEIERTAG*10+F_Update;
    recordp = (struct C_FEIERTAG *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    FEIERTAG
    SET
    FEIERTAG_UPDATE(recordp)
    where current of THOLIDAY_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE THOLIDAY_U1;
    }
#else

    EXEC SQL UPDATE
    FEIERTAG
    SET
    FEIERTAG_UPDATE(recordp)
    where PKtholiday;
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
/*  FUNCTION: pxHoliDayInsert                                       */
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
int pxHoliDayInsert
(
    struct tFEIERTAG* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_FEIERTAG * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_FEIERTAG*10+F_Insert;
    recordp = (struct C_FEIERTAG *) record;

    EXEC SQL INSERT INTO
    FEIERTAG
    (FEIERTAG_LISTE)
    VALUES ( FEIERTAG_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    FEIERTAG
    VALUES ( FEIERTAG_ZEIGER(recordp) );   */


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
/*  FUNCTION: pxHoliDayDelete                                        */
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

int pxHoliDayDelete
(
    struct tFEIERTAG* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_FEIERTAG * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_FEIERTAG*10+F_Delete;
    recordp = (struct C_FEIERTAG *) record;

    EXEC SQL DELETE FROM
    FEIERTAG
    where PKtholiday;

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
