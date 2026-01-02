/*(c)
 ********************* PHARMX Customer Order Entry Server *********************


    Embedded SQL for C application


    FILE: tkdauftragpospromo.c (.sqc)

    Database functions




    FUNCTIONS:

        pxOrderPosPromoStartBrowse  declare and open Cursor
        pxOrderPosPromoGetNext      get next record
        pxOrderPosPromoEndBrowse    close cursor
        pxOrderPosPromoRead         get one record
        pxOrderPosPromoReadLock     get one record with lock
        pxOrderPosPromoInsert       Insert record
        pxOrderPosPromoUpdate       Update record
        pxOrderPosPromoDelete       Delete record


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
#include <tkdauftragpospromo.h>
#include <keys.h>

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxOrderPosPromoStartBrowse                                   */
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
int pxOrderPosPromoStartBrowse
(
     struct tKDAUFTRAGPOSPROMO* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGPOSPROMO * recordp;
#ifdef MCtkdauftragpospromo
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_KDAUFTRAGPOSPROMO*10+F_StartBrowse;
    recordp = (struct C_KDAUFTRAGPOSPROMO *) record;

    if (!(sizeof(struct C_KDAUFTRAGPOSPROMO) == sizeof(struct tKDAUFTRAGPOSPROMO)))
       return cDBXR_DEFINITION;


#ifdef MCtkdauftragpospromo
    strcpy(matchcode,recordp->MCtkdauftragpospromo);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        KDAUFTRAGPOSPROMO_LISTE
    from KDAUFTRAGPOSPROMO
    DWtkdauftragpospromo
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        KDAUFTRAGPOSPROMO_LISTE
    from KDAUFTRAGPOSPROMO
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
/*  FUNCTION: pxOrderPosPromoGetNext                                       */
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
int pxOrderPosPromoGetNext
(
    struct tKDAUFTRAGPOSPROMO* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGPOSPROMO * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_KDAUFTRAGPOSPROMO*10+F_GetNext;
    recordp = (struct C_KDAUFTRAGPOSPROMO *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into KDAUFTRAGPOSPROMO_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into KDAUFTRAGPOSPROMO_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxOrderPosPromoEndBrowse                                     */
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
int pxOrderPosPromoEndBrowse
(
    int browseid
)
{
    functionnr = F_KDAUFTRAGPOSPROMO*10+F_EndBrowse;

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
/*  FUNCTION: pxOrderPosPromoRead                                          */
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

int pxOrderPosPromoRead
(
    struct tKDAUFTRAGPOSPROMO* record
#ifdef SKtkdauftragpospromo
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGPOSPROMO * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRAGPOSPROMO*10+F_Read;
    recordp = (struct C_KDAUFTRAGPOSPROMO *) record;

#ifdef SKtkdauftragpospromo
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        KDAUFTRAGPOSPROMO_LISTE
     into KDAUFTRAGPOSPROMO_ZEIGER(recordp)
     from KDAUFTRAGPOSPROMO
     where SKtkdauftragpospromo;
     break;
    default:
#endif

    EXEC SQL SELECT
        KDAUFTRAGPOSPROMO_LISTE
     into KDAUFTRAGPOSPROMO_ZEIGER(recordp)
     from KDAUFTRAGPOSPROMO
     where PKtkdauftragpospromo;

#ifdef SKtkdauftragpospromo
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
/*  FUNCTION: pxOrderPosPromoReadLock                                      */
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
int pxOrderPosPromoReadLock
(
    struct tKDAUFTRAGPOSPROMO* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGPOSPROMO * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRAGPOSPROMO*10+F_ReadLock;
    recordp = (struct C_KDAUFTRAGPOSPROMO *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE tkdauftragpospromo_U1 CURSOR WITH HOLD FOR
        SELECT
        KDAUFTRAGPOSPROMO_LISTE
    from KDAUFTRAGPOSPROMO
    where PKtkdauftragpospromo
    FOR UPDATE;
    EXEC SQL OPEN tkdauftragpospromo_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH tkdauftragpospromo_U1
      into KDAUFTRAGPOSPROMO_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         KDAUFTRAGPOSPROMO_LISTE
    into KDAUFTRAGPOSPROMO_ZEIGER(recordp)
    from KDAUFTRAGPOSPROMO    HOLDLOCK
    where PKtkdauftragpospromo;
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
/*  FUNCTION: pxOrderPosPromoUpdate                                        */
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

int pxOrderPosPromoUpdate
(
    struct tKDAUFTRAGPOSPROMO* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGPOSPROMO * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRAGPOSPROMO*10+F_Update;
    recordp = (struct C_KDAUFTRAGPOSPROMO *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    KDAUFTRAGPOSPROMO
    SET
    KDAUFTRAGPOSPROMO_UPDATE(recordp)
    where current of tkdauftragpospromo_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE tkdauftragpospromo_U1;
    }
#else

    EXEC SQL UPDATE
    KDAUFTRAGPOSPROMO
    SET
    KDAUFTRAGPOSPROMO_UPDATE(recordp)
    where PKtkdauftragpospromo;
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
/*  FUNCTION: pxOrderPosPromoInsert                                       */
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
int pxOrderPosPromoInsert
(
    struct tKDAUFTRAGPOSPROMO* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGPOSPROMO * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRAGPOSPROMO*10+F_Insert;
    recordp = (struct C_KDAUFTRAGPOSPROMO *) record;

    EXEC SQL INSERT INTO
    KDAUFTRAGPOSPROMO
    (KDAUFTRAGPOSPROMO_LISTE)
    VALUES ( KDAUFTRAGPOSPROMO_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    KDAUFTRAGPOSPROMO
    VALUES ( KDAUFTRAGPOSPROMO_ZEIGER(recordp) );   */


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
/*  FUNCTION: pxOrderPosPromoDelete                                        */
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

int pxOrderPosPromoDelete
(
    struct tKDAUFTRAGPOSPROMO* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGPOSPROMO * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRAGPOSPROMO*10+F_Delete;
    recordp = (struct C_KDAUFTRAGPOSPROMO *) record;

    EXEC SQL DELETE FROM
    KDAUFTRAGPOSPROMO
    where PKtkdauftragpospromo;

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
