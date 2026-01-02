/*(c)
 ********************* PHARMX Customer Order Entry Server *********************


    Embedded SQL for C application


    FILE: tkdauftragposcharge.c (.sqc)

    Database functions




    FUNCTIONS:

        pxItemChargeStartBrowse  declare and open Cursor
        pxItemChargeGetNext      get next record
        pxItemChargeEndBrowse    close cursor
        pxItemChargeRead         get one record
        pxItemChargeReadLock     get one record with lock
        pxItemChargeInsert       Insert record
        pxItemChargeUpdate       Update record
        pxItemChargeDelete       Delete record


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
#include <tkdauftragposcharge.h>
#include <keys.h>

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxItemChargeStartBrowse                                   */
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
int pxItemChargeStartBrowse
(
     struct tKDAUFTRAGPOSCHARGE* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGPOSCHARGE * recordp;
#ifdef MCtkdauftragposcharge
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_KDAUFTRAGPOSCHARGE*10+F_StartBrowse;
    recordp = (struct C_KDAUFTRAGPOSCHARGE *) record;

    if (!(sizeof(struct C_KDAUFTRAGPOSCHARGE) == sizeof(struct tKDAUFTRAGPOSCHARGE)))
       return cDBXR_DEFINITION;


#ifdef MCtkdauftragposcharge
    strcpy(matchcode,recordp->MCtkdauftragposcharge);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        KDAUFTRAGPOSCHARGE_LISTE
    from KDAUFTRAGPOSCHARGE
    DWtkdauftragposcharge
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        KDAUFTRAGPOSCHARGE_LISTE
    from KDAUFTRAGPOSCHARGE
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
/*  FUNCTION: pxItemChargeGetNext                                       */
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
int pxItemChargeGetNext
(
    struct tKDAUFTRAGPOSCHARGE* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGPOSCHARGE * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_KDAUFTRAGPOSCHARGE*10+F_GetNext;
    recordp = (struct C_KDAUFTRAGPOSCHARGE *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into KDAUFTRAGPOSCHARGE_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into KDAUFTRAGPOSCHARGE_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxItemChargeEndBrowse                                     */
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
int pxItemChargeEndBrowse
(
    int browseid
)
{
    functionnr = F_KDAUFTRAGPOSCHARGE*10+F_EndBrowse;

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
/*  FUNCTION: pxItemChargeRead                                          */
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

int pxItemChargeRead
(
    struct tKDAUFTRAGPOSCHARGE* record
#ifdef SKtkdauftragposcharge
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGPOSCHARGE * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRAGPOSCHARGE*10+F_Read;
    recordp = (struct C_KDAUFTRAGPOSCHARGE *) record;

#ifdef SKtkdauftragposcharge
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        KDAUFTRAGPOSCHARGE_LISTE
     into KDAUFTRAGPOSCHARGE_ZEIGER(recordp)
     from KDAUFTRAGPOSCHARGE
     where SKtkdauftragposcharge;
     break;
    default:
#endif

    EXEC SQL SELECT
        KDAUFTRAGPOSCHARGE_LISTE
     into KDAUFTRAGPOSCHARGE_ZEIGER(recordp)
     from KDAUFTRAGPOSCHARGE
     where PKtkdauftragposcharge;

#ifdef SKtkdauftragposcharge
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
/*  FUNCTION: pxItemChargeReadLock                                      */
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
int pxItemChargeReadLock
(
    struct tKDAUFTRAGPOSCHARGE* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGPOSCHARGE * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRAGPOSCHARGE*10+F_ReadLock;
    recordp = (struct C_KDAUFTRAGPOSCHARGE *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE tkdauftragposcharge_U1 CURSOR WITH HOLD FOR
        SELECT
        KDAUFTRAGPOSCHARGE_LISTE
    from KDAUFTRAGPOSCHARGE
    where PKtkdauftragposcharge
    FOR UPDATE;
    EXEC SQL OPEN tkdauftragposcharge_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH tkdauftragposcharge_U1
      into KDAUFTRAGPOSCHARGE_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         KDAUFTRAGPOSCHARGE_LISTE
    into KDAUFTRAGPOSCHARGE_ZEIGER(recordp)
    from KDAUFTRAGPOSCHARGE    HOLDLOCK
    where PKtkdauftragposcharge;
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
/*  FUNCTION: pxItemChargeUpdate                                        */
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

int pxItemChargeUpdate
(
    struct tKDAUFTRAGPOSCHARGE* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGPOSCHARGE * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRAGPOSCHARGE*10+F_Update;
    recordp = (struct C_KDAUFTRAGPOSCHARGE *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    KDAUFTRAGPOSCHARGE
    SET
    KDAUFTRAGPOSCHARGE_UPDATE(recordp)
    where current of tkdauftragposcharge_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE tkdauftragposcharge_U1;
    }
#else

    EXEC SQL UPDATE
    KDAUFTRAGPOSCHARGE
    SET
    KDAUFTRAGPOSCHARGE_UPDATE(recordp)
    where PKtkdauftragposcharge;
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
/*  FUNCTION: pxItemChargeInsert                                       */
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
int pxItemChargeInsert
(
    struct tKDAUFTRAGPOSCHARGE* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGPOSCHARGE * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRAGPOSCHARGE*10+F_Insert;
    recordp = (struct C_KDAUFTRAGPOSCHARGE *) record;

    EXEC SQL INSERT INTO
    KDAUFTRAGPOSCHARGE
    (KDAUFTRAGPOSCHARGE_LISTE)
    VALUES ( KDAUFTRAGPOSCHARGE_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    KDAUFTRAGPOSCHARGE
    VALUES ( KDAUFTRAGPOSCHARGE_ZEIGER(recordp) );   */


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
/*  FUNCTION: pxItemChargeDelete                                        */
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

int pxItemChargeDelete
(
    struct tKDAUFTRAGPOSCHARGE* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGPOSCHARGE * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRAGPOSCHARGE*10+F_Delete;
    recordp = (struct C_KDAUFTRAGPOSCHARGE *) record;

    EXEC SQL DELETE FROM
    KDAUFTRAGPOSCHARGE
    where PKtkdauftragposcharge;

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
