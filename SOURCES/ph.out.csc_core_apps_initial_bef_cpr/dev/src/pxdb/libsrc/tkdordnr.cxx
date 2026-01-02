/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

                 (c) Copyright 1994-1995 by NORDAT Network GmbH
                              All rights reserved

    Embedded SQL for C application


    FILE: tkdordnr.c (.sqc)

    Database functions




    FUNCTIONS:

        pxCustOrderNumberStartBrowse  declare and open Cursor
        pxCustOrderNumberGetNext      get next record
        pxCustOrderNumberEndBrowse    close cursor
        pxCustOrderNumberRead         get one record
        pxCustOrderNumberReadLock     get one record with lock
        pxCustOrderNumberInsert       Insert record
        pxCustOrderNumberUpdate       Update record
        pxCustOrderNumberDelete       Delete record


REVISION HISTORY

06 Oct 1995 V1.00 REV 00 written by Dietmar Schloetel

*/


#include <stddef.h>         /* standard C run-time header */
#include <stdio.h>          /* standard C run-time header */
#include <pxrecord.h>       /* all record structures */
#include "pxdbfunc.h"
#include "pxdbxx.h"
#include "ndefs.h"
#include <pxenv.h>
#include <tkdordnr.h>
#include <keys.h>

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxCustOrderNumberStartBrowse                                   */
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
int pxCustOrderNumberStartBrowse
(
     struct tCUSTOMERORDERNO* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CUSTOMERORDERNO * recordp;
#ifdef MCtkdordnr
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_CUSTOMERORDERNO*10+F_StartBrowse;
    recordp = (struct C_CUSTOMERORDERNO *) record;

    if (!(sizeof(struct C_CUSTOMERORDERNO) == sizeof(struct tCUSTOMERORDERNO)))
       return cDBXR_DEFINITION;


#ifdef MCtkdordnr
    strcpy(matchcode,recordp->MCtkdordnr);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        CUSTOMERORDERNO_LISTE
    from CUSTOMERORDERNO
    DWtkdordnr
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        CUSTOMERORDERNO_LISTE
    from CUSTOMERORDERNO
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif
    EXEC SQL DECLARE C2 CURSOR FOR
        SELECT
        CUSTOMERORDERNO_LISTE
    from CUSTOMERORDERNO
    where BRANCHNO          = :recordp->BRANCHNO
    and   CUSTOMERNO        = :recordp->CUSTOMERNO
    and   ORDERVALUE        = :recordp->ORDERVALUE
    and   CUSTOMERORDERNO   = :recordp->CUSTOMERORDERNO
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
       case cCRSCUSTORDERNUM       :
          EXEC SQL OPEN C2;
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
/*  FUNCTION: pxCustOrderNumberGetNext                                       */
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
int pxCustOrderNumberGetNext
(
    struct tCUSTOMERORDERNO* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CUSTOMERORDERNO * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_CUSTOMERORDERNO*10+F_GetNext;
    recordp = (struct C_CUSTOMERORDERNO *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into CUSTOMERORDERNO_ZEIGER(recordp);
          break;
       case cCRSCUSTORDERNUM:
          EXEC SQL FETCH C2
          into CUSTOMERORDERNO_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into CUSTOMERORDERNO_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxCustOrderNumberEndBrowse                                     */
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
int pxCustOrderNumberEndBrowse
(
    int browseid
)
{
    functionnr = F_CUSTOMERORDERNO*10+F_EndBrowse;

    /* close the cursor */
    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL CLOSE C0;
          break;
       case cCRSCUSTORDERNUM:
          EXEC SQL CLOSE C2;
          break;
       default:
          EXEC SQL CLOSE C1;
          break;
    }
    return 0;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxCustOrderNumberRead                                          */
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

int pxCustOrderNumberRead
(
    struct tCUSTOMERORDERNO* record
#ifdef SKtkdordnr
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CUSTOMERORDERNO * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_CUSTOMERORDERNO*10+F_Read;
    recordp = (struct C_CUSTOMERORDERNO *) record;

#ifdef SKtkdordnr
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        CUSTOMERORDERNO_LISTE
     into CUSTOMERORDERNO_ZEIGER(recordp)
     from CUSTOMERORDERNO
     where SKtkdordnr;
     break;
    default:
#endif

    EXEC SQL SELECT
        CUSTOMERORDERNO_LISTE
     into CUSTOMERORDERNO_ZEIGER(recordp)
     from CUSTOMERORDERNO
     where PKtkdordnr;

#ifdef SKtkdordnr
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
/*  FUNCTION: pxCustOrderNumberReadLock                                      */
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
int pxCustOrderNumberReadLock
(
    struct tCUSTOMERORDERNO* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CUSTOMERORDERNO * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_CUSTOMERORDERNO*10+F_ReadLock;
    recordp = (struct C_CUSTOMERORDERNO *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE TKDORDNR_U1 CURSOR WITH HOLD FOR
        SELECT
        CUSTOMERORDERNO_LISTE
    from CUSTOMERORDERNO
    where PKtkdordnr
    FOR UPDATE;
    EXEC SQL OPEN TKDORDNR_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH TKDORDNR_U1
      into CUSTOMERORDERNO_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         CUSTOMERORDERNO_LISTE
    into CUSTOMERORDERNO_ZEIGER(recordp)
    from CUSTOMERORDERNO    HOLDLOCK
    where PKtkdordnr;
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
/*  FUNCTION: pxCustOrderNumberUpdate                                        */
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

int pxCustOrderNumberUpdate
(
    struct tCUSTOMERORDERNO* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CUSTOMERORDERNO * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_CUSTOMERORDERNO*10+F_Update;
    recordp = (struct C_CUSTOMERORDERNO *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    CUSTOMERORDERNO
    SET
    CUSTOMERORDERNO_UPDATE(recordp)
    where current of TKDORDNR_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE TKDORDNR_U1;
    }
#else

    EXEC SQL UPDATE
    CUSTOMERORDERNO
    SET
    CUSTOMERORDERNO_UPDATE(recordp)
    where PKtkdordnr;
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
/*  FUNCTION: pxCustOrderNumberInsert                                       */
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
int pxCustOrderNumberInsert
(
    struct tCUSTOMERORDERNO* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CUSTOMERORDERNO * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_CUSTOMERORDERNO*10+F_Insert;
    recordp = (struct C_CUSTOMERORDERNO *) record;

    EXEC SQL INSERT INTO
    CUSTOMERORDERNO
    (CUSTOMERORDERNO_LISTE)
    VALUES ( CUSTOMERORDERNO_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    CUSTOMERORDERNO
    VALUES ( CUSTOMERORDERNO_ZEIGER(recordp) );   */


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
/*  FUNCTION: pxCustOrderNumberDelete                                        */
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

int pxCustOrderNumberDelete
(
    struct tCUSTOMERORDERNO* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CUSTOMERORDERNO * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_CUSTOMERORDERNO*10+F_Delete;
    recordp = (struct C_CUSTOMERORDERNO *) record;

    EXEC SQL DELETE FROM
    CUSTOMERORDERNO
    where PKtkdordnr;

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
