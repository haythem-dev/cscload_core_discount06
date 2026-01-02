/*(c)
 ********************* PHARMX Customer Order Entry Server *********************


    Embedded SQL for C application


    FILE: tarticleoldprice.c (.sqc)

    Database functions




    FUNCTIONS:

        pxArtOldPriceStartBrowse  declare and open Cursor
        pxArtOldPriceGetNext      get next record
        pxArtOldPriceEndBrowse    close cursor
        pxArtOldPriceRead         get one record
        pxArtOldPriceReadLock     get one record with lock
        pxArtOldPriceInsert       Insert record
        pxArtOldPriceUpdate       Update record
        pxArtOldPriceDelete       Delete record


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
#include <tarticleoldprice.h>
#include <keys.h>

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxArtOldPriceStartBrowse                                   */
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
int pxArtOldPriceStartBrowse
(
     struct tARTICLEOLDPRICE* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTICLEOLDPRICE * recordp;
#ifdef MCtarticleoldprice
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_ARTICLEOLDPRICE*10+F_StartBrowse;
    recordp = (struct C_ARTICLEOLDPRICE *) record;

    if (!(sizeof(struct C_ARTICLEOLDPRICE) == sizeof(struct tARTICLEOLDPRICE)))
       return cDBXR_DEFINITION;


#ifdef MCtarticleoldprice
    strcpy(matchcode,recordp->MCtarticleoldprice);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        ARTICLEOLDPRICE_LISTE
    from ARTICLEOLDPRICE
    DWtarticleoldprice
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        ARTICLEOLDPRICE_LISTE
    from ARTICLEOLDPRICE
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
/*  FUNCTION: pxArtOldPriceGetNext                                       */
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
int pxArtOldPriceGetNext
(
    struct tARTICLEOLDPRICE* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTICLEOLDPRICE * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_ARTICLEOLDPRICE*10+F_GetNext;
    recordp = (struct C_ARTICLEOLDPRICE *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into ARTICLEOLDPRICE_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into ARTICLEOLDPRICE_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxArtOldPriceEndBrowse                                     */
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
int pxArtOldPriceEndBrowse
(
    int browseid
)
{
    functionnr = F_ARTICLEOLDPRICE*10+F_EndBrowse;

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
/*  FUNCTION: pxArtOldPriceRead                                          */
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

int pxArtOldPriceRead
(
    struct tARTICLEOLDPRICE* record
#ifdef SKtarticleoldprice
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTICLEOLDPRICE * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTICLEOLDPRICE*10+F_Read;
    recordp = (struct C_ARTICLEOLDPRICE *) record;

#ifdef SKtarticleoldprice
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        ARTICLEOLDPRICE_LISTE
     into ARTICLEOLDPRICE_ZEIGER(recordp)
     from ARTICLEOLDPRICE
     where SKtarticleoldprice;
     break;
    default:
#endif

    EXEC SQL SELECT
        ARTICLEOLDPRICE_LISTE
     into ARTICLEOLDPRICE_ZEIGER(recordp)
     from ARTICLEOLDPRICE
     where PKtarticleoldprice;

#ifdef SKtarticleoldprice
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
/*  FUNCTION: pxArtOldPriceReadLock                                      */
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
int pxArtOldPriceReadLock
(
    struct tARTICLEOLDPRICE* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTICLEOLDPRICE * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTICLEOLDPRICE*10+F_ReadLock;
    recordp = (struct C_ARTICLEOLDPRICE *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE tarticleoldprice_U1 CURSOR WITH HOLD FOR
        SELECT
        ARTICLEOLDPRICE_LISTE
    from ARTICLEOLDPRICE
    where PKtarticleoldprice
    FOR UPDATE;
    EXEC SQL OPEN tarticleoldprice_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH tarticleoldprice_U1
      into ARTICLEOLDPRICE_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         ARTICLEOLDPRICE_LISTE
    into ARTICLEOLDPRICE_ZEIGER(recordp)
    from ARTICLEOLDPRICE    HOLDLOCK
    where PKtarticleoldprice;
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
/*  FUNCTION: pxArtOldPriceUpdate                                        */
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

int pxArtOldPriceUpdate
(
    struct tARTICLEOLDPRICE* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTICLEOLDPRICE * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTICLEOLDPRICE*10+F_Update;
    recordp = (struct C_ARTICLEOLDPRICE *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    ARTICLEOLDPRICE
    SET
    ARTICLEOLDPRICE_UPDATE(recordp)
    where current of tarticleoldprice_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE tarticleoldprice_U1;
    }
#else

    EXEC SQL UPDATE
    ARTICLEOLDPRICE
    SET
    ARTICLEOLDPRICE_UPDATE(recordp)
    where PKtarticleoldprice;
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
/*  FUNCTION: pxArtOldPriceInsert                                       */
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
int pxArtOldPriceInsert
(
    struct tARTICLEOLDPRICE* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTICLEOLDPRICE * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTICLEOLDPRICE*10+F_Insert;
    recordp = (struct C_ARTICLEOLDPRICE *) record;

    EXEC SQL INSERT INTO
    ARTICLEOLDPRICE
    (ARTICLEOLDPRICE_LISTE)
    VALUES ( ARTICLEOLDPRICE_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    ARTICLEOLDPRICE
    VALUES ( ARTICLEOLDPRICE_ZEIGER(recordp) );   */


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
/*  FUNCTION: pxArtOldPriceDelete                                        */
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

int pxArtOldPriceDelete
(
    struct tARTICLEOLDPRICE* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTICLEOLDPRICE * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTICLEOLDPRICE*10+F_Delete;
    recordp = (struct C_ARTICLEOLDPRICE *) record;

    EXEC SQL DELETE FROM
    ARTICLEOLDPRICE
    where PKtarticleoldprice;

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
