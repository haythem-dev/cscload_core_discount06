/*(c)
 ********************* PHARMX Customer Order Entry Server *********************


    Embedded SQL for C application


    FILE: tkdaufdiscacc.c (.sqc)

    Database functions




    FUNCTIONS:

        pxOrderDiscAccStartBrowse  declare and open Cursor
        pxOrderDiscAccGetNext      get next record
        pxOrderDiscAccEndBrowse    close cursor
        pxOrderDiscAccRead         get one record
        pxOrderDiscAccReadLock     get one record with lock
        pxOrderDiscAccInsert       Insert record
        pxOrderDiscAccUpdate       Update record
        pxOrderDiscAccDelete       Delete record


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
#include <tkdaufdiscacc.h>
#include <keys.h>

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxOrderDiscAccStartBrowse                                   */
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
int pxOrderDiscAccStartBrowse
(
     struct tKDAUFTRAGDISCACC* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGDISCACC * recordp;
#ifdef MCtkdaufdiscacc
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_KDAUFTRAGDISCACC*10+F_StartBrowse;
    recordp = (struct C_KDAUFTRAGDISCACC *) record;

    if (!(sizeof(struct C_KDAUFTRAGDISCACC) == sizeof(struct tKDAUFTRAGDISCACC)))
       return cDBXR_DEFINITION;


#ifdef MCtkdaufdiscacc
    strcpy(matchcode,recordp->MCtkdaufdiscacc);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        KDAUFTRAGDISCACC_LISTE
    from KDAUFTRAGDISCACC
    DWtkdaufdiscacc
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        KDAUFTRAGDISCACC_LISTE
    from KDAUFTRAGDISCACC
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
/*  FUNCTION: pxOrderDiscAccGetNext                                       */
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
int pxOrderDiscAccGetNext
(
    struct tKDAUFTRAGDISCACC* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGDISCACC * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_KDAUFTRAGDISCACC*10+F_GetNext;
    recordp = (struct C_KDAUFTRAGDISCACC *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into KDAUFTRAGDISCACC_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into KDAUFTRAGDISCACC_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxOrderDiscAccEndBrowse                                     */
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
int pxOrderDiscAccEndBrowse
(
    int browseid
)
{
    functionnr = F_KDAUFTRAGDISCACC*10+F_EndBrowse;

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
/*  FUNCTION: pxOrderDiscAccRead                                          */
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

int pxOrderDiscAccRead
(
    struct tKDAUFTRAGDISCACC* record
#ifdef SKtkdaufdiscacc
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGDISCACC * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRAGDISCACC*10+F_Read;
    recordp = (struct C_KDAUFTRAGDISCACC *) record;

#ifdef SKtkdaufdiscacc
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        KDAUFTRAGDISCACC_LISTE
     into KDAUFTRAGDISCACC_ZEIGER(recordp)
     from KDAUFTRAGDISCACC
     where SKtkdaufdiscacc;
     break;
    default:
#endif

    EXEC SQL SELECT
        KDAUFTRAGDISCACC_LISTE
     into KDAUFTRAGDISCACC_ZEIGER(recordp)
     from KDAUFTRAGDISCACC
     where PKtkdaufdiscacc;

#ifdef SKtkdaufdiscacc
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
/*  FUNCTION: pxOrderDiscAccReadLock                                      */
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
int pxOrderDiscAccReadLock
(
    struct tKDAUFTRAGDISCACC* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGDISCACC * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRAGDISCACC*10+F_ReadLock;
    recordp = (struct C_KDAUFTRAGDISCACC *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE tkdaufdiscacc_U1 CURSOR WITH HOLD FOR
        SELECT
        KDAUFTRAGDISCACC_LISTE
    from KDAUFTRAGDISCACC
    where PKtkdaufdiscacc
    FOR UPDATE;
    EXEC SQL OPEN tkdaufdiscacc_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH tkdaufdiscacc_U1
      into KDAUFTRAGDISCACC_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         KDAUFTRAGDISCACC_LISTE
    into KDAUFTRAGDISCACC_ZEIGER(recordp)
    from KDAUFTRAGDISCACC    HOLDLOCK
    where PKtkdaufdiscacc;
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
/*  FUNCTION: pxOrderDiscAccUpdate                                        */
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

int pxOrderDiscAccUpdate
(
    struct tKDAUFTRAGDISCACC* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGDISCACC * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRAGDISCACC*10+F_Update;
    recordp = (struct C_KDAUFTRAGDISCACC *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    KDAUFTRAGDISCACC
    SET
    KDAUFTRAGDISCACC_UPDATE(recordp)
    where current of tkdaufdiscacc_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE tkdaufdiscacc_U1;
    }
#else

    EXEC SQL UPDATE
    KDAUFTRAGDISCACC
    SET
    KDAUFTRAGDISCACC_UPDATE(recordp)
    where PKtkdaufdiscacc;
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
/*  FUNCTION: pxOrderDiscAccInsert                                       */
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
int pxOrderDiscAccInsert
(
    struct tKDAUFTRAGDISCACC* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGDISCACC * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRAGDISCACC*10+F_Insert;
    recordp = (struct C_KDAUFTRAGDISCACC *) record;

    EXEC SQL INSERT INTO
    KDAUFTRAGDISCACC
    (KDAUFTRAGDISCACC_LISTE)
    VALUES ( KDAUFTRAGDISCACC_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    KDAUFTRAGDISCACC
    VALUES ( KDAUFTRAGDISCACC_ZEIGER(recordp) );   */


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
/*  FUNCTION: pxOrderDiscAccDelete                                        */
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

int pxOrderDiscAccDelete
(
    struct tKDAUFTRAGDISCACC* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGDISCACC * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRAGDISCACC*10+F_Delete;
    recordp = (struct C_KDAUFTRAGDISCACC *) record;

    EXEC SQL DELETE FROM
    KDAUFTRAGDISCACC
    where PKtkdaufdiscacc;

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
