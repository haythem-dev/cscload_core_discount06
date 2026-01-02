/*(c)
 ********************* PHARMX Customer Order Entry Server *********************


    Embedded SQL for C application


    FILE: tdebtlim.c (.sqc)

    Database functions




    FUNCTIONS:

        pxDebitLimitStartBrowse  declare and open Cursor
        pxDebitLimitGetNext      get next record
        pxDebitLimitEndBrowse    close cursor
        pxDebitLimitRead         get one record
        pxDebitLimitReadLock     get one record with lock
        pxDebitLimitInsert       Insert record
        pxDebitLimitUpdate       Update record
        pxDebitLimitDelete       Delete record


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
#include <tdebtlim.h>
#include <keys.h>

/* Global variables */
extern int  functionnr;

#define UNUSED(x) (void)(x)

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxDebitLimitStartBrowse                                   */
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
int pxDebitLimitStartBrowse
(
     struct tDEBTLIMIT* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
#ifdef MCtdebtlim
    struct C_DEBTLIMIT * recordp;
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_DEBTLIMIT*10+F_StartBrowse;
#ifdef MCtdebtlim
    recordp = (struct C_DEBTLIMIT *) record;
#else
    UNUSED(record);
#endif

    if (!(sizeof(struct C_DEBTLIMIT) == sizeof(struct tDEBTLIMIT)))
       return cDBXR_DEFINITION;


#ifdef MCtdebtlim
    strcpy(matchcode,recordp->MCtdebtlim);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        DEBTLIMIT_LISTE
    from DEBTLIMIT
    DWtdebtlim
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        DEBTLIMIT_LISTE
    from DEBTLIMIT
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
/*  FUNCTION: pxDebitLimitGetNext                                       */
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
int pxDebitLimitGetNext
(
    struct tDEBTLIMIT* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_DEBTLIMIT * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_DEBTLIMIT*10+F_GetNext;
    recordp = (struct C_DEBTLIMIT *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into DEBTLIMIT_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into DEBTLIMIT_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxDebitLimitEndBrowse                                     */
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
int pxDebitLimitEndBrowse
(
    int browseid
)
{
    functionnr = F_DEBTLIMIT*10+F_EndBrowse;

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
/*  FUNCTION: pxDebitLimitRead                                          */
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

int pxDebitLimitRead
(
    struct tDEBTLIMIT* record
#ifdef SKtdebtlim
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_DEBTLIMIT * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_DEBTLIMIT*10+F_Read;
    recordp = (struct C_DEBTLIMIT *) record;

#ifdef SKtdebtlim
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        DEBTLIMIT_LISTE
     into DEBTLIMIT_ZEIGER(recordp)
     from DEBTLIMIT
     where SKtdebtlim;
     break;
    default:
#endif

    EXEC SQL SELECT
        DEBTLIMIT_LISTE
     into DEBTLIMIT_ZEIGER(recordp)
     from DEBTLIMIT
     where PKtdebtlim;

#ifdef SKtdebtlim
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
/*  FUNCTION: pxDebitLimitReadLock                                      */
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
int pxDebitLimitReadLock
(
    struct tDEBTLIMIT* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_DEBTLIMIT * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_DEBTLIMIT*10+F_ReadLock;
    recordp = (struct C_DEBTLIMIT *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE TDEBTLIM_U1 CURSOR WITH HOLD FOR
        SELECT
        DEBTLIMIT_LISTE
    from DEBTLIMIT
    where PKtdebtlim
    FOR UPDATE;
    EXEC SQL OPEN TDEBTLIM_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH TDEBTLIM_U1
      into DEBTLIMIT_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         DEBTLIMIT_LISTE
    into DEBTLIMIT_ZEIGER(recordp)
    from DEBTLIMIT    HOLDLOCK
    where PKtdebtlim;
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
/*  FUNCTION: pxDebitLimitUpdate                                        */
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

int pxDebitLimitUpdate
(
    struct tDEBTLIMIT* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_DEBTLIMIT * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_DEBTLIMIT*10+F_Update;
    recordp = (struct C_DEBTLIMIT *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    DEBTLIMIT
    SET
    DEBTLIMIT_UPDATE(recordp)
    where current of TDEBTLIM_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE TDEBTLIM_U1;
    }
#else

    EXEC SQL UPDATE
    DEBTLIMIT
    SET
    DEBTLIMIT_UPDATE(recordp)
    where PKtdebtlim;
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
/*  FUNCTION: pxDebitLimitInsert                                       */
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
int pxDebitLimitInsert
(
    struct tDEBTLIMIT* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_DEBTLIMIT * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_DEBTLIMIT*10+F_Insert;
    recordp = (struct C_DEBTLIMIT *) record;

    EXEC SQL INSERT INTO
    DEBTLIMIT
    (DEBTLIMIT_LISTE)
    VALUES ( DEBTLIMIT_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    DEBTLIMIT
    VALUES ( DEBTLIMIT_ZEIGER(recordp) );   */


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
/*  FUNCTION: pxDebitLimitDelete                                        */
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

int pxDebitLimitDelete
(
    struct tDEBTLIMIT* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_DEBTLIMIT * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_DEBTLIMIT*10+F_Delete;
    recordp = (struct C_DEBTLIMIT *) record;

    EXEC SQL DELETE FROM
    DEBTLIMIT
    where PKtdebtlim;

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
