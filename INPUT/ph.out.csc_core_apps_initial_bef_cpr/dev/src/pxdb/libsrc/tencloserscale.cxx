/*(c)
 ********************* PHARMX Customer Order Entry Server *********************


    Embedded SQL for C application


    FILE: tencloserscale.c (.sqc)

    Database functions




    FUNCTIONS:

        pxEncloserScaleStartBrowse  declare and open Cursor
        pxEncloserScaleGetNext      get next record
        pxEncloserScaleEndBrowse    close cursor
        pxEncloserScaleRead         get one record
        pxEncloserScaleReadLock     get one record with lock
        pxEncloserScaleInsert       Insert record
        pxEncloserScaleUpdate       Update record
        pxEncloserScaleDelete       Delete record


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
#include <tencloserscale.h>
#include <keys.h>

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxEncloserScaleStartBrowse                                   */
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
int pxEncloserScaleStartBrowse
(
     struct tENCLOSERSCALE* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ENCLOSERSCALE * recordp;
#ifdef MCtencloserscale
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_ENCLOSERSCALE*10+F_StartBrowse;
    recordp = (struct C_ENCLOSERSCALE *) record;

    if (!(sizeof(struct C_ENCLOSERSCALE) == sizeof(struct tENCLOSERSCALE)))
       return cDBXR_DEFINITION;


#ifdef MCtencloserscale
    strcpy(matchcode,recordp->MCtencloserscale);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        ENCLOSERSCALE_LISTE
    from ENCLOSERSCALE
    DWtencloserscale
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        ENCLOSERSCALE_LISTE
    from ENCLOSERSCALE
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
/*  FUNCTION: pxEncloserScaleGetNext                                       */
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
int pxEncloserScaleGetNext
(
    struct tENCLOSERSCALE* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ENCLOSERSCALE * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_ENCLOSERSCALE*10+F_GetNext;
    recordp = (struct C_ENCLOSERSCALE *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into ENCLOSERSCALE_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into ENCLOSERSCALE_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxEncloserScaleEndBrowse                                     */
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
int pxEncloserScaleEndBrowse
(
    int browseid
)
{
    functionnr = F_ENCLOSERSCALE*10+F_EndBrowse;

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
/*  FUNCTION: pxEncloserScaleRead                                          */
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

int pxEncloserScaleRead
(
    struct tENCLOSERSCALE* record
#ifdef SKtencloserscale
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ENCLOSERSCALE * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ENCLOSERSCALE*10+F_Read;
    recordp = (struct C_ENCLOSERSCALE *) record;

#ifdef SKtencloserscale
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        ENCLOSERSCALE_LISTE
     into ENCLOSERSCALE_ZEIGER(recordp)
     from ENCLOSERSCALE
     where SKtencloserscale;
     break;
    default:
#endif

    EXEC SQL SELECT
        ENCLOSERSCALE_LISTE
     into ENCLOSERSCALE_ZEIGER(recordp)
     from ENCLOSERSCALE
     where PKtencloserscale;

#ifdef SKtencloserscale
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
/*  FUNCTION: pxEncloserScaleReadLock                                      */
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
int pxEncloserScaleReadLock
(
    struct tENCLOSERSCALE* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ENCLOSERSCALE * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ENCLOSERSCALE*10+F_ReadLock;
    recordp = (struct C_ENCLOSERSCALE *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE tencloserscale_U1 CURSOR WITH HOLD FOR
        SELECT
        ENCLOSERSCALE_LISTE
    from ENCLOSERSCALE
    where PKtencloserscale
    FOR UPDATE;
    EXEC SQL OPEN tencloserscale_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH tencloserscale_U1
      into ENCLOSERSCALE_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         ENCLOSERSCALE_LISTE
    into ENCLOSERSCALE_ZEIGER(recordp)
    from ENCLOSERSCALE    HOLDLOCK
    where PKtencloserscale;
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
/*  FUNCTION: pxEncloserScaleUpdate                                        */
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

int pxEncloserScaleUpdate
(
    struct tENCLOSERSCALE* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ENCLOSERSCALE * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ENCLOSERSCALE*10+F_Update;
    recordp = (struct C_ENCLOSERSCALE *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    ENCLOSERSCALE
    SET
    ENCLOSERSCALE_UPDATE(recordp)
    where current of tencloserscale_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE tencloserscale_U1;
    }
#else

    EXEC SQL UPDATE
    ENCLOSERSCALE
    SET
    ENCLOSERSCALE_UPDATE(recordp)
    where PKtencloserscale;
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
/*  FUNCTION: pxEncloserScaleInsert                                       */
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
int pxEncloserScaleInsert
(
    struct tENCLOSERSCALE* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ENCLOSERSCALE * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ENCLOSERSCALE*10+F_Insert;
    recordp = (struct C_ENCLOSERSCALE *) record;

    EXEC SQL INSERT INTO
    ENCLOSERSCALE
    (ENCLOSERSCALE_LISTE)
    VALUES ( ENCLOSERSCALE_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    ENCLOSERSCALE
    VALUES ( ENCLOSERSCALE_ZEIGER(recordp) );   */


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
/*  FUNCTION: pxEncloserScaleDelete                                        */
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

int pxEncloserScaleDelete
(
    struct tENCLOSERSCALE* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ENCLOSERSCALE * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ENCLOSERSCALE*10+F_Delete;
    recordp = (struct C_ENCLOSERSCALE *) record;

    EXEC SQL DELETE FROM
    ENCLOSERSCALE
    where PKtencloserscale;

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
