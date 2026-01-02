/*(c)
 ********************* PHARMX Customer Order Entry Server *********************


    Embedded SQL for C application


    FILE: tpromotions.c (.sqc)

    Database functions




    FUNCTIONS:

        pxPromotionsStartBrowse  declare and open Cursor
        pxPromotionsGetNext      get next record
        pxPromotionsEndBrowse    close cursor
        pxPromotionsRead         get one record
        pxPromotionsReadLock     get one record with lock
        pxPromotionsInsert       Insert record
        pxPromotionsUpdate       Update record
        pxPromotionsDelete       Delete record


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
#include <tpromotions.h>
#include <keys.h>

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxPromotionsStartBrowse                                   */
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
int pxPromotionsStartBrowse
(
     struct tPROMOTIONS* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_PROMOTIONS * recordp;
#ifdef MCtpromotions
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_PROMOTIONS*10+F_StartBrowse;
    recordp = (struct C_PROMOTIONS *) record;

    if (!(sizeof(struct C_PROMOTIONS) == sizeof(struct tPROMOTIONS)))
       return cDBXR_DEFINITION;


#ifdef MCtpromotions
    strcpy(matchcode,recordp->MCtpromotions);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        PROMOTIONS_LISTE
    from PROMOTIONS
    DWtpromotions
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        PROMOTIONS_LISTE
    from PROMOTIONS
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
/*  FUNCTION: pxPromotionsGetNext                                       */
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
int pxPromotionsGetNext
(
    struct tPROMOTIONS* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_PROMOTIONS * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_PROMOTIONS*10+F_GetNext;
    recordp = (struct C_PROMOTIONS *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into PROMOTIONS_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into PROMOTIONS_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxPromotionsEndBrowse                                     */
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
int pxPromotionsEndBrowse
(
    int browseid
)
{
    functionnr = F_PROMOTIONS*10+F_EndBrowse;

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
/*  FUNCTION: pxPromotionsRead                                          */
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

int pxPromotionsRead
(
    struct tPROMOTIONS* record
#ifdef SKtpromotions
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_PROMOTIONS * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_PROMOTIONS*10+F_Read;
    recordp = (struct C_PROMOTIONS *) record;

#ifdef SKtpromotions
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        PROMOTIONS_LISTE
     into PROMOTIONS_ZEIGER(recordp)
     from PROMOTIONS
     where SKtpromotions;
     break;
    default:
#endif

    EXEC SQL SELECT
        PROMOTIONS_LISTE
     into PROMOTIONS_ZEIGER(recordp)
     from PROMOTIONS
     where PKtpromotions;

#ifdef SKtpromotions
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
/*  FUNCTION: pxPromotionsReadLock                                      */
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
int pxPromotionsReadLock
(
    struct tPROMOTIONS* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_PROMOTIONS * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_PROMOTIONS*10+F_ReadLock;
    recordp = (struct C_PROMOTIONS *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE tpromotions_U1 CURSOR WITH HOLD FOR
        SELECT
        PROMOTIONS_LISTE
    from PROMOTIONS
    where PKtpromotions
    FOR UPDATE;
    EXEC SQL OPEN tpromotions_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH tpromotions_U1
      into PROMOTIONS_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         PROMOTIONS_LISTE
    into PROMOTIONS_ZEIGER(recordp)
    from PROMOTIONS    HOLDLOCK
    where PKtpromotions;
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
/*  FUNCTION: pxPromotionsUpdate                                        */
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

int pxPromotionsUpdate
(
    struct tPROMOTIONS* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_PROMOTIONS * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_PROMOTIONS*10+F_Update;
    recordp = (struct C_PROMOTIONS *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    PROMOTIONS
    SET
    PROMOTIONS_UPDATE(recordp)
    where current of tpromotions_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE tpromotions_U1;
    }
#else

    EXEC SQL UPDATE
    PROMOTIONS
    SET
    PROMOTIONS_UPDATE(recordp)
    where PKtpromotions;
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
/*  FUNCTION: pxPromotionsInsert                                       */
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
int pxPromotionsInsert
(
    struct tPROMOTIONS* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_PROMOTIONS * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_PROMOTIONS*10+F_Insert;
    recordp = (struct C_PROMOTIONS *) record;

    EXEC SQL INSERT INTO
    PROMOTIONS
    (PROMOTIONS_LISTE)
    VALUES ( PROMOTIONS_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    PROMOTIONS
    VALUES ( PROMOTIONS_ZEIGER(recordp) );   */


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
/*  FUNCTION: pxPromotionsDelete                                        */
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

int pxPromotionsDelete
(
    struct tPROMOTIONS* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_PROMOTIONS * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_PROMOTIONS*10+F_Delete;
    recordp = (struct C_PROMOTIONS *) record;

    EXEC SQL DELETE FROM
    PROMOTIONS
    where PKtpromotions;

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
