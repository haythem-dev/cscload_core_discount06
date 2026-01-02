/*(c)
 ********************* PHARMX Customer Order Entry Server *********************


    Embedded SQL for C application


    FILE: tnarctracttrfer.c (.sqc)

    Database functions




    FUNCTIONS:

        pxNarcTransferStartBrowse  declare and open Cursor
        pxNarcTransferGetNext      get next record
        pxNarcTransferEndBrowse    close cursor
        pxNarcTransferRead         get one record
        pxNarcTransferReadLock     get one record with lock
        pxNarcTransferInsert       Insert record
        pxNarcTransferUpdate       Update record
        pxNarcTransferDelete       Delete record


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
#include <tnarctracttrfer.h>
#include <keys.h>

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxNarcTransferStartBrowse                                   */
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
int pxNarcTransferStartBrowse
(
     struct tNARCTRANSACTIONTRANSFER * record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_NARCTRANSACTIONTRANSFER * recordp;
#ifdef MCtnarctracttrfer
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_NARCTRANSACTIONTRANSFER*10+F_StartBrowse;
    recordp = (struct C_NARCTRANSACTIONTRANSFER *) record;

    if (!(sizeof(struct C_NARCTRANSACTIONTRANSFER) == sizeof(struct tNARCTRANSACTIONTRANSFER)))
       return cDBXR_DEFINITION;


#ifdef MCtnarctracttrfer
    strcpy(matchcode,recordp->MCtnarctracttrfer);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        NARCTRANSACTIONTRANSFER_LISTE
    from NARCTRANSACTIONTRANSFER
    DWtnarctracttrfer
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        NARCTRANSACTIONTRANSFER_LISTE
    from NARCTRANSACTIONTRANSFER
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif
    EXEC SQL DECLARE C2 CURSOR FOR
        SELECT
        NARCTRANSACTIONTRANSFER_LISTE
    from NARCTRANSACTIONTRANSFER
    where ORDERNO      = :recordp->ORDERNO
    and   POSNO        = :recordp->POSNO
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C3 CURSOR FOR
        SELECT
        NARCTRANSACTIONTRANSFER_LISTE
    from NARCTRANSACTIONTRANSFER
    where BRANCHNO     = :recordp->BRANCHNO
    and   ORDERNO      = :recordp->ORDERNO
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
       case cCRSNARCTRANSFER_ORDERPOS:
          EXEC SQL OPEN C2;
          break;
       case cCRSNARCTRANSFER_ORDERART:
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
/*  FUNCTION: pxNarcTransferGetNext                                       */
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
int pxNarcTransferGetNext
(
    struct tNARCTRANSACTIONTRANSFER * record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_NARCTRANSACTIONTRANSFER * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_NARCTRANSACTIONTRANSFER*10+F_GetNext;
    recordp = (struct C_NARCTRANSACTIONTRANSFER *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into NARCTRANSACTIONTRANSFER_ZEIGER(recordp);
          break;
       case cCRSNARCTRANSFER_ORDERPOS:
          EXEC SQL FETCH C2
          into NARCTRANSACTIONTRANSFER_ZEIGER(recordp);
          break;
       case cCRSNARCTRANSFER_ORDERART:
          EXEC SQL FETCH C3
          into NARCTRANSACTIONTRANSFER_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into NARCTRANSACTIONTRANSFER_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxNarcTransferEndBrowse                                     */
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
int pxNarcTransferEndBrowse
(
    int browseid
)
{
    functionnr = F_NARCTRANSACTIONTRANSFER*10+F_EndBrowse;

    /* close the cursor */
    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL CLOSE C0;
          break;
       case cCRSNARCTRANSFER_ORDERPOS:
          EXEC SQL CLOSE C2;
          break;
       case cCRSNARCTRANSFER_ORDERART:
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
/*  FUNCTION: pxNarcTransferRead                                          */
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

int pxNarcTransferRead
(
    struct tNARCTRANSACTIONTRANSFER * record
#ifdef SKtnarctracttrfer
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_NARCTRANSACTIONTRANSFER * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_NARCTRANSACTIONTRANSFER*10+F_Read;
    recordp = (struct C_NARCTRANSACTIONTRANSFER *) record;

#ifdef SKtnarctracttrfer
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        NARCTRANSACTIONTRANSFER_LISTE
     into NARCTRANSACTIONTRANSFER_ZEIGER(recordp)
     from NARCTRANSACTIONTRANSFER
     where SKtnarctracttrfer;
     break;
    default:
#endif

    EXEC SQL SELECT
        NARCTRANSACTIONTRANSFER_LISTE
     into NARCTRANSACTIONTRANSFER_ZEIGER(recordp)
     from NARCTRANSACTIONTRANSFER
     where PKtnarctracttrfer;

#ifdef SKtnarctracttrfer
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
/*  FUNCTION: pxNarcTransferReadLock                                      */
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
int pxNarcTransferReadLock
(
    struct tNARCTRANSACTIONTRANSFER * record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_NARCTRANSACTIONTRANSFER * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_NARCTRANSACTIONTRANSFER*10+F_ReadLock;
    recordp = (struct C_NARCTRANSACTIONTRANSFER *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE tnarctracttrfer_U1 CURSOR WITH HOLD FOR
        SELECT
        NARCTRANSACTIONTRANSFER_LISTE
    from NARCTRANSACTIONTRANSFER
    where PKtnarctracttrfer
    FOR UPDATE;
    EXEC SQL OPEN tnarctracttrfer_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH tnarctracttrfer_U1
      into NARCTRANSACTIONTRANSFER_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         NARCTRANSACTIONTRANSFER_LISTE
    into NARCTRANSACTIONTRANSFER_ZEIGER(recordp)
    from NARCTRANSACTIONTRANSFER    HOLDLOCK
    where PKtnarctracttrfer;
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
/*  FUNCTION: pxNarcTransferUpdate                                        */
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

int pxNarcTransferUpdate
(
    struct tNARCTRANSACTIONTRANSFER * record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_NARCTRANSACTIONTRANSFER * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_NARCTRANSACTIONTRANSFER*10+F_Update;
    recordp = (struct C_NARCTRANSACTIONTRANSFER *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    NARCTRANSACTIONTRANSFER
    SET
    NARCTRANSACTIONTRANSFER_UPDATE(recordp)
    where current of tnarctracttrfer_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE tnarctracttrfer_U1;
    }
#else

    EXEC SQL UPDATE
    NARCTRANSACTIONTRANSFER
    SET
    NARCTRANSACTIONTRANSFER_UPDATE(recordp)
    where PKtnarctracttrfer;
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
/*  FUNCTION: pxNarcTransferInsert                                       */
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
int pxNarcTransferInsert
(
    struct tNARCTRANSACTIONTRANSFER * record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_NARCTRANSACTIONTRANSFER * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_NARCTRANSACTIONTRANSFER*10+F_Insert;
    recordp = (struct C_NARCTRANSACTIONTRANSFER *) record;

    EXEC SQL INSERT INTO
    NARCTRANSACTIONTRANSFER
    (NARCTRANSACTIONTRANSFER_LISTE)
    VALUES ( NARCTRANSACTIONTRANSFER_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    NARCTRANSACTIONTRANSFER
    VALUES ( NARCTRANSACTIONTRANSFER_ZEIGER(recordp) );   */


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
/*  FUNCTION: pxNarcTransferDelete                                        */
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

int pxNarcTransferDelete
(
    struct tNARCTRANSACTIONTRANSFER * record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_NARCTRANSACTIONTRANSFER * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_NARCTRANSACTIONTRANSFER*10+F_Delete;
    recordp = (struct C_NARCTRANSACTIONTRANSFER *) record;

    EXEC SQL DELETE FROM
    NARCTRANSACTIONTRANSFER
    where PKtnarctracttrfer;

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
