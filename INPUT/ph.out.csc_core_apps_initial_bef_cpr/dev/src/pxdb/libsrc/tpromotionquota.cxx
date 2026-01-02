/*(c)
 ********************* PHARMX Customer Order Entry Server *********************


    Embedded SQL for C application


    FILE: tpromotionquota.c (.sqc)

    Database functions




    FUNCTIONS:

        pxPromotionQuotaStartBrowse  declare and open Cursor
        pxPromotionQuotaGetNext      get next record
        pxPromotionQuotaEndBrowse    close cursor
        pxPromotionQuotaRead         get one record
        pxPromotionQuotaReadLock     get one record with lock
        pxPromotionQuotaInsert       Insert record
        pxPromotionQuotaUpdate       Update record
        pxPromotionQuotaDelete       Delete record


REVISION HISTORY

25 Jun 2004 V1.00 REV 00 written by Ysbrand Bouma

*/


#include <stddef.h>         /* standard C run-time header */
#include <stdio.h>          /* standard C run-time header */
#include <pxrecord.h>       /* all record structures */
#include "pxdbfunc.h"
#include "pxdbxx.h"
#include "ndefs.h"
#include <pxenv.h>
#include <tpromotionquota.h>
#include <keys.h>

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxPromotionQuotaStartBrowse                                   */
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
int pxPromotionQuotaStartBrowse
(
     struct tPROMOTIONQUOTA* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_PROMOTIONQUOTA * recordp;
#ifdef MCtpromotionquota
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_PROMOTIONQUOTA*10+F_StartBrowse;
    recordp = (struct C_PROMOTIONQUOTA *) record;

    if (!(sizeof(struct C_PROMOTIONQUOTA) == sizeof(struct tPROMOTIONQUOTA)))
       return cDBXR_DEFINITION;


#ifdef MCtpromotionquota
    strcpy(matchcode,recordp->MCtpromotionquota);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        PROMOTIONQUOTA_LISTE
    from PROMOTIONQUOTA
    DWtpromotionquota
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        PROMOTIONQUOTA_LISTE
    from PROMOTIONQUOTA
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif
    EXEC SQL DECLARE C2 CURSOR FOR
        SELECT
        PROMOTIONQUOTA_LISTE
    from PROMOTIONQUOTA
    where PROMOTIONQUOTA.BRANCHNO        = :recordp->BRANCHNO
    and   PROMOTIONQUOTA.PROMOTION_NO    = :recordp->PROMOTION_NO
    and  (PROMOTIONQUOTA.ARTICLENO  = :recordp->ARTICLENO or PROMOTIONQUOTA.ARTICLENO  = 0)
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
       case cCRSPROMOTION_BR_PRO_ART:
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
/*  FUNCTION: pxPromotionQuotaGetNext                                       */
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
int pxPromotionQuotaGetNext
(
    struct tPROMOTIONQUOTA* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_PROMOTIONQUOTA * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_PROMOTIONQUOTA*10+F_GetNext;
    recordp = (struct C_PROMOTIONQUOTA *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into PROMOTIONQUOTA_ZEIGER(recordp);
          break;
       case cCRSPROMOTION_BR_PRO_ART:
          EXEC SQL FETCH C2
          into PROMOTIONQUOTA_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into PROMOTIONQUOTA_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxPromotionQuotaEndBrowse                                     */
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
int pxPromotionQuotaEndBrowse
(
    int browseid
)
{
    functionnr = F_PROMOTIONQUOTA*10+F_EndBrowse;

    /* close the cursor */
    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL CLOSE C0;
          break;
       case cCRSPROMOTION_BR_PRO_ART:
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
/*  FUNCTION: pxPromotionQuotaRead                                          */
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

int pxPromotionQuotaRead
(
    struct tPROMOTIONQUOTA* record
#ifdef SKtpromotionquota
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_PROMOTIONQUOTA * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_PROMOTIONQUOTA*10+F_Read;
    recordp = (struct C_PROMOTIONQUOTA *) record;

#ifdef SKtpromotionquota
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        PROMOTIONQUOTA_LISTE
     into PROMOTIONQUOTA_ZEIGER(recordp)
     from PROMOTIONQUOTA
     where SKtpromotionquota;
     break;
    default:
#endif

    EXEC SQL SELECT
        PROMOTIONQUOTA_LISTE
     into PROMOTIONQUOTA_ZEIGER(recordp)
     from PROMOTIONQUOTA
     where PKtpromotionquota;

#ifdef SKtpromotionquota
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
/*  FUNCTION: pxPromotionQuotaReadLock                                      */
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
int pxPromotionQuotaReadLock
(
    struct tPROMOTIONQUOTA* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_PROMOTIONQUOTA * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_PROMOTIONQUOTA*10+F_ReadLock;
    recordp = (struct C_PROMOTIONQUOTA *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE tpromotionquota_U1 CURSOR WITH HOLD FOR
        SELECT
        PROMOTIONQUOTA_LISTE
    from PROMOTIONQUOTA
    where PKtpromotionquota
    FOR UPDATE;
    EXEC SQL OPEN tpromotionquota_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH tpromotionquota_U1
      into PROMOTIONQUOTA_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         PROMOTIONQUOTA_LISTE
    into PROMOTIONQUOTA_ZEIGER(recordp)
    from PROMOTIONQUOTA    HOLDLOCK
    where PKtpromotionquota;
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
/*  FUNCTION: pxPromotionQuotaUpdate                                        */
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

int pxPromotionQuotaUpdate
(
    struct tPROMOTIONQUOTA* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_PROMOTIONQUOTA * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_PROMOTIONQUOTA*10+F_Update;
    recordp = (struct C_PROMOTIONQUOTA *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    PROMOTIONQUOTA
    SET
    PROMOTIONQUOTA_UPDATE(recordp)
    where current of tpromotionquota_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE tpromotionquota_U1;
    }
#else

    EXEC SQL UPDATE
    PROMOTIONQUOTA
    SET
    PROMOTIONQUOTA_UPDATE(recordp)
    where PKtpromotionquota;
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
/*  FUNCTION: pxPromotionQuotaInsert                                       */
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
int pxPromotionQuotaInsert
(
    struct tPROMOTIONQUOTA* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_PROMOTIONQUOTA * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_PROMOTIONQUOTA*10+F_Insert;
    recordp = (struct C_PROMOTIONQUOTA *) record;

    EXEC SQL INSERT INTO
    PROMOTIONQUOTA
    (PROMOTIONQUOTA_LISTE)
    VALUES ( PROMOTIONQUOTA_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    PROMOTIONQUOTA
    VALUES ( PROMOTIONQUOTA_ZEIGER(recordp) );   */


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
/*  FUNCTION: pxPromotionQuotaDelete                                        */
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

int pxPromotionQuotaDelete
(
    struct tPROMOTIONQUOTA* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_PROMOTIONQUOTA * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_PROMOTIONQUOTA*10+F_Delete;
    recordp = (struct C_PROMOTIONQUOTA *) record;

    EXEC SQL DELETE FROM
    PROMOTIONQUOTA
    where PKtpromotionquota;

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
