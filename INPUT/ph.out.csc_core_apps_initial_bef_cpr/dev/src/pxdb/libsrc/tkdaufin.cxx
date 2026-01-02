/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

                 (c) Copyright 1994-1995 by NORDAT Network GmbH
                              All rights reserved

    Embedded SQL for C application


    FILE: tkdaufin.c (.sqc)

    Database functions




    FUNCTIONS:

        pxCustOrderInfoStartBrowse  declare and open Cursor
        pxCustOrderInfoGetNext      get next record
        pxCustOrderInfoEndBrowse    close cursor
        pxCustOrderInfoRead         get one record
        pxCustOrderInfoReadLock     get one record with lock
        pxCustOrderInfoInsert       Insert record
        pxCustOrderInfoUpdate       Update record
        pxCustOrderInfoDelete       Delete record


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
#include <tkdaufin.h>
#include <keys.h>

/* Global variables */
extern int  functionnr;

#define UNUSED(x) (void)(x)

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxCustOrderInfoStartBrowse                                   */
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
int pxCustOrderInfoStartBrowse
(
     struct tKDAUFTRAGINFO* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
#ifdef MCtkdaufin
    struct C_KDAUFTRAGINFO * recordp;
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_KDAUFTRAGINFO*10+F_StartBrowse;
#ifdef MCtkdaufin
    recordp = (struct C_KDAUFTRAGINFO *) record;
#else
    UNUSED(record);
#endif

    if (!(sizeof(struct C_KDAUFTRAGINFO) == sizeof(struct tKDAUFTRAGINFO)))
       return cDBXR_DEFINITION;


#ifdef MCtkdaufin
    strcpy(matchcode,recordp->MCtkdaufin);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        KDAUFTRAGINFO_LISTE
    from KDAUFTRAGINFO
    DWtkdaufin
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        KDAUFTRAGINFO_LISTE
    from KDAUFTRAGINFO
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
/*  FUNCTION: pxCustOrderInfoGetNext                                       */
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
int pxCustOrderInfoGetNext
(
    struct tKDAUFTRAGINFO* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGINFO * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_KDAUFTRAGINFO*10+F_GetNext;
    recordp = (struct C_KDAUFTRAGINFO *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into KDAUFTRAGINFO_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into KDAUFTRAGINFO_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxCustOrderInfoEndBrowse                                     */
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
int pxCustOrderInfoEndBrowse
(
    int browseid
)
{
    functionnr = F_KDAUFTRAGINFO*10+F_EndBrowse;

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
/*  FUNCTION: pxCustOrderInfoRead                                          */
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

int pxCustOrderInfoRead
(
    struct tKDAUFTRAGINFO* record
#ifdef SKtkdaufin
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGINFO * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRAGINFO*10+F_Read;
    recordp = (struct C_KDAUFTRAGINFO *) record;

#ifdef SKtkdaufin
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        KDAUFTRAGINFO_LISTE
     into KDAUFTRAGINFO_ZEIGER(recordp)
     from KDAUFTRAGINFO
     where SKtkdaufin;
     break;
    default:
#endif

    EXEC SQL SELECT
        KDAUFTRAGINFO_LISTE
     into KDAUFTRAGINFO_ZEIGER(recordp)
     from KDAUFTRAGINFO
     where PKtkdaufin;

#ifdef SKtkdaufin
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
/*  FUNCTION: pxCustOrderInfoReadLock                                      */
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
int pxCustOrderInfoReadLock
(
    struct tKDAUFTRAGINFO* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGINFO * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRAGINFO*10+F_ReadLock;
    recordp = (struct C_KDAUFTRAGINFO *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE TKDAUFIN_U1 CURSOR WITH HOLD FOR
        SELECT
        KDAUFTRAGINFO_LISTE
    from KDAUFTRAGINFO
    where PKtkdaufin
    FOR UPDATE;
    EXEC SQL OPEN TKDAUFIN_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH TKDAUFIN_U1
      into KDAUFTRAGINFO_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         KDAUFTRAGINFO_LISTE
    into KDAUFTRAGINFO_ZEIGER(recordp)
    from KDAUFTRAGINFO    HOLDLOCK
    where PKtkdaufin;
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
/*  FUNCTION: pxCustOrderInfoUpdate                                        */
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

int pxCustOrderInfoUpdate
(
    struct tKDAUFTRAGINFO* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGINFO * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRAGINFO*10+F_Update;
    recordp = (struct C_KDAUFTRAGINFO *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    KDAUFTRAGINFO
    SET
    KDAUFTRAGINFO_UPDATE(recordp)
    where current of TKDAUFIN_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE TKDAUFIN_U1;
    }
#else

    EXEC SQL UPDATE
    KDAUFTRAGINFO
    SET
    KDAUFTRAGINFO_UPDATE(recordp)
    where PKtkdaufin;
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
/*  FUNCTION: pxCustOrderInfoInsert                                       */
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
int pxCustOrderInfoInsert
(
    struct tKDAUFTRAGINFO* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGINFO * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRAGINFO*10+F_Insert;
    recordp = (struct C_KDAUFTRAGINFO *) record;

    EXEC SQL INSERT INTO
    KDAUFTRAGINFO
    (KDAUFTRAGINFO_LISTE)
    VALUES ( KDAUFTRAGINFO_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    KDAUFTRAGINFO
    VALUES ( KDAUFTRAGINFO_ZEIGER(recordp) );   */


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
/*  FUNCTION: pxCustOrderInfoDelete                                        */
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

int pxCustOrderInfoDelete
(
    struct tKDAUFTRAGINFO* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGINFO * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRAGINFO*10+F_Delete;
    recordp = (struct C_KDAUFTRAGINFO *) record;

    EXEC SQL DELETE FROM
    KDAUFTRAGINFO
    where PKtkdaufin;

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
