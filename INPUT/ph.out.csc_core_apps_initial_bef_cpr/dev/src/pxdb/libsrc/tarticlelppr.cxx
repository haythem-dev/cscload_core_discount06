/*(c)
 ********************* PHARMX Customer Order Entry Server *********************


    Embedded SQL for C application


    FILE: tarticlelppr.c (.sqc)

    Database functions




    FUNCTIONS:

        pxArticleLpprStartBrowse  declare and open Cursor
        pxArticleLpprGetNext      get next record
        pxArticleLpprEndBrowse    close cursor
        pxArticleLpprRead         get one record
        pxArticleLpprReadLock     get one record with lock
        pxArticleLpprInsert       Insert record
        pxArticleLpprUpdate       Update record
        pxArticleLpprDelete       Delete record


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
#include <tarticlelppr.h>
#include <keys.h>

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxArticleLpprStartBrowse                                   */
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
int pxArticleLpprStartBrowse
(
     struct tARTICLELPPR* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTICLELPPR * recordp;
#ifdef MCtarticlelppr
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_ARTICLELPPR*10+F_StartBrowse;
    recordp = (struct C_ARTICLELPPR *) record;

    if (!(sizeof(struct C_ARTICLELPPR) == sizeof(struct tARTICLELPPR)))
       return cDBXR_DEFINITION;


#ifdef MCtarticlelppr
    strcpy(matchcode,recordp->MCtarticlelppr);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        ARTICLELPPR_LISTE
    from ARTICLELPPR
    DWtarticlelppr
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        ARTICLELPPR_LISTE
    from ARTICLELPPR
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
/*  FUNCTION: pxArticleLpprGetNext                                       */
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
int pxArticleLpprGetNext
(
    struct tARTICLELPPR* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTICLELPPR * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_ARTICLELPPR*10+F_GetNext;
    recordp = (struct C_ARTICLELPPR *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into ARTICLELPPR_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into ARTICLELPPR_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxArticleLpprEndBrowse                                     */
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
int pxArticleLpprEndBrowse
(
    int browseid
)
{
    functionnr = F_ARTICLELPPR*10+F_EndBrowse;

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
/*  FUNCTION: pxArticleLpprRead                                          */
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

int pxArticleLpprRead
(
    struct tARTICLELPPR* record
#ifdef SKtarticlelppr
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTICLELPPR * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTICLELPPR*10+F_Read;
    recordp = (struct C_ARTICLELPPR *) record;

#ifdef SKtarticlelppr
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        ARTICLELPPR_LISTE
     into ARTICLELPPR_ZEIGER(recordp)
     from ARTICLELPPR
     where SKtarticlelppr;
     break;
    default:
#endif

    EXEC SQL SELECT
        ARTICLELPPR_LISTE
     into ARTICLELPPR_ZEIGER(recordp)
     from ARTICLELPPR
     where PKtarticlelppr;

#ifdef SKtarticlelppr
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
/*  FUNCTION: pxArticleLpprReadLock                                      */
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
int pxArticleLpprReadLock
(
    struct tARTICLELPPR* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTICLELPPR * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTICLELPPR*10+F_ReadLock;
    recordp = (struct C_ARTICLELPPR *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE tarticlelppr_U1 CURSOR WITH HOLD FOR
        SELECT
        ARTICLELPPR_LISTE
    from ARTICLELPPR
    where PKtarticlelppr
    FOR UPDATE;
    EXEC SQL OPEN tarticlelppr_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH tarticlelppr_U1
      into ARTICLELPPR_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         ARTICLELPPR_LISTE
    into ARTICLELPPR_ZEIGER(recordp)
    from ARTICLELPPR    HOLDLOCK
    where PKtarticlelppr;
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
/*  FUNCTION: pxArticleLpprUpdate                                        */
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

int pxArticleLpprUpdate
(
    struct tARTICLELPPR* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTICLELPPR * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTICLELPPR*10+F_Update;
    recordp = (struct C_ARTICLELPPR *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    ARTICLELPPR
    SET
    ARTICLELPPR_UPDATE(recordp)
    where current of tarticlelppr_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE tarticlelppr_U1;
    }
#else

    EXEC SQL UPDATE
    ARTICLELPPR
    SET
    ARTICLELPPR_UPDATE(recordp)
    where PKtarticlelppr;
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
/*  FUNCTION: pxArticleLpprInsert                                       */
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
int pxArticleLpprInsert
(
    struct tARTICLELPPR* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTICLELPPR * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTICLELPPR*10+F_Insert;
    recordp = (struct C_ARTICLELPPR *) record;

    EXEC SQL INSERT INTO
    ARTICLELPPR
    (ARTICLELPPR_LISTE)
    VALUES ( ARTICLELPPR_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    ARTICLELPPR
    VALUES ( ARTICLELPPR_ZEIGER(recordp) );   */


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
/*  FUNCTION: pxArticleLpprDelete                                        */
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

int pxArticleLpprDelete
(
    struct tARTICLELPPR* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTICLELPPR * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTICLELPPR*10+F_Delete;
    recordp = (struct C_ARTICLELPPR *) record;

    EXEC SQL DELETE FROM
    ARTICLELPPR
    where PKtarticlelppr;

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
