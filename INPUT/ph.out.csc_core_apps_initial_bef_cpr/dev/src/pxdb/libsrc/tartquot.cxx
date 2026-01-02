/*(c)
 ********************* PHARMX Customer Order Entry Server *********************


    Embedded SQL for C application


    FILE: tartquot.c (.sqc)

    Database functions




    FUNCTIONS:

        pxArticleQuotaStartBrowse  declare and open Cursor
        pxArticleQuotaGetNext      get next record
        pxArticleQuotaEndBrowse    close cursor
        pxArticleQuotaRead         get one record
        pxArticleQuotaReadLock     get one record with lock
        pxArticleQuotaInsert       Insert record
        pxArticleQuotaUpdate       Update record
        pxArticleQuotaDelete       Delete record


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
#include <tartquot.h>
#include <keys.h>

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxArticleQuotaStartBrowse                                   */
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
int pxArticleQuotaStartBrowse
(
     struct tARTICLEQUOTA* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTICLEQUOTA * recordp;
#ifdef MCtartquot
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_ARTICLEQUOTA*10+F_StartBrowse;
    recordp = (struct C_ARTICLEQUOTA *) record;

    if (!(sizeof(struct C_ARTICLEQUOTA) == sizeof(struct tARTICLEQUOTA)))
       return cDBXR_DEFINITION;


#ifdef MCtartquot
    strcpy(matchcode,recordp->MCtartquot);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        ARTICLEQUOTA_LISTE
    from ARTICLEQUOTA
    DWtartquot
    and   ARTICLEQUOTA.DATEFROM <= TO_CHAR(today, '%Y%m%d')
    and   ARTICLEQUOTA.DATETO >= TO_CHAR(today, '%Y%m%d')

#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C2 CURSOR FOR
        SELECT
        ARTICLEQUOTA_LISTE
    from ARTICLEQUOTA
    where
    ARTICLEQUOTA.ARTICLENO = :recordp->ARTICLENO
    and ARTICLEQUOTA.BRANCHNO = :recordp->BRANCHNO
    and (ARTICLEQUOTA.CUSTOMERNO = :recordp->CUSTOMERNO
    or (ARTICLEQUOTA.CUSTOMERNO = 0
    and ARTICLEQUOTA.PHARMACYGROUPID in
    ( select CUSTOMERPHARMACYGR.PHARMACYGROUPID
    from CUSTOMERPHARMACYGR
    where CUSTOMERPHARMACYGR.BRANCHNO = :recordp->BRANCHNO
    and CUSTOMERPHARMACYGR.CUSTOMERNO = :recordp->CUSTOMERNO)))
    and   ARTICLEQUOTA.DATEFROM <= TO_CHAR(today, '%Y%m%d')
    and   ARTICLEQUOTA.DATETO >= TO_CHAR(today, '%Y%m%d')

#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C3 CURSOR FOR
        SELECT
        ARTICLEQUOTA_LISTE
    from ARTICLEQUOTA
    where
    ARTICLEQUOTA.ARTICLENO = :recordp->ARTICLENO
    and ARTICLEQUOTA.BRANCHNO = :recordp->BRANCHNO
    and ARTICLEQUOTA.CUSTOMERNO = 0
    and (ARTICLEQUOTA.PHARMACYGROUPID = "" or ARTICLEQUOTA.PHARMACYGROUPID = "000")
    and   ARTICLEQUOTA.DATEFROM <= TO_CHAR(today, '%Y%m%d')
    and   ARTICLEQUOTA.DATETO >= TO_CHAR(today, '%Y%m%d')

#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        ARTICLEQUOTA_LISTE
    from ARTICLEQUOTA
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
       case cCRSARTICLEQUOTA_ORIGINAL:
          EXEC SQL OPEN C2;
          break;
       case cCRSARTICLEQUOTA_BASIC:
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
/*  FUNCTION: pxArticleQuotaGetNext                                       */
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
int pxArticleQuotaGetNext
(
    struct tARTICLEQUOTA* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTICLEQUOTA * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_ARTICLEQUOTA*10+F_GetNext;
    recordp = (struct C_ARTICLEQUOTA *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into ARTICLEQUOTA_ZEIGER(recordp);
          break;
       case cCRSARTICLEQUOTA_ORIGINAL:
          EXEC SQL FETCH C2
          into ARTICLEQUOTA_ZEIGER(recordp);
          break;
       case cCRSARTICLEQUOTA_BASIC:
          EXEC SQL FETCH C3
          into ARTICLEQUOTA_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into ARTICLEQUOTA_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxArticleQuotaEndBrowse                                     */
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
int pxArticleQuotaEndBrowse
(
    int browseid
)
{
    functionnr = F_ARTICLEQUOTA*10+F_EndBrowse;

    /* close the cursor */
    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL CLOSE C0;
          break;
       case cCRSARTICLEQUOTA_ORIGINAL:
          EXEC SQL CLOSE C2;
          break;
       case cCRSARTICLEQUOTA_BASIC:
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
/*  FUNCTION: pxArticleQuotaRead                                          */
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

int pxArticleQuotaRead
(
    struct tARTICLEQUOTA* record
#ifdef SKtartquot
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTICLEQUOTA * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTICLEQUOTA*10+F_Read;
    recordp = (struct C_ARTICLEQUOTA *) record;

#ifdef SKtartquot
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        ARTICLEQUOTA_LISTE
     into ARTICLEQUOTA_ZEIGER(recordp)
     from ARTICLEQUOTA
     where SKtartquot;
     break;
    default:
#endif

    EXEC SQL SELECT
        ARTICLEQUOTA_LISTE
     into ARTICLEQUOTA_ZEIGER(recordp)
     from ARTICLEQUOTA
     where PKtartquot;

#ifdef SKtartquot
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
/*  FUNCTION: pxArticleQuotaReadLock                                      */
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
int pxArticleQuotaReadLock
(
    struct tARTICLEQUOTA* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTICLEQUOTA * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTICLEQUOTA*10+F_ReadLock;
    recordp = (struct C_ARTICLEQUOTA *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE TARTQUOT_U1 CURSOR WITH HOLD FOR
        SELECT
        ARTICLEQUOTA_LISTE
    from ARTICLEQUOTA
    where PKtartquot
    FOR UPDATE;
    EXEC SQL OPEN TARTQUOT_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH TARTQUOT_U1
      into ARTICLEQUOTA_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         ARTICLEQUOTA_LISTE
    into ARTICLEQUOTA_ZEIGER(recordp)
    from ARTICLEQUOTA    HOLDLOCK
    where PKtartquot;
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
/*  FUNCTION: pxArticleQuotaUpdate                                        */
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

int pxArticleQuotaUpdate
(
    struct tARTICLEQUOTA* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTICLEQUOTA * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTICLEQUOTA*10+F_Update;
    recordp = (struct C_ARTICLEQUOTA *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    ARTICLEQUOTA
    SET
    ARTICLEQUOTA_UPDATE(recordp)
    where current of TARTQUOT_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE TARTQUOT_U1;
    }
#else

    EXEC SQL UPDATE
    ARTICLEQUOTA
    SET
    ARTICLEQUOTA_UPDATE(recordp)
    where PKtartquot;
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
/*  FUNCTION: pxArticleQuotaInsert                                       */
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
int pxArticleQuotaInsert
(
    struct tARTICLEQUOTA* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTICLEQUOTA * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTICLEQUOTA*10+F_Insert;
    recordp = (struct C_ARTICLEQUOTA *) record;

    EXEC SQL INSERT INTO
    ARTICLEQUOTA
    (ARTICLEQUOTA_LISTE)
    VALUES ( ARTICLEQUOTA_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    ARTICLEQUOTA
    VALUES ( ARTICLEQUOTA_ZEIGER(recordp) );   */


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
/*  FUNCTION: pxArticleQuotaDelete                                        */
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

int pxArticleQuotaDelete
(
    struct tARTICLEQUOTA* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTICLEQUOTA * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTICLEQUOTA*10+F_Delete;
    recordp = (struct C_ARTICLEQUOTA *) record;

    EXEC SQL DELETE FROM
    ARTICLEQUOTA
    where PKtartquot;

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
