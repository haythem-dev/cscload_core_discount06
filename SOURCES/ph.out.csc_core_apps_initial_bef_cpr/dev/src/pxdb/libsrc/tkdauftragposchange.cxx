/*(c)
 ********************* PHARMX Customer Order Entry Server *********************


    Embedded SQL for C application


    FILE: tkdauftragposchange.c (.sqc)

    Database functions




    FUNCTIONS:

        pxOrderPosChangeStartBrowse  declare and open Cursor
        pxOrderPosChangeGetNext      get next record
        pxOrderPosChangeEndBrowse    close cursor
        pxOrderPosChangeRead         get one record
        pxOrderPosChangeReadLock     get one record with lock
        pxOrderPosChangeInsert       Insert record
        pxOrderPosChangeUpdate       Update record
        pxOrderPosChangeDelete       Delete record


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
#include <tkdauftragposchange.h>
#include <keys.h>

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxOrderPosChangeStartBrowse                                   */
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
int pxOrderPosChangeStartBrowse
(
     struct tKDAUFTRAGPOSCHANGE* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGPOSCHANGE * recordp;
#ifdef MCtkdauftragposchange
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_KDAUFTRAGPOSCHANGE*10+F_StartBrowse;
    recordp = (struct C_KDAUFTRAGPOSCHANGE *) record;

    if (!(sizeof(struct C_KDAUFTRAGPOSCHANGE) == sizeof(struct tKDAUFTRAGPOSCHANGE)))
       return cDBXR_DEFINITION;


#ifdef MCtkdauftragposchange
    strcpy(matchcode,recordp->MCtkdauftragposchange);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        KDAUFTRAGPOSCHANGE_LISTE
    from KDAUFTRAGPOSCHANGE
    DWtkdauftragposchange
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        KDAUFTRAGPOSCHANGE_LISTE
    from KDAUFTRAGPOSCHANGE
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
/*  FUNCTION: pxOrderPosChangeGetNext                                       */
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
int pxOrderPosChangeGetNext
(
    struct tKDAUFTRAGPOSCHANGE* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGPOSCHANGE * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_KDAUFTRAGPOSCHANGE*10+F_GetNext;
    recordp = (struct C_KDAUFTRAGPOSCHANGE *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into KDAUFTRAGPOSCHANGE_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into KDAUFTRAGPOSCHANGE_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxOrderPosChangeEndBrowse                                     */
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
int pxOrderPosChangeEndBrowse
(
    int browseid
)
{
    functionnr = F_KDAUFTRAGPOSCHANGE*10+F_EndBrowse;

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
/*  FUNCTION: pxOrderPosChangeRead                                          */
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

int pxOrderPosChangeRead
(
    struct tKDAUFTRAGPOSCHANGE* record
#ifdef SKtkdauftragposchange
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGPOSCHANGE * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRAGPOSCHANGE*10+F_Read;
    recordp = (struct C_KDAUFTRAGPOSCHANGE *) record;

#ifdef SKtkdauftragposchange
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        KDAUFTRAGPOSCHANGE_LISTE
     into KDAUFTRAGPOSCHANGE_ZEIGER(recordp)
     from KDAUFTRAGPOSCHANGE
     where SKtkdauftragposchange;
     break;
    default:
#endif

    EXEC SQL SELECT
        KDAUFTRAGPOSCHANGE_LISTE
     into KDAUFTRAGPOSCHANGE_ZEIGER(recordp)
     from KDAUFTRAGPOSCHANGE
     where PKtkdauftragposchange;

#ifdef SKtkdauftragposchange
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
/*  FUNCTION: pxOrderPosChangeReadLock                                      */
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
int pxOrderPosChangeReadLock
(
    struct tKDAUFTRAGPOSCHANGE* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGPOSCHANGE * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRAGPOSCHANGE*10+F_ReadLock;
    recordp = (struct C_KDAUFTRAGPOSCHANGE *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE tkdauftragposchange_U1 CURSOR WITH HOLD FOR
        SELECT
        KDAUFTRAGPOSCHANGE_LISTE
    from KDAUFTRAGPOSCHANGE
    where PKtkdauftragposchange
    FOR UPDATE;
    EXEC SQL OPEN tkdauftragposchange_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH tkdauftragposchange_U1
      into KDAUFTRAGPOSCHANGE_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         KDAUFTRAGPOSCHANGE_LISTE
    into KDAUFTRAGPOSCHANGE_ZEIGER(recordp)
    from KDAUFTRAGPOSCHANGE    HOLDLOCK
    where PKtkdauftragposchange;
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
/*  FUNCTION: pxOrderPosChangeUpdate                                        */
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

int pxOrderPosChangeUpdate
(
    struct tKDAUFTRAGPOSCHANGE* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGPOSCHANGE * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRAGPOSCHANGE*10+F_Update;
    recordp = (struct C_KDAUFTRAGPOSCHANGE *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    KDAUFTRAGPOSCHANGE
    SET
    KDAUFTRAGPOSCHANGE_UPDATE(recordp)
    where current of tkdauftragposchange_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE tkdauftragposchange_U1;
    }
#else

    EXEC SQL UPDATE
    KDAUFTRAGPOSCHANGE
    SET
    KDAUFTRAGPOSCHANGE_UPDATE(recordp)
    where PKtkdauftragposchange;
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
/*  FUNCTION: pxOrderPosChangeInsert                                       */
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
int pxOrderPosChangeInsert
(
    struct tKDAUFTRAGPOSCHANGE* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGPOSCHANGE * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRAGPOSCHANGE*10+F_Insert;
    recordp = (struct C_KDAUFTRAGPOSCHANGE *) record;

    EXEC SQL INSERT INTO
    KDAUFTRAGPOSCHANGE
    (KDAUFTRAGPOSCHANGE_LISTE)
    VALUES ( KDAUFTRAGPOSCHANGE_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    KDAUFTRAGPOSCHANGE
    VALUES ( KDAUFTRAGPOSCHANGE_ZEIGER(recordp) );   */


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
/*  FUNCTION: pxOrderPosChangeDelete                                        */
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

int pxOrderPosChangeDelete
(
    struct tKDAUFTRAGPOSCHANGE* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGPOSCHANGE * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRAGPOSCHANGE*10+F_Delete;
    recordp = (struct C_KDAUFTRAGPOSCHANGE *) record;

    EXEC SQL DELETE FROM
    KDAUFTRAGPOSCHANGE
    where PKtkdauftragposchange;

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
