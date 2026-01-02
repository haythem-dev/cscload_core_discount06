/*(c)
 ********************* PHARMX Customer Order Entry Server *********************


    Embedded SQL for C application


    FILE: tpromotionscale.c (.sqc)

    Database functions




    FUNCTIONS:

        pxPromotionScaleStartBrowse  declare and open Cursor
        pxPromotionScaleGetNext      get next record
        pxPromotionScaleEndBrowse    close cursor
        pxPromotionScaleRead         get one record
        pxPromotionScaleReadLock     get one record with lock
        pxPromotionScaleInsert       Insert record
        pxPromotionScaleUpdate       Update record
        pxPromotionScaleDelete       Delete record


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
#include <tpromotionscale.h>
#include <keys.h>

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxPromotionScaleStartBrowse                            */
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
int pxPromotionScaleStartBrowse
(
     struct tPROMOTIONSCALE* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_PROMOTIONSCALE * recordp;
#ifdef MCtpromotionscale
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_PROMOTIONSCALE*10+F_StartBrowse;
    recordp = (struct C_PROMOTIONSCALE *) record;

    if (!(sizeof(struct C_PROMOTIONSCALE) == sizeof(struct tPROMOTIONSCALE)))
       return cDBXR_DEFINITION;


#ifdef MCtpromotions
    strcpy(matchcode,recordp->MCtpromotionscale);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        PROMOTIONSCALE_LISTE
    from PROMOTIONSCALE
    DWtpromotionscale
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C2 CURSOR FOR
        SELECT
        PROMOTIONSCALE_LISTE
    from PROMOTIONSCALE
    where BASEPROMOTION  = :recordp->BASEPROMOTION
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        PROMOTIONSCALE_LISTE
    from PROMOTIONSCALE
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
       case cCRS_BASEPROMOTION:
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
/*  FUNCTION: pxPromotionScaleGetNext                                */
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
int pxPromotionScaleGetNext
(
    struct tPROMOTIONSCALE* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_PROMOTIONSCALE * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_PROMOTIONSCALE*10+F_GetNext;
    recordp = (struct C_PROMOTIONSCALE *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into PROMOTIONSCALE_ZEIGER(recordp);
          break;
       case cCRS_BASEPROMOTION:
          EXEC SQL FETCH C2
          into PROMOTIONSCALE_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into PROMOTIONSCALE_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxPromotionScaleEndBrowse                              */
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
int pxPromotionScaleEndBrowse
(
    int browseid
)
{
    functionnr = F_PROMOTIONSCALE*10+F_EndBrowse;

    /* close the cursor */
    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL CLOSE C0;
          break;
       case cCRS_BASEPROMOTION:
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
/*  FUNCTION: pxPromotionScaleRead                                          */
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

int pxPromotionScaleRead
(
    struct tPROMOTIONSCALE* record
#ifdef SKtpromotionscale
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_PROMOTIONSCALE * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_PROMOTIONSCALE*10+F_Read;
    recordp = (struct C_PROMOTIONSCALE *) record;

#ifdef SKtpromotionscale
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        PROMOTIONSCALE_LISTE
     into PROMOTIONSCALE_ZEIGER(recordp)
     from PROMOTIONSCALE
     where SKtpromotionscale;
     break;
    default:
#endif

    EXEC SQL SELECT
        PROMOTIONSCALE_LISTE
     into PROMOTIONSCALE_ZEIGER(recordp)
     from PROMOTIONSCALE
     where PKtpromotionscale;

#ifdef SKtpromotionscale
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
/*  FUNCTION: pxPromotionScaleReadLock                                      */
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
int pxPromotionScaleReadLock
(
    struct tPROMOTIONSCALE* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_PROMOTIONSCALE * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_PROMOTIONSCALE*10+F_ReadLock;
    recordp = (struct C_PROMOTIONSCALE *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE tpromotionscale_U1 CURSOR WITH HOLD FOR
        SELECT
        PROMOTIONSCALE_LISTE
    from PROMOTIONSCALE
    where PKtpromotionscale
    FOR UPDATE;
    EXEC SQL OPEN tpromotionscale_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH tpromotionscale_U1
      into PROMOTIONSCALE_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         PROMOTIONSCALE_LISTE
    into PROMOTIONSCALE_ZEIGER(recordp)
    from PROMOTIONSCALE    HOLDLOCK
    where PKtpromotionscale;
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
/*  FUNCTION: pxPromotionScaleUpdate                                 */
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

int pxPromotionScaleUpdate
(
    struct tPROMOTIONSCALE* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_PROMOTIONSCALE * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_PROMOTIONSCALE*10+F_Update;
    recordp = (struct C_PROMOTIONSCALE *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    PROMOTIONSCALE
    SET
    PROMOTIONSCALE_UPDATE(recordp)
    where current of tpromotionscale_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE tpromotionscale_U1;
    }
#else

    EXEC SQL UPDATE
    PROMOTIONSCALE
    SET
    PROMOTIONSCALE_UPDATE(recordp)
    where PKtpromotionscale;
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
/*  FUNCTION: pxPromotionScaleInsert                                 */
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
int pxPromotionScaleInsert
(
    struct tPROMOTIONSCALE* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_PROMOTIONSCALE * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_PROMOTIONSCALE*10+F_Insert;
    recordp = (struct C_PROMOTIONSCALE *) record;

    EXEC SQL INSERT INTO
    PROMOTIONSCALE
    (PROMOTIONSCALE_LISTE)
    VALUES ( PROMOTIONSCALE_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    PROMOTIONS
    VALUES ( PROMOTIONSCALE_ZEIGER(recordp) );   */


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
/*  FUNCTION: pxPromotionScaleDelete                                        */
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

int pxPromotionScaleDelete
(
    struct tPROMOTIONSCALE* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_PROMOTIONSCALE * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_PROMOTIONSCALE*10+F_Delete;
    recordp = (struct C_PROMOTIONSCALE *) record;

    EXEC SQL DELETE FROM
    PROMOTIONSCALE
    where PKtpromotionscale;

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
