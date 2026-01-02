/*(c)
 ********************* PHARMX Customer Order Entry Server *********************


    Embedded SQL for C application


    FILE: tcstdiscacc.c (.sqc)

    Database functions




    FUNCTIONS:

        pxCstDiscAccStartBrowse  declare and open Cursor
        pxCstDiscAccGetNext      get next record
        pxCstDiscAccEndBrowse    close cursor
        pxCstDiscAccRead         get one record
        pxCstDiscAccReadLock     get one record with lock
        pxCstDiscAccInsert       Insert record
        pxCstDiscAccUpdate       Update record
        pxCstDiscAccDelete       Delete record


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
#include <tcstdiscacc.h>
#include <keys.h>

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxCstDiscAccStartBrowse                                   */
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
int pxCstDiscAccStartBrowse
(
     struct tCSTDISCACC* record,
     int browseid,
     long DateTo
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CSTDISCACC * recordp;
    long dateto = DateTo;
#ifdef MCtcstdiscacc
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_CSTDISCACC*10+F_StartBrowse;
    recordp = (struct C_CSTDISCACC *) record;

    if (!(sizeof(struct C_CSTDISCACC) == sizeof(struct tCSTDISCACC)))
       return cDBXR_DEFINITION;


#ifdef MCtcstdiscacc
    strcpy(matchcode,recordp->MCtcstdiscacc);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        CSTDISCACC_LISTE
    from CSTDISCACC
    DWtcstdiscacc
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        CSTDISCACC_LISTE
    from CSTDISCACC
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif
    EXEC SQL DECLARE C2 CURSOR FOR
        SELECT
        CSTDISCACC_LISTE
    from CSTDISCACC
    where BRANCHNO     = :recordp->BRANCHNO
    and   CUSTOMERNO   = :recordp->CUSTOMERNO
    and   DATE        >= :recordp->DATE
    and   DATE        <= :dateto
    and   KDAUFTRAGNR  = 0
    and   BALANCE      > 0.0
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif
    EXEC SQL DECLARE C3 CURSOR FOR
        SELECT
        CSTDISCACC_LISTE
    from CSTDISCACC
    where MAINCSTNO    = :recordp->MAINCSTNO
    and   DATE        >= :recordp->DATE
    and   DATE        <= :dateto
    and   KDAUFTRAGNR  = 0
    and   BALANCE      > 0.0
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif
    EXEC SQL DECLARE C4 CURSOR FOR
        SELECT
        CSTDISCACC_LISTE
    from CSTDISCACC
    where KDAUFTRAGNR  = :recordp->KDAUFTRAGNR
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif
    EXEC SQL DECLARE C5 CURSOR FOR
        SELECT
        CSTDISCACC_LISTE
    from CSTDISCACC
    where BRANCHNO     = :recordp->BRANCHNO
    and   CUSTOMERNO   = :recordp->CUSTOMERNO
    and   DATE        >= :recordp->DATE
    and   DATE        <= :dateto
    and   KDAUFTRAGNR  = 0
    and   BALANCE      > 0.0
    and   VOUCHERTYP   = :recordp->VOUCHERTYP
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif
    EXEC SQL DECLARE C6 CURSOR FOR
        SELECT
        CSTDISCACC_LISTE
    from CSTDISCACC
    where MAINCSTNO    = :recordp->MAINCSTNO
    and   DATE        >= :recordp->DATE
    and   DATE        <= :dateto
    and   KDAUFTRAGNR  = 0
    and   BALANCE      > 0.0
    and   VOUCHERTYP   = :recordp->VOUCHERTYP
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
       case cCRCDACUSTOMERNO:
          EXEC SQL OPEN C2;
          break;
       case cCRCDAMAINCSTNO:
          EXEC SQL OPEN C3;
          break;
       case cCRCDAKDAUFTRAGNR:
          EXEC SQL OPEN C4;
          break;
       case cCRCDACUSTOMERNOVOUCHERTYP:
          EXEC SQL OPEN C5;
          break;
       case cCRCDAMAINCSTNOVOUCHERTYP:
          EXEC SQL OPEN C6;
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
/*  FUNCTION: pxCstDiscAccGetNext                                       */
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
int pxCstDiscAccGetNext
(
    struct tCSTDISCACC* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CSTDISCACC * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_CSTDISCACC*10+F_GetNext;
    recordp = (struct C_CSTDISCACC *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into CSTDISCACC_ZEIGER(recordp);
          break;
       case cCRCDACUSTOMERNO:
          EXEC SQL FETCH C2
          into CSTDISCACC_ZEIGER(recordp);
          break;
       case cCRCDAMAINCSTNO:
          EXEC SQL FETCH C3
          into CSTDISCACC_ZEIGER(recordp);
          break;
       case cCRCDAKDAUFTRAGNR:
          EXEC SQL FETCH C4
          into CSTDISCACC_ZEIGER(recordp);
          break;
       case cCRCDACUSTOMERNOVOUCHERTYP:
          EXEC SQL FETCH C5
          into CSTDISCACC_ZEIGER(recordp);
          break;
       case cCRCDAMAINCSTNOVOUCHERTYP:
          EXEC SQL FETCH C6
          into CSTDISCACC_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into CSTDISCACC_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxCstDiscAccEndBrowse                                     */
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
int pxCstDiscAccEndBrowse
(
    int browseid
)
{
    functionnr = F_CSTDISCACC*10+F_EndBrowse;

    /* close the cursor */
    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL CLOSE C0;
          break;
       case cCRCDACUSTOMERNO:
          EXEC SQL CLOSE C2;
          break;
       case cCRCDAMAINCSTNO:
          EXEC SQL CLOSE C3;
          break;
       case cCRCDAKDAUFTRAGNR:
          EXEC SQL CLOSE C4;
          break;
       case cCRCDACUSTOMERNOVOUCHERTYP:
          EXEC SQL CLOSE C5;
          break;
       case cCRCDAMAINCSTNOVOUCHERTYP:
          EXEC SQL CLOSE C6;
          break;
       default:
          EXEC SQL CLOSE C1;
          break;
    }
    return 0;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxCstDiscAccRead                                          */
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

int pxCstDiscAccRead
(
    struct tCSTDISCACC* record
#ifdef SKtcstdiscacc
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CSTDISCACC * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_CSTDISCACC*10+F_Read;
    recordp = (struct C_CSTDISCACC *) record;

#ifdef SKtcstdiscacc
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        CSTDISCACC_LISTE
     into CSTDISCACC_ZEIGER(recordp)
     from CSTDISCACC
     where SKtcstdiscacc;
     break;
    default:
#endif

    EXEC SQL SELECT
        CSTDISCACC_LISTE
     into CSTDISCACC_ZEIGER(recordp)
     from CSTDISCACC
     where PKtcstdiscacc;

#ifdef SKtcstdiscacc
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
/*  FUNCTION: pxCstDiscAccReadLock                                      */
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
int pxCstDiscAccReadLock
(
    struct tCSTDISCACC* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CSTDISCACC * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_CSTDISCACC*10+F_ReadLock;
    recordp = (struct C_CSTDISCACC *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE tcstdiscacc_U1 CURSOR WITH HOLD FOR
        SELECT
        CSTDISCACC_LISTE
    from CSTDISCACC
    where PKtcstdiscacc
    FOR UPDATE;
    EXEC SQL OPEN tcstdiscacc_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH tcstdiscacc_U1
      into CSTDISCACC_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         CSTDISCACC_LISTE
    into CSTDISCACC_ZEIGER(recordp)
    from CSTDISCACC    HOLDLOCK
    where PKtcstdiscacc;
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
/*  FUNCTION: pxCstDiscAccUpdate                                        */
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

int pxCstDiscAccUpdate
(
    struct tCSTDISCACC* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CSTDISCACC * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_CSTDISCACC*10+F_Update;
    recordp = (struct C_CSTDISCACC *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    CSTDISCACC
    SET
    CSTDISCACC_UPDATE(recordp)
    where current of tcstdiscacc_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE tcstdiscacc_U1;
    }
#else

    EXEC SQL UPDATE
    CSTDISCACC
    SET
    CSTDISCACC_UPDATE(recordp)
    where PKtcstdiscacc;
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
/*  FUNCTION: pxCstDiscAccInsert                                       */
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
int pxCstDiscAccInsert
(
    struct tCSTDISCACC* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CSTDISCACC * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_CSTDISCACC*10+F_Insert;
    recordp = (struct C_CSTDISCACC *) record;

    EXEC SQL INSERT INTO
    CSTDISCACC
    (CSTDISCACC_LISTE)
    VALUES ( CSTDISCACC_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    CSTDISCACC
    VALUES ( CSTDISCACC_ZEIGER(recordp) );   */


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
/*  FUNCTION: pxCstDiscAccDelete                                        */
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

int pxCstDiscAccDelete
(
    struct tCSTDISCACC* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CSTDISCACC * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_CSTDISCACC*10+F_Delete;
    recordp = (struct C_CSTDISCACC *) record;

    EXEC SQL DELETE FROM
    CSTDISCACC
    where PKtcstdiscacc;

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
