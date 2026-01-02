/*(c)
 ********************* PHARMX Customer Order Entry Server *********************


    Embedded SQL for C application


    FILE: tpromotionquotacst.c (.sqc)

    Database functions




    FUNCTIONS:

        pxPromotionQuotaCstStartBrowse  declare and open Cursor
        pxPromotionQuotaCstGetNext      get next record
        pxPromotionQuotaCstEndBrowse    close cursor
        pxPromotionQuotaCstRead         get one record
        pxPromotionQuotaCstReadLock     get one record with lock
        pxPromotionQuotaCstInsert       Insert record
        pxPromotionQuotaCstUpdate       Update record
        pxPromotionQuotaCstDelete       Delete record


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
#include <tpromotionquotacst.h>
#include <keys.h>

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxPromotionQuotaCstStartBrowse                                   */
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
int pxPromotionQuotaCstStartBrowse
(
     struct tPROMOTIONQUOTACST* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_PROMOTIONQUOTACST * recordp;
#ifdef MCtpromotionquotacst
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_PROMOTIONQUOTACST*10+F_StartBrowse;
    recordp = (struct C_PROMOTIONQUOTACST *) record;

    if (!(sizeof(struct C_PROMOTIONQUOTACST) == sizeof(struct tPROMOTIONQUOTACST)))
       return cDBXR_DEFINITION;


#ifdef MCtpromotionquotacst
    strcpy(matchcode,recordp->MCtpromotionquotacst);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        PROMOTIONQUOTACST_LISTE
    from PROMOTIONQUOTACST
    DWtpromotionquotacst
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        PROMOTIONQUOTACST_LISTE
    from PROMOTIONQUOTACST
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif
    EXEC SQL DECLARE C2 CURSOR FOR
        SELECT
        PROMOTIONQUOTACST_LISTE
    from PROMOTIONQUOTACST
    where PROMOTIONQUOTACST.BRANCHNO        = :recordp->BRANCHNO
    and   PROMOTIONQUOTACST.PROMOTION_NO    = :recordp->PROMOTION_NO
    and   PROMOTIONQUOTACST.CUSTOMERNO      = :recordp->CUSTOMERNO
    and  (PROMOTIONQUOTACST.ARTICLENO  = :recordp->ARTICLENO or PROMOTIONQUOTACST.ARTICLENO  = 0)
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
       case cCRSPROMOTIONCST_BR_PRO_CST_ART:
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
/*  FUNCTION: pxPromotionQuotaCstGetNext                                       */
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
int pxPromotionQuotaCstGetNext
(
    struct tPROMOTIONQUOTACST* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_PROMOTIONQUOTACST * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_PROMOTIONQUOTACST*10+F_GetNext;
    recordp = (struct C_PROMOTIONQUOTACST *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into PROMOTIONQUOTACST_ZEIGER(recordp);
          break;
       case cCRSPROMOTIONCST_BR_PRO_CST_ART:
          EXEC SQL FETCH C2
          into PROMOTIONQUOTACST_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into PROMOTIONQUOTACST_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxPromotionQuotaCstEndBrowse                                     */
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
int pxPromotionQuotaCstEndBrowse
(
    int browseid
)
{
    functionnr = F_PROMOTIONQUOTACST*10+F_EndBrowse;

    /* close the cursor */
    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL CLOSE C0;
          break;
       case cCRSPROMOTIONCST_BR_PRO_CST_ART:
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
/*  FUNCTION: pxPromotionQuotaCstRead                                          */
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

int pxPromotionQuotaCstRead
(
    struct tPROMOTIONQUOTACST* record
#ifdef SKtpromotionquotacst
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_PROMOTIONQUOTACST * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_PROMOTIONQUOTACST*10+F_Read;
    recordp = (struct C_PROMOTIONQUOTACST *) record;

#ifdef SKtpromotionquotacst
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        PROMOTIONQUOTACST_LISTE
     into PROMOTIONQUOTACST_ZEIGER(recordp)
     from PROMOTIONQUOTACST
     where SKtpromotionquotacst;
     break;
    default:
#endif

    EXEC SQL SELECT
        PROMOTIONQUOTACST_LISTE
     into PROMOTIONQUOTACST_ZEIGER(recordp)
     from PROMOTIONQUOTACST
     where PKtpromotionquotacst;

#ifdef SKtpromotionquotacst
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
/*  FUNCTION: pxPromotionQuotaCstReadLock                                      */
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
int pxPromotionQuotaCstReadLock
(
    struct tPROMOTIONQUOTACST* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_PROMOTIONQUOTACST * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_PROMOTIONQUOTACST*10+F_ReadLock;
    recordp = (struct C_PROMOTIONQUOTACST *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE tpromotionquotacst_U1 CURSOR WITH HOLD FOR
        SELECT
        PROMOTIONQUOTACST_LISTE
    from PROMOTIONQUOTACST
    where PKtpromotionquotacst
    FOR UPDATE;
    EXEC SQL OPEN tpromotionquotacst_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH tpromotionquotacst_U1
      into PROMOTIONQUOTACST_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         PROMOTIONQUOTACST_LISTE
    into PROMOTIONQUOTACST_ZEIGER(recordp)
    from PROMOTIONQUOTACST    HOLDLOCK
    where PKtpromotionquotacst;
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
/*  FUNCTION: pxPromotionQuotaCstUpdate                                        */
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

int pxPromotionQuotaCstUpdate
(
    struct tPROMOTIONQUOTACST* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_PROMOTIONQUOTACST * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_PROMOTIONQUOTACST*10+F_Update;
    recordp = (struct C_PROMOTIONQUOTACST *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    PROMOTIONQUOTACST
    SET
    PROMOTIONQUOTACST_UPDATE(recordp)
    where current of tpromotionquotacst_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE tpromotionquotacst_U1;
    }
#else

    EXEC SQL UPDATE
    PROMOTIONQUOTACST
    SET
    PROMOTIONQUOTACST_UPDATE(recordp)
    where PKtpromotionquotacst;
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
/*  FUNCTION: pxPromotionQuotaCstInsert                                       */
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
int pxPromotionQuotaCstInsert
(
    struct tPROMOTIONQUOTACST* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_PROMOTIONQUOTACST * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_PROMOTIONQUOTACST*10+F_Insert;
    recordp = (struct C_PROMOTIONQUOTACST *) record;

    EXEC SQL INSERT INTO
    PROMOTIONQUOTACST
    (PROMOTIONQUOTACST_LISTE)
    VALUES ( PROMOTIONQUOTACST_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    PROMOTIONQUOTACST
    VALUES ( PROMOTIONQUOTACST_ZEIGER(recordp) );   */


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
/*  FUNCTION: pxPromotionQuotaCstDelete                                        */
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

int pxPromotionQuotaCstDelete
(
    struct tPROMOTIONQUOTACST* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_PROMOTIONQUOTACST * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_PROMOTIONQUOTACST*10+F_Delete;
    recordp = (struct C_PROMOTIONQUOTACST *) record;

    EXEC SQL DELETE FROM
    PROMOTIONQUOTACST
    where PKtpromotionquotacst;

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
