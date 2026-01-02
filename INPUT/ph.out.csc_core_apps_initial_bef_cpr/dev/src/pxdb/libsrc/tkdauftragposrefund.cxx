/*(c)
 ********************* PHARMX Customer Order Entry Server *********************


    Embedded SQL for C application


    FILE: tkdauftragposrefund.c (.sqc)

    Database functions




    FUNCTIONS:

        pxKdAuftragPosRefundStartBrowse  declare and open Cursor
        pxKdAuftragPosRefundGetNext      get next record
        pxKdAuftragPosRefundEndBrowse    close cursor
        pxKdAuftragPosRefundRead         get one record
        pxKdAuftragPosRefundReadLock     get one record with lock
        pxKdAuftragPosRefundInsert       Insert record
        pxKdAuftragPosRefundUpdate       Update record
        pxKdAuftragPosRefundDelete       Delete record


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
#include <tkdauftragposrefund.h>
#include <keys.h>

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxKdAuftragPosRefundStartBrowse                                   */
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
int pxKdAuftragPosRefundStartBrowse
(
     struct tKDAUFTRAGPOSREFUND* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGPOSREFUND * recordp;
#ifdef MCtkdauftragposrefund
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_KDAUFTRAGPOSREFUND*10+F_StartBrowse;
    recordp = (struct C_KDAUFTRAGPOSREFUND *) record;

    if (!(sizeof(struct C_KDAUFTRAGPOSREFUND) == sizeof(struct tKDAUFTRAGPOSREFUND)))
       return cDBXR_DEFINITION;


#ifdef MCtkdauftragposrefund
    strcpy(matchcode,recordp->MCtkdauftragposrefund);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        KDAUFTRAGPOSREFUND_LISTE
    from KDAUFTRAGPOSREFUND
    DWtkdauftragposrefund
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        KDAUFTRAGPOSREFUND_LISTE
    from KDAUFTRAGPOSREFUND
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
/*  FUNCTION: pxKdAuftragPosRefundGetNext                                       */
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
int pxKdAuftragPosRefundGetNext
(
    struct tKDAUFTRAGPOSREFUND* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGPOSREFUND * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_KDAUFTRAGPOSREFUND*10+F_GetNext;
    recordp = (struct C_KDAUFTRAGPOSREFUND *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into KDAUFTRAGPOSREFUND_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into KDAUFTRAGPOSREFUND_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxKdAuftragPosRefundEndBrowse                                     */
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
int pxKdAuftragPosRefundEndBrowse
(
    int browseid
)
{
    functionnr = F_KDAUFTRAGPOSREFUND*10+F_EndBrowse;

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
/*  FUNCTION: pxKdAuftragPosRefundRead                                          */
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

int pxKdAuftragPosRefundRead
(
    struct tKDAUFTRAGPOSREFUND* record
#ifdef SKtkdauftragposrefund
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGPOSREFUND * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRAGPOSREFUND*10+F_Read;
    recordp = (struct C_KDAUFTRAGPOSREFUND *) record;

#ifdef SKtkdauftragposrefund
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        KDAUFTRAGPOSREFUND_LISTE
     into KDAUFTRAGPOSREFUND_ZEIGER(recordp)
     from KDAUFTRAGPOSREFUND
     where SKtkdauftragposrefund;
     break;
    default:
#endif

    EXEC SQL SELECT
        KDAUFTRAGPOSREFUND_LISTE
     into KDAUFTRAGPOSREFUND_ZEIGER(recordp)
     from KDAUFTRAGPOSREFUND
     where PKtkdauftragposrefund;

#ifdef SKtkdauftragposrefund
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
/*  FUNCTION: pxKdAuftragPosRefundReadLock                                      */
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
int pxKdAuftragPosRefundReadLock
(
    struct tKDAUFTRAGPOSREFUND* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGPOSREFUND * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRAGPOSREFUND*10+F_ReadLock;
    recordp = (struct C_KDAUFTRAGPOSREFUND *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE tkdauftragposrefund_U1 CURSOR WITH HOLD FOR
        SELECT
        KDAUFTRAGPOSREFUND_LISTE
    from KDAUFTRAGPOSREFUND
    where PKtkdauftragposrefund
    FOR UPDATE;
    EXEC SQL OPEN tkdauftragposrefund_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH tkdauftragposrefund_U1
      into KDAUFTRAGPOSREFUND_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         KDAUFTRAGPOSREFUND_LISTE
    into KDAUFTRAGPOSREFUND_ZEIGER(recordp)
    from KDAUFTRAGPOSREFUND    HOLDLOCK
    where PKtkdauftragposrefund;
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
/*  FUNCTION: pxKdAuftragPosRefundUpdate                                        */
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

int pxKdAuftragPosRefundUpdate
(
    struct tKDAUFTRAGPOSREFUND* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGPOSREFUND * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRAGPOSREFUND*10+F_Update;
    recordp = (struct C_KDAUFTRAGPOSREFUND *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    KDAUFTRAGPOSREFUND
    SET
    KDAUFTRAGPOSREFUND_UPDATE(recordp)
    where current of tkdauftragposrefund_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE tkdauftragposrefund_U1;
    }
#else

    EXEC SQL UPDATE
    KDAUFTRAGPOSREFUND
    SET
    KDAUFTRAGPOSREFUND_UPDATE(recordp)
    where PKtkdauftragposrefund;
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
/*  FUNCTION: pxKdAuftragPosRefundInsert                                       */
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
int pxKdAuftragPosRefundInsert
(
    struct tKDAUFTRAGPOSREFUND* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGPOSREFUND * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRAGPOSREFUND*10+F_Insert;
    recordp = (struct C_KDAUFTRAGPOSREFUND *) record;

    EXEC SQL INSERT INTO
    KDAUFTRAGPOSREFUND
    (KDAUFTRAGPOSREFUND_LISTE)
    VALUES ( KDAUFTRAGPOSREFUND_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    KDAUFTRAGPOSREFUND
    VALUES ( KDAUFTRAGPOSREFUND_ZEIGER(recordp) );   */


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
/*  FUNCTION: pxKdAuftragPosRefundDelete                                        */
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

int pxKdAuftragPosRefundDelete
(
    struct tKDAUFTRAGPOSREFUND* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGPOSREFUND * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRAGPOSREFUND*10+F_Delete;
    recordp = (struct C_KDAUFTRAGPOSREFUND *) record;

    EXEC SQL DELETE FROM
    KDAUFTRAGPOSREFUND
    where PKtkdauftragposrefund;

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
